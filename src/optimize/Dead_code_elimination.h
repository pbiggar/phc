/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Dead-code elimination
 */

#ifndef PHC_DEAD_CODE_ELIMINATION 
#define PHC_DEAD_CODE_ELIMINATION

#include "CFG_visitor.h"


class DCE : public CFG_visitor 
{
public:
	void run (CFG* cfg);
private:
	CFG* cfg;
	map<Basic_block*, bool> marks;
	void mark_pass ();
	void sweep_pass ();
};

#endif // PHC_DEAD_CODE_ELIMINATION
