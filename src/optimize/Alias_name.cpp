/*
 * phc -- the open source PHP compiler
 * 
 * Representation of a variable_name/object.
 */

#include "MIR.h"
#include "process_ir/General.h"

#include "Basic_block.h"

#include "Alias_name.h"
#include "wpa/Aliasing.h"
#include "wpa/Points_to.h"

#include <boost/algorithm/string/replace.hpp>

using namespace std;
using namespace MIR;

Alias_name::Alias_name ()
: cached_name (NULL)
, ssa_version (0)
{
}

Alias_name::Alias_name (string prefix, string name)
: cached_name (NULL)
, prefix (prefix)
, name (name)
, ssa_version (0)
{
	assert (prefix != "");
}

bool
Alias_name::operator== (const Alias_name& other) const
{
	return this->str () == other.str ();
}

bool
Alias_name::operator!= (const Alias_name& other) const
{
	return not (operator== (other));
}

// In some cases (at least lattice_map, maybe elsewhere), its hard to put use
// an Alias_name instead of a string.
string
Alias_name::str () const
{
	if (cached_name)
		return *cached_name;

	stringstream ss;

	if (prefix != "")
		ss << prefix << "::";

	ss << name;

	if (ssa_version)
		ss << "__v" << ssa_version;

	this->cached_name = s (ss.str ());
	return *cached_name;
}

string
Alias_name::get_name () const
{
	return name;
}

string
Alias_name::get_prefix () const
{
	return prefix;
}

int
Alias_name::get_version () const
{
	return ssa_version;
}

string
Alias_name::non_ssa_str () const
{
	return prefix+"::"+name;
}

void
Alias_name::drop_ssa_version ()
{
	this->cached_name = NULL;
	this->ssa_version = 0;
}

void
Alias_name::set_version (int version)
{
	this->cached_name = NULL;
	this->ssa_version = version;
}

// Return a new Alias_name, which has had its name converted from OLDC to NEWC.
//
// XXX HACK:
// There is a problem that context has been converted to a string by the time
// it gets put into an alias name. So we find it hard to switch from a
// contextual to a non-contextual context. This is hard to fix, so this hacks
// it instead of fixing it properly. We just do a string replacement from the
// name in OLDc to the name in NEWC.
Alias_name
Alias_name::convert_context_name () const
{
	Alias_name result (
		Context::convert_context_name (this->prefix), 
		Context::convert_context_name (this->name));
	assert (this->ssa_version == 0);

	return result;
}

