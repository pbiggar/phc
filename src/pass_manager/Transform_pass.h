/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap generic transforms for the Pass queue.
 */

#ifndef PHC_TRANSFORM_PASS_H
#define PHC_TRANSFORM_PASS_H

#include "AST_transform.h"
#include "MIR_transform.h"

class Transform_pass : public Pass
{
	AST::Transform* ast_transform;
	MIR::Transform* mir_transform;

public:

	Transform_pass (AST::Transform* v, String* name)
	{
		this->name = name;
		ast_transform = v;
		mir_transform = NULL;
	}

	Transform_pass (MIR::Transform* v, String* name)
	{
		this->name = name;
		ast_transform = NULL;
		mir_transform = v;
	}

	void run (IR* in, Pass_manager* pm)
	{
		if (ast_transform != NULL)
			in->transform_children (ast_transform);
		else
			in->transform_children (mir_transform);
	}
};

#endif // PHC_TRANSFORM_PASS_H
