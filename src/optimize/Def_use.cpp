
#include "boost/tuple/tuple.hpp"

#include "process_ir/debug.h"

#include "Def_use.h"
#include "Set.h"
#include "ssa/Virtual_variable.h"


using namespace MIR;
using namespace std;
using namespace boost;

/*
 * SSA-web. 
 *
 * For now, use the SSA-web (which doesnt actually rely on SSA form, nor is
 * it built during it) both for getting into SSA form, and for creating the
 * SSA web.
 */


SSA_edge::SSA_edge (VARIABLE_NAME* var, SSA_op* op)
: variable_name (var)
, op (op)
{
}

void
SSA_edge::dump ()
{
	// TODO: mention if its a use or a def?
	DEBUG ("Edge from " << *variable_name->get_ssa_var_name () << ": ");
	op->dump ();
}


Def_use_web::Def_use_web (Set* aliases)
: def_use_chains (&variable_name_ptr_comparison)
, use_def_chains (&variable_name_ptr_comparison)
, aliases (aliases)
{
}

/*
 * We want to avoid maintaining two separate versions of the Def-use-web -
 * one in this class, and one implicitly through the SSA-form. So we run the
 * entire update lazily before get_defs or get_uses is called. After that,
 * this is a performance problem, but the results are correct. */
SSA_op_list*
Def_use_web::get_defs (VARIABLE_NAME* use, int flags)
{
	SSA_op_list* result = new SSA_op_list;

	foreach (SSA_edge* edge, use_def_chains [use])
		result->push_back (edge->op);

	return result;
}

SSA_op_list*
Def_use_web::get_uses (VARIABLE_NAME* def, int flags)
{
	// Its possible to have defs without uses.
	if (!def_use_chains.has (def))
		return new SSA_op_list ();

	SSA_op_list* result = new SSA_op_list;
	foreach (SSA_edge* edge, def_use_chains[def])
	{
		if (edge->op->type_flag & flags)
			result->push_back (edge->op);
	}
	return result;
}


SSA_stmt*
Def_use_web::get_def_stmt (VARIABLE_NAME* use)
{
	assert (has_def (use));
	SSA_op_list* defs = get_defs (use, SSA_STMT);

	assert (defs->size() < 2);
	if (defs->size() == 1)
		return dyc<SSA_stmt> (defs->front ());
	else
	{
		assert (0);
		return NULL;
	}
}

bool
Def_use_web::has_def (VARIABLE_NAME* use)
{
	return use_def_chains[use].size () == 1;
}



VARIABLE_NAME_list*
Def_use_web::get_block_defs (Basic_block* bb, int flags)
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	// Go through the use-def result, finding those who's BB == BB
	VARIABLE_NAME* key;
	SSA_edge_list edge_list;
	foreach (tie (key, edge_list), use_def_chains)
	{
		foreach (SSA_edge* edge, edge_list)
		{
			if ((edge->op->type_flag & flags) // filter based on flags
				&& edge->op->get_bb () == bb)
			{
				// Dont insert the key itself, it may be a different var_name
				// with the same value, but we return exact var_name.
				result->push_back (edge->variable_name);
			}
		}
	}
	return result;

}

VARIABLE_NAME_list*
Def_use_web::get_block_uses (Basic_block* bb, int flags)
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	// Go through the use-def result, finding those who's BB == BB
	VARIABLE_NAME* key;
	SSA_edge_list edge_list;
	foreach (tie (key, edge_list), def_use_chains)
	{
		foreach (SSA_edge* edge, edge_list)
		{
			if ((edge->op->type_flag & flags) // filter based on flags
				&& edge->op->get_bb () == bb)
			{
				// Dont insert the key itself, it may be the wrong var_name.
				result->push_back (edge->variable_name);
			}
		}
	}
	return result;

}


/*
 * Calculate the def-use web
 */
void
Def_use_web::add_use (MIR::Rvalue* def, SSA_op* use, bool add_mu)
{
	if (isa<VARIABLE_NAME> (def))
		add_use (dyc<VARIABLE_NAME> (def), use, add_mu);
}

void
Def_use_web::add_use (MIR::VARIABLE_NAME* def, SSA_op* use, bool add_mu)
{
	SSA_edge* edge = new SSA_edge (def, use);
	edge->variable_name = def;
	def_use_chains[def].push_back (edge);

	DEBUG ("Adding a def_use edge from ");
	debug (def);
	DEBUG ("to ")
	use->dump ();
	DEBUG (endl);

	if (add_mu)
		add_mus (use->get_bb(), def);
}

