
#if 0

	TODO:

		Remove this file. Right now it is being kept because of the
		comments, and because the transformer is a tidier way of
		doing things than the current combination of CCP and
		Optimization_transformer.
 
/*
 * Cooper/Torczon Section 10.3.3 describes SSCP, which is weaker than SCCP.
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
 *		uses. Cite it (2005 proceedings)
 *
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
#include "Def_use_web.h"
#include "Oracle.h"
#include "process_ir/debug.h"

using namespace MIR;


void
SCCP::visit_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
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
	foreach (Edge* pred, *bb->get_predecessor_edges ())
	{
		if (!pred->is_executable)
			; // use TOP, aka do nothing
		else
		{
			VARIABLE_NAME* arg = bb->get_phi_arg_for_edge (pred, phi_lhs);
			result = ::meet (result, lattice[arg]);
		}
	}
	// This overwrites the old value.
	set_lattice (phi_lhs, result);
}

void
SCCP::visit_chi_node (Basic_block* bb, VARIABLE_NAME* chi_lhs, VARIABLE_NAME*)
{
	set_lattice (chi_lhs, BOTTOM);
}


/*
 * The rest of the statements make up VisitExpr:
 *
 *	VisitExpr:
 *	Evaluate the expression.
 *	- If its an assignment and creates a result for the LHS, add all SSA edges
 *	from LHS to SSAWL.
 *	- If its a branch, add:
 *		- all outgoing edges to CFGWL for BOTTOM
 *		- only the appropriate outgoing edge for a constant
 */



// Initialize all parameters to BOTTOM.
void
SCCP::visit_entry_block (Entry_block* bb)
{
	foreach (VARIABLE_NAME* var, *bb->get_defs (SSA_FORMAL))
	{
		// No need to run again
		lattice[var] = BOTTOM;
	}
}

Edge_list*
SCCP::get_branch_successors (Branch_block* bb)
{
	/*	- If its a branch, add:
	 *		- all outgoing edges to CFGWL for BOTTOM
	 *		- only the appropriate outgoing edge for a constant
	 */
	if (lattice[bb->branch->variable_name] == BOTTOM)
		return bb->get_successor_edges ();

	else
	{
		// If its TOP, it must not have a def. Otherwise it would have been
		// processed by visit_block.
		if (lattice[bb->branch->variable_name] == TOP)
			assert (!bb->cfg->duw->has_def (bb->branch->variable_name));

		if (PHP::is_true (get_literal (bb->branch->variable_name)))
			return new Edge_list (bb->get_true_successor_edge ());
		else
			return new Edge_list (bb->get_false_successor_edge ());
	}
}

/*
 * Statements
 */

void
SCCP::visit_assign_field (Statement_block*, MIR::Assign_field *)
{
	phc_optimization_exception("SCCP does not support assignments to fields");
}

// In the paper, this is VisitExpression.
void
SCCP::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	if (lattice[in->lhs] == BOTTOM)
		return;

	// We dont care about is_ref, because CHI nodes will handle it.

	// TODO: if all MU have the same value, we can probably optimize.


	Expr* expr = transform_expr (bb, in->rhs->clone ());

	if (isa<Literal> (expr))
		meet_lattice (in->lhs, new Literal_cell (dyc<Literal> (expr)));
	else if (!isa<Literal> (expr))
		set_lattice (in->lhs, BOTTOM);
}


