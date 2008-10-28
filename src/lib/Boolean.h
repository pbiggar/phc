/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Class to represent bools 
 */

#ifndef PHC_BOOLEAN_H
#define PHC_BOOLEAN_H

#include "lib/Object.h"

class Boolean : virtual public Object
{
private:
	bool _b;

public:
	Boolean();
	Boolean(bool b);
	bool value(); 

public:
	Boolean* clone();
};

SET_CLONABLE(Boolean)

#endif // PHC_BOOLEAN_H
