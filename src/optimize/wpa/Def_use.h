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

	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);

	void kill_value (Basic_block* bb, Alias_name name);
	void kill_reference (Basic_block* bb, Alias_name name);
	void assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* rhs, certainty cert);
	void assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert);
	void assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert);
	void record_use (Basic_block* bb, Alias_name lhs, certainty cert);



	void dump (Basic_block* bb);

	void backward_bind (Basic_block* context, CFG* callee_cfg);

	// TODO: do we need function local ones for call-clobbering
	Map<long, Set<Alias_name> > defs;
	Map<long, Set<Alias_name> > uses;
	Map<long, Set<Alias_name> > may_defs;
	Map<long, Set<Alias_name> > may_uses;

	// We also want to store the complete set in the function, for the
	// function exit (indexed by method_name)
	Map<string, Set<Alias_name> > func_defs;
	Map<string, Set<Alias_name> > func_uses;
	Map<string, Set<Alias_name> > func_may_defs;
	Map<string, Set<Alias_name> > func_may_uses;
/*
	// TODO: do we need function local ones for call-clobbering
	Map<long, Set<Alias_name> > direct_must_defs;
	Map<long, Set<Alias_name> > indirect_must_defs;
	Map<long, Set<Alias_name> > indirect_may_defs;
	Map<long, Set<Alias_name> > direct_must_uses;
	Map<long, Set<Alias_name> > indirect_must_uses;
	Map<long, Set<Alias_name> > indirect_may_uses;

	// We also want to store the complete set in the function, for the
	// function exit (indexed by method_name)
	Map<string , Set<Alias_name> > func_direct_must_defs;
	Map<string , Set<Alias_name> > func_indirect_must_defs;
	Map<string , Set<Alias_name> > func_indirect_may_defs;
	Map<string , Set<Alias_name> > func_direct_must_uses;
	Map<string , Set<Alias_name> > func_indirect_must_uses;
	Map<string , Set<Alias_name> > func_indirect_may_uses;
	*/
};

#endif // PHC_DEF_USE
