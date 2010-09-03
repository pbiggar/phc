#ifndef PHC_EDGE
#define PHC_EDGE

#include <boost/graph/properties.hpp>

#include "CFG.h"
#include "MIR.h"

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

	boost::tribool direction;

	Basic_block* get_source ();
	Basic_block* get_target ();
	void copy_phi_map (Edge* other);

public:
	/*
	 * Boost::Graph integration
	 */

	Edge* clone ();

	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::edge_property_tag kind;

};

#endif // PHC_EDGE
