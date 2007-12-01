/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated directly from the AST; once we have an
 * IR, the C code will be generated from the IR instead.
 */

#ifndef GENERATE_C
#define GENERATE_C

#include <sstream>
#include "cmdline.h"
#include "HIR_visitor.h"
#include "pass_manager/Pass_manager.h"

class Generate_C : public HIR::Visitor, public Pass
{
public:

	ostream& os;

	void run (IR*, Pass_manager*);
	Generate_C(ostream&);

public:
	void children_statement(HIR::Statement* in);
	void pre_php_script(HIR::PHP_script* in);
	void post_php_script(HIR::PHP_script* in);
	bool pass_is_enabled (Pass_manager* pm);

public:
	String* extension_name;
	bool is_extension;
	List<HIR::Signature*>* methods;	// List of all methods compiled	
	bool return_by_reference; 		// current methods returns by reference	
};

#endif // GENERATE_C
