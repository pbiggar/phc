#ifndef PHC_EDGE
#define PHC_EDGE

#include <boost/graph/properties.hpp>

#include "MIR.h"
#include "CFG.h"
#include "Set.h"
#include "SSA.h"
#include "Phi.h"

// CFG edge
class Edge : public Object
{
public:
	CFG* cfg;
	edge_t edge;

public:
	Edge (CFG* cfg, edge_t edge, boost::tribool direction = boost::indeterminate);

public:
	/*
	 * Block properties
	 */

	bool is_executable;
	boost::tribool direction;
	Phi_map pm;

	Basic_block* get_source ();
	Basic_block* get_target ();
	void copy_phi_map (Edge* other);

public:
	/*
	 * Boost::Graph integration
	 */

	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::edge_property_tag kind;

public:
	/*
	 * Graphviz properties
	 */

/*	virtual String* get_graphviz_label () = 0;

	// Override if there are extra properties for this block.
	// Returns a list of (name,value) pairs
	virtual list<std::pair<String*,String*> >* get_graphviz_properties ();

	// Returns a list of (name, list[values]) pairs
	virtual list<pair<String*,Set*> >* get_graphviz_bb_properties ();
	virtual list<pair<String*,Set*> >* get_graphviz_head_properties ();
	virtual list<pair<String*,Set*> >* get_graphviz_tail_properties ();
*/
public:
		Edge* clone() { assert (0); }
};

// TODO move to SSA.h
class Statement_block;
class Branch_block;
class SSA_edge : public Object
{

public:
	// Target is either a PHI or a statement (aka an expr).
	
	// This means any BB (for a PHI) or a statement_block, or a branch_block.
	enum _which {PHI, STATEMENT, BRANCH} which;

	Basic_block* bb;

	// This is a pointer to the actual variable name for the def/use. The
	// variable in the def-use web is just a key, and may be a different
	// instance of the same variable.
	MIR::VARIABLE_NAME* variable_name;
	MIR::VARIABLE_NAME* phi_lhs;

public:


	SSA_edge (MIR::VARIABLE_NAME* phi_lhs, Basic_block* bb);
	SSA_edge (Statement_block* bb);
	SSA_edge (Branch_block* bb);
	SSA_edge* clone ();

	pair<MIR::VARIABLE_NAME*, Basic_block*> get_phi ();
	Statement_block* get_statement_block ();
	Branch_block* get_branch_block ();

	void dump ();
};

typedef List<SSA_edge*> SSA_edge_list;


#endif // PHC_EDGE
