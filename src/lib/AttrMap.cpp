/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Specialized version of std::map
 */

#include "AttrMap.h"
#include "String.h"

AttrMap::AttrMap() : map<string, Object*>() 
{
}

AttrMap::~AttrMap() 
{
}

Object* AttrMap::get(string key)
{
	if (!has (key)) return NULL;

	return (*this)[key];
}

Boolean* AttrMap::get_boolean(string key)
{
	Boolean* ret = dynamic_cast<Boolean*> (get (key));
	assert(ret != NULL);
	return ret;
}

Integer* AttrMap::get_integer(string key)
{
	Integer* ret = dynamic_cast<Integer*> (get (key));
	assert(ret != NULL);
	return ret;
}

String* AttrMap::get_string(string key)
{
	String* ret = dynamic_cast<String*> (get (key));
	assert(ret != NULL);
	return ret;
}

void AttrMap::set_true(string key)
{
	set(key, new Boolean(true));
}

void AttrMap::set_false(string key)
{
	set(key, new Boolean(false));
}

bool AttrMap::is_true(string key)
{
	if(!has(key)) return false;
	Boolean* ret = dynamic_cast<Boolean*>((*this)[key]);
	assert(ret != NULL);
	return ret->value();
}

bool AttrMap::has(string key)
{
	return find(key) != end();
}

void AttrMap::set(string key, Object* value)
{
	(*this)[key] = value;
}

void AttrMap::erase_with_prefix (string key_prefix)
{
	AttrMap::iterator i;
	// erasing using an iterator may invalidate the iterator
	for(i = begin(); i != end(); )
	{
		if ((*i).first.find (key_prefix, 0) != string::npos)
		{
			string key = (*i).first;
			i++; // advance the iterator before deleting
			erase (key);
		}
		else
			i++;
	}
}

AttrMap* AttrMap::clone()
{
	AttrMap* result = new AttrMap;
	result->clone_all_from(this);
	return result;
}

void AttrMap::clone_all_from(AttrMap* other)
{
	AttrMap::const_iterator i;
	for(i = other->begin(); i != other->end(); i++)
	{
		assert ((*i).second != NULL);
		set((*i).first, (*i).second->clone());
	}
}
