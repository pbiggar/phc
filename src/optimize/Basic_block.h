#ifndef PHC_BASIC_BLOCK
#define PHC_BASIC_BLOCK

#include <boost/graph/properties.hpp>

#include "CFG.h"
#include "MIR.h"
#include "Var_set.h"
#include "Var_map.h"
#include "ssa/SSA.h"

class Points_to;
class WPA;

/* Basic blocks */
class Basic_block : virtual public GC_obj
{
public:
	CFG* cfg;
	static long max_id;

public:
	Basic_block (CFG* parent);
	virtual void dump () = 0;

public:
	/*
	 * Boost::Graph integration
	 */

	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::vertex_property_tag kind;
	vertex_t vertex;

public:
	/*
	 * Graphviz properties
	 */

	virtual String* get_graphviz_label () = 0;

public:

	/*
	 * CFG properties
	 */
public:
	// Assert a block has a single successor, and return it.
	Basic_block* get_successor ();
	Edge* get_successor_edge  ();

	// Assert a block has a single predeccessor, and return it.
	Basic_block* get_predecessor ();
	Edge* get_predecessor_edge  ();

	BB_list* get_successors ();
	Edge_list* get_successor_edges ();

	BB_list* get_predecessors ();
	Edge_list* get_predecessor_edges ();

	/*
	 * Dominance
	 */
public:
	Basic_block* get_immediate_dominator ();
	BB_list* get_dominated_blocks ();
	bool is_dominated_by (Basic_block* bb);

	// Returns an incomplete solution during creation.
	BB_list* get_dominance_frontier ();

	// And in reverse
	Basic_block* get_immediate_reverse_dominator ();
	BB_list* get_reverse_dominated_blocks ();
	bool is_reverse_dominated_by (Basic_block* bb);

	BB_list* get_reverse_dominance_frontier ();

	/*
	 * Phi functions (or nodes)
	 */
public:
	// Copy the phi nodes from OTHER, including the phi args from OTHER's
	// incoming edges.
	void old_copy_phi_nodes (Basic_block* other);

	// For SSA creation/destruction
	void old_add_phi_node (Alias_name phi_lhs);
	bool old_has_phi_node (Alias_name phi_lhs);
	void old_add_phi_arg (Alias_name phi_lhs, int version, Edge* edge);
	void old_remove_phi_nodes ();

	// These are stored using operator< in VARIABLE_NAME, which changes when
	// there VARIABLE_NAME changes.
	void old_update_phi_node (Alias_name old_phi_lhs, Alias_name new_phi_lhs);

	// Remove a node (including its args from the edges)
	void old_remove_phi_node (Alias_name phi_lhs);

	// If the nodes have 1 argument, remove them, putting them into
	// predecessors.
	void fix_solo_phi_args ();

	// Get the arguments with VARIABLE_NAME as the lhs.
	old_Alias_name_list* old_get_phi_args (Alias_name phi_lhs);

	Var_set* old_get_phi_lhss ();

	Alias_name old_get_phi_arg_for_edge (Edge*, Alias_name phi_lhs);
	void old_set_phi_arg_for_edge (Edge*, Alias_name phi_lhs, Alias_name arg);

private:
	// Instead of an explicit phi node, store the phi->lhs here, and the phi
	// arguments in edges. Then they can be updated all-at-once.
	Var_set* old_phi_lhss;

	/*
	 * Misc
	 */

public:
	// Can be useful for debugging.
	int get_index ();
	virtual Basic_block* clone () = 0;
	virtual bool equals (Basic_block* other) = 0;

	long ID;
};

class Entry_block : public Basic_block
{
public:
	virtual String* get_graphviz_label ();
	Entry_block (CFG* cfg, MIR::Method* method);
	MIR::Method* method;

	void dump ();
	Basic_block* clone ();
	bool equals (Basic_block* other);
};

class Exit_block : public Basic_block
{
public:
	MIR::Method* method;

public:
	Exit_block (CFG* cfg, MIR::Method* method);

	virtual String* get_graphviz_label ();

	void dump ();
	Basic_block* clone ();
	bool equals (Basic_block* other);
};

class Empty_block : public Basic_block
{
public:
	Empty_block (CFG* cfg);

	virtual String* get_graphviz_label ();

	void dump ();
	Basic_block* clone ();
	bool equals (Basic_block* other);
};

class Branch_block : public Basic_block
{
public:
	MIR::Branch* branch;

public:
	Branch_block (CFG* parent, MIR::Branch* b);

	/*
	 * Graphviz
	 */
	String* get_graphviz_label ();

	// Assert a block has a two successors, representing true and false
	// branches, and return the true branch.
	Basic_block* get_true_successor ();
	Edge* get_true_successor_edge ();

	// Assert a block has a two successors, representing true and false
	// branches, and return the false branch.
	Basic_block* get_false_successor ();
	Edge* get_false_successor_edge ();

	/*
	 * Block manipulation: moved to CFG
	 */

	// except:
	void switch_successors ();

	void dump ();
	Basic_block* clone ();
	bool equals (Basic_block* other);
};

class Statement_block : public Basic_block 
{
public:
	MIR::Statement* statement;

public:
	Statement_block (CFG* cfg, MIR::Statement* s);

	virtual String* get_graphviz_label ();

	void dump ();
	Basic_block* clone ();
	bool equals (Basic_block* other);
};

#endif // PHC_BASIC_BLOCK
