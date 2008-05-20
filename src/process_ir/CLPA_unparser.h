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
#include "General.h"

/* We want to dump our IR pretty much directly into Calypso, using the
 * predicates defined by maketea.
 *
 * A simple program would look like this:
 *
 * session ast (PROG:string).
 *
 * import "src/generated/AST.clp".
 * 
 * +ast("myprog.php")->vARIABLE_NAME (
 * 	vARIABLE_NAME_id {5},
 * 	"x").
 * 
 * +ast("myprog.php")->vARIABLE_NAME (
 * 	vARIABLE_NAME_id {7},
 * 	"i").
 * 
 * +ast("myprog.php")->variable (
 * 	variable_id {6},
 * 	no,
 * 	variable_name_VARIABLE_NAME_id { vARIABLE_NAME_id {7} },
 * 	[]).
 * 
 * +ast("myprog.php")->variable (
 * 	variable_id {4},
 * 	no,
 * 	variable_name_VARIABLE_NAME_id { vARIABLE_NAME_id {5} },
 * 	[
 * 		yes { expr_Variable_id { Variable_id {6} } }
 * 	]).
 * 
 * +ast("myprog.php")->sTRING (
 * 	sTRING_id {8},
 * 	"xxxxx").
 * 
 * +ast("myprog.php")->assignment (
 * 	assignment_id {3},
 * 	variable_id {4},
 * 	false,
 * 	expr_STRING_id { sTRING_id {8} }).
 * 
 * +ast("myprog.php")->eval_expr (
 * 	Eval_expr_id {2},
 * 	Expr_Assignment_id { Assignment_id {3} }).
 * 
 * +ast("myprog.php")->nop (
 * 	nop_id {9}).
 * 
 * +ast("myprog.php")->pHP_script (
 * 	pHP_script_id {1},
 * 	[
 * 		statement_Eval_expr_id { eval_expr_id {2} }, 
 * 		statement_Nop_id { nop_id {9} }
 * 	]).
 *	The first parameter is the ID. So the PHP_script 1 has 1 param,
 *	which is a list nodes 2 and 9.
 *
 *	The type system is defined using maketea, in src/generated/?.clp. Each IR
 *	type has an associated predicate, and a type TYPE. Each predicate has its
 *	initial parameter being its ID, and subsequent parameters are the IDs of its
 *	arguments. Lists use Calypsos built-in lists ([...]), rather something along
 *	the lines of t_statement_list.  Nullable parameters use the Calypso
 *	'maybe' type, whose constructors are 'yes{}' and 'no'. Lists of Nullable
 *	parameters need to be wrapped as well. All parts are strongly typed. nop_id
 *	{9} indicates a Nop with ID 9. statement_Eval_expr_id means it expects a
 *	statement and we've given it an Eval_expr (which is a subtype of statement).
 *
 * Creating the basic structure is simple enough with a visitor, but there is
 * some subtlety. On descending the tree, we add each node to a stack. On
 * re-ascending, we search the stack looking the current node, and all nodes
 * which we pop are parameters to the predicate for the current node.
 *
 * For markers, we push Bools onto the stack. For literals, we push Strings
 * containing the literal's value. For NULL nullable parameters, we push NULL.
 * For NULL lists, we push NULL. For nullable parameters which are not NULL,
 * we push the node and an instance of Optional (which will be below the node
 * on the stack). For Lists, we fetch SIZE parameters from the stack into the
 * list, and push a List structure on instead. For lists of optional
 * parameters, we put an Optional into the list after each element.
 *
 * */


template
<
	class Script,
	class Node,
	class Literal,
	class STRING,
	class BOOL,
	class Identifier,
	class Visitor
>
class CLPA_unparser : public Visitor 
{
protected:
	stack<Object*> ids;
	stack<String*> types;
	String* filename; // due to bugs, it may not be available everywhere
	String* uc_prefix;
	String* prefix;
	List<String*> keywords;

public:

	void pre_php_script (Script* in)
	{
		filename = in->get_filename ();

		// get prefix in upper and lower case
		uc_prefix = s (demangle (in, true));
		uc_prefix = s (uc_prefix->substr (0, 3));
		prefix  = s (*uc_prefix);
		prefix->toLower ();

		init_keywords ();

		cout << "import \"src/generated/" << *uc_prefix << ".clp\".\n" << endl;
	}

