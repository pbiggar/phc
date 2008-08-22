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
Flow_visitor::visit (CFG* cfg)
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		this->init_block (bb);
		visit_bb_local (cfg, bb);
	}

	// Add the each block to the worklist
	list<Basic_block*>* worklist = get_initial_worklist (cfg);

	// iterate until the worklist is no more
	while (not worklist->empty ())
	{
		// Process the front block
		Basic_block* bb = worklist->front ();
		worklist->pop_front ();

		cdebug << "process BB " << bb->vertex << endl;
		visit_transfer_functions (bb, cfg);

		if (this->solution_has_changed (bb))
			foreach (Basic_block* next, *get_next_cfg_nodes (bb, cfg))
				worklist->push_back (next);
	}

	// After the pure analysis section, apply the results (once).
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		list<Basic_block*>* replacements = new list<Basic_block*>;
		transform_bb (bb, replacements);
		cfg->replace_bb (bb, replacements);
	}
}

void
Flow_visitor::visit_bb_local (CFG* cfg, Basic_block* bb)
{
	/* Using the THIS pointer is a little unusual, but its required to make
	 * these calls be resolved at template instantiation time, rather than
	 * declaration time. See Section 10.8.2 in the GCC manual. We need the
	 * calls to be resolved at template instantiation time as their
	 * definition is done through partial template instantiation. */
	if (Entry_block* eb = dynamic_cast<Entry_block*> (bb))
		this->visit_entry_block (eb);

	else if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		this->visit_empty_block (eb);

	else if (Exit_block* eb = dynamic_cast<Exit_block*> (bb))
		this->visit_exit_block (eb);

	else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
		this->visit_branch_block (brb);

	else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		switch (sb->statement->classid ())
		{
			case MIR::Assign_array::ID:
				this->visit_assign_array(sb, dyc<MIR::Assign_array>(sb->statement));
				break;
			case MIR::Assign_field::ID:
				this->visit_assign_field(sb, dyc<MIR::Assign_field>(sb->statement));
				break;
			case MIR::Assign_var::ID:
				this->visit_assign_var(sb, dyc<MIR::Assign_var>(sb->statement));
				break;
			case MIR::Assign_var_var::ID:
				this->visit_assign_var_var(sb, dyc<MIR::Assign_var_var>(sb->statement));
				break;
			case MIR::Eval_expr::ID:
				this->visit_eval_expr(sb, dyc<MIR::Eval_expr>(sb->statement));
				break;
			case MIR::Foreach_end::ID:
				this->visit_foreach_end(sb, dyc<MIR::Foreach_end>(sb->statement));
				break;
			case MIR::Foreach_next::ID:
				this->visit_foreach_next(sb, dyc<MIR::Foreach_next>(sb->statement));
				break;
			case MIR::Foreach_reset::ID:
				this->visit_foreach_reset(sb, dyc<MIR::Foreach_reset>(sb->statement));
				break;
			case MIR::Global::ID:
				this->visit_global(sb, dyc<MIR::Global>(sb->statement));
				break;
			case MIR::Param_is_ref::ID:
				this->visit_param_is_ref (sb, dyc<MIR::Param_is_ref>(sb->statement));
				break;
			case MIR::Pre_op::ID:
				this->visit_pre_op(sb, dyc<MIR::Pre_op>(sb->statement));
				break;
			case MIR::Push_array::ID:
				this->visit_push_array(sb, dyc<MIR::Push_array>(sb->statement));
				break;
			case MIR::Return::ID:
				this->visit_return(sb, dyc<MIR::Return>(sb->statement));
				break;
			case MIR::Static_declaration::ID:
				this->visit_static_declaration(sb, dyc<MIR::Static_declaration>(sb->statement));
				break;
			case MIR::Throw::ID:
				this->visit_throw(sb, dyc<MIR::Throw>(sb->statement));
				break;
			case MIR::Try::ID:
				this->visit_try(sb, dyc<MIR::Try>(sb->statement));
				break;
			case MIR::Unset::ID:
				this->visit_unset (sb, dyc<MIR::Unset>(sb->statement));
				break;
			default:
				xdebug (sb->statement);
				assert (0);
		}
	}

	else
		assert (0);
}

	// Assume for now we only need a sparse version.
