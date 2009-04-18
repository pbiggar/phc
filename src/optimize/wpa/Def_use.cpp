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

void
Def_use::init (Context outer)
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

		&& this->summary_ref_defs.equals (&other->summary_ref_defs)
		&& this->summary_ref_uses.equals (&other->summary_ref_uses)
		&& this->summary_ref_may_defs.equals (&other->summary_ref_may_defs)

		&& this->summary_val_defs.equals (&other->summary_val_defs)
		&& this->summary_val_uses.equals (&other->summary_val_uses)
		&& this->summary_val_may_defs.equals (&other->summary_val_may_defs)
		;
}


void dump_set (Map<Context, Set<Alias_name> >& map, Context cx, string set_name)
{
	if (map.has (cx))
	{
		cdebug << cx << ": " << set_name << " list: ";
		foreach (Alias_name name, map[cx])
			cdebug << name.str() << ", ";
		cdebug << endl;
	}
	else
		cdebug << cx << ": No " << set_name << " results" << endl;
}

void
Def_use::dump (Context cx, string comment)
{
	// Print out the results for existing BBs (done this way so that IN and OUT
	// results are presented together).
	dump_set (ref_defs, cx, "REF-DEF");
	dump_set (ref_uses, cx, "REF-USE");
	dump_set (ref_may_defs, cx, "REF-MAY-DEF");
	dump_set (val_defs, cx, "VAL_DEF");
	dump_set (val_uses, cx, "VAL_USE");
	dump_set (val_may_defs, cx, "VAL_MAY_DEF");
}

/*
 * Kills
 */
void
Def_use::kill_value (Context cx, Index_node* lhs)
{
	val_assignment (cx, lhs->name(), DEFINITE);
}

void
Def_use::kill_reference (Context cx, Index_node* lhs)
{
	ref_assignment (cx, lhs->name(), DEFINITE);
}

/* Simple assignments */

void
Def_use::val_assignment (Context cx, Alias_name lhs, certainty cert)
{
	DEBUG ("def (val): " << lhs.str());
	DEBUG ("use (ref): " << lhs.str());

	// In C terms, *x = ...;
	// This uses 'x';

	if (cert == DEFINITE)
		val_defs[cx].insert (lhs);
	else if (cert == POSSIBLE)
		val_may_defs[cx].insert (lhs);

	ref_uses[cx].insert (lhs);
	
}

void
Def_use::ref_assignment (Context cx, Alias_name lhs, certainty cert)
{
	DEBUG ("def (ref): " << lhs.str());
	DEBUG ("def (val): " << lhs.str());

	// Assignments by ref also change the value
	if (cert == DEFINITE)
	{
		ref_defs[cx].insert (lhs);
		val_defs[cx].insert (lhs);
	}
	else if (cert == POSSIBLE)
	{
		ref_may_defs[cx].insert (lhs);
		val_may_defs[cx].insert (lhs);
	}
}


/* Assignments with RHSs */
void
Def_use::set_scalar (Context cx, Value_node* storage, Abstract_value* val)
{
	// TODO: I think we dont need this
//	val_assignment (bb, storage->name(), DEFINITE);
}

void
Def_use::set_storage (Context cx, Storage_node* storage, Types types)
{
	// TODO: I think we dont need this
//	val_assignment (bb, storage->name(), DEFINITE);
}

void
Def_use::assign_value (Context cx, Index_node* lhs, Storage_node* storage_name, certainty cert)
{
	val_assignment (cx, lhs->name(), cert);
}

void
Def_use::create_reference (Context cx, Index_node* lhs, Index_node* rhs, certainty cert)
{
	DEBUG ("use (ref): " << rhs->name().str());
	DEBUG ("use (val): " << rhs->name().str());

	ref_assignment (cx, lhs->name(), cert);
	ref_uses[cx].insert (rhs->name());
	val_uses[cx].insert (rhs->name());
}


void
Def_use::record_use (Context cx, Index_node* use, certainty cert)
{
	DEBUG ("use (val): " << use->name().str());

	// This is always by value (I think)
	val_uses[cx].insert (use->name());
}


bool 
in_scope (Context cx, Alias_name& name)
{
	// Index_node alias_names put the name of the symtable as the prefix.
	return name.prefix == cx.symtable_node ()->storage;
}

