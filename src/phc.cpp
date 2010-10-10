/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Main application module 
 */

#include <ltdl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast_to_hir/AST_shredder.h"
#include "ast_to_hir/Desugar.h"
#include "ast_to_hir/Early_lower_control_flow.h"
#include "ast_to_hir/Echo_split.h"
#include "ast_to_hir/List_shredder.h"
#include "ast_to_hir/Lower_expr_flow.h"
#include "ast_to_hir/Pre_post_op_shredder.h"
#include "ast_to_hir/Remove_solo_exprs.h"
#include "ast_to_hir/Split_multiple_arguments.h"
#include "ast_to_hir/Split_unset_isset.h"
#include "ast_to_hir/Strip_comments.h"
#include "ast_to_hir/Switch_bin_op.h"
#include "generated/cmdline.h"
#include "codegen/Clarify.h"
#include "codegen/Compile_C.h"
#include "codegen/Generate_C_annotations.h"
#include "codegen/Generate_C_pass.h"
#include "codegen/Lift_functions_and_classes.h"
#include "embed/embed.h"
#include "hir_to_mir/HIR_to_MIR.h"
#include "hir_to_mir/Lower_control_flow.h"
#include "hir_to_mir/Lower_dynamic_definitions.h"
#include "hir_to_mir/Lower_method_invocations.h"
#include "optimize/hacks/Copy_propagation.h"
#include "optimize/hacks/Dead_temp_cleanup.h"
#include "optimize/Dead_code_elimination.h"
#include "optimize/Def_use_web.h"
#include "optimize/If_simplification.h"
#include "optimize/Inlining.h"
#include "optimize/Mark_initialized.h"
#include "optimize/Misc_annotations.h"
#include "optimize/Prune_symbol_table.h"
#include "optimize/Remove_loop_booleans.h"
#include "parsing/parse.h"
#include "parsing/XML_parser.h"
#include "pass_manager/Fake_pass.h"
#include "pass_manager/Pass_manager.h"
#include "process_ast/Constant_folding.h"
#include "process_ast/DOT_unparser.h"
#include "process_ast/Invalid_check.h"
#include "process_ast/Note_top_level_declarations.h"
#include "process_ast/Pretty_print.h"
#include "process_ast/Process_includes.h"
#include "process_ast/Remove_concat_null.h"
#include "process_ast/Strip_unparser_attributes.h"
#include "process_ir/XML_unparser.h"
#include "process_mir/Obfuscate.h"

using namespace std;

void init_plugins (Pass_manager* pm);
void initialize_ini_entries ();
void print_stats ();

extern struct gengetopt_args_info error_args_info;
struct gengetopt_args_info args_info;
Pass_manager* pm;

void sighandler(int signum)
{
	switch(signum)
	{
		case SIGABRT:
			fprintf(stderr, "SIGABRT received!\n");
			break;
		case SIGSEGV:
			fprintf(stderr, "SIGSEGV received!\n");
			break;
		case SIGALRM:
			fprintf(stderr, "SIGALRM received!\n");
			break;
		default:
			fprintf(stderr, "Unknown signal received!\n");
			break;
	}

	fprintf(stderr, "This could be a bug in phc. If you suspect it is, please email\n");
	fprintf(stderr, "a bug report to phc-general@phpcompiler.org.\n");

	if (pm->args_info->stats_given)
	{
		dump_stats ();
		dump_stringset_stats ();
	}

	_exit(-1);
}

