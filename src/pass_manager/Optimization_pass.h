/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap Optimizations for the pass queue.
 */

#ifndef PHC_OPTIMIZATION_PASS_H
#define PHC_OPTIMIZATION_PASS_H

#include "optimize/Flow_visitor.h"
#include "pass_manager/Pass.h"
#include "process_ir/IR.h"

class Optimization_pass : public Pass
{
	Flow_visitor* visitor;
public:

	Optimization_pass (Flow_visitor* v, String* name, String* description);
	void run (CFG* in, Pass_manager* pm);
	void run (IR::PHP_script* in, Pass_manager* pm);
};

#endif // PHC_VISITOR_PASS_H
