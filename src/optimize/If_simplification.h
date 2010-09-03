/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * This just does very simple optimizations, currently only turning:
 *
 *		if (!$x) goto L1; else goto L2;
 *
 *	into
 *
 *		if ($x) goto L2; else goto L1;
 */

#ifndef PHC_IF_SIMPLIFICATION 
#define PHC_IF_SIMPLIFICATION

#include "Visit_once.h"

class If_simplification : public Visit_once
{
public:
	void visit_branch_block (Branch_block*);
};

#endif // PHC_IF_SIMPLIFICATION
