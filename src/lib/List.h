/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Like the STL list, but inherit from Object
 */
 
#ifndef PHC_LIST
#define PHC_LIST

#include <assert.h>
#include <list>
#include "lib/Object.h"

using namespace std;

template<typename _Tp, typename _Alloc = allocator<_Tp> >
class List : public list<_Tp, _Alloc>, virtual public Object 
{
public:
	using list<_Tp, _Alloc>::push_back;

public:
	List() : list<_Tp, _Alloc>() {}
	virtual ~List() {}

// Create a singleton list
public:
	List(_Tp elem) : list<_Tp, _Alloc>()
	{
		push_back(elem);
	}

public:
	using list<_Tp, _Alloc>::begin;
	using list<_Tp, _Alloc>::end;

	void push_back_all(List* other) 
	{
		insert(end(), other->begin(), other->end());
	}

public:
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

#endif /* LIST_H */
