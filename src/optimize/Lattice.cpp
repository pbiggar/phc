
#include "Lattice.h"
#include "Basic_block.h"

using namespace std;

// Cannot allocate a new Lattice_cell, but we wish to have a real pointer.
Lattice_cell* TOP = reinterpret_cast<Lattice_cell*> (new int);
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


void
BB_lattices::dump (Basic_block* bb, string name)
{
	if (this->has (bb->ID))
	{
		cdebug << name << " Lattice for BB: " << bb->ID << endl;
		(*this)[bb->ID].dump();
		cdebug << endl;
	}
	else
		cdebug << "No " << name << " results for BB: " << bb->ID << endl;
}

void
dump_lattice (Lattice_cell* cell)
{
	if (cell == TOP)
		cdebug << "TOP";
	else if (cell == BOTTOM)
		cdebug << "BOTTOM";
	else
	{
		cdebug << "(";
		cell->dump ();
		cdebug << ")";
	}
}
