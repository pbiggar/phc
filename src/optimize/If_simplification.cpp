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

	Branch* branch = bb->branch;
	Wildcard<Unary_op>* uop = new Wildcard<Unary_op>;

	// SCCP would have fixed it otherwise
	// TODO: dont base this on the variable_name, use the alias_name.
//	assert (bb->cfg->duw->has_def (branch->variable_name));

	// TODO: bring this back
//	phc_TODO ();


//	SSA_op* op = bb->cfg->duw->get_def (branch->variable_name);
/*	SSA_stmt* def = dynamic_cast<SSA_stmt*> (op);

	if (def && def->get_statement()->match (
				new Assign_var (new Wildcard<VARIABLE_NAME>, false, uop))
			&& *uop->value->op->value == "!")
	{
		branch->variable_name = uop->value->variable_name->clone ();
		bb->switch_successors ();
	}*/
}
