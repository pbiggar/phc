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

template <
	typename _Tp, 
	typename _Compare = std::less<_Tp>,
	typename _Alloc = phc_allocator<_Tp>
>
class Set : public std::set<_Tp, _Compare, _Alloc>, virtual public GC_obj
{
public:
	typedef std::set<
		_Tp,
		_Compare,
		_Alloc
	> parent;

public:
	// If true, the SET holds every possible node of that type.
	bool full;

public:
	Set () : full (false) {}
	Set (_Compare comparator) 
	: parent (comparator)
	, full (false)
	{
	}

	Set (_Tp elem1) 
	: full (false)
	{
		insert (elem1);
	}

	Set (_Tp elem1, _Tp elem2) 
	: full (false)
	{
		insert (elem1);
		insert (elem2);
	}

	Set (_Tp elem1, _Tp elem2,  _Tp elem3) 
	: full (false)
	{
		insert (elem1);
		insert (elem2);
		insert (elem3);
	}

	Set (_Tp elem1, _Tp elem2,  _Tp elem3, _Tp elem4) 
	: full (false)
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
	Set<_Tp, _Compare, _Alloc>* set_union (Set<_Tp, _Compare, _Alloc>* other)
	{
		Set<_Tp, _Compare, _Alloc>* result = new Set<_Tp, _Compare, _Alloc> (key_comp ());

		if (other->full or full)
			result->full = true;
		else
		{
			std::set_union (
					this->begin (), this->end(),
					other->begin (), other->end (),
					std::insert_iterator<parent> (*result, result->begin ()));
		}

		return result;
	}
	Set<_Tp, _Compare, _Alloc>* set_intersection (Set<_Tp, _Compare, _Alloc>* other)
	{
		Set<_Tp, _Compare, _Alloc>* result = new Set<_Tp, _Compare, _Alloc> (key_comp ());

		if (this->full && other->full)
		{
			result->full = true;
		}
		else if (this->full)
		{
			std::copy (
					this->begin (), this->end(),
					std::insert_iterator<parent> (*result, result->begin ()));
		}
		else if (other->full)
		{
			std::copy (
					other->begin (), other->end(),
					std::insert_iterator<parent> (*result, result->begin ()));
		}
		else
		{
			std::set_intersection (
					this->begin (), this->end(),
					other->begin (), other->end (),
					std::insert_iterator<parent> (*result, result->begin ()));
		}

		return result;
	}


	Set<_Tp, _Compare, _Alloc>* set_difference (Set<_Tp, _Compare, _Alloc>* other)
	{
		Set<_Tp, _Compare, _Alloc>* result = new Set<_Tp, _Compare, _Alloc> (key_comp ());

		if (other->full)
			return result;
		else if (this->full)
		{
			result->full = true;
			return result;
		}

		std::set_difference (
				this->begin (), this->end(),
				other->begin (), other->end (),
				std::insert_iterator<parent> (*result, result->begin ()));

		return result;
	}	
public:
	// Include all possible values
	void insert_all ()
	{
		full = true;
	}

	bool has (_Tp entry)
	{
		return full || (find (entry) != this->end());
	}

	Set<_Tp, _Compare, _Alloc>* clone ()
	{
		Set<_Tp, _Compare, _Alloc>* result = new Set<_Tp, _Compare, _Alloc> (key_comp ());
		if (full)
		{
			result->full = true;
			return result;
		}

		foreach (_Tp entry, *this)
		{
			result->insert (phc_clone (entry));
		}

		return result;
}	
public:
	// TODO when using iterators, assert (!full). We cant iterate through the
	// full set.


	List<_Tp>* to_list ()
	{
		List<_Tp>* result = new List<_Tp>;
		foreach (_Tp entry, *this)
			result->push_back (entry);

		return result;
	}
};


#endif // PHC_SET
