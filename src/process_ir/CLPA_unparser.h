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
 * A simple hello-world program would look like this:
 *
 *		phc_actual_parameter("#20","#22","#21")
 *		phc_actual_parameter("#23","#25","#24")
 *		phc_token_variable_name_list("#6",[])
 *		phc_token_variable_name_list("#13",[])
 *		phc_token_variable_name_list("#21",[])
 *		phc_token_variable_name_list("#24",[])
 *		phc_token_variable_name_list("#29",[])
 *		phc_eval_expr("#2","#3")
 *		phc_eval_expr("#9","#10")
 *		phc_eval_expr("#16","#17")
 *		phc_assignment("#3","#5",false,"#4")
 *		phc_assignment("#10","#12",false,"#11")
 *		phc_assignment("#17","#28",false,"#18")
 *		phc_variable("#5","#8","#7","#6")
 *		phc_variable("#12","#15","#14","#13")
 *		phc_variable("#28","#31","#30","#29")
 *		phc_actual_parameter_list("#19",["#20","#23"])
 *		phc_method_invocation("#18","#27","#26","#19")
 *		phc_string("#4","helloworld")
 *		phc_string("#7","TLE0")
 *		phc_string("#11","%s")
 *		phc_string("#14","TLE1")
 *		phc_string("#22","TLE1")
 *		phc_string("#25","TLE0")
 *		phc_string("#26","printf")
 *		phc_string("#30","TSe0")
 *		phc_curfn("main")
 *		phc_php_script("#0","#1")
 *		phc_statement_list("#1",["#2","#9","#16"])
 *
 *	The first string is gererally the ID. So the PHP_script #0 has 1 param,
 *	named #1. #1 is a statement_list containing #2, #9 and #16. And so on.
 *
 *
 * This is quite simple with a visitor. On descending the tree, we add each
 * node to a stack. On re-ascending, every node leaves itself on the stack. For
 * each node, we search the stack looking for itself, and all nodes which we
 * pop are parameters to the predicate.
 */


template
<
	class Script,
	class Node,
	class Literal,
	class Identifier,
	class Visitor
>
class CLPA_unparser : public Visitor 
{
protected:
	stack<Object*> ids;

public:

/*	void visit_marker(char const* name, bool value)
	{
		ids.push (new Boolean (value));
	}
*/
	void pre_list(char const* type_id, int size)
	{
		cout << "LIST" << endl;
		cout << "<" << type_id << "_list>" << endl;
	}

	void post_list(char const* type_id, int size)
	{
		cout << "POST_LIST" << endl;
		cout << "</" << type_id << "_list>" << endl;
	}

	/* Get an id for this node, and add it to the stack. The magic
	 * happens in post_node. */
	void pre_node(Node* in)
	{
		in->attrs->set ("phc.clpa.id", get_id (in));
		ids.push (in);
	}

	void pre_identifier (Identifier* in)
	{
		ids.push (in->get_value_as_string ());
	}

	void pre_literal (Literal* in)
	{
		ids.push (in->get_value_as_string ());
	}



	/* If we search backwards down the stack until we find our own
	 * node, then all subnodes will be parameters to this node. */
	void post_node(Node* in)
	{
		// The params are either IDs or literals
		List<String*>* params = new List<String*>;
		while (ids.top () != in)
		{
			Object* obj = ids.top();
			cdebug << "Removing: " << demangle(obj, true);

			// Get IDs for nodes
			if (dynamic_cast<Literal*> (obj))
			{
				Literal* lit = dynamic_cast<Literal*> (obj);
				params->push_back (lit->get_value_as_string ());
			}
			else if (dynamic_cast<Node*> (obj))
			{
				Node* node = dynamic_cast<Node*> (obj);
				params->push_back (node->attrs->get_string ("phc.clpa.id"));
			}
/*			else if (dynamic_cast<Boolean*> (obj))
			{
				Boolean* b = dynamic_cast<Boolean*> (obj);
				params->push_back (s(b->value() ? "true" : "false"));
			}
*/			else if (dynamic_cast<String*> (obj))
			{
				String* b = dynamic_cast<String*> (obj);
				params->push_back (b);
			}
			else
				assert (0);

			ids.pop ();
		}

		List<String*>::const_iterator i = params->begin ();
		while (i != params->end ())
		{
			cout << **i;
			i++;

			// no comma on final iteration
			if (i != params->end ())
				cout << ", ";

		}
		cout << ")" << endl;
	}

protected:

	String* get_id (Node* node)
	{
		static int id = 0;
		String* string_id;

		if (node->attrs->has ("phc.clpa.id"))
			string_id = node->attrs->get_string ("phc.clpa.id");
		else
		{
			stringstream ss;
			ss << "#" << id;
			string_id = new String(ss.str());
			node->attrs->set ("phc.clpa.id", string_id);
			id++;
		}
		return string_id;
	}

};

#include "AST_visitor.h"
class AST_CLPA_unparser : public CLPA_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Literal,
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
	MIR::Identifier,
	MIR::Visitor
>
{
};

#endif // PHC_CLPA_UNPARSER
