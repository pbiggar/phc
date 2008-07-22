/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "pass_manager/Pass_manager.h"

class Live_variable_analysis : public Pass
{
public:
	Live_variable_analysis ();
	bool pass_is_enabled (Pass_manager* pm);
	void run (IR::PHP_script* ir_script, Pass_manager* pm);
};


