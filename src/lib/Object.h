/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * GC_obj provides a polymorpic base (i.e., a base that supports RTTI), and
 * garbage collection.  Object additionally provides a clone() method.
 */

#ifndef PHC_OBJECT_H
#define PHC_OBJECT_H

#include "config.h"
#include <assert.h>

#ifndef NULL
#define NULL 0L
#endif

/*
 * Garbage collection:
 *
 *	We use the Boehm garbage collector for C++. This creates a very small number
 *	of rules that we need to follow. Failure to follow these rules will
 *	typically lead to the garbage allocator prematurely collecting objects,
 *	leading to segfaults. (Note: object on the stack are NOT excepted).
 *
 *	1. _ALL_ (let me repeat, ALL) classes which we define need to inherit from GC_obj.
 *	2. Its OK to use string or stringstream on the stack, since they dont
 *		contain other objects, they get cleared up on going out of scope, and they
 *		appear everywhere.
 *		TODO: do we clear up the result of stringstream::str()
 *	3. Never use STL objects without wrapping them. For example:
 *		-	Create Map to wrap std::map, either using gc_allocator as the
 *			allocator, or inheriting from Object. It _should_ inherit from Object and
 *			support the clone() method, but that may not yet be implemented. If it is
 *			not, it inherits from GC_obj instead.
 *	4. When using embedded PHP, do garbage collection manually. If garbage
 *		collected objects need to be put in PHP structures (which they currently
 *		dont), then the memory must be allocated using libgc's traceable
 *		allocators, which traces, but doesn't deallocate memory.
 *	5. For exceptional objects allocated with new, use the placement new form:
 *			int* a = new (GC) int;
 *		If they need to be traceable but not collectable, use the other placement new form:
 *			int* a = new (NoGC) int;
 *
 *
 * TODO: it may be necessary to include libgc within phc to ensure that it is
 * compiled correctly for our use.
 *
 * TODO: should libgc be mandatory (fail to compile without it)? it exists on all platforms...
 * 
 * TODO: what does libgccpp do for us? It doesnt fix the bugs by magic...
 */

// Avoid proliferation of USE_GC by defining the allocator here.
#ifndef DISABLE_GC
#include "gc/gc_cpp.h"
#include "gc/gc_allocator.h"
#define phc_allocator gc_allocator
#else
#define phc_allocator std::allocator
#endif


#ifndef DISABLE_GC
class GC_obj : public gc
#else
class GC_obj
#endif
{
// Make Obj a virtual base (required for RTTI and dynamic casts)
public:
	virtual ~GC_obj() {}
};

class Object : public GC_obj
{
// Objects should support cloning
public:
	virtual Object* clone() = 0;
};

/* These are copies of ideas from LLVM. All of our uses of casts can be
 * characterized as one of these. */
template <class T> bool isa (GC_obj* in) 
{ 
	return dynamic_cast<T*> (in) != NULL;
}

template <class T> bool isa (const GC_obj* in) 
{ 
	return dynamic_cast<const T*> (in) != NULL;
}


template <class T> T* dyc (GC_obj* in)
{
	if (in == NULL) return NULL;

	T* result = dynamic_cast<T*> (in); 
	assert (result != NULL); 
	return result;
}

template <class T> const T* dyc (const GC_obj* in)
{
	if (in == NULL) return NULL;

	const T* result = dynamic_cast<const T*> (in); 
	assert (result != NULL); 
	return result;
}


// Add class traits to indicate whether cloning works (see List.h).
template<typename T> 
struct
supports_cloning
{
  static const bool value = false;
};

#define SET_CLONABLE(TYPE)								\
template<>													\
struct														\
supports_cloning<TYPE*>									\
{																\
  static const bool value = true;					\
};

SET_CLONABLE(Object)


template<typename T> 
struct
supports_equality
{
  static const bool value = false;
};

#define SET_COMPARABLE(TYPE)							\
template<>													\
struct														\
supports_equality<TYPE*>								\
{																\
  static const bool value = true;					\
};																\
template<>													\
struct														\
supports_equality<TYPE>									\
{																\
  static const bool value = true;					\
};

#endif // PHC_OBJECT_H
