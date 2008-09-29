#include "Dead_code_elimination.h" // TODO: rename file
#include "process_ir/General.h"
#include "Def_use.h"
#include "assert.h"
#include "embed/embed.h"

using namespace MIR;

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
}

/*
 * Cooper/Torczon, Sec. 10.3.1 and Figure 10.3
 *		http://www.cs.rice.edu/~keith/512/Lectures/10DeadCprop.pdf
 *
 *	Has a mark-sweep-style DCE algorithm:
 *
 *	Dead ():
 *		MarkPass ()
 *		SweepPass ()
 */

/*	MarkPass ():
 *
 *		Worklist = []
 *
 *		foreach statement S
 *			clear s.mark
 *			if s is critical
 *				set s.mark
 *				worklist []= s
 *
 *		while !worklist.empty ()
 *			s = worklist.pop_front ()
 *			foreach u in s.uses ()
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
	BB_list* worklist = new BB_list;

	// Initialize the critical blocks - a critical block is a side-effecting one
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (isa<Entry_block> (bb) || isa<Exit_block> (bb))
			marks[bb] = true;

		else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
		{
			if (is_critical (sb->statement))
			{
				marks[bb] = true;
				worklist->push_back (bb);
			}
		}
		else
		{
			// Branches and phis are handled below.
		}
	}

	// Go through the worklist, propagating the mark from uses to defs
	while (worklist->size () > 0)
	{
		Basic_block* bb = worklist->front ();
		worklist->pop_front ();

		foreach (VARIABLE_NAME* use, *cfg->duw->get_bb_uses (bb))
		{
			SSA_edge* def = cfg->duw->get_var_defs (use);
			if (marks[def->bb])
			{
				marks[def->bb] = true;
				worklist->push_back (bb);
			}
		}

		// Mark the critical branches (ie, the reverse dominance frontier of the
		// critical blocks)
		foreach (Basic_block* rdf, *bb->get_reverse_dominance_frontier ())
		{
			assert (isa<Branch_block> (rdf));
			marks[rdf] = true;
			worklist->push_back (rdf);
		}
	}
}

/*	SweepPass ():
 *		foreach statement S:
 *			if !s.mark
 *				if isa<Branch> (s)
 *					s = jump to nearest marked post-dominator
 *				else
 *					delete s
 */
void
DCE::sweep_pass ()
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (!marks[bb])
		{
			if (isa<Branch_block> (bb))
			{
				// TODO: post-dominance isnt correct
				assert (0);

				// find the nearest marked post-dominator
				Basic_block* postdominator = bb;
				while (!marks[postdominator])
					postdominator = postdominator->get_immediate_reverse_dominator ();

				cfg->remove_branch (dyc<Branch_block> (bb), postdominator);
			}
			else
				cfg->remove_bb (bb);
		}
	}
}

void
DCE::run (CFG* cfg)
{
	marks.clear ();
	this->cfg = cfg;
	mark_pass ();
	sweep_pass ();
}

/*
void
DCE::transform_assign_var (Statement_block* bb, Assign_var* in, BB_list* out)
{
	if (bb->cfg->duw->get_var_uses(in->lhs)->size () == 0)
	{
		if (not is_pure (in->rhs))
		{
			out->push_back (new Statement_block (bb->cfg, new Eval_expr (in->rhs)));
		}
		else
		{
			DEBUG ("Removing BB (no uses)")
			debug (in);
		}
	}
	else
		out->push_back (bb);
}

// TODO: replace with ADCE
// TODO: add remove SSA_pre_ops

void
DCE::transform_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
{
	// remove phis with unused LHSs
	if (bb->cfg->duw->get_var_uses (phi_lhs)->size () == 0)
		bb->remove_phi_node (phi_lhs);
}

void
DCE::transform_eval_expr (Statement_block* bb, MIR::Eval_expr* in, BB_list* out)
{
	if (not is_pure (in->expr))
	{
		out->push_back (bb);
	}
}
*/
