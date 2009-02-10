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
	assign_unknown_typed (bb, lhs, get_literal_type (rhs), cert);
}

Set<string>
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


Set<string>
Type_inference::get_bin_op_type (string ltype, string rtype, string op)
{
	Set<string> always_bool_ops;
	always_bool_ops.insert ("<");
	if (always_bool_ops.has (op))
		return Set<string> ("bool");

	phc_TODO ();

//	Map<string, Map <string, Map<string, Set<string> > > > type_map;
//	type_map ["+"]["int"]["int"] = Set<string> ("int");
//	type_map ["<"]["int"]["int"] = Set<string> ("bool");

}




Set<string>
Type_inference::get_bin_op_types (Basic_block* bb, Alias_name* left, Alias_name* right, MIR::Literal* left_lit, MIR::Literal* right_lit, string op)
{
	assert (left_lit || left);
	assert (right_lit || right);

	Set<string>* left_types;
	Set<string>* right_types;

	if (left_lit)
		left_types = new Set<string> (get_literal_type (left_lit));
	else
		left_types = get_types (bb, *left).clone ();

	if (right_lit)
		right_types = new Set<string> (get_literal_type (right_lit));
	else
		right_types = get_types (bb, *right).clone ();


	// (op, type, type) -> {types}
	// TODO: what about impossible types?
	// TODO: what about all types: (<, *, *) -> {bool}
	if (left_types->size() != 1)
		phc_TODO ();
	if (right_types->size() != 1)
		phc_TODO ();

	Set<string> result_types;
	foreach (string ltype, *left_types)
		foreach (string rtype, *right_types)
		{
			Set<string> op_result = get_bin_op_type (ltype, rtype, op);
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
