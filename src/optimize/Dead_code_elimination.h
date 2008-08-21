/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Dead-code elimination
 */

#include "pass_manager/Pass_manager.h"
#include "Flow_visitor.h"

#ifndef PHC_DEAD_CODE_ELIMINATION 
#define PHC_DEAD_CODE_ELIMINATION

class Dead_code_elimination : public Pass, public Flow_visitor<Sparse_flow_visitor, FORWARD_FLOW>
{
public:
	Dead_code_elimination ();
	bool pass_is_enabled (Pass_manager* pm);
	void run (IR::PHP_script* ir_script, Pass_manager* pm);
public:

	void transform_assign_var (Statement_block*, MIR::Assign_var*, list<Basic_block*>*);
};

#endif // PHC_DEAD_CODE_ELIMINATION
