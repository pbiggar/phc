/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#include "MIR.h"

#include "Whole_program.h"
#include "Type_inference.h"
#include "optimize/Abstract_value.h"
#include "Points_to.h"

using namespace MIR;
using namespace std;
using namespace boost;

Type_inference::Type_inference (Whole_program* wp)
: WPA_lattice (wp)
{
}

void
Type_inference::set_scalar (Context cx, Value_node* storage, Abstract_value* val)
{
	Lattice_map& lat = outs[cx];
	string name = storage->name().str();
	lat[name] = meet (lat[name], val->type);
}

void
Type_inference::set_storage (Context cx, Storage_node* storage, Types types)
{
	Lattice_map& lat = outs[cx];
	string name = storage->name().str();
	lat[name] = meet (lat[name], new Type_cell (types));
}

void
Type_inference::pull_possible_null (Context cx, Index_node* node)
{
	Lattice_map& lat = ins[cx];
	lat[node->name().str()] = meet (lat[node->name().str()], new Type_cell (Types ("unset")));
	lat[ABSVAL(node)->name().str()] = meet (lat[ABSVAL(node)->name().str()], new Type_cell (Types ("unset")));
}


Types
Type_inference::get_types (Context cx, Alias_name name)
{
	Lattice_cell* cell = get_value (cx, name);

	if (cell == BOTTOM)
		phc_TODO ();

	if (cell == TOP)
		return Types ("unset");

	// TODO: this will fail for bottom
	return dyc<Type_cell> (cell)->types;
}


void
Type_inference::set_types (Context cx, Alias_name name, Types types)
{
	Lattice_map& lat = outs[cx];

	lat[name.str()] = meet (lat[name.str()], new Type_cell (types));
}

static class MIR_types : public Map<int,string>
{
public:
   MIR_types () : Map<int,string>()
	{
		(*this)[MIR::BOOL::ID]		= "bool";
		(*this)[MIR::INT::ID]		= "int";
		(*this)[MIR::NIL::ID]		= "unset";
		(*this)[MIR::REAL::ID]		= "real";
		(*this)[MIR::STRING::ID]	= "string";
	}
} mir_types;

static class Scalar_types : public Types
{
public:
   Scalar_types () : Types()
	{
		insert ("bool");
		insert ("int");
		insert ("unset");
		insert ("real");
		insert ("string");
	}
} scalar_types;


Types
Type_inference::get_all_scalar_types ()
{
	return scalar_types;
}

Types
Type_inference::get_type (MIR::Literal* lit)
{
	return Types (mir_types [lit->classid()]);
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
Type_inference::get_unary_op_types (Context cx, Abstract_value* operand, string op)
{
	Set<string> always_bool_ops;
	always_bool_ops.insert ("!");
	if (always_bool_ops.has (op))
		return Types ("bool");

	if (op == "-")
		return dyc<Type_cell> (operand->type)->types;

	DEBUG ("unary op: " << op << " not handled");
	phc_TODO ();
}

Types
Type_inference::get_bin_op_type (string ltype, string rtype, string op)
{
	if (!scalar_types.has (ltype) || !scalar_types.has (rtype))
		phc_TODO ();

	Set<string> always_bool_ops;
	always_bool_ops.insert ("<");
	always_bool_ops.insert ("<=");
	always_bool_ops.insert ("==");
	always_bool_ops.insert (">");
	if (always_bool_ops.has (op))
		return Types ("bool");

	// TODO: implicit __toString on both params
	if (op == ".")
		return Types ("string");
	else if (op == "*")
	{
		if (ltype == "real" || rtype == "real")
			return Types ("real");

		return Types ("int", "real");
	}
	else if (op == "/")
	{
		if (ltype == "real" || rtype == "real")
			return Types ("real", "bool"); // FALSE for divide by zero

		// PHP division is not modulo arithmetic
		if (ltype == "int" && rtype == "int")
			return Types ("int", "bool", "real"); // FALSE for divide by zero

		// Other scalars are possible
		phc_TODO ();
	}
	else if (op == "/")
	{
		return Types ("int", "bool"); // FALSE for divide by zero
	}
	else if (op == "%")
	{
		if (ltype == "real" || rtype == "real")
			return Types ("real", "bool"); // FALSE for divide by zero

		// PHP division is not modulo arithmetic
		if (ltype == "int" && rtype == "int")
			return Types ("int", "bool", "real"); // FALSE for divide by zero

		// Other scalars are possible
		phc_TODO ();
	}
	else if (op == "+")
	{
		if (ltype == "array" && rtype == "array")
			phc_TODO ();

		if (ltype == "real" || rtype == "real")
			return Types ("real");

		// ints can overflow.
		// Strings, bools and NULLs coerce to ints
		return Types ("int", "real"); // possible overflow
	}
	else if (op == "-")
	{
		if (ltype == "real" || rtype == "real")
			return Types ("real");

		// ints can overflow.
		// Strings, bools and NULLs coerce to ints
		return Types ("int", "real"); // possible overflow
	}

	phc_TODO ();

//	Map<string, Map <string, Map<string, Types > > > type_map;
//	type_map ["+"]["int"]["int"] = Types ("int");
//	type_map ["<"]["int"]["int"] = Types ("bool");

}

Types
Type_inference::get_bin_op_types (Context cx, Abstract_value* left, Abstract_value* right, string op)
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
Type_cell::dump (ostream& os)
{
	foreach (string type, types)
	{
		os << type << ", ";
	}
}

bool
Type_cell::equals (Lattice_cell* other_cell)
{
	// TODO: I think I can replace this with Set::equals or set::operator==
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
