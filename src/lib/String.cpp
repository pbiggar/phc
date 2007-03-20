/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Like STL string, but inherit from Object
 */

#include "String.h" 

String::String() 
{
	attrs = new AttrMap();
}

String::String(const string& s) : string(s)  
{
	attrs = new AttrMap();
}

String::String(char const* s) : string(s) 
{
	attrs = new AttrMap();
}

String::String(char const* s, size_t n) : string(s, n) 
{
	attrs = new AttrMap();
}

String::~String() 
{
}

String* String::clone()
{
	return new String(*this);
}
