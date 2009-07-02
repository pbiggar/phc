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
class phc_unordered_map : virtual public GC_obj, public std::tr1::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>
{
};


template <
	typename _Key, 
	typename _Tp, 
	typename _Hash = std::tr1::hash<_Key>,
	typename _Pred = std::equal_to<_Key>,
	typename _Alloc = phc_allocator<std::pair<const _Key, _Tp> >
>
class Map : virtual public GC_obj
{
	/*
	 * Make maps copy-on-write. We do this by hiding away the map details, and
	 * writing a copy-constructor to separate it.
	 *
	 * The idea is that the optimization data-structures, which are maps of maps
	 * of maps, will be copy-on-write all the way down.
	 */
	typedef phc_unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc> inner_type;

	/*
	 * Expose typedefs
	 */
public:
#define EXPOSE(TYPEDEF) typedef typename inner_type::TYPEDEF TYPEDEF;
	EXPOSE (const_iterator);
	EXPOSE (iterator);
	EXPOSE (size_type);
	EXPOSE (key_type);
	EXPOSE (value_type);

#undef EXPOSE

private:
	inner_type* inner;


public:
	typedef Map<_Key, _Tp, _Hash, _Pred, _Alloc> this_type;

	Map ()
	: inner (new inner_type)
	{
	}

	virtual ~Map() {}

	Map (const this_type& other)
	{
		// Deep copy of the delegated type.
		this->inner = new inner_type (*other.inner);
	}

	const this_type& operator=(const this_type& other)
	{
		if (this == &other)
			return *this;

		this->inner = new inner_type (*other.inner);

		// This is the result of the entire (x = y), and doesnt affect what goes
		// into x.
		return *this;
	}

public:

	/* 
	 * New methods we like
	 */

	bool has (const _Key& key) const
	{
		return this->inner->find (key) != this->inner->end ();
	}

	_Tp at (const _Key& key) const
	{
		return this->inner->find (key)->second;
	}

	_Tp get(const _Key& key) const
	{
		if (!this->has (key))
			return NULL;

		return this->at (key);
	}

	void set (_Key key, _Tp value)
	{
		(*this->inner)[key] = value;
	}

	List<_Key>* keys () const
	{
		List<_Key>* result = new List<_Key>;

		_Key key;
		_Tp value;
		foreach (boost::tie (key, value), *this->inner)
			result->push_back (key);

		return result;
	}

	List<_Tp>* values () const
	{
		List<_Tp>* result = new List<_Tp>;

		_Key key;
		_Tp value;
		foreach (boost::tie (key, value), *this->inner)
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

public:
	
	/*
	 * Copy-on-write wrappers
	 */

	const_iterator begin () const { return inner->begin (); }
	iterator begin () { return inner->begin (); }
	const_iterator end () const { return inner->end (); }
	iterator end () { return inner->end (); }

	bool empty () const { return inner->empty (); }
	size_type size () const { return inner->size (); }
	size_type count (const key_type& x) const { return inner->count (x); }

	_Tp& operator[] (const key_type& x) { return (*this->inner)[x]; }
	const _Tp& operator[] (const key_type& x) const { return get (x); }

	std::pair<iterator,bool> insert (const value_type& x) { return inner->insert (x); }
	iterator insert (iterator position, const value_type& x) { return inner->insert (position, x); }
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last) { return inner->insert (first, last); }

	void erase (iterator position) { return inner->erase (position); }
	size_type erase (const key_type& x) { return inner->erase (x); }
	void erase (iterator first, iterator last) { return inner->erase (first, last); }

	void clear () { return inner->clear (); }

	iterator find (const key_type& x) { return inner->find (x); }
	const_iterator find (const key_type& x) const { return inner->find (x); }
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
