/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all the phc.unparser attributes from the IR
 */

#include "Strip_unparser_attributes.h"

using namespace AST;

void Strip_unparser_attributes::pre_real (REAL* in)
{
	// we need the source_rep for codegen for REALs.
	in->attrs->set ("phc.codegen.source_rep", in->attrs->get ("phc.unparser.source_rep"));
}

void Strip_unparser_attributes::post_node (Node* in)
{
	in->attrs->erase_with_prefix ("phc.unparser");
}
