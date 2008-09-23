#include <boost/graph/properties.hpp>

#include "Edge.h"
#include "MIR.h"
#include "CFG.h"
#include "Set.h"
#include "SSA.h"
#include "Basic_block.h"

#include "process_ir/debug.h"

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
, variable_name (NULL)
{
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

SSA_edge* 
SSA_edge::clone ()
{
	assert (0);
}


Phi*
SSA_edge::get_phi ()
{
	assert (which == PHI);
	return phi;
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
			phi->dump ();
			break;

		case STATEMENT:
		case BRANCH:
			bb->dump ();
			break;
	}
}
