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

	void visit_assign_array (Statement_block* bb, MIR::Assign_array* in);
	void visit_assign_field (Statement_block* bb, MIR::Assign_field * in);
	void visit_assign_var (Statement_block* bb, MIR::Assign_var* in);
	void visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in);
	void visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in);
	void visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in);
	void visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in);
	void visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in);
	void visit_global (Statement_block* bb, MIR::Global* in);
	void visit_pre_op (Statement_block* bb, MIR::Pre_op* in);
	void visit_assign_next (Statement_block* bb, MIR::Assign_next* in);
	void visit_return (Statement_block* bb, MIR::Return* in);
	void visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in);
	void visit_throw (Statement_block* bb, MIR::Throw* in);
	void visit_try (Statement_block* bb, MIR::Try* in);
	void visit_unset (Statement_block* bb, MIR::Unset* in);

	void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	void visit_bin_op (Statement_block* bb, MIR::Bin_op* in);
	void visit_bool (Statement_block* bb, MIR::BOOL* in);
	void visit_cast (Statement_block* bb, MIR::Cast* in);
	void visit_constant (Statement_block* bb, MIR::Constant* in);
	void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	void visit_int (Statement_block* bb, MIR::INT* in);
	void visit_isset (Statement_block* bb, MIR::Isset* in);
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_nil (Statement_block* bb, MIR::NIL* in);
	void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	void visit_real (Statement_block* bb, MIR::REAL* in);
	void visit_string (Statement_block* bb, MIR::STRING* in);
	void visit_unary_op (Statement_block* bb, MIR::Unary_op* in);
	void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
};

#endif // PHC_OPTIMIZATION_TRANSFORMER
