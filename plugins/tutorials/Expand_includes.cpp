/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "parsing/parse.h"
#include "AST_transform.h"
#include "process_ir/General.h"
#include <cstdlib>

using namespace AST;
using namespace std;

class Expand_includes : public Transform
{
private:
	Wildcard<STRING>* filename;
	Method_invocation* pattern;

public:
	Expand_includes()
	{
		filename = new Wildcard<STRING>;
		pattern = 
			new Method_invocation(
				NULL,
				new METHOD_NAME(new String("include")),
				new List<Actual_parameter*>(
					new Actual_parameter(false, filename)
				)
			);
	}

public:
	void pre_eval_expr(Eval_expr* in, List<Statement*>* out)
	{
		// xdebug (in);

		// Check for calls to include
		if(in->expr->match(pattern))
		{
			// Matched! Try to parse the file 
			PHP_script* php_script = parse(filename->value->value, NULL);
			if(php_script == NULL)
			{
				cerr 
				<< "Could not parse file " << *filename->value->value
				<< " on line " << in->get_line_number() << endl;
				exit(-1);
			}

			// Replace the include by the statements in the parsed file
			out->push_back_all(php_script->statements);
		}
		else
		{
			// No match; leave untouched
			out->push_back(in);
		}
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->transform_children (new Expand_includes ());
}
