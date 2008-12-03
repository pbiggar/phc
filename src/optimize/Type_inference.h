#ifndef PHC_TYPE_INFERENCE_H_
#define PHC_TYPE_INFERENCE_H_

#include "Sparse_conditional_visitor.h"

// TODO: we should be able to represent sum types, weak-typing, and
// inheritence hierachies in this model.
class Type_cell : public Lattice_cell
{
public:
	Type_cell (String* type_name);

	void dump ();
	bool equals (Lattice_cell* other);

	String* type_name;
};

class Type_inference : public Sparse_conditional_visitor
{
public:
	void initialize (CFG*);
	void post_pass (CFG*);

	// High-level SSA properties
	void visit_chi_node (Basic_block* bb, MIR::VARIABLE_NAME* lhs, MIR::VARIABLE_NAME* rhs);
	void visit_phi_node (Basic_block* bb, MIR::VARIABLE_NAME* lhs); 
	Edge_list* get_branch_successors (Branch_block*);

	// Expressions (in SCCP terminology)
	void visit_entry_block (Entry_block* bb);
};


#endif // PHC_TYPE_INFERENCE_H
