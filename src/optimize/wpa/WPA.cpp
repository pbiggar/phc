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

string
BB_array_name (Context cx)
{
	return "array_" + cx.name ();
}

string
BB_object_name (Context cx)
{
	return "object_" + cx.name ();
}

std::ostream&
operator<< (std::ostream &out, const Context &cx)
{
	out << cx.name ();
	return out;
}

certainty combine_certs (certainty c1, certainty c2)
{
	assert (c1 != PTG_ALL);
	assert (c2 != PTG_ALL);

	if (c1 == DEFINITE && c2 == DEFINITE)
		return DEFINITE;
	
	return POSSIBLE;
}

void
CX_lattices::dump (Context cx, string name)
{
	if (this->has (cx))
	{
		cdebug << name << " Lattice for BB: " << cx << endl;
		(*this)[cx].dump();
		cdebug << endl;
	}
	else
		cdebug << "No " << name << " results for BB: " << cx << endl;
}



