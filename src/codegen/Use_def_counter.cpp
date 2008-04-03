/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * HACK TODO: Remove.
 * This is exactly the sort of hacky thing we wanted
 * to remove. This would be much better done with a data-flow
 * framework, but is much easier than cleaning up the passes, which
 * would otherwise be necessary.
 *
 * Count the uses and defs of each variable. Of course, it is very
 * imprecise, only works for very certain cases, doesn't use any
 * sort of data-flow techniques, won't work in the general case in
 * the presence of any sort of features, doesn't take references
 * into account, etc. This is only barely usable for the hacky dead
 * code elimination and copy propagation I've hacked into place.
 *
 */

#include "Use_def_counter.h"
#include "HIR_visitor.h"

using namespace HIR;
VARIABLE_NAME* simple_var (Expr* in)
{
	Variable* var = dynamic_cast<Variable*> (in);
	if (!var)
		return NULL;

	// Normal vars only, not array_indices or var-vars
	if (var->array_indices->size () > 0
		|| var->target)
		return NULL;

	return dynamic_cast<VARIABLE_NAME*> (var->variable_name);
}

void print_map (map<string, int>& in)
{
	map<string, int>::const_iterator i;
	for(i = in.begin(); i != in.end(); i++)
		cdebug << (*i).first << ": " << (*i).second << endl;
}



bool extract_simple_assignment (Eval_expr* in, VARIABLE_NAME*& lhs, VARIABLE_NAME*& rhs, Assignment*& assignment)
{
	assignment = dynamic_cast<Assignment*> (in->expr);
	if (assignment == NULL)
		return false;

	lhs = simple_var (assignment->variable);
	rhs = simple_var (assignment->expr);

	if (lhs == NULL || rhs == NULL)
		return false;

	return true;
}




Use_def_counter::Use_def_counter (map<string, int>& uses, map<string, int>& defs)
: uses (uses)
, defs (defs)
, occurences ()
{
}

void Use_def_counter::pre_method (Method* in)
{
	uses.clear ();
	defs.clear ();
	occurences.clear ();
}

void Use_def_counter::pre_assignment (Assignment* in)
{
	if (VARIABLE_NAME* var_name = simple_var (in->variable))
		defs [*var_name->value] ++;
}

void Use_def_counter::pre_variable_name (VARIABLE_NAME* in)
{
	occurences [*in->value] ++;
}


void Use_def_counter::post_method (Method* in)
{
	// our exit point - work out the uses from the occurences and
	// the defs

	// first if either occurences or defs are missing a variable,
	// add it.
	map<string, int>::const_iterator i;
	for(i = defs.begin(); i != defs.end(); i++)
		if (occurences.find ((*i).first) == defs.end ())
			occurences [(*i).first] = 0;

	for(i = occurences.begin(); i != occurences.end(); i++)
		if (defs.find ((*i).first) == defs.end ())
			defs [(*i).first] = 0;


	for(i = occurences.begin(); i != occurences.end(); i++)
	{
		string key = (*i).first;
		uses [key] = occurences [key] - defs [key];
	}
}
