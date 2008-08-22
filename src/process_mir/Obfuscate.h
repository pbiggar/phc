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

#include "process_mir/MIR_unparser.h"

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
		MIR_unparser().unparse_uppered (in);
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->obfuscate_flag;
	}
};


#endif // PHC_OBFUSCATE
