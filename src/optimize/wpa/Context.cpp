/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Context-sensitivity
 */

#include <boost/regex.hpp>

#include "Context.h"
#include "Points_to.h"

using namespace std;
using namespace boost;

Context::Context()
: use_caller (false)
, cached_name (NULL)
{
}

Context* 
Context::outer (Basic_block* bb)
{
	// Contextual, but only has the outer BB
	Context* result = new Context;
	result->BBs.push_back (bb);
	result->BB_counts[bb]++;
	result->use_caller = true;
	return result;
}
Context* 
Context::non_contextual (Basic_block* bb)
{
	Context* result = new Context;
	result->BBs.push_back (bb);
	result->BB_counts[bb]++;
	result->use_caller = false;
	return result;
}

Context* 
Context::contextual (Context* caller, Basic_block* bb)
{
	Context* result = new Context;
	result->BBs = caller->BBs;
	result->BB_counts = caller->BB_counts;
	result->use_caller = true;

	result->BBs.push_back (bb);
	result->BB_counts[bb]++;

	return result;
}

// Use PEER's caller
Context* 
Context::as_peer (Context* peer, Basic_block* bb)
{
	return Context::contextual (peer->caller(), bb);
}

Context* 
Context::caller () const
{
	assert (this->use_caller);

	Context* result = new Context (*this);
	result->cached_name = NULL;

	Basic_block* popped = result->BBs.back ();
	result->BBs.pop_back ();
	result->BB_counts[popped]--;

	return result;
}

Context* 
Context::get_non_contextual () const
{
	assert (this->use_caller);
	return Context::non_contextual (this->get_bb());
}

Basic_block*
Context::get_bb () const
{
	return BBs.back();
}

bool
Context::is_outer () const
{
	return get_bb ()->ID == 0;
}

bool
Context::empty () const
{
	return BBs.empty ();
}

bool
Context::operator== (const Context &other) const
{
	if (this->use_caller != other.use_caller)
		return false;

	return this->name() == other.name();
}

string
Context::name () const
{
	if (cached_name)
		return *cached_name;

	// How long is our call-string?
	int ignore_length = BBs.size () - pm->args_info->call_string_length_arg;
	if (pm->args_info->call_string_length_arg == 0)
		ignore_length = 0;

	stringstream ss;
	foreach (Basic_block* bb, BBs)
	{
		// Ignore the first N - call_string_length entries.
		if (ignore_length > 0)
		{
			ignore_length--;
			continue;
		}

		ss << "/" << bb->ID;

		// Cant use 'BB_counts[bb]' because of constness
		if (BB_counts.at (bb) > 1)
		{
			// In the case of recursion, stop the name here. This allows us to
			// keep adding to the context, but know that we arent actually
			// changing its representation (allowing us to keep caller()
			// accurate).
			ss << "/" << "R";
      phc_optimization_exception ("Recursion not supported") ;
			break;
		}
	}

	this->cached_name = s (ss.str ());
	return *cached_name;
}

bool
Context::is_recursive () const
{
	foreach (int count, *BB_counts.values ())
		if (count > 1)
			return true;

	return false;
}

string
Context::full_name () const
{
	stringstream ss;
	foreach (Basic_block* bb, BBs)
	{
		ss << "/" << bb->ID;
	}
	return ss.str ();
}

std::ostream &operator<< (std::ostream &out, const Context &num);

string
Context::array_name () const
{
	return storage_name ("array");
}

string
Context::symtable_name () const
{
	// TODO: This name should include the class, or else we're overlapping other
	// methods of the same name.

	if (this->use_caller)
		return "SYM" + get_bb()->get_prefix () + this->caller ()->name();
	else
		return "SYM" + get_bb()->get_prefix ();
}

string
Context::storage_name (string type) const
{
	return type + SEP + this->name ();
}


string
Context::convert_context_name (string name)
{
	// We want to remove traces of the contexts. So:
	//		- symtables get their entire number removed (= to ::)
	//		- heap objects keep the number before the '-'
	//

	string result;

	/* 
	 * Hand-written lexer:
	 *		Start in COPY state.
	 *			Move out of COPY state upon seeing a '/'
	 *			Otherwise copy the character
	 *		If not in COPY state
	 *			Store last number (starts with a '/') and copy it on seeing '-'
	 *			If character is not in [0-9/], copy char and move to COPY state.
	 */
	bool copy = true;
	string last_number;
	
	foreach (char c, name)
	{
		if (copy)
		{
			if (c == '/')
				copy = false;
			else
				result += c;
		}
		else
		{
			if (c != '/' && (c < '0' || c > '9'))
			{
				if (c == '-')
				{
					result += last_number;
				}

				result += c;
				copy = true;
			}
			else
			{
				if (c == '/')
					last_number = "/";
				else
					last_number += c;
			}
		}
	}
	return result;
}

Storage_node*
Context::array_node () const
{
	return SN (array_name ());
}

Storage_node*
Context::storage_node (string type) const
{
	return SN (storage_name (type));
}

Storage_node*
Context::symtable_node () const
{
	return SN (symtable_name ());
}



std::ostream&
operator<< (std::ostream &out, const Context* cx)
{
	out << cx->full_name ();
	return out;
}
