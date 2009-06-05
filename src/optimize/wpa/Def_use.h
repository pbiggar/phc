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

// TODO: better names for deftype and reftype.
enum _reftype { REF, VAL };
typedef enum _reftype reftype;

enum _deftype { DEF, MAYDEF, USE };
typedef enum _deftype deftype;


class Def_use : public WPA
{
public:
	Def_use (Whole_program* wp);

	void init (Context outer) {}


	void create_reference (Context cx, Index_node* lhs,
								 Index_node* rhs, Certainty cert);

	void assign_value (Context cx, Index_node* lhs, Storage_node* storage);

	void kill_value (Context cx, Index_node* lhs);
	void kill_reference (Context cx, Index_node* lhs);

	void record_use (Context cx, Index_node* use, Certainty cert);


	void aggregate_results (Context cx);

	bool equals (WPA* other);
	void dump (Context cx, string comment);
	void dump_everything (string comment);

	void backward_bind (Context caller, Context exit);

	void merge_contexts ();

	// These return pointers to the actual values, not copies. This allows the
	// SSA name to be updated.
	Alias_name_list* get_defs (Basic_block* bb);
	Alias_name_list* get_may_defs (Basic_block* bb);
	Alias_name_list* get_uses (Basic_block* bb);
private:
	Alias_name_list* get_alias_name (Basic_block* bb, deftype dt);

private:


	void dump_set (Context cx, reftype rt, deftype dt);
	void record (Context cx, reftype rt, deftype dt, Index_node* index);
	bool has (Context cx, reftype rt, deftype dt, Index_node* index);

	Map<Context, Map<reftype, Map<deftype, Set<Alias_name> > > > maps;

	// The exit block gets a use for every non-local def. This prevents DCE from
	// killing them.
	Map<Context, Map<reftype, Map<deftype, Map<string, Set<Alias_name> > > > > summary_maps;
};

#endif // PHC_DEF_USE
