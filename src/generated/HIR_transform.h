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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


#include "HIR.h"

namespace HIR{
class Transform
{
public:
    virtual ~Transform();
// Invoked before the children are transformed
public:
    virtual PHP_script* pre_php_script(PHP_script* in);
    virtual void pre_class_def(Class_def* in, List<Statement*>* out);
    virtual Class_mod* pre_class_mod(Class_mod* in);
    virtual void pre_interface_def(Interface_def* in, List<Statement*>* out);
    virtual void pre_method(Method* in, List<Method*>* out);
    virtual Signature* pre_signature(Signature* in);
    virtual Method_mod* pre_method_mod(Method_mod* in);
    virtual void pre_formal_parameter(Formal_parameter* in, List<Formal_parameter*>* out);
    virtual Type* pre_type(Type* in);
    virtual void pre_attribute(Attribute* in, List<Member*>* out);
    virtual Attr_mod* pre_attr_mod(Attr_mod* in);
    virtual Name_with_default* pre_name_with_default(Name_with_default* in);
    virtual void pre_return(Return* in, List<Statement*>* out);
    virtual void pre_static_declaration(Static_declaration* in, List<Statement*>* out);
    virtual void pre_global(Global* in, List<Statement*>* out);
    virtual void pre_try(Try* in, List<Statement*>* out);
    virtual void pre_catch(Catch* in, List<Catch*>* out);
    virtual void pre_throw(Throw* in, List<Statement*>* out);
    virtual void pre_eval_expr(Eval_expr* in, List<Statement*>* out);
    virtual void pre_branch(Branch* in, List<Statement*>* out);
    virtual void pre_goto(Goto* in, List<Statement*>* out);
    virtual void pre_label(Label* in, List<Statement*>* out);
    virtual void pre_foreach_reset(Foreach_reset* in, List<Statement*>* out);
    virtual void pre_foreach_next(Foreach_next* in, List<Statement*>* out);
    virtual void pre_foreach_end(Foreach_end* in, List<Statement*>* out);
    virtual Expr* pre_foreach_has_key(Foreach_has_key* in);
    virtual Expr* pre_foreach_get_key(Foreach_get_key* in);
    virtual Expr* pre_foreach_get_val(Foreach_get_val* in);
    virtual Expr* pre_assignment(Assignment* in);
    virtual Expr* pre_cast(Cast* in);
    virtual Expr* pre_unary_op(Unary_op* in);
    virtual Expr* pre_bin_op(Bin_op* in);
    virtual Expr* pre_constant(Constant* in);
    virtual Expr* pre_instanceof(Instanceof* in);
    virtual Variable* pre_variable(Variable* in);
    virtual Reflection* pre_reflection(Reflection* in);
    virtual Expr* pre_pre_op(Pre_op* in);
    virtual Expr* pre_array(Array* in);
    virtual void pre_array_elem(Array_elem* in, List<Array_elem*>* out);
    virtual Expr* pre_method_invocation(Method_invocation* in);
    virtual void pre_actual_parameter(Actual_parameter* in, List<Actual_parameter*>* out);
    virtual Expr* pre_new(New* in);
    virtual HT_ITERATOR* pre_ht_iterator(HT_ITERATOR* in);
    virtual CLASS_NAME* pre_class_name(CLASS_NAME* in);
    virtual INTERFACE_NAME* pre_interface_name(INTERFACE_NAME* in);
    virtual METHOD_NAME* pre_method_name(METHOD_NAME* in);
    virtual VARIABLE_NAME* pre_variable_name(VARIABLE_NAME* in);
    virtual LABEL_NAME* pre_label_name(LABEL_NAME* in);
    virtual Expr* pre_int(INT* in);
    virtual Expr* pre_real(REAL* in);
    virtual Expr* pre_string(STRING* in);
    virtual Expr* pre_bool(BOOL* in);
    virtual Expr* pre_nil(NIL* in);
    virtual CAST* pre_cast(CAST* in);
    virtual OP* pre_op(OP* in);
    virtual CONSTANT_NAME* pre_constant_name(CONSTANT_NAME* in);
// Invoked after the children have been transformed
public:
    virtual PHP_script* post_php_script(PHP_script* in);
    virtual void post_class_def(Class_def* in, List<Statement*>* out);
    virtual Class_mod* post_class_mod(Class_mod* in);
    virtual void post_interface_def(Interface_def* in, List<Statement*>* out);
    virtual void post_method(Method* in, List<Method*>* out);
    virtual Signature* post_signature(Signature* in);
    virtual Method_mod* post_method_mod(Method_mod* in);
    virtual void post_formal_parameter(Formal_parameter* in, List<Formal_parameter*>* out);
    virtual Type* post_type(Type* in);
    virtual void post_attribute(Attribute* in, List<Member*>* out);
    virtual Attr_mod* post_attr_mod(Attr_mod* in);
    virtual Name_with_default* post_name_with_default(Name_with_default* in);
    virtual void post_return(Return* in, List<Statement*>* out);
    virtual void post_static_declaration(Static_declaration* in, List<Statement*>* out);
    virtual void post_global(Global* in, List<Statement*>* out);
    virtual void post_try(Try* in, List<Statement*>* out);
    virtual void post_catch(Catch* in, List<Catch*>* out);
    virtual void post_throw(Throw* in, List<Statement*>* out);
    virtual void post_eval_expr(Eval_expr* in, List<Statement*>* out);
    virtual void post_branch(Branch* in, List<Statement*>* out);
    virtual void post_goto(Goto* in, List<Statement*>* out);
    virtual void post_label(Label* in, List<Statement*>* out);
    virtual void post_foreach_reset(Foreach_reset* in, List<Statement*>* out);
    virtual void post_foreach_next(Foreach_next* in, List<Statement*>* out);
    virtual void post_foreach_end(Foreach_end* in, List<Statement*>* out);
    virtual Expr* post_foreach_has_key(Foreach_has_key* in);
    virtual Expr* post_foreach_get_key(Foreach_get_key* in);
    virtual Expr* post_foreach_get_val(Foreach_get_val* in);
    virtual Expr* post_assignment(Assignment* in);
    virtual Expr* post_cast(Cast* in);
    virtual Expr* post_unary_op(Unary_op* in);
    virtual Expr* post_bin_op(Bin_op* in);
    virtual Expr* post_constant(Constant* in);
    virtual Expr* post_instanceof(Instanceof* in);
    virtual Variable* post_variable(Variable* in);
    virtual Reflection* post_reflection(Reflection* in);
    virtual Expr* post_pre_op(Pre_op* in);
    virtual Expr* post_array(Array* in);
    virtual void post_array_elem(Array_elem* in, List<Array_elem*>* out);
    virtual Expr* post_method_invocation(Method_invocation* in);
    virtual void post_actual_parameter(Actual_parameter* in, List<Actual_parameter*>* out);
    virtual Expr* post_new(New* in);
    virtual HT_ITERATOR* post_ht_iterator(HT_ITERATOR* in);
    virtual CLASS_NAME* post_class_name(CLASS_NAME* in);
    virtual INTERFACE_NAME* post_interface_name(INTERFACE_NAME* in);
    virtual METHOD_NAME* post_method_name(METHOD_NAME* in);
    virtual VARIABLE_NAME* post_variable_name(VARIABLE_NAME* in);
    virtual LABEL_NAME* post_label_name(LABEL_NAME* in);
    virtual Expr* post_int(INT* in);
    virtual Expr* post_real(REAL* in);
    virtual Expr* post_string(STRING* in);
    virtual Expr* post_bool(BOOL* in);
    virtual Expr* post_nil(NIL* in);
    virtual CAST* post_cast(CAST* in);
    virtual OP* post_op(OP* in);
    virtual CONSTANT_NAME* post_constant_name(CONSTANT_NAME* in);
// Transform the children of the node
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
    virtual void children_return(Return* in);
    virtual void children_static_declaration(Static_declaration* in);
    virtual void children_global(Global* in);
    virtual void children_try(Try* in);
    virtual void children_catch(Catch* in);
    virtual void children_throw(Throw* in);
    virtual void children_eval_expr(Eval_expr* in);
    virtual void children_branch(Branch* in);
    virtual void children_goto(Goto* in);
    virtual void children_label(Label* in);
    virtual void children_foreach_reset(Foreach_reset* in);
    virtual void children_foreach_next(Foreach_next* in);
    virtual void children_foreach_end(Foreach_end* in);
    virtual void children_foreach_has_key(Foreach_has_key* in);
    virtual void children_foreach_get_key(Foreach_get_key* in);
    virtual void children_foreach_get_val(Foreach_get_val* in);
    virtual void children_assignment(Assignment* in);
    virtual void children_cast(Cast* in);
    virtual void children_unary_op(Unary_op* in);
    virtual void children_bin_op(Bin_op* in);
    virtual void children_constant(Constant* in);
    virtual void children_instanceof(Instanceof* in);
    virtual void children_variable(Variable* in);
    virtual void children_reflection(Reflection* in);
    virtual void children_pre_op(Pre_op* in);
    virtual void children_array(Array* in);
    virtual void children_array_elem(Array_elem* in);
    virtual void children_method_invocation(Method_invocation* in);
    virtual void children_actual_parameter(Actual_parameter* in);
    virtual void children_new(New* in);
// Tokens don't have children, so these methods do nothing by default
public:
    virtual void children_ht_iterator(HT_ITERATOR* in);
    virtual void children_class_name(CLASS_NAME* in);
    virtual void children_interface_name(INTERFACE_NAME* in);
    virtual void children_method_name(METHOD_NAME* in);
    virtual void children_variable_name(VARIABLE_NAME* in);
    virtual void children_label_name(LABEL_NAME* in);
    virtual void children_int(INT* in);
    virtual void children_real(REAL* in);
    virtual void children_string(STRING* in);
    virtual void children_bool(BOOL* in);
    virtual void children_nil(NIL* in);
    virtual void children_cast(CAST* in);
    virtual void children_op(OP* in);
    virtual void children_constant_name(CONSTANT_NAME* in);
// Call the pre-transform, transform-children post-transform methods in order
// Do not override unless you know what you are doing
public:
    virtual List<Statement*>* transform_statement_list(List<Statement*>* in);
    virtual List<Statement*>* transform_statement(Statement* in);
    virtual Class_mod* transform_class_mod(Class_mod* in);
    virtual CLASS_NAME* transform_class_name(CLASS_NAME* in);
    virtual List<INTERFACE_NAME*>* transform_interface_name_list(List<INTERFACE_NAME*>* in);
    virtual List<Member*>* transform_member_list(List<Member*>* in);
    virtual List<Member*>* transform_member(Member* in);
    virtual INTERFACE_NAME* transform_interface_name(INTERFACE_NAME* in);
    virtual Signature* transform_signature(Signature* in);
    virtual Method_mod* transform_method_mod(Method_mod* in);
    virtual METHOD_NAME* transform_method_name(METHOD_NAME* in);
    virtual List<Formal_parameter*>* transform_formal_parameter_list(List<Formal_parameter*>* in);
    virtual List<Formal_parameter*>* transform_formal_parameter(Formal_parameter* in);
    virtual Type* transform_type(Type* in);
    virtual Name_with_default* transform_name_with_default(Name_with_default* in);
    virtual Attr_mod* transform_attr_mod(Attr_mod* in);
    virtual VARIABLE_NAME* transform_variable_name(VARIABLE_NAME* in);
    virtual Expr* transform_expr(Expr* in);
    virtual Variable_name* transform_variable_name(Variable_name* in);
    virtual List<Catch*>* transform_catch_list(List<Catch*>* in);
    virtual List<Catch*>* transform_catch(Catch* in);
    virtual LABEL_NAME* transform_label_name(LABEL_NAME* in);
    virtual HT_ITERATOR* transform_ht_iterator(HT_ITERATOR* in);
    virtual Variable* transform_variable(Variable* in);
    virtual CAST* transform_cast(CAST* in);
    virtual OP* transform_op(OP* in);
    virtual CONSTANT_NAME* transform_constant_name(CONSTANT_NAME* in);
    virtual Class_name* transform_class_name(Class_name* in);
    virtual Target* transform_target(Target* in);
    virtual List<VARIABLE_NAME*>* transform_variable_name_list(List<VARIABLE_NAME*>* in);
    virtual List<Array_elem*>* transform_array_elem_list(List<Array_elem*>* in);
    virtual List<Array_elem*>* transform_array_elem(Array_elem* in);
    virtual Method_name* transform_method_name(Method_name* in);
    virtual List<Actual_parameter*>* transform_actual_parameter_list(List<Actual_parameter*>* in);
    virtual List<Actual_parameter*>* transform_actual_parameter(Actual_parameter* in);
    virtual PHP_script* transform_php_script(PHP_script* in);
// Invoke the right pre-transform (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void pre_statement(Statement* in, List<Statement*>* out);
    virtual void pre_member(Member* in, List<Member*>* out);
    virtual Expr* pre_expr(Expr* in);
    virtual Variable_name* pre_variable_name(Variable_name* in);
    virtual Class_name* pre_class_name(Class_name* in);
    virtual Target* pre_target(Target* in);
    virtual Method_name* pre_method_name(Method_name* in);
// Invoke the right post-transform (manual dispatching)
// Do not override unless you know what you are doing
public:
    virtual void post_statement(Statement* in, List<Statement*>* out);
    virtual void post_member(Member* in, List<Member*>* out);
    virtual Expr* post_expr(Expr* in);
    virtual Variable_name* post_variable_name(Variable_name* in);
    virtual Class_name* post_class_name(Class_name* in);
    virtual Target* post_target(Target* in);
    virtual Method_name* post_method_name(Method_name* in);
// Invoke the right transform-children (manual dispatching)
// Do not override unless you what you are doing
public:
    virtual void children_statement(Statement* in);
    virtual void children_member(Member* in);
    virtual void children_expr(Expr* in);
    virtual void children_variable_name(Variable_name* in);
    virtual void children_class_name(Class_name* in);
    virtual void children_target(Target* in);
    virtual void children_method_name(Method_name* in);
};
}


#endif
