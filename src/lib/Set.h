/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL set
 */

#ifndef PHC_SET_H
#define PHC_SET_H

#include <tr1/unordered_set>
#include <iterator>
#include <algorithm>
#include "List.h"

#include "assert.h"

template <
	typename _Tp, 
	typename _Hash = std::tr1::hash<_Tp>,
	typename _Pred = std::equal_to<_Tp>,
	typename _Alloc = phc_allocator<_Tp>
>
class phc_unordered_set : virtual public GC_obj, public std::tr1::unordered_set<_Tp, _Hash, _Pred, _Alloc>
{
public:
	int reference_count;
};

#define COW_PROFILE(NAME) __set_private_##NAME##_count++;
//#define COW_PROFILE(NAME) /* do nothing */

// We want these global, not per-template.
extern long long __set_private_construct_count;
extern long long __set_private_op_eq_count;
extern long long __set_private_detach_count;
extern long long __set_private_copy_construct_count;




template <
	typename _Tp, 
	typename _Hash = std::tr1::hash<_Tp>,
	typename _Pred = std::equal_to<_Tp>,
	typename _Alloc = phc_allocator<_Tp>
>
class Set : virtual public GC_obj
{
	/*
	 * Make sets copy-on-write. See the comments in Map.h.
	 */
	typedef phc_unordered_set<_Tp, _Hash, _Pred, _Alloc> inner_type;

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
	typedef Set<_Tp, _Hash, _Pred, _Alloc > this_type;

	/*
	 * Copy-on-write implementation
	 */
	Set ()
	: inner (new inner_type)
	{
		inner->reference_count = 1;
		COW_PROFILE (construct);
	}

	virtual ~Set()
	{
		this->inner->reference_count--;
	}

	Set (const this_type& other)
	{
		COW_PROFILE (copy_construct);

		// Deep copy of the delegated type.
		this->inner = other.inner;
		this->inner->reference_count++;
	}

	const this_type& operator=(const this_type& other)
	{
		if (this == &other)
			return *this;

		// Dont add extra references where they arent needed
		if (this->inner == other.inner)
			return *this;

		COW_PROFILE (op_eq);

		// Start sharing.
		this->inner = other.inner;
		this->inner->reference_count++;

		// This is the result of the entire (x = y), and doesnt affect what goes
		// into x.
		return *this;
	}

	void detach ()
	{
		if (this->inner->reference_count == 1)
			return;

		COW_PROFILE (detach);

		assert (this->inner->reference_count > 0);

		this->inner->reference_count--;

		this->inner = new inner_type (*this->inner);
		this->inner->reference_count = 1;
	}

public:

	/* 
	 * New methods we like
	 */

	Set (_Tp elem1) 
	: inner (new inner_type)
	{
		inner->reference_count = 1;
		COW_PROFILE (construct);

		insert (elem1);
	}

	Set (_Tp elem1, _Tp elem2) 
	: inner (new inner_type)
	{
		inner->reference_count = 1;
		COW_PROFILE (construct);

		insert (elem1);
		insert (elem2);
	}

	Set (_Tp elem1, _Tp elem2,  _Tp elem3) 
	: inner (new inner_type)
	{
		inner->reference_count = 1;
		COW_PROFILE (construct);

		insert (elem1);
		insert (elem2);
		insert (elem3);
	}

	Set (_Tp elem1, _Tp elem2,  _Tp elem3, _Tp elem4) 
	: inner (new inner_type)
	{
		inner->reference_count = 1;
		COW_PROFILE (construct);

		insert (elem1);
		insert (elem2);
		insert (elem3);
		insert (elem4);
	}

public:

	// Out-of-place operations return new sets. We only consider out-of-place
	// versions since the STL includes only out-of-place versions. In-place
	// versions could be created in some cases, however, possibly with lower
	// complexity.
	this_type* set_union (const this_type* other) const
	{
		this_type* result = new this_type ();

		foreach (_Tp key, *other)
			result->insert (key);

		foreach (_Tp key, *this)
			result->insert (key);

		return result;
	}
	this_type* set_intersection (const this_type* other) const
	{
		this_type* result = new this_type ();

		foreach (_Tp key, *other)
			if (this->has (key))
				result->insert (key);

		return result;
	}


	this_type* set_difference (const this_type* other) const
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

	this_type* clone () const
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

	_Tp front () const
	{
		assert (this->size ());
		return *this->begin ();
	}

	List<_Tp>* to_list () const
	{
		List<_Tp>* result = new List<_Tp>;
		foreach (_Tp entry, *this)
			result->push_back (entry);

		return result;
	}

public:
	
	/*
	 * Copy-on-write wrappers
	 */

	const_iterator begin () const { return inner->begin (); }
	iterator begin () { detach(); return inner->begin (); }
	const_iterator end () const { return inner->end (); }
	iterator end () { detach(); return inner->end (); }

	bool empty () const { return inner->empty (); }
	size_type size () const { return inner->size (); }
	size_type count (const key_type& x) const { return inner->count (x); }


	std::pair<iterator,bool> insert (const value_type& x) { detach(); return inner->insert (x); }
	iterator insert (iterator position, const value_type& x) { detach(); return inner->insert (position, x); }
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last) { detach(); return inner->insert (first, last); }

	void erase (iterator position) { detach(); return inner->erase (position); }
	size_type erase (const key_type& x) { detach(); return inner->erase (x); }
	void erase (iterator first, iterator last) { detach(); return inner->erase (first, last); }

	void clear ()
	{
		if (this->inner->reference_count == 1)
		{
			this->inner->clear ();
		}
		else
		{
			this->inner->reference_count--;

			this->inner = new inner_type;
			this->inner->reference_count = 1;
		}
	}

	iterator find (const key_type& x) { detach(); return inner->find (x); }
	const_iterator find (const key_type& x) const { return inner->find (x); }
};

template<typename _Tp, typename _Compare, typename _Alloc>
struct
supports_equality<Set<_Tp, _Compare, _Alloc>* >
{
	static const bool value = true;
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

#undef COW_PROFILE


#endif // PHC_SET
