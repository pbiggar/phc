
#include "boost/tuple/tuple.hpp"

#include "process_ir/debug.h"

#include "Def_use_web.h"
#include "optimize/wpa/Def_use.h"
#include "Var_set.h"

#include "wpa/Aliasing.h"


using namespace MIR;
using namespace std;
using namespace boost;


/*
 * SSA-web. 
 *
 * Use the SSA-web (which doesnt actually rely on SSA form, nor is
 * it built during it) both for getting into SSA form, and for creating the
 * SSA web.
 */


Def_use_web::Def_use_web (Def_use* du)
: du (du)
{
}

void
Def_use_web::build_web (CFG* cfg, bool update)
{

	// TODO:  Need to think about may_defs, to what extent, if any, do we need them represented in the DUW?

	// If we're updating the web with SSA variable versions, then defs and uses will
	// exist here and not need to be retrieved, i.e. named_uses/defs and def/use_ops just need to be updated.
	// Otherwise, we get the information from the def_use
	if (update) 
	{
		named_uses.clear ();
		named_defs.clear ();
		use_ops.clear ();
		def_ops.clear ();
	}
	else
	{
		foreach (Basic_block* bb, *cfg->get_all_bbs ())
		{
			defs[bb->ID].push_back_all (du->get_defs (bb));
			uses[bb->ID].push_back_all (du->get_uses (bb));
			may_defs [bb->ID].push_back_all (du->get_may_defs (bb));
		}
	}
	// Build all the ops
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		foreach (Alias_name* use, uses[bb->ID])
			named_uses[*use].push_back (new SSA_use (bb, use, SSA_BB));

		foreach (Alias_name* def, defs[bb->ID])
			named_defs[*def].push_back (new SSA_def (bb, def, SSA_BB));

/*		foreach (Alias_name* may_def, may_defs[bb->ID])
		{
			named_defs[*may_def].push_back (new SSA_def (bb, may_def, SSA_CHI));
			named_uses[*may_def].push_back (new SSA_use (
					bb,
					new Alias_name (*may_def),
					SSA_CHI));
		}
*/	}

	// Create the web
	Alias_name name;
	SSA_def_list& def_list = *(new SSA_def_list ());
	foreach (tie (name, def_list), named_defs)
	{
		foreach (SSA_def* def, def_list)
		{
			def_ops[def->bb->ID].push_back (def);

			// Add to all uses
			foreach (SSA_use* use, named_uses[*def->name])
				use->aux_ops.push_back (def);
		}
	}

	SSA_use_list& use_list = *(new SSA_use_list ());
	foreach (tie (name, use_list), named_uses)
	{
		foreach (SSA_use* use, use_list)
		{
			use_ops[use->bb->ID].push_back (use);

			// Add to all uses
			foreach (SSA_def* def, named_defs[*use->name])
				def->aux_ops.push_back (use);
		}
	}
}



// TODO: CHIs are not created for the parameters to a method call. They
// clearly should be.

// TODO:
// There is a special problem that occurs when you have two indirect
// assignments in the same statement. Suppose you have:
//
//		$x = my_func ($y);
//
//	Then you have to add CHIs for the aliases of $y AND for the aliases of
//	$x. However, the CHIs for the variables which alias $x do not occur at
//	the same time as the variables which alias $y. Instead, $y's aliases
//	should occur after the method invocation, and $x's aliases should occur
//	after the assignment to $x. $x is in the first set, but not in the
//	second. Anything which aliases both $y and $x gets 2 CHIs. $y will get
//	2 CHIs.
//
//	So:
//		$x0 = 5;
//		$x2 = my_func ($y0);
//		$x1 = CHI ($x0); // METHOD
//		$y1 = CHI ($y0); // METHOD
//		$y2 = CHI ($y1); // ASSIGNMENT
//
//	Some interesting notes:
//		- There is no use of $x1.
//		- This problem only occurs when there can be > 1 assignment, which
//		can only occur in assignments from method invocations.
//		- The same variable can get given a CHI from each of a method's
//		parameters, but that is only 1 CHI overall.
//		- There can only be 1 or 2 CHIs, not more (see above).
//		- If we were to use zero versions, the first chi would have a zero
//		version, since it has no real use.
//		- This is only really important for getting the numbering right.
//		Anywhere that uses phis would get them all.
//
//
//
// Some possible solutions:
//		Associate CHIs with other definitions, maybe each def has a list of
//		maydefs. But there is no def in the function call to associate it
//		with, though I think one could safely be added (the MU would ensure
//		that it is not overwritten).
//
//		Allow multiple CHIs in the CHI list. If there is more than 1 of the
//		same name, they are assumed to be in the same order in which they
//		occur. I believe that the only variable which will only occur once
//		in the variable on the RHS.
//		 - but what about when we have small alias sets? Then we dont really
//		 know which is which.
//		 - besides, keeping track of that seems very buggy
//
// XXX: I like this one best, I think.
//		Have two CHI lists, one for 'mid' statement, one for
//		'post-statement'. Aliases of assignments go in the latter. Aliases
//		due to the call go in the former.
//
//	I think this will also solve the problem of 'vanishing globals'. In the
//	case of:
//		global $x;
//		$x = 5;
//
//	The global statement is remove because $x_0 is not used. However, $x = 5
//	is a must_def of $x_0. We can model it as a may-def however, giving it a
//	CHI in the mid-part, and the CHI in the post-statement part gives it the
//	new value.
//
//	The global statement will not in fact be solved by this. If there were
//	an extra statement, $x = 8 after $x = 5, then $x = 5 would be kept live
//	by this 'Early CHI'.
//
//	How about each assignment to an alias gets a MU of the variables in the
//	statement which created the alias.



