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


void
Def_use::dump_set (Context cx, reftype rt, deftype dt)
{
	string set_name = (rt == REF) ? "REF" : "DEF";
	set_name += "-";
	if (dt == DEF) set_name += "DEF";
	else if (dt == MAYDEF) set_name += "MAYDEF";
	else if (dt == USE) set_name += "USE";
	else phc_unreachable ();

	if (maps[cx][rt][dt].size())
	{
		cdebug << cx << ": " << name << " list: ";
		foreach (Alias_name name, maps[cx][rt][dt])
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
	foreach_rtdt
		dump_set (cx, rt, dt);
}

void
Def_use::dump_everything (string comment)
{
	foreach (Context cx, *maps.keys ())
		dump (cx, comment);
}

/*
 * References
 */

void
Def_use::kill_reference (Context cx, Index_node* lhs)
{
	record (cx, REF, DEF, lhs);
}

void
Def_use::create_reference (Context cx, Index_node* lhs, Index_node* rhs, Certainty cert)
{
	// A may-ref is a must-def with no killing
	if (has (cx, REF, DEF, lhs))
		record (cx, REF, MAYDEF, lhs);

	record (cx, REF, USE, rhs);
}


/*
 * Value
 */
void
Def_use::kill_value (Context cx, Index_node* lhs)
{
	record (cx, VAL, DEF, lhs);
	record (cx, REF, USE, lhs);
}

void
Def_use::assign_value (Context cx, Index_node* lhs, Storage_node* storage_name)
{
	if (not has (cx, VAL, DEF, lhs))
		record (cx, VAL, MAYDEF, lhs);

	record (cx, REF, USE, lhs);
}



void
Def_use::record_use (Context cx, Index_node* use, Certainty cert)
{
	record (cx, REF, USE, use);
	record (cx, VAL, USE, use);
}


void
Def_use::record (Context cx, reftype rt, deftype dt, Index_node* index)
{
	maps[cx][rt][dt].insert (index->name ());
}

bool
Def_use::has (Context cx, reftype rt, deftype dt, Index_node* index)
{
	return maps[cx][rt][dt].has (index->name ());
}



/* Interprocedural support */

// TODO: the caller should use __RETNAME__ in the callee if it has a LHS. If
// LHS is not used, it will be cleaned up with iteration.


bool 
in_scope (Context cx, Alias_name& name)
{
	// Index_node alias_names put the name of the symtable as the prefix.
	return name.prefix == cx.symtable_node ()->for_index_node ();
}

void
Def_use::aggregate_results (Context cx)
{
	string symtable = cx.symtable_name ();

	// All defs/uses which are out of scope must be recorded in the function
	// summary.
	foreach_rtdt
	{
		foreach (Alias_name name, maps[cx][rt][dt])
		{
			if (not in_scope (cx, name))
				summary_maps[cx][rt][dt][symtable].insert (name);

			Context exit_cx = Context::as_peer (cx, cx.get_bb()->cfg->get_exit_bb ());
		}
	}

	// The exit block must "use" all out-of-scope defs, or they'll be killed
	// later.
	foreach_dtrt
	{
		if (dt == USE)
			continue;

		foreach (Alias_name name, maps[cx][rt][dt])
		{
			Context exit_cx = Context::as_peer (cx, cx.get_bb()->cfg->get_exit_bb ());
			if (not in_scope (cx, name))
				maps[exit_cx][rt][USE].insert (name);
		}
	}
}

void
Def_use::merge_contexts ()
{
	// TODO: fix storage_nodes in summary_*
	foreach (Context cx, *maps.keys ())
	{
		Context new_cx = cx.get_non_contextual ();
		foreach_dtrt
		{
			foreach (Alias_name name, maps[cx][rt][dt])
				maps[new_cx][rt][dt].insert (name.convert_context_name ());
		}
	}
}

void
Def_use::backward_bind (Context caller, Context exit)
{
	string st_name = exit.symtable_name ();
	foreach_dtrt
	{
		Set<Alias_name>& set = summary_maps[exit][rt][dt][st_name];
		maps[caller][rt][dt].insert (set.begin(), set.end ());
	}
}

string prefix (string, string);


Alias_name_list*
Def_use::get_alias_name (Basic_block* bb, deftype dt)
{
	Alias_name_list* result = new Alias_name_list;
	Context cx = Context::non_contextual (bb);

	foreach (Alias_name name, maps[cx][VAL][dt])
		result->push_back (new Alias_name (name.prefix, "*_" + name.name));

	foreach (Alias_name name, maps[cx][REF][dt])
		result->push_back (new Alias_name (name));
	
	return result;
}

Alias_name_list*
Def_use::get_defs (Basic_block* bb)
{
	return get_alias_name (bb, DEF);
}

Alias_name_list*
Def_use::get_may_defs (Basic_block* bb)
{
	return get_alias_name (bb, MAYDEF);
}

Alias_name_list*
Def_use::get_uses (Basic_block* bb)
{
	return get_alias_name (bb, USE);
}
