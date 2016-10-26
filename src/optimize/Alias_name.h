/*
 * phc -- the open source PHP compiler
 * 
 * Representation of a variable_name/object.
 */
 
/*
 * Every 'memory_location' modelled must have a unique name. We previously
 * used strings to represent these, but we dont want to be manipulating
 * strings just to find out what function a name is in.
 *
 * The alias_name is either an Index_node, in which case the first part is a
 * function_name, and the second is the variable name. Otherwise its a
 * storage node, in which case the first part is "ST", and the second is some
 * unique name based on the program point of its defintion.
 *
 * This abstracts over the name. The only important part is that they are
 * unique. However, is order to trim the results, some passes may wish to
 * rely on the first part of the name being the function_name. That's fine.
 */

#ifndef PHC_ALIAS_NAME
#define PHC_ALIAS_NAME

#include <string>
#include "lib/List.h"

class Context;

class Index_node;
class Storage_node;

#define SEP "="

DECL(Alias_name);
typedef List<const Alias_name*> cAlias_name_list;

class Alias_name : virtual public GC_obj
{
public:
	Alias_name ();

	virtual bool operator== (const Alias_name& other) const;
	virtual bool operator!= (const Alias_name& other) const;
	size_t hash () const;

	virtual string str () const = 0;

public:

	// TODO: if we want to cache these, we should make it const Alias_name

	// Return a new Alias_name, which has had its name converted from OLDC to NEWC.
	//
	// XXX HACK:
	// There is a problem that context has been converted to a string by the
	// time it gets put into an alias name. So we find it hard to switch from a
	// contextual to a non-contextual context. This is hard to fix, so this
	// hacks it instead of fixing it properly. We just do a string replacement
	// from the name in OLDc to the name in NEWC.

	virtual Alias_name* convert_context_name () const = 0;
	virtual String* get_graphviz_label () const = 0;
};


namespace std
{
	template <>                                     
	struct equal_to <const Alias_name*>
	{                                                     
		bool operator () (const Alias_name* const an1, const Alias_name* const an2) const
		{
			return *an1 == *an2;
		}
	};

	template <>                                     
	struct equal_to <Alias_name*>
	{                                                     
		bool operator () (const Alias_name*& an1, const Alias_name*& an2) const
		{
			return *an1 == *an2;
		}
	};



	namespace tr1
	{
		template <>
		struct hash<Alias_name>
		{
			size_t operator() (const Alias_name& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<const Alias_name>
		{
			size_t operator() (const Alias_name& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<Alias_name*>
		{
			size_t operator() (const Alias_name*& an) const
			{
				return an->hash ();
			}
		};

		template <>
		struct hash<const Alias_name*>
		{
			size_t operator() (const Alias_name* const an) const
			{
				return an->hash ();
			}
		};
	}
}

#endif // PHC_ALIAS_NAME
