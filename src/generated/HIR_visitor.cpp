#include "HIR_visitor.h"

namespace HIR{
HIR_visitor::~HIR_visitor()
{
}

// Invoked before the children are visited
void HIR_visitor::pre_node(HIR_node* in)
{
}

void HIR_visitor::pre_php_script(HIR_php_script* in)
{
}

void HIR_visitor::pre_statement(HIR_statement* in)
{
}

void HIR_visitor::pre_class_def(HIR_class_def* in)
{
}

void HIR_visitor::pre_class_mod(HIR_class_mod* in)
{
}

void HIR_visitor::pre_interface_def(HIR_interface_def* in)
{
}

void HIR_visitor::pre_member(HIR_member* in)
{
}

void HIR_visitor::pre_method(HIR_method* in)
{
}

void HIR_visitor::pre_signature(HIR_signature* in)
{
}

void HIR_visitor::pre_method_mod(HIR_method_mod* in)
{
}

void HIR_visitor::pre_formal_parameter(HIR_formal_parameter* in)
{
}

void HIR_visitor::pre_type(HIR_type* in)
{
}

void HIR_visitor::pre_attribute(HIR_attribute* in)
{
}

void HIR_visitor::pre_attr_mod(HIR_attr_mod* in)
{
}

void HIR_visitor::pre_name_with_default(HIR_name_with_default* in)
{
}

void HIR_visitor::pre_return(HIR_return* in)
{
}

void HIR_visitor::pre_static_declaration(HIR_static_declaration* in)
{
}

void HIR_visitor::pre_global(HIR_global* in)
{
}

void HIR_visitor::pre_try(HIR_try* in)
{
}

void HIR_visitor::pre_catch(HIR_catch* in)
{
}

void HIR_visitor::pre_throw(HIR_throw* in)
{
}

void HIR_visitor::pre_eval_expr(HIR_eval_expr* in)
{
}

void HIR_visitor::pre_branch(HIR_branch* in)
{
}

void HIR_visitor::pre_goto(HIR_goto* in)
{
}

void HIR_visitor::pre_label(HIR_label* in)
{
}

void HIR_visitor::pre_expr(HIR_expr* in)
{
}

void HIR_visitor::pre_literal(HIR_literal* in)
{
}

void HIR_visitor::pre_assignment(HIR_assignment* in)
{
}

void HIR_visitor::pre_cast(HIR_cast* in)
{
}

void HIR_visitor::pre_unary_op(HIR_unary_op* in)
{
}

void HIR_visitor::pre_bin_op(HIR_bin_op* in)
{
}

void HIR_visitor::pre_constant(HIR_constant* in)
{
}

void HIR_visitor::pre_instanceof(HIR_instanceof* in)
{
}

void HIR_visitor::pre_variable(HIR_variable* in)
{
}

void HIR_visitor::pre_variable_name(HIR_variable_name* in)
{
}

void HIR_visitor::pre_reflection(HIR_reflection* in)
{
}

void HIR_visitor::pre_target(HIR_target* in)
{
}

void HIR_visitor::pre_pre_op(HIR_pre_op* in)
{
}

void HIR_visitor::pre_array(HIR_array* in)
{
}

void HIR_visitor::pre_array_elem(HIR_array_elem* in)
{
}

void HIR_visitor::pre_method_invocation(HIR_method_invocation* in)
{
}

void HIR_visitor::pre_method_name(HIR_method_name* in)
{
}

void HIR_visitor::pre_actual_parameter(HIR_actual_parameter* in)
{
}

void HIR_visitor::pre_new(HIR_new* in)
{
}

void HIR_visitor::pre_class_name(HIR_class_name* in)
{
}

void HIR_visitor::pre_identifier(HIR_identifier* in)
{
}

void HIR_visitor::pre_class_name(Token_class_name* in)
{
}

void HIR_visitor::pre_interface_name(Token_interface_name* in)
{
}

void HIR_visitor::pre_method_name(Token_method_name* in)
{
}

void HIR_visitor::pre_variable_name(Token_variable_name* in)
{
}

void HIR_visitor::pre_label_name(Token_label_name* in)
{
}

void HIR_visitor::pre_int(Token_int* in)
{
}

void HIR_visitor::pre_real(Token_real* in)
{
}

void HIR_visitor::pre_string(Token_string* in)
{
}

void HIR_visitor::pre_bool(Token_bool* in)
{
}

void HIR_visitor::pre_null(Token_null* in)
{
}

void HIR_visitor::pre_cast(Token_cast* in)
{
}

void HIR_visitor::pre_op(Token_op* in)
{
}

void HIR_visitor::pre_constant_name(Token_constant_name* in)
{
}

// Invoked after the children have been visited
void HIR_visitor::post_node(HIR_node* in)
{
}

void HIR_visitor::post_php_script(HIR_php_script* in)
{
}

void HIR_visitor::post_statement(HIR_statement* in)
{
}

void HIR_visitor::post_class_def(HIR_class_def* in)
{
}

void HIR_visitor::post_class_mod(HIR_class_mod* in)
{
}

void HIR_visitor::post_interface_def(HIR_interface_def* in)
{
}

void HIR_visitor::post_member(HIR_member* in)
{
}

void HIR_visitor::post_method(HIR_method* in)
{
}

void HIR_visitor::post_signature(HIR_signature* in)
{
}

void HIR_visitor::post_method_mod(HIR_method_mod* in)
{
}

void HIR_visitor::post_formal_parameter(HIR_formal_parameter* in)
{
}

void HIR_visitor::post_type(HIR_type* in)
{
}

void HIR_visitor::post_attribute(HIR_attribute* in)
{
}

void HIR_visitor::post_attr_mod(HIR_attr_mod* in)
{
}

void HIR_visitor::post_name_with_default(HIR_name_with_default* in)
{
}

void HIR_visitor::post_return(HIR_return* in)
{
}

void HIR_visitor::post_static_declaration(HIR_static_declaration* in)
{
}

void HIR_visitor::post_global(HIR_global* in)
{
}

void HIR_visitor::post_try(HIR_try* in)
{
}

void HIR_visitor::post_catch(HIR_catch* in)
{
}

void HIR_visitor::post_throw(HIR_throw* in)
{
}

void HIR_visitor::post_eval_expr(HIR_eval_expr* in)
{
}

void HIR_visitor::post_branch(HIR_branch* in)
{
}

void HIR_visitor::post_goto(HIR_goto* in)
{
}

void HIR_visitor::post_label(HIR_label* in)
{
}

void HIR_visitor::post_expr(HIR_expr* in)
{
}

void HIR_visitor::post_literal(HIR_literal* in)
{
}

void HIR_visitor::post_assignment(HIR_assignment* in)
{
}

void HIR_visitor::post_cast(HIR_cast* in)
{
}

void HIR_visitor::post_unary_op(HIR_unary_op* in)
{
}

void HIR_visitor::post_bin_op(HIR_bin_op* in)
{
}

void HIR_visitor::post_constant(HIR_constant* in)
{
}

void HIR_visitor::post_instanceof(HIR_instanceof* in)
{
}

void HIR_visitor::post_variable(HIR_variable* in)
{
}

void HIR_visitor::post_variable_name(HIR_variable_name* in)
{
}

void HIR_visitor::post_reflection(HIR_reflection* in)
{
}

void HIR_visitor::post_target(HIR_target* in)
{
}

void HIR_visitor::post_pre_op(HIR_pre_op* in)
{
}

void HIR_visitor::post_array(HIR_array* in)
{
}

void HIR_visitor::post_array_elem(HIR_array_elem* in)
{
}

void HIR_visitor::post_method_invocation(HIR_method_invocation* in)
{
}

void HIR_visitor::post_method_name(HIR_method_name* in)
{
}

void HIR_visitor::post_actual_parameter(HIR_actual_parameter* in)
{
}

void HIR_visitor::post_new(HIR_new* in)
{
}

void HIR_visitor::post_class_name(HIR_class_name* in)
{
}

void HIR_visitor::post_identifier(HIR_identifier* in)
{
}

void HIR_visitor::post_class_name(Token_class_name* in)
{
}

void HIR_visitor::post_interface_name(Token_interface_name* in)
{
}

void HIR_visitor::post_method_name(Token_method_name* in)
{
}

void HIR_visitor::post_variable_name(Token_variable_name* in)
{
}

void HIR_visitor::post_label_name(Token_label_name* in)
{
}

void HIR_visitor::post_int(Token_int* in)
{
}

void HIR_visitor::post_real(Token_real* in)
{
}

void HIR_visitor::post_string(Token_string* in)
{
}

void HIR_visitor::post_bool(Token_bool* in)
{
}

void HIR_visitor::post_null(Token_null* in)
{
}

void HIR_visitor::post_cast(Token_cast* in)
{
}

void HIR_visitor::post_op(Token_op* in)
{
}

void HIR_visitor::post_constant_name(Token_constant_name* in)
{
}

// Visit the children of a node
void HIR_visitor::children_php_script(HIR_php_script* in)
{
    visit_statement_list(in->statements);
}

void HIR_visitor::children_class_def(HIR_class_def* in)
{
    visit_class_mod(in->class_mod);
    visit_class_name(in->class_name);
    visit_class_name(in->extends);
    visit_interface_name_list(in->implements);
    visit_member_list(in->members);
}

void HIR_visitor::children_class_mod(HIR_class_mod* in)
{
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void HIR_visitor::children_interface_def(HIR_interface_def* in)
{
    visit_interface_name(in->interface_name);
    visit_interface_name_list(in->extends);
    visit_member_list(in->members);
}

void HIR_visitor::children_method(HIR_method* in)
{
    visit_signature(in->signature);
    visit_statement_list(in->statements);
}

void HIR_visitor::children_signature(HIR_signature* in)
{
    visit_method_mod(in->method_mod);
    visit_marker("is_ref", in->is_ref);
    visit_method_name(in->method_name);
    visit_formal_parameter_list(in->formal_parameters);
}

void HIR_visitor::children_method_mod(HIR_method_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void HIR_visitor::children_formal_parameter(HIR_formal_parameter* in)
{
    visit_type(in->type);
    visit_marker("is_ref", in->is_ref);
    visit_name_with_default(in->var);
}

void HIR_visitor::children_type(HIR_type* in)
{
    visit_class_name(in->class_name);
}

void HIR_visitor::children_attribute(HIR_attribute* in)
{
    visit_attr_mod(in->attr_mod);
    visit_name_with_default(in->var);
}

void HIR_visitor::children_attr_mod(HIR_attr_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_const", in->is_const);
}

void HIR_visitor::children_name_with_default(HIR_name_with_default* in)
{
    visit_variable_name(in->variable_name);
    visit_expr(in->expr);
}

void HIR_visitor::children_return(HIR_return* in)
{
    visit_expr(in->expr);
}

void HIR_visitor::children_static_declaration(HIR_static_declaration* in)
{
    visit_name_with_default(in->var);
}

void HIR_visitor::children_global(HIR_global* in)
{
    visit_variable_name(in->variable_name);
}

void HIR_visitor::children_try(HIR_try* in)
{
    visit_statement_list(in->statements);
    visit_catch_list(in->catches);
}

void HIR_visitor::children_catch(HIR_catch* in)
{
    visit_class_name(in->class_name);
    visit_variable_name(in->variable_name);
    visit_statement_list(in->statements);
}

void HIR_visitor::children_throw(HIR_throw* in)
{
    visit_expr(in->expr);
}

void HIR_visitor::children_eval_expr(HIR_eval_expr* in)
{
    visit_expr(in->expr);
}

void HIR_visitor::children_branch(HIR_branch* in)
{
    visit_expr(in->expr);
    visit_label_name(in->iftrue);
    visit_label_name(in->iffalse);
}

void HIR_visitor::children_goto(HIR_goto* in)
{
    visit_label_name(in->label_name);
}

void HIR_visitor::children_label(HIR_label* in)
{
    visit_label_name(in->label_name);
}

void HIR_visitor::children_assignment(HIR_assignment* in)
{
    visit_variable(in->variable);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->expr);
}

void HIR_visitor::children_cast(HIR_cast* in)
{
    visit_cast(in->cast);
    visit_variable_name(in->variable_name);
}

void HIR_visitor::children_unary_op(HIR_unary_op* in)
{
    visit_op(in->op);
    visit_variable_name(in->variable_name);
}

void HIR_visitor::children_bin_op(HIR_bin_op* in)
{
    visit_variable_name(in->left);
    visit_op(in->op);
    visit_variable_name(in->right);
}

void HIR_visitor::children_constant(HIR_constant* in)
{
    visit_class_name(in->class_name);
    visit_constant_name(in->constant_name);
}

void HIR_visitor::children_instanceof(HIR_instanceof* in)
{
    visit_variable_name(in->variable_name);
    visit_class_name(in->class_name);
}

void HIR_visitor::children_variable(HIR_variable* in)
{
    visit_target(in->target);
    visit_variable_name(in->variable_name);
    visit_expr_list(in->array_indices);
}

void HIR_visitor::children_reflection(HIR_reflection* in)
{
    visit_variable_name(in->variable_name);
}

void HIR_visitor::children_pre_op(HIR_pre_op* in)
{
    visit_op(in->op);
    visit_variable(in->variable);
}

void HIR_visitor::children_array(HIR_array* in)
{
    visit_array_elem_list(in->array_elems);
}

void HIR_visitor::children_array_elem(HIR_array_elem* in)
{
    visit_expr(in->key);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->val);
}

void HIR_visitor::children_method_invocation(HIR_method_invocation* in)
{
    visit_target(in->target);
    visit_method_name(in->method_name);
    visit_actual_parameter_list(in->actual_parameters);
}

void HIR_visitor::children_actual_parameter(HIR_actual_parameter* in)
{
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->expr);
}

