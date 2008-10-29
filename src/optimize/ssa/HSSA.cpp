
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

#include "HSSA.h"
#include "Phi.h"
#include "Dominance.h"
#include "process_mir/MIR_unparser.h"
#include "optimize/Def_use.h"
#include "SSA_ops.h"

using namespace MIR;
using namespace boost;


/*
 * Chow96: "Effective Representation of Aliases and Indirect Memory Operations
 * in SSA Form"; Fred Chow, Sun Chan, Shin-Ming Liu, Raymond Lo, Mark Streich;
 * CC 96.
 */

void
HSSA::convert_to_ssa_form ()
{
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
HSSA::rebuild_ssa_form ()
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
HSSA::convert_out_of_ssa_form ()
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		// Drop the chi and mu args
		bb->remove_chi_nodes ();
		bb->remove_mu_nodes ();
		bb->remove_virtual_phis ();

		// There are two problems when coming out of SSA form:
		//		1.) variable-variables: i_0 is not the same as i
		//		2.) CHI nodes update variable indices, but when you drop the chi
		//		nodes, you lose the relationship between them. Renumbering is
		//		possible, I suppose, but not as good as:
		//
		//	The solution is to drop the indices when coming out of SSA form.
		//	(Warning, this could hide bugs unfortunately). The only real problem
		//	is to make sure that variables with overlapping live ranges are not
		//	created. This could happen in copy-propagation, value numbering, or
		//	PRE. I suspect the latter two can be avoided by using the HSSA
		//	algorithms. For copy-propagation, I'll just have to be careful.

		// TODO: Add a check that there aren't overlapping live ranges.
		foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss ())
		{
			foreach (Edge* pred, *bb->get_predecessor_edges ())
			{
				Rvalue* rval = bb->get_phi_arg_for_edge (pred, phi_lhs);
				if (isa<VARIABLE_NAME> (rval))
				{
					VARIABLE_NAME* var = dyc<VARIABLE_NAME> (rval);

					// We've dropped the indices, so make sure the varaibles are
					// equal (if they arent, perhaps if we've added copy
					// propagation, we should add an assignment).
					assert (*var->value == *phi_lhs->value);
					continue;
				}

				Assign_var* copy = new Assign_var (
					phi_lhs->clone (),
					false,
					rval->clone ());

				Statement_block* new_bb = new Statement_block (cfg, copy);

				cfg->insert_bb_between (pred, new_bb);

				// We avoid the critical edge problem because we have only 1
				// statement per block. Removing phi nodes adds a single block
				// along the necessary edge.
			}
		}
		bb->remove_phi_nodes ();

	}


	// Drop variable indices 
	rebuild_ssa_form (); // we only care about DUW
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		foreach (VARIABLE_NAME* var, *cfg->duw->get_real_uses (bb))
			var->drop_ssa_index();

		foreach (VARIABLE_NAME* var, *cfg->duw->get_real_defs (bb))
			var->drop_ssa_index();
	}


	

	// TODO: at this point, we could do with a register-allocation style
	// interference graph to reduce the number of temporaries (aka
	// "registers") that we use in the generated code.
}


