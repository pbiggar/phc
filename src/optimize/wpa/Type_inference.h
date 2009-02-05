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
};

class Type_inference : public WPA, public MIR::Visitor
{
public:
	Type_inference (Whole_program* wp);


	void forward_bind (CFG* caller_cfg, CFG* callee_cfg,
							 MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs);

	void backward_bind (CFG* caller_cfg, CFG* callee_cfg);

	void dump (Basic_block* bb);

private:
	BB_lattices ins;
	BB_lattices locals;
	BB_lattices outs;
};


#endif // PHC_TYPE_INFERENCE
