/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A whole-program analysis. This has access to other analysis results as its
 * run, and must keep its state for the whole program. This simply provides the interface.
 */

#include "WPA.h"

using namespace std;
using namespace boost;
using namespace MIR;

Certainty combine_certs (Certainty c1, Certainty c2)
{
	assert (is_valid_certainty (c1));
	assert (is_valid_certainty (c2));

	if (c1 == DEFINITE && c2 == DEFINITE)
		return DEFINITE;
	
	return POSSIBLE;
}

bool
is_valid_certainty (Certainty cert)
{
	return (cert == POSSIBLE || cert == DEFINITE);
}

string
result_state_string (Result_state state)
{
	const char* strings[] = {NULL, "IN", "OUT", "WORKING", "POST_BIND"};
	return string (strings[state]);
}
