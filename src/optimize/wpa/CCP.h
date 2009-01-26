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

#ifndef PHC_CCP
#define PHC_CCP

#include "WPA.h"
#include "optimize/Lattice.h"

class CCP : public WPA
{
public:
	CCP (Whole_program* wp);

	void dump ();

	bool branch_is_true (MIR::Branch*) { return false; }
	bool branch_is_false (MIR::Branch*) { return false; }

	void set_value (Basic_block* bb, string index_node, MIR::Literal* lit, certainty cert);

	Map<long, Lattice_map> lattices;
};

#endif // PHC_CPP
