/*
 * The propagation algorithm from SCCP.
 */

#ifndef PHC_SPARSE_CONDITIONAL_VISITOR_H_
#define PHC_SPARSE_CONDITIONAL_VISITOR_H_

#include "CFG.h"
#include "CFG_visitor.h"
#include "Edge.h"
#include "Def_use_web.h"
#include "Lattice.h"
#include "process_ir/debug.h"

class Sparse_conditional_visitor : public CFG_visitor
{
	Edge_list* cfg_wl;
	SSA_op_list* ssa_wl;

protected:
	SSA_map lattice;

public:
	virtual void post_pass (CFG*) = 0;
	virtual Edge_list* get_branch_successors (Branch_block*) = 0;

public:
	void run (CFG* cfg);

	void set_lattice (MIR::VARIABLE_NAME* var, Lattice_cell* value);

	// Combine the lattice value for VAR_NAME with VALUE, and set the new value for VAR_NAME.
	void meet_lattice (MIR::VARIABLE_NAME* var, Lattice_cell* value);


	int get_predecessor_executable_count (Basic_block* bb);

	// High-level SSA properties
	void visit_branch_block (Branch_block*);
};



#endif // PHC_SPARSE_CONDITIONAL_VISITOR_H
