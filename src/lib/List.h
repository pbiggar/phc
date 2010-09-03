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
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_scalar.hpp>

// XXX HACK
/*
 * The implementation of List requires a clone() method, because it was
 * originally designed for the maketea derived clone() methods. But we want to
 * use List instead of std::list to make sure garbage collection is used
 * everywhere. This "hack" allows us to call Object::clone(), and fail if
 * clone() is called for classes that don't support it (all other classes).
 */

namespace IR { class Node; class FOREIGN; class PHP_script; }

#define MAKETEA_USER_DEFINED(TYPE) SET_CLONABLE(TYPE) SET_COMPARABLE(TYPE)
MAKETEA_USER_DEFINED(IR::Node)
MAKETEA_USER_DEFINED(IR::FOREIGN)
MAKETEA_USER_DEFINED(IR::PHP_script)
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
struct clone_algorithm_selector 
{ 
	template<typename T> 
	static T clone (T object) 
	{
		return object;
	} 
};

// Call to clone for classes that support it.
template<> 
struct clone_algorithm_selector<true>
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
	return clone_algorithm_selector<supports_cloning<T>::value>::clone(object); 
}

template<bool supports_equality, bool is_scalar, bool is_pointer> 
struct equals_algorithm_selector 
{ 
	template<typename T> 
	static bool equals (T object1, T object2) 
	{
		// This probably doesn't do what you want in this case.
		abort();
	} 
};

// Non-pointers which have operator== should work too (like strings and
// primitives).
template<> 
struct equals_algorithm_selector<false, true, false>
{ 
	template<typename T> 
	static bool equals (T object1, T object2)
	{ 
		return object1 == object2;
	} 
};

// Call to equals for classes that support it.
template<> 
struct equals_algorithm_selector<true, true, true>
{ 
	template<typename T> 
	static bool equals (T object1, T object2)
	{ 
		return object1->equals (object2); 
	} 
};

template<> 
struct equals_algorithm_selector<true, false, false>
{ 
	template<typename T> 
	static bool equals (T object1, T object2)
	{ 
		return object1.equals (&object2); 
	} 
};

template<typename T> 
bool phc_equals (T object1, T object2)
{ 
	return equals_algorithm_selector<supports_equality<T>::value, boost::is_scalar<T>::value, boost::is_pointer<T>::value>::equals(object1, object2); 
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

	void push_back_all (List* other) 
	{
		insert(end(), other->begin(), other->end());
	}
	
	void push_front_all (List* other) 
	{
		insert(begin(), other->begin(), other->end());
	}

public:
	List* clone ()
	{
		List* result = new List<_Tp, _Alloc>;

		foreach (_Tp elem, *this)
		{
			result->push_back (phc_clone (elem));
		}
	
		return result;
	}

	List* clone () const
	{
		// Just reuse clone(), we know it's const.
		return const_cast<const List<_Tp, _Alloc>*> (this)->clone ();
	}
	

	_Tp at (int index) const
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

	bool has (const _Tp needle) const
	{
		foreach (_Tp elem, *this)
			if (elem == needle)
				return true;

		return false;
	}
};

template <class Result_type, class List_type>
List<Result_type*>* rewrap_list (const List<List_type*>* list)
{
	List<Result_type*>* result = new List<Result_type*>;
	foreach (List_type* n, *list)
	{
		result->push_back (dyc<Result_type> (n));
	}
	return result;
}

// A filter that removes objects not of the type FILTER_TYPE.
template <class Filter_type, class List_type>
List<Filter_type*>* filter_types (const List<List_type*>* list)
{
	List<Filter_type*>* result = new List<Filter_type*>;
	foreach (List_type* n, *list)
	{
		if (isa<Filter_type> (n))
			result->push_back (dyc<Filter_type> (n));
	}
	return result;
}

typedef List<Object*> Object_list;

#define DECL_LIST(T) typedef List<T*> T##_list;
#define DECL_CONST_LIST(T) typedef List<const T*> c##T##_list;
#define DECL(T) class T; DECL_LIST(T); DECL_CONST_LIST(T)
DECL (Boolean);
DECL (Integer);
DECL (String);


#endif // PHC_LIST_H
