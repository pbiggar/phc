/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Keep track of included files, and put them into the CFG.
 */

#include "Include_analysis.h"

Include_analysis::Include_analysis (Whole_program* wp)
: WPA (wp)
{
}

void
Include_analysis::use_summary_results (Method_info* info, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}

void
Include_analysis::dump()
{
	phc_TODO ();
}


void
Include_analysis::initialize_function (MIR::Method* in, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}

void
Include_analysis::finalize_function (MIR::Method* in)
{
	phc_TODO ();
}


