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
#include "optimize/SCCP.h"
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


bool
CCP::branch_known_true (Context cx, Alias_name cond)
{
	Literal* lit = get_lit (cx, cond);

	if (lit == NULL)
		return false;

	return (PHP::is_true (lit));
}

bool
CCP::branch_known_false (Context cx, Alias_name cond)
{
	// TODO: a value may have lots of actual values, all of which are true.
	// Add a true/false analysis to handle it.
	Literal* lit = get_lit (cx, cond);

	if (lit == NULL)
		return false;

	return (!PHP::is_true (lit));

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



