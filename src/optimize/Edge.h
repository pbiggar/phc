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

};

// TODO move to SSA.h

#endif // PHC_EDGE
