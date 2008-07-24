#include "Backwards_flow_visitor.h"
#include <boost/foreach.hpp>
#include "MIR.h"

using namespace MIR;

void
Backwards_flow_visitor::run (CFG* cfg)
{
	BOOST_FOREACH (Basic_block* bb, *cfg->get_all_bbs ())
	{
		bb->init_df ();
	}

	// Add the exit block the worklist
	list<Basic_block*> worklist;
	worklist.push_back (cfg->get_exit_bb ());

	// iterate until the worklist is no more
	while (not worklist.empty ())
	{
		// Process the front block
		Basic_block* bb = worklist.front ();
		worklist.pop_front ();

		process_bb (bb, cfg);

		// If 
		if (bb->should_reiterate ())
		{
			BOOST_FOREACH (Basic_block* pred, *cfg->get_predecessors (bb))
			{
				worklist.push_front (pred);
			}
		}
	}
}

void
Backwards_flow_visitor::process_bb (Basic_block* bb, CFG* cfg)
{
	/* Calculate the OUT solution from the successors */
	transfer_out (bb, cfg->get_successors (bb));

	/* Calculate the local solution */
	if (Entry_block* eb = dynamic_cast<Entry_block*> (bb))
		process_entry_block (eb);

	else if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		process_empty_block (eb);

	else if (Exit_block* eb = dynamic_cast<Exit_block*> (bb))
		process_exit_block (eb);

	else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
		process_branch_block (brb);

	else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		switch (sb->statement->classid ())
		{
			case Assign_array::ID:
				return process_assign_array(sb, dyc<Assign_array>(sb->statement));
			case Assign_target::ID:
				return process_assign_target(sb, dyc<Assign_target>(sb->statement));
			case Assign_var::ID:
				return process_assign_var(sb, dyc<Assign_var>(sb->statement));
			case Assign_var_var::ID:
				return process_assign_var_var(sb, dyc<Assign_var_var>(sb->statement));
			case Eval_expr::ID:
				return process_eval_expr(sb, dyc<Eval_expr>(sb->statement));
			case Foreach_end::ID:
				return process_foreach_end(sb, dyc<Foreach_end>(sb->statement));
			case Foreach_next::ID:
				return process_foreach_next(sb, dyc<Foreach_next>(sb->statement));
			case Foreach_reset::ID:
				return process_foreach_reset(sb, dyc<Foreach_reset>(sb->statement));
			case Global::ID:
				return process_global(sb, dyc<Global>(sb->statement));
			case Pre_op::ID:
				return process_pre_op(sb, dyc<Pre_op>(sb->statement));
			case Push_array::ID:
				return process_push_array(sb, dyc<Push_array>(sb->statement));
			case Return::ID:
				return process_return(sb, dyc<Return>(sb->statement));
			case Static_declaration::ID:
				return process_static_declaration(sb, dyc<Static_declaration>(sb->statement));
			case Throw::ID:
				return process_throw(sb, dyc<Throw>(sb->statement));
			case Try::ID:
				return process_try(sb, dyc<Try>(sb->statement));
			default:
				assert (0);
		}
	}

	// Calculate the IN solution from the local results
	transfer_in (bb, cfg->get_predecessors (bb));
}
