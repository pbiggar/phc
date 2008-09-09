#ifndef PHC_SCCP_H_
#define PHC_SCCP_H_

#include "CFG.h"
#include "Lattice.h"

class SCCP
{
	CFG* cfg;
	Lattice_map lattice;
	Edge_list* cfg_wl;
	SSA_edge_list* ssa_wl;

public:
	SCCP (CFG* cfg);
	void execute ();
	MIR::Literal* get_literal (MIR::Rvalue* in);
	int get_predecessor_executable_count (Basic_block* bb);

	// High-level SSA properties
	void visit_phi (Phi* phi);
	void visit_block (Basic_block* bb);
	void visit_ssa_edge (SSA_edge* phi);

	// Generic MIR properties
	void visit_statement (MIR::Statement* in);
	void visit_branch (MIR::Branch* in);

	// Blocks
	void visit_entry_block (Entry_block*);
	void visit_empty_block (Empty_block*);
	void visit_exit_block (Exit_block*);
	void visit_branch_block (Branch_block*);

	// Statement blocks
	void visit_assign_array (Statement_block*, MIR::Assign_array*);
	void visit_assign_field (Statement_block*, MIR::Assign_field *);
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	void visit_global (Statement_block*, MIR::Global*);
	void visit_param_is_ref (Statement_block*, MIR::Param_is_ref*);
	void visit_pre_op (Statement_block*, MIR::Pre_op*);
	void visit_push_array (Statement_block*, MIR::Push_array*);
	void visit_return (Statement_block*, MIR::Return*);
	void visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*);
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	void visit_throw (Statement_block*, MIR::Throw*);
	void visit_try (Statement_block*, MIR::Try*);
	void visit_unset (Statement_block*, MIR::Unset*);

};


#endif // PHC_SCCP_H
