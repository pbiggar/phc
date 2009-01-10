/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Callgraph construction.
 */

#ifndef PHC_CALLGRAPH
#define PHC_CALLGRAPH

#include "WPA.h"

class Callgraph : public WPA
{
public:
	Callgraph ();
	void eval_bb (Basic_block* bb);
};

#endif // PHC_CALLGRAPH
