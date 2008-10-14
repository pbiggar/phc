/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compare the semantic value of tokens against their source representation
 */

/* We assume that both plugins are run, and start the output in the first entry
 * method, and finish it in the last */

#include "AST_visitor.h"
#include "pass_manager/Plugin_pass.h"

using namespace AST;
using namespace std;

class Get_source_and_semantic_values : public Visitor
{
public:
	void print_comparison(String* type, String* value, String* source)
	{
		if (*value != *source)
			cout 
				<< "test ("
				<< '"' << *type	<< "\", "
				<< '"' << *value	<< "\", "
				<< *value	<< ", "
				<< '"' << *source	<< "\", "
				<< *source	<< ");" << endl;
	}

	void pre_int(INT* in)
	{
		// We skip __LINE__, because we cannot check whether in->value is correct 
		if(*in->get_source_rep() == "__LINE__")
			return;

		print_comparison(new String("INT"), in->get_value_as_string(), in->get_source_rep());
	}

	void pre_bool(BOOL* in)
	{
		print_comparison(new String("BOOL"), in->get_value_as_string(), in->get_source_rep());
	}

	void pre_real(REAL* in)
	{
		print_comparison(new String("REAL"), in->get_value_as_string(), in->get_source_rep());
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_ast_pass (pass);

	// print a header
	cout 
		<< "<?php\n"
		<< "function test ($type, $value_str, $value, $source_str, $source)\n"
		<< "{\n"
		<< "	if($value !== $source)\n"
		<< "	{\n"
		<< "		print \"Failure ($type)): \"\n"
		<<	"			. \"value: '$value_str' (\"\n"
		<< "			. gettype($value)\n"
		<< "			. \"): $value) vs \"\n"
		<< "			. \"value: '$source_str' (\"\n"
		<< "			. gettype($source)\n"
		<< "			. \"): $source)\";\n"
		<< "		die (-1);\n"
		<< "	}\n"
		<< "}" << endl;
}


extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Get_source_and_semantic_values ());
}

extern "C" void unload ()
{
	// print the footer
	cout 
		<< "print(\"Success\\n\");\n"
		<< "?>";
}
