/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare the semantic value of tokens against their source representation
 */

/* We assume that both plugins are run, and start the output in the first entry
 * method, and finish it in the last */

#include "process_ast/Pass_manager.h"

class Get_source_and_semantic_values : public AST_visitor
{
public:
	void print_comparison(String* type, String* value, String* source)
	{
		printf ("\tif(%s !== %s)\n", value->c_str(), source->c_str());
		printf ("\t{\n");
		printf ("\t\t$success = false;\n");
		printf ("\t\tprint \"Failure (%s): ", type->c_str());
		printf ("value: '%s' (\".gettype(%s).\": \".(%s).\") vs ", value->c_str(), value->c_str(), value->c_str());
		printf ("source: '%s' (\".gettype(%s).\": \".(%s).\"))\\n\";\n", source->c_str(), source->c_str(), source->c_str());
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

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);

	// print a header
	cout << "<?php\n\n$success = true;\n\n";
}


extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->visit(new Get_source_and_semantic_values ());
}

extern "C" void unload ()
{
	// print the footer
	cout <<	"if($success)\n"
				"{\n"
				"\tprint(\"Success\\n\");\n"
				"}\n"
				"else\n"
				"{\n"
				"\tprint(\"Failure\\n\");\n"
				"}\n"
				"\n?>";
}