void HIR_visitor::children_new(HIR_new* in)
{
    visit_class_name(in->class_name);
    visit_actual_parameter_list(in->actual_parameters);
}

// Tokens don't have children, so these methods do nothing by default
void HIR_visitor::children_class_name(Token_class_name* in)
{
}

void HIR_visitor::children_interface_name(Token_interface_name* in)
{
}

void HIR_visitor::children_method_name(Token_method_name* in)
{
}

void HIR_visitor::children_variable_name(Token_variable_name* in)
{
}

void HIR_visitor::children_label_name(Token_label_name* in)
{
}

void HIR_visitor::children_int(Token_int* in)
{
}

void HIR_visitor::children_real(Token_real* in)
{
}

void HIR_visitor::children_string(Token_string* in)
{
}

void HIR_visitor::children_bool(Token_bool* in)
{
}

void HIR_visitor::children_null(Token_null* in)
{
}

void HIR_visitor::children_cast(Token_cast* in)
{
}

void HIR_visitor::children_op(Token_op* in)
{
}

void HIR_visitor::children_constant_name(Token_constant_name* in)
{
}

// Unparser support
void HIR_visitor::visit_marker(char const* name, bool value)
{
}

void HIR_visitor::visit_null(char const* type_id)
{
}

void HIR_visitor::visit_null_list(char const* type_id)
{
}