/*
 * How to convert into HSSA form algorithm 2 from "Effective Representation
 * of Aliases and Indirect Memory Operations in SSA Form", by Chow et al.
 *
 * 1) Assign virtual variables to indirect variables in the program
 *
 * 2)	Perform alias analysis and insert MU and CHI for all scalar and
 *		virtual variables
 *
 * 3) Insert PHIs using Cytron algorithm, including CHI as assignments
 *
 * 4) Rename all scalar and virtual variables using Cytron algorithm
 *
 *
 * We ignore steps 5, 6, 7 and 8. 5 and 6 create zero versions in order to
 * reduce the memory usage of the implementation. That doesnt bother us (at
 * least for now). Steps 7 and 8 perform the global value numbering. While we
 * do wish to have GVN, they also convert it into HSSA form, which actually
 * isnt that interesting, as the only real advantage is how compact it is, and
 * we dont care about that (for now).
 *
 * 5) Simultaneously:
 *		a)	Perform DCE, including on PHIs and CHIs, using Cytron algorithm
 *		b)	Perform steps 1 and 2 of algorithm 1 (Compute Zero Versions), to set
 *			the HasRealOcc flag for all variable versions. These steps are:
 *				czv1)	Initialize flag HasRealOcc for each variable version created
 *						by SSA renaming to false.
 *				czv2)	Pass over the program. On visiting a real occurrence, set
 *						the HasRealOcc flag for the variable version to true.
 *
 *	6)	Performs steps 3, 4 and 5 of CZV algorithm to set variable versions to
 *		0. These steps are:
 *		czv3)	For each program varaible, create NonZeroPhiList and init to
 *				empty.
 *		czv4)	Iterate through all variable versions:
 *				a)	If HasRealOcc is false, and is defined by CHI, set version to 0
 *				b) If HasRealOcc is false, and is defined by PHI:
 *					-	If the version of one of the operands is 0, set version to 0
 *					-	Else if HasRealOcc flag of all operand is set to true, set
 *						HasRealOcc to true
 *					-	Else add version to NonZeroPhiList for the variable
 *		czv5)	For each program variable, iterate until its NonZeroPhiList no
 *				longer changes:
 *				a)	For each version in NonZeroPhiList
 *					-	If the version of one of the operands in 0, set version to 0
 *						and remove from NonZeroPhiList
 *					-	Else if the HasRealOcc flag of all operands is true, set
 *						HasRealOcc to true and remove from NonZeroPhiList
 *
 *	7)	Hash a unique value number and create the corresponding hash table VAR
 *		node for each scalar and virtual variable version that are determined to
 *		be live in Step 5a.
 *
 *	8) Conduct a pre-order traversal of the dominator tree of the control flow
 *		graph of the program and apply global value numbering to the code in
 *		each basic_block:
 *		a)	Hash expression trees bottom-up into the hash-table, searching for
 *			any existing matching entry before creating each new value number
 *			and entry.  At a VAR node, use the node created in step 7 for that
 *			variable version.
 *		b)	For two IVAR nodes to match, two conditions must be satisfied:
 *			1) Their address expressions have the same value number, and
 *			2) the versions of their virtual variables are either the same, or
 *				are separated by definitions that do not alias with the IVAR.
 *		c)	For each assignment statement, including PHI and CHI, represent its
 *			lhs by making the statement point to the VAR or IVAR for direct and
 *			indirect assignments respectively. Also make the VAR or IVAR node
 *			point back to its defining statement.
 *		d)	Update all PHI, MU and CHI operands and results to make them refer
 *			to entries in the hash-table.
 */
HSSA::HSSA (CFG* cfg)
: cfg(cfg)
{
}



