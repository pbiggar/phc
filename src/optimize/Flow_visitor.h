#ifndef PHC_FLOW_VISITOR
#define PHC_FLOW_VISITOR

#include "CFG.h"
#include "Basic_block.h"
#include "process_ir/General.h"

/* Direction chooses whether the worklist operates from backwards from Exit,
 * or forwards from Entry. */
enum Flow_visitor_direction { FORWARD_FLOW, BACKWARD_FLOW };

/* A FULL analysis contains compile-time checks that all constructs are
 * supported. Every process_X method is pure-virtual, and the compiler will
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
			process_bb_local (bb);
		}

		// Add the exit block the worklist
		list<Basic_block*> worklist;
		worklist.push_back (cfg->get_exit_bb ());
		assert (0);

		// iterate until the worklist is no more
		while (not worklist.empty ())
		{
			// Process the front block
			Basic_block* bb = worklist.front ();
			worklist.pop_front ();

			cdebug << "process BB " << bb->vertex << endl;
			process_transfer_functions (bb, cfg);

			foreach (Basic_block* pred, *get_next_cfg_nodes (bb, cfg))
				worklist.push_back (pred);

			if (bb->should_reiterate ())
				worklist.push_back (bb);
		}
	}

private:
	/* Calculate the local solution */
	void process_bb_local (Basic_block* bb)
	{
		/* Using the THIS pointer is a little unusual, but its required to make
		 * these calls be resolved at template instantiation time, rather than
		 * declaration time. See Section 10.8.2 in the GCC manual. We need the
		 * calls to be resoled at template instantiation time as their definition
		 * is done through partial template instantiation. */
		if (Entry_block* eb = dynamic_cast<Entry_block*> (bb))
			this->process_entry_block (eb);

		else if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
			this->process_empty_block (eb);

		else if (Exit_block* eb = dynamic_cast<Exit_block*> (bb))
			this->process_exit_block (eb);

		else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
			this->process_branch_block (brb);

		else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
		{
			switch (sb->statement->classid ())
			{
				case MIR::Assign_array::ID:
					this->process_assign_array(sb, dyc<MIR::Assign_array>(sb->statement));
					break;
				case MIR::Assign_target::ID:
					this->process_assign_target(sb, dyc<MIR::Assign_target>(sb->statement));
					break;
				case MIR::Assign_var::ID:
					this->process_assign_var(sb, dyc<MIR::Assign_var>(sb->statement));
					break;
				case MIR::Assign_var_var::ID:
					this->process_assign_var_var(sb, dyc<MIR::Assign_var_var>(sb->statement));
					break;
				case MIR::Eval_expr::ID:
					this->process_eval_expr(sb, dyc<MIR::Eval_expr>(sb->statement));
					break;
				case MIR::Foreach_end::ID:
					this->process_foreach_end(sb, dyc<MIR::Foreach_end>(sb->statement));
					break;
				case MIR::Foreach_next::ID:
					this->process_foreach_next(sb, dyc<MIR::Foreach_next>(sb->statement));
					break;
				case MIR::Foreach_reset::ID:
					this->process_foreach_reset(sb, dyc<MIR::Foreach_reset>(sb->statement));
					break;
				case MIR::Global::ID:
					this->process_global(sb, dyc<MIR::Global>(sb->statement));
					break;
				case MIR::Pre_op::ID:
					this->process_pre_op(sb, dyc<MIR::Pre_op>(sb->statement));
					break;
				case MIR::Push_array::ID:
					this->process_push_array(sb, dyc<MIR::Push_array>(sb->statement));
					break;
				case MIR::Return::ID:
					this->process_return(sb, dyc<MIR::Return>(sb->statement));
					break;
				case MIR::Static_declaration::ID:
					this->process_static_declaration(sb, dyc<MIR::Static_declaration>(sb->statement));
					break;
				case MIR::Throw::ID:
					this->process_throw(sb, dyc<MIR::Throw>(sb->statement));
					break;
				case MIR::Try::ID:
					this->process_try(sb, dyc<MIR::Try>(sb->statement));
					break;
				default:
					assert (0);
			}
		}
	}

	list<Basic_block*>* get_next_cfg_nodes (Basic_block* bb, CFG* cfg)
	{
		if (Direction == FORWARD_FLOW)
			return cfg->get_successors (bb);
		else
			return cfg->get_predecessors (bb);
	}

	void process_transfer_functions (Basic_block* bb, CFG* cfg)
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
	virtual void process_entry_block (Entry_block*) = 0;
	virtual void process_empty_block (Empty_block*) = 0;
	virtual void process_exit_block (Exit_block*) = 0;
	virtual void process_branch_block (Branch_block*) = 0;
	// TODO: any need for a process_statement_block?
	
	// Local solution - statements
	virtual void process_assign_array (Statement_block*, MIR::Assign_array*) = 0;
	virtual void process_assign_target (Statement_block*, MIR::Assign_target*) = 0;
	virtual void process_assign_var (Statement_block*, MIR::Assign_var*) = 0;
	virtual void process_assign_var_var (Statement_block*, MIR::Assign_var_var*) = 0;
	virtual void process_eval_expr (Statement_block*, MIR::Eval_expr*) = 0;
	virtual void process_foreach_end (Statement_block*, MIR::Foreach_end*) = 0;
	virtual void process_foreach_next (Statement_block*, MIR::Foreach_next*) = 0;
	virtual void process_foreach_reset (Statement_block*, MIR::Foreach_reset*) = 0;
	virtual void process_global (Statement_block*, MIR::Global*) = 0;
	virtual void process_pre_op (Statement_block*, MIR::Pre_op*) = 0;
	virtual void process_push_array (Statement_block*, MIR::Push_array*) = 0;
	virtual void process_return (Statement_block*, MIR::Return*) = 0;
	virtual void process_static_declaration (Statement_block*, MIR::Static_declaration*) = 0;
	virtual void process_throw (Statement_block*, MIR::Throw*) = 0;
	virtual void process_try (Statement_block*, MIR::Try*) = 0;
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
	virtual void process_entry_block (Entry_block*) {};
	virtual void process_empty_block (Empty_block*) {};
	virtual void process_exit_block (Exit_block*) {};
	virtual void process_branch_block (Branch_block*) {};
	// TODO: any need for a process_statement_block?
	
	// Local solution - statements
	virtual void process_assign_array (Statement_block*, MIR::Assign_array*) {};
	virtual void process_assign_target (Statement_block*, MIR::Assign_target*) {};
	virtual void process_assign_var (Statement_block*, MIR::Assign_var*) {};
	virtual void process_assign_var_var (Statement_block*, MIR::Assign_var_var*) {};
	virtual void process_eval_expr (Statement_block*, MIR::Eval_expr*) {};
	virtual void process_foreach_end (Statement_block*, MIR::Foreach_end*) {};
	virtual void process_foreach_next (Statement_block*, MIR::Foreach_next*) {};
	virtual void process_foreach_reset (Statement_block*, MIR::Foreach_reset*) {};
	virtual void process_global (Statement_block*, MIR::Global*) {};
	virtual void process_pre_op (Statement_block*, MIR::Pre_op*) {};
	virtual void process_push_array (Statement_block*, MIR::Push_array*) {};
	virtual void process_return (Statement_block*, MIR::Return*) {};
	virtual void process_static_declaration (Statement_block*, MIR::Static_declaration*) {};
	virtual void process_throw (Statement_block*, MIR::Throw*) {};
	virtual void process_try (Statement_block*, MIR::Try*) {};
};


#endif // PHC_FLOW_VISITOR
