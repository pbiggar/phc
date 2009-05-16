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
#include "process_ir/IR.h"
#include "process_ir/Foreach.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "HIR.h"

namespace HIR{
class Transform
{
public:
    virtual ~Transform();
/* Invoked before the children are transformed */
public:
    virtual PHP_script* pre_php_script(PHP_script* in);
    virtual void pre_class_def(Class_def* in, Statement_list* out);
    virtual Class_mod* pre_class_mod(Class_mod* in);
    virtual void pre_interface_def(Interface_def* in, Statement_list* out);
    virtual void pre_method(Method* in, Method_list* out);
    virtual Signature* pre_signature(Signature* in);
    virtual Method_mod* pre_method_mod(Method_mod* in);
    virtual void pre_formal_parameter(Formal_parameter* in, Formal_parameter_list* out);
    virtual Type* pre_type(Type* in);
    virtual void pre_attribute(Attribute* in, Member_list* out);
    virtual Attr_mod* pre_attr_mod(Attr_mod* in);
    virtual Name_with_default* pre_name_with_default(Name_with_default* in);
    virtual void pre_if(If* in, Statement_list* out);
    virtual void pre_loop(Loop* in, Statement_list* out);
    virtual void pre_foreach(Foreach* in, Statement_list* out);
    virtual void pre_break(Break* in, Statement_list* out);
    virtual void pre_continue(Continue* in, Statement_list* out);
    virtual void pre_return(Return* in, Statement_list* out);
    virtual void pre_static_declaration(Static_declaration* in, Statement_list* out);
    virtual void pre_global(Global* in, Statement_list* out);
    virtual void pre_try(Try* in, Statement_list* out);
    virtual void pre_catch(Catch* in, Catch_list* out);
    virtual void pre_throw(Throw* in, Statement_list* out);
    virtual void pre_assign_var(Assign_var* in, Statement_list* out);
    virtual void pre_assign_field(Assign_field* in, Statement_list* out);
    virtual void pre_assign_array(Assign_array* in, Statement_list* out);
    virtual void pre_assign_var_var(Assign_var_var* in, Statement_list* out);
    virtual void pre_assign_next(Assign_next* in, Statement_list* out);
    virtual void pre_pre_op(Pre_op* in, Statement_list* out);
    virtual void pre_eval_expr(Eval_expr* in, Statement_list* out);
    virtual Expr* pre_field_access(Field_access* in);
    virtual Expr* pre_array_access(Array_access* in);
    virtual Expr* pre_array_next(Array_next* in);
    virtual Expr* pre_cast(Cast* in);
    virtual Expr* pre_unary_op(Unary_op* in);
    virtual Expr* pre_bin_op(Bin_op* in);
    virtual Constant* pre_constant(Constant* in);
    virtual Expr* pre_instanceof(Instanceof* in);
    virtual Expr* pre_method_invocation(Method_invocation* in);
    virtual Expr* pre_new(New* in);
    virtual void pre_variable_actual_parameter(Variable_actual_parameter* in, Actual_parameter_list* out);
    virtual Method_name* pre_variable_method(Variable_method* in);
    virtual Variable_name* pre_variable_variable(Variable_variable* in);
    virtual Class_name* pre_variable_class(Variable_class* in);
    virtual Field_name* pre_variable_field(Variable_field* in);
    virtual Static_value* pre_static_array(Static_array* in);
    virtual void pre_static_array_elem(Static_array_elem* in, Static_array_elem_list* out);
    virtual FOREIGN* pre_foreign(FOREIGN* in);
    virtual CLASS_NAME* pre_class_name(CLASS_NAME* in);
    virtual INTERFACE_NAME* pre_interface_name(INTERFACE_NAME* in);
    virtual METHOD_NAME* pre_method_name(METHOD_NAME* in);
    virtual VARIABLE_NAME* pre_variable_name(VARIABLE_NAME* in);
    virtual OP* pre_op(OP* in);
    virtual Literal* pre_int(INT* in);
    virtual Literal* pre_real(REAL* in);
    virtual Literal* pre_string(STRING* in);
    virtual Literal* pre_bool(BOOL* in);
    virtual Literal* pre_nil(NIL* in);
    virtual CAST* pre_cast(CAST* in);
    virtual CONSTANT_NAME* pre_constant_name(CONSTANT_NAME* in);
    virtual Field_name* pre_field_name(FIELD_NAME* in);
/* Invoked after the children have been transformed */
public:
    virtual PHP_script* post_php_script(PHP_script* in);
    virtual void post_class_def(Class_def* in, Statement_list* out);
    virtual Class_mod* post_class_mod(Class_mod* in);
    virtual void post_interface_def(Interface_def* in, Statement_list* out);
    virtual void post_method(Method* in, Method_list* out);
    virtual Signature* post_signature(Signature* in);
    virtual Method_mod* post_method_mod(Method_mod* in);
    virtual void post_formal_parameter(Formal_parameter* in, Formal_parameter_list* out);
    virtual Type* post_type(Type* in);
    virtual void post_attribute(Attribute* in, Member_list* out);
    virtual Attr_mod* post_attr_mod(Attr_mod* in);
    virtual Name_with_default* post_name_with_default(Name_with_default* in);
    virtual void post_if(If* in, Statement_list* out);
    virtual void post_loop(Loop* in, Statement_list* out);
    virtual void post_foreach(Foreach* in, Statement_list* out);
    virtual void post_break(Break* in, Statement_list* out);
    virtual void post_continue(Continue* in, Statement_list* out);
    virtual void post_return(Return* in, Statement_list* out);
    virtual void post_static_declaration(Static_declaration* in, Statement_list* out);
    virtual void post_global(Global* in, Statement_list* out);
    virtual void post_try(Try* in, Statement_list* out);
    virtual void post_catch(Catch* in, Catch_list* out);
    virtual void post_throw(Throw* in, Statement_list* out);
    virtual void post_assign_var(Assign_var* in, Statement_list* out);
    virtual void post_assign_field(Assign_field* in, Statement_list* out);
    virtual void post_assign_array(Assign_array* in, Statement_list* out);
    virtual void post_assign_var_var(Assign_var_var* in, Statement_list* out);
    virtual void post_assign_next(Assign_next* in, Statement_list* out);
    virtual void post_pre_op(Pre_op* in, Statement_list* out);
    virtual void post_eval_expr(Eval_expr* in, Statement_list* out);
    virtual Expr* post_field_access(Field_access* in);
    virtual Expr* post_array_access(Array_access* in);
    virtual Expr* post_array_next(Array_next* in);
    virtual Expr* post_cast(Cast* in);
    virtual Expr* post_unary_op(Unary_op* in);
    virtual Expr* post_bin_op(Bin_op* in);
    virtual Constant* post_constant(Constant* in);
    virtual Expr* post_instanceof(Instanceof* in);
    virtual Expr* post_method_invocation(Method_invocation* in);
    virtual Expr* post_new(New* in);
    virtual void post_variable_actual_parameter(Variable_actual_parameter* in, Actual_parameter_list* out);
    virtual Method_name* post_variable_method(Variable_method* in);
    virtual Variable_name* post_variable_variable(Variable_variable* in);
    virtual Class_name* post_variable_class(Variable_class* in);
    virtual Field_name* post_variable_field(Variable_field* in);
    virtual Static_value* post_static_array(Static_array* in);
    virtual void post_static_array_elem(Static_array_elem* in, Static_array_elem_list* out);
    virtual FOREIGN* post_foreign(FOREIGN* in);
    virtual CLASS_NAME* post_class_name(CLASS_NAME* in);
    virtual INTERFACE_NAME* post_interface_name(INTERFACE_NAME* in);
    virtual METHOD_NAME* post_method_name(METHOD_NAME* in);
    virtual VARIABLE_NAME* post_variable_name(VARIABLE_NAME* in);
    virtual OP* post_op(OP* in);
    virtual Literal* post_int(INT* in);
    virtual Literal* post_real(REAL* in);
    virtual Literal* post_string(STRING* in);
    virtual Literal* post_bool(BOOL* in);
    virtual Literal* post_nil(NIL* in);
    virtual CAST* post_cast(CAST* in);
    virtual CONSTANT_NAME* post_constant_name(CONSTANT_NAME* in);
    virtual Field_name* post_field_name(FIELD_NAME* in);
/* Transform the children of the node */
public:
    virtual void children_php_script(PHP_script* in);
    virtual void children_class_def(Class_def* in);
    virtual void children_class_mod(Class_mod* in);
    virtual void children_interface_def(Interface_def* in);
    virtual void children_method(Method* in);
    virtual void children_signature(Signature* in);
    virtual void children_method_mod(Method_mod* in);
    virtual void children_formal_parameter(Formal_parameter* in);
    virtual void children_type(Type* in);
    virtual void children_attribute(Attribute* in);
    virtual void children_attr_mod(Attr_mod* in);
    virtual void children_name_with_default(Name_with_default* in);
    virtual void children_if(If* in);
    virtual void children_loop(Loop* in);
    virtual void children_foreach(Foreach* in);
    virtual void children_break(Break* in);
    virtual void children_continue(Continue* in);
    virtual void children_return(Return* in);
    virtual void children_static_declaration(Static_declaration* in);
    virtual void children_global(Global* in);
    virtual void children_try(Try* in);
    virtual void children_catch(Catch* in);
    virtual void children_throw(Throw* in);
    virtual void children_assign_var(Assign_var* in);
    virtual void children_assign_field(Assign_field* in);
    virtual void children_assign_array(Assign_array* in);
    virtual void children_assign_var_var(Assign_var_var* in);
    virtual void children_assign_next(Assign_next* in);
    virtual void children_pre_op(Pre_op* in);
    virtual void children_eval_expr(Eval_expr* in);
    virtual void children_field_access(Field_access* in);
    virtual void children_array_access(Array_access* in);
    virtual void children_array_next(Array_next* in);
    virtual void children_cast(Cast* in);
    virtual void children_unary_op(Unary_op* in);
    virtual void children_bin_op(Bin_op* in);
    virtual void children_constant(Constant* in);
    virtual void children_instanceof(Instanceof* in);
    virtual void children_method_invocation(Method_invocation* in);
    virtual void children_new(New* in);
    virtual void children_variable_actual_parameter(Variable_actual_parameter* in);
    virtual void children_variable_method(Variable_method* in);
    virtual void children_variable_variable(Variable_variable* in);
    virtual void children_variable_class(Variable_class* in);
    virtual void children_variable_field(Variable_field* in);
    virtual void children_static_array(Static_array* in);
    virtual void children_static_array_elem(Static_array_elem* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_foreign(FOREIGN* in);
    virtual void children_class_name(CLASS_NAME* in);
    virtual void children_interface_name(INTERFACE_NAME* in);
    virtual void children_method_name(METHOD_NAME* in);
    virtual void children_variable_name(VARIABLE_NAME* in);
    virtual void children_op(OP* in);
    virtual void children_int(INT* in);
    virtual void children_real(REAL* in);
    virtual void children_string(STRING* in);
    virtual void children_bool(BOOL* in);
    virtual void children_nil(NIL* in);
    virtual void children_cast(CAST* in);
    virtual void children_constant_name(CONSTANT_NAME* in);
    virtual void children_field_name(FIELD_NAME* in);
/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
public:
    virtual Statement_list* transform_statement_list(Statement_list* in);
    virtual Statement_list* transform_statement(Statement* in);
    virtual Class_mod* transform_class_mod(Class_mod* in);
    virtual CLASS_NAME* transform_class_name(CLASS_NAME* in);
    virtual INTERFACE_NAME_list* transform_interface_name_list(INTERFACE_NAME_list* in);
    virtual Member_list* transform_member_list(Member_list* in);
    virtual Member_list* transform_member(Member* in);
    virtual INTERFACE_NAME* transform_interface_name(INTERFACE_NAME* in);
    virtual Signature* transform_signature(Signature* in);
    virtual Method_mod* transform_method_mod(Method_mod* in);
    virtual METHOD_NAME* transform_method_name(METHOD_NAME* in);
    virtual Formal_parameter_list* transform_formal_parameter_list(Formal_parameter_list* in);
    virtual Formal_parameter_list* transform_formal_parameter(Formal_parameter* in);
    virtual Type* transform_type(Type* in);
    virtual Name_with_default* transform_name_with_default(Name_with_default* in);
    virtual Attr_mod* transform_attr_mod(Attr_mod* in);
    virtual VARIABLE_NAME* transform_variable_name(VARIABLE_NAME* in);
    virtual Static_value* transform_static_value(Static_value* in);
    virtual Expr* transform_expr(Expr* in);
    virtual Rvalue* transform_rvalue(Rvalue* in);
    virtual Variable_name* transform_variable_name(Variable_name* in);
    virtual Catch_list* transform_catch_list(Catch_list* in);
    virtual Catch_list* transform_catch(Catch* in);
    virtual Target* transform_target(Target* in);
    virtual Field_name* transform_field_name(Field_name* in);
    virtual OP* transform_op(OP* in);
    virtual CAST* transform_cast(CAST* in);
    virtual CONSTANT_NAME* transform_constant_name(CONSTANT_NAME* in);
    virtual Class_name* transform_class_name(Class_name* in);
    virtual Method_name* transform_method_name(Method_name* in);
    virtual Actual_parameter_list* transform_actual_parameter_list(Actual_parameter_list* in);
    virtual Actual_parameter_list* transform_actual_parameter(Actual_parameter* in);
    virtual Rvalue_list* transform_rvalue_list(Rvalue_list* in);
    virtual Static_array_elem_list* transform_static_array_elem_list(Static_array_elem_list* in);
    virtual Static_array_elem_list* transform_static_array_elem(Static_array_elem* in);
    virtual Static_array_key* transform_static_array_key(Static_array_key* in);
    virtual PHP_script* transform_php_script(PHP_script* in);
/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_statement(Statement* in, Statement_list* out);
    virtual void pre_member(Member* in, Member_list* out);
    virtual Static_value* pre_static_value(Static_value* in);
    virtual Expr* pre_expr(Expr* in);
    virtual Rvalue* pre_rvalue(Rvalue* in);
    virtual Variable_name* pre_variable_name(Variable_name* in);
    virtual Target* pre_target(Target* in);
    virtual Field_name* pre_field_name(Field_name* in);
    virtual Class_name* pre_class_name(Class_name* in);
    virtual Method_name* pre_method_name(Method_name* in);
    virtual void pre_actual_parameter(Actual_parameter* in, Actual_parameter_list* out);
    virtual Static_array_key* pre_static_array_key(Static_array_key* in);
/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_statement(Statement* in, Statement_list* out);
    virtual void post_member(Member* in, Member_list* out);
    virtual Static_value* post_static_value(Static_value* in);
    virtual Expr* post_expr(Expr* in);
    virtual Rvalue* post_rvalue(Rvalue* in);
    virtual Variable_name* post_variable_name(Variable_name* in);
    virtual Target* post_target(Target* in);
    virtual Field_name* post_field_name(Field_name* in);
    virtual Class_name* post_class_name(Class_name* in);
    virtual Method_name* post_method_name(Method_name* in);
    virtual void post_actual_parameter(Actual_parameter* in, Actual_parameter_list* out);
    virtual Static_array_key* post_static_array_key(Static_array_key* in);
/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
public:
    virtual void children_statement(Statement* in);
    virtual void children_member(Member* in);
    virtual void children_static_value(Static_value* in);
    virtual void children_expr(Expr* in);
    virtual void children_rvalue(Rvalue* in);
    virtual void children_variable_name(Variable_name* in);
    virtual void children_target(Target* in);
    virtual void children_field_name(Field_name* in);
    virtual void children_class_name(Class_name* in);
    virtual void children_method_name(Method_name* in);
    virtual void children_actual_parameter(Actual_parameter* in);
    virtual void children_static_array_key(Static_array_key* in);
};
}


#endif
