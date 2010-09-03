
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
, check_ssi (false)
, counter (1)
{
}

void
HSSA::convert_to_hssa_form ()
{
	DEBUG ("Calculating Def-use-web for SSA/SSI");

	// Build (Non-SSA) Def Use Web
	cfg->duw = new Def_use_web (wp->def_use);
	cfg->duw->build_web (cfg, false);

	// Calculate Dominance Frontiers
	cfg->dominance = new Dominance (cfg);
	cfg->dominance->calculate_forward_dominance ();
	cfg->dominance->calculate_reverse_dominance ();

	// Generic interface to insert Phi/Sigma nodes.
	insert_nodes ();

	if (debugging_enabled)
		cfg->dump_graphviz (s("Pre-renaming"));

	// Rename variables to SSA versions
	rename_vars (cfg->get_entry_bb ());

	// update Def Use Web with SSA/SSI versions of variables
	// including phis and sigmas.
	cfg->duw->build_web(cfg, true);
	
	if (debugging_enabled)
		cfg->dump_graphviz (s("Post-renaming"));

	// cfg->duw->dump ();
	cfg->duw->ssa_consistency_check();

	if (check_ssi)
		cfg->duw->ssi_consistency_check ();

	DEBUG ("Finish building SSA/SSI");
}

void
HSSA::convert_out_of_hssa_form ()
{
	// There is no longer a need. We just drop the SSA web.
	
	cfg->duw = NULL;
	cfg->dump_graphviz (NULL);
}

void HSSA::insert_nodes() {
  insert_phi_nodes();
}

/*
 * Insertion of phi nodes.
 */
bool HSSA::insert_phi_nodes() {
  bool changed = false;

  BB_list *worklist = cfg->get_all_bbs_top_down();
  BB_list::iterator i = worklist->begin();

  while (i != worklist->end()) {
    // Analyze basic block bb.
    Basic_block *bb = *i;

    // Find basic block's dominance frontier.
    BB_list *frontier_list = bb->get_dominance_frontier();

    // Collect defs only if there is at least one basic blocks
    // in the dominance frontier.
    if (frontier_list->size() > 0) {
      // Get defs (including phis and chis)
      SSA_def_list *defs = new SSA_def_list;
      defs->push_back_all(cfg->duw->get_block_defs(bb));

      // phis add a def that is not in the DUW
      foreach (SSA_name phi_lhs, *bb->get_phi_lhss()) {
        SSA_def *phi = new SSA_def(bb, new SSA_name(phi_lhs), SSA_PHI);
        defs->push_back(phi);
      }

      // Sigmas also adds several defs that are not in the DUW.
      // Check if the current block add sigma nodes.
      foreach (SSA_name sigma_rhs, *bb->get_sigma_rhss()) {
        // We should add sigma_lhs instead of sigma_rhs, but since they
        // have no version yet they are exactly the same.
        SSA_def *sigma = new SSA_def(bb, new SSA_name(sigma_rhs), SSI_SIGMA);
        defs->push_back(sigma);
      }

      // Find all immediate predecessors of basic block bb to check if any
      // defines a sigma function. Add a def for each.
      // (they'll be later merged by a phi function).
      foreach (Basic_block *pred, *bb->get_predecessors()) {
        // Set each sigma use into a definition in the current basic block.
        foreach (SSA_name sigma_rhs, *pred->get_sigma_rhss()) {
          // We should add sigma_lhs instead of sigma_rhs, but since they
          // have no version yet they are exactly the same.
          SSA_def *sigma = new SSA_def(bb, new SSA_name(sigma_rhs), SSA_BB);
          defs->push_back(sigma);
        }
      }

      // Add the phi node for each basic block in the dominance frontier.
      // If isn't already added.
      foreach (Basic_block *frontier, *frontier_list) {
        bool def_added = false;

        foreach (SSA_def *def, *defs) {
          if (!frontier->has_phi_node(*def->name)) {
            frontier->add_phi_node(*def->name);
            def_added = true;
          }
        }

        // This adds a new def, which requires us to iterate.
        if (def_added) {
          worklist->push_back(frontier);
          changed = true;
        }
      }
    }

    i++;
  }

  return changed;
}

/*
 * Renaming.
 */
