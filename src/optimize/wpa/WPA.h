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
class Points_to;

class Annotator : virtual public GC_obj, public MIR::Visitor
{
public:
	Points_to* ptg;
	Basic_block* bb;
	Annotator (){}
};

class WPA : virtual public GC_obj, public CFG_visitor
{
public:
	Whole_program* wp;
	Annotator* pre_annotator;
	Annotator* post_annotator;

	WPA (Whole_program* wp)
	: wp (wp)
	, pre_annotator (NULL)
	, post_annotator (NULL)
	{
	}

	// Statements are dispatched by Whole_program.
	void run (CFG* cfg) {}

	// Prepare for a new function
	virtual void forward_bind (
			CFG* caller_cfg, CFG* callee_cfg,
			MIR::Actual_parameter_list* actuals,
			MIR::VARIABLE_NAME* lhs) = 0;

	// Indicate we are finished analysing this function
	virtual void backward_bind (CFG* caller_cfg, CFG* callee_cfg) = 0;


	// We do not have an implementation of the called method to analyse, so we
	// must instead use this summary. This summary may represent the
	// worst-case.
	virtual void use_summary_results (
			Method_info* info,
			MIR::Actual_parameter_list* actuals,
			MIR::VARIABLE_NAME* lhs) = 0;

	// Print debugging information
	virtual void dump() = 0;

	// Annotate BB using information from POINTS-TO
	// TODO: make pure virtual
	void pre_annotate (Basic_block* bb, Points_to* ptg)
	{
		if (pre_annotator == NULL)
			return;

		pre_annotator->ptg = ptg;
		pre_annotator->bb = bb;


		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
			sb->statement->visit (pre_annotator);
		else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
			phc_TODO ();

		// TODO: we're gonna have to offer a way to annotate entry and exit blocks.
	}
	void post_annotate (Basic_block* bb, Points_to*)
	{
		if (post_annotator == NULL)
			return;

		phc_TODO ();
	}
};




#endif // PHC_WPA
