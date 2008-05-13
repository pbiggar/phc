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

#include <cctype>
char phc_tolower (char c)
{
	return std::tolower(c); 
}

// This is a common idiom discussed all over the web. The 'correct'
// way to do it supports locales, which is not our aim. We simply
// convert everything to lowercase and compare case-sensitively.
bool String::ci_compare (const string& s)
{
	// get a copy of both
	String* s1 = this->clone ();
	String* s2 = new String (s);
	s2 = s2->clone ();

	// convert both to lower case
	transform (s1->begin(), s1->end(), s1->begin (), phc_tolower);
	transform (s2->begin(), s2->end(), s1->begin (), phc_tolower);

	return *s1 == *s2;
}

void String::toLower ()
{
	transform (begin(), end(), begin (), phc_tolower);
}
