/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile generated C code
 */

#ifndef PHC_COMPILE_C
#define PHC_COMPILE_C

#include "pass_manager/Pass.h"

class Compile_C : public Pass
{
public:
	stringstream& os;

	Compile_C (stringstream& os);
	void run (IR::PHP_script* in, Pass_manager* pm);
	bool pass_is_enabled (Pass_manager* pm);
};

#endif // PHC_COMPILE_C
