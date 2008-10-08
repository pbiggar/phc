
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

using namespace MIR;
using namespace boost;

void
HSSA::convert_to_ssa_form ()
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
	// Virtual variables are used when converting C code to SSA. They deal with
	// a number of syntactic constructs:
	//		*p
	//		*(p+1)
	//		**p
	//		p->next
	//		a[i]
	//
	//	Aliases affect these constructs in various ways:
	//		a[i] -- aliases all elements of the array
	//		p->next -- p could be any struct, so p->next acceesses an abstract
	//						object, not a concrete one.
	//		*p -- can alias anything, really, including the above
	//		*(p+1) -- same as *p, but is intended to indicate it cant alias *p
	//		**p -- just a different syntactic construct, with the same idea.
	//
	//	PHP has different syntactic constructs:
	//		$a[$i]
	//		$$a
	//		$p->next
	//		$p->$f
	//
	//	but it suffers from a different problem: 'normal' syntactic constructs
	//	can have aliasing behaviour, based on the run-time is_ref field of the
	//	value. So some constructs may or may not have aliases:
	//		$p
	//	and some become 'super-aliasers':
	//		$a[$i]
	//		$$a
	//		$p->next
	//		$p->$f
	//
	//	which, as well as supporting the standard aliasing semantics, generally
	//	the same as in C, their value can turn out to be is_ref, which means it
	//	can alias a whole rake of other variables. For example:
	//		$$x = 10;
	//		Assume that $x is either "a" or "b", so it can alias either $a or $b.
	//		However, if $a or $b are is_ref, then the assignment to them is even
	//		more indirect.
	//
	// The good news is that the copy semantics means we can ignore the fact
	// that a variable isnt a storage location, per-se, but is instead a pointer
	// to a zval, and the very zval it points to can change. That doesnt really
	// bother us, because the semantics are assignment either way.
	//
	// So, returning to the HSSA algorithm:
	//		- What is an indirect variable?
	//			In C, there are syntactic constructs to tell us 'here be dragons'.
	//			Not so in PHP, so we have to either:
	//				- Be conservative, and assume everything is an alias.
	//				- Perform _some_ kind of alias analysis so that 'normal'
	//				variables aren't affected by this insanity.
	//
	//			At the end of the day, we can treat everything like an indirect
	//			variable if we need to.
	//
	//		- How do we name the virtual variables?
	//			In C, there is the structure of the addressing expression. We can
	//			use this in PHP too.
	//
	//		- So what gets a virtual variable?
	//			Any variable that might possibly be indirect:
	//				- anything in a Change-on-write set (this isnt that bad):
	//					- $x = $a[$i]; // $x isnt in a COW set after the assignment.
	//				- anything where is_ref is set
	//					- thats the same as the last one, since for is_ref to be set,
	//					the refcount must be 2.
	//				- abstract locations (which can refer to multiple places)
	//					- $a[$i]
	//					- $$a
	//					- $p->next
	//
	//		- What about super-aliasing?
	//			I dont know. We'll see where it goes. Hopefully nothing.
	//
	//
	//
	// 1) Assign virtual variables to indirect variables in the program
//	create_virtuals ();

	//	2)	Perform alias analysis and insert MU and CHI for all scalar and
	//		virtual variables.
	//
	//	Perform alias analysis. Anything which has only one alias (typically
	//	local variables) can be turned back to scalars.

//	Address_taken* aliasing = new Address_taken ();
//	aliasing->run (cfg);

	
	//	3) Insert PHIs using Cytron algorithm, including CHI as assignments
	//	-- simple

	// 4) Rename all scalar and virtual variables using Cytron algorithm
	// -- simple
	

	// We still have the explosion of MUs and CHIs, so these need to be
	// trimmed down.

	// Build def-use web (we're not in SSA form, but this will do the job).
	cfg->duw = new Def_use_web ();
	cfg->duw->run (cfg);





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

class Virtuals_creator : public Visit_once
{
public:
	map<string, VARIABLE_NAME*> virtuals;

	void create_virtual (Node* in)
	{
		assert (isa<Statement> (in) || isa <Expr> (in));

		stringstream ss;
		ss << "virt_" << unparse (in);
		string name = ss.str ();

		if (virtuals.find (name) == virtuals.end ())
		{
			virtuals[name] = new VARIABLE_NAME (s (name));
			DEBUG ("Creating virtual: " << name);
		}
	}
	
	void visit_entry_block (Entry_block*)
	{
		// TODO: entry nodes
	}