int main(int argc, char** argv)
{

	/* 
	 *	Startup
	 */
	IR::PHP_script* ir = NULL;

	// Start the embedded interpreter
	PHP::startup_php ();

	// Ready XERCES
	init_xml ();

	// Synchronise C and C++ I/O
	ios_base::sync_with_stdio();

	// catch a seg fault - note this doesnt harm gdb, which will override this.
	// We do this so that tests will still continue if theres a seg fault
	signal(SIGSEGV, sighandler);
	signal(SIGABRT, sighandler);
	signal(SIGALRM, sighandler);

	// Parse command line parameters 
	if(cmdline_parser(argc, argv, &args_info) != 0)
		exit(-1);

	// Passing this struct through the pass manager is a bit hard.
	error_args_info = args_info;

	// Pass INI entries to PHP
	initialize_ini_entries ();
	

	/* 
	 *	Set up the pass_manager
	 */

	pm = new Pass_manager (&args_info);

	// process_ast passes
	pm->add_ast_pass (new Invalid_check ());
	pm->add_ast_pass (new Fake_pass (s("ast"), s("Abstract Syntax Tree - a representation of the PHP program, as written")));
	pm->add_ast_pass (new Process_includes (false, s("incl1"), pm, s("incl1")));
	pm->add_ast_pass (new Pretty_print ());

	// Begin lowering to hir
	pm->add_ast_visitor (new Strip_comments (), s("decomment"), s("Remove comments"));
	pm->add_ast_visitor (new Strip_unparser_attributes (), s("sua"), s("Remove the attributes used to pretty-print source code"));
	pm->add_ast_visitor (new Note_top_level_declarations (), s("ntld"), s("Make a note of top-level-declarations before the information is lost"));

	// Small optimization on the AST
	pm->add_ast_transform (new Constant_folding(), s("const-fold"), s("Fold constant expressions"));
	pm->add_ast_transform (new Remove_concat_null (), s("rcn"), s("Remove concatenations with \"\"")); // TODO: this is wrong - it really should be converted to a cast to string.



	// Make simple statements simpler
	pm->add_ast_transform (new Desugar (), s("desug"), s("Canonicalize simple constructs"));
	pm->add_ast_transform (new Split_multiple_arguments (), s("sma"), s("Split multiple arguments for globals, attributes and static declarations"));
	pm->add_ast_transform (new Split_unset_isset (), s("sui"), s("Split unset() and isset() into multiple calls with one argument each"));
	pm->add_ast_transform (new Echo_split (), s("ecs"), s("Split echo() into multiple calls with one argument each"));

	pm->add_ast_transform (new Early_lower_control_flow (), s("elcf"), s("Early Lower Control Flow - lower for, while, do and switch statements")); // AST
	pm->add_ast_transform (new Lower_expr_flow (), s("lef"), s("Lower Expression Flow - Lower ||, && and ?: expressions"));
	pm->add_ast_transform (new List_shredder (), s("lish"), s("List shredder - simplify to array assignments"));
	pm->add_ast_transform (new Shredder (), s("ashred"), s("Shredder - turn the AST into three-address-code, replacing complex expressions with a temporary variable"));
	pm->add_ast_transform (new Pre_post_op_shredder (), s("pps"), s("Shred pre- and post-ops, removing post-ops"));
	pm->add_ast_transform (new Switch_bin_op (), s("swbin"), s("Switch '>=' and '>' bin-ops"));
	pm->add_ast_transform (new Remove_solo_exprs (), s("rse"), s("Remove expressions which are not stored"));
	pm->add_ast_pass (new Fake_pass (s("AST-to-HIR"), s("The HIR in AST form")));


	pm->add_hir_pass (new Fake_pass (s("hir"), s("High-level Internal Representation - the smallest subset of PHP which can represent the entire language")));
	pm->add_hir_transform (new Copy_propagation (), s("prc"), s("Propagate copies - Remove some copies introduced as a result of lowering"));
	pm->add_hir_transform (new Dead_temp_cleanup (), s("dtc"), s("Dead temp cleanup")); // TODO: Description?
	pm->add_hir_transform (new Lower_dynamic_definitions (), s("ldd"), s("Lower Dynamic Definitions - Lower dynamic class, interface and method definitions using aliases"));
	pm->add_hir_transform (new Lower_method_invocations (), s("lmi"), s("Lower Method Invocations - Lower parameters using run-time reference checks"));
	pm->add_hir_transform (new Lower_control_flow (), s("lcf"), s("Lower Control Flow - Use gotos in place of loops, ifs, breaks and continues"));
	pm->add_hir_pass (new Fake_pass (s("HIR-to-MIR"), s("The MIR in HIR form")));


	pm->add_mir_pass (new Fake_pass (s("mir"), s("Medium-level Internal Representation - simple code with high-level constructs lowered to straight-line code")));
	pm->add_mir_pass (new Obfuscate ());
//	pm->add_mir_pass (new Process_includes (true, new String ("mir"), pm, "incl2"));
	pm->add_mir_transform (new Lift_functions_and_classes (), s("lfc"), s("Move statements from global scope into __MAIN__ method"));
	pm->add_mir_visitor (new Clarify (), s("clar"), s("Clarify - Make implicit definitions explicit"));
	// TODO: move this into optimization passes
	pm->add_mir_visitor (new Prune_symbol_table (), s("pst"), s("Prune Symbol Table - Note whether a symbol table is required in generated code"));


	// Optimization passes
	pm->add_local_optimization_pass (new Fake_pass (s("wpa"), s("Whole-program analysis")));
	pm->add_local_optimization_pass (new Fake_pass (s("cfg"), s("Initial Control-Flow Graph")));
	pm->add_local_optimization_pass (new Fake_pass (s("build-ssa-ssi"), s("Create SSA/SSI form")));
	pm->add_local_optimization (new If_simplification (), s("ifsimple"), s("If-simplification"), true);
	pm->add_local_optimization (new DCE (), s("dce"), s("Aggressive Dead-code elimination"), true);
	pm->add_local_optimization_pass (new Fake_pass (s("drop-ssa-ssi"), s("Drop SSA/SSI form")));
	pm->add_local_optimization (new Remove_loop_booleans (), s("rlb"), s("Remove loop-booleans"), false);

	pm->add_ipa_optimization (new Inlining (), s("inlining"), s("Method inlining"), false);

	// TODO: we could consider this for resolving isset/empty/unset queries
	// TODO: I think these should mostly move to WPA
//	pm->add_optimization (new Mark_initialized (), s("mvi"), s("Mark variable initialization status"), false);
//	pm->add_optimization (new Misc_annotations (), s("mao"), s("Miscellaneous annotations for optimization"), false);


	// codegen passes
	stringstream ss;
	pm->add_codegen_pass (new Fake_pass(s("codegen"), s("Last pass before codegen generation begins")));
	pm->add_codegen_visitor (new Generate_C_annotations, s("cgann"), s("Make annotations for code generation"));
	pm->add_codegen_pass (new Generate_C_pass (ss));
	pm->add_codegen_pass (new Compile_C (ss));


	// Plugins add their passes to the pass manager
	init_plugins (pm);

	// All the passes are added, so check the dumping options
#define check_passes(FLAG)																		\
	for (unsigned int i = 0; i < args_info.FLAG##_given; i++)						\
	{																									\
		if (!pm->has_pass_named (new String (args_info.FLAG##_arg [i])))			\
			phc_error ("Pass %s, specified with flag --" #FLAG ", is not valid", args_info.FLAG##_arg [i]);	\
	}
	// check_passes (stats);
	check_passes (dump);
	check_passes (dump_xml);
	check_passes (dump_dot);
//	check_passes (debug); // we're a bit fast and loose in optimizing
	check_passes (disable);

	// There's only one read-xml option.
	if (args_info.read_xml_given
		&& !pm->has_pass_named (new String (const_cast<const char*>(args_info.read_xml_arg))))
		phc_error ("Pass %s, specified with flag --read-xml, is not valid", args_info.read_xml_arg);	\

#undef check_passes

	// Disable passes if asked
	for (unsigned int i = 0; i < args_info.disable_given; i++)
	{
		pm->get_pass_named (s(args_info.disable_arg [i]))->set_enabled (false);
	}

	// -e implies -c (I dont know how to do this in gengetopt)
	if (args_info.execute_flag)
		args_info.compile_flag = true;

	if (args_info.web_app_given)
		phc_error ("Not directly implemented: please instead follow instructions in the \"Compiling web applications\" section of the user manual.");


	/* 
	 *	Parsing 
	 */

	// handle --list-passes the same as --help or --version
	if (args_info.list_passes_given)
		pm->list_passes ();

	if (args_info.list_passes_given && args_info.inputs_num == 0)
	{
		// do nothing
	}
	
	else
	{
		if (args_info.inputs_num > 1)
			phc_error ("Only 1 input file can be processed. Input file '%s' is ignored.", args_info.inputs[1]);

		String* filename;
		if (args_info.inputs_num == 0)
			filename = new String ("-");
		else 
			filename = new String (args_info.inputs[0]);

		// Make sure the inputs cannot be accessed globally
		args_info.inputs = NULL;

		if (args_info.read_xml_given)
		{
			#ifndef HAVE_XERCES
				phc_error("XML support not built-in; install Xerces C development library");
			#else
				String* pass_name = new String (args_info.read_xml_arg);

				// We'd like debug info while parsing too.
				pm->maybe_enable_debug (pass_name);

				XML_parser parser;
				if(args_info.inputs_num == 0)
					ir = parser.parse_xml_stdin();
				else
					ir = parser.parse_xml_file (filename);

				// If we are reading the output of another phc session, make note
				// of the variable names used, so we dont re-use them.
				ir->visit (
					new Read_fresh_suffix_counter, 
					new Read_fresh_suffix_counter, 
					new Read_fresh_suffix_counter);
				// TODO:
				// this should add a pass

				pm->run_from (pass_name, ir, true);
			#endif
		}
		else if (args_info.dump_parse_tree_flag)
		{
			dump_parse_tree (filename, NULL);
		}
		else
		{
			ir = parse (filename, NULL);

			// print error
			if (ir == NULL)
			{
				if (args_info.inputs_num != 0)
					phc_error("File not found", filename, 0, 0);
				else
					return -1;
			}

			// Avoid overwriting source variables.
			ir->visit (
				new Read_fresh_suffix_counter, 
				new Read_fresh_suffix_counter, 
				new Read_fresh_suffix_counter);

			// run passes
			pm->run (ir, true);
		}

		pm->post_process ();
	}


	if (pm->args_info->stats_given)
	{
		dump_stats ();
	}

	/*
	 * Destruction
	 */

	int ret = lt_dlexit();
	if (ret != 0) 
		phc_error ("Error closing ltdl plugin infrastructure: %s", lt_dlerror ());


	PHP::shutdown_php ();

	shutdown_xml ();

	return 0;
}

void print_stats ()
{
	if (args_info.stats_flag)
	{
		print_cow_memory_stats ();
	}
}
		

void init_plugins (Pass_manager* pm)
{
	int ret = lt_dlinit();
	if (ret != 0) phc_error ("Error initializing ltdl plugin infrastructure: %s", lt_dlerror ());

	for(unsigned i = 0; i < pm->args_info->run_given; i++)
	{
		// Try opening the specified plugin from its default location, 
		// from the current working directory, and from PKGLIBDIR (in that order)
		const char* name = pm->args_info->run_arg[i];
		const char* option = "";
		if (pm->args_info->r_option_given >= i+1)
			option = pm->args_info->r_option_arg[i];
		lt_dlhandle handle = lt_dlopenext (name);

		const char* default_err;
		const char* cwd_err;
		char in_cwd[256];
		if(handle == NULL)
		{
			// we record multiple errors, so need strdup, or they'll oerv-write each other
			default_err = strdup (lt_dlerror ()); 

			// Try current directory
			getcwd(in_cwd, 256);

			// TODO insecure
			strcat(in_cwd, "/");
			strcat(in_cwd, name);
			handle = lt_dlopenext (in_cwd);
		}

		const char* datadir_err;
		char in_datadir[256];
		if(handle == NULL)
		{
			cwd_err = strdup (lt_dlerror ());

			// Try installed dir
			// TODO insecure 
			strcpy(in_datadir, PKGLIBDIR);
			strcat(in_datadir, "/");
			strcat(in_datadir, name);
			handle = lt_dlopenext (in_datadir);	
		}

		if(handle == NULL)
		{
			datadir_err = strdup (lt_dlerror ());
			phc_error (
				"Could not find %s plugin with errors \"%s\", \"%s\" and \"%s\"",
				name, default_err, cwd_err, datadir_err);
		}

		// Save for later
		pm->add_plugin (handle, s(name), s(option));

	}
}

void initialize_ini_entries ()
{
	if (!args_info.define_given)
		return;

	for (unsigned int i = 0; i < args_info.define_given; i++)
	{
		String* define = s (args_info.define_arg[i]);

		// Split into key/value pair
		size_t index = define->find ("=");
		if (index == string::npos)
			phc_error ("Invalid key/value pair: '%s'", define->c_str ());

		string key = define->substr (0, index);
		string value = define->substr (index+1, define->size() );
		PHP::set_ini_entry (s (key), s(value));
	}
}
