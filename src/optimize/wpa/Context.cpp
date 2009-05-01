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

Context
Context::outer (Basic_block* bb)
{
	// Contextual, but only has the outer BB
	Context result;
	result.BBs.push_back (bb);
	result.BB_counts[bb]++;
	result.use_caller = true;
	return result;
}
Context
Context::non_contextual (Basic_block* bb)
{
	Context result;
	result.BBs.push_back (bb);
	result.BB_counts[bb]++;
	result.use_caller = false;
	return result;
}

Context
Context::contextual (Context caller, Basic_block* bb)
{
	Context result;
	result.BBs = caller.BBs;
	result.BB_counts = caller.BB_counts;
	result.use_caller = true;

	result.BBs.push_back (bb);
	result.BB_counts[bb]++;

	return result;
}

// Use PEER's caller
Context
Context::as_peer (Context peer, Basic_block* bb)
{
	return Context::contextual (peer.caller(), bb);
}

Context
Context::caller ()
{
	assert (this->use_caller);

	Context result = *this;
	result.cached_name = NULL;

	Basic_block* popped = result.BBs.back ();
	result.BBs.pop_back ();
	result.BB_counts[popped]--;

	return result;
}

Context
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

	stringstream ss;
	foreach (Basic_block* bb, BBs)
	{
		ss << "/" << bb->ID;

		// Cant use [] because of constness
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
	return "array_" + this->name ();
}

string
Context::object_name ()
{
	return "object_" + this->name ();
}

string
Context::symtable_name ()
{
	if (this->use_caller)
		return *get_bb()->cfg->method->signature->method_name->value + "_" + this->caller().name();
	else
		return *get_bb()->cfg->method->signature->method_name->value + "_";
}


string
Context::convert_context_name (string name)
{
	// If it starts with "array_" or "object_", we want the last BB ID, its a
	// heap allocation, and we want its last BB ID.
	string BB_ID = "/\\d+";
	string all_IDs = "(" + BB_ID + ")+";
	string all_but_one = all_IDs + "(" + BB_ID + ")";

   boost::regex re1 ("(array|object)_" + all_but_one);
   if (boost::regex_match (name, re1))
	{
		return boost::regex_replace (name, re1, "\\1\\3");
	}


	// Remove other BB IDs
   boost::regex re2("([^/]+)" + all_IDs);
   if (boost::regex_match (name, re2))
	{
		return boost::regex_replace (name, re2, "\\1");
	}


	
	// Otherwise, just leave it
	return name;
}

Storage_node*
Context::array_node ()
{
	return SN (array_name());
}

Storage_node*
Context::object_node ()
{
	return SN (object_name ());
}

Storage_node*
Context::symtable_node ()
{
	return SN (symtable_name ());
}



std::ostream&
operator<< (std::ostream &out, const Context &cx)
{
	out << cx.full_name ();
	return out;
}



void
CX_lattices::dump (Context cx, string name)
{
	if (this->has (cx))
	{
		cdebug << name << " Lattice for BB: " << cx << endl;
		(*this)[cx].dump();
		cdebug << endl;
	}
	else
		cdebug << "No " << name << " results for BB: " << cx << endl;
}

void
CX_lattices::dump_everything (string name)
{
	foreach (Context cx, *this->keys())
	{
		dump (cx, name);
	}
}
