#ifndef PHC_BACKWARDS_FLOW_VISITOR
#define PHC_BACKWARDS_FLOW_VISITOR

#include "CFG.h"
#include "Basic_block.h"

class Backwards_flow_visitor
{
public:
	void run (CFG* cfg);
	void process_bb (Basic_block* bb);
public:
	virtual void process_entry (Entry_block*) = 0;
	virtual void process_empty (Empty_block*) = 0;
	virtual void process_exit (Exit_block*) = 0;
	virtual void process_branch (Branch_block*) = 0;
	virtual void process_return (Statement_block* sb, MIR::Return*) = 0;
	virtual void process_static_declaration (Statement_block* sb, MIR::Static_declaration*) = 0;
	virtual void process_global (Statement_block* sb, MIR::Global*) = 0;
	virtual void process_try (Statement_block* sb, MIR::Try*) = 0;
	virtual void process_throw (Statement_block* sb, MIR::Throw*) = 0;
	virtual void process_foreach_next (Statement_block* sb, MIR::Foreach_next*) = 0;
	virtual void process_foreach_reset (Statement_block* sb, MIR::Foreach_reset*) = 0;
	virtual void process_foreach_end (Statement_block* sb, MIR::Foreach_end*) = 0;
	virtual void process_assign_var (Statement_block* sb, MIR::Assign_var*) = 0;
	virtual void process_assign_var_var (Statement_block* sb, MIR::Assign_var_var*) = 0;
	virtual void process_assign_array (Statement_block* sb, MIR::Assign_array*) = 0;
	virtual void process_push_array (Statement_block* sb, MIR::Push_array*) = 0;
	virtual void process_assign_target (Statement_block* sb, MIR::Assign_target*) = 0;
	virtual void process_eval_expr (Statement_block* sb, MIR::Eval_expr*) = 0;
	virtual void process_pre_op (Statement_block* sb, MIR::Pre_op*) = 0;
};


#endif // PHC_BACKWARDS_FLOW_VISITOR
