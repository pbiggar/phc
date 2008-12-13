/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Return the demangled classname of the specified object 
 */

#ifndef PHC_DEMANGLE_H
#define PHC_DEMANGLE_H

class Object;

const char* demangle(Object* obj, bool include_namespace = true);

#endif // PHC_DEMANGLE_H
