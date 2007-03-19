/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Return the demangled classname of the specified object 
 */

#include <typeinfo>
#include <cxxabi.h>
#include "lib/demangle.h"

const char* demangle(Object* obj)
{
	int rv;
	const char* mangled = typeid(*obj).name();
	const char* demangled = abi::__cxa_demangle(mangled, NULL, NULL, &rv);
	if(rv == 0)
		return demangled;
	else
		return mangled;
}
