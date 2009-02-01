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
#include "Callgraph.h"
#include "Def_use.h"
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
Aliasing::use_summary_results (Basic_block* context, Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs)
{
	// TODO: what about functions with callbacks
	wp->callgraph->add_summary_call (context, info);

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
	{
		caller_ns = *context->cfg->method->signature->method_name->value;
		wp->callgraph->add_user_call (context, callee_cfg);
	}

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
					N (callee_ns, fp->var->variable_name),
					N (caller_ns, dyc<VARIABLE_NAME> (ap->rvalue)));
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
	wp->def_use->backward_bind (context, callee_cfg);
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
	{
		wpa->dump (bb);
		cdebug << endl;
	}
}




/*
 * Analysis
 */

void
Aliasing::visit_global (Statement_block* bb, MIR::Global* in)
{
	set_reference (bb,
			N (ST (bb), in->variable_name),
			N ("__MAIN__", in->variable_name));
}


void
Aliasing::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	string ns = ST (bb);
	Name* lhs = N (ns, in->lhs);
	Name* rhs;

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
			phc_TODO ();
			break;

		// Straightforward
		case Array_access::ID:
		case Field_access::ID:
		case VARIABLE_NAME::ID:
		case Variable_variable::ID:
			rhs = N (ns, in->rhs);
			break;

		// Values
		case BOOL::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
			set_scalar_value (bb, lhs, dyc<Literal> (in->rhs));
			return;

		// Need to use analysis results before putting into the graph
		case Foreach_get_key::ID:
		case Foreach_get_val::ID:
		case Foreach_has_key::ID:
		case Cast::ID:
			phc_TODO ();
			break;


		// Interprocedural stuff
		case New::ID:
			handle_new (bb, dyc<New> (in->rhs), in->lhs);
			phc_TODO ();
			break;

		case Method_invocation::ID:
			handle_method_invocation (bb, dyc<Method_invocation> (in->rhs), in->lhs);
			phc_TODO ();
			break;

		default:
			phc_unreachable ();
			break;
	}

	assert (rhs);
	if (in->is_ref)
		set_reference (bb, lhs, rhs);
	else
		copy_value (bb, lhs, rhs);
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
Aliasing::set_reference (Basic_block* bb, Name* nlhs, Name* nrhs)
{
	// We don't need to worry about aliases, as this is killing.
	Index_node_list* lhss = get_named_indices (bb, nlhs);
	Index_node_list* rhss = get_named_indices (bb, nrhs);

	// Send the results to the analyses for all variables which could be
	// overwritten.
	foreach (Index_node* lhs, *lhss)
	{
		foreach (Index_node* rhs, *rhss)
		{
			// Handle LHS itself
			string name;
			WPA* wpa;
			foreach (tie (name, wpa), wp->analyses)
				wpa->set_value_from (bb, lhs->get_unique_name (), rhs->get_unique_name(), DEFINITE);


			// Handle aliasing
			ptg->set_reference (lhs, rhs);
		}
	}
}

void
Aliasing::set_scalar_value (Basic_block* bb, Name* lhs, Literal* lit)
{
	Index_node_list* indices = get_named_indices (bb, lhs);

	// Send the results to the analyses for all variables which could be
	// overwritten.
	foreach (Index_node* index, *indices)
	{
		WPA* wpa;
		string name;
		certainty certainties[] = {POSSIBLE, DEFINITE};
		foreach (certainty cert, certainties)
		{
			Index_node_list* refs = ptg->get_references (index, cert);
			foreach (tie (name, wpa), wp->analyses)
			{
				foreach (Index_node* ref, *refs)
					wpa->set_value (bb, ref->get_unique_name(), lit, cert);
			}
		}

		// Handle LHS itself
		foreach (tie (name, wpa), wp->analyses)
			wpa->set_value (bb, index->get_unique_name (), lit, DEFINITE);

		// Handle aliasing
		ptg->set_scalar_value (index);
	}
}

