/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Modify 'target' attribute on variables in %MAIN%::%run%(), 
 * and add them as static member variables to the %MAIN% class.
 */

#ifndef PHC_VARIABLE_TARGETS
#define PHC_VARIABLE_TARGETS

#include "AST_visitor.h"
#include <set>

class Variable_targets : public AST_visitor
{
private:
	struct ltstr
	{
	  bool operator()(const Token_variable_name* s1, const Token_variable_name* s2) const
	  {
	    return s1->value->compare(*s2->value) < 0;
	  }
	};

private:
	bool in_run;
	AST_class_def* current_class; // This will be set to %MAIN% when in_run is true.
	set<Token_variable_name*, ltstr> var_names;

public:
	Variable_targets(); 
	virtual ~Variable_targets();

public:
	void pre_class_def(AST_class_def* in);
	void pre_method(AST_method* in);
	void post_method(AST_method* in);
	void pre_variable(AST_variable* in);

};

#endif // PHC_VARIABLE_TARGETS
