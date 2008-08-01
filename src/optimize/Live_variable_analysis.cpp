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
	for_lci (script->statements, Statement, i)
	{
		Method* method = dyc<Method> (*i);
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

#define USE(VAR) bb->uses->insert (VAR->value)
#define DEF(VAR) bb->defs->insert (VAR->value)

void
Live_variable_analysis::visit_branch_block (Branch_block* bb)
{
	USE (bb->branch->variable_name);
}

void
use_variable_name (Basic_block* bb, Variable_name* in)
{
	if (isa<VARIABLE_NAME> (in))
		USE (dyc<VARIABLE_NAME> (in));
	else
		assert (0); // TODO
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
			USE (bin_op->left);
			USE (bin_op->right);
			break;
		}

		case Cast::ID:
			USE (dyc<Cast> (in)->variable_name);
			break;

		case Foreach_get_key::ID:
			USE (dyc<Foreach_get_key> (in)->array);
			break;

		case Foreach_get_val::ID:
			USE (dyc<Foreach_get_val> (in)->array);
			break;

		case Foreach_has_key::ID:
			USE (dyc<Foreach_has_key> (in)->array);
			break;

		case Index_array::ID:
		{
			Index_array* ia = dyc<Index_array> (in);
			USE (ia->variable_name);
			USE (ia->index);
			break;
		}

		case Instanceof::ID:
			USE (dyc<Instanceof> (in)->variable_name);
			break;

		case Method_invocation::ID:
		{
			Method_invocation* mi = dyc<Method_invocation> (in);

			if (isa<VARIABLE_NAME> (mi->method_name))
				assert (0); // TODO

			foreach (Actual_parameter* ap, *mi->actual_parameters)
			{
				use_variable_name (bb, ap->variable_name);
			}
			break;
		}

		case New::ID:
			// TODO
			// TODO class_name?
			assert (0);

		case Target_expr::ID:
		{
			Target_expr* te = dyc<Target_expr> (in);
			use_variable_name (bb, te->variable_name);

			if (isa<VARIABLE_NAME> (te->target))
				assert (0); // bottom

			break;
		}

		case Unary_op::ID:
			USE (dyc<Unary_op> (in)->variable_name);
			break;

		case VARIABLE_NAME::ID:
			USE (dyc<VARIABLE_NAME> (in));
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
	USE (in->lhs); // may be defined, but we conservativly say it won't.
	USE (in->index);
	USE (in->rhs); // cant be defined
}

void
Live_variable_analysis::visit_assign_target (Statement_block* bb, MIR::Assign_target* in)
{
//	use_expr (bb, in->target);
	assert (0); // USE (in->lhs);
	USE (in->rhs);
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
	USE (in->rhs);
}

void
Live_variable_analysis::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	use_expr (bb, in->expr);
}

void
Live_variable_analysis::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	USE (in->array);
}

void
Live_variable_analysis::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	USE (in->array);
}

void
Live_variable_analysis::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	USE (in->array);
}

void
Live_variable_analysis::visit_global (Statement_block* bb, MIR::Global* in)
{
	// TODO This might define the variable in some cases. Is that useful?
}

void
Live_variable_analysis::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	USE (in->variable_name);
	// Technically, it is also DEF, but it makes no difference.
}

void
Live_variable_analysis::visit_push_array (Statement_block* bb, MIR::Push_array* in)
{
	USE (in->lhs);
	USE (in->rhs);
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
