
#include "boost/tuple/tuple.hpp"

#include "process_ir/debug.h"

#include "Def_use_web.h"
#include "optimize/wpa/Def_use.h"

#include "wpa/Aliasing.h"


using namespace MIR;
using namespace std;
using namespace boost;

/*
* defs, uses, may_defs => maps of BB IDs to lists of SSA_names in that block
* named_defs, named_uses => maps of SSA_names to lists of SSA_defs/SSA_uses
* def_ops, use_ops => maps of BB IDs to lists of SSA_uses/SSA_defs in that block
*/


Def_use_web::Def_use_web (Def_use* du)
: du (du)
{
}

Def_use*
Def_use_web::get_def_use ()
{
	return du;
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
		// Need to clear these before we put new versions in.
		named_uses.clear ();
		named_defs.clear ();
		use_ops.clear ();
		def_ops.clear ();
		
		// Collect all new defs and uses created by the insertion of phi nodes.
		foreach (Basic_block* bb, *cfg->get_all_bbs ())
		{	
			DEBUG ("BBID: " << bb->ID);
			foreach (SSA_name phi_lhs, *get_phi_lhss (bb))
			{
				SSA_name* clone = new SSA_name (phi_lhs);
				phi_defs[bb->ID].push_back (clone);
				
				foreach (SSA_name* phi_arg, *get_phi_args (bb, phi_lhs))
					phi_uses[bb->ID].push_back (phi_arg);	
			}
		}
	}
	else
	{
		// Collect all uses, defs and may defs from the Def Use
		foreach (Basic_block* bb, *cfg->get_all_bbs ())
		{
			foreach (const Alias_name* name, *du->get_defs (bb))
				defs[bb->ID].push_back (new SSA_name (name->str ()));

			foreach (const Alias_name* name, *du->get_uses (bb))
				uses[bb->ID].push_back (new SSA_name (name->str ()));

			foreach (const Alias_name* name, *du->get_may_defs (bb))
			{
				may_defs[bb->ID].push_back (new SSA_name (name->str ()));
				uses[bb->ID].push_back (new SSA_name (name->str ()));	// Every may def needs a use
			}
		}
	}
	// Build all the ops
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		foreach (SSA_name* use, uses[bb->ID])
			named_uses[use->str ()].push_back (new SSA_use (bb, use, SSA_BB));

		foreach (SSA_name* def, defs[bb->ID])
			named_defs[def->str ()].push_back (new SSA_def (bb, def, SSA_BB));
		
		uses[bb->ID].push_back_all (&phi_uses[bb->ID]);
		defs[bb->ID].push_back_all (&phi_defs[bb->ID]);

		foreach (SSA_name* use, phi_uses[bb->ID])
			named_uses[use->str ()].push_back (new SSA_use (bb, use, SSA_PHI));

		foreach (SSA_name* def, phi_defs[bb->ID])
			named_defs[def->str ()].push_back (new SSA_def (bb, def, SSA_PHI));
		
		foreach (SSA_name* may_def, may_defs[bb->ID])
		{
			named_defs[may_def->str ()].push_back (new SSA_def (bb, may_def, SSA_CHI));
			named_uses[may_def->str ()].push_back (new SSA_use (
					bb,
					new SSA_name (*may_def),
					SSA_CHI));
		}

	}

	// Create the web
	std::string name;
	SSA_def_list& def_list = *(new SSA_def_list ());
	foreach (tie (name, def_list), named_defs)
	{
		foreach (SSA_def* def, def_list)
		{		
			def_ops[def->bb->ID].push_back (def);
		
			// Add to all uses
			foreach (SSA_use* use, named_uses[name])
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
			foreach (SSA_def* def, named_defs[name])
				def->aux_ops.push_back (use);
		}
	}
}



