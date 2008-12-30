/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated directly from the AST; once we have an
 * LIR, the C code will be generated from the LIR instead.
 */

#ifndef PHC_GENERATE_C_PASS
#define PHC_GENERATE_C_PASS

#include "MIR_visitor.h"
#include "pass_manager/Pass.h"

class Generate_C_pass : public Pass
{
public:
	std::ostream& os;

	bool pass_is_enabled (Pass_manager* pm);
	void run (IR::PHP_script*, Pass_manager*);
	Generate_C_pass (std::ostream&);
};

#endif // PHC_GENERATE_C_PASS