void HIR_visitor::pre_list(char const* type_id, int size)
{
}

void HIR_visitor::post_list(char const* type_id, int size)
{
}

// Invoke the chain of pre-visit methods along the inheritance hierachy
// Do not override unless you know what you are doing
void HIR_visitor::pre_php_script_chain(HIR_php_script* in)
{
    pre_node(in);
    pre_php_script(in);
}

void HIR_visitor::pre_class_def_chain(HIR_class_def* in)
{
    pre_node(in);
    pre_statement(in);
    pre_class_def(in);
}

void HIR_visitor::pre_class_mod_chain(HIR_class_mod* in)
{
    pre_node(in);
    pre_class_mod(in);
}

void HIR_visitor::pre_interface_def_chain(HIR_interface_def* in)
{
    pre_node(in);
    pre_statement(in);
    pre_interface_def(in);
}

void HIR_visitor::pre_method_chain(HIR_method* in)
{
    pre_node(in);
    pre_statement(in);
    pre_member(in);
    pre_method(in);
}

void HIR_visitor::pre_signature_chain(HIR_signature* in)
{
    pre_node(in);
    pre_signature(in);
}

void HIR_visitor::pre_method_mod_chain(HIR_method_mod* in)
{
    pre_node(in);
    pre_method_mod(in);
}

void HIR_visitor::pre_formal_parameter_chain(HIR_formal_parameter* in)
{
    pre_node(in);
    pre_formal_parameter(in);
}

