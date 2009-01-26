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
: WPA (wp)
{
}


void
CCP::dump()
{
	CHECK_DEBUG ();
	cdebug << "Dumping CCP" << endl;
	long id;
	Lattice_map lat;
	foreach (tie (id, lat), lattices)
	{
		cdebug << "Lattice for BB: " << id << endl;
		lat.dump();
	}
}

void
CCP::set_value (Basic_block* bb, string lhs, Literal* lit, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	

	// The current lattice I have implemented is designed for SSA, in the sense
	// that there being only 1 assignment, we can make the defualt value TOP,
	// and then just merge.
	//
	// But there can be multiple assignments to the same variable in non-SSA.
	// The important tihng to remember is that there is one lattice per
	// program-point. So you start it at TOP, and the first assignment to it
	// merges with TOP.
	//
	// The question is what happens when you merge from two branches, the first
	// branch doesnt have it, but the second does. so that merges TOP, TOP and
	// value, which should be BOTTOM. In C, you can assume its anything if its
	// not assigned, but we cant in PHP.
	//
	// TODO: we should have a true/false lattice.
	//
	// I guess the TOP isnt uninit - its the set of all possible values. So if
	// we fetch a value from something, we should get NULL for the default.
	

	// TODO: we're going to have to deal with this when flow-sensitivity is running.
	
	Lattice_map& lat = lattices[bb->ID];
	
	// Values dont get killed to ensure monotonicity.
	lat[lhs] = meet (lat[lhs], new Literal_cell (lit));
}


void
CCP::set_value_from (Basic_block* bb, string lhs, string rhs, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();


	Lattice_map& lat = lattices[bb->ID];
	
	// Values dont get killed to ensure monotonicity.
	lat[lhs] = meet (lat[lhs], lat[rhs]);
}
