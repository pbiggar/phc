#ifndef PHC_FLOW_VISITOR
#define PHC_FLOW_VISITOR

#include "CFG.h"
#include "Basic_block.h"
#include "process_ir/General.h"

/* Direction chooses whether the worklist operates from backwards from Exit,
 * or forwards from Entry. */
enum Flow_visitor_direction { FORWARD_FLOW, BACKWARD_FLOW };

/* A FULL analysis contains compile-time checks that all constructs are
 * supported. Every visit_X method is pure-virtual, and the compiler will
 * complain if they are not defined. Use FUL if the analysis must handle the
 * whole language.
 *
 * A SPARSE analysis just touches a number of constructs, say empty blocks, or
 * assignments. For small analyses, where the entire language is not being
 * modeled, a sparse analysis allows you to just override the usefl methods,
 * and avoid the rest of the language. */
class Sparse_flow_visitor;
class Full_flow_visitor;

template <class Sparseness_base, Flow_visitor_direction Direction>
class Flow_visitor : public Sparseness_base
{
public:

	virtual void visit (CFG* cfg)
	{
		foreach (Basic_block* bb, *cfg->get_all_bbs ())
		{
			bb->init_df ();
			visit_bb_local (cfg, bb);
		}

		// Add the exit block the worklist
		list<Basic_block*> worklist;
		worklist.push_back (get_initial_bb (cfg));

		// iterate until the worklist is no more
		while (not worklist.empty ())
		{
			// Process the front block
			Basic_block* bb = worklist.front ();
			worklist.pop_front ();

			cdebug << "process BB " << bb->vertex << endl;
			visit_transfer_functions (bb, cfg);

			foreach (Basic_block* pred, *get_next_cfg_nodes (bb, cfg))
				worklist.push_back (pred);

			if (bb->should_reiterate ())
				worklist.push_back (bb);
		}

		// After the pure analysis section, apply the results (once).
		foreach (Basic_block* bb, *cfg->get_all_bbs ())
		{
			bb->init_df ();
			list<Basic_block*>* bbs = new list<Basic_block*>;
			transform_bb (bb, bbs);
//			cfg->replace (bb, bbs);
		}
	}

private:
	/* Calculate the local solution */
	void visit_bb_local (CFG* cfg, Basic_block* bb)
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
				case MIR::Assign_target::ID:
					this->visit_assign_target(sb, dyc<MIR::Assign_target>(sb->statement));
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
				default:
					assert (0);
			}
		}
	}

	// Assume for now we only need a sparse version.
	void transform_bb (Basic_block* bb, list<Basic_block*>* out)
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
				case MIR::Assign_target::ID:
					this->transform_assign_target(sb, dyc<MIR::Assign_target>(sb->statement), out);
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
				default:
					assert (0);
			}
		}
	}

	virtual void transform_entry_block (Entry_block* in, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_empty_block (Empty_block* in, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_exit_block (Exit_block* in, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_branch_block (Branch_block* in, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	// TODO: any need for a visit_statement_block?
	
	// Local solution - statements
	virtual void transform_assign_array (Statement_block* in, MIR::Assign_array*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_assign_target (Statement_block* in, MIR::Assign_target*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_assign_var (Statement_block* in, MIR::Assign_var*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_assign_var_var (Statement_block* in, MIR::Assign_var_var*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_eval_expr (Statement_block* in, MIR::Eval_expr*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_foreach_end (Statement_block* in, MIR::Foreach_end*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_foreach_next (Statement_block* in, MIR::Foreach_next*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_foreach_reset (Statement_block* in, MIR::Foreach_reset*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_global (Statement_block* in, MIR::Global*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_pre_op (Statement_block* in, MIR::Pre_op*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_push_array (Statement_block* in, MIR::Push_array*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_return (Statement_block* in, MIR::Return*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_static_declaration (Statement_block* in, MIR::Static_declaration*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_throw (Statement_block* in, MIR::Throw*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}
	virtual void transform_try (Statement_block* in, MIR::Try*, list<Basic_block*>* out)
	{
		out->push_back (in);
	}


	list<Basic_block*>* get_next_cfg_nodes (Basic_block* bb, CFG* cfg)
	{
		if (Direction == FORWARD_FLOW)
			return cfg->get_successors (bb);
		else
			return cfg->get_predecessors (bb);
	}

	void visit_transfer_functions (Basic_block* bb, CFG* cfg)
	{
		if (Direction == FORWARD_FLOW)
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

	Basic_block* get_initial_bb (CFG* cfg)
	{
		if (Direction == FORWARD_FLOW)
			return cfg->get_entry_bb ();
		else
			return cfg->get_exit_bb ();
	}

};

/* Each method is pure virtual, so we get compile-time warnings, requiring each
 * method to be overridden. */
class Full_flow_visitor
{
public:
	/* Public interface for analyses */

	/* Transfer functions */
	virtual void transfer_in (Basic_block* bb, list<Basic_block*>* preds) = 0;
	virtual void transfer_out (Basic_block* bb, list<Basic_block*>* succs) = 0;

	// Local solution - blocks
	virtual void visit_entry_block (Entry_block*) = 0;
	virtual void visit_empty_block (Empty_block*) = 0;
	virtual void visit_exit_block (Exit_block*) = 0;
	virtual void visit_branch_block (Branch_block*) = 0;
	// TODO: any need for a visit_statement_block?
	
	// Local solution - statements
	virtual void visit_assign_array (Statement_block*, MIR::Assign_array*) = 0;
	virtual void visit_assign_target (Statement_block*, MIR::Assign_target*) = 0;
	virtual void visit_assign_var (Statement_block*, MIR::Assign_var*) = 0;
	virtual void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*) = 0;
	virtual void visit_eval_expr (Statement_block*, MIR::Eval_expr*) = 0;
	virtual void visit_foreach_end (Statement_block*, MIR::Foreach_end*) = 0;
	virtual void visit_foreach_next (Statement_block*, MIR::Foreach_next*) = 0;
	virtual void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*) = 0;
	virtual void visit_global (Statement_block*, MIR::Global*) = 0;
	virtual void visit_pre_op (Statement_block*, MIR::Pre_op*) = 0;
	virtual void visit_push_array (Statement_block*, MIR::Push_array*) = 0;
	virtual void visit_return (Statement_block*, MIR::Return*) = 0;
	virtual void visit_static_declaration (Statement_block*, MIR::Static_declaration*) = 0;
	virtual void visit_throw (Statement_block*, MIR::Throw*) = 0;
	virtual void visit_try (Statement_block*, MIR::Try*) = 0;
};

/* Each method is defined and empty, so we can override a small number of
 * methods, and are not required to override them all. */
class Sparse_flow_visitor
{
public:
	/* Public interface for analyses */

	/* Transfer functions */
	virtual void transfer_in (Basic_block* bb, list<Basic_block*>* preds) {};
	virtual void transfer_out (Basic_block* bb, list<Basic_block*>* succs) {};

	// Local solution - blocks
	virtual void visit_entry_block (Entry_block*) {};
	virtual void visit_empty_block (Empty_block*) {};
	virtual void visit_exit_block (Exit_block*) {};
	virtual void visit_branch_block (Branch_block*) {};
	// TODO: any need for a visit_statement_block?
	
	// Local solution - statements
	virtual void visit_assign_array (Statement_block*, MIR::Assign_array*) {};
	virtual void visit_assign_target (Statement_block*, MIR::Assign_target*) {};
	virtual void visit_assign_var (Statement_block*, MIR::Assign_var*) {};
	virtual void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*) {};
	virtual void visit_eval_expr (Statement_block*, MIR::Eval_expr*) {};
	virtual void visit_foreach_end (Statement_block*, MIR::Foreach_end*) {};
	virtual void visit_foreach_next (Statement_block*, MIR::Foreach_next*) {};
	virtual void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*) {};
	virtual void visit_global (Statement_block*, MIR::Global*) {};
	virtual void visit_pre_op (Statement_block*, MIR::Pre_op*) {};
	virtual void visit_push_array (Statement_block*, MIR::Push_array*) {};
	virtual void visit_return (Statement_block*, MIR::Return*) {};
	virtual void visit_static_declaration (Statement_block*, MIR::Static_declaration*) {};
	virtual void visit_throw (Statement_block*, MIR::Throw*) {};
	virtual void visit_try (Statement_block*, MIR::Try*) {};
};


#endif // PHC_FLOW_VISITOR
