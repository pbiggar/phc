/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Value-range propagation.
 *
 * Based mostly on
 * Accurate static branch prediction by value range propagation,
 * Jason Patterson,
 * PLDI95.
 *
 * We need this to help determine when integers overflow into doubles.
 *
 */

#include "VRP.h"

VRP::VRP (Whole_program* wp)
: WPA (wp)
{
}

void
VRP::use_summary_results (Method_info* info, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}

void
VRP::dump()
{
	phc_TODO ();
}

void
VRP::initialize_function (CFG* cfg, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}

void
VRP::finalize_function (CFG* cfg)
{
	phc_TODO ();
}


