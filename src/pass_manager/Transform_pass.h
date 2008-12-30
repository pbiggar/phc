/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap generic transforms for the Pass queue.
 */

#ifndef PHC_TRANSFORM_PASS_H
#define PHC_TRANSFORM_PASS_H

#include "Pass.h"

class Transform_pass : public Pass
{
	AST::Transform* ast_transform;
	HIR::Transform* hir_transform;
	MIR::Transform* mir_transform;

public:

	Transform_pass (AST::Transform* t, String* name, String* description)
	{
		this->name = name;
		this->description = description;
		ast_transform = t;
		hir_transform = NULL;
		mir_transform = NULL;
	}

	Transform_pass (HIR::Transform* t, String* name, String* description)
	{
		this->name = name;
		this->description = description;
		ast_transform = NULL;
		hir_transform = t;
		mir_transform = NULL;
	}

	Transform_pass (MIR::Transform* t, String* name, String* description)
	{
		this->name = name;
		this->description = description;
		ast_transform = NULL;
		hir_transform = NULL;
		mir_transform = t;
	}


	void run (IR::PHP_script* in, Pass_manager* pm)
	{
		if (ast_transform)
			in->transform_children (ast_transform);
		else if (hir_transform)
			in->transform_children (hir_transform);
		else
			in->transform_children (mir_transform);
	}
};

#endif // PHC_TRANSFORM_PASS_H
