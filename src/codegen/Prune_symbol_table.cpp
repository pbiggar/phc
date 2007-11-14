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

using namespace AST;


// TODO we cant compile nested functions anyway, but this needs to be
// updated when we do.

// We do the "analysis" in the pre_ methods, and update in the post_ methods.
void Prune_symbol_table::pre_method (AST_method* in)
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
void Prune_symbol_table::pre_reflection (AST_reflection* in)
{
	prune = false;
}

void Prune_symbol_table::pre_method_invocation (AST_method_invocation* in)
{
	/* To be able to support includes with return statements, without
	 * dataflow, we dont shred their string arguments */
	Token_method_name* name = dynamic_cast<Token_method_name*>(in->method_name);
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


void Prune_symbol_table::post_variable_name (Token_variable_name* in)
{
	if (prune)
		in->attrs->set_true ("phc.codegen.st_entry_not_required");
}

/* Also mark the function. */
void Prune_symbol_table::post_method (AST_method* in)
{
	if (prune)
	{
		assert (*in->signature->method_name->value != "__MAIN__");
		in->signature->method_name->attrs->set_true ("phc.codegen.st_entry_not_required");
	}
}
