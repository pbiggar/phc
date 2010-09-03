#ifndef PHC_BASIC_BLOCK
#define PHC_BASIC_BLOCK

#include <boost/graph/properties.hpp>

#include "CFG.h"
#include "MIR.h"

#include "lib/Set.h"

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
	void copy_phi_nodes (Basic_block* other);

	// For SSA creation/destruction
	void add_phi_node (SSA_name phi_lhs);
	bool has_phi_node (SSA_name phi_lhs);
	void add_phi_arg (SSA_name phi_lhs, int version, Edge* edge);
	void remove_phi_nodes ();

	// These are stored using operator< in VARIABLE_NAME, which changes when
	// there VARIABLE_NAME changes.
	void update_phi_node (SSA_name phi_lhs, SSA_name new_phi_lhs);

	// Remove a node (including its args from the edges)
	void remove_phi_node (SSA_name phi_lhs);

	// If the nodes have 1 argument, remove them, putting them into
	// predecessors.
	void fix_solo_phi_args ();

	// Get the arguments with VARIABLE_NAME as the lhs.
	SSA_name_list* get_phi_args (SSA_name phi_lhs);

	Set<SSA_name>* get_phi_lhss ();

	SSA_name get_phi_arg_for_edge (Edge*, SSA_name phi_lhs);
	void set_phi_arg_for_edge (Edge*, SSA_name phi_lhs, SSA_name arg);

public:
	// For SSI creation/destruction
	void add_sigma_node(SSA_name sigma_rhs);
	bool has_sigma_node(SSA_name sigma_rhs);
	void add_sigma_arg(SSA_name sigma_rhs, int version, Edge* edge);
	void remove_sigma_nodes();

	// These are stored using operator< in VARIABLE_NAME, which changes when
	// there VARIABLE_NAME changes.
	void update_sigma_node(SSA_name sigma_rhs, SSA_name new_sigma_rhs);

	// Remove a node (including its args from the edges)
	void remove_sigma_node(SSA_name sigma_rhs);

	// Get the arguments with VARIABLE_NAME as the lhs.
	SSA_name_list *get_sigma_args(SSA_name sigma_rhs);
	Set<SSA_name> *get_sigma_rhss();

	SSA_name get_sigma_arg_for_edge(Edge *, SSA_name sigma_rhs);
	void set_sigma_arg_for_edge (Edge *, SSA_name sigma_rhs, SSA_name arg);

	/*
	 * Misc
	 */

public:
	// Can be useful for debugging.
	int get_index ();
	virtual Basic_block* clone () = 0;
	virtual bool equals (Basic_block* other) = 0;

	// the prefix for SSA_names
	string get_prefix ();

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
