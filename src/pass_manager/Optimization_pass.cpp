/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap Optimizations for the pass queue.
 */

#include "pass_manager/Optimization_pass.h"
#include "pass_manager/Pass_manager.h"

#include "optimize/CFG_visitor.h"
#include "optimize/CFG.h"

Optimization_pass::Optimization_pass (CFG_visitor* v, String* name, String* description,
                                      bool require_ssa, bool require_ssi)
: visitor (v)
, require_ssa (require_ssa)
, require_ssi (require_ssi)
{
	this->name = name;
	this->description = description;
}

void
Optimization_pass::run (CFG* in, Pass_manager* pm)
{
	visitor->run (in);
}

void
Optimization_pass::run (IR::PHP_script* in, Pass_manager* pm)
{
	assert (0);
}
