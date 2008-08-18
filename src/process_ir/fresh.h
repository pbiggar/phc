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
extern set<string> unfresh_vars;

namespace AST
{
	AST::Variable* fresh_var (string prefix);
	AST::VARIABLE_NAME* fresh_var_name (string prefix);
}

namespace HIR
{
	HIR::VARIABLE_NAME* fresh_var_name (string prefix);
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
{

public:
   void pre_variable_name (AST::VARIABLE_NAME* in) 
	{
		unfresh_vars.insert (*in->value);
	}
   void pre_variable_name (HIR::VARIABLE_NAME* in) 
	{
		unfresh_vars.insert (*in->value);
	}
   void pre_variable_name (MIR::VARIABLE_NAME* in) 
	{
		unfresh_vars.insert (*in->value);
	}
};

#endif // PHC_FRESH_H
