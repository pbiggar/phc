/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * GC_Obj provides a polymorpic base (i.e., a base that supports RTTI), and
 * garbage collection.  Object additionally provides a clone() method.
 */

#ifndef PHC_OBJECT_H
#define PHC_OBJECT_H

#include "config.h"
#include <assert.h>

#ifndef NULL
#define NULL 0L
#endif

#ifdef ENABLE_GC
#ifdef HAVE_GC_LIB
#ifdef HAVE_GC_INC
// Logical AND for the preceding three
#define USE_GC
#endif
#endif
#endif

/*
 * Garbage collection:
 *
 *	We use the Boehm garbage collector for C++. This creates a very small number
 *	of rules that we need to follow. Failure to follow these rules will
 *	typically lead to the garbage allocator prematurely collecting objects,
 *	leading to segfaults. (Note: object on the stack are NOt excepted).
 *
 *	1. _ALL_ (let me repeat, ALL) classes which we define need to inherit from GC_Obj.
 *	2. Never use STL objects without wrapping them. The naming scheme is as follows:
 *		- phc::map is identical to std::map, except that it uses it uses the GC allocator.
 *		- phc::Map is a phc::map with extra interface components such as the clone() method.
 *	3. When using embedded PHP, do garbage collection manually. If garbage
 *		collected objects need to be put in PHP structures (which they currently
 *		dont), then the memory must be allocated using libgc's traceable
 *		allocators, which traces, but doesn't deallocate memory.
 *	4. For exceptional objects allocated with new, use the placement new form:
 *			int* a = new (GC) int;
 *		If they need to be traceable but not collectable, use the other placement new form:
 *			int* a = new (NoGC) int;
 *	5. Object which dont contain other objects and are allocated on the stack
 *		are OK: ie string, stringstream.
 *
 *
 * TODO: it may be necessary to include libgc within phc to ensure that it is
 * compiled correctly for our use.
 */



#ifdef USE_GC
#include "gc/gc_cpp.h"
class GC_Obj : public gc
#else
class GC_Obj
#endif
{
// Make Obj a virtual base (required for RTTI and dynamic casts)
public:
	virtual ~GC_Obj() {}
};

class Object : public GC_Obj
{
// Objects should support cloning
public:
	virtual Object* clone() = 0;
};

/* These are copies of ideas from LLVM. All of our uses of casts can be
 * characterized as one of these. */
template <class T> bool isa(GC_Obj* in) 
{ 
	return dynamic_cast<T*> (in) != NULL;
}

template <class T> T* dyc(GC_Obj* in)
{
	if (in == NULL) return NULL;

	T* result = dynamic_cast<T*> (in); 
	assert (result != NULL); 
	return result;
}

#endif // PHC_OBJECT_H
