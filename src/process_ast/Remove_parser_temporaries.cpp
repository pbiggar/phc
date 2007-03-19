/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 */

#include "Remove_parser_temporaries.h"

void Remove_parser_temporaries::pre_node(AST_node* in)
{
	in->attrs->erase("phc.parser.is_ref");
	in->attrs->erase("phc.parser.function_params");
}
