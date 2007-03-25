#ifndef _AST_TRANSFORM_H_
#define _AST_TRANSFORM_H_

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


#include "AST.h"

class AST_transform
{
public:
    virtual ~AST_transform();
// The pre-transform gets called before the children of the node are transformed
public:
    virtual AST_php_script* pre_php_script(AST_php_script* in);
    virtual void pre_interface_def(AST_interface_def* in, List<AST_interface_def*>* out);
    virtual void pre_class_def(AST_class_def* in, List<AST_class_def*>* out);
    virtual AST_class_mod* pre_class_mod(AST_class_mod* in);
    virtual void pre_method(AST_method* in, List<AST_member*>* out);
    virtual AST_signature* pre_signature(AST_signature* in);
    virtual AST_method_mod* pre_method_mod(AST_method_mod* in);
    virtual void pre_formal_parameter(AST_formal_parameter* in, List<AST_formal_parameter*>* out);
    virtual AST_type* pre_type(AST_type* in);
    virtual void pre_attribute(AST_attribute* in, List<AST_member*>* out);
    virtual AST_attr_mod* pre_attr_mod(AST_attr_mod* in);
    virtual void pre_if(AST_if* in, List<AST_statement*>* out);
    virtual void pre_while(AST_while* in, List<AST_statement*>* out);
    virtual void pre_do(AST_do* in, List<AST_statement*>* out);
    virtual void pre_for(AST_for* in, List<AST_statement*>* out);
    virtual void pre_foreach(AST_foreach* in, List<AST_statement*>* out);
    virtual void pre_switch(AST_switch* in, List<AST_statement*>* out);
    virtual void pre_switch_case(AST_switch_case* in, List<AST_switch_case*>* out);
    virtual void pre_break(AST_break* in, List<AST_statement*>* out);
    virtual void pre_continue(AST_continue* in, List<AST_statement*>* out);
    virtual void pre_return(AST_return* in, List<AST_statement*>* out);
    virtual void pre_static_declaration(AST_static_declaration* in, List<AST_statement*>* out);
    virtual void pre_unset(AST_unset* in, List<AST_statement*>* out);
    virtual void pre_declare(AST_declare* in, List<AST_statement*>* out);
    virtual void pre_directive(AST_directive* in, List<AST_directive*>* out);
    virtual void pre_try(AST_try* in, List<AST_statement*>* out);
    virtual void pre_catch(AST_catch* in, List<AST_catch*>* out);
    virtual void pre_throw(AST_throw* in, List<AST_statement*>* out);
    virtual void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);
    virtual void pre_nop(AST_nop* in, List<AST_statement*>* out);
    virtual AST_expr* pre_assignment(AST_assignment* in);
    virtual AST_expr* pre_list_assignment(AST_list_assignment* in);
    virtual AST_list_elements* pre_list_elements(AST_list_elements* in);
    virtual AST_expr* pre_cast(AST_cast* in);
    virtual AST_expr* pre_unary_op(AST_unary_op* in);
    virtual AST_expr* pre_bin_op(AST_bin_op* in);
    virtual AST_expr* pre_conditional_expr(AST_conditional_expr* in);
    virtual AST_expr* pre_ignore_errors(AST_ignore_errors* in);
    virtual AST_expr* pre_constant(AST_constant* in);
    virtual AST_expr* pre_instanceof(AST_instanceof* in);
    virtual AST_variable* pre_variable(AST_variable* in);
    virtual AST_reflection* pre_reflection(AST_reflection* in);
    virtual AST_expr* pre_pre_op(AST_pre_op* in);
    virtual AST_expr* pre_post_op(AST_post_op* in);
    virtual AST_expr* pre_array(AST_array* in);
    virtual void pre_array_elem(AST_array_elem* in, List<AST_array_elem*>* out);
    virtual AST_expr* pre_method_invocation(AST_method_invocation* in);
    virtual void pre_actual_parameter(AST_actual_parameter* in, List<AST_actual_parameter*>* out);
    virtual AST_expr* pre_new(AST_new* in);
    virtual AST_expr* pre_clone(AST_clone* in);
    virtual Token_interface_name* pre_interface_name(Token_interface_name* in);
    virtual Token_class_name* pre_class_name(Token_class_name* in);
    virtual Token_method_name* pre_method_name(Token_method_name* in);
    virtual Token_variable_name* pre_variable_name(Token_variable_name* in);
    virtual Token_directive_name* pre_directive_name(Token_directive_name* in);
    virtual AST_expr* pre_int(Token_int* in);
    virtual AST_expr* pre_real(Token_real* in);
    virtual AST_expr* pre_string(Token_string* in);
    virtual AST_expr* pre_bool(Token_bool* in);
    virtual AST_expr* pre_null(Token_null* in);
    virtual Token_cast* pre_cast(Token_cast* in);
    virtual Token_op* pre_op(Token_op* in);
    virtual Token_constant_name* pre_constant_name(Token_constant_name* in);
