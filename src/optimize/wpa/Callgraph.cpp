/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Callgraph construction.
 */

#include "Callgraph.h"

Callgraph::Callgraph (Whole_program* wp)
: WPA(wp)
{
}

void
Callgraph::use_summary_results (Method_info* info, MIR::Actual_parameter_list*, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}

void
Callgraph::initialize_function (MIR::Method* in, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}

void
Callgraph::finalize_function (MIR::Method* in)
{
	phc_TODO ();
}



void
Callgraph::dump()
{
	phc_TODO ();
}
