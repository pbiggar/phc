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
#include "CCP.h"
#include "optimize/SCCP.h"

using namespace MIR;
using namespace boost;
using namespace std;

BCCH_aliasing::BCCH_aliasing (Whole_program* wp)
: wp (wp)
{
	ptg = new Points_to;
	transformer = new Optimization_transformer (this);
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

	// Give the CFG access to the PTG results
	callee_cfg->ptgs = &ptgs;

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
	if (callee_cfg->method->is_main ())
		return;

	phc_TODO ();

	// TODO: handle returns

	ptg->close_scope (*callee_cfg->method->signature->method_name->value);
}

bool
BCCH_aliasing::analyse_block (Basic_block* bb)
{
	DEBUG ("Analysing BB: " << bb->ID);
	string name;
	WPA* wpa;

	// Merge results from predecessors
	foreach (tie (name, wpa), wp->analyses)
		wpa->pull_results (bb);

	
	// Do the aliasing (and hence other analyses)
	visit_block (bb);

	// TODO: we really need to use pull_results and aggregate_results, etc.
	// But for now just store a clone of the graph.
	ptgs[bb->ID] = ptg->clone ();


	// Create OUT sets from the results 
	foreach (tie (name, wpa), wp->analyses)
		wpa->aggregate_results (bb);


	// Dump
	dump(bb);
	foreach (tie (name, wpa), wp->analyses)
		wpa->dump (bb);


	// Calculate fix-point
	bool changed = false;
	foreach (tie (name, wpa), wp->analyses)
		changed |= wpa->solution_changed (bb);


	return changed;
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
BCCH_aliasing::dump (Basic_block* bb)
{
	CHECK_DEBUG();
	ptgs[bb->ID]->dump_graphviz (s(lexical_cast<string> (bb->ID)));
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
		Index_node_list* refs = ptg->get_references (lhs, cert);
		foreach (tie (name, wpa), wp->analyses)
		{
			foreach (Index_node* ref, *refs)
				wpa->set_value (bb, ref->get_unique_name(), lit, cert);
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
	// This is not killing in terms of references, so it assigns to all
	// aliases of lhs.
	WPA* wpa;
	string name;
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty cert, certainties)
	{
		Index_node_list* refs = ptg->get_references (lhs, cert);
		foreach (tie (name, wpa), wp->analyses)
		{
			foreach (Index_node* ref, *refs)
				wpa->set_value_from (bb, ref->get_unique_name (),
											rhs->get_unique_name (), cert);
		}
	}
	// And for the LHS
	wpa->set_value_from (bb, lhs->get_unique_name (),
								rhs->get_unique_name (), DEFINITE);


	// Handle points-to aliasing
	ptg->copy_value (lhs, rhs);
}


void
BCCH_aliasing::apply_results (Basic_block* bb)
{
	if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		Statement* old = sb->statement->clone ();

		transformer->visit_block (bb);

		if (sb->statement->equals (old))
			DEBUG ("No changes in BB: " << bb->ID);
		else
			DEBUG ("BB " << bb->ID << " changed");
	}
}



/*
 * Apply the optimization results.
 */
Optimization_transformer::Optimization_transformer (BCCH_aliasing* aliasing)
: aliasing (aliasing)
{
}

void
Optimization_transformer::run (CFG* cfg)
{
}


void
Optimization_transformer::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_assign_field (Statement_block* bb, MIR::Assign_field * in)
{
	phc_TODO ();
}


Rvalue*
Optimization_transformer::get_literal (Basic_block* bb, Rvalue* in)
{
	if (isa<Literal> (in))
		return in;


	string ns = NAME (bb);
	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);

	Index_node* rhs = VN (ns, var_name);
	CCP* ccp = aliasing->wp->ccp;
	Lattice_cell* result = ccp->ins[bb->ID][rhs->get_unique_name ()];

	if (result == BOTTOM)
		return in;

	if (result == TOP)
		return new NIL;

	return dyc<Literal_cell> (result)->value;
}

void
Optimization_transformer::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	string ns = NAME (bb);
	Index_node* lhs = IN (ns, *in->lhs->value);

	// The assignment is by reference. We will be able to remove this later, via DCE.
	if (in->is_ref)
		return;

	// Ignore
	if (isa<Literal> (in->rhs))
		return;

	// TODO: check that there are no implicit operations on the rhs

	if (isa<VARIABLE_NAME> (in->rhs))
		in->rhs = get_literal (bb, dyc<VARIABLE_NAME> (in->rhs));
}

void
Optimization_transformer::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

void
Optimization_transformer::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_global (Statement_block* bb, MIR::Global* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_return (Statement_block* bb, MIR::Return* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_throw (Statement_block* bb, MIR::Throw* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_try (Statement_block* bb, MIR::Try* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_unset (Statement_block* bb, MIR::Unset* in)
{
	phc_TODO ();
}


void
Optimization_transformer::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_bin_op (Statement_block* bb, MIR::Bin_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_bool (Statement_block* bb, MIR::BOOL* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_cast (Statement_block* bb, MIR::Cast* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_constant (Statement_block* bb, MIR::Constant* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_field_access (Statement_block* bb, MIR::Field_access* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_instanceof (Statement_block* bb, MIR::Instanceof* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_int (Statement_block* bb, MIR::INT* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_isset (Statement_block* bb, MIR::Isset* in)
{
	phc_TODO ();
}


void
Optimization_transformer::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	if (!isa<METHOD_NAME> (in->method_name))
		phc_TODO ();

	METHOD_NAME* name = dyc<METHOD_NAME> (in->method_name);

	// TODO: this should get all possible receivers
	
	Method_info* info = Oracle::get_method_info (name->value);

	if (info->has_implementation ())
		phc_TODO ();


	// Update the parameters with constants
	int i = -1;
	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		i++;

		if (isa<Literal> (param->rvalue))
			continue;

		if (!param->is_ref
				&& !info->params->at (i)->pass_by_reference)
		{
			param->rvalue = get_literal (bb, param->rvalue);
		}
	}
}

void
Optimization_transformer::visit_new (Statement_block* bb, MIR::New* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_nil (Statement_block* bb, MIR::NIL* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_real (Statement_block* bb, MIR::REAL* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_string (Statement_block* bb, MIR::STRING* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_unary_op (Statement_block* bb, MIR::Unary_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in)
{
	phc_TODO ();
}
