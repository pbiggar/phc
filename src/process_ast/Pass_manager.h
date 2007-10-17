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
	Pass () : name (NULL), description(NULL), enabled(true) { }
	String* name;
	String* description;

public:

	virtual void run (AST::AST_php_script* in, Pass_manager* pm) = 0;
	virtual void post_process () { }

private:
	bool enabled;

public:
	bool is_enabled (Pass_manager* pm) { return enabled && pass_is_enabled (pm); }
	void set_enabled (bool e) { enabled = e; }

	// Plugin writers should use this
	virtual bool pass_is_enabled (Pass_manager* pm) { return true; }

	void run_pass (AST::AST_php_script* in, Pass_manager* pm)
	{
		if (is_enabled (pm))
			run (in, pm);
	}

public:

	virtual ~Pass () {}

	// not sure how this should work
	Pass* clone () { assert (0); }
};


class AST_visitor_pass : public Pass
{
	AST::AST_visitor* visitor;

public:

	AST_visitor_pass (AST::AST_visitor* v)
	{
		visitor = v;
	}

	void run (AST::AST_php_script* in, Pass_manager* pm)
	{
		in->visit (visitor);
	}
};

class AST_transform_pass : public Pass
{
	AST::AST_transform* transform;

public:

	AST_transform_pass (AST::AST_transform* t)
	{
		transform = t;
	}

	void run (AST::AST_php_script* in, Pass_manager* pm)
	{
		in->transform_children (transform);
	}

};

class Plugin_pass : public Pass
{
	lt_dlhandle handle;
	String* option;
public:

	Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option);
	void run (AST::AST_php_script* in, Pass_manager* pm);
	void post_process ();

};



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


// TODO a file of its own
class List_passes : public Pass
{
public:
	List_passes ()
	{
		this->name = new String ("lp");
	}

	void run (AST::AST_php_script* in, Pass_manager* pm)
	{
		pm->list_passes ();
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->list_passes_given;
	}
};

#endif // PHC_PASS_MANAGER_H
