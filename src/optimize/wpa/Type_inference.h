/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#ifndef PHC_TYPE_INFERENCE
#define PHC_TYPE_INFERENCE

#include "WPA_lattice.h"

class Type_cell : public Lattice_cell
{
public:
	Type_cell (string type);
	Type_cell (Types types);
	Type_cell ();
	void dump (std::ostream& os = cdebug);
	bool equals (Lattice_cell* other);

	Lattice_cell* meet (Lattice_cell* other);

	Types types;
};

class Type_inference : public WPA_lattice
{
public:
	Type_inference (Whole_program* wp);

	void set_storage (Context cx, Storage_node* storage, Types types);
	void set_scalar (Context cx, Value_node* storage, Abstract_value* val);
	void pull_possible_null (Context cx, Index_node* node);


	// Fetch results

	Types get_types (Context cx, Alias_name name);

	// HACK - TMI - TODO: i think we can kill this now.
	void set_types (Context cx, Alias_name name, Types types);

	static Types get_bin_op_types (Context cx, Abstract_value* left, Abstract_value* right, string op);
	static Types get_bin_op_type (string left, string right, string op);

	static Types get_unary_op_types (Context cx, Abstract_value* operand, string op);


	static Types get_type (MIR::Literal* lit);
	static Types get_all_scalar_types ();

	// Given a set of types, we want to know which types are scalars, which is
	// an array, and which are objects. These return new sets with only the
	// appropriate types in them.
	// TODO: what about the complete set of types?
	// TODO: all this time I've been ignoring resources!!
	static Types get_scalar_types (Types);
	static Types get_array_types (Types); // can only be "array"
	static Types get_object_types (Types); // anything thats not covered above.
};


#endif // PHC_TYPE_INFERENCE
