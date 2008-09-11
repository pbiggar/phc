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
#include "Def_use.h"
#include "process_ir/debug.h"

using namespace MIR;

void
SCCP::run (CFG* cfg)
{
	// 1. Initialize:
	cfg_wl = new Edge_list(cfg->get_entry_edge ());
	ssa_wl = new SSA_edge_list;

	foreach (Edge* e, *cfg->get_all_edges ())
		e->is_executable = false;

	// TOP is NULL, so the lattice map is already initialized.

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

			if (get_predecessor_executable_count (e->target) == 1)
				visit_block (e->target);

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

			visit_ssa_edge (e);
		}
	}
}

void
SCCP::die ()
{
	lattice.dump ();
	assert (0);
}

int
SCCP::get_predecessor_executable_count (Basic_block* bb)
{
	int exec_count = 0;
	foreach (Edge* pred, *bb->get_predecessor_edges ())
	{
		if (pred->is_executable)
			exec_count++;
	}
	return exec_count;
}

void
SCCP::visit_phi (Phi* phi)
{
	/*	VisitPhi:
	 *	The lattice of the phis output variable is the meet of all the inputs
	 *	(non-execable means TOP), with the meet function:
	 *		any + TOP = any
	 *		any + BOTTOM = BOTTOM
	 *		ci + cj = ci if i == j (? surely if c_i == c_j?)
	 *		c1 + c2 = BOTTOM if i != j (this can be improved with VRP, using a
	 *			similar algorithm).
	 */
	Lattice_cell* result = TOP;

	pair<VARIABLE_NAME*, Edge*> pair;
	foreach (pair, *phi->get_arg_edges ())
	{
		if (pair.second->is_executable)
			; // use TOP, aka do nothing
		else
			result = meet (result, lattice[pair.first]);
	}
	lattice[phi->lhs] = result;
}

/*
 * 4/5.	For SSAWL, pop e. If e.target is a Phi, perform visitPhi (e.target).
 * If e.target is an expression, and any of e.targets incoming edges is
 * executable, run visit_expression.
 *
 *	VisitExpr:
 *	Evaluate the expression.
 *	- If its an assignment and creates a result for the LHS, add all SSA edges
 *	from LHS to SSAWL.
 *	- If its a branch, add:
 *		- all outgoing edges to CFGWL for BOTTOM
 *		- only the appropriate outgoing edge for a constant
 */

void
SCCP::visit_ssa_edge (SSA_edge* edge)
{
	switch (edge->which)
	{
		case SSA_edge::PHI:
			visit_phi (edge->phi);
			break;

		case SSA_edge::BRANCH:
		case SSA_edge::STATEMENT:
			if (get_predecessor_executable_count (edge->bb))
				visit_block (edge->bb);
			break;

		default:
			die ();
	}
}

void
SCCP::visit_branch_block (Branch_block* bb)
{
	/*	- If its a branch, add:
	 *		- all outgoing edges to CFGWL for BOTTOM
	 *		- only the appropriate outgoing edge for a constant
	 */
	if (lattice[bb->branch->variable_name] == BOTTOM)
		cfg_wl->push_back_all (bb->get_successor_edges ());

	else if (lattice[bb->branch->variable_name] == TOP)
		// Not possible, as the previous visit_block will have lowered this.
		die ();

	else
	{
		die (); // TODO
	}
}

/*
 * Statements
 */
void
SCCP::visit_assign_array (Statement_block*, MIR::Assign_array*)
{
	die ();
}

void
SCCP::visit_assign_field (Statement_block*, MIR::Assign_field *)
{
	die ();
}

void
SCCP::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	if (lattice[in->lhs] == BOTTOM)
		return;

	Expr* expr = transform_expr (bb, in->rhs);

	// Update the Lattice
	if (isa<Literal> (expr))
	{
		// If it changes the lattice value,
		//	- add uses of the LHS to the SSA worklist.
		if (lattice[in->lhs] == TOP)
		{
			assert (in->is_ref == false); // TODO
			lattice[in->lhs] = new Lattice_cell (dyc<Literal> (expr));
			foreach (SSA_edge* edge, *bb->cfg->duw->get_def_use_edges (in->lhs))
			{
				ssa_wl->push_back (edge);
			}
		}
		else // must both be CONST - do nothing
			assert (in->rhs->equals (expr));
	}
	else
		lattice[in->lhs] = BOTTOM;

	in->rhs = expr;
}

void
SCCP::visit_assign_var_var (Statement_block*, MIR::Assign_var_var*)
{
	die ();
}

void
SCCP::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	in->expr = transform_expr (bb, in->expr);
	if (! (isa<New> (in->expr) || isa<Method_invocation> (in->expr)))
		die (); // TODO remove
}

void
SCCP::visit_foreach_end (Statement_block*, MIR::Foreach_end*)
{
	die ();
}

void
SCCP::visit_foreach_next (Statement_block*, MIR::Foreach_next*)
{
	die ();
}

void
SCCP::visit_foreach_reset (Statement_block*, MIR::Foreach_reset*)
{
	die ();
}

void
SCCP::visit_global (Statement_block*, MIR::Global*)
{
}

void
SCCP::visit_pre_op (Statement_block*, MIR::Pre_op*)
{
	die ();
}

void
SCCP::visit_push_array (Statement_block*, MIR::Push_array*)
{
	die ();
}

