
#include "process_ir/debug.h"

#include "Def_use.h"
#include "Set.h"

using namespace MIR;
using namespace std;

/*
 * SSA-web. 
 *
 * For now, use the SSA-web (which doesnt actually rely on SSA form, nor is
 * it built during it) both for getting into SSA form, and for creating the
 * SSA web.
 */


Def_use_web::Def_use_web ()
: def_use_chains (&variable_name_ptr_comparison)
, use_def_chains (&variable_name_ptr_comparison)
{
}

#if 0
VARIABLE_NAME_list*
Def_use_web::get_bb_defs (Basic_block* bb)
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	// Go through the use-def result, finding those who's BB == BB
	VARIABLE_NAME* key;
	SSA_edge_list edge_list;
	foreach (tie (key, edge_list), use_def_chains)
	{
		foreach (SSA_edge* edge, edge_list)
		{
			assert (0);
/*			if (edge->bb == bb)
			{
				// Dont insert the key itself, it may be the wrong var_name.
				result->push_back (edge->variable_name);
			}
*/		}
	}
	return result;
}

VARIABLE_NAME_list*
Def_use_web::get_bb_uses (Basic_block* bb)
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	// Go through the def-use result, finding those who's BB == BB
	VARIABLE_NAME* key;
	SSA_edge_list edge_list;
	foreach (tie (key, edge_list), def_use_chains)
	{
		foreach (SSA_edge* edge, edge_list)
		{
			assert (0);
/*			if (edge->bb == bb)
			{
				// Dont insert the key itself, it may be the wrong var_name.
				result->push_back (edge->variable_name);
			}
*/		}
	}

	return result;
}

SSA_edge_list*
Def_use_web::get_bb_use_edges (Basic_block* bb)
{
	SSA_edge_list* result = new SSA_edge_list;

	// Go through the def-use result, finding those who's BB == BB
	VARIABLE_NAME* key;
	SSA_edge_list edge_list;
	foreach (tie (key, edge_list), def_use_chains)
		foreach (SSA_edge* edge, edge_list)
			if (edge->bb == bb)
				result->push_back (edge);

	return result;
}

SSA_edge_list*
Def_use_web::get_var_uses (MIR::VARIABLE_NAME* def)
{
	// Its possible to have defs without uses.
	if (def_use_chains.find (def) == def_use_chains.end ())
		return new SSA_edge_list ();

	return &def_use_chains[def];
}

bool
Def_use_web::has_def (VARIABLE_NAME* use)
{
	return use_def_chains[use].size () == 1;
}

SSA_edge*
Def_use_web::get_var_def (MIR::VARIABLE_NAME* use)
{
	// every use must have exactly 1 def (in SSA form). (Uninitialized
	// variables can be identified using Def_use_web::has_def (use);
	assert (use_def_chains[use].size() == 1);

	// every ssa_edge must have a VARIABLE_NAME
	assert (use_def_chains[use].front()->variable_name);
	return use_def_chains[use].front ();
}

#endif

void
Def_use_web::add_use (MIR::Rvalue* def, SSA_op* use)
{
	if (isa<VARIABLE_NAME> (def))
		add_use (dyc<VARIABLE_NAME> (def), use);
}

// TODO: do we need the Edges, or is it explicit enough without them??

void
Def_use_web::add_use (MIR::VARIABLE_NAME* def, SSA_op* use)
{
	SSA_edge* edge = new SSA_edge (def, use);
	edge->variable_name = def;
	def_use_chains[def].push_back (edge);

	DEBUG ("Adding a def_use edge from ");
	debug (def);
	DEBUG ("to ")
	use->dump ();
	DEBUG (endl);
}

void
Def_use_web::add_def (MIR::VARIABLE_NAME* use, SSA_op* def)
{
	SSA_edge* edge = new SSA_edge (use, def);

	// When used on pre-SSA form, there can be many defs.
	use_def_chains[use].push_back (edge);

	DEBUG ("Adding a use_def edge from ");
	debug (use);
	DEBUG ("to ")
	def->dump ();
	DEBUG (endl);
}

