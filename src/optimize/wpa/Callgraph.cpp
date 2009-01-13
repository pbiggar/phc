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
Callgraph::use_summary_results (Method_info* info)
{
	phc_TODO ();
}

void
Callgraph::dump()
{
	phc_TODO ();
}
