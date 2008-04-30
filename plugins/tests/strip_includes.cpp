/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all include (), require (), include_once () and require_once ()
 * statements.
 */

#include "pass_manager/Plugin_pass.h"
#include "pass_manager/Pass_manager.h"
#include "AST_transform.h"
#include "process_ir/General.h"

using namespace AST;

class Strip_includes : public Transform
{
public:
	void pre_eval_expr (Eval_expr* in, List<Statement*>* out)
	{
		Wildcard<STRING>* token_filename = new Wildcard<STRING>;
		Wildcard<METHOD_NAME>* method_name = new Wildcard<METHOD_NAME>;

		// the filename is the only parameter of the include statement

		// TODO this code is much duplicated
		if (in->expr->match (new Method_invocation(
				NULL,
				method_name,
				new List<Actual_parameter*>(
					new Actual_parameter(false, token_filename)
					)
				))
				and (*(method_name->value->value) == "include"
					or *(method_name->value->value) == "include_once"
					or *(method_name->value->value) == "require"
					or *(method_name->value->value) == "require_once"))
		{
			// empty
		}
		else
		{
			out->push_back (in);
		}
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	// TODO after incl2 goes back in, put this back to incl2.
	pm->add_after_named_pass (pass, s("incl1"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->transform_children (new Strip_includes ());

}
