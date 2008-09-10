/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Simple alias analysis using address-taken semantics. If any variable is, or
 * may be, passed by reference, consider it part of the alias-set, all members
 * of which alias each other.
 */

#ifndef PHC_ADDRESS_TAKEN
#define PHC_ADDRESS_TAKEN


#include "Visit_once.h"


class Address_taken : public Visit_once
{
public:
	Address_taken ();

	Set* aliases;

public:
	void alias_expr (Basic_block* bb, MIR::Expr*);
	void alias_bottom (Basic_block* bb);
	void aliased (Basic_block* bb, MIR::Variable_name*);
	void aliased (Basic_block* bb, MIR::Rvalue*);
	void aliased (Basic_block* bb, MIR::VARIABLE_NAME*);

	void visit_entry_block (Entry_block*);
	void visit_statement_block (Statement_block*);

	void visit_assign_array (Statement_block* sb, MIR::Assign_array*);
	void visit_assign_field (Statement_block* sb, MIR::Assign_field*);
	void visit_assign_var (Statement_block* sb, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block* sb, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block* sb, MIR::Eval_expr*);
	void visit_global (Statement_block* sb, MIR::Global*);
	void visit_push_array (Statement_block* sb, MIR::Push_array*);
	void visit_return (Statement_block* sb, MIR::Return*);
	void visit_static_declaration (Statement_block* sb, MIR::Static_declaration*);
	void visit_try (Statement_block* sb, MIR::Try*);
	void visit_throw (Statement_block* sb, MIR::Throw*);
};

#endif // PHC_ADDRESS_TAKEN
