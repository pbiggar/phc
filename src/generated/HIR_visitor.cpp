#include "HIR_visitor.h"

namespace HIR{
Visitor::~Visitor()
{
}

// Invoked before the children are visited
void Visitor::pre_node(Node* in)
{
}

void Visitor::pre_php_script(PHP_script* in)
{
}

void Visitor::pre_statement(Statement* in)
{
}

void Visitor::pre_class_def(Class_def* in)
{
}

void Visitor::pre_class_mod(Class_mod* in)
{
}

void Visitor::pre_interface_def(Interface_def* in)
{
}

void Visitor::pre_member(Member* in)
{
}

void Visitor::pre_method(Method* in)
{
}

void Visitor::pre_signature(Signature* in)
{
}

void Visitor::pre_method_mod(Method_mod* in)
{
}

void Visitor::pre_formal_parameter(Formal_parameter* in)
{
}

void Visitor::pre_type(Type* in)
{
}

void Visitor::pre_attribute(Attribute* in)
{
}

void Visitor::pre_attr_mod(Attr_mod* in)
{
}

void Visitor::pre_name_with_default(Name_with_default* in)
{
}

void Visitor::pre_if(If* in)
{
}

void Visitor::pre_loop(Loop* in)
{
}

void Visitor::pre_foreach(Foreach* in)
{
}

void Visitor::pre_break(Break* in)
{
}

void Visitor::pre_continue(Continue* in)
{
}

void Visitor::pre_return(Return* in)
{
}

void Visitor::pre_static_declaration(Static_declaration* in)
{
}

void Visitor::pre_global(Global* in)
{
}

void Visitor::pre_try(Try* in)
{
}

void Visitor::pre_catch(Catch* in)
{
}

void Visitor::pre_throw(Throw* in)
{
}

void Visitor::pre_assign_var(Assign_var* in)
{
}

void Visitor::pre_assign_target(Assign_target* in)
{
}

void Visitor::pre_assign_array(Assign_array* in)
{
}

void Visitor::pre_assign_var_var(Assign_var_var* in)
{
}

void Visitor::pre_push_array(Push_array* in)
{
}

void Visitor::pre_pre_op(Pre_op* in)
{
}

void Visitor::pre_eval_expr(Eval_expr* in)
{
}

void Visitor::pre_expr(Expr* in)
{
}

void Visitor::pre_literal(Literal* in)
{
}

void Visitor::pre_target_expr(Target_expr* in)
{
}

void Visitor::pre_variable_name(Variable_name* in)
{
}

void Visitor::pre_variable_variable(Variable_variable* in)
{
}

void Visitor::pre_index_array(Index_array* in)
{
}

void Visitor::pre_cast(Cast* in)
{
}

void Visitor::pre_unary_op(Unary_op* in)
{
}

void Visitor::pre_bin_op(Bin_op* in)
{
}

void Visitor::pre_constant(Constant* in)
{
}

void Visitor::pre_instanceof(Instanceof* in)
{
}

void Visitor::pre_target(Target* in)
{
}

void Visitor::pre_method_invocation(Method_invocation* in)
{
}

void Visitor::pre_method_name(Method_name* in)
{
}

void Visitor::pre_variable_method(Variable_method* in)
{
}

void Visitor::pre_actual_parameter(Actual_parameter* in)
{
}

void Visitor::pre_new(New* in)
{
}

void Visitor::pre_class_name(Class_name* in)
{
}

void Visitor::pre_variable_class(Variable_class* in)
{
}

void Visitor::pre_static_value(Static_value* in)
{
}

void Visitor::pre_static_array(Static_array* in)
{
}

void Visitor::pre_static_array_elem(Static_array_elem* in)
{
}

void Visitor::pre_static_array_key(Static_array_key* in)
{
}

void Visitor::pre_identifier(Identifier* in)
{
}

void Visitor::pre_foreign(Foreign* in)
{
}

void Visitor::pre_class_name(CLASS_NAME* in)
{
}

void Visitor::pre_interface_name(INTERFACE_NAME* in)
{
}

void Visitor::pre_method_name(METHOD_NAME* in)
{
}

void Visitor::pre_variable_name(VARIABLE_NAME* in)
{
}

void Visitor::pre_op(OP* in)
{
}

void Visitor::pre_int(INT* in)
{
}

void Visitor::pre_real(REAL* in)
{
}

void Visitor::pre_string(STRING* in)
{
}

void Visitor::pre_bool(BOOL* in)
{
}

void Visitor::pre_nil(NIL* in)
{
}

void Visitor::pre_cast(CAST* in)
{
}

void Visitor::pre_constant_name(CONSTANT_NAME* in)
{
}

// Invoked after the children have been visited
void Visitor::post_node(Node* in)
{
}

void Visitor::post_php_script(PHP_script* in)
{
}

void Visitor::post_statement(Statement* in)
{
}

void Visitor::post_class_def(Class_def* in)
{
}

void Visitor::post_class_mod(Class_mod* in)
{
}

void Visitor::post_interface_def(Interface_def* in)
{
}

void Visitor::post_member(Member* in)
{
}

void Visitor::post_method(Method* in)
{
}

void Visitor::post_signature(Signature* in)
{
}

void Visitor::post_method_mod(Method_mod* in)
{
}

void Visitor::post_formal_parameter(Formal_parameter* in)
{
}

void Visitor::post_type(Type* in)
{
}

void Visitor::post_attribute(Attribute* in)
{
}

void Visitor::post_attr_mod(Attr_mod* in)
{
}

void Visitor::post_name_with_default(Name_with_default* in)
{
}

void Visitor::post_if(If* in)
{
}

void Visitor::post_loop(Loop* in)
{
}

void Visitor::post_foreach(Foreach* in)
{
}

void Visitor::post_break(Break* in)
{
}

void Visitor::post_continue(Continue* in)
{
}

void Visitor::post_return(Return* in)
{
}

void Visitor::post_static_declaration(Static_declaration* in)
{
}

void Visitor::post_global(Global* in)
{
}

void Visitor::post_try(Try* in)
{
}

void Visitor::post_catch(Catch* in)
{
}

void Visitor::post_throw(Throw* in)
{
}

void Visitor::post_assign_var(Assign_var* in)
{
}

void Visitor::post_assign_target(Assign_target* in)
{
}

void Visitor::post_assign_array(Assign_array* in)
{
}

void Visitor::post_assign_var_var(Assign_var_var* in)
{
}

void Visitor::post_push_array(Push_array* in)
{
}

void Visitor::post_pre_op(Pre_op* in)
{
}

void Visitor::post_eval_expr(Eval_expr* in)
{
}

void Visitor::post_expr(Expr* in)
{
}

void Visitor::post_literal(Literal* in)
{
}

void Visitor::post_target_expr(Target_expr* in)
{
}

void Visitor::post_variable_name(Variable_name* in)
{
}

void Visitor::post_variable_variable(Variable_variable* in)
{
}

void Visitor::post_index_array(Index_array* in)
{
}

void Visitor::post_cast(Cast* in)
{
}

void Visitor::post_unary_op(Unary_op* in)
{
}

void Visitor::post_bin_op(Bin_op* in)
{
}

void Visitor::post_constant(Constant* in)
{
}

void Visitor::post_instanceof(Instanceof* in)
{
}

void Visitor::post_target(Target* in)
{
}

void Visitor::post_method_invocation(Method_invocation* in)
{
}

void Visitor::post_method_name(Method_name* in)
{
}

void Visitor::post_variable_method(Variable_method* in)
{
}

void Visitor::post_actual_parameter(Actual_parameter* in)
{
}

void Visitor::post_new(New* in)
{
}

void Visitor::post_class_name(Class_name* in)
{
}

void Visitor::post_variable_class(Variable_class* in)
{
}

void Visitor::post_static_value(Static_value* in)
{
}

void Visitor::post_static_array(Static_array* in)
{
}

void Visitor::post_static_array_elem(Static_array_elem* in)
{
}

void Visitor::post_static_array_key(Static_array_key* in)
{
}

void Visitor::post_identifier(Identifier* in)
{
}

void Visitor::post_foreign(Foreign* in)
{
}

void Visitor::post_class_name(CLASS_NAME* in)
{
}

void Visitor::post_interface_name(INTERFACE_NAME* in)
{
}

void Visitor::post_method_name(METHOD_NAME* in)
{
}

void Visitor::post_variable_name(VARIABLE_NAME* in)
{
}

void Visitor::post_op(OP* in)
{
}

void Visitor::post_int(INT* in)
{
}

void Visitor::post_real(REAL* in)
{
}

void Visitor::post_string(STRING* in)
{
}

void Visitor::post_bool(BOOL* in)
{
}

void Visitor::post_nil(NIL* in)
{
}

void Visitor::post_cast(CAST* in)
{
}

void Visitor::post_constant_name(CONSTANT_NAME* in)
{
}

// Visit the children of a node
void Visitor::children_php_script(PHP_script* in)
{
    visit_statement_list(in->statements);
}

void Visitor::children_class_def(Class_def* in)
{
    visit_class_mod(in->class_mod);
    visit_class_name(in->class_name);
    visit_optional (in->extends == NULL);
	visit_class_name(in->extends);
    visit_interface_name_list(in->implements);
    visit_member_list(in->members);
}

void Visitor::children_class_mod(Class_mod* in)
{
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void Visitor::children_interface_def(Interface_def* in)
{
    visit_interface_name(in->interface_name);
    visit_interface_name_list(in->extends);
    visit_member_list(in->members);
}

void Visitor::children_method(Method* in)
{
    visit_signature(in->signature);
    visit_optional (in->statements == NULL);
	visit_statement_list(in->statements);
}

void Visitor::children_signature(Signature* in)
{
    visit_method_mod(in->method_mod);
    visit_marker("is_ref", in->is_ref);
    visit_method_name(in->method_name);
    visit_formal_parameter_list(in->formal_parameters);
}

void Visitor::children_method_mod(Method_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void Visitor::children_formal_parameter(Formal_parameter* in)
{
    visit_type(in->type);
    visit_marker("is_ref", in->is_ref);
    visit_name_with_default(in->var);
}

void Visitor::children_type(Type* in)
{
    visit_optional (in->class_name == NULL);
	visit_class_name(in->class_name);
}

void Visitor::children_attribute(Attribute* in)
{
    visit_attr_mod(in->attr_mod);
    visit_name_with_default(in->var);
}

void Visitor::children_attr_mod(Attr_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_const", in->is_const);
}

void Visitor::children_name_with_default(Name_with_default* in)
{
    visit_variable_name(in->variable_name);
    visit_optional (in->default_value == NULL);
	visit_static_value(in->default_value);
}

void Visitor::children_if(If* in)
{
    visit_variable_name(in->variable_name);
    visit_statement_list(in->iftrue);
    visit_statement_list(in->iffalse);
}

void Visitor::children_loop(Loop* in)
{
    visit_statement_list(in->statements);
}

void Visitor::children_foreach(Foreach* in)
{
    visit_variable_name(in->arr);
    visit_optional (in->key == NULL);
	visit_variable_name(in->key);
    visit_marker("is_ref", in->is_ref);
    visit_variable_name(in->val);
    visit_statement_list(in->statements);
}

void Visitor::children_break(Break* in)
{
    visit_optional (in->expr == NULL);
	visit_expr(in->expr);
}

void Visitor::children_continue(Continue* in)
{
    visit_optional (in->expr == NULL);
	visit_expr(in->expr);
}

void Visitor::children_return(Return* in)
{
    visit_expr(in->expr);
}

void Visitor::children_static_declaration(Static_declaration* in)
{
    visit_name_with_default(in->var);
}

void Visitor::children_global(Global* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_try(Try* in)
{
    visit_statement_list(in->statements);
    visit_catch_list(in->catches);
}

void Visitor::children_catch(Catch* in)
{
    visit_class_name(in->class_name);
    visit_variable_name(in->variable_name);
    visit_statement_list(in->statements);
}

void Visitor::children_throw(Throw* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_assign_var(Assign_var* in)
{
    visit_variable_name(in->lhs);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->rhs);
}

void Visitor::children_assign_target(Assign_target* in)
{
    visit_target(in->target);
    visit_variable_name(in->lhs);
    visit_marker("is_ref", in->is_ref);
    visit_variable_name(in->rhs);
}

void Visitor::children_assign_array(Assign_array* in)
{
    visit_variable_name(in->lhs);
    visit_variable_name(in->index);
    visit_marker("is_ref", in->is_ref);
    visit_variable_name(in->rhs);
}

void Visitor::children_assign_var_var(Assign_var_var* in)
{
    visit_variable_name(in->lhs);
    visit_marker("is_ref", in->is_ref);
    visit_variable_name(in->rhs);
}

void Visitor::children_push_array(Push_array* in)
{
    visit_variable_name(in->lhs);
    visit_marker("is_ref", in->is_ref);
    visit_variable_name(in->rhs);
}

void Visitor::children_pre_op(Pre_op* in)
{
    visit_op(in->op);
    visit_variable_name(in->variable_name);
}

void Visitor::children_eval_expr(Eval_expr* in)
{
    visit_expr(in->expr);
}

void Visitor::children_target_expr(Target_expr* in)
{
    visit_target(in->target);
    visit_variable_name(in->variable_name);
}

void Visitor::children_variable_variable(Variable_variable* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_index_array(Index_array* in)
{
    visit_variable_name(in->variable_name);
    visit_variable_name(in->index);
}

void Visitor::children_cast(Cast* in)
{
    visit_cast(in->cast);
    visit_variable_name(in->variable_name);
}

void Visitor::children_unary_op(Unary_op* in)
{
    visit_op(in->op);
    visit_variable_name(in->variable_name);
}

void Visitor::children_bin_op(Bin_op* in)
{
    visit_variable_name(in->left);
    visit_op(in->op);
    visit_variable_name(in->right);
}

void Visitor::children_constant(Constant* in)
{
    visit_optional (in->class_name == NULL);
	visit_class_name(in->class_name);
    visit_constant_name(in->constant_name);
}

void Visitor::children_instanceof(Instanceof* in)
{
    visit_variable_name(in->variable_name);
    visit_class_name(in->class_name);
}

void Visitor::children_method_invocation(Method_invocation* in)
{
    visit_optional (in->target == NULL);
	visit_target(in->target);
    visit_method_name(in->method_name);
    visit_actual_parameter_list(in->actual_parameters);
}

void Visitor::children_variable_method(Variable_method* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_actual_parameter(Actual_parameter* in)
{
    visit_marker("is_ref", in->is_ref);
    visit_optional (in->target == NULL);
	visit_target(in->target);
    visit_variable_name(in->variable_name);
    visit_variable_name_list(in->array_indices);
}

void Visitor::children_new(New* in)
{
    visit_class_name(in->class_name);
    visit_actual_parameter_list(in->actual_parameters);
}

void Visitor::children_variable_class(Variable_class* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_static_array(Static_array* in)
{
    visit_static_array_elem_list(in->static_array_elems);
}

void Visitor::children_static_array_elem(Static_array_elem* in)
{
    visit_optional (in->key == NULL);
	visit_static_array_key(in->key);
    visit_marker("is_ref", in->is_ref);
    visit_static_value(in->val);
}

void Visitor::children_foreign(Foreign* in)
{
}

// Tokens don't have children, so these methods do nothing by default
void Visitor::children_class_name(CLASS_NAME* in)
{
}

void Visitor::children_interface_name(INTERFACE_NAME* in)
{
}

void Visitor::children_method_name(METHOD_NAME* in)
{
}

void Visitor::children_variable_name(VARIABLE_NAME* in)
{
}

void Visitor::children_op(OP* in)
{
}

void Visitor::children_int(INT* in)
{
}

void Visitor::children_real(REAL* in)
{
}

void Visitor::children_string(STRING* in)
{
}

void Visitor::children_bool(BOOL* in)
{
}

void Visitor::children_nil(NIL* in)
{
}

void Visitor::children_cast(CAST* in)
{
}

void Visitor::children_constant_name(CONSTANT_NAME* in)
{
}

// Unparser support
void Visitor::visit_marker(char const* name, bool value)
{
}

void Visitor::visit_type(char const* name_space, char const* type_id)
{
}

void Visitor::visit_optional(bool is_null)
{
}

void Visitor::visit_null(char const* name_space, char const* type_id)
{
}

void Visitor::visit_null_list(char const* name_space, char const* type_id)
{
}

void Visitor::pre_list(char const* name_space, char const* type_id, int size, bool nullable_elements)
{
}

void Visitor::post_list(char const* name_space, char const* type_id, int size, bool nullable_elements)
{
}

// Invoke the chain of pre-visit methods along the inheritance hierachy
// Do not override unless you know what you are doing
void Visitor::pre_php_script_chain(PHP_script* in)
{
    pre_node((Node*) in);
    pre_php_script((PHP_script*) in);
}

void Visitor::pre_class_def_chain(Class_def* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_class_def((Class_def*) in);
}

void Visitor::pre_class_mod_chain(Class_mod* in)
{
    pre_node((Node*) in);
    pre_class_mod((Class_mod*) in);
}

void Visitor::pre_interface_def_chain(Interface_def* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_interface_def((Interface_def*) in);
}

void Visitor::pre_method_chain(Method* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_member((Member*) in);
    pre_method((Method*) in);
}

void Visitor::pre_signature_chain(Signature* in)
{
    pre_node((Node*) in);
    pre_signature((Signature*) in);
}

void Visitor::pre_method_mod_chain(Method_mod* in)
{
    pre_node((Node*) in);
    pre_method_mod((Method_mod*) in);
}

void Visitor::pre_formal_parameter_chain(Formal_parameter* in)
{
    pre_node((Node*) in);
    pre_formal_parameter((Formal_parameter*) in);
}

void Visitor::pre_type_chain(Type* in)
{
    pre_node((Node*) in);
    pre_type((Type*) in);
}

void Visitor::pre_attribute_chain(Attribute* in)
{
    pre_node((Node*) in);
    pre_member((Member*) in);
    pre_attribute((Attribute*) in);
}

void Visitor::pre_attr_mod_chain(Attr_mod* in)
{
    pre_node((Node*) in);
    pre_attr_mod((Attr_mod*) in);
}

void Visitor::pre_name_with_default_chain(Name_with_default* in)
{
    pre_node((Node*) in);
    pre_name_with_default((Name_with_default*) in);
}

void Visitor::pre_if_chain(If* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_if((If*) in);
}

void Visitor::pre_loop_chain(Loop* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_loop((Loop*) in);
}

void Visitor::pre_foreach_chain(Foreach* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_foreach((Foreach*) in);
}

void Visitor::pre_break_chain(Break* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_break((Break*) in);
}

void Visitor::pre_continue_chain(Continue* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_continue((Continue*) in);
}

void Visitor::pre_return_chain(Return* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_return((Return*) in);
}

void Visitor::pre_static_declaration_chain(Static_declaration* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_static_declaration((Static_declaration*) in);
}

void Visitor::pre_global_chain(Global* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_global((Global*) in);
}

void Visitor::pre_try_chain(Try* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_try((Try*) in);
}

void Visitor::pre_catch_chain(Catch* in)
{
    pre_node((Node*) in);
    pre_catch((Catch*) in);
}

void Visitor::pre_throw_chain(Throw* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_throw((Throw*) in);
}

void Visitor::pre_assign_var_chain(Assign_var* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_assign_var((Assign_var*) in);
}

void Visitor::pre_assign_target_chain(Assign_target* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_assign_target((Assign_target*) in);
}

void Visitor::pre_assign_array_chain(Assign_array* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_assign_array((Assign_array*) in);
}

void Visitor::pre_assign_var_var_chain(Assign_var_var* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_assign_var_var((Assign_var_var*) in);
}

void Visitor::pre_push_array_chain(Push_array* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_push_array((Push_array*) in);
}

void Visitor::pre_pre_op_chain(Pre_op* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_pre_op((Pre_op*) in);
}

void Visitor::pre_eval_expr_chain(Eval_expr* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_eval_expr((Eval_expr*) in);
}

void Visitor::pre_target_expr_chain(Target_expr* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_target_expr((Target_expr*) in);
}

void Visitor::pre_variable_variable_chain(Variable_variable* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_variable_name((Variable_name*) in);
    pre_variable_variable((Variable_variable*) in);
}

void Visitor::pre_index_array_chain(Index_array* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_index_array((Index_array*) in);
}

void Visitor::pre_cast_chain(Cast* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_cast((Cast*) in);
}

void Visitor::pre_unary_op_chain(Unary_op* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_unary_op((Unary_op*) in);
}

void Visitor::pre_bin_op_chain(Bin_op* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_bin_op((Bin_op*) in);
}

void Visitor::pre_constant_chain(Constant* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_static_value((Static_value*) in);
    pre_static_array_key((Static_array_key*) in);
    pre_constant((Constant*) in);
}

void Visitor::pre_instanceof_chain(Instanceof* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_instanceof((Instanceof*) in);
}

void Visitor::pre_method_invocation_chain(Method_invocation* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_method_invocation((Method_invocation*) in);
}

void Visitor::pre_variable_method_chain(Variable_method* in)
{
    pre_node((Node*) in);
    pre_method_name((Method_name*) in);
    pre_variable_method((Variable_method*) in);
}

void Visitor::pre_actual_parameter_chain(Actual_parameter* in)
{
    pre_node((Node*) in);
    pre_actual_parameter((Actual_parameter*) in);
}

void Visitor::pre_new_chain(New* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_new((New*) in);
}

void Visitor::pre_variable_class_chain(Variable_class* in)
{
    pre_node((Node*) in);
    pre_class_name((Class_name*) in);
    pre_variable_class((Variable_class*) in);
}

void Visitor::pre_static_array_chain(Static_array* in)
{
    pre_node((Node*) in);
    pre_static_value((Static_value*) in);
    pre_static_array((Static_array*) in);
}

void Visitor::pre_static_array_elem_chain(Static_array_elem* in)
{
    pre_node((Node*) in);
    pre_static_array_elem((Static_array_elem*) in);
}

void Visitor::pre_foreign_chain(Foreign* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_expr((Expr*) in);
    pre_foreign((Foreign*) in);
}

void Visitor::pre_class_name_chain(CLASS_NAME* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_class_name((Class_name*) in);
    pre_identifier((Identifier*) in);
    pre_class_name((CLASS_NAME*) in);
}

void Visitor::pre_interface_name_chain(INTERFACE_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_interface_name((INTERFACE_NAME*) in);
}

void Visitor::pre_method_name_chain(METHOD_NAME* in)
{
    pre_node((Node*) in);
    pre_method_name((Method_name*) in);
    pre_identifier((Identifier*) in);
    pre_method_name((METHOD_NAME*) in);
}

void Visitor::pre_variable_name_chain(VARIABLE_NAME* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_variable_name((Variable_name*) in);
    pre_target((Target*) in);
    pre_identifier((Identifier*) in);
    pre_variable_name((VARIABLE_NAME*) in);
}

void Visitor::pre_op_chain(OP* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_op((OP*) in);
}

void Visitor::pre_int_chain(INT* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_static_value((Static_value*) in);
    pre_static_array_key((Static_array_key*) in);
    pre_literal((Literal*) in);
    pre_int((INT*) in);
}

void Visitor::pre_real_chain(REAL* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_static_value((Static_value*) in);
    pre_static_array_key((Static_array_key*) in);
    pre_literal((Literal*) in);
    pre_real((REAL*) in);
}

void Visitor::pre_string_chain(STRING* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_static_value((Static_value*) in);
    pre_static_array_key((Static_array_key*) in);
    pre_literal((Literal*) in);
    pre_string((STRING*) in);
}

void Visitor::pre_bool_chain(BOOL* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_static_value((Static_value*) in);
    pre_static_array_key((Static_array_key*) in);
    pre_literal((Literal*) in);
    pre_bool((BOOL*) in);
}

void Visitor::pre_nil_chain(NIL* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_static_value((Static_value*) in);
    pre_static_array_key((Static_array_key*) in);
    pre_literal((Literal*) in);
    pre_nil((NIL*) in);
}

void Visitor::pre_cast_chain(CAST* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_cast((CAST*) in);
}

void Visitor::pre_constant_name_chain(CONSTANT_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_constant_name((CONSTANT_NAME*) in);
}

// Invoke the chain of post-visit methods along the inheritance hierarchy
// (invoked in opposite order to the pre-chain)
// Do not override unless you know what you are doing
void Visitor::post_php_script_chain(PHP_script* in)
{
    post_php_script((PHP_script*) in);
    post_node((Node*) in);
}

void Visitor::post_class_def_chain(Class_def* in)
{
    post_class_def((Class_def*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_class_mod_chain(Class_mod* in)
{
    post_class_mod((Class_mod*) in);
    post_node((Node*) in);
}

void Visitor::post_interface_def_chain(Interface_def* in)
{
    post_interface_def((Interface_def*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_method_chain(Method* in)
{
    post_method((Method*) in);
    post_member((Member*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_signature_chain(Signature* in)
{
    post_signature((Signature*) in);
    post_node((Node*) in);
}

void Visitor::post_method_mod_chain(Method_mod* in)
{
    post_method_mod((Method_mod*) in);
    post_node((Node*) in);
}

void Visitor::post_formal_parameter_chain(Formal_parameter* in)
{
    post_formal_parameter((Formal_parameter*) in);
    post_node((Node*) in);
}

void Visitor::post_type_chain(Type* in)
{
    post_type((Type*) in);
    post_node((Node*) in);
}

void Visitor::post_attribute_chain(Attribute* in)
{
    post_attribute((Attribute*) in);
    post_member((Member*) in);
    post_node((Node*) in);
}

void Visitor::post_attr_mod_chain(Attr_mod* in)
{
    post_attr_mod((Attr_mod*) in);
    post_node((Node*) in);
}

void Visitor::post_name_with_default_chain(Name_with_default* in)
{
    post_name_with_default((Name_with_default*) in);
    post_node((Node*) in);
}

void Visitor::post_if_chain(If* in)
{
    post_if((If*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_loop_chain(Loop* in)
{
    post_loop((Loop*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_chain(Foreach* in)
{
    post_foreach((Foreach*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_break_chain(Break* in)
{
    post_break((Break*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_continue_chain(Continue* in)
{
    post_continue((Continue*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_return_chain(Return* in)
{
    post_return((Return*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_static_declaration_chain(Static_declaration* in)
{
    post_static_declaration((Static_declaration*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_global_chain(Global* in)
{
    post_global((Global*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_try_chain(Try* in)
{
    post_try((Try*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_catch_chain(Catch* in)
{
    post_catch((Catch*) in);
    post_node((Node*) in);
}

void Visitor::post_throw_chain(Throw* in)
{
    post_throw((Throw*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_assign_var_chain(Assign_var* in)
{
    post_assign_var((Assign_var*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_assign_target_chain(Assign_target* in)
{
    post_assign_target((Assign_target*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_assign_array_chain(Assign_array* in)
{
    post_assign_array((Assign_array*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_assign_var_var_chain(Assign_var_var* in)
{
    post_assign_var_var((Assign_var_var*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_push_array_chain(Push_array* in)
{
    post_push_array((Push_array*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_pre_op_chain(Pre_op* in)
{
    post_pre_op((Pre_op*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_eval_expr_chain(Eval_expr* in)
{
    post_eval_expr((Eval_expr*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_target_expr_chain(Target_expr* in)
{
    post_target_expr((Target_expr*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_variable_variable_chain(Variable_variable* in)
{
    post_variable_variable((Variable_variable*) in);
    post_variable_name((Variable_name*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_index_array_chain(Index_array* in)
{
    post_index_array((Index_array*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_cast_chain(Cast* in)
{
    post_cast((Cast*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_unary_op_chain(Unary_op* in)
{
    post_unary_op((Unary_op*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_bin_op_chain(Bin_op* in)
{
    post_bin_op((Bin_op*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_constant_chain(Constant* in)
{
    post_constant((Constant*) in);
    post_static_array_key((Static_array_key*) in);
    post_static_value((Static_value*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_instanceof_chain(Instanceof* in)
{
    post_instanceof((Instanceof*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_method_invocation_chain(Method_invocation* in)
{
    post_method_invocation((Method_invocation*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_variable_method_chain(Variable_method* in)
{
    post_variable_method((Variable_method*) in);
    post_method_name((Method_name*) in);
    post_node((Node*) in);
}

void Visitor::post_actual_parameter_chain(Actual_parameter* in)
{
    post_actual_parameter((Actual_parameter*) in);
    post_node((Node*) in);
}

void Visitor::post_new_chain(New* in)
{
    post_new((New*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_variable_class_chain(Variable_class* in)
{
    post_variable_class((Variable_class*) in);
    post_class_name((Class_name*) in);
    post_node((Node*) in);
}

void Visitor::post_static_array_chain(Static_array* in)
{
    post_static_array((Static_array*) in);
    post_static_value((Static_value*) in);
    post_node((Node*) in);
}

void Visitor::post_static_array_elem_chain(Static_array_elem* in)
{
    post_static_array_elem((Static_array_elem*) in);
    post_node((Node*) in);
}

void Visitor::post_foreign_chain(Foreign* in)
{
    post_foreign((Foreign*) in);
    post_expr((Expr*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_class_name_chain(CLASS_NAME* in)
{
    post_class_name((CLASS_NAME*) in);
    post_identifier((Identifier*) in);
    post_class_name((Class_name*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_interface_name_chain(INTERFACE_NAME* in)
{
    post_interface_name((INTERFACE_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_method_name_chain(METHOD_NAME* in)
{
    post_method_name((METHOD_NAME*) in);
    post_identifier((Identifier*) in);
    post_method_name((Method_name*) in);
    post_node((Node*) in);
}

void Visitor::post_variable_name_chain(VARIABLE_NAME* in)
{
    post_variable_name((VARIABLE_NAME*) in);
    post_identifier((Identifier*) in);
    post_target((Target*) in);
    post_variable_name((Variable_name*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_op_chain(OP* in)
{
    post_op((OP*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_int_chain(INT* in)
{
    post_int((INT*) in);
    post_literal((Literal*) in);
    post_static_array_key((Static_array_key*) in);
    post_static_value((Static_value*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_real_chain(REAL* in)
{
    post_real((REAL*) in);
    post_literal((Literal*) in);
    post_static_array_key((Static_array_key*) in);
    post_static_value((Static_value*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_string_chain(STRING* in)
{
    post_string((STRING*) in);
    post_literal((Literal*) in);
    post_static_array_key((Static_array_key*) in);
    post_static_value((Static_value*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_bool_chain(BOOL* in)
{
    post_bool((BOOL*) in);
    post_literal((Literal*) in);
    post_static_array_key((Static_array_key*) in);
    post_static_value((Static_value*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_nil_chain(NIL* in)
{
    post_nil((NIL*) in);
    post_literal((Literal*) in);
    post_static_array_key((Static_array_key*) in);
    post_static_value((Static_value*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_cast_chain(CAST* in)
{
    post_cast((CAST*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_constant_name_chain(CONSTANT_NAME* in)
{
    post_constant_name((CONSTANT_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

// Call the pre-chain, visit children and post-chain in order
// Do not override unless you know what you are doing
void Visitor::visit_statement_list(List<Statement*>* in)
{
    List<Statement*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "Statement");
    else
    {
    	pre_list("HIR", "Statement", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_statement(*i);
    	}
    
    	post_list("HIR", "Statement", in->size(), false);
    }
}

void Visitor::visit_statement(Statement* in)
{
    visit_type("HIR", "Statement");
    if(in == NULL)
    	visit_null("HIR", "Statement");
    else
    {
    	pre_statement_chain(in);
    	children_statement(in);
    	post_statement_chain(in);
    }
}

void Visitor::visit_class_mod(Class_mod* in)
{
    visit_type("HIR", "Class_mod");
    if(in == NULL)
    	visit_null("HIR", "Class_mod");
    else
    {
    	pre_class_mod_chain(in);
    	children_class_mod(in);
    	post_class_mod_chain(in);
    }
}

void Visitor::visit_class_name(CLASS_NAME* in)
{
    visit_type("HIR", "CLASS_NAME");
    if(in == NULL)
    	visit_null("HIR", "CLASS_NAME");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void Visitor::visit_interface_name_list(List<INTERFACE_NAME*>* in)
{
    List<INTERFACE_NAME*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "INTERFACE_NAME");
    else
    {
    	pre_list("HIR", "INTERFACE_NAME", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_interface_name(*i);
    	}
    
    	post_list("HIR", "INTERFACE_NAME", in->size(), false);
    }
}

void Visitor::visit_member_list(List<Member*>* in)
{
    List<Member*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "Member");
    else
    {
    	pre_list("HIR", "Member", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_member(*i);
    	}
    
    	post_list("HIR", "Member", in->size(), false);
    }
}

void Visitor::visit_member(Member* in)
{
    visit_type("HIR", "Member");
    if(in == NULL)
    	visit_null("HIR", "Member");
    else
    {
    	pre_member_chain(in);
    	children_member(in);
    	post_member_chain(in);
    }
}

void Visitor::visit_interface_name(INTERFACE_NAME* in)
{
    visit_type("HIR", "INTERFACE_NAME");
    if(in == NULL)
    	visit_null("HIR", "INTERFACE_NAME");
    else
    {
    	pre_interface_name_chain(in);
    	children_interface_name(in);
    	post_interface_name_chain(in);
    }
}

void Visitor::visit_signature(Signature* in)
{
    visit_type("HIR", "Signature");
    if(in == NULL)
    	visit_null("HIR", "Signature");
    else
    {
    	pre_signature_chain(in);
    	children_signature(in);
    	post_signature_chain(in);
    }
}

void Visitor::visit_method_mod(Method_mod* in)
{
    visit_type("HIR", "Method_mod");
    if(in == NULL)
    	visit_null("HIR", "Method_mod");
    else
    {
    	pre_method_mod_chain(in);
    	children_method_mod(in);
    	post_method_mod_chain(in);
    }
}

void Visitor::visit_method_name(METHOD_NAME* in)
{
    visit_type("HIR", "METHOD_NAME");
    if(in == NULL)
    	visit_null("HIR", "METHOD_NAME");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void Visitor::visit_formal_parameter_list(List<Formal_parameter*>* in)
{
    List<Formal_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "Formal_parameter");
    else
    {
    	pre_list("HIR", "Formal_parameter", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_formal_parameter(*i);
    	}
    
    	post_list("HIR", "Formal_parameter", in->size(), false);
    }
}

void Visitor::visit_formal_parameter(Formal_parameter* in)
{
    visit_type("HIR", "Formal_parameter");
    if(in == NULL)
    	visit_null("HIR", "Formal_parameter");
    else
    {
    	pre_formal_parameter_chain(in);
    	children_formal_parameter(in);
    	post_formal_parameter_chain(in);
    }
}

void Visitor::visit_type(Type* in)
{
    visit_type("HIR", "Type");
    if(in == NULL)
    	visit_null("HIR", "Type");
    else
    {
    	pre_type_chain(in);
    	children_type(in);
    	post_type_chain(in);
    }
}

void Visitor::visit_name_with_default(Name_with_default* in)
{
    visit_type("HIR", "Name_with_default");
    if(in == NULL)
    	visit_null("HIR", "Name_with_default");
    else
    {
    	pre_name_with_default_chain(in);
    	children_name_with_default(in);
    	post_name_with_default_chain(in);
    }
}

void Visitor::visit_attr_mod(Attr_mod* in)
{
    visit_type("HIR", "Attr_mod");
    if(in == NULL)
    	visit_null("HIR", "Attr_mod");
    else
    {
    	pre_attr_mod_chain(in);
    	children_attr_mod(in);
    	post_attr_mod_chain(in);
    }
}

void Visitor::visit_variable_name(VARIABLE_NAME* in)
{
    visit_type("HIR", "VARIABLE_NAME");
    if(in == NULL)
    	visit_null("HIR", "VARIABLE_NAME");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void Visitor::visit_static_value(Static_value* in)
{
    visit_type("HIR", "Static_value");
    if(in == NULL)
    	visit_null("HIR", "Static_value");
    else
    {
    	pre_static_value_chain(in);
    	children_static_value(in);
    	post_static_value_chain(in);
    }
}

void Visitor::visit_expr(Expr* in)
{
    visit_type("HIR", "Expr");
    if(in == NULL)
    	visit_null("HIR", "Expr");
    else
    {
    	pre_expr_chain(in);
    	children_expr(in);
    	post_expr_chain(in);
    }
}

void Visitor::visit_variable_name(Variable_name* in)
{
    visit_type("HIR", "Variable_name");
    if(in == NULL)
    	visit_null("HIR", "Variable_name");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void Visitor::visit_catch_list(List<Catch*>* in)
{
    List<Catch*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "Catch");
    else
    {
    	pre_list("HIR", "Catch", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_catch(*i);
    	}
    
    	post_list("HIR", "Catch", in->size(), false);
    }
}

void Visitor::visit_catch(Catch* in)
{
    visit_type("HIR", "Catch");
    if(in == NULL)
    	visit_null("HIR", "Catch");
    else
    {
    	pre_catch_chain(in);
    	children_catch(in);
    	post_catch_chain(in);
    }
}

void Visitor::visit_target(Target* in)
{
    visit_type("HIR", "Target");
    if(in == NULL)
    	visit_null("HIR", "Target");
    else
    {
    	pre_target_chain(in);
    	children_target(in);
    	post_target_chain(in);
    }
}

void Visitor::visit_op(OP* in)
{
    visit_type("HIR", "OP");
    if(in == NULL)
    	visit_null("HIR", "OP");
    else
    {
    	pre_op_chain(in);
    	children_op(in);
    	post_op_chain(in);
    }
}

void Visitor::visit_cast(CAST* in)
{
    visit_type("HIR", "CAST");
    if(in == NULL)
    	visit_null("HIR", "CAST");
    else
    {
    	pre_cast_chain(in);
    	children_cast(in);
    	post_cast_chain(in);
    }
}

void Visitor::visit_constant_name(CONSTANT_NAME* in)
{
    visit_type("HIR", "CONSTANT_NAME");
    if(in == NULL)
    	visit_null("HIR", "CONSTANT_NAME");
    else
    {
    	pre_constant_name_chain(in);
    	children_constant_name(in);
    	post_constant_name_chain(in);
    }
}

void Visitor::visit_class_name(Class_name* in)
{
    visit_type("HIR", "Class_name");
    if(in == NULL)
    	visit_null("HIR", "Class_name");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void Visitor::visit_method_name(Method_name* in)
{
    visit_type("HIR", "Method_name");
    if(in == NULL)
    	visit_null("HIR", "Method_name");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void Visitor::visit_actual_parameter_list(List<Actual_parameter*>* in)
{
    List<Actual_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "Actual_parameter");
    else
    {
    	pre_list("HIR", "Actual_parameter", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_actual_parameter(*i);
    	}
    
    	post_list("HIR", "Actual_parameter", in->size(), false);
    }
}

void Visitor::visit_actual_parameter(Actual_parameter* in)
{
    visit_type("HIR", "Actual_parameter");
    if(in == NULL)
    	visit_null("HIR", "Actual_parameter");
    else
    {
    	pre_actual_parameter_chain(in);
    	children_actual_parameter(in);
    	post_actual_parameter_chain(in);
    }
}

void Visitor::visit_variable_name_list(List<VARIABLE_NAME*>* in)
{
    List<VARIABLE_NAME*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "VARIABLE_NAME");
    else
    {
    	pre_list("HIR", "VARIABLE_NAME", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_variable_name(*i);
    	}
    
    	post_list("HIR", "VARIABLE_NAME", in->size(), false);
    }
}

void Visitor::visit_static_array_elem_list(List<Static_array_elem*>* in)
{
    List<Static_array_elem*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR", "Static_array_elem");
    else
    {
    	pre_list("HIR", "Static_array_elem", in->size(), false);
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_static_array_elem(*i);
    	}
    
    	post_list("HIR", "Static_array_elem", in->size(), false);
    }
}

void Visitor::visit_static_array_elem(Static_array_elem* in)
{
    visit_type("HIR", "Static_array_elem");
    if(in == NULL)
    	visit_null("HIR", "Static_array_elem");
    else
    {
    	pre_static_array_elem_chain(in);
    	children_static_array_elem(in);
    	post_static_array_elem_chain(in);
    }
}

void Visitor::visit_static_array_key(Static_array_key* in)
{
    visit_type("HIR", "Static_array_key");
    if(in == NULL)
    	visit_null("HIR", "Static_array_key");
    else
    {
    	pre_static_array_key_chain(in);
    	children_static_array_key(in);
    	post_static_array_key_chain(in);
    }
}

void Visitor::visit_php_script(PHP_script* in)
{
    visit_type("HIR", "PHP_script");
    if(in == NULL)
    	visit_null("HIR", "PHP_script");
    else
    {
    	pre_php_script_chain(in);
    	children_php_script(in);
    	post_php_script_chain(in);
    }
}

// Invoke the right pre-chain (manual dispatching)
// Do not override unless you know what you are doing
void Visitor::pre_statement_chain(Statement* in)
{
    switch(in->classid())
    {
    case Class_def::ID:
    	pre_class_def_chain(dynamic_cast<Class_def*>(in));
    	break;
    case Interface_def::ID:
    	pre_interface_def_chain(dynamic_cast<Interface_def*>(in));
    	break;
    case Method::ID:
    	pre_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Return::ID:
    	pre_return_chain(dynamic_cast<Return*>(in));
    	break;
    case Static_declaration::ID:
    	pre_static_declaration_chain(dynamic_cast<Static_declaration*>(in));
    	break;
    case Global::ID:
    	pre_global_chain(dynamic_cast<Global*>(in));
    	break;
    case Try::ID:
    	pre_try_chain(dynamic_cast<Try*>(in));
    	break;
    case Throw::ID:
    	pre_throw_chain(dynamic_cast<Throw*>(in));
    	break;
    case If::ID:
    	pre_if_chain(dynamic_cast<If*>(in));
    	break;
    case Loop::ID:
    	pre_loop_chain(dynamic_cast<Loop*>(in));
    	break;
    case Foreach::ID:
    	pre_foreach_chain(dynamic_cast<Foreach*>(in));
    	break;
    case Break::ID:
    	pre_break_chain(dynamic_cast<Break*>(in));
    	break;
    case Continue::ID:
    	pre_continue_chain(dynamic_cast<Continue*>(in));
    	break;
    case Assign_var::ID:
    	pre_assign_var_chain(dynamic_cast<Assign_var*>(in));
    	break;
    case Assign_var_var::ID:
    	pre_assign_var_var_chain(dynamic_cast<Assign_var_var*>(in));
    	break;
    case Assign_array::ID:
    	pre_assign_array_chain(dynamic_cast<Assign_array*>(in));
    	break;
    case Push_array::ID:
    	pre_push_array_chain(dynamic_cast<Push_array*>(in));
    	break;
    case Assign_target::ID:
    	pre_assign_target_chain(dynamic_cast<Assign_target*>(in));
    	break;
    case Eval_expr::ID:
    	pre_eval_expr_chain(dynamic_cast<Eval_expr*>(in));
    	break;
    case Pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<Pre_op*>(in));
    	break;
    case Foreign::ID:
    	pre_foreign_chain(dynamic_cast<Foreign*>(in));
    	break;
    }
}

void Visitor::pre_member_chain(Member* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	pre_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Attribute::ID:
    	pre_attribute_chain(dynamic_cast<Attribute*>(in));
    	break;
    }
}

void Visitor::pre_static_value_chain(Static_value* in)
{
    switch(in->classid())
    {
    case INT::ID:
    	pre_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	pre_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	pre_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	pre_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	pre_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Static_array::ID:
    	pre_static_array_chain(dynamic_cast<Static_array*>(in));
    	break;
    case Constant::ID:
    	pre_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    }
}

void Visitor::pre_expr_chain(Expr* in)
{
    switch(in->classid())
    {
    case Cast::ID:
    	pre_cast_chain(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	pre_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<Instanceof*>(in));
    	break;
    case Method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	pre_new_chain(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	pre_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	pre_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	pre_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	pre_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	pre_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Foreign::ID:
    	pre_foreign_chain(dynamic_cast<Foreign*>(in));
    	break;
    case VARIABLE_NAME::ID:
    	pre_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	pre_variable_variable_chain(dynamic_cast<Variable_variable*>(in));
    	break;
    case Index_array::ID:
    	pre_index_array_chain(dynamic_cast<Index_array*>(in));
    	break;
    case Target_expr::ID:
    	pre_target_expr_chain(dynamic_cast<Target_expr*>(in));
    	break;
    }
}

void Visitor::pre_variable_name_chain(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	pre_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	pre_variable_variable_chain(dynamic_cast<Variable_variable*>(in));
    	break;
    }
}

void Visitor::pre_target_chain(Target* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	pre_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case CLASS_NAME::ID:
    	pre_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Visitor::pre_class_name_chain(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	pre_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Variable_class::ID:
    	pre_variable_class_chain(dynamic_cast<Variable_class*>(in));
    	break;
    }
}

void Visitor::pre_method_name_chain(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	pre_method_name_chain(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Variable_method::ID:
    	pre_variable_method_chain(dynamic_cast<Variable_method*>(in));
    	break;
    }
}

void Visitor::pre_static_array_key_chain(Static_array_key* in)
{
    switch(in->classid())
    {
    case INT::ID:
    	pre_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	pre_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	pre_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	pre_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	pre_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Constant::ID:
    	pre_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    }
}

// Invoke the right post-chain (manual dispatching)
// Do not override unless you know what you are doing
void Visitor::post_statement_chain(Statement* in)
{
    switch(in->classid())
    {
    case Class_def::ID:
    	post_class_def_chain(dynamic_cast<Class_def*>(in));
    	break;
    case Interface_def::ID:
    	post_interface_def_chain(dynamic_cast<Interface_def*>(in));
    	break;
    case Method::ID:
    	post_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Return::ID:
    	post_return_chain(dynamic_cast<Return*>(in));
    	break;
    case Static_declaration::ID:
    	post_static_declaration_chain(dynamic_cast<Static_declaration*>(in));
    	break;
    case Global::ID:
    	post_global_chain(dynamic_cast<Global*>(in));
    	break;
    case Try::ID:
    	post_try_chain(dynamic_cast<Try*>(in));
    	break;
    case Throw::ID:
    	post_throw_chain(dynamic_cast<Throw*>(in));
    	break;
    case If::ID:
    	post_if_chain(dynamic_cast<If*>(in));
    	break;
    case Loop::ID:
    	post_loop_chain(dynamic_cast<Loop*>(in));
    	break;
    case Foreach::ID:
    	post_foreach_chain(dynamic_cast<Foreach*>(in));
    	break;
    case Break::ID:
    	post_break_chain(dynamic_cast<Break*>(in));
    	break;
    case Continue::ID:
    	post_continue_chain(dynamic_cast<Continue*>(in));
    	break;
    case Assign_var::ID:
    	post_assign_var_chain(dynamic_cast<Assign_var*>(in));
    	break;
    case Assign_var_var::ID:
    	post_assign_var_var_chain(dynamic_cast<Assign_var_var*>(in));
    	break;
    case Assign_array::ID:
    	post_assign_array_chain(dynamic_cast<Assign_array*>(in));
    	break;
    case Push_array::ID:
    	post_push_array_chain(dynamic_cast<Push_array*>(in));
    	break;
    case Assign_target::ID:
    	post_assign_target_chain(dynamic_cast<Assign_target*>(in));
    	break;
    case Eval_expr::ID:
    	post_eval_expr_chain(dynamic_cast<Eval_expr*>(in));
    	break;
    case Pre_op::ID:
    	post_pre_op_chain(dynamic_cast<Pre_op*>(in));
    	break;
    case Foreign::ID:
    	post_foreign_chain(dynamic_cast<Foreign*>(in));
    	break;
    }
}

void Visitor::post_member_chain(Member* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	post_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Attribute::ID:
    	post_attribute_chain(dynamic_cast<Attribute*>(in));
    	break;
    }
}

void Visitor::post_static_value_chain(Static_value* in)
{
    switch(in->classid())
    {
    case INT::ID:
    	post_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	post_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	post_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	post_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	post_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Static_array::ID:
    	post_static_array_chain(dynamic_cast<Static_array*>(in));
    	break;
    case Constant::ID:
    	post_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    }
}

void Visitor::post_expr_chain(Expr* in)
{
    switch(in->classid())
    {
    case Cast::ID:
    	post_cast_chain(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	post_unary_op_chain(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	post_bin_op_chain(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	post_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	post_instanceof_chain(dynamic_cast<Instanceof*>(in));
    	break;
    case Method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	post_new_chain(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	post_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	post_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	post_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	post_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	post_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Foreign::ID:
    	post_foreign_chain(dynamic_cast<Foreign*>(in));
    	break;
    case VARIABLE_NAME::ID:
    	post_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	post_variable_variable_chain(dynamic_cast<Variable_variable*>(in));
    	break;
    case Index_array::ID:
    	post_index_array_chain(dynamic_cast<Index_array*>(in));
    	break;
    case Target_expr::ID:
    	post_target_expr_chain(dynamic_cast<Target_expr*>(in));
    	break;
    }
}

void Visitor::post_variable_name_chain(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	post_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	post_variable_variable_chain(dynamic_cast<Variable_variable*>(in));
    	break;
    }
}

void Visitor::post_target_chain(Target* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	post_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case CLASS_NAME::ID:
    	post_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Visitor::post_class_name_chain(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	post_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Variable_class::ID:
    	post_variable_class_chain(dynamic_cast<Variable_class*>(in));
    	break;
    }
}

void Visitor::post_method_name_chain(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	post_method_name_chain(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Variable_method::ID:
    	post_variable_method_chain(dynamic_cast<Variable_method*>(in));
    	break;
    }
}

void Visitor::post_static_array_key_chain(Static_array_key* in)
{
    switch(in->classid())
    {
    case INT::ID:
    	post_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	post_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	post_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	post_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	post_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Constant::ID:
    	post_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    }
}

// Invoke the right visit-children (manual dispatching)
// Do not override unless you know what you are doing
void Visitor::children_statement(Statement* in)
{
    switch(in->classid())
    {
    case Class_def::ID:
    	children_class_def(dynamic_cast<Class_def*>(in));
    	break;
    case Interface_def::ID:
    	children_interface_def(dynamic_cast<Interface_def*>(in));
    	break;
    case Method::ID:
    	children_method(dynamic_cast<Method*>(in));
    	break;
    case Return::ID:
    	children_return(dynamic_cast<Return*>(in));
    	break;
    case Static_declaration::ID:
    	children_static_declaration(dynamic_cast<Static_declaration*>(in));
    	break;
    case Global::ID:
    	children_global(dynamic_cast<Global*>(in));
    	break;
    case Try::ID:
    	children_try(dynamic_cast<Try*>(in));
    	break;
    case Throw::ID:
    	children_throw(dynamic_cast<Throw*>(in));
    	break;
    case If::ID:
    	children_if(dynamic_cast<If*>(in));
    	break;
    case Loop::ID:
    	children_loop(dynamic_cast<Loop*>(in));
    	break;
    case Foreach::ID:
    	children_foreach(dynamic_cast<Foreach*>(in));
    	break;
    case Break::ID:
    	children_break(dynamic_cast<Break*>(in));
    	break;
    case Continue::ID:
    	children_continue(dynamic_cast<Continue*>(in));
    	break;
    case Assign_var::ID:
    	children_assign_var(dynamic_cast<Assign_var*>(in));
    	break;
    case Assign_var_var::ID:
    	children_assign_var_var(dynamic_cast<Assign_var_var*>(in));
    	break;
    case Assign_array::ID:
    	children_assign_array(dynamic_cast<Assign_array*>(in));
    	break;
    case Push_array::ID:
    	children_push_array(dynamic_cast<Push_array*>(in));
    	break;
    case Assign_target::ID:
    	children_assign_target(dynamic_cast<Assign_target*>(in));
    	break;
    case Eval_expr::ID:
    	children_eval_expr(dynamic_cast<Eval_expr*>(in));
    	break;
    case Pre_op::ID:
    	children_pre_op(dynamic_cast<Pre_op*>(in));
    	break;
    case Foreign::ID:
    	children_foreign(dynamic_cast<Foreign*>(in));
    	break;
    }
}

void Visitor::children_member(Member* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	children_method(dynamic_cast<Method*>(in));
    	break;
    case Attribute::ID:
    	children_attribute(dynamic_cast<Attribute*>(in));
    	break;
    }
}

void Visitor::children_static_value(Static_value* in)
{
    switch(in->classid())
    {
    case INT::ID:
    	children_int(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	children_real(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	children_bool(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	children_nil(dynamic_cast<NIL*>(in));
    	break;
    case Static_array::ID:
    	children_static_array(dynamic_cast<Static_array*>(in));
    	break;
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    }
}

void Visitor::children_expr(Expr* in)
{
    switch(in->classid())
    {
    case Cast::ID:
    	children_cast(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	children_unary_op(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	children_bin_op(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	children_instanceof(dynamic_cast<Instanceof*>(in));
    	break;
    case Method_invocation::ID:
    	children_method_invocation(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	children_new(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	children_int(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	children_real(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	children_bool(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	children_nil(dynamic_cast<NIL*>(in));
    	break;
    case Foreign::ID:
    	children_foreign(dynamic_cast<Foreign*>(in));
    	break;
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	children_variable_variable(dynamic_cast<Variable_variable*>(in));
    	break;
    case Index_array::ID:
    	children_index_array(dynamic_cast<Index_array*>(in));
    	break;
    case Target_expr::ID:
    	children_target_expr(dynamic_cast<Target_expr*>(in));
    	break;
    }
}

void Visitor::children_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	children_variable_variable(dynamic_cast<Variable_variable*>(in));
    	break;
    }
}

void Visitor::children_target(Target* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Visitor::children_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Variable_class::ID:
    	children_variable_class(dynamic_cast<Variable_class*>(in));
    	break;
    }
}

void Visitor::children_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	children_method_name(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Variable_method::ID:
    	children_variable_method(dynamic_cast<Variable_method*>(in));
    	break;
    }
}

void Visitor::children_static_array_key(Static_array_key* in)
{
    switch(in->classid())
    {
    case INT::ID:
    	children_int(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	children_real(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	children_bool(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	children_nil(dynamic_cast<NIL*>(in));
    	break;
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    }
}
}

