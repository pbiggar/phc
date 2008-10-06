
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/transpose_graph.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/topological_sort.hpp>

#include "process_ir/General.h"

#include "optimize/Basic_block.h"
#include "optimize/Address_taken.h"

#include "SSA.h"
#include "Phi.h"
#include "Dominance.h"
#include "optimize/Def_use.h"

using namespace MIR;
using namespace boost;

void
HSSA::convert_to_ssa_form (CFG* cfg)
{
	Address_taken* aliasing = new Address_taken ();
	aliasing->run (cfg);

	// Calculate dominance frontiers
	cfg->dominance = new Dominance (cfg);
	cfg->dominance->calculate_forward_dominance ();
	cfg->dominance->calculate_reverse_dominance ();
	cfg->dominance->dump ();

	// Build def-use web (we're not in SSA form, but this will do the job).
	cfg->duw = new Def_use_web ();
	cfg->duw->run (cfg);

	// Muchnick gives up at this point. We continue instead in Cooper/Torczon,
	// Section 9.3.3, with some minor changes. Since we dont have a list of
	// global names, we iterate through all blocks, rather than the blocks
	// corresponding to the variable names. 
	// TODO: get a list of global names, and convert to semi-pruned form
	
	// For an assignment to X in BB, add a PHI function for variable X in the
	// dominance frontier of BB.
	// TODO Abstract this.
	BB_list* worklist = cfg->get_all_bbs_top_down ();
	BB_list::iterator i = worklist->begin ();
	while (i != worklist->end ())
	{
		Basic_block* bb = *i;
		foreach (Basic_block* frontier, *bb->get_dominance_frontier ())
		{
			// Get defs (including phi node LHSs)
			VARIABLE_NAME_list* def_list = bb->get_pre_ssa_defs ();
			foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
				def_list->push_back (phi_lhs);

			bool def_added = false;
			foreach (VARIABLE_NAME* var_name, *def_list)
			{
				if (!frontier->has_phi_node (var_name))
				{
					frontier->add_phi_node (var_name);
					def_added = true;
				}
			}

			// This adds a new def, which requires us to iterate.
			if (def_added)
				worklist->push_back (frontier);
		}
		i++;
	}

	// Rename SSA variables
	SSA_renaming sr(cfg);
	sr.rename_vars (cfg->get_entry_bb ());


	// Check all variables are converted
	class Check_in_SSA : public Visitor
	{
		void pre_variable_name (VARIABLE_NAME* in)
		{
			assert (in->in_ssa);
		}
	};

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
			sb->statement->visit (new Check_in_SSA ());
	}


	cfg->consistency_check ();

	// TODO: needed?
	// Build def-use web
	cfg->duw = new Def_use_web ();
	cfg->duw->run (cfg);
}

void
HSSA::rebuild_ssa_form (CFG* cfg)
{
	cfg->clean ();
	cfg->consistency_check ();

	cfg->dominance = new Dominance (cfg);
	cfg->dominance->calculate_forward_dominance ();
	cfg->dominance->calculate_reverse_dominance ();

	cfg->duw = new Def_use_web ();
	cfg->duw->run (cfg);
}


void
HSSA::convert_out_of_ssa_form (CFG* cfg)
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss ())
		{
			BB_list* preds = bb->get_predecessors ();
			foreach (Rvalue* rval, *bb->get_phi_args (phi_lhs))
			{
				Assign_var* copy = new Assign_var (
					phi_lhs->clone (),
					false,
					rval->clone ());

				Statement_block* new_bb = new Statement_block (cfg, copy);

				cfg->insert_bb_between (cfg->get_edge (preds->front (), bb), new_bb);
				// TODO I'm not sure these are in the same order.
				// - the edge is included in the phi node, so use it.
				preds->pop_front ();

				// We avoid the critical edge problem because we have only 1
				// statement per block. Removing phi nodes adds a single block
				// along the necessary edge.
			}
		}
		bb->remove_phi_nodes ();
	}

	// TODO: at this point, we could do with a register-allocation style
	// interference graph to reduce the number of temporaries (aka
	// "registers") that we use in the generated code.
}


SSA_renaming::SSA_renaming (CFG* cfg)
: cfg(cfg)
, counter (0)
{
}

void
SSA_renaming::push_to_var_stack (VARIABLE_NAME* var_name, int version)
{
	var_stacks[*var_name->value].push (version);
}

int
SSA_renaming::read_var_stack (VARIABLE_NAME* var_name)
{
	// In traditional SSA, all variables are initialized at the start of a
	// function. Not so here (though it could be done that way).
	if (var_stacks[*var_name->value].size () == 0)
		push_to_var_stack (var_name, counter++);

	int result = var_stacks[*var_name->value].top();
	return result;
}

void
SSA_renaming::pop_var_stack (VARIABLE_NAME* var_name)
{
	var_stacks[*var_name->value].pop();
}

void 
SSA_renaming::create_new_ssa_name (VARIABLE_NAME* var_name)
{
	var_name->convert_to_ssa_name (counter);
	push_to_var_stack (var_name, counter++);
}

void
SSA_renaming::debug_var_stacks ()
{
	CHECK_DEBUG ();
	string name;
	stack<int> st;
	foreach (tie (name,st), var_stacks)
	{
		cdebug << name << ": (TOP) ";
		stack<int> copy (st);
		while (copy.size ())
		{
			cdebug << copy.top () << ", ";
			copy.pop ();
		}
		cdebug << "(BOTTOM)" << endl;
	}
}

void 
SSA_renaming::rename_vars (Basic_block* bb)
{
	DEBUG ("renaming vars in " << *bb->get_graphviz_label ());
	debug_var_stacks ();

	// Convert the phi nodes
	foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
	{
		DEBUG ("converting phi lhs");
		debug (phi_lhs);
//		create_new_ssa_name (phi_lhs);

		VARIABLE_NAME* clone = phi_lhs->clone ();
		create_new_ssa_name (clone);
		bb->update_phi_node (phi_lhs, clone);

		DEBUG (" to ");
		debug (phi_lhs);
	}

	// Rename local variable uses
	foreach (VARIABLE_NAME* use, *bb->get_pre_ssa_uses ())
	{
		DEBUG ("Converting use " << *use->get_ssa_var_name ());
		debug (use);
		use->convert_to_ssa_name (read_var_stack (use));
		DEBUG (" to ");
		debug (use);
	}

	// Create new names for defs
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
	{
		DEBUG ("Converting def " << *def->get_ssa_var_name ());
		debug (def);
		create_new_ssa_name (def);
		DEBUG (" to ");
		debug (def);
	}

	// Copy names to CFG successors (including names defined in
	// predecessor, which are not redefined here).
	foreach (Basic_block* succ, *bb->get_successors ())
		foreach (VARIABLE_NAME* phi_lhs, *succ->get_phi_lhss())
			succ->add_phi_arg (phi_lhs, read_var_stack (phi_lhs), cfg->get_edge (bb, succ));


	// Recurse down the dominator tree
	foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
		rename_vars (dominated);


	// Before going back up the tree, get rid of new variable names from
	// the stack, so the next node up sees its own names.
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
		pop_var_stack (def);
}
