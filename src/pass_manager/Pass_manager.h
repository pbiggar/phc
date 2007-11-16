/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#ifndef PHC_PASS_MANAGER_H
#define PHC_PASS_MANAGER_H

#include "Pass.h"
#include "AST_visitor.h"
#include "AST_transform.h"
#include "cmdline.h"
#include "ltdl.h"

class Pass;

class Pass_manager : public List<Pass*>
{

public:
	gengetopt_args_info* args_info;
	bool check; // check AST after each pass

	Pass_manager (gengetopt_args_info* args_info)
	: args_info (args_info),
	  check (false)
	{
	}

	// TODO make these use Strings
	void add_pass (Pass* pass);
	void add_visitor (AST::AST_visitor* visitor, const char* name);
	void add_transform (AST::AST_transform* transform, const char* name);
	void add_plugin (lt_dlhandle handle, const char* name, String* option);

	void add_after_each_pass (Pass* pass);
	void add_after_named_pass (Pass* pass, const char* name);
	void add_before_named_pass (Pass* pass, const char* name);
	void run_from_to (String* from, String* to, AST::AST_php_script* in);
	void run_until (String* to, AST::AST_php_script* in);
	Pass* get_pass (const char* name);
	void list_passes ();

	void dump (AST::AST_php_script* in, Pass* pass);
	void run (AST::AST_php_script* in);
	void post_process ();
	

};


#endif // PHC_PASS_MANAGER_H
