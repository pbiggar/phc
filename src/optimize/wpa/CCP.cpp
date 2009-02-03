/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SCCP, so its a step forward, and then
 * one back, which will probably land in about the same place.
 *
 */

#include "CCP.h"
#include "optimize/SCCP.h"

using namespace std;
using namespace boost;
using namespace MIR;

CCP::CCP (Whole_program* wp)
: WPA (wp)
{
}


void
CCP::dump(Basic_block* bb)
{
	CHECK_DEBUG ();
	cdebug << "Dumping CCP" << endl;

	long id = bb->ID;

	// Print out the results for existing BBs (done this way so that IN and OUT
	// results are presented together).
	if (ins.has (id))
	{
		cdebug << "IN Lattice for BB: " << id << endl;
		ins[id].dump();
	}
	else
		cdebug << "No IN results for BB: " << id << endl;

	if (outs.has (id))
	{
		cdebug << "OUT Lattice for BB: " << id << endl;
		outs[id].dump();
	}
	else
		cdebug << "No OUT results for BB: " << id << endl;
}

/*
 * So we're trying to reconcile the standard daaflow techniques:
 *
 *		IN,OUT, gen, kill
 *
 *	with using the points to results to drive the analysis. Pioli's approach
 *	is very nice: worklist of BBs, keep going til its solved. But he's not
 *	doing interprocedural. However, that will work for interprocedural, so
 *	maybe just let it go.
 *
 *	So, we need to mark when a solution changes. Pioli's solution was to push
 *	results into the next section, instead of pulling. This meant saving half
 *	the result sets, and setting a block to be executed when a merge changed
 *	the solution. But this might break with branches:
 *
 *		if (...)
 *		1:	$x = 5;
 *		else
 *		2:	;
 *		3:
 *
 *	At 3: we expect $x to have the value BOTTOM, not 5, as it is uninit (and
 *	therefore NULL) at 2:.
 *
 *	This is possible using pull. To make it possible using a push model, we
 *	would need to count the number of times a value is pushed. If it is pushed
 *	less than the number of predecessor edges, it should be merged with NULL.
 *	But would this work for aliasing?
 *
 *	And if we're doing a monotonic analysis, wont running it when NULL has not
 *	yet been pushed ruin the results?  I guess when pushing the results, we
 *	must also push for missing variables.
 */

void
CCP::kill_value (Basic_block* bb, Alias_name name)
{
	if (get_value (bb, name) != TOP)
		phc_TODO ();
}

void
CCP::kill_reference (Basic_block* bb, Alias_name name)
{
	if (get_value (bb, name) != TOP)
		phc_TODO ();
}


void
CCP::assign_scalar (Basic_block* bb, Alias_name lhs, Literal* lit, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	// We ensure monotonicity. In the LOCALS lattice, the fact that LHS can be
	// assigned to multiple times is taken care of via the lattice. The first
	// assignment will merge with TOP, and the later ones might take it to
	// BOTTOM.

	Lattice_map& lat = locals[bb->ID];
	lat[lhs.str()] = meet (lat[lhs.str()], new Literal_cell (lit));
}


void
CCP::assign_by_value (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	Lattice_map& lat = locals[bb->ID];
	lat[lhs.str()] = meet (lat[lhs.str()], ins[bb->ID][rhs.str()]);
}

void
CCP::pull_results (Basic_block* bb)
{
	// TODO: only pull along executable edges
	// TODO: I could imagine this causing error in the presence of recursion.
	changed_flags[bb->ID] = false;

	// Throw away old values (change is detected in aggregation)
	ins[bb->ID].clear ();
	locals[bb->ID].clear ();

	foreach (Basic_block* pred, *bb->get_predecessors ())
	{
		ins[bb->ID].merge (&outs[pred->ID]);
	}

	if (bb->get_predecessors()->size() > 1)
		phc_TODO (); // check it
}

void
CCP::aggregate_results (Basic_block* bb)
{
	// Copy the results from INS, but overwrite them with LOCALS.
	Lattice_map* old = outs[bb->ID].clone ();
//	cdebug << "old" << endl;
//	old->dump ();

	outs[bb->ID].clear();
	outs[bb->ID].merge (&ins[bb->ID]);
	outs[bb->ID].overwrite (&locals[bb->ID]);

//	cdebug << "new" << endl;
//	outs[bb->ID].dump ();

	// Set solution_changed
	if (!outs[bb->ID].equals (old))
		changed_flags[bb->ID] = true;
}


bool
CCP::branch_known_true (Alias_name cond)
{
	return false; 
}

bool
CCP::branch_known_false (Alias_name cond)
{
	return false;
}


Lattice_cell*
CCP::get_value (Basic_block* bb, Alias_name name)
{
	return ins[bb->ID][name.str()];
}