void HIR_visitor::pre_type_chain(HIR_type* in)
{
    pre_node(in);
    pre_type(in);
}

void HIR_visitor::pre_attribute_chain(HIR_attribute* in)
{
    pre_node(in);
    pre_member(in);
    pre_attribute(in);
}

void HIR_visitor::pre_attr_mod_chain(HIR_attr_mod* in)
{
    pre_node(in);
    pre_attr_mod(in);
}

void HIR_visitor::pre_name_with_default_chain(HIR_name_with_default* in)
{
    pre_node(in);
    pre_name_with_default(in);
}

void HIR_visitor::pre_return_chain(HIR_return* in)
{
    pre_node(in);
    pre_statement(in);
    pre_return(in);
}

void HIR_visitor::pre_static_declaration_chain(HIR_static_declaration* in)
{
    pre_node(in);
    pre_statement(in);
    pre_static_declaration(in);
}

void HIR_visitor::pre_global_chain(HIR_global* in)
{
    pre_node(in);
    pre_statement(in);
    pre_global(in);
}

void HIR_visitor::pre_try_chain(HIR_try* in)
{
    pre_node(in);
    pre_statement(in);
    pre_try(in);
}

void HIR_visitor::pre_catch_chain(HIR_catch* in)
{
    pre_node(in);
    pre_catch(in);
}

void HIR_visitor::pre_throw_chain(HIR_throw* in)
{
    pre_node(in);
    pre_statement(in);
    pre_throw(in);
}

void HIR_visitor::pre_eval_expr_chain(HIR_eval_expr* in)
{
    pre_node(in);
    pre_statement(in);
    pre_eval_expr(in);
}

void HIR_visitor::pre_branch_chain(HIR_branch* in)
{
    pre_node(in);
    pre_statement(in);
    pre_branch(in);
}

void HIR_visitor::pre_goto_chain(HIR_goto* in)
{
    pre_node(in);
    pre_statement(in);
    pre_goto(in);
}

void HIR_visitor::pre_label_chain(HIR_label* in)
{
    pre_node(in);
    pre_statement(in);
    pre_label(in);
}

void HIR_visitor::pre_assignment_chain(HIR_assignment* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_assignment(in);
}

void HIR_visitor::pre_cast_chain(HIR_cast* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_cast(in);
}

void HIR_visitor::pre_unary_op_chain(HIR_unary_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_unary_op(in);
}

void HIR_visitor::pre_bin_op_chain(HIR_bin_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_bin_op(in);
}

void HIR_visitor::pre_constant_chain(HIR_constant* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_constant(in);
}

void HIR_visitor::pre_instanceof_chain(HIR_instanceof* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_instanceof(in);
}

void HIR_visitor::pre_variable_chain(HIR_variable* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_variable(in);
}

void HIR_visitor::pre_reflection_chain(HIR_reflection* in)
{
    pre_node(in);
    pre_variable_name(in);
    pre_method_name(in);
    pre_class_name(in);
    pre_reflection(in);
}

void HIR_visitor::pre_pre_op_chain(HIR_pre_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_pre_op(in);
}

void HIR_visitor::pre_array_chain(HIR_array* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_array(in);
}

void HIR_visitor::pre_array_elem_chain(HIR_array_elem* in)
{
    pre_node(in);
    pre_array_elem(in);
}

void HIR_visitor::pre_method_invocation_chain(HIR_method_invocation* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_method_invocation(in);
}

void HIR_visitor::pre_actual_parameter_chain(HIR_actual_parameter* in)
{
    pre_node(in);
    pre_actual_parameter(in);
}

void HIR_visitor::pre_new_chain(HIR_new* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_new(in);
}

void HIR_visitor::pre_class_name_chain(Token_class_name* in)
{
    pre_node(in);
    pre_target(in);
    pre_class_name(in);
    pre_identifier(in);
    pre_class_name(in);
}

void HIR_visitor::pre_interface_name_chain(Token_interface_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_interface_name(in);
}

void HIR_visitor::pre_method_name_chain(Token_method_name* in)
{
    pre_node(in);
    pre_method_name(in);
    pre_identifier(in);
    pre_method_name(in);
}

void HIR_visitor::pre_variable_name_chain(Token_variable_name* in)
{
    pre_node(in);
    pre_variable_name(in);
    pre_identifier(in);
    pre_variable_name(in);
}

void HIR_visitor::pre_label_name_chain(Token_label_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_label_name(in);
}

void HIR_visitor::pre_int_chain(Token_int* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_int(in);
}

void HIR_visitor::pre_real_chain(Token_real* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_real(in);
}

void HIR_visitor::pre_string_chain(Token_string* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_string(in);
}

void HIR_visitor::pre_bool_chain(Token_bool* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_bool(in);
}

void HIR_visitor::pre_null_chain(Token_null* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_null(in);
}

void HIR_visitor::pre_cast_chain(Token_cast* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_cast(in);
}

void HIR_visitor::pre_op_chain(Token_op* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_op(in);
}

void HIR_visitor::pre_constant_name_chain(Token_constant_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_constant_name(in);
}

// Invoke the chain of post-visit methods along the inheritance hierarchy
// (invoked in opposite order to the pre-chain)
// Do not override unless you know what you are doing
void HIR_visitor::post_php_script_chain(HIR_php_script* in)
{
    post_php_script(in);
    post_node(in);
}

