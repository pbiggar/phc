#include "Dead_code_elimination.h" // TODO: rename file
#include "process_ir/General.h"
#include "Def_use_web.h"
#include "assert.h"
#include "embed/embed.h"
#include "Oracle.h"

using namespace MIR;
using namespace boost;

DCE::DCE ()
{
}

// TODO: move this to Oracle
bool is_pure (Expr* in)
{
	// TODO: use Whole_program for this, and mark user-functions according to
	// whether they do something impure (except uses and defs).
	Wildcard<METHOD_NAME>* name = new Wildcard<METHOD_NAME>;
	if (in->match (new Method_invocation (NULL, name, NULL))
		&& Oracle::is_pure_function (name->value))
		return true;

	return (not (isa<New> (in) || isa<Method_invocation> (in)));
}

/*
 * Does the statement have any externally visible effects (like IO)?
 *		Has visible effects:
 *			Any function we dont know anything about
 *			TODO: impure functions dont necessarily have them (ie array_merge)
 *			Any class instatiation
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

	// Foreach_end is needed every time the Foreach_reset is present. So treat
	// it specially.
	// TODO: is there a way to handle this without special casing it?
	// TODO: just mark the foreach_* nodes which write as critical.
	// TODO: rethink this. We should be able to remove unused blocks entirely.
	if (	isa<Foreach_reset> (in)
		|| isa<Foreach_next> (in)
		|| isa<Foreach_end> (in))
		return true;

	// TODO: these can cause side-effecting functions such as __get or __set.
	// Function calls
	Wildcard<Expr>* expr = new Wildcard<Expr>;
	if (in->match (new Eval_expr (expr))
		|| in->match (
			new Assign_var (
				new Wildcard<VARIABLE_NAME>,
				false, // dont-care
				expr)))
	{
		return !is_pure (expr->value);
	}
	else
		return false;
}

bool
is_bb_critical (Basic_block* bb)
{
	if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
		return (is_critical (sb->statement));

	if (isa<Exit_block> (bb) || isa<Entry_block> (bb))
		return true;

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
	// reference parameters. However, these are covered since the Exit_block
	// is critical, and it uses all reference parameters. This creates
	// may-uses for all the aliases, which transitively follows CHI nodes,
	// ensuring that assignments are marked as critical.

	dump ();
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (is_bb_critical (bb))
		{
			mark_entire_block (bb, "as critical");
		}
	}

	dump ();

	// Go through the worklist, propagating the mark from uses to defs
	while (worklist->size () > 0)
	{
		SSA_def* def = worklist->front ();
		worklist->pop_front ();
		DEBUG ("\nProcessing ");
		def->dump ();

		foreach (SSA_use* use, *def->get_uses ())
		{
			if (use->type_flag != SSA_PHI)
				mark_def (use);
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
							unmark_block (bb);

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
DCE::mark_entire_block (Basic_block* bb, string why)
{
	if (bb_marks[bb->ID])
		return;

	DEBUG ("marking " << bb->ID << " " << why);
	bb_marks [bb->ID] = true;

	// Note there are no may-defs here. They're already divided into defs or
	// uses. Also, "entire block" doesnt include Phis.

	foreach (SSA_use* use, *bb->cfg->duw->get_block_uses (bb))
	{
		if (use->type_flag != SSA_PHI)
			mark_def (use);
	}
	foreach (SSA_def* def, *bb->cfg->duw->get_block_defs (bb))
	{
		if (def->type_flag != SSA_PHI)
			mark (def, "");
	}
	// Mark the critical branches (ie, the reverse dominance frontier of
	// the critical blocks: The dominance frontier occurs at joins. The
	// reverse-dominance frontier is therefore at splits, which must be
	// branches). They are marked as they are required for control flow to
	// reach this point. They are just as important for phis as they are for
	// other statements, and we mark the branch, not the phi.
	mark_rdf (bb);
}

void
DCE::mark_rdf (Basic_block* bb)
{
	foreach (Basic_block* rdf, *bb->get_reverse_dominance_frontier ())
	{
		mark_entire_block (rdf, "as part of " + lexical_cast<string>(bb->ID) + "'s RDF"); 
	}
}

void
DCE::mark (SSA_def* def, string why)
{
	assert (def->type_flag != SSA_PHI);		//Not 100% sure if this assertion is correct, think so though

	if (marks[def])
	{
		return;
	}
		
	DEBUG ("marking ");
	def->dump();
	DEBUG (why);

	marks[def] = true;

	// TODO: really we should be marking the def but not the CHI, but its not
	// set up well for that at the moment.
	mark_entire_block (def->bb, "");

	worklist->push_back (def);
}

void
DCE::mark_def (SSA_use* use)
{
	if (use->get_defs ()->size () == 1)
	{
		SSA_def* def = use->get_defs ()->front ();
		if (marks[def])
			return;

		// When a def which is a phi node is marked, we need to mark it's arguments also
		if (def->type_flag == SSA_PHI)
		{
			// Here I'm making the assumption that the RDF of a phi node whose arguments we're marking 
			// doesn't need to be marked.  This could be wrong however...
			
			marks[def] = true;		//should I call mark () here?  Probably... I'd need to change mark () though.. TODO
			foreach (SSA_name* phi_arg, *def->bb->get_phi_args (*def->name))
			{
				if (phi_arg->str () != use->name->str ())
				{
					if (phi_arg->get_version ())			
					{
						if (def->bb->cfg->duw->get_named_uses (phi_arg)->size ())
						{
							SSA_use* arg_use = def->bb->cfg->duw->get_named_uses (phi_arg)->front ();
							mark_def (arg_use);	
						}	
					}	
				}
			}
		}	
		else
			mark (def, "due to def of " + use->name->str ());
		
	}	

}

void
DCE::unmark_block (Basic_block* bb)
{
	bb_marks [bb->ID] = false;
}

// Check if the block is marked (ignoring the phi nodes)
bool
DCE::is_marked (Basic_block* bb)
{
	if (isa<Entry_block> (bb) || isa<Exit_block> (bb) || isa<Empty_block> (bb))
		return true;

	return bb_marks [bb->ID];
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
	DEBUG("START SWEEP PASS");

	// TODO: Verify if the below code for removing phis is in anyway useful 
	//	(I think the ones we remove will just not get recreated when the DUW is rebuilt)
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		// Remove the phi nodes first, since the BB* may be replaced with an
		// Empty BB.
		foreach (SSA_name phi_lhs, *bb->get_phi_lhss ())
		{
			if (!marks[new SSA_def (bb, &phi_lhs,SSA_PHI)])
				bb->remove_phi_node (phi_lhs);
		}
	}

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (is_marked (bb))
			continue;

		DEBUG (bb->ID << " is not marked");

		if (isa<Statement_block> (bb))
		{
			cfg->remove_bb (bb);
			DEBUG ("REMOVED " << bb->ID);
			CTS ("num_blocks_removed");
		}

		else if (isa<Branch_block> (bb))
		{
			// find the nearest marked post-dominator
			Basic_block* postdominator = bb;
			while (!is_marked (postdominator))
				postdominator = postdominator->get_immediate_reverse_dominator ();

			cfg->remove_branch (dyc<Branch_block> (bb), postdominator);
			DEBUG ("REMOVED BRANCH " << bb->ID << " NEAREST MARKED POSTDOMINATOR: " << postdominator->ID);
			CTS ("num_blocks_removed");
		}
	}

	// TODO: we have enough information to manipulate the BBs to based on the
	// CHIs which are still live.
}

void
DCE::run (CFG* cfg)
{
	DEBUG ("START DCE");
	marks.clear ();
	bb_marks.clear ();

	worklist = new SSA_def_list;
	this->cfg = cfg;

	mark_pass ();
	dump ();
	sweep_pass ();
	dump ();
}

void
DCE::dump()
{
	CHECK_DEBUG ();
	DEBUG ("DCE:");
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
		DEBUG (bb->ID << ": " << is_marked (bb));
}
