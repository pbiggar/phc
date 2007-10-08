/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Return the demangled classname of the specified object 
 */

#include <typeinfo>
#include <cxxabi.h>
#include "lib/demangle.h"
#include "string.h"

const char* demangle(Object* obj)
{
	int rv;
	const char* mangled = typeid(*obj).name();
	const char* demangled = abi::__cxa_demangle(mangled, NULL, NULL, &rv);
	if(rv == 0)
	{
		// Strip of the namespace (if any)
		const char* without_namespace = strchr(demangled, ':');
		if(without_namespace != NULL)
			return without_namespace + 2;	// skip the '::'
		else
			return demangled;
	}
	else
		return mangled;
}
