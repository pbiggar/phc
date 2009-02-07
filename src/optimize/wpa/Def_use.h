/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Def-use information.
 *
 * Gather the def-use information while the alias analysis is running.
 *
 */

#ifndef PHC_DEF_USE
#define PHC_DEF_USE

#include "WPA.h"

class Def_use : public WPA
{
public:
	Def_use (Whole_program* wp);

	void kill_by_copy (Basic_block* bb, Alias_name name);
	void kill_by_ref (Basic_block* bb, Alias_name name);

	void assign_by_ref (Basic_block* bb, Alias_name lhs,
	                    Alias_name rhs, certainty cert);

	void assign_by_copy (Basic_block* bb, Alias_name lhs,
	                     Alias_name rhs, certainty cert);

	void assign_scalar (Basic_block* bb, Alias_name lhs,
							  MIR::Literal* rhs, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);

	void assign_unknown (Basic_block* bb, Alias_name lhs,
							   certainty cert);

	void record_use (Basic_block* bb, Alias_name lhs, certainty cert);

	void aggregate_results (Basic_block* bb);

	void dump (Basic_block* bb);

	void backward_bind (Basic_block* context, CFG* callee_cfg);

	// These return pointers to the actual values, not copies. This allows the
	// SSA name to be updated.
	Alias_name_list* get_defs (Basic_block* bb);
	Alias_name_list* get_may_defs (Basic_block* bb);
	Alias_name_list* get_uses (Basic_block* bb);

private:

	void val_assignment (Basic_block* bb, Alias_name lhs, certainty cert);
	void ref_assignment (Basic_block* bb, Alias_name lhs, certainty cert);

	Map<long, Set<Alias_name> > ref_defs;
	Map<long, Set<Alias_name> > ref_uses;
	Map<long, Set<Alias_name> > ref_may_defs;

	Map<long, Set<Alias_name> > val_defs;
	Map<long, Set<Alias_name> > val_uses;
	Map<long, Set<Alias_name> > val_may_defs;

	// We also want to store the complete set in the function, for the
	// function exit (indexed by method_name).
	// TODO: using the function name doesnt quite gel with what we're doing in
	// the analysis.
	Map<string, Set<Alias_name> > func_ref_defs;
	Map<string, Set<Alias_name> > func_ref_uses;
	Map<string, Set<Alias_name> > func_ref_may_defs;

	Map<string, Set<Alias_name> > func_val_defs;
	Map<string, Set<Alias_name> > func_val_uses;
	Map<string, Set<Alias_name> > func_val_may_defs;

};

#endif // PHC_DEF_USE