void
HSSA::convert_to_hssa_form ()
{
	// A particular version of a virtual-variable can have only 1 value,
	// maintaining the single-value per defintion rule. If you have
	//		v(*p) = 5;
	//	and then
	//		$x = v(*p);
	//	then 5 can be propagated to $x.
	//
	// The chi's make note of the new version so that this property is
	// maintained, and the mu's extend the live ranges of the definition so that
	// assignments arent killed when they are still in use.
	//
	// A virtual variable represents an 'indirect variable', which can refer to
	// many memory locations:
	//
	//		in C:
	//			*p
	//			*(p+1)
	//			**p
	//			p->next
	//			a[i]
	//
	//		in PHP:
	//			$a[$i]
	//			$$a
	//			$p->next
	//			$p->$f
	//
	//
	//
	// The virtual variables do not remove the requirement for a mu/chi variable
	// at each load/store, for each variable in the alias set at that point.

	// However, virtual-variables can also be used to condense alias sets.
	// Chow96, Fig 5, shows that you can represent multiple indirect variables
	// with a single virtual variable. In fact, we can use a single virtual
	// variable for every indirect variable in the program. But I dont think we
	// will.


	//	PHP has a different and "new" problem: 'normal' syntactic constructs can
	//	have aliasing behaviour, based on the run-time is_ref field of the value.
	//	So some constructs may or may not have aliases:
	//		$p
	//	and some may become 'super-aliases':
	//		$a[$i]
	//		$$a
	//		$p->next
	//		$p->$f
	//
	//	The 'super-aliases' can have is_ref set in their zval, which means they
	//	can can alias a whole rake of other variables. For example:
	//		$$x = 10;
	//		Assume that $x is either "a" or "b", so it can alias either $a or $b.
	//		However, if $a or $b are is_ref, then the assignment to them is even
	//		more indirect.
	//
	//	Super-aliases are tough: conservatively, they could mean that each
	//	variable needs a virtual-variable (we can still use virtual variables,
	//	since assignments to them maintain the 'one-version-one-value' property).
	//	We would need to perform analysis or this insanity would spill
	//	into 'normal variables'.
	//
	//	We can't really name the set after its real or virtual variable though.
	//	It could be a def of $a or $b, not just $p. So the alias set is {$p, $a,
	//	$b), and you cant just have a variable like v^p to represent it.
	//
	
	

	// So, returning to the HSSA algorithm:
	//		- How do we name the virtual variables?
	//			In C, there is the structure of the addressing expression. We can
	//			use this in PHP too. We dont use the versions of the variables
	//			though.
	//
	//		- So what gets a virtual variable?
	//			Any expression which is not a 'real' variable, but can have a value
	//			(aka abstract locations)
	//					- $a[$i]
	//					- $$a
	//					- $p->next
	//					- $p->$f
	//
	//		- What about super-aliasing?
	//			I dont know. We'll see where it goes. Hopefully nothing (doubt it).



	// 1) Assign virtual variables to indirect variables in the program
	// Do it on the fly.

	//	2)	Perform alias analysis and insert MU and CHI for all scalar and
	//		virtual variables.

	Address_taken* aliasing = new Address_taken ();
	aliasing->run (cfg);

	// Build existing def-use web
	cfg->duw = new Def_use_web ();
	cfg->duw->run (cfg);

	// For any variable in the alias set, add a may_use/may_def of all other
	// symbols in the alias set.
	add_mu_and_chi_nodes (aliasing->aliases);

//	assert (*cfg->get_entry_bb ()->method->signature->method_name->value != "simpleucall");

	
	//	3) Insert PHIs using Cytron algorithm, including CHI as assignments


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
			// Get defs (including phis and chis)
			VARIABLE_NAME_list* def_list = bb->get_pre_ssa_defs ();
			def_list->push_back_all (bb->get_phi_lhss ());
			def_list->push_back_all (bb->get_chi_lhss ());


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


	// 4) Rename all scalar and virtual variables using Cytron algorithm

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


	// TODO: Zero versioning is actually useful, so add steps 5 and 6. There
	// is not necessarily a need to combine zero versioning with GVN.
}



// Given the alias set, all for every use, add a mu of all aliased variables,
// and for every def, add a chi.
void
HSSA::add_mu_and_chi_nodes (Set* aliases)
{
	// TODO
	assert (!aliases->full);

	// Means we might be able to use it for alias analysis?
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		foreach (VARIABLE_NAME* use, *bb->get_pre_ssa_uses ())
			if (aliases->has (use))
				foreach (VARIABLE_NAME* alias, *aliases)
					bb->add_mu_node (alias);

		VARIABLE_NAME_list* defs = new VARIABLE_NAME_list;
		defs->push_back_all (bb->get_pre_ssa_defs ());
		defs->push_back_all (bb->cfg->duw->get_may_defs (bb));
		foreach (VARIABLE_NAME* def, *defs)
			if (aliases->has (def))
				foreach (VARIABLE_NAME* alias, *aliases)
					if (!alias->equals (def))
						bb->add_chi_node (alias);
	}
}
