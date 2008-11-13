#include "Dead_code_elimination.h" // TODO: rename file
#include "process_ir/General.h"
#include "Def_use.h"
#include "assert.h"
#include "embed/embed.h"

using namespace MIR;
using namespace boost;

DCE::DCE ()
: marks (&ssa_op_ptr_comparison)
{
}

bool is_pure (Expr* in)
{
	Wildcard<METHOD_NAME>* name = new Wildcard<METHOD_NAME>;
	if (in->match (new Method_invocation (NULL, name, NULL))
		&& PHP::is_pure_function (name->value))
		return true;

	return (not (isa<New> (in) || isa<Method_invocation> (in)));
}

/*
 * Does the statement have any externally visible effects (like IO)?
 *		Has visible effects:
 *			Any function we dont know anything about
 *			TODO: impure functions dont necessarily have them (ie array_merge)
 *			Any class instatiation we know nothing about
 *
 *		 Doesn't have visible effects
 *			Anything else
*/
bool is_critical (Statement* in)
{
	if (isa<Return> (in))
		return true;

	if (not (isa<Eval_expr> (in) || isa<Assign_var> (in)))
		return false;

	Wildcard<Expr>* expr = new Wildcard<Expr>;
	if (in->match (new Eval_expr (expr))
		|| in->match (
			new Assign_var (
				new Wildcard<VARIABLE_NAME>,
				false, // dont-care
				expr)))
	{
		// TODO: pure and critical are different
		// TODO: indirect operations arent taken into account
		return !is_pure (expr->value);
	}
	else
		return false;

	// TODO: the statement is critical if it assigns to a reference parameter
}

// TODO add phi nodes

/*
 * Cooper/Torczon, Sec. 10.3.1 and Figure 10.3
 *		http://www.cs.rice.edu/~keith/512/Lectures/10DeadCprop.pdf
 *
 *	Has a mark-sweep-style DCE algorithm: (based on Cytron et al SSA paper,
 *	section 7.1)
 *
 *	Dead ():
 *		MarkPass ()
 *		SweepPass ()
 */

/*	MarkPass ():
 *
 *		Worklist = []
 *
 *		// works on statements only: Phis cant be critical
 *		foreach statement S
 *			clear s.mark
 *			if s is critical
 *				set s.mark
 *				worklist []= s
 *
 *		// Works on phis and statements.
 *		while !worklist.empty ()
 *			i = worklist.pop_front ()
 *			foreach u in i.uses ()
 *				d = u.def ()
 *				if (!d.mark)
 *					set d.mark
 *					worklist []= d
 *
 *			foreach bb in s.rdf ()
 *				j = bb.branch ()
 *				if j.mark:
 *					set j.mark
 *					worklist =[] j
 */
void
DCE::mark_pass ()
{
	// Initialize the critical blocks - a critical block is a side-effecting
	// statement.
	// We don't have any information with which to mark assignments affecting
	// reference parameters. However, these are covered since the Exit_block is
	// critical, and it uses all reference parameters. This creates may-uses for
	// all the aliases, which transitively follows CHI nodes, ensuring that
	// assignments are marked as critical.
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
		{
			if (is_critical (sb->statement))
			{
				DEBUG ("marking " << bb->get_index() << " as critical");
				mark(SSA_op::for_bb (sb));
			}
		}
		else if (isa<Exit_block> (bb))
		{
			// Make sure the uses from the Exit block are processed
			foreach (VARIABLE_NAME* use, *bb->get_uses (SSA_ALL))
				mark_def (use);
		}
	}

	dump ();

	// Go through the worklist, propagating the mark from uses to defs
	while (worklist->size () > 0)
	{
		SSA_op* op = worklist->front ();
		worklist->pop_front ();
		DEBUG ("\nProcessing ");
		op->dump ();

		foreach (VARIABLE_NAME* use, *op->get_uses ())
		{
			mark_def (use);

			// MU/CHIs make the BB containing them live.
			if (isa<SSA_mu> (op) || isa<SSA_chi> (op))
			{
				Basic_block* bb = op->get_bb ();
				if (isa<Branch_block> (bb) || isa<Statement_block> (bb))
					mark (SSA_op::for_bb (bb));
			}
		}

		// Mark the critical branches (ie, the reverse dominance frontier of
		// the critical blocks: The dominance frontier occurs at joins. The
		// reverse-dominance frontier is therefore at splits, which must be
		// branches). They are marked as they are required for control flow to
		// reach this point. They are just as important for phis as they are for
		// other statements, and we mark the branch, not the phi.
		foreach (Basic_block* rdf, *op->get_bb ()->get_reverse_dominance_frontier ())
		{
			DEBUG ("marking " << rdf->get_index()
					<< " as part of " << op->get_bb()->get_index() << "'s RDF");
			mark(SSA_op::for_bb (rdf));
		}
	}
}

void
DCE::mark (SSA_op* op)
{
	if (!marks[op])
	{
		marks[op] = true;
		worklist->push_back (op);
	}
}

void
DCE::mark_def (VARIABLE_NAME* use)
{
	// ignore uninit
	if (!cfg->duw->has_def (use))
		return;

	SSA_op* def = cfg->duw->get_defs (use, SSA_ALL)->front ();
	DEBUG ("marking ")
	def->dump ();
	DEBUG (" due to def of " << *use->get_ssa_var_name ());
	mark (def);
}

// Check if the block is marked (ignoring the phi nodes)
bool
DCE::is_marked (Basic_block* bb)
{
	if (isa<Entry_block> (bb) || isa<Exit_block> (bb) || isa<Empty_block> (bb))
		return true;

	return marks[SSA_op::for_bb (bb)];
}

/*	SweepPass ():
 *		foreach operation i: // i can be a phi or a statement
 *			if !i.mark
 *				if isa<Branch> (i)
 *					i = jump to nearest marked post-dominator
 *				else
 *					delete i
 */
void
DCE::sweep_pass ()
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		// Remove the phi nodes first, since the BB* may be replaced with an
		// Empty BB.
		foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss ())
		{
			if (!marks[new SSA_phi (bb, phi_lhs)])
				bb->remove_phi_node (phi_lhs);
		}

		if (isa<Statement_block> (bb) && !is_marked (bb))
		{
			cfg->remove_bb (bb);
		}

		else if (isa<Branch_block> (bb) && !is_marked (bb))
		{
			// find the nearest marked post-dominator
			Basic_block* postdominator = bb;
			while (!is_marked (postdominator))
				postdominator = postdominator->get_immediate_reverse_dominator ();

			cfg->remove_branch (dyc<Branch_block> (bb), postdominator);
		}
	}

	// TODO: what about removing CHIs?
}

void
DCE::run (CFG* cfg)
{
	marks.clear ();
	worklist = new SSA_op_list;
	this->cfg = cfg;

	mark_pass ();
	dump ();
	sweep_pass ();
}

void
DCE::dump()
{
	CHECK_DEBUG ();
	DEBUG ("DCE:");
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
		DEBUG (bb->get_index() << ": " << is_marked (bb))
}
