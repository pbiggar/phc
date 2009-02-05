/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#ifndef PHC_TYPE_INFERENCE
#define PHC_TYPE_INFERENCE

#include "WPA.h"
#include "optimize/Lattice.h"

class Type_cell : public Lattice_cell
{
public:
	Type_cell (string type);
	void dump ();
	bool equals (Lattice_cell* other);

	Lattice_cell* meet (Lattice_cell* other);

	Set<string> types;
};

class Type_inference : public WPA, public MIR::Visitor
{
public:
	Type_inference (Whole_program* wp);


	void forward_bind (CFG* caller_cfg, CFG* callee_cfg,
							 MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs);

	void backward_bind (CFG* caller_cfg, CFG* callee_cfg);

	void assign_unknown (Basic_block* bb, Alias_name name,
							  certainty cert);

	void assign_unknown_typed (Basic_block* bb, Alias_name name,
									  string type, certainty cert);
	
	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									string unique_name, certainty cert);

	void assign_scalar (Basic_block* bb, Alias_name lhs,
										 MIR::Literal* rhs, certainty cert);

	void assign_value (Basic_block* bb, Alias_name lhs,
										 Alias_name rhs, certainty cert);

	void kill_value (Basic_block* bb, Alias_name name);


	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);




	void dump (Basic_block* bb);

private:
	BB_lattices ins;
	BB_lattices locals;
	BB_lattices outs;
};


#endif // PHC_TYPE_INFERENCE
