#include "AST_visitor.h"

AST_visitor::~AST_visitor()
{
}

// Invoked before the children are visited
void AST_visitor::pre_node(AST_node* in)
{
}

void AST_visitor::pre_php_script(AST_php_script* in)
{
}

void AST_visitor::pre_statement(AST_statement* in)
{
}

void AST_visitor::pre_class_def(AST_class_def* in)
{
}

void AST_visitor::pre_class_mod(AST_class_mod* in)
{
}

void AST_visitor::pre_interface_def(AST_interface_def* in)
{
}

void AST_visitor::pre_member(AST_member* in)
{
}

void AST_visitor::pre_method(AST_method* in)
{
}

void AST_visitor::pre_signature(AST_signature* in)
{
}

void AST_visitor::pre_method_mod(AST_method_mod* in)
{
}

void AST_visitor::pre_formal_parameter(AST_formal_parameter* in)
{
}

void AST_visitor::pre_type(AST_type* in)
{
}

void AST_visitor::pre_attribute(AST_attribute* in)
{
}

void AST_visitor::pre_attr_mod(AST_attr_mod* in)
{
}

void AST_visitor::pre_if(AST_if* in)
{
}

void AST_visitor::pre_while(AST_while* in)
{
}

void AST_visitor::pre_do(AST_do* in)
{
}

void AST_visitor::pre_for(AST_for* in)
{
}

void AST_visitor::pre_foreach(AST_foreach* in)
{
}

void AST_visitor::pre_switch(AST_switch* in)
{
}

void AST_visitor::pre_switch_case(AST_switch_case* in)
{
}

void AST_visitor::pre_break(AST_break* in)
{
}

void AST_visitor::pre_continue(AST_continue* in)
{
}

void AST_visitor::pre_return(AST_return* in)
{
}

void AST_visitor::pre_branch(AST_branch* in)
{
}

void AST_visitor::pre_goto(AST_goto* in)
{
}

void AST_visitor::pre_label(AST_label* in)
{
}

void AST_visitor::pre_static_declaration(AST_static_declaration* in)
{
}

void AST_visitor::pre_global(AST_global* in)
{
}

void AST_visitor::pre_unset(AST_unset* in)
{
}

void AST_visitor::pre_declare(AST_declare* in)
{
}

void AST_visitor::pre_directive(AST_directive* in)
{
}

void AST_visitor::pre_try(AST_try* in)
{
}

void AST_visitor::pre_catch(AST_catch* in)
{
}

void AST_visitor::pre_throw(AST_throw* in)
{
}

void AST_visitor::pre_eval_expr(AST_eval_expr* in)
{
}

void AST_visitor::pre_nop(AST_nop* in)
{
}

void AST_visitor::pre_expr(AST_expr* in)
{
}

void AST_visitor::pre_literal(AST_literal* in)
{
}

void AST_visitor::pre_assignment(AST_assignment* in)
{
}

void AST_visitor::pre_list_assignment(AST_list_assignment* in)
{
}

void AST_visitor::pre_list_element(AST_list_element* in)
{
}

void AST_visitor::pre_nested_list_elements(AST_nested_list_elements* in)
{
}

void AST_visitor::pre_cast(AST_cast* in)
{
}

void AST_visitor::pre_unary_op(AST_unary_op* in)
{
}

void AST_visitor::pre_bin_op(AST_bin_op* in)
{
}

void AST_visitor::pre_conditional_expr(AST_conditional_expr* in)
{
}

void AST_visitor::pre_ignore_errors(AST_ignore_errors* in)
{
}

void AST_visitor::pre_constant(AST_constant* in)
{
}

void AST_visitor::pre_instanceof(AST_instanceof* in)
{
}

void AST_visitor::pre_variable(AST_variable* in)
{
}

void AST_visitor::pre_variable_name(AST_variable_name* in)
{
}

void AST_visitor::pre_reflection(AST_reflection* in)
{
}

void AST_visitor::pre_target(AST_target* in)
{
}

void AST_visitor::pre_pre_op(AST_pre_op* in)
{
}

void AST_visitor::pre_post_op(AST_post_op* in)
{
}

void AST_visitor::pre_array(AST_array* in)
{
}

void AST_visitor::pre_array_elem(AST_array_elem* in)
{
}

void AST_visitor::pre_method_invocation(AST_method_invocation* in)
{
}

void AST_visitor::pre_method_name(AST_method_name* in)
{
}

void AST_visitor::pre_actual_parameter(AST_actual_parameter* in)
{
}

void AST_visitor::pre_new(AST_new* in)
{
}

void AST_visitor::pre_class_name(AST_class_name* in)
{
}

void AST_visitor::pre_clone(AST_clone* in)
{
}

void AST_visitor::pre_commented_node(AST_commented_node* in)
{
}

void AST_visitor::pre_identifier(AST_identifier* in)
{
}

void AST_visitor::pre_class_name(Token_class_name* in)
{
}

void AST_visitor::pre_interface_name(Token_interface_name* in)
{
}

void AST_visitor::pre_method_name(Token_method_name* in)
{
}

void AST_visitor::pre_variable_name(Token_variable_name* in)
{
}

void AST_visitor::pre_label_name(Token_label_name* in)
{
}

void AST_visitor::pre_directive_name(Token_directive_name* in)
{
}

void AST_visitor::pre_int(Token_int* in)
{
}

void AST_visitor::pre_real(Token_real* in)
{
}

void AST_visitor::pre_string(Token_string* in)
{
}

void AST_visitor::pre_bool(Token_bool* in)
{
}

void AST_visitor::pre_null(Token_null* in)
{
}

void AST_visitor::pre_cast(Token_cast* in)
{
}

void AST_visitor::pre_op(Token_op* in)
{
}

void AST_visitor::pre_constant_name(Token_constant_name* in)
{
}

// Invoked after the children have been visited
void AST_visitor::post_node(AST_node* in)
{
}

void AST_visitor::post_php_script(AST_php_script* in)
{
}

void AST_visitor::post_statement(AST_statement* in)
{
}

void AST_visitor::post_class_def(AST_class_def* in)
{
}

void AST_visitor::post_class_mod(AST_class_mod* in)
{
}

void AST_visitor::post_interface_def(AST_interface_def* in)
{
}

void AST_visitor::post_member(AST_member* in)
{
}

void AST_visitor::post_method(AST_method* in)
{
}

void AST_visitor::post_signature(AST_signature* in)
{
}

void AST_visitor::post_method_mod(AST_method_mod* in)
{
}

void AST_visitor::post_formal_parameter(AST_formal_parameter* in)
{
}

void AST_visitor::post_type(AST_type* in)
{
}

void AST_visitor::post_attribute(AST_attribute* in)
{
}

void AST_visitor::post_attr_mod(AST_attr_mod* in)
{
}

void AST_visitor::post_if(AST_if* in)
{
}

void AST_visitor::post_while(AST_while* in)
{
}

void AST_visitor::post_do(AST_do* in)
{
}

void AST_visitor::post_for(AST_for* in)
{
}

void AST_visitor::post_foreach(AST_foreach* in)
{
}

void AST_visitor::post_switch(AST_switch* in)
{
}

void AST_visitor::post_switch_case(AST_switch_case* in)
{
}

void AST_visitor::post_break(AST_break* in)
{
}

void AST_visitor::post_continue(AST_continue* in)
{
}

void AST_visitor::post_return(AST_return* in)
{
}

