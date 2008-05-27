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
#include "process_mir/Foreach_uppering.h"

#include "process_hir/HIR_to_AST.h"
#include "process_mir/MIR_to_AST.h"


Pass_manager::Pass_manager (gengetopt_args_info* args_info)
: args_info (args_info),
  check (false)
{
	ast_queue = new List<Pass*>;
	hir_queue = new List<Pass*>;
	mir_queue = new List<Pass*>;
	queues = new List <List<Pass*>* > (ast_queue, hir_queue, mir_queue);
}

void Pass_manager::add_ast_visitor (AST::Visitor* visitor, String* name, String* description)
{
	Pass* pass = new Visitor_pass (visitor, name, description);
	add_pass (pass, ast_queue);
}

void Pass_manager::add_ast_transform (AST::Transform* transform, String* name, String* description)
{
	Pass* pass = new Transform_pass (transform, name, description);
	add_pass (pass, ast_queue);
}

void Pass_manager::add_ast_pass (Pass* pass)
{
	add_pass (pass, ast_queue);
}

void Pass_manager::add_hir_visitor (HIR::Visitor* visitor, String* name, String* description)
{
	Pass* pass = new Visitor_pass (visitor, name, description);
	add_pass (pass, hir_queue);
}

void Pass_manager::add_hir_transform (HIR::Transform* transform, String* name, String* description)
{
	Pass* pass = new Transform_pass (transform, name, description);
	add_pass (pass, hir_queue);
}

void Pass_manager::add_hir_pass (Pass* pass)
{
	add_pass (pass, hir_queue);
}



void Pass_manager::add_mir_visitor (MIR::Visitor* visitor, String* name, String* description)
{
	Pass* pass = new Visitor_pass (visitor, name, description);
	add_pass (pass, mir_queue);
}

