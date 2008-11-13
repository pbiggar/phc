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
 *
 *
 *		The propagation must not update the IR. Instead, it should just propagate
 *		lattice cells. At the end of the analysis, it is appropriate to replace
 *		variables with their constants. For example:
 *
 *		L0:
 *		x0 = 5;
 *		x2 = PHI (x0, x1)
 *		z = x2 + 5;
 *		x1 = 7;
 *		...
 *		goto L0;
 *
 *		Although we can propagate 10 into z, we cannot replace z's assignment
 *		with z = 10. If we do, then when x2 becomes BOTTOM, on the second loop
 *		iteration, we'll already have the wrong result in z.
 */

#include "SCCP.h"
#include "Lattice.h"
#include "embed/embed.h"
#include "Def_use.h"
#include "process_ir/debug.h"

using namespace MIR;

void
SCCP::run (CFG* cfg)
{
	this->cfg = cfg;
	cfg->consistency_check ();
	lattice.clear ();

	// 1. Initialize:
	cfg_wl = new Edge_list(cfg->get_entry_edge ());
	ssa_wl = new SSA_op_list;

	foreach (Edge* e, *cfg->get_all_edges ())
		e->is_executable = false;

	// TOP is NULL, so the lattice map is already initialized.

	// Start in the entry block
	visit_entry_block (cfg->get_entry_bb ());

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

			foreach (VARIABLE_NAME* phi_lhs, *e->get_target ()->get_phi_lhss ())
				visit_phi (e->get_target (), phi_lhs);

			if (get_predecessor_executable_count (e->get_target()) == 1)
				visit_block (e->get_target ());

			Edge_list* succs = e->get_target ()->get_successor_edges ();
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
			SSA_op* e = ssa_wl->front ();
			ssa_wl->pop_front ();

			visit_ssa_op (e);
		}
	}

	if (debugging_enabled)
		lattice.dump();

	// The algorithm so far has found the answers. We now need to update the
	// results.
	update_ir (cfg);
}

#define die() do { lattice.dump(); assert (0); } while (0)

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
SCCP::visit_phi (Basic_block* bb, VARIABLE_NAME* phi_lhs)
{
	Lattice_cell* old = lattice[phi_lhs];

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
	foreach (Edge* pred, *bb->get_predecessor_edges ())
	{
		if (!pred->is_executable)
			; // use TOP, aka do nothing
		else
		{
			Rvalue* arg = bb->get_phi_arg_for_edge (pred, phi_lhs);
			if (isa<Literal> (arg))
				result = ::meet (result, dyc<Literal> (arg));
			else
				result = ::meet (result, lattice[dyc<VARIABLE_NAME> (arg)]);
		}
	}
	lattice[phi_lhs] = result;

	// Although the algorithm doesnt explicitly state this, surely this is an
	// assignment.
	check_changed_definition (old, phi_lhs); // (BB is only used to get the DUW*)
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
SCCP::visit_ssa_op (SSA_op* op)
{
	if (SSA_phi* phi = dynamic_cast<SSA_phi*> (op))
	{
		visit_phi (phi->bb, phi->phi_lhs);
	}
	else
	{
		assert (!isa<SSA_formal> (op));

		// Branches and statements
		Basic_block* bb = op->get_bb ();
		if (get_predecessor_executable_count (bb))
			visit_block (bb);
	}
}

// Initialize all parameters to BOTTOM.
void
SCCP::visit_entry_block (Entry_block* bb)
{
	foreach (VARIABLE_NAME* var_name, *bb->get_defs (SSA_FORMAL))
	{
		lattice[var_name] = BOTTOM;
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
		assert (0);

	else
	{
		if (PHP::is_true (get_literal (bb->branch->variable_name)))
			cfg_wl->push_back (bb->get_true_successor_edge ());
		else
			cfg_wl->push_back (bb->get_false_successor_edge ());
	}
}

/*
 * Statements
 */

void
SCCP::visit_assign_field (Statement_block*, MIR::Assign_field *)
{
	die ();
}

// In the paper, this is VisitExpression.
void
SCCP::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	if (lattice[in->lhs] == BOTTOM)
		return;

	Expr* expr = transform_expr (bb, in->rhs->clone ());

	// Dont transform the assignment, just the expression.
	// TODO: I'm sure we can optimize here.
	if (in->is_ref)
	{
		lattice[in->lhs] = BOTTOM;
		return;
	}

	Lattice_cell* old = lattice[in->lhs];


	// If it changes the lattice value,
	if (isa<Literal> (expr) && old == TOP)
		lattice[in->lhs] = new Lattice_cell (dyc<Literal> (expr));
	else if (!isa<Literal> (expr))
		lattice[in->lhs] = BOTTOM;


	check_changed_definition (old, in->lhs);
}

void
SCCP::check_changed_definition (Lattice_cell* old_value, VARIABLE_NAME* def)
{
	if (lattice[def] != old_value)
	{
		foreach (SSA_op* edge, *cfg->duw->get_uses (def, SSA_ALL))
		{
			//	1. add uses of the LHS to the SSA worklist.
			ssa_wl->push_back (edge);

			// 2. If the expression controls a conditional branch, .... However,
			// conditions never control branches - that's always a VARIABLE_NAME.
			// The new value for that variable will propagate through 1.
		}
	}
}

void
SCCP::visit_assign_var_var (Statement_block*, MIR::Assign_var_var*)
{
	die ();
}

void
SCCP::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr->clone ());
}