void
Def_use_web::dump ()
{
	CHECK_DEBUG ();

	cdebug << "def_ops:\n";
	foreach (long key, *def_ops.keys ())
	{
		cdebug << key << ":\n";
		foreach (SSA_def* def, def_ops[key])
		{
			cdebug << "\t";
			def->dump ();
			cdebug << "\n";
		}

	}

	cdebug << "\n\nuse_ops:\n";
	foreach (long key, *use_ops.keys ())
	{
		cdebug << key << ":\n";
		foreach (SSA_use* use, use_ops[key])
		{
			cdebug << "\t";
			use->dump ();
			cdebug << "\n";
		}
	}

	cdebug << "\n\nnamed_defs:\n";
	foreach (Alias_name key, *named_defs.keys ())
	{
		cdebug << key.str () << ":\n";
		foreach (SSA_def* def, named_defs[key])
		{
			cdebug << "\t";
			def->dump ();
			cdebug << "\n";
		}
	}

	cdebug << "\n\nnamed_uses:\n";
	foreach (Alias_name key, *named_uses.keys ())
	{
		cdebug << key.str () << ":\n";
		foreach (SSA_use* use, named_uses[key])
		{
			cdebug << "\t";
			use->dump ();
			cdebug << "\n";
		}
	}

/*
	TODO: dump:

	Map<long, Var_set> phi_lhss;
	Map<edge_t, Phi_map> phi_rhss;

	Map<long, Alias_name_list> uses;
	Map<long, Alias_name_list> defs;
	Map<long, Alias_name_list> may_defs;

*/

}

void
Def_use_web::ssa_consistency_check ()
{
	// TODO: a lot of stuff isnt in SSA, but we don't want to break everything with a commit
	

	// There isnt much that will help here. I'll implement it if its buggy.
	// Check that named defs are correctly named
	// Check that blocked defs are in the right block.
	// Check that all the defs for a use contains the use
	// and vice-versa

	// Check that each key is in SSA form
	Alias_name use;
	SSA_def_list def_list;
	foreach (tie (use, def_list), named_defs)
	{
		assert (use.ssa_version);
		foreach (SSA_def* def, def_list)
			assert (def->name->ssa_version);
	}
	
	Alias_name def;
	SSA_use_list use_list;
	foreach (tie (def, use_list), named_uses)
	{
		assert (def.ssa_version);
		foreach (SSA_use* use, use_list)
			assert (use->name->ssa_version);
	}


	foreach (tie (use, def_list), named_defs)
	{
		// Check that each use has 0 or 1 def.
		assert (def_list.size () < 2);


		// TODO: Fails on the following if the section on line 66 isn't commented out because may defs are in both named_uses and named_defs, 
		// and is_dominated_by () doesn't account for self dominance.  Not sure if is_dominated_by ()
		// needs to be changed (probably should be anyway, seems to make sense that a block would dominate itself),
		// because I think we can just stop considering may_defs when building the web (they're a subset of defs anyway)

		// Check the dominance property (every use is dominated by its def)
		if (def_list.size () == 1)
		{
			Basic_block* def_bb = def_list.front()->bb;

			foreach (SSA_use* ssa_use, named_uses[use])
			{
				DEBUG("SSAUSE: " << ssa_use->name->str () << "DEF: " << def_list.front ()->name->str () << " BBID: " << def_bb->ID );
				assert (ssa_use->bb->is_dominated_by (def_bb));
			}
		}
	}
}


Alias_name_list*
Def_use_web::get_defs (Basic_block* bb)
{
	return &defs[bb->ID];
}

Alias_name_list*
Def_use_web::get_uses (Basic_block* bb)
{
	return &uses[bb->ID];
}

Alias_name_list*
Def_use_web::get_may_defs (Basic_block* bb)
{
	return &may_defs[bb->ID];
}


SSA_use_list*
Def_use_web::get_block_uses (Basic_block* bb)
{
	return &use_ops[bb->ID];
}

SSA_def_list*
Def_use_web::get_block_defs (Basic_block* bb)
{
	return &def_ops[bb->ID];
}

SSA_use_list*
Def_use_web::get_named_uses (Alias_name* name)
{
	return &named_uses[*name];
}

