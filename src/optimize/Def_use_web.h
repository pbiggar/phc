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

#define SSA_BB			(1 << 0)
#define SSA_PHI		(1 << 1)
#define SSA_CHI		(1 << 2)
#define SSA_ALL		(SSA_BB|SSA_PHI|SSA_CHI)


class Def_use_web : virtual public GC_obj
{
	Def_use* du; 

public:
	Def_use_web (Def_use* du);

	void dump ();
	void consistency_check ();

private:

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

	SSA_use_list* get_named_uses (Alias_name* name);
	SSA_def_list* get_named_defs (Alias_name* name);

private:
	Map<long, SSA_def_list> def_ops;
	Map<long, SSA_use_list> use_ops;

	Map<Alias_name, SSA_def_list> named_defs;
	Map<Alias_name, SSA_use_list> named_uses;

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
};

#endif // PHC_DEF_USE_WEB
