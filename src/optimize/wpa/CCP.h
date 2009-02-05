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

	// WPA
	void kill_value (Basic_block* bb, Alias_name name);

	void assign_scalar (Basic_block* bb, Alias_name lhs,
							  MIR::Literal* rhs, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);

	void assign_unknown (Basic_block* bb, Alias_name lhs,
								certainty cert);

	void assign_value (Basic_block* bb, Alias_name lhs,
							   Alias_name rhs, certainty cert);

	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);

	void dump (Basic_block* bb);


	// CCP-specific
	bool branch_known_true (Alias_name cond);
	bool branch_known_false (Alias_name cond);

	Lattice_cell* get_value (Basic_block* bb, Alias_name name);

private:
	BB_lattices ins;
	BB_lattices locals;
	BB_lattices outs;
};

#endif // PHC_CCP
