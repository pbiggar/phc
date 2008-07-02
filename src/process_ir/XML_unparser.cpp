/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */

#include "cmdline.h"
// See comment in XML_unparser::print_indent
extern gengetopt_args_info args_info;
char* get_args_info_tab ()
{
	return args_info.tab_arg;
}