void
HSSA::rename_vars (Basic_block* bb)
{
  DEBUG ("BB[" << bb->ID << "]: " << *bb->get_graphviz_label() << " (Before)");

  foreach (Edge *pred_edge, *bb->get_predecessor_edges()) {
    Basic_block *pred = pred_edge->get_source();
    foreach (SSA_name sigma_rhs, *pred->get_sigma_rhss()) {
      // Create a new definition for sigma.
      SSA_name clone = sigma_rhs;
      create_new_ssa_name (&clone);

      // Acquire the sigma variable for this edge.
      pred->set_sigma_arg_for_edge(pred_edge, sigma_rhs, clone);

      // Condition: pred has sigma and bb has phi.
      // Correct phi arg with proper sigma version.
      foreach (SSA_name phi_lhs, *bb->get_phi_lhss()) {
        if (phi_lhs.get_name() == clone.get_name())
          bb->add_phi_arg(phi_lhs, clone.get_version(), pred_edge);
      }
    }
  }

  // For each phi function in bb, rename lhs
  foreach (SSA_name phi_lhs, *bb->get_phi_lhss()) {
    debug_top_var_stack(&phi_lhs, "PHI");
    SSA_name clone = phi_lhs;

    create_new_ssa_name(&clone);
    debug_top_var_stack(&phi_lhs, "PHI");
    bb->update_phi_node(phi_lhs, clone);
  }

  // Rename each use in bb
  foreach (SSA_name *use, *bb->cfg->duw->get_uses(bb)) {
    use->set_version(read_var_stack(use));
  }

  foreach(SSA_name *may_def, *bb->cfg->duw->get_may_defs(bb)) {
    DEBUG("MAY-DEF: " << may_def->str());
    create_new_ssa_name(may_def);
  }

  // Rename each def in bb
  foreach (SSA_name *def, *bb->cfg->duw->get_defs(bb)) {
    debug_top_var_stack(def, "DEF");
    create_new_ssa_name(def);
    debug_top_var_stack(def, "DEF");
  }

  // Fix sigmas here.
  foreach (SSA_name sigma_rhs, *bb->get_sigma_rhss()) {
    SSA_name new_sigma_rhs = sigma_rhs;
    new_sigma_rhs.set_version(read_var_stack(&new_sigma_rhs));

    bb->update_sigma_node(sigma_rhs, new_sigma_rhs);
  }

  // Fill in successors' phi args
  foreach (Basic_block *succ, *bb->get_successors()) {
    DEBUG("Filling in successors' phi args\n" << " SUCC:" << succ->ID);
    foreach (SSA_name phi_lhs, *succ->get_phi_lhss()) {
      debug_top_var_stack(&phi_lhs, "PHI");

      // Condition: bb has sigma and succ has phi.
      // We shouldn't add a phi argument if we don't know which sigma value to use.
      bool add = true;
      foreach (SSA_name sigma_rhs, *bb->get_sigma_rhss()) {
        if (phi_lhs.get_name() == sigma_rhs.get_name()) {
          add = false;
          break;
        }
      }

      if (add) {
        // No point if nothing on var stack
        if (var_stacks[phi_lhs.get_name ()].size() != 0) {
          // Unnecessary? succ->get_phi_lhss will return only nodes with phis.
          phc_optimization_assertion(succ->has_phi_node(phi_lhs));

          succ->add_phi_arg(phi_lhs, read_var_stack(&phi_lhs), cfg->get_edge(bb, succ));
        }
      }
    }
  }

  // Recurse down the dominator tree
  foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
    rename_vars (dominated);

  DEBUG ("BB[" << bb->ID << "]: " << *bb->get_graphviz_label() << " (After)");

  // Before going back up the tree, get rid of new variable names from
  // the stack, so the next node up sees its own names.
  SSA_name_list* defs_to_pop = new SSA_name_list;

  foreach (SSA_name phi_lhs, *bb->get_phi_lhss()) {
    defs_to_pop->push_back (new SSA_name(phi_lhs));
  }

  // TODO: Eventually remove the DEBUGs

  DEBUG ("Popping Var stack of: " << bb->ID );
  defs_to_pop->push_back_all (bb->cfg->duw->get_defs (bb));
  defs_to_pop->push_back_all (bb->cfg->duw->get_may_defs (bb));

  // Removing the sigma def.
  foreach (Basic_block *pred, *bb->get_predecessors()) {
    foreach (SSA_name sigma_rhs, *pred->get_sigma_rhss())
      defs_to_pop->push_back (new SSA_name(sigma_rhs));
  }

  // Popping all defs.
  foreach (SSA_name* def, *defs_to_pop)
  {
    if (var_stacks[def->get_name ()].size () > 0)
      DEBUG ("Initial Top Var Stack: " << var_stacks[def->get_name ()].top ());

    pop_var_stack (def);

    if (var_stacks[def->get_name ()].size () > 0)
      DEBUG ("Top Var Stack: " << var_stacks[def->get_name ()].top ());
  }
}

void
HSSA::push_to_var_stack (SSA_name* name)
{
	//assert (name->get_version () == 0);
	var_stacks[name->get_name ()].push (counter);
	name->set_version (counter);
	DEBUG ("Pushed " << counter << " to var stack for " << name->str ());
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
