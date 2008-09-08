#ifndef PHC_EDGE
#define PHC_EDGE

#include <boost/graph/properties.hpp>

#include "MIR.h"
#include "CFG.h"
#include "Set.h"
#include "SSA.h"

// CFG edge
class Edge : virtual public Object
{
public:
	Basic_block* source;
	Basic_block* target;
	edge_t edge;
	tribool direction;

public:
	Edge (Basic_block* source, Basic_block* target, edge_t edge)
	: source (source)
	, target (target)
	, edge (edge)
	, direction (indeterminate)
	{
	}

	Edge (Basic_block* source, Basic_block* target, edge_t edge, bool direction)
	: source (source)
	, target (target)
	, edge (edge)
	, direction (direction)
	{
	}

public:
	/*
	 * Boost::Graph integration
	 */

	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::edge_property_tag kind;
	edge_t vertex;

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
	/*
	 * Block properties
	 */

	bool is_executable;

	// TODO do we need to clone a block?
	Edge* clone() { assert (0); }
};

// TODO move to SSA.h
class SSA_edge : public Object
{
	//		source var
	//		target var
	//		source stmt
	//		target stmt
	//		source BB
	//		target BB
	//
public:
	SSA_edge* clone ()
	{
		assert (0);
	}
};

typedef List<SSA_edge*> SSA_edge_list;


#endif // PHC_EDGE
