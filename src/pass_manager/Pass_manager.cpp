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
#include "Optimization_pass.h"

#include "process_ir/XML_unparser.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"
#include "process_ast/DOT_unparser.h"

#include "process_ast/Invalid_check.h"

#include "optimize/Oracle.h"
#include "process_hir/HIR_to_AST.h"
#include "process_mir/MIR_to_AST.h"
#include "optimize/CFG.h"
#include "optimize/Def_use_web.h"
#include "optimize/ssa/HSSA.h"
#include "optimize/ssi/SSI.h"
#include "optimize/ssi/ESSA.h"
#include "optimize/wpa/Whole_program.h"

#include "lib/error.h"
#include <iostream>

using namespace std;

Pass_manager::Pass_manager (gengetopt_args_info* args_info)
: args_info (args_info),
  check (true)
{
	ast_queue = new Pass_queue;
	hir_queue = new Pass_queue;
	mir_queue = new Pass_queue;
	wpa_queue = new Pass_queue;
	opt_queue = new Pass_queue;
	ipa_queue = new Pass_queue;
	codegen_queue = new Pass_queue;

	queues = new List <Pass_queue* > (ast_queue, hir_queue, mir_queue);
	queues->push_back (wpa_queue);
	queues->push_back (opt_queue);
	queues->push_back (ipa_queue);
	queues->push_back (codegen_queue);
}

// AST
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

void Pass_manager::add_after_each_ast_pass (Pass* pass)
{
	add_after_each_pass (pass, ast_queue);
}


// HIR
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

void Pass_manager::add_after_each_hir_pass (Pass* pass)
{
	add_after_each_pass (pass, hir_queue);
}




// MIR
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

void Pass_manager::add_after_each_mir_pass (Pass* pass)
{
	add_after_each_pass (pass, mir_queue);
}




// Optimization
void Pass_manager::add_local_optimization (CFG_visitor* v, String* name, String* description, bool require_ssa, bool require_ssi)
{
	Pass* pass = new Optimization_pass (v, name, description, require_ssa, require_ssi);
	add_pass (pass, opt_queue);
}

void Pass_manager::add_local_optimization_pass (Pass* pass)
{
	add_pass (pass, opt_queue);
}

void Pass_manager::add_ipa_optimization (CFG_visitor* v, String* name, String* description, bool require_ssa, bool require_ssi)
{
	Pass* pass = new Optimization_pass (v, name, description, require_ssa, require_ssi);
	add_pass (pass, ipa_queue);
}

void Pass_manager::add_ipa_optimization_pass (Pass* pass)
{
	add_pass (pass, ipa_queue);
}

// Codegen
void Pass_manager::add_codegen_visitor (MIR::Visitor* visitor, String* name, String* description)
{
	Pass* pass = new Visitor_pass (visitor, name, description);
	add_pass (pass, codegen_queue);
}

void Pass_manager::add_codegen_transform (MIR::Transform* transform, String* name, String* description)
{
	Pass* pass = new Transform_pass (transform, name, description);
	add_pass (pass, codegen_queue);
}

void Pass_manager::add_codegen_pass (Pass* pass)
{
	add_pass (pass, codegen_queue);
}




// Generic
void Pass_manager::add_pass (Pass* pass, Pass_queue* queue)
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

void Pass_manager::add_after_each_pass (Pass* pass, Pass_queue* queue)
{
	for_li (queue, Pass, p)
	{
		p++;
		p = queue->insert (p, pass);
	}
}

void Pass_manager::remove_all ()
{
	for_li (queues, Pass_queue, q)
	{
		(*q)->clear ();
	}
}

void Pass_manager::remove_after_named_pass (String* name)
{
	String* n = name;

	bool remove = false;
	for_li (queues, Pass_queue, q)
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
	for_li (queues, Pass_queue, q)
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
	foreach (Pass_queue* q, *queues)
		add_after_each_pass (pass, q);
}



