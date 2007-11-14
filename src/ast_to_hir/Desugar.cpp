/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#include "Desugar.h"

using namespace AST;


// All eval_expr must be assignments; if they are not, we generate
// a dummy assignment on the LHS
void Desugar::pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	// remove variables on their own
	if (in->expr->classid() == AST_variable::ID)
		return;

	// Don't generate an assignment for unset
	AST_expr* unset = new AST_method_invocation("unset", new Wildcard<AST_expr>);

	if(in->expr->classid() != AST_assignment::ID && 
			in->expr->classid() != AST_op_assignment::ID &&
			in->expr->classid() != AST_list_assignment::ID &&
			!in->expr->match(unset))
	{
		AST_variable* var = fresh_var ("TSe");
		var->attrs->set_true ("phc.codegen.unused");

		in->expr = new AST_assignment(var, false, in->expr);
	}

	out->push_back(in);
}

// NOP statements are removed
void Desugar::pre_nop(AST_nop* in, List<AST_statement*>* out)
{
	// Leave "out" empty 
}

// Replace "-x" by "0 - x"
AST_expr* Desugar:: pre_unary_op(AST_unary_op* in)
{
	if(*in->op->value == "-") return new AST_bin_op(
			new Token_int(0),
			in->op,
			in->expr);
	else
		return in;
}

// All return statements must get an argument (NULL if none specified)
void Desugar::pre_return(AST_return* in, List<AST_statement*>* out)
{
	if(in->expr == NULL)
	{
		in->expr = new Token_null(new String("NULL"));
		in->expr->attrs->set_true ("phc.codegen.unused");
	}

	out->push_back(in);
}
