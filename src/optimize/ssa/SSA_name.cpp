/*
 * phc -- the open source PHP compiler
 * 
 * Name for something in SSA form.
 */

#include "process_ir/General.h"
#include "SSA_name.h"
#include "lib/String.h"
#include "optimize/wpa/Points_to.h"

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

bool SSA_name::is_starred() const {
	return boost::starts_with(name, "*_");
}

/*
 * This functions builds an Index_node based on the current SSA name.
 * This is considered to be a dangerous conversion, and its use
 * is highly discouraged.
 */
Index_node *SSA_name::reverse() const {
  // Do not build starred index nodes.
  string n = is_starred() ? name.substr(2) : name;

  // Seek the last delimiter.
  size_t idx = n.rfind("::");
  phc_optimization_assertion(idx != string::npos);

  // Split between the storage node and the index node.
  string storage = n.substr(0, idx);
  string index = n.substr(idx + 2);

  // Return the correspondent index node.
  return (new Index_node(storage, index));
}
