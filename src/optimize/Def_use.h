#ifndef PHC_DEF_USE
#define PHC_DEF_USE

#include "lib/Map.h"
#include "MIR.h"
#include "Set.h"
#include "Edge.h"
#include "Flow_visitor.h"
#include "Visit_once.h"
#include "ssa/SSA_ops.h"

class CFG;

// A link between variables and the operations on variables.
class SSA_edge : virtual public GC_obj
{
public:
	SSA_edge (MIR::VARIABLE_NAME* var, SSA_op* op);

	// This is a pointer to the actual variable name for the def/use. The
	// variable in the def-use web is just a key, and may be a different
	// instance of the same variable.
	MIR::VARIABLE_NAME* variable_name;
	SSA_op* op;

	void dump ();
};

typedef List<SSA_edge*> SSA_edge_list;



class Def_use_web : public Visit_once
{
	// TODO: This class would benefit from additional indexing, in particular
	// by BB.
	
	// The indexing variable may not be the correct var, while the vars in the
	// SSA_edge_list will be the correct vars. The indexing variable is just
	// for indexing, and it can index multiple vars, so we cant say anythng
	// abour it.
	Map<
		MIR::VARIABLE_NAME*,
		SSA_edge_list, 
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)
	> def_use_chains;

	Map<
		MIR::VARIABLE_NAME*,
		SSA_edge_list, 
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)
	> use_def_chains;

	Map<
		MIR::VARIABLE_NAME*,
		SSA_edge_list, 
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)
	> may_defs;


public:
	Def_use_web ();

	// Return whether USE has a defining statement (vs being uninitialized).
	bool has_def (MIR::VARIABLE_NAME* use);

	// Return the SSA_stmt defining USE, or NULL if it is not defined in a
	// statement (but instead in a phi or a formal). Fail if it is not defined
	// anywhere.
	SSA_stmt* get_def_stmt (MIR::VARIABLE_NAME* use);

	// Get the operations in which USE is defined.
	SSA_op* get_var_def (MIR::VARIABLE_NAME* use);

	// Get the operations in which DEF is used.
	SSA_op_list* get_var_uses (MIR::VARIABLE_NAME* def);

	// Get basic_blocks in which USE is defined (a variable can be defined
	// multiple times if we arent in SSA form. Check that only non-SSA
	// assignments are returned.
	BB_list* get_pre_ssa_var_defs (MIR::VARIABLE_NAME* use);


	// Get all variables defined/used in the basic
	// block, except for those from phis, mus and chis.
	MIR::VARIABLE_NAME_list* get_real_defs (Basic_block* bb);
	MIR::VARIABLE_NAME_list* get_real_uses (Basic_block* bb);

	// Return the variables defined by formal parameters in the entry_block
	MIR::VARIABLE_NAME_list* get_formal_defs ();

	MIR::VARIABLE_NAME_list* get_may_defs (Basic_block* bb);
	
	void dump ();

private:
	// Add defs or uses
	void add_use (MIR::VARIABLE_NAME* def, SSA_op* use);
	void add_use (MIR::Rvalue* def, SSA_op* use);
	void add_def (MIR::VARIABLE_NAME* use, SSA_op* def);
	void add_may_def (MIR::VARIABLE_NAME* use, SSA_op* def);

	void visit_entry_block (Entry_block* bb);
	void visit_branch_block (Branch_block* bb);

	void visit_chi_node (Basic_block* bb, MIR::VARIABLE_NAME* def, MIR::VARIABLE_NAME* use);
	void visit_mu_node (Basic_block* bb, MIR::VARIABLE_NAME* use);
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
	void visit_assign_next (Statement_block*, MIR::Assign_next*);
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
	void visit_unary_op (Statement_block* bb, MIR::Unary_op* in);
	void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
};

#endif // PHC_DEF_USE
