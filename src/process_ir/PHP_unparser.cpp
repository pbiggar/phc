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

void PHP_unparser::echo(string str)
{
	echo (new String (str));
}

void PHP_unparser::echo_nl(string s)
{
	echo_nl (new String (s));
}

void PHP_unparser::echo(String* str)
{
	output_start_tag();
	if(ups->delayed_newline) newline();
	output_tabs();
	ups->os << *str;
}

void PHP_unparser::echo_nl(String* str)
{
	echo(str);
	newline();
}

void PHP_unparser::inc_indent()
{
	ups->indent_level++;
	newline();
}

void PHP_unparser::dec_indent()
{
	ups->indent_level--;
	newline();
}

void PHP_unparser::newline()
{
	if(!ups->at_start_of_line)
	{
		ups->at_start_of_line = true;
		ups->os << endl;
	}

	clear_delayed_newline();
}

void PHP_unparser::output_tabs()
{
	if(ups->at_start_of_line)
		for(long i = 0; i < ups->indent_level; i++)
			ups->os << args_info.tab_arg;

	ups->at_start_of_line = false;
}

void PHP_unparser::empty_line()
{
	ups->at_start_of_line = true;
	ups->os << endl;
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
	ups->delayed_newline = true;
}

void PHP_unparser::clear_delayed_newline()
{
	ups->delayed_newline = false;
}

void PHP_unparser::output_start_tag()
{
	if(!ups->in_php)
	{
		newline();
		ups->os << "<?php\n";
		ups->in_php = true;
	}
}

void PHP_unparser::output_end_tag()
{
	if(ups->in_php)
	{
		newline();
		ups->os << "?>\n";
		ups->in_php = false;
	}
}

void PHP_unparser::echo_html(String* str)
{
	output_end_tag();
	ups->os << *str;
}

PHP_unparser::PHP_unparser(ostream& os, bool in_php)
{
	ups = new Unparser_state (os, in_php);
}

PHP_unparser::PHP_unparser(Unparser_state* ups)
: ups (ups)
{
}

Unparser_state::Unparser_state (ostream& os, bool in_php)
: in_php (in_php)
, os(os)
{
	indent_level = 0;
	at_start_of_line = true;
	delayed_newline = false;
}
	

