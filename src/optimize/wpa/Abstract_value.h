/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Abstract values fetch their results from optimizations, and are then read
 * by (possibly other) optimizations to perform their analyses.
 *
 * For example, we might be able to say that an int times 1 is an int, but
 * not than an int times and int is an int.
 *
 */

#ifndef PHC_ABSTRACT_VALUE_H
#define PHC_ABSTRACT_VALUE_H

class Type_lattice;
class CCP_lattice;

class Abstract_value : public GC_obj
{
public:
	Abstract_value ();
	Type_cell* type;
	Literal_cell* type;
};

#endif // PHC_ABSTRACT_VALUE_H
