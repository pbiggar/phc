/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * For-loops are converted to an unusual form:
 *
 *			loop_init ();
 *			$first = true;
 *		L0:
 *			if ($first) goto L1; else goto L2;
 *		L1:
 *			$first = false;
 *			goto L3;
 *		L2:
 *			loop_incr ();
 *			goto L3;
 *		L3:
 *			$cond = loop_cond ();
 *			if (!$cond) goto L4; else goto L5;
 *		L4:
 *			loop_body ();
 *			goto L0;
 *		L5:
 *
 *	We wish to remove the messing around with the booleans by splitting the
 *	'if ($first) block in two, and letting the optimizers at it (which will
 *	remove them).
 *
 *	We convert this to:
 *
 *			loop_init ();
 *			$first = true;
 *			goto L0a:
 *		L0a:
 *			if ($first) goto L1; else goto L2;
 *		L0b:
 *			if ($first) goto L1; else goto L2;
 *		L1:
 *			$first = false;
 *			goto L3;
 *		L2:
 *			loop_incr ();
 *			goto L3;
 *		L3:
 *			$cond = loop_cond ();
 *			if (!$cond) goto L4; else goto L5;
 *		L4:
 *			loop_body ();
 *			goto L0b;
 *		L5:
 *
 *	Then the SCCP and DCE should kill a lot of statements, leaving:
 *
 *			loop_init ();
 *			goto L3;
 *		L2:
 *			loop_incr ();
 *		L3:
 *			$cond = loop_cond ();
 *			if (!$cond) goto L4; else goto L5;
 *		L4:
 *			loop_body ();
 *			goto L2;
 *
 *	While it is correct to do this anywhere, we dont want to do it unless it
 *	will result in a win. Identifying a win is tricky, so we'll just look for
 *	identifying features.
 *
 *	Its vastly simpler to do this out-of-SSA than in it.
 * TODO: simpler to annotate it in the Early_lower_control_flow maybe?
 * TODO: this should get both do_while loops and foreach
 */

#include "Remove_loop_booleans.h"
#include "process_ir/General.h"
#include "Def_use.h"

using namespace MIR;

void
Remove_loop_booleans::visit_branch_block (Branch_block* bb)
{
	if (is_applicable_branch (bb))
		cfg->split_block (bb);
}

bool
Remove_loop_booleans::is_applicable_branch (Branch_block* bb)
{
	// Identifying the circumstance is very specific:
	//	- The boolean is defined has two defs
	//	- The first def is to true, and is in the predecessor
	//	- the second def is to false, and is in a successor
	
	// must have a def
	if (!cfg->duw->has_def (bb->branch->variable_name))
		return false;

	// If this happens, SCCP will sort it out.
	if (bb->get_predecessors()->size() < 2)
		return false;

	SSA_op_list* defs = cfg->duw->get_defs (bb->branch->variable_name, SSA_ALL);
	if (defs->size() != 2)
		return false;

	if (!isa<SSA_stmt> (defs->front()) || !isa<SSA_stmt> (defs->back ()))
		return false;
	

	Basic_block* bb0 = defs->front ()->get_bb ();
	Basic_block* bb1 = defs->back ()->get_bb ();

	Basic_block* true_bb;
	Basic_block* false_bb;
	if (bb0->get_successors ()->has (bb)
		&& bb->get_successors ()->has (bb1))
	{
		true_bb = bb0;
		false_bb = bb1;
	}
	else if (bb1->get_successors ()->has (bb)
		&& bb->get_successors ()->has (bb0))
	{
		true_bb = bb1;
		false_bb = bb0;
	}
	else
		return false;

	// The predecessor is the true block
	if (!(dyc<Statement_block> (true_bb))->statement->match (
			new Assign_var (
				bb->branch->variable_name,
				false,
				new BOOL (true))))
		return false;

	// Successor is the false block
	if (!(dyc<Statement_block> (false_bb))->statement->match (
			new Assign_var (
				bb->branch->variable_name,
				false,
				new BOOL (false))))
		return false;

	return true;
}
