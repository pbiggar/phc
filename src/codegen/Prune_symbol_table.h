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
private:
	// We can only prune in functions other than __MAIN__
	bool prune;

	// is there reflection
	bool var_reflection_present;

	// We only record globals if they are not in a gloal statement
	bool record_globals;

	// variables which are present anywhere in the method
	map<string, bool> vars;

public:
	Prune_symbol_table ();
	// do the analysis
	void pre_method (MIR::Method* in);
	void pre_variable_variable (MIR::Variable_variable* in);
	void pre_method_invocation (MIR::Method_invocation* in);
	void pre_global (MIR::Global* in);
	void post_global (MIR::Global* in);

	// mark methods and variable_names
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
	void post_variable_name (MIR::Variable_name* in);
};

#endif  // _PRUNE_SYMBOL_TABLE_H_