// The post-transform gets called after the children of the node have been transformed
public:
    virtual AST_php_script* post_php_script(AST_php_script* in);
    virtual void post_interface_def(AST_interface_def* in, List<AST_interface_def*>* out);
    virtual void post_class_def(AST_class_def* in, List<AST_class_def*>* out);
    virtual AST_class_mod* post_class_mod(AST_class_mod* in);
    virtual void post_method(AST_method* in, List<AST_member*>* out);
    virtual AST_signature* post_signature(AST_signature* in);
    virtual AST_method_mod* post_method_mod(AST_method_mod* in);
    virtual void post_formal_parameter(AST_formal_parameter* in, List<AST_formal_parameter*>* out);
    virtual AST_type* post_type(AST_type* in);
    virtual void post_attribute(AST_attribute* in, List<AST_member*>* out);
    virtual AST_attr_mod* post_attr_mod(AST_attr_mod* in);
    virtual void post_if(AST_if* in, List<AST_statement*>* out);
    virtual void post_while(AST_while* in, List<AST_statement*>* out);
    virtual void post_do(AST_do* in, List<AST_statement*>* out);
    virtual void post_for(AST_for* in, List<AST_statement*>* out);
    virtual void post_foreach(AST_foreach* in, List<AST_statement*>* out);
    virtual void post_switch(AST_switch* in, List<AST_statement*>* out);
    virtual void post_switch_case(AST_switch_case* in, List<AST_switch_case*>* out);
    virtual void post_break(AST_break* in, List<AST_statement*>* out);
    virtual void post_continue(AST_continue* in, List<AST_statement*>* out);
    virtual void post_return(AST_return* in, List<AST_statement*>* out);
    virtual void post_static_declaration(AST_static_declaration* in, List<AST_statement*>* out);
    virtual void post_unset(AST_unset* in, List<AST_statement*>* out);
    virtual void post_declare(AST_declare* in, List<AST_statement*>* out);
    virtual void post_directive(AST_directive* in, List<AST_directive*>* out);
    virtual void post_try(AST_try* in, List<AST_statement*>* out);
    virtual void post_catch(AST_catch* in, List<AST_catch*>* out);
    virtual void post_throw(AST_throw* in, List<AST_statement*>* out);
    virtual void post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);
    virtual void post_nop(AST_nop* in, List<AST_statement*>* out);
    virtual AST_expr* post_assignment(AST_assignment* in);
    virtual AST_expr* post_list_assignment(AST_list_assignment* in);
    virtual AST_list_elements* post_list_elements(AST_list_elements* in);
    virtual AST_expr* post_cast(AST_cast* in);
    virtual AST_expr* post_unary_op(AST_unary_op* in);
    virtual AST_expr* post_bin_op(AST_bin_op* in);
    virtual AST_expr* post_conditional_expr(AST_conditional_expr* in);
    virtual AST_expr* post_ignore_errors(AST_ignore_errors* in);
    virtual AST_expr* post_constant(AST_constant* in);
    virtual AST_expr* post_instanceof(AST_instanceof* in);
    virtual AST_variable* post_variable(AST_variable* in);
    virtual AST_reflection* post_reflection(AST_reflection* in);
    virtual AST_expr* post_pre_op(AST_pre_op* in);
    virtual AST_expr* post_post_op(AST_post_op* in);
    virtual AST_expr* post_array(AST_array* in);
    virtual void post_array_elem(AST_array_elem* in, List<AST_array_elem*>* out);
    virtual AST_expr* post_method_invocation(AST_method_invocation* in);
    virtual void post_actual_parameter(AST_actual_parameter* in, List<AST_actual_parameter*>* out);
    virtual AST_expr* post_new(AST_new* in);
    virtual AST_expr* post_clone(AST_clone* in);
    virtual Token_interface_name* post_interface_name(Token_interface_name* in);
    virtual Token_class_name* post_class_name(Token_class_name* in);
    virtual Token_method_name* post_method_name(Token_method_name* in);
    virtual Token_variable_name* post_variable_name(Token_variable_name* in);
    virtual Token_directive_name* post_directive_name(Token_directive_name* in);
    virtual AST_expr* post_int(Token_int* in);
    virtual AST_expr* post_real(Token_real* in);
    virtual AST_expr* post_string(Token_string* in);
    virtual AST_expr* post_bool(Token_bool* in);
    virtual AST_expr* post_null(Token_null* in);
    virtual Token_cast* post_cast(Token_cast* in);
    virtual Token_op* post_op(Token_op* in);
    virtual Token_constant_name* post_constant_name(Token_constant_name* in);
