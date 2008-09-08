#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


#include <map>
#include "MIR.h"
#include "Set.h"

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

	// We want TOP to be the default for uninitialized vars.
	pair<iterator, bool> insert(const pair<MIR::VARIABLE_NAME*, Lattice_cell*>& x)
	{
		if (x.second == NULL)
			return parent::insert (make_pair (x.first, TOP));

		return parent::insert (x);
	}

	Lattice_map* clone()
	{
		// TODO
		assert (0);
	}
private:
	using parent::insert;
};

Lattice_cell* meet (Lattice_cell* l1, Lattice_cell* l2);


#endif // PHC_LATTICE_H
