
#include "process_ir/debug.h"

#include "Def_use.h"
#include "Set.h"

using namespace MIR;
using namespace std;

/*
 * SSA-web. 
 *
 * For now, use the SSA-web (which doesnt actually rely on SSA form, nor is it
 * built during it) both for getting into SSA form, and for creating the SSA
 * web.
 */


Def_use_web::Def_use_web ()
: def_use_chains (&variable_name_ptr_comparison)
, use_def_chains (&variable_name_ptr_comparison)
{
}

Set*
Def_use_web::get_defs (Basic_block* bb)
{
	Set* result = new Set;

	// Go through the use-def result, finding those who's BB == BB
	pair<VARIABLE_NAME*, SSA_edge_list> pair;
	foreach (pair, use_def_chains)
	{
		foreach (SSA_edge* edge, pair.second)
		{
			assert (edge->which != SSA_edge::PHI);

			// Dont insert the key, it may be the wrong var_name.
			if (edge->bb == bb)
				result->insert (edge->variable_name);
		}
	}
	return result;
}

Set*
Def_use_web::get_uses (Basic_block* bb)
{
	Set* result = new Set;

	// Go through the def-use result, finding those who's BB == BB
	pair<VARIABLE_NAME*, SSA_edge_list> pair;
	foreach (pair, def_use_chains)
	{
		foreach (SSA_edge* edge, pair.second)
		{
			assert (edge->which != SSA_edge::PHI);

			// Dont insert the key, it may be the wrong var_name.
			if (edge->bb == bb)
				result->insert (edge->variable_name);
		}
	}

	return result;
}

SSA_edge_list*
Def_use_web::get_def_use_edges (MIR::VARIABLE_NAME* def)
{
	// Its possible to have defs without uses.
	if (def_use_chains.find (def) == def_use_chains.end ())
		return new SSA_edge_list ();

	return &def_use_chains[def];
}

SSA_edge*
Def_use_web::get_use_def_edge (MIR::VARIABLE_NAME* use)
{
	// every use must have exactly 1 def (in SSA form).
	assert (use_def_chains[use].size() == 1);

	// every ssa_edge must have a VARIABLE_NAME
	assert (use_def_chains[use].front()->variable_name);
	return use_def_chains[use].front ();
}

void
Def_use_web::add_def_use_edge (MIR::Rvalue* def, SSA_edge* use)
{
	if (isa<VARIABLE_NAME> (def))
		add_def_use_edge (dyc<VARIABLE_NAME> (def), use);
}

void
Def_use_web::add_def_use_edge (MIR::VARIABLE_NAME* def, SSA_edge* use)
{
	DEBUG ("Adding a def_use edge from ");
	debug (def);
	DEBUG ("to ")
	use->dump ();
	DEBUG (endl);
	
	use->variable_name = def;
	def_use_chains[def].push_back (use);
}

void
Def_use_web::add_use_def_edge (MIR::VARIABLE_NAME* use, SSA_edge* def)
{
	DEBUG ("Adding a use_def edge from ");
	debug (use);
	DEBUG ("to ")
	def->dump ();
	DEBUG (endl);


	def->variable_name = use;

	// When used on pre-SSA form, there can be many defs.
	use_def_chains[use].push_back (def);
}

void
Def_use_web::visit_branch_block (Branch_block* bb)
{
	add_def_use_edge (bb->branch->variable_name, new SSA_edge (bb));
}

void
Def_use_web::visit_phi_node (Basic_block* bb, Phi* phi)
{
	foreach (VARIABLE_NAME* use, *phi->get_args ())
		add_def_use_edge (use, new SSA_edge (phi));

	add_use_def_edge (phi->lhs, new SSA_edge (phi));
}

void
Def_use_web::visit_assign_array (Statement_block*, MIR::Assign_array* in)
{
	assert (0);
}

void
Def_use_web::visit_assign_field (Statement_block*, MIR::Assign_field * in)
{
	assert (0);
}

void
Def_use_web::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	add_use_def_edge (in->lhs, new SSA_edge (bb));
	visit_expr (bb, in->rhs);
}

void
Def_use_web::visit_assign_var_var (Statement_block*, MIR::Assign_var_var* in)
{
	assert (0);
}

void
Def_use_web::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

