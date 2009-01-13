/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SCCP, so its a step forward, and then
 * one back, which will probably land in about the same place.
 *
 */

#include "CCP.h"

CCP::CCP (Whole_program* wp)
: WPA (wp)
{
}


void
CCP::use_summary_results (Method_info* info, MIR::Actual_parameter_list* in)
{
	phc_TODO ();
}

void
CCP::dump()
{
	phc_TODO ();
}
