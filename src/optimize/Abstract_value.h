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

#ifndef PHC_ABSTRACT_VALUE_H
#define PHC_ABSTRACT_VALUE_H

#include "lib/Object.h"

class Lattice_cell;

class Abstract_value : public GC_obj
{
public:
	Abstract_value ();
	Lattice_cell* type;
	Lattice_cell* lit;

	void dump ();
};



#endif // PHC_ABSTRACT_VALUE_H
