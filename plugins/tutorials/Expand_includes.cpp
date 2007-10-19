/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Pass_manager.h"
#include "parsing/parse.h"
#include "process_ast/XML_unparser.h"

class Expand_includes : public AST_transform
{
private:
	XML_unparser* xml_unparser;
	Wildcard<Token_string>* filename;
	AST_method_invocation* pattern;

public:
	Expand_includes()
	{
		xml_unparser = new XML_unparser(cout, false);

		filename = new Wildcard<Token_string>;
		pattern = 
			new AST_method_invocation(
				NULL,
				new Token_method_name(new String("include")),
				new List<AST_actual_parameter*>(
					new AST_actual_parameter(false, filename)
				)
			);
	}

public:
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		// in->visit(xml_unparser);

		// Check for calls to include
		if(in->expr->match(pattern))
		{
			// Matched! Try to parse the file 
			AST_php_script* php_script = parse(filename->value->value, NULL, false);
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
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->transform_children (new Expand_includes ());
}
