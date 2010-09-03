/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We dont optimize the __MAIN__ method, but most of our tests dont have
 * methods. So move all the code into a method, and call that. Programs wont
 * work the same, but we'll be able to test by comparing php and phc.
 */

#include "process_ir/General.h"
#include "pass_manager/Plugin_pass.h"
#include "MIR_visitor.h"

using namespace MIR;

class Raise_globals : public Visitor
{
	Method* new_main;

	void pre_method (Method* in)
	{
		if (*in->signature->method_name->value != "__MAIN__")
			return;

		new_main->statements = in->statements;

		// Add a call to new__MAIN__
		in->statements = new Statement_list;
		in->statements->push_back (
				new Eval_expr (
					new Method_invocation (
						NULL,
						new METHOD_NAME ("new__MAIN__"),
						new Actual_parameter_list)));
	}

	void pre_php_script (PHP_script* in)
	{
		// Move statements from __MAIN__ to new__MAIN__
		new_main =
			new Method (
					new Signature (
						new Method_mod,
						false,
						false,
						new METHOD_NAME ("new__MAIN__"),
						new Formal_parameter_list),
					new Statement_list);

		new_main->attrs->set_true ("phc.lower_control_flow.top_level_declaration");

		in->statements->push_front (new_main);
	}
};

void run (PHP_script* in)
{
	in->visit (new Raise_globals);
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*, String* option)
{
	run (in);
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	// Just after __MAIN__ is created.
	pm->add_after_named_pass (pass, s("lfc"));
}
