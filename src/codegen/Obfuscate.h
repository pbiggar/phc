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
		if (!pm->args_info->obfuscate_flag)
			return;

		in = in->clone ();
		in->visit (new Goto_uppering());
		in->visit (new PHP_unparser);
	}
};


#endif // PHC_OBFUSCATE_H
