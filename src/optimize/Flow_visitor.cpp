/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for data-flow analyses.
 */

#include "Flow_visitor.h"

Flow_visitor::Flow_visitor (Flow_visitor_direction direction)
: direction (direction)
{
}

void
Flow_visitor::run (CFG* cfg)
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		this->init_block (bb);
		visit_block (bb);
	}

	// Add the each block to the worklist
	BB_list* worklist = get_initial_worklist (cfg);

	// iterate until the worklist is no more
	while (not worklist->empty ())
	{
		// Process the front block
		Basic_block* bb = worklist->front ();
		worklist->pop_front ();

		visit_transfer_functions (bb, cfg);

		if (this->solution_has_changed (bb))
		{
			foreach (Basic_block* next, *get_next_cfg_nodes (bb, cfg))
				worklist->push_back (next);
		}
	}

	// After the pure analysis section, apply the results (once).
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
		transform_block (bb);

	// Call the pass' own post-processing.
	post_pass (cfg);
}

BB_list*
Flow_visitor::get_next_cfg_nodes (Basic_block* bb, CFG* cfg)
{
	if (direction == FORWARD_FLOW)
		return bb->get_successors ();
	else
		return bb->get_predecessors ();
}

void
Flow_visitor::visit_transfer_functions (Basic_block* bb, CFG* cfg)
{
	if (direction == FORWARD_FLOW)
	{
		this->transfer_in (bb, bb->get_predecessors ());
		this->transfer_out (bb, bb->get_successors ());
	}
	else
	{
		this->transfer_out (bb, bb->get_successors ());
		this->transfer_in (bb, bb->get_predecessors ());
	}
}

BB_list*
Flow_visitor::get_initial_worklist (CFG* cfg)
{
	if (direction == FORWARD_FLOW)
		return cfg->get_all_bbs_top_down ();
	else
		return cfg->get_all_bbs_bottom_up ();
}

void
Flow_visitor::post_pass (CFG* cfg)
{
}
