/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Return the demangled classname of the specified object 
 */

#include <typeinfo>
#include <cxxabi.h>
#include <string.h>

#include "lib/Object.h"

#include "lib/demangle.h"

const char* demangle(GC_obj* obj, bool include_namespace)
{
	int rv;
	const char* mangled = typeid(*obj).name();
	const char* demangled = abi::__cxa_demangle(mangled, NULL, NULL, &rv);
	if(rv == 0)
	{
		// Strip of the namespace (if any)
		const char* without_namespace = strchr(demangled, ':');
		if(without_namespace != NULL && !include_namespace)
			return without_namespace + 2; // skip the '::'
		else
			return demangled;
	}
	else
		return mangled;
}
