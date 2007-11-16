/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all include (), require (), include_once () and require_once ()
 * statements.
 */

#include "pass_manager/Plugin_pass.h"

using namespace AST;

class Strip_includes : public AST_transform
{
public:
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
	{
		Wildcard<Token_string>* token_filename = new Wildcard<Token_string>;
		Wildcard<Token_method_name>* method_name = new Wildcard<Token_method_name>;

		// the filename is the only parameter of the include statement

		// TODO this code is much duplicated
		if (in->expr->match (new AST_method_invocation(
				NULL,
				method_name,
				new List<AST_actual_parameter*>(
					new AST_actual_parameter(false, token_filename)
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
	pm->add_after_named_pass (pass, "incl2");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->transform_children (new Strip_includes ());

}
