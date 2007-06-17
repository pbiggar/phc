/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Printout all the tokens with their line numbers.
 */

#include "process_ast/Pass_manager.h"
#include "process_ast/PHP_unparser.h"

class Print_line_numbers : public AST_visitor
{
	String delimiter;
	bool read;
public:

	Print_line_numbers()
		:	delimiter("--!!--!!--"),
			read(false)
	{
		
	}

	void pre_if(AST_if* in)
	{
		cout << "if:" << in->get_line_number() << delimiter;
	}

	void pre_while(AST_while* in)
	{
		cout << "while:" << in->get_line_number() << delimiter;
	}

	void pre_do(AST_do* in)
	{
		cout << "do:" << in->get_line_number() << delimiter;
	}

	void pre_for(AST_for* in)
	{
		cout << "for:" << in->get_line_number() << delimiter;
	}

	void pre_foreach(AST_foreach* in)
	{
		cout << "foreach:" << in->get_line_number() << delimiter;
	}

	void pre_switch(AST_switch* in)
	{
		cout << "switch:" << in->get_line_number() << delimiter;
	}

	void pre_switch_case(AST_switch_case* in)
	{
		cout << "case:" << in->get_line_number() << delimiter;
	}

	void pre_break(AST_break* in)
	{
		cout << "break:" << in->get_line_number() << delimiter;
	}

	void pre_continue(AST_continue* in)
	{
		cout << "continue:" << in->get_line_number() << delimiter;
	}

	void pre_return(AST_return* in)
	{
		cout << "return:" << in->get_line_number() << delimiter;
	}

	void pre_try(AST_try* in)
	{
		cout << "try:" << in->get_line_number() << delimiter;
	}

	void pre_catch(AST_catch* in)
	{
		cout << "catch:" << in->get_line_number() << delimiter;
	}

	void pre_throw(AST_throw* in)
	{
		cout << "throw:" << in->get_line_number() << delimiter;
	}

	void pre_new(AST_new* in)
	{
		cout << "new:" << in->get_line_number() << delimiter;
	}

	void pre_interface_name(Token_interface_name* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_class_name(Token_class_name* in)
	{
		String* class_name = in->value;
		if (*class_name != "%MAIN%" and *class_name != "%STDLIB%")
		{
			cout << *class_name << ":" << in->get_line_number() << delimiter;
		}
	}

	void pre_method_name(Token_method_name* in)
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

	void pre_variable_name(Token_variable_name* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_directive_name(Token_directive_name* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_cast(Token_cast* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_op(Token_op* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_constant_name(Token_constant_name* in)
	{
		cout << *in->value << ":" << in->get_line_number() << delimiter;
	}

	void pre_string(Token_string* in)
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

	void pre_int (Token_int* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

	void pre_real (Token_real* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

	void pre_bool (Token_bool* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

	void pre_null (Token_null* in)
	{
		cout << *in->get_source_rep() << ":" << in->get_line_number() << delimiter;
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->visit (new Print_line_numbers ());
	cout << endl;
}
