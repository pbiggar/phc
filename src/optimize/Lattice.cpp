
#include "Lattice.h"
#include "Basic_block.h"

using namespace std;

// Cannot allocate a new Lattice_cell, but we wish to have a real pointer. We
// require that it is a class an has RRTI, and that isa<Lattice_cell> is
// successful.
class Special_cell : public Lattice_cell
{
	// TODO: funny, I thought TOP was NULL?
	void dump (ostream&) { phc_unreachable(); }
	bool equals (Lattice_cell* other) { phc_unreachable();}
	Lattice_cell* meet (Lattice_cell* other) { phc_unreachable (); }
};
Lattice_cell* TOP = new Special_cell;
Lattice_cell* BOTTOM = new Special_cell;

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
dump_cell (Lattice_cell* cell, ostream& os)
{
	if (cell == TOP)
		os << "TOP";
	else if (cell == BOTTOM)
		os << "BOTTOM";
	else
	{
		os << "(";
		cell->dump (os);
		os << ")";
	}
}
