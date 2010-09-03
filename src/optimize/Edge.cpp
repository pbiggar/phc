#include <boost/graph/properties.hpp>

#include "Edge.h"
#include "MIR.h"
#include "CFG.h"
#include "Basic_block.h"
#include "Def_use_web.h"

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
	if (cfg->duw == NULL)
		return;

	cfg->duw->copy_phi_map (this, other);
}

Edge*
Edge::clone ()
{
	return new Edge (cfg, edge, direction);
}
