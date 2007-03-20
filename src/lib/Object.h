/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * The sole purpose of Object is to guarantee a polymorpic base
 * (i.e., a base that supports RTTI)
 */

#ifndef PHC_OBJECT
#define PHC_OBJECT

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

#ifdef USE_GC
#include "gc/gc_cpp.h"
class Object : public gc
#else
class Object
#endif
{
// Make Object a virtual base (required for RTTI and dynamic casts)
public:
	virtual ~Object() {}

// Objects should support cloning
public:
	virtual Object* clone() = 0;
};

#endif /* OBJECT_H */
