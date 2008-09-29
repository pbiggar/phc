#ifndef PHC_BASIC_BLOCK
#define PHC_BASIC_BLOCK

#include <boost/graph/properties.hpp>

#include "MIR.h"
#include "CFG.h"
#include "Set.h"
#include "SSA.h"

/* Basic blocks */
class Basic_block : virtual public Object
{
public:
	CFG* cfg;

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

	// Override if there are extra properties for this block.
	// Returns a list of (name,value) pairs
	virtual list<std::pair<String*,String*> >* get_graphviz_properties ();

	// Returns a list of (name, list[values]) pairs
	virtual list<pair<String*,list<String*> > >* get_graphviz_bb_properties ();
	virtual list<pair<String*,list<String*> > >* get_graphviz_head_properties ();
	virtual list<pair<String*,list<String*> > >* get_graphviz_tail_properties ();

public:
	/* In the presence of variable_variables, the variable which is actually
	 * used (ie $x for $$x) is returned, not a full set.
	 * TODO: this will probably break for defs.
	 * These are really for SSA_renaming. We can't use them for a different
	 * purpose with the same semantics.*/
	virtual MIR::VARIABLE_NAME_list* get_pre_ssa_defs ();
	virtual MIR::VARIABLE_NAME_list* get_pre_ssa_uses ();

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
	void copy_phi_nodes (Basic_block* other);

	// For SSA creation/destruction
	void add_phi_node (MIR::VARIABLE_NAME* phi_lhs);
	bool has_phi_node (MIR::VARIABLE_NAME* phi_lhs);
	void add_phi_arg (MIR::VARIABLE_NAME* phi_lhs, int version, Edge* edge);
	void remove_phi_nodes ();
	void update_phi_node (MIR::VARIABLE_NAME* old_phi_lhs, MIR::VARIABLE_NAME* new_phi_lhs);

	// Remove a node (including its args from the edges)
	void remove_phi_node (MIR::VARIABLE_NAME* phi_lhs);

	// If the nodes have 1 argument, remove them, putting them into
	// predecessors.
	void fix_solo_phi_args ();

	// Get the arguments with VARIABLE_NAME as the lhs.
	MIR::Rvalue_list* get_phi_args (MIR::VARIABLE_NAME* phi_lhs);

	MIR::VARIABLE_NAME_list* get_phi_lhss ();

	MIR::Rvalue* get_phi_arg_for_edge (Edge*, MIR::VARIABLE_NAME* phi_lhs);
	void set_phi_arg_for_edge (Edge*, MIR::VARIABLE_NAME* phi_lhs, MIR::Rvalue* arg);


private:
	// Instead of an explicit phi node, store the phi->lhs here, and the phi
	// arguments in edges. Then they can be updated all-at-once.
	MIR::VARIABLE_NAME_list* phi_lhss;


public:
	/*
	 * Block manipulation
	 */
	// See CFG


public:
	/*
	 * Data-flow properties
	 *
	 * TODO: Abstract into a DF_Solution class
	 */
	
	Set* defs;
	Set* uses;
	Set* live_in;
	Set* live_out;
	int iteration_count;
	bool changed;

	// This is a global solution, so each BB should have the same solution.
	Set* aliases;

public:
	/*
	 * Misc
	 */

	// Can be useful for debugging.
	int get_index ();

	// TODO do we need to clone a block?
	Basic_block* clone() { assert (0); }
};

class Entry_block : public Basic_block
{
public:
	virtual String* get_graphviz_label ();
	Entry_block (CFG* cfg, MIR::Method* method);
	MIR::Method* method;

	void dump ();
};

class Exit_block : public Basic_block
{
public:
	MIR::Method* method;

public:
	Exit_block (CFG* cfg, MIR::Method* method);

	virtual String* get_graphviz_label ();

	void dump ();
};

class Empty_block : public Basic_block
{
public:
	Empty_block (CFG* cfg);

	virtual String* get_graphviz_label ();

	void dump ();
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
	list<pair<String*,String*> >* get_graphviz_properties ();

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
};

class Statement_block : public Basic_block 
{
public:
	MIR::Statement* statement;

public:
	Statement_block (CFG* cfg, MIR::Statement* s);

	virtual String* get_graphviz_label ();

	void dump ();
};

#endif // PHC_BASIC_BLOCK
