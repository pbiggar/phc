/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax, being as explicit as possible. This adds
 * bracket around most expressions, removes user-specified brackets and
 * curlies.
 */

#include "process_ast/PHP_unparser.h" 
#include "pass_manager/Pass_manager.h" 
class Clear_user_syntax : public virtual AST_visitor
{
	void pre_node (AST_node* in)
	{
		in->attrs->erase("phc.unparser.needs_user_curlies");
		in->attrs->erase("phc.unparser.needs_user_brackets");
	}
};

class Canonical_unparser : public virtual PHP_unparser
{
	bool bracket;

	// clear all the users syntax so the PHP_unparser wont print it
	// out
	void pre_php_script (AST_php_script* in)
	{
		Clear_user_syntax cus;
		in->visit(&cus);

		bracket = true;
	}


// bracket all allowed expressions
#define WRAP(TYPE)												\
	void pre_##TYPE (AST_##TYPE* in) { if (bracket) echo ("("); }	\
	void post_##TYPE (AST_##TYPE* in) { if (bracket) echo (")"); }

// within some constructs, bracketing leads to a parse error
#define EXCEPT_IN(TYPE)													\
	void pre_##TYPE (AST_##TYPE* in) { bracket = false; }	\
	void post_##TYPE (AST_##TYPE* in) { bracket = true; }
						
	WRAP (unary_op)
	// bin_op handled separately
	WRAP (conditional_expr)
	WRAP (constant)
	WRAP (pre_op)
	WRAP (post_op)
	WRAP (array)
	WRAP (literal)

	EXCEPT_IN (attribute)
	EXCEPT_IN (static_declaration)
	EXCEPT_IN (formal_parameter)
	EXCEPT_IN (directive)

#undef WRAP
#undef EXCEPT_IN

	void children_bin_op(AST_bin_op* in)
	{
		if (*in->op->value != ",") echo("(");
		PHP_unparser::children_bin_op (in);
		if (*in->op->value != ",") echo(")");
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->clone()->visit (new Canonical_unparser ());
}