// Transform the children of the node
public:
    virtual void children_php_script(AST_php_script* in);
    virtual void children_interface_def(AST_interface_def* in);
    virtual void children_class_def(AST_class_def* in);
    virtual void children_class_mod(AST_class_mod* in);
    virtual void children_method(AST_method* in);
    virtual void children_signature(AST_signature* in);
    virtual void children_method_mod(AST_method_mod* in);
    virtual void children_formal_parameter(AST_formal_parameter* in);
    virtual void children_type(AST_type* in);
    virtual void children_attribute(AST_attribute* in);
    virtual void children_attr_mod(AST_attr_mod* in);
    virtual void children_if(AST_if* in);
    virtual void children_while(AST_while* in);
    virtual void children_do(AST_do* in);
    virtual void children_for(AST_for* in);
    virtual void children_foreach(AST_foreach* in);
    virtual void children_switch(AST_switch* in);
    virtual void children_switch_case(AST_switch_case* in);
    virtual void children_break(AST_break* in);
    virtual void children_continue(AST_continue* in);
    virtual void children_return(AST_return* in);
    virtual void children_static_declaration(AST_static_declaration* in);
    virtual void children_unset(AST_unset* in);
    virtual void children_declare(AST_declare* in);
    virtual void children_directive(AST_directive* in);
    virtual void children_try(AST_try* in);
    virtual void children_catch(AST_catch* in);
    virtual void children_throw(AST_throw* in);
    virtual void children_eval_expr(AST_eval_expr* in);
    virtual void children_nop(AST_nop* in);
    virtual void children_assignment(AST_assignment* in);
    virtual void children_list_assignment(AST_list_assignment* in);
    virtual void children_list_elements(AST_list_elements* in);
    virtual void children_cast(AST_cast* in);
    virtual void children_unary_op(AST_unary_op* in);
    virtual void children_bin_op(AST_bin_op* in);
    virtual void children_conditional_expr(AST_conditional_expr* in);
    virtual void children_ignore_errors(AST_ignore_errors* in);
    virtual void children_constant(AST_constant* in);
    virtual void children_instanceof(AST_instanceof* in);
    virtual void children_variable(AST_variable* in);
    virtual void children_reflection(AST_reflection* in);
    virtual void children_pre_op(AST_pre_op* in);
    virtual void children_post_op(AST_post_op* in);
    virtual void children_array(AST_array* in);
    virtual void children_array_elem(AST_array_elem* in);
    virtual void children_method_invocation(AST_method_invocation* in);
    virtual void children_actual_parameter(AST_actual_parameter* in);
    virtual void children_new(AST_new* in);
    virtual void children_clone(AST_clone* in);
// Tokens don't have children, so these methods do nothing by default
public:
    virtual void children_interface_name(Token_interface_name* in);
    virtual void children_class_name(Token_class_name* in);
    virtual void children_method_name(Token_method_name* in);
    virtual void children_variable_name(Token_variable_name* in);
    virtual void children_directive_name(Token_directive_name* in);
    virtual void children_int(Token_int* in);
    virtual void children_real(Token_real* in);
    virtual void children_string(Token_string* in);
    virtual void children_bool(Token_bool* in);
    virtual void children_null(Token_null* in);
    virtual void children_cast(Token_cast* in);
    virtual void children_op(Token_op* in);
    virtual void children_constant_name(Token_constant_name* in);
