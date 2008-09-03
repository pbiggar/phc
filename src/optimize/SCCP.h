/*
 * Cooper/Torczon Section 10.3.3 describes SSCP, which is weaker than SCCP.
 * Muchnick 12.6 describes SCCP, but does a very poor job of it. The original
 * paper, "Constant propagation with Conditional Branches", by Wegman and
 * Zadeck, is quite readable. I'll summarize:
 *		
 *		Simple Constant Propagation, by Kildall, propagates constants.
 *
 *		Sparse Simple Constant Propagation, by Reif and Lewis, repeats this using
 *		SSA, getting faster optimizations, but the same results.
 *
 *		Conditional Constant Propagation, by Wegbreit, additionally evaluates
 *		constant expressions, and only proceeds down flow control edges which are
 *		known to be executable. This is faster (doesnt waste time processing
 *		unreachable code), but importantly gets better results (see later).
 *
 *		Sparse Conditional Constant Propagation, does to CCP what SSCP does to
 *		SCP, reformulates it with SSA.
 *
 *		Sect 5.1: The important difference between the first two and second two is
 *		that SC is _pessimistic_, which CC is _optimistic_.  So SC expects all
 *		the argument to the PHI node to be available before it thinks it can
 *		evaluate it. CC knows that some edges aren't executable, and can evaluate
 *		a "partial" phi node.
 *
 *
 *		Sect 5.2: using def-use chains is worse than SSA edges, since the chain
 *		may go through an unreachable region. Doesnt affect us, since we dont even have Def-use chains.
 *
 *		TODO: describe algorithm
 *		TODO: can be used for type inference, or VRP?
 *		TODO: GCC has a similar approach, abstracting the algorithm for other uses. Cite it.
 *		TODO read sections 6 and 7.
 *
 *		Algorithm: (Section 3.4)
 *
 *		CFG-worklist contains CFG edges.
 *		SSA-worklist contains SSA edges, an edge between a defining statement and
 *		the use of that statement (def-use web for SSA).
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
 *		3.  For CFGWL, pop e. If ExecFlag(e) == false, do nothing. Else:
 *				- ExecFlag(e) = true;
 *				- visitPhi (p) for all phis in e.target.
 *				- if this is the first time the stmt is evaluated 
 *					(ie. if count (execflags(e1), where e1.target = e.target) == 1)
 *				  then visitExpr (e.target)
 *				- If e.target has 1 outgoing edge, add it to CFGWL
 *
 *		4/5.	For SSAWL, pop e. If e.target is a Phi, perform visitPhi (e.target).
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
 *		At the end of the execution, check that all latticeCells are c or bottom,
 *		or non-executable.
 *
 *
 *
 *
 *
 *
 *
 *
 */
