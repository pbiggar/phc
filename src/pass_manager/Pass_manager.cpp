/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#include "cmdline.h"
#include "ltdl.h"
#include "Plugin_pass.h"
#include "Pass_manager.h"
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



Pass_manager::Pass_manager (gengetopt_args_info* args_info)
: args_info (args_info),
  check (false)
{
	ast_queue = new List<Pass*>;
	hir_queue = new List<Pass*>;
	queues = new List <List<Pass*>* > (ast_queue, hir_queue);
}

void Pass_manager::add_ast_visitor (AST::Visitor* visitor, const char* name)
{
	Pass* pass = new Visitor_pass (visitor, new String (name));
	add_pass (pass, ast_queue);
}

void Pass_manager::add_ast_transform (AST::Transform* transform, const char* name)
{
	Pass* pass = new Transform_pass (transform, new String (name));
	add_pass (pass, ast_queue);
}

void Pass_manager::add_ast_pass (Pass* pass)
{
	add_pass (pass, ast_queue);
}

void Pass_manager::add_hir_visitor (HIR::Visitor* visitor, const char* name)
{
	Pass* pass = new Visitor_pass (visitor, new String (name));
	add_pass (pass, hir_queue);
}

void Pass_manager::add_hir_transform (HIR::Transform* transform, const char* name)
{
	Pass* pass = new Transform_pass (transform, new String (name));
	add_pass (pass, hir_queue);
}

void Pass_manager::add_hir_pass (Pass* pass)
{
	add_pass (pass, hir_queue);
}



void Pass_manager::add_pass (Pass* pass, List<Pass*>* queue)
{
	assert (pass->name);
	queue->push_back (pass);
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

void Pass_manager::add_after_each_ast_pass (Pass* pass)
{
	add_after_each_pass (pass, ast_queue);
}

void Pass_manager::add_after_each_hir_pass (Pass* pass)
{
	add_after_each_pass (pass, hir_queue);
}

void Pass_manager::add_after_each_pass (Pass* pass, List<Pass*>* queue)
{
	for_li (queue, Pass, p)
	{
		p++;
		p = queue->insert (p, pass);
	}
}

void Pass_manager::remove_all ()
{
	for_li (queues, List<Pass*>, q)
	{
		(*q)->clear ();
	}
}



void Pass_manager::add_after_each_pass (Pass* pass)
{
	for_lci (queues, List<Pass*>, q)
		add_after_each_pass (pass, *q);
}



void Pass_manager::add_before_named_pass (Pass* pass, const char* name)
{
	String* n = new String (name);

	for_lci (queues, List<Pass*>, q)
		for_li (*q, Pass, p) 
			if (*n == *((*p)->name))
			{
				(*q)->insert (p, pass);
				return;
			}


	phc_error ("No pass with name %s was found", name);
}

void Pass_manager::add_after_named_pass (Pass* pass, const char* name)
{
	String* n = new String (name);

	for_lci (queues, List<Pass*>, q)
		for_li (*q, Pass, p) 
			if (*n == *((*p)->name))
			{
				if (p == (*q)->end ())
					(*q)->push_back (pass);
				else
				{
					// insert before the next item
					p++;
					(*q)->insert (p, pass);
				}
				return;
			}

	phc_error ("No pass with name %s was found", name);
}

void Pass_manager::list_passes ()
{
	cout << "Passes:\n";
	for_lci (queues, List<Pass*>, q)
		for_lci (*q, Pass, p) 
		{
			String* desc = (*p)->description;
			printf ("%-30s\t(%-8s - %s)\t%s\n", 
					(*p)->name->c_str (),
					(*p)->is_enabled (this) ? "enabled" : "disabled",
					(*q) == ast_queue ? "AST" : "HIR",
					desc ? desc->c_str () : "No description");
		}
}

void Pass_manager::dump (IR* in, Pass* pass)
{
	String* name = pass->name;
	for (unsigned int i = 0; i < args_info->dump_given; i++)
	{
		if (*name == args_info->dump_arg [i])
		{
			in->visit(new AST_unparser(), new HIR_unparser());
		}
	}

	for (unsigned int i = 0; i < args_info->udump_given; i++)
	{
		if (*name == args_info->udump_arg [i])
		{
			if (in->is_AST())
			{
				AST::PHP_script* ast = in->as_AST()->clone ();
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
			// Works on AST only
			in->visit(new DOT_unparser());
		}
	}

	for (unsigned int i = 0; i < args_info->xdump_given; i++)
	{
		if (*name == args_info->xdump_arg [i])
		{
			in->visit(new AST_XML_unparser(), new HIR_XML_unparser());
		}
	}
}

IR* Pass_manager::run (IR* in, bool dump)
{
	for_lci (queues, List<Pass*>, q)
	{
		for_lci (*q, Pass, p)
		{
			run_pass (*p, in, dump);
		}

		in = in->fold_lower ();
	}
	return in;
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
IR* Pass_manager::run_from_until (String* from, String* to, IR* in, bool dump)
{
	bool exec = false;
	for_lci (queues, List<Pass*>, q)
	{
		for_lci (*q, Pass, p)
		{
			// check for starting pass
			if (!exec && *((*p)->name) == *from)
				exec = true;

			if (exec)
				run_pass (*p, in, dump);

			// check for last pass
			if (exec && *((*p)->name) == *to)
				return in;
		}
		in = in->fold_lower ();
	}
	return in;
}

/* Run all passes until TO, inclusive. */
IR* Pass_manager::run_until (String* to, IR* in, bool dump)
{
	for_lci (queues, List<Pass*>, q)
	{
		for_lci (*q, Pass, p)
		{
			run_pass (*p, in, dump);

			// check for last pass
			if (*((*p)->name) == *to)
				return in;
		}
		in = in->fold_lower ();
	}
	return in;
}

void Pass_manager::post_process ()
{
	for_lci (queues, List<Pass*>, q)
		for_lci (*q, Pass, p)
		{
			(*p)->post_process ();
		}
}


bool Pass_manager::has_pass_named (String* name)
{
	for_lci (queues, List<Pass*>, q)
		for_lci (*q, Pass, p)
		{
			if (*name == *(*p)->name)
				return true;
		}
	return false;
}
