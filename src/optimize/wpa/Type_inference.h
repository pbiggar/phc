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
	Type_cell ();
	void dump ();
	bool equals (Lattice_cell* other);

	Lattice_cell* meet (Lattice_cell* other);

	Set<string> types;
};

class Type_inference : public WPA_lattice
{
public:
	Type_inference (Whole_program* wp);

	void assign_unknown_typed (Basic_block* bb, Alias_name name,
									  string type, certainty cert);
	
	void assign_scalar (Basic_block* bb, Alias_name lhs,
										 MIR::Literal* rhs, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);
};


#endif // PHC_TYPE_INFERENCE
