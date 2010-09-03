/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 *
 * Def-use information.
 *
 * Gather the def-use information while the alias analysis is running.
 *
 *
 * What are we trying to model with Def-use? Just DCE!!
 *		- So how can we tell if a statement needs to be killed?
 *			- It doesnt have any useful defs
 *
 *
 *	- How can we tell if a whole function is useful?
 *		- Get all of its defs/may-defs:
 *			- some of them will be for external definitions:
 *				- ie globals, parameters, returned values
 *
 *
 *	Lets think about the storage, do we want UD/DU chains? Suppose we use ST->x,
 *	do we need to record the change of ST? No. Therefore we just care about
 *	index nodes.
 *
 *
 * We keep track of index nodes at 2 levels:
 *		- ref level:
 *			- a def uses the ref
 *			- a ref-def ref-defs the ref-def
 *			- a ref-def ref-uses the ref-use
 *		- value level
 *			- a def defs the value
 *			- a use uses the value
 *
 *		OK, so given
 *			1. $y =& $z;
 *			2. $x =& $y;
 *			3. $z = 5;
 *			4. var_dump ($x);
 *
 *		we need to be sure that enough things are used to be correct:
 *			- 4 uses $x
 *			- 3 defs x-value, y-value, z-value, uses x-ref, y-ref and z-ref
 *			- 2 defs x-ref
 *			- 1 defs y-ref
 *
 *		What about:
 * 		0. $c =& $z;
 * 		1. $y =& $z;
 *			2. $x =& $y;
 *			3. $z = 5;
 *			4. var_dump ($x);
 *
 *		We are overly conservative, since all refs are in the BB. This currently does
 *			- 4 uses $x
 *			- 3 defs x-value, y-value, z-value, c-value, uses x-ref, y-ref, z-ref, c-ref
 *			- 2 defs x-ref
 *			- 1 defs y-ref
 *
 *		We'd like to:
 * 		- 4 uses $x
 *			- 3 defs x-value, uses x-ref in a CHI node. defs z-value, uses z-ref in the main block
 *			- 2 defs x-ref (used by 3), uses y-ref
 *			- 1 defs y-ref (used by 2), uses z-ref
 *			- 0 does nothing (unless there is an implicit definition in 4, but there isnt).
 *			
 *			
 *
 *	Reference definitions
 *		Given $x =& $y
 *			- the is an implicit def to $y, and $y is later used.
 *				- the value def to $x and implicit one to $y are both already modelled. Nothing special.
 *
 *			- $y (or any of its references) is later defed (but only if $x is used)
 *				- it will be noted that there is a ref-def of $x a ref-def of $y. A
 *				ref-use comes up when there is a normal def or a normal use.
 *
 *			- $x is later defed (but only if $y or its refs are used)
 *				- that will be a ref-use of $x, meaning the corresponding ref-def
 *				is important.
 *
 *			- $x is later used
 *				- that will be a use of the normal def associated with $y
 *		
 *
 *	May-ref/must-def
 *		-	if there is a kill for a variable first, it is a must-def. If there is
 *		not, it is a may-def. Uses arent split into may- and must- defs.
 *
 *
 *	Supporting interprocedural-optimizations (inlining and escape-analysis):
 *		- We have to make a summary of what is def-ed within the function.
 *		- How easy is it to calculate what escapes?
 *
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


reftype reftypes[] = { REF, VAL };
deftype deftypes[] = { DEF, MAYDEF, USE };

#define foreach_dtrt foreach_rtdt
#define foreach_rtdt							\
	foreach (reftype rt, reftypes)		\
		foreach (deftype dt, deftypes)


bool
Def_use::equals (WPA* wpa)
{
	Def_use* other = dyc<Def_use> (wpa);
	return this->maps.equals (&other->maps);
}

string debug_name (reftype rt, deftype dt)
{
	string result = (rt == REF) ? "REF" : "VAL";

	result += "-";

	if (dt == DEF) result += "DEF";
	else if (dt == MAYDEF) result += "MAYDEF";
	else if (dt == USE) result += "USE";
	else phc_unreachable ();

	return result;
}


