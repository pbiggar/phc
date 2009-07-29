
#include <algorithm>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/transpose_graph.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/topological_sort.hpp>

#include <iostream>

#include "process_ir/General.h"
#include "process_mir/MIR_unparser.h"

#include "optimize/Basic_block.h"

#include "optimize/wpa/Whole_program.h"
#include "optimize/Def_use_web.h"

#include "Dominance.h"
#include "HSSA.h"
#include "Phi.h"
#include "SSA_ops.h"

using namespace MIR;
using namespace boost;
HSSA::HSSA (Whole_program* wp, CFG* cfg)
: wp (wp)
, cfg (cfg)
, counter (1)
{
}

void
HSSA::convert_to_hssa_form ()
{
	// Build (Non-SSA) Def Use Web
	DEBUG ("Calculating Def-use-web for SSA");
	cfg->duw = new Def_use_web (wp->def_use);
	cfg->duw->build_web (cfg, false);

	// Calculate Dominance Frontiers
	cfg->dominance = new Dominance (cfg);
	cfg->dominance->calculate_forward_dominance ();
	cfg->dominance->calculate_reverse_dominance ();

	// Insert Phi nodes (using dominance frontiers)
	insert_phi_nodes ();

	if (debugging_enabled)
		cfg->dump_graphviz (s("Pre-renaming"));

	// Rename variables to SSA versions
	rename_vars (cfg->get_entry_bb ());

	if (debugging_enabled)
		cfg->dump_graphviz (s("Post-renaming"));

	// update Def Use Web with SSA versions of variables and Phis
	cfg->duw->build_web(cfg, true);

//	cfg->duw->dump ();
	cfg->duw->ssa_consistency_check ();
	
}

void
HSSA::insert_phi_nodes ()
{
	BB_list* worklist = cfg->get_all_bbs_top_down ();
	BB_list::iterator i = worklist->begin ();
	while (i != worklist->end ())
	{
		Basic_block* bb = *i;
		foreach (Basic_block* frontier, *bb->get_dominance_frontier ())
		{
			// Get defs (including phis and chis)
			bool def_added = false;
			SSA_def_list* defs = new SSA_def_list;
			defs->push_back_all (cfg->duw->get_block_defs (bb));
		
			// phis add a def thats not in the DUW
			Set<SSA_name>* phidefs = bb->get_phi_lhss ();	
			
			foreach (SSA_name name, *phidefs)
			{
				SSA_def* phi = new SSA_def (bb, new SSA_name (name), SSA_PHI);
				defs->push_back (phi);				 
			}

			foreach (SSA_def* def, *defs)
			{
				if (!frontier->has_phi_node (*(def->name)))
				{
					frontier->add_phi_node (*(def->name));
					
					def_added = true;
				}
			}

			// This adds a new def, which requires us to iterate.
			if (def_added)
				worklist->push_back (frontier);
		}
		i++;
	}

}

void
HSSA::convert_out_of_ssa_form ()
{
	// There is no longer a need. We just drop the SSA web.
	
	cfg->duw = NULL;
	cfg->dump_graphviz (NULL);
}

/*
 * Renaming
 */
void
HSSA::push_to_var_stack (SSA_name* name)
{
	assert (name->get_version () == 0);
	var_stacks[name->get_name ()].push (counter);
	name->set_version (counter);
	counter++;
}

int
HSSA::read_var_stack (SSA_name* name)
{
	// In traditional SSA, all variables are initialized at the start of a
	// function. Not so here (though it could be done that way).

	// NAME gets an SSA version in push_to_var_stack, which changes the
	// indexing.
	
	SSA_name index = *name;
	if (var_stacks[index.get_name ()].size () == 0)
		push_to_var_stack (name);
	
	return var_stacks[index.get_name ()].top();
}

void
HSSA::pop_var_stack (SSA_name* name)
{
	if (var_stacks[name->get_name ()].size () > 0)
	{
		var_stacks[name->get_name ()].pop();
	}	
}

void 
HSSA::create_new_ssa_name (SSA_name* name)
{
	push_to_var_stack (name);
}

void
HSSA::debug_top_var_stack (SSA_name* var, string type)
{
	CHECK_DEBUG ();
	DEBUG(type << ": " << var->str () << "\n");
	if (var_stacks[var->get_name ()].size () == 0)
	{
		DEBUG ("var stack empty");
	}else
	{
		DEBUG ("TOP OF VAR STACK:" << var_stacks[var->get_name ()].top ());
	}
}

void 
HSSA::rename_vars (Basic_block* bb)
{
	// For each phi function in bb, rename lhs
	
	DEBUG ("BB:"<<bb->ID);
	foreach (SSA_name phi_lhs, *bb->get_phi_lhss())
	{
		debug_top_var_stack (&phi_lhs, "PHI");
		SSA_name clone = phi_lhs;
		
		create_new_ssa_name (&clone);
		debug_top_var_stack (&phi_lhs, "PHI");	
		bb->update_phi_node (phi_lhs, clone);
	}
	
	// Rename each use in bb
	foreach (SSA_name* use, *bb->cfg->duw->get_uses (bb))
	{
		use->set_version (read_var_stack (use));
	}	
	
	foreach (SSA_name* may_def, *bb->cfg->duw->get_may_defs (bb))
	{
		DEBUG("MAY-DEF: " << may_def->str ());
		create_new_ssa_name (may_def);
	}

	// Rename each def in bb	
       foreach (SSA_name* def, *bb->cfg->duw->get_defs (bb))
	{
		debug_top_var_stack (def,"DEF");
		create_new_ssa_name (def);
		debug_top_var_stack (def, "DEF");
	}	
	// Fill in successors' phi args	
	foreach (Basic_block* succ, *bb->get_successors ())
	{
		DEBUG("Filling in successors' phi args\n" << " SUCC:" << succ->ID);
		foreach (SSA_name phi_lhs, *succ->get_phi_lhss ())
		{	
			debug_top_var_stack (&phi_lhs, "PHI");
			if (var_stacks[phi_lhs.get_name ()].size () != 0) // No point if nothing on var stack
			{
				if (succ->has_phi_node (phi_lhs))
				{
					succ->add_phi_arg (phi_lhs, read_var_stack (&phi_lhs), cfg->get_edge (bb, succ));
				}
			}
		}
	}
	// Recurse down the dominator tree
	foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
		rename_vars (dominated);
	
	// Before going back up the tree, get rid of new variable names from
	// the stack, so the next node up sees its own names.
	SSA_name_list* defs_to_pop = new SSA_name_list;
	foreach (SSA_name phi_lhs, *bb->get_phi_lhss ())
	{
		defs_to_pop->push_back (&phi_lhs);
	}
	defs_to_pop->push_back_all (bb->cfg->duw->get_defs (bb));
	foreach (SSA_name* def, *defs_to_pop)
		pop_var_stack (def);
}
