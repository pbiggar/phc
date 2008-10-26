/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all the phc.unparser attributes from the IR
 */

#include "Strip_unparser_attributes.h"

using namespace AST;

void Strip_unparser_attributes::post_node (Node* in)
{
	in->attrs->erase_with_prefix ("phc.unparser");
}