void
Def_use::dump_set (Context* cx, reftype rt, deftype dt) const
{
	string set_name = debug_name (rt, dt);
	if (maps[cx][rt][dt].size())
	{
		cdebug << cx << ": " << set_name << " list: ";
		foreach (const Index_node* name, maps[cx][rt][dt])
			cdebug << name->str() << ", ";
		cdebug << endl;
	}
	else
		cdebug << cx << ": No " << set_name << " results" << endl;
}

void
Def_use::dump (Context* cx, Result_state, string comment) const
{
	// Print out the results for existing BBs (done this way so that IN and OUT
	// results are presented together).
	foreach_rtdt
		dump_set (cx, rt, dt);


	string st_name = "__MAIN__";
	if (!cx->is_outer ())
		st_name = cx->symtable_name ();

	foreach_rtdt
	{
		string set_name = debug_name (rt, dt);
		if (summary_maps[st_name][rt][dt].size())
		{
			cdebug << st_name << " (summary): " << set_name << " list: ";
			foreach (const Index_node* name, summary_maps[st_name][rt][dt])
				cdebug << name->str() << ", ";
			cdebug << endl;
		}
		else
			cdebug << st_name << ": No summary " << set_name << " results" << endl;
	}
}

void
Def_use::dump_everything (string comment) const
{
	foreach (Context* cx, *maps.keys ())
		dump (cx, R_OUT, comment);
}

/*
 * References
 */

void
Def_use::create_reference (Context* cx, const Index_node* lhs, const Index_node* rhs, Certainty cert)
{
	// A may-ref is a must-def with no killing
	if (has (cx, REF, DEF, lhs))
		record (cx, REF, MAYDEF, lhs);

	record (cx, REF, USE, rhs);

	// Although we know the actual value, we can rarely propagate it, so the
	// tends to be needed here (if this statement is not needed, it will
	// probably be killed).
	record (cx, VAL, USE, rhs);
}


/*
 * Value
 */
void
Def_use::kill_value (Context* cx, const Index_node* lhs, bool also_kill_refs)
{
	record (cx, VAL, DEF, lhs);
	record (cx, REF, USE, lhs);

	if (also_kill_refs)
		record (cx, REF, DEF, lhs);
}

void
Def_use::assign_value (Context* cx, const Index_node* lhs, const Storage_node*)
{
	if (not has (cx, VAL, DEF, lhs))
		record (cx, VAL, MAYDEF, lhs);

	record (cx, REF, USE, lhs);
}



void
Def_use::record_use (Context* cx, const Index_node* use, Certainty cert)
{
	record (cx, REF, USE, use);
	record (cx, VAL, USE, use);
}


void
Def_use::record (Context* cx, reftype rt, deftype dt, const Index_node* index)
{
	if (index->storage == "FAKE")
		return;

	maps[cx][rt][dt].insert (index);
}

bool
Def_use::has (Context* cx, reftype rt, deftype dt, const Index_node* index) const
{
	return maps[cx][rt][dt].has (index);
}



/* Interprocedural support */

// TODO: the caller should use __RETNAME__ in the callee if it has a LHS. If
// LHS is not used, it will be cleaned up with iteration.


bool 
in_scope (Context* cx, const Index_node* index)
{
	// Index_node index_nodes put the name of the symtable as the prefix.
	return index->storage == cx->symtable_name ();
}

void
Def_use::finish_block (Context* cx)
{
	string symtable = cx->symtable_name ();

	// All defs/uses which are out of scope must be recorded in the function
	// summary.
	foreach_rtdt
	{
		foreach (const Index_node* index, maps[cx][rt][dt])
		{
			if (not in_scope (cx, index))
				summary_maps[symtable][rt][dt].insert (index);
		}
	}

	// The exit block must "use" all out-of-scope defs, or they'll be killed
	// later.
	foreach_dtrt
	{
		if (dt == USE)
			continue;

		foreach (const Index_node* index, maps[cx][rt][dt])
		{
			Context* exit_cx = Context::as_peer (cx, cx->get_bb()->cfg->get_exit_bb ());
			if (not in_scope (cx, index))
				maps[exit_cx][rt][USE].insert (index);
		}
	}
}

void
Def_use::merge_contexts ()
{
	// TODO: fix storage_nodes in summary_*
	foreach (Context* cx, *maps.keys ())
	{
		Context* new_cx = cx->get_non_contextual ();
		foreach_dtrt
		{
			Set<const Index_node*> new_map;

			foreach (const Index_node *index, maps[cx][rt][dt])
				new_map.insert (index->convert_context_name ());

			maps[new_cx][rt][dt] = new_map;
		}
	}
}

