/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#ifndef PHC_FRESH_H
#define PHC_FRESH_H

#include "AST.h"
#include "HIR.h"
#include "MIR.h"

String* fresh(string prefix);

namespace AST
{
	AST::Variable* fresh_var (string prefix);
	AST::VARIABLE_NAME* fresh_var_name (string prefix);
}

namespace HIR
{
	HIR::Variable* fresh_var (string prefix);
	HIR::VARIABLE_NAME* fresh_var_name (string prefix);
}

namespace MIR
{
	MIR::Variable* fresh_var (string prefix);
	MIR::VARIABLE_NAME* fresh_var_name (string prefix);
	MIR::Label* fresh_label ();
	MIR::HT_ITERATOR* fresh_iter ();
}

#endif // PHC_FRESH_H
