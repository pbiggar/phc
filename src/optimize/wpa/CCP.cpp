/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SCCP, so its a step forward, and
 * then one back, which will probably land in about the same place.
 *
 */

#include "CCP.h"
#include "optimize/Abstract_value.h"
#include "Points_to.h"

using namespace std;
using namespace boost;
using namespace MIR;

CCP::CCP (Whole_program* wp)
: WPA_lattice (wp)
{
}


void
CCP::set_scalar (Context cx, Value_node* storage, Abstract_value* val)
{
	Lattice_map& lat = outs[cx];
	lat[storage->name().str()] = meet (lat[storage->name().str()], val->lit);
}

void
CCP::set_storage (Context cx, Storage_node* storage, Types types)
{
	outs[cx][storage->name().str()] = BOTTOM;
}

void
CCP::pull_possible_null (Context cx, Index_node* node)
{
	Lattice_map& lat = ins[cx];
	lat[node->name().str()] = meet (lat[node->name().str()], new Literal_cell (new NIL));
	lat[ABSVAL(node)->name().str()] = meet (lat[ABSVAL(node)->name().str()], new Literal_cell (new NIL));
}


MIR::Literal*
CCP::get_lit (Context cx, Alias_name name)
{
	Lattice_cell* lat = get_value (cx, name);

	if (lat == BOTTOM)
		return NULL;

	if (lat == TOP)
		return new NIL;

	return dyc<Literal_cell> (lat)->value;
}


Literal_cell::Literal_cell (Literal* value)
: value (value)
{
}

void
Literal_cell::dump (std::ostream& os)
{
	os << *value->get_value_as_string ();
}

bool
Literal_cell::equals (Lattice_cell* other)
{
	return (this->value->equals (dyc<Literal_cell> (other)->value));
}



