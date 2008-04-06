/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A pass to wrap plugins.
 */

#ifndef PHC_PLUGIN_PASS_H
#define PHC_PLUGIN_PASS_H

#include "Pass_manager.h"

class Plugin_pass : public Pass
{
	lt_dlhandle handle;
	String* option;
public:

	Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option);
	void run (IR::PHP_script* in, Pass_manager* pm);
	void post_process ();

};

// declare these for type checking
extern "C" void load (Pass_manager* pm, Plugin_pass* pass);
extern "C" void unload ();
extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option);
extern "C" void run_hir (HIR::PHP_script* in, Pass_manager* pm, String* option);
extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option);




#endif // PHC_PLUGIN_PASS_H
