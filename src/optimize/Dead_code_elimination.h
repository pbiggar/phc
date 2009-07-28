/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Dead-code elimination
 */

#ifndef PHC_DEAD_CODE_ELIMINATION 
#define PHC_DEAD_CODE_ELIMINATION

#include "lib/Map.h"

#include "CFG_visitor.h"
#include "Edge.h"
#include "ssa/SSA_ops.h"

class DCE : public CFG_visitor 
{
public:
	void run (CFG* cfg);
	DCE();
private:
	CFG* cfg;

	SSA_def_list* worklist;

;
	// Is the SSA_def marked?
	SSA_op_map<bool> marks;

	// Is the BB marked?
	Map<long, bool> bb_marks;

	bool is_marked (Basic_block*);

	// Mark this operation as not-dead
	void mark (SSA_def*, string why);

	// Mark the definition of USE
	void mark_def (SSA_use* use);

	void mark_entire_block (Basic_block* bb, string why);
	void mark_rdf (Basic_block* bb);
	// Doesn't undo the marked SSA_ops
	void unmark_block (Basic_block* bb);
	
	void mark_pass ();
	void sweep_pass ();
	void dump();
};

#endif // PHC_DEAD_CODE_ELIMINATION
