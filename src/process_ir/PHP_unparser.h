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

class Unparser_state : virtual public GC_obj
{
	public:
		Unparser_state (std::ostream& os, bool in_php);

	public:
		bool at_start_of_line;
		bool in_php;

	public:
		std::ostream& os;
		int indent_level;
		bool delayed_newline;
};

class PHP_unparser : virtual public GC_obj
{
// Constructor; pass in a different std::ostream to write to a file/string instead
// of standard output
public:
	PHP_unparser(std::ostream& os = std::cout, bool in_php = false);
	PHP_unparser(Unparser_state* ups);

	Unparser_state* ups;

	// unparse the node
	virtual void unparse (IR::Node* in) = 0;

// Interface
protected:
	void echo(string str);
	void echo_nl(string s);
	void echo(String* str);
	void echo_nl(String* str);

	void echo_delayed_newline();
	void clear_delayed_newline();

	void echo_html(String* str);
	void output_start_tag();
	void output_end_tag();

	void inc_indent();
	void dec_indent();
	void newline();
	void output_tabs();
	void empty_line();
	void space_or_newline();

	virtual ~PHP_unparser () {}

};

#endif // PHC_PHP_UNPARSER 
