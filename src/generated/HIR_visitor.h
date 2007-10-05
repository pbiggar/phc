#ifndef _HIR_VISITOR_H_
#define _HIR_VISITOR_H_

#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/error.h"
#include "lib/Object.h"
#include "lib/List.h"
#include "lib/String.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/AttrMap.h"
#include <list>
#include <string>
#include <assert.h>
using namespace std;


#include "HIR.h"

namespace HIR{
class HIR_visitor
{
public:
    virtual ~HIR_visitor();
// Invoked before the children are visited
public:
    virtual void pre_node(HIR_node* in);
    virtual void pre_php_script(HIR_php_script* in);
    virtual void pre_statement(HIR_statement* in);
    virtual void pre_class_def(HIR_class_def* in);
    virtual void pre_class_mod(HIR_class_mod* in);
    virtual void pre_interface_def(HIR_interface_def* in);
    virtual void pre_member(HIR_member* in);
    virtual void pre_method(HIR_method* in);
    virtual void pre_signature(HIR_signature* in);
    virtual void pre_method_mod(HIR_method_mod* in);
    virtual void pre_formal_parameter(HIR_formal_parameter* in);
    virtual void pre_type(HIR_type* in);
    virtual void pre_attribute(HIR_attribute* in);
    virtual void pre_attr_mod(HIR_attr_mod* in);
    virtual void pre_if(HIR_if* in);
    virtual void pre_while(HIR_while* in);
    virtual void pre_do(HIR_do* in);
    virtual void pre_for(HIR_for* in);
    virtual void pre_foreach(HIR_foreach* in);
    virtual void pre_switch(HIR_switch* in);
    virtual void pre_switch_case(HIR_switch_case* in);
    virtual void pre_break(HIR_break* in);
    virtual void pre_continue(HIR_continue* in);
    virtual void pre_return(HIR_return* in);
    virtual void pre_static_declaration(HIR_static_declaration* in);
    virtual void pre_global(HIR_global* in);
    virtual void pre_declare(HIR_declare* in);
    virtual void pre_directive(HIR_directive* in);
    virtual void pre_try(HIR_try* in);
    virtual void pre_catch(HIR_catch* in);
    virtual void pre_throw(HIR_throw* in);
    virtual void pre_eval_expr(HIR_eval_expr* in);
    virtual void pre_nop(HIR_nop* in);
    virtual void pre_branch(HIR_branch* in);
    virtual void pre_goto(HIR_goto* in);
    virtual void pre_label(HIR_label* in);
    virtual void pre_expr(HIR_expr* in);
    virtual void pre_literal(HIR_literal* in);
    virtual void pre_assignment(HIR_assignment* in);
    virtual void pre_op_assignment(HIR_op_assignment* in);
    virtual void pre_list_assignment(HIR_list_assignment* in);
    virtual void pre_list_element(HIR_list_element* in);
    virtual void pre_nested_list_elements(HIR_nested_list_elements* in);
    virtual void pre_cast(HIR_cast* in);
    virtual void pre_unary_op(HIR_unary_op* in);
    virtual void pre_bin_op(HIR_bin_op* in);
    virtual void pre_conditional_expr(HIR_conditional_expr* in);
    virtual void pre_ignore_errors(HIR_ignore_errors* in);
    virtual void pre_constant(HIR_constant* in);
    virtual void pre_instanceof(HIR_instanceof* in);
    virtual void pre_variable(HIR_variable* in);
    virtual void pre_variable_name(HIR_variable_name* in);
    virtual void pre_reflection(HIR_reflection* in);
    virtual void pre_target(HIR_target* in);
    virtual void pre_pre_op(HIR_pre_op* in);
    virtual void pre_post_op(HIR_post_op* in);
    virtual void pre_array(HIR_array* in);
    virtual void pre_array_elem(HIR_array_elem* in);
    virtual void pre_method_invocation(HIR_method_invocation* in);
    virtual void pre_method_name(HIR_method_name* in);
    virtual void pre_actual_parameter(HIR_actual_parameter* in);
    virtual void pre_new(HIR_new* in);
    virtual void pre_class_name(HIR_class_name* in);
    virtual void pre_commented_node(HIR_commented_node* in);
    virtual void pre_identifier(HIR_identifier* in);
    virtual void pre_class_name(Token_class_name* in);
    virtual void pre_interface_name(Token_interface_name* in);
    virtual void pre_method_name(Token_method_name* in);
    virtual void pre_variable_name(Token_variable_name* in);
    virtual void pre_directive_name(Token_directive_name* in);
    virtual void pre_label_name(Token_label_name* in);
    virtual void pre_int(Token_int* in);
    virtual void pre_real(Token_real* in);
    virtual void pre_string(Token_string* in);
    virtual void pre_bool(Token_bool* in);
    virtual void pre_null(Token_null* in);
    virtual void pre_op(Token_op* in);
    virtual void pre_cast(Token_cast* in);
    virtual void pre_constant_name(Token_constant_name* in);
// Invoked after the children have been visited
public:
    virtual void post_node(HIR_node* in);
    virtual void post_php_script(HIR_php_script* in);
    virtual void post_statement(HIR_statement* in);
    virtual void post_class_def(HIR_class_def* in);
    virtual void post_class_mod(HIR_class_mod* in);
    virtual void post_interface_def(HIR_interface_def* in);
    virtual void post_member(HIR_member* in);
    virtual void post_method(HIR_method* in);
    virtual void post_signature(HIR_signature* in);
    virtual void post_method_mod(HIR_method_mod* in);
    virtual void post_formal_parameter(HIR_formal_parameter* in);
    virtual void post_type(HIR_type* in);
    virtual void post_attribute(HIR_attribute* in);
    virtual void post_attr_mod(HIR_attr_mod* in);
    virtual void post_if(HIR_if* in);
    virtual void post_while(HIR_while* in);
    virtual void post_do(HIR_do* in);
    virtual void post_for(HIR_for* in);
    virtual void post_foreach(HIR_foreach* in);
    virtual void post_switch(HIR_switch* in);
    virtual void post_switch_case(HIR_switch_case* in);
    virtual void post_break(HIR_break* in);
    virtual void post_continue(HIR_continue* in);
    virtual void post_return(HIR_return* in);
    virtual void post_static_declaration(HIR_static_declaration* in);
    virtual void post_global(HIR_global* in);
    virtual void post_declare(HIR_declare* in);
    virtual void post_directive(HIR_directive* in);
    virtual void post_try(HIR_try* in);
    virtual void post_catch(HIR_catch* in);
    virtual void post_throw(HIR_throw* in);
    virtual void post_eval_expr(HIR_eval_expr* in);
    virtual void post_nop(HIR_nop* in);
    virtual void post_branch(HIR_branch* in);
    virtual void post_goto(HIR_goto* in);
    virtual void post_label(HIR_label* in);
    virtual void post_expr(HIR_expr* in);
    virtual void post_literal(HIR_literal* in);
    virtual void post_assignment(HIR_assignment* in);
    virtual void post_op_assignment(HIR_op_assignment* in);
    virtual void post_list_assignment(HIR_list_assignment* in);
    virtual void post_list_element(HIR_list_element* in);
    virtual void post_nested_list_elements(HIR_nested_list_elements* in);
    virtual void post_cast(HIR_cast* in);
    virtual void post_unary_op(HIR_unary_op* in);
    virtual void post_bin_op(HIR_bin_op* in);
    virtual void post_conditional_expr(HIR_conditional_expr* in);
    virtual void post_ignore_errors(HIR_ignore_errors* in);
    virtual void post_constant(HIR_constant* in);
    virtual void post_instanceof(HIR_instanceof* in);
    virtual void post_variable(HIR_variable* in);
    virtual void post_variable_name(HIR_variable_name* in);
    virtual void post_reflection(HIR_reflection* in);
    virtual void post_target(HIR_target* in);
    virtual void post_pre_op(HIR_pre_op* in);
    virtual void post_post_op(HIR_post_op* in);
    virtual void post_array(HIR_array* in);
    virtual void post_array_elem(HIR_array_elem* in);
    virtual void post_method_invocation(HIR_method_invocation* in);
    virtual void post_method_name(HIR_method_name* in);
    virtual void post_actual_parameter(HIR_actual_parameter* in);
    virtual void post_new(HIR_new* in);
    virtual void post_class_name(HIR_class_name* in);
    virtual void post_commented_node(HIR_commented_node* in);
    virtual void post_identifier(HIR_identifier* in);
    virtual void post_class_name(Token_class_name* in);
    virtual void post_interface_name(Token_interface_name* in);
    virtual void post_method_name(Token_method_name* in);
    virtual void post_variable_name(Token_variable_name* in);
    virtual void post_directive_name(Token_directive_name* in);
    virtual void post_label_name(Token_label_name* in);
    virtual void post_int(Token_int* in);
    virtual void post_real(Token_real* in);
    virtual void post_string(Token_string* in);
    virtual void post_bool(Token_bool* in);
    virtual void post_null(Token_null* in);
    virtual void post_op(Token_op* in);
    virtual void post_cast(Token_cast* in);
    virtual void post_constant_name(Token_constant_name* in);
// Visit the children of a node
public:
    virtual void children_php_script(HIR_php_script* in);
    virtual void children_class_def(HIR_class_def* in);
    virtual void children_class_mod(HIR_class_mod* in);
    virtual void children_interface_def(HIR_interface_def* in);
    virtual void children_method(HIR_method* in);
    virtual void children_signature(HIR_signature* in);
    virtual void children_method_mod(HIR_method_mod* in);
    virtual void children_formal_parameter(HIR_formal_parameter* in);
    virtual void children_type(HIR_type* in);
    virtual void children_attribute(HIR_attribute* in);
    virtual void children_attr_mod(HIR_attr_mod* in);
    virtual void children_if(HIR_if* in);
    virtual void children_while(HIR_while* in);
    virtual void children_do(HIR_do* in);
    virtual void children_for(HIR_for* in);
    virtual void children_foreach(HIR_foreach* in);
    virtual void children_switch(HIR_switch* in);
    virtual void children_switch_case(HIR_switch_case* in);
    virtual void children_break(HIR_break* in);
    virtual void children_continue(HIR_continue* in);
    virtual void children_return(HIR_return* in);
    virtual void children_static_declaration(HIR_static_declaration* in);
    virtual void children_global(HIR_global* in);
    virtual void children_declare(HIR_declare* in);
    virtual void children_directive(HIR_directive* in);
    virtual void children_try(HIR_try* in);
    virtual void children_catch(HIR_catch* in);
    virtual void children_throw(HIR_throw* in);
    virtual void children_eval_expr(HIR_eval_expr* in);
    virtual void children_nop(HIR_nop* in);
    virtual void children_branch(HIR_branch* in);
    virtual void children_goto(HIR_goto* in);
    virtual void children_label(HIR_label* in);
    virtual void children_assignment(HIR_assignment* in);
    virtual void children_op_assignment(HIR_op_assignment* in);
    virtual void children_list_assignment(HIR_list_assignment* in);
    virtual void children_nested_list_elements(HIR_nested_list_elements* in);
    virtual void children_cast(HIR_cast* in);
    virtual void children_unary_op(HIR_unary_op* in);
    virtual void children_bin_op(HIR_bin_op* in);
    virtual void children_conditional_expr(HIR_conditional_expr* in);
    virtual void children_ignore_errors(HIR_ignore_errors* in);
    virtual void children_constant(HIR_constant* in);
    virtual void children_instanceof(HIR_instanceof* in);
    virtual void children_variable(HIR_variable* in);
    virtual void children_reflection(HIR_reflection* in);
    virtual void children_pre_op(HIR_pre_op* in);
    virtual void children_post_op(HIR_post_op* in);
    virtual void children_array(HIR_array* in);
    virtual void children_array_elem(HIR_array_elem* in);
    virtual void children_method_invocation(HIR_method_invocation* in);
    virtual void children_actual_parameter(HIR_actual_parameter* in);
    virtual void children_new(HIR_new* in);
// Tokens don't have children, so these methods do nothing by default
public:
    virtual void children_class_name(Token_class_name* in);
    virtual void children_interface_name(Token_interface_name* in);
    virtual void children_method_name(Token_method_name* in);
    virtual void children_variable_name(Token_variable_name* in);
    virtual void children_directive_name(Token_directive_name* in);
    virtual void children_label_name(Token_label_name* in);
    virtual void children_int(Token_int* in);
    virtual void children_real(Token_real* in);
    virtual void children_string(Token_string* in);
    virtual void children_bool(Token_bool* in);
    virtual void children_null(Token_null* in);
    virtual void children_op(Token_op* in);
    virtual void children_cast(Token_cast* in);
    virtual void children_constant_name(Token_constant_name* in);
// Unparser support
public:
    virtual void visit_marker(char const* name, bool value);
    virtual void visit_null(char const* type_id);
    virtual void visit_null_list(char const* type_id);
    virtual void pre_list(char const* type_id, int size);
    virtual void post_list(char const* type_id, int size);
// Invoke the chain of pre-visit methods along the inheritance hierachy
// Do not override unless you know what you are doing
public:
    virtual void pre_php_script_chain(HIR_php_script* in);
    virtual void pre_class_def_chain(HIR_class_def* in);
    virtual void pre_class_mod_chain(HIR_class_mod* in);
    virtual void pre_interface_def_chain(HIR_interface_def* in);
    virtual void pre_method_chain(HIR_method* in);
    virtual void pre_signature_chain(HIR_signature* in);
    virtual void pre_method_mod_chain(HIR_method_mod* in);
    virtual void pre_formal_parameter_chain(HIR_formal_parameter* in);
    virtual void pre_type_chain(HIR_type* in);
    virtual void pre_attribute_chain(HIR_attribute* in);
    virtual void pre_attr_mod_chain(HIR_attr_mod* in);
    virtual void pre_if_chain(HIR_if* in);
    virtual void pre_while_chain(HIR_while* in);
    virtual void pre_do_chain(HIR_do* in);
    virtual void pre_for_chain(HIR_for* in);
    virtual void pre_foreach_chain(HIR_foreach* in);
    virtual void pre_switch_chain(HIR_switch* in);
    virtual void pre_switch_case_chain(HIR_switch_case* in);
    virtual void pre_break_chain(HIR_break* in);
    virtual void pre_continue_chain(HIR_continue* in);
    virtual void pre_return_chain(HIR_return* in);
    virtual void pre_static_declaration_chain(HIR_static_declaration* in);
    virtual void pre_global_chain(HIR_global* in);
    virtual void pre_declare_chain(HIR_declare* in);
    virtual void pre_directive_chain(HIR_directive* in);
    virtual void pre_try_chain(HIR_try* in);
    virtual void pre_catch_chain(HIR_catch* in);
    virtual void pre_throw_chain(HIR_throw* in);
    virtual void pre_eval_expr_chain(HIR_eval_expr* in);
    virtual void pre_nop_chain(HIR_nop* in);
    virtual void pre_branch_chain(HIR_branch* in);
    virtual void pre_goto_chain(HIR_goto* in);
    virtual void pre_label_chain(HIR_label* in);
    virtual void pre_assignment_chain(HIR_assignment* in);
    virtual void pre_op_assignment_chain(HIR_op_assignment* in);
    virtual void pre_list_assignment_chain(HIR_list_assignment* in);
    virtual void pre_nested_list_elements_chain(HIR_nested_list_elements* in);
    virtual void pre_cast_chain(HIR_cast* in);
    virtual void pre_unary_op_chain(HIR_unary_op* in);
    virtual void pre_bin_op_chain(HIR_bin_op* in);
    virtual void pre_conditional_expr_chain(HIR_conditional_expr* in);
    virtual void pre_ignore_errors_chain(HIR_ignore_errors* in);
    virtual void pre_constant_chain(HIR_constant* in);
    virtual void pre_instanceof_chain(HIR_instanceof* in);
    virtual void pre_variable_chain(HIR_variable* in);
    virtual void pre_reflection_chain(HIR_reflection* in);
    virtual void pre_pre_op_chain(HIR_pre_op* in);
    virtual void pre_post_op_chain(HIR_post_op* in);
    virtual void pre_array_chain(HIR_array* in);
    virtual void pre_array_elem_chain(HIR_array_elem* in);
    virtual void pre_method_invocation_chain(HIR_method_invocation* in);
    virtual void pre_actual_parameter_chain(HIR_actual_parameter* in);
    virtual void pre_new_chain(HIR_new* in);
    virtual void pre_class_name_chain(Token_class_name* in);
    virtual void pre_interface_name_chain(Token_interface_name* in);
    virtual void pre_method_name_chain(Token_method_name* in);
    virtual void pre_variable_name_chain(Token_variable_name* in);
    virtual void pre_directive_name_chain(Token_directive_name* in);
    virtual void pre_label_name_chain(Token_label_name* in);
    virtual void pre_int_chain(Token_int* in);
    virtual void pre_real_chain(Token_real* in);
    virtual void pre_string_chain(Token_string* in);
    virtual void pre_bool_chain(Token_bool* in);
    virtual void pre_null_chain(Token_null* in);
    virtual void pre_op_chain(Token_op* in);
    virtual void pre_cast_chain(Token_cast* in);
    virtual void pre_constant_name_chain(Token_constant_name* in);
// Invoke the chain of post-visit methods along the inheritance hierarchy
// (invoked in opposite order to the pre-chain)
// Do not override unless you know what you are doing
public:
    virtual void post_php_script_chain(HIR_php_script* in);
    virtual void post_class_def_chain(HIR_class_def* in);
    virtual void post_class_mod_chain(HIR_class_mod* in);
    virtual void post_interface_def_chain(HIR_interface_def* in);
    virtual void post_method_chain(HIR_method* in);
    virtual void post_signature_chain(HIR_signature* in);
    virtual void post_method_mod_chain(HIR_method_mod* in);
    virtual void post_formal_parameter_chain(HIR_formal_parameter* in);
    virtual void post_type_chain(HIR_type* in);
    virtual void post_attribute_chain(HIR_attribute* in);
    virtual void post_attr_mod_chain(HIR_attr_mod* in);
    virtual void post_if_chain(HIR_if* in);
    virtual void post_while_chain(HIR_while* in);
    virtual void post_do_chain(HIR_do* in);
    virtual void post_for_chain(HIR_for* in);
    virtual void post_foreach_chain(HIR_foreach* in);
    virtual void post_switch_chain(HIR_switch* in);
    virtual void post_switch_case_chain(HIR_switch_case* in);
    virtual void post_break_chain(HIR_break* in);
    virtual void post_continue_chain(HIR_continue* in);
    virtual void post_return_chain(HIR_return* in);
    virtual void post_static_declaration_chain(HIR_static_declaration* in);
    virtual void post_global_chain(HIR_global* in);
    virtual void post_declare_chain(HIR_declare* in);
    virtual void post_directive_chain(HIR_directive* in);
    virtual void post_try_chain(HIR_try* in);
    virtual void post_catch_chain(HIR_catch* in);
    virtual void post_throw_chain(HIR_throw* in);
    virtual void post_eval_expr_chain(HIR_eval_expr* in);
    virtual void post_nop_chain(HIR_nop* in);
    virtual void post_branch_chain(HIR_branch* in);
    virtual void post_goto_chain(HIR_goto* in);
    virtual void post_label_chain(HIR_label* in);
    virtual void post_assignment_chain(HIR_assignment* in);
    virtual void post_op_assignment_chain(HIR_op_assignment* in);
    virtual void post_list_assignment_chain(HIR_list_assignment* in);
    virtual void post_nested_list_elements_chain(HIR_nested_list_elements* in);
    virtual void post_cast_chain(HIR_cast* in);
    virtual void post_unary_op_chain(HIR_unary_op* in);
    virtual void post_bin_op_chain(HIR_bin_op* in);
    virtual void post_conditional_expr_chain(HIR_conditional_expr* in);
    virtual void post_ignore_errors_chain(HIR_ignore_errors* in);
    virtual void post_constant_chain(HIR_constant* in);
    virtual void post_instanceof_chain(HIR_instanceof* in);
    virtual void post_variable_chain(HIR_variable* in);
    virtual void post_reflection_chain(HIR_reflection* in);
    virtual void post_pre_op_chain(HIR_pre_op* in);
    virtual void post_post_op_chain(HIR_post_op* in);
    virtual void post_array_chain(HIR_array* in);
    virtual void post_array_elem_chain(HIR_array_elem* in);
    virtual void post_method_invocation_chain(HIR_method_invocation* in);
    virtual void post_actual_parameter_chain(HIR_actual_parameter* in);
    virtual void post_new_chain(HIR_new* in);
    virtual void post_class_name_chain(Token_class_name* in);
    virtual void post_interface_name_chain(Token_interface_name* in);
    virtual void post_method_name_chain(Token_method_name* in);
    virtual void post_variable_name_chain(Token_variable_name* in);
    virtual void post_directive_name_chain(Token_directive_name* in);
    virtual void post_label_name_chain(Token_label_name* in);
    virtual void post_int_chain(Token_int* in);
    virtual void post_real_chain(Token_real* in);
    virtual void post_string_chain(Token_string* in);
    virtual void post_bool_chain(Token_bool* in);
    virtual void post_null_chain(Token_null* in);
    virtual void post_op_chain(Token_op* in);
    virtual void post_cast_chain(Token_cast* in);
    virtual void post_constant_name_chain(Token_constant_name* in);
// Call the pre-chain, visit children and post-chain in order
// Do not override unless you know what you are doing
public:
    virtual void visit_statement_list(List<HIR_statement*>* in);
    virtual void visit_statement(HIR_statement* in);
    virtual void visit_class_mod(HIR_class_mod* in);
    virtual void visit_class_name(Token_class_name* in);
    virtual void visit_interface_name_list(List<Token_interface_name*>* in);
    virtual void visit_member_list(List<HIR_member*>* in);
    virtual void visit_member(HIR_member* in);
    virtual void visit_interface_name(Token_interface_name* in);
    virtual void visit_signature(HIR_signature* in);
    virtual void visit_method_mod(HIR_method_mod* in);
    virtual void visit_method_name(Token_method_name* in);
    virtual void visit_formal_parameter_list(List<HIR_formal_parameter*>* in);
    virtual void visit_formal_parameter(HIR_formal_parameter* in);
    virtual void visit_type(HIR_type* in);
    virtual void visit_variable_name(Token_variable_name* in);
    virtual void visit_expr(HIR_expr* in);
    virtual void visit_attr_mod(HIR_attr_mod* in);
    virtual void visit_variable(HIR_variable* in);
    virtual void visit_switch_case_list(List<HIR_switch_case*>* in);
    virtual void visit_switch_case(HIR_switch_case* in);
    virtual void visit_variable_name(HIR_variable_name* in);
    virtual void visit_directive_list(List<HIR_directive*>* in);
    virtual void visit_directive(HIR_directive* in);
    virtual void visit_directive_name(Token_directive_name* in);
    virtual void visit_catch_list(List<HIR_catch*>* in);
    virtual void visit_catch(HIR_catch* in);
    virtual void visit_label_name(Token_label_name* in);
    virtual void visit_op(Token_op* in);
    virtual void visit_list_element_list(List<HIR_list_element*>* in);
    virtual void visit_list_element(HIR_list_element* in);
    virtual void visit_cast(Token_cast* in);
    virtual void visit_constant_name(Token_constant_name* in);
    virtual void visit_class_name(HIR_class_name* in);
    virtual void visit_target(HIR_target* in);
    virtual void visit_expr_list(List<HIR_expr*>* in);
    virtual void visit_array_elem_list(List<HIR_array_elem*>* in);
    virtual void visit_array_elem(HIR_array_elem* in);
    virtual void visit_method_name(HIR_method_name* in);
    virtual void visit_actual_parameter_list(List<HIR_actual_parameter*>* in);
    virtual void visit_actual_parameter(HIR_actual_parameter* in);
    virtual void visit_php_script(HIR_php_script* in);
// Invoke the right pre-chain (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void pre_statement_chain(HIR_statement* in);
    virtual void pre_member_chain(HIR_member* in);
    virtual void pre_expr_chain(HIR_expr* in);
    virtual void pre_variable_name_chain(HIR_variable_name* in);
    virtual void pre_list_element_chain(HIR_list_element* in);
    virtual void pre_class_name_chain(HIR_class_name* in);
    virtual void pre_target_chain(HIR_target* in);
    virtual void pre_method_name_chain(HIR_method_name* in);
// Invoke the right post-chain (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void post_statement_chain(HIR_statement* in);
    virtual void post_member_chain(HIR_member* in);
    virtual void post_expr_chain(HIR_expr* in);
    virtual void post_variable_name_chain(HIR_variable_name* in);
    virtual void post_list_element_chain(HIR_list_element* in);
    virtual void post_class_name_chain(HIR_class_name* in);
    virtual void post_target_chain(HIR_target* in);
    virtual void post_method_name_chain(HIR_method_name* in);
// Invoke the right visit-children (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void children_statement(HIR_statement* in);
    virtual void children_member(HIR_member* in);
    virtual void children_expr(HIR_expr* in);
    virtual void children_variable_name(HIR_variable_name* in);
    virtual void children_list_element(HIR_list_element* in);
    virtual void children_class_name(HIR_class_name* in);
    virtual void children_target(HIR_target* in);
    virtual void children_method_name(HIR_method_name* in);
};
}


#endif
