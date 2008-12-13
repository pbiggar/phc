
#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_DEBUG_PRINT_SOME 80


#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/utility/lists.hpp>
#include <boost/spirit/utility/escape_char.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace boost::spirit;


void parse_lir (string s);

#define DLS(LIR) parse_lir (#LIR);
int main (int argc, char** argv)
{
	if (argc == 1)
	{
		DLS ((if (equals (deref (ZVPP p_lhs)) (ZVP rhs))))
		DLS ((if (equals (deref (ZVPP p_lhs)) (ZVP rhs)) [(CODE "write_var (p_lhs, rhs);")] [] ))
		DLS ((if (== (* p_lhs) rhs) [(CODE "write_var (p_lhs, rhs);")] [] ))
	}
	else
		parse_lir (argv[1]);
}

void parse_lir (string s)
{
	cout << s << endl;

	rule<> r, sexp, classname, param, symbol, list, string, nil, helper, ws;

	// Classname can be any LIR classname
	// TODO: add ability to have shortcuts, like *,& or ==
	classname = *(alpha_p | '_');
	ws = !space_p;

	// a param can be any variable-name
	symbol = +(alpha_p | '_');
//	list = '[' >> *sexp >> ']';
//	nil = str_p ("nil");
//	string = '"' >> *sexp >> '"'; // TODO: escaping?

	param = symbol | sexp ; // | list | string;
	sexp = '(' >> ws >> classname >> ws >> *(param >> ws) >> ')' ;

	BOOST_SPIRIT_DEBUG_RULE(classname);
	BOOST_SPIRIT_DEBUG_RULE(helper);
	BOOST_SPIRIT_DEBUG_RULE(ws);
	BOOST_SPIRIT_DEBUG_RULE(param);
	BOOST_SPIRIT_DEBUG_RULE(symbol);
	BOOST_SPIRIT_DEBUG_RULE(sexp);

	if (parse (s.c_str (), sexp).full)
		cout << "matches" << endl;
	else
		cout << "failed" << endl;
}
