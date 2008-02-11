/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#include "Pass_manager.h"
#include "process_ir/General.h"

#include "cmdline.h"
#include "ltdl.h"

#include "Plugin_pass.h"
#include "Visitor_pass.h"
#include "Transform_pass.h"

#include "process_ir/XML_unparser.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"
#include "process_ast/DOT_unparser.h"

#include "process_ast/Invalid_check.h"
#include "process_mir/Goto_uppering.h"


Pass_manager::Pass_manager (gengetopt_args_info* args_info)
: args_info (args_info),
  check (false)
{
	ast_queue = new List<Pass*>;
	hir_queue = new List<Pass*>;
	mir_queue = new List<Pass*>;
	queues = new List <List<Pass*>* > (ast_queue, hir_queue, mir_queue);
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



void Pass_manager::add_mir_visitor (MIR::Visitor* visitor, const char* name)
{
	Pass* pass = new Visitor_pass (visitor, new String (name));
	add_pass (pass, mir_queue);
}

void Pass_manager::add_mir_transform (MIR::Transform* transform, const char* name)
{
	Pass* pass = new Transform_pass (transform, new String (name));
	add_pass (pass, mir_queue);
}

void Pass_manager::add_mir_pass (Pass* pass)
{
	add_pass (pass, mir_queue);
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

void Pass_manager::add_after_each_mir_pass (Pass* pass)
{
	add_after_each_pass (pass, mir_queue);
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

void Pass_manager::remove_after_named_pass (const char* name)
{
	String* n = new String (name);

	bool remove = false;
	for_li (queues, List<Pass*>, q)
	{
		for_li (*q, Pass, p) 
		{
			if (remove)
			{
				p = (*q)->erase (p); // advance
				p--; // for_li has an implicit p++
			}
			else if (*n == *((*p)->name))
				remove = true;
		}
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
			const char* name = "AST";
			if ((*q) == hir_queue) name = "HIR";
			if ((*q) == mir_queue) name = "MIR";
			String* desc = (*p)->description;
			printf ("%-30s\t(%-8s - %s)\t%s\n", 
					(*p)->name->c_str (),
					(*p)->is_enabled (this) ? "enabled" : "disabled",
					name,
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
			in->visit (new AST_unparser (), new HIR_unparser (), new MIR_unparser ());
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
				phc_error ("Cannot convert MIR to uppered form for dumping");
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
			in->visit(new AST_XML_unparser(), new HIR_XML_unparser(), new MIR_XML_unparser ());
		}
	}
}

void Pass_manager::run (IR* in, bool dump)
{
	// AST
	for_lci (ast_queue, Pass, p)
		run_pass (*p, in, dump);

	// Sometimes folding can crash. If you went out of your way to remove the
	// passes in the later queues, dont fold.
	if (hir_queue->size() == 0 && mir_queue->size () == 0)
		return;

	// HIR
	in = in->fold_lower ();

	for_lci (hir_queue, Pass, p)
		run_pass (*p, in, dump);

	if (mir_queue->size () == 0)
		return;

	// MIR
	in = in->fold_lower ();

	for_lci (mir_queue, Pass, p)
		run_pass (*p, in, dump);
}


void Pass_manager::run_pass (Pass* pass, IR* in, bool dump)
{
	assert (pass->name);

	if (args_info->verbose_flag)
		cout << "Running pass: " << *pass->name << endl;

	pass->run_pass (in, this);
	if (dump)
		this->dump (in, pass);

	if (check)
		::check (in, false);

}

/* Run all passes between FROM and TO, inclusive. */
IR* Pass_manager::run_from (String* from, IR* in, bool dump)
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
		}

		// TODO dirty hack
		if ((*q == ast_queue && in->is_AST ())
				or (*q == hir_queue && in->is_HIR ()))
			in = in->fold_lower ();
	}
	return in;
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

		// TODO dirty hack
		if ((*q == ast_queue && in->is_AST ())
				or (*q == hir_queue && in->is_HIR ()))
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

		// TODO dirty hack
		if ((*q == ast_queue && in->is_AST ())
				or (*q == hir_queue && in->is_HIR ()))
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
	return (get_pass_named (name) != NULL);
}

Pass* Pass_manager::get_pass_named (String* name)
{
	for_lci (queues, List<Pass*>, q)
		for_lci (*q, Pass, p)
		{
			if (*name == *(*p)->name)
				return *p;
		}
	return NULL;
}

bool is_queue_pass (String* name, List<Pass*>* queue)
{
	for_lci (queue, Pass, p)
	{
		if (*name == *(*p)->name)
			return true;
	}
	return false;
}

bool Pass_manager::is_ast_pass (String* name)
{
	return is_queue_pass (name, ast_queue);
}

bool Pass_manager::is_hir_pass (String* name)
{
	return is_queue_pass (name, hir_queue);
}

bool Pass_manager::is_mir_pass (String* name)
{
	return is_queue_pass (name, mir_queue);
}
