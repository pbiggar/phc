#ifndef PHC_SCCP_H_
#define PHC_SCCP_H_

#include "CFG.h"
#include "CFG_visitor.h"
#include "Lattice.h"

class SCCP : public CFG_visitor
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
	void visit_ssa_edge (SSA_edge* phi);

	// Blocks
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

	MIR::Expr* transform_array_access (MIR::Array_access* in);
	MIR::Expr* transform_bin_op (MIR::Bin_op* in);
	MIR::Expr* transform_cast (MIR::Cast* in);
	MIR::Expr* transform_constant (MIR::Constant* in);
	MIR::Expr* transform_field_access (MIR::Field_access* in);
	MIR::Expr* transform_instanceof (MIR::Instanceof* in);
	MIR::Expr* transform_isset (MIR::Isset* in);
	MIR::Expr* transform_method_invocation (MIR::Method_invocation* in);
	MIR::Expr* transform_new (MIR::New* in);
	MIR::Expr* transform_param_is_ref (MIR::Param_is_ref* in);
	MIR::Expr* transform_unary_op (MIR::Unary_op* in);
	MIR::Expr* transform_variable_name (MIR::VARIABLE_NAME* in);
	MIR::Expr* transform_variable_variable (MIR::Variable_variable* in);
};


#endif // PHC_SCCP_H
