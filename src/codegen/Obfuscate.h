/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Goto-upper and print IR if the --obfuscate optiopn is given
 */



#ifndef PHC_OBFUSCATE_H
#define PHC_OBFUSCATE_H

#include "process_ast/PHP_unparser.h"
#include "codegen/Goto_uppering.h"
#include "process_ast/Pass_manager.h"

class Obfuscate : public Pass
{
public:
	Obfuscate ()
	{
		name = new String ("obfuscate");
	}

	void run (AST_php_script* in, Pass_manager* pm)
	{
		in = in->clone ();
		in->visit (new Goto_uppering());
		in->visit (new PHP_unparser);
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->obfuscate_flag;
	}
};


#endif // PHC_OBFUSCATE_H
