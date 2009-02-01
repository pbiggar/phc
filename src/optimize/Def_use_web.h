#ifndef PHC_DEF_USE_WEB
#define PHC_DEF_USE_WEB

#include "Var_map.h"
#include "MIR.h"
#include "Var_set.h"
#include "Edge.h"
#include "Flow_visitor.h"
#include "Visit_once.h"
#include "Alias_name.h"
#include "ssa/SSA_ops.h"

class CFG;
class Def_use;
class Points_to;

// A link between variables and the operations on variables.
class SSA_edge : virtual public GC_obj
{
public:
	SSA_edge (Alias_name name, SSA_op* op);

	// This is a pointer to the actual variable name for the def/use. The
	// variable in the def-use web is just a key, and may be a different
	// instance of the same variable.
	Alias_name name;
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
	Var_map<SSA_edge_list> def_use_chains;
	Var_map<SSA_edge_list> use_def_chains;

public:
	Def_use_web (Def_use* du);

	// The analysis portion. This forms a DU-web over the data analysed.
	Def_use* du; 

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
	SSA_op_list* get_defs (Alias_name use, int flags);

	// Get all operations that use DEF, and that satisfy FLAGS.
	SSA_op_list* get_uses (Alias_name def, int flags);

	// Get the variables defined/used in BB
	Alias_name_list* get_block_defs (Basic_block* bb, int flags);
	Alias_name_list* get_block_uses (Basic_block* bb, int flags);

	/*
	 * All operations in this class go through either get_defs or get_uses.
	 * They simply call it with different flags.
	 */

	// Return whether USE has a defining statement (vs being uninitialized).
	bool has_def (Alias_name use);

	// Return the SSA_op defining USE.
	SSA_op* get_def (Alias_name use);

	void dump ();
	void consistency_check ();

private:
	// Add defs or uses
	void add_use (Alias_name def, SSA_op* use);
	void add_def (Alias_name use, SSA_op* def);
	void add_may_def (Alias_name var, SSA_op* def);
	void add_may_use (Alias_name var, SSA_op* use);

	void add_mus (Basic_block* bb, Alias_name use);
	void add_chis (Basic_block* bb, Alias_name def);

	void visit_entry_block (Entry_block* bb);
	void visit_exit_block (Exit_block* bb);
	void visit_branch_block (Branch_block* bb);
	void visit_statement_block (Statement_block* bb);

	void visit_chi_node (Basic_block* bb, Alias_name def, Alias_name use);
	void visit_mu_node (Basic_block* bb, Alias_name use);
	void visit_phi_node (Basic_block* bb, Alias_name phi_lhs);

};

#endif // PHC_DEF_USE_WEB
