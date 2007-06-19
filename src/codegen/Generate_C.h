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
#include "AST_visitor.h"
#include "process_ast/Pass_manager.h"

class Generate_C : public AST_visitor, public Pass
{
public:
	stringstream& os;

	// use NULL to compile as an extension
	Generate_C(stringstream& os);

	void run (AST_php_script* in, Pass_manager* pm)
	{
		if (!(pm->args_info->generate_c_flag
					or pm->args_info->compile_flag))
			return;

		if (pm->args_info->extension_given)
		{
			extension_name = new String (pm->args_info->extension_arg);
			is_extension = true;
		}
		else
		{
			extension_name = new String("app");
			is_extension = false;
		}

		// adding an ostream is so invasive, thats its
		// simpler to simply hack in this osteam as a global.
		streambuf* backup = cout.rdbuf ();
		cout.rdbuf (os.rdbuf ());
		in->visit(this);
		cout.rdbuf (backup);

		if (pm->args_info->generate_c_flag)
			cout << os.str ();
	}


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
