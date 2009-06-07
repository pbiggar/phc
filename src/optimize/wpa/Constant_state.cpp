/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 */

#include "Constant_state.h"
#include "optimize/Abstract_value.h"

using namespace MIR;

Constant_state::Constant_state (Whole_program* wp)
: WPA_lattice (wp)
{
}

void
Constant_state::set_constant (Context cx, Abstract_value* name, Abstract_value* value)
{
	Literal* lit = name->get_literal ();
	if (lit == NULL)
	{
		phc_TODO ();
	}
	else
	{
		Lattice_map& lat = outs[cx];

		String* str_name = PHP::get_string_value (lit);
		if (lat.has (*str_name))
			phc_TODO (); // hmmmm, loops

		phc_TODO ();
//		lat[*str_name] = new Absval_cell (value);
	}
}

Abstract_value*
Constant_state::get_constant (Context cx, MIR::Constant* constant)
{
	phc_TODO ();
}

void
Constant_state::pull_possible_null (Context cx, Index_node* node)
{
}


