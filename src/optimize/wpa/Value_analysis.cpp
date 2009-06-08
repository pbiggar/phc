/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A lattice representing values we wish to represent. Currently models types
 * and literals.
 *
 */

#include "optimize/Abstract_value.h"
#include "Points_to.h"
#include "Value_analysis.h"

using namespace std;
using namespace boost;
using namespace MIR;

Value_analysis::Value_analysis (Whole_program* wp)
: WPA_lattice<Absval_cell> (wp)
{
}


/*
 * WPA interface
 */


void
Value_analysis::set_storage (Context cx, Storage_node* storage, Types* types)
{
	Lattice_type& lat = outs[cx];
	string name = storage->name().str();

	lat[name] = lat[name]->meet (new Absval_cell (new Abstract_value (types)));
}

void
Value_analysis::set_scalar (Context cx, Value_node* storage, Abstract_value* val)
{
	Lattice_type& lat = outs[cx];
	string name = storage->name().str();

	lat[name] = lat[name]->meet (new Absval_cell (val));
}

void
Value_analysis::pull_possible_null (Context cx, Index_node* index)
{
	Lattice_type& lat = ins[cx];

	// WPA_lattice::assign_value copies the SCLVAL to the index_node in the
	// general case. However, we need to do it ourselves here.
	string scalar_name = SCLVAL (index)->name().str();
	lat[scalar_name] = lat[scalar_name]->meet (new Absval_cell (new Abstract_value (new NIL)));

	string name = index->name().str();
	lat[name] = lat[name]->meet (new Absval_cell (new Abstract_value (new NIL)));
}


/*
 * Literals
 */

MIR::Literal*
Value_analysis::get_lit (Context cx, Alias_name name)
{
	return get_value (cx, name)->value->lit;
}

/*
 * Types
 */

Types*
Value_analysis::get_types (Context cx, Alias_name name)
{
	return get_value (cx, name)->value->types;
}



Types*
Value_analysis::get_bin_op_types (Context cx, Abstract_value* left, Abstract_value* right, string op)
{
	if (left->types == NULL || right->types == NULL)
		phc_TODO ();

	Types* result_types = new Types;
	foreach (string ltype, *left->types)
		foreach (string rtype, *right->types)
		{
			Types* op_result = get_bin_op_type (ltype, rtype, op);
			result_types->insert (op_result->begin (), op_result->end());
		}

	return result_types;
}

Types*
Value_analysis::get_bin_op_type (string ltype, string rtype, string op)
{
	if (not Type_info::get_all_scalar_types ()->has (ltype) || not Type_info::get_all_scalar_types()->has (rtype))
		phc_TODO ();

	Set<string> always_bool_ops;
	always_bool_ops.insert ("<");
	always_bool_ops.insert ("<=");
	always_bool_ops.insert ("==");
	always_bool_ops.insert (">");
	if (always_bool_ops.has (op))
		return new Types ("bool");

	// TODO: implicit __toString on both params
	if (op == ".")
		return new Types ("string");
	else if (op == "*")
	{
		if (ltype == "real" || rtype == "real")
			return new Types ("real");

		return new Types ("int", "real");
	}
	else if (op == "/")
	{
		if (ltype == "real" || rtype == "real")
			return new Types ("real", "bool"); // FALSE for divide by zero

		// PHP division is not modulo arithmetic
		if (ltype == "int" && rtype == "int")
			return new Types ("int", "bool", "real"); // FALSE for divide by zero

		// Other scalars are possible
		phc_TODO ();
	}
	else if (op == "/")
	{
		return new Types ("int", "bool"); // FALSE for divide by zero
	}
	else if (op == "%")
	{
		if (ltype == "real" || rtype == "real")
			return new Types ("real", "bool"); // FALSE for divide by zero

		// PHP division is not modulo arithmetic
		if (ltype == "int" && rtype == "int")
			return new Types ("int", "bool", "real"); // FALSE for divide by zero

		// Other scalars are possible
		phc_TODO ();
	}
	else if (op == "+")
	{
		if (ltype == "array" && rtype == "array")
			phc_TODO ();

		if (ltype == "real" || rtype == "real")
			return new Types ("real");

		// ints can overflow.
		// Strings, bools and NULLs coerce to ints
		return new Types ("int", "real"); // possible overflow
	}
	else if (op == "-")
	{
		if (ltype == "real" || rtype == "real")
			return new Types ("real");

		// ints can overflow.
		// Strings, bools and NULLs coerce to ints
		return new Types ("int", "real"); // possible overflow
	}

	phc_TODO ();

//	Map<string, Map <string, Map<string, Types > > > type_map;
//	type_map ["+"]["int"]["int"] = Types ("int");
//	type_map ["<"]["int"]["int"] = Types ("bool");
}

Types*
Value_analysis::get_unary_op_types (Context cx, Abstract_value* operand, string op)
{
	Set<string> always_bool_ops;
	always_bool_ops.insert ("!");
	if (always_bool_ops.has (op))
		return new Types ("bool");

	if (op == "-")
		return operand->types;

	DEBUG ("unary op: " << op << " not handled");
	phc_TODO ();
}



/*
 * Lattice_cell interface
 */

Absval_cell* Absval_cell::TOP = new Absval_cell (new Abstract_value (new NIL));

Absval_cell::Absval_cell (Abstract_value* value)
: value (value)
{
}

void
Absval_cell::dump (std::ostream& os)
{
	value->dump (os);
}

bool
Absval_cell::equals (Absval_cell* other)
{
	return value->equals (other->value);
}

Absval_cell*
Absval_cell::meet (Absval_cell* other)
{
	// There is a trick here, that TOP has a value, but it also represents TOP,
	// so that meet() works as expected. So the Abstract_value for NIL is the
	// same as TOP, but TOP will meet with another value X and go to X, which
	// the other NIL Absval will go to BOTTOM.

	// This is a little confusing, since we kind-of have two levels of lattice.
	// As well as the Absval_cell, Abstract_value has NULL values for BOTTOM.

	if (this == TOP)
		return other;

	if (other == TOP)
		return this;

	if (this->value->lit && other->value->lit && this->value->lit->equals (other->value->lit))
		return new Absval_cell (new Abstract_value (this->value->lit));

	if (this->value->types && other->value->types)
		return new Absval_cell (new Abstract_value (this->value->types->set_union (other->value->types)));

	return new Absval_cell (Abstract_value::unknown ());
}

Absval_cell*
Absval_cell::get_default ()
{
	return TOP;
}



