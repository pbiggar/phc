#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


#include <map>
#include "MIR.h"
#include "Set.h"
#include "process_ir/debug.h"

struct Lattice_cell;

extern Lattice_cell* TOP;
extern Lattice_cell* BOTTOM;

struct Lattice_cell
{
	Lattice_cell (MIR::Literal* value) : value(value) {}

	MIR::Literal* get_value ()
	{
		assert (value != NULL);
		return value;
	}

private:
	MIR::Literal* value;
};


// TODO templatize on the lattice type
class Lattice_map
: public map<
	MIR::VARIABLE_NAME*,
	Lattice_cell*,
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)>
, virtual public Object
{
	typedef map<
		MIR::VARIABLE_NAME*,
		Lattice_cell*,
		bool (*)(MIR::VARIABLE_NAME*,
		MIR::VARIABLE_NAME*)
	> parent;
public:
	Lattice_map ()
	: parent (&variable_name_ptr_comparison)
	{
	}

	void dump ()
	{
		pair<MIR::VARIABLE_NAME*, Lattice_cell*> pair;
		foreach (pair, *this)
		{
			cdebug << *pair.first->get_ssa_var_name () << " => ";
			if (pair.second == TOP)
				cdebug << "TOP";
			else if (pair.second == BOTTOM)
				cdebug << "BOTTOM";
			else
				cdebug << "(" << *pair.second->get_value()->get_value_as_string () << ")";
			cdebug << "\n";
		}
	}

	Lattice_map* clone()
	{
		// TODO
		assert (0);
	}
};

Lattice_cell* meet (Lattice_cell* l1, Lattice_cell* l2);


#endif // PHC_LATTICE_H