void
SCCP::visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op* in)
{
	if (lattice[in->use] == BOTTOM)
		lattice[in->def] = BOTTOM;

	else if (lattice[in->use] == TOP)
		; // do nothing

	else
	{
		Literal* lit = lattice[in->use]->get_value ();
		die (); // TODO go through embed
		// TODO lower the lattice (same as in assign_var)
	}
}

void
SCCP::visit_return (Statement_block*, MIR::Return*)
{
	die ();
}

void
SCCP::visit_static_declaration (Statement_block*, MIR::Static_declaration*)
{
	die ();
}

void
SCCP::visit_throw (Statement_block*, MIR::Throw*)
{
	die ();
}

void
SCCP::visit_try (Statement_block*, MIR::Try*)
{
	die ();
}

void
SCCP::visit_unset (Statement_block*, MIR::Unset*)
{
	die ();
}

/* Returns NULL, or the literal in VARIABLE_NAME. We have separate functions,
 * because we cant substitute Literals directly into the IR in many cases.*/
Literal*
SCCP::get_literal (Rvalue* in)
{
	if (isa<Literal> (in))
		return dyc<Literal> (in);

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);

	if (lattice[var_name] == TOP || lattice[var_name] == BOTTOM)
		return NULL;

	return lattice[var_name]->get_value ()->clone ();
}


/*
 * Exprs
 */

Expr*
SCCP::transform_array_access (Statement_block*, Array_access* in)
{
	// TODO is this a string, with a known index?

	// Fold index
	if (Literal* lit = get_literal (in->index))
		in->index = lit;

	return in;
}

Expr*
SCCP::transform_bin_op (Statement_block*, Bin_op* in)
{
	Bin_op* bin_op = dyc<Bin_op> (in);

	Literal* left = get_literal (bin_op->left);
	Literal* right = get_literal (bin_op->right);

	if (left) bin_op->left = left;
	if (right) bin_op->right = right;

	if (isa<Literal> (bin_op->left) 
			&& isa<Literal> (bin_op->right))
		die (); // TODO go through embed

	return in;
}

Expr*
SCCP::transform_cast (Statement_block*, Cast* in)
{
	Cast* cast = dyc<Cast> (in);
	Literal* lit = get_literal (cast->variable_name);

	if (lit)
		die (); // go through embed

	return in;
}

Expr*
SCCP::transform_constant (Statement_block*, Constant* in)
{
	// TODO:
	// We'd very much like to know the value of this, however, since these are
	// likely to be deinfed at the top-level, and this optimization won't run
	// at the top-level (until its interprocedural), it won't do much good.
	return in;
}

Expr*
SCCP::transform_field_access (Statement_block*, Field_access* in)
{
	// TODO warning
	// TODO promote name to FIEDL_NAME
	Field_access* fa = dyc<Field_access> (in);

	// This uses a variable field, not a variable expr.
	//			if (isa<Variable_field> (fa->field_name))
	//				use (bb, dyc<Variable_field> (fa->field_name)->variable_name);
	//
	//			if (isa<VARIABLE_NAME> (fa->target))
	//				use (bb, dyc<VARIABLE_NAME> (fa->target));

	die ();
	return in;
}

Expr*
SCCP::transform_instanceof (Statement_block*, Instanceof* in)
{
	die ();
	return in;
}

Expr*
SCCP::transform_isset (Statement_block*, Isset* in)
{
	// fold isset (5) to true;
	if (in->target == NULL
			&& isa<VARIABLE_NAME> (in->variable_name)
			&& in->array_indices->size () == 0
			&& get_literal (dyc<VARIABLE_NAME> (in->variable_name)))
		return new BOOL (true);

	return in;
}

Expr*
SCCP::transform_method_invocation (Statement_block*, Method_invocation* in)
{
	// TODO APC::Optimizer has a list of pure functions. Go through
	// embed for them.

	// ignore for now
	if (isa<METHOD_NAME> (in->method_name))
	{
		METHOD_NAME* name = dyc<METHOD_NAME> (in->method_name);
		if (*name->value == "var_dump"
				|| *name->value == "print")
			return in;
	}

	die ();
	// TODO replace Variable_variable with VARIABLE_NAME, if possible.

	// TODO: we can replace a arguement with its actual parameter
	// (watch out for refs) (only if passing by copy)

	/*			if (isa<VARIABLE_NAME> (mi->method_name))
				die (); // TODO

				foreach (Actual_parameter* ap, *mi->actual_parameters)
				{
				VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (ap->rvalue);
				if (var_name)
				use (bb, var_name);
				}*/
	return in;
}

Expr*
SCCP::transform_new (Statement_block*, New* in)
{
	// TODO turn a varaible_class into a CLASS_NAME 
	die ();
	return in;
}

Expr*
SCCP::transform_param_is_ref (Statement_block*, Param_is_ref* in)
{
	// TODO go through embed.
	die ();
	return in;
}

Expr*
SCCP::transform_unary_op (Statement_block*, Unary_op* in)
{
	if (Literal* lit = get_literal (in->variable_name))
		die (); // go through embed

	return in;
}

Expr*
SCCP::transform_variable_name (Statement_block*, VARIABLE_NAME* in)
{
	if (Literal* lit = get_literal (in))
		return lit;

	return in;
}

Expr*
SCCP::transform_variable_variable (Statement_block*, Variable_variable* in)
{
	if (Literal* lit = get_literal (in->variable_name))
		die ();

	// in = new VARIABLE_NAME (PHP::to_string (lit));
	return in;
}
