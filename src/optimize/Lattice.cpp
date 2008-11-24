
#include "Lattice.h"

// We use NULL so that 
Lattice_cell* TOP = NULL;
// Cannot allocate a new Lattice_cell, but we wish to have a real pointer.
Lattice_cell* BOTTOM = reinterpret_cast<Lattice_cell*> (new int);

Lattice_cell*
Lattice_cell::meet (Lattice_cell* other)
{
	if (this->equals (other))
		return this;
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

	return l1->meet (l2);
}
