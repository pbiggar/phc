/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * 
 */
#include "Plugin_pass.h"


Plugin_pass::Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option)
{
	this->handle = handle;
	this->name = name;
	this->option = option;
}

void Plugin_pass::run (IR* in, Pass_manager* pm)
{
	// RUN
	typedef void (*ast_function)(AST::PHP_script*, Pass_manager*, String*);
	ast_function ast_func = (ast_function) lt_dlsym(handle, "run");

	if (not (ast_func))
		phc_error ("A plugin must define the AST run () function");

	if (ast_func && in->is_AST())
		(*ast_func)(in->as_AST(), pm, option);

/*
	typedef void (*hir_function)(PHP_script*, Pass_manager*, String*);
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


