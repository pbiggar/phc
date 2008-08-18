/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#include "Desugar.h"
#include "process_ir/fresh.h"

using namespace AST;


// NOP statements are removed
void Desugar::pre_nop(Nop* in, Statement_list* out)
{
	// Leave "out" empty 
}

// Replace "-x" by "0 - x"
Expr* Desugar::pre_unary_op(Unary_op* in)
{
	if(*in->op->value == "-") return new Bin_op(
			new INT(0),
			in->op,
			in->expr);
	else
		return in;
}

// All return statements must get an argument (NULL if none specified)
void Desugar::pre_return(Return* in, Statement_list* out)
{
	if(in->expr == NULL)
	{
		in->expr = new NIL();
		in->expr->attrs->set_true ("phc.codegen.unused");
	}

	out->push_back(in);
}

void Desugar::pre_declare (Declare* in, Statement_list* out)
{
	// Just remove declare statements, they dont make sense in a compiler.
}
