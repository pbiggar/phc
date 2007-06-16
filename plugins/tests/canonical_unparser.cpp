/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax, being as explicit as possible. Right
 * now, this only addes brackets around binary_ops.
 */

#include "process_ast/PHP_unparser.h" 
#include "process_ast/Pass_manager.h" 
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
	// clear all the users syntax so the PHP_unparser wont print it
	// out
	void pre_php_script (AST_php_script* in)
	{
		Clear_user_syntax cus;
		in->visit(&cus);
	}

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
