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

#include "WPA.h"
#include "Points_to.h"

class BCCH_aliasing : public WPA
{

public:
	Points_to* ptg;

	BCCH_aliasing (Whole_program*);

	void use_summary_results (Method_info* info);

	void dump ();

	void visit_entry_block (Entry_block*);
	void visit_exit_block (Exit_block*) { phc_TODO (); }
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

	void visit_array_access (Statement_block* bb, MIR::Array_access* in) { phc_TODO (); }
	void visit_bin_op (Statement_block* bb, MIR::Bin_op* in) { phc_TODO (); }
	void visit_bool (Statement_block* bb, MIR::BOOL* in) { phc_TODO (); }
	void visit_cast (Statement_block* bb, MIR::Cast* in) { phc_TODO (); }
	void visit_constant (Statement_block* bb, MIR::Constant* in) { phc_TODO (); }
	void visit_field_access (Statement_block* bb, MIR::Field_access* in) { phc_TODO (); }
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in) { phc_TODO (); }
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in) { phc_TODO (); }
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in) { phc_TODO (); }
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in) { phc_TODO (); }
	void visit_int (Statement_block* bb, MIR::INT* in) { phc_TODO (); }
	void visit_isset (Statement_block* bb, MIR::Isset* in) { phc_TODO (); }
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_nil (Statement_block* bb, MIR::NIL* in) { phc_TODO (); }
	void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in) { phc_TODO (); }
	void visit_real (Statement_block* bb, MIR::REAL* in) { phc_TODO (); }
	void visit_string (Statement_block* bb, MIR::STRING* in) { phc_TODO (); }
	void visit_unary_op (Statement_block* bb, MIR::Unary_op* in) { phc_TODO (); }
	void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in) { phc_TODO (); }
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in) { phc_TODO (); }
};

#endif // PHC_BCCH_ALIASING
