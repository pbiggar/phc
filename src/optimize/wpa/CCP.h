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


	bool branch_is_true (MIR::Branch*) { return false; }
	bool branch_is_false (MIR::Branch*) { return false; }

	void set_value (Basic_block* bb, string lhs, MIR::Literal* lit, certainty cert);
	void set_value_from (Basic_block* bb, string lhs, string rhs, certainty cert);


	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);
	void dump (Basic_block* bb);

	Map<long, Lattice_map> ins;
	Map<long, Lattice_map> locals;
	Map<long, Lattice_map> outs;
};

#endif // PHC_CPP