SSA_def_list*
Def_use_web::get_named_defs (Alias_name* name)
{
	return &named_defs[*name];
}

/*
 * SSA
 */

void
Def_use_web::copy_phi_nodes (Basic_block* source, Basic_block* dest)
{
	// Since a phi is an assignment, and variables can only be assigned to
	// once, DEST's PHIs cant exist in SOURCE.
	foreach (Alias_name phi_lhs, *get_phi_lhss (dest))
	{
		add_phi_node (source, phi_lhs);
	}
}


bool
Def_use_web::has_phi_node (Basic_block* bb, Alias_name phi_lhs)
{
	return phi_lhss[bb->ID].has (phi_lhs);
}

void
Def_use_web::add_phi_node (Basic_block* bb, Alias_name phi_lhs)
{
	assert (!has_phi_node (bb, phi_lhs));

	phi_lhss[bb->ID].insert (phi_lhs);
	
	assert (has_phi_node (bb, phi_lhs));
}

void
Def_use_web::add_phi_arg (Basic_block* bb, Alias_name phi_lhs, int version, Edge* edge)
{
	// phi_lhs doesnt have to be in SSA, since it will be updated later using
	// update_phi_node, if it is not.
	assert (has_phi_node (bb, phi_lhs));
	DEBUG("ADDING PHI ARG V"<<version<<" for "<<phi_lhs.name);
	Alias_name arg = phi_lhs; // copy
	arg.set_version (version);
	set_phi_arg_for_edge (edge, phi_lhs, arg);
}

void
Def_use_web::remove_phi_nodes (Basic_block* bb)
{
	foreach (Edge* pred, *bb->get_predecessor_edges ())
		phi_rhss[pred->edge].clear ();

	phi_lhss[bb->ID].clear ();
}

void
Def_use_web::remove_phi_node (Basic_block* bb, Alias_name phi_lhs)
{
	assert (has_phi_node (bb, phi_lhs));

	foreach (Edge* pred, *bb->get_predecessor_edges ())
		phi_rhss[pred->edge].erase (phi_lhs);

	// TODO: are we trying to remove the pointer, when we have a different
	// pointer to the same thing?
	phi_lhss[bb->ID].erase (phi_lhs);

	assert (!has_phi_node (bb, phi_lhs));
}


void
Def_use_web::update_phi_node (Basic_block* bb, Alias_name phi_lhs, Alias_name new_phi_lhs)
{
	// TODO: too complicated for the mechanical conversion we're doing now. Its easier
	// If a phi_lhs changes into SSA form, its indexing will change. So we must
	// re-insert its args with the new index.

	assert (phi_lhs.ssa_version == 0);							
	assert (new_phi_lhs.ssa_version != 0);
	assert (phi_lhs.name == new_phi_lhs.name);
	add_phi_node (bb, new_phi_lhs);

	foreach (Edge* pred, *bb->get_predecessor_edges ())
	{
		// Not all nodes have their phi argument added yet
		if (phi_rhss[pred->edge].has (phi_lhs))
			set_phi_arg_for_edge (
					pred,
					new_phi_lhs,
					get_phi_arg_for_edge (pred, phi_lhs));
	}

	remove_phi_node (bb,phi_lhs);
}


Alias_name_list*
Def_use_web::get_phi_args (Basic_block* bb, Alias_name phi_lhs)
{
	Alias_name_list* result = new Alias_name_list;

	foreach (Edge* pred, *bb->get_predecessor_edges ())
		result->push_back (new Alias_name (get_phi_arg_for_edge (pred, phi_lhs)));
		
	return result;
}

Var_set*
Def_use_web::get_phi_lhss (Basic_block* bb)
{
	// Return a clone, since we sometimes like to update the list
	// (but dont call ->clone, since we dont want clones of the variables).
	return phi_lhss[bb->ID].set_union (new Var_set);
}

Alias_name
Def_use_web::get_phi_arg_for_edge (Edge* edge, Alias_name phi_lhs)
{
	return phi_rhss[edge->edge][phi_lhs];
}

void
Def_use_web::set_phi_arg_for_edge (Edge* edge, Alias_name phi_lhs, Alias_name arg)
{
	DEBUG("SETTING "<<arg.name<<"V "<<arg.ssa_version<<" AS PHI ARG FOR "<<phi_lhs.name<<"V "<<phi_lhs.ssa_version);
	phi_rhss[edge->edge][phi_lhs] = arg;
}

void
Def_use_web::copy_phi_map (Edge* source, Edge* dest)
{
	// The target of either edge may have changed, so use the keys of other's
	// phi_map.
	
	// It should all work out in the end, and will be verified by
	// consistency_check.
	
	// They're not required to have the same target, only that this.target has
	// all of other.target's phi_lhss (which must be guaranteed by the caller).
	Alias_name phi_lhs;
	Alias_name arg;
	foreach (tie (phi_lhs, arg), phi_rhss[dest->edge])
	{
		source->get_target()->set_phi_arg_for_edge (source, phi_lhs, arg);
	}
}




