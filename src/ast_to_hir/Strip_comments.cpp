/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Strip all comments.
 */

#include "Strip_comments.h"

using namespace AST;

void Strip_comments::pre_commented_node(Commented_node* in)
{
	in->attrs->set ("phc.comments", new String_list);
}
