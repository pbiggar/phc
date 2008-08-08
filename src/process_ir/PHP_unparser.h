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
protected:
	// This should be accessible to the PHP_unparser
	class Unparser_state
	{
		public:
			Unparser_state (ostream& os = cout, bool in_php = false);

		public:
			bool at_start_of_line;
			bool in_php;

		public:
			ostream& os;
			int indent_level;
			bool delayed_newline;
	};


// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	PHP_unparser(ostream& os = cout, bool in_php = false);
	PHP_unparser(Unparser_state* ups);

	Unparser_state* ups;

	// unparse the node
	virtual void unparse (IR::Node* in) = 0;

	// Other unparsers can call this unparser to unparse Foreign nodes from
	// their IR.
	virtual void unparse_foreign (IR::Node* in) = 0;

// Interface
protected:
	void echo(const char* str);
	void echo_nl(const char* s);
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

// Escaping a string
public:
	static String* escape_dq(String* s);
	static String* escape_sq(String* s);

	virtual ~PHP_unparser () {}

};

#endif // PHC_PHP_UNPARSER 