void
Def_use_web::add_def (MIR::VARIABLE_NAME* use, SSA_op* def, bool add_chi)
{
	SSA_edge* edge = new SSA_edge (use, def);

	// When used on pre-SSA form, there can be many defs.
	use_def_chains[use].push_back (edge);

	DEBUG ("Adding a use_def edge from ");
	debug (use);
	DEBUG ("to ")
	def->dump ();
	DEBUG (endl);

	if (add_chi)
		add_chis (def->get_bb (), use);
}

void
Def_use_web::add_mus (Basic_block* bb, VARIABLE_NAME* use)
{
	// TODO: remove mu and chis from the BBs. Instead, just make them SSA_ops.
	// XXX: But, if we do that, how do we 'remove' the CHI and MU statements
	// from the CFG? We do throw them away after each optimization, but do we
	// actually want to remove CHIs via DCE? Why?
	//
	// For now: add the chi/mu to the BB, and also add a SSA_mu/SSA_chi to the
	// use_def info.

	if (aliases->has (use))
		foreach (VARIABLE_NAME* alias, *aliases)
			if (!alias->equals (use))
			{
				bb->add_mu_node (alias);
				add_use (alias, new SSA_mu (bb, alias), false);
			}
}

void
Def_use_web::add_chis (Basic_block* bb, VARIABLE_NAME* def)
{
	// TODO: what about the use?
	if (aliases->has (def))
		foreach (VARIABLE_NAME* alias, *aliases)
			if (!alias->equals (def))
			{
				VARIABLE_NAME* clone = alias->clone ();
				bb->add_chi_node (alias, clone);
				add_def (alias, new SSA_chi (bb, alias, clone), false);
				add_use (clone, new SSA_chi (bb, alias, clone), false);
			}
}



void
Def_use_web::visit_entry_block (Entry_block* bb)
{
	foreach (Formal_parameter* param, *bb->method->signature->formal_parameters)
		add_def (param->var->variable_name, new SSA_formal (bb));
}

void
Def_use_web::visit_exit_block (Exit_block* bb)
{
	foreach (Formal_parameter* param, *bb->method->signature->formal_parameters)
		// TODO not really a formal. Need SSA_EXIT?
		add_use (param->var->variable_name, new SSA_formal (bb));
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
Def_use_web::visit_chi_node (Basic_block* bb, VARIABLE_NAME* lhs, VARIABLE_NAME* rhs)
{
	assert (aliases->size () == 0);
	add_def (lhs, new SSA_chi (bb, lhs, rhs));
	add_use (rhs, new SSA_chi (bb, lhs, rhs));
}

void
Def_use_web::visit_mu_node (Basic_block* bb, VARIABLE_NAME* rhs)
{
	assert (aliases->size () == 0);
	add_use (rhs, new SSA_mu (bb, rhs));
}

void
Def_use_web::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	add_use (in->lhs, new SSA_stmt (bb));
	add_use (in->rhs, new SSA_stmt (bb));
	add_use (in->index, new SSA_stmt (bb));
	add_def (get_virtual (in), new SSA_stmt (bb));
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
	// For SSA creation, this is a def.
	if (isa<VARIABLE_NAME> (in->variable_name))
		add_def (dyc<VARIABLE_NAME> (in->variable_name), new SSA_stmt (bb), false);
	else
		phc_TODO (); // global var-var!
}

void
Def_use_web::visit_pre_op (Statement_block*, MIR::Pre_op* in)
{
	assert (0);
}

void
Def_use_web::visit_assign_next (Statement_block*, MIR::Assign_next* in)
{
	assert (0);
}

void
Def_use_web::visit_return (Statement_block* bb, MIR::Return* in)
{
	// what does the Chow paper say about return values? we need a mu
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

	// Virtuals are intentionally created using an SSA_stmt. Chis and mus are
	// indirect, but virtuals do not represent indirect variables.

	// TODO: assignments to and uses of virtuals do not appear in the graphviz
	// graph. 
	add_use (get_virtual (in), new SSA_stmt (bb));
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

	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		assert (!param->is_ref);
		if (VARIABLE_NAME* var = dynamic_cast<VARIABLE_NAME*> (param->rvalue))
		{
			add_use (var, new SSA_stmt (bb));

			// TODO: use embed and interprocedural analysis to get precise
			// results.
		
			// Note the potential may-def
			add_chis (bb, var);
		}
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
