/*
 * Cooper/Torczon Section 10.3.3 describes SCCP, which is weaker than SCCP.
 * Muchnick 12.6 describes SCCP, but does a very poor job of it. The original
 * paper, "Constant propagation with Conditional Branches", by Wegman and
 * Zadeck, is quite readable. I'll summarize:
 *		
 *		Simple Constant Propagation, by Kildall, propagates constants.
 *
 *		Sparse Simple Constant Propagation, by Reif and Lewis, repeats this
 *		using SSA, getting faster optimizations, but the same results.
 *
 *		Conditional Constant Propagation, by Wegbreit, additionally evaluates
 *		constant expressions, and only proceeds down flow control edges which
 *		are known to be executable. This is faster (doesnt waste time
 *		processing unreachable code), but importantly gets better results (see
 *		later).
 *
 *		Sparse Conditional Constant Propagation, does to CCP what SCCP does to
 *		SCP, reformulating it with SSA.
 *
 *		The algorithm iterates through the SSA graph, following SSA-edges (SSA
 *		def-use chains) and CFG edges. When it comes to a phi node, it
 *		evaluates it, assuming that TOP is never executed. After seeing a
 *		constant defintion, it adds the use of this def to the SSA worklist.
 *		After processing a basic block, it adds the successors to the CFG
 *		worklist, but only if they havent been executed. It ensures termination
 *		through a monotonic lattice: TOP->constant->BOTTOM.
 *
 *		Sect 5.1: The important difference between the first two and second two
 *		is that SC is _pessimistic_, which CC is _optimistic_.  So SC expects
 *		all the argument to the PHI node to be available before it thinks it
 *		can evaluate it. CC knows that some edges aren't executable, and can
 *		evaluate a "partial" phi node.
 *
 *		Sect 5.2: Using def-use chains is worse than SSA edges, since the chain
 *		may go through an unreachable region.
 *
 *		VRP uses pretty much the same algorithm. In fact, it subsumes constant-
 *		and copy-propagation, as explained in Section 6 of "Accurate Static
 *		Branch Prediction by Value Range Propagation", by Jason Patterson.
 *
 *		I believe there is a type-inference algorithm with the same algorithm.
 *		TODO find it:
 *
 *		TODO: GCC has a similar approach, abstracting the algorithm for other
 *		uses. Cite it.
 *
 *		TODO: Section 6 expands it to inter-procedural, including alias
 *		information. Incorporate.
 *			
 *
 *		Algorithm: (Section 3.4)
 *
 *		CFG-worklist contains CFG edges.
 *		SSA-worklist contains SSA edges, an edge between a defining statement
 *		and the use of that statement (def-use web for SSA).
 *
 *		1. Initialize:
 *			CFG-Worklist: { entry->B1 }
 *			SSA-Worklist: {}
 *			ExecFlag (e) = false, for all CFG edges e
 *			LatticeCell (v) = TOP, for all variables v
 *
 *		2. Stop when CFG-worklist and SSA-worklist are both empty.
 *
 *		Take workitem from either list.
 *
 *		3.  For CFGWL, pop e. If ExecFlag(e) == true, do nothing. Else:
 *				- ExecFlag(e) = true;
 *				- visitPhi (p) for all phis in e.target.
 *				- if this is the first time the stmt is evaluated 
 *					(ie. if count (execflags(e1), where e1.target = e.target) == 1)
 *				  then visitExpr (e.target)
 *				- If e.target has 1 outgoing edge, add it to CFGWL
 *
 *		4/5.	For SSAWL, pop e. If e.target is a Phi, perform visitPhi
 *		(e.target).
 *			If e.target is an expression, and any of e.targets incoming edges is
 *			executable, run visit_expression. Else do nothing.
 *
 *		The lattice is TOP -> literals -> BOTTOM, where bottom is Not contant,
 *		and TOP is unitialised. 
 *
 *		VisitPhi:
 *		The lattice of the phis output variable is the meet of all the inputs
 *		(non-execable means TOP), with the meet function:
 *			any + TOP = any
 *			any + BOTTOM = BOTTOM
 *			ci + cj = ci if i == j (? surely if c_i == c_j?)
 *			c1 + c2 = BOTTOM if i != j (this can be improved with VRP, using a similar algorithm).
 *
 *		VisitExpr:
 *			Evaluate the expression.
 *				- If its an assignment and creates a result for the LHS, add all
 *				SSA edges from LHS to SSAWL.
 *				- If its a branch, add:
 *					- all outgoing edges to CFGWL for BOTTOM
 *					- only the appropriate outgoing edge for a constant
 *		
 *
 *
 *		At the end of the execution, check that all latticeCells are c or
 *		bottom, or non-executable.
 */

