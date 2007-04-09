/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Assign temporaries 
 */

#include "Assign_temps.h"

Assign_temps::Assign_temps()
{
	nextFresh = 0;
}

String* Assign_temps::fresh()
{
	stringstream ss;
	ss << "T" << nextFresh++;
	return new String(ss.str());
}

void Assign_temps::pre_expr(AST_expr* in)
{
	in->attrs->set("phc.codegen.temp", fresh());
}
