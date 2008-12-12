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

class Generate_C : public MIR::Visitor, public Pass
{
public:

	std::ostream& os;

	void run (IR::PHP_script*, Pass_manager*);
	Generate_C (std::ostream&);

public:
	void children_statement(MIR::Statement* in);
	void pre_php_script(MIR::PHP_script* in);
	void post_php_script(MIR::PHP_script* in);
	bool pass_is_enabled (Pass_manager* pm);

public:
	String* extension_name;
	bool is_extension;

	LIR::C_file* lir;
	LIR::UNINTERPRETED* clear_code_buffer ();
};

#endif // PHC_GENERATE_C
