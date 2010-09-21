/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience functions and headers
 */

#ifndef PHC_GENERAL
#define PHC_GENERAL

#include "lib/String.h"


#include "debug.h"
#include "stats.h"
#include "Foreach.h"
#include "fresh.h"
#include "parsing/Parse_buffer.h"

using boost::lexical_cast;

bool is_builtin_function (String* name);

template<class T> T* C(const T* x) { return const_cast<T*> (x); }

template<class T>
T* clone (const T* t)
{
	return C(t)->clone ();
}

template<class T>
bool equals (const T* t1, const T* t2)
{
	return C(t1)->equals (C(t2));
}


#endif // PHC_GENERAL
