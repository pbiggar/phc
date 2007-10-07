#ifndef _HIR_TRANSFORM_H_
#define _HIR_TRANSFORM_H_

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
class HIR_transform
{
public:
    virtual ~HIR_transform();
// Invoked before the children are transformed
public:
    virtual HIR_php_script* pre_php_script(HIR_php_script* in);
    virtual void pre_class_def(HIR_class_def* in, List<HIR_statement*>* out);
    virtual HIR_class_mod* pre_class_mod(HIR_class_mod* in);
    virtual void pre_interface_def(HIR_interface_def* in, List<HIR_statement*>* out);
    virtual void pre_method(HIR_method* in, List<HIR_method*>* out);
    virtual HIR_signature* pre_signature(HIR_signature* in);
    virtual HIR_method_mod* pre_method_mod(HIR_method_mod* in);
    virtual void pre_formal_parameter(HIR_formal_parameter* in, List<HIR_formal_parameter*>* out);
    virtual HIR_type* pre_type(HIR_type* in);
    virtual void pre_attribute(HIR_attribute* in, List<HIR_member*>* out);
    virtual HIR_attr_mod* pre_attr_mod(HIR_attr_mod* in);
    virtual void pre_return(HIR_return* in, List<HIR_statement*>* out);
    virtual void pre_static_declaration(HIR_static_declaration* in, List<HIR_statement*>* out);
    virtual void pre_global(HIR_global* in, List<HIR_statement*>* out);
    virtual void pre_try(HIR_try* in, List<HIR_statement*>* out);
    virtual void pre_catch(HIR_catch* in, List<HIR_catch*>* out);
    virtual void pre_throw(HIR_throw* in, List<HIR_statement*>* out);
    virtual void pre_eval_expr(HIR_eval_expr* in, List<HIR_statement*>* out);
    virtual void pre_branch(HIR_branch* in, List<HIR_statement*>* out);
    virtual void pre_goto(HIR_goto* in, List<HIR_statement*>* out);
    virtual void pre_label(HIR_label* in, List<HIR_statement*>* out);
    virtual HIR_expr* pre_assignment(HIR_assignment* in);
    virtual HIR_expr* pre_cast(HIR_cast* in);
    virtual HIR_expr* pre_unary_op(HIR_unary_op* in);
    virtual HIR_expr* pre_bin_op(HIR_bin_op* in);
    virtual HIR_expr* pre_constant(HIR_constant* in);
    virtual HIR_expr* pre_instanceof(HIR_instanceof* in);
    virtual HIR_variable* pre_variable(HIR_variable* in);
    virtual HIR_reflection* pre_reflection(HIR_reflection* in);
    virtual HIR_expr* pre_pre_op(HIR_pre_op* in);
    virtual HIR_expr* pre_post_op(HIR_post_op* in);
    virtual HIR_expr* pre_array(HIR_array* in);
    virtual void pre_array_elem(HIR_array_elem* in, List<HIR_array_elem*>* out);
    virtual HIR_expr* pre_method_invocation(HIR_method_invocation* in);
    virtual void pre_actual_parameter(HIR_actual_parameter* in, List<HIR_actual_parameter*>* out);
    virtual HIR_expr* pre_new(HIR_new* in);
    virtual Token_class_name* pre_class_name(Token_class_name* in);
    virtual Token_interface_name* pre_interface_name(Token_interface_name* in);
    virtual Token_method_name* pre_method_name(Token_method_name* in);
    virtual Token_variable_name* pre_variable_name(Token_variable_name* in);
    virtual Token_label_name* pre_label_name(Token_label_name* in);
    virtual HIR_expr* pre_int(Token_int* in);
    virtual HIR_expr* pre_real(Token_real* in);
    virtual HIR_expr* pre_string(Token_string* in);
    virtual HIR_expr* pre_bool(Token_bool* in);
    virtual HIR_expr* pre_null(Token_null* in);
    virtual Token_cast* pre_cast(Token_cast* in);
    virtual Token_op* pre_op(Token_op* in);
    virtual Token_constant_name* pre_constant_name(Token_constant_name* in);
// Invoked after the children have been transformed
public:
    virtual HIR_php_script* post_php_script(HIR_php_script* in);
    virtual void post_class_def(HIR_class_def* in, List<HIR_statement*>* out);
    virtual HIR_class_mod* post_class_mod(HIR_class_mod* in);
    virtual void post_interface_def(HIR_interface_def* in, List<HIR_statement*>* out);
    virtual void post_method(HIR_method* in, List<HIR_method*>* out);
    virtual HIR_signature* post_signature(HIR_signature* in);
    virtual HIR_method_mod* post_method_mod(HIR_method_mod* in);
    virtual void post_formal_parameter(HIR_formal_parameter* in, List<HIR_formal_parameter*>* out);
    virtual HIR_type* post_type(HIR_type* in);
    virtual void post_attribute(HIR_attribute* in, List<HIR_member*>* out);
    virtual HIR_attr_mod* post_attr_mod(HIR_attr_mod* in);
    virtual void post_return(HIR_return* in, List<HIR_statement*>* out);
    virtual void post_static_declaration(HIR_static_declaration* in, List<HIR_statement*>* out);
    virtual void post_global(HIR_global* in, List<HIR_statement*>* out);
    virtual void post_try(HIR_try* in, List<HIR_statement*>* out);
    virtual void post_catch(HIR_catch* in, List<HIR_catch*>* out);
    virtual void post_throw(HIR_throw* in, List<HIR_statement*>* out);
    virtual void post_eval_expr(HIR_eval_expr* in, List<HIR_statement*>* out);
    virtual void post_branch(HIR_branch* in, List<HIR_statement*>* out);
    virtual void post_goto(HIR_goto* in, List<HIR_statement*>* out);
    virtual void post_label(HIR_label* in, List<HIR_statement*>* out);
    virtual HIR_expr* post_assignment(HIR_assignment* in);
    virtual HIR_expr* post_cast(HIR_cast* in);
    virtual HIR_expr* post_unary_op(HIR_unary_op* in);
    virtual HIR_expr* post_bin_op(HIR_bin_op* in);
    virtual HIR_expr* post_constant(HIR_constant* in);
    virtual HIR_expr* post_instanceof(HIR_instanceof* in);
    virtual HIR_variable* post_variable(HIR_variable* in);
    virtual HIR_reflection* post_reflection(HIR_reflection* in);
    virtual HIR_expr* post_pre_op(HIR_pre_op* in);
    virtual HIR_expr* post_post_op(HIR_post_op* in);
    virtual HIR_expr* post_array(HIR_array* in);
    virtual void post_array_elem(HIR_array_elem* in, List<HIR_array_elem*>* out);
    virtual HIR_expr* post_method_invocation(HIR_method_invocation* in);
    virtual void post_actual_parameter(HIR_actual_parameter* in, List<HIR_actual_parameter*>* out);
    virtual HIR_expr* post_new(HIR_new* in);
    virtual Token_class_name* post_class_name(Token_class_name* in);
    virtual Token_interface_name* post_interface_name(Token_interface_name* in);
    virtual Token_method_name* post_method_name(Token_method_name* in);
    virtual Token_variable_name* post_variable_name(Token_variable_name* in);
    virtual Token_label_name* post_label_name(Token_label_name* in);
    virtual HIR_expr* post_int(Token_int* in);
    virtual HIR_expr* post_real(Token_real* in);
    virtual HIR_expr* post_string(Token_string* in);
    virtual HIR_expr* post_bool(Token_bool* in);
    virtual HIR_expr* post_null(Token_null* in);
    virtual Token_cast* post_cast(Token_cast* in);
    virtual Token_op* post_op(Token_op* in);
    virtual Token_constant_name* post_constant_name(Token_constant_name* in);
// Transform the children of the node
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
    virtual void children_return(HIR_return* in);
    virtual void children_static_declaration(HIR_static_declaration* in);
    virtual void children_global(HIR_global* in);
    virtual void children_try(HIR_try* in);
    virtual void children_catch(HIR_catch* in);
    virtual void children_throw(HIR_throw* in);
    virtual void children_eval_expr(HIR_eval_expr* in);
    virtual void children_branch(HIR_branch* in);
    virtual void children_goto(HIR_goto* in);
    virtual void children_label(HIR_label* in);
    virtual void children_assignment(HIR_assignment* in);
    virtual void children_cast(HIR_cast* in);
    virtual void children_unary_op(HIR_unary_op* in);
    virtual void children_bin_op(HIR_bin_op* in);
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
    virtual void children_label_name(Token_label_name* in);
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
    virtual List<HIR_statement*>* transform_statement_list(List<HIR_statement*>* in);
    virtual List<HIR_statement*>* transform_statement(HIR_statement* in);
    virtual HIR_class_mod* transform_class_mod(HIR_class_mod* in);
    virtual Token_class_name* transform_class_name(Token_class_name* in);
    virtual List<Token_interface_name*>* transform_interface_name_list(List<Token_interface_name*>* in);
    virtual List<HIR_member*>* transform_member_list(List<HIR_member*>* in);
    virtual List<HIR_member*>* transform_member(HIR_member* in);
    virtual Token_interface_name* transform_interface_name(Token_interface_name* in);
    virtual HIR_signature* transform_signature(HIR_signature* in);
    virtual HIR_method_mod* transform_method_mod(HIR_method_mod* in);
    virtual Token_method_name* transform_method_name(Token_method_name* in);
    virtual List<HIR_formal_parameter*>* transform_formal_parameter_list(List<HIR_formal_parameter*>* in);
    virtual List<HIR_formal_parameter*>* transform_formal_parameter(HIR_formal_parameter* in);
    virtual HIR_type* transform_type(HIR_type* in);
    virtual Token_variable_name* transform_variable_name(Token_variable_name* in);
    virtual HIR_expr* transform_expr(HIR_expr* in);
    virtual HIR_attr_mod* transform_attr_mod(HIR_attr_mod* in);
    virtual HIR_variable_name* transform_variable_name(HIR_variable_name* in);
    virtual List<HIR_catch*>* transform_catch_list(List<HIR_catch*>* in);
    virtual List<HIR_catch*>* transform_catch(HIR_catch* in);
    virtual Token_label_name* transform_label_name(Token_label_name* in);
    virtual HIR_variable* transform_variable(HIR_variable* in);
    virtual Token_cast* transform_cast(Token_cast* in);
    virtual Token_op* transform_op(Token_op* in);
    virtual Token_constant_name* transform_constant_name(Token_constant_name* in);
    virtual HIR_class_name* transform_class_name(HIR_class_name* in);
    virtual HIR_target* transform_target(HIR_target* in);
    virtual List<HIR_expr*>* transform_expr_list(List<HIR_expr*>* in);
    virtual List<HIR_array_elem*>* transform_array_elem_list(List<HIR_array_elem*>* in);
    virtual List<HIR_array_elem*>* transform_array_elem(HIR_array_elem* in);
    virtual HIR_method_name* transform_method_name(HIR_method_name* in);
    virtual List<HIR_actual_parameter*>* transform_actual_parameter_list(List<HIR_actual_parameter*>* in);
    virtual List<HIR_actual_parameter*>* transform_actual_parameter(HIR_actual_parameter* in);
    virtual HIR_php_script* transform_php_script(HIR_php_script* in);
// Invoke the right pre-transform (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void pre_statement(HIR_statement* in, List<HIR_statement*>* out);
    virtual void pre_member(HIR_member* in, List<HIR_member*>* out);
    virtual HIR_expr* pre_expr(HIR_expr* in);
    virtual HIR_variable_name* pre_variable_name(HIR_variable_name* in);
    virtual HIR_class_name* pre_class_name(HIR_class_name* in);
    virtual HIR_target* pre_target(HIR_target* in);
    virtual HIR_method_name* pre_method_name(HIR_method_name* in);
// Invoke the right post-transform (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void post_statement(HIR_statement* in, List<HIR_statement*>* out);
    virtual void post_member(HIR_member* in, List<HIR_member*>* out);
    virtual HIR_expr* post_expr(HIR_expr* in);
    virtual HIR_variable_name* post_variable_name(HIR_variable_name* in);
    virtual HIR_class_name* post_class_name(HIR_class_name* in);
    virtual HIR_target* post_target(HIR_target* in);
    virtual HIR_method_name* post_method_name(HIR_method_name* in);
// Invoke the right transform-children (manual dispatching)
// Do not override unless you what you are doing
public:
    virtual void children_statement(HIR_statement* in);
    virtual void children_member(HIR_member* in);
    virtual void children_expr(HIR_expr* in);
    virtual void children_variable_name(HIR_variable_name* in);
    virtual void children_class_name(HIR_class_name* in);
    virtual void children_target(HIR_target* in);
    virtual void children_method_name(HIR_method_name* in);
};
}


#endif
