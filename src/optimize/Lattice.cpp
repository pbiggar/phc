#include "Lattice.h"

/*		VisitPhi:
 *		The lattice of the phis output variable is the meet of all the inputs
 *		(non-execable means TOP), with the meet function:
 *			any + TOP = any
 *			any + BOTTOM = BOTTOM
 *			ci + cj = ci if i == j (? surely if c_i == c_j?)
 *			c1 + c2 = BOTTOM if i != j (this can be improved with VRP, using a similar algorithm).
 */
// TODO move this into SCCP
Lattice_cell* meet (Lattice_cell* l1, MIR::Literal* lit)
{
	if (l1 == BOTTOM) return BOTTOM;
	if (l1 == TOP) return new Lattice_cell (lit);
	
	// l1 == CONST && l2 == CONST
	if (l1->get_value()->equals (lit))
		return l1;
	else
		return BOTTOM;
}
Lattice_cell* meet (Lattice_cell* l1, Lattice_cell* l2)
{
	if (l1 == BOTTOM || l2 == BOTTOM)
		return BOTTOM;

	if (l1 == TOP)
		return l2;
	
	if (l2 == TOP)
		return l1;

	// l1 == CONST && l2 == CONST
	return meet (l1, l2->get_value ());
}


// Pointers in the lattice_map are initialized to NULL, so this is the
// easiest way to make them TOP.
Lattice_cell* TOP = NULL;
Lattice_cell* BOTTOM = new Lattice_cell (NULL);
