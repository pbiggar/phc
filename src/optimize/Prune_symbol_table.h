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

class Prune_symbol_table : public MIR::Visitor, public virtual GC_obj
{
private:
	bool prune;
	bool var_reflection_present;
	Map<string, bool>* vars;

public:
	Prune_symbol_table ();

	void pre_method (MIR::Method* in);

	// mark methods and variable_names
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
};

#endif  // _PRUNE_SYMBOL_TABLE_H_
