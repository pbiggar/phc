
#include "process_ir/debug.h"

#include "Def_use.h"
#include "MIR_visitor.h"

using namespace MIR;

class Def_use_visitor : public MIR::Visitor 
{
public:
	Set* defs;
	Set* uses;
	bool handled;
public:
	Def_use_visitor ()
	{
		defs = new Set;
		uses = new Set;
		handled = false;
	}

	void use (Rvalue* in)
	{
		if (isa<VARIABLE_NAME> (in))
			uses->insert (dyc<VARIABLE_NAME> (in));
	}

	void def (VARIABLE_NAME* in)
	{
		defs->insert (in);
	}

	void pre_pre_op (Pre_op* in)
	{
		// should be conveted to SSA_pre_op
		assert (0);
	}

	void pre_actual_parameter (Actual_parameter* in)
	{
		use (in->rvalue);
		handled = true;
	}

	void pre_ssa_pre_op (SSA_pre_op* in)
	{
		use (in->use);
		def (in->def);
		handled = true;
	}

	void pre_assign_var (Assign_var* in)
	{
		def (in->lhs);
		if (isa<VARIABLE_NAME> (in->rhs) || isa<Literal> (in->rhs))
			handled = true;
	}

	void pre_bin_op (Bin_op* in)
	{
		use (in->left);
		use (in->right);
		handled = true;
	}

	void pre_unary_op (Unary_op* in)
	{
		use (in->variable_name);
		handled = true;
	}

	void pre_global (Global* in)
	{
		
		if (VARIABLE_NAME* vn = dynamic_cast<VARIABLE_NAME*> (in->variable_name))
			def (vn);
		else
		{
			// what's defined here?
			use (dyc<Variable_variable> (in)->variable_name);
		}

		handled = true;
	}

	/* Leave this in until this works */
	void post_statement (Statement* in)
	{
		if (!handled)
		{
			debug (in);
			xdebug (in);
		}
		assert (handled);
	}
};

/* There return the uses and defs to turn into SSA form. They are not useful
 * for SSA webs (SSA def-use or use-edf chains).
 */
Set*
Def_use::get_defs (Statement* in)
{
	Def_use_visitor* duv = new Def_use_visitor;
	in->visit (duv);
	return duv->defs;
}

Set*
Def_use::get_uses (Statement* in)
{
	Def_use_visitor* duv = new Def_use_visitor;
	in->visit (duv);
	return duv->uses;
}

/*
 * Def-use chains. These are slightly different def-use chains, since they
 * work on SSA form.
 */

#include "Set.h"

Def_use_web::Def_use_web ()
: def_use_chains (&variable_name_ptr_comparison)
, use_def_chains (&variable_name_ptr_comparison)
{
}

SSA_edge_list*
Def_use_web::get_def_use_edges (MIR::VARIABLE_NAME* def)
{
	// Its possible to have defs without uses.
	if (def_use_chains.find (def) == def_use_chains.end ())
		return new SSA_edge_list ();

	return def_use_chains[def];
}

SSA_edge*
Def_use_web::get_use_def_edges (MIR::VARIABLE_NAME* use)
{
	assert (use_def_chains[use]); // every use must have a def
	return use_def_chains[use];
}


void
Def_use_web::add_def_use_edge (MIR::VARIABLE_NAME* def, SSA_edge* use)
{
	if (def_use_chains[def] == NULL)
		def_use_chains[def] = new SSA_edge_list (use);
	else
		def_use_chains[def]->push_back (use);
}

void
Def_use_web::add_use_def_edge (MIR::VARIABLE_NAME* use, SSA_edge* def)
{
	assert (use_def_chains[use] == NULL);
	use_def_chains[use] = def;
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
	visit_expr (in->rhs);
}

void
Def_use_web::visit_assign_var_var (Statement_block*, MIR::Assign_var_var* in)
{
	assert (0);
}

void
Def_use_web::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (in->expr);
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
Def_use_web::visit_global (Statement_block*, MIR::Global* in)
{
	// Is this a use or a def?
	// TODO dont need this now, come back later.
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
Def_use_web::visit_array_access (Array_access* in)
{
	assert (0);
}

void
Def_use_web::visit_bin_op (Bin_op* in)
{
//	add_def_use_edge (in->left, new SSA_edge (bb));
//	add_def_use_edge (in->right, new SSA_edge (bb));
}

void
Def_use_web::visit_cast (Cast* in)
{
	assert (0);
}

void
Def_use_web::visit_constant (Constant* in)
{
	assert (0);
}

void
Def_use_web::visit_field_access (Field_access* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_get_key (Foreach_get_key* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_get_val (Foreach_get_val* in)
{
	assert (0);
}

void
Def_use_web::visit_foreach_has_key (Foreach_has_key* in)
{
	assert (0);
}

void
Def_use_web::visit_instanceof (Instanceof* in)
{
	assert (0);
}

void
Def_use_web::visit_isset (Isset* in)
{
	assert (0);
}

void
Def_use_web::visit_method_invocation (Method_invocation* in)
{
	assert (0);
}

void
Def_use_web::visit_new (New* in)
{
	assert (0);
}

void
Def_use_web::visit_param_is_ref (Param_is_ref* in)
{
	assert (0);
}

void
Def_use_web::visit_unary_op (Unary_op* in)
{
	assert (0);
}

void
Def_use_web::visit_variable_name (VARIABLE_NAME* in)
{
	assert (0);
}

void
Def_use_web::visit_variable_variable (Variable_variable* in)
{
	assert (0);
}
