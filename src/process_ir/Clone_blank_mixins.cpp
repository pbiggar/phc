/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Clone mixins from a particular node, avoiding precisely inserting
 * mixin following code everywhere.
 */


#include "General.h"
#include "Clone_blank_mixins.h"

#define create_clone_blank_mixins(IR)																\
void clone_blank_mixins_from (IR::Node* source, IR::Node* container)						\
{																												\
	container->visit (new Clone_blank_mixins<IR::Node, IR::Visitor> (source));			\
}																												\
void clone_blank_mixins_from (IR::Node* source, List<IR::Statement*>* containers)	\
{																												\
	for_lci (containers, IR::Statement, i)															\
	{																											\
		(*i)->visit (new Clone_blank_mixins<IR::Node, IR::Visitor> (source));			\
	}																											\
}

create_clone_blank_mixins (AST)
create_clone_blank_mixins (HIR)
create_clone_blank_mixins (MIR)

#undef create_clone_blank_mixins
