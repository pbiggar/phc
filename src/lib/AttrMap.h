/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Specialized version of Map 
 */

#ifndef PHC_ATTR_MAP_H
#define PHC_ATTR_MAP_H

#include "lib/String.h"
#include "lib/Object.h"
#include "lib/Map.h"

class String;
class Integer;
class Boolean;

class AttrMap : public Map<string, Object*>
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
	void erase_with_prefix (string key_prefix);

public:
	AttrMap* clone();
	void clone_all_from(AttrMap* other);
};

#endif // PHC_ATTR_MAP_H
