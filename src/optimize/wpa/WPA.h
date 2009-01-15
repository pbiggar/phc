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

	WPA (Whole_program* wp) : wp (wp) {}

	// Statements are dispatched by Whole_program.
	void run (CFG* cfg) {}

	// Prepare for a new function
	virtual void initialize_function (
			CFG* caller_cfg, CFG* callee_cfg,
			MIR::Actual_parameter_list* actuals,
			MIR::VARIABLE_NAME* lhs) = 0;

	// Indicate we are finished analysing this function
	virtual void finalize_function (CFG* caller_cfg, CFG* callee_cfg) = 0;


	// We do not have an implementation of the called method to analyse, so we
	// must instead use this summary. This summary may represent the
	// worst-case.
	virtual void use_summary_results (
			Method_info* info,
			MIR::Actual_parameter_list* actuals,
			MIR::VARIABLE_NAME* lhs) = 0;

	// Really, we only need to override this in CCP.
	bool branch_is_true (MIR::Branch*) { return false; }
	bool branch_is_false (MIR::Branch*) { return false; }

	// Print debugging information
	virtual void dump() = 0;
};

#endif // PHC_WPA
