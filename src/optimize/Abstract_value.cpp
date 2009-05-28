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

#include "process_ir/debug.h"

#include "Abstract_value.h"
#include "Lattice.h"
#include "wpa/CCP.h"
#include "wpa/Type_inference.h"

Abstract_value::Abstract_value (Lattice_cell* lit, Lattice_cell* type)
: lit (lit)
, type (type)
{
}

void
Abstract_value::dump ()
{
	CHECK_DEBUG ();
	cdebug << "{";
	dump_cell (lit, cdebug);
	cdebug << ", ";
	dump_cell (type, cdebug);
	cdebug << "}";
}

Types
Abstract_value::get_types ()
{
	assert (type != BOTTOM);
	if (type == TOP)
		return Types ("unset");

	return dyc<Type_cell> (type)->types;
}

MIR::Literal*
Abstract_value::get_literal ()
{
	if (this->lit == TOP)
		return new MIR::NIL;

	if (this->lit == BOTTOM)
		return NULL;

	return dyc<Literal_cell> (lit)->value;
}

Abstract_value*
Abstract_value::from_literal (MIR::Literal* lit)
{
	return new Abstract_value (
		new Literal_cell (lit),
		new Type_cell (Type_inference::get_type (lit)));
}

Abstract_value*
Abstract_value::from_types (Types types)
{
	return new Abstract_value (BOTTOM, new Type_cell (types));
}

Abstract_value*
Abstract_value::unknown ()
{
	return new Abstract_value (
		BOTTOM,
		new Type_cell (Type_inference::get_all_scalar_types ()));
}

bool
Abstract_value::known_false ()
{
	if (lit == BOTTOM)
		return false;

	return not this->known_true ();
}

bool
Abstract_value::known_true ()
{
	if (lit == BOTTOM)
		return false;

	if (lit == TOP)
		return false;

	return PHP::is_true (dyc<Literal_cell> (lit)->value);
}
