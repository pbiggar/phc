#ifndef PHC_EDGE
#define PHC_EDGE

#include <boost/graph/properties.hpp>

#include "CFG.h"
#include "MIR.h"
#include "Var_set.h"
#include "ssa/Phi.h"
#include "ssa/SSA.h"

// CFG edge
class Edge : virtual public GC_obj
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
};

// TODO move to SSA.h

#endif // PHC_EDGE
