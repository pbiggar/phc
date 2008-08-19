/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "Live_variable_analysis.h"
#include "Dead_code_elimination.h"
#include "Address_taken.h"
#include "process_ir/General.h"
#include "cmdline.h"

extern struct gengetopt_args_info args_info;

using namespace MIR;

Live_variable_analysis::Live_variable_analysis () 
{
	this->name = s("LVA");
	this->description = s("Live-variable analysis");
}

bool
Live_variable_analysis::pass_is_enabled (Pass_manager* pm)
{
	return args_info.optimize_given;
}


void
Live_variable_analysis::run (IR::PHP_script* ir_script, Pass_manager* pm)
{
	MIR::PHP_script* script = ir_script->as_MIR();
	foreach (Statement* s, *script->statements)
	{
		// TODO we should be optimizing all methods
		if (isa<Method> (s))
		{
			Method* method = dyc<Method> (s);
			CFG* cfg = new CFG ();
			cfg->add_statements (method->statements);
			//		cfg->dump_graphviz (s("BEFORE DCE"));
			visit (cfg);
			Address_taken* at = new Address_taken;
			at->visit (cfg);
			//		cfg->dump_graphviz (s("AFTER LVA"));
			Dead_code_elimination* dce = new Dead_code_elimination;
			dce->visit (cfg);
			//		cfg->dump_graphviz (s("AFTER DCE"));
			method->statements = cfg->get_linear_statements ();
		}
	}
}


void
Live_variable_analysis::transfer_in (Basic_block* bb, list<Basic_block*>*)
{
	Set* old = bb->live_in;

	// IN = (OUT / DEFS) U USES
	bb->live_in = bb->live_out->set_difference (bb->defs)->set_union (bb->uses);

	if (*bb->live_in != *old)
		bb->changed = true;
}

void
Live_variable_analysis::transfer_out (Basic_block* bb, list<Basic_block*>* succs)
{
	// OUT = \/ IN (s), where s in Succs (BB).
	bb->live_out = new Set;
	foreach (Basic_block* succ, *succs)
	{
		bb->live_out = bb->live_out->set_union (succ->live_in);
	}

	// We don't care if the OUT solution changes, unless the IN solution does,
	// as the OUT solution wouldn't propagate.
}

void
use_bottom (Basic_block* bb)
{
	bb->uses->insert_all ();
}

void
use (Basic_block* bb, VARIABLE_NAME* var_name)
{
	bb->uses->insert (var_name->value);
}

void
use (Basic_block* bb, Rvalue* rval)
{
	if (isa<VARIABLE_NAME> (rval))
		use (bb, dyc<VARIABLE_NAME> (rval));
}

void
use (Basic_block* bb, Variable_name* var_name)
{
	if (isa<VARIABLE_NAME> (var_name))
		use (bb, dyc<VARIABLE_NAME> (var_name));
	else
		assert (0); // TODO
}

void
def (Basic_block* bb, VARIABLE_NAME* var_name)
{
	bb->defs->insert (var_name->value);
}


#define DEF(VAR) bb->defs->insert (VAR->value)

void
Live_variable_analysis::visit_branch_block (Branch_block* bb)
{
	use (bb, bb->branch->variable_name);
}