	void init_keywords ()
	{
		keywords.push_back (s("type"));
		keywords.push_back (s("predicate"));
		keywords.push_back (s("session"));
		keywords.push_back (s("analyse"));
		keywords.push_back (s("using"));
		keywords.push_back (s("import"));
	}

	// If its a keyword, then we need to prefix it
	String* check_for_keywords (String* name, String* prefix)
	{
		for_lci (&keywords, String, i)
		{
			if (**i == *name)
			{
				// append prefix
				stringstream ss;
				ss << *prefix << "_" << *name;
				return s (ss.str ());
			}
		}
		return name;
	}

	/* BOOLs are pushed for markers */
	void visit_marker(char const* name, bool value)
	{
		ids.push (new Boolean (value));
	}

	/* NULLs get pushed for null values */
	void visit_null(char const* name_space, char const* type_id)
	{
		ids.push (NULL);
	}
	void visit_null_list(char const* name_space, char const* type_id)
	{
		ids.push (NULL);
	}

	/* Nullable elements get an Optional pushed onto the stack below the element
	 * itself. */
	class Optional : public Object {Object* clone () { return NULL;}};
	void visit_optional(bool is_null)
	{
		if (!is_null)
			ids.push (new Optional);
	}

	/* Disjunctive types are represented in the .clp definition as 
	 *		t_Target ::= 
	 *			target_Assignment_id {t_Assignment} 
	 *			| target_Cast_id {t_cast}
	 *			| etc ...
	 *
	 *	When we have an ast_Target as a parameter, we need the fact that a
	 *	Target is expected. Since we don't have reflexive access to the type
	 *	hierarchy, we only know that we have an Assignment (note that is skips
	 *	right through Expr, though the hierarchy is target -> expr ->
	 *	assignment). We need to make a note of target at some point, which
	 *	visit_type allows us to do. It records the expected type, which is then
	 *	at the top of the types stack.
	 */
	void visit_type (char const* name_space, char const* type_id)
	{
		types.push (new String (type_id));
	}