void
SCCP::visit_foreach_end (Statement_block*, MIR::Foreach_end*)
{
	// No constants to be folded for any foreach.
}

void
SCCP::visit_foreach_next (Statement_block*, MIR::Foreach_next*)
{
}

void
SCCP::visit_foreach_reset (Statement_block*, MIR::Foreach_reset*)
{
}

void
SCCP::visit_pre_op (Statement_block*, MIR::Pre_op*)
{
	die ();
}

void
SCCP::visit_assign_next (Statement_block*, MIR::Assign_next*)
{
	die ();
}

void
SCCP::visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
{
	Lattice_cell* old = lattice[in->def];

	if (lattice[in->use] == BOTTOM)
		lattice[in->def] = BOTTOM;

	else if (lattice[in->use] == TOP)
		assert (lattice[in->def] == TOP); // do nothing

	else
	{
		Literal* lit = get_literal (in->use);
		Literal* result = PHP::fold_pre_op (lit, in->op);

		if (result)
			meet (in->def, result);
	}

	// TODO: this could get duplicated a lot. The simplest way to avoid that is
	// to move to iterarating over SSA_operations in a node, instead of
	// painstakingly checking each place that can be a def.
	
	check_changed_definition (old, in->def);
}

void
SCCP::visit_static_declaration (Statement_block*, MIR::Static_declaration*)
{
	die ();
}

void
SCCP::visit_try (Statement_block*, MIR::Try*)
{
	die ();
}