void AST_visitor::post_branch(AST_branch* in)
{
}

void AST_visitor::post_goto(AST_goto* in)
{
}

void AST_visitor::post_label(AST_label* in)
{
}

void AST_visitor::post_static_declaration(AST_static_declaration* in)
{
}

void AST_visitor::post_global(AST_global* in)
{
}

void AST_visitor::post_unset(AST_unset* in)
{
}

void AST_visitor::post_declare(AST_declare* in)
{
}

void AST_visitor::post_directive(AST_directive* in)
{
}

void AST_visitor::post_try(AST_try* in)
{
}

void AST_visitor::post_catch(AST_catch* in)
{
}

void AST_visitor::post_throw(AST_throw* in)
{
}

void AST_visitor::post_eval_expr(AST_eval_expr* in)
{
}

void AST_visitor::post_nop(AST_nop* in)
{
}

void AST_visitor::post_expr(AST_expr* in)
{
}

void AST_visitor::post_literal(AST_literal* in)
{
}

void AST_visitor::post_assignment(AST_assignment* in)
{
}

void AST_visitor::post_list_assignment(AST_list_assignment* in)
{
}

void AST_visitor::post_list_element(AST_list_element* in)
{
}

void AST_visitor::post_nested_list_elements(AST_nested_list_elements* in)
{
}

void AST_visitor::post_cast(AST_cast* in)
{
}

void AST_visitor::post_unary_op(AST_unary_op* in)
{
}

void AST_visitor::post_bin_op(AST_bin_op* in)
{
}

void AST_visitor::post_conditional_expr(AST_conditional_expr* in)
{
}

void AST_visitor::post_ignore_errors(AST_ignore_errors* in)
{
}

void AST_visitor::post_constant(AST_constant* in)
{
}

void AST_visitor::post_instanceof(AST_instanceof* in)
{
}

void AST_visitor::post_variable(AST_variable* in)
{
}

void AST_visitor::post_variable_name(AST_variable_name* in)
{
}

void AST_visitor::post_reflection(AST_reflection* in)
{
}

void AST_visitor::post_target(AST_target* in)
{
}

void AST_visitor::post_pre_op(AST_pre_op* in)
{
}

void AST_visitor::post_post_op(AST_post_op* in)
{
}

void AST_visitor::post_array(AST_array* in)
{
}

void AST_visitor::post_array_elem(AST_array_elem* in)
{
}

void AST_visitor::post_method_invocation(AST_method_invocation* in)
{
}

void AST_visitor::post_method_name(AST_method_name* in)
{
}

void AST_visitor::post_actual_parameter(AST_actual_parameter* in)
{
}

void AST_visitor::post_new(AST_new* in)
{
}

void AST_visitor::post_class_name(AST_class_name* in)
{
}

void AST_visitor::post_clone(AST_clone* in)
{
}

void AST_visitor::post_commented_node(AST_commented_node* in)
{
}

void AST_visitor::post_identifier(AST_identifier* in)
{
}

void AST_visitor::post_class_name(Token_class_name* in)
{
}

void AST_visitor::post_interface_name(Token_interface_name* in)
{
}

void AST_visitor::post_method_name(Token_method_name* in)
{
}

void AST_visitor::post_variable_name(Token_variable_name* in)
{
}

void AST_visitor::post_label_name(Token_label_name* in)
{
}

void AST_visitor::post_directive_name(Token_directive_name* in)
{
}

void AST_visitor::post_int(Token_int* in)
{
}

void AST_visitor::post_real(Token_real* in)
{
}

void AST_visitor::post_string(Token_string* in)
{
}

void AST_visitor::post_bool(Token_bool* in)
{
}

void AST_visitor::post_null(Token_null* in)
{
}

void AST_visitor::post_cast(Token_cast* in)
{
}

void AST_visitor::post_op(Token_op* in)
{
}

void AST_visitor::post_constant_name(Token_constant_name* in)
{
}

// Visit the children of a node
void AST_visitor::children_php_script(AST_php_script* in)
{
    visit_statement_list(in->statements);
}

void AST_visitor::children_class_def(AST_class_def* in)
{
    visit_class_mod(in->class_mod);
    visit_class_name(in->class_name);
    visit_class_name(in->extends);
    visit_interface_name_list(in->implements);
    visit_member_list(in->members);
}

