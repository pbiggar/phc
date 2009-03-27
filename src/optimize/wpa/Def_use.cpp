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
#include "Points_to.h"

using namespace std;
using namespace boost;
using namespace MIR;

Def_use::Def_use (Whole_program* wp)
: WPA (wp)
{
}


bool
Def_use::equals (WPA* wpa)
{
	Def_use* other = dyc<Def_use> (wpa);
	return true
		&& this->ref_defs.equals (&other->ref_defs)
		&& this->ref_uses.equals (&other->ref_uses)
		&& this->ref_may_defs.equals (&other->ref_may_defs)
		&& this->val_defs.equals (&other->val_defs)
		&& this->val_uses.equals (&other->val_uses)
		&& this->val_may_defs.equals (&other->val_may_defs)
		&& this->ref_defs.equals (&other->ref_defs)
		&& this->ref_uses.equals (&other->ref_uses)
		&& this->ref_may_defs.equals (&other->ref_may_defs)
		&& this->summary_val_defs.equals (&other->summary_val_defs)
		&& this->summary_val_uses.equals (&other->summary_val_uses)
		&& this->summary_val_may_defs.equals (&other->summary_val_may_defs);
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
Def_use::dump(Basic_block* bb, string comment)
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
Def_use::kill_value (Basic_block* bb, Index_node* lhs)
{
	val_assignment (bb, lhs->name(), DEFINITE);
}

void
Def_use::kill_reference (Basic_block* bb, Index_node* lhs)
{
	ref_assignment (bb, lhs->name(), DEFINITE);
}

/* Simple assignments */

void
Def_use::val_assignment (Basic_block* bb, Alias_name lhs, certainty cert)
{
	DEBUG ("def (val): " << lhs.str());
	DEBUG ("use (ref): " << lhs.str());

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
	DEBUG ("def (ref): " << lhs.str());
	DEBUG ("def (val): " << lhs.str());

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
Def_use::set_scalar (Basic_block* bb, Value_node* storage, Abstract_value* val)
{
	// TODO: I think we dont need this
//	val_assignment (bb, storage->name(), DEFINITE);
}

void
Def_use::set_storage (Basic_block* bb, Storage_node* storage, Types types)
{
	// TODO: I think we dont need this
//	val_assignment (bb, storage->name(), DEFINITE);
}

void
Def_use::assign_value (Basic_block* bb, Index_node* lhs, Storage_node* storage_name, certainty cert)
{
	val_assignment (bb, lhs->name(), cert);
}

void
Def_use::create_reference (Basic_block* bb, Index_node* lhs, Index_node* rhs, certainty cert)
{
	DEBUG ("use (ref): " << rhs->name().str());
	DEBUG ("use (val): " << rhs->name().str());

	ref_assignment (bb, lhs->name(), cert);
	ref_uses[bb->ID].insert (rhs->name());
	val_uses[bb->ID].insert (rhs->name());
}


void
Def_use::record_use (Basic_block* bb, Index_node* use, certainty cert)
{
	DEBUG ("use (val): " << use->name().str());

	// This is always by value (I think)
	val_uses[bb->ID].insert (use->name());
}


bool 
in_scope (Basic_block* bb, Alias_name& name)
{
	return name.prefix == ST (bb);
}

void
merge_into_function_summary (Basic_block* bb,
									  Map<long, Set<Alias_name> >& bb_sets,
									  Set<Alias_name>& summary)
{
	foreach (Alias_name name, bb_sets[bb->ID])
		if (!in_scope (bb, name))
			summary.insert (name);
}

void
merge_into_exit_bb (Basic_block* bb,
						  Map<long, Set<Alias_name> >& defs,
						  Map<long, Set<Alias_name> >& uses)
{
	foreach (Alias_name name, defs[bb->ID])
		if (!in_scope (bb, name))
			uses[bb->cfg->get_exit_bb()->ID].insert (name);
}

void
Def_use::aggregate_results (Basic_block* bb)
{
	// All defs/uses which are out of scope must be recorded in the function
	// summary.
	merge_into_function_summary (bb, ref_defs, summary_ref_defs[ST (bb)]);
	merge_into_function_summary (bb, ref_uses, summary_ref_uses[ST (bb)]);
	merge_into_function_summary (bb, ref_may_defs, summary_ref_may_defs[ST (bb)]);

	merge_into_function_summary (bb, val_defs, summary_val_defs[ST (bb)]);
	merge_into_function_summary (bb, val_uses, summary_val_uses[ST (bb)]);
	merge_into_function_summary (bb, val_may_defs, summary_val_may_defs[ST (bb)]);


	// The exit block must "use" all out-of-scope defs, or they'll be killed
	// later.
	merge_into_exit_bb (bb, ref_defs, ref_uses);
	merge_into_exit_bb (bb, ref_may_defs, ref_uses);

	merge_into_exit_bb (bb, val_defs, val_uses);
	merge_into_exit_bb (bb, val_may_defs, val_uses);
}

void
merge_from_callee (Basic_block* caller, Basic_block* callee,
						Map<long, Set<Alias_name> >& bb_sets,
						Map<string, Set<Alias_name> >& callee_sets)

{
	Set<Alias_name>& callee_set = callee_sets[ST(callee)];
	bb_sets[caller->ID].insert (callee_set.begin (), callee_set.end());
}

void
Def_use::backward_bind (Basic_block* caller, Exit_block* exit)
{
	if (caller == NULL)
	{
		// TODO: in __MAIN__, mark everything as unused except _SESSION (and
		// everything it can reach!).
		return;
	}

	long ID = exit->ID;

	// The defs and uses from the callee represent the entire function.
	merge_from_callee (caller, exit, ref_defs, summary_ref_defs);
	merge_from_callee (caller, exit, ref_uses, summary_ref_uses);
	merge_from_callee (caller, exit, ref_may_defs, summary_ref_may_defs);

	merge_from_callee (caller, exit, val_defs, summary_val_defs);
	merge_from_callee (caller, exit, val_uses, summary_val_uses);
	merge_from_callee (caller, exit, val_may_defs, summary_val_may_defs);
}

string prefix (string, string);

Alias_name_list*
Def_use::get_defs (Basic_block* bb)
{
	Alias_name_list* result = new Alias_name_list;

	foreach (Alias_name def, val_defs[bb->ID])
	{
		def.name = prefix (def.name, "*");
		result->push_back (new Alias_name (def));
	}

	foreach (Alias_name def, ref_defs[bb->ID])
		result->push_back (new Alias_name (def));
	
	return result;
}

Alias_name_list*
Def_use::get_may_defs (Basic_block* bb)
{
	Alias_name_list* result = new Alias_name_list;

	foreach (Alias_name def, val_may_defs[bb->ID])
	{
		def.name = prefix (def.name, "*");
		result->push_back (new Alias_name (def));
	}

	foreach (Alias_name def, ref_may_defs[bb->ID])
		result->push_back (new Alias_name (def));
	
	return result;
}

Alias_name_list*
Def_use::get_uses (Basic_block* bb)
{
	Alias_name_list* result = new Alias_name_list;

	foreach (Alias_name use, val_uses[bb->ID])
	{
		use.name = prefix (use.name, "*");
		result->push_back (new Alias_name (use));
	}

	foreach (Alias_name use, ref_uses[bb->ID])
		result->push_back (new Alias_name (use));
	
	return result;
}