void Pass_manager::add_before_named_pass (Pass* pass, String* name)
{
	String* n = name;

	foreach (Pass_queue* q, *queues)
		for_li (q, Pass, p) 
			if (*n == *((*p)->name))
			{
				q->insert (p, pass);
				return;
			}


	phc_error ("No pass with name %s was found", name);
}

void Pass_manager::add_after_named_pass (Pass* pass, String* name)
{
	String* n = name;

	foreach (Pass_queue* q, *queues)
		for_li (q, Pass, p) 
			if (*n == *((*p)->name))
			{
				if (p == q->end ())
					q->push_back (pass);
				else
				{
					// insert before the next item
					p++;
					q->insert (p, pass);
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
	foreach (Pass_queue* q, *queues)
		foreach (Pass* p, *q) 
		{
			const char* name;
			if (q == ast_queue) name = "AST";
			else if (q == hir_queue) name = "HIR";
			else if (q == mir_queue) name = "MIR";
			else if (q == wpa_queue) name = "WPA";
			else if (q == opt_queue) name = "OPT";
			else if (q == ipa_queue) name = "IPA";
			else if (q == codegen_queue) name = "GEN";
			else phc_unreachable ();
			String* desc = p->description;

			printf ("%-15s    (%-8s - %3s)    %s\n", 
					p->name->c_str (),
					p->is_enabled (this) ? "enabled" : "disabled",
					name,
					desc ? (format (desc, 39)->c_str ()) : "No description");
		}
}

void
Pass_manager::maybe_enable_debug (String* pass_name)
{
	disable_cdebug ();

	for (unsigned int i = 0; i < args_info->debug_given; i++)
	{
		if (*pass_name == args_info->debug_arg [i])
		{
			enable_cdebug ();
		}
	}
}

void Pass_manager::dump (IR::PHP_script* in, String* passname)
{
	for (unsigned int i = 0; i < args_info->dump_given; i++)
	{
		if (*passname == args_info->dump_arg [i])
		{
			if (in->is_AST ())
			{
				AST_unparser ().unparse (in->as_AST ());
			}
			else if (in->is_HIR ())
			{
				if (args_info->convert_uppered_flag)
				{
					// this needs to be fixed. It probably used to work when the
					// HIR was lowered to AST then uppered. However, since the
					// uppering is now in the MIR, we've nothing to upper this. I
					// think templatizing the Foreach_uppering should work.
					// However, we want to replace nodes which need uppering with
					// foreign nodes.
					
					// I think not supporting this is fine - but dont error as it
					// may be used for MIR.
					//phc_error ("Uppered dump is not supported during HIR pass: %s", name->c_str ());
				}

				HIR_unparser ().unparse (in->as_HIR ());
			}
			else if (in->is_MIR ())
			{
				if (args_info->convert_uppered_flag)
					MIR_unparser().unparse_uppered (in->as_MIR ());
				else
					MIR_unparser ().unparse (in->as_MIR ());
			}
			else
				phc_unreachable ();
		}
	}

	for (unsigned int i = 0; i < args_info->dump_dot_given; i++)
	{
		if (*passname == args_info->dump_dot_arg [i])
		{
			// TODO: Works on AST only
			in->visit(new DOT_unparser());
		}
	}

	for (unsigned int i = 0; i < args_info->dump_xml_given; i++)
	{
		if (*passname == args_info->dump_xml_arg [i])
		{
			xml_unparse (in, std::cout, !args_info->no_xml_attrs_flag, !args_info->no_xml_base_64_flag);
		}
	}


	// TODO: add arguments to --stats to allow stats to be dumped once per passname, all at once at the end, or once per specified passname
	if (args_info->stats_given)
	{
		if (stringset_stats_size () > 0)
		{
		//	cerr << *passname << endl;
			dump_stringset_stats ();
			dump_stats ();
			reset_stringset_stats ();
			reset_stats ();
		}
	}


}

void Pass_manager::run (IR::PHP_script* in, bool main)
{
	run_from_until (NULL, NULL, in, main);
}

// The pass manager is used to parse and transform small snippets of
// compiler-generated code aswell as the whole file. Set MAIN to false for
// small snippets, and to true for the main program.
void Pass_manager::run_pass (Pass* pass, IR::PHP_script* in, bool main)
{
	try
	{
		assert (pass->name);

		if (args_info->verbose_flag && main)
			cout << "Running pass: " << *pass->name << endl;

		if (main)
			maybe_enable_debug (pass->name);

		pass->run_pass (in, this, main);
		if (main)
			this->dump (in, pass->name);

		if (check)
			::check (in, false);
	}
	catch (String* e)
	{
		// TODO: Handle this	
	}
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
	if (from) assert (has_pass_named (from));
	if (to) assert (has_pass_named (to));

	bool exec = false;
	// AST
	foreach (Pass* p, *ast_queue)
	{
		// check for starting pass
		if (!exec && 
				((from == NULL) || *(p->name) == *from))
			exec = true;

		if (exec)
			run_pass (p, in, main);

		// check for last pass
		if (exec && (to != NULL) && *(p->name) == *to)
			return in;
	}

	// Sometimes folding can crash. If you went out of your way to remove the
	// passes in the later queues, dont fold.
	if (hir_queue->size() == 0
		&& mir_queue->size () == 0 
		&& wpa_queue->size () == 0 
		&& opt_queue->size () == 0 
		&& ipa_queue->size () == 0 
		&& codegen_queue->size() == 0)
		return in;

	// HIR
	if (exec)
		in = in->fold_lower ();

	foreach (Pass* p, *hir_queue)
	{
		// check for starting pass
		if (!exec && 
				((from == NULL) || *(p->name) == *from))
			exec = true;

		if (exec)
			run_pass (p, in, main);

		// check for last pass
		if (exec && (to != NULL) && *(p->name) == *to)
			return in;
	}

	if (mir_queue->size () == 0 
		&& wpa_queue->size () == 0 
		&& opt_queue->size () == 0 
		&& ipa_queue->size () == 0 
		&& codegen_queue->size() == 0)
		return in;

	// MIR
	if (exec)
		in = in->fold_lower ();

	foreach (Pass* p, *mir_queue)
	{
		// check for starting pass
		if (!exec && 
				((from == NULL) || *(p->name) == *from))
			exec = true;

		if (exec)
			run_pass (p, in, main);

		// check for last pass
		if (exec && (to != NULL) && *(p->name) == *to)
			return in;
	}

	if (exec)
		optimize (in->as_MIR());

	// Codegen
	foreach (Pass* p, *codegen_queue)
	{
		// check for starting pass
		if (!exec && 
				((from == NULL) || *(p->name) == *from))
			exec = true;

		if (exec)
			run_pass (p, in, main);

		// check for last pass
		if (exec && (to != NULL) && *(p->name) == *to)
			return in;
	}

	return in;
}

void Pass_manager::post_process ()
{
	foreach (Pass_queue* q, *queues)
		foreach (Pass* p, *q)
		{
			p->post_process ();
		}
}


bool Pass_manager::has_pass_named (String* name)
{
	return (get_pass_named (name) != NULL);
}

Pass* Pass_manager::get_pass_named (String* name)
{
	foreach (Pass_queue* q, *queues)
		foreach (Pass* p, *q)
		{
			if (*name == *p->name)
				return p;
		}
	return NULL;
}

void
Pass_manager::cfg_dump (CFG* cfg, String* passname, String* comment)
{
	//	for (unsigned int i = 0; i < args_info->cfg_dump_given; i++)
	//		if (*cfg_pass->name == args_info->cfg_dump_arg [i])
	//			cfg->dump_graphviz (cfg_pass->name);
	
	stringstream title;
	title << *passname;
	if (comment)
		title << " - " << *comment;

	for (unsigned int i = 0; i < args_info->cfg_dump_given; i++)
	{
		if (*passname == args_info->cfg_dump_arg [i])
			cfg->dump_graphviz (s(title.str()));

		if (string ("all") == args_info->cfg_dump_arg [i])
		{
			cfg->dump_graphviz (s(title.str()));
			break;
		}
	}

	// We may not be able to dump the IR, but we can still get stats.
//	dump (NULL, passname);
}

void Pass_manager::optimize (MIR::PHP_script* in)
{
	try
	{	
		if (args_info->optimize_arg == string("0"))
			return;

		// Initialize the optimization oracle (also builds CFGs)
		maybe_enable_debug (s("cfg"));
		Oracle::initialize (in);

		// TODO: check if WPA is enabled


		// WPA calls all other passes
		maybe_enable_debug (s("wpa"));
		Whole_program* wpa = new Whole_program (this);
		wpa->run (in);
	}
	catch (String* e)
	{
		cerr << "Warning: The optimizer has failed for the following reason:\n" << *e << endl; 
	}
}

void
Pass_manager::run_local_optimization_passes (Whole_program* wp, CFG* cfg)
{
	foreach (Pass* pass, *opt_queue)
	{
		run_optimization_pass (pass, wp, cfg);
	}
	cfg_dump (cfg, s("cfg"), s("After all local passes"));
}

void
Pass_manager::run_ipa_passes (Whole_program* wp, CFG* cfg)
{
	foreach (Pass* pass, *ipa_queue)
	{
		run_optimization_pass (pass, wp, cfg);
	}
	cfg_dump (cfg, s("cfg"), s("After all ipa passes"));
}

// TODO: Whole_program shouldn't need to be passed. We can avoid it if we
// don't need to create the def-use-web during create HSSA. Strictly, we
// shouldnt.
void
Pass_manager::run_optimization_pass (Pass* pass, Whole_program* wp, CFG* cfg)
{
	Optimization_pass* opt = dynamic_cast<Optimization_pass*> (pass);
	if (opt == NULL || !pass->is_enabled (pm))
	{
		if (args_info->verbose_flag)
			cout << "Skipping pass: " << *pass->name << endl;

		return;
	}

	if (args_info->verbose_flag)
		cout << "Running pass: " << *pass->name << endl;

	// TODO: re-enable this.
	// If an optimization pass sees something it cant handle, it throws an
	// exception, and we skip optimizing the function.

	maybe_enable_debug (s("build-ssa-ssi"));

	HSSA *hssa = NULL;
	if (opt->require_ssa || opt->require_ssi)
	{
		if (opt->require_ssi) { // Convert to SSI
			if (args_info->ssi_type_arg == ssi_type_arg_ssi)
				hssa = new SSI(wp, cfg);
			else
				hssa = new ESSA(wp, cfg);
		} else // Convert to SSA
			hssa = new HSSA(wp, cfg);

		hssa->convert_to_hssa_form ();

		cfg->clean ();
		cfg_dump (cfg, pass->name, s("In SSA/SSI (cleaned)"));
	}
	else
	{
		// We still want use-def information.
		cfg->duw = new Def_use_web (wp->def_use);
		cfg->duw->build_web (cfg, false);
		cfg_dump (cfg, pass->name, s("Non-SSA"));
	}

	// Run optimization
	maybe_enable_debug (pass->name);

	try
	{
		opt->run (cfg, this);
	}
	catch (String* e)
	{
		cerr << "Warning: The optimizer has failed, but can continue. It experienced the following problem: " << *e << endl; 
	}

	cfg->clean ();
	cfg_dump (cfg, pass->name, s("After optimization (cleaned)"));

	// Convert out of SSA/SSI
	if (opt->require_ssa || opt->require_ssi)
	{
		maybe_enable_debug (s("drop-ssa-ssi"));
		hssa->convert_out_of_hssa_form ();
		cfg->clean ();
		cfg_dump (cfg, pass->name, s("Out of SSA/SSI (cleaned)"));
	}
	else
	{
		// We need the DUW for gathering stats
		if (!args_info->stats_given)
			cfg->duw = NULL;
	}
}
