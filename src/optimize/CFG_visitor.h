/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class handling the "Visitor" part of the CFG. Flow-analyses (such as
 * SCCP, or Visit_once) using this can traverse the CFG, and dispatch to the
 * clients using visit_block(). Clients (the user analyses, like DCE) override
 * the appropriate methods.
 *
 * Expressions can be manually dispatched by the client using visit_expr() and transform_expr ();
 */

#ifndef PHC_CFG_VISITOR
#define PHC_CFG_VISITOR

#include "process_ir/General.h"

#include "Basic_block.h"
#include "CFG.h"
#include "ssa/Phi.h"

class CFG_visitor : virtual public GC_obj
{
public:
	// Run the analysis - common interface
	virtual void run (CFG* cfg) = 0;

	/*
	 * Dispatchers - Call from clients
	 */

	void visit_block (Basic_block* bb);
	void visit_expr (Statement_block* bb, MIR::Expr*);

	// We handle putting the blocks back into the CFG
	void transform_block (Basic_block* bb);

	// The client is responsible for handling the result (this only does
	// dispatch).
	MIR::Expr* transform_expr (Statement_block* bb, MIR::Expr*);


	/*
	 * Block visitors - Override in clients.
	 * These are called automatically for visit_block(), which should be called
	 * by the analysis.
	 */

	virtual void visit_entry_block (Entry_block*);
	virtual void visit_empty_block (Empty_block*);
	virtual void visit_exit_block (Exit_block*);
	virtual void visit_branch_block (Branch_block*);
	virtual void visit_statement_block (Statement_block*);

	/*
	 * Phi visitor - Override in clients.
	 * Automatically called for each block.
	 */

	virtual void visit_phi_node (Basic_block* bb, MIR::VARIABLE_NAME* lhs);
	virtual void visit_chi_node (Basic_block* bb, MIR::VARIABLE_NAME* def, MIR::VARIABLE_NAME* use);
	virtual void visit_mu_node (Basic_block* bb, MIR::VARIABLE_NAME* use);

	/*
	 * Statement visitors - Override in clients.
	 * Automatically called for statement_blocks.
	 */


	virtual void visit_assign_array (Statement_block*, MIR::Assign_array*);
	virtual void visit_assign_field (Statement_block*, MIR::Assign_field *);
	virtual void visit_assign_var (Statement_block*, MIR::Assign_var*);
	virtual void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	virtual void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	virtual void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	virtual void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	virtual void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	virtual void visit_global (Statement_block*, MIR::Global*);
	virtual void visit_pre_op (Statement_block*, MIR::Pre_op*);
	virtual void visit_assign_next (Statement_block*, MIR::Assign_next*);
	virtual void visit_return (Statement_block*, MIR::Return*);
	virtual void visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*);
	virtual void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	virtual void visit_throw (Statement_block*, MIR::Throw*);
	virtual void visit_try (Statement_block*, MIR::Try*);
	virtual void visit_unset (Statement_block*, MIR::Unset*);

	/*
	 * Expression visitors - Override in clients.
	 * The client must call visit_expr() manually.
	 */

	virtual void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	virtual void visit_bin_op (Statement_block* bb, MIR::Bin_op* in);
	virtual void visit_bool (Statement_block* bb, MIR::BOOL* in);
	virtual void visit_cast (Statement_block* bb, MIR::Cast* in);
	virtual void visit_constant (Statement_block* bb, MIR::Constant* in);
	virtual void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	virtual void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	virtual void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	virtual void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	virtual void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	virtual void visit_int (Statement_block* bb, MIR::INT* in);
	virtual void visit_isset (Statement_block* bb, MIR::Isset* in);
	virtual void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	virtual void visit_new (Statement_block* bb, MIR::New* in);
	virtual void visit_nil (Statement_block* bb, MIR::NIL* in);
	virtual void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	virtual void visit_real (Statement_block* bb, MIR::REAL* in);
	virtual void visit_string (Statement_block* bb, MIR::STRING* in);
	virtual void visit_unary_op (Statement_block* bb, MIR::Unary_op* in);
	virtual void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	virtual void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);


	/*
	 * Block transforms - Override in clients
	 * These are called automatically for transform_block(), which should be
	 * called by the analysis.
	 */

	virtual void transform_entry_block (Entry_block* in, BB_list* out);
	virtual void transform_empty_block (Empty_block* in, BB_list* out);
	virtual void transform_exit_block (Exit_block* in, BB_list* out);
	virtual void transform_branch_block (Branch_block* in, BB_list* out);
	// Note lack of transform_statement_block. It could be added if needed.

	// This has the same signature as visit_phi_node, but it must obviously be
	// a different function from visit_phi_node, or else it would be called
	// twice.
	virtual void transform_phi_node (Basic_block* bb, MIR::VARIABLE_NAME* lhs);
	virtual void transform_chi_node (Basic_block* bb, MIR::VARIABLE_NAME* def, MIR::VARIABLE_NAME* use);
	virtual void transform_mu_node (Basic_block* bb, MIR::VARIABLE_NAME* use);

	/*
	 * Statement transforms - Override in clients.
	 * Automatically called for statement_blocks.
	 */

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
	virtual void transform_assign_next (Statement_block*, MIR::Assign_next*, BB_list*);
	virtual void transform_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*, BB_list*);
	virtual void transform_return (Statement_block*, MIR::Return*, BB_list*);
	virtual void transform_static_declaration (Statement_block*, MIR::Static_declaration*, BB_list*);
	virtual void transform_throw (Statement_block*, MIR::Throw*, BB_list*);
	virtual void transform_try (Statement_block*, MIR::Try*, BB_list*);
	virtual void transform_unset (Statement_block*, MIR::Unset*, BB_list*);


	/*
	 * Expression transforms - Override in clients.
	 * The client must call transform_expr() manually.
	 */

	virtual MIR::Expr* transform_array_access (Statement_block* bb, MIR::Array_access* in);
	virtual MIR::Expr* transform_bin_op (Statement_block* bb, MIR::Bin_op* in);
	virtual MIR::Expr* transform_bool (Statement_block* bb, MIR::BOOL* in);
	virtual MIR::Expr* transform_cast (Statement_block* bb, MIR::Cast* in);
	virtual MIR::Expr* transform_constant (Statement_block* bb, MIR::Constant* in);
	virtual MIR::Expr* transform_field_access (Statement_block* bb, MIR::Field_access* in);
	virtual MIR::Expr* transform_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	virtual MIR::Expr* transform_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	virtual MIR::Expr* transform_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	virtual MIR::Expr* transform_instanceof (Statement_block* bb, MIR::Instanceof* in);
	virtual MIR::Expr* transform_int (Statement_block* bb, MIR::INT* in);
	virtual MIR::Expr* transform_isset (Statement_block* bb, MIR::Isset* in);
	virtual MIR::Expr* transform_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	virtual MIR::Expr* transform_new (Statement_block* bb, MIR::New* in);
	virtual MIR::Expr* transform_nil (Statement_block* bb, MIR::NIL* in);
	virtual MIR::Expr* transform_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	virtual MIR::Expr* transform_real (Statement_block* bb, MIR::REAL* in);
	virtual MIR::Expr* transform_string (Statement_block* bb, MIR::STRING* in);
	virtual MIR::Expr* transform_unary_op (Statement_block* bb, MIR::Unary_op* in);
	virtual MIR::Expr* transform_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	virtual MIR::Expr* transform_variable_variable (Statement_block* bb, MIR::Variable_variable* in);

};

#endif // PHC_CFG_VISITOR
