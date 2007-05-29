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

#include "AST_visitor.h"

class Generate_C : public AST_visitor
{
public:
	// use NULL to compile as an extension
	Generate_C(String* extension_name);

public:
	void children_statement(AST_statement* in);
	void pre_php_script(AST_php_script* in);
	void post_php_script(AST_php_script* in);

public:
	String* extension_name;
	bool is_extension;
	List<AST_signature*>* methods;	// List of all methods compiled	
	bool return_by_reference; 		// current methods returns by reference	
};

#endif // GENERATE_C
