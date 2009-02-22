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

	void assign_scalar (Basic_block* bb, Alias_name lhs,
						  Alias_name lhs_storage, Abstract_value* val, certainty cert);

	void assign_storage (Basic_block* bb, Alias_name lhs,
						  Alias_name storage, certainty cert);


	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);

	Types get_types (Basic_block* bb, Alias_name name);

	static Types get_bin_op_types (Basic_block* bb, Abstract_value* left, Abstract_value* right, string op);
	static Types get_bin_op_type (string left, string right, string op);

	static Types get_unary_op_types (Basic_block* bb, Abstract_value* operand, string op);


	static Types get_type (MIR::Literal* lit);

	// Given a set of types, we want to know which types are scalars, which is
	// an array, and which are objects. These return new sets with only the
	// appropriate types in them.
	// TODO: what about the complete set of types?
	// TODO: all this time I've been ignoring resources!!
	static Types get_scalar_types (Types);
	static Types get_array_types (Types); // can only be "array"
	static Types get_object_types (Types); // anything thats not covered above.

private:
	static Map<int, string> MIR_types;
	static Types scalar_types;

};


#endif // PHC_TYPE_INFERENCE
