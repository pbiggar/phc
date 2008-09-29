#ifndef PHC_DEF_USE
#define PHC_DEF_USE

#include "MIR.h"
#include "Set.h"
#include "Edge.h"
#include "Flow_visitor.h"
#include "Visit_once.h"

class CFG;

// We dont want to put this into mir.tea. Its a long way from where its used.
class Def_use
{
};

class Def_use_web : public Visit_once
{
	map<
		MIR::VARIABLE_NAME*,
		SSA_edge_list, 
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)
	> def_use_chains;

	map<
		MIR::VARIABLE_NAME*,
		SSA_edge_list, 
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)
	> use_def_chains;

public:
	Def_use_web ();

	// Get all defs/uses in the basic_block. (Originally, this was designed
	// for converting into SSA form, but it has been repurposed, so it might
	// still have legacy bugs).
	MIR::VARIABLE_NAME_list* get_bb_defs (Basic_block* bb);
	MIR::VARIABLE_NAME_list* get_bb_uses (Basic_block* bb);

	// For the variable DEF, return its uses.
	SSA_edge_list* get_var_uses (MIR::VARIABLE_NAME* def);

	// For the variable USE, return its defs.
	SSA_edge* get_var_defs (MIR::VARIABLE_NAME* use);

	void dump ();

private:
	// Add that the variable DEF is used in USE
	void add_use (MIR::VARIABLE_NAME* def, SSA_edge* use);
	void add_def (MIR::VARIABLE_NAME* use, SSA_edge* def);

	// Add that the variable DEF is used in USE
	void add_use (MIR::Rvalue* def, SSA_edge* use);

	void visit_branch_block (Branch_block* bb);

	void visit_phi_node (Basic_block* bb, MIR::VARIABLE_NAME* phi_lhs);

	void visit_assign_array (Statement_block*, MIR::Assign_array*);
	void visit_assign_field (Statement_block*, MIR::Assign_field *);
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	void visit_global (Statement_block*, MIR::Global* in);
	void visit_pre_op (Statement_block*, MIR::Pre_op*);
	void visit_push_array (Statement_block*, MIR::Push_array*);
	void visit_return (Statement_block*, MIR::Return*);
	void visit_ssa_pre_op (Statement_block*, MIR::SSA_pre_op*);
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	void visit_throw (Statement_block*, MIR::Throw*);
	void visit_try (Statement_block*, MIR::Try*);
	void visit_unset (Statement_block*, MIR::Unset*);

	void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	void visit_bin_op (Statement_block* bb, MIR::Bin_op* in);
	void visit_cast (Statement_block* bb, MIR::Cast* in);
	void visit_constant (Statement_block* bb, MIR::Constant* in);
	void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	void visit_isset (Statement_block* bb, MIR::Isset* in);
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	void visit_unary_op (Statement_block* bb, MIR::Unary_op* in);
	void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
};

#endif // PHC_DEF_USE
