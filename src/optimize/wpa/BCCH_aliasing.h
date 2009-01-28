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
 * research can be used to constrain the memory usage at a later date. There
 * is one points-to graph per program point (which corresponds to a basic
 * block for us).
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
	Optimization_transformer* transformer;

	// Record 1 per program-point.
	Map<long, Points_to*> ptgs;

	BCCH_aliasing (Whole_program*);


	void use_summary_results (Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs);

	void forward_bind (Basic_block* bb, CFG* callee_cfg,
			MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* retval);

	void backward_bind (Basic_block* bb, CFG* callee_cfg);

	// Performs points-to analysis, and call the other analyses with the
	// results. Returns true if a solution has changed, requiring this block
	// to be reanalysed.
	bool analyse_block (Basic_block* bb);

	// Apply the interprocedural optimization results to this BB.
	void apply_results (Basic_block* bb);

	void dump (Basic_block* bb);

private:
	// These functions describe the operation being performed in each block.
	// They pass the information to the Points-to graph, and to the other
	// analyses. The BB is to give a unique index to the results.
	void set_reference (Basic_block* bb, Index_node* lhs, Index_node* rhs);
	void set_scalar_value (Basic_block* bb, Index_node* lhs, MIR::Literal* lit);
	void copy_value (Basic_block* bb, Index_node* lhs, Index_node* rhs);

	// Make LHS reference the storage node pointed-to by STORAGE, indexed by
	// the _value_ of RHS.
	// ie $lhs = $storage[$rhs];
	// or $lhs = $storage->$rhs;
	// or $lhs = $$rhs;
	void set_indirect_reference (Basic_block* bb, Index_node* lhs, Index_node* storage, Index_node* rhs);


	// Whole_program runs this, so we dont need it.
	void run (CFG* cfg){}


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



#endif // PHC_BCCH_ALIASING
