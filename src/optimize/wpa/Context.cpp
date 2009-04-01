/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Context-sensitivity
 */

#include "Context.h"

using namespace std;
using namespace boost;

Context
Context::non_contextual (Basic_block* bb)
{
	Context result;
	result.BBs.push_back (bb);
	result.use_caller = false;
	return result;
}

Context
Context::contextual (Context caller, Basic_block* bb)
{
	Context result;
	result.BBs = caller.BBs;
	result.use_caller = true;
	result.BBs.push_back (bb);
	return result;
}

// Use PEER's caller
Context
Context::as_peer (Context peer, Basic_block* bb)
{
	Context result;
	result.BBs = peer.caller ().BBs;
	result.BBs.push_back (bb);
	result.use_caller = true;
	return result;
}

// Represents the first caller
Context
Context::outer_scope ()
{
	Context result;
	result.BBs.push_back (NULL);
	result.use_caller = true;
	return result;
}

Context
Context::caller ()
{
	assert (this->use_caller);

	Context result = *this;
	result.BBs.pop_back ();
	return result;
}

Basic_block*
Context::get_bb ()
{
	return BBs.back();
}

bool
Context::operator< (const Context &other) const
{
	// Not using context means any BB with the same ID matches.
	if (!this->use_caller)
		return this->BBs.back()->ID < other.BBs.back()->ID;

	// TODO: what about other.use_caller

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
	stringstream ss;
	foreach (Basic_block* bb, BBs)
	{
		if (bb == NULL) // outer_scope
			ss << "/" << "NULL";
		else
			ss << "/" << bb->ID;
	}
	return ss.str ();
}

std::ostream &operator<< (std::ostream &out, const Context &num);


string
CX_array_name (Context cx)
{
	return "array_" + cx.name ();
}

string
CX_object_name (Context cx)
{
	return "object_" + cx.name ();
}

std::ostream&
operator<< (std::ostream &out, const Context &cx)
{
	out << cx.name ();
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