void
SCCP::visit_assign_var_var (Statement_block*, MIR::Assign_var_var*)
{
	phc_optimization_exception("SCCP does not support assignments to variable-variables");
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
SCCP::visit_global (Statement_block*, MIR::Global* in)
{
	// The Def-use info indicates this is a DEF, so we must put it to BOTTOM, or
	// else it will be assumed TOP.
	if (isa<Variable_variable> (in->variable_name))
		phc_optimization_exception ("SCCP does not support global variable-variables");

	set_lattice (dyc<VARIABLE_NAME> (in->variable_name), BOTTOM);
}

void
SCCP::visit_pre_op (Statement_block*, MIR::Pre_op*)
{
	phc_unreachable ();
}

void
SCCP::visit_assign_next (Statement_block*, MIR::Assign_next* in)
{
	// TODO: theres a virtual here
}

void
SCCP::visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
{
	if (lattice[in->use] == BOTTOM)
		set_lattice (in->def, BOTTOM);

	else
	{
		Literal* result = PHP::fold_pre_op (get_literal (in->use), in->op);

		if (result)
			meet_lattice (in->def, new Literal_cell (result));
	}
}

void
SCCP::visit_static_declaration (Statement_block*, MIR::Static_declaration*)
{
	phc_optimization_exception("SCCP does not support assignments to statics");
}

void
SCCP::visit_try (Statement_block*, MIR::Try*)
{
	phc_optimization_exception("SCCP does not support try blocks");
}

void
SCCP::visit_unset (Statement_block*, MIR::Unset* in)
{
	if (in->target == NULL
	&& in->array_indices->size () == 0
	&& isa<VARIABLE_NAME> (in->variable_name))
	{
		// Def_use asserts what we cant handle, for now.
		meet_lattice (dyc<VARIABLE_NAME> (in->variable_name),
				new Literal_cell (new NIL ()));
	}
	else if (isa<Variable_variable> (in->variable_name))
		// TODO: kill everything
	  phc_optimization_exception("SCCP does not support unset-ing variable-variables");
}

/* Returns NULL, or the literal in VARIABLE_NAME. We have separate functions,
 * because we cant substitute Literals directly into the IR in many cases.*/
Literal*
SCCP::get_literal (Rvalue* in)
{
	if (isa<Literal> (in))
		return dyc<Literal> (in);

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);

	// UNINIT becomes NULL. This doesn't affect the algorithm in Phi nodes.
	if (lattice[var_name] == TOP)
		return new NIL();

	if (lattice[var_name] == BOTTOM)
		return NULL;

	return dyc<Literal_cell> (lattice[var_name])->value;
}


/*
 * Exprs
 *		To avoid code duplication, we use the same visit_expr. In the initial
 *		analysis, we pass a clone, so that destructive updates are OK.
 */

Expr*
SCCP::transform_array_access (Statement_block*, Array_access* in)
{
	Literal* index = get_literal (in->index);

	// Fold index
	if (index)
		in->index = index;

	// Is this a string, with a known index.
	Literal* array = get_literal (in->variable_name);
	if (array && index)
	{
		Literal* result = PHP::fold_string_index (array, index);
		if (result)
			return result;
	}

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

		// TODO: cast could take an Rvalue, is it a good idea?
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

	phc_optimization_exception("SCCP does not support optimizing field-accesses");
	return in;
}

Expr*
SCCP::transform_instanceof (Statement_block*, Instanceof* in)
{
	phc_optimization_exception("SCCP does not support optimizing instanceof statements");
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
	  phc_optimization_exception("SCCP does not support optimizing method invocations involving variable-methods");

	// ignore for now
	if (METHOD_NAME* name = dynamic_cast<METHOD_NAME*> (in->method_name))
	{
		phc_optimization_exception ("SCCP does not support optimizing method invocations");
		/*
		Signature* sig = Oracle::get_signature (name);
		if (Oracle::is_pure_function (name))
		{
			assert (sig);

			bool all_args_const = true;
			Literal_list* params = new Literal_list;
			foreach (Actual_parameter* param, *in->actual_parameters)
			{
				// TODO: we can replace a argument with its actual parameter
				// (watch out for refs) (only if passing by copy)
				if (param->is_ref
					|| sig->is_param_passed_by_ref (params->size ())
					|| get_literal (param->rvalue) == NULL)
				{
					all_args_const = false;
					break;
				}
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
		int i = 0;
		foreach (Actual_parameter* param, *in->actual_parameters)
		{
			if (!param->is_ref
				&& sig 
				&& !sig->is_param_passed_by_ref (i)
				&& get_literal (param->rvalue))
			{
				param->rvalue = get_literal (param->rvalue);
			}

			i++;
		}
		*/
	}

	return in;
}

