/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Flow-, field-, and context-sensitive alias analysis, in a similar fashion to
 *
 * Michael Hind and Michael Burke and Paul Carini and Jong-Deok Choi,
 * Interprocedural pointer alias analysis
 * ACM Trans. Program. Lang. Syst., 1999
 *
 * We use an infinite call-string approach, and assume that other peoples
 * research can be used to constrain the memory usage at a later date. There is
 * one points-to graph per program point (which corresponds to a basic block
 * for us).
 */

#include "BCCH_aliasing.h"
#include "Points_to.h"
#include "Whole_program.h"

using namespace MIR;

BCCH_aliasing::BCCH_aliasing (Whole_program* wp)
: wp (wp)
{
	ptg = new Points_to;
}


void
BCCH_aliasing::visit_global (Statement_block* bb, MIR::Global* in)
{
	// These dont really change anything
	// TODO: these might set a var to NULL, from uninit
	if (bb->cfg->method->is_main ())
		return;

	phc_TODO ();
}

void
BCCH_aliasing::visit_entry_block (Entry_block* bb)
{
	if (bb->cfg->method->is_main ())
		return;

	if (bb->method->signature->formal_parameters->size ())
		phc_TODO ();
}

void
BCCH_aliasing::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	switch(in->rhs->classid())
	{
		// Does not affect pointer analysis
		// TODO: except to call object properties!!
		case Bin_op::ID:
		case Isset::ID:
		case Param_is_ref::ID:
		case Unary_op::ID:
		case Instanceof::ID:
			break;

		default:
			phc_TODO ();
			break;

		// Simple graph nodes
		case BOOL::ID:
		case Constant::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
		case VARIABLE_NAME::ID:
			ptg->add_edge (ptg->get_node (in->lhs), ptg->get_node (in->rhs));
			return;

		// Need to use analysis results before putting into the graph
		case Variable_variable::ID:
		case Array_access::ID:
		case Field_access::ID:
		case Foreach_get_key::ID:
		case Foreach_get_val::ID:
		case Foreach_has_key::ID:
		case Cast::ID:
			phc_TODO ();
			break;

		// Interprocedural stuff
		case New::ID:
			phc_TODO ();
		case Method_invocation::ID:
			visit_method_invocation (bb, dyc<Method_invocation> (in->rhs));
			break;
	}

	// handle assignment to LHS
	phc_TODO ();
}

void BCCH_aliasing::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	wp->invoke_method (in);

	phc_TODO ();
}

void BCCH_aliasing::dump ()
{
	CHECK_DEBUG();
	ptg->dump_graphviz (NULL);
}