void
Def_use_web::visit_foreach_end (Statement_block*, MIR::Foreach_end* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_next (Statement_block*, MIR::Foreach_next* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_reset (Statement_block*, MIR::Foreach_reset* in)
{
	assert (0);
}

void
Def_use_web::visit_global (Statement_block* bb, MIR::Global* in)
{
	// For SSA creation, this is a def. For later, probably a virtual use too?
	if (isa<VARIABLE_NAME> (in->variable_name))
		add_use_def_edge (dyc<VARIABLE_NAME> (in->variable_name), new SSA_edge (bb));
}

void
Def_use_web::visit_param_is_ref (Statement_block*, MIR::Param_is_ref* in)
{
	assert (0);
}

void
Def_use_web::visit_pre_op (Statement_block*, MIR::Pre_op* in)
{
	assert (0);
}

void
Def_use_web::visit_push_array (Statement_block*, MIR::Push_array* in)
{
	assert (0);
}

void
Def_use_web::visit_return (Statement_block*, MIR::Return* in)
{
	assert (0);
}

void
Def_use_web::visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
{
	add_def_use_edge (in->use, new SSA_edge (bb));
	add_use_def_edge (in->def, new SSA_edge (bb));
}

void
Def_use_web::visit_static_declaration (Statement_block*, MIR::Static_declaration* in)
{
	assert (0);
}

void
Def_use_web::visit_throw (Statement_block*, MIR::Throw* in)
{
	assert (0);
}

void
Def_use_web::visit_try (Statement_block*, MIR::Try* in)
{
	assert (0);
}

void
Def_use_web::visit_unset (Statement_block*, MIR::Unset* in)
{
	assert (0);
}

/*
 * Exprs
 */

void
Def_use_web::visit_array_access (Statement_block* bb, Array_access* in)
{
	assert (0);
}

void
Def_use_web::visit_bin_op (Statement_block* bb, Bin_op* in)
{
	add_def_use_edge (in->left, new SSA_edge (bb));
	add_def_use_edge (in->right, new SSA_edge (bb));
}

void
Def_use_web::visit_cast (Statement_block* bb, Cast* in)
{
	assert (0);
}

void
Def_use_web::visit_constant (Statement_block* bb, Constant* in)
{
	assert (0);
}

void
Def_use_web::visit_field_access (Statement_block* bb, Field_access* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_get_key (Statement_block* bb, Foreach_get_key* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_get_val (Statement_block* bb, Foreach_get_val* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_has_key (Statement_block* bb, Foreach_has_key* in)
{
	assert (0);
}

void
Def_use_web::visit_instanceof (Statement_block* bb, Instanceof* in)
{
	assert (0);
}

void
Def_use_web::visit_isset (Statement_block* bb, Isset* in)
{
	assert (0);
}

void
Def_use_web::visit_method_invocation (Statement_block* bb, Method_invocation* in)
{
	if (isa<Variable_method> (in->method_name))
		assert (0);

	// TODO isnt this a potential def
	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		assert (!param->is_ref); // TODO
		add_def_use_edge (param->rvalue, new SSA_edge (bb));
		// what about virtual defs
	}
		
}

void
Def_use_web::visit_new (Statement_block* bb, New* in)
{
	assert (0);
}

void
Def_use_web::visit_unary_op (Statement_block* bb, Unary_op* in)
{
	add_def_use_edge (in->variable_name, new SSA_edge (bb));
}

void
Def_use_web::visit_variable_name (Statement_block* bb, VARIABLE_NAME* in)
{
	add_def_use_edge (in, new SSA_edge (bb));
}

void
Def_use_web::visit_variable_variable (Statement_block* bb, Variable_variable* in)
{
	assert (0);
}


void
Def_use_web::dump ()
{
	CHECK_DEBUG ();

	cdebug << "Use-def web (" << use_def_chains.size() << "):\n";
	pair<VARIABLE_NAME*, SSA_edge_list> p;
	foreach (p, use_def_chains)
	{
		cdebug << "SSA edges for ";
		debug (p.first);

		foreach (SSA_edge* edge, p.second)
		{
			edge->dump ();
		}
		cdebug << endl;
	}

	cdebug << "Def-use web (" << def_use_chains.size() << "):\n";
	foreach (p, def_use_chains)
	{
		cdebug << "SSA edges for ";
		debug (p.first);

		foreach (SSA_edge* edge, p.second)
		{
			edge->dump ();
		}
		cdebug << endl;
	}

}

