/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Like STL string, but inherit from Object
 */

#ifndef PHC_STRING_H
#define PHC_STRING_H

#include <string>
#include "lib/Object.h"
#include "lib/List.h"

// We use these everywhere, so allow them to be used without std::.
using std::string;
using std::stringstream;

class AttrMap;

// TODO: strings are not garbage collected (it doesnt matter that they arent traced)
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
	String(const string& s, size_t i, size_t n);

	// case insensitive comparison
	virtual ~String();

public:
	bool ci_compare (const string& s);
	void toLower();
	String* clone();
};

// 'new String' must be the most typed function in phc
String* s (const string& s);

typedef List<String*> String_list;

#endif // PHC_STRING_H
