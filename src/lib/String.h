/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Like STL string, but inherit from Object
 */

#ifndef PHC_STRING
#define PHC_STRING

#include <string>
#include "lib/Object.h"
#include "lib/AttrMap.h"

using namespace std;

class String : public string, virtual public Object
{
// This is a hack and will at some point be removed.
// Do not depend on it.
public:	
	AttrMap* attrs; // __attribute__ ((deprecated));

public:
	String(); 
	String(const string& s); 
	String(char const* s); 
	String(char const* s, size_t n);
	virtual ~String();

public:
	String* clone();
};

#endif
