#include <boost/graph/properties.hpp>

#include "Edge.h"
#include "MIR.h"
#include "CFG.h"
#include "Set.h"
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
	// The target of either edge may have changed, so use the keys of other's phi_map.
	
	// It should all work out in the end, and will be verified by consistency_check.
	
	// They're not required to have the same target, only that this.target has
	// all of other.target's phi_lhss (which must be guaranteed by the caller).
	VARIABLE_NAME* phi_lhs;
	Rvalue* arg;
	foreach (tie (phi_lhs, arg), other->pm)
	{
		get_target()->set_phi_arg_for_edge (this, phi_lhs, arg);
	}
}


SSA_edge::SSA_edge (VARIABLE_NAME* phi_lhs, Basic_block* bb)
: which (PHI)
, bb (bb)
, variable_name (NULL)
, phi_lhs (phi_lhs)
{
	assert (phi_lhs);
}

SSA_edge::SSA_edge (Statement_block* bb)
: which (STATEMENT)
, bb (bb)
, variable_name (NULL)
{
}

SSA_edge::SSA_edge (Branch_block* bb)
: which (BRANCH)
, bb (bb)
, variable_name (NULL)
{
}

SSA_edge::SSA_edge (Entry_block* bb)
: which (FORMAL_PARAMETER)
, bb (bb)
, variable_name (NULL)
{
}

SSA_edge* 
SSA_edge::clone ()
{
	assert (0);
}


pair<MIR::VARIABLE_NAME*, Basic_block*>
SSA_edge::get_phi ()
{
	assert (which == PHI);
	assert (phi_lhs);
	return make_pair (phi_lhs, bb);
}

Statement_block*
SSA_edge::get_statement_block ()
{
	assert (which == STATEMENT);
	return dynamic_cast<Statement_block*> (bb);
}

Branch_block*
SSA_edge::get_branch_block ()
{
	assert (which == BRANCH);
	return dynamic_cast<Branch_block*> (bb);
}


void
SSA_edge::dump ()
{
	CHECK_DEBUG ();

	cdebug << "SSA edge: ";

	switch (which)
	{
		case PHI:
			cdebug << "PHI: ";
			debug (variable_name);
			bb->dump ();
			break;

		case STATEMENT:
		case BRANCH:
		case FORMAL_PARAMETER:
			bb->dump ();
			break;
	}
}
