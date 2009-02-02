/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 */

#ifndef PHC_CONSTANT_STATE
#define PHC_CONSTANT_STATE

#include "WPA.h"

class Constant_state : public WPA
{
public:
	Constant_state (Whole_program* wp);

	void dump ();
};


#endif // PHC_CONSTANT_STATE
