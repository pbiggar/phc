/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test that the callbacks are only called once.
 */

#include "pass_manager/Plugin_pass.h"

using namespace std;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
	pm->add_after_named_pass (pass, s("hir"));
	pm->add_after_named_pass (pass, s("mir"));
}

static int ast_run_count = 0;
static int hir_run_count = 0;
static int mir_run_count = 0;

extern "C" void run_ast (AST::PHP_script* in, Pass_manager*, String* option)
{
  ast_run_count++;
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*, String* option)
{
  hir_run_count++;
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*, String* option)
{
  mir_run_count++;
}

extern "C" void unload ()
{
	if (ast_run_count == 1 and hir_run_count == 1 and mir_run_count == 1)
		printf("Success\n");
	else
		printf("Failure\n");
}
