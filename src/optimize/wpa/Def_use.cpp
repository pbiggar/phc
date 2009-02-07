/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 *
 * Def-use information.
 *
 * Gather the def-use information while the alias analysis is running.
 *
 */

#include "Def_use.h"

using namespace std;
using namespace boost;
using namespace MIR;

Def_use::Def_use (Whole_program* wp)
: WPA (wp)
{
}

void dump_set (Map<long, Set<Alias_name> >& map, long id, string set_name)
{
	if (map.has (id))
	{
		cdebug << id << ": " << set_name << " list: ";
		foreach (Alias_name name, map[id])
			cdebug << name.str() << ", ";
		cdebug << endl;
	}
	else
		cdebug << id << ": No " << set_name << " results" << endl;
}

void
Def_use::dump(Basic_block* bb)
{
	long id = bb->ID;

	// Print out the results for existing BBs (done this way so that IN and OUT
	// results are presented together).
	dump_set (ref_defs, bb->ID, "REF-DEF");
	dump_set (ref_uses, bb->ID, "REF-USE");
	dump_set (ref_may_defs, bb->ID, "REF-MAY-DEF");
	dump_set (val_defs, bb->ID, "VAL_DEF");
	dump_set (val_uses, bb->ID, "VAL_USE");
	dump_set (val_may_defs, bb->ID, "VAL_MAY_DEF");
}

/*
 * Kills
 */
void
Def_use::kill_by_copy (Basic_block* bb, Alias_name lhs)
{
	val_assignment (bb, lhs, DEFINITE);
}

void
Def_use::kill_by_ref (Basic_block* bb, Alias_name lhs)
{
	ref_assignment (bb, lhs, DEFINITE);
}

/* Simple assignments */

void
Def_use::assign_scalar (Basic_block* bb, Alias_name lhs, Literal* lit, certainty cert)
{
	val_assignment (bb, lhs, cert);
}

void
Def_use::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	val_assignment (bb, lhs, cert);
}

void
Def_use::assign_unknown (Basic_block* bb, Alias_name lhs, certainty cert)
{
	val_assignment (bb, lhs, cert);
}

void
Def_use::val_assignment (Basic_block* bb, Alias_name lhs, certainty cert)
{
	// In C terms, *x = ...;
	// This uses 'x';

	if (cert == DEFINITE)
		val_defs[bb->ID].insert (lhs);
	else if (cert == POSSIBLE)
		val_may_defs[bb->ID].insert (lhs);

	ref_uses[bb->ID].insert (lhs);
	
}

void
Def_use::ref_assignment (Basic_block* bb, Alias_name lhs, certainty cert)
{
	// Assignments by ref also change the value
	if (cert == DEFINITE)
	{
		ref_defs[bb->ID].insert (lhs);
		val_defs[bb->ID].insert (lhs);
	}
	else if (cert == POSSIBLE)
	{
		ref_may_defs[bb->ID].insert (lhs);
		val_may_defs[bb->ID].insert (lhs);
	}
}


/* Assignments with RHSs */
void
Def_use::assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	val_assignment (bb, lhs, cert);
	val_uses[bb->ID].insert (rhs);
}

void
Def_use::assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	ref_assignment (bb, lhs, cert);
	ref_uses[bb->ID].insert (rhs);
	val_uses[bb->ID].insert (rhs);
}


void
Def_use::record_use (Basic_block* bb, Alias_name use, certainty cert)
{
	// This is always by value (I think)
	val_uses[bb->ID].insert (use);
}



void
merge_into_func_sets (Basic_block* bb,
							Map<long, Set<Alias_name> >& bb_sets,
							Map<string, Set<Alias_name> >& func_sets)
{
	// TODO: what do we do about the ones which are out of scope? It's
	// probably safe to do nothing about them, as they won't be used later (I
	// think though that we would confuse them with a later function call).
	Set<Alias_name>& sets = bb_sets[bb->ID];
	func_sets[ST (bb)].insert (sets.begin(), sets.end());
}

void
Def_use::aggregate_results (Basic_block* bb)
{
	merge_into_func_sets (bb, ref_defs, func_ref_defs);
	merge_into_func_sets (bb, ref_uses, func_ref_uses);
	merge_into_func_sets (bb, ref_may_defs, func_ref_may_defs);
	merge_into_func_sets (bb, val_defs, func_val_defs);
	merge_into_func_sets (bb, val_uses, func_val_uses);
	merge_into_func_sets (bb, val_may_defs, func_val_may_defs);
}

// TODO: we could do with a 'close_scope' to trim results.

void
merge_from_callee (Basic_block* bb, CFG* callee_cfg,
						Map<long, Set<Alias_name> >& bb_vals,
						Map<string, Set<Alias_name> >& func_vals)
{
	Set<Alias_name>& callee_vals = func_vals[ST (callee_cfg->get_entry_bb ())];
	bb_vals[bb->ID].insert (callee_vals.begin (), callee_vals.end());
}

bool 
has_prefix (string prefix, Alias_name& name)
{
	return name.prefix == prefix;
}


void
remove_prefixed (Set<Alias_name>& set, string prefix)
{
	Set<Alias_name> to_remove;

	// Iterators gets killed by changing the set.
	foreach (Alias_name name, set)
		if (name.prefix == prefix)
			to_remove.insert (name);

	foreach (Alias_name name, to_remove)
		set.erase (name);
}

void
Def_use::backward_bind (Basic_block* context, CFG* callee_cfg)
{
	if (context == NULL)
		return;

	// The defs and uses from the callee represent the entire function.
	merge_from_callee (context, callee_cfg, ref_defs, func_ref_defs);
	merge_from_callee (context, callee_cfg, ref_uses, func_ref_uses);
	merge_from_callee (context, callee_cfg, ref_may_defs, func_ref_may_defs);

	merge_from_callee (context, callee_cfg, val_defs, func_val_defs);
	merge_from_callee (context, callee_cfg, val_uses, func_val_uses);
	merge_from_callee (context, callee_cfg, val_may_defs, func_val_may_defs);

	remove_prefixed (ref_defs[context->ID], CFG_ST (callee_cfg));
	remove_prefixed (ref_uses[context->ID], CFG_ST (callee_cfg));
	remove_prefixed (ref_may_defs[context->ID], CFG_ST (callee_cfg));

	remove_prefixed (val_defs[context->ID], CFG_ST (callee_cfg));
	remove_prefixed (val_uses[context->ID], CFG_ST (callee_cfg));
	remove_prefixed (val_may_defs[context->ID], CFG_ST (callee_cfg));
}


Alias_name_list*
Def_use::get_defs (Basic_block* bb)
{
	phc_TODO ();
/*	Alias_name_list* result = new Alias_name_list;

	foreach (Alias_name def, defs[bb->ID])
		result->push_back (new Alias_name (def));
	
	return result;*/
}

Alias_name_list*
Def_use::get_may_defs (Basic_block* bb)
{
	phc_TODO ();
/*	Alias_name_list* result = new Alias_name_list;

	foreach (Alias_name may_def, may_defs[bb->ID])
		result->push_back (new Alias_name (may_def));
	
	return result;*/
}

Alias_name_list*
Def_use::get_uses (Basic_block* bb)
{
	phc_TODO ();
/*	Alias_name_list* result = new Alias_name_list;

	foreach (Alias_name use, uses[bb->ID])
		result->push_back (new Alias_name (use));
	
	return result;*/
}
