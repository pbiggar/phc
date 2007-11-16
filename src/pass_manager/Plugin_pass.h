/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A pass to wrap plugins.
 */

#ifndef PHC_PLUGIN_PASS_H
#define PHC_PLUGIN_PASS_H

#include "Pass.h"
#include "Pass_manager.h"

class Plugin_pass : public Pass
{
	lt_dlhandle handle;
	String* option;
public:

	Plugin_pass (String* name, lt_dlhandle handle, Pass_manager* pm, String* option);
	void run (IR* in, Pass_manager* pm);
	void post_process ();

};





#endif // PHC_PLUGIN_PASS_H
