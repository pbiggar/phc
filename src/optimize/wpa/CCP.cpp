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

using namespace std;
using namespace boost;
using namespace MIR;

CCP::CCP (Whole_program* wp)
: WPA_lattice (wp)
{
}


void
CCP::assign_scalar (Basic_block* bb, Alias_name lhs, Literal* lit, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	// We ensure monotonicity. In the LOCALS lattice, the fact that LHS can be
	// assigned to multiple times is taken care of via the lattice. The first
	// assignment will merge with TOP, and the later ones might take it to
	// BOTTOM.

	Lattice_map& lat = outs[bb->ID];
	lat[lhs.str()] = meet (lat[lhs.str()], new Literal_cell (lit));
}

void
CCP::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
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
	Literal_cell* cell = dyc<Literal_cell> (get_value (bb, cond));

	if (cell == TOP)
		return true;

	if (cell == BOTTOM)
		return false;

	return (!PHP::is_true (cell->value));
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



