/*
 * phc -- the open source PHP compiler
 * 
 * Name for something in SSA form.
 */

#include "process_ir/General.h"
#include "SSA_name.h"

using namespace std;
using namespace MIR;

SSA_name::SSA_name ()
: ssa_version (0)
{
}

SSA_name::SSA_name (string name)
: name (name)
, ssa_version (0)
{
}

bool
SSA_name::operator== (const SSA_name& other) const
{
	return this->str () == other.str ();
}

bool
SSA_name::operator!= (const SSA_name& other) const
{
	return not (operator== (other));
}

size_t
SSA_name::hash () const
{
	return std::tr1::hash<string>() (this->str ());
}

string
SSA_name::str () const
{
	stringstream ss;
	ss << name;

	if (ssa_version)
		ss << "__v" << ssa_version;

	return ss.str ();
}

string
SSA_name::get_name () const
{
	return name;
}

int
SSA_name::get_version () const
{
	return ssa_version;
}

void
SSA_name::drop_ssa_version ()
{
	this->ssa_version = 0;
}

void
SSA_name::set_version (int version)
{
	this->ssa_version = version;
}

