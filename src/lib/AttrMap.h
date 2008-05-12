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

// General
public:
	bool has(string key);
	Object* get(string key);
	void set(string key, Object* value);
	
// Bools
public:
	Boolean* get_boolean(string key);
	void set_true(string key);
	void set_false(string key);
	bool is_true(string key); // is_true returns false is not has(key)

// Integers
public:
	Integer* get_integer(string key);
	void set_integer (string key, int value);

// Strings
public:
	String* get_string(string key);

public:
	void erase_with_prefix (string key_prefix);

public:
	AttrMap* clone();
	void clone_all_from(AttrMap* other);
};

#endif // PHC_MAP
