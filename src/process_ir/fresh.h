/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#ifndef PHC_FRESH_H
#define PHC_FRESH_H

#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "MIR_visitor.h"
#include <set>

String* fresh(string prefix);

extern int fresh_suffix_counter;
extern std::set<string> unfresh_vars;

namespace AST
{
	AST::Variable* fresh_var (string prefix);
	AST::VARIABLE_NAME* fresh_var_name (string prefix);
}

namespace HIR
{
	HIR::VARIABLE_NAME* fresh_var_name (string prefix);
	HIR::CLASS_NAME* fresh_class_name (string prefix);
	HIR::INTERFACE_NAME* fresh_interface_name (string prefix);
	HIR::METHOD_NAME* fresh_method_name (string prefix);
}

namespace MIR
{
	MIR::VARIABLE_NAME* fresh_var_name (string prefix);
	MIR::Label* fresh_label ();
	LABEL_NAME* fresh_label_name ();
	MIR::HT_ITERATOR* fresh_iter ();
}

// There is a similar problem that this does not solve: variables used in a
// program's source should never be used for temporary variables.
class Read_fresh_suffix_counter
: public AST::Visitor
, public HIR::Visitor
, public MIR::Visitor
, virtual public GC_obj
{

public:
	void found_value (String* value)
	{
		unfresh_vars.insert (*value);
	}

   void pre_variable_name (AST::VARIABLE_NAME* in) { found_value (in->value); }
	void pre_variable_name (HIR::VARIABLE_NAME* in) { found_value (in->value); }
	void pre_variable_name (MIR::VARIABLE_NAME* in) { found_value (in->value); }
	void pre_label_name (MIR::LABEL_NAME* in)			{ found_value (in->value); }
	void pre_ht_iterator (MIR::HT_ITERATOR* in)		{ found_value (in->value); }

};

#endif // PHC_FRESH_H
