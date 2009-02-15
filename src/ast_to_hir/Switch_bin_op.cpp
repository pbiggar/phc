/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Replace '>=' and '>' with '<=' and '<', after switching the operands.
 */

#include "Switch_bin_op.h"
#include "process_ir/fresh.h"

using namespace AST;

// Replace >= and > with <= and <, and swap the operators.
Expr*
Switch_bin_op::pre_bin_op (Bin_op* in)
{
	if (*in->op->value == ">" || *in->op->value == ">=")
	{
		Expr* left = in->left;
		in->left = in->right;
		in->right = left;

		if (*in->op->value == ">")
			in->op->value = s ("<");
		else
			in->op->value = s ("<=");
	}

	return in;
}
