#include "AST_visitor.h"

AST_visitor::~AST_visitor()
{
}

void AST_visitor::pre_php_script(AST_php_script* in)
{
}

void AST_visitor::pre_interface_def(AST_interface_def* in)
{
}

void AST_visitor::pre_class_def(AST_class_def* in)
{
}

void AST_visitor::pre_class_mod(AST_class_mod* in)
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

void AST_visitor::pre_statement(AST_statement* in)
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

void AST_visitor::pre_static_declaration(AST_static_declaration* in)
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

void AST_visitor::pre_list_elements(AST_list_elements* in)
{
}

void AST_visitor::pre_list_element(AST_list_element* in)
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

void AST_visitor::pre_node(AST_node* in)
{
}

void AST_visitor::pre_commented_node(AST_commented_node* in)
{
}

void AST_visitor::pre_identifier(AST_identifier* in)
{
}

void AST_visitor::pre_interface_name(Token_interface_name* in)
{
}

void AST_visitor::pre_class_name(Token_class_name* in)
{
}

void AST_visitor::pre_method_name(Token_method_name* in)
{
}

void AST_visitor::pre_variable_name(Token_variable_name* in)
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

void AST_visitor::post_php_script(AST_php_script* in)
{
}

void AST_visitor::post_interface_def(AST_interface_def* in)
{
}

void AST_visitor::post_class_def(AST_class_def* in)
{
}

void AST_visitor::post_class_mod(AST_class_mod* in)
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

void AST_visitor::post_statement(AST_statement* in)
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

void AST_visitor::post_static_declaration(AST_static_declaration* in)
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

void AST_visitor::post_list_elements(AST_list_elements* in)
{
}

void AST_visitor::post_list_element(AST_list_element* in)
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

void AST_visitor::post_node(AST_node* in)
{
}

void AST_visitor::post_commented_node(AST_commented_node* in)
{
}

void AST_visitor::post_identifier(AST_identifier* in)
{
}

void AST_visitor::post_interface_name(Token_interface_name* in)
{
}

void AST_visitor::post_class_name(Token_class_name* in)
{
}

void AST_visitor::post_method_name(Token_method_name* in)
{
}

void AST_visitor::post_variable_name(Token_variable_name* in)
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

void AST_visitor::children_php_script(AST_php_script* in)
{
    visit_interface_def_list(in->interface_defs);
    visit_class_def_list(in->class_defs);
}

