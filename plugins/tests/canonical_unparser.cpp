/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax, being as explicit as possible. Right
 * now, this only addes brackets around binary_ops.
 */

#include "process_ast/PHP_unparser.h" 

class Canonical_unparser : public virtual PHP_unparser
{
	void children_bin_op(AST_bin_op* in)
	{
		if (*in->op->value != ",") echo("(");
		PHP_unparser::children_bin_op (in);
		if (*in->op->value != ",") echo(")");
	}
};

extern "C" void process_ast(AST_php_script* script)
{
	Canonical_unparser cup;
	script->visit(&cup);
}