Expr*
SCCP::transform_new (Statement_block*, New* in)
{
	// TODO turn a variable_class into a CLASS_NAME 
	phc_optimization_exception("SCCP does not support optimizing `new` statements");
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
	  phc_optimization_exception("SCCP does not support optimizing variable-variables");

	// in = new VARIABLE_NAME (PHP::to_string (lit));
	return in;
}


/*
 * Updating, after the analysis is finished.
 */

class SCCP_updater : public Visit_once
{
	SSA_map& lattice;

	// For visit_expr
	SCCP* sccp;
public:

	SCCP_updater (SSA_map& lattice, SCCP* sccp)
	: lattice (lattice)
	, sccp (sccp)
	{
	}

	void visit_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
	{
		// Dont update phi nodes. We're going to drop them later, and we dont
		// want to remove the use of the variable.
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
		if (index) in->index = index;

		if (!in->is_ref)
		{
			Literal* rhs = get_literal (in->rhs);
			if (rhs) in->rhs = rhs;
		}
	}

	void visit_assign_field (Statement_block*, MIR::Assign_field *)
	{
	  phc_optimization_exception("SCCP does not support optimizing field assignments");
	}

	void visit_assign_next (Statement_block*, MIR::Assign_next* in)
	{
		if (!in->is_ref)
		{
			Literal* rhs = get_literal (in->rhs);
			if (rhs) in->rhs = rhs;
		}
	}

	void visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
	{
		// Put the transformed expression in unless its a reference assignment,
		// and the result is a literal, which isnt allowed).
		Expr* result = sccp->transform_expr (bb, in->rhs);
		if (!(in->is_ref && isa<Literal> (result)))
			in->rhs = result;
	}

	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*)
	{
	  phc_optimization_exception("SCCP does not support optimizing variable-variables");
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
	    phc_optimization_exception("SCCP does not support optimizing global variable-variables");
	}

	void visit_pre_op (Statement_block*, MIR::Pre_op*)
	{
		phc_unreachable ();
	}

	void visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
	{
		if (Literal* lit = get_literal (in->def))
			bb->statement = new Assign_var (in->def, false, lit);
	}

	void visit_return (Statement_block* bb, MIR::Return* in)
	{
		// Dont propagate to return-by-ref
		if (bb->cfg->get_entry_bb ()->method->signature->return_by_ref)
			return;

		// TODO change Return to take an Rvalue
	  phc_optimization_exception("SCCP does not support optimizing return values");
	}

	void visit_static_declaration (Statement_block*, MIR::Static_declaration*)
	{
	  phc_optimization_exception("SCCP does not support optimizing static declarations");
	}

	void visit_throw (Statement_block*, MIR::Throw*)
	{
	  phc_optimization_exception("SCCP does not support optimizing throw statements");
	}

	void visit_try (Statement_block*, MIR::Try*)
	{
	  phc_optimization_exception("SCCP does not support optimizing try blocks");
	}

	void visit_unset (Statement_block*, MIR::Unset* in)
	{
		assert (in->target == NULL);
		assert (isa<VARIABLE_NAME> (in->variable_name));

		foreach (Rvalue*& rv, *in->array_indices)
		{
			if (VARIABLE_NAME* var = dynamic_cast<VARIABLE_NAME*> (rv))
				if (Literal* lit = get_literal (var))
					rv = lit;
		}

		// do nothing for a normal variable
	}

	Literal* get_literal (Rvalue* in)
	{
		return sccp->get_literal (in);
	}

};


void
SCCP::post_pass (CFG* cfg)
{
	SCCP_updater* updater = new SCCP_updater (lattice, this);
	updater->run (cfg);
}
#endif



