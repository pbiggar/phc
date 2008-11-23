#ifndef PHC_SPARSE_CONDITIONAL_VISITOR_H_
#define PHC_SPARSE_CONDITIONAL_VISITOR_H_

#include "CFG.h"
#include "CFG_visitor.h"
#include "Edge.h"
#include "Def_use.h"


class Sparse_conditional_visitor : public CFG_visitor
{
	Edge_list* cfg_wl;
public:
	// TODO: move the lattice to this class, then remove the public, and stop SCCP having access to ssa_wl.
	SSA_op_list* ssa_wl;

public:
	void run (CFG* cfg);
	virtual void initialize (CFG*) = 0;
	virtual void post_pass (CFG*) = 0;

	int get_predecessor_executable_count (Basic_block* bb);

	// High-level SSA properties
	void visit_branch_block (Branch_block*);
	virtual Edge_list* get_branch_successors (Branch_block*) = 0;
};


#endif // PHC_SPARSE_CONDITIONAL_VISITOR_H
