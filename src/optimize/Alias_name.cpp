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
	ss << prefix << "::" << name;
	if (ssa_version)
		ss << "__v" << ssa_version;

	return ss.str ();
}

Alias_name
v2an (Basic_block* bb, VARIABLE_NAME* var)
{
	return Alias_name (ST (bb), *var->value);
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

/*
 * It seems that since we use Alias_name everywhere, we might not actually
 * need the Index_node and Storage_nodes. That may be the case. Currently,
 * the difference between the two is useful in Points_to::get_target. It
 * could probably be replaced with is_ind() instead, though. I'm in no rush
 * to do this.
 */
Index_node*
Alias_name::ind()
{
	assert (ssa_version == 0);
	assert (prefix != SNP);
	return new Index_node (prefix, name);
}

Storage_node*
Alias_name::stor()
{
	assert (ssa_version == 0);
	assert (prefix == SNP);
	return new Storage_node (name);
}


