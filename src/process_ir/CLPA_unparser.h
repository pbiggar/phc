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
#include <set>
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
 * +mir()->program (pHP_script { 1, 
 * [
 *	 statement_Eval_expr_id {
 *	  eval_expr_id { 2, 
 *    Expr_Assignment_id { 
 *     Assignment_id {3,
 * 	  variable_id {4,
 *       no,
 *       variable_name_VARIABLE_NAME_id { 
 *        vARIABLE_NAME_id {5, "x"}},
 *       [
 * 		 yes {
 *			  expr_Variable_id {
 *			   Variable_id {6,
 *			    no,
 *			    variable_name_VARIABLE_NAME_id {
 *			     vARIABLE_NAME_id {7, "i"}},
 *			    []}}}
 *			]}
 *		 false,
 *		 expr_STRING_id {
 *		  sTRING_id {8, "XXXXXX"}}}}}},
 *	 statement_Nop_id { nop_id {9} }]}
 *
 *	The first parameter is the ID, and the rest of the are the nodes
 *	parameters, with appropriate typing.
 *
 *	The type system is defined using maketea, in src/generated/?.clp. Each IR
 *	type has an associated constructor, and a type TYPE. There is only a need
 *	for 1 predicate, containing a PHP_Script. Lists use Calypsos built-in
 *	lists ([...]), rather something along the lines of t_statement_list.
 *	Nullable parameters use the Calypso 'maybe' type, whose constructors are
 *	'yes{}' and 'no'. Lists of Nullable parameters need to be wrapped as well.
 *	All parts are strongly typed. nop_id {9} indicates a Nop with ID 9.
 *	statement_Eval_expr_id means it expects a statement and we've given it an
 *	Eval_expr (which is a subtype of statement).
 *
 * The tree is created with a simple pre-order recursive descent of the tree.
 * We use bools for markers, and strings of the literals value for literals.
 * For NULL nullable parameters, we use maybe. For NULL lists, we use [].
 * For nullable parameters which are not NULL.
 */


template
<
	class PHP_script,
	class Node,
	class Literal,
	class STRING,
	class BOOL,
	class REAL,
	class Identifier,
	class Visitor,
	class Unparser
>
class CLPA_unparser : public Visitor 
{
	typedef CLPA_unparser<PHP_script, Node, Literal, STRING, BOOL, REAL, Identifier, Visitor, Unparser> Parent;

protected:
	String* uc_prefix;
	String* prefix;
	set<string> keywords;
	int id;
	int indent_depth;
	bool leading_comma;
	const char* base_type;
	stringstream out;
	bool next_node_optional;
	int list_depth;
	map<int,bool> optional_lists;

public:

	CLPA_unparser ()
	: id (0)
	, indent_depth (0)
	, leading_comma (false)
	, base_type (NULL)
	, next_node_optional (false)
	, list_depth (0)
	{
		init_keywords ();
	}

/* 
 * Top-level printing 
 */

	void init (PHP_script* in)
	{
//		String* filename = in->get_filename ();

		// get prefix in upper and lower case
		prefix = s (demangle (in, true));
		uc_prefix = s (prefix->substr (0, 3));
		prefix  = s (*uc_prefix);
		prefix->toLower ();
		init_keywords ();

		
		stringstream ss; ss << "src/generated/" << uc_prefix << ".clp";

		print_import (s(s("src/generated/")->append (*uc_prefix).append(".clp")));
		print_import (s("src/analyse/base.clp"));
		open_predicate (prefix, s("program"));
	}

	void finish (PHP_script* in)
	{
		close_predicate ();
		in->visit (new Attr_unparser (this));
		cout << out.str ();
	}



	void visit_php_script (PHP_script* in)
	{
		// pre_/post_node run outside pre_/post_php_script, so initializers
		// cant go into pre_/post_php_script
		init (in);
		Visitor::visit_php_script (in);
		finish (in);
	}

/* 
 * Unparsing
 */

	/* BOOLs are pushed for markers */
	void visit_marker(char const* name, bool value)
	{
		print_line (value ? s("true") : s("false"));
	}

	/* NULLs get pushed for null values */
/*	void visit_null(char const* name_space, char const* type_id)
	{
	}
	void visit_null_list(char const* name_space, char const* type_id)
	{
	}
*/
	/* We could do with a pre_/post_optional here, but its really hard to put
	 * that into maketea. */
	void visit_optional(bool is_null)
	{
		if (is_null)
			print_line (s("no"));
		else
			next_node_optional = true;
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
		base_type = type_id;
	}

	void pre_list(char const* name_space, char const* type_id, int size, bool nullable_elements)
	{
		// Optional applies to lists, but we cant annotate a list, since it
		// isnt a node. So we make a note of the depth of lists, and when we
		// come to this depth again, we close the yes{} braces.
		if (next_node_optional)
			open_scope (s("yes"));

		optional_lists [list_depth] = next_node_optional;
		next_node_optional = false;

		open_list ();
	}


	void post_list(char const* name_space, char const* type_id, int size, bool nullable_elements)
	{
		close_list ();

		if (optional_lists[list_depth] == true)
		{
			optional_lists[list_depth] = false;
			close_scope ();
		}
	}

	void pre_node(Node* in)
	{
		// Optional nodes need to be wrapped in yes{}
		if (next_node_optional)
		{
			open_scope (s ("yes"));
			in->attrs->set_true ("phc.clpa.optional");
			next_node_optional = false;
		}

		// Does the name need to be wrapped in a base_type
		if (*s(demangle (in, false)) != *s(base_type))
		{
			open_scope (disj_constructor_name (s(base_type), in));
			in->attrs->set_true ("phc.clpa.use_base_type");
		}

		// We need this for attribute unparsing
		in->attrs->set_integer ("phc.clpa.id", id);

		open_scope (constructor_name (in));

		// Node ID
		print_line (id++);

		// indicate its been used
		base_type = NULL;
	}

	void post_node(Node* in)
	{
		if (in->attrs->is_true ("phc.clpa.optional"))
			close_scope ();

		close_scope ();

		// Base types need to be closed
		if (in->attrs->is_true ("phc.clpa.use_base_type"))
			close_scope ();
	}

	void pre_identifier (Identifier* in)
	{
		// Strings need quotes
		print_quoted_line (in->get_value_as_string ());
	}

	void pre_literal (Literal* in)
	{
		switch (in->classid ())
		{
			case STRING::ID:
				// String literals need to be wrapped in quotes, and must be on a
				// single line
				print_quoted_line (escape (in->get_value_as_string ()));
				break;

			// Bools must be entirely lower case, or Calypso will think they
			// are variable names
			case BOOL::ID:
			{
				String* value = in->get_value_as_string ();
				value->toLower();
				print_line (value);
				break;
			}

			// Calypso doesnt like eks trings in scientific format
			case REAL::ID:
			{
				REAL* real = dynamic_cast<REAL*> (in);
				print_line (real->value); // TODO fixed precision
				break;
			}

			default:
				print_line (in->get_value_as_string ());
		}
	}

	/*
	 * Calypso name formatting 
	 */

	String* constructor_name (Node* in)
	{
		return check_for_keywords (
				lowerFirst (s (demangle (in, false))),
				s ("c"));
	}

	String* disj_constructor_name (String* base_type, Node* sub_type)
	{
		stringstream ss;
		ss 
			<< *lowerFirst (base_type)
			<< "_"
			<< demangle (sub_type, false);
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
				case '\n':
					ss << "\\n";
					break;
				case '\\':
					ss << "\\\\";
					break;
				case '"':
					ss << "\\\"";
					break;
				default:
					ss << *i;
					break;
			}
		}

		return new String(ss.str());	
	}

	void init_keywords ()
	{
		keywords.insert ("type");
		keywords.insert ("predicate");
		keywords.insert ("session");
		keywords.insert ("analyse");
		keywords.insert ("using");
		keywords.insert ("import");
	}

	// If its a keyword, then we need to prefix it
	String* check_for_keywords (String* name, String* prefix)
	{
		if (keywords.find (*name) == keywords.end())
			return name;

		// append prefix
		stringstream ss;
		ss << *prefix << "_" << *name;
		return s (ss.str ());
	}


	/*
	 * Utility functions
	 */

	// Lower the first characted of the string
	String* lowerFirst (String *in)
	{
		stringstream ss;
		const char* name = in->c_str ();
		ss << (char)(tolower (name[0]));
		ss << (&name[1]);
		return s (ss.str ());
	}


	/*
	 * Printing functions
	 */
	void print_import (String* filename)
	{
		out << "import \"" << *filename << "\".\n";
	}

	void open_predicate (String* prefix, String* predicate_name)
	{
		out 
			<< "+" << *prefix << "()->" << *predicate_name
			<< *indent(false) << "(";

		indent_depth++;
		leading_comma = false;
	}

	void close_predicate ()
	{
		indent_depth--;

		out
			<< "\n). \n\n";
	}

	void print_line (String* line)
	{ 
		out 
			<< *indent() << *line;

	}

	void print_line (int num)
	{ 
		out 
			<< *indent() << num; 
	}

	void print_quoted_line (String* line)
	{ 
		out << *indent() << "\"" << *line << "\"";
	}

	void open_scope (String* name)
	{
		// indent() resets leading_comma, so when its used twice in the same
		// expr, we dont have a guaranteed ordering, so they need to be split.
		out
			<< *indent() << *name;
		out
			<< *indent(false) << "{";
			
		leading_comma = false;
		indent_depth++;
	}
	void close_scope ()
	{
		indent_depth--;

		out << *indent(false) << "}";
	}

	void open_list ()
	{
		out << *indent() << "[";

		leading_comma = false;
		indent_depth++;
		list_depth++;
	}
	void close_list ()
	{
		indent_depth--;

		out << *indent(false) << "]";
		list_depth--;
	}
	String* indent(bool comma = true)
	{
		// TODO theres a better way to do this
		stringstream ss;
		ss 
			<< ((leading_comma && comma) ? ", " : "")
			<< "\n" 
			<< string (indent_depth*3, ' ');

		leading_comma = true;
		return s(ss.str());
	}




	// Unparse the attributes seperately
	class Attr_unparser : public Visitor
	{
		Parent* parent;

	public:
		Attr_unparser (Parent* parent) : parent (parent) { }

	
		void pre_node(Node* in)
		{
			// We dont need clpa.id anymore
			int id = in->attrs->get_integer ("phc.clpa.id")->value();
			in->attrs->erase_with_prefix ("phc.clpa");

			// Print out the attributes
			AttrMap::const_iterator i;
			for(i = in->attrs->begin(); i != in->attrs->end(); i++)
			{
				parent->out
					<< "+" << *parent->prefix << "()->attr (" << id << ", "
					<< "\"" << (*i).first << "\", ";

				Object* attr = (*i).second;

				if(String* str = dynamic_cast<String*>(attr))
					parent->out << "attr_str{\"" << *str << "\"}";
				else if(Integer* _int = dynamic_cast<Integer*>(attr))
					parent->out << "attr_int{" << _int->value () << "}";
				else if(Boolean* b = dynamic_cast<Boolean*>(attr))
					parent->out << "attr_bool{" << (b->value () ? "true" : "false") << "}";
				else
					parent->out << "attr_unavaiable";

				parent->out << ").\n";
			}

			// Print out the source representation
			stringstream ss;
			Unparser unparser (ss, true);
			unparser.unparse (in);
			parent->out
				<< "+" << *parent->prefix << "()->source_rep (" << id << ", "
				<< "\"" << *parent->escape (s (ss.str ())) << "\").\n";

		}

	};

};

#include "AST_visitor.h"
class AST_CLPA_unparser : public CLPA_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Literal,
	AST::STRING,
	AST::BOOL,
	AST::REAL,
	AST::Identifier,
	AST::Visitor,
	AST_unparser
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
	HIR::REAL,
	HIR::Identifier,
	HIR::Visitor,
	HIR_unparser
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
	MIR::REAL,
	MIR::Identifier,
	MIR::Visitor,
	MIR_unparser
>
{
};

#endif // PHC_CLPA_UNPARSER
