/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Main application module 
 */

#include "AST.h"
#include "ast_to_hir/AST_shredder.h"
#include "ast_to_hir/Desugar.h"
#include "ast_to_hir/Early_lower_control_flow.h"
#include "ast_to_hir/Echo_split.h"
#include "ast_to_hir/List_shredder.h"
#include "ast_to_hir/Lower_expr_flow.h"
#include "ast_to_hir/Pre_post_op_shredder.h"
#include "ast_to_hir/Split_multiple_arguments.h"
#include "ast_to_hir/Split_unset_isset.h"
#include "ast_to_hir/Strip_comments.h"
#include "ast_to_hir/Tidy_print.h"
#include "ast_to_hir/Translate_empty.h"
#include "cmdline.h"
#include "codegen/Clarify.h"
#include "codegen/Compile_C.h"
#include "codegen/Copy_propagation.h"
#include "codegen/Dead_code_elimination.h"
#include "codegen/Generate_C.h"
#include "codegen/Lift_functions_and_classes.h"
#include "codegen/Prune_symbol_table.h"
#include "embed/embed.h"
#include "hir_to_mir/HIR_to_MIR.h"
#include "hir_to_mir/Lower_control_flow.h"
#include <ltdl.h>
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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void init_plugins (Pass_manager* pm);

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
		default:
			fprintf(stderr, "Unknown signal received!\n");
			break;
	}

	fprintf(stderr, "This could be a bug in phc. If you suspect it is, please email\n");
	fprintf(stderr, "a bug report to phc-general@phpcompiler.org.\n");
	exit(-1);
}



extern struct gengetopt_args_info error_args_info;
struct gengetopt_args_info args_info;
Pass_manager* pm;

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

	// Parse command line parameters 
	if(cmdline_parser(argc, argv, &args_info) != 0)
		exit(-1);

	// Passign this struct through the pass manager is a bit hard.
	error_args_info = args_info;


	/* 
	 *	Set up the pass_manager
	 */

	pm = new Pass_manager (&args_info);

	// process_ast passes
	pm->add_ast_pass (new Invalid_check ());
	pm->add_ast_pass (new Fake_pass (s("ast"), s("Abstract Syntax Tree - a representation of the PHP program, as written")));
	pm->add_ast_pass (new Process_includes (false, s("ast"), pm, s("incl1")));
	pm->add_ast_pass (new Pretty_print ());

	// Begin lowering to hir
	pm->add_ast_visitor (new Strip_comments (), s("decomment"), s("Remove comments"));
	pm->add_ast_visitor (new Strip_unparser_attributes (), s("sua"), s("Remove the attributes used to pretty-print source code"));
	pm->add_ast_visitor (new Note_top_level_declarations (), s("ntld"), s("Make a note of top-level-declarations before the information is lost"));

	// Small optimization on the AST
	pm->add_ast_transform (new Constant_folding(), s("const-fold"), s("Fold constant expressions"));
	pm->add_ast_transform (new Remove_concat_null (), s("rcn"), s("Remove concatentations with \")\""));



	// Make simple statements simpler
	pm->add_ast_transform (new Split_multiple_arguments (), s("sma"), s("Split multiple arguments for globals, attributes and static declarations"));
	pm->add_ast_transform (new Split_unset_isset (), s("sui"), s("Split unset() and isset() into multiple calls with one argument each"));
	pm->add_ast_transform (new Echo_split (), s("ecs"), s("Split echo() into multiple calls with one argument each"));
	pm->add_ast_transform (new Translate_empty (), s("empty"), s("Translate calls to empty() into casts"));

	pm->add_ast_transform (new Early_lower_control_flow (), s("elcf"), s("Early Lower Control Flow - lower for, while, do and switch statements")); // AST
	pm->add_ast_transform (new Lower_expr_flow (), s("lef"), s("Lower Expression Flow - Lower ||, && and ?: expressions"));
	pm->add_ast_transform (new Desugar (), s("desug"), s("Desugar"));
	pm->add_ast_transform (new Pre_post_op_shredder (), s("pps"), s("Shred pre- and post-ops, removing post-ops"));
	pm->add_ast_transform (new List_shredder (), s("lish"), s("List shredder - simplify to array assignments"));
	pm->add_ast_transform (new AST::Shredder (), s("ashred"), s("Shredder - turn the AST into three-address-code, replacing complex expressions with a temporary variable"));
	pm->add_ast_transform (new Tidy_print (), s("tidyp"), s("Replace calls to echo() and print() with printf()"));
	pm->add_ast_pass (new Fake_pass (s("AST-to-HIR"), s("The HIR in AST form")));


	pm->add_hir_pass (new Fake_pass (s("hir"), s("High-level Internal Representation - the smallest subset of PHP which can represent the entire language")));
	pm->add_hir_transform (new Copy_propagation (), s("prc"), s("Propagate copies - Remove some copies introduced as a result of lowering"));
	pm->add_hir_transform (new Dead_code_elimination (), s("dce"), s("Dead code elimination - Remove some copies introduced by lowered"));
	pm->add_hir_transform (new Lower_control_flow (), s("lcf"), s("Lower Control Flow - Use gotos in place of loops, ifs, breaks and continues"));


	// process_hir passes
	pm->add_hir_pass (new Obfuscate ()); // TODO move to MIR
	pm->add_hir_pass (new Fake_pass (s("HIR-to-MIR"), s("The MIR in HIR form")));


	// codegen passes
	// Use ss to pass generated code between Generate_C and Compile_C
	pm->add_mir_pass (new Fake_pass (s("mir"), s("Medium-level Internal Representation - simple code with high-level constructs lowered to straight-line code.")));
