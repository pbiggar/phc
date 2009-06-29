#include "If_simplification.h"
#include "process_ir/General.h"
#include "Def_use_web.h"

using namespace MIR;

void
If_simplification::visit_branch_block (Branch_block* bb)
{
	/* Turn
	 *
	 *		if (!$x) goto L1; else goto L2;
	 *
	 *	into
	 *
	 *		if ($x) goto L2; else goto L1;
	 */

	Def_use_web* duw = bb->cfg->duw;

	SSA_use* use = duw->get_block_uses (bb)->front ();
	SSA_def_list* defs = use->get_defs ();

	if (defs->size () == 1)
	{
		Wildcard<Unary_op>* uop = new Wildcard<Unary_op>;

		Statement_block* sb = dyc<Statement_block> (defs->front()->bb);
		if (sb->statement->match (
				new Assign_var (
				new Wildcard<VARIABLE_NAME>, false, uop))
			&& *uop->value->op->value == "!")
		{
			bb->branch->variable_name = uop->value->variable_name->clone ();
			bb->switch_successors ();
		}
	}
}
