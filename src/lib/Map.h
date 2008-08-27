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

#include "process_ir/Foreach.h"

template <class Key, class Value>
class Map : public map<Key, Value*>, virtual public Object
{
public:
	Map() {}
	virtual ~Map() {};

public:
	bool has(Key key)
	{
		return this->find(key) != this->end();
	}

	Value* get(Key key)
	{
		if (!has (key)) return NULL;

		return (*this)[key];
	}

	void set(Key key, Value* value)
	{
		(*this)[key] = value;
	}

public:
	Map* clone()
	{
		Map* result = new Map;
		result->clone_all_from(this);
		return result;
	}

	void clone_all_from(Map* other)
	{
		pair<Key, Value*> p;
		foreach (p, *other)
		{
			assert (p.second != NULL);
			set(p.first, p.second->clone());
		}
	}
};

#endif // PHC_MAP
