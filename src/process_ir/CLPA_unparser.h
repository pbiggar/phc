/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate syntax databases for the Calypso interpreter.
 */

#ifndef PHC_CLPA_UNPARSER
#define PHC_CLPA_UNPARSER

#include <iostream>
#include <stack>
#include "lib/base64.h"
#include "lib/demangle.h"
#include "lib/error.h"
#include "lib/String.h"
#include "lib/List.h"

/* We want to dump our IR pretty much directly into Calypso, using the
 * predicates defined by maketea.
 *
 * A simple program would look like this (this is slightly simplied already):
 *
 *		+ast_VARIABLE_NAME (
 *			phc_VARIABLE_NAME_id{4}, 
 *			"a").
 *
 *		+ast_VARIABLE_NAME (
 *			phc_VARIABLE_NAME_id{9}, 
 *			"TSe0").
 *
 *		+ast_VARIABLE_NAME (
 *			phc_VARIABLE_NAME_id{13}, 
 *			"a").
 *
 *		+ast_METHOD_NAME (
 *			phc_METHOD_NAME_id{11}, 
 *			"var_dump").
 *
 *		+ast_Variable (
 *			phc_Variable_id{3}, 
 *			phc_VARIABLE_NAME_id{4}).
 *
 *		+ast_Variable (
 *			phc_Variable_id{8}, 
 *			phc_VARIABLE_NAME_id{9}).
 *
 *		+ast_Variable (
 *			phc_Variable_id{20}, 
 *			phc_VARIABLE_NAME_id{13}).
 *
 *		+ast_Assignment (
 *			phc_Assignment_id{2},
 *			phc_Variable_id{3}, 
 *			phc_Expr_IntLiteral_id{phc_Literal_INT_id{phc_INT_id{102}}}).
 *
 *		+ast_INT (
 *			phc_INT_id{102}, 
 *			5).
 *
 *		+ast_Eval_expr (
 *			phc_Eval_expr_id{1}, 
 *			phc_Expr_Assignment_id{phc_Assignment_id{9}}).
 *
 *		+ast_Actual_parameter (
 *			phc_Actual_parameter_id{12}, 
 *			false, 
 *			phc_Expr_Variable_id{phc_Variable_id{20}}).
 *
 *		+ast_Method_invocation (
 *			phc_Method_invocation_id{10}, 
 *			phc_METHOD_NAME_id{11}, 
 *			[
 *				phc_Actual_parameter_id{12}
 *			]).
 *
 *		+ast_Assignment (
 *			phc_Assignment_id{7}, 
 *			phc_Variable_id{10}, 
 *			phc_Expr_Method_invocation_id{phc_Method_invocation_id{10}}).
 *
 *		+ast_Eval_expr (
 *			phc_Eval_expr_id{6}, 
 *			phc_Expr_Assignment_id{phc_Assignment_id{7}}).
 *
 *		+ast_PHP_script (
 *			phc_PHP_script_id{0}, 
 *			[
 *				phc_Statement_Eval_expr_id{phc_Eval_expr_id{1}}, 
 *				phc_Statement_Eval_expr_id{phc_Eval_expr_id{6}}
 *			]).
 *
 *	The first parameter is the ID. So the PHP_script 0 has 1 param,
 *	which is a list nodes 1 and 6.
 *
 * This is quite simple with a visitor. On descending the tree, we add each
 * node to a stack. On re-ascending, every node leaves itself on the stack.
 * For each node, we search the stack looking for itself, and all nodes which
 * we pop are parameters to the predicate.
 */


template
<
	class Script,
	class Node,
	class Literal,
	class STRING,
	class Identifier,
	class Visitor
>
class CLPA_unparser : public Visitor 
{
protected:
	stack<Object*> ids;
	stack<String*> types;

public:

	void pre_php_script (Script* in)
	{
		cout << "import \"src/generated/AST.clp\".\n" << endl;
	}

	class List_end : public List<Object*> {};

	void visit_marker(char const* name, bool value)
	{
		ids.push (new Boolean (value));
	}

	void visit_null(char const* name_space, char const* type_id)
	{
		ids.push (NULL);
	}

	/* Disjunctive types are represented in the .clp definition as 
	 *		ast_Target ::= 
	 *			ast_Target_ast_Assignment_id {t_ast_Assignment} 
	 *			| ast_Target_ast_Cast_id {t_ast_target}
	 *			| etc ...
	 *
	 *	When we have an ast_Target as a parameter, we need the fact that a
	 *	Target is expected. Since we don't have reflexive access to the type
	 *	hierarchy, we only know that we have an Assignment (note that is skips
	 *	right through Expr, though the hierarchy is target -> expr ->
	 *	assignment). We need to make a note of target at some point, which
	 *	visit_type allows us to do. It records the expected type, which is then
	 *	at the top of the stack.
	 */
	void visit_type (char const* name_space, char const* type_id)
	{
		types.push (new String (type_id));
	}
	
	void post_list(char const* name_space, char const* type_id, int size)
	{
		// Fetch SIZE items off the list and add them within
		List_end* le = new List_end ();
		for(int i = 0; i < size; i++)
		{
			le->push_back (ids.top());
			ids.pop ();
		}
		ids.push (le);
	}

