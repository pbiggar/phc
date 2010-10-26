/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use the results of the analyses to transform the MIR. Do not handle dead
 * code.
 * */

#ifndef PHC_OPTIMIZATION_TRANSFORMER
#define PHC_OPTIMIZATION_TRANSFORMER

class Whole_program;
class Index_node;

class Optimization_transformer : public CFG_visitor
{
public:
	Whole_program* wp;
	Optimization_transformer (Whole_program*);

	void run (CFG* cfg);

	// for passing between visit_assign_var and visit_expr
	Index_node* lhs;
	bool assign_var_is_ref;

	MIR::Rvalue* get_literal (Basic_block* bb, MIR::Rvalue* in);

	virtual void visit_block (Basic_block* bb);

	const Abstract_value* get_in_abstract_value (Basic_block* bb, MIR::Rvalue* in);
	const Abstract_value* get_out_abstract_value (Basic_block* bb, MIR::Rvalue* in);
	bool rhs_is_pure (Statement_block* bb, MIR::Expr* in);

	void visit_branch_block (Branch_block* bb);

	DECLARE_STATEMENT_CFG_VISITORS
	DECLARE_EXPR_CFG_VISITORS
	MIR::Expr* transform_cast (Statement_block*, MIR::Cast*);
	void transform_eval_expr (Statement_block*, MIR::Eval_expr*, BB_list*);

private:

	void copy_in_literals (Basic_block* bb, Method_info_list* receivers, MIR::Actual_parameter_list* params);
};

#endif // PHC_OPTIMIZATION_TRANSFORMER
