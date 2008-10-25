/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all the phc.unparser attributes from the IR
 */

#ifndef STRIP_UNPARSER_ATTRIBUTES_H
#define STRIP_UNPARSER_ATTRIBUTES_H

#include "AST_visitor.h"

class Strip_unparser_attributes : public virtual AST::Visitor, virtual public GC_obj
{
	void post_node (AST::Node* in);
};

#endif // STRIP_UNPARSER_ATTRIBUTES_H
