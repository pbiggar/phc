/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Value-range propagation.
 *
 * Based mostly on
 * Accurate static branch prediction by value range propagation,
 * Jason Patterson,
 * PLDI95.
 *
 * We need this to help determine when integers overflow into doubles.
 *
 */

#ifndef PHC_VRP
#define PHC_VRP

#include "WPA.h"

class VRP : public WPA
{
public:
	VRP ();
	void eval_bb (Basic_block* bb);
};

#endif // PHC_VRP
