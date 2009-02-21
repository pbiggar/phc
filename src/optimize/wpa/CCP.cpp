/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SCCP, so its a step forward, and then
 * one back, which will probably land in about the same place.
 *
 */

#include "CCP.h"
#include "optimize/SCCP.h"
#include "optimize/Abstract_value.h"

using namespace std;
using namespace boost;
using namespace MIR;

CCP::CCP (Whole_program* wp)
: WPA_lattice (wp)
{
}


void
CCP::assign_scalar (Basic_block* bb, Alias_name lhs, Alias_name lhs_storage, Abstract_value* val, certainty cert)
{
	Lattice_map& lat = outs[bb->ID];
	lat[lhs_storage.str()] = meet (lat[lhs_storage.str()], val->lit);
	lat[lhs.str()] = meet (lat[lhs.str()], val->lit);
}

void
CCP::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	outs[bb->ID][lhs.str()] = BOTTOM;
}

void
CCP::assign_storage (Basic_block* bb, Alias_name lhs, Alias_name storage, certainty cert)
{
	outs[bb->ID][lhs.str()] = BOTTOM;
}


bool
CCP::branch_known_true (Basic_block* bb, Alias_name cond)
{
	Literal* lit = get_lit (bb, cond);

	if (lit == NULL)
		return false;

	return (PHP::is_true (lit));
}

bool
CCP::branch_known_false (Basic_block* bb, Alias_name cond)
{
	// TODO: TOP is NULL
	Lattice_cell* cell = get_value (bb, cond);

	if (cell == TOP)
		return true;

	if (cell == BOTTOM)
		return false;

	return (!PHP::is_true (dyc<Literal_cell> (cell)->value));
}


MIR::Literal*
CCP::get_lit (Basic_block* bb, Alias_name name)
{
	Lattice_cell* lat = get_value (bb, name);

	if (lat == BOTTOM)
		return NULL;

	if (lat == TOP)
		return new NIL;

	return dyc<Literal_cell> (lat)->value;
}



