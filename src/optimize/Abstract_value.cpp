/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Abstract values fetch their results from optimizations, and are then read
 * by (possibly other) optimizations to perform their analyses.
 *
 * For example, we might be able to say that an int times 1 is an int, but
 * not than an int times and int is an int.
 *
 */

#include "Abstract_value.h"
#include "Lattice.h"
#include "process_ir/debug.h"

Abstract_value::Abstract_value ()
{
}

void
Abstract_value::dump ()
{
	CHECK_DEBUG ();
	dump_lattice (lit);
	dump_lattice (type);
}
