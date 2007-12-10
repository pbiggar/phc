/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We can easily tell when a function isnt using its symbol table. If they
 * arent, mark the variables in a function as not using the symbol table.
 */

#ifndef _PRUNE_SYMBOL_TABLE_H_
#define _PRUNE_SYMBOL_TABLE_H_

#include "MIR_visitor.h"

class Prune_symbol_table : public MIR::Visitor
{
	bool prune;

public:
	Prune_symbol_table ();
	// do the analysis
	void pre_method (MIR::Method* in);
	void pre_reflection (MIR::Reflection* in);
	void pre_method_invocation (MIR::Method_invocation* in);

	// mark methods and variable_names
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
};

#endif  // _PRUNE_SYMBOL_TABLE_H_
