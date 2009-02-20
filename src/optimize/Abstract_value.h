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
#include "wpa/Type_inference.h"

class Lattice_cell;
namespace MIR { class Literal; }

class Abstract_value : public GC_obj
{
// Don't instantiate directly, use factories.
	Abstract_value (Lattice_cell* lit, Lattice_cell* type);
public:
	Lattice_cell* lit;
	Lattice_cell* type;

	void dump ();

	static Abstract_value* from_literal (MIR::Literal* lit);
	static Abstract_value* from_types (Types types);

	// We dont know anything
	static Abstract_value* unknown ();
};



#endif // PHC_ABSTRACT_VALUE_H
