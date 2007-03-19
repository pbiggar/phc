/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include <iostream>
#include "AST_transform.h"
#include "parsing/parse.h"

class Expand_includes : public AST_transform
{
public:
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		// Pattern to match include statements	
		Token_string* filename; 
		AST_actual_parameter* param;
		List<AST_actual_parameter*>* params;
		Token_method_name* method_name;
		Token_class_name* target; 
		AST_method_invocation* pattern;
		
		filename = new Token_string(NULL, NULL);
		param = new AST_actual_parameter(false, filename);
		params = new List<AST_actual_parameter*>;
		params->push_back(param);
		method_name = new Token_method_name(new String("include"));
		target = new Token_class_name(new String("%STDLIB%"));
		pattern = new AST_method_invocation(target, method_name, params);	
	
		// Check we have a matching function
		if(!in->expr->match(pattern))
		{
			// No match; leave untouched
			out->push_back(in);
		}
		else
		{
			AST_php_script* php_script = parse(filename->value, NULL, false);
			if(php_script == NULL)
			{
				cout << "Could not parse file " << *filename->value;
				cout << " on line " << in->get_line_number() << endl;
				exit(-1);
			}

			// Include all statements in %MAIN%::%run% at the location of the include
			AST_class_def* main = php_script->get_class_def("%MAIN%");
			AST_method* run = main->get_method("%run%");
			out->push_back_all(run->statements);
		}
	}
};

extern "C" void process_ast(AST_php_script* php_script)
{
	Expand_includes einc;
	php_script->transform(&einc);
}
