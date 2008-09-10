/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class handling the "Visitor" part of the CFG. Its immediate clients
 * should handle traversing the CFG, and simply call visit_block.
 * Higher-level clients (which actually analyse) should behave as if this is
 * an MIR::Visitor which is noly called on statements, or branches.
 */

#ifndef PHC_CFG_VISITOR
#define PHC_CFG_VISITOR

#include "CFG.h"
#include "Basic_block.h"
#include "process_ir/General.h"

class CFG_visitor
{
public:
	// Dispatcher - Call from clients
	void visit_block (Basic_block* bb);
	void visit_expr (MIR::Expr*);

	// We handle putting the blocks back into the CFG */
	void transform_block (Basic_block* bb);

	// The client is responsible for handling the result (this only does
	// dispatch).
	MIR::Expr* transform_expr (MIR::Expr*);


	// Visitor - Override in clients
	virtual void visit_entry_block (Entry_block*);
	virtual void visit_empty_block (Empty_block*);
	virtual void visit_exit_block (Exit_block*);
	virtual void visit_branch_block (Branch_block*);

	// Don't depend on the ordering of this call in relation to
	// visit_mir_nodes below.
	virtual void visit_statement_block (Statement_block*);

	virtual void visit_phi_node (Phi*);

	virtual void visit_assign_array (Statement_block*, MIR::Assign_array*);
	virtual void visit_assign_field (Statement_block*, MIR::Assign_field *);
	virtual void visit_assign_var (Statement_block*, MIR::Assign_var*);
	virtual void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	virtual void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	virtual void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	virtual void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	virtual void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	virtual void visit_global (Statement_block*, MIR::Global*);
	virtual void visit_param_is_ref (Statement_block*, MIR::Param_is_ref*);
	virtual void visit_pre_op (Statement_block*, MIR::Pre_op*);
	virtual void visit_push_array (Statement_block*, MIR::Push_array*);
	virtual void visit_return (Statement_block*, MIR::Return*);
	virtual void visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*);
	virtual void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	virtual void visit_throw (Statement_block*, MIR::Throw*);
	virtual void visit_try (Statement_block*, MIR::Try*);
	virtual void visit_unset (Statement_block*, MIR::Unset*);

	// Visit_expr - Override in clients
	virtual void visit_array_access (MIR::Array_access* in);
	virtual void visit_bin_op (MIR::Bin_op* in);
	virtual void visit_bool (MIR::BOOL* in);
	virtual void visit_cast (MIR::Cast* in);
	virtual void visit_constant (MIR::Constant* in);
	virtual void visit_field_access (MIR::Field_access* in);
	virtual void visit_foreach_get_key (MIR::Foreach_get_key* in);
	virtual void visit_foreach_get_val (MIR::Foreach_get_val* in);
	virtual void visit_foreach_has_key (MIR::Foreach_has_key* in);
	virtual void visit_instanceof (MIR::Instanceof* in);
	virtual void visit_int (MIR::INT* in);
	virtual void visit_isset (MIR::Isset* in);
	virtual void visit_method_invocation (MIR::Method_invocation* in);
	virtual void visit_new (MIR::New* in);
	virtual void visit_nil (MIR::NIL* in);
	virtual void visit_param_is_ref (MIR::Param_is_ref* in);
	virtual void visit_real (MIR::REAL* in);
	virtual void visit_string (MIR::STRING* in);
	virtual void visit_unary_op (MIR::Unary_op* in);
	virtual void visit_variable_name (MIR::VARIABLE_NAME* in);
	virtual void visit_variable_variable (MIR::Variable_variable* in);


	// Transform - Override in clients
	virtual void transform_entry_block (Entry_block* in, BB_list* out);
	virtual void transform_empty_block (Empty_block* in, BB_list* out);
	virtual void transform_exit_block (Exit_block* in, BB_list* out);
	virtual void transform_branch_block (Branch_block* in, BB_list* out);

	virtual void transform_phi_node (Phi*, List<Phi*>* out);

	virtual void transform_assign_array (Statement_block*, MIR::Assign_array*, BB_list*);
	virtual void transform_assign_field (Statement_block*, MIR::Assign_field*, BB_list*);
	virtual void transform_assign_var (Statement_block*, MIR::Assign_var*, BB_list*);
	virtual void transform_assign_var_var (Statement_block*, MIR::Assign_var_var*, BB_list*);
	virtual void transform_eval_expr (Statement_block*, MIR::Eval_expr*, BB_list*);
	virtual void transform_foreach_end (Statement_block*, MIR::Foreach_end*, BB_list*);
	virtual void transform_foreach_next (Statement_block*, MIR::Foreach_next*, BB_list*);
	virtual void transform_foreach_reset (Statement_block*, MIR::Foreach_reset*, BB_list*);
	virtual void transform_global (Statement_block*, MIR::Global*, BB_list*);
	virtual void transform_param_is_ref (Statement_block*, MIR::Param_is_ref*, BB_list*);
	virtual void transform_pre_op (Statement_block*, MIR::Pre_op*, BB_list*);
	virtual void transform_push_array (Statement_block*, MIR::Push_array*, BB_list*);
	virtual void transform_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*, BB_list*);
	virtual void transform_return (Statement_block*, MIR::Return*, BB_list*);
	virtual void transform_static_declaration (Statement_block*, MIR::Static_declaration*, BB_list*);
	virtual void transform_throw (Statement_block*, MIR::Throw*, BB_list*);
	virtual void transform_try (Statement_block*, MIR::Try*, BB_list*);
	virtual void transform_unset (Statement_block*, MIR::Unset*, BB_list*);

	virtual MIR::Expr* transform_array_access (MIR::Array_access* in);
	virtual MIR::Expr* transform_bin_op (MIR::Bin_op* in);
	virtual MIR::Expr* transform_bool (MIR::BOOL* in);
	virtual MIR::Expr* transform_cast (MIR::Cast* in);
	virtual MIR::Expr* transform_constant (MIR::Constant* in);
	virtual MIR::Expr* transform_field_access (MIR::Field_access* in);
	virtual MIR::Expr* transform_foreach_get_key (MIR::Foreach_get_key* in);
	virtual MIR::Expr* transform_foreach_get_val (MIR::Foreach_get_val* in);
	virtual MIR::Expr* transform_foreach_has_key (MIR::Foreach_has_key* in);
	virtual MIR::Expr* transform_instanceof (MIR::Instanceof* in);
	virtual MIR::Expr* transform_int (MIR::INT* in);
	virtual MIR::Expr* transform_isset (MIR::Isset* in);
	virtual MIR::Expr* transform_method_invocation (MIR::Method_invocation* in);
	virtual MIR::Expr* transform_new (MIR::New* in);
	virtual MIR::Expr* transform_nil (MIR::NIL* in);
	virtual MIR::Expr* transform_param_is_ref (MIR::Param_is_ref* in);
	virtual MIR::Expr* transform_real (MIR::REAL* in);
	virtual MIR::Expr* transform_string (MIR::STRING* in);
	virtual MIR::Expr* transform_unary_op (MIR::Unary_op* in);
	virtual MIR::Expr* transform_variable_name (MIR::VARIABLE_NAME* in);
	virtual MIR::Expr* transform_variable_variable (MIR::Variable_variable* in);

};

#endif // PHC_CFG_VISITOR
