#include "optimize/ssa/HSSA.h"
#include "optimize/ssa/Phi.h"
#include "optimize/ssa/SSA_ops.h"
#include "optimize/wpa/Aliasing.h"
#include "optimize/wpa/Whole_program.h"

#include "optimize/Basic_block.h"
#include "optimize/Def_use_web.h"

#include "ESSA.h"

using namespace MIR;

ESSA::ESSA(Whole_program* wp, CFG* cfg) : HSSA(wp, cfg) {
}

void ESSA::insert_nodes() {
  // Insert sigma nodes only once for conditional branches.
  insert_sigma_nodes();

  // Always try to insert phi nodes.
  insert_phi_nodes();
}

bool ESSA::insert_sigma_nodes() {
  bool changed = false;

  foreach (Basic_block *bb, *cfg->get_all_bbs()) {
    if (Branch_block *br = dynamic_cast<Branch_block *>(bb)) {
      // Obtain where the variables was defined.
      SSA_def *def = find_variable(br, br->branch->variable_name);

      // May have legitimate cases where the def is unknown.
      if (!def)
        continue;

      SSA_name_list *sigmas = collect_vars(def->bb);

      // Adding sigmas for collected uses on the branch block.
      foreach (SSA_name *add, *sigmas) {
        // Add the sigma node.
        if (!br->has_sigma_node(*add)) {
          br->add_sigma_node(*add);
          changed = true;
        }
      }
    }
  }

  return changed;
}

SSA_def *ESSA::find_variable(Basic_block *bb, VARIABLE_NAME *var_name) {
  Context* cx = Context::non_contextual(bb);
  string ns = cx->symtable_name();

  Index_node name(ns, *var_name->value);
  string starred_name = name.get_starred_name()->str();

  SSA_use *use = NULL;
  foreach (SSA_use *tmp, *cfg->duw->get_block_uses(bb)) {
    // Not interested in phi and sigma nodes.
    if (tmp->type_flag == SSA_PHI || tmp->type_flag == SSI_SIGMA)
      continue;

    string s = tmp->name->get_name();
    if (s == starred_name) {
      // Found the use.
      use = tmp;
      break;
    }
  }

  if (!use)
    return NULL;

  SSA_def_list *defs = use->get_defs();

  // The def-use may be outdated and a use may have more than 1 def.
  // If this is the case, let's skip it.
  if (defs->size() != 1)
    return NULL;

  return defs->front();
}

SSA_name_list *ESSA::collect_vars(Basic_block *bb) {
  SSA_name_list *names = new SSA_name_list;

  Statement_block *stmt = dynamic_cast<Statement_block *>(bb);
  if (!stmt)
    return names;

  // TODO: Should we handle casts here?
  // Add sigma for variables referenced by the casts.

  foreach (SSA_use *use, *cfg->duw->get_block_uses(stmt)) {
    // Ugly hack to see if the use is a starred index node.
    if (!use->name->is_starred())
      continue;

    // Checking the type of the used variable.
    Context *ctx = Context::non_contextual(use->bb);
    Index_node *in = use->name->reverse();
    VARIABLE_NAME *var = new VARIABLE_NAME(s(in->index));

    const Abstract_value *absval = wp->get_abstract_value(ctx, R_OUT, var);

    // If a variable's type is not a string, it's not a source of problem.
    if (!absval->types->has("string"))
      continue;

    names->push_back(use->name);

    // Find its variable names alias.
    cReference_list *refs = wp->aliasing->get_references(ctx, R_OUT, in, PTG_ALL);
    foreach (const Reference *ref, *refs) {
      Index_node *starred = ref->index->get_starred_name();
      names->push_back(new SSA_name(starred->str()));
    }
  }

  return names;
}
