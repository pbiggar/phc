/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL set
 */

#ifndef PHC_SET
#define PHC_SET

#include <iterator>
#include <tr1/unordered_set>
#include <algorithm>

#include "assert.h"

#include <lib/List.h>

template <
	typename _Tp, 
	typename _Hash = std::tr1::hash<_Tp>,
	typename _Pred = std::equal_to<_Tp>,
	typename _Alloc = phc_allocator<_Tp>
>
class Set : public std::tr1::unordered_set<_Tp, _Hash, _Pred, _Alloc>, virtual public GC_obj
{
public:
	typedef Set<_Tp, _Hash, _Pred, _Alloc > this_type;
	typedef std::tr1::unordered_set<_Tp, _Hash, _Pred, _Alloc> parent;

public:
	Set () {}

	Set (_Tp elem1) 
	{
		insert (elem1);
	}

	Set (_Tp elem1, _Tp elem2) 
	{
		insert (elem1);
		insert (elem2);
	}

	Set (_Tp elem1, _Tp elem2,  _Tp elem3) 
	{
		insert (elem1);
		insert (elem2);
		insert (elem3);
	}

	Set (_Tp elem1, _Tp elem2,  _Tp elem3, _Tp elem4) 
	{
		insert (elem1);
		insert (elem2);
		insert (elem3);
		insert (elem4);
	}

	virtual ~Set() {}

public:

	// Out-of-place operations return new sets. We only consider out-of-place
	// versions since the STL includes only out-of-place versions. In-place
	// versions could be created in some cases, however, possibly with lower
	// complexity.
	this_type* set_union (this_type* other) const
	{
		this_type* result = new this_type ();

		foreach (_Tp key, *other)
			result->insert (key);

		foreach (_Tp key, *this)
			result->insert (key);

		return result;
	}
	this_type* set_intersection (this_type* other) const
	{
		this_type* result = new this_type ();

		foreach (_Tp key, *other)
			if (this->has (key))
				result->insert (key);

		return result;
	}


	this_type* set_difference (this_type* other) const
	{
		this_type* result = new this_type ();

		foreach (_Tp key, *this)
			if (not this->has (key))
				result->insert (key);

		return result;
	}	
public:
	bool has (_Tp entry) const
	{
		return find (entry) != this->end ();
	}

	this_type* clone ()
	{
		this_type* result = new this_type ();
		foreach (_Tp entry, *this)
		{
			result->insert (phc_clone (entry));
		}

		return result;
	}

	bool equals (this_type* other) const
	{
		return (*this == *other);
	}

	bool operator== (const this_type& other) const
	{
		if (this->size () != other.size ())
			return false;

		foreach (_Tp elem, *this)
			if (!other.has (elem))
				return false;

		return true;
	}

	bool operator!= (const this_type& other) const
	{
		return not (*this == other);
	}

	_Tp front ()
	{
		assert (this->size ());
		return *this->begin ();
	}

public:

	List<_Tp>* to_list () const
	{
		List<_Tp>* result = new List<_Tp>;
		foreach (_Tp entry, *this)
			result->push_back (entry);

		return result;
	}
};


template<typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
struct
supports_equality<Set<_Tp, _Hash, _Pred, _Alloc>* >
{
	static const bool value = true;
};

template<typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
struct
supports_equality<Set<_Tp, _Hash, _Pred, _Alloc> >
{
	static const bool value = true;
};




#endif // PHC_SET