void Pass_manager::add_mir_transform (MIR::Transform* transform, String* name, String* description)
{
	Pass* pass = new Transform_pass (transform, name, description);
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



void Pass_manager::add_plugin (lt_dlhandle handle, String* name, String* option)
{
	Plugin_pass* pp = new Plugin_pass (name, handle, this, option);

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

void Pass_manager::remove_after_named_pass (String* name)
{
	String* n = name;

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

void Pass_manager::remove_pass_named (String* name)
{
	for_li (queues, List<Pass*>, q)
	{
		for_li (*q, Pass, p) 
		{
			if (*name == *((*p)->name))
				p = (*q)->erase (p);
		}
	}
}



void Pass_manager::add_after_each_pass (Pass* pass)
{
	for_lci (queues, List<Pass*>, q)
		add_after_each_pass (pass, *q);
}



void Pass_manager::add_before_named_pass (Pass* pass, String* name)
{
	String* n = name;

	for_lci (queues, List<Pass*>, q)
		for_li (*q, Pass, p) 
			if (*n == *((*p)->name))
			{
				(*q)->insert (p, pass);
				return;
			}


	phc_error ("No pass with name %s was found", name);
}

void Pass_manager::add_after_named_pass (Pass* pass, String* name)
{
	String* n = name;

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

// TODO this could be much nicer, but its not important
/* Format the string so that each line in LENGTH long, and all lines except the
 * first have WHITESPACE of leading whitespace */
String* format (String* str, int prefix_length)
{
	const int LINE_LENGTH = 80;
	assert (prefix_length < LINE_LENGTH);
	stringstream result;
	stringstream line;
	stringstream word;

	string leading_whitespace (prefix_length, ' ');


	for (unsigned int i = 0; i < str->size (); i++)
	{
		// add the letter to the word
		word << (*str)[i];

		// end of word
		if ((*str)[i] == ' ')
		{
			line << word.str();
			word.str(""); // erase
		}
		else
		{
			// end of line?
			if (line.str().size() + word.str().size() > (unsigned int)(LINE_LENGTH - prefix_length))
			{
				result << line.str() << "\n";
				line.str (""); // erase
				line << leading_whitespace;

				// only use the prefix on the first line
				prefix_length = 0;
			}
		}
	}

	// flush the remainder of the string
	result << line.str () << word.str ();

	return s(result.str ());
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

			printf ("%-15s    (%-8s - %3s)    %s\n", 
					(*p)->name->c_str (),
					(*p)->is_enabled (this) ? "enabled" : "disabled",
					name,
					desc ? (format (desc, 39)->c_str ()) : "No description");
		}
}

void Pass_manager::maybe_enable_debug (Pass* pass)
{
	disable_cdebug ();

	String* name = pass->name;
	for (unsigned int i = 0; i < args_info->debug_given; i++)
	{
		if (*name == args_info->debug_arg [i])
		{
			enable_cdebug ();
		}
	}
}

void Pass_manager::dump (IR::PHP_script* in, Pass* pass)
{
	String* name = pass->name;
	for (unsigned int i = 0; i < args_info->dump_given; i++)
	{
		if (*name == args_info->dump_arg [i])
		{
			if (in->is_AST ()) AST_unparser ().unparse (in->as_AST ());
			else if (in->is_HIR ()) HIR_unparser ().unparse (in->as_HIR ());
			else if (in->is_MIR ()) MIR_unparser ().unparse (in->as_MIR ());
			else assert (0);
		}
	}

	for (unsigned int i = 0; i < args_info->udump_given; i++)
	{
		if (*name == args_info->udump_arg [i])
		{
			// TODO uppering should be built in to this
			// TODO this should be built into to MIR_unparser
			// TODO remove code duplication from Obfuscate.h
			if (in->is_MIR ())
			{
				MIR::PHP_script* mir = in->as_MIR ();
				mir->transform_children (new Foreach_uppering);
				mir->visit (new Goto_uppering);
				AST::PHP_script* ast = (new MIR_to_AST ())->fold_php_script (mir);
				AST_unparser(new MIR_unparser ()).unparse (ast) ;
			}

			// As pure HIR, this should be fine. As HIR with Foreign MIR nodes (during HIR-to-MIR lowering), ?
			if (in->is_HIR ())
			{
				// this needs to be fixed. It probably used to work when the HIR
				// was lowered to AST then uppered. However, since the uppering is
				// now in the MIR, we've nothing to upper this. I think
				// templatizing the Foreach_uppering should work. However, we want
				// to replace nodes which need uppering with foreign nodes, so
				// we'll leave this as-is for now.

				HIR_unparser().unparse (in->as_HIR ());
			}

			if (in->is_AST())
				AST_unparser().unparse (in->as_AST()->clone ()); // TODO do we still need to clone?

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
			bool attrs = !args_info->no_xml_attrs_flag;
			in->visit(	new AST_XML_unparser (cout, attrs),
							new HIR_XML_unparser (cout, attrs), 
							new MIR_XML_unparser (cout, attrs));
		}
	}
}

void Pass_manager::run (IR::PHP_script* in, bool main)
{
	// AST
	for_lci (ast_queue, Pass, p)
		run_pass (*p, in, main);

	// Sometimes folding can crash. If you went out of your way to remove the
	// passes in the later queues, dont fold.
	if (hir_queue->size() == 0 && mir_queue->size () == 0)
		return;

	// HIR
	in = in->fold_lower ();

	for_lci (hir_queue, Pass, p)
		run_pass (*p, in, main);

	if (mir_queue->size () == 0)
		return;

	// MIR
	in = in->fold_lower ();

	for_lci (mir_queue, Pass, p)
		run_pass (*p, in, main);
}

// The pass manager is used to parse and transform small snippets of
// compiler-generated code aswell as the whole file. Set MAIN to false for
// small snippets, and to true for the main program.
void Pass_manager::run_pass (Pass* pass, IR::PHP_script* in, bool main)
{
	assert (pass->name);

	if (args_info->verbose_flag && main)
		cout << "Running pass: " << *pass->name << endl;

	if (main)
		maybe_enable_debug (pass);

	pass->run_pass (in, this);
	if (main)
		this->dump (in, pass);

	if (check)
		::check (in, false);

}

/* Run all passes between FROM and TO, inclusive. */
IR::PHP_script* Pass_manager::run_from (String* from, IR::PHP_script* in, bool main)
{
	return run_from_until (from, NULL, in, main);
}

/* Run all passes until TO, inclusive. */
IR::PHP_script* Pass_manager::run_until (String* to, IR::PHP_script* in, bool main)
{
	return run_from_until (NULL, to, in, main);
}



/* Run all passes between FROM and TO, inclusive. */
IR::PHP_script* Pass_manager::run_from_until (String* from, String* to, IR::PHP_script* in, bool main)
{
	bool exec = false;
	for_lci (queues, List<Pass*>, q)
	{
		for_lci (*q, Pass, p)
		{
			// check for starting pass
			if (!exec && 
					((from == NULL) || *((*p)->name) == *from))
				exec = true;

			if (exec)
				run_pass (*p, in, main);

			// check for last pass
			if (exec && (to != NULL) && *((*p)->name) == *to)
				return in;
		}

		// TODO dirty hack
		if (*q == ast_queue && in->is_AST () 
			&& hir_queue->size () == 0 
			&& mir_queue->size () == 0)
			return in;

		if (*q == hir_queue && in->is_HIR () 
			&& mir_queue->size () == 0)
			return in;

		if ((in->is_AST () && *q == ast_queue)
			|| (in->is_HIR () && *q == hir_queue))
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
