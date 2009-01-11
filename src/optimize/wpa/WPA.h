/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A whole-program analysis. This has access to other analysis results as its
 * run, and must keep its state for the whole program. This simply provides the interface.
 */

#ifndef PHC_WPA
#define PHC_WPA

#include "optimize/CFG_visitor.h"

class WPA : virtual public GC_obj, public CFG_visitor
{
public:
	// Statements are dispatched by Whole_program.
	void run (CFG* cfg) {}

	// Tell the analysis that we are dealing with a new function here.
	void new_function (MIR::Method* in) {}

	// Really, we only need to override this in CCP.
	bool branch_is_true (MIR::Branch*) { return false; }
	bool branch_is_false (MIR::Branch*) { return false; }
};

#endif // PHC_WPA
