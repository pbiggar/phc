/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Simple alias analysis using address-taken semantics. If any variable is, or
 * may be, passed by reference, consider it part of the alias-set, all members
 * of which alias each other.
 */

#include "pass_manager/Pass_manager.h"
#include "Flow_visitor.h"

#ifndef PHC_ADDRESS_TAKEN
#define PHC_ADDRESS_TAKEN

class Address_taken : public Flow_visitor<Full_flow_visitor, FORWARD_FLOW>
{
public:
	Address_taken ();
	bool pass_is_enabled (Pass_manager* pm);

	Set* aliases;

public:
	void init_block (Basic_block* bb);
	bool solution_has_changed (Basic_block* bb);
	void alias_expr (Basic_block* bb, MIR::Expr*);
	void alias_bottom (Basic_block* bb);
	void aliased (Basic_block* bb, MIR::Variable_name*);
	void aliased (Basic_block* bb, MIR::Rvalue*);
	void aliased (Basic_block* bb, MIR::VARIABLE_NAME*);

	// Transfer functions
	void transfer_in (Basic_block* bb, list<Basic_block*>* preds);
	void transfer_out (Basic_block* bb, list<Basic_block*>* succs);

	// Local solution
	void visit_entry_block (Entry_block*);
	void visit_empty_block (Empty_block*) {}
	void visit_exit_block (Exit_block*) {}
	void visit_branch_block (Branch_block*);

	void visit_assign_array (Statement_block* sb, MIR::Assign_array*);
	void visit_assign_target (Statement_block* sb, MIR::Assign_target*);
	void visit_assign_var (Statement_block* sb, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block* sb, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block* sb, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block* sb, MIR::Foreach_end*);
	void visit_foreach_next (Statement_block* sb, MIR::Foreach_next*);
	void visit_foreach_reset (Statement_block* sb, MIR::Foreach_reset*);
	void visit_global (Statement_block* sb, MIR::Global*);
	void visit_param_is_ref (Statement_block* sb, MIR::Param_is_ref*);
	void visit_pre_op (Statement_block* sb, MIR::Pre_op*);
	void visit_push_array (Statement_block* sb, MIR::Push_array*);
	void visit_return (Statement_block* sb, MIR::Return*);
	void visit_static_declaration (Statement_block* sb, MIR::Static_declaration*);
	void visit_try (Statement_block* sb, MIR::Try*);
	void visit_throw (Statement_block* sb, MIR::Throw*);
	void visit_unset (Statement_block* sb, MIR::Unset*);

};

#endif // PHC_ADDRESS_TAKEN
