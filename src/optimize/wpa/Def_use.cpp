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
	dump_set (defs, bb->ID, "DEF");
	dump_set (uses, bb->ID, "USE");
	dump_set (may_defs, bb->ID, "MAY_DEF");
}


void
Def_use::kill_value (Basic_block* bb, Alias_name lhs)
{
	assign_value (bb, lhs, lhs, DEFINITE);
}

void
Def_use::assign_scalar (Basic_block* bb, Alias_name lhs, Literal* lit, certainty cert)
{
	// It ignores the second LHS
	assign_value (bb, lhs, lhs, cert);
}


void
Def_use::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	assign_value (bb, lhs, lhs, cert);
}

void
Def_use::assign_unknown (Basic_block* bb, Alias_name lhs, certainty cert)
{
	assign_value (bb, lhs, lhs, cert);
}


void
Def_use::assign_value (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	if (cert == DEFINITE)
		defs[bb->ID].insert (lhs);
	else if (cert == POSSIBLE)
		may_defs[bb->ID].insert (lhs);
}


void
Def_use::record_use (Basic_block* bb, Alias_name use, certainty cert)
{
	uses[bb->ID].insert (use);
}


void
merge_into_func_sets (Basic_block* bb,
							Map<long, Set<Alias_name> >& bb_vals,
							Map<string, Set<Alias_name> >& func_vals)
{
	// TODO: what do we do about the ones which are out of scope? It's
	// probably safe to do nothing about them, as they won't be used later (I
	// think though that we would confuse them with a later function call).
	Set<Alias_name>& vals = bb_vals[bb->ID];
	func_vals[ST (bb)].insert (vals.begin(), vals.end());
}

void
Def_use::aggregate_results (Basic_block* bb)
{
	merge_into_func_sets (bb, defs, func_defs);
	merge_into_func_sets (bb, uses, func_uses);
	merge_into_func_sets (bb, may_defs, func_may_defs);
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
	// The defs and uses from the callee represent the entire function.
	merge_from_callee (context, callee_cfg, defs, func_defs);
	merge_from_callee (context, callee_cfg, uses, func_uses);
	merge_from_callee (context, callee_cfg, may_defs, func_may_defs);

	remove_prefixed (defs[context->ID], CFG_ST (callee_cfg));
	remove_prefixed (uses[context->ID], CFG_ST (callee_cfg));
	remove_prefixed (may_defs[context->ID], CFG_ST (callee_cfg));
}
