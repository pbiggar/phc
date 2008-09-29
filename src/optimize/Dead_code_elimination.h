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
	map<Basic_block*, bool> marks;
	void run (CFG* cfg);
};

#endif // PHC_DEAD_CODE_ELIMINATION
