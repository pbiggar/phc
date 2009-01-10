/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Flow-, field-, and context-sensitive alias analysis, in a similar fashion to
 *
 * Michael Hind and Michael Burke and Paul Carini and Jong-Deok Choi,
 * Interprocedural pointer alias analysis
 * ACM Trans. Program. Lang. Syst., 1999
 *
 * We use an infinite call-string approach, and assume that other peoples
 * research can be used to constrain the memory usage at a later date. There is
 * one points-to graph per program point (which corresponds to a basic block
 * for us).
 */

#ifndef PHC_BCCH_ALIASING
#define PHC_BCCH_ALIASING

#include "WPA.h"

class BCCH_aliasing : public WPA
{
public:
	BCCH_aliasing ();
	void eval_bb (Basic_block* bb);
};

#endif // PHC_BCCH_ALIASING
