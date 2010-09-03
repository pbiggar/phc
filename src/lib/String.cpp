/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Like STL string, but inherit from Object
 */

#include <boost/algorithm/string.hpp>

#include "String.h" 
#include "AttrMap.h"

using std::string;

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

String::String(const string& s, size_t i, size_t n) : string(s, i, n)
{
}

String::~String() 
{
}

String* String::clone()
{
	return new String(*this);
}


// This is a common idiom discussed all over the web. The 'correct'
// way to do it supports locales, which is not our aim. We simply
// convert everything to lowercase and compare case-sensitively.
bool String::ci_compare (const string& other)
{
	// get a copy of both
	String* s1 = this->to_lower ();
	String* s2 = s(other)->to_lower ();

	return *s1 == *s2;
}

String*
String::to_lower () const
{
	String* result = new String (*this); 
	boost::to_lower (*result);
	return result;
}

String* s (const string& str)
{
	return new String (str);
}
