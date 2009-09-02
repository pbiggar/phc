/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Find define()s, and output the key-value pair that is its parameters 
 */


#include "AST_visitor.h"
#include "process_ast/AST_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "lib/List.h"
#include "lib/Map.h"
#include "process_ir/General.h"

using namespace AST;
using namespace std;

class Get_defines: virtual public GC_obj, public Visitor
{
public:

	// Used during traversal
	Map <string, string> definitions;

	Get_defines ()
	{
	}

	void post_method_invocation (Method_invocation *in)
	{
		// define()s are never like this
		if (in->target || not isa<METHOD_NAME> (in->method_name))
			return;

		String* name = dyc<METHOD_NAME> (in->method_name)->value;

		if (*name == "define")
		{
			Actual_parameter_list* params = in->actual_parameters;
			if (params->size () == 2)
			{
				Literal* key = dynamic_cast<Literal*> (params->front ()->expr);
				Literal* value = dynamic_cast<Literal*> (params->back ()->expr);

				if (key && value)
				{
					foreach (char c, *key->get_value_as_string ())
						if (c == '\n' || c == '"' || c == '\'')
							return;
				
					foreach (char c, *value->get_value_as_string ())
						if (c == '\n' || c == '"' || c == '\'')
							return;

					definitions [*key->get_value_as_string ()] = *value->get_value_as_string ();
				}
			}
		}	
	}

	void post_php_script (PHP_script* in)
	{
		string s,t;
		foreach (tie (s,t), definitions)
			cout << s << "\\," << t << "\\|";
	
		exit (0);
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Get_defines ());
}
