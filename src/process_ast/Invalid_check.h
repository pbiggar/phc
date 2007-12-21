/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check for invalid PHP, which otherwise fits within the constraints of
 * our language. This should be run after the parser so we dont operate
 * on invalid code, and any time we worry we may generate invalid code in
 * the HIR.
 */

#ifndef PHC_INVALID_CHECK
#define PHC_INVALID_CHECK

#include "AST_visitor.h"
#include "HIR.h"
#include "pass_manager/Pass_manager.h"

// Returns true if IN is not allowed be on the RHS of a reference assignment.
bool is_ref_literal (AST::Expr* in);
bool is_ref_literal (HIR::Expr* in); // todo avoid duplication
void check (IR* in, bool use_ice);

class Invalid_check : public AST::Visitor, public Pass
{
public:

	// If this is set, use phc_internal_error instead of phc_error
	bool use_ice; // ice == Internal Compiler Error
	Invalid_check (bool use_ice = false) 
	: use_ice (use_ice)
	{
		this->name = new String ("check");
	}

	// decide the error based on whether USE_ICE is set
	void error (const char* message, AST::Node* node);
	void run (IR*, Pass_manager*);

	void pre_statement (AST::Statement* in);
	void pre_assignment (AST::Assignment* in);
	void pre_foreach (AST::Foreach* in);
	void pre_interface_def (AST::Interface_def* in);
	void pre_directive (AST::Directive *in);
	void pre_formal_parameter (AST::Formal_parameter* in);
	void pre_method_invocation (AST::Method_invocation* in);
	void pre_array_elem (AST::Array_elem* in);
	void pre_name_with_default (AST::Name_with_default* var);
	void pre_attribute (AST::Attribute* in);
};

#endif // PHC_INVALID_CHECK
