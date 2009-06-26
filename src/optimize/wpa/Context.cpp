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
Context::caller ()
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
Context::get_non_contextual ()
{
	assert (this->use_caller);
	return Context::non_contextual (this->get_bb());
}

Basic_block*
Context::get_bb ()
{
	return BBs.back();
}

bool
Context::is_outer ()
{
	return get_bb ()->ID == 0;
}

bool
Context::empty ()
{
	return BBs.empty ();
}

bool
Context::operator< (const Context &other) const
{
	if (this->use_caller != other.use_caller)
		return this->use_caller < other.use_caller;

	// Not using context means any BB with the same ID matches.
	return this->name() < other.name();
}

bool
Context::operator== (const Context &other) const
{
	return !(*this < other) && !(other < *this);
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
			break;
		}
	}

	this->cached_name = new string (ss.str ());
	return *cached_name;
}

bool
Context::is_recursive ()
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
Context::array_name ()
{
	return storage_name ("array");
}

string
Context::symtable_name ()
{
	if (this->use_caller)
		return get_bb()->get_prefix () + this->caller ()->name();
	else
		return get_bb()->get_prefix ();
}

string
Context::storage_name (string type)
{
	return type + SEP + this->name ();
}


string
Context::convert_context_name (string name)
{
	string BB_ID = "/\\d+";
	string all_IDs = "(" + BB_ID + ")+";

	string symtable = all_IDs;
	string heap = all_IDs + "(" + BB_ID + "-\\d+)";


	// If it starts with "$type$SEP", we want the last BB ID, its a
	// heap allocation, and we want its last BB ID.
   static boost::regex re1 ("(ST::)?(\\w+)=" + heap + "(.*)");
   if (boost::regex_match (name, re1))
	{
		string result = boost::regex_replace (name, re1, "\\1\\2\\4\\5");
//		cdebug << "RE1 matches: " << name << " -> " << result << "\n";
		return result;
	}



	// Remove other BB IDs
   static boost::regex re2("([^/]+)" + symtable + "(.*)");
   if (boost::regex_match (name, re2))
	{
		string result = boost::regex_replace (name, re2, "\\1\\3");
//		cdebug << "RE2 matches: " << name << " -> " << result << "\n";
		return result;
	}
	
	// Otherwise, just leave it

//	cdebug << "No matches: " << name << "\n";
	return name;
}

Storage_node*
Context::array_node ()
{
	return SN (array_name());
}

Storage_node*
Context::storage_node (string type)
{
	return SN (storage_name (type));
}

Storage_node*
Context::symtable_node ()
{
	return SN (symtable_name ());
}



std::ostream&
operator<< (std::ostream &out, const Context* cx)
{
	out << cx->full_name ();
	return out;
}
