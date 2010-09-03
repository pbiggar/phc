#ifndef PHC_DEF_USE_WEB
#define PHC_DEF_USE_WEB

#include "MIR.h"
#include "Edge.h"
#include "Flow_visitor.h"
#include "Visit_once.h"
#include "ssa/SSA_name.h"
#include "ssa/SSA_ops.h"
#include "ssa/Phi.h"
#include "ssi/Sigma.h"

class CFG;
class Def_use;
class Points_to;

#define SSA_BB		(1 << 0)
#define SSA_PHI		(1 << 1)
#define SSA_CHI		(1 << 2)
#define SSA_ALL		(SSA_BB|SSA_PHI|SSA_CHI)

#define SSI_SIGMA 	(1 << 3)
#define SSI_ALL		(SSI_SIGMA|SSA_ALL)

class Def_use_web : virtual public GC_obj
{
	Def_use* du; 

public:
	Def_use_web (Def_use* du);

	void dump ();
	void ssa_consistency_check ();
	void ssi_consistency_check ();

private:

public:
	void build_web (CFG* cfg, bool update);
	Def_use* get_def_use ();
	

	// Returned SSA_name*s point to the actual SSA_names, so that their SSA
	// version can be updated.
	SSA_name_list* get_uses (Basic_block* bb);
	SSA_name_list* get_defs (Basic_block* bb);
	SSA_name_list* get_may_defs (Basic_block* bb);


	// Get the SSA_ops from the block. Doesnt include PHIs or CHIs.
	// TODO: this includes non-block-local must defs. Probably shouldnt.
	SSA_use_list* get_block_uses (Basic_block* bb);
	SSA_def_list* get_block_defs (Basic_block* bb);

	SSA_use_list* get_named_uses (SSA_name* name);
	SSA_def_list* get_named_defs (SSA_name* name);

	/*
	 * Phi functions (or nodes)
	 */
public:
	// Copy the phi nodes from OTHER, including the phi args from OTHER's
	// incoming edges.
	void copy_phi_nodes (Basic_block* source, Basic_block* dest);
	void copy_phi_map (Edge* source, Edge* dest);

	// For SSA creation/destruction
	void add_phi_node (Basic_block* bb, SSA_name phi_lhs);
	bool has_phi_node (Basic_block* bb, SSA_name phi_lhs);
	void add_phi_arg (Basic_block* bb, SSA_name phi_lhs, int version, Edge* edge);
	void remove_phi_nodes (Basic_block* bb);

	// These are stored using operator< in VARIABLE_NAME, which changes when
	// there VARIABLE_NAME changes.
	void update_phi_node (Basic_block* bb, SSA_name old_phi_lhs, SSA_name new_phi_lhs);

	// Remove a node (including its args from the edges)
	void remove_phi_node (Basic_block* bb, SSA_name phi_lhs);

	// If the nodes have 1 argument, remove them, putting them into
	// predecessors.
	void fix_solo_phi_args (Basic_block* bb);

	// Get the arguments with VARIABLE_NAME as the lhs.
	SSA_name_list* get_phi_args (Basic_block* bb, SSA_name phi_lhs);
	
	Set<SSA_name>* get_phi_lhss (Basic_block* bb);

	SSA_name get_phi_arg_for_edge (Edge*, SSA_name phi_lhs);
	void set_phi_arg_for_edge (Edge*, SSA_name phi_lhs, SSA_name arg);

	Edge *get_edge_for_phi_arg(SSA_name arg);

	/*
	 * Sigma functions (or nodes)
	 */
public:
	// For SSI creation/destruction
	void add_sigma_node(Basic_block *bb, SSA_name sigma_rhs);
	bool has_sigma_node(Basic_block *bb, SSA_name sigma_rhs);
	void add_sigma_arg(Basic_block *bb, SSA_name sigma_rhs, int version, Edge *edge);
	void remove_sigma_nodes(Basic_block *bb);

	// These are stored using operator< in VARIABLE_NAME, which changes when
	// there VARIABLE_NAME changes.
	void update_sigma_node(Basic_block *bb, SSA_name old_sigma_rhs, SSA_name new_sigma_rhs);

	// Remove a node (including its args from the edges)
	void remove_sigma_node(Basic_block *bb, SSA_name sigma_rhs);

	// Get the arguments with VARIABLE_NAME as the lhs.
	SSA_name_list *get_sigma_args(Basic_block *bb, SSA_name sigma_rhs);
	Set<SSA_name> *get_sigma_rhss (Basic_block *bb);

	SSA_name get_sigma_arg_for_edge(Edge *, SSA_name sigma_rhs);
	void set_sigma_arg_for_edge(Edge *, SSA_name sigma_rhs, SSA_name arg);

	Edge *get_edge_for_sigma_arg(SSA_name arg);
private:

	Map<long, SSA_def_list> def_ops;
	Map<long, SSA_use_list> use_ops;

	Map<std::string, SSA_def_list> named_defs;
	Map<std::string, SSA_use_list> named_uses;

	// Instead of an explicit phi node, store the phi->lhs here, mapped by BB.
	Map<long, Set<SSA_name> > phi_lhss;

	// Store phi arguments by edge. Then they can be updated all-at-once.
	Map<Edge*, Phi_map> phi_rhss;

	// Dual for Sigma's. sigma->rhs will be indexed by edge and sigma->lhs by basic block id.
	// Instead of an explicit phi node, store the phi->lhs here, mapped by BB.
	Map<long, Set<SSA_name> > sigma_rhss;
	Map<Edge *, Sigma_map> sigma_lhss;

	/*
	 * The DUW holds an ordered list of SSA_ops for each BB. An op is a use,
	 * def or may-def (may-uses are marked as full uses). These are alias_names,
	 * so that they can easily be renumbered by SSA.
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
	Map<long, SSA_name_list> uses;
	Map<long, SSA_name_list> defs;

	// Uses and defs don't include the chis or phis.
	Map<long, SSA_name_list> may_defs;

	Map<long, SSA_name_list> phi_uses;
	Map<long, SSA_name_list> phi_defs;

	Map<long, SSA_name_list> sigma_uses;
	Map<long, SSA_name_list> sigma_defs;

};

#endif // PHC_DEF_USE_WEB