	/* Take off as many elements as there are in the list, and replace them with the list. */
	class List_end : public List<Object*> {};
	void post_list(char const* name_space, char const* type_id, int size, bool nullable_elements)
	{
		// Fetch SIZE items off the list and add them within
		List_end* le = new List_end ();
		for(int i = 0; i < size; i++)
		{
			Object* obj = ids.top ();
			le->push_back (obj);
			ids.pop ();

			// Optional lists need optional nodes added behind them.
			if (nullable_elements && obj != NULL)
				le->push_back (new Optional);
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

	
	void pre_identifier (Identifier* in)
	{
		// Strings need to be wrapped in quotes
		ids.push (wrap_in_quotes (in->get_value_as_string ()));
	}

	void pre_literal (Literal* in)
	{
		String* value = in->get_value_as_string ();

		// String literals need to be wrapped in quotes, and must be on a single line
		if (in->classid () == STRING::ID)
			value = wrap_in_quotes (escape(value));

		// Bools must be entirely lower case, or Calypso will think they are variable names
		if (in->classid () == BOOL::ID)
			value->toLower();

		ids.push (value);
	}


	/* Turn a stack element into a parameter */
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
		else if (dynamic_cast<Optional*> (obj))
		{
			// wrap in "yes{}"
			stringstream ss;
			ss << "yes { " << *params->front () << "}";

			params->pop_front ();
			params->push_front (new String (ss.str ()));
		}
		else
			assert (0);

	}

	/* If we search backwards down the stack until we find our own
	 * node, then all subnodes will be parameters to this node. */
	void post_node(Node* in)
	{
//		print_stacks (in);

		// All elements above IN on the stack are parameters to INs predicate. Move them into PARAMS.
		List<String*>* params = new List<String*>;
		while (ids.top () != in)
		{
			Object* obj = ids.top();
			handle_parameter (obj, params);
			ids.pop ();
		}

		// Print out the predicate.
		cout 
			<< "+" << *prefix << "(\"" << *filename << "\")->" << *pred_name (in) << " (\n\t"
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
		ss << *constructor_name (in) << " {" << id << "}";
		return new String(ss.str());
	}

	String* get_param_id_string (Node* in)
	{
		int id = in->attrs->get_integer ("phc.clpa.id")->value();

		String* type = type_name (in);
		String* base_type = types.top ();
		types.pop ();

		stringstream ss;
		if (*base_type == *type)
		{
			ss << *constructor_name (in) << " {" << id << "}";
		}
		else
		{
			// see comment at visit_type().
			ss << *disj_constructor_name (base_type, in)
				<< " { "
				<< *constructor_name (in) << "{" << id << "} }";
		}

		return new String(ss.str());
	}

	String* pred_name (Node* in)
	{
		stringstream ss;
		const char* name = demangle (in, false);
		ss << (char)(tolower (name[0]));
		ss << &name[1];

		return check_for_keywords (s (ss.str ()), s("p"));
	}

	String* constructor_name (Node* in)
	{
		stringstream ss;
		const char* name = demangle (in, false);
		ss << (char)(tolower (name[0]));
		ss << (&name[1]);
		ss << "_id";
		return s (ss.str ());
	}

	String* disj_constructor_name (String* base_type, Node* sub_type)
	{
		stringstream ss;
		const char* name = base_type->c_str ();
		ss << (char)(tolower (name[0]));
		ss << (&name[1]);
		ss << "_";
		ss << *type_name (sub_type);
		return s (ss.str ());
	}

	String* type_name (Node* in)
	{
		stringstream ss;
		const char* name = demangle (in, false);
		ss << name;
		return s (ss.str ());
	}

	String* escape(String* s)
	{
		stringstream ss;

		string::iterator i;
		for(i = s->begin(); i != s->end(); i++)
		{
			switch (*i)
			{
				case '\n': // newline
					ss << "\\n";
					break;
				case '\\': // newline
					ss << "\\\\";
					break;
				case '"': // newline
					ss << "\\\"";
					break;
				default:
					ss << *i;
					break;
			}
		}

		return new String(ss.str());	
	}

	String* wrap_in_quotes (String* str)
	{
		stringstream ss;
		ss << '"' << *str << '"';
		return s(ss.str ());
	}

	// Debugging. This is very very slow.
	void print_stack_element (Object * obj)
	{
		cdebug << "*\t";
		if (obj == NULL)
		{
			cdebug << "Optional (no): NULL";
		}
		else if (dynamic_cast<Node*> (obj))
		{
			Node* node = dynamic_cast<Node*> (obj);
			cdebug << "Node: " << demangle (obj, false) << " -- id=" << node->attrs->get_integer ("phc.clpa.id")->value ();
		}
		else if (dynamic_cast<Boolean*> (obj))
		{
			Boolean* b = dynamic_cast<Boolean*> (obj);
			cdebug << "Marker: " << b->value();
		}
		else if (dynamic_cast<String*> (obj))
		{
			// All literals come pre-packed into strings
			String* s = dynamic_cast<String*> (obj);
			cdebug << "Literal: " << *s;
		}
		else if (dynamic_cast<List_end*> (obj))
		{
			List_end* le = dynamic_cast<List_end*> (obj);
			cdebug << "Start List (" << le->size () << ")\n";

			// Get strings for each list element
			List<String*> list_params;
			for_lci (le, Object, i)
			{
				cdebug << "\t";
				print_stack_element (*i);
			}
			cdebug << "End List (" << le->size () << ")\n";
		}
		else if (dynamic_cast<Optional*> (obj))
		{
			cdebug << "Optional (yes)";
		}
		else
			assert (0);

		cdebug << endl;
	}

	void print_stacks (Node* in)
	{
		// We cant iterate over a stack. Instead we pop all the items, storing
		// them in reverse order in the other stack. Then repeat in reverse.
		stack<Object*> copy;
		cdebug << "START_STACK: " << demangle (in, false) << ": \""; 
		debug (in);
		cdebug << "\" ************" << endl;
		while (not ids.empty ())
		{
			Object* obj = ids.top ();
			print_stack_element (obj);
			ids.pop ();
			copy.push (obj);
		}

		while (not copy.empty ())
		{
			Object* obj = copy.top ();
			copy.pop ();
			ids.push (obj);
		}
		cdebug << "END STACK******************************************" << endl;
	}



};

#include "AST_visitor.h"
class AST_CLPA_unparser : public CLPA_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Literal,
	AST::STRING,
	AST::BOOL,
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
	HIR::BOOL,
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
	MIR::BOOL,
	MIR::Identifier,
	MIR::Visitor
>
{
};

#endif // PHC_CLPA_UNPARSER
