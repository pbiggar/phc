/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Class to represent bools 
 */

#include "lib/Boolean.h"

Boolean::Boolean()
{
	_b = false;
}

Boolean::Boolean(bool b)
{
	_b = b;
}

bool Boolean::value() 
{
	return _b;
}

Boolean* Boolean::clone()
{
	return new Boolean(_b);
}
