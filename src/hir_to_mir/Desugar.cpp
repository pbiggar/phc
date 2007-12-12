/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#include "Desugar.h"
#include "process_ir/fresh.h"

using namespace HIR;


// All eval_expr must be assignments; if they are not, we generate
// a dummy assignment on the LHS
void Desugar::pre_eval_expr(Eval_expr* in, List<Statement*>* out)
{
	// remove variables on their own
	if (in->expr->classid() == Variable::ID)
		return;

	// Don't generate an assignment for unset
	Expr* unset = new Method_invocation("unset", new Wildcard<Expr>);

	if(in->expr->classid() != Assignment::ID && 
			in->expr->classid() != Op_assignment::ID &&
			in->expr->classid() != List_assignment::ID &&
			!in->expr->match(unset))
	{
		Variable* var = fresh_var ("TSe");
		var->attrs->set_true ("phc.codegen.unused");

		in->expr = new Assignment(var, false, in->expr);
	}

	out->push_back(in);
}

// NOP statements are removed
void Desugar::pre_nop(Nop* in, List<Statement*>* out)
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
void Desugar::pre_return(Return* in, List<Statement*>* out)
{
	if(in->expr == NULL)
	{
		in->expr = new NIL(new String("NULL"));
		in->expr->attrs->set_true ("phc.codegen.unused");
	}

	out->push_back(in);
}

void Desugar::pre_declare (Declare* in, List<Statement*>* out)
{
	// Just remove declare statements, they dont make sense in a compiler.
}
