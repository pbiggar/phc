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
: WPA_lattice <string, const Absval_cell> (wp)
{
}

// TODO: can be case-insensitive
string
Constant_state::context_merge_key (string key) const
{
	// Constant keys have context in them.
	return key;
}


void
Constant_state::set_constant (Context* cx, string name, const Abstract_value* value)
{
	// Should be handled in Whole_program.
	assert (not is_constant_defined (cx, R_WORKING, name));

	working[cx][name] = new Absval_cell (value);
}

// TODO: for conditionally defined constants, this might return true, even
// though its unknown.
bool
Constant_state::is_constant_defined (Context* cx, Result_state state, string name) const
{
	if (lattices[state][cx].has (name))
		return true;

	Literal* constant = PHP::fold_constant (new Constant (NULL, new CONSTANT_NAME (s(name))));
	if (constant)
		return true;

	return false;
}

void
Constant_state::set_unknown_constant (Context* cx, const Abstract_value* value)
{
	phc_TODO ();
}

const Abstract_value*
Constant_state::get_constant (Context* cx, Result_state state, string name) const
{
	if (lattices[state][cx].has (name))
		return lattices[state][cx][name]->value;

	Literal* constant = PHP::fold_constant (new Constant (NULL, new CONSTANT_NAME (s(name))));
	if (constant)
		return new Abstract_value (constant);

	return new Abstract_value (new STRING (s(name)));
}

