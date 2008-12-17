/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated directly from the AST; once we have an
 * LIR, the C code will be generated from the LIR instead.
 */

#ifndef PHC_GENERATE_C
#define PHC_GENERATE_C

#include "MIR_visitor.h"
#include "LIR.h"
#include "pass_manager/Pass.h"

class Generate_C : public Pass
{
public:
	std::ostream& os;

	bool pass_is_enabled (Pass_manager* pm);
	void run (IR::PHP_script*, Pass_manager*);
	Generate_C (std::ostream&);
};

#endif // PHC_GENERATE_C
