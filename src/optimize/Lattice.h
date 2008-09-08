#ifndef PHC_LATTICE_H
#define PHC_LATTICE_H


enum Lattice_cell_enum { TOP, CONST, BOTTOM };
typedef enum Lattice_cell_enum Lattice_cell;

#include <map>
#include "MIR.h"

// TODO templatize on the lattice type
class Lattice 
: public map<
	MIR::VARIABLE_NAME*,
	Lattice_cell,
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)>
, virtual public Object
{
	typedef map<
		MIR::VARIABLE_NAME*,
		Lattice_cell,
		bool (*)(MIR::VARIABLE_NAME*,
		MIR::VARIABLE_NAME*)
	> parent;
public:
	Lattice ()
	{
	}

	Lattice* clone()
	{
		// TODO
		assert (0);
	}
};

Lattice_cell meet (Lattice_cell l1, Lattice_cell l2);


#endif // PHC_LATTICE_H
