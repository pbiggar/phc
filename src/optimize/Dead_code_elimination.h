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
	void mark (SSA_op*);
	
	void mark_pass ();
	void sweep_pass ();
	void dump();
};

#endif // PHC_DEAD_CODE_ELIMINATION
