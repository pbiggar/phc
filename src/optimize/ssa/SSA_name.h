/*
 * phc -- the open source PHP compiler
 * 
 * Name for something in SSA form.
 */
 
#ifndef PHC_SSA_NAME
#define PHC_SSA_NAME

#include <string>
#include "lib/List.h"

DECL(SSA_name);

class Index_node;

class SSA_name : virtual public GC_obj
{
	std::string name;
	int ssa_version;

public:
	SSA_name (std::string name);
	SSA_name ();

	bool operator== (const SSA_name& other) const;
	bool operator!= (const SSA_name& other) const;
	size_t hash () const;

public:
	// I'm not 100% sure what this is used for...
	std::string str () const;
	std::string get_name () const;

	// We'd like to make these private
	int get_version () const;
	void set_version (int version);
	void drop_ssa_version ();

	bool is_starred() const;
	Index_node *reverse() const;
};


namespace std
{
	template <>                                     
	struct equal_to <const SSA_name*>
	{                                                     
		bool operator () (const SSA_name* const sn1, const SSA_name* const sn2) const
		{
			return *sn1 == *sn2;
		}
	};

	template <>                                     
	struct equal_to <SSA_name*>
	{                                                     
		bool operator () (const SSA_name*& sn1, const SSA_name*& sn2) const
		{
			return *sn1 == *sn2;
		}
	};



	namespace tr1
	{
		template <>
		struct hash<SSA_name>
		{
			size_t operator() (const SSA_name& sn) const
			{
				return sn.hash ();
			}
		};

		template <>
		struct hash<const SSA_name>
		{
			size_t operator() (const SSA_name& sn) const
			{
				return sn.hash ();
			}
		};

		template <>
		struct hash<SSA_name*>
		{
			size_t operator() (const SSA_name*& sn) const
			{
				return sn->hash ();
			}
		};

		template <>
		struct hash<const SSA_name*>
		{
			size_t operator() (const SSA_name* const sn) const
			{
				return sn->hash ();
			}
		};
	}
}



#endif // PHC_SSA_NAME
