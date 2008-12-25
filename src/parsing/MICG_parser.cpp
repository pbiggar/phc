/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the Macro inline code generator.
 */

#include "MICG_parser.h"

// Uncomment to debug parsing. Useful for finding bugs in the parsed data as
// well as in the parser.
#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_PRINT_SOME 80

#include <boost/spirit.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "lib/error.h"

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
			attr_name, equals, lookup, expr, rule_line, not_eol, empty_line, symbol,
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
			BOOST_SPIRIT_DEBUG_RULE(not_eol);
			BOOST_SPIRIT_DEBUG_RULE(empty_line);
			BOOST_SPIRIT_DEBUG_RULE(symbol);
			BOOST_SPIRIT_DEBUG_RULE(_template);
			BOOST_SPIRIT_DEBUG_RULE(base_expr);
			BOOST_SPIRIT_DEBUG_RULE(C_code);
			BOOST_SPIRIT_DEBUG_RULE(macro_call);
			BOOST_SPIRIT_DEBUG_RULE(interpolation);
			BOOST_SPIRIT_DEBUG_RULE(quoted_string);
			BOOST_SPIRIT_DEBUG_RULE(body);



			not_eol = ~ch_p ('\n') & ~ch_p ('\r');

			// A signature line
			pattern_name = lexeme_d[+(alpha_p | '_')];
			type_name = lexeme_d[+lower_p];
			param_name = lexeme_d[+(upper_p | '_')];
			signature = pattern_name >> '(' >> list_p(type_name >> param_name, ",") >> ')';

			// A rule line
			attr_name = lexeme_d[+(alpha_p | '_')];
			symbol = lexeme_d[+(alpha_p | '_')];
			lookup = param_name >> "." >> attr_name;
			base_expr = lookup | symbol | param_name;
			expr = base_expr >> !("==" >> base_expr);
			rule_line = "where" >> expr;

			// Bodies
			C_code = lexeme_d[(anychar_p - ch_p('@'))];

			quoted_string = confix_p ('"', *anychar_p, '"');
			macro_call = ch_p('\\') >> pattern_name >> '('
				>> list_p (param_name | quoted_string, ", ") >> ch_p(')') >> ';';

			interpolation = ('$' >> param_name) | ("${" >> lookup >> '}');

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

	cout
	<< "stop: " << string (pi.stop).substr (0,500) << "\n"
	<< "hit: " << pi.hit << "\n"
	<< "full: " << pi.full << "\n"
	<< "length: " << pi.length << "\n"
	;

	assert (0);
}
/*
void sexp_a (const char* first, const char* last)
{
	string sexp = string (first, last);
	DEBUG ("sexp: " << sexp);

	// Get the argument list
	int num_children = num_children_stack.top();
	num_children_stack.pop();

	List<Object*> args;

	for(int i = 0; i < num_children; i++)
	{
		args.push_front(node_stack.top());
		node_stack.pop();
	}

	// Get the classname
	String* classname = dyc<String> (node_stack.top());
	node_stack.pop ();

	// uppercase first lette
	(*classname)[0] = toupper ((*classname)[0]);


	// Now that we have the classname, just pass all the objects on the stack
	Object* result = LIR::Node_factory::create (classname->c_str (), &args);
	if (result == NULL)
		phc_internal_error ("Could not create object '%s', with sexp '%s",
			classname->c_str (),
			sexp.c_str());

	assert (result);

	node_stack.push (result);
	dump_stack ();

}

void classname_a (const char* first, const char* last)
{
	string classname = string (first, last);
	DEBUG ("classname: " << classname);

	// Just push the name, to be available for sexp.
	node_stack.push (new String (classname));
	dump_stack ();
	num_children_stack.top()++;
	num_children_stack.push(0);
}

void value_a (const char* first, const char* last)
{
	string value = string (first, last);
	DEBUG ("value: " << value);

	node_stack.push (new String (value));
	num_children_stack.top()++;
	dump_stack ();
}

void string_a (const char* first, const char* last)
{
	// take off the quotes
	string value = string (first+1, last-1);
	DEBUG ("string: " << value);

	node_stack.push (new String (value));
	num_children_stack.top()++;
	dump_stack ();
}


void number_a (const char* first, const char* last)
{
	string value = string (first, last);
	DEBUG ("number: " << value);

	// HACK: uses INT instead of putting INT in the parsed string. The correct
	// way to do this is to overwrite LIR_factory to explain what to do when we
	// see an INT.
	node_stack.push (new LIR::INT (lexical_cast<int> (value)));
	num_children_stack.top()++;
	dump_stack ();
}

void open_list_a (const char* first, const char* last)
{
	string value = string (first, last);

	// Find out the type: if omitted, use statement
	string type;
	if (value == "[")
		type = "statement";
	else
		type = value.substr (1, value.size());

	// uppercase first letter
	type[0] = toupper (type[0]);

	// Save as 'Statement_list'
	type.append ("_list");

	DEBUG ("open list: " << type);
	type_stack.push (type);
	num_children_stack.push(0);
}

void list_a (const char* first, const char* last)
{
	string value = string (first, last);
	DEBUG ("list: " << value);

	// Get the type
	string type = type_stack.top ();
	type_stack.pop ();

	// Get the argument list
	int num_children = num_children_stack.top();
	num_children_stack.pop();

	List<Object*> args;

	for(int i = 0; i < num_children; i++)
	{
		args.push_front(node_stack.top());
		node_stack.pop();
	}

	// Now that we have the classname, just pass all the objects on the stack
	Object* result = LIR::Node_factory::create (type.c_str (), &args);
	if (result == NULL)
		phc_internal_error ("Could not create list of type '%s', with sexp '%s",
			type.c_str (),
			value.c_str());


	node_stack.push (result);
	dump_stack ();
	num_children_stack.top()++;
}

Object*
parse_lir (String* s)
{
	num_children_stack.push(0);
	DEBUG (*s);

	rule<> r, sexp, classname, param, value, list, string, ws, number;
	// TODO: add ability to have shortcuts, like *,& or ==

	
	classname = +(alpha_p | '_'); // An LIR classname
	ws = *space_p; // optional space
	value = (alpha_p | '_') >> *(alnum_p | '_'); // a value (really a string, but no "" required)
	list = (ch_p('[') >> !classname)[&open_list_a] >> ws >> *(sexp >> ws) >> (ws >> (']'))[&list_a]; // list of Objects

	// Any char except ", or, alternatively, the sequence \"
	string = '"' >> *((anychar_p - '"') | str_p ("\\\"")) >> '"';
	number = +digit_p;

	// constructor parameters 
	param = number[&number_a] | value[&value_a] | sexp | list | string[&string_a];

	// definition: a classname and a number of arguments
	sexp = ('(' >> classname[&classname_a] >> ws >> *(param >> ws) >> ')')[&sexp_a] ;



   BOOST_SPIRIT_DEBUG_RULE(classname);
	BOOST_SPIRIT_DEBUG_RULE(ws);
	BOOST_SPIRIT_DEBUG_RULE(param);
	BOOST_SPIRIT_DEBUG_RULE(number);
	BOOST_SPIRIT_DEBUG_RULE(value);
	BOOST_SPIRIT_DEBUG_RULE(list);
	BOOST_SPIRIT_DEBUG_RULE(value);
	BOOST_SPIRIT_DEBUG_RULE(sexp);

	if (!parse (s->c_str (), sexp | list).full)
		phc_internal_error ("Bad parse of \n%s\n", s->c_str ());

	Object* result = node_stack.top ();

	if (LIR::Node* node = dynamic_cast<LIR::Node*> (result))
		node->assert_valid ();
	else if (LIR::Statement_list* stmt_list = dynamic_cast<LIR::Statement_list*> (result))
	{
		foreach (LIR::Statement* stmt, *stmt_list)
			stmt->assert_valid ();
	}


//	assert (node_stack.size () == 1);
//	assert (num_children_stack.top () == 1);
	return result;
}

List<std::pair<string, string> >* result;
string first;
string second;

void first_line_a (const char* start, const char* end)
{
	first = string (start, end);
}

void otherlines_a (const char* start, const char* end)
{
	second = string (start, end);
}

void complete_a (const char* start, const char* end)
{
	result->push_back (make_pair<string, string> (first, second));
}

List<std::pair<string, string> >*
parse_templates (String* s)
{
	result = new List<std::pair<string, string> >;
	// A very simple parser. We match sets of two strings:
	//		- The first is the name: a single line, starting in the first column,
	//		and ending in a ':'. It contains no whitespace
	//		- The second is the value: contains whitespace in the first line, and
	//		continues until another first line is matched.


	rule<> r, first_line, otherline, end_line_p, not_eol, empty_line, comment;
	not_eol = ~ch_p ('\n') & ~ch_p ('\r');


	comment = ch_p('#') >> *not_eol >> eol_p;
	first_line = (+(alpha_p | ch_p('_')))[&first_line_a] >> ':' >> eol_p;
	otherline = +blank_p >> +not_eol >> eol_p;
	empty_line = (*blank_p >> eol_p);

	r =  +(*comment >> (first_line >> (+otherline)[&otherlines_a])[&complete_a] >> *empty_line);

   BOOST_SPIRIT_DEBUG_RULE(first_line);
	BOOST_SPIRIT_DEBUG_RULE(otherline);
	BOOST_SPIRIT_DEBUG_RULE(not_eol);
	BOOST_SPIRIT_DEBUG_RULE(eol_p);

	if (!parse (s->c_str (), r).full)
		phc_internal_error ("Bad parse of '%s'", s->c_str ());

	return result;
}

*/
