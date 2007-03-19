/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Modify 'target' attribute on method invocations 
 */

#ifndef PHC_INVOCATION_TARGETS
#define PHC_INVOCATION_TARGETS

#include "AST_visitor.h"

class Collect_method_names : public AST_visitor
{
public: 
	bool in_main;
	List<Token_method_name*> method_names;

public:
	Collect_method_names();
	virtual ~Collect_method_names();

public:
	void pre_class_def(AST_class_def* in);
	void pre_signature(AST_signature* in);
	void children_method_invocation(AST_method_invocation* in);
};

class Invocation_targets : public AST_visitor
{ 
private: 
	Collect_method_names cmn;

public:
	Invocation_targets();
	virtual ~Invocation_targets(); 

public:
	void pre_php_script(AST_php_script* in);
	void pre_method_invocation(AST_method_invocation* in);
	bool defined_in_main(Token_method_name* name);
};

#endif // PHC_INVOCATION_TARGETS
