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
#include "pass_manager/Pass_manager.h"

// Returns true if IN is not allowed be on the RHS of a reference assignment.
bool is_ref_literal (AST::AST_expr* in);
void check (IR* in, bool use_ice);

class Invalid_check : public AST::AST_visitor, public Pass
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
	void error (const char* message, AST::AST_node* node);
	void run (IR*, Pass_manager*);

	void pre_statement (AST::AST_statement* in);
	void pre_assignment (AST::AST_assignment* in);
	void pre_foreach (AST::AST_foreach* in);
	void pre_interface_def (AST::AST_interface_def* in);
	void pre_directive (AST::AST_directive *in);
	void pre_formal_parameter (AST::AST_formal_parameter* in);
	void pre_method_invocation (AST::AST_method_invocation* in);
	void pre_array_elem (AST::AST_array_elem* in);
	void pre_name_with_default (AST::AST_name_with_default* var);
	void pre_attribute (AST::AST_attribute* in);
};

#endif // PHC_INVALID_CHECK