void
Aliasing::copy_value (Basic_block* bb, Name* nlhs, Name* nrhs)
{
	Index_node_list* lhss = get_named_indices (bb, nlhs);
	Index_node_list* rhss = get_named_indices (bb, nrhs);

	// This is not killing in terms of references, so it assigns to all
	// aliases of lhs.
	WPA* wpa;
	string name;
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty cert, certainties)
	{
		foreach (Index_node* lhs, *lhss)
		{
			Index_node_list* refs = ptg->get_references (lhs, cert);
			foreach (tie (name, wpa), wp->analyses)
			{
				foreach (Index_node* rhs, *rhss)
				{
					foreach (Index_node* ref, *refs)
						wpa->set_value_from (bb, ref->get_unique_name (),
								rhs->get_unique_name (), cert);

					// And for the LHS
					wpa->set_value_from (bb, lhs->get_unique_name (),
							rhs->get_unique_name (), DEFINITE);


					// Handle points-to aliasing
					ptg->copy_value (lhs, rhs);
				}
			}
		}
	}
}

String_list*
Aliasing::get_string_values (Basic_block* bb, Index_node* index)
{
	Lattice_cell* result = wp->ccp->ins[bb->ID][index->get_unique_name ()];

	if (result == BOTTOM || result == TOP)
		phc_TODO ();

	// TODO: this isnt quite right, we need to cast to a string.
	return new String_list (
		dyc<Literal_cell> (result)->value->get_value_as_string ());
}




Index_node_list*
Aliasing::get_named_indices (Basic_block* bb, Name* name)
{
	Indexing* n = dyc<Indexing> (name);


	// Get the set of storage nodes representing the LHS.
	Set<string> lhss;

	if (ST_name* st = dynamic_cast <ST_name*> (n->lhs))
	{
		// 1 named storage node
		lhss.insert (st->name);
	}
	else
	{
		// Lookup the storage nodes indexed by LHS
		foreach (Index_node* st_index, *get_named_indices (bb, n->lhs))
			foreach (Storage_node* pointed_to, *ptg->get_points_to (st_index, PTG_ALL))
				lhss.insert (pointed_to->name);
	}


	// Get the names of the fields of the storage nodes.
	Set<string> rhss;

	if (Index_name* st = dynamic_cast <Index_name*> (n->rhs))
	{
		// 1 named field of the storage nodes
		rhss.insert (st->name);
	}
	else
	{
		// The name of the field must be looked up
		foreach (Index_node* field_index, *get_named_indices (bb, n->rhs))
			foreach (String* value, *get_string_values (bb, field_index))
				rhss.insert (*value);
	}


	// Combine the results
	Index_node_list* result = new Index_node_list;

	foreach (string lhs, lhss)
		foreach (string rhs, rhss)
			result->push_back (new Index_node (lhs, rhs));

	return result;
}

Index_node*
Aliasing::get_named_index (Basic_block* bb, Name* name)
{
	Index_node_list* all = get_named_indices (bb, name);

	// TODO: can this happen
	assert (all->size());

	if (all->size () > 1)
		return NULL;

	return all->front ();
}


/*
 * Name is used to represent the MIR constructs in an abstract way that models
 * all the MIR constructs. A name is a limited combination of Index_ and
 * Storage_nodes which represents a path in the Points_to graph, and as such
 * can represent more than 1 Index_node.
 *
 *
 * For "->" read 'indexed_by"
 *		$a[$i]		(ST -> "a") -> (ST -> "i")
 *		$a				ST -> "a"
 *		$$a			ST -> (ST -> "a")
 *		$a["str"]	(ST -> "a") -> "str"
 *		$a->f			(ST -> "a") -> "f"
 *		$a->$f		(ST -> "a") -> (ST -> "f")
 */

Indexing::Indexing (Name* lhs, Name *rhs) : lhs (lhs), rhs (rhs) {}
ST_name::ST_name (string name) : name (name) {}
Index_name::Index_name (string name) : name (name) {}


// In the context of the symtable st, create a Name for NODE
Name*
N (string symtable, Node* in)
{
	ST_name* st = new ST_name (symtable);

	switch (in->classid ())
	{
		case VARIABLE_NAME::ID:
			return new Indexing (st,
					new Index_name (*dyc<VARIABLE_NAME> (in)->value));

		case Array_access::ID:
		{
			Array_access* aa = dyc<Array_access> (in);

			return new Indexing (
				new Indexing (st, new Index_name (*aa->variable_name->value)),
				N (symtable, aa->index));
		}

		default:
			DEBUG (demangle (in));
			phc_TODO ();
	}
}



