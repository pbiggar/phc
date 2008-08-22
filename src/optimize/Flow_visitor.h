/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for data-flow analyses.
 */

#ifndef PHC_FLOW_VISITOR
#define PHC_FLOW_VISITOR

#include "CFG.h"
#include "Basic_block.h"
#include "process_ir/General.h"

/* Direction chooses whether the worklist operates from backwards from Exit,
 * or forwards from Entry. */
enum Flow_visitor_direction { FORWARD_FLOW, BACKWARD_FLOW };

class Flow_visitor
{
private:
	Flow_visitor_direction direction;

public:
	Flow_visitor (Flow_visitor_direction direction);

	/* Public interface for analyses */
	void visit (CFG* cfg);
	virtual void init_block (Basic_block* bb) {}
	virtual bool solution_has_changed (Basic_block* bb) { return false; }

	/* Transfer functions */
	virtual void transfer_in (Basic_block* bb, list<Basic_block*>* preds) {};
	virtual void transfer_out (Basic_block* bb, list<Basic_block*>* succs) {};

	virtual void visit_entry_block (Entry_block*) {};
	virtual void visit_empty_block (Empty_block*) {};
	virtual void visit_exit_block (Exit_block*) {};
	virtual void visit_branch_block (Branch_block*) {};

	virtual void visit_assign_array (Statement_block*, MIR::Assign_array*) {};
	virtual void visit_assign_field (Statement_block*, MIR::Assign_field *) {};
	virtual void visit_assign_var (Statement_block*, MIR::Assign_var*) {};
	virtual void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*) {};
	virtual void visit_eval_expr (Statement_block*, MIR::Eval_expr*) {};
	virtual void visit_foreach_end (Statement_block*, MIR::Foreach_end*) {};
	virtual void visit_foreach_next (Statement_block*, MIR::Foreach_next*) {};
	virtual void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*) {};
	virtual void visit_global (Statement_block*, MIR::Global*) {};
	virtual void visit_param_is_ref (Statement_block*, MIR::Param_is_ref*) {};
	virtual void visit_pre_op (Statement_block*, MIR::Pre_op*) {};
	virtual void visit_push_array (Statement_block*, MIR::Push_array*) {};
	virtual void visit_return (Statement_block*, MIR::Return*) {};
	virtual void visit_static_declaration (Statement_block*, MIR::Static_declaration*) {};
	virtual void visit_throw (Statement_block*, MIR::Throw*) {};
	virtual void visit_try (Statement_block*, MIR::Try*) {};
	virtual void visit_unset (Statement_block*, MIR::Unset*) {};


	virtual void transform_entry_block (Entry_block* in, list<Basic_block*>* out);
	virtual void transform_empty_block (Empty_block* in, list<Basic_block*>* out);
	virtual void transform_exit_block (Exit_block* in, list<Basic_block*>* out);
	virtual void transform_branch_block (Branch_block* in, list<Basic_block*>* out);

	virtual void transform_assign_array (Statement_block* in, MIR::Assign_array*, list<Basic_block*>* out);
	virtual void transform_assign_field (Statement_block* in, MIR::Assign_field*, list<Basic_block*>* out);
	virtual void transform_assign_var (Statement_block* in, MIR::Assign_var*, list<Basic_block*>* out);
	virtual void transform_assign_var_var (Statement_block* in, MIR::Assign_var_var*, list<Basic_block*>* out);
	virtual void transform_eval_expr (Statement_block* in, MIR::Eval_expr*, list<Basic_block*>* out);
	virtual void transform_foreach_end (Statement_block* in, MIR::Foreach_end*, list<Basic_block*>* out);
	virtual void transform_foreach_next (Statement_block* in, MIR::Foreach_next*, list<Basic_block*>* out);
	virtual void transform_foreach_reset (Statement_block* in, MIR::Foreach_reset*, list<Basic_block*>* out);
	virtual void transform_global (Statement_block* in, MIR::Global*, list<Basic_block*>* out);
	virtual void transform_param_is_ref (Statement_block* in, MIR::Param_is_ref*, list<Basic_block*>* out);
	virtual void transform_pre_op (Statement_block* in, MIR::Pre_op*, list<Basic_block*>* out);
	virtual void transform_push_array (Statement_block* in, MIR::Push_array*, list<Basic_block*>* out);
	virtual void transform_return (Statement_block* in, MIR::Return*, list<Basic_block*>* out);
	virtual void transform_static_declaration (Statement_block* in, MIR::Static_declaration*, list<Basic_block*>* out);
	virtual void transform_throw (Statement_block* in, MIR::Throw*, list<Basic_block*>* out);
	virtual void transform_try (Statement_block* in, MIR::Try*, list<Basic_block*>* out);
	virtual void transform_unset (Statement_block* in, MIR::Unset*, list<Basic_block*>* out);


private:
	/* Calculate the local solution */
	void visit_bb_local (CFG* cfg, Basic_block* bb);
	void transform_bb (Basic_block* bb, list<Basic_block*>* out);

	list<Basic_block*>* get_next_cfg_nodes (Basic_block* bb, CFG* cfg);
	void visit_transfer_functions (Basic_block* bb, CFG* cfg);
	list<Basic_block*>* get_initial_worklist (CFG* cfg);
};

class Forward_flow_visitor : public Flow_visitor
{
public:
	Forward_flow_visitor () : Flow_visitor (FORWARD_FLOW) {}
};

class Backward_flow_visitor : public Flow_visitor
{
public:
	Backward_flow_visitor () : Flow_visitor (BACKWARD_FLOW) {}
};



#endif // PHC_FLOW_VISITOR
