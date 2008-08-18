/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We can easily tell when a function isnt using its symbol table. If they
 * arent, mark the variables in a function as not using the symbol table.
 */


/* GLOBALS:
 *		Globals do not affect whether or not functions are candidates
 *		for pruning. Something like
 *
 *			global $x
 *
 *		means that we create a local $x, into which is put a reference
 *		to the global $x. Whether the local $x is a named C variable
 *		or a hashtable entry doesnt affect correctness. Obviously
 *
 *			global $$y;
 *
 *		means we need a symbol table entry, but that is true of
 *		anything which uses reflection.
 *
 * Pruning globals:
 *		We add global declarations of all the superglobals --- GLOBALS,
 *		HTTP_POST_VARS etc --- in Clarify. Here we check if they are used. If a
 *		global is not used, we remove them. Since we use post_variable_name to do
 *		this, we must avoid going into the VARIABLE_NAME belonging to global $X -
 *		that would defeat the purpose.
 */

#include "Prune_symbol_table.h"
#include "MIR_transform.h"

using namespace MIR;

Prune_symbol_table::Prune_symbol_table () 
: prune (false)
, var_reflection_present (false)
{
	vars = new map<string, bool>;
}

// TODO we cant compile nested functions anyway, but this needs to be
// updated when we do.



class Analysis : public Visitor
{
public:
	bool prune;
	bool var_reflection_present;

	// variables which are present anywhere in the method
	map<string, bool>* vars;

	// We only record globals if they are not in a
	// global statement
	bool record_globals;

	Analysis (map<string, bool>* vars)
	: prune (false)
	, vars(vars)
	{
	}

	void pre_variable_variable (Variable_variable* in)
	{
		prune = false;
	}


	void pre_method_invocation (Method_invocation* in)
	{
		METHOD_NAME* name = dynamic_cast<METHOD_NAME*>(in->method_name);
		if (name && (
					// TODO look at extract () and anything else that affects the symbol table
					*name->value == "eval"
					or *name->value == "include"
					or *name->value == "require" 
					or *name->value == "include_once" 
					or *name->value == "require_once"))
		{
			prune = false;
		}
		else
		{
			// Since eval, include etc are builtin, and cant be called as
			// variable variables, its actually safe to prune here.
		}
	}


	void pre_global (Global* in)
	{
		// Don't mark children variable names
		record_globals = false;
	}

	void post_global (Global* in)
	{
		record_globals = true;
	}

	void post_variable_name (VARIABLE_NAME* in)
	{
		// record variable names for removing globals
		if (record_globals)
			(*vars)[*in->value] = true;
	}

	void post_variable_variable (Variable_variable* in)
	{
		var_reflection_present = true;
	}

};

// We do the "analysis" in the pre_ methods, and update in the post_ methods.
void Prune_symbol_table::pre_method (Method* in)
{
	Analysis a (vars);
	in->visit (&a);
	prune = a.prune;
	var_reflection_present = a.var_reflection_present;
	vars = a.vars;

	// We cant prune in __MAIN__, due to globals.
	if (*in->signature->method_name->value == "__MAIN__")
		prune = false;
}

void Prune_symbol_table::post_variable_name (VARIABLE_NAME* in)
{
	if (prune)
		in->attrs->set_true ("phc.codegen.st_entry_not_required");
}

class Remove_globals : public Transform
{
private:
	map<string, bool>* var_names;

public:
	Remove_globals (map<string, bool> *var_names) 
	: var_names (var_names) 
	{
	}

	void pre_global (Global* in, Statement_list* out)
	{
		// if there were any reflection, we wouldnt be here
		VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in->variable_name);

		// if the key is there, we need the global
		if (var_names->find (*var_name->value) != var_names->end ())
			out->push_back (in);
		else 
		{
			// we dont need the global
		}
	}
};

/* Also mark the function. */
void Prune_symbol_table::post_method (Method* in)
{
	if (prune)
	{
		assert (*in->signature->method_name->value != "__MAIN__");
		in->signature->method_name->attrs->set_true ("phc.codegen.st_entry_not_required");

		// Go through the globals and check if they're used
		if (!var_reflection_present)
			in->transform_children (new Remove_globals (vars));
	}
}

