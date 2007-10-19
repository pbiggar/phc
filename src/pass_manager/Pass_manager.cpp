/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#include "AST_visitor.h"
#include "cmdline.h"
#include "ltdl.h"
#include "AST_transform.h"
#include "process_ast/Invalid_check.h"
#include "process_ast/PHP_unparser.h"
#include "process_ast/DOT_unparser.h"
#include "process_ast/XML_unparser.h"
#include "process_hir/Goto_uppering.h"
#include "Pass_manager.h"

Plugin_pass::Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option)
{
	this->handle = handle;
	this->name = name;
	this->option = option;
}

void Plugin_pass::run (AST_php_script* in, Pass_manager* pm)
{
	// RUN
	typedef void (*run_function)(AST_php_script*, Pass_manager*, String*);
	run_function func = (run_function) lt_dlsym(handle, "run");
	// TODO this is mandatory (in the sense that it
	// doesnt make sense not to use this)

	(*func)(in, pm, option);
}

void Plugin_pass::post_process ()
{
	// only do this once per instance of a pass, even though
	// it might appear at multiple locations in the pass
	// queue
	if (this->handle == NULL)
		return;

	// UNLOAD
	typedef void (*unload_function)();
	unload_function func = (unload_function) lt_dlsym(handle, "unload");

	if (func)
		(*func)();

	int ret = lt_dlclose (handle);
	if (ret != 0) 
		phc_error ("Error closing %s plugin with error: %s", name, lt_dlerror ());

	this->handle = NULL;
}

void Pass_manager::add_pass (Pass* pass)
{
	push_back (pass);
}

void Pass_manager::add_visitor (AST_visitor* visitor, const char* name)
{
	Pass* pass = new AST_visitor_pass (visitor);
	if (name)
		pass->name = new String (name);
	add_pass (pass);
}

void Pass_manager::add_transform (AST_transform* transform, const char* name)
{
	Pass* pass = new AST_transform_pass (transform);
	if (name)
		pass->name = new String (name);

	assert (pass->name);
	add_pass (pass);
}

void Pass_manager::add_plugin (lt_dlhandle handle, const char* name, String* option)
{
	Plugin_pass* pp = new Plugin_pass (new String (name), handle, this, option);

	// LOAD
	typedef void (*load_function)(Pass_manager*, Plugin_pass*);
	load_function func = (load_function) lt_dlsym(handle, "load");
	if(func == NULL)
		phc_error ("Unable to find 'load' function in plugin %s: %s", pp->name->c_str (), lt_dlerror ());

	(*func)(this, pp);
	
}

void Pass_manager::add_after_each_pass (Pass* pass)
{
	List<Pass*>::iterator i;
	for (i = begin (); i != end (); i++)
	{
		insert (i, pass);
		i++;
	}
}

void Pass_manager::add_before_named_pass (Pass* pass, const char* name)
{
	String* n = new String (name);
	List<Pass*>::iterator i;
	for (i = begin (); i != end (); i++)
	{
		if (*n == *((*i)->name))
		{
			insert (i, pass);
			return;
		}
	}

	phc_error ("No pass with name %s was found", name);
}

void Pass_manager::add_after_named_pass (Pass* pass, const char* name)
{
	String* n = new String (name);
	List<Pass*>::iterator i;
	for (i = begin (); i != end (); i++)
	{
		if (*n == *((*i)->name))
		{
			if (i == end ())
				push_back (pass);
			else
			{
				// insert before the next item
				i++;
				insert (i, pass);
			}
			return;
		}
	}

	phc_error ("No pass with name %s was found", name);
}

void Pass_manager::list_passes ()
{
	List<Pass*>::iterator i;
	cout << "Passes:\n";
	for (i = begin (); i != end (); i++)
	{
		String* desc = (*i)->description;
		printf ("%-15s\t(%s)\t%s\n", 
			(*i)->name->c_str (),
			(*i)->is_enabled (this) ? "enabled" : "disabled",
			desc ? desc->c_str () : "No description");
	}
}

Pass* Pass_manager::get_pass (const char* name)
{
	List<Pass*>::iterator i;
	for (i = begin (); i != end (); i++)
	{
		if (*(*i)->name == name)
			return (*i);
	}
	return NULL;
}

void Pass_manager::dump (AST_php_script* in, Pass* pass)
{
	String* name = pass->name;
	for (unsigned int i = 0; i < args_info->dump_given; i++)
	{
		if (*name == args_info->dump_arg [i])
		{
			in->visit (new PHP_unparser ());
		}
	}

	for (unsigned int i = 0; i < args_info->udump_given; i++)
	{
		if (*name == args_info->udump_arg [i])
		{
			in = in->clone ();
			in->visit (new Goto_uppering ());
			in->visit (new PHP_unparser ());
		}
	}

	for (unsigned int i = 0; i < args_info->ddump_given; i++)
	{
		if (*name == args_info->ddump_arg [i])
		{
			in->visit (new DOT_unparser ());
		}
	}

	for (unsigned int i = 0; i < args_info->xdump_given; i++)
	{
		if (*name == args_info->xdump_arg [i])
		{
			in->visit (new XML_unparser ());
		}
	}
}

void Pass_manager::run (AST_php_script* in)
{
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		assert ((*i)->name);
		(*i)->run_pass (in, this);
		if (check)
			::check (in, false);
		dump (in, *i);
	}
}

/* Run all passes between FROM and TO, inclusive. */
void Pass_manager::run_from_to (String* from, String* to, AST_php_script* in)
{
	bool exec = false;
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		assert ((*i)->name);

		// check for starting pass
		if (exec == false)
		{
			if (*((*i)->name) == *from)
				exec = true;
		}

		if (exec == true)
		{
			(*i)->run_pass (in, this);
			if (check)
				::check (in, true);

			// check for last pass
			if (*((*i)->name) == *to)
				exec = false;
		}

		// dont dump
	}
}

/* Run all passes until TO, inclusive. */
void Pass_manager::run_until (String* to, AST_php_script* in)
{
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		assert ((*i)->name);

		(*i)->run_pass (in, this);
		if (check)
			::check (in, false);

		// check for last pass
		if (*((*i)->name) == *to)
			break;
		// dont dump
	}
}

void Pass_manager::post_process ()
{
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		(*i)->post_process ();
	}
}
