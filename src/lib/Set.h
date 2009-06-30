/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL set
 */

#ifndef PHC_SET
#define PHC_SET

#include <iterator>
#include <set>
#include <algorithm>

#include "assert.h"

#include <lib/List.h>

template <
	typename _Tp, 
	typename _Compare = std::less<_Tp>,
	typename _Alloc = phc_allocator<_Tp>
>
class Set : public std::set<_Tp, _Compare, _Alloc>, virtual public GC_obj
{
public:
	typedef std::set<_Tp, _Compare, _Alloc> parent;
	typedef Set<_Tp, _Compare, _Alloc > this_type;

public:
	Set () {}
	Set (_Compare comparator) 
	: parent (comparator)
	{
	}

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

	using parent::key_comp;

	// Out-of-place operations return new sets. We only consider out-of-place
	// versions since the STL includes only out-of-place versions. In-place
	// versions could be created in some cases, however, possibly with lower
	// complexity.
	this_type* set_union (this_type* other)
	{
		this_type* result = new this_type (key_comp ());

		std::set_union (
					this->begin (), this->end(),
					other->begin (), other->end (),
					std::insert_iterator<parent> (*result, result->begin ()));

		return result;
	}
	this_type* set_intersection (this_type* other)
	{
		this_type* result = new this_type (key_comp ());

		std::set_intersection (
				this->begin (), this->end(),
				other->begin (), other->end (),
				std::insert_iterator<parent> (*result, result->begin ()));

		return result;
	}


	Set<_Tp, _Compare, _Alloc>* set_difference (Set<_Tp, _Compare, _Alloc>* other)
	{
		this_type* result = new this_type (key_comp ());

		std::set_difference (
				this->begin (), this->end(),
				other->begin (), other->end (),
				std::insert_iterator<parent> (*result, result->begin ()));

		return result;
	}	
public:
	bool has (_Tp entry)
	{
		return find (entry) != this->end ();
	}

	this_type* clone ()
	{
		this_type* result = new this_type (key_comp ());
		foreach (_Tp entry, *this)
		{
			result->insert (phc_clone (entry));
		}

		return result;
	}

	bool equals (this_type* other)
	{
		if (this->size () != other->size ())
			return false;

		foreach (_Tp elem, *this)
			if (!other->has (elem))
				return false;

		return true;
	}

	_Tp front ()
	{
		assert (this->size ());
		return *this->begin ();
	}

public:

	List<_Tp>* to_list ()
	{
		List<_Tp>* result = new List<_Tp>;
		foreach (_Tp entry, *this)
			result->push_back (entry);

		return result;
	}
};

template<typename _Tp, typename _Compare, typename _Alloc>
struct
supports_equality<Set<_Tp, _Compare, _Alloc>* >
{
	static const bool value = true;
};

template<typename _Tp, typename _Compare, typename _Alloc>
struct
supports_equality<Set<_Tp, _Compare, _Alloc> >
{
	static const bool value = true;
};




#endif // PHC_SET
