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
#include "process_ir/General.h" 

using namespace AST;

class Canonical_unparser : public virtual AST_unparser 
{ 
	bool bracket;

	// clear all the users syntax so the PHP_unparser wont print it
	// out
	void pre_php_script (PHP_script* in)
	{
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

Plugin_pass* this_pass;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("sua"));
	this_pass = pass;
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	Canonical_unparser ().unparse (in);

	// HACK: 
	// The pass queue is used multiple times, when we parse some code within the
	// compiler. This leads to code being printed multiple times. As a result,
	// we turn this off after it runs once.
	
	this_pass->set_enabled (false);
}
