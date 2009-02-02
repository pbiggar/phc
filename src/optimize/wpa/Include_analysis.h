/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Keep track of included files, and put them into the CFG.
 */

#ifndef PHC_INCLUDE_ANALYSIS
#define PHC_INCLUDE_ANALYSIS

#include "WPA.h"

class Include_analysis : public WPA
{
public:
	Include_analysis (Whole_program* wp);
	void dump ();
};

#endif // PHC_INCLUDE_ANALYSIS
