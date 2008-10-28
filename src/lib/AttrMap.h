/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Specialized version of Map 
 */

#ifndef PHC_ATTR_MAP_H
#define PHC_ATTR_MAP_H

#include "lib/Object.h"
#include "lib/Map.h"
#include <string>

class String;
class Integer;
class Boolean;

class AttrMap : public Map<std::string, Object*>
{
public:
	AttrMap();
	virtual ~AttrMap();

// Retrieve attributes of various types
public:
	Boolean* get_boolean(std::string key);
	Integer* get_integer(std::string key);
	String* get_string(std::string key);
	
// Special support for bools
public:
	void set_true(std::string key);
	void set_false(std::string key);
	bool is_true(std::string key); // is_true returns false is not has(key)

public:
	void erase_with_prefix (std::string key_prefix);

public:
	AttrMap* clone();
	void clone_all_from(AttrMap* other);
};

#endif // PHC_ATTR_MAP_H
