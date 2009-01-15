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

#define NAME(BB) *BB->cfg->method->signature->method_name->value

using namespace MIR;

BCCH_aliasing::BCCH_aliasing (Whole_program* wp)
: WPA (wp)
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
BCCH_aliasing::initialize_function (CFG* caller_cfg, CFG* callee_cfg, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	string caller_ns;
	if (caller_cfg) 
		caller_ns = *caller_cfg->method->signature->method_name->value;

	string callee_ns = *callee_cfg->method->signature->method_name->value;

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
			ptg->set_reference (callee_ns, fp->var->variable_name,
									  caller_ns, dyc<VARIABLE_NAME> (ap->rvalue));
		}
		else
		{
			// $fp = $ap;
			phc_TODO ();
		}
	}

	if (lhs)
	{
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
BCCH_aliasing::finalize_function (CFG* caller_cfg, CFG* callee_cfg)
{
	// TODO: remove return and parameter nodes, and clear away unreachable nodes.
}




void
BCCH_aliasing::visit_global (Statement_block* bb, MIR::Global* in)
{
	// These dont really change anything
	// TODO: these might set a var to NULL, from uninit
	if (bb->cfg->method->is_main ())
		return;

	if (isa<Variable_variable> (in->variable_name))
		phc_TODO ();

	// TODO: this will do for now, but we might want to think about using the
	// __MAIN__ GLOBALS variable (though that can be set, can it not?).
	
	// TODO: a really nice way to handle this would be to consider the global
	// scope to be values in an array called EG(symbol_table). GLOBALS would
	// initially point to this too (though some tricks might be necessary to
	// avoid them both being overwritten if GLOBALS is changed). The same thing
	// could handle the locals array, perhaps named EG(active_symbol_table).
	// This would mean that var-vars and arrays are treated identically.

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in->variable_name);
	ptg->set_reference (NAME (bb), var_name, "__MAIN__", var_name);
}


void
BCCH_aliasing::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	string name = NAME (bb);

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
			if (in->is_ref)
				ptg->set_reference (name, in->lhs, name, dyc<VARIABLE_NAME> (in->rhs));
			else
				ptg->set_value (name, in->lhs, name, dyc<VARIABLE_NAME> (in->rhs));
			break;

		default:
			phc_TODO ();
			break;

		// Simple graph nodes
		case BOOL::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
			assert (!in->is_ref);
			ptg->set_value (name, in->lhs, dyc<Literal> (in->rhs));
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
			// TODO: globals are special
			phc_TODO ();
			break;

		// Interprocedural stuff
		case New::ID:
			handle_new (bb, dyc<New> (in->rhs), in->lhs);
			break;

		case Method_invocation::ID:
			handle_method_invocation (bb, dyc<Method_invocation> (in->rhs), in->lhs);
			break;
	}
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


void BCCH_aliasing::dump ()
{
	CHECK_DEBUG();
	ptg->dump_graphviz (NULL);
}
