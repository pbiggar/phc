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
	SSA_op_list* old_get_defs (Alias_name use, int flags);

	// Get all operations that use DEF, and that satisfy FLAGS.
	SSA_op_list* old_get_uses (Alias_name def, int flags);

	// Get the variables defined/used in BB
	old_Alias_name_list* old_get_block_defs (Basic_block* bb, int flags);
	old_Alias_name_list* old_get_block_uses (Basic_block* bb, int flags);

	/*
	 * All operations in this class go through either get_defs or get_uses.
	 * They simply call it with different flags.
	 */

	// Return whether USE has a defining statement (vs being uninitialized).
	bool old_has_def (Alias_name use);

	// Return the SSA_op defining USE.
	SSA_op* old_get_def (Alias_name use);

	void dump ();
	void consistency_check ();

private:

	/*
	 * Old stuff
	 */

	// Add defs or uses
	void old_add_use (Alias_name def, SSA_op* use);
	void old_add_def (Alias_name use, SSA_op* def);
	void old_add_may_def (Alias_name var, SSA_op* def);
	void old_add_may_use (Alias_name var, SSA_op* use);


	// The indexing variable may not be the correct var, while the vars in the
	// SSA_edge_list will be the correct vars. The indexing variable is just
	// for indexing, and it can index multiple vars, so we cant say anythng
	// about it.
	Var_map<SSA_edge_list> old_def_use_chains;
	Var_map<SSA_edge_list> old_use_def_chains;


	void old_add_mus (Basic_block* bb, Alias_name use);
	void old_add_chis (Basic_block* bb, Alias_name def);


	void old_visit_chi_node (Basic_block* bb, Alias_name def, Alias_name use);
	void old_visit_mu_node (Basic_block* bb, Alias_name use);
	void old_visit_phi_node (Basic_block* bb, Alias_name phi_lhs);


	/*
	 * New stuff
	 */
	void add_use (Basic_block* bb, Alias_name* def);
	void add_def (Basic_block* bb, Alias_name* use);
	void add_may_def (Basic_block* bb, Alias_name* var);

	// Uses doesn't include the RHS of may_defs or Phis.
	Map<long, Alias_name_list> uses;
	// defs doesn't include the LHS of may_defs or Phis.
	Map<long, Alias_name_list> defs;

	Map<long, Alias_name_list> may_defs;

	void visit_entry_block (Entry_block* bb);
	void visit_exit_block (Exit_block* bb);
	void visit_branch_block (Branch_block* bb);
	void visit_statement_block (Statement_block* bb);

public:
	// Returns points to the actual Alias_names, so that their SSA version can
	// be updated. (Still separates maydefs from defs/uses).
	Alias_name_list* get_uses (Basic_block* bb);
	Alias_name_list* get_defs (Basic_block* bb);
	Alias_name_list* get_may_defs (Basic_block* bb);
};

#endif // PHC_DEF_USE_WEB
