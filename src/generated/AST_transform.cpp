#include "AST_transform.h"

AST_transform::~AST_transform()
{
}

// The pre-transform gets called before the children of the node are transformed
AST_php_script* AST_transform::pre_php_script(AST_php_script* in)
{
    return in;
}

void AST_transform::pre_class_def(AST_class_def* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

AST_class_mod* AST_transform::pre_class_mod(AST_class_mod* in)
{
    return in;
}

void AST_transform::pre_interface_def(AST_interface_def* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_method(AST_method* in, List<AST_method*>* out)
{
    out->push_back(in);
}

AST_signature* AST_transform::pre_signature(AST_signature* in)
{
    return in;
}

AST_method_mod* AST_transform::pre_method_mod(AST_method_mod* in)
{
    return in;
}

void AST_transform::pre_formal_parameter(AST_formal_parameter* in, List<AST_formal_parameter*>* out)
{
    out->push_back(in);
}

AST_type* AST_transform::pre_type(AST_type* in)
{
    return in;
}

void AST_transform::pre_attribute(AST_attribute* in, List<AST_member*>* out)
{
    out->push_back(in);
}

AST_attr_mod* AST_transform::pre_attr_mod(AST_attr_mod* in)
{
    return in;
}

void AST_transform::pre_if(AST_if* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_while(AST_while* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_do(AST_do* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_for(AST_for* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_foreach(AST_foreach* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_switch(AST_switch* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_switch_case(AST_switch_case* in, List<AST_switch_case*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_break(AST_break* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_continue(AST_continue* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_return(AST_return* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_static_declaration(AST_static_declaration* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_unset(AST_unset* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_declare(AST_declare* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_directive(AST_directive* in, List<AST_directive*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_try(AST_try* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_catch(AST_catch* in, List<AST_catch*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_throw(AST_throw* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_nop(AST_nop* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_goto(AST_goto* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::pre_label(AST_label* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

AST_expr* AST_transform::pre_assignment(AST_assignment* in)
{
    return in;
}

AST_expr* AST_transform::pre_list_assignment(AST_list_assignment* in)
{
    return in;
}

AST_list_elements* AST_transform::pre_list_elements(AST_list_elements* in)
{
    return in;
}

AST_expr* AST_transform::pre_cast(AST_cast* in)
{
    return in;
}

AST_expr* AST_transform::pre_unary_op(AST_unary_op* in)
{
    return in;
}

AST_expr* AST_transform::pre_bin_op(AST_bin_op* in)
{
    return in;
}

AST_expr* AST_transform::pre_conditional_expr(AST_conditional_expr* in)
{
    return in;
}

AST_expr* AST_transform::pre_ignore_errors(AST_ignore_errors* in)
{
    return in;
}

AST_expr* AST_transform::pre_constant(AST_constant* in)
{
    return in;
}

AST_expr* AST_transform::pre_instanceof(AST_instanceof* in)
{
    return in;
}

AST_variable* AST_transform::pre_variable(AST_variable* in)
{
    return in;
}

AST_reflection* AST_transform::pre_reflection(AST_reflection* in)
{
    return in;
}

AST_expr* AST_transform::pre_pre_op(AST_pre_op* in)
{
    return in;
}

AST_expr* AST_transform::pre_post_op(AST_post_op* in)
{
    return in;
}

AST_expr* AST_transform::pre_array(AST_array* in)
{
    return in;
}

void AST_transform::pre_array_elem(AST_array_elem* in, List<AST_array_elem*>* out)
{
    out->push_back(in);
}

AST_expr* AST_transform::pre_method_invocation(AST_method_invocation* in)
{
    return in;
}

void AST_transform::pre_actual_parameter(AST_actual_parameter* in, List<AST_actual_parameter*>* out)
{
    out->push_back(in);
}

AST_expr* AST_transform::pre_new(AST_new* in)
{
    return in;
}

AST_expr* AST_transform::pre_clone(AST_clone* in)
{
    return in;
}

Token_class_name* AST_transform::pre_class_name(Token_class_name* in)
{
    return in;
}

Token_interface_name* AST_transform::pre_interface_name(Token_interface_name* in)
{
    return in;
}

Token_method_name* AST_transform::pre_method_name(Token_method_name* in)
{
    return in;
}

Token_variable_name* AST_transform::pre_variable_name(Token_variable_name* in)
{
    return in;
}

Token_directive_name* AST_transform::pre_directive_name(Token_directive_name* in)
{
    return in;
}

Token_label_name* AST_transform::pre_label_name(Token_label_name* in)
{
    return in;
}

AST_expr* AST_transform::pre_int(Token_int* in)
{
    return in;
}

AST_expr* AST_transform::pre_real(Token_real* in)
{
    return in;
}

AST_expr* AST_transform::pre_string(Token_string* in)
{
    return in;
}

AST_expr* AST_transform::pre_bool(Token_bool* in)
{
    return in;
}

AST_expr* AST_transform::pre_null(Token_null* in)
{
    return in;
}

Token_cast* AST_transform::pre_cast(Token_cast* in)
{
    return in;
}

Token_op* AST_transform::pre_op(Token_op* in)
{
    return in;
}

Token_constant_name* AST_transform::pre_constant_name(Token_constant_name* in)
{
    return in;
}

// The post-transform gets called after the children of the node have been transformed
AST_php_script* AST_transform::post_php_script(AST_php_script* in)
{
    return in;
}

void AST_transform::post_class_def(AST_class_def* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

AST_class_mod* AST_transform::post_class_mod(AST_class_mod* in)
{
    return in;
}

void AST_transform::post_interface_def(AST_interface_def* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_method(AST_method* in, List<AST_method*>* out)
{
    out->push_back(in);
}

AST_signature* AST_transform::post_signature(AST_signature* in)
{
    return in;
}

AST_method_mod* AST_transform::post_method_mod(AST_method_mod* in)
{
    return in;
}

void AST_transform::post_formal_parameter(AST_formal_parameter* in, List<AST_formal_parameter*>* out)
{
    out->push_back(in);
}

AST_type* AST_transform::post_type(AST_type* in)
{
    return in;
}

void AST_transform::post_attribute(AST_attribute* in, List<AST_member*>* out)
{
    out->push_back(in);
}

AST_attr_mod* AST_transform::post_attr_mod(AST_attr_mod* in)
{
    return in;
}

void AST_transform::post_if(AST_if* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_while(AST_while* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_do(AST_do* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_for(AST_for* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_foreach(AST_foreach* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_switch(AST_switch* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_switch_case(AST_switch_case* in, List<AST_switch_case*>* out)
{
    out->push_back(in);
}

void AST_transform::post_break(AST_break* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_continue(AST_continue* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_return(AST_return* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_static_declaration(AST_static_declaration* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_unset(AST_unset* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_declare(AST_declare* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_directive(AST_directive* in, List<AST_directive*>* out)
{
    out->push_back(in);
}

void AST_transform::post_try(AST_try* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_catch(AST_catch* in, List<AST_catch*>* out)
{
    out->push_back(in);
}

void AST_transform::post_throw(AST_throw* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_nop(AST_nop* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_goto(AST_goto* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

void AST_transform::post_label(AST_label* in, List<AST_statement*>* out)
{
    out->push_back(in);
}

AST_expr* AST_transform::post_assignment(AST_assignment* in)
{
    return in;
}

AST_expr* AST_transform::post_list_assignment(AST_list_assignment* in)
{
    return in;
}

AST_list_elements* AST_transform::post_list_elements(AST_list_elements* in)
{
    return in;
}

AST_expr* AST_transform::post_cast(AST_cast* in)
{
    return in;
}

AST_expr* AST_transform::post_unary_op(AST_unary_op* in)
{
    return in;
}

AST_expr* AST_transform::post_bin_op(AST_bin_op* in)
{
    return in;
}

AST_expr* AST_transform::post_conditional_expr(AST_conditional_expr* in)
{
    return in;
}

AST_expr* AST_transform::post_ignore_errors(AST_ignore_errors* in)
{
    return in;
}

AST_expr* AST_transform::post_constant(AST_constant* in)
{
    return in;
}

AST_expr* AST_transform::post_instanceof(AST_instanceof* in)
{
    return in;
}

AST_variable* AST_transform::post_variable(AST_variable* in)
{
    return in;
}

AST_reflection* AST_transform::post_reflection(AST_reflection* in)
{
    return in;
}

AST_expr* AST_transform::post_pre_op(AST_pre_op* in)
{
    return in;
}

AST_expr* AST_transform::post_post_op(AST_post_op* in)
{
    return in;
}

AST_expr* AST_transform::post_array(AST_array* in)
{
    return in;
}

void AST_transform::post_array_elem(AST_array_elem* in, List<AST_array_elem*>* out)
{
    out->push_back(in);
}

AST_expr* AST_transform::post_method_invocation(AST_method_invocation* in)
{
    return in;
}

void AST_transform::post_actual_parameter(AST_actual_parameter* in, List<AST_actual_parameter*>* out)
{
    out->push_back(in);
}

AST_expr* AST_transform::post_new(AST_new* in)
{
    return in;
}

AST_expr* AST_transform::post_clone(AST_clone* in)
{
    return in;
}

Token_class_name* AST_transform::post_class_name(Token_class_name* in)
{
    return in;
}

Token_interface_name* AST_transform::post_interface_name(Token_interface_name* in)
{
    return in;
}

Token_method_name* AST_transform::post_method_name(Token_method_name* in)
{
    return in;
}

Token_variable_name* AST_transform::post_variable_name(Token_variable_name* in)
{
    return in;
}

Token_directive_name* AST_transform::post_directive_name(Token_directive_name* in)
{
    return in;
}

Token_label_name* AST_transform::post_label_name(Token_label_name* in)
{
    return in;
}

AST_expr* AST_transform::post_int(Token_int* in)
{
    return in;
}

AST_expr* AST_transform::post_real(Token_real* in)
{
    return in;
}

AST_expr* AST_transform::post_string(Token_string* in)
{
    return in;
}

AST_expr* AST_transform::post_bool(Token_bool* in)
{
    return in;
}

AST_expr* AST_transform::post_null(Token_null* in)
{
    return in;
}

Token_cast* AST_transform::post_cast(Token_cast* in)
{
    return in;
}

Token_op* AST_transform::post_op(Token_op* in)
{
    return in;
}

Token_constant_name* AST_transform::post_constant_name(Token_constant_name* in)
{
    return in;
}

// Transform the children of the node
void AST_transform::children_php_script(AST_php_script* in)
{
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_class_def(AST_class_def* in)
{
    in->class_mod = transform_class_mod(in->class_mod);
    in->class_name = transform_class_name(in->class_name);
    in->extends = transform_class_name(in->extends);
    in->implements = transform_interface_name_list(in->implements);
    in->members = transform_member_list(in->members);
}

void AST_transform::children_class_mod(AST_class_mod* in)
{
}

void AST_transform::children_interface_def(AST_interface_def* in)
{
    in->interface_name = transform_interface_name(in->interface_name);
    in->extends = transform_interface_name_list(in->extends);
    in->members = transform_member_list(in->members);
}

void AST_transform::children_method(AST_method* in)
{
    in->signature = transform_signature(in->signature);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_signature(AST_signature* in)
{
    in->method_mod = transform_method_mod(in->method_mod);
    in->method_name = transform_method_name(in->method_name);
    in->formal_parameters = transform_formal_parameter_list(in->formal_parameters);
}

void AST_transform::children_method_mod(AST_method_mod* in)
{
}

void AST_transform::children_formal_parameter(AST_formal_parameter* in)
{
    in->type = transform_type(in->type);
    in->variable_name = transform_variable_name(in->variable_name);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_type(AST_type* in)
{
    in->class_name = transform_class_name(in->class_name);
}

void AST_transform::children_attribute(AST_attribute* in)
{
    in->attr_mod = transform_attr_mod(in->attr_mod);
    in->variable_name = transform_variable_name(in->variable_name);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_attr_mod(AST_attr_mod* in)
{
}

void AST_transform::children_if(AST_if* in)
{
    in->expr = transform_expr(in->expr);
    in->iftrue = transform_statement_list(in->iftrue);
    in->iffalse = transform_statement_list(in->iffalse);
}

void AST_transform::children_while(AST_while* in)
{
    in->expr = transform_expr(in->expr);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_do(AST_do* in)
{
    in->statements = transform_statement_list(in->statements);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_for(AST_for* in)
{
    in->init = transform_expr(in->init);
    in->cond = transform_expr(in->cond);
    in->incr = transform_expr(in->incr);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_foreach(AST_foreach* in)
{
    in->expr = transform_expr(in->expr);
    in->key = transform_variable(in->key);
    in->val = transform_variable(in->val);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_switch(AST_switch* in)
{
    in->expr = transform_expr(in->expr);
    in->switch_cases = transform_switch_case_list(in->switch_cases);
}

void AST_transform::children_switch_case(AST_switch_case* in)
{
    in->expr = transform_expr(in->expr);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_break(AST_break* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_continue(AST_continue* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_return(AST_return* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_static_declaration(AST_static_declaration* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_unset(AST_unset* in)
{
    in->variable = transform_variable(in->variable);
}

void AST_transform::children_declare(AST_declare* in)
{
    in->directives = transform_directive_list(in->directives);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_directive(AST_directive* in)
{
    in->directive_name = transform_directive_name(in->directive_name);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_try(AST_try* in)
{
    in->statements = transform_statement_list(in->statements);
    in->catches = transform_catch_list(in->catches);
}

void AST_transform::children_catch(AST_catch* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->variable_name = transform_variable_name(in->variable_name);
    in->statements = transform_statement_list(in->statements);
}

void AST_transform::children_throw(AST_throw* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_eval_expr(AST_eval_expr* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_nop(AST_nop* in)
{
}

void AST_transform::children_goto(AST_goto* in)
{
    in->label_name = transform_label_name(in->label_name);
}

void AST_transform::children_label(AST_label* in)
{
    in->label_name = transform_label_name(in->label_name);
}

void AST_transform::children_assignment(AST_assignment* in)
{
    in->variable = transform_variable(in->variable);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_list_assignment(AST_list_assignment* in)
{
    in->list_elements = transform_list_elements(in->list_elements);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_list_elements(AST_list_elements* in)
{
    in->list_elements = transform_list_element_list(in->list_elements);
}

void AST_transform::children_cast(AST_cast* in)
{
    in->cast = transform_cast(in->cast);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_unary_op(AST_unary_op* in)
{
    in->op = transform_op(in->op);
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_bin_op(AST_bin_op* in)
{
    in->left = transform_expr(in->left);
    in->op = transform_op(in->op);
    in->right = transform_expr(in->right);
}

void AST_transform::children_conditional_expr(AST_conditional_expr* in)
{
    in->cond = transform_expr(in->cond);
    in->iftrue = transform_expr(in->iftrue);
    in->iffalse = transform_expr(in->iffalse);
}

void AST_transform::children_ignore_errors(AST_ignore_errors* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_constant(AST_constant* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->constant_name = transform_constant_name(in->constant_name);
}

void AST_transform::children_instanceof(AST_instanceof* in)
{
    in->expr = transform_expr(in->expr);
    in->class_name = transform_class_name(in->class_name);
}

void AST_transform::children_variable(AST_variable* in)
{
    in->target = transform_target(in->target);
    in->variable_name = transform_variable_name(in->variable_name);
    in->array_indices = transform_expr_list(in->array_indices);
    in->string_index = transform_expr(in->string_index);
}

void AST_transform::children_reflection(AST_reflection* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_pre_op(AST_pre_op* in)
{
    in->op = transform_op(in->op);
    in->variable = transform_variable(in->variable);
}

void AST_transform::children_post_op(AST_post_op* in)
{
    in->variable = transform_variable(in->variable);
    in->op = transform_op(in->op);
}

void AST_transform::children_array(AST_array* in)
{
    in->array_elems = transform_array_elem_list(in->array_elems);
}

void AST_transform::children_array_elem(AST_array_elem* in)
{
    in->key = transform_expr(in->key);
    in->val = transform_expr(in->val);
}

void AST_transform::children_method_invocation(AST_method_invocation* in)
{
    in->target = transform_target(in->target);
    in->method_name = transform_method_name(in->method_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

void AST_transform::children_actual_parameter(AST_actual_parameter* in)
{
    in->expr = transform_expr(in->expr);
}

void AST_transform::children_new(AST_new* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

void AST_transform::children_clone(AST_clone* in)
{
    in->expr = transform_expr(in->expr);
}

// Tokens don't have children, so these methods do nothing by default
void AST_transform::children_class_name(Token_class_name* in)
{
}

void AST_transform::children_interface_name(Token_interface_name* in)
{
}

void AST_transform::children_method_name(Token_method_name* in)
{
}

void AST_transform::children_variable_name(Token_variable_name* in)
{
}

void AST_transform::children_directive_name(Token_directive_name* in)
{
}

void AST_transform::children_label_name(Token_label_name* in)
{
}

void AST_transform::children_int(Token_int* in)
{
}

void AST_transform::children_real(Token_real* in)
{
}

void AST_transform::children_string(Token_string* in)
{
}

void AST_transform::children_bool(Token_bool* in)
{
}

void AST_transform::children_null(Token_null* in)
{
}

void AST_transform::children_cast(Token_cast* in)
{
}

void AST_transform::children_op(Token_op* in)
{
}

void AST_transform::children_constant_name(Token_constant_name* in)
{
}

// Call the pre-transform, transform-children post-transform methods in order
// Do not override unless you know what you are doing
List<AST_statement*>* AST_transform::transform_statement_list(List<AST_statement*>* in)
{
    List<AST_statement*>::const_iterator i;
    List<AST_statement*>* out = new List<AST_statement*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_statement(*i));
    }
    
    return out;
}

List<AST_statement*>* AST_transform::transform_statement(AST_statement* in)
{
    List<AST_statement*>::const_iterator i;
    List<AST_statement*>* out1 = new List<AST_statement*>;
    List<AST_statement*>* out2 = new List<AST_statement*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_statement(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_statement(*i);
    		post_statement(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

AST_class_mod* AST_transform::transform_class_mod(AST_class_mod* in)
{
    if(in == NULL) return NULL;
    
    AST_class_mod* out;
    
    out = pre_class_mod(in);
    if(out != NULL)
    {
    	children_class_mod(out);
    	out = post_class_mod(out);
    }
    
    return out;
}

Token_class_name* AST_transform::transform_class_name(Token_class_name* in)
{
    if(in == NULL) return NULL;
    
    Token_class_name* out;
    
    out = pre_class_name(in);
    if(out != NULL)
    {
    	children_class_name(out);
    	out = post_class_name(out);
    }
    
    return out;
}

List<Token_interface_name*>* AST_transform::transform_interface_name_list(List<Token_interface_name*>* in)
{
    List<Token_interface_name*>::const_iterator i;
    List<Token_interface_name*>* out = new List<Token_interface_name*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_interface_name(*i));
    }
    
    return out;
}

List<AST_member*>* AST_transform::transform_member_list(List<AST_member*>* in)
{
    List<AST_member*>::const_iterator i;
    List<AST_member*>* out = new List<AST_member*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_member(*i));
    }
    
    return out;
}

List<AST_member*>* AST_transform::transform_member(AST_member* in)
{
    List<AST_member*>::const_iterator i;
    List<AST_member*>* out1 = new List<AST_member*>;
    List<AST_member*>* out2 = new List<AST_member*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_member(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_member(*i);
    		post_member(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

Token_interface_name* AST_transform::transform_interface_name(Token_interface_name* in)
{
    if(in == NULL) return NULL;
    
    Token_interface_name* out;
    
    out = pre_interface_name(in);
    if(out != NULL)
    {
    	children_interface_name(out);
    	out = post_interface_name(out);
    }
    
    return out;
}

AST_signature* AST_transform::transform_signature(AST_signature* in)
{
    if(in == NULL) return NULL;
    
    AST_signature* out;
    
    out = pre_signature(in);
    if(out != NULL)
    {
    	children_signature(out);
    	out = post_signature(out);
    }
    
    return out;
}

AST_method_mod* AST_transform::transform_method_mod(AST_method_mod* in)
{
    if(in == NULL) return NULL;
    
    AST_method_mod* out;
    
    out = pre_method_mod(in);
    if(out != NULL)
    {
    	children_method_mod(out);
    	out = post_method_mod(out);
    }
    
    return out;
}

Token_method_name* AST_transform::transform_method_name(Token_method_name* in)
{
    if(in == NULL) return NULL;
    
    Token_method_name* out;
    
    out = pre_method_name(in);
    if(out != NULL)
    {
    	children_method_name(out);
    	out = post_method_name(out);
    }
    
    return out;
}

List<AST_formal_parameter*>* AST_transform::transform_formal_parameter_list(List<AST_formal_parameter*>* in)
{
    List<AST_formal_parameter*>::const_iterator i;
    List<AST_formal_parameter*>* out = new List<AST_formal_parameter*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_formal_parameter(*i));
    }
    
    return out;
}

List<AST_formal_parameter*>* AST_transform::transform_formal_parameter(AST_formal_parameter* in)
{
    List<AST_formal_parameter*>::const_iterator i;
    List<AST_formal_parameter*>* out1 = new List<AST_formal_parameter*>;
    List<AST_formal_parameter*>* out2 = new List<AST_formal_parameter*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_formal_parameter(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_formal_parameter(*i);
    		post_formal_parameter(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

AST_type* AST_transform::transform_type(AST_type* in)
{
    if(in == NULL) return NULL;
    
    AST_type* out;
    
    out = pre_type(in);
    if(out != NULL)
    {
    	children_type(out);
    	out = post_type(out);
    }
    
    return out;
}

Token_variable_name* AST_transform::transform_variable_name(Token_variable_name* in)
{
    if(in == NULL) return NULL;
    
    Token_variable_name* out;
    
    out = pre_variable_name(in);
    if(out != NULL)
    {
    	children_variable_name(out);
    	out = post_variable_name(out);
    }
    
    return out;
}

AST_expr* AST_transform::transform_expr(AST_expr* in)
{
    if(in == NULL) return NULL;
    
    AST_expr* out;
    
    out = pre_expr(in);
    if(out != NULL)
    {
    	children_expr(out);
    	out = post_expr(out);
    }
    
    return out;
}

AST_attr_mod* AST_transform::transform_attr_mod(AST_attr_mod* in)
{
    if(in == NULL) return NULL;
    
    AST_attr_mod* out;
    
    out = pre_attr_mod(in);
    if(out != NULL)
    {
    	children_attr_mod(out);
    	out = post_attr_mod(out);
    }
    
    return out;
}

AST_variable* AST_transform::transform_variable(AST_variable* in)
{
    if(in == NULL) return NULL;
    
    AST_variable* out;
    
    out = pre_variable(in);
    if(out != NULL)
    {
    	children_variable(out);
    	out = post_variable(out);
    }
    
    return out;
}

List<AST_switch_case*>* AST_transform::transform_switch_case_list(List<AST_switch_case*>* in)
{
    List<AST_switch_case*>::const_iterator i;
    List<AST_switch_case*>* out = new List<AST_switch_case*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_switch_case(*i));
    }
    
    return out;
}

List<AST_switch_case*>* AST_transform::transform_switch_case(AST_switch_case* in)
{
    List<AST_switch_case*>::const_iterator i;
    List<AST_switch_case*>* out1 = new List<AST_switch_case*>;
    List<AST_switch_case*>* out2 = new List<AST_switch_case*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_switch_case(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_switch_case(*i);
    		post_switch_case(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

List<AST_directive*>* AST_transform::transform_directive_list(List<AST_directive*>* in)
{
    List<AST_directive*>::const_iterator i;
    List<AST_directive*>* out = new List<AST_directive*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_directive(*i));
    }
    
    return out;
}

List<AST_directive*>* AST_transform::transform_directive(AST_directive* in)
{
    List<AST_directive*>::const_iterator i;
    List<AST_directive*>* out1 = new List<AST_directive*>;
    List<AST_directive*>* out2 = new List<AST_directive*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_directive(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_directive(*i);
    		post_directive(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

Token_directive_name* AST_transform::transform_directive_name(Token_directive_name* in)
{
    if(in == NULL) return NULL;
    
    Token_directive_name* out;
    
    out = pre_directive_name(in);
    if(out != NULL)
    {
    	children_directive_name(out);
    	out = post_directive_name(out);
    }
    
    return out;
}

List<AST_catch*>* AST_transform::transform_catch_list(List<AST_catch*>* in)
{
    List<AST_catch*>::const_iterator i;
    List<AST_catch*>* out = new List<AST_catch*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_catch(*i));
    }
    
    return out;
}

List<AST_catch*>* AST_transform::transform_catch(AST_catch* in)
{
    List<AST_catch*>::const_iterator i;
    List<AST_catch*>* out1 = new List<AST_catch*>;
    List<AST_catch*>* out2 = new List<AST_catch*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_catch(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_catch(*i);
    		post_catch(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

Token_label_name* AST_transform::transform_label_name(Token_label_name* in)
{
    if(in == NULL) return NULL;
    
    Token_label_name* out;
    
    out = pre_label_name(in);
    if(out != NULL)
    {
    	children_label_name(out);
    	out = post_label_name(out);
    }
    
    return out;
}

AST_list_elements* AST_transform::transform_list_elements(AST_list_elements* in)
{
    if(in == NULL) return NULL;
    
    AST_list_elements* out;
    
    out = pre_list_elements(in);
    if(out != NULL)
    {
    	children_list_elements(out);
    	out = post_list_elements(out);
    }
    
    return out;
}

List<AST_list_element*>* AST_transform::transform_list_element_list(List<AST_list_element*>* in)
{
    List<AST_list_element*>::const_iterator i;
    List<AST_list_element*>* out = new List<AST_list_element*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_list_element(*i));
    }
    
    return out;
}

List<AST_list_element*>* AST_transform::transform_list_element(AST_list_element* in)
{
    List<AST_list_element*>::const_iterator i;
    List<AST_list_element*>* out1 = new List<AST_list_element*>;
    List<AST_list_element*>* out2 = new List<AST_list_element*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_list_element(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_list_element(*i);
    		post_list_element(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

Token_cast* AST_transform::transform_cast(Token_cast* in)
{
    if(in == NULL) return NULL;
    
    Token_cast* out;
    
    out = pre_cast(in);
    if(out != NULL)
    {
    	children_cast(out);
    	out = post_cast(out);
    }
    
    return out;
}

Token_op* AST_transform::transform_op(Token_op* in)
{
    if(in == NULL) return NULL;
    
    Token_op* out;
    
    out = pre_op(in);
    if(out != NULL)
    {
    	children_op(out);
    	out = post_op(out);
    }
    
    return out;
}

Token_constant_name* AST_transform::transform_constant_name(Token_constant_name* in)
{
    if(in == NULL) return NULL;
    
    Token_constant_name* out;
    
    out = pre_constant_name(in);
    if(out != NULL)
    {
    	children_constant_name(out);
    	out = post_constant_name(out);
    }
    
    return out;
}

AST_class_name* AST_transform::transform_class_name(AST_class_name* in)
{
    if(in == NULL) return NULL;
    
    AST_class_name* out;
    
    out = pre_class_name(in);
    if(out != NULL)
    {
    	children_class_name(out);
    	out = post_class_name(out);
    }
    
    return out;
}

AST_target* AST_transform::transform_target(AST_target* in)
{
    if(in == NULL) return NULL;
    
    AST_target* out;
    
    out = pre_target(in);
    if(out != NULL)
    {
    	children_target(out);
    	out = post_target(out);
    }
    
    return out;
}

AST_variable_name* AST_transform::transform_variable_name(AST_variable_name* in)
{
    if(in == NULL) return NULL;
    
    AST_variable_name* out;
    
    out = pre_variable_name(in);
    if(out != NULL)
    {
    	children_variable_name(out);
    	out = post_variable_name(out);
    }
    
    return out;
}

List<AST_expr*>* AST_transform::transform_expr_list(List<AST_expr*>* in)
{
    List<AST_expr*>::const_iterator i;
    List<AST_expr*>* out = new List<AST_expr*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_expr(*i));
    }
    
    return out;
}

List<AST_array_elem*>* AST_transform::transform_array_elem_list(List<AST_array_elem*>* in)
{
    List<AST_array_elem*>::const_iterator i;
    List<AST_array_elem*>* out = new List<AST_array_elem*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_array_elem(*i));
    }
    
    return out;
}

List<AST_array_elem*>* AST_transform::transform_array_elem(AST_array_elem* in)
{
    List<AST_array_elem*>::const_iterator i;
    List<AST_array_elem*>* out1 = new List<AST_array_elem*>;
    List<AST_array_elem*>* out2 = new List<AST_array_elem*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_array_elem(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_array_elem(*i);
    		post_array_elem(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

AST_method_name* AST_transform::transform_method_name(AST_method_name* in)
{
    if(in == NULL) return NULL;
    
    AST_method_name* out;
    
    out = pre_method_name(in);
    if(out != NULL)
    {
    	children_method_name(out);
    	out = post_method_name(out);
    }
    
    return out;
}

List<AST_actual_parameter*>* AST_transform::transform_actual_parameter_list(List<AST_actual_parameter*>* in)
{
    List<AST_actual_parameter*>::const_iterator i;
    List<AST_actual_parameter*>* out = new List<AST_actual_parameter*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_actual_parameter(*i));
    }
    
    return out;
}

List<AST_actual_parameter*>* AST_transform::transform_actual_parameter(AST_actual_parameter* in)
{
    List<AST_actual_parameter*>::const_iterator i;
    List<AST_actual_parameter*>* out1 = new List<AST_actual_parameter*>;
    List<AST_actual_parameter*>* out2 = new List<AST_actual_parameter*>;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_actual_parameter(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_actual_parameter(*i);
    		post_actual_parameter(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

AST_php_script* AST_transform::transform_php_script(AST_php_script* in)
{
    if(in == NULL) return NULL;
    
    AST_php_script* out;
    
    out = pre_php_script(in);
    if(out != NULL)
    {
    	children_php_script(out);
    	out = post_php_script(out);
    }
    
    return out;
}

// Invoke the right pre-transform (manual dispatching)
// Do not override unless you know what you are doing
void AST_transform::pre_statement(AST_statement* in, List<AST_statement*>* out)
{
    switch(in->classid())
    {
    case 2: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_class_def(dynamic_cast<AST_class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 4: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_interface_def(dynamic_cast<AST_interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 5: 
    	{
    		List<AST_method*>* local_out = new List<AST_method*>;
    		List<AST_method*>::const_iterator i;
    		pre_method(dynamic_cast<AST_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 12: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_if(dynamic_cast<AST_if*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 13: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_while(dynamic_cast<AST_while*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 14: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_do(dynamic_cast<AST_do*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 15: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_for(dynamic_cast<AST_for*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 16: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_foreach(dynamic_cast<AST_foreach*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 17: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_switch(dynamic_cast<AST_switch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 19: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_break(dynamic_cast<AST_break*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 20: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_continue(dynamic_cast<AST_continue*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 21: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_return(dynamic_cast<AST_return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 22: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_static_declaration(dynamic_cast<AST_static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 23: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_unset(dynamic_cast<AST_unset*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 24: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_declare(dynamic_cast<AST_declare*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 26: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_try(dynamic_cast<AST_try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 28: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_throw(dynamic_cast<AST_throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 29: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_eval_expr(dynamic_cast<AST_eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 30: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_nop(dynamic_cast<AST_nop*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 32: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_label(dynamic_cast<AST_label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 31: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		pre_goto(dynamic_cast<AST_goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

void AST_transform::pre_member(AST_member* in, List<AST_member*>* out)
{
    switch(in->classid())
    {
    case 5: 
    	{
    		List<AST_method*>* local_out = new List<AST_method*>;
    		List<AST_method*>::const_iterator i;
    		pre_method(dynamic_cast<AST_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 10: 
    	{
    		List<AST_member*>* local_out = new List<AST_member*>;
    		List<AST_member*>::const_iterator i;
    		pre_attribute(dynamic_cast<AST_attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

AST_expr* AST_transform::pre_expr(AST_expr* in)
{
    switch(in->classid())
    {
    case 33: return pre_assignment(dynamic_cast<AST_assignment*>(in));
    case 34: return pre_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    case 36: return pre_cast(dynamic_cast<AST_cast*>(in));
    case 37: return pre_unary_op(dynamic_cast<AST_unary_op*>(in));
    case 38: return pre_bin_op(dynamic_cast<AST_bin_op*>(in));
    case 39: return pre_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    case 40: return pre_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    case 41: return pre_constant(dynamic_cast<AST_constant*>(in));
    case 42: return pre_instanceof(dynamic_cast<AST_instanceof*>(in));
    case 43: return pre_variable(dynamic_cast<AST_variable*>(in));
    case 45: return pre_pre_op(dynamic_cast<AST_pre_op*>(in));
    case 46: return pre_post_op(dynamic_cast<AST_post_op*>(in));
    case 47: return pre_array(dynamic_cast<AST_array*>(in));
    case 49: return pre_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    case 51: return pre_new(dynamic_cast<AST_new*>(in));
    case 52: return pre_clone(dynamic_cast<AST_clone*>(in));
    case 59: return pre_int(dynamic_cast<Token_int*>(in));
    case 60: return pre_real(dynamic_cast<Token_real*>(in));
    case 61: return pre_string(dynamic_cast<Token_string*>(in));
    case 62: return pre_bool(dynamic_cast<Token_bool*>(in));
    case 63: return pre_null(dynamic_cast<Token_null*>(in));
    }
    assert(0);
}

void AST_transform::pre_list_element(AST_list_element* in, List<AST_list_element*>* out)
{
    switch(in->classid())
    {
    case 43: 
    	out->push_back(pre_variable(dynamic_cast<AST_variable*>(in)));
    	return;
    case 35: 
    	out->push_back(pre_list_elements(dynamic_cast<AST_list_elements*>(in)));
    	return;
    }
    assert(0);
}

AST_class_name* AST_transform::pre_class_name(AST_class_name* in)
{
    switch(in->classid())
    {
    case 53: return pre_class_name(dynamic_cast<Token_class_name*>(in));
    case 44: return pre_reflection(dynamic_cast<AST_reflection*>(in));
    }
    assert(0);
}

AST_target* AST_transform::pre_target(AST_target* in)
{
    switch(in->classid())
    {
    case 33: return pre_assignment(dynamic_cast<AST_assignment*>(in));
    case 34: return pre_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    case 36: return pre_cast(dynamic_cast<AST_cast*>(in));
    case 37: return pre_unary_op(dynamic_cast<AST_unary_op*>(in));
    case 38: return pre_bin_op(dynamic_cast<AST_bin_op*>(in));
    case 39: return pre_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    case 40: return pre_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    case 41: return pre_constant(dynamic_cast<AST_constant*>(in));
    case 42: return pre_instanceof(dynamic_cast<AST_instanceof*>(in));
    case 43: return pre_variable(dynamic_cast<AST_variable*>(in));
    case 45: return pre_pre_op(dynamic_cast<AST_pre_op*>(in));
    case 46: return pre_post_op(dynamic_cast<AST_post_op*>(in));
    case 47: return pre_array(dynamic_cast<AST_array*>(in));
    case 49: return pre_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    case 51: return pre_new(dynamic_cast<AST_new*>(in));
    case 52: return pre_clone(dynamic_cast<AST_clone*>(in));
    case 59: return pre_int(dynamic_cast<Token_int*>(in));
    case 60: return pre_real(dynamic_cast<Token_real*>(in));
    case 61: return pre_string(dynamic_cast<Token_string*>(in));
    case 62: return pre_bool(dynamic_cast<Token_bool*>(in));
    case 63: return pre_null(dynamic_cast<Token_null*>(in));
    case 53: return pre_class_name(dynamic_cast<Token_class_name*>(in));
    }
    assert(0);
}

AST_variable_name* AST_transform::pre_variable_name(AST_variable_name* in)
{
    switch(in->classid())
    {
    case 56: return pre_variable_name(dynamic_cast<Token_variable_name*>(in));
    case 44: return pre_reflection(dynamic_cast<AST_reflection*>(in));
    }
    assert(0);
}

AST_method_name* AST_transform::pre_method_name(AST_method_name* in)
{
    switch(in->classid())
    {
    case 55: return pre_method_name(dynamic_cast<Token_method_name*>(in));
    case 44: return pre_reflection(dynamic_cast<AST_reflection*>(in));
    }
    assert(0);
}

// Invoke the right post-transform (manual dispatching)
// Do not override unless you know what you are doing
void AST_transform::post_statement(AST_statement* in, List<AST_statement*>* out)
{
    switch(in->classid())
    {
    case 2: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_class_def(dynamic_cast<AST_class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 4: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_interface_def(dynamic_cast<AST_interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 5: 
    	{
    		List<AST_method*>* local_out = new List<AST_method*>;
    		List<AST_method*>::const_iterator i;
    		post_method(dynamic_cast<AST_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 12: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_if(dynamic_cast<AST_if*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 13: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_while(dynamic_cast<AST_while*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 14: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_do(dynamic_cast<AST_do*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 15: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_for(dynamic_cast<AST_for*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 16: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_foreach(dynamic_cast<AST_foreach*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 17: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_switch(dynamic_cast<AST_switch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 19: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_break(dynamic_cast<AST_break*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 20: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_continue(dynamic_cast<AST_continue*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 21: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_return(dynamic_cast<AST_return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 22: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_static_declaration(dynamic_cast<AST_static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 23: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_unset(dynamic_cast<AST_unset*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 24: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_declare(dynamic_cast<AST_declare*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 26: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_try(dynamic_cast<AST_try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 28: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_throw(dynamic_cast<AST_throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 29: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_eval_expr(dynamic_cast<AST_eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 30: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_nop(dynamic_cast<AST_nop*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 32: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_label(dynamic_cast<AST_label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 31: 
    	{
    		List<AST_statement*>* local_out = new List<AST_statement*>;
    		List<AST_statement*>::const_iterator i;
    		post_goto(dynamic_cast<AST_goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

void AST_transform::post_member(AST_member* in, List<AST_member*>* out)
{
    switch(in->classid())
    {
    case 5: 
    	{
    		List<AST_method*>* local_out = new List<AST_method*>;
    		List<AST_method*>::const_iterator i;
    		post_method(dynamic_cast<AST_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case 10: 
    	{
    		List<AST_member*>* local_out = new List<AST_member*>;
    		List<AST_member*>::const_iterator i;
    		post_attribute(dynamic_cast<AST_attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

AST_expr* AST_transform::post_expr(AST_expr* in)
{
    switch(in->classid())
    {
    case 33: return post_assignment(dynamic_cast<AST_assignment*>(in));
    case 34: return post_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    case 36: return post_cast(dynamic_cast<AST_cast*>(in));
    case 37: return post_unary_op(dynamic_cast<AST_unary_op*>(in));
    case 38: return post_bin_op(dynamic_cast<AST_bin_op*>(in));
    case 39: return post_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    case 40: return post_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    case 41: return post_constant(dynamic_cast<AST_constant*>(in));
    case 42: return post_instanceof(dynamic_cast<AST_instanceof*>(in));
    case 43: return post_variable(dynamic_cast<AST_variable*>(in));
    case 45: return post_pre_op(dynamic_cast<AST_pre_op*>(in));
    case 46: return post_post_op(dynamic_cast<AST_post_op*>(in));
    case 47: return post_array(dynamic_cast<AST_array*>(in));
    case 49: return post_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    case 51: return post_new(dynamic_cast<AST_new*>(in));
    case 52: return post_clone(dynamic_cast<AST_clone*>(in));
    case 59: return post_int(dynamic_cast<Token_int*>(in));
    case 60: return post_real(dynamic_cast<Token_real*>(in));
    case 61: return post_string(dynamic_cast<Token_string*>(in));
    case 62: return post_bool(dynamic_cast<Token_bool*>(in));
    case 63: return post_null(dynamic_cast<Token_null*>(in));
    }
    assert(0);
}

void AST_transform::post_list_element(AST_list_element* in, List<AST_list_element*>* out)
{
    switch(in->classid())
    {
    case 43: 
    	out->push_back(post_variable(dynamic_cast<AST_variable*>(in)));
    	return;
    case 35: 
    	out->push_back(post_list_elements(dynamic_cast<AST_list_elements*>(in)));
    	return;
    }
    assert(0);
}

AST_class_name* AST_transform::post_class_name(AST_class_name* in)
{
    switch(in->classid())
    {
    case 53: return post_class_name(dynamic_cast<Token_class_name*>(in));
    case 44: return post_reflection(dynamic_cast<AST_reflection*>(in));
    }
    assert(0);
}

AST_target* AST_transform::post_target(AST_target* in)
{
    switch(in->classid())
    {
    case 33: return post_assignment(dynamic_cast<AST_assignment*>(in));
    case 34: return post_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    case 36: return post_cast(dynamic_cast<AST_cast*>(in));
    case 37: return post_unary_op(dynamic_cast<AST_unary_op*>(in));
    case 38: return post_bin_op(dynamic_cast<AST_bin_op*>(in));
    case 39: return post_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    case 40: return post_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    case 41: return post_constant(dynamic_cast<AST_constant*>(in));
    case 42: return post_instanceof(dynamic_cast<AST_instanceof*>(in));
    case 43: return post_variable(dynamic_cast<AST_variable*>(in));
    case 45: return post_pre_op(dynamic_cast<AST_pre_op*>(in));
    case 46: return post_post_op(dynamic_cast<AST_post_op*>(in));
    case 47: return post_array(dynamic_cast<AST_array*>(in));
    case 49: return post_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    case 51: return post_new(dynamic_cast<AST_new*>(in));
    case 52: return post_clone(dynamic_cast<AST_clone*>(in));
    case 59: return post_int(dynamic_cast<Token_int*>(in));
    case 60: return post_real(dynamic_cast<Token_real*>(in));
    case 61: return post_string(dynamic_cast<Token_string*>(in));
    case 62: return post_bool(dynamic_cast<Token_bool*>(in));
    case 63: return post_null(dynamic_cast<Token_null*>(in));
    case 53: return post_class_name(dynamic_cast<Token_class_name*>(in));
    }
    assert(0);
}

AST_variable_name* AST_transform::post_variable_name(AST_variable_name* in)
{
    switch(in->classid())
    {
    case 56: return post_variable_name(dynamic_cast<Token_variable_name*>(in));
    case 44: return post_reflection(dynamic_cast<AST_reflection*>(in));
    }
    assert(0);
}

AST_method_name* AST_transform::post_method_name(AST_method_name* in)
{
    switch(in->classid())
    {
    case 55: return post_method_name(dynamic_cast<Token_method_name*>(in));
    case 44: return post_reflection(dynamic_cast<AST_reflection*>(in));
    }
    assert(0);
}

// Invoke the right transform-children (manual dispatching)
// Do not override unless you what you are doing
void AST_transform::children_statement(AST_statement* in)
{
    switch(in->classid())
    {
    case 2:
    	children_class_def(dynamic_cast<AST_class_def*>(in));
    	break;
    case 4:
    	children_interface_def(dynamic_cast<AST_interface_def*>(in));
    	break;
    case 5:
    	children_method(dynamic_cast<AST_method*>(in));
    	break;
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
    case 32:
    	children_label(dynamic_cast<AST_label*>(in));
    	break;
    case 31:
    	children_goto(dynamic_cast<AST_goto*>(in));
    	break;
    }
}

void AST_transform::children_member(AST_member* in)
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

void AST_transform::children_expr(AST_expr* in)
{
    switch(in->classid())
    {
    case 33:
    	children_assignment(dynamic_cast<AST_assignment*>(in));
    	break;
    case 34:
    	children_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 36:
    	children_cast(dynamic_cast<AST_cast*>(in));
    	break;
    case 37:
    	children_unary_op(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 38:
    	children_bin_op(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 39:
    	children_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 40:
    	children_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 41:
    	children_constant(dynamic_cast<AST_constant*>(in));
    	break;
    case 42:
    	children_instanceof(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 43:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case 45:
    	children_pre_op(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 46:
    	children_post_op(dynamic_cast<AST_post_op*>(in));
    	break;
    case 47:
    	children_array(dynamic_cast<AST_array*>(in));
    	break;
    case 49:
    	children_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 51:
    	children_new(dynamic_cast<AST_new*>(in));
    	break;
    case 52:
    	children_clone(dynamic_cast<AST_clone*>(in));
    	break;
    case 59:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case 60:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case 61:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case 62:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case 63:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void AST_transform::children_list_element(AST_list_element* in)
{
    switch(in->classid())
    {
    case 43:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case 35:
    	children_list_elements(dynamic_cast<AST_list_elements*>(in));
    	break;
    }
}

void AST_transform::children_class_name(AST_class_name* in)
{
    switch(in->classid())
    {
    case 53:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    case 44:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_transform::children_target(AST_target* in)
{
    switch(in->classid())
    {
    case 33:
    	children_assignment(dynamic_cast<AST_assignment*>(in));
    	break;
    case 34:
    	children_list_assignment(dynamic_cast<AST_list_assignment*>(in));
    	break;
    case 36:
    	children_cast(dynamic_cast<AST_cast*>(in));
    	break;
    case 37:
    	children_unary_op(dynamic_cast<AST_unary_op*>(in));
    	break;
    case 38:
    	children_bin_op(dynamic_cast<AST_bin_op*>(in));
    	break;
    case 39:
    	children_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
    	break;
    case 40:
    	children_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
    	break;
    case 41:
    	children_constant(dynamic_cast<AST_constant*>(in));
    	break;
    case 42:
    	children_instanceof(dynamic_cast<AST_instanceof*>(in));
    	break;
    case 43:
    	children_variable(dynamic_cast<AST_variable*>(in));
    	break;
    case 45:
    	children_pre_op(dynamic_cast<AST_pre_op*>(in));
    	break;
    case 46:
    	children_post_op(dynamic_cast<AST_post_op*>(in));
    	break;
    case 47:
    	children_array(dynamic_cast<AST_array*>(in));
    	break;
    case 49:
    	children_method_invocation(dynamic_cast<AST_method_invocation*>(in));
    	break;
    case 51:
    	children_new(dynamic_cast<AST_new*>(in));
    	break;
    case 52:
    	children_clone(dynamic_cast<AST_clone*>(in));
    	break;
    case 59:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case 60:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case 61:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case 62:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case 63:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    case 53:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void AST_transform::children_variable_name(AST_variable_name* in)
{
    switch(in->classid())
    {
    case 56:
    	children_variable_name(dynamic_cast<Token_variable_name*>(in));
    	break;
    case 44:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

void AST_transform::children_method_name(AST_method_name* in)
{
    switch(in->classid())
    {
    case 55:
    	children_method_name(dynamic_cast<Token_method_name*>(in));
    	break;
    case 44:
    	children_reflection(dynamic_cast<AST_reflection*>(in));
    	break;
    }
}

