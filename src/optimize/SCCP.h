#ifndef PHC_SCCP_H_
#define PHC_SCCP_H_

#include "Sparse_conditional_visitor.h"
#include "Lattice.h"


class SCCP : public Sparse_conditional_visitor 
{
	Lattice_map<MIR::Literal> lattice;

public:
	void initialize (CFG*);
	void post_pass (CFG*);

	MIR::Literal* get_literal (MIR::Rvalue* in);
	void set_lattice (MIR::VARIABLE_NAME* def, Lattice_cell<MIR::Literal>* value);
	void meet (MIR::VARIABLE_NAME* var_name, Lattice_cell<MIR::Literal>*);
	void meet (MIR::VARIABLE_NAME* var_name, MIR::Literal*);

	// High-level SSA properties
	void visit_chi_node (Basic_block* bb, MIR::VARIABLE_NAME* lhs, MIR::VARIABLE_NAME* rhs);
	void visit_phi_node (Basic_block* bb, MIR::VARIABLE_NAME* lhs); 
	Edge_list* get_branch_successors (Branch_block*);

	// Expressions (in SCCP terminology)
	void visit_entry_block (Entry_block* bb);
	void visit_assign_field (Statement_block*, MIR::Assign_field *);
	void visit_assign_next (Statement_block*, MIR::Assign_next*);
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	void visit_global (Statement_block*, MIR::Global* in);
	void visit_pre_op (Statement_block*, MIR::Pre_op*);
	void visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*);
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	void visit_try (Statement_block*, MIR::Try*);
	void visit_unset (Statement_block*, MIR::Unset*);

	MIR::Expr* transform_array_access (Statement_block*, MIR::Array_access* in);
	MIR::Expr* transform_bin_op (Statement_block*, MIR::Bin_op* in);
	MIR::Expr* transform_cast (Statement_block*, MIR::Cast* in);
	MIR::Expr* transform_constant (Statement_block*, MIR::Constant* in);
	MIR::Expr* transform_field_access (Statement_block*, MIR::Field_access* in);
	MIR::Expr* transform_instanceof (Statement_block*, MIR::Instanceof* in);
	MIR::Expr* transform_isset (Statement_block*, MIR::Isset* in);
	MIR::Expr* transform_method_invocation (Statement_block*, MIR::Method_invocation* in);
	MIR::Expr* transform_new (Statement_block*, MIR::New* in);
	MIR::Expr* transform_param_is_ref (Statement_block*, MIR::Param_is_ref* in);
	MIR::Expr* transform_unary_op (Statement_block*, MIR::Unary_op* in);
	MIR::Expr* transform_variable_name (Statement_block*, MIR::VARIABLE_NAME* in);
	MIR::Expr* transform_variable_variable (Statement_block*, MIR::Variable_variable* in);
};


#endif // PHC_SCCP_H
