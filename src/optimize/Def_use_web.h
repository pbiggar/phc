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

#define SSA_BB			(1 << 0)
#define SSA_PHI		(1 << 1)
#define SSA_CHI		(1 << 2)
#define SSA_ALL		(SSA_BB|SSA_PHI|SSA_CHI)


class Def_use_web : virtual public GC_obj
{
public:
	Def_use_web (Def_use* du);

	// The analysis portion. This forms a DU-web over the data analysed.
	Def_use* du; 

	/*
	 * Flags:
	 *		SSA_BB
	 *		SSA_PHI
	 *		SSA_CHI
	 */
	// Get all operations that define USE, and that satisfy flags.
	SSA_op_list* get_defs (Alias_name use, int flags);

	// Get all operations that use DEF, and that satisfy FLAGS.
	SSA_op_list* get_uses (Alias_name def, int flags);

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
	Var_map<SSA_edge_list> def_use_chains;
	Var_map<SSA_edge_list> use_def_chains;


	void old_add_mus (Basic_block* bb, Alias_name use);
	void old_add_chis (Basic_block* bb, Alias_name def);


	void old_visit_chi_node (Basic_block* bb, Alias_name def, Alias_name use);
	void old_visit_mu_node (Basic_block* bb, Alias_name use);
	void old_visit_phi_node (Basic_block* bb, Alias_name phi_lhs);


	/*
	 * The DUW holds an ordered list of SSA_ops for each BB. An op is a use,
	 * def, may-use or may-def. These are alias_names, so that they can easily
	 * be renumbered by SSA.
	 *
	 * Seperately, there is a web over these. This is a list indexed by the
	 * alias_name of the op, and pointing to the BB is which it is created or
	 * consumed. Both uses and defs point to a list of SSA_ops (non-SSA form
	 * can have a list of defs for each use).
	 *
	 * The ops are either defs or uses, and they are any of CHI, BB and PHI,
	 * indicating which part of the statement they occur in.
	 *
	 * TODO: Should may-defs get all the uses from the BB too? I guess it
	 * depends on whether they come from the method_invocation, or whether
	 * they come from the def.
	 */
	Map<long, Alias_name_list> uses;
	Map<long, Alias_name_list> defs;
	// Uses and defs don't include the chis or phis.
	Map<long, Alias_name_list> may_defs;

public:
	void build_web (CFG* cfg);

	// Returned Alias_name*s point to the actual Alias_names, so that their SSA
	// version can be updated.
	Alias_name_list* get_uses (Basic_block* bb);
	Alias_name_list* get_defs (Basic_block* bb);
	Alias_name_list* get_may_defs (Basic_block* bb);

	// TODO: should ssa_renaming just use get_ops, so that it can update them
	// in order?

	// Get the SSA_ops from the block. Doesnt include PHIs or CHIs.
	// TODO: this includes non-block-local must defs. Probably shouldnt.
	SSA_use_list* get_block_uses (Basic_block* bb);
	SSA_def_list* get_block_defs (Basic_block* bb);

private:
	Map<long, SSA_def_list> def_ops;
	Map<long, SSA_use_list> use_ops;

};

#endif // PHC_DEF_USE_WEB
