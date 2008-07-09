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

String* fresh(string prefix);

extern int fresh_suffix_counter;

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
	MIR::HT_ITERATOR* fresh_iter ();
}

// There is a similar problem that this does not solve: variables used in a
// program's source should never be used for temporary variables.
template <class VARIABLE_NAME, class Visitor>
class Read_fresh_suffix_counter : virtual public Visitor
{

public:
   void pre_variable_name (VARIABLE_NAME* in) 
	{
		if (not in->attrs->has ("phc.fresh.suffix"))
			return;

		Integer* suffix = in->attrs->get_integer ("phc.fresh.suffix");
		if (suffix && suffix->value () >= fresh_suffix_counter)
			fresh_suffix_counter = suffix->value() + 1;
	}
};

class AST_read_fresh_suffix_counter : public Read_fresh_suffix_counter
<
	AST::VARIABLE_NAME,
	AST::Visitor
>
{
};

class HIR_read_fresh_suffix_counter : public Read_fresh_suffix_counter
<
	HIR::VARIABLE_NAME,
	HIR::Visitor
>
{
};

class MIR_read_fresh_suffix_counter : public Read_fresh_suffix_counter
<
	MIR::VARIABLE_NAME,
	MIR::Visitor
>
{
};

#endif // PHC_FRESH_H
