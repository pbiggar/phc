/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare the semantic value of tokens against their source representation
 */

#include "AST_visitor.h"

class Get_source_and_semantic_values : public AST_visitor
{
public:
	void pre_php_script(AST_php_script* in)
	{
		printf("<?php\n\n$success = true;\n\n");
	}

	void post_php_script(AST_php_script* in)
	{
		printf(	"if($success)\n"
				"{\n"
				"\tprint(\"Success\\n\");\n"
				"}\n"
				"else\n"
				"{\n"
				"\tprint(\"Failure\\n\");\n"
				"}\n"
				"\n?>");
	}

	void print_comparison(String* type, String* value, String* source)
	{
		printf ("\tif(%s !== %s)\n", value->c_str(), source->c_str());
		printf ("\t{\n");
		printf ("\t\t$success = false;\n");
		printf ("\t\tprint \"Failure (%s): ", type->c_str());
		printf ("'%s' (\".gettype(%s).\": \".(%s).\") vs ", value->c_str(), value->c_str(), value->c_str());
		printf ("'%s' (\".gettype(%s).\": \".(%s).\"))\\n\";\n", source->c_str(), source->c_str(), source->c_str());
		printf ("\t}\n\n");
	}

	void pre_int(Token_int* in)
	{
		// We skip __LINE__, because we cannot check whether in->value is correct 
		if(*in->get_source_rep() == "__LINE__")
			return;

		print_comparison(new String("Token_int"), in->get_value_as_string(), in->get_source_rep());
	}

	void pre_bool(Token_bool* in)
	{
		print_comparison(new String("Token_bool"), in->get_value_as_string(), in->get_source_rep());
	}

	void pre_real(Token_real* in)
	{
		print_comparison(new String("Token_real"), in->get_value_as_string(), in->get_source_rep());
	}
};

extern "C" void process_ast(AST_php_script* script)
{
	Get_source_and_semantic_values gsasv;
	script->visit(&gsasv);
}
