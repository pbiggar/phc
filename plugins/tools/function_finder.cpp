/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Printout any impure function calls in a given script
 */


#include "MIR_visitor.h"
#include "pass_manager/Plugin_pass.h"
#include "process_ir/General.h"
#include "embed/embed.h"

using namespace MIR;
using namespace std;

// search for scripts that are "pure"; ie have no side effects
class Function_finder : public Visitor
{
	void post_method_invocation (Method_invocation *in)
	{
		if (in->target == NULL && isa<METHOD_NAME> (in->method_name))
		{
			METHOD_NAME* name = dyc<METHOD_NAME> (in->method_name);
			Method_info* info = PHP::get_method_info (name->value);
			if (info)
			{
				cout << *name->value << endl;
			}
		}
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("mir"));
}

extern "C" void run_mir (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Function_finder ());
}
