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

certainty combine_certs (certainty c1, certainty c2)
{
	assert (c1 != PTG_ALL);
	assert (c2 != PTG_ALL);

	if (c1 == DEFINITE && c2 == DEFINITE)
		return DEFINITE;
	
	return POSSIBLE;
}


