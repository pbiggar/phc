/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 */

#include "Constant_state.h"

Constant_state::Constant_state (Whole_program* wp)
: WPA(wp)
{
}

void
Constant_state::use_summary_results (Method_info* info, MIR::Actual_parameter_list* actuals)
{
	phc_TODO ();
}

void
Constant_state::dump()
{
	phc_TODO ();
}
