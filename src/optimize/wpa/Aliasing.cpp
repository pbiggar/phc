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

#include "Aliasing.h"
#include "Points_to.h"
#include "Whole_program.h"
#include "CCP.h"
#include "optimize/SCCP.h"
#include "Optimization_transformer.h"

using namespace MIR;
using namespace boost;
using namespace std;

Aliasing::Aliasing (Whole_program* wp)
: wp (wp)
{
	ptg = new Points_to;
	transformer = new Optimization_transformer (this);
}


void
Aliasing::use_summary_results (Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs)
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
Aliasing::forward_bind (Basic_block* context, CFG* callee_cfg, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	string callee_ns = *callee_cfg->method->signature->method_name->value;
	string caller_ns;
	if (context) 
		caller_ns = *context->cfg->method->signature->method_name->value;

	// Give the CFG access to the PTG results
	callee_cfg->in_ptgs = &in_ptgs;
	callee_cfg->out_ptgs = &out_ptgs;

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
			// $fp =& $ap;
			set_reference (context,
					VN (callee_ns, fp->var->variable_name),
					VN (caller_ns, dyc<VARIABLE_NAME> (ap->rvalue)));
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

	// Store results in the entry block
	out_ptgs[callee_cfg->get_entry_bb ()->ID] = ptg->clone ();
	in_ptgs[callee_cfg->get_entry_bb ()->ID] = ptg->clone ();
	dump (callee_cfg->get_entry_bb ());
}

void
Aliasing::backward_bind (Basic_block* context, CFG* callee_cfg)
{
	if (callee_cfg->method->is_main ())
		return;

	ptg->close_scope (*callee_cfg->method->signature->method_name->value);

	// TODO: we need to handle returns for all the analyses, not just here
}

bool
Aliasing::analyse_block (Basic_block* bb)
{
	DEBUG ("Analysing BB: " << bb->ID);
	string name;
	WPA* wpa;

	// Merge results from predecessors
	foreach (tie (name, wpa), wp->analyses)
		wpa->pull_results (bb);

	// TODO: we really need to use pull_results and aggregate_results, etc.
	// But for now just store a clone of the graph.
	in_ptgs[bb->ID] = ptg->clone ();
	
	// Do the aliasing (and hence other analyses)
	visit_block (bb);

	// TODO: see comment at in_ptgs
	out_ptgs[bb->ID] = ptg->clone ();


	// Create OUT sets from the results 
	foreach (tie (name, wpa), wp->analyses)
		wpa->aggregate_results (bb);


	// Dump
	dump(bb);


	// Calculate fix-point
	bool changed = false;
	foreach (tie (name, wpa), wp->analyses)
		changed |= wpa->solution_changed (bb);


	return changed;
}

void
Aliasing::apply_results (Basic_block* bb)
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

void
Aliasing::dump (Basic_block* bb)
{
	CHECK_DEBUG();
	out_ptgs[bb->ID]->dump_graphviz (s(lexical_cast<string> (bb->ID)));

	string name;
	WPA* wpa;
	foreach (tie (name, wpa), wp->analyses)
		wpa->dump (bb);
}




/*
 * Analysis
 */

void
Aliasing::visit_global (Statement_block* bb, MIR::Global* in)
{
	if (bb->cfg->method->is_main ())
		return;

	if (isa<Variable_variable> (in->variable_name))
		phc_TODO ();

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in->variable_name);
	set_reference (bb,
			VN (NAME (bb), var_name),
			VN ("__MAIN__", var_name));
}


void
Aliasing::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
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
			Array_access* aa = dyc<Array_access> (in->rhs);
			if (in->is_ref)
			{
				// TODO - this genericity is needed both ways
				set_indirect_reference (bb, lhs,
					VN (NAME (bb), aa->variable_name),
					VN (NAME (bb), dyc<VARIABLE_NAME> (aa->index)));
			}
			else
				phc_TODO ();
			return;
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
Aliasing::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	if (isa<New> (in->expr))
		handle_new (bb, dyc<New> (in->expr), NULL);
	else
		handle_method_invocation (bb, dyc<Method_invocation> (in->expr), NULL);
}

void
Aliasing::handle_method_invocation (Statement_block* bb, MIR::Method_invocation* in, MIR::VARIABLE_NAME* lhs)
{
	wp->invoke_method (in, bb, lhs);
}

void
Aliasing::handle_new (Statement_block* bb, MIR::New* in, MIR::VARIABLE_NAME* lhs)
{
	phc_TODO ();
}



/*
 * Update the Points-to solution, and interface with other analyses.
 */


void
Aliasing::set_reference (Basic_block* bb, Index_node* lhs, Index_node* rhs)
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
Aliasing::set_scalar_value (Basic_block* bb, Index_node* lhs, Literal* lit)
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
Aliasing::copy_value (Basic_block* bb, Index_node* lhs, Index_node* rhs)
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


// Note that INDEX is not the index of STORAGE. INDEX points to a set values that may index STORAGE.
void
Aliasing::set_indirect_reference (Basic_block* bb, Index_node* lhs, Index_node* storage, Index_node* index)
{
	// Possible configurations we must deal with:
	//		- we may not know index
	//		- we may know some values of the index
	//		- we may know the exact value of the index
	//		- we may know a set of values for the index, which are all the same
	//		- the index (or one of the possible values) may have an unknown
	//		type, necesitating a call to __get or __toString
	//
	//		- the storage node may have an unknown type, requiring a call to
	//		__set
	//		- the storage node may have an unknown value
	//		- 1 or more possible values may be scalars
	//
	//		in total:
	//			weak typing
	//			dynamic typing

	// If storage has only 1 storage node, OK.
	Storage_node_list* stores = ptg->get_points_to (storage, PTG_ALL);
	if (stores->size () != 1)
		phc_TODO ();
	
	// If index has only 1 possible value, OK (and its a scalar)
	if (ptg->get_points_to (index, PTG_ALL)->size () != 0)
		phc_TODO ();

	Lattice_cell* result = wp->ccp->ins[bb->ID][index->get_unique_name ()];
	if (result == BOTTOM || result == TOP)
		phc_TODO ();

	// TODO: this isnt quite right, we need to cast to a string.
	string name = *dyc<Literal_cell> (result)->value->get_value_as_string ();

	
	Index_node* rhs = IN (stores->front()->name, name);
	set_reference (bb, lhs, rhs);
}

