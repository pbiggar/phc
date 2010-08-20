/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap optimizations for the pass queue.
 */

#ifndef PHC_OPTIMIZATION_PASS_H
#define PHC_OPTIMIZATION_PASS_H

#include "pass_manager/Pass.h"
#include "process_ir/IR.h"

class CFG_visitor;
class CFG;

class Optimization_pass : public Pass
{
	CFG_visitor* visitor;
public:
	bool require_ssa;
	bool require_ssi;

	Optimization_pass (CFG_visitor* v, String* name, String* description, bool require_ssa = false, bool require_ssi = false);
	void run (CFG* in, Pass_manager* pm);
	void run (IR::PHP_script* in, Pass_manager* pm);

};

#endif // PHC_VISITOR_PASS_H
