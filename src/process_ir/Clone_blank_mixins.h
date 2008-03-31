/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Clone mixins from a particular node, avoiding precisely inserting
 * mixin following code everywhere.
 */

#ifndef PHC_CLONE_BLANK_MIXINS
#define PHC_CLONE_BLANK_MIXINS

#include "AST.h"
#include "HIR.h"
#include "MIR.h"
#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "MIR_visitor.h"

template
<
	class Node,
	class Visitor
>
class Clone_blank_mixins : public Visitor
{
private:
	Node* source;

public:
	Clone_blank_mixins (Node* source) : source (source)
	{
	}

	void pre_node (Node* in)
	{
		if (in->attrs->size () == 0)
			in->clone_mixin_from (source);
	}
};

void clone_blank_mixins_from (AST::Node* source, AST::Node* container);
void clone_blank_mixins_from (AST::Node* source, List<AST::Statement*>* containers);

void clone_blank_mixins_from (HIR::Node* source, HIR::Node* container);
void clone_blank_mixins_from (HIR::Node* source, List<HIR::Statement*>* containers);

void clone_blank_mixins_from (MIR::Node* source, MIR::Node* container);
void clone_blank_mixins_from (MIR::Node* source, List<MIR::Statement*>* containers);

#endif // PHC_CLONE_BLANK_MIXINS
