/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap generic transforms for the Pass queue.
 */

#ifndef PHC_TRANSFORM_PASS_H
#define PHC_TRANSFORM_PASS_H

#include "AST_transform.h"

// TODO generic transform pass
class AST_transform_pass : public Pass
{
	AST::AST_transform* transform;

public:

	AST_transform_pass (AST::AST_transform* t)
	{
		transform = t;
	}

	void run (AST::AST_php_script* in, Pass_manager* pm)
	{
		in->transform_children (transform);
	}

};

#endif // PHC_TRANSFORM_PASS_H