void
Flow_visitor::transform_bb (Basic_block* bb, list<Basic_block*>* out)
{
	/* Using the THIS pointer is a little unusual, but its required to make
	 * these calls be resolved at template instantiation time, rather than
	 * declaration time. See Section 10.8.2 in the GCC manual. We need the
	 * calls to be resolved at template instantiation time as their
	 * definition is done through partial template instantiation. */
	if (Entry_block* eb = dynamic_cast<Entry_block*> (bb))
		this->transform_entry_block (eb, out);

	else if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		this->transform_empty_block (eb, out);

	else if (Exit_block* eb = dynamic_cast<Exit_block*> (bb))
		this->transform_exit_block (eb, out);

	else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
		this->transform_branch_block (brb, out);

	else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		switch (sb->statement->classid ())
		{
			case MIR::Assign_array::ID:
				this->transform_assign_array(sb, dyc<MIR::Assign_array>(sb->statement), out);
				break;
			case MIR::Assign_field::ID:
				this->transform_assign_field(sb, dyc<MIR::Assign_field>(sb->statement), out);
				break;
			case MIR::Assign_var::ID:
				this->transform_assign_var(sb, dyc<MIR::Assign_var>(sb->statement), out);
				break;
			case MIR::Assign_var_var::ID:
				this->transform_assign_var_var(sb, dyc<MIR::Assign_var_var>(sb->statement), out);
				break;
			case MIR::Eval_expr::ID:
				this->transform_eval_expr(sb, dyc<MIR::Eval_expr>(sb->statement), out);
				break;
			case MIR::Foreach_end::ID:
				this->transform_foreach_end(sb, dyc<MIR::Foreach_end>(sb->statement), out);
				break;
			case MIR::Foreach_next::ID:
				this->transform_foreach_next(sb, dyc<MIR::Foreach_next>(sb->statement), out);
				break;
			case MIR::Foreach_reset::ID:
				this->transform_foreach_reset(sb, dyc<MIR::Foreach_reset>(sb->statement), out);
				break;
			case MIR::Global::ID:
				this->transform_global(sb, dyc<MIR::Global>(sb->statement), out);
				break;
			case MIR::Param_is_ref::ID:
				this->transform_param_is_ref (sb, dyc<MIR::Param_is_ref> (sb->statement), out);
				break;
			case MIR::Pre_op::ID:
				this->transform_pre_op(sb, dyc<MIR::Pre_op>(sb->statement), out);
				break;
			case MIR::Push_array::ID:
				this->transform_push_array(sb, dyc<MIR::Push_array>(sb->statement), out);
				break;
			case MIR::Return::ID:
				this->transform_return(sb, dyc<MIR::Return>(sb->statement), out);
				break;
			case MIR::Static_declaration::ID:
				this->transform_static_declaration(sb, dyc<MIR::Static_declaration>(sb->statement), out);
				break;
			case MIR::Throw::ID:
				this->transform_throw(sb, dyc<MIR::Throw>(sb->statement), out);
				break;
			case MIR::Try::ID:
				this->transform_try(sb, dyc<MIR::Try>(sb->statement), out);
				break;
			case MIR::Unset::ID:
				this->transform_unset(sb, dyc<MIR::Unset>(sb->statement), out);
				break;
			default:
				assert (0);
		}
	}

	else 
		assert (0);
}

void
Flow_visitor::transform_entry_block (Entry_block* in, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_empty_block (Empty_block* in, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_exit_block (Exit_block* in, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_branch_block (Branch_block* in, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_assign_array (Statement_block* in, MIR::Assign_array*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_assign_field (Statement_block* in, MIR::Assign_field*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_assign_var (Statement_block* in, MIR::Assign_var*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_assign_var_var (Statement_block* in, MIR::Assign_var_var*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_eval_expr (Statement_block* in, MIR::Eval_expr*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_foreach_end (Statement_block* in, MIR::Foreach_end*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_foreach_next (Statement_block* in, MIR::Foreach_next*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_foreach_reset (Statement_block* in, MIR::Foreach_reset*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_global (Statement_block* in, MIR::Global*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_param_is_ref (Statement_block* in, MIR::Param_is_ref*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_pre_op (Statement_block* in, MIR::Pre_op*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_push_array (Statement_block* in, MIR::Push_array*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_return (Statement_block* in, MIR::Return*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_static_declaration (Statement_block* in, MIR::Static_declaration*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_throw (Statement_block* in, MIR::Throw*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_try (Statement_block* in, MIR::Try*, list<Basic_block*>* out)
{
	out->push_back (in);
}

void
Flow_visitor::transform_unset (Statement_block* in, MIR::Unset*, list<Basic_block*>* out)
{
	out->push_back (in);
}

list<Basic_block*>*
Flow_visitor::get_next_cfg_nodes (Basic_block* bb, CFG* cfg)
{
	if (direction == FORWARD_FLOW)
		return cfg->get_successors (bb);
	else
		return cfg->get_predecessors (bb);
}

void
Flow_visitor::visit_transfer_functions (Basic_block* bb, CFG* cfg)
{
	if (direction == FORWARD_FLOW)
	{
		this->transfer_in (bb, cfg->get_predecessors (bb));
		this->transfer_out (bb, cfg->get_successors (bb));
	}
	else
	{
		this->transfer_out (bb, cfg->get_successors (bb));
		this->transfer_in (bb, cfg->get_predecessors (bb));
	}
}

list<Basic_block*>*
Flow_visitor::get_initial_worklist (CFG* cfg)
{
	list<Basic_block*>* worklist = new list<Basic_block*>;
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		// TODO its correct both ways, but its faster if we get a
		// topological ordering for forward, and a reverse tpologocial
		// ordering for backwards
		worklist->push_back (bb);
	}
	return worklist;
}


