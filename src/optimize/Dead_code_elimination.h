/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Dead-code elimination
 */

#ifndef PHC_DEAD_CODE_ELIMINATION 
#define PHC_DEAD_CODE_ELIMINATION

#include "CFG_visitor.h"
#include "Edge.h"
#include "SSA_ops.h"

class DCE : public CFG_visitor 
{
public:
	void run (CFG* cfg);
	DCE();
private:
	CFG* cfg;

	SSA_op_list* worklist;

;
	// Dont index on the pointer, but on a comparison function.
	map<SSA_op*, bool, bool (*)(SSA_op*, SSA_op*)> marks;

	bool is_marked (Basic_block*);

	// Mark this operation as not-dead
	void mark (SSA_op*);

	// Mark the definition of USE
	void mark_def (MIR::VARIABLE_NAME* use);
	
	void mark_pass ();
	void sweep_pass ();
	void dump();
};

#endif // PHC_DEAD_CODE_ELIMINATION
