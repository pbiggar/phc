/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Goto-upper and print IR if the --obfuscate optiopn is given
 */

#ifndef PHC_OBFUSCATE_H
#define PHC_OBFUSCATE_H

#include "process_mir/Goto_uppering.h"
#include "pass_manager/Pass_manager.h"

class Obfuscate : public Pass
{
public:
	Obfuscate ()
	{
		name = new String ("obfuscate");
	}

	void run (IR* in, Pass_manager* pm)
	{
		AST::PHP_script* ast = in->as_AST()->clone ();
		ast->visit (new Goto_uppering());
		ast->visit (new AST_unparser);
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->obfuscate_flag;
	}
};


#endif // PHC_OBFUSCATE_H
