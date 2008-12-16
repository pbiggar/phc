/*
 * Use an SCCP algorithm to propagate types. Although not based on Lenart,
 * Sadler and Guptas work, I took a gander, and I expect we can do it better
 * (where better is handle the same things, without inventing new stuff).
 *
 * So we add a lattice, and use our aliasing.
 *
 * We can solve simple function calls like is_array, is_number etc.
 *
 * We'll need to combine value range propagation as well, to see overflows (or
 * else we can only say that sums lead to numbers, not longs).
 *
 * TODO: also add a finite-state transducer based string analysis.
 *
 * At the end of the day, it would be great to have all of these (including
 * alias analysis), running simultaneously. That is about as precise as we can
 * possibly hope to get.
 *
  */

#include "Type_inference.h"
#include "Lattice.h"
#include "embed/embed.h"
#include "Def_use.h"
#include "Oracle.h"
#include "process_ir/debug.h"

using namespace MIR;


#define die() do { lattice.dump(); assert (0); } while (0)

void
Type_inference::post_pass (CFG* cfg)
{
//	Type_inference_updater* updater = new Type_inference_updater (lattice, this);
//	updater->run (cfg);
}

/* TODO: how to use this? its probably useful for this to be used both to pick
 * a better codegen as well as for micro-optimizing the generated LIR. For
 * example, we may know that something is a REAL, which means we can just use a
 * C double, and ignore the zval wrapper. At the micro-optimization level, we
 * can detect the result of (if (Z_TYPE_P (zvp) == IS_STRING)).
 */


void
Type_inference::visit_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
{
	/*	VisitPhi:
	 *	The lattice of the phis output variable is the meet of all the inputs
	 *	(non-execable means TOP), with the meet function:
	 *		any + TOP = any
	 *		any + BOTTOM = BOTTOM
	 *		ci + cj = ci if i == j (? surely if c_i == c_j?)
	 *		c1 + c2 = BOTTOM if i != j (this can be improved with VRP, using a
	 *			similar algorithm).
	 */
	Lattice_cell* result = TOP;
	foreach (Edge* pred, *bb->get_predecessor_edges ())
	{
		if (!pred->is_executable)
			; // use TOP, aka do nothing
		else
		{
			VARIABLE_NAME* arg = bb->get_phi_arg_for_edge (pred, phi_lhs);
			result = ::meet (result, lattice[arg]);
		}
	}
	// This overwrites the old value.
	set_lattice (phi_lhs, result);
}

void
Type_inference::visit_chi_node (Basic_block* bb, VARIABLE_NAME* chi_lhs, VARIABLE_NAME*)
{
	set_lattice (chi_lhs, BOTTOM);
}


/*
 * The rest of the statements make up VisitExpr:
 *
 *	VisitExpr:
 *	Evaluate the expression.
 *	- If its an assignment and creates a result for the LHS, add all SSA edges
 *	from LHS to SSAWL.
 *	- If its a branch, add:
 *		- all outgoing edges to CFGWL for BOTTOM
 *		- only the appropriate outgoing edge for a constant
 */



// Initialize all parameters to BOTTOM.
void
Type_inference::visit_entry_block (Entry_block* bb)
{
	foreach (VARIABLE_NAME* var, *bb->get_defs (SSA_FORMAL))
	{
		// No need to run again
		lattice[var] = BOTTOM;
	}
}

Edge_list*
Type_inference::get_branch_successors (Branch_block* bb)
{
	// TODO: We'd like to use the type-inference to answer questions like:
	// is_array, or is_number. But we really want to integrate this with SCCP
	// (have them running at the same time, not just using the same
	// algorithm), as I dont want to have to try to duplicate propagating
	// true/false (and value ranges, and string values, etc).

	// For now return all successors
	return bb->get_successor_edges ();
}

/*
 * Statements
 */


Type_cell::Type_cell (String* type_name)
: type_name (type_name)
{
}

void
Type_cell::dump ()
{
	DEBUG (*type_name);
}

bool
Type_cell::equals (Lattice_cell* other)
{
	return (*this->type_name == *(dyc<Type_cell> (other)->type_name));
}
