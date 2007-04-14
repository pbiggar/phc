/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Specialized version of std::map 
 */

#ifndef PHC_MAP
#define PHC_MAP

using namespace std;

#include <map>
#include "lib/Object.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"

class String;

class AttrMap : public map<string, Object*>, virtual public Object
{
public:
	AttrMap();
	virtual ~AttrMap();

// Retrieve attributes of various types
public:
	Object* get(string key);
	Boolean* get_boolean(string key);
	Integer* get_integer(string key);
	String* get_string(string key);
	bool has(string key);
	
// Special support for bools
public:
	void set_true(string key);
	void set_false(string key);
	bool is_true(string key); // is_true returns false is not has(key)

public:
	void set(string key, Object* value);

public:
	AttrMap* clone();
};

#endif // PHC_MAP
