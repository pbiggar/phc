/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL map
 */
 
#ifndef PHC_MAP_H
#define PHC_MAP_H

#include <map>
#include "List.h"
#include <boost/tuple/tuple.hpp> // for tie

using boost::tie;

template <
	typename _Key, 
	typename _Tp, 
	typename _Compare = std::less<_Key>,
	typename _Alloc = phc_allocator<std::pair<const _Key, _Tp> >
>
class Map : public std::map<_Key, _Tp, _Compare, _Alloc>, virtual public GC_obj 
{
public:
	Map() : std::map<_Key, _Tp, _Compare, _Alloc>() {}
	Map(_Compare comparator) : std::map<_Key, _Tp, _Compare, _Alloc>(comparator) {}
	virtual ~Map() {}

public:
	bool has(_Key key)
	{
		return this->find(key) != this->end();
	}

	_Tp get(_Key key)
	{
		if (!has (key)) return NULL;

		return (*this)[key];
	}

	void set(_Key key, _Tp value)
	{
		(*this)[key] = value;
	}

	List<_Key>* keys ()
	{
		List<_Key>* result = new List<_Key>;

		_Key key;
		_Tp value;
		foreach (boost::tie (key, value), *this)
			result->push_back (key);

		return result;
	}

	List<_Tp>* values ()
	{
		List<_Tp>* result = new List<_Tp>;

		_Key key;
		_Tp value;
		foreach (boost::tie (key, value), *this)
			result->push_back (value);

		return result;
	}


};

#endif // PHC_MAP_H
