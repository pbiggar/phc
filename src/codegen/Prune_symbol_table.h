/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We can easily tell when a function isnt using its symbol table. If they
 * arent, mark the variables in a function as not using the symbol table.
 */

#ifndef _PRUNE_SYMBOL_TABLE_H_
#define _PRUNE_SYMBOL_TABLE_H_

#include "Prune_symbol_table.h"
#include "AST_visitor.h"

class Prune_symbol_table : public AST_visitor
{
	bool prune;

public:
	Prune_symbol_table () : prune (true) {}

	// do the analysis
	void pre_method (AST_method* in);
	void pre_reflection (AST_reflection* in);
	void pre_method_invocation (AST_method_invocation* in);

	// mark methods and variable_names
	void post_method (AST_method* in);
	void post_variable_name (Token_variable_name* in);
};

#endif  // _PRUNE_SYMBOL_TABLE_H_
