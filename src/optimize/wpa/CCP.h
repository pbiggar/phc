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

#include "WPA_lattice.h"

class CCP : public WPA_lattice
{
public:
	CCP (Whole_program* wp);

	void assign_scalar (Basic_block* bb, Alias_name lhs,
							  MIR::Literal* rhs, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);

	// CCP-specific
	bool branch_known_true (Alias_name cond);
	bool branch_known_false (Alias_name cond);

	Lattice_cell* get_value (Basic_block* bb, Alias_name name);

};

#endif // PHC_CCP
