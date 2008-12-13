/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience functions for parsing code represented as S-expressions (ish).
 */



#include <boost/spirit.hpp>
#include <iostream>

#include "LIR.h"
#include "LIR_parser.h"
#include "LIR_factory.h"
#include "lib/String.h"
#include "lib/demangle.h"
#include "lib/Stack.h"
#include "process_ir/debug.h"

using namespace std;
using namespace boost::spirit;


void parse_lir (string s);

/*
	new If (
		new Equals (
			new Deref (
				new ZVPP ("p_lhs")),
			new ZVP ("rhs")),
			new LIR::Statement_list (
				new CODE ("write_var (p_lhs, rhs);\n")),
			new LIR::Statement_list));
*/
Stack<Object*> node_stack;
Stack<int> num_children_stack;

void dump_stack ()
{
	CHECK_DEBUG ();
	cout << node_stack.size() << " things on the stack" << endl;
	cout << demangle (node_stack.top()) << " on top of stack" << endl;
	cout << num_children_stack.top() << " children on the stack" << endl;
	cout << endl;
}

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

	num_children_stack.top()++;
	node_stack.push (new String (value));
	dump_stack ();
}

void open_list_a (char first)
{
	DEBUG ("open list");
	num_children_stack.push(0);
}

void list_a (const char* first, const char* last)
{
	DEBUG ("list: " << string (first, last));

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
	// TODO: How can we know the list's type?
	Object* result = LIR::Node_factory::create ("Statement_list", &args);
	assert (result);

	node_stack.push (result);
	dump_stack ();
	num_children_stack.top()++;
}

LIR::Node*
parse_lir (String* s)
{
	num_children_stack.push(0);
	DEBUG (*s);

	rule<> r, sexp, classname, param, value, list, string, ws;
	// TODO: add ability to have shortcuts, like *,& or ==

	
	classname = +(alpha_p | '_'); // An LIR classname
	ws = !space_p; // optional space
	value = +(alpha_p | '_'); // a value (really a string, but no "" required)
	list = ch_p('[')[&open_list_a] >> ws >> *sexp >> ws >> ']'; // list of Objects

	// Any char except ", or, alternatively, the sequence \"
	string = '"' >> *((anychar_p - '"') | str_p ("\\\"")) >> '"';

	// constructor parameters 
	param = value[&value_a] | sexp | list[&list_a] | string[&string_a];

	// definition: a classname and a number of arguments
	sexp = ('(' >> ws >> classname[&classname_a] >> ws >> *(param >> ws) >> ')')[&sexp_a] ;

/*
	#define BOOST_SPIRIT_DEBUG
	#define BOOST_SPIRIT_DEBUG_PRINT_SOME 80

   BOOST_SPIRIT_DEBUG_RULE(classname);
	BOOST_SPIRIT_DEBUG_RULE(helper);
	BOOST_SPIRIT_DEBUG_RULE(ws);
	BOOST_SPIRIT_DEBUG_RULE(param);
	BOOST_SPIRIT_DEBUG_RULE(value);
	BOOST_SPIRIT_DEBUG_RULE(sexp);
*/
	if (parse (s->c_str (), sexp).full)
		DEBUG ("matches");
	else
		DEBUG ("failed");

//	assert (node_stack.size () == 1);
//	assert (num_children_stack.top () == 1);
	return dyc<LIR::Node> (node_stack.top ());
}
