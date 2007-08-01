/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#ifndef PHC_PASS_MANAGER_H
#define PHC_PASS_MANAGER_H

#include "AST_visitor.h"
#include "AST_transform.h"
#include "ltdl.h"
#include "cmdline.h"

class Pass_manager;

class Pass
{
public:
	Pass () {}
	String* name;

	virtual void run (AST_php_script* in, Pass_manager* pm) = 0;
	virtual void post_process () { }

	virtual ~Pass () {}

	// not sure how this should work
	Pass* clone () { assert (0); }
};


class AST_visitor_pass : public Pass
{
	AST_visitor* visitor;

public:

	AST_visitor_pass (AST_visitor* v)
	{
		visitor = v;
	}

	void run (AST_php_script* in, Pass_manager* pm)
	{
		in->visit (visitor);
	}
};

class AST_transform_pass : public Pass
{
	AST_transform* transform;

public:

	AST_transform_pass (AST_transform* t)
	{
		transform = t;
	}

	void run (AST_php_script* in, Pass_manager* pm)
	{
		in->transform_children (transform);
	}

};

class Plugin_pass : public Pass
{
	lt_dlhandle handle;
public:

	Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm);
	void run (AST_php_script* in, Pass_manager* pm);
	void post_process ();

};


class Pass_manager : List<Pass*>
{

public:
	gengetopt_args_info* args_info;

	Pass_manager (gengetopt_args_info* args_info)
	{
		this->args_info = args_info;
	}

	// TODO make these use Strings
	void add_pass (Pass* pass);
	void add_visitor (AST_visitor* visitor, const char* name);
	void add_transform (AST_transform* transform, const char* name);
	void add_plugin (lt_dlhandle handle, const char* name);

	void add_after_each_pass (Pass* pass);
	void add_after_named_pass (Pass* pass, const char* name);
	void add_before_named_pass (Pass* pass, const char* name);
	void run_from_to (String* from, String* to, AST_php_script* in);
	void run_until (String* to, AST_php_script* in);

	void dump (AST_php_script* in, Pass* pass);
	void dump_list ();
	void run (AST_php_script* in);
	void post_process ();
	

};

#endif // PHC_PASS_MANAGER_H
