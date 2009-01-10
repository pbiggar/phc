/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A whole-program analysis. This has access to other analysis results as its
 * run, and must keep its state for the whole program. This simply provides the interface.
 */

#ifndef PHC_WPA
#define PHC_WPA

#include "optimize/Basic_block.h"

class WPA : virtual public GC_obj
{
public:
	virtual void eval_bb (Basic_block* bb) = 0;
};

#endif // PHC_WPA
