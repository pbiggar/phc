#ifndef PHC_DEF_USE
#define PHC_DEF_USE

#include "MIR.h"
#include "Set.h"
#include "Flow_visitor.h"

class CFG;

// We dont want to put this into mir.tea. Its a long way from where its used.
class Def_use
{
public:
	static Set* get_defs (MIR::Statement* statement);
	static Set* get_uses (MIR::Statement* statement);
};

class Def_use_web : public Flow_visitor
{
public:
	Def_use_web (CFG* cfg);

	map<MIR::VARIABLE_NAME*, SSA_edge_list*> def_use_chains;
	map<MIR::VARIABLE_NAME*, SSA_edge*> use_def_chains;

	SSA_edge_list* get_def_use_edges (MIR::VARIABLE_NAME* def);
	SSA_edge* get_use_def_edges (MIR::VARIABLE_NAME* use);
	void add_def_use_edge (MIR::VARIABLE_NAME* use, SSA_edge* edge);

	void visit_entry_block (Entry_block*);
	void visit_empty_block (Empty_block*);
	void visit_exit_block (Exit_block*);
	void visit_branch_block (Branch_block* bb);

	void visit_assign_array (Statement_block*, MIR::Assign_array*);
	void visit_assign_field (Statement_block*, MIR::Assign_field *);
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	void visit_global (Statement_block*, MIR::Global* in);
	void visit_param_is_ref (Statement_block*, MIR::Param_is_ref*);
	void visit_pre_op (Statement_block*, MIR::Pre_op*);
	void visit_push_array (Statement_block*, MIR::Push_array*);
	void visit_return (Statement_block*, MIR::Return*);
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	void visit_throw (Statement_block*, MIR::Throw*);
	void visit_try (Statement_block*, MIR::Try*);
	void visit_unset (Statement_block*, MIR::Unset*);
};

#endif // PHC_DEF_USE
