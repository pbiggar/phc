/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We can easily tell when a function isnt using its symbol table. If they
 * arent, mark the variables in a function as not using the symbol table.
 */

#ifndef _PRUNE_SYMBOL_TABLE_H_
#define _PRUNE_SYMBOL_TABLE_H_

#include "AST_visitor.h"

class Prune_symbol_table : public AST::Visitor
{
	bool prune;

public:
	Prune_symbol_table () : prune (true) {}

	// do the analysis
	void pre_method (AST::Method* in);
	void pre_reflection (AST::Reflection* in);
	void pre_method_invocation (AST::Method_invocation* in);

	// mark methods and variable_names
	void post_method (AST::Method* in);
	void post_variable_name (AST::VARIABLE_NAME* in);
};

#endif  // _PRUNE_SYMBOL_TABLE_H_
