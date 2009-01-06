/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Do miscellaneous annotations for optimizations - simple cases which involve
 * checking the Optimization Oracle, and do not require analysis.
 */

#ifndef PHC_MARK_REFERENCE_PARAMETERS
#define PHC_MARK_REFERENCE_PARAMETERS

#include "Visit_once.h"
#include "Address_taken.h"

class Misc_annotations : virtual public GC_obj, public Visit_once
{
private:
	Address_taken* aliasing;

public:
	void run (CFG* cfg);
	// visit_expr needs to be called manually
	void visit_assign_var (Statement_block* bb, MIR::Assign_var* in);
	void visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in);

	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_basic_block (Basic_block* bb);


	void annotate_non_by_ref_vars (Basic_block* bb);
};

#endif
