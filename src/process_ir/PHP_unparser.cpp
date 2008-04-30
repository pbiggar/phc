/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include <iostream>
#include <iomanip> 
#include "PHP_unparser.h" 
#include "cmdline.h"

extern struct gengetopt_args_info args_info;

using namespace std;

void PHP_unparser::echo(const char* str)
{
	echo (new String (str));
}

void PHP_unparser::echo_nl(const char* s)
{
	echo_nl (new String (s));
}

void PHP_unparser::echo(String* str)
{
	output_start_tag();
	if(delayed_newline) newline();
	output_tabs();
	os << *str;
}

void PHP_unparser::echo_nl(String* str)
{
	echo(str);
	newline();
}

void PHP_unparser::inc_indent()
{
	indent_level++;
	newline();
}

void PHP_unparser::dec_indent()
{
	indent_level--;
	newline();
}

void PHP_unparser::newline()
{
	if(!at_start_of_line)
	{
		at_start_of_line = true;
		os << endl;
	}

	clear_delayed_newline();
}

void PHP_unparser::output_tabs()
{
	if(at_start_of_line)
		for(long i = 0; i < indent_level; i++)
			os << args_info.tab_arg;

	at_start_of_line = false;
}

void PHP_unparser::empty_line()
{
	at_start_of_line = true;
	os << endl;
}

void PHP_unparser::space_or_newline()
{
	if(args_info.next_line_curlies_flag)
		newline();
	else
		echo(" ");
}

void PHP_unparser::echo_delayed_newline()
{
	delayed_newline = true;
}

void PHP_unparser::clear_delayed_newline()
{
	delayed_newline = false;
}

void PHP_unparser::output_start_tag()
{
	if(!in_php)
	{
		newline();
		os << "<?php\n";
		in_php = true;
	}
}

void PHP_unparser::output_end_tag()
{
	if(in_php)
	{
		newline();
		os << "?>\n";
		in_php = false;
	}
}

void PHP_unparser::echo_html(String* str)
{
	output_end_tag();
	os << *str;
}

PHP_unparser::PHP_unparser(ostream& os, bool in_php)
: in_php (in_php)
, os(os)
{
	indent_level = 0;
	at_start_of_line = true;
	delayed_newline = false;
}
	
String* PHP_unparser::escape_dq(String* s)
{
	stringstream os;

	string::iterator i;
	for(i = s->begin(); i != s->end(); i++)
	{
		switch(*i)
		{
			case '\n':
				os << "\\n";
				break;
			case '\r':
				os << "\\r";
				break;
			case '\t':
				os << "\\t";
				break;
			case '\\':
			case '$':
			case '"':
				os << "\\" << *i;
				break;
			default:
				if(*i < 32 || *i == 127)
				{
						os << "\\x" << setw(2) <<
							setfill('0') << hex << uppercase << (unsigned long int)(unsigned char)*i;
						os << resetiosflags(cout.flags());
				}
				else
					os << *i;
				break;
		}
	}
	
	return new String(os.str());	
}

String* PHP_unparser::escape_sq(String* s)
{
	stringstream os;

	string::iterator i;
	for(i = s->begin(); i != s->end(); i++)
	{
		switch (*i)
		{
			case '\'': // single quote
			case '\\': // backslash
				os << '\\' << *i;
				break;
			default:
				os << *i;
				break;
		}
	}
	
	return new String(os.str());	
}
