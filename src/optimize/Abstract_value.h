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
public:
	Lattice_cell* lit;
	Lattice_cell* type;

public:
	Abstract_value (Lattice_cell* lit, Lattice_cell* type);
	Types get_types ();
	MIR::Literal* get_literal ();

	// These could have a truth value incorporated - for now just use the
	// constant.
	bool known_true ();
	bool known_false ();


	void dump ();

public:
	// Factories
	static Abstract_value* from_literal (MIR::Literal* lit);
	static Abstract_value* from_types (Types types);

	// We dont know anything
	static Abstract_value* unknown ();
};


/*
 * This is the simplest way to get this working, but its really nasty. I'm
 * going to change Abstract_value to take a Types and Literal, instead of
 * Lattices, and combine the functionality.
 */
class Absval_cell : public Lattice_cell
{
public:
	Absval_cell (Abstract_value*);

	void dump (std::ostream& os = cdebug);
	bool equals (Lattice_cell* other);

	Abstract_value* value;
};




#endif // PHC_ABSTRACT_VALUE_H
