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
using namespace boost;
using namespace std;

BCCH_aliasing::BCCH_aliasing (Whole_program* wp)
: wp (wp)
{
	ptg = new Points_to;
}


void
BCCH_aliasing::use_summary_results (Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs)
{
	if (lhs)
		phc_TODO ();

	if (info->can_touch_globals)
		phc_TODO ();

	if (info->can_touch_locals)
		phc_TODO ();

	if (info->return_by_ref)
		phc_TODO ();

	// We model each parameter, and the return value, for:
	//		- can they alias other parameters (keep it simple, we can do more
	//		complicated thing for functions we analyse, such as 'aliases a field
	//		of param1'.
	//		- can they alias a global variable
	foreach (Parameter_info* pinfo, *info->params)
	{
		if (pinfo->pass_by_reference)
			phc_TODO ();

		if (pinfo->is_callback)
			phc_TODO ();

		if (pinfo->can_touch_objects)
			phc_TODO ();

		// Magic methods are handled in the callgraph.
	}

	// TODO: does this create alias relationships
	// TODO: how does this affect the callgraph
	//		- need to look at types for that
}



void
BCCH_aliasing::forward_bind (CFG* caller_cfg, CFG* callee_cfg, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	string callee_ns = *callee_cfg->method->signature->method_name->value;
	string caller_ns;
	if (caller_cfg) 
		caller_ns = *caller_cfg->method->signature->method_name->value;


	ptg->open_scope (callee_ns);

	if (actuals->size () != callee_cfg->method->signature->formal_parameters->size ())
		phc_TODO ();


	Actual_parameter_list::const_iterator i = actuals->begin ();
	foreach (Formal_parameter* fp, *callee_cfg->method->signature->formal_parameters)
	{
		if (fp->var->default_value)
			phc_TODO ();

		Actual_parameter* ap = *i;
		if (fp->is_ref || ap->is_ref)
		{
			phc_TODO ();
			// $fp =& $ap;
//			ptg->set_reference (
//				ptg->get_var (callee_ns, fp->var->variable_name),
//				ptg->get_var (caller_ns, dyc<VARIABLE_NAME> (ap->rvalue)));
		}
		else
		{
			// $fp = $ap;
			phc_TODO ();
		}
	}

	if (lhs)
	{
		// TODO: do this upon return instead
		phc_TODO ();
		/*
		if (return_by_ref)
			set_reference
		else
			set_value
		*/
	}
}

void
BCCH_aliasing::backward_bind (CFG* caller_cfg, CFG* callee_cfg)
{
	phc_TODO ();

	// TODO: handle returns

	ptg->close_scope (*callee_cfg->method->signature->method_name->value);
}

bool
BCCH_aliasing::analyse_block (Basic_block* bb)
{
	string name;
	WPA* wpa;

	// Merge results from predecessors
	foreach (tie (name, wpa), wp->analyses)
		wpa->pull_results (bb);

	
	// Do the aliasing (and hence other analyses)
	visit_block (bb);


	// Create OUT sets from the results 
	foreach (tie (name, wpa), wp->analyses)
		wpa->aggregate_results (bb);


	// Dump
	dump();
	foreach (tie (name, wpa), wp->analyses)
		wpa->dump (bb);


	// Calculate fix-point
	bool reiterate = false;
	foreach (tie (name, wpa), wp->analyses)
		reiterate |= wpa->solution_changed (bb);


	return reiterate;
}



void
BCCH_aliasing::visit_global (Statement_block* bb, MIR::Global* in)
{
	// These dont really change anything
	// TODO: these might set a var to NULL, from uninit
	// TODO: merge from trunk, it removes the semantics changing ones
	if (bb->cfg->method->is_main ())
		return;

	if (isa<Variable_variable> (in->variable_name))
		phc_TODO ();

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in->variable_name);
	phc_TODO ();
/*	ptg->set_reference (
		ptg->get_var (NAME (bb), var_name),
		ptg->get_var ("__MAIN__", var_name));
*/
}


