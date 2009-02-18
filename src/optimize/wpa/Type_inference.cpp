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
Type_inference::assign_value (Basic_block* bb, Alias_name lhs, Abstract_value* val, Alias_name* source, certainty cert)
{
	Lattice_map& lat = outs[bb->ID];
	if (source)
		phc_TODO ();

	// If theres a literal, there will be a type.
	lat[lhs.str()] = meet (lat[lhs.str()], val->type);
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
	// TODO: this will fail for bottom
	return dyc<Type_cell> (get_value (bb, name))->types;
}



string
Type_inference::get_literal_type (MIR::Literal* lit)
{
	Map<int, string> type_names;
	type_names[MIR::BOOL::ID]		= "bool";
	type_names[MIR::INT::ID]		= "int";
	type_names[MIR::NIL::ID]		= "nil";
	type_names[MIR::REAL::ID]		= "real";
	type_names[MIR::STRING::ID]	= "string";

	return type_names[lit->classid()];
}

Types
Type_inference::get_unary_op_types (Basic_block* bb, Alias_name* operand, string op)
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
Type_inference::get_bin_op_types (Basic_block* bb, Alias_name* left, Alias_name* right, MIR::Literal* left_lit, MIR::Literal* right_lit, string op)
{
	assert (left_lit || left);
	assert (right_lit || right);

	Types* left_types;
	Types* right_types;

	if (left_lit)
		left_types = new Types (get_literal_type (left_lit));
	else
		left_types = get_types (bb, *left).clone ();

	if (right_lit)
		right_types = new Types (get_literal_type (right_lit));
	else
		right_types = get_types (bb, *right).clone ();

	Types result_types;
	foreach (string ltype, *left_types)
		foreach (string rtype, *right_types)
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
