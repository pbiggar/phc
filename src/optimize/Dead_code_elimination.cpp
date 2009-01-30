#include "Dead_code_elimination.h" // TODO: rename file
#include "process_ir/General.h"
#include "Def_use_web.h"
#include "assert.h"
#include "embed/embed.h"
#include "Oracle.h"

using namespace MIR;
using namespace boost;

DCE::DCE ()
: marks (&ssa_op_ptr_comparison)
{
}

// TODO: move this to Oracle
bool is_pure (Expr* in)
{
	Wildcard<METHOD_NAME>* name = new Wildcard<METHOD_NAME>;
	if (in->match (new Method_invocation (NULL, name, NULL))
		&& Oracle::is_pure_function (name->value))
		return true;

	return (not (isa<New> (in) || isa<Method_invocation> (in)));
}

/*
 * TODO:
 *		How do we model that an otherwise dead statement may def its RHS. It
 *		clearly shouldnt be done here. It should be in the def-use info.
 *
 *		Then we can say that 'global $x' is not _automatically_ critical, and
 *		likewise for all of the indirect assignments.
 */

bool
is_reference_statement (Statement* in)
{
	// global $x creates a NULL $x in the global scope (which can probably only
	// be seen by the compact function, but what of it).
	if (isa<Global> (in))
		return true;
	
	if (Assign_var* av = dynamic_cast<Assign_var*> (in))
		return false; // We should be able to handle this with the def-use info we have now.
	else if (Assign_var_var* avv = dynamic_cast<Assign_var_var*> (in))
		return avv->is_ref;
	else if (Assign_field* af = dynamic_cast<Assign_field*> (in))
		return af->is_ref;
	else if (Assign_array* aa = dynamic_cast<Assign_array*> (in))
		return aa->is_ref;
	else if (Assign_next* an = dynamic_cast<Assign_next*> (in))
		return an->is_ref;

	return false;
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
 *
 *	Whether or not this touches reference parameters is modelled with a MU in
 *	the block exit, so it can be safely ignored here.
*/
bool is_critical (Statement* in)
{
	// TODO: this is only critical if its result is used.
	if (isa<Return> (in))
		return true;

	// Foreach_end defines a virtual variable representing the iterator. As
	// such, its never going to be critical. However, its needed every time the
	// Foreach_reset is present. So treat it specially.
	// TODO: is there a way to handle this without special casing it?
	// TODO: virtual-variables are incorrect, so we just mark the foreach_*
	// nodes which write as critical.
	if (	isa<Foreach_reset> (in)
		|| isa<Foreach_next> (in)
		|| isa<Foreach_end> (in))
		return true;

	// TODO: we are assuming for now that all indirect assignments are
	// incorrectly modelled, and should not be removed.
	if (	isa<Assign_field> (in)
		|| isa<Assign_next> (in)
		|| isa<Assign_array> (in)
		|| isa<Assign_var_var> (in))
		return true;

	// TODO: As above
	Unset* unset = dynamic_cast<Unset*> (in);
	if (unset && unset->array_indices->size () > 0)
		return true;
	

	// All reference statements may create values for their RHS
	if (is_reference_statement (in))
		return true;

	// TODO: these can cause side-effecting functions such as __get or __set.
	if (not (isa<Eval_expr> (in) || isa<Assign_var> (in)))
		return false;

	// Function calls
	Wildcard<Expr>* expr = new Wildcard<Expr>;
	if (in->match (new Eval_expr (expr))
		|| in->match (
			new Assign_var (
				new Wildcard<VARIABLE_NAME>,
				false, // dont-care
				expr)))
	{
		// TODO: pure and critical are different
		// TODO: note also that variables can be created by a reference here.
		return !is_pure (expr->value);
	}
	else
		return false;
}

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

	dump ();
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
			foreach (VARIABLE_NAME* use, *bb->get_uses (SSA_STMT | SSA_MU | SSA_CHI))
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

	// Special case for Foreach_end: If its defining reset isnt marked, unmark it.
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		Foreach_end* fe = NULL;
		Foreach_reset* fr = NULL;
		Statement_block *sb, *sdom;
		if ((sb = dynamic_cast<Statement_block*> (bb))
			&& (fe = dynamic_cast<Foreach_end*> (sb->statement)))
		{
			// Find the Foreach_reset, which must dominate it.
			bool found = false;
			Basic_block* dom = bb;
			while ((dom = dom->get_immediate_dominator ()))
			{
				if ((sdom = dynamic_cast<Statement_block*> (dom))
					&& (fr = dynamic_cast<Foreach_reset*> (sdom->statement)))
				{
					if (fr->iter->equals (fe->iter))
					{
						if (!is_marked (dom))
							marks [SSA_op::for_bb (bb)] = false;

						found = true;
						break;
					}
				}
			}
			assert (found);
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
	DEBUG ("marking ");
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
	}

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
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
		DEBUG (bb->get_index() << ": " << is_marked (bb));
}
