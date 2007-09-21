/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We can easily tell when a function isnt using its symbol table. If they
 * arent, mark the variables in a function as not using the symbol table.
 */

#include "Prune_symbol_table.h"


// TODO globals. To prune or not to prune?

// TODO we cant compile nested functions anyway, but this needs to be
// updated when we do.
void Prune_symbol_table::pre_method (AST_method* in)
{
	// reset
	prune = true;

	if (*in->signature->method_name->value == "__MAIN__")
	{
		prune = false;
	}
}

void Prune_symbol_table::post_variable (AST_variable* in)
{
	if (prune)
		in->attrs->set_true ("phc.codegen.st_entry_not_required");
}

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
