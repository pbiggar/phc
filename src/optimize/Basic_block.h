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
	virtual list<pair<String*,Set*> >* get_graphviz_bb_properties ();
	virtual list<pair<String*,Set*> >* get_graphviz_head_properties ();
	virtual list<pair<String*,Set*> >* get_graphviz_tail_properties ();

public:
	/* In the presence of variable_variables, the variable which is actually
	 * used (ie $x for $$x) is returned, not a full set.
	 * TODO: this will probably break for defs.
	 * These are really for SSA_renaming. We can't use them for a different
	 * purpose with the same semantics.*/
	virtual Set* get_pre_ssa_defs ();
	virtual Set* get_pre_ssa_uses ();

	/*
	 * CFG properties
	 */
public:

	BB_list* get_predecessors ();
	BB_list* get_successors ();

	// Assert a block has a single successor, and return it.
	Basic_block* get_successor ();
	Edge* get_successor_edge  ();
	// TODO same for preds

	Edge_list* get_predecessor_edges ();
	Edge_list* get_successor_edges ();

	Basic_block* get_immediate_dominator ();
	BB_list* get_dominated_blocks ();

	// Returns an incomplete solution during creation.
	BB_list* get_dominance_frontier ();
	void add_to_dominance_frontier (Basic_block*);

	/*
	 * Phi functions (or nodes)
	 */
public:
	void add_phi_function (MIR::VARIABLE_NAME* var_name);
	bool has_phi_function (MIR::VARIABLE_NAME* var_name);
	void merge_phi_nodes (Basic_block* other);
	void remove_phi_nodes ();

	List<Phi*>* get_phi_nodes ();

private:
	Map<string, Phi*> phi_nodes;


public:
	/*
	 * Block manipulation
	 */
	void remove ();
	void replace (BB_list* replacements);

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

	// Assert a block has a two successors, representing true and false
	// branches, and return the false branch.
	Basic_block* get_false_successor ();


	void replace (BB_list* replacements)
	{
		// TODO
		assert (0);
	}

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