void
Def_use_web::visit_entry_block (Entry_block* bb)
{
	foreach (Formal_parameter* param, *bb->method->signature->formal_parameters)
		add_def (param->var->variable_name, new SSA_formal (bb));
}

void
Def_use_web::visit_branch_block (Branch_block* bb)
{
	add_use (bb->branch->variable_name, new SSA_branch (bb));
}

void
Def_use_web::visit_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
{
	foreach (Rvalue* use, *bb->get_phi_args (phi_lhs))
		add_use (use, new SSA_phi (bb, phi_lhs));

	add_def (phi_lhs, new SSA_phi (bb, phi_lhs));
}

void
Def_use_web::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	add_use (in->lhs, new SSA_stmt (bb));
	add_use (in->rhs, new SSA_stmt (bb));
	add_use (in->index, new SSA_stmt (bb));
}

void
Def_use_web::visit_assign_field (Statement_block*, MIR::Assign_field * in)
{
	assert (0);
}

void
Def_use_web::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	add_def (in->lhs, new SSA_stmt (bb));
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
Def_use_web::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	add_use (in->array, new SSA_stmt (bb));
}

void
Def_use_web::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	add_use (in->array, new SSA_stmt (bb));
}

void
Def_use_web::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	add_use (in->array, new SSA_stmt (bb));
}

void
Def_use_web::visit_global (Statement_block* bb, MIR::Global* in)
{
	// For SSA creation, this is a def. For later, probably a virtual use too?
	if (isa<VARIABLE_NAME> (in->variable_name))
		add_def (dyc<VARIABLE_NAME> (in->variable_name), new SSA_stmt (bb));
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
Def_use_web::visit_return (Statement_block* bb, MIR::Return* in)
{
	add_use (in->variable_name, new SSA_stmt (bb));
}

void
Def_use_web::visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
{
	add_use (in->use, new SSA_stmt (bb));
	add_def (in->def, new SSA_stmt (bb));
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
Def_use_web::visit_unset (Statement_block* bb, MIR::Unset* in)
{
	assert (in->target == NULL);
	assert (in->array_indices->size () == 0);
	assert (isa<VARIABLE_NAME> (in->variable_name));

	add_def (dyc<VARIABLE_NAME> (in->variable_name), new SSA_stmt (bb));
}

/*
 * Exprs
 */

void
Def_use_web::visit_array_access (Statement_block* bb, Array_access* in)
{
	add_use (in->variable_name, new SSA_stmt (bb));
	add_use (in->index, new SSA_stmt (bb));
}

void
Def_use_web::visit_bin_op (Statement_block* bb, Bin_op* in)
{
	add_use (in->left, new SSA_stmt (bb));
	add_use (in->right, new SSA_stmt (bb));
}

void
Def_use_web::visit_cast (Statement_block* bb, Cast* in)
{
	add_use (in->variable_name, new SSA_stmt (bb));
}

void
Def_use_web::visit_constant (Statement_block* bb, Constant* in)
{
}

void
Def_use_web::visit_field_access (Statement_block* bb, Field_access* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_get_key (Statement_block* bb, Foreach_get_key* in)
{
	add_use (in->array, new SSA_stmt (bb));
}

void
Def_use_web::visit_foreach_get_val (Statement_block* bb, Foreach_get_val* in)
{
	add_use (in->array, new SSA_stmt (bb));
}

void
Def_use_web::visit_foreach_has_key (Statement_block* bb, Foreach_has_key* in)
{
	add_use (in->array, new SSA_stmt (bb));
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
		add_use (param->rvalue, new SSA_stmt (bb));
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
	add_use (in->variable_name, new SSA_stmt (bb));
}

void
Def_use_web::visit_variable_name (Statement_block* bb, VARIABLE_NAME* in)
{
	add_use (in, new SSA_stmt (bb));
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


