/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#include "Type_inference.h"
#include "Whole_program.h"
#include "MIR.h"

using namespace MIR;
using namespace std;
using namespace boost;

Type_inference::Type_inference (Whole_program* wp)
: WPA_lattice (wp)
{
}

void
Type_inference::assign_unknown_typed (Basic_block* bb, Alias_name lhs, string type, certainty cert)
{
	outs[bb->ID][lhs.str()] = meet (outs[bb->ID][lhs.str()], new Type_cell (type));
}
	
void
Type_inference::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	outs[bb->ID][lhs.str()] = meet (outs[bb->ID][lhs.str()], new Type_cell ("array"));
	outs[bb->ID][unique_name] = meet (outs[bb->ID][unique_name], new Type_cell ("array"));
}

void
Type_inference::assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* rhs, certainty cert)
{
	Map<int, string> type_names;
	type_names[MIR::BOOL::ID]		= "bool";
	type_names[MIR::INT::ID]		= "int";
	type_names[MIR::NIL::ID]		= "nil";
	type_names[MIR::REAL::ID]		= "real";
	type_names[MIR::STRING::ID]	= "string";

	outs[bb->ID][lhs.str()] = meet (outs[bb->ID][lhs.str()],
		new Type_cell (type_names[rhs->classid()]));
}


/*
 * Lattice
 */

Type_cell::Type_cell (string type)
{
	types.insert (type);
}

Type_cell::Type_cell ()
{
}

void
Type_cell::dump ()
{
	foreach (string type, types)
	{
		cdebug << type << ", ";
	}
}

bool
Type_cell::equals (Lattice_cell* other_cell)
{
	Type_cell* other = dyc<Type_cell> (other_cell);

	if (other->types.size () != this->types.size ())
		return false;

	foreach (string type, types)
		if (!other->types.has (type))
			return false;

	return true;
}

Lattice_cell*
Type_cell::meet (Lattice_cell* other)
{
	Type_cell* tc = dyc<Type_cell> (other);

	// Merge the contents of the two
	Type_cell* result = new Type_cell;

	foreach (string type, types)
		result->types.insert (type);

	foreach (string type, tc->types)
		result->types.insert (type);

	return result;
}