void
Def_use_web::dump ()
{
/*	CHECK_DEBUG ();

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
	foreach (SSA_name key, *named_defs.keys ())
	{
		cdebug << key.str () << ":\n";
		foreach (SSA_def* def, named_defs[key.str ()])
		{
			cdebug << "\t";
			def->dump ();
			cdebug << "\n";
		}
	}

	cdebug << "\n\nnamed_uses:\n";
	foreach (SSA_name key, *named_uses.keys ())
	{
		cdebug << key.str () << ":\n";
		foreach (SSA_use* use, named_uses[key.str ()])
		{
			cdebug << "\t";
			use->dump ();
			cdebug << "\n";
		}
	}


	TODO: dump:

	Map<long, Set<SSA_name> > phi_lhss;
	Map<edge_t, Phi_map> phi_rhss;

	Map<long, SSA_name_list> uses;
	Map<long, SSA_name_list> defs;
	Map<long, SSA_name_list> may_defs;

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
	std::string use;
	SSA_def_list def_list;
	foreach (tie (use, def_list), named_defs)
	{
		foreach (SSA_def* def, def_list)
			assert (def->name->get_version ());
	}
	
	std::string def;
	SSA_use_list use_list;
	foreach (tie (def, use_list), named_uses)
	{			
		foreach (SSA_use* use, use_list)
			assert (use->name->get_version () || use->type_flag == SSA_PHI); //Phi arguments can be zero versions (uninitialised)
			
	}


	foreach (tie (use, def_list), named_defs)
	{
		// Check that each use has 0 or 1 def.
		assert (def_list.size () < 2);

		// Check the dominance property (every use is dominated by its def)
		if (def_list.size () == 1)
		{
			Basic_block* def_bb = def_list.front ()->bb;

			foreach (SSA_use* ssa_use, named_uses[use])
			{
				DEBUG ("SSAUSE->BB: " << ssa_use->bb->ID << " DEF_BB " << def_bb->ID << " DEF: " << def_list.front ()->name->str ());
				assert (ssa_use->bb->is_dominated_by (def_bb) || 
					ssa_use->type_flag == SSA_PHI);		// Phi nodes don't need to be dominated by each of their arguments
			}
		}
	}
}


SSA_name_list*
Def_use_web::get_defs (Basic_block* bb)
{
	return &defs[bb->ID];
}

SSA_name_list*
Def_use_web::get_uses (Basic_block* bb)
{
	return &uses[bb->ID];
}

SSA_name_list*
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
Def_use_web::get_named_uses (SSA_name* name)
{
	return &named_uses[name->str ()];
}

SSA_def_list*
Def_use_web::get_named_defs (SSA_name* name)
{
	return &named_defs[name->str ()];
}

/*
 * SSA
 */

void
Def_use_web::copy_phi_nodes (Basic_block* source, Basic_block* dest)
{
	// Since a phi is an assignment, and variables can only be assigned to
	// once, DEST's PHIs cant exist in SOURCE.
	foreach (SSA_name phi_lhs, *get_phi_lhss (dest))
	{
		add_phi_node (source, phi_lhs);
	}
}


bool
Def_use_web::has_phi_node (Basic_block* bb, SSA_name phi_lhs)
{
	return phi_lhss[bb->ID].has (phi_lhs);
}

void
Def_use_web::add_phi_node (Basic_block* bb, SSA_name phi_lhs)
{
	assert (!has_phi_node (bb, phi_lhs));

	phi_lhss[bb->ID].insert (phi_lhs);
	
	assert (has_phi_node (bb, phi_lhs));
}

void
Def_use_web::add_phi_arg (Basic_block* bb, SSA_name phi_lhs, int version, Edge* edge)
{
	// phi_lhs doesnt have to be in SSA, since it will be updated later using
	// update_phi_node, if it is not.
	assert (has_phi_node (bb, phi_lhs));
	DEBUG("ADDING PHI ARG V" << version << " for " << phi_lhs.str ());
	SSA_name arg = phi_lhs; // copy
	arg.set_version (version);
	set_phi_arg_for_edge (edge, phi_lhs, arg);
}

void
Def_use_web::remove_phi_nodes (Basic_block* bb)
{
	foreach (Edge* pred, *bb->get_predecessor_edges ())
		phi_rhss[pred].clear ();

	phi_lhss[bb->ID].clear ();
}

void
Def_use_web::remove_phi_node (Basic_block* bb, SSA_name phi_lhs)
{
	assert (has_phi_node (bb, phi_lhs));

	foreach (Edge* pred, *bb->get_predecessor_edges ())
		phi_rhss[pred].erase (phi_lhs);

	// TODO: are we trying to remove the pointer, when we have a different
	// pointer to the same thing?
	phi_lhss[bb->ID].erase (phi_lhs);

	assert (!has_phi_node (bb, phi_lhs));
}


void
Def_use_web::update_phi_node (Basic_block* bb, SSA_name phi_lhs, SSA_name new_phi_lhs)
{
	// TODO: too complicated for the mechanical conversion we're doing now. Its easier
	// If a phi_lhs changes into SSA form, its indexing will change. So we must
	// re-insert its args with the new index.

	assert (phi_lhs.get_version () == 0);							
	assert (new_phi_lhs.get_version () != 0);
	assert (phi_lhs.get_name() == new_phi_lhs.get_name ());
	add_phi_node (bb, new_phi_lhs);

	foreach (Edge* pred, *bb->get_predecessor_edges ())
	{
		// Not all nodes have their phi argument added yet
		if (phi_rhss[pred].has (phi_lhs))
			set_phi_arg_for_edge (
					pred,
					new_phi_lhs,
					get_phi_arg_for_edge (pred, phi_lhs));
	}

	remove_phi_node (bb,phi_lhs);
}


SSA_name_list*
Def_use_web::get_phi_args (Basic_block* bb, SSA_name phi_lhs)
{
	SSA_name_list* result = new SSA_name_list;

	foreach (Edge* pred, *bb->get_predecessor_edges ())
		result->push_back (new SSA_name (get_phi_arg_for_edge (pred, phi_lhs)));
		
	return result;
}

Set<SSA_name>*
Def_use_web::get_phi_lhss (Basic_block* bb)
{
	// Return a clone, since we sometimes like to update the list
	// (but dont call ->clone, since we dont want clones of the variables).
	return phi_lhss[bb->ID].set_union (new Set<SSA_name>);
}

SSA_name
Def_use_web::get_phi_arg_for_edge (Edge* edge, SSA_name phi_lhs)
{
	return phi_rhss[edge][phi_lhs];
}

void
Def_use_web::set_phi_arg_for_edge (Edge* edge, SSA_name phi_lhs, SSA_name arg)
{
	DEBUG("SETTING " << arg.str () << "V " << arg.get_version () << " AS PHI ARG FOR " << phi_lhs.str () << "V " << phi_lhs.get_version ());
	phi_rhss[edge][phi_lhs] = arg;
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
	SSA_name phi_lhs;
	SSA_name arg;
	foreach (tie (phi_lhs, arg), phi_rhss[dest])
	{
		source->get_target()->set_phi_arg_for_edge (source, phi_lhs, arg);
	}
}
