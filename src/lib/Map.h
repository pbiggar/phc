/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL map
 */
 
#ifndef PHC_MAP_H
#define PHC_MAP_H

#include <tr1/unordered_map>
#include <tr1/functional_hash.h>
#include "List.h"
#include <boost/tuple/tuple.hpp> // for tie

using boost::tie;

template <
	typename _Key, 
	typename _Tp, 
	typename _Hash = std::tr1::hash<_Key>,
	typename _Pred = std::equal_to<_Key>,
	typename _Alloc = phc_allocator<std::pair<const _Key, _Tp> >
>
class Map : public std::tr1::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>, virtual public GC_obj 
{
public:
	typedef Map <_Key, _Tp, _Hash, _Pred, _Alloc> this_type;

	Map () : std::tr1::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc> () {}
	virtual ~Map() {}

public:
	bool has(_Key key)
	{
		return this->find(key) != this->end();
	}

	_Tp at(_Key key) const
	{
		return this->find(key)->second;
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

	bool equals (this_type* other)
	{
		if (other->size () != this->size ())
			return false;

		_Key key;
		_Tp value;
		foreach (boost::tie (key, value), *this)
		{
			if (!other->has (key))
				return false;

			if (!phc_equals (value, (*other)[key]))
				return false;
		}

		return true;
	}
};


template<typename _Key, typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
struct
supports_equality<Map<_Key, _Tp, _Hash, _Pred, _Alloc>* >
{
	static const bool value = true;
};

template<typename _Key, typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
struct
supports_equality<Map<_Key, _Tp, _Hash, _Pred, _Alloc> >
{
	static const bool value = true;
};



#endif // PHC_MAP_H
