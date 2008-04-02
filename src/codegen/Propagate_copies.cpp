/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * The lowering passes introduce a lot of unnecessary copies, which
 * add extra reference counts, resulting in extra copying and poor
 * performance.
 *
 * HACK TODO: Remove.
 * This is exactly the sort of hacky thing we wanted
 * to remove. This would be much better done with a data-flow
 * framework, but is much easier than cleaning up the passes, which
 * would otherwise be necessary.
 *
 * Since we do not have proper data-flow, we are going to be very
 * conservative, using the following assumptions:
 *
 *	-	Only do this for compiler generated temporaries, this is not
 *		for optimization of user-code, just as a clean-up.
 *
 * -	Simple example: :
 *		1.)	$L1 = $R1; // replaceable
 *		2.)	$L2 = $L1; // removable
 *		becomes:
 *		1.)	$L2 = $R1; // replaced
 *
 *	-	This is not the same as:
 *		1.)	$L1 = $R1;
 *		2.)	$L2 = $L1;	
 *		becoming:
 *		2.)	$L2 = $R1; // $R1 might have been assigned to in-between
 *			
 *	-	$L1 must be a simple variable, and must be annotated with
 *		phc.codegen.compiler_generated
 *
 *	-	Statement 1. must occur after statement 2.
 *
 *	-	Strange cases which break it, shouldn't happen because we only
 *		use this for the restricted set of compiler-generated
 *		temporaries.
 *
 *	The following restrictions may be temporary:
 *
 *	-	Both the assignments involved must be of the form
 *			$R = $L
 *		and must not be by reference, or involve array_indices.
 *	-	$L1 must be assigned exactly once.
 *	-	$L1 must be used exactly once - in the assignment to $L2.
 *	-	$L2 is assigned exactly once, by $R1
 *	-	We only work in methods, not in the global statement list
 */

#include "Propagate_copies.h"
#include "process_ir/General.h"
#include "HIR_visitor.h"

using namespace HIR;

Propagate_copies::Propagate_copies ()
: in_method (false)
{
}

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

/* Entering at the method level, count the total occurences of a variable, and
 * the number of defintions, and the uses is the difference of the two. */
class Use_def_counter : public HIR::Visitor
{
	map<string, int>& uses;
	map<string, int>& defs;
	map<string, int> occurences;

public:
	Use_def_counter (map<string, int>& uses, map<string, int>& defs)
	: uses (uses)
	, defs (defs)
	, occurences ()
	{
	}

	void pre_method (Method* in)
	{
		uses.clear ();
		defs.clear ();
		occurences.clear ();
	}

	void pre_assignment (Assignment* in)
	{
		if (VARIABLE_NAME* var_name = simple_var (in->variable))
			defs [*var_name->value] ++;
	}

	void pre_variable_name (VARIABLE_NAME* in)
	{
		occurences [*in->value] ++;
	}


	void post_method (Method* in)
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
};

void Propagate_copies::pre_method (Method* in, List<Method*>* out)
{

	// each function is separate
	replaceable.clear ();
	use_counts.clear ();
	def_counts.clear ();

	// count uses and defs
	in->visit (new Use_def_counter (use_counts, def_counts));

	in_method = true;

	out->push_back (in);
}

void Propagate_copies::post_method (Method* in, List<Method*>* out)
{
	in_method = false;
	out->push_back (in);
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

void Propagate_copies::pre_eval_expr (Eval_expr* in, List<Statement*>* out)
{
	// only method, not the global part
	if (!in_method)
	{
		out->push_back (in);
		return;
	}

	cdebug << "TEST" << endl;

	debug (in);

	// get useful variables
	VARIABLE_NAME *lhs, *rhs;
	Assignment* assignment;
	if (extract_simple_assignment (in, lhs, rhs, assignment))
	{
		xadebug (lhs);
		xadebug (rhs);
		cdebug << "is simple assignment" << endl;
		string slhs = *lhs->value;
		string srhs = *rhs->value;

		// add to the list of for future consideration
		if (lhs->attrs->is_true ("phc.codegen.compiler_generated"))
		{
			cdebug << "lhs is compiler generated" << endl;
			assert (replaceable.find (slhs) == replaceable.end ());
			replaceable [slhs] = assignment;
		}

		cdebug << "use counts" << endl;
		print_map (use_counts);
		cdebug << "def counts" << endl;
		print_map (def_counts);

		// be conservative
		if (replaceable.find (srhs) != replaceable.end ()
				&&	use_counts [srhs] == 1
				&&	def_counts [srhs] == 1)
		{
			cdebug << "r s is replacable" << endl;
			replaceable [srhs]->variable = new Variable (NULL, new VARIABLE_NAME (s(slhs)), new List<Expr*>);
			// note lack of out->push_back (in);
			return;
		}
	}

	out->push_back (in);
}
