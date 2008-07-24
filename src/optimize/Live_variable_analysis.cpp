/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "Live_variable_analysis.h"
#include "CFG.h"
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
		cfg->dump_graphviz ();
		Backwards_flow_visitor::run (cfg);
		cfg->dump_graphviz ();
	}
}


void
Live_variable_analysis::transfer_in (Basic_block* bb, list<Basic_block*>*)
{
	// IN = (OUT / DEFS) U USES
	bb->live_in = bb->live_out->oop_union (bb->defs)->ip_union (bb->live_out);
}

void
Live_variable_analysis::transfer_out (Basic_block* bb, list<Basic_block*>* succs)
{
	// OUT = \/ IN (s), where s in Succs (BB).
	bb->live_out = new Set;
	BOOST_FOREACH (Basic_block* succ, *succs)
	{
		bb->live_out->ip_union (succ->live_in);
	}
}

#define USE(VAR) bb->uses->add (VAR->value);
#define DEF(VAR) bb->defs->add (VAR->value);

void use_expr (Basic_block* bb, Expr* in)
{
	// TODO
	assert (0);
}

void
Live_variable_analysis::process_branch_block (Branch_block* bb)
{
	USE (bb->branch->variable_name);
}

void
Live_variable_analysis::process_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	USE (in->lhs); // may be defined, but we conservativly say it won't.
	USE (in->index);
	USE (in->rhs); // cant be defined
}

void
Live_variable_analysis::process_assign_target (Statement_block* bb, MIR::Assign_target* in)
{
	assert (0); //use_expr (in->target);
	assert (0); // USE (in->lhs);
	USE (in->rhs);
}

void
Live_variable_analysis::process_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	DEF (in->lhs);
	assert (0); //use_expr (bb, in->expr);
}

void
Live_variable_analysis::process_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	// We don't know what variable is assigned, so we conservatively say none.
	USE (in->rhs);
}

void
Live_variable_analysis::process_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	use_expr (bb, in->expr);
}

void
Live_variable_analysis::process_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	USE (in->array);
}

void
Live_variable_analysis::process_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	USE (in->array);
}

void
Live_variable_analysis::process_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	USE (in->array);
}

void
Live_variable_analysis::process_global (Statement_block* bb, MIR::Global* in)
{
	// TODO This might define the variable in some cases. Is that useful?
}

void
Live_variable_analysis::process_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	USE (in->variable_name);
	// Technically, it is also DEF, but it makes no difference.
}

void
Live_variable_analysis::process_push_array (Statement_block* bb, MIR::Push_array* in)
{
	USE (in->lhs);
	USE (in->rhs);
}

void
Live_variable_analysis::process_return (Statement_block* bb, MIR::Return* in)
{
	use_expr (bb, in->expr);
}
void
Live_variable_analysis::process_static_declaration (Statement_block* sb, MIR::Static_declaration*)
{
	assert (0);
	// TODO
}

void
Live_variable_analysis::process_try (Statement_block* sb, MIR::Try*)
{
	assert (0);
	// TODO
}

void
Live_variable_analysis::process_throw (Statement_block* sb, MIR::Throw*)
{
	assert (0);
	// TODO
}

