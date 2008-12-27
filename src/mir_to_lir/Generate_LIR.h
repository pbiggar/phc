/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate LIR
 *
 */

#ifndef PHC_GENERATE_LIR
#define PHC_GENERATE_LIR

#include "MIR_visitor.h"
#include "LIR.h"
#include "codegen/MICG_gen.h"
#include "pass_manager/Pass.h"

class Generate_LIR : public MIR::Visitor, virtual public GC_obj
{
public:
	Generate_LIR();
	LIR::PHP_script* fold_php_script (MIR::PHP_script* in);

public:
	void children_statement (MIR::Statement* in);
	void pre_php_script (MIR::PHP_script* in);
	void post_php_script (MIR::PHP_script* in);

public:
	String* extension_name;
	bool is_extension;

	MICG_gen micg;

	LIR::C_file* lir;
	LIR::UNINTERPRETED* clear_code_buffer ();
};

#endif // PHC_GENERATE_LIR
