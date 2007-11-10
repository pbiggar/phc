/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for unparsers
 */

#ifndef PHC_PHP_UNPARSER
#define PHC_PHP_UNPARSER

#include <iostream>
#include <iomanip>
#include <sstream>
#include "AST_visitor.h"

class PHP_unparser
{
// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	PHP_unparser(ostream& os = cout);

// Unparsing
protected:
	ostream& os;
	int indent_level;
	bool at_start_of_line;
	bool delayed_newline;

	void echo(const char* str);
	void echo_nl(const char* s);
	void echo(String* str);
	void echo_nl(String* str);

	void echo_delayed_newline();
	void clear_delayed_newline();

	void inc_indent();
	void dec_indent();
	void newline();
	void output_tabs();
	void empty_line();
	void space_or_newline();
};

#endif // PHC_PHP_UNPARSER 
