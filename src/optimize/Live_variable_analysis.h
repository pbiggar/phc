/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "pass_manager/Pass_manager.h"
#include "Backwards_flow_visitor.h"

#ifndef LIVE_VARIABLE_ANALYSIS
#define LIVE_VARIABLE_ANALYSIS

class Live_variable_analysis : public Pass, public Backwards_flow_visitor
{
public:
	Live_variable_analysis ();
	bool pass_is_enabled (Pass_manager* pm);
	void run (IR::PHP_script* ir_script, Pass_manager* pm);
public:

	// Transfer functions
	void transfer_in (Basic_block* bb, list<Basic_block*>* preds);
	void transfer_out (Basic_block* bb, list<Basic_block*>* succs);

	// Local solution
	void process_entry (Entry_block*) {}
	void process_empty (Empty_block*) {}
	void process_exit (Exit_block*) {}
	void process_branch (Branch_block*);
	void process_assign_array (Statement_block* sb, MIR::Assign_array*);
	void process_assign_target (Statement_block* sb, MIR::Assign_target*);
	void process_assign_var (Statement_block* sb, MIR::Assign_var*);
	void process_assign_var_var (Statement_block* sb, MIR::Assign_var_var*);
	void process_eval_expr (Statement_block* sb, MIR::Eval_expr*);
	void process_foreach_end (Statement_block* sb, MIR::Foreach_end*);
	void process_foreach_next (Statement_block* sb, MIR::Foreach_next*);
	void process_foreach_reset (Statement_block* sb, MIR::Foreach_reset*);
	void process_global (Statement_block* sb, MIR::Global*);
	void process_pre_op (Statement_block* sb, MIR::Pre_op*);
	void process_push_array (Statement_block* sb, MIR::Push_array*);
	void process_return (Statement_block* sb, MIR::Return*);

};

#endif // LIVE_VARIABLE_ANALYSIS
