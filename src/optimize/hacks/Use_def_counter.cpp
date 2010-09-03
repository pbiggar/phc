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
using namespace std;

Use_def_counter::Use_def_counter ()
: analysis_defs ()
, analysis_occurences ()
{
}


/* The entry points are the php script, and method entries */
void Use_def_counter::init_analysis ()
{
	analysis_defs.push (new Map<string, int>);
	analysis_occurences.push (new Map<string, int>);
}

void Use_def_counter::children_php_script (PHP_script* in)
{
	init_analysis ();

	// continue the visitor
	Visitor::children_php_script (in);

	finish_analysis (in->statements);
}

void Use_def_counter::pre_method (Method* in)
{
	init_analysis ();
}



/* Count defs and uses */
void Use_def_counter::pre_assign_var (Assign_var* in)
{
	(*analysis_defs.top()) [*in->lhs->value] ++;
}

void Use_def_counter::pre_variable_name (VARIABLE_NAME* in)
{
	(*analysis_occurences.top()) [*in->value] ++;
}

/* Exit points are after methods, and after the script completes */
void Use_def_counter::post_method (Method* in)
{
	finish_analysis (in->statements);
}

class Add_attributes : public HIR::Visitor, public virtual GC_obj
{
private:
	Map<string, int>* uses;
	Map<string, int>* defs;
public:
	Add_attributes (Map<string, int>* uses, Map<string, int>* defs)
	: uses (uses)
	, defs (defs)
	{
	}

	void children_method (Method* in)
	{
		// Do not descend into functions
	}

	void pre_variable_name (VARIABLE_NAME* in)
	{
		in->attrs->set ("phc.use_defs.use_count", new Integer ((*uses) [*in->value]));
		in->attrs->set ("phc.use_defs.def_count", new Integer ((*defs) [*in->value]));
	}
};

void Use_def_counter::finish_analysis (HIR::Statement_list* in)
{
	Map<string, int>* defs = analysis_defs.top ();
	Map<string, int>* occurences = analysis_occurences.top ();
	Map<string, int>* uses = new Map <string, int> ();

	analysis_occurences.pop ();
	analysis_defs.pop ();


	// If either occurences or defs are missing a variable, add it.
	Map<string, int>::const_iterator i;
	for(i = defs->begin(); i != defs->end(); i++)
		if (occurences->find ((*i).first) == defs->end ())
			(*occurences) [(*i).first] = 0;

	for(i = occurences->begin(); i != occurences->end(); i++)
		if (defs->find ((*i).first) == defs->end ())
			(*defs) [(*i).first] = 0;


	for(i = occurences->begin(); i != occurences->end(); i++)
	{
		string key = (*i).first;
		(*uses) [key] = (*occurences) [key] - (*defs) [key];
	}

	(new Add_attributes (uses, defs))->visit_statement_list (in);
}

