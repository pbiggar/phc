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

#define SSA_STMT		(1 << 0)
#define SSA_BRANCH	(1 << 1)
#define SSA_FORMAL	(1 << 2)
#define SSA_PHI		(1 << 3)
#define SSA_CHI		(1 << 4)
#define SSA_MU			(1 << 5)
#define SSA_ALL		(SSA_STMT|SSA_BRANCH|SSA_FORMAL|SSA_PHI|SSA_CHI|SSA_MU)


class Def_use_web : public Visit_once
{
	// The indexing variable may not be the correct var, while the vars in the
	// SSA_edge_list will be the correct vars. The indexing variable is just
	// for indexing, and it can index multiple vars, so we cant say anythng
	// about it.
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

	// This is a single set of possible aliases. All variables in the set can
	// (conservatively) be considered to alias all other variables in the
	// set. When adding a use or a def, and the use/def aliases another
	// variable in the set, we add Mus and Chis accordingly.
	Set* aliases;

public:
	Def_use_web (Set* aliases);

	/*
	 * Flags:
	 *		SSA_STMT
	 *		SSA_PHI
	 *		SSA_BRANCH
	 *		SSA_FORMAL
	 *		SSA_CHI
	 *		SSA_MU
	 */
	// Get all operations that define USE, and that satisfy flags.
	SSA_op_list* get_defs (MIR::VARIABLE_NAME* use, int flags);

	// Get all operations that use DEF, and that satisfy FLAGS.
	SSA_op_list* get_uses (MIR::VARIABLE_NAME* def, int flags);

	// Get the variables defined/used in BB
	MIR::VARIABLE_NAME_list* get_block_defs (Basic_block* bb, int flags);
	MIR::VARIABLE_NAME_list* get_block_uses (Basic_block* bb, int flags);

	/*
	 * All operations in this class go through either get_defs or get_uses.
	 * They simply call it with different flags.
	 */

	// Return whether USE has a defining statement (vs being uninitialized).
	bool has_def (MIR::VARIABLE_NAME* use);

	// Return the SSA_op defining USE.
	SSA_op* get_def (MIR::VARIABLE_NAME* use);

	void dump ();
	void consistency_check ();

private:
	// Add defs or uses
	void add_use (MIR::VARIABLE_NAME* def, SSA_op* use, bool add_mu = true);
	void add_use (MIR::Rvalue* def, SSA_op* use, bool add_mu = true);
	void add_def (MIR::VARIABLE_NAME* use, SSA_op* def, bool add_chi = true);
	void add_mus (Basic_block* bb, MIR::VARIABLE_NAME* use);
	void add_chis (Basic_block* bb, MIR::VARIABLE_NAME* def);


	void visit_entry_block (Entry_block* bb);
	void visit_exit_block (Exit_block* bb);
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
