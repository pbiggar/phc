/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a single visit to each BB, then a single transform on each visit.
 */

#ifndef PHC_VISIT_ONCE
#define PHC_VISIT_ONCE

#include "process_ir/General.h"

#include "CFG.h"
#include "CFG_visitor.h"
#include "Basic_block.h"

class Visit_once : public CFG_visitor
{
public:
	/* Public interface for analyses */
	void run (CFG* cfg);
};

#endif // PHC_VISIT_ONCE
