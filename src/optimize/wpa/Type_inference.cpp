/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#include "Type_inference.h"
#include "optimize/Abstract_value.h"
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
Type_inference::assign_scalar (Basic_block* bb, Alias_name lhs, Alias_name lhs_storage, Abstract_value* val, certainty cert)
{
	Lattice_map& lat = outs[bb->ID];

	// If theres a literal, there will be a type.
	lat[lhs.str()] = meet (lat[lhs.str()], val->type);
	lat[lhs_storage.str()] = meet (lat[lhs_storage.str()], val->type);
}

void
Type_inference::assign_storage (Basic_block* bb, Alias_name lhs,
						  Alias_name storage, certainty cert)
{
	// TODO: this needs type information
	outs[bb->ID][lhs.str()] = BOTTOM;
	outs[bb->ID][storage.str()] = BOTTOM;
}

void
Type_inference::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	outs[bb->ID][lhs.str()] = meet (outs[bb->ID][lhs.str()], new Type_cell ("array"));
	outs[bb->ID][unique_name] = meet (outs[bb->ID][unique_name], new Type_cell ("array"));
}


Types
Type_inference::get_types (Basic_block* bb, Alias_name name)
{
	Lattice_cell* cell = get_value (bb, name);

	if (cell == BOTTOM)
		phc_TODO ();

	if (cell == TOP)
		return Types ("unset");

	// TODO: this will fail for bottom
	return dyc<Type_cell> (cell)->types;
}

Map<int, string>
init_MIR_types ()
{
	Map<int, string> result;

	result[MIR::BOOL::ID]	= "bool";
	result[MIR::INT::ID]		= "int";
	result[MIR::NIL::ID]		= "unset";
	result[MIR::REAL::ID]	= "real";
	result[MIR::STRING::ID]	= "string";

	return result;
}

Map<int, string>
Type_inference::MIR_types = init_MIR_types ();

Types
init_scalar_types ()
{
	Types result;

	result.insert ("bool");
	result.insert ("int");
	result.insert ("unset");
	result.insert ("real");
	result.insert ("string");

	return result;
}

Types
Type_inference::scalar_types = init_scalar_types ();


Types 
Type_inference::get_type (MIR::Literal* lit)
{
	return Types (MIR_types [lit->classid()]);
}


Types
Type_inference::get_scalar_types (Types in)
{
	Types out;

	// Faster and simpler to check for each scalar type than the other way
	// round.
	foreach (string scalar, scalar_types)
		if (in.has (scalar))
			out.insert (scalar);

	return out;
}

Types
Type_inference::get_array_types (Types in)
{
	if (in.has ("array"))
		return Types ("array");
	else
		return Types ();
}

Types
Type_inference::get_object_types (Types in)
{
	Types out;
	foreach (string type, in)
		if (!scalar_types.has (type) && type != "array")
			out.insert (type);

	return out;
}

Types
Type_inference::get_unary_op_types (Basic_block* bb, Abstract_value* operand, string op)
{
	Set<string> always_bool_ops;
	always_bool_ops.insert ("!");
	if (always_bool_ops.has (op))
		return Types ("bool");

	phc_TODO ();
}

Types
Type_inference::get_bin_op_type (string ltype, string rtype, string op)
{
	Set<string> always_bool_ops;
	always_bool_ops.insert ("<");
	always_bool_ops.insert ("<=");
	always_bool_ops.insert (">");
	if (always_bool_ops.has (op))
		return Types ("bool");

	// TODO: implicit __toString on both params
	if (op == ".")
		return Types ("string");

	phc_TODO ();

//	Map<string, Map <string, Map<string, Types > > > type_map;
//	type_map ["+"]["int"]["int"] = Types ("int");
//	type_map ["<"]["int"]["int"] = Types ("bool");

}

Types
Type_inference::get_bin_op_types (Basic_block* bb, Abstract_value* left, Abstract_value* right, string op)
{
	if (left->type == BOTTOM)
		phc_TODO ();

	if (right->type == BOTTOM)
		phc_TODO ();

	Types result_types;
	foreach (string ltype, dyc<Type_cell> (left->type)->types)
		foreach (string rtype, dyc<Type_cell> (right->type)->types)
		{
			Types op_result = get_bin_op_type (ltype, rtype, op);
			result_types.insert (op_result.begin (), op_result.end());
		}

	return result_types;
}


/*
 * Lattice
 */

Type_cell::Type_cell (string type)
{
	types.insert (type);
}

Type_cell::Type_cell (Types ts)
{
	types.insert (ts.begin(), ts.end());
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
