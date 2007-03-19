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
	return (*this)[key];
}

Boolean* AttrMap::get_boolean(string key)
{
	Boolean* ret = dynamic_cast<Boolean*>((*this)[key]);
	assert(ret != NULL);
	return ret;
}

Integer* AttrMap::get_integer(string key)
{
	Integer* ret = dynamic_cast<Integer*>((*this)[key]);
	assert(ret != NULL);
	return ret;
}

String* AttrMap::get_string(string key)
{
	String* ret = dynamic_cast<String*>((*this)[key]);
	assert(ret != NULL);
	return ret;
}

bool AttrMap::is_true(string key)
{
	Boolean* ret = dynamic_cast<Boolean*>((*this)[key]);
	if(ret == NULL)
		return false;
	else
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
