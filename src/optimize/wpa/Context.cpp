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
Context::outer (Basic_block* bb)
{
	// Contextual, but only has the outer BB
	Context result;
	result.BBs.push_back (bb);
	result.use_caller = true;
	return result;
}
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

Context
Context::caller ()
{
	assert (this->use_caller);

	Context result = *this;
	result.BBs.pop_back ();
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


