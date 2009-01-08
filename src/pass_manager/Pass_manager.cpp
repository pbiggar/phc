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
#include "optimize/Def_use.h"
#include "optimize/ssa/HSSA.h"

using namespace std;

Pass_manager::Pass_manager (gengetopt_args_info* args_info)
: args_info (args_info),
  check (false)
{
	ast_queue = new Pass_queue;
	hir_queue = new Pass_queue;
	mir_queue = new Pass_queue;
	optimization_queue = new Pass_queue;
	codegen_queue = new Pass_queue;

	queues = new List <Pass_queue* > (ast_queue, hir_queue, mir_queue);
	queues->push_back (optimization_queue);
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
void Pass_manager::add_optimization (CFG_visitor* v, String* name, String* description, bool require_ssa)
{
	Pass* pass = new Optimization_pass (v, name, description, require_ssa);
	add_pass (pass, optimization_queue);
}

void Pass_manager::add_optimization_pass (Pass* pass)
{
	add_pass (pass, optimization_queue);
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
			else if (q == optimization_queue) name = "OPT";
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
			else phc_unreachable ();
		}
	}

	for (unsigned int i = 0; i < args_info->dump_uppered_given; i++)
	{
		if (*name == args_info->dump_uppered_arg [i])
		{
			if (in->is_MIR ())
				MIR_unparser().unparse_uppered (in->as_MIR ());

			// As pure HIR, this should be fine. As HIR with Foreign MIR nodes (during HIR-to-MIR lowering), ?
			if (in->is_HIR ())
			{
				// this needs to be fixed. It probably used to work when the HIR
				// was lowered to AST then uppered. However, since the uppering is
				// now in the MIR, we've nothing to upper this. I think
				// templatizing the Foreach_uppering should work. However, we want
				// to replace nodes which need uppering with foreign nodes.
				
				// I think not supporting this is fine
				phc_error ("Uppered dump is not supported during HIR pass: %s", name->c_str ());
			}

			if (in->is_AST())
				AST_unparser().unparse (in->as_AST());

		}
	}

	for (unsigned int i = 0; i < args_info->dump_dot_given; i++)
	{
		if (*name == args_info->dump_dot_arg [i])
		{
			// TODO: Works on AST only
			in->visit(new DOT_unparser());
		}
	}

	for (unsigned int i = 0; i < args_info->dump_xml_given; i++)
	{
		if (*name == args_info->dump_xml_arg [i])
		{
			xml_unparse (in, std::cout, !args_info->no_xml_attrs_flag, !args_info->no_base_64_flag);
		}
	}

	for (unsigned int i = 0; i < args_info->stats_given; i++)
	{
		if (*name == args_info->stats_arg [i])
		{
			dump_stats ();
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
		&& optimization_queue->size () == 0 
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
		&& optimization_queue->size () == 0 
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
		run_optimization_passes (in->as_MIR());

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
Pass_manager::cfg_dump (CFG* cfg, Pass* pass, String* comment, int iteration)
{
	//	for (unsigned int i = 0; i < args_info->cfg_dump_given; i++)
	//		if (*cfg_pass->name == args_info->cfg_dump_arg [i])
	//			cfg->dump_graphviz (cfg_pass->name);
	
	stringstream title;
	title << *pass->name;
	if (comment)
		title << " - " << *comment;

	title << " - " << iteration;
	for (unsigned int i = 0; i < args_info->cfg_dump_given; i++)
	{
		if (*pass->name == args_info->cfg_dump_arg [i])
		{
			cfg->dump_graphviz (s(title.str()));
		}
	}
	if (*pass->name == "all")
		cfg->dump_graphviz (s(title.str()));

	// We may not be able to dump the IR, but we can still get stats.
	dump (NULL, pass);
}

bool
Pass_manager::can_optimize (MIR::Method* method)
{
	if (lexical_cast<int> (args_info->optimize_arg) == 0)
		return false;

	if (*method->signature->method_name->value != "__MAIN__")
		return true;

	return false;

	// TODO: we did this so that most of our tests would be meaningful (since
	// most test programs are very short, and just have a main method).. Its
	// hard to get the semantics right to both __MAIN__ and all other functions.
	// So skip analyzing main, and instead add the raise_globals plugin. Analyse
	// main in the future.


	// If it is __MAIN__ we can still analyse it if it doesn't call methods
	// which touch global variables.
	
	class Main_is_optimizable : public MIR::Visitor
	{
	public:
		bool is_optimizable;
		Main_is_optimizable () : is_optimizable (true) {}
		void pre_new (MIR::New*) { is_optimizable = false; }
		void pre_method_invocation (MIR::Method_invocation* in)
		{
			if (in->target)
				is_optimizable = false;

			MIR::METHOD_NAME* method_name
				= dynamic_cast<MIR::METHOD_NAME*> (in->method_name);

			// variable-function call
			if (!method_name)
				is_optimizable = false;

			// calls a const function
			if (method_name && Oracle::is_const_function (method_name))
				is_optimizable = false;
		}
	};

	Main_is_optimizable mio;
	method->visit (&mio);

	return mio.is_optimizable;
}


void Pass_manager::run_optimization_passes (MIR::PHP_script* in)
{
	// Initialize the optimization oracle
	Oracle::initialize ();

	// The pass_manager allows passes to be added in-between the passes we expect. Ignore them.
	Pass* cfg_pass;
	do
	{
		cfg_pass = optimization_queue->front();
		optimization_queue->pop_front();
	}
	while (*cfg_pass->name != "cfg");

	Pass* build_pass;
	do
	{
		build_pass = optimization_queue->front();
		optimization_queue->pop_front();
	}
	while (*build_pass->name != "build_ssa");

	Pass* drop_pass;
	do
	{
		drop_pass = optimization_queue->back ();
		optimization_queue->pop_back ();
	}
	while (*drop_pass->name != "drop_ssa");


	MIR::Method_list* candidates = new MIR::Method_list;


	// Perform optimizations method-at-a-time.
	MIR::PHP_script* script = in->as_MIR();
	foreach (MIR::Statement* stmt, *script->statements)
	{
		// TODO: we should be optimizing all methods, not just functions.
		if (isa<MIR::Method> (stmt))
		{
			MIR::Method* method = dyc<MIR::Method> (stmt);

			// Until we have interprocedural alias analysis, we should punt on
			// __MAIN__ (with some exceptions) make an exception when there are
			// no function calls.
			if (can_optimize (method))
				candidates->push_back (method);
			else
			{
				maybe_enable_debug (cfg_pass);
				CFG* cfg = new CFG (method);
				cfg_dump (cfg, cfg_pass, s("No optimizations"), -1);
			}
		}
	}

	// Get the method signatures for use in later optimizations. Naturally,
	// this will give way once we have interprocedural optimizations.
	foreach (MIR::Method* method, *candidates)
	{
		Oracle::add_signature (method->signature);
	}

	foreach (MIR::Method* method, *candidates)
	{
		maybe_enable_debug (cfg_pass);
		CFG* cfg = new CFG (method);

		if (lexical_cast<int> (args_info->optimize_arg) > 0)
		{
			MIR::Method* old = method->clone ();

			// iterate until it fix-points (or 10 times)
			for (int iter = 0; iter < 10; iter++)
			{
				// Dump the CFG
				cfg_dump (cfg, cfg_pass, s("Iterating"), iter);
				foreach (Pass* pass, *optimization_queue)
				{
					Optimization_pass* opt = dynamic_cast<Optimization_pass*> (pass);
					if (opt == NULL || !pass->is_enabled (pm))
						continue;

					if (args_info->verbose_flag)
						cout << "Running pass: " << *pass->name << endl;

					// If an optimization pass sees something it cant handle, it
					// throws an exception, and we skip optimizing the function.
					try
					{
						maybe_enable_debug (build_pass);
						HSSA* hssa;
						if (opt->require_ssa)
						{
							// Convert to SSA form
							hssa = new HSSA (cfg);
							hssa->convert_to_hssa_form ();
							cfg->clean ();
							cfg_dump (cfg, pass, s("In SSA (cleaned)"), iter);
						}
						else
						{
							// We still want use-def information.
							cfg->duw = new Def_use_web (NULL);
							cfg->duw->run (cfg);
							cfg_dump (cfg, pass, s("Non-SSA"), iter);
						}


						// Run optimization
						maybe_enable_debug (pass);
						opt->run (cfg, this);
						cfg->clean ();
						cfg_dump (cfg, pass, s("After optimization (cleaned)"), iter);

						// Convert out of SSA
						if (opt->require_ssa)
						{
							maybe_enable_debug (drop_pass);
							hssa->convert_out_of_ssa_form ();
							cfg->clean ();
							cfg_dump (cfg, pass, s("Out of SSA (cleaned)"), iter);
						}
					}
					catch (...)
					{
						phc_missed_opt ("exceptional code in pass %s and method %s", method,
							*pass->name->c_str (), *method->signature->method_name->value->c_str ());
					}
				}
				cfg_dump (cfg, cfg_pass, s("After full set of passes"), iter);

				// After each run through the passes, check whether it has
				// fix-pointed.
				method->statements = cfg->get_linear_statements ();

				// Labels are always new values, so checking for equality wont work.
				//					if (old->equals (method))
				{
					//						cfg_dump (cfg, cfg_pass, s("Finished"), iter);
					break;
				}
				old = method->clone ();
			}
		}
	}
}
