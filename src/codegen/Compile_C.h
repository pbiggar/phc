/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile generated C code
 */

#include "pass_manager/Pass_manager.h"

class Compile_C : public Pass
{
public:
	stringstream& os;

	Compile_C (stringstream& os);
	void run (IR::PHP_script* in, Pass_manager* pm);
	bool pass_is_enabled (Pass_manager* pm);
};
