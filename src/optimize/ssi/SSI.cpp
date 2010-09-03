#include "optimize/ssa/HSSA.h"
#include "optimize/ssa/Phi.h"
#include "optimize/ssa/SSA_ops.h"

#include "optimize/Basic_block.h"
#include "optimize/Def_use_web.h"

#include "SSI.h"

SSI::SSI(Whole_program* wp, CFG* cfg) : HSSA(wp, cfg) {
  check_ssi = true;
}

void SSI::insert_nodes() {
  bool changed = false;

  // Always try to insert phi nodes.
  insert_phi_nodes();

  // First round may insert sigma nodes even if no phi nodes are inserted.
  changed = insert_sigma_nodes();

  // Insert phi and sigma nodes until a fix-point is reached.
  while (changed) {
    changed = insert_phi_nodes();
    if (changed)
      changed = insert_sigma_nodes();
  }
}

bool SSI::insert_sigma_nodes() {
  bool changed = false;

  BB_list *worklist = cfg->get_all_bbs_bottom_up();
  BB_list::iterator i = worklist->begin();

  while (i != worklist->end()) {
    // Analyze basic block bb.
    Basic_block *bb = *i;

    // Find basic block's dominance frontier.
    BB_list *rev_frontier_list = bb->get_reverse_dominance_frontier();

    // Collect uses only if there is at least one basic blocks
    // in the reverse dominance frontier.
    if (rev_frontier_list->size() > 0) {
      // Get all uses.
      SSA_use_list *uses = cfg->duw->get_block_uses(bb);

      // Sigma can also add uses.
      foreach (SSA_name sigma_rhs, *bb->get_sigma_rhss())
        uses->push_back(new SSA_use(bb, new SSA_name(sigma_rhs), SSA_BB));

      // Add a sigma node for each basic block in the dominance frontier for
      // each use, unless it is already present.
      foreach (Basic_block *rev_frontier, *rev_frontier_list) {
        bool use_added = false;

        foreach (SSA_use *use, *uses) {
          if (!rev_frontier->has_sigma_node(*use->name)) {
            rev_frontier->add_sigma_node(*use->name);
            use_added = true;
          }
        }

        // This adds a new use, which requires us to iterate.
        if (use_added) {
          worklist->push_back(rev_frontier);
          changed = true;
        }
      }
    }

    i++;
  }

  return changed;
}
