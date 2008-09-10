/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a single visit to each BB, then a single transform on each BB.
 */

#include "Visit_once.h"

void
Visit_once::run (CFG* cfg)
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		visit_block (bb);
	}

	// After the pure analysis section, apply the results (once).
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		transform_block (bb);
	}
}