#include "SCCP.h"
#include "Lattice.h"
using namespace MIR;

SCCP::SCCP (CFG* cfg)
{
}

void
SCCP::execute ()
{

	// 1. Initialize:
	Edge_list* cfg_wl = new Edge_list(cfg->get_entry_edge ());
	SSA_edge_list* ssa_wl = new SSA_edge_list;

	foreach (Edge* e, *cfg->get_all_edges ())
	{
		e->is_executable = false;
	}
	cfg->get_entry_edge()->is_executable = true;

	foreach (VARIABLE_NAME* var, *cfg->get_all_variables ())
	{
		lattice [var] = TOP;
	}

	// 2. Stop when CFG-worklist and SSA-worklist are both empty.
	while (cfg_wl->size () > 0 || ssa_wl->size () > 0)
	{
		// Take workitem from either list.

		/* 3.
		 * For CFGWL, pop e. If ExecFlag(e) == true, do nothing. Else:
		 *	- ExecFlag(e) = true;
		 *	- visitPhi (p) for all phis in e.target.
		 *	- if this is the first time the stmt is evaluated 
		 *		(ie. if count (execflags(e1), where e1.target = e.target) == 1)
		 *	  then visitExpr (e.target)
		 *		- If e.target has 1 outgoing edge, add it to CFGW BB
		 */

		while (cfg_wl->size() > 0)
		{
			Edge* e = cfg_wl->front();
			cfg_wl->pop_front ();

			if (e->is_executable)
				continue;

			e->is_executable = true;

			foreach (Phi* phi, *e->target->get_phi_nodes ())
				visit_phi (phi);

			// Is this the first time the stmt is evaluated?
			int exec_count = 0;
			foreach (Edge* pred, *e->target->get_predecessor_edges ())
			{
				if (pred->is_executable)
					exec_count++;
			}
			// This will include the current edge. so the count will always
			// be > 1
			assert (exec_count > 0);

			if (exec_count > 1)
			{
				assert (0); // TODO
//				visit_expr (e->target);
			}

			Edge_list* succs = e->target->get_successor_edges ();
			if (succs->size() == 1)
				cfg_wl->push_back (succs->front ());
		}

		while (ssa_wl->size() > 0)
		{
			/*
			 * 4/5.
			 * For SSAWL, pop e.
			 * - If e.target is a Phi, perform visitPhi (e.target).
			 *	- If e.target is an expression, and any of e.targets incoming
			 *	  edges is executable, run visit_expression. Else do nothing.
			 */
			SSA_edge* e = ssa_wl->front ();
			ssa_wl->pop_front ();

			assert (0); // TODO
//			if (isa<Phi> (e->target))
//				visit_phi (e->target);
//			else if (isa<Expr> (e->target))
//				visit_expr (e->target);
//			else
//				;
		}
	}
}

void
SCCP::visit_phi (Phi* phi)
{
	Lattice_cell result = TOP;
	foreach (VARIABLE_NAME* var, *phi->args)
	{
		result = meet (result, lattice[var]);
	}
	lattice[phi->lhs] = result;
	/*		VisitPhi:
	 *		The lattice of the phis output variable is the meet of all the inputs
	 *		(non-execable means TOP), with the meet function:
	 *			any + TOP = any
	 *			any + BOTTOM = BOTTOM
	 *			ci + cj = ci if i == j (? surely if c_i == c_j?)
	 *			c1 + c2 = BOTTOM if i != j (this can be improved with VRP, using a similar algorithm).
	 */
}

/*	VisitExpr:
 *	Evaluate the expression.
 *		- If its an assignment and creates a result for the LHS, add all SSA
 *		edges from LHS to SSAWL.
 *		- If its a branch, add:
 *			- all outgoing edges to CFGWL for BOTTOM
 *			- only the appropriate outgoing edge for a constant
 */
void
SCCP::visit_statement (Statement* in)
{
	// TODO const folding
	assert (0);
}

void
SCCP::visit_branch (Branch* in)
{
	// TODO const folding
	assert (0);
}

