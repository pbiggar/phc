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
 */

#include "Prune_symbol_table.h"

using namespace MIR;

Prune_symbol_table::Prune_symbol_table () 
:  prune (true) 
{
}

// TODO we cant compile nested functions anyway, but this needs to be
// updated when we do.

// We do the "analysis" in the pre_ methods, and update in the post_ methods.
void Prune_symbol_table::pre_method (Method* in)
{
	// reset
	prune = true;

	if (*in->signature->method_name->value == "__MAIN__")
	{
		prune = false;
	}
}

// TODO this is over-conservative, as it will stop variable
// functions, which are fine.
void Prune_symbol_table::pre_reflection (Reflection* in)
{
	prune = false;
}

void Prune_symbol_table::pre_method_invocation (Method_invocation* in)
{
	/* To be able to support includes with return statements, without
	 * dataflow, we dont shred their string arguments */
	METHOD_NAME* name = dynamic_cast<METHOD_NAME*>(in->method_name);
	if (name && (
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


void Prune_symbol_table::post_variable_name (VARIABLE_NAME* in)
{
	if (prune)
		in->attrs->set_true ("phc.codegen.st_entry_not_required");
}

/* Also mark the function. */
void Prune_symbol_table::post_method (Method* in)
{
	if (prune)
	{
		assert (*in->signature->method_name->value != "__MAIN__");
		in->signature->method_name->attrs->set_true ("phc.codegen.st_entry_not_required");
	}
}