void AST_visitor::children_interface_def(AST_interface_def* in)
{
    visit_interface_name(in->interface_name);
    visit_interface_name_list(in->extends);
    visit_member_list(in->members);
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
    visit_marker("is_array", in->is_array);
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

void AST_visitor::children_static_declaration(AST_static_declaration* in)
{
    visit_variable_name(in->variable_name);
    visit_expr(in->expr);
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
    visit_list_elements(in->list_elements);
    visit_expr(in->expr);
}

void AST_visitor::children_list_elements(AST_list_elements* in)
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
    visit_expr(in->string_index);
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

void AST_visitor::children_interface_name(Token_interface_name* in)
{
}

void AST_visitor::children_class_name(Token_class_name* in)
{
}

void AST_visitor::children_method_name(Token_method_name* in)
{
}

void AST_visitor::children_variable_name(Token_variable_name* in)
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

void AST_visitor::pre_php_script_chain(AST_php_script* in)
{
    pre_node(in);
    pre_php_script(in);
}

void AST_visitor::pre_interface_def_chain(AST_interface_def* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_interface_def(in);
}

void AST_visitor::pre_class_def_chain(AST_class_def* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_class_def(in);
}

void AST_visitor::pre_class_mod_chain(AST_class_mod* in)
{
    pre_node(in);
    pre_class_mod(in);
}

void AST_visitor::pre_method_chain(AST_method* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_member(in);
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

void AST_visitor::pre_static_declaration_chain(AST_static_declaration* in)
{
    pre_node(in);
    pre_commented_node(in);
    pre_statement(in);
    pre_static_declaration(in);
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

void AST_visitor::pre_list_elements_chain(AST_list_elements* in)
{
    pre_node(in);
    pre_list_element(in);
    pre_list_elements(in);
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
    pre_target(in);
    pre_list_element(in);
    pre_expr(in);
    pre_variable(in);
}

void AST_visitor::pre_reflection_chain(AST_reflection* in)
{
    pre_node(in);
    pre_class_name(in);
    pre_method_name(in);
    pre_variable_name(in);
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

void AST_visitor::pre_interface_name_chain(Token_interface_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_interface_name(in);
}

void AST_visitor::pre_class_name_chain(Token_class_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_class_name(in);
    pre_target(in);
    pre_class_name(in);
}

void AST_visitor::pre_method_name_chain(Token_method_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_method_name(in);
    pre_method_name(in);
}

void AST_visitor::pre_variable_name_chain(Token_variable_name* in)
{
    pre_node(in);
    pre_identifier(in);
    pre_variable_name(in);
    pre_variable_name(in);
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

void AST_visitor::post_php_script_chain(AST_php_script* in)
{
    post_php_script(in);
    post_node(in);
}

void AST_visitor::post_interface_def_chain(AST_interface_def* in)
{
    post_interface_def(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_class_def_chain(AST_class_def* in)
{
    post_class_def(in);
    post_commented_node(in);
    post_node(in);
}

void AST_visitor::post_class_mod_chain(AST_class_mod* in)
{
    post_class_mod(in);
    post_node(in);
}

void AST_visitor::post_method_chain(AST_method* in)
{
    post_method(in);
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

void AST_visitor::post_static_declaration_chain(AST_static_declaration* in)
{
    post_static_declaration(in);
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

void AST_visitor::post_list_elements_chain(AST_list_elements* in)
{
    post_list_elements(in);
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
    post_list_element(in);
    post_target(in);
    post_node(in);
}

void AST_visitor::post_reflection_chain(AST_reflection* in)
{
    post_reflection(in);
    post_variable_name(in);
    post_method_name(in);
    post_class_name(in);
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

void AST_visitor::post_interface_name_chain(Token_interface_name* in)
{
    post_interface_name(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_class_name_chain(Token_class_name* in)
{
    post_class_name(in);
    post_target(in);
    post_class_name(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_method_name_chain(Token_method_name* in)
{
    post_method_name(in);
    post_method_name(in);
    post_identifier(in);
    post_node(in);
}

void AST_visitor::post_variable_name_chain(Token_variable_name* in)
{
    post_variable_name(in);
    post_variable_name(in);
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

void AST_visitor::visit_interface_def_list(List<AST_interface_def*>* in)
{
    List<AST_interface_def*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_interface_def*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_interface_def(*i);
    }
}

void AST_visitor::visit_interface_def(AST_interface_def* in)
{
    if(in == NULL)
    	visit_null("List<AST_interface_def*>");
    else
    {
    	pre_interface_def_chain(in);
    	children_interface_def(in);
    	post_interface_def_chain(in);
    }
}

void AST_visitor::visit_class_def_list(List<AST_class_def*>* in)
{
    List<AST_class_def*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_class_def*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_class_def(*i);
    }
}

void AST_visitor::visit_class_def(AST_class_def* in)
{
    if(in == NULL)
    	visit_null("List<AST_class_def*>");
    else
    {
    	pre_class_def_chain(in);
    	children_class_def(in);
    	post_class_def_chain(in);
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

void AST_visitor::visit_interface_name_list(List<Token_interface_name*>* in)
{
    List<Token_interface_name*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<Token_interface_name*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_interface_name(*i);
    }
}

void AST_visitor::visit_member_list(List<AST_member*>* in)
{
    List<AST_member*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_member*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_member(*i);
    }
}

void AST_visitor::visit_member(AST_member* in)
{
    if(in == NULL)
    	visit_null("List<AST_member*>");
    else
    {
    	pre_member_chain(in);
    	children_member(in);
    	post_member_chain(in);
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

void AST_visitor::visit_statement_list(List<AST_statement*>* in)
{
    List<AST_statement*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_statement*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_statement(*i);
    }
}

void AST_visitor::visit_statement(AST_statement* in)
{
    if(in == NULL)
    	visit_null("List<AST_statement*>");
    else
    {
    	pre_statement_chain(in);
    	children_statement(in);
    	post_statement_chain(in);
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
    	visit_null("List<AST_formal_parameter*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_formal_parameter(*i);
    }
}

void AST_visitor::visit_formal_parameter(AST_formal_parameter* in)
{
    if(in == NULL)
    	visit_null("List<AST_formal_parameter*>");
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
    	visit_null("List<AST_switch_case*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_switch_case(*i);
    }
}

void AST_visitor::visit_switch_case(AST_switch_case* in)
{
    if(in == NULL)
    	visit_null("List<AST_switch_case*>");
    else
    {
    	pre_switch_case_chain(in);
    	children_switch_case(in);
    	post_switch_case_chain(in);
    }
}

void AST_visitor::visit_directive_list(List<AST_directive*>* in)
{
    List<AST_directive*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_directive*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_directive(*i);
    }
}

void AST_visitor::visit_directive(AST_directive* in)
{
    if(in == NULL)
    	visit_null("List<AST_directive*>");
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
    	visit_null("List<AST_catch*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_catch(*i);
    }
}

void AST_visitor::visit_catch(AST_catch* in)
{
    if(in == NULL)
    	visit_null("List<AST_catch*>");
    else
    {
    	pre_catch_chain(in);
    	children_catch(in);
    	post_catch_chain(in);
    }
}

void AST_visitor::visit_list_elements(AST_list_elements* in)
{
    if(in == NULL)
    	visit_null("AST_list_elements");
    else
    {
    	pre_list_elements_chain(in);
    	children_list_elements(in);
    	post_list_elements_chain(in);
    }
}

void AST_visitor::visit_list_element_list(List<AST_list_element*>* in)
{
    List<AST_list_element*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_list_element*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_list_element(*i);
    }
}

void AST_visitor::visit_list_element(AST_list_element* in)
{
    if(in == NULL)
    	visit_null("List<AST_list_element*>");
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

void AST_visitor::visit_expr_list(List<AST_expr*>* in)
{
    List<AST_expr*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_expr*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_expr(*i);
    }
}

void AST_visitor::visit_array_elem_list(List<AST_array_elem*>* in)
{
    List<AST_array_elem*>::const_iterator i;
    
    if(in == NULL)
    	visit_null("List<AST_array_elem*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_array_elem(*i);
    }
}

void AST_visitor::visit_array_elem(AST_array_elem* in)
{
    if(in == NULL)
    	visit_null("List<AST_array_elem*>");
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
    	visit_null("List<AST_actual_parameter*>");
    else for(i = in->begin(); i != in->end(); i++)
    {
    	visit_actual_parameter(*i);
    }
}

void AST_visitor::visit_actual_parameter(AST_actual_parameter* in)
{
    if(in == NULL)
    	visit_null("List<AST_actual_parameter*>");
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

void AST_visitor::visit_null(char const* name)
{
}

void AST_visitor::visit_marker(char const* name, bool value)
{
}

void AST_visitor::pre_member_chain(AST_member* in)
{
    switch(in->classid())
    {
    case 5:
    	pre_method_chain(dynamic_cast<AST_method*>(in));
    	break;
    case 10:
    	pre_attribute_chain(dynamic_cast<AST_attribute*>(in));
    	break;
    }
}

void AST_visitor::pre_statement_chain(AST_statement* in)
{
    switch(in->classid())
    {
    case 12:
    	pre_if_chain(dynamic_cast<AST_if*>(in));
    	break;
    case 13:
    	pre_while_chain(dynamic_cast<AST_while*>(in));
    	break;
    case 14:
    	pre_do_chain(dynamic_cast<AST_do*>(in));
    	break;
    case 15:
    	pre_for_chain(dynamic_cast<AST_for*>(in));
    	break;
    case 16:
    	pre_foreach_chain(dynamic_cast<AST_foreach*>(in));
    	break;
    case 17:
    	pre_switch_chain(dynamic_cast<AST_switch*>(in));
    	break;
    case 19:
    	pre_break_chain(dynamic_cast<AST_break*>(in));
    	break;
    case 20:
    	pre_continue_chain(dynamic_cast<AST_continue*>(in));
    	break;
    case 21:
    	pre_return_chain(dynamic_cast<AST_return*>(in));
    	break;
    case 22:
    	pre_static_declaration_chain(dynamic_cast<AST_static_declaration*>(in));
    	break;
    case 23:
    	pre_unset_chain(dynamic_cast<AST_unset*>(in));
    	break;
    case 24:
    	pre_declare_chain(dynamic_cast<AST_declare*>(in));
    	break;
    case 26:
    	pre_try_chain(dynamic_cast<AST_try*>(in));
    	break;
    case 28:
    	pre_throw_chain(dynamic_cast<AST_throw*>(in));
    	break;
    case 29:
    	pre_eval_expr_chain(dynamic_cast<AST_eval_expr*>(in));
    	break;
    case 30:
    	pre_nop_chain(dynamic_cast<AST_nop*>(in));
    	break;
    }
}

void AST_visitor::pre_expr_chain(AST_expr* in)
{
    switch(in->classid())
    {
    case 31:
    	pre_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case 32:
    	pre_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 34:
    	pre_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case 35:
    	pre_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 36:
    	pre_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 37:
    	pre_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 38:
    	pre_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 39:
    	pre_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case 40:
    	pre_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 41:
    	pre_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case 43:
    	pre_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 44:
    	pre_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case 45:
    	pre_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case 47:
    	pre_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 49:
    	pre_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case 50:
    	pre_clone_chain(dynamic_cast<AST_clone*>(in));
    	break;
    case 56:
    	pre_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case 57:
    	pre_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case 58:
    	pre_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case 59:
    	pre_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case 60:
    	pre_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void AST_visitor::pre_list_element_chain(AST_list_element* in)
{
    switch(in->classid())
    {
    case 41:
    	pre_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case 33:
    	pre_list_elements_chain(dynamic_cast<AST_list_elements*>(in));
    	break;
    }
}

void AST_visitor::pre_class_name_chain(AST_class_name* in)
{
    switch(in->classid())
    {
    case 52:
    	pre_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    case 42:
    	pre_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::pre_target_chain(AST_target* in)
{
    switch(in->classid())
    {
    case 31:
    	pre_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case 32:
    	pre_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 34:
    	pre_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case 35:
    	pre_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 36:
    	pre_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 37:
    	pre_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 38:
    	pre_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 39:
    	pre_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case 40:
    	pre_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 41:
    	pre_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case 43:
    	pre_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 44:
    	pre_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case 45:
    	pre_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case 47:
    	pre_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 49:
    	pre_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case 50:
    	pre_clone_chain(dynamic_cast<AST_clone*>(in));
    	break;
    case 56:
    	pre_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case 57:
    	pre_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case 58:
    	pre_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case 59:
    	pre_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case 60:
    	pre_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    case 52:
    	pre_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void AST_visitor::pre_variable_name_chain(AST_variable_name* in)
{
    switch(in->classid())
    {
    case 54:
    	pre_variable_name_chain(dynamic_cast<Token_variable_name*>(in));
    	break;
    case 42:
    	pre_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::pre_method_name_chain(AST_method_name* in)
{
    switch(in->classid())
    {
    case 53:
    	pre_method_name_chain(dynamic_cast<Token_method_name*>(in));
    	break;
    case 42:
    	pre_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::post_member_chain(AST_member* in)
{
    switch(in->classid())
    {
    case 5:
    	post_method_chain(dynamic_cast<AST_method*>(in));
    	break;
    case 10:
    	post_attribute_chain(dynamic_cast<AST_attribute*>(in));
    	break;
    }
}

void AST_visitor::post_statement_chain(AST_statement* in)
{
    switch(in->classid())
    {
    case 12:
    	post_if_chain(dynamic_cast<AST_if*>(in));
    	break;
    case 13:
    	post_while_chain(dynamic_cast<AST_while*>(in));
    	break;
    case 14:
    	post_do_chain(dynamic_cast<AST_do*>(in));
    	break;
    case 15:
    	post_for_chain(dynamic_cast<AST_for*>(in));
    	break;
    case 16:
    	post_foreach_chain(dynamic_cast<AST_foreach*>(in));
    	break;
    case 17:
    	post_switch_chain(dynamic_cast<AST_switch*>(in));
    	break;
    case 19:
    	post_break_chain(dynamic_cast<AST_break*>(in));
    	break;
    case 20:
    	post_continue_chain(dynamic_cast<AST_continue*>(in));
    	break;
    case 21:
    	post_return_chain(dynamic_cast<AST_return*>(in));
    	break;
    case 22:
    	post_static_declaration_chain(dynamic_cast<AST_static_declaration*>(in));
    	break;
    case 23:
    	post_unset_chain(dynamic_cast<AST_unset*>(in));
    	break;
    case 24:
    	post_declare_chain(dynamic_cast<AST_declare*>(in));
    	break;
    case 26:
    	post_try_chain(dynamic_cast<AST_try*>(in));
    	break;
    case 28:
    	post_throw_chain(dynamic_cast<AST_throw*>(in));
    	break;
    case 29:
    	post_eval_expr_chain(dynamic_cast<AST_eval_expr*>(in));
    	break;
    case 30:
    	post_nop_chain(dynamic_cast<AST_nop*>(in));
    	break;
    }
}

void AST_visitor::post_expr_chain(AST_expr* in)
{
    switch(in->classid())
    {
    case 31:
    	post_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case 32:
    	post_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 34:
    	post_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case 35:
    	post_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 36:
    	post_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 37:
    	post_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 38:
    	post_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 39:
    	post_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case 40:
    	post_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 41:
    	post_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case 43:
    	post_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 44:
    	post_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case 45:
    	post_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case 47:
    	post_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 49:
    	post_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case 50:
    	post_clone_chain(dynamic_cast<AST_clone*>(in));
    	break;
    case 56:
    	post_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case 57:
    	post_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case 58:
    	post_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case 59:
    	post_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case 60:
    	post_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void AST_visitor::post_list_element_chain(AST_list_element* in)
{
    switch(in->classid())
    {
    case 41:
    	post_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case 33:
    	post_list_elements_chain(dynamic_cast<AST_list_elements*>(in));
    	break;
    }
}

void AST_visitor::post_class_name_chain(AST_class_name* in)
{
    switch(in->classid())
    {
    case 52:
    	post_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    case 42:
    	post_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::post_target_chain(AST_target* in)
{
    switch(in->classid())
    {
    case 31:
    	post_assignment_chain(dynamic_cast<AST_assignment*>(in));
    	break;
    case 32:
    	post_list_assignment_chain(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 34:
    	post_cast_chain(dynamic_cast<AST_cast*>(in));
    	break;
    case 35:
    	post_unary_op_chain(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 36:
    	post_bin_op_chain(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 37:
    	post_conditional_expr_chain(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 38:
    	post_ignore_errors_chain(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 39:
    	post_constant_chain(dynamic_cast<AST_constant*>(in));
    	break;
    case 40:
    	post_instanceof_chain(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 41:
    	post_variable_chain(dynamic_cast<AST_variable*>(in));
    	break;
    case 43:
    	post_pre_op_chain(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 44:
    	post_post_op_chain(dynamic_cast<AST_post_op*>(in));
    	break;
    case 45:
    	post_array_chain(dynamic_cast<AST_array*>(in));
    	break;
    case 47:
    	post_method_invocation_chain(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 49:
    	post_new_chain(dynamic_cast<AST_new*>(in));
    	break;
    case 50:
    	post_clone_chain(dynamic_cast<AST_clone*>(in));
    	break;
    case 56:
    	post_int_chain(dynamic_cast<Token_int*>(in));
    	break;
    case 57:
    	post_real_chain(dynamic_cast<Token_real*>(in));
    	break;
    case 58:
    	post_string_chain(dynamic_cast<Token_string*>(in));
    	break;
    case 59:
    	post_bool_chain(dynamic_cast<Token_bool*>(in));
    	break;
    case 60:
    	post_null_chain(dynamic_cast<Token_null*>(in));
    	break;
    case 52:
    	post_class_name_chain(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void AST_visitor::post_variable_name_chain(AST_variable_name* in)
{
    switch(in->classid())
    {
    case 54:
    	post_variable_name_chain(dynamic_cast<Token_variable_name*>(in));
    	break;
    case 42:
    	post_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::post_method_name_chain(AST_method_name* in)
{
    switch(in->classid())
    {
    case 53:
    	post_method_name_chain(dynamic_cast<Token_method_name*>(in));
    	break;
    case 42:
    	post_reflection_chain(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::children_member(AST_member* in)
{
    switch(in->classid())
    {
    case 5:
    	children_method(dynamic_cast<AST_method*>(in));
    	break;
    case 10:
    	children_attribute(dynamic_cast<AST_attribute*>(in));
    	break;
    }
}

void AST_visitor::children_statement(AST_statement* in)
{
    switch(in->classid())
    {
    case 12:
    	children_if(dynamic_cast<AST_if*>(in));
    	break;
    case 13:
    	children_while(dynamic_cast<AST_while*>(in));
    	break;
    case 14:
    	children_do(dynamic_cast<AST_do*>(in));
    	break;
    case 15:
    	children_for(dynamic_cast<AST_for*>(in));
    	break;
    case 16:
    	children_foreach(dynamic_cast<AST_foreach*>(in));
    	break;
    case 17:
    	children_switch(dynamic_cast<AST_switch*>(in));
    	break;
    case 19:
    	children_break(dynamic_cast<AST_break*>(in));
    	break;
    case 20:
    	children_continue(dynamic_cast<AST_continue*>(in));
    	break;
    case 21:
    	children_return(dynamic_cast<AST_return*>(in));
    	break;
    case 22:
    	children_static_declaration(dynamic_cast<AST_static_declaration*>(in));
    	break;
    case 23:
    	children_unset(dynamic_cast<AST_unset*>(in));
    	break;
    case 24:
    	children_declare(dynamic_cast<AST_declare*>(in));
    	break;
    case 26:
    	children_try(dynamic_cast<AST_try*>(in));
    	break;
    case 28:
    	children_throw(dynamic_cast<AST_throw*>(in));
    	break;
    case 29:
    	children_eval_expr(dynamic_cast<AST_eval_expr*>(in));
    	break;
    case 30:
    	children_nop(dynamic_cast<AST_nop*>(in));
    	break;
    }
}

void AST_visitor::children_expr(AST_expr* in)
{
    switch(in->classid())
    {
    case 31:
    	children_assignment(dynamic_cast<AST_assignment*>(in));
    	break;
    case 32:
    	children_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 34:
    	children_cast(dynamic_cast<AST_cast*>(in));
    	break;
    case 35:
    	children_unary_op(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 36:
    	children_bin_op(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 37:
    	children_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 38:
    	children_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 39:
    	children_constant(dynamic_cast<AST_constant*>(in));
    	break;
    case 40:
    	children_instanceof(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 41:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case 43:
    	children_pre_op(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 44:
    	children_post_op(dynamic_cast<AST_post_op*>(in));
    	break;
    case 45:
    	children_array(dynamic_cast<AST_array*>(in));
    	break;
    case 47:
    	children_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 49:
    	children_new(dynamic_cast<AST_new*>(in));
    	break;
    case 50:
    	children_clone(dynamic_cast<AST_clone*>(in));
    	break;
    case 56:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case 57:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case 58:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case 59:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case 60:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void AST_visitor::children_list_element(AST_list_element* in)
{
    switch(in->classid())
    {
    case 41:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case 33:
    	children_list_elements(dynamic_cast<AST_list_elements*>(in));
    	break;
    }
}

void AST_visitor::children_class_name(AST_class_name* in)
{
    switch(in->classid())
    {
    case 52:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    case 42:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::children_target(AST_target* in)
{
    switch(in->classid())
    {
    case 31:
    	children_assignment(dynamic_cast<AST_assignment*>(in));
    	break;
    case 32:
    	children_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 34:
    	children_cast(dynamic_cast<AST_cast*>(in));
    	break;
    case 35:
    	children_unary_op(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 36:
    	children_bin_op(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 37:
    	children_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 38:
    	children_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 39:
    	children_constant(dynamic_cast<AST_constant*>(in));
    	break;
    case 40:
    	children_instanceof(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 41:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case 43:
    	children_pre_op(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 44:
    	children_post_op(dynamic_cast<AST_post_op*>(in));
    	break;
    case 45:
    	children_array(dynamic_cast<AST_array*>(in));
    	break;
    case 47:
    	children_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 49:
    	children_new(dynamic_cast<AST_new*>(in));
    	break;
    case 50:
    	children_clone(dynamic_cast<AST_clone*>(in));
    	break;
    case 56:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case 57:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case 58:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case 59:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case 60:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    case 52:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void AST_visitor::children_variable_name(AST_variable_name* in)
{
    switch(in->classid())
    {
    case 54:
    	children_variable_name(dynamic_cast<Token_variable_name*>(in));
    	break;
    case 42:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_visitor::children_method_name(AST_method_name* in)
{
    switch(in->classid())
    {
    case 53:
    	children_method_name(dynamic_cast<Token_method_name*>(in));
    	break;
    case 42:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

