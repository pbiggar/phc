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

	void kill_value (Basic_block* bb, Alias_name name){};
	void kill_reference (Basic_block* bb, Alias_name name){};
	void assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* rhs, certainty cert);
	void assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert){phc_TODO ();}
	void assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert);
	void record_use (Basic_block* bb, Alias_name lhs, certainty cert){};





	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);
	void dump (Basic_block* bb);

	Map<long, Lattice_map> ins;
	Map<long, Lattice_map> locals;
	Map<long, Lattice_map> outs;
};

#endif // PHC_CPP
