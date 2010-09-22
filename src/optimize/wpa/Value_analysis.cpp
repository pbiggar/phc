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
#include "process_ir/IR.h"

using namespace std;
using namespace boost;
using namespace MIR;

Value_analysis::Value_analysis (Whole_program* wp)
: WPA_lattice<const Alias_name*, const Absval_cell> (wp)
{
}


const Alias_name*
Value_analysis::context_merge_key (const Alias_name* name) const
{
	return name->convert_context_name ();
}


/*
 * WPA interface
 */


void
Value_analysis::set_storage (Context* cx, const Storage_node* storage, const Types* types)
{
	Lattice_type& lat = working[cx];

	lat[storage] = lat[storage]->meet (new Absval_cell (new Abstract_value (types)));
}

void
Value_analysis::set_scalar (Context* cx, const Value_node* storage, const Abstract_value* val)
{
	Lattice_type& lat = working[cx];

	lat[storage] = lat[storage]->meet (new Absval_cell (val));
}

void
Value_analysis::pull_possible_null (Context* cx, const Index_node* index)
{
	Lattice_type& lat = ins[cx];

	lat[index] = lat[index]->meet (new Absval_cell (new Abstract_value (new NIL)));

	// WPA_lattice::assign_value copies the SCLVAL to the index_node in the
	// general case. However, we need to do it ourselves here.
	const Value_node* scalar_name = SCLVAL (index);
	lat[scalar_name] = lat[scalar_name]->meet (new Absval_cell (new Abstract_value (new NIL)));
}

const Absval_cell*
Value_analysis::get_value (Context* cx, Result_state state, const Alias_name* name) const
{
	return lattices[state][cx][name];
}

void
Value_analysis::kill_value (Context* cx, const Index_node* lhs, bool also_kill_refs)
{
	Lattice_type& lat = working[cx];
	lat.erase (lhs);
	lat.erase (SCLVAL (lhs));
}


void
Value_analysis::remove_fake_node (Context* cx, const Index_node* fake)
{
	this->kill_value (cx, fake, false /* dont care */);
}

void
Value_analysis::assign_value (Context* cx, const Index_node* lhs, const Storage_node* storage)
{
	Lattice_type& lat = working[cx];

	lat[lhs] = lat[lhs]->meet (lat[storage]);
}




/*
 * Literals
 */

const MIR::Literal*
Value_analysis::get_lit (Context* cx, Result_state state, const Alias_name* name) const
{
	return get_value (cx, state, name)->value->lit;
}

/*
 * Types
 */

void
Value_analysis::remove_non_objects (Context* cx, Result_state state, const Index_node* index)
{
	// Remove the object types (we assume there are already object types)
	const Abstract_value* val = get_value (cx, state, index)->value;
	val = new Abstract_value (Type_info::get_object_types (val->types));

	// Set it back
	Lattice_type& lat = lattices[state][cx];
	lat[index] = new Absval_cell (val);
}

const Types*
Value_analysis::get_types (Context* cx, Result_state state, const Alias_name* name) const
{
	const Types* types = get_value (cx, state, name)->value->types;
	assert (types->size ());
	return types;
}



Types*
Value_analysis::get_bin_op_types (Context* cx, const Abstract_value* left, const Abstract_value* right, string op)
{
	if (left->types == NULL || right->types == NULL)
    phc_optimization_exception ("Optimization of binary operations with no abstract values unsupported");

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
	Set<string> always_bool_ops;
	always_bool_ops.insert ("<");
	always_bool_ops.insert (">");
	always_bool_ops.insert ("<=");
	always_bool_ops.insert (">=");
	always_bool_ops.insert ("==");
	always_bool_ops.insert ("!=");
	always_bool_ops.insert ("===");
	always_bool_ops.insert ("!==");
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
		return new Types ("int", "bool", "real"); // FALSE for divide by zero
	}
	else if (op == "%")
	{
		return new Types ("int", "bool"); // FALSE for divide by zero
	}
	else if (op == "/")
	{
		if (ltype == "real" || rtype == "real")
			return new Types ("real", "bool"); // FALSE for divide by zero

		// PHP division is not modulo arithmetic
		if (ltype == "int" && rtype == "int")
			return new Types ("int", "bool", "real"); // FALSE for divide by zero

		// Other scalars are possible
    phc_optimization_exception ("Optimization of weird types of division unsupported");
	}
	else if (op == "+")
	{
		// If its just one array, thats a run-time error, so we can ignore what
		// happens here.
		if (ltype == "array" && rtype == "array")
      phc_optimization_exception ("Optimization of array concatenation unsupported");

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
	else if (op == "&" || op == "|" || op == "^")
	{
		// bitwise operations will do something string-y if they are both strings.
		if (ltype == "string" || rtype == "string")
			return new Types ("string");

		// Reals get converted to integers first
		return new Types ("int");
	}
	else if (op == "<<" || op == ">>")
	{
		// These always get integers (they even overflow)
		return new Types ("int");
	}


	stringstream ss;
  ss << "Optimization of a " << left << " " << op << " a " << right << "unsupported " << endl;
  phc_optimization_exception (ss.str());
  return NULL; // silence warning

//	Map<string, Map <string, Map<string, Types > > > type_map;
//	type_map ["+"]["int"]["int"] = Types ("int");
//	type_map ["<"]["int"]["int"] = Types ("bool");
}

Types*
Value_analysis::get_unary_op_types (Context* cx, const Abstract_value* operand, string op)
{
	Set<string> always_bool_ops;
	always_bool_ops.insert ("!");
	if (always_bool_ops.has (op))
		return new Types ("bool");

	if (op == "-" || op == "~")
		return operand->types->clone ();

	stringstream ss;
  ss << "Optimization of unary op '" << op << "' not supported";
  phc_optimization_exception (ss.str());
  return NULL; // silence warning
}



/*
 * Lattice_cell interface
 */

const Absval_cell* Absval_cell::TOP = new Absval_cell (new Abstract_value (new NIL));

Absval_cell::Absval_cell (const Abstract_value* value, bool case_insensitive)
: value (value),
  case_insensitive (case_insensitive)
{
}

void
Absval_cell::dump (std::ostream& os) const
{
	value->dump (os);
}

bool
Absval_cell::equals (const Absval_cell* other) const
{
	return value->equals (other->value);
}

const Absval_cell*
Absval_cell::meet (const Absval_cell* other) const
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

	if (	this->value->lit
		&& other->value->lit
		&& ::equals (this->value->lit, other->value->lit))
		return new Absval_cell (new Abstract_value (this->value->lit), this->case_insensitive);

	if (this->value->types && other->value->types)
		return new Absval_cell (
			new Abstract_value (
				this->value->types->set_union (other->value->types)));

	return new Absval_cell (Abstract_value::unknown ());
}

const Absval_cell*
Absval_cell::get_default ()
{
	return TOP;
}