// Call the pre-transform, transform-children post-transform methods in order
// Do not override unless you know what you are doing
public:
    virtual List<AST_interface_def*>* transform_interface_def_list(List<AST_interface_def*>* in);
    virtual List<AST_interface_def*>* transform_interface_def(AST_interface_def* in);
    virtual List<AST_class_def*>* transform_class_def_list(List<AST_class_def*>* in);
    virtual List<AST_class_def*>* transform_class_def(AST_class_def* in);
    virtual Token_interface_name* transform_interface_name(Token_interface_name* in);
    virtual List<Token_interface_name*>* transform_interface_name_list(List<Token_interface_name*>* in);
    virtual List<AST_member*>* transform_member_list(List<AST_member*>* in);
    virtual List<AST_member*>* transform_member(AST_member* in);
    virtual AST_class_mod* transform_class_mod(AST_class_mod* in);
    virtual Token_class_name* transform_class_name(Token_class_name* in);
    virtual AST_signature* transform_signature(AST_signature* in);
    virtual List<AST_statement*>* transform_statement_list(List<AST_statement*>* in);
    virtual List<AST_statement*>* transform_statement(AST_statement* in);
    virtual AST_method_mod* transform_method_mod(AST_method_mod* in);
    virtual Token_method_name* transform_method_name(Token_method_name* in);
    virtual List<AST_formal_parameter*>* transform_formal_parameter_list(List<AST_formal_parameter*>* in);
    virtual List<AST_formal_parameter*>* transform_formal_parameter(AST_formal_parameter* in);
    virtual AST_type* transform_type(AST_type* in);
    virtual Token_variable_name* transform_variable_name(Token_variable_name* in);
    virtual AST_expr* transform_expr(AST_expr* in);
    virtual AST_attr_mod* transform_attr_mod(AST_attr_mod* in);
    virtual AST_variable* transform_variable(AST_variable* in);
    virtual List<AST_switch_case*>* transform_switch_case_list(List<AST_switch_case*>* in);
    virtual List<AST_switch_case*>* transform_switch_case(AST_switch_case* in);
    virtual List<AST_directive*>* transform_directive_list(List<AST_directive*>* in);
    virtual List<AST_directive*>* transform_directive(AST_directive* in);
    virtual Token_directive_name* transform_directive_name(Token_directive_name* in);
    virtual List<AST_catch*>* transform_catch_list(List<AST_catch*>* in);
    virtual List<AST_catch*>* transform_catch(AST_catch* in);
    virtual AST_list_elements* transform_list_elements(AST_list_elements* in);
    virtual List<AST_list_element*>* transform_list_element_list(List<AST_list_element*>* in);
    virtual List<AST_list_element*>* transform_list_element(AST_list_element* in);
    virtual Token_cast* transform_cast(Token_cast* in);
    virtual Token_op* transform_op(Token_op* in);
    virtual Token_constant_name* transform_constant_name(Token_constant_name* in);
    virtual AST_class_name* transform_class_name(AST_class_name* in);
    virtual AST_target* transform_target(AST_target* in);
    virtual AST_variable_name* transform_variable_name(AST_variable_name* in);
    virtual List<AST_expr*>* transform_expr_list(List<AST_expr*>* in);
    virtual List<AST_array_elem*>* transform_array_elem_list(List<AST_array_elem*>* in);
    virtual List<AST_array_elem*>* transform_array_elem(AST_array_elem* in);
    virtual AST_method_name* transform_method_name(AST_method_name* in);
    virtual List<AST_actual_parameter*>* transform_actual_parameter_list(List<AST_actual_parameter*>* in);
    virtual List<AST_actual_parameter*>* transform_actual_parameter(AST_actual_parameter* in);
    virtual AST_php_script* transform_php_script(AST_php_script* in);
// Invoke the right pre-transform (manual dispatching)
// Do not override unless you know what you are doing
protected:
    virtual void pre_member(AST_member* in, List<AST_member*>* out);
    virtual void pre_statement(AST_statement* in, List<AST_statement*>* out);
    virtual AST_expr* pre_expr(AST_expr* in);
    virtual void pre_list_element(AST_list_element* in, List<AST_list_element*>* out);
    virtual AST_class_name* pre_class_name(AST_class_name* in);
    virtual AST_target* pre_target(AST_target* in);
    virtual AST_variable_name* pre_variable_name(AST_variable_name* in);
    virtual AST_method_name* pre_method_name(AST_method_name* in);
// Invoke the right post-transform (manual dispatching)
// Do not override unless you know what you are doing
protected:
    virtual void post_member(AST_member* in, List<AST_member*>* out);
    virtual void post_statement(AST_statement* in, List<AST_statement*>* out);
    virtual AST_expr* post_expr(AST_expr* in);
    virtual void post_list_element(AST_list_element* in, List<AST_list_element*>* out);
    virtual AST_class_name* post_class_name(AST_class_name* in);
    virtual AST_target* post_target(AST_target* in);
    virtual AST_variable_name* post_variable_name(AST_variable_name* in);
    virtual AST_method_name* post_method_name(AST_method_name* in);
// Invoke the right transform-children (manual dispatching)
// Do not override unless you what you are doing
protected:
    virtual void children_member(AST_member* in);
    virtual void children_statement(AST_statement* in);
    virtual void children_expr(AST_expr* in);
    virtual void children_list_element(AST_list_element* in);
    virtual void children_class_name(AST_class_name* in);
    virtual void children_target(AST_target* in);
    virtual void children_variable_name(AST_variable_name* in);
    virtual void children_method_name(AST_method_name* in);
};


#endif
