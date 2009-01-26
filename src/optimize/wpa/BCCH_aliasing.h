/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Flow-, field-, and context-sensitive alias analysis, in a similar fashion to
 *
 * Michael Hind and Michael Burke and Paul Carini and Jong-Deok Choi,
 * Interprocedural pointer alias analysis
 * ACM Trans. Program. Lang. Syst., 1999
 *
 * We use an infinite call-string approach, and assume that other peoples
 * research can be used to constrain the memory usage at a later date. There is
 * one points-to graph per program point (which corresponds to a basic block
 * for us).
 */

#ifndef PHC_BCCH_ALIASING
#define PHC_BCCH_ALIASING

#define NAME(BB) *BB->cfg->method->signature->method_name->value

#include "WPA.h"
#include "Points_to.h"


class Optimization_transformer;

class BCCH_aliasing : public CFG_visitor
{

public:
	Points_to* ptg;
	Whole_program* wp;

	// Whole_program runs this.
	void run (CFG* cfg){}

	BCCH_aliasing (Whole_program*);

	Optimization_transformer* transformer;

	void use_summary_results (Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs);

	void forward_bind (CFG* caller_cfg, CFG* callee_cfg,
			MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* retval);

	void backward_bind (CFG* caller_cfg, CFG* callee_cfg);

	void dump ();

	// Performs points-to analysis, and call the other analyses with the
	// results. Returns true if a solution has changed, requiring this block
	// to be reanalysed.
	bool analyse_block (Basic_block* bb);

	// Apply the interprocedural optimization results to this BB.
	void apply_results (Basic_block* bb);


	// These functions describe the operation being performed in each block.
	// They pass the information to the Points-to graph, and to the other
	// analyses. The BB is to give a unique index to the results.
	void set_reference (Basic_block* bb, Index_node* lhs, Index_node* rhs);
	void set_scalar_value (Basic_block* bb, Index_node* lhs, MIR::Literal* lit);
	void copy_value (Basic_block* bb, Index_node* lhs, Index_node* rhs);


	/*
	 * For analysis
	 */
	void visit_branch_block (Branch_block*) { phc_TODO (); }

	void visit_assign_array (Statement_block*, MIR::Assign_array*) { phc_TODO (); }
	void visit_assign_field (Statement_block*, MIR::Assign_field *) { phc_TODO (); }
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*) { phc_TODO (); }
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*) { phc_TODO (); }
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*) { phc_TODO (); }
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*) { phc_TODO (); }
	void visit_global (Statement_block*, MIR::Global*);
	void visit_pre_op (Statement_block*, MIR::Pre_op*) { phc_TODO (); }
	void visit_assign_next (Statement_block*, MIR::Assign_next*) { phc_TODO (); }
	void visit_return (Statement_block*, MIR::Return*) { phc_TODO (); }
	void visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*) { phc_TODO (); }
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*) { phc_TODO (); }
	void visit_throw (Statement_block*, MIR::Throw*) { phc_TODO (); }
	void visit_try (Statement_block*, MIR::Try*) { phc_TODO (); }
	void visit_unset (Statement_block*, MIR::Unset*) { phc_TODO (); }

	void handle_method_invocation (Statement_block* bb, MIR::Method_invocation* in, MIR::VARIABLE_NAME* lhs);

	void handle_new (Statement_block* bb, MIR::New* in, MIR::VARIABLE_NAME* lhs);
};

class Optimization_transformer : public CFG_visitor
{
public:
	BCCH_aliasing* aliasing;
	Optimization_transformer (BCCH_aliasing*);

	void run (CFG* cfg);

	MIR::Rvalue* get_literal (Basic_block* bb, MIR::Rvalue* in);

	void visit_assign_array (Statement_block* bb, MIR::Assign_array* in);
	void visit_assign_field (Statement_block* bb, MIR::Assign_field * in);
	void visit_assign_var (Statement_block* bb, MIR::Assign_var* in);
	void visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in);
	void visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in);
	void visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in);
	void visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in);
	void visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in);
	void visit_global (Statement_block* bb, MIR::Global* in);
	void visit_pre_op (Statement_block* bb, MIR::Pre_op* in);
	void visit_assign_next (Statement_block* bb, MIR::Assign_next* in);
	void visit_return (Statement_block* bb, MIR::Return* in);
	void visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in);
	void visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in);
	void visit_throw (Statement_block* bb, MIR::Throw* in);
	void visit_try (Statement_block* bb, MIR::Try* in);
	void visit_unset (Statement_block* bb, MIR::Unset* in);

	void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	void visit_bin_op (Statement_block* bb, MIR::Bin_op* in);
	void visit_bool (Statement_block* bb, MIR::BOOL* in);
	void visit_cast (Statement_block* bb, MIR::Cast* in);
	void visit_constant (Statement_block* bb, MIR::Constant* in);
	void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	void visit_int (Statement_block* bb, MIR::INT* in);
	void visit_isset (Statement_block* bb, MIR::Isset* in);
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_nil (Statement_block* bb, MIR::NIL* in);
	void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	void visit_real (Statement_block* bb, MIR::REAL* in);
	void visit_string (Statement_block* bb, MIR::STRING* in);
	void visit_unary_op (Statement_block* bb, MIR::Unary_op* in);
	void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
};



#endif // PHC_BCCH_ALIASING
