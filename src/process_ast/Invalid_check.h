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

// Returns true if IN is not allowed be on the RHS of a reference assignment.
bool is_ref_literal (AST_expr* in);

class Invalid_check : public AST_visitor 
{
public:

	// If this is set, use phc_internal_error instead of phc_error
	bool use_ice; // ice == Internal Compiler Error
	Invalid_check () : use_ice (false) {}

	// decide the error based on whether USE_ICE is set
	void error (const char* message, AST_node* node);

	void pre_statement (AST_statement* in);
	void pre_assignment (AST_assignment* in);
	void pre_foreach (AST_foreach* in);
	void pre_interface_def (AST_interface_def* in);
	void pre_directive (AST_directive *in);
	void pre_formal_parameter (AST_formal_parameter* in);
	void pre_method_invocation (AST_method_invocation* in);
	void pre_attribute (AST_attribute* in);
	void pre_static_declaration (AST_static_declaration* in);
};

#endif // PHC_INVALID_CHECK
