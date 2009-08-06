/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Find evals and dynamic includes.
 */


#include "AST_visitor.h"
#include "process_ast/AST_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "lib/List.h"
#include "process_ir/General.h"

using namespace AST;
using namespace std;

class Dynamic_things : virtual public GC_obj, public Visitor
{
public:

	// "Analysis" results
	int calls_to_eval;
	int calls_to_include;
	int calls_to_dynamic_include;

	// Used during traversal
	bool include_is_dynamic;
	Method_invocation* include;

	Dynamic_things ()
	: calls_to_eval (0)
	, calls_to_include (0)
	, calls_to_dynamic_include (0)
	, include_is_dynamic (false)
	, include (NULL)
	{
	}

	void pre_method_invocation (Method_invocation *in)
	{
		// Includes and evals are never like this
		if (in->target || not isa<METHOD_NAME> (in->method_name))
			return;

		// This isnt very likely, but we dont want to break things.
		if (include)
			return;


		String* name = dyc<METHOD_NAME> (in->method_name)->value;

		if (*name == "eval")
		{
			calls_to_eval++;
		}
		else if (*name == "include"
				|| *name == "include_once"
				|| *name == "require"
				|| *name == "require_once")
		{
			calls_to_include++;
			include_is_dynamic = false; // check in the post_method_invocation
			include = in;
		}
	}

	void pre_expr (Expr* in)
	{
		if (not include)
			return;

		/*
		 * What constitutes dynamic?
		 */
		if (not (
				isa<Constant> (in) || isa<Literal> (in) // these are OK
			|| isa<Bin_op> (in) || isa<Unary_op> (in) || isa<Cast> (in))) // lets see the subexprs
		{
			include_is_dynamic = true;
		}
	}


	void post_method_invocation (Method_invocation *in)
	{
		if (include == in)
		{
			if (include_is_dynamic)
			{
				calls_to_dynamic_include++;
				include_is_dynamic = false;
			}

			include = NULL;
		}
	}



	void post_php_script (PHP_script* in)
	{
		cout
			<< *in->get_filename () << ":"
			<< calls_to_eval << ","
			<< calls_to_include << ","
			<< calls_to_dynamic_include
			<< endl;

		// Dont care anymore.
		exit (0);
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("incl1"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Dynamic_things ());
}