void
merge_into_function_summary (Context cx,
									  Map<Context, Set<Alias_name> >& cx_sets,
									  Set<Alias_name>& summary)
{
	foreach (Alias_name name, cx_sets[cx])
		if (!in_scope (cx, name))
			summary.insert (name);
}

void
merge_into_exit_bb (Context cx,
						  Map<Context, Set<Alias_name> >& defs,
						  Map<Context, Set<Alias_name> >& uses)
{
	Context exit_cx = Context::as_peer (cx, cx.get_bb()->cfg->get_exit_bb());
	foreach (Alias_name name, defs[cx])
		if (!in_scope (cx, name))
			uses[exit_cx].insert (name);
}

void
Def_use::aggregate_results (Context cx)
{
	Alias_name name = cx.symtable_name ();

	// All defs/uses which are out of scope must be recorded in the function
	// summary.
	merge_into_function_summary (cx, ref_defs, summary_ref_defs [name]);
	merge_into_function_summary (cx, ref_uses, summary_ref_uses [name]);
	merge_into_function_summary (cx, ref_may_defs, summary_ref_may_defs [name]);

	merge_into_function_summary (cx, val_defs, summary_val_defs [name]);
	merge_into_function_summary (cx, val_uses, summary_val_uses [name]);
	merge_into_function_summary (cx, val_may_defs, summary_val_may_defs [name]);


	// The exit block must "use" all out-of-scope defs, or they'll be killed
	// later.
	merge_into_exit_bb (cx, ref_defs, ref_uses);
	merge_into_exit_bb (cx, ref_may_defs, ref_uses);

	merge_into_exit_bb (cx, val_defs, val_uses);
	merge_into_exit_bb (cx, val_may_defs, val_uses);
}

Map<Context, Set<Alias_name> >
merge_context (Map<Context, Set<Alias_name> >& in_map)
{
	Map<Context, Set<Alias_name> > result;

	Context cx;
	Set<Alias_name> s; // refs must be initialized
	Set<Alias_name>& set = s;
	foreach (tie (cx, set), in_map)
	{
		Context new_cx = cx.get_non_contextual ();

		foreach (Alias_name an, set)
			result [new_cx].insert (an.switch_context (cx, new_cx));
	}
	in_map.clear ();

	return result;
}

void
Def_use::merge_contexts ()
{
	// TODO: fix storage_nodes in summary_*

	ref_defs = merge_context (ref_defs);
	ref_uses = merge_context (ref_uses);
	ref_may_defs = merge_context (ref_may_defs);

	val_defs = merge_context (val_defs);
	val_uses = merge_context (val_uses);
	val_may_defs = merge_context (val_may_defs);
}

void
merge_from_callee (Context caller, Context callee,
						Map<Context, Set<Alias_name> >& cx_sets,
						Map<Alias_name, Set<Alias_name> >& callee_sets)

{
	Set<Alias_name>& callee_set = callee_sets[callee.symtable_node ()->name()];
	cx_sets[caller].insert (callee_set.begin (), callee_set.end());
}




void
Def_use::backward_bind (Context caller, Context exit)
{
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
	Context cx = Context::non_contextual (bb);

	foreach (Alias_name def, val_defs[cx])
	{
		def.name = prefix (def.name, "*");
		result->push_back (new Alias_name (def));
	}

	foreach (Alias_name def, ref_defs[cx])
		result->push_back (new Alias_name (def));
	
	return result;
}

Alias_name_list*
Def_use::get_may_defs (Basic_block* bb)
{
	Alias_name_list* result = new Alias_name_list;
	Context cx = Context::non_contextual (bb);

	foreach (Alias_name def, val_may_defs[cx])
	{
		def.name = prefix (def.name, "*");
		result->push_back (new Alias_name (def));
	}

	foreach (Alias_name def, ref_may_defs[cx])
		result->push_back (new Alias_name (def));
	
	return result;
}

Alias_name_list*
Def_use::get_uses (Basic_block* bb)
{
	Alias_name_list* result = new Alias_name_list;
	Context cx = Context::non_contextual (bb);

	foreach (Alias_name use, val_uses[cx])
	{
		use.name = prefix (use.name, "*");
		result->push_back (new Alias_name (use));
	}

	foreach (Alias_name use, ref_uses[cx])
		result->push_back (new Alias_name (use));
	
	return result;
}
