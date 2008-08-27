/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap Optimizations for the pass queue.
 */

#include "pass_manager/Optimization_pass.h"
#include "pass_manager/Pass_manager.h"

#include "optimize/Flow_visitor.h"
#include "optimize/CFG.h"

Optimization_pass::Optimization_pass (Flow_visitor* v, String* name, String* description)
: visitor (v)
{
	this->name = name;
	this->description = description;
}

void
Optimization_pass::run (CFG* in, Pass_manager* pm)
{
	visitor->visit (in);
}

void
Optimization_pass::run (IR::PHP_script* in, Pass_manager* pm)
{
	assert (0);
}
