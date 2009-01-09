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

// XXX HACK
/*
 * The implementation of List requires a clone() method, because it was
 * originally designed for the maketea derived clone() methods. But we want to
 * use List instead of std::list to make sure garbage collection is used
 * everywhere. This "hack" allows us to call Object::clone(), and fail if
 * clone() is called for classes that don't support it (all other classes).
 */

namespace IR { class Node; class FOREIGN; class PHP_script; }
SET_CLONABLE(IR::Node)
SET_CLONABLE(IR::FOREIGN)
SET_CLONABLE(IR::PHP_script)

#define MAKETEA_USER_DEFINED(TYPE) SET_CLONABLE(TYPE)
#include "AST_user_defined.h"
#include "HIR_user_defined.h"
#include "MIR_user_defined.h"
#undef MAKETEA_USER_DEFINED

/*
 * For all classes on which SET_CLONABLE is set, supports_cloning<T>::value is
 * true, making the template call obj->clone(). All other classes will default
 * to false, calling assert (0) instead. Using this approach means that other
 * classes do not have to have a clone() method - all other approaches I tried
 * led to compile-time failure, or didnt do the right thing.
 */

template<bool b> 
struct algorithm_selector 
{ 
	template<typename T> 
	static T& clone (T object) 
	{ 
		assert (0);
	} 
};



// Call to clone for classes that support it.
template<> 
struct algorithm_selector<true>
{ 
	template<typename T> 
	static T clone (T object)
	{ 
		if (object == NULL)
			return NULL;

		return object->clone (); 
	} 
};
template<typename T> 
T phc_clone (T object)
{ 
	return algorithm_selector<supports_cloning<T>::value>::clone(object); 
}


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

	// We're probably pushing it at 4...
	List(_Tp elem1, _Tp elem2, _Tp elem3, _Tp elem4) : std::list<_Tp, _Alloc>()
	{
		push_back(elem1);
		push_back(elem2);
		push_back(elem3);
		push_back(elem4);
	}

public:
	using std::list<_Tp, _Alloc>::begin;
	using std::list<_Tp, _Alloc>::end;

	void push_back_all(List* other) 
	{
		insert(end(), other->begin(), other->end());
	}
	
	void push_front_all(List* other) 
	{
		insert(begin(), other->begin(), other->end());
	}

public:
	List* clone()
	{
		List* result = new List<_Tp, _Alloc>;

		foreach (_Tp elem, *this)
		{
			result->push_back (phc_clone (elem));
		}
	
		return result;
	}

	_Tp at (int index)
	{
		int i = 0;
		assert (this->size () > (unsigned int)(i));
		foreach (_Tp elem, *this)
		{
			if (i == index)
				return elem;

			i++;
		}

		assert (0);
	}

	bool has (_Tp needle)
	{
		foreach (_Tp elem, *this)
			if (elem == needle)
				return true;

		return false;
	}
};

template <class Result_type, class List_type>
List<Result_type*>* rewrap_list (List<List_type*>* nodes)
{
	List<Result_type*>* result = new List<Result_type*>;
	foreach (List_type* n, *nodes)
	{
		result->push_back (dyc<Result_type> (n));
	}
	return result;
}

typedef List<Object*> Object_list;
class Boolean;
typedef List<Boolean*> Boolean_list;
class Integer;
typedef List<Integer*> Integer_list;
class String;
typedef List<String*> String_list;


#endif // PHC_LIST_H
