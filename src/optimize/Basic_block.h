#ifndef PHC_BASIC_BLOCK
#define PHC_BASIC_BLOCK

#include <boost/graph/properties.hpp>

#include "CFG.h"
#include "MIR.h"
#include "Set.h"
#include "Var_map.h"
#include "ssa/SSA.h"

/* Basic blocks */
class Basic_block : virtual public GC_obj
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

public:
	/* 
	 * These are really for SSA_renaming. We can't use them for a different
	 * purpose with the same semantics.
	 * */
	MIR::VARIABLE_NAME_list* get_defs_for_renaming ();
	MIR::VARIABLE_NAME_list* get_uses_for_renaming ();

	MIR::VARIABLE_NAME_list* get_defs (int flags);
	MIR::VARIABLE_NAME_list* get_uses (int flags);

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

	// These are stored using operator< in VARIABLE_NAME, which changes when
	// there VARIABLE_NAME changes.
	void update_phi_node (MIR::VARIABLE_NAME* old_phi_lhs, MIR::VARIABLE_NAME* new_phi_lhs);
	void update_chi_lhs (MIR::VARIABLE_NAME* old_chi_lhs, MIR::VARIABLE_NAME* new_chi_lhs);
	void update_mu_node (MIR::VARIABLE_NAME* old_mu, MIR::VARIABLE_NAME* new_mu);

	// Remove a node (including its args from the edges)
	void remove_phi_node (MIR::VARIABLE_NAME* phi_lhs);

	// If the nodes have 1 argument, remove them, putting them into
	// predecessors.
	void fix_solo_phi_args ();

	// Get the arguments with VARIABLE_NAME as the lhs.
	MIR::VARIABLE_NAME_list* get_phi_args (MIR::VARIABLE_NAME* phi_lhs);

	Set* get_phi_lhss ();

	MIR::VARIABLE_NAME* get_phi_arg_for_edge (Edge*, MIR::VARIABLE_NAME* phi_lhs);
	void set_phi_arg_for_edge (Edge*, MIR::VARIABLE_NAME* phi_lhs, MIR::VARIABLE_NAME* arg);

	/*
	 * MU and CHI nodes, for HSSA form. A MU node is a may_use, a CHI is a
	 * may_def.
	 */
public:
	void add_mu_node (MIR::VARIABLE_NAME*);
	void add_chi_node (MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*);

	Var_map<MIR::VARIABLE_NAME*>* get_chis ();
	MIR::VARIABLE_NAME_list* get_chi_lhss ();
	MIR::VARIABLE_NAME_list* get_chi_rhss ();
	Set* get_mus();
	MIR::VARIABLE_NAME* get_chi_rhs (MIR::VARIABLE_NAME* lhs);

	void remove_chi (MIR::VARIABLE_NAME* lhs, MIR::VARIABLE_NAME* rhs);
	void remove_mu (MIR::VARIABLE_NAME* rhs);

	void remove_mu_nodes ();
	void remove_chi_nodes ();
	void remove_virtual_phis ();


private:
	// Instead of an explicit phi node, store the phi->lhs here, and the phi
	// arguments in edges. Then they can be updated all-at-once.
	Set* phi_lhss;
	Set* mus;
	Var_map<MIR::VARIABLE_NAME*>* chis;

public:
	/*
	 * Misc
	 */

	// Can be useful for debugging.
	int get_index ();
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