void
SCCP::visit_unset (Statement_block*, MIR::Unset* in)
{
	assert (in->target == NULL);
	assert (in->array_indices->size () == 0);
	assert (isa<VARIABLE_NAME> (in->variable_name));

	// Def_use asserts what we cant handle, for now.
	meet (dyc<VARIABLE_NAME> (in->variable_name), new NIL ());
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

void
SCCP::meet (VARIABLE_NAME* var_name, Literal* lit)
{
	meet (var_name, new Lattice_cell (lit));
}

void
SCCP::meet (VARIABLE_NAME* var_name, Lattice_cell* lat)
{
	lattice[var_name] = ::meet (lattice[var_name], lat);
}


/*
 * Exprs
 *		To avoid code duplication, we use the same visit_expr. In the initial
 *		analysis, we pass a clone, so that destructive updates are OK.
 */

Expr*
SCCP::transform_array_access (Statement_block*, Array_access* in)
{
	Literal* index = 0;

	// Fold index
	if (Literal* index = get_literal (in->index))
		in->index = index;

	// Is this a string, with a known index.
	Literal* array = get_literal (in->variable_name);
	if (array && index)
		die ();
//		return fold_string_index (array, literal);

	return in;
}

Expr*
SCCP::transform_bin_op (Statement_block*, Bin_op* in)
{
	Literal* left = get_literal (in->left);
	Literal* right = get_literal (in->right);

	if (left) in->left = left;
	if (right) in->right = right;

	if (isa<Literal> (in->left) 
			&& isa<Literal> (in->right))
	{
		Literal* result = PHP::fold_bin_op (left, in->op, right);
		if (result)
			return result;
	}

	return in;
}

Expr*
SCCP::transform_cast (Statement_block*, Cast* in)
{
	Literal* lit = get_literal (in->variable_name);

	if (lit)
	{
		Literal* result = PHP::cast_to (in->cast, lit);
		if (result)
			return result;
	}

	return in;
}

Expr*
SCCP::transform_constant (Statement_block*, Constant* in)
{
	Literal* lit = PHP::fold_constant (in);
	if (lit)
		return lit;
	
	// We'd very much like to know the value of this, however, since these are
	// likely to be defined at the top-level, and this optimization won't run
	// at the top-level (until its interprocedural), it won't do much good.
	return in;
}

Expr*
SCCP::transform_field_access (Statement_block*, Field_access* in)
{
	// TODO warning
	// TODO promote name to FIELD_NAME
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
	// TODO replace Variable_variable with VARIABLE_NAME, if possible.
	if (isa<Variable_method> (in->method_name))
		die ();

	// ignore for now
	if (isa<METHOD_NAME> (in->method_name))
	{
		METHOD_NAME* name = dyc<METHOD_NAME> (in->method_name);
		if (PHP::is_pure_function (name))
		{
			bool all_args_const = true;
			Literal_list* params = new Literal_list;
			foreach (Actual_parameter* param, *in->actual_parameters)
			{
				// TODO: we can replace a arguement with its actual parameter
				// (watch out for refs) (only if passing by copy)
				if (param->is_ref
					|| get_literal (param->rvalue) == NULL)
					all_args_const = false;
				else
					params->push_back (get_literal (param->rvalue));
			}

			if (all_args_const)
			{
				Literal* result = PHP::call_function (name, params);
				if (result)
					return result;
				else
				{
					// fall through to get params updated.
				}
			}
		}

		// Update the parameters
		foreach (Actual_parameter* param, *in->actual_parameters)
		{
			// TODO: We can replace a argument with its actual parameter (watch
			// out for refs) (only if passing by copy)
			// TODO: re-enable once codegen supports it. (also, once we can check signatures)
//			if (!param->is_ref && get_literal (param->rvalue))
//				param->rvalue = get_literal (param->rvalue);
		}
	}

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
	return in;
}

Expr*
SCCP::transform_unary_op (Statement_block*, Unary_op* in)
{
	if (Literal* lit = get_literal (in->variable_name))
	{
		Literal* folded = PHP::fold_unary_op (in->op, lit);
		assert (folded);
		return folded;
	}

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

class SCCP_updater : public Visit_once
{
	Lattice_map& lattice;

	// For visit_expr
	SCCP* sccp;
public:

	SCCP_updater (Lattice_map& lattice, SCCP* sccp)
	: lattice (lattice)
	, sccp (sccp)
	{
	}

	void visit_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
	{
		foreach (Edge* edge, *bb->get_predecessor_edges ())
		{
			Rvalue* arg = bb->get_phi_arg_for_edge (edge, phi_lhs);

			if (isa<Literal> (arg))
				continue;

			Literal* lit = get_literal (arg);
			if (lit)
				bb->set_phi_arg_for_edge (edge, phi_lhs, lit);
		}
	}

	void visit_branch_block (Branch_block* bb)
	{
		Literal* lit = get_literal (bb->branch->variable_name);
		if (lit)
			bb->cfg->set_branch_direction (bb, PHP::is_true (lit));
	}

	void visit_assign_array (Statement_block*, MIR::Assign_array* in)
	{
		Literal* index = get_literal (in->index);
		Literal* rhs = get_literal (in->rhs);
		if (index) in->index = index;
		if (rhs) in->rhs = rhs;
	}

	void visit_assign_field (Statement_block*, MIR::Assign_field *)
	{
		die ();
	}

	void visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
	{
		in->rhs = sccp->transform_expr (bb, in->rhs);
	}

	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*)
	{
		die ();
	}

	void visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
	{
		in->expr = sccp->transform_expr (bb, in->expr);
	}

	void visit_foreach_end (Statement_block*, MIR::Foreach_end*)
	{
		// No folding for any foreach statement.
	}

	void visit_foreach_next (Statement_block*, MIR::Foreach_next*)
	{
	}

	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*)
	{
	}

	void visit_global (Statement_block*, MIR::Global* in)
	{
		// if it has a Variable_variable, with a static variable, update.
		if (isa<Variable_variable> (in->variable_name))
			die ();
	}

	void visit_pre_op (Statement_block*, MIR::Pre_op*)
	{
		die ();
	}

	void visit_assign_next (Statement_block*, MIR::Assign_next*)
	{
		die ();
	}

	void visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
	{
		if (Literal* lit = get_literal (in->def))
			bb->statement = new Assign_var (in->def, false, lit);
	}

	void visit_return (Statement_block* bb, MIR::Return* in)
	{
		// Dont propagate to return-by-ref
		if (bb->cfg->get_entry_bb ()->method->signature->is_ref)
			return;

		// TODO change Return to take an Rvalue
	}

	void visit_static_declaration (Statement_block*, MIR::Static_declaration*)
	{
		die ();
	}

	void visit_throw (Statement_block*, MIR::Throw*)
	{
		die ();
	}

	void visit_try (Statement_block*, MIR::Try*)
	{
		die ();
	}

	void visit_unset (Statement_block*, MIR::Unset* in)
	{
		assert (in->target == NULL);
		assert (in->array_indices->size () == 0);
		assert (isa<VARIABLE_NAME> (in->variable_name));

		// do nothing for a normal variable
	}

	Literal* get_literal (Rvalue* in)
	{
		return sccp->get_literal (in);
		// TODO: When updating, TOP means uninitialized, which in PHP means
		// NULL. (Need to expand this poor attempt at uninitialized variables).
//		if (lit)
//			return lit;
//		else if (sccp->lattice[dyc<VARIABLE_NAME>(in)] == TOP)
//			return new NIL();
//		else
//			return NULL;
	}

};

void
SCCP::update_ir (CFG* cfg)
{
	SCCP_updater* updater = new SCCP_updater (lattice, this);
	updater->run (cfg);
}