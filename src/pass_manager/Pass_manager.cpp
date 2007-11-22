/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#include "cmdline.h"
#include "ltdl.h"
#include "Pass_manager.h"
#include "Plugin_pass.h"
#include "Visitor_pass.h"
#include "Transform_pass.h"
#include "process_ast/AST_unparser.h"
#include "process_ir/XML_unparser.h"
#include "process_ir/Foreach.h"
#include "process_ast/DOT_unparser.h"
#include "process_ast/Invalid_check.h"
#include "process_hir/Goto_uppering.h"
#include "process_hir/HIR_unparser.h"
#include "AST.h"
#include "HIR.h"

using namespace AST;
using namespace HIR;

Plugin_pass::Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option)
{
	this->handle = handle;
	this->name = name;
	this->option = option;
}

void Plugin_pass::run (IR* in, Pass_manager* pm)
{
	// RUN
	typedef void (*ast_function)(AST_php_script*, Pass_manager*, String*);
	ast_function ast_func = (ast_function) lt_dlsym(handle, "run");

	if (not (ast_func))
		phc_error ("A plugin must define the AST run () function");

	if (ast_func && in->ast)
		(*ast_func)(in->ast, pm, option);

/*
	typedef void (*hir_function)(HIR_php_script*, Pass_manager*, String*);
	hir_function hir_func = (hir_function) lt_dlsym (handle, "run");

	if (not (ast_func || hir_func))
		phc_error ("A plugin must use either the HIR run () function or the AST run () function");

	if (hir_func && in->hir)
		(*hir_func)(in->hir, pm, option);
*/
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
	Pass* pass = new Visitor_pass (visitor);
	if (name)
		pass->name = new String (name);
	add_pass (pass);
}

void Pass_manager::add_transform (AST_transform* transform, const char* name)
{
	Pass* pass = new Transform_pass (transform);
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

void Pass_manager::dump (IR* in, Pass* pass)
{
	String* name = pass->name;
	for (unsigned int i = 0; i < args_info->dump_given; i++)
	{
		if (*name == args_info->dump_arg [i])
		{
			if (in->ast)
				in->ast->visit (new AST_unparser ());
			else
				in->hir->visit (new HIR_unparser ());
		}
	}

	for (unsigned int i = 0; i < args_info->udump_given; i++)
	{
		if (*name == args_info->udump_arg [i])
		{
			if (in->ast)
			{
				AST::AST_php_script* ast = in->ast->clone ();
				ast->visit (new Goto_uppering ());
				ast->visit (new AST_unparser ());
			}
			else
				phc_error ("Cannot convert HIR to uppered form for dumping");
		}
	}

	for (unsigned int i = 0; i < args_info->ddump_given; i++)
	{
		if (*name == args_info->ddump_arg [i])
		{
			if (in->ast)
			{
				in->ast->visit (new DOT_unparser ());
			}
			else
				assert (0);
		}
	}

	for (unsigned int i = 0; i < args_info->xdump_given; i++)
	{
		if (*name == args_info->xdump_arg [i])
		{
			if (in->ast)
				in->ast->visit (new AST_XML_unparser ());
			else
				in->hir->visit (new HIR_XML_unparser ());

		}
	}
}

void Pass_manager::run (IR* in, bool dump)
{
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		run_pass (*i, in, dump);
	}
}

void Pass_manager::run_pass (Pass* pass, IR* in, bool dump)
{
	assert (pass->name);
	pass->run_pass (in, this);
	if (check)
		::check (in, false);

	if (dump)
		this->dump (in, pass);
}

/* Run all passes between FROM and TO, inclusive. */
void Pass_manager::run_from_until (String* from, String* to, IR* in, bool dump)
{
	bool exec = false;
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		// check for starting pass
		if (!exec && *((*i)->name) == *from)
			exec = true;

		if (exec)
			run_pass (*i, in, dump);

		// check for last pass
		if (exec && *((*i)->name) == *to)
			exec = false;
	}
}

/* Run all passes until TO, inclusive. */
void Pass_manager::run_until (String* to, IR* in, bool dump)
{
	List<Pass*>::const_iterator i;
	for (i = begin (); i != end (); i++)
	{
		run_pass (*i, in, dump);

		// check for last pass
		if (*((*i)->name) == *to)
			break;
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


bool Pass_manager::has_pass_named (String* name)
{
	for_lci (this, Pass, i)
	{
		if (*name == *(*i)->name)
			return true;
	}
	return false;
}
