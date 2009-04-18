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
: ssa_version (0)
{
}

Alias_name::Alias_name (string prefix, string name)
: prefix (prefix)
, name (name)
, ssa_version (0)
{
	assert (prefix != "");
	assert (name != "");
}

bool
Alias_name::operator== (const Alias_name& other) const
{
	return !((*this) < other || other < (*this));
}

bool
Alias_name::operator< (const Alias_name& other) const
{
	// If there is an SSA number, use that.
	if (ssa_version)
	{
		assert (other.ssa_version);
		return ssa_version < other.ssa_version;
	}

	if (prefix == other.prefix)
		return name < other.name;

	return prefix < other.prefix;
}

	// In some cases (at least lattice_map, maybe elsewhere), its hard to put
	// use an Alias_name instead of a string.
string
Alias_name::str ()
{
	stringstream ss;

	if (prefix != "")
		ss << prefix << "::";

	ss << name;

	if (ssa_version)
		ss << "__v" << ssa_version;

	return ss.str ();
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
Alias_name::switch_context (Context oldc, Context newc)
{
	Alias_name result (this->prefix, this->name);
	assert (this->ssa_version == 0);

	string old_cname = oldc.name ();
	string new_cname = newc.name ();

	boost::replace_first (result.prefix, old_cname, new_cname);
	boost::replace_first (result.name, old_cname, new_cname);

	return result;
}


void
Alias_name::drop_ssa_version ()
{
	this->ssa_version = 0;
}

void
Alias_name::set_version (int version)
{
	this->ssa_version = version;
}

