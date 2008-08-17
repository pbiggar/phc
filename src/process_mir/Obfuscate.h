/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Goto-upper and print IR if the --obfuscate optiopn is given
 */

#ifndef PHC_OBFUSCATE
#define PHC_OBFUSCATE

#include "pass_manager/Pass_manager.h"
#include "process_mir/MIR_to_AST.h"

#include "process_mir/Goto_uppering.h"
#include "process_mir/Foreach_uppering.h"
#include "process_mir/Param_is_ref_uppering.h"
#include "process_mir/Main_uppering.h"

class Obfuscate : public Pass
{
public:
	Obfuscate ()
	{
		name = new String ("obfuscate");
		description = new String ("Print program with obfuscated control-flow");
	}

	void run (IR::PHP_script* in, Pass_manager* pm)
	{
		// TODO this should be built into to MIR_unparser
		// TODO remove code duplication from Pass_manager.cpp
		MIR::PHP_script* mir = in->as_MIR ()->clone ();
		mir->transform_children (new Foreach_uppering);
		mir->transform_children (new Param_is_ref_uppering);
		mir->visit (new Goto_uppering);
		mir->visit (new Main_uppering);

		AST::PHP_script* ast = (new MIR_to_AST ())->fold_php_script (mir);
		AST_unparser().unparse (ast);
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->obfuscate_flag;
	}
};


#endif // PHC_OBFUSCATE
