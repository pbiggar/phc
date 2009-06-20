/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 */

#include "Constant_state.h"
#include "Value_analysis.h"

using namespace MIR;

Constant_state::Constant_state (Whole_program* wp)
: WPA_lattice<Absval_cell> (wp)
{
}

// TODO: can be case-insensitive

void
Constant_state::set_constant (Context* cx, string name, Abstract_value* value)
{
	// Should be handled in Whole_program.
	assert (not is_constant_defined (cx, name));

	outs[cx][name] = new Absval_cell (value);
}

// TODO: for conditionally defined constants, this might return true, even
// though its unknown.
bool
Constant_state::is_constant_defined (Context* cx, string name)
{
	if (outs[cx].has (name))
		return true;

	Literal* constant = PHP::fold_constant (new Constant (NULL, new CONSTANT_NAME (s(name))));
	if (constant)
		return true;

	return false;
}

void
Constant_state::set_unknown_constant (Context* cx, Abstract_value* value)
{
	phc_TODO ();
}

Abstract_value*
Constant_state::get_constant (Context* cx, string name)
{
	// TODO: check for unknown constants
	if (not is_constant_defined (cx, name))
		return new Abstract_value (new STRING (s(name)));

	return outs[cx][name]->value;
}