bool
Def_use::has_analysis_result (Context* cx, Result_state state) const
{
	return maps.has (cx);
}

void
Def_use::backward_bind (Context* caller, Context* exit)
{
	string st_name = exit->symtable_name ();
	foreach_dtrt
	{
		Set<const Index_node*>& set = summary_maps[st_name][rt][dt];
		maps[caller][rt][dt].insert (set.begin(), set.end ());
	}
}

cIndex_node_list*
Def_use::get_index_nodes (Basic_block* bb, deftype dt) const
{
	cIndex_node_list* result = new cIndex_node_list;
	Context* cx = Context::non_contextual (bb);

	foreach (const Index_node* name, maps[cx][VAL][dt])
		result->push_back (name->get_starred_name ());

	foreach (const Index_node* name, maps[cx][REF][dt])
		result->push_back (name);
	
	return result;
}

int
Def_use::get_num_refs (CFG* cfg, deftype dt, bool entryexit)
{
	int res = 0;
	foreach (Basic_block* bb,  *cfg->get_all_bbs ())
	{
		if ((entryexit || !((dynamic_cast<Entry_block*> (bb))
							|| (dynamic_cast<Exit_block*> (bb)))))
		{
			Context* cx = Context::non_contextual (bb);
			res += maps[cx][REF][dt].size ();	
		/*	foreach (const Index_node* in, maps[cx][REF][dt])
			{
				if ((cx->get_bb ()->cfg) && in_scope (cx, in))
				res++;
			}
		*/
		}
	}
	return res;
}

int
Def_use::get_num_vals (CFG* cfg, deftype dt, bool entryexit)
{
	int res = 0;
	foreach (Basic_block* bb,  *cfg->get_all_bbs ())
	{
		if ((entryexit || !((dynamic_cast<Entry_block*> (bb))
							|| (dynamic_cast<Exit_block*> (bb)))))
		{
			Context* cx = Context::non_contextual (bb);
			res += maps[cx][VAL][dt].size ();	
		/*	foreach (const Index_node* in, maps[cx][REF][dt])
			{
				if ((cx->get_bb ()->cfg) && in_scope (cx, in))
				res++;
			}
		*/
		}
	}
	return res;
}

cIndex_node_list*
Def_use::get_defs (Basic_block* bb) const
{
	return get_index_nodes (bb, DEF);
}

cIndex_node_list*
Def_use::get_may_defs (Basic_block* bb) const
{
	return get_index_nodes (bb, MAYDEF);
}

cIndex_node_list*
Def_use::get_uses (Basic_block* bb) const
{
	return get_index_nodes (bb, USE);
}

void
Def_use::insert_index_node (Basic_block* bb, const Index_node *name, deftype dt)
{
	Context* cx = Context::non_contextual (bb);

	// Only insert non starred nodes.
	if (!name->is_starred()) {
		maps[cx][VAL][dt].insert(name);
		maps[cx][REF][dt].insert(name);
	}
}

void
Def_use::insert_def(Basic_block *bb, const Index_node *name)
{
	insert_index_node(bb, name, DEF);
}

void
Def_use::insert_may_def(Basic_block *bb, const Index_node *name)
{
	insert_index_node(bb, name, MAYDEF);
}

void
Def_use::insert_use(Basic_block *bb, const Index_node *name)
{
	insert_index_node(bb, name, USE);
}

void
Def_use::remove_index_node (Basic_block* bb, const Index_node *name, deftype dt)
{
	Context* cx = Context::non_contextual (bb);

	// Only remove non starred nodes.
	if (!name->is_starred()) {
		maps[cx][VAL][dt].erase(name);
		maps[cx][REF][dt].erase(name);
	}
}

void
Def_use::remove_def(Basic_block *bb, const Index_node *name)
{
	remove_index_node(bb, name, DEF);
}

void
Def_use::remove_may_def(Basic_block *bb, const Index_node *name)
{
	remove_index_node(bb, name, MAYDEF);
}

void
Def_use::remove_use(Basic_block *bb, const Index_node *name)
{
	remove_index_node(bb, name, USE);
}
