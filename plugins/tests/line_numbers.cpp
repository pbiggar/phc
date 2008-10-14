/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Printout all the tokens with their line numbers.
 */

#include "AST_visitor.h"
#include "pass_manager/Plugin_pass.h"
#include "process_ir/General.h"

using namespace AST;
using namespace std;

class Print_line_numbers : public Visitor
{
	String delimiter;
	bool read;
public:

	Print_line_numbers()
		:	delimiter("--!!--!!--"),
			read(false)
	{
		
	}

	void pre_if(If* in)
	{
		cout << "if:" << in->get_line_number() << delimiter;
	}

	void pre_while(While* in)
	{
		cout << "while:" << in->get_line_number() << delimiter;
	}

	void pre_do(Do* in)
	{
		cout << "do:" << in->get_line_number() << delimiter;
	}

	void pre_for(For* in)
	{
		cout << "for:" << in->get_line_number() << delimiter;
	}

	void pre_foreach(Foreach* in)
	{
		cout << "foreach:" << in->get_line_number() << delimiter;
	}

	void pre_switch(Switch* in)
	{
		cout << "switch:" << in->get_line_number() << delimiter;
	}

	void pre_switch_case(Switch_case* in)
	{
		cout << "case:" << in->get_line_number() << delimiter;
	}

	void pre_break(Break* in)
	{
		cout << "break:" << in->get_line_number() << delimiter;
	}

	void pre_continue(Continue* in)
	{
		cout << "continue:" << in->get_line_number() << delimiter;
	}

	void pre_return(Return* in)
	{
		cout << "return:" << in->get_line_number() << delimiter;
	}

	void pre_try(Try* in)
	{
		cout << "try:" << in->get_line_number() << delimiter;
	}

	void pre_catch(Catch* in)
	{
		cout << "catch:" << in->get_line_number() << delimiter;
	}

	void pre_throw(Throw* in)
	{
		cout << "throw:" << in->get_line_number() << delimiter;
	}

	void pre_new(New* in)
	{
		cout << "new:" << in->get_line_number() << delimiter;
	}

	void pre_interface_name(INTERFACE_NAME* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_class_name(CLASS_NAME* in)
	{
		String* class_name = in->value;
		if (*class_name != "%MAIN%" and *class_name != "%STDLIB%")
		{
			cout << *class_name << ":" << in->get_line_number() << delimiter;
		}
	}

	void pre_method_name(METHOD_NAME* in)
	{
		/* this could also check that it's in the main class, but its a tad
		 * complicated for the incredibly limited benefit
		 */
		String* method_name = in->value;
		if (*method_name != "%run%") 
		{
			cout << *method_name << ":" << in->get_line_number() << delimiter;
		}
	}

	void pre_variable_name(VARIABLE_NAME* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_directive_name(DIRECTIVE_NAME* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_cast(CAST* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_op(OP* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_constant_name(CONSTANT_NAME* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_string(STRING* in)
	{
		string::iterator i;
		/* We cant use the PHP_unparser here, since that adds "'"s in
		 * interpolated strings. All the code is taken from PHP_unparser, and
		 * could be refactored at a later date. */
		String *s = in->get_source_rep(); // deals with the __FILE__ problem.
		for(i = s->begin(); i != s->end(); i++)
		{
			switch(*i)
			{
				case '\n':
					cout << "\\n";
					break;
				case '\r':
					cout << "\\r";
					break;
				case '\t':
					cout << "\\t";
					break;
				case '\\':
				case '$':
				case '"':
					cout << "\\" << *i;
					break;
				default:
					if(*i < 32 || *i == 127)
					{
						cout << "\\x" << setw(2) <<
							setfill('0') << hex << uppercase << (unsigned long int)(unsigned char)*i;
						cout << resetiosflags(cout.flags());
					}
					else
						cout << *i;
					break;
			}
		}
		cout << ":" << in->get_line_number() << delimiter;
	}

	void pre_int (INT* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

	void pre_real (REAL* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

	void pre_bool (BOOL* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

	void pre_null (NIL* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Print_line_numbers ());
	cout << endl;
}
