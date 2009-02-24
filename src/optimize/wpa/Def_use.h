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

	void create_reference (Basic_block* bb, Index_node* lhs,
								 Index_node* rhs, certainty cert);

	void assign_value (Basic_block* bb, Index_node* lhs,
							 Storage_node* storage, certainty cert);

	// TODO: I dont think I need these... Wat about when I change the value of
	// a scalar? I think there should be a call to assign_value?
	void set_storage (Basic_block* bb, Storage_node* storage, Types types);
	void set_scalar (Basic_block* bb, Value_node* storage,
						  Abstract_value* val);

	void kill_value (Basic_block* bb, Index_node* lhs);
	void kill_reference (Basic_block* bb, Index_node* lhs);

	void record_use (Basic_block* bb, Index_node* use, certainty cert);


	void aggregate_results (Basic_block* bb);

	bool equals (WPA* other);
	void dump (Basic_block* bb, string comment);

	void backward_bind (Basic_block* caller, Exit_block* exit);

	// These return pointers to the actual values, not copies. This allows the
	// SSA name to be updated.
	Alias_name_list* get_defs (Basic_block* bb);
	Alias_name_list* get_may_defs (Basic_block* bb);
	Alias_name_list* get_uses (Basic_block* bb);

private:

	void val_assignment (Basic_block* bb, Alias_name lhs, certainty cert);
	void ref_assignment (Basic_block* bb, Alias_name lhs, certainty cert);

	// The exit block gets a use for every non-local def. This prevents DCE
	// from killing them.
	Map<long, Set<Alias_name> > ref_defs;
	Map<long, Set<Alias_name> > ref_uses;
	Map<long, Set<Alias_name> > ref_may_defs;

	Map<long, Set<Alias_name> > val_defs;
	Map<long, Set<Alias_name> > val_uses;
	Map<long, Set<Alias_name> > val_may_defs;

	Map<string, Set<Alias_name> > summary_ref_defs;
	Map<string, Set<Alias_name> > summary_ref_uses;
	Map<string, Set<Alias_name> > summary_ref_may_defs;

	Map<string, Set<Alias_name> > summary_val_defs;
	Map<string, Set<Alias_name> > summary_val_uses;
	Map<string, Set<Alias_name> > summary_val_may_defs;
};

#endif // PHC_DEF_USE
