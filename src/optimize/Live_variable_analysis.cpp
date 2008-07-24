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
	}
}

#define USE(VAR) bb->uses.insert (*VAR->value);
#define DEF(VAR) bb->defs.insert (*VAR->value);

void use_expr (Basic_block* bb, Expr* in) {}

void
Live_variable_analysis::process_branch (Branch_block* bb)
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
