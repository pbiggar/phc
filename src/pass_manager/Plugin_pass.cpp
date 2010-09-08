/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A pass to wrap plugins.
 */

#include "Plugin_pass.h"
#include "lib/error.h"
#include "AST.h"
#include "HIR.h"
#include "MIR.h"


Plugin_pass::Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option)
{
	this->handle = handle;
	this->name = name;
	this->option = option;
}

void
Plugin_pass::run_pass (IR::PHP_script* in, Pass_manager* pm, bool main)
{
  // Don't call plugin passes except from the main pipeline pass.
  if (main)
    Pass::run_pass(in, pm, main);
}

void Plugin_pass::run (IR::PHP_script* in, Pass_manager* pm)
{
	/* The ltdl interface uses C, so overloading on type doesnt work. We must
	 * use different names instead. */
	if (in->is_AST ())
	{
		typedef void (*run_function)(AST::PHP_script*, Pass_manager*, String*); 
		run_function ast_func = (run_function) lt_dlsym(handle, "run_ast");

		if (not (ast_func))
			phc_error ("Plugins which operate on the AST must define a run_ast() function.");

		(*ast_func)(in->as_AST(), pm, option);
	}
	else if (in->is_HIR ())
	{
		typedef void (*run_function)(HIR::PHP_script*, Pass_manager*, String*);
		run_function hir_func = (run_function) lt_dlsym (handle, "run_hir");

		if (not (hir_func))
			phc_error ("Plugins which operate on the HIR must define a run_hir() function.");

		(*hir_func)(in->as_HIR (), pm, option);
	}
	else
	{
		typedef void (*run_function)(MIR::PHP_script*, Pass_manager*, String*);
		run_function mir_func = (run_function) lt_dlsym (handle, "run_mir");

		if (not (mir_func))
			phc_error ("Plugins which operate on the MIR must define a run_mir() function.");

		(*mir_func)(in->as_MIR (), pm, option);
	}
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
