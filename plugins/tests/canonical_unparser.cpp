/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax, being as explicit as possible. This adds
 * bracket around most expressions, removes user-specified brackets and
 * curlies.
 */

#include "process_ast/AST_unparser.h" 
#include "pass_manager/Plugin_pass.h" 

using namespace AST;

class Clear_user_syntax : public virtual Visitor
{
	void pre_node (Node* in)
	{
		// Remove all the unparser attributes. is_singly_quoted must either be
		// escaped or removed, however.
		AttrMap::const_iterator i;
		for(i = in->attrs->begin(); i != in->attrs->end(); i++)
		{
			if((*i).first.find ("phc.unparser") == 0
				&& (*i).first != "phc.unparser.is_singly_quoted")
			{
				in->attrs->erase ((*i).first);
			}
		}
	} 

#define REMOVE_SOURCE_REP(TYPE_V, TYPE_C)													\
	void pre##TYPE_V (TYPE_C* in) { in->source_rep = NULL; }

	/* Not all tokens have source_reps. Those that do should still be unparsable
	 * if they're set to NULL. */
	REMOVE_SOURCE_REP (bool, BOOL); 
	REMOVE_SOURCE_REP (cast, CAST);
//	REMOVE_SOURCE_REP (class_name); REMOVE_SOURCE_REP (constant_name);
//	REMOVE_SOURCE_REP (directive_name);
	REMOVE_SOURCE_REP (int, INT);
//	REMOVE_SOURCE_REP (interface_name); 
//	REMOVE_SOURCE_REP (label_name);
//	REMOVE_SOURCE_REP (method_name);
	REMOVE_SOURCE_REP (nil, NIL);
//	REMOVE_SOURCE_REP (op);
	REMOVE_SOURCE_REP (real, REAL);
	REMOVE_SOURCE_REP (string, STRING);
//	REMOVE_SOURCE_REP (variable_name);

#undef REMOVE_SOURCE_REP


};

/* There is no need to override the unparser methods for tokens. They should be
 * able to unparse without a source_rep. */
class Canonical_unparser : public virtual AST_unparser { bool bracket;

	// clear all the users syntax so the PHP_unparser wont print it
	// out
	void pre_php_script (PHP_script* in)
	{
		Clear_user_syntax cus;
		in->visit(&cus);

		bracket = true;
	}


// bracket all allowed expressions
#define WRAP(TYPE_V, TYPE_C)												\
	void pre_##TYPE_V (TYPE_C* in) { if (bracket) echo ("("); }	\
	void post_##TYPE_V (TYPE_C* in) { if (bracket) echo (")"); }

// within some constructs, bracketing leads to a parse error
#define EXCEPT_IN(TYPE_V, TYPE_C)													\
	void pre_##TYPE_V (TYPE_C* in) { bracket = false; }	\
	void post_##TYPE_V (TYPE_C* in) { bracket = true; }
						
	WRAP (unary_op, Unary_op)
	// bin_op handled separately
	WRAP (conditional_expr, Conditional_expr)
	WRAP (constant, Constant)
	WRAP (pre_op, Pre_op)
	WRAP (post_op, Post_op)
	WRAP (array, Array)
	WRAP (literal, Literal)

	EXCEPT_IN (attribute, Attribute)
	EXCEPT_IN (static_declaration, Static_declaration)
	EXCEPT_IN (formal_parameter, Formal_parameter)
	EXCEPT_IN (directive, Directive)

#undef WRAP
#undef EXCEPT_IN

	void children_bin_op(Bin_op* in)
	{
		if (*in->op->value != ",") echo("(");
		AST_unparser::children_bin_op (in);
		if (*in->op->value != ",") echo(")");
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (PHP_script* in, Pass_manager* pm)
{
	in->clone()->visit (new Canonical_unparser ());
}
