#include <boost/graph/properties.hpp>

#include "Edge.h"
#include "MIR.h"
#include "CFG.h"
#include "Set.h"
#include "SSA.h"
#include "Basic_block.h"

Edge::Edge (Basic_block* source, Basic_block* target, edge_t edge)
: source (source)
, target (target)
, edge (edge)
, direction (indeterminate)
{
}

Edge::Edge (Basic_block* source, Basic_block* target, edge_t edge, bool direction)
: source (source)
, target (target)
, edge (edge)
, direction (direction)
{
}

// TODO do we need to clone a block?
Edge*
Edge::clone()
{ 
	assert (0);
}

SSA_edge::SSA_edge (Phi* phi)
: which (PHI)
, phi (phi)
{
}

SSA_edge::SSA_edge (Statement_block* bb)
: which (STATEMENT)
, bb (bb)
{
}

SSA_edge::SSA_edge (Branch_block* bb)
: which (BRANCH)
, bb (bb)
{
}

SSA_edge* 
SSA_edge::clone ()
{
	assert (0);
}
