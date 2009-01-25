/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 */

#ifndef PHC_GENERATE_C
#define PHC_GENERATE_C

#include "MIR_visitor.h"
#include "codegen/MICG_gen.h"
#include "pass_manager/Pass.h"

class Generate_C : public MIR::Visitor, virtual public GC_obj
{
	std::ostream& os;
public:
	Generate_C (std::ostream&);

	/* TODO: os is not written into until post_php_script. There should be
	 * another way to flush its contents early, rather than accesing body
	 * directly. */
	stringstream body;

public:
	void children_statement (MIR::Statement* in);
	void pre_php_script (MIR::PHP_script* in);
	void post_php_script (MIR::PHP_script* in);

public:
	String* extension_name;
	bool is_extension;

	MICG_gen micg;

public:
	string compile_statement(MIR::Statement* in);
	void compile_static_value(string result, std::ostream& os, MIR::Static_value* sv);
};

#endif // PHC_GENERATE_C
