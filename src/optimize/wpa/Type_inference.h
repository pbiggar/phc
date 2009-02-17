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
	void dump ();
	bool equals (Lattice_cell* other);

	Lattice_cell* meet (Lattice_cell* other);

	Types types;
};

class Type_inference : public WPA_lattice
{
public:
	Type_inference (Whole_program* wp);

	void assign_value (Basic_block* bb, Alias_name name,
						    Abstract_value* val, Alias_name* source,
							 certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);

	Types get_types (Basic_block* bb, Alias_name name);

	Types get_bin_op_types (Basic_block* bb, Alias_name* left, Alias_name* right, MIR::Literal* left_lit, MIR::Literal* right_lit, string op);
	Types get_unary_op_types (Basic_block* bb, Alias_name* operand, string op);


	static string get_literal_type (MIR::Literal* lit);
	static Types get_bin_op_type (string left, string right, string op);

};


#endif // PHC_TYPE_INFERENCE
