#include <boost/graph/properties.hpp>

#include "Edge.h"
#include "MIR.h"
#include "CFG.h"
#include "Def_use.h"
#include "SSA.h"
#include "Basic_block.h"

#include "process_ir/debug.h"

using namespace MIR;
using namespace boost;

Edge::Edge (CFG* cfg, edge_t edge, tribool direction)
: cfg (cfg)
, edge (edge)
, direction (direction)
{
}

Basic_block*
Edge::get_source ()
{
	return cfg->vb[source (edge, cfg->bs)];
}


Basic_block*
Edge::get_target ()
{
	return cfg->vb[target (edge, cfg->bs)];
}


void
Edge::copy_phi_map (Edge* other)
{
	// The target of either edge may have changed, so use the keys of other's
	// phi_map.
	
	// It should all work out in the end, and will be verified by
	// consistency_check.
	
	// They're not required to have the same target, only that this.target has
	// all of other.target's phi_lhss (which must be guaranteed by the caller).
	VARIABLE_NAME* phi_lhs;
	Rvalue* arg;
	foreach (tie (phi_lhs, arg), other->pm)
	{
		get_target()->set_phi_arg_for_edge (this, phi_lhs, arg);
	}
}