	void visit_empty_block (Empty_block*)
	{
		assert (0);
	}

	void visit_exit_block (Exit_block*) {}

	void visit_branch_block (Branch_block* bb)
	{
		create_virtual (bb->branch->variable_name);
	}


	void visit_statement_block (Statement_block* bb)
	{
		debug (bb->statement);
	}

	void visit_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
	{
		assert (0);
	}


	void visit_assign_array (Statement_block*, Assign_array* in)
	{
		create_virtual (new Array_access (in->lhs, in->index));
		create_virtual (in->rhs);
	}

	void visit_assign_field (Statement_block*, Assign_field *)
	{
		assert (0);
	}

	void visit_assign_var (Statement_block* bb, Assign_var* in)
	{
		create_virtual (in->lhs);
		visit_expr (bb, in->rhs);
	}

	void visit_assign_var_var (Statement_block*, Assign_var_var*)
	{
		assert (0);
	}

	void visit_eval_expr (Statement_block* bb, Eval_expr* in)
	{
		visit_expr (bb, in->expr);
	}

	void visit_foreach_end (Statement_block*, Foreach_end*)
	{
		assert (0);
	}

	void visit_foreach_next (Statement_block*, Foreach_next*)
	{
		assert (0);
	}

	void visit_foreach_reset (Statement_block*, Foreach_reset*)
	{
		assert (0);
	}

	void visit_global (Statement_block*, Global*)
	{
		// Even though this aliases, we dont need to do any renaming on it.
	}

	void visit_pre_op (Statement_block*, Pre_op*)
	{
		assert (0);
	}

	void visit_push_array (Statement_block*, Push_array*)
	{
		assert (0);
	}

	void visit_return (Statement_block*, Return*)
	{
		assert (0);
	}

	void visit_ssa_pre_op (Statement_block*, SSA_pre_op* in)
	{
		create_virtual (in->use);
		create_virtual (in->def);
	}

	void visit_static_declaration (Statement_block*, Static_declaration*)
	{
		assert (0);
	}

	void visit_throw (Statement_block*, Throw*)
	{
		assert (0);
	}

	void visit_try (Statement_block*, Try*)
	{
		assert (0);
	}

	void visit_unset (Statement_block*, Unset*)
	{
		assert (0);
	}

	/*
	 * Exprs
	 */
	void visit_array_access (Statement_block*, Array_access* in)
	{
		create_virtual (in);
	}

	void visit_bin_op (Statement_block*, Bin_op* in)
	{
		create_virtual (in->left);
		create_virtual (in->right);
	}

	void visit_cast (Statement_block*, Cast* in)
	{
		assert (0);
	}

	void visit_constant (Statement_block*, Constant* in)
	{
		assert (0);
	}

	void visit_field_access (Statement_block*, Field_access* in)
	{
		assert (0);
	}

	void visit_foreach_get_key (Statement_block*, Foreach_get_key* in)
	{
		assert (0);
	}

	void visit_foreach_get_val (Statement_block*, Foreach_get_val* in)
	{
		assert (0);
	}

	void visit_foreach_has_key (Statement_block*, Foreach_has_key* in)
	{
		assert (0);
	}

	void visit_instanceof (Statement_block*, Instanceof* in)
	{
		assert (0);
	}

	void visit_isset (Statement_block*, Isset* in)
	{
		assert (0);
	}

	void visit_method_invocation (Statement_block*, Method_invocation* in)
	{
		if (in->target)
			create_virtual (in->target);

		if (isa <Variable_method> (in->method_name))
			create_virtual (dyc<Variable_method> (in->method_name)->variable_name);

		foreach (Actual_parameter* ap, *in->actual_parameters)
		{
			if (isa<VARIABLE_NAME> (ap->rvalue))
				create_virtual (ap->rvalue);
		}
	}

	void visit_new (Statement_block*, New* in)
	{
		assert (0);
	}

	void visit_param_is_ref (Statement_block*, Param_is_ref* in)
	{
		assert (0);
	}

	void visit_real (Statement_block*, REAL* in)
	{
		assert (0);
	}

	void visit_unary_op (Statement_block*, Unary_op* in)
	{
		assert (0);
	}

	void visit_variable_name (Statement_block*, VARIABLE_NAME* in)
	{
		assert (0);
	}

	void visit_variable_variable (Statement_block*, Variable_variable* in)
	{
		assert (0);
	}
};

void
HSSA::create_virtuals ()
{
	Virtuals_creator vc;
	vc.run (cfg);
}
