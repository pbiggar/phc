/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL list
 */
 
#ifndef PHC_LIST_H
#define PHC_LIST_H

#include <list>
#include "lib/Object.h"
#include "process_ir/Foreach.h"

template<typename _Tp, typename _Alloc = phc_allocator<_Tp> >
class List : public std::list<_Tp, _Alloc>, virtual public Object 
{
public:
	using std::list<_Tp, _Alloc>::push_back;

public:
	List() : std::list<_Tp, _Alloc>() {}
	virtual ~List() {}

// Create a list with one, two or three elements 
public:
	List(_Tp elem1) : std::list<_Tp, _Alloc>()
	{
		push_back(elem1);
	}

	List(_Tp elem1, _Tp elem2) : std::list<_Tp, _Alloc>()
	{
		push_back(elem1);
		push_back(elem2);
	}

	List(_Tp elem1, _Tp elem2, _Tp elem3) : std::list<_Tp, _Alloc>()
	{
		push_back(elem1);
		push_back(elem2);
		push_back(elem3);
	}

public:
	using std::list<_Tp, _Alloc>::begin;
	using std::list<_Tp, _Alloc>::end;

	void push_back_all(List* other) 
	{
		insert(end(), other->begin(), other->end());
	}

public:
	// TODO: clone assumes that _Tp supports a clone method. It would be useful
	// if we could automatically call a clone method if supported, and do a
	// shallow copy (or call a copy-constructor, which?) if not. I think that
	// checking for a clonable trait of _Tp might do that (involves adding such
	// a trait to Object, which is OK).
	List* clone()
	{
		List* result = new List<_Tp, _Alloc>;

		typename List<_Tp, _Alloc>::const_iterator i;
		for(i = begin(); i != end(); i++)
		{
			if(*i)
				result->push_back((*i)->clone());
			else
				result->push_back(NULL);
		}
	
		return result;
	}
};

template <class List_type, class Result_type>
List<Result_type*>* rewrap_list (List<List_type*>* nodes)
{
	List<Result_type*>* result = new List<Result_type*>;
	foreach (List_type* n, *nodes)
	{
		result->push_back (dyc<Result_type> (n));
	}
	return result;
}

#endif // PHC_LIST_H