/* Expressions */
void use_expr (Basic_block* bb, Expr* in)
{
	switch(in->classid())
	{
		case BOOL::ID:
		case Constant::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
			// do nothing
			break;

		case Bin_op::ID:
		{
			Bin_op* bin_op = dyc<Bin_op> (in);
			use (bb, bin_op->left);
			use (bb, bin_op->right);
			break;
		}

		case Cast::ID:
			use (bb, dyc<Cast> (in)->variable_name);
			break;

		case Foreach_get_key::ID:
			use (bb, dyc<Foreach_get_key> (in)->array);
			break;

		case Foreach_get_val::ID:
			use (bb, dyc<Foreach_get_val> (in)->array);
			break;

		case Foreach_has_key::ID:
			use (bb, dyc<Foreach_has_key> (in)->array);
			break;

		case Index_array::ID:
		{
			Index_array* ia = dyc<Index_array> (in);
			use (bb, ia->variable_name);
			use (bb, ia->index);
			break;
		}

		case Isset::ID:
		{
			Isset* i = dyc<Isset> (in);
			if (i->target && isa<VARIABLE_NAME> (i->target))
				use (bb, dyc<VARIABLE_NAME> (i->target));

			// If there is a target, then a var-var means a field access, not
			// accessing any variable.
			if (isa<Variable_variable> (i->variable_name))
			{
				if (i->target)
					use (bb, dyc<Variable_variable> (i->variable_name)->variable_name);
				else
					use_bottom (bb);
			}
			else
				use (bb, dyc<VARIABLE_NAME> (i->variable_name));

			foreach (Rvalue* rv, *i->array_indices)
				use (bb, rv);

			break;
		}

		case Instanceof::ID:
			use (bb, dyc<Instanceof> (in)->variable_name);
			break;

		case Method_invocation::ID:
		{
			Method_invocation* mi = dyc<Method_invocation> (in);

			if (isa<VARIABLE_NAME> (mi->method_name))
				assert (0); // TODO

			foreach (Actual_parameter* ap, *mi->actual_parameters)
			{
				VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (ap->rvalue);
				if (var_name)
					use (bb, var_name);
			}
			break;
		}

		case New::ID:
		{
			New* n = dyc<New> (in);

			if (isa<VARIABLE_NAME> (n->class_name))
				assert (0); // TODO

			foreach (Actual_parameter* ap, *n->actual_parameters)
			{
				VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (ap->rvalue);
				if (var_name)
					use (bb, var_name);
			}
			break;
		}

		case Target_expr::ID:
		{
			Target_expr* te = dyc<Target_expr> (in);
			use (bb, te->variable_name);

			if (isa<VARIABLE_NAME> (te->target))
				assert (0); // bottom

			break;
		}

		case Unary_op::ID:
			use (bb, dyc<Unary_op> (in)->variable_name);
			break;

		case VARIABLE_NAME::ID:
			use (bb, dyc<VARIABLE_NAME> (in));
			break;

		case Variable_variable::ID:
			// TODO: bottom
			assert (0);
			break;

		default:
			assert (0);
			break;
	}
}

void
Live_variable_analysis::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	use (bb, in->lhs); // may be defined, but we conservativly say it won't.
	use (bb, in->index);
	use (bb, in->rhs); // cant be defined
}

void
Live_variable_analysis::visit_assign_target (Statement_block* bb, MIR::Assign_target* in)
{
//	use_expr (bb, in->target);
	assert (0); // use (bb, in->lhs);
	use (bb, in->rhs);
}

void
Live_variable_analysis::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	DEF (in->lhs);
	use_expr (bb, in->rhs);
}

void
Live_variable_analysis::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	// We don't know what variable is assigned, so we conservatively say none.
	use (bb, in->rhs);
}

void
Live_variable_analysis::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	use_expr (bb, in->expr);
}

void
Live_variable_analysis::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	use (bb, in->array);
}

void
Live_variable_analysis::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	use (bb, in->array);
}

void
Live_variable_analysis::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	use (bb, in->array);
}

void
Live_variable_analysis::visit_global (Statement_block* bb, MIR::Global* in)
{
	// TODO This might define the variable in some cases. Is that useful?
}

void
Live_variable_analysis::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	use (bb, in->variable_name);
	// Technically, it is also DEF, but it makes no difference.
}

void
Live_variable_analysis::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
	// Nothing used
}

void
Live_variable_analysis::visit_push_array (Statement_block* bb, MIR::Push_array* in)
{
	use (bb, in->lhs);
	use (bb, in->rhs);
}

void
Live_variable_analysis::visit_return (Statement_block* bb, MIR::Return* in)
{
	use_expr (bb, in->expr);
}
void
Live_variable_analysis::visit_static_declaration (Statement_block* sb, MIR::Static_declaration*)
{
	assert (0);
	// TODO
}

void
Live_variable_analysis::visit_try (Statement_block* sb, MIR::Try*)
{
	assert (0);
	// TODO
}

void
Live_variable_analysis::visit_throw (Statement_block* sb, MIR::Throw*)
{
	assert (0);
	// TODO
}

void
Live_variable_analysis::visit_unset (Statement_block* bb, MIR::Unset* in)
{
	if (in->target == NULL
		&& isa<VARIABLE_NAME> (in->variable_name)
		&& in->array_indices->size () == 0)
	{
		def (bb, dyc<VARIABLE_NAME> (in->variable_name));
	}
}

void
Live_variable_analysis::init_block (Basic_block* bb)
{
	bb->defs = new Set();
	bb->uses = new Set();
	bb->live_in = new Set();
	bb->live_out = new Set();
	bb->changed = false;
}

bool
Live_variable_analysis::solution_has_changed (Basic_block* bb)
{
	bool result = bb->changed;
	bb->changed = false;
	return result;
}
