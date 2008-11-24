#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


#include "lib/Map.h"
#include "Var_map.h"

#include "MIR.h"
#include "Set.h"
#include "process_ir/debug.h"

class Lattice_cell : virtual public GC_obj
{
public:
	virtual void dump () = 0;

	// Assume THIS and OTHER are not TOP or BOTTOM, and they are all of the same type.
	virtual bool equals (Lattice_cell* other) = 0;

	// Assuming that THIS and OTHER are not TOP or BOTTOM. This models a 3-level
	// lattice. A subclass may wish to model a deeper lattice.
	virtual Lattice_cell* meet (Lattice_cell* other);
};

extern Lattice_cell* TOP;
extern Lattice_cell* BOTTOM;


class Lattice_map
: public Var_map<Lattice_cell*>
{
public:
	Lattice_map () : Var_map<Lattice_cell*> () { }

	void dump ()
	{
		std::pair<MIR::VARIABLE_NAME*, Lattice_cell*> pair;
		foreach (pair, *this)
		{
			cdebug << *pair.first->get_ssa_var_name () << " => ";
			if (pair.second == TOP)
				cdebug << "TOP";
			else if (pair.second == BOTTOM)
				cdebug << "BOTTOM";
			else
			{
				cdebug << "(";
				pair.second->dump ();
				cdebug << ")";
			}
			cdebug << "\n";
		}
	}
};

Lattice_cell* meet (Lattice_cell* l1, Lattice_cell* l2);

#endif // PHC_LATTICE_H
