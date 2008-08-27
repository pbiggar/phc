/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Specialized version of std::map, for (string,object) pairs
 */

#ifndef PHC_ATTR_MAP
#define PHC_ATTR_MAP

using namespace std;

#include <string>

#include "lib/Object.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/Map.h"

class String;

class AttrMap : public Map<string, Object>
{
public:
	AttrMap();
	virtual ~AttrMap();

// Retrieve attributes of various types
public:
	Boolean* get_boolean(string key);
	Integer* get_integer(string key);
	String* get_string(string key);
	
// Special support for bools
public:
	void set_true(string key);
	void set_false(string key);
	bool is_true(string key); // is_true returns false is not has(key)

public:
	void erase_with_prefix (string key_prefix);

	AttrMap* clone()
	{
		AttrMap* result = new AttrMap;
		result->clone_all_from(this);
		return result;
	}

	void clone_all_from(AttrMap* other)
	{
		pair<string, Object*> p;
		foreach (p, *other)
		{
			assert (p.second != NULL);
			set(p.first, p.second->clone());
		}
	}
};

#endif // PHC_ATTR_MAP