void
BCCH_aliasing::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	string ns = NAME (bb);
	Index_node* lhs = VN (ns, in->lhs);
	PT_node* rhs = NULL;

	switch(in->rhs->classid())
	{
		// Does not affect pointer analysis
		// TODO: except to call object properties!!
		case Bin_op::ID:
		case Isset::ID:
		case Param_is_ref::ID:
		case Unary_op::ID:
		case Instanceof::ID:
		case Constant::ID:
			break;

		case VARIABLE_NAME::ID:
			rhs =	VN (ns, dyc<VARIABLE_NAME> (in->rhs));
			break;

		default:
			phc_TODO ();
			break;

		// Not in the graph
		case BOOL::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
			set_scalar_value (bb, lhs, dyc<Literal> (in->rhs));
			return;

		// Need to use analysis results before putting into the graph
		case Variable_variable::ID:
		case Field_access::ID:
		case Foreach_get_key::ID:
		case Foreach_get_val::ID:
		case Foreach_has_key::ID:
		case Cast::ID:
			phc_TODO ();
			break;

		case Array_access::ID:
		{
			phc_TODO ();
//			Array_access* aa = dyc<Array_access> (in->rhs);
//			Location* array = ptg->get_var (ns, aa->variable_name);
//			Location* index =
//				ptg->get_var (ns, dyc<VARIABLE_NAME> (aa->index));

			phc_TODO ();
//			rhs = ptg->get_indexed_location (array, index);
			break;
		}

		// Interprocedural stuff
		case New::ID:
			handle_new (bb, dyc<New> (in->rhs), in->lhs);
			phc_TODO ();
			break;

		case Method_invocation::ID:
			handle_method_invocation (bb, dyc<Method_invocation> (in->rhs), in->lhs);
			phc_TODO ();
			break;
	}

	assert (rhs);
	if (in->is_ref)
		set_reference (bb, lhs, dyc<Index_node> (rhs));
	else
		copy_value (bb, lhs, dyc<Index_node> (rhs));
}

void
BCCH_aliasing::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	if (isa<New> (in->expr))
		handle_new (bb, dyc<New> (in->expr), NULL);
	else
		handle_method_invocation (bb, dyc<Method_invocation> (in->expr), NULL);
}

void
BCCH_aliasing::handle_method_invocation (Statement_block* bb, MIR::Method_invocation* in, MIR::VARIABLE_NAME* lhs)
{
	wp->invoke_method (in, bb->cfg, lhs);
}

void
BCCH_aliasing::handle_new (Statement_block* bb, MIR::New* in, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}


void
BCCH_aliasing::dump ()
{
	CHECK_DEBUG();
	ptg->dump_graphviz (NULL);
}



/*
 * Update the Points-to solution, and interface with other analyses.
 */
void
BCCH_aliasing::set_reference (Basic_block* bb, Index_node* lhs, Index_node* rhs)
{
	// We don't need to worry about aliases, as this is killing.

	// Handle LHS itself
	string name;
	WPA* wpa;
	foreach (tie (name, wpa), wp->analyses)
		wpa->set_value_from (bb, lhs->get_unique_name (), rhs->get_unique_name(), DEFINITE);


	// Handle aliasing
	ptg->set_reference (lhs, rhs);
}

// TODO: i expect we dont need to do a union of the RHSs (ie, I expect that's
// already sorted from when the aliasing happened).

void
BCCH_aliasing::set_scalar_value (Basic_block* bb, Index_node* lhs, Literal* lit)
{
	// Send the results to the analyses for all variables which could be
	// overwritten.
	WPA* wpa;
	string name;
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty cert, certainties)
	{
		String_list* aliases = ptg->get_aliases (lhs, cert);
		foreach (tie (name, wpa), wp->analyses)
		{
			foreach (String* alias, *aliases)
				wpa->set_value (bb, *alias, lit, cert);
		}
	}

	// Handle LHS itself
	foreach (tie (name, wpa), wp->analyses)
		wpa->set_value (bb, lhs->get_unique_name (), lit, DEFINITE);


	// Handle aliasing
	ptg->set_scalar_value (lhs);
}

void
BCCH_aliasing::copy_value (Basic_block* bb, Index_node* lhs, Index_node* rhs)
{
	// This is not killing in terms of aliasing, so it assigns to all aliases
	// of lhs.
	WPA* wpa;
	string name;
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty cert, certainties)
	{
		String_list* aliases = ptg->get_aliases (lhs, cert);
		foreach (tie (name, wpa), wp->analyses)
		{
			foreach (String* alias, *aliases)
				wpa->set_value_from (bb, *alias, rhs->get_unique_name (), cert);
		}
	}
	// Handle aliasing
	ptg->copy_value (lhs, rhs);

}


