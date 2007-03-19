/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "AST.h"

extern "C" void process_ast(AST_php_script* php_script)
{
	printf("%d class definition(s) found\n", php_script->class_defs->size());
}
