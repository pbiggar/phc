/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Mark variables as definitely initialized, or definitely uninitialized, or maybe initialized.
 *
 * The simplest way to do this is outside SSA-form:
 *		if there is a definition in a block which dominates the block with the use, then 
 */

#ifndef PHC_MARK_INITIALIZED
#define PHC_MARK_INITIALIZED


#include "Visit_once.h"

class Mark_initialized : public Visit_once
{
public:
//	void visit_assign_array (Statement_block* sb, MIR::Assign_array*);
//	void visit_assign_field (Statement_block* sb, MIR::Assign_field*);
	void visit_assign_var (Statement_block* sb, MIR::Assign_var*);
/*	void visit_assign_var_var (Statement_block* sb, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block* sb, MIR::Eval_expr*);
	void visit_global (Statement_block* sb, MIR::Global*);
	void visit_assign_next (Statement_block* sb, MIR::Assign_next*);
	void visit_return (Statement_block* sb, MIR::Return*);
	void visit_static_declaration (Statement_block* sb, MIR::Static_declaration*);
	void visit_try (Statement_block* sb, MIR::Try*);
	void visit_throw (Statement_block* sb, MIR::Throw*);

	void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	void visit_isset (Statement_block* bb, MIR::Isset* in);
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
*/


};

#endif // PHC_ADDRESS_TAKEN