	/* Get an id for this node, and add it to the stack. The magic
	 * happens in post_node. */
	void pre_node(Node* in)
	{
		in->attrs->set ("phc.clpa.id", get_id (in));
		ids.push (in);
	}

	String* wrap_in_quotes (String* str)
	{
		stringstream ss;
		ss << '"' << *str << '"';
		return s(ss.str ());
	}

	void pre_identifier (Identifier* in)
	{
		// Strings need to be wrapped in quotes
		ids.push (wrap_in_quotes (in->get_value_as_string ()));
	}

	void pre_literal (Literal* in)
	{
		String* value = in->get_value_as_string ();

		// Strings need to be wrapped in quotes
		if (in->classid () == STRING::ID)
			value = wrap_in_quotes (value);

		ids.push (value);
	}


	void handle_parameter (Object* obj, List<String*>* params)
	{
		if (obj == NULL)
		{
			// NULL in the IR
			params->push_front (new String ("no"));

			// we dont need this type
			types.pop ();
		}
		else if (dynamic_cast<Node*> (obj))
		{
			// Get IDs for nodes
			Node* node = dynamic_cast<Node*> (obj);
			params->push_front (get_param_id_string (node));

			types.pop();
		}
		else if (dynamic_cast<Boolean*> (obj))
		{
			// Markers are wrapped in bools
			Boolean* b = dynamic_cast<Boolean*> (obj);
			params->push_front (s(b->value() ? "true" : "false"));
		}
		else if (dynamic_cast<String*> (obj))
		{
			// All literals come pre-packed into strings
			String* s = dynamic_cast<String*> (obj);
			params->push_front (s);
		}
		else if (dynamic_cast<List_end*> (obj))
		{
			// Combine all elements of the list into a single param
			List_end* le = dynamic_cast<List_end*> (obj);

			// Get strings for each list element
			List<String*> list_params;
			for_lci (le, Object, i)
			{
				handle_parameter (*i, &list_params);
			}

			// Combine into 1 string
			stringstream ss;
			ss << "[";
			List<String*>::const_iterator i = list_params.begin ();;
			while (i != list_params.end ())
			{
				ss << "\n\t\t" << **i;
				i++;

				if (i != list_params.end ())
					ss << ", ";

			}
			if (list_params.size () != 0)
				ss << "\n\t"; // allow [] for empty lists
			ss << "]";

			params->push_back (s (ss.str ()));
		}
		else
			assert (0);

	}

	/* If we search backwards down the stack until we find our own
	 * node, then all subnodes will be parameters to this node. */
	void post_node(Node* in)
	{
		// Add all parameters to PARAMS from the stack
		List<String*>* params = new List<String*>;
		while (ids.top () != in)
		{
			Object* obj = ids.top();
			handle_parameter (obj, params);
			ids.pop ();
		}

		// Print out params
		cout 
			<< "+ast_" << demangle(in, false) << " (\n\t"
			<< *get_subject_id_string (in);

		for_lci (params, String, i)
		{
			cout << ",\n\t" << **i;
		}
		cout << ").\n" << endl;
	}

protected:

	Integer* get_id (Node* node)
	{
		static int id = 0;

		if (node->attrs->has ("phc.clpa.id"))
			return node->attrs->get_integer ("phc.clpa.id");
		else
		{
			node->attrs->set_integer ("phc.clpa.id", id);
			id++;

			return new Integer (id);
		}
	}

	// SUBJECT is the first parameter to a predicate (aka the 'this' parameter)
	String* get_subject_id_string (Node* in)
	{
		int id = in->attrs->get_integer ("phc.clpa.id")->value();

		stringstream ss;
		ss << "t_ast_" << demangle(in, false) 
			<< "_id {" << id << "}";
		return new String(ss.str());
	}

	String* get_param_id_string (Node* in)
	{
		int id = in->attrs->get_integer ("phc.clpa.id")->value();

		String* type = s (demangle (in, false));
		String* base_type = types.top ();

		stringstream ss;
		if (*base_type == *type)
		{
			ss << "t_ast_" << *type
				<< "_id { " << id << "}";
		}
		else
		{
			ss << "t_ast_" << *base_type
				<< "_t_ast_" << *type
				<< "_id { "
				<< "t_ast_" << *type << "_id {" << id << "} }";
		}

		return new String(ss.str());
	}



};

#include "AST_visitor.h"
class AST_CLPA_unparser : public CLPA_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Literal,
	AST::STRING,
	AST::Identifier,
	AST::Visitor
>
{

};

#include "HIR_visitor.h"
class HIR_CLPA_unparser : public CLPA_unparser
<
	HIR::PHP_script,
	HIR::Node,
	HIR::Literal,
	HIR::STRING,
	HIR::Identifier,
	HIR::Visitor
>
{
};

#include "MIR_visitor.h"
class MIR_CLPA_unparser : public CLPA_unparser
<
	MIR::PHP_script,
	MIR::Node,
	MIR::Literal,
	MIR::STRING,
	MIR::Identifier,
	MIR::Visitor
>
{
};

#endif // PHC_CLPA_UNPARSER
