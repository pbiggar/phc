/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Value-range propagation.
 *
 * See:
 * Accurate static branch prediction by value range propagation,
 * Jason Patterson,
 * PLDI95.
 *
 * We need this to help determine when integers overflow into doubles. So we
 * don't need anymore than the max and min values.
 *
 */

#ifndef PHC_VRP
#define PHC_VRP

#include "WPA.h"

class VRP : public WPA
{
public:
	VRP (Whole_program* wp);
	void dump ();
};

#endif // PHC_VRP
