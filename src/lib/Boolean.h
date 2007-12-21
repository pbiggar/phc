/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Class to represent bools 
 */

#ifndef PHC_BOOLEAN
#define PHC_BOOLEAN

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

#endif 