void AST_visitor::children_class_mod(AST_class_mod* in)
{
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void AST_visitor::children_interface_def(AST_interface_def* in)
{
    visit_interface_name(in->interface_name);
    visit_interface_name_list(in->extends);
    visit_member_list(in->members);
}

void AST_visitor::children_method(AST_method* in)
{
    visit_signature(in->signature);
    visit_statement_list(in->statements);
}

void AST_visitor::children_signature(AST_signature* in)
{
    visit_method_mod(in->method_mod);
    visit_marker("is_ref", in->is_ref);
    visit_method_name(in->method_name);
    visit_formal_parameter_list(in->formal_parameters);
}

void AST_visitor::children_method_mod(AST_method_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void AST_visitor::children_formal_parameter(AST_formal_parameter* in)
{
    visit_type(in->type);
    visit_marker("is_ref", in->is_ref);
    visit_variable_name(in->variable_name);
    visit_expr(in->expr);
}

void AST_visitor::children_type(AST_type* in)
{
    visit_class_name(in->class_name);
}

void AST_visitor::children_attribute(AST_attribute* in)
{
    visit_attr_mod(in->attr_mod);
    visit_variable_name(in->variable_name);
    visit_expr(in->expr);
}

void AST_visitor::children_attr_mod(AST_attr_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_const", in->is_const);
}

void AST_visitor::children_if(AST_if* in)
{
    visit_expr(in->expr);
    visit_statement_list(in->iftrue);
    visit_statement_list(in->iffalse);
}

void AST_visitor::children_while(AST_while* in)
{
    visit_expr(in->expr);
    visit_statement_list(in->statements);
}

void AST_visitor::children_do(AST_do* in)
{
    visit_statement_list(in->statements);
    visit_expr(in->expr);
}

void AST_visitor::children_for(AST_for* in)
{
    visit_expr(in->init);
    visit_expr(in->cond);
    visit_expr(in->incr);
    visit_statement_list(in->statements);
}

void AST_visitor::children_foreach(AST_foreach* in)
{
    visit_expr(in->expr);
    visit_variable(in->key);
    visit_marker("is_ref", in->is_ref);
    visit_variable(in->val);
    visit_statement_list(in->statements);
}

void AST_visitor::children_switch(AST_switch* in)
{
    visit_expr(in->expr);
    visit_switch_case_list(in->switch_cases);
}

void AST_visitor::children_switch_case(AST_switch_case* in)
{
    visit_expr(in->expr);
    visit_statement_list(in->statements);
}

void AST_visitor::children_break(AST_break* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_continue(AST_continue* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_return(AST_return* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_branch(AST_branch* in)
{
    visit_expr(in->expr);
    visit_label_name(in->iftrue);
    visit_label_name(in->iffalse);
}

void AST_visitor::children_goto(AST_goto* in)
{
    visit_label_name(in->label_name);
}

void AST_visitor::children_label(AST_label* in)
{
    visit_label_name(in->label_name);
}

void AST_visitor::children_static_declaration(AST_static_declaration* in)
{
    visit_variable_name(in->variable_name);
    visit_expr(in->expr);
}

void AST_visitor::children_global(AST_global* in)
{
    visit_variable_name(in->variable_name);
}

void AST_visitor::children_unset(AST_unset* in)
{
    visit_variable(in->variable);
}

void AST_visitor::children_declare(AST_declare* in)
{
    visit_directive_list(in->directives);
    visit_statement_list(in->statements);
}

void AST_visitor::children_directive(AST_directive* in)
{
    visit_directive_name(in->directive_name);
    visit_expr(in->expr);
}

void AST_visitor::children_try(AST_try* in)
{
    visit_statement_list(in->statements);
    visit_catch_list(in->catches);
}

void AST_visitor::children_catch(AST_catch* in)
{
    visit_class_name(in->class_name);
    visit_variable_name(in->variable_name);
    visit_statement_list(in->statements);
}

void AST_visitor::children_throw(AST_throw* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_eval_expr(AST_eval_expr* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_nop(AST_nop* in)
{
}

void AST_visitor::children_assignment(AST_assignment* in)
{
    visit_variable(in->variable);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->expr);
}

void AST_visitor::children_list_assignment(AST_list_assignment* in)
{
    visit_list_element_list(in->list_elements);
    visit_expr(in->expr);
}

void AST_visitor::children_nested_list_elements(AST_nested_list_elements* in)
{
    visit_list_element_list(in->list_elements);
}

void AST_visitor::children_cast(AST_cast* in)
{
    visit_cast(in->cast);
    visit_expr(in->expr);
}

void AST_visitor::children_unary_op(AST_unary_op* in)
{
    visit_op(in->op);
    visit_expr(in->expr);
}

void AST_visitor::children_bin_op(AST_bin_op* in)
{
    visit_expr(in->left);
    visit_op(in->op);
    visit_expr(in->right);
}

void AST_visitor::children_conditional_expr(AST_conditional_expr* in)
{
    visit_expr(in->cond);
    visit_expr(in->iftrue);
    visit_expr(in->iffalse);
}

void AST_visitor::children_ignore_errors(AST_ignore_errors* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_constant(AST_constant* in)
{
    visit_class_name(in->class_name);
    visit_constant_name(in->constant_name);
}

void AST_visitor::children_instanceof(AST_instanceof* in)
{
    visit_expr(in->expr);
    visit_class_name(in->class_name);
}

void AST_visitor::children_variable(AST_variable* in)
{
    visit_target(in->target);
    visit_variable_name(in->variable_name);
    visit_expr_list(in->array_indices);
}

void AST_visitor::children_reflection(AST_reflection* in)
{
    visit_expr(in->expr);
}

void AST_visitor::children_pre_op(AST_pre_op* in)
{
    visit_op(in->op);
    visit_variable(in->variable);
}

void AST_visitor::children_post_op(AST_post_op* in)
{
    visit_variable(in->variable);
    visit_op(in->op);
}

void AST_visitor::children_array(AST_array* in)
{
    visit_array_elem_list(in->array_elems);
}

void AST_visitor::children_array_elem(AST_array_elem* in)
{
    visit_expr(in->key);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->val);
}

void AST_visitor::children_method_invocation(AST_method_invocation* in)
{
    visit_target(in->target);
    visit_method_name(in->method_name);
    visit_actual_parameter_list(in->actual_parameters);
}

void AST_visitor::children_actual_parameter(AST_actual_parameter* in)
{
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->expr);
}

void AST_visitor::children_new(AST_new* in)
{
    visit_class_name(in->class_name);
    visit_actual_parameter_list(in->actual_parameters);
}

void AST_visitor::children_clone(AST_clone* in)
{
    visit_expr(in->expr);
}

// Tokens don't have children, so these methods do nothing by default
void AST_visitor::children_class_name(Token_class_name* in)
{
}

void AST_visitor::children_interface_name(Token_interface_name* in)
{
}

void AST_visitor::children_method_name(Token_method_name* in)
{
}

void AST_visitor::children_variable_name(Token_variable_name* in)
{
}

void AST_visitor::children_label_name(Token_label_name* in)
{
}

void AST_visitor::children_directive_name(Token_directive_name* in)
{
}

void AST_visitor::children_int(Token_int* in)
{
}

void AST_visitor::children_real(Token_real* in)
{
}

void AST_visitor::children_string(Token_string* in)
{
}

void AST_visitor::children_bool(Token_bool* in)
{
}

void AST_visitor::children_null(Token_null* in)
{
}

void AST_visitor::children_cast(Token_cast* in)
{
}

void AST_visitor::children_op(Token_op* in)
{
}

void AST_visitor::children_constant_name(Token_constant_name* in)
{
}

// Unparser support
void AST_visitor::visit_marker(char const* name, bool value)
{
}

void AST_visitor::visit_null(char const* type_id)
{
}

void AST_visitor::visit_null_list(char const* type_id)
{
}

void AST_visitor::pre_list(char const* type_id, int size)
{
}

void AST_visitor::post_list(char const* type_id, int size)
{
}

// Invoke the chain of pre-visit methods along the inheritance hierachy
// Do not override unless you know what you are doing
void AST_visitor::pre_php_script_chain(AST_php_script* in)
{
    pre_node(in);
    pre_php_script(in);
}

void AST_visitor::pre_class_def_chain(AST_class_def* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_class_def(in);
}

void AST_visitor::pre_class_mod_chain(AST_class_mod* in)
{
    pre_node(in);
    pre_class_mod(in);
}

void AST_visitor::pre_interface_def_chain(AST_interface_def* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_interface_def(in);
}

void AST_visitor::pre_method_chain(AST_method* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_member(in);
    pre_statement(in);
    pre_method(in);
}

void AST_visitor::pre_signature_chain(AST_signature* in)
{
    pre_node(in);
    pre_signature(in);
}

void AST_visitor::pre_method_mod_chain(AST_method_mod* in)
{
    pre_node(in);
    pre_method_mod(in);
}

void AST_visitor::pre_formal_parameter_chain(AST_formal_parameter* in)
{
    pre_node(in);
    pre_formal_parameter(in);
}

void AST_visitor::pre_type_chain(AST_type* in)
{
    pre_node(in);
    pre_type(in);
}

void AST_visitor::pre_attribute_chain(AST_attribute* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_member(in);
    pre_attribute(in);
}

void AST_visitor::pre_attr_mod_chain(AST_attr_mod* in)
{
    pre_node(in);
    pre_attr_mod(in);
}

void AST_visitor::pre_if_chain(AST_if* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_if(in);
}

void AST_visitor::pre_while_chain(AST_while* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_while(in);
}

void AST_visitor::pre_do_chain(AST_do* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_do(in);
}

void AST_visitor::pre_for_chain(AST_for* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_for(in);
}

void AST_visitor::pre_foreach_chain(AST_foreach* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_foreach(in);
}

void AST_visitor::pre_switch_chain(AST_switch* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_switch(in);
}

void AST_visitor::pre_switch_case_chain(AST_switch_case* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_switch_case(in);
}

void AST_visitor::pre_break_chain(AST_break* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_break(in);
}

void AST_visitor::pre_continue_chain(AST_continue* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_continue(in);
}

void AST_visitor::pre_return_chain(AST_return* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_return(in);
}

void AST_visitor::pre_branch_chain(AST_branch* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_branch(in);
}

void AST_visitor::pre_goto_chain(AST_goto* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_goto(in);
}

void AST_visitor::pre_label_chain(AST_label* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_label(in);
}

void AST_visitor::pre_static_declaration_chain(AST_static_declaration* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_static_declaration(in);
}

void AST_visitor::pre_global_chain(AST_global* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_global(in);
}

void AST_visitor::pre_unset_chain(AST_unset* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_unset(in);
}

void AST_visitor::pre_declare_chain(AST_declare* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_declare(in);
}

void AST_visitor::pre_directive_chain(AST_directive* in)
{
    pre_node(in);
    pre_directive(in);
}

void AST_visitor::pre_try_chain(AST_try* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_try(in);
}

void AST_visitor::pre_catch_chain(AST_catch* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_catch(in);
}

void AST_visitor::pre_throw_chain(AST_throw* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_throw(in);
}

void AST_visitor::pre_eval_expr_chain(AST_eval_expr* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_eval_expr(in);
}

void AST_visitor::pre_nop_chain(AST_nop* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_nop(in);
}

void AST_visitor::pre_assignment_chain(AST_assignment* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_assignment(in);
}

void AST_visitor::pre_list_assignment_chain(AST_list_assignment* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_list_assignment(in);
}

void AST_visitor::pre_nested_list_elements_chain(AST_nested_list_elements* in)
{
    pre_node(in);
    pre_list_element(in);
    pre_nested_list_elements(in);
}

void AST_visitor::pre_cast_chain(AST_cast* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_cast(in);
}

void AST_visitor::pre_unary_op_chain(AST_unary_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_unary_op(in);
}

void AST_visitor::pre_bin_op_chain(AST_bin_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_bin_op(in);
}

void AST_visitor::pre_conditional_expr_chain(AST_conditional_expr* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_conditional_expr(in);
}

void AST_visitor::pre_ignore_errors_chain(AST_ignore_errors* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_ignore_errors(in);
}

void AST_visitor::pre_constant_chain(AST_constant* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_constant(in);
}

void AST_visitor::pre_instanceof_chain(AST_instanceof* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_instanceof(in);
}

void AST_visitor::pre_variable_chain(AST_variable* in)
{
    pre_node(in);
    pre_list_element(in);
    pre_target(in);
    pre_expr(in);
    pre_variable(in);
}

void AST_visitor::pre_reflection_chain(AST_reflection* in)
{
    pre_node(in);
    pre_variable_name(in);
    pre_method_name(in);
    pre_class_name(in);
    pre_reflection(in);
}

void AST_visitor::pre_pre_op_chain(AST_pre_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_pre_op(in);
}

void AST_visitor::pre_post_op_chain(AST_post_op* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_post_op(in);
}

void AST_visitor::pre_array_chain(AST_array* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_array(in);
}

void AST_visitor::pre_array_elem_chain(AST_array_elem* in)
{
    pre_node(in);
    pre_array_elem(in);
}

void AST_visitor::pre_method_invocation_chain(AST_method_invocation* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_method_invocation(in);
}

void AST_visitor::pre_actual_parameter_chain(AST_actual_parameter* in)
{
    pre_node(in);
    pre_actual_parameter(in);
}

void AST_visitor::pre_new_chain(AST_new* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_new(in);
}

void AST_visitor::pre_clone_chain(AST_clone* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_clone(in);
}

void AST_visitor::pre_class_name_chain(Token_class_name* in)
{
    pre_node(in);
    pre_target(in);
    pre_class_name(in);
    pre_identifier(in);
    pre_class_name(in);
}

void AST_visitor::pre_interface_name_chain(Token_interface_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_interface_name(in);
}

void AST_visitor::pre_method_name_chain(Token_method_name* in)
{
    pre_node(in);
    pre_method_name(in);
    pre_identifier(in);
    pre_method_name(in);
}

void AST_visitor::pre_variable_name_chain(Token_variable_name* in)
{
    pre_node(in);
    pre_variable_name(in);
    pre_identifier(in);
    pre_variable_name(in);
}

void AST_visitor::pre_label_name_chain(Token_label_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_label_name(in);
}

void AST_visitor::pre_directive_name_chain(Token_directive_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_directive_name(in);
}

void AST_visitor::pre_int_chain(Token_int* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_int(in);
}

void AST_visitor::pre_real_chain(Token_real* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_real(in);
}

void AST_visitor::pre_string_chain(Token_string* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_string(in);
}

void AST_visitor::pre_bool_chain(Token_bool* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_bool(in);
}

void AST_visitor::pre_null_chain(Token_null* in)
{
    pre_node(in);
    pre_target(in);
    pre_expr(in);
    pre_literal(in);
    pre_null(in);
}

void AST_visitor::pre_cast_chain(Token_cast* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_cast(in);
}

void AST_visitor::pre_op_chain(Token_op* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_op(in);
}

void AST_visitor::pre_constant_name_chain(Token_constant_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_constant_name(in);
}

// Invoke the chain of post-visit methods along the inheritance hierarchy
// (invoked in opposite order to the pre-chain)
// Do not override unless you know what you are doing
void AST_visitor::post_php_script_chain(AST_php_script* in)
{
    post_php_script(in);
    post_node(in);
}

void AST_visitor::post_class_def_chain(AST_class_def* in)
{
    post_class_def(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_class_mod_chain(AST_class_mod* in)
{
    post_class_mod(in);
    post_node(in);
}

void AST_visitor::post_interface_def_chain(AST_interface_def* in)
{
    post_interface_def(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_method_chain(AST_method* in)
{
    post_method(in);
    post_statement(in);
    post_member(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_signature_chain(AST_signature* in)
{
    post_signature(in);
    post_node(in);
}

void AST_visitor::post_method_mod_chain(AST_method_mod* in)
{
    post_method_mod(in);
    post_node(in);
}

void AST_visitor::post_formal_parameter_chain(AST_formal_parameter* in)
{
    post_formal_parameter(in);
    post_node(in);
}

void AST_visitor::post_type_chain(AST_type* in)
{
    post_type(in);
    post_node(in);
}

void AST_visitor::post_attribute_chain(AST_attribute* in)
{
    post_attribute(in);
    post_member(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_attr_mod_chain(AST_attr_mod* in)
{
    post_attr_mod(in);
    post_node(in);
}

void AST_visitor::post_if_chain(AST_if* in)
{
    post_if(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_while_chain(AST_while* in)
{
    post_while(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_do_chain(AST_do* in)
{
    post_do(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_for_chain(AST_for* in)
{
    post_for(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_foreach_chain(AST_foreach* in)
{
    post_foreach(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_switch_chain(AST_switch* in)
{
    post_switch(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_switch_case_chain(AST_switch_case* in)
{
    post_switch_case(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_break_chain(AST_break* in)
{
    post_break(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_continue_chain(AST_continue* in)
{
    post_continue(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_return_chain(AST_return* in)
{
    post_return(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_branch_chain(AST_branch* in)
{
    post_branch(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_goto_chain(AST_goto* in)
{
    post_goto(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_label_chain(AST_label* in)
{
    post_label(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_static_declaration_chain(AST_static_declaration* in)
{
    post_static_declaration(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_global_chain(AST_global* in)
{
    post_global(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_unset_chain(AST_unset* in)
{
    post_unset(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_declare_chain(AST_declare* in)
{
    post_declare(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_directive_chain(AST_directive* in)
{
    post_directive(in);
    post_node(in);
}

void AST_visitor::post_try_chain(AST_try* in)
{
    post_try(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_catch_chain(AST_catch* in)
{
    post_catch(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_throw_chain(AST_throw* in)
{
    post_throw(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_eval_expr_chain(AST_eval_expr* in)
{
    post_eval_expr(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_nop_chain(AST_nop* in)
{
    post_nop(in);
    post_statement(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_assignment_chain(AST_assignment* in)
{
    post_assignment(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_list_assignment_chain(AST_list_assignment* in)
{
    post_list_assignment(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_nested_list_elements_chain(AST_nested_list_elements* in)
{
    post_nested_list_elements(in);
    post_list_element(in);
    post_node(in);
}

void AST_visitor::post_cast_chain(AST_cast* in)
{
    post_cast(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_unary_op_chain(AST_unary_op* in)
{
    post_unary_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_bin_op_chain(AST_bin_op* in)
{
    post_bin_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_conditional_expr_chain(AST_conditional_expr* in)
{
    post_conditional_expr(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_ignore_errors_chain(AST_ignore_errors* in)
{
    post_ignore_errors(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_constant_chain(AST_constant* in)
{
    post_constant(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_instanceof_chain(AST_instanceof* in)
{
    post_instanceof(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_variable_chain(AST_variable* in)
{
    post_variable(in);
    post_expr(in);
    post_target(in);
    post_list_element(in);
    post_node(in);
}

void AST_visitor::post_reflection_chain(AST_reflection* in)
{
    post_reflection(in);
    post_class_name(in);
    post_method_name(in);
    post_variable_name(in);
    post_node(in);
}

void AST_visitor::post_pre_op_chain(AST_pre_op* in)
{
    post_pre_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_post_op_chain(AST_post_op* in)
{
    post_post_op(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_array_chain(AST_array* in)
{
    post_array(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_array_elem_chain(AST_array_elem* in)
{
    post_array_elem(in);
    post_node(in);
}

void AST_visitor::post_method_invocation_chain(AST_method_invocation* in)
{
    post_method_invocation(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_actual_parameter_chain(AST_actual_parameter* in)
{
    post_actual_parameter(in);
    post_node(in);
}

void AST_visitor::post_new_chain(AST_new* in)
{
    post_new(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_clone_chain(AST_clone* in)
{
    post_clone(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_class_name_chain(Token_class_name* in)
{
    post_class_name(in);
    post_identifier(in);
    post_class_name(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_interface_name_chain(Token_interface_name* in)
{
    post_interface_name(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_method_name_chain(Token_method_name* in)
{
    post_method_name(in);
    post_identifier(in);
    post_method_name(in);
    post_node(in);
}

void AST_visitor::post_variable_name_chain(Token_variable_name* in)
{
    post_variable_name(in);
    post_identifier(in);
    post_variable_name(in);
    post_node(in);
}

void AST_visitor::post_label_name_chain(Token_label_name* in)
{
    post_label_name(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_directive_name_chain(Token_directive_name* in)
{
    post_directive_name(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_int_chain(Token_int* in)
{
    post_int(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_real_chain(Token_real* in)
{
    post_real(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_string_chain(Token_string* in)
{
    post_string(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_bool_chain(Token_bool* in)
{
    post_bool(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_null_chain(Token_null* in)
{
    post_null(in);
    post_literal(in);
    post_expr(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_cast_chain(Token_cast* in)
{
    post_cast(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_op_chain(Token_op* in)
{
    post_op(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_constant_name_chain(Token_constant_name* in)
{
    post_constant_name(in);
    post_identifier(in);
    post_node(in);
}

// Call the pre-chain, visit children and post-chain in order
// Do not override unless you know what you are doing
void AST_visitor::visit_statement_list(List<AST_statement*>* in)
{
    List<AST_statement*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_statement");
    else
    {
    	pre_list("AST_statement", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_statement(*i);
    	}
    
    	post_list("AST_statement", in->size());
    }
}

void AST_visitor::visit_statement(AST_statement* in)
{
    if(in == NULL)
    	visit_null("AST_statement");
    else
    {
    	pre_statement_chain(in);
    	children_statement(in);
    	post_statement_chain(in);
    }
}

void AST_visitor::visit_class_mod(AST_class_mod* in)
{
    if(in == NULL)
    	visit_null("AST_class_mod");
    else
    {
    	pre_class_mod_chain(in);
    	children_class_mod(in);
    	post_class_mod_chain(in);
    }
}

void AST_visitor::visit_class_name(Token_class_name* in)
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

void AST_visitor::visit_interface_name_list(List<Token_interface_name*>* in)
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

void AST_visitor::visit_member_list(List<AST_member*>* in)
{
    List<AST_member*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_member");
    else
    {
    	pre_list("AST_member", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_member(*i);
    	}
    
    	post_list("AST_member", in->size());
    }
}

void AST_visitor::visit_member(AST_member* in)
{
    if(in == NULL)
    	visit_null("AST_member");
    else
    {
    	pre_member_chain(in);
    	children_member(in);
    	post_member_chain(in);
    }
}

void AST_visitor::visit_interface_name(Token_interface_name* in)
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

void AST_visitor::visit_signature(AST_signature* in)
{
    if(in == NULL)
    	visit_null("AST_signature");
    else
    {
    	pre_signature_chain(in);
    	children_signature(in);
    	post_signature_chain(in);
    }
}

void AST_visitor::visit_method_mod(AST_method_mod* in)
{
    if(in == NULL)
    	visit_null("AST_method_mod");
    else
    {
    	pre_method_mod_chain(in);
    	children_method_mod(in);
    	post_method_mod_chain(in);
    }
}

void AST_visitor::visit_method_name(Token_method_name* in)
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

void AST_visitor::visit_formal_parameter_list(List<AST_formal_parameter*>* in)
{
    List<AST_formal_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_formal_parameter");
    else
    {
    	pre_list("AST_formal_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_formal_parameter(*i);
    	}
    
    	post_list("AST_formal_parameter", in->size());
    }
}

void AST_visitor::visit_formal_parameter(AST_formal_parameter* in)
{
    if(in == NULL)
    	visit_null("AST_formal_parameter");
    else
    {
    	pre_formal_parameter_chain(in);
    	children_formal_parameter(in);
    	post_formal_parameter_chain(in);
    }
}

void AST_visitor::visit_type(AST_type* in)
{
    if(in == NULL)
    	visit_null("AST_type");
    else
    {
    	pre_type_chain(in);
    	children_type(in);
    	post_type_chain(in);
    }
}

void AST_visitor::visit_variable_name(Token_variable_name* in)
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

void AST_visitor::visit_expr(AST_expr* in)
{
    if(in == NULL)
    	visit_null("AST_expr");
    else
    {
    	pre_expr_chain(in);
    	children_expr(in);
    	post_expr_chain(in);
    }
}

void AST_visitor::visit_attr_mod(AST_attr_mod* in)
{
    if(in == NULL)
    	visit_null("AST_attr_mod");
    else
    {
    	pre_attr_mod_chain(in);
    	children_attr_mod(in);
    	post_attr_mod_chain(in);
    }
}

void AST_visitor::visit_variable(AST_variable* in)
{
    if(in == NULL)
    	visit_null("AST_variable");
    else
    {
    	pre_variable_chain(in);
    	children_variable(in);
    	post_variable_chain(in);
    }
}

void AST_visitor::visit_switch_case_list(List<AST_switch_case*>* in)
{
    List<AST_switch_case*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_switch_case");
    else
    {
    	pre_list("AST_switch_case", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_switch_case(*i);
    	}
    
    	post_list("AST_switch_case", in->size());
    }
}

void AST_visitor::visit_switch_case(AST_switch_case* in)
{
    if(in == NULL)
    	visit_null("AST_switch_case");
    else
    {
    	pre_switch_case_chain(in);
    	children_switch_case(in);
    	post_switch_case_chain(in);
    }
}

void AST_visitor::visit_label_name(Token_label_name* in)
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

void AST_visitor::visit_variable_name(AST_variable_name* in)
{
    if(in == NULL)
    	visit_null("AST_variable_name");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void AST_visitor::visit_directive_list(List<AST_directive*>* in)
{
    List<AST_directive*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_directive");
    else
    {
    	pre_list("AST_directive", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_directive(*i);
    	}
    
    	post_list("AST_directive", in->size());
    }
}

void AST_visitor::visit_directive(AST_directive* in)
{
    if(in == NULL)
    	visit_null("AST_directive");
    else
    {
    	pre_directive_chain(in);
    	children_directive(in);
    	post_directive_chain(in);
    }
}

void AST_visitor::visit_directive_name(Token_directive_name* in)
{
    if(in == NULL)
    	visit_null("Token_directive_name");
    else
    {
    	pre_directive_name_chain(in);
    	children_directive_name(in);
    	post_directive_name_chain(in);
    }
}

void AST_visitor::visit_catch_list(List<AST_catch*>* in)
{
    List<AST_catch*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_catch");
    else
    {
    	pre_list("AST_catch", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_catch(*i);
    	}
    
    	post_list("AST_catch", in->size());
    }
}

void AST_visitor::visit_catch(AST_catch* in)
{
    if(in == NULL)
    	visit_null("AST_catch");
    else
    {
    	pre_catch_chain(in);
    	children_catch(in);
    	post_catch_chain(in);
    }
}

void AST_visitor::visit_list_element_list(List<AST_list_element*>* in)
{
    List<AST_list_element*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_list_element");
    else
    {
    	pre_list("AST_list_element", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_list_element(*i);
    	}
    
    	post_list("AST_list_element", in->size());
    }
}

void AST_visitor::visit_list_element(AST_list_element* in)
{
    if(in == NULL)
    	visit_null("AST_list_element");
    else
    {
    	pre_list_element_chain(in);
    	children_list_element(in);
    	post_list_element_chain(in);
    }
}

void AST_visitor::visit_cast(Token_cast* in)
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

void AST_visitor::visit_op(Token_op* in)
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

void AST_visitor::visit_constant_name(Token_constant_name* in)
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

void AST_visitor::visit_class_name(AST_class_name* in)
{
    if(in == NULL)
    	visit_null("AST_class_name");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void AST_visitor::visit_target(AST_target* in)
{
    if(in == NULL)
    	visit_null("AST_target");
    else
    {
    	pre_target_chain(in);
    	children_target(in);
    	post_target_chain(in);
    }
}

void AST_visitor::visit_expr_list(List<AST_expr*>* in)
{
    List<AST_expr*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_expr");
    else
    {
    	pre_list("AST_expr", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_expr(*i);
    	}
    
    	post_list("AST_expr", in->size());
    }
}

void AST_visitor::visit_array_elem_list(List<AST_array_elem*>* in)
{
    List<AST_array_elem*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_array_elem");
    else
    {
    	pre_list("AST_array_elem", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_array_elem(*i);
    	}
    
    	post_list("AST_array_elem", in->size());
    }
}

void AST_visitor::visit_array_elem(AST_array_elem* in)
{
    if(in == NULL)
    	visit_null("AST_array_elem");
    else
    {
    	pre_array_elem_chain(in);
    	children_array_elem(in);
    	post_array_elem_chain(in);
    }
}

void AST_visitor::visit_method_name(AST_method_name* in)
{
    if(in == NULL)
    	visit_null("AST_method_name");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void AST_visitor::visit_actual_parameter_list(List<AST_actual_parameter*>* in)
{
    List<AST_actual_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("AST_actual_parameter");
    else
    {
    	pre_list("AST_actual_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_actual_parameter(*i);
    	}
    
    	post_list("AST_actual_parameter", in->size());
    }
}

void AST_visitor::visit_actual_parameter(AST_actual_parameter* in)
{
    if(in == NULL)
    	visit_null("AST_actual_parameter");
    else
    {
    	pre_actual_parameter_chain(in);
    	children_actual_parameter(in);
    	post_actual_parameter_chain(in);
    }
}

void AST_visitor::visit_php_script(AST_php_script* in)
{
    if(in == NULL)
    	visit_null("AST_php_script");
    else
    {
    	pre_php_script_chain(in);
    	children_php_script(in);
    	post_php_script_chain(in);
    }
}

// Invoke the right pre-chain (manual dispatching)
// Do not override unless you know what you are doing
void AST_visitor::pre_statement_chain(AST_statement* in)
{
    switch(in->classid())
    {
    case AST_class_def::ID:
    	pre_class_def_chain(dynamic_cast<AST_class_def*>(in));
    	break;
    case AST_interface_def::ID:
    	pre_interface_def_chain(dynamic_cast<AST_interface_def*>(in));
    	break;
    case AST_method::ID:
    	pre_method_chain(dynamic_cast<AST_method*>(in));
    	break;
    case AST_if::ID:
    	pre_if_chain(dynamic_cast<AST_if*>(in));
    	break;
    case AST_while::ID:
    	pre_while_chain(dynamic_cast<AST_while*>(in));
    	break;
    case AST_do::ID:
    	pre_do_chain(dynamic_cast<AST_do*>(in));
    	break;
    case AST_for::ID:
    	pre_for_chain(dynamic_cast<AST_for*>(in));
    	break;
    case AST_foreach::ID:
    	pre_foreach_chain(dynamic_cast<AST_foreach*>(in));
    	break;
    case AST_switch::ID:
    	pre_switch_chain(dynamic_cast<AST_switch*>(in));
    	break;
    case AST_break::ID:
    	pre_break_chain(dynamic_cast<AST_break*>(in));
    	break;
    case AST_continue::ID:
    	pre_continue_chain(dynamic_cast<AST_continue*>(in));
    	break;
    case AST_return::ID:
    	pre_return_chain(dynamic_cast<AST_return*>(in));
    	break;
    case AST_static_declaration::ID:
    	pre_static_declaration_chain(dynamic_cast<AST_static_declaration*>(in));
    	break;
    case AST_global::ID:
    	pre_global_chain(dynamic_cast<AST_global*>(in));
    	break;
    case AST_unset::ID:
    	pre_unset_chain(dynamic_cast<AST_unset*>(in));
    	break;
    case AST_declare::ID:
    	pre_declare_chain(dynamic_cast<AST_declare*>(in));
    	break;
    case AST_try::ID:
    	pre_try_chain(dynamic_cast<AST_try*>(in));
    	break;
    case AST_throw::ID:
    	pre_throw_chain(dynamic_cast<AST_throw*>(in));
    	break;
    case AST_eval_expr::ID:
    	pre_eval_expr_chain(dynamic_cast<AST_eval_expr*>(in));
    	break;
    case AST_nop::ID:
    	pre_nop_chain(dynamic_cast<AST_nop*>(in));
    	break;
    case AST_label::ID:
    	pre_label_chain(dynamic_cast<AST_label*>(in));
    	break;
    case AST_goto::ID:
    	pre_goto_chain(dynamic_cast<AST_goto*>(in));
    	break;
    case AST_branch::ID:
    	pre_branch_chain(dynamic_cast<AST_branch*>(in));
    	break;
    }
}

void AST_visitor::pre_member_chain(AST_member* in)
{
    switch(in->classid())
    {
    case AST_method::ID:
    	pre_method_chain(dynamic_cast<AST_method*>(in));
    	break;
    case AST_attribute::ID:
    	pre_attribute_chain(dynamic_cast<AST_attribute*>(in));
    	break;
    }
}

void AST_visitor::pre_expr_chain(AST_expr* in)
{
    switch(in->classid())
    {
    case AST_assignment::ID:
    	pre_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case AST_list_assignment::ID:
    	pre_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case AST_cast::ID:
    	pre_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case AST_unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case AST_bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case AST_conditional_expr::ID:
    	pre_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case AST_ignore_errors::ID:
    	pre_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case AST_constant::ID:
    	pre_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case AST_instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case AST_variable::ID:
    	pre_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case AST_post_op::ID:
    	pre_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case AST_array::ID:
    	pre_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case AST_method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case AST_new::ID:
    	pre_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case AST_clone::ID:
    	pre_clone_chain(dynamic_cast<AST_clone*>(in));
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

void AST_visitor::pre_variable_name_chain(AST_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	pre_variable_name_chain(dynamic_cast<Token_variable_name*>(in));
    	break;
    case AST_reflection::ID:
    	pre_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::pre_list_element_chain(AST_list_element* in)
{
    switch(in->classid())
    {
    case AST_variable::ID:
    	pre_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_nested_list_elements::ID:
    	pre_nested_list_elements_chain(dynamic_cast<AST_nested_list_elements*>(in));
    	break;
    }
}

void AST_visitor::pre_class_name_chain(AST_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	pre_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    case AST_reflection::ID:
    	pre_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::pre_target_chain(AST_target* in)
{
    switch(in->classid())
    {
    case AST_assignment::ID:
    	pre_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case AST_list_assignment::ID:
    	pre_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case AST_cast::ID:
    	pre_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case AST_unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case AST_bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case AST_conditional_expr::ID:
    	pre_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case AST_ignore_errors::ID:
    	pre_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case AST_constant::ID:
    	pre_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case AST_instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case AST_variable::ID:
    	pre_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case AST_post_op::ID:
    	pre_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case AST_array::ID:
    	pre_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case AST_method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case AST_new::ID:
    	pre_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case AST_clone::ID:
    	pre_clone_chain(dynamic_cast<AST_clone*>(in));
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

void AST_visitor::pre_method_name_chain(AST_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	pre_method_name_chain(dynamic_cast<Token_method_name*>(in));
    	break;
    case AST_reflection::ID:
    	pre_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

// Invoke the right post-chain (manual dispatching)
// Do not override unless you know what you are doing
void AST_visitor::post_statement_chain(AST_statement* in)
{
    switch(in->classid())
    {
    case AST_class_def::ID:
    	post_class_def_chain(dynamic_cast<AST_class_def*>(in));
    	break;
    case AST_interface_def::ID:
    	post_interface_def_chain(dynamic_cast<AST_interface_def*>(in));
    	break;
    case AST_method::ID:
    	post_method_chain(dynamic_cast<AST_method*>(in));
    	break;
    case AST_if::ID:
    	post_if_chain(dynamic_cast<AST_if*>(in));
    	break;
    case AST_while::ID:
    	post_while_chain(dynamic_cast<AST_while*>(in));
    	break;
    case AST_do::ID:
    	post_do_chain(dynamic_cast<AST_do*>(in));
    	break;
    case AST_for::ID:
    	post_for_chain(dynamic_cast<AST_for*>(in));
    	break;
    case AST_foreach::ID:
    	post_foreach_chain(dynamic_cast<AST_foreach*>(in));
    	break;
    case AST_switch::ID:
    	post_switch_chain(dynamic_cast<AST_switch*>(in));
    	break;
    case AST_break::ID:
    	post_break_chain(dynamic_cast<AST_break*>(in));
    	break;
    case AST_continue::ID:
    	post_continue_chain(dynamic_cast<AST_continue*>(in));
    	break;
    case AST_return::ID:
    	post_return_chain(dynamic_cast<AST_return*>(in));
    	break;
    case AST_static_declaration::ID:
    	post_static_declaration_chain(dynamic_cast<AST_static_declaration*>(in));
    	break;
    case AST_global::ID:
    	post_global_chain(dynamic_cast<AST_global*>(in));
    	break;
    case AST_unset::ID:
    	post_unset_chain(dynamic_cast<AST_unset*>(in));
    	break;
    case AST_declare::ID:
    	post_declare_chain(dynamic_cast<AST_declare*>(in));
    	break;
    case AST_try::ID:
    	post_try_chain(dynamic_cast<AST_try*>(in));
    	break;
    case AST_throw::ID:
    	post_throw_chain(dynamic_cast<AST_throw*>(in));
    	break;
    case AST_eval_expr::ID:
    	post_eval_expr_chain(dynamic_cast<AST_eval_expr*>(in));
    	break;
    case AST_nop::ID:
    	post_nop_chain(dynamic_cast<AST_nop*>(in));
    	break;
    case AST_label::ID:
    	post_label_chain(dynamic_cast<AST_label*>(in));
    	break;
    case AST_goto::ID:
    	post_goto_chain(dynamic_cast<AST_goto*>(in));
    	break;
    case AST_branch::ID:
    	post_branch_chain(dynamic_cast<AST_branch*>(in));
    	break;
    }
}

void AST_visitor::post_member_chain(AST_member* in)
{
    switch(in->classid())
    {
    case AST_method::ID:
    	post_method_chain(dynamic_cast<AST_method*>(in));
    	break;
    case AST_attribute::ID:
    	post_attribute_chain(dynamic_cast<AST_attribute*>(in));
    	break;
    }
}

void AST_visitor::post_expr_chain(AST_expr* in)
{
    switch(in->classid())
    {
    case AST_assignment::ID:
    	post_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case AST_list_assignment::ID:
    	post_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case AST_cast::ID:
    	post_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case AST_unary_op::ID:
    	post_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case AST_bin_op::ID:
    	post_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case AST_conditional_expr::ID:
    	post_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case AST_ignore_errors::ID:
    	post_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case AST_constant::ID:
    	post_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case AST_instanceof::ID:
    	post_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case AST_variable::ID:
    	post_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_pre_op::ID:
    	post_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case AST_post_op::ID:
    	post_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case AST_array::ID:
    	post_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case AST_method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case AST_new::ID:
    	post_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case AST_clone::ID:
    	post_clone_chain(dynamic_cast<AST_clone*>(in));
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

void AST_visitor::post_variable_name_chain(AST_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	post_variable_name_chain(dynamic_cast<Token_variable_name*>(in));
    	break;
    case AST_reflection::ID:
    	post_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::post_list_element_chain(AST_list_element* in)
{
    switch(in->classid())
    {
    case AST_variable::ID:
    	post_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_nested_list_elements::ID:
    	post_nested_list_elements_chain(dynamic_cast<AST_nested_list_elements*>(in));
    	break;
    }
}

void AST_visitor::post_class_name_chain(AST_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	post_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    case AST_reflection::ID:
    	post_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::post_target_chain(AST_target* in)
{
    switch(in->classid())
    {
    case AST_assignment::ID:
    	post_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case AST_list_assignment::ID:
    	post_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case AST_cast::ID:
    	post_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case AST_unary_op::ID:
    	post_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case AST_bin_op::ID:
    	post_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case AST_conditional_expr::ID:
    	post_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case AST_ignore_errors::ID:
    	post_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case AST_constant::ID:
    	post_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case AST_instanceof::ID:
    	post_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case AST_variable::ID:
    	post_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_pre_op::ID:
    	post_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case AST_post_op::ID:
    	post_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case AST_array::ID:
    	post_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case AST_method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case AST_new::ID:
    	post_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case AST_clone::ID:
    	post_clone_chain(dynamic_cast<AST_clone*>(in));
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

void AST_visitor::post_method_name_chain(AST_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	post_method_name_chain(dynamic_cast<Token_method_name*>(in));
    	break;
    case AST_reflection::ID:
    	post_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

// Invoke the right visit-children (manual dispatching)
// Do not override unless you know what you are doing
void AST_visitor::children_statement(AST_statement* in)
{
    switch(in->classid())
    {
    case AST_class_def::ID:
    	children_class_def(dynamic_cast<AST_class_def*>(in));
    	break;
    case AST_interface_def::ID:
    	children_interface_def(dynamic_cast<AST_interface_def*>(in));
    	break;
    case AST_method::ID:
    	children_method(dynamic_cast<AST_method*>(in));
    	break;
    case AST_if::ID:
    	children_if(dynamic_cast<AST_if*>(in));
    	break;
    case AST_while::ID:
    	children_while(dynamic_cast<AST_while*>(in));
    	break;
    case AST_do::ID:
    	children_do(dynamic_cast<AST_do*>(in));
    	break;
    case AST_for::ID:
    	children_for(dynamic_cast<AST_for*>(in));
    	break;
    case AST_foreach::ID:
    	children_foreach(dynamic_cast<AST_foreach*>(in));
    	break;
    case AST_switch::ID:
    	children_switch(dynamic_cast<AST_switch*>(in));
    	break;
    case AST_break::ID:
    	children_break(dynamic_cast<AST_break*>(in));
    	break;
    case AST_continue::ID:
    	children_continue(dynamic_cast<AST_continue*>(in));
    	break;
    case AST_return::ID:
    	children_return(dynamic_cast<AST_return*>(in));
    	break;
    case AST_static_declaration::ID:
    	children_static_declaration(dynamic_cast<AST_static_declaration*>(in));
    	break;
    case AST_global::ID:
    	children_global(dynamic_cast<AST_global*>(in));
    	break;
    case AST_unset::ID:
    	children_unset(dynamic_cast<AST_unset*>(in));
    	break;
    case AST_declare::ID:
    	children_declare(dynamic_cast<AST_declare*>(in));
    	break;
    case AST_try::ID:
    	children_try(dynamic_cast<AST_try*>(in));
    	break;
    case AST_throw::ID:
    	children_throw(dynamic_cast<AST_throw*>(in));
    	break;
    case AST_eval_expr::ID:
    	children_eval_expr(dynamic_cast<AST_eval_expr*>(in));
    	break;
    case AST_nop::ID:
    	children_nop(dynamic_cast<AST_nop*>(in));
    	break;
    case AST_label::ID:
    	children_label(dynamic_cast<AST_label*>(in));
    	break;
    case AST_goto::ID:
    	children_goto(dynamic_cast<AST_goto*>(in));
    	break;
    case AST_branch::ID:
    	children_branch(dynamic_cast<AST_branch*>(in));
    	break;
    }
}

void AST_visitor::children_member(AST_member* in)
{
    switch(in->classid())
    {
    case AST_method::ID:
    	children_method(dynamic_cast<AST_method*>(in));
    	break;
    case AST_attribute::ID:
    	children_attribute(dynamic_cast<AST_attribute*>(in));
    	break;
    }
}

void AST_visitor::children_expr(AST_expr* in)
{
    switch(in->classid())
    {
    case AST_assignment::ID:
    	children_assignment(dynamic_cast<AST_assignment*>(in));
    	break;
    case AST_list_assignment::ID:
    	children_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case AST_cast::ID:
    	children_cast(dynamic_cast<AST_cast*>(in));
    	break;
    case AST_unary_op::ID:
    	children_unary_op(dynamic_cast<AST_unary_op*>(in));
    	break;
    case AST_bin_op::ID:
    	children_bin_op(dynamic_cast<AST_bin_op*>(in));
    	break;
    case AST_conditional_expr::ID:
    	children_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case AST_ignore_errors::ID:
    	children_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case AST_constant::ID:
    	children_constant(dynamic_cast<AST_constant*>(in));
    	break;
    case AST_instanceof::ID:
    	children_instanceof(dynamic_cast<AST_instanceof*>(in));
    	break;
    case AST_variable::ID:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_pre_op::ID:
    	children_pre_op(dynamic_cast<AST_pre_op*>(in));
    	break;
    case AST_post_op::ID:
    	children_post_op(dynamic_cast<AST_post_op*>(in));
    	break;
    case AST_array::ID:
    	children_array(dynamic_cast<AST_array*>(in));
    	break;
    case AST_method_invocation::ID:
    	children_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case AST_new::ID:
    	children_new(dynamic_cast<AST_new*>(in));
    	break;
    case AST_clone::ID:
    	children_clone(dynamic_cast<AST_clone*>(in));
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

void AST_visitor::children_variable_name(AST_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	children_variable_name(dynamic_cast<Token_variable_name*>(in));
    	break;
    case AST_reflection::ID:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::children_list_element(AST_list_element* in)
{
    switch(in->classid())
    {
    case AST_variable::ID:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_nested_list_elements::ID:
    	children_nested_list_elements(dynamic_cast<AST_nested_list_elements*>(in));
    	break;
    }
}

void AST_visitor::children_class_name(AST_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    case AST_reflection::ID:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::children_target(AST_target* in)
{
    switch(in->classid())
    {
    case AST_assignment::ID:
    	children_assignment(dynamic_cast<AST_assignment*>(in));
    	break;
    case AST_list_assignment::ID:
    	children_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case AST_cast::ID:
    	children_cast(dynamic_cast<AST_cast*>(in));
    	break;
    case AST_unary_op::ID:
    	children_unary_op(dynamic_cast<AST_unary_op*>(in));
    	break;
    case AST_bin_op::ID:
    	children_bin_op(dynamic_cast<AST_bin_op*>(in));
    	break;
    case AST_conditional_expr::ID:
    	children_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case AST_ignore_errors::ID:
    	children_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case AST_constant::ID:
    	children_constant(dynamic_cast<AST_constant*>(in));
    	break;
    case AST_instanceof::ID:
    	children_instanceof(dynamic_cast<AST_instanceof*>(in));
    	break;
    case AST_variable::ID:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case AST_pre_op::ID:
    	children_pre_op(dynamic_cast<AST_pre_op*>(in));
    	break;
    case AST_post_op::ID:
    	children_post_op(dynamic_cast<AST_post_op*>(in));
    	break;
    case AST_array::ID:
    	children_array(dynamic_cast<AST_array*>(in));
    	break;
    case AST_method_invocation::ID:
    	children_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case AST_new::ID:
    	children_new(dynamic_cast<AST_new*>(in));
    	break;
    case AST_clone::ID:
    	children_clone(dynamic_cast<AST_clone*>(in));
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

void AST_visitor::children_method_name(AST_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	children_method_name(dynamic_cast<Token_method_name*>(in));
    	break;
    case AST_reflection::ID:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