void HIR_visitor::post_class_def_chain(HIR_class_def* in)
{
    post_class_def(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_class_mod_chain(HIR_class_mod* in)
{
    post_class_mod(in);
    post_node(in);
}

void HIR_visitor::post_interface_def_chain(HIR_interface_def* in)
{
    post_interface_def(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_method_chain(HIR_method* in)
{
    post_method(in);
    post_member(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_signature_chain(HIR_signature* in)
{
    post_signature(in);
    post_node(in);
}

void HIR_visitor::post_method_mod_chain(HIR_method_mod* in)
{
    post_method_mod(in);
    post_node(in);
}

void HIR_visitor::post_formal_parameter_chain(HIR_formal_parameter* in)
{
    post_formal_parameter(in);
    post_node(in);
}

void HIR_visitor::post_type_chain(HIR_type* in)
{
    post_type(in);
    post_node(in);
}

void HIR_visitor::post_attribute_chain(HIR_attribute* in)
{
    post_attribute(in);
    post_member(in);
    post_node(in);
}

void HIR_visitor::post_attr_mod_chain(HIR_attr_mod* in)
{
    post_attr_mod(in);
    post_node(in);
}

void HIR_visitor::post_name_with_default_chain(HIR_name_with_default* in)
{
    post_name_with_default(in);
    post_node(in);
}

void HIR_visitor::post_return_chain(HIR_return* in)
{
    post_return(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_static_declaration_chain(HIR_static_declaration* in)
{
    post_static_declaration(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_global_chain(HIR_global* in)
{
    post_global(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_try_chain(HIR_try* in)
{
    post_try(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_catch_chain(HIR_catch* in)
{
    post_catch(in);
    post_node(in);
}

void HIR_visitor::post_throw_chain(HIR_throw* in)
{
    post_throw(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_eval_expr_chain(HIR_eval_expr* in)
{
    post_eval_expr(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_branch_chain(HIR_branch* in)
{
    post_branch(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_goto_chain(HIR_goto* in)
{
    post_goto(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_label_chain(HIR_label* in)
{
    post_label(in);
    post_statement(in);
    post_node(in);
}

void HIR_visitor::post_assignment_chain(HIR_assignment* in)
{
    post_assignment(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_cast_chain(HIR_cast* in)
{
    post_cast(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_unary_op_chain(HIR_unary_op* in)
{
    post_unary_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_bin_op_chain(HIR_bin_op* in)
{
    post_bin_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_constant_chain(HIR_constant* in)
{
    post_constant(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_instanceof_chain(HIR_instanceof* in)
{
    post_instanceof(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_variable_chain(HIR_variable* in)
{
    post_variable(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_reflection_chain(HIR_reflection* in)
{
    post_reflection(in);
    post_class_name(in);
    post_method_name(in);
    post_variable_name(in);
    post_node(in);
}

void HIR_visitor::post_pre_op_chain(HIR_pre_op* in)
{
    post_pre_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_array_chain(HIR_array* in)
{
    post_array(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_array_elem_chain(HIR_array_elem* in)
{
    post_array_elem(in);
    post_node(in);
}

void HIR_visitor::post_method_invocation_chain(HIR_method_invocation* in)
{
    post_method_invocation(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_actual_parameter_chain(HIR_actual_parameter* in)
{
    post_actual_parameter(in);
    post_node(in);
}

void HIR_visitor::post_new_chain(HIR_new* in)
{
    post_new(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_class_name_chain(Token_class_name* in)
{
    post_class_name(in);
    post_identifier(in);
    post_class_name(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_interface_name_chain(Token_interface_name* in)
{
    post_interface_name(in);
    post_identifier(in);
    post_node(in);
}

void HIR_visitor::post_method_name_chain(Token_method_name* in)
{
    post_method_name(in);
    post_identifier(in);
    post_method_name(in);
    post_node(in);
}

void HIR_visitor::post_variable_name_chain(Token_variable_name* in)
{
    post_variable_name(in);
    post_identifier(in);
    post_variable_name(in);
    post_node(in);
}

void HIR_visitor::post_label_name_chain(Token_label_name* in)
{
    post_label_name(in);
    post_identifier(in);
    post_node(in);
}

void HIR_visitor::post_int_chain(Token_int* in)
{
    post_int(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_real_chain(Token_real* in)
{
    post_real(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_string_chain(Token_string* in)
{
    post_string(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_bool_chain(Token_bool* in)
{
    post_bool(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_null_chain(Token_null* in)
{
    post_null(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void HIR_visitor::post_cast_chain(Token_cast* in)
{
    post_cast(in);
    post_identifier(in);
    post_node(in);
}

void HIR_visitor::post_op_chain(Token_op* in)
{
    post_op(in);
    post_identifier(in);
    post_node(in);
}

void HIR_visitor::post_constant_name_chain(Token_constant_name* in)
{
    post_constant_name(in);
    post_identifier(in);
    post_node(in);
}

// Call the pre-chain, visit children and post-chain in order
// Do not override unless you know what you are doing
void HIR_visitor::visit_statement_list(List<HIR_statement*>* in)
{
    List<HIR_statement*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_statement");
    else
    {
    	pre_list("HIR_statement", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_statement(*i);
    	}
    
    	post_list("HIR_statement", in->size());
    }
}

void HIR_visitor::visit_statement(HIR_statement* in)
{
    if(in == NULL)
    	visit_null("HIR_statement");
    else
    {
    	pre_statement_chain(in);
    	children_statement(in);
    	post_statement_chain(in);
    }
}

void HIR_visitor::visit_class_mod(HIR_class_mod* in)
{
    if(in == NULL)
    	visit_null("HIR_class_mod");
    else
    {
    	pre_class_mod_chain(in);
    	children_class_mod(in);
    	post_class_mod_chain(in);
    }
}

void HIR_visitor::visit_class_name(Token_class_name* in)
{
    if(in == NULL)
    	visit_null("Token_class_name");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void HIR_visitor::visit_interface_name_list(List<Token_interface_name*>* in)
{
    List<Token_interface_name*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("Token_interface_name");
    else
    {
    	pre_list("Token_interface_name", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_interface_name(*i);
    	}
    
    	post_list("Token_interface_name", in->size());
    }
}

void HIR_visitor::visit_member_list(List<HIR_member*>* in)
{
    List<HIR_member*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_member");
    else
    {
    	pre_list("HIR_member", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_member(*i);
    	}
    
    	post_list("HIR_member", in->size());
    }
}

void HIR_visitor::visit_member(HIR_member* in)
{
    if(in == NULL)
    	visit_null("HIR_member");
    else
    {
    	pre_member_chain(in);
    	children_member(in);
    	post_member_chain(in);
    }
}

void HIR_visitor::visit_interface_name(Token_interface_name* in)
{
    if(in == NULL)
    	visit_null("Token_interface_name");
    else
    {
    	pre_interface_name_chain(in);
    	children_interface_name(in);
    	post_interface_name_chain(in);
    }
}

void HIR_visitor::visit_signature(HIR_signature* in)
{
    if(in == NULL)
    	visit_null("HIR_signature");
    else
    {
    	pre_signature_chain(in);
    	children_signature(in);
    	post_signature_chain(in);
    }
}

void HIR_visitor::visit_method_mod(HIR_method_mod* in)
{
    if(in == NULL)
    	visit_null("HIR_method_mod");
    else
    {
    	pre_method_mod_chain(in);
    	children_method_mod(in);
    	post_method_mod_chain(in);
    }
}

void HIR_visitor::visit_method_name(Token_method_name* in)
{
    if(in == NULL)
    	visit_null("Token_method_name");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void HIR_visitor::visit_formal_parameter_list(List<HIR_formal_parameter*>* in)
{
    List<HIR_formal_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_formal_parameter");
    else
    {
    	pre_list("HIR_formal_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_formal_parameter(*i);
    	}
    
    	post_list("HIR_formal_parameter", in->size());
    }
}

void HIR_visitor::visit_formal_parameter(HIR_formal_parameter* in)
{
    if(in == NULL)
    	visit_null("HIR_formal_parameter");
    else
    {
    	pre_formal_parameter_chain(in);
    	children_formal_parameter(in);
    	post_formal_parameter_chain(in);
    }
}

void HIR_visitor::visit_type(HIR_type* in)
{
    if(in == NULL)
    	visit_null("HIR_type");
    else
    {
    	pre_type_chain(in);
    	children_type(in);
    	post_type_chain(in);
    }
}

void HIR_visitor::visit_name_with_default(HIR_name_with_default* in)
{
    if(in == NULL)
    	visit_null("HIR_name_with_default");
    else
    {
    	pre_name_with_default_chain(in);
    	children_name_with_default(in);
    	post_name_with_default_chain(in);
    }
}

void HIR_visitor::visit_attr_mod(HIR_attr_mod* in)
{
    if(in == NULL)
    	visit_null("HIR_attr_mod");
    else
    {
    	pre_attr_mod_chain(in);
    	children_attr_mod(in);
    	post_attr_mod_chain(in);
    }
}

void HIR_visitor::visit_variable_name(Token_variable_name* in)
{
    if(in == NULL)
    	visit_null("Token_variable_name");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void HIR_visitor::visit_expr(HIR_expr* in)
{
    if(in == NULL)
    	visit_null("HIR_expr");
    else
    {
    	pre_expr_chain(in);
    	children_expr(in);
    	post_expr_chain(in);
    }
}

void HIR_visitor::visit_variable_name(HIR_variable_name* in)
{
    if(in == NULL)
    	visit_null("HIR_variable_name");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void HIR_visitor::visit_catch_list(List<HIR_catch*>* in)
{
    List<HIR_catch*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_catch");
    else
    {
    	pre_list("HIR_catch", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_catch(*i);
    	}
    
    	post_list("HIR_catch", in->size());
    }
}

void HIR_visitor::visit_catch(HIR_catch* in)
{
    if(in == NULL)
    	visit_null("HIR_catch");
    else
    {
    	pre_catch_chain(in);
    	children_catch(in);
    	post_catch_chain(in);
    }
}

void HIR_visitor::visit_label_name(Token_label_name* in)
{
    if(in == NULL)
    	visit_null("Token_label_name");
    else
    {
    	pre_label_name_chain(in);
    	children_label_name(in);
    	post_label_name_chain(in);
    }
}

void HIR_visitor::visit_variable(HIR_variable* in)
{
    if(in == NULL)
    	visit_null("HIR_variable");
    else
    {
    	pre_variable_chain(in);
    	children_variable(in);
    	post_variable_chain(in);
    }
}

void HIR_visitor::visit_cast(Token_cast* in)
{
    if(in == NULL)
    	visit_null("Token_cast");
    else
    {
    	pre_cast_chain(in);
    	children_cast(in);
    	post_cast_chain(in);
    }
}

void HIR_visitor::visit_op(Token_op* in)
{
    if(in == NULL)
    	visit_null("Token_op");
    else
    {
    	pre_op_chain(in);
    	children_op(in);
    	post_op_chain(in);
    }
}

void HIR_visitor::visit_constant_name(Token_constant_name* in)
{
    if(in == NULL)
    	visit_null("Token_constant_name");
    else
    {
    	pre_constant_name_chain(in);
    	children_constant_name(in);
    	post_constant_name_chain(in);
    }
}

void HIR_visitor::visit_class_name(HIR_class_name* in)
{
    if(in == NULL)
    	visit_null("HIR_class_name");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void HIR_visitor::visit_target(HIR_target* in)
{
    if(in == NULL)
    	visit_null("HIR_target");
    else
    {
    	pre_target_chain(in);
    	children_target(in);
    	post_target_chain(in);
    }
}

void HIR_visitor::visit_expr_list(List<HIR_expr*>* in)
{
    List<HIR_expr*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_expr");
    else
    {
    	pre_list("HIR_expr", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_expr(*i);
    	}
    
    	post_list("HIR_expr", in->size());
    }
}

void HIR_visitor::visit_array_elem_list(List<HIR_array_elem*>* in)
{
    List<HIR_array_elem*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_array_elem");
    else
    {
    	pre_list("HIR_array_elem", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_array_elem(*i);
    	}
    
    	post_list("HIR_array_elem", in->size());
    }
}

void HIR_visitor::visit_array_elem(HIR_array_elem* in)
{
    if(in == NULL)
    	visit_null("HIR_array_elem");
    else
    {
    	pre_array_elem_chain(in);
    	children_array_elem(in);
    	post_array_elem_chain(in);
    }
}

void HIR_visitor::visit_method_name(HIR_method_name* in)
{
    if(in == NULL)
    	visit_null("HIR_method_name");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void HIR_visitor::visit_actual_parameter_list(List<HIR_actual_parameter*>* in)
{
    List<HIR_actual_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("HIR_actual_parameter");
    else
    {
    	pre_list("HIR_actual_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_actual_parameter(*i);
    	}
    
    	post_list("HIR_actual_parameter", in->size());
    }
}

void HIR_visitor::visit_actual_parameter(HIR_actual_parameter* in)
{
    if(in == NULL)
    	visit_null("HIR_actual_parameter");
    else
    {
    	pre_actual_parameter_chain(in);
    	children_actual_parameter(in);
    	post_actual_parameter_chain(in);
    }
}

void HIR_visitor::visit_php_script(HIR_php_script* in)
{
    if(in == NULL)
    	visit_null("HIR_php_script");
    else
    {
    	pre_php_script_chain(in);
    	children_php_script(in);
    	post_php_script_chain(in);
    }
}

// Invoke the right pre-chain (manual dispatching)
// Do not override unless you know what you are doing
void HIR_visitor::pre_statement_chain(HIR_statement* in)
{
    switch(in->classid())
    {
    case HIR_class_def::ID:
    	pre_class_def_chain(dynamic_cast<HIR_class_def*>(in));
    	break;
    case HIR_interface_def::ID:
    	pre_interface_def_chain(dynamic_cast<HIR_interface_def*>(in));
    	break;
    case HIR_method::ID:
    	pre_method_chain(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_return::ID:
    	pre_return_chain(dynamic_cast<HIR_return*>(in));
    	break;
    case HIR_static_declaration::ID:
    	pre_static_declaration_chain(dynamic_cast<HIR_static_declaration*>(in));
    	break;
    case HIR_global::ID:
    	pre_global_chain(dynamic_cast<HIR_global*>(in));
    	break;
    case HIR_try::ID:
    	pre_try_chain(dynamic_cast<HIR_try*>(in));
    	break;
    case HIR_throw::ID:
    	pre_throw_chain(dynamic_cast<HIR_throw*>(in));
    	break;
    case HIR_eval_expr::ID:
    	pre_eval_expr_chain(dynamic_cast<HIR_eval_expr*>(in));
    	break;
    case HIR_label::ID:
    	pre_label_chain(dynamic_cast<HIR_label*>(in));
    	break;
    case HIR_goto::ID:
    	pre_goto_chain(dynamic_cast<HIR_goto*>(in));
    	break;
    case HIR_branch::ID:
    	pre_branch_chain(dynamic_cast<HIR_branch*>(in));
    	break;
    }
}

void HIR_visitor::pre_member_chain(HIR_member* in)
{
    switch(in->classid())
    {
    case HIR_method::ID:
    	pre_method_chain(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_attribute::ID:
    	pre_attribute_chain(dynamic_cast<HIR_attribute*>(in));
    	break;
    }
}

void HIR_visitor::pre_expr_chain(HIR_expr* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	pre_assignment_chain(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	pre_cast_chain(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	pre_constant_chain(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	pre_variable_chain(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	pre_array_chain(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	pre_new_chain(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	pre_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	pre_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	pre_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	pre_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	pre_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void HIR_visitor::pre_variable_name_chain(HIR_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	pre_variable_name_chain(dynamic_cast<Token_variable_name*>(in));
    	break;
    case HIR_reflection::ID:
    	pre_reflection_chain(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_visitor::pre_class_name_chain(HIR_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	pre_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    case HIR_reflection::ID:
    	pre_reflection_chain(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_visitor::pre_target_chain(HIR_target* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	pre_assignment_chain(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	pre_cast_chain(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	pre_constant_chain(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	pre_variable_chain(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	pre_array_chain(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	pre_new_chain(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	pre_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	pre_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	pre_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	pre_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	pre_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    case Token_class_name::ID:
    	pre_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void HIR_visitor::pre_method_name_chain(HIR_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	pre_method_name_chain(dynamic_cast<Token_method_name*>(in));
    	break;
    case HIR_reflection::ID:
    	pre_reflection_chain(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

// Invoke the right post-chain (manual dispatching)
// Do not override unless you know what you are doing
void HIR_visitor::post_statement_chain(HIR_statement* in)
{
    switch(in->classid())
    {
    case HIR_class_def::ID:
    	post_class_def_chain(dynamic_cast<HIR_class_def*>(in));
    	break;
    case HIR_interface_def::ID:
    	post_interface_def_chain(dynamic_cast<HIR_interface_def*>(in));
    	break;
    case HIR_method::ID:
    	post_method_chain(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_return::ID:
    	post_return_chain(dynamic_cast<HIR_return*>(in));
    	break;
    case HIR_static_declaration::ID:
    	post_static_declaration_chain(dynamic_cast<HIR_static_declaration*>(in));
    	break;
    case HIR_global::ID:
    	post_global_chain(dynamic_cast<HIR_global*>(in));
    	break;
    case HIR_try::ID:
    	post_try_chain(dynamic_cast<HIR_try*>(in));
    	break;
    case HIR_throw::ID:
    	post_throw_chain(dynamic_cast<HIR_throw*>(in));
    	break;
    case HIR_eval_expr::ID:
    	post_eval_expr_chain(dynamic_cast<HIR_eval_expr*>(in));
    	break;
    case HIR_label::ID:
    	post_label_chain(dynamic_cast<HIR_label*>(in));
    	break;
    case HIR_goto::ID:
    	post_goto_chain(dynamic_cast<HIR_goto*>(in));
    	break;
    case HIR_branch::ID:
    	post_branch_chain(dynamic_cast<HIR_branch*>(in));
    	break;
    }
}

void HIR_visitor::post_member_chain(HIR_member* in)
{
    switch(in->classid())
    {
    case HIR_method::ID:
    	post_method_chain(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_attribute::ID:
    	post_attribute_chain(dynamic_cast<HIR_attribute*>(in));
    	break;
    }
}

void HIR_visitor::post_expr_chain(HIR_expr* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	post_assignment_chain(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	post_cast_chain(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	post_unary_op_chain(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	post_bin_op_chain(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	post_constant_chain(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	post_instanceof_chain(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	post_variable_chain(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	post_pre_op_chain(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	post_array_chain(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	post_new_chain(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	post_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	post_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	post_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	post_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	post_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void HIR_visitor::post_variable_name_chain(HIR_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	post_variable_name_chain(dynamic_cast<Token_variable_name*>(in));
    	break;
    case HIR_reflection::ID:
    	post_reflection_chain(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_visitor::post_class_name_chain(HIR_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	post_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    case HIR_reflection::ID:
    	post_reflection_chain(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_visitor::post_target_chain(HIR_target* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	post_assignment_chain(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	post_cast_chain(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	post_unary_op_chain(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	post_bin_op_chain(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	post_constant_chain(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	post_instanceof_chain(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	post_variable_chain(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	post_pre_op_chain(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	post_array_chain(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	post_new_chain(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	post_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	post_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	post_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	post_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	post_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    case Token_class_name::ID:
    	post_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void HIR_visitor::post_method_name_chain(HIR_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	post_method_name_chain(dynamic_cast<Token_method_name*>(in));
    	break;
    case HIR_reflection::ID:
    	post_reflection_chain(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

// Invoke the right visit-children (manual dispatching)
// Do not override unless you know what you are doing
void HIR_visitor::children_statement(HIR_statement* in)
{
    switch(in->classid())
    {
    case HIR_class_def::ID:
    	children_class_def(dynamic_cast<HIR_class_def*>(in));
    	break;
    case HIR_interface_def::ID:
    	children_interface_def(dynamic_cast<HIR_interface_def*>(in));
    	break;
    case HIR_method::ID:
    	children_method(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_return::ID:
    	children_return(dynamic_cast<HIR_return*>(in));
    	break;
    case HIR_static_declaration::ID:
    	children_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
    	break;
    case HIR_global::ID:
    	children_global(dynamic_cast<HIR_global*>(in));
    	break;
    case HIR_try::ID:
    	children_try(dynamic_cast<HIR_try*>(in));
    	break;
    case HIR_throw::ID:
    	children_throw(dynamic_cast<HIR_throw*>(in));
    	break;
    case HIR_eval_expr::ID:
    	children_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
    	break;
    case HIR_label::ID:
    	children_label(dynamic_cast<HIR_label*>(in));
    	break;
    case HIR_goto::ID:
    	children_goto(dynamic_cast<HIR_goto*>(in));
    	break;
    case HIR_branch::ID:
    	children_branch(dynamic_cast<HIR_branch*>(in));
    	break;
    }
}

void HIR_visitor::children_member(HIR_member* in)
{
    switch(in->classid())
    {
    case HIR_method::ID:
    	children_method(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_attribute::ID:
    	children_attribute(dynamic_cast<HIR_attribute*>(in));
    	break;
    }
}

void HIR_visitor::children_expr(HIR_expr* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	children_assignment(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	children_cast(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	children_unary_op(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	children_bin_op(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	children_constant(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	children_instanceof(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	children_variable(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	children_pre_op(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	children_array(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	children_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	children_new(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void HIR_visitor::children_variable_name(HIR_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	children_variable_name(dynamic_cast<Token_variable_name*>(in));
    	break;
    case HIR_reflection::ID:
    	children_reflection(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_visitor::children_class_name(HIR_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    case HIR_reflection::ID:
    	children_reflection(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_visitor::children_target(HIR_target* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	children_assignment(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	children_cast(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	children_unary_op(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	children_bin_op(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	children_constant(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	children_instanceof(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	children_variable(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	children_pre_op(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	children_array(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	children_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	children_new(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    case Token_class_name::ID:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void HIR_visitor::children_method_name(HIR_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	children_method_name(dynamic_cast<Token_method_name*>(in));
    	break;
    case HIR_reflection::ID:
    	children_reflection(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}
}

