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
//		cfg->dump_graphviz ();
	}
}


