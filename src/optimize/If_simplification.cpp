#include "If_simplification.h"
#include "process_ir/General.h"
#include "Def_use.h"

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

	Branch* branch = bb->branch;
	Wildcard<Unary_op>* op = new Wildcard<Unary_op>;

	bb->cfg->duw->dump ();

	SSA_edge* def = bb->cfg->duw->get_var_defs (branch->variable_name);

	if (def->which == SSA_edge::STATEMENT
		&& def->get_statement_block ()->statement->match (
			new Assign_var (new Wildcard<VARIABLE_NAME>, false, op))
		&& *op->value->op->value == "!")
	{
		branch->variable_name = op->value->variable_name->clone ();
		bb->switch_successors ();
	}
}
