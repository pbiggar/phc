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
	mutable String* cached_name;
	string prefix;
	string name;

public:
	Alias_name ();
	Alias_name (const Alias_name* other);
	Alias_name (string prefix, string name);


	bool operator== (const Alias_name& other) const;
	bool operator!= (const Alias_name& other) const;
	size_t hash () const;
	string str () const;

public:
	// Get key for indexing var_stacks
	string non_ssa_str () const;

	// We'd like to make these private
	string get_name () const;
	string get_prefix () const;

	// Drops the context info
	// TODO: if we want to cache these, we should make it const Alias_name
	Alias_name* convert_context_name () const;
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
