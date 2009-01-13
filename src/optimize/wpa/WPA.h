/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A whole-program analysis. This has access to other analysis results as its
 * run, and must keep its state for the whole program. This simply provides the interface.
 */

#ifndef PHC_WPA
#define PHC_WPA

#include "optimize/Oracle.h"
#include "optimize/CFG_visitor.h"
#include "Whole_program.h"

class Whole_program;

class WPA : virtual public GC_obj, public CFG_visitor
{
public:
	Whole_program* wp;

	WPA(Whole_program* wp) : wp(wp) {}

	// Statements are dispatched by Whole_program.
	void run (CFG* cfg) {}

	// Tell the analysis that we are dealing with a new function here.
	// TODO: re-enable when we have an actual use for this
//	virtual void init_function (MIR::Method* in) {}

	// Each analysis needs to be able to update when a function for which we
	// only have a summary is called (the summary will be Bottom in the worst
	// case).
	virtual void use_summary_results (Method_info* info) = 0;

	// Really, we only need to override this in CCP.
	bool branch_is_true (MIR::Branch*) { return false; }
	bool branch_is_false (MIR::Branch*) { return false; }

	// Print debugging information
	virtual void dump() = 0;
};

#endif // PHC_WPA
