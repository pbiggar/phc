/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Class to represent ints (for passing around as synthesized attributes) 
 */


#include "lib/Integer.h"

Integer::Integer()
{
	_n = 0;
}

Integer::Integer(long n)
{
	_n = n;
}

long Integer::value()
{
	return _n; 
}

void Integer::operator++(POST_INCREMENT)
{
	_n++;
}

Integer* Integer::clone()
{
	return new Integer(_n);
}
