/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Abstraction for passes that simply propagate a lattice. This avoids a great
 * deal of code duplication.
 *
 */

#ifndef PHC_WPA_LATTICE
#define PHC_WPA_LATTICE

#include "WPA.h"
#include "optimize/Lattice.h"

class WPA_lattice : public WPA
{
public:
	WPA_lattice (Whole_program* wp);

	// WPA
	void forward_bind (Basic_block* context, CFG* callee_cfg,
										MIR::Actual_parameter_list* actuals,
										MIR::VARIABLE_NAME* retval);

	void backward_bind (Basic_block* context, CFG* callee_cfg);

	void kill_value (Basic_block* bb, Alias_name name);

	void assign_unknown (Basic_block* bb, Alias_name lhs,
								certainty cert);

	void assign_value (Basic_block* bb, Alias_name lhs,
							   Alias_name rhs, certainty cert);

	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);

	void dump (Basic_block* bb);

private:
	void init_outs (Basic_block* bb);

protected:
	BB_lattices ins;
	BB_lattices clones;
	BB_lattices outs;
};

#endif // PHC_WPA_LATTICE
