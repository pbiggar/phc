/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the Macro inline code generator.
 */

#include "MICG_parser.h"

// Uncomment to debug parsing. Useful for finding bugs in the parsed data as
// well as in the parser.
//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_PRINT_SOME 80

#include <boost/spirit.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "lib/error.h"
#include "process_ir/debug.h"

using namespace std;
using namespace boost::spirit;
using namespace boost;


MICG_parser::MICG_parser ()
{
}

struct skip_grammar : public grammar<skip_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		rule<ScannerT> skip;

		definition (skip_grammar const& self)
		{
			BOOST_SPIRIT_DEBUG_TRACE_NODE(skip, false);
			skip = space_p | comment_p ("//") | comment_p ("/*", "*/");
		}

		rule<ScannerT> const& start() const
		{ 
			return skip;
		}
	};
};


void r_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("r: " << value);
}

void pattern_name_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("pattern_name: " << value);
}

void type_name_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("type_name: " << value);
}

void param_name_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("param_name: " << value);
}

void signature_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("signature: " << value);
}

void attr_name_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("attr_name: " << value);
}

void equals_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("equals: " << value);
}

void lookup_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("lookup: " << value);
}

void expr_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("expr: " << value);
}

void rule_line_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("rule_line: " << value);
}

void symbol_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("symbol: " << value);
}

void _template_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("_template: " << value);
}

void base_expr_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("base_expr: " << value);
}

void C_code_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("C_code: " << value);
}

void macro_call_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("macro_call: " << value);
}

void interpolation_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("interpolation: " << value);
}

void quoted_string_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("quoted_string: " << value);
}

void body_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first, last);
	DEBUG ("body_string: " << value);
}



/*
 * Limitations:
 *		- Its hard to put {} around the body of a template. Use @@@ instead.
 *		- Bodies must have at least one character, though it can be a space.
 *		- Quoted strings dont support escaping of '"'. However, a quoted string
 *		is only used as a parameter to a macro, so thats not a great problem.
 */
struct MICG_grammar : public grammar<MICG_grammar>
{
	template <typename ScannerT>
	struct definition
	{
		rule<ScannerT> r, pattern_name, type_name, param_name, signature,
			attr_name, equals, lookup, expr, rule_line, symbol,
			_template, base_expr, C_code, macro_call, interpolation, quoted_string, body;

		definition (MICG_grammar const& self)
		{
			BOOST_SPIRIT_DEBUG_RULE(r);
			BOOST_SPIRIT_DEBUG_RULE(pattern_name);
			BOOST_SPIRIT_DEBUG_RULE(type_name);
			BOOST_SPIRIT_DEBUG_RULE(param_name);
			BOOST_SPIRIT_DEBUG_RULE(signature);
			BOOST_SPIRIT_DEBUG_RULE(attr_name);
			BOOST_SPIRIT_DEBUG_RULE(equals);
			BOOST_SPIRIT_DEBUG_RULE(lookup);
			BOOST_SPIRIT_DEBUG_RULE(expr);
			BOOST_SPIRIT_DEBUG_RULE(rule_line);
			BOOST_SPIRIT_DEBUG_RULE(symbol);
			BOOST_SPIRIT_DEBUG_RULE(_template);
			BOOST_SPIRIT_DEBUG_RULE(base_expr);
			BOOST_SPIRIT_DEBUG_RULE(C_code);
			BOOST_SPIRIT_DEBUG_RULE(macro_call);
			BOOST_SPIRIT_DEBUG_RULE(interpolation);
			BOOST_SPIRIT_DEBUG_RULE(quoted_string);
			BOOST_SPIRIT_DEBUG_RULE(body);



			// A signature line
			pattern_name = lexeme_d[+(alpha_p | '_')][&pattern_name_a];
			type_name = lexeme_d[+lower_p][&type_name_a];
			param_name = lexeme_d[+(upper_p | '_')][&param_name_a];
			signature = (pattern_name >> '(' >> list_p(type_name >> param_name, ",") >> ')')[&signature_a];

			// A rule line
			attr_name = lexeme_d[+(alpha_p | '_')][&attr_name_a];
			symbol = lexeme_d[+(alpha_p | '_')][&symbol_a];
			lookup = (param_name >> "." >> attr_name)[&lookup_a];
			base_expr = (lookup | symbol | param_name)[&base_expr_a];
			expr = (base_expr >> !("==" >> base_expr))[&expr_a];
			rule_line = "where" >> expr;

			// Bodies
			C_code = lexeme_d[anychar_p - ch_p('@')][&C_code_a];

			quoted_string = confix_p ('"', *anychar_p, '"')[&quoted_string_a];
			macro_call = (ch_p('\\') >> pattern_name >> '('
				>> list_p (param_name | quoted_string, ", ") >> ch_p(')') >> ';')[&macro_call_a];

			interpolation = (('$' >> param_name) | ("${" >> lookup >> '}'))[&interpolation_a];

			// A template
			body = "@@@" >> *(macro_call | interpolation | C_code) >> "@@@";
			_template = signature >> *rule_line >> body;

			r = *_template;
		}

		rule<ScannerT> const& start() const
		{ 
			return r;
		}
	};
};


void
MICG_parser::parse (string str)
{
	// By using a phrase parser with a white-space skip, comments are ignored,
	// and we can ignore white space.

	MICG_grammar g;
	skip_grammar skipg;

	BOOST_SPIRIT_DEBUG_GRAMMAR(g);
	BOOST_SPIRIT_DEBUG_TRACE_NODE(skipg, false);

	parse_info<> pi = boost::spirit::parse (str.c_str(), g >> end_p, skipg);

#ifdef BOOST_SPIRIT_DEBUG
	cout
	<< "stop: " << string (pi.stop).substr (0,500) << "\n"
	<< "hit: " << pi.hit << "\n"
	<< "full: " << pi.full << "\n"
	<< "length: " << pi.length << "\n"
	;
#endif

	if (!pi.full)
		phc_internal_error ("Cannot parse template at %s", string (pi.stop).substr (0,100).c_str ());
}

