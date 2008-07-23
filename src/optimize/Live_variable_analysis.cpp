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
	}
}

void
Live_variable_analysis::process_entry (Entry_block*)
{
}
void
Live_variable_analysis::process_empty (Empty_block*)
{
}
void
Live_variable_analysis::process_exit (Exit_block*)
{
}
void
Live_variable_analysis::process_branch (Branch_block*)
{
}
void
Live_variable_analysis::process_return (Statement_block* sb, MIR::Return*)
{
}
void
Live_variable_analysis::process_static_declaration (Statement_block* sb, MIR::Static_declaration*)
{
}
void
Live_variable_analysis::process_global (Statement_block* sb, MIR::Global*)
{
}
void
Live_variable_analysis::process_try (Statement_block* sb, MIR::Try*)
{
}
void
Live_variable_analysis::process_throw (Statement_block* sb, MIR::Throw*)
{
}
void
Live_variable_analysis::process_foreach_next (Statement_block* sb, MIR::Foreach_next*)
{
}
void
Live_variable_analysis::process_foreach_reset (Statement_block* sb, MIR::Foreach_reset*)
{
}
void
Live_variable_analysis::process_foreach_end (Statement_block* sb, MIR::Foreach_end*)
{
}
void
Live_variable_analysis::process_assign_var (Statement_block* sb, MIR::Assign_var*)
{
}
void
Live_variable_analysis::process_assign_var_var (Statement_block* sb, MIR::Assign_var_var*)
{
}
void
Live_variable_analysis::process_assign_array (Statement_block* sb, MIR::Assign_array*)
{
}
void
Live_variable_analysis::process_push_array (Statement_block* sb, MIR::Push_array*)
{
}
void
Live_variable_analysis::process_assign_target (Statement_block* sb, MIR::Assign_target*)
{
}
void
Live_variable_analysis::process_eval_expr (Statement_block* sb, MIR::Eval_expr*)
{
}
void
Live_variable_analysis::process_pre_op (Statement_block* sb, MIR::Pre_op*)
{
}

