/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Pretty print if the --pretty-print
 * option is given
 */

#ifndef PHC_PRETTY_PRINT_H
#define PHC_PRETTY_PRINT_H

#include "process_ast/AST_unparser.h"
#include "pass_manager/Pass_manager.h"


class Pretty_print : public Pass
{
public:
	Pretty_print ()
	{
		this->name = new String ("pretty-print");
		this->description = new String ("Print the formatted program source");
	}

	void run (IR::PHP_script* in, Pass_manager* pm)
	{
		AST_unparser().unparse (in->as_AST ());
		set_enabled (false);
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->pretty_print_flag;
	}
};


#endif // PHC_PRETTY_PRINT_H