//	pm->add_mir_pass (new Process_includes (true, new String ("mir"), pm, "incl2"));
	pm->add_mir_transform (new Lift_functions_and_classes (), s("lfc"), s("Move statements from global scope into __MAIN__ method"));
	pm->add_mir_visitor (new Clarify (), s("clar"), s("Clarify - Make implicit defintions explicit"));
	pm->add_mir_visitor (new Prune_symbol_table (), s("pst"), s("Prune Symbol Table - Note whether a symbol table is required in generated code"));
	stringstream ss;
	pm->add_mir_pass (new Generate_C (ss));
	pm->add_mir_pass (new Compile_C (ss));


	// Plugins add their passes to the pass manager
	init_plugins (pm);

	// All the passes are added, so check the dumping options
#define check_passes(FLAG)																		\
	for (unsigned int i = 0; i < args_info.FLAG##_given; i++)				\
	{																									\
		if (! pm->has_pass_named (new String (args_info.FLAG##_arg [i])))			\
			phc_error ("No " #FLAG " pass named %s", args_info.FLAG##_arg [i]);	\
	}
	check_passes (dump);
	check_passes (udump);
	check_passes (xdump);
	check_passes (ddump);
	check_passes (debug);
	check_passes (disable);

#undef check_passes

	// Disable passes if asked
	for (unsigned int i = 0; i < args_info.disable_given; i++)
	{
		pm->get_pass_named (s(args_info.disable_arg [i]))->set_enabled (false);
	}



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
				if (not pm->has_pass_named (pass_name))
					phc_error ("Specified pass %s is not valid", pass_name->c_str ());

				if (pm->is_ast_pass (pass_name))
				{
					AST_XML_parser parser;
					if(args_info.inputs_num == 0)
						ir = parser.parse_xml_stdin();
					else
						ir = parser.parse_xml_file (filename);
				}
				else if (pm->is_hir_pass (pass_name))
				{
					HIR_XML_parser parser;
					if(args_info.inputs_num == 0)
						ir = parser.parse_xml_stdin();
					else
						ir = parser.parse_xml_file (filename);
				}
				else if (pm->is_mir_pass (pass_name))
				{
					MIR_XML_parser parser;
					if(args_info.inputs_num == 0)
						ir = parser.parse_xml_stdin();
					else
						ir = parser.parse_xml_file (filename);
				}
				pm->run_from (pass_name, ir, true);
			#endif
		}
		else
		{
			ir = parse (filename, NULL);

			// print error
			if (ir == NULL)
				if (args_info.inputs_num != 0)
					phc_error("File not found", filename, 0);
				else
					return -1;

			// run passes
			pm->run (ir, true);
		}

		pm->post_process ();
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
				NULL, 0, name, default_err, cwd_err, datadir_err);
		}

		// Save for later
		pm->add_plugin (handle, s(name), s(option));

	}
}
