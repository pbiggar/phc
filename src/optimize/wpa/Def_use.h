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
#include "Points_to.h"

// TODO: better names for deftype and reftype.
enum _reftype { REF, VAL };
typedef enum _reftype reftype;

enum _deftype { DEF, MAYDEF, USE };
typedef enum _deftype deftype;

// For hashmaps
namespace std
{
	namespace tr1
	{
		template <>
		struct hash<reftype>
		{
			size_t operator() (reftype t) const
			{
				return hash<int>() ((int)(t));
			}
		};

		template <>
		struct hash<deftype>
		{
			size_t operator() (deftype t) const
			{
				return hash<int>() ((int)(t));
			}
		};
	}
}

class Def_use : public WPA
{
public:
	Def_use (Whole_program* wp);

	void init (Context* outer) {}


	void create_reference (Context* cx, const Index_node* lhs,
								 const Index_node* rhs, Certainty cert);

	void assign_value (Context* cx, const Index_node* lhs, const Storage_node* storage);

	void kill_value (Context* cx, const Index_node* lhs, bool also_kill_refs = false);

	void record_use (Context* cx, const Index_node* use, Certainty cert);


	void finish_block (Context* cx);

	bool equals (WPA* other);
	void dump (Context* cx, Result_state state, string comment) const;
	void dump_everything (string comment) const;

	void backward_bind (Context* caller, Context* exit);

	void merge_contexts ();

	bool has_analysis_result (Context* cx, Result_state state) const;

	int get_num_refs (CFG* cfg, deftype dt, bool entryexit);
	int get_num_vals (CFG* cfg, deftype dt, bool entryexit);


	// These return pointers to the actual values, not copies. This allows the
	// SSA name to be updated.
	cIndex_node_list* get_defs (Basic_block* bb) const;
	cIndex_node_list* get_may_defs (Basic_block* bb) const;
	cIndex_node_list* get_uses (Basic_block* bb) const;

	void insert_def (Basic_block *bb, const Index_node *name);
	void insert_may_def (Basic_block *bb, const Index_node *name);
	void insert_use (Basic_block *bb, const Index_node *name);
 
	void remove_def (Basic_block *bb, const Index_node *name);
	void remove_may_def (Basic_block *bb, const Index_node *name);
	void remove_use (Basic_block *bb, const Index_node *name);

private:
	cIndex_node_list* get_index_nodes (Basic_block* bb, deftype dt) const;

	void insert_index_node (Basic_block* bb, const Index_node *name, deftype dt);
	void remove_index_node (Basic_block* bb, const Index_node *name, deftype dt);

private:
	void dump_set (Context* cx, reftype rt, deftype dt) const;
	void record (Context* cx, reftype rt, deftype dt, const Index_node* index);
	bool has (Context* cx, reftype rt, deftype dt, const Index_node* index) const;

	CX_map<Map<reftype, Map<deftype, Set<const Index_node*> > > > maps;

	// The exit block gets a use for every non-local def. This prevents DCE from
	// killing them.
	Map<string, Map<reftype, Map<deftype, Set<const Index_node*> > > > summary_maps;
};

#endif // PHC_DEF_USE
