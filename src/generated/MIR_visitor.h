#ifndef _MIR_VISITOR_H_
#define _MIR_VISITOR_H_

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


#include "MIR.h"

namespace MIR{
class Visitor
{
public:
    virtual ~Visitor();
/* Invoked before the children are visited */
public:
    virtual void pre_node(Node* in);
    virtual void pre_php_script(PHP_script* in);
    virtual void pre_statement(Statement* in);
    virtual void pre_class_def(Class_def* in);
    virtual void pre_class_mod(Class_mod* in);
    virtual void pre_interface_def(Interface_def* in);
    virtual void pre_member(Member* in);
    virtual void pre_method(Method* in);
    virtual void pre_signature(Signature* in);
    virtual void pre_method_mod(Method_mod* in);
    virtual void pre_formal_parameter(Formal_parameter* in);
    virtual void pre_type(Type* in);
    virtual void pre_attribute(Attribute* in);
    virtual void pre_attr_mod(Attr_mod* in);
    virtual void pre_name_with_default(Name_with_default* in);
    virtual void pre_class_alias(Class_alias* in);
    virtual void pre_interface_alias(Interface_alias* in);
    virtual void pre_method_alias(Method_alias* in);
    virtual void pre_return(Return* in);
    virtual void pre_static_declaration(Static_declaration* in);
    virtual void pre_global(Global* in);
    virtual void pre_try(Try* in);
    virtual void pre_catch(Catch* in);
    virtual void pre_throw(Throw* in);
    virtual void pre_assign_var(Assign_var* in);
    virtual void pre_assign_field(Assign_field* in);
    virtual void pre_assign_array(Assign_array* in);
    virtual void pre_assign_var_var(Assign_var_var* in);
    virtual void pre_assign_next(Assign_next* in);
    virtual void pre_pre_op(Pre_op* in);
    virtual void pre_eval_expr(Eval_expr* in);
    virtual void pre_unset(Unset* in);
    virtual void pre_isset(Isset* in);
    virtual void pre_expr(Expr* in);
    virtual void pre_literal(Literal* in);
    virtual void pre_rvalue(Rvalue* in);
    virtual void pre_field_access(Field_access* in);
    virtual void pre_array_access(Array_access* in);
    virtual void pre_array_next(Array_next* in);
    virtual void pre_cast(Cast* in);
    virtual void pre_unary_op(Unary_op* in);
    virtual void pre_bin_op(Bin_op* in);
    virtual void pre_constant(Constant* in);
    virtual void pre_instanceof(Instanceof* in);
    virtual void pre_target(Target* in);
    virtual void pre_method_invocation(Method_invocation* in);
    virtual void pre_new(New* in);
    virtual void pre_actual_parameter(Actual_parameter* in);
    virtual void pre_method_name(Method_name* in);
    virtual void pre_variable_name(Variable_name* in);
    virtual void pre_class_name(Class_name* in);
    virtual void pre_field_name(Field_name* in);
    virtual void pre_variable_method(Variable_method* in);
    virtual void pre_variable_variable(Variable_variable* in);
    virtual void pre_variable_class(Variable_class* in);
    virtual void pre_variable_field(Variable_field* in);
    virtual void pre_static_value(Static_value* in);
    virtual void pre_static_array(Static_array* in);
    virtual void pre_static_array_elem(Static_array_elem* in);
    virtual void pre_static_array_key(Static_array_key* in);
    virtual void pre_branch(Branch* in);
    virtual void pre_goto(Goto* in);
    virtual void pre_label(Label* in);
    virtual void pre_foreach_reset(Foreach_reset* in);
    virtual void pre_foreach_next(Foreach_next* in);
    virtual void pre_foreach_end(Foreach_end* in);
    virtual void pre_foreach_has_key(Foreach_has_key* in);
    virtual void pre_foreach_get_key(Foreach_get_key* in);
    virtual void pre_foreach_get_val(Foreach_get_val* in);
    virtual void pre_param_is_ref(Param_is_ref* in);
    virtual void pre_identifier(Identifier* in);
    virtual void pre_param_index(PARAM_INDEX* in);
    virtual void pre_foreign(FOREIGN* in);
    virtual void pre_class_name(CLASS_NAME* in);
    virtual void pre_interface_name(INTERFACE_NAME* in);
    virtual void pre_method_name(METHOD_NAME* in);
    virtual void pre_variable_name(VARIABLE_NAME* in);
    virtual void pre_op(OP* in);
    virtual void pre_int(INT* in);
    virtual void pre_real(REAL* in);
    virtual void pre_string(STRING* in);
    virtual void pre_bool(BOOL* in);
    virtual void pre_nil(NIL* in);
    virtual void pre_cast(CAST* in);
    virtual void pre_constant_name(CONSTANT_NAME* in);
    virtual void pre_field_name(FIELD_NAME* in);
    virtual void pre_label_name(LABEL_NAME* in);
    virtual void pre_ht_iterator(HT_ITERATOR* in);
/* Invoked after the children have been visited */
public:
    virtual void post_node(Node* in);
    virtual void post_php_script(PHP_script* in);
    virtual void post_statement(Statement* in);
    virtual void post_class_def(Class_def* in);
    virtual void post_class_mod(Class_mod* in);
    virtual void post_interface_def(Interface_def* in);
    virtual void post_member(Member* in);
    virtual void post_method(Method* in);
    virtual void post_signature(Signature* in);
    virtual void post_method_mod(Method_mod* in);
    virtual void post_formal_parameter(Formal_parameter* in);
    virtual void post_type(Type* in);
    virtual void post_attribute(Attribute* in);
    virtual void post_attr_mod(Attr_mod* in);
    virtual void post_name_with_default(Name_with_default* in);
    virtual void post_class_alias(Class_alias* in);
    virtual void post_interface_alias(Interface_alias* in);
    virtual void post_method_alias(Method_alias* in);
    virtual void post_return(Return* in);
    virtual void post_static_declaration(Static_declaration* in);
    virtual void post_global(Global* in);
    virtual void post_try(Try* in);
    virtual void post_catch(Catch* in);
    virtual void post_throw(Throw* in);
    virtual void post_assign_var(Assign_var* in);
    virtual void post_assign_field(Assign_field* in);
    virtual void post_assign_array(Assign_array* in);
    virtual void post_assign_var_var(Assign_var_var* in);
    virtual void post_assign_next(Assign_next* in);
    virtual void post_pre_op(Pre_op* in);
    virtual void post_eval_expr(Eval_expr* in);
    virtual void post_unset(Unset* in);
    virtual void post_isset(Isset* in);
    virtual void post_expr(Expr* in);
    virtual void post_literal(Literal* in);
    virtual void post_rvalue(Rvalue* in);
    virtual void post_field_access(Field_access* in);
    virtual void post_array_access(Array_access* in);
    virtual void post_array_next(Array_next* in);
    virtual void post_cast(Cast* in);
    virtual void post_unary_op(Unary_op* in);
    virtual void post_bin_op(Bin_op* in);
    virtual void post_constant(Constant* in);
    virtual void post_instanceof(Instanceof* in);
    virtual void post_target(Target* in);
    virtual void post_method_invocation(Method_invocation* in);
    virtual void post_new(New* in);
    virtual void post_actual_parameter(Actual_parameter* in);
    virtual void post_method_name(Method_name* in);
    virtual void post_variable_name(Variable_name* in);
    virtual void post_class_name(Class_name* in);
    virtual void post_field_name(Field_name* in);
    virtual void post_variable_method(Variable_method* in);
    virtual void post_variable_variable(Variable_variable* in);
    virtual void post_variable_class(Variable_class* in);
    virtual void post_variable_field(Variable_field* in);
    virtual void post_static_value(Static_value* in);
    virtual void post_static_array(Static_array* in);
    virtual void post_static_array_elem(Static_array_elem* in);
    virtual void post_static_array_key(Static_array_key* in);
    virtual void post_branch(Branch* in);
    virtual void post_goto(Goto* in);
    virtual void post_label(Label* in);
    virtual void post_foreach_reset(Foreach_reset* in);
    virtual void post_foreach_next(Foreach_next* in);
    virtual void post_foreach_end(Foreach_end* in);
    virtual void post_foreach_has_key(Foreach_has_key* in);
    virtual void post_foreach_get_key(Foreach_get_key* in);
    virtual void post_foreach_get_val(Foreach_get_val* in);
    virtual void post_param_is_ref(Param_is_ref* in);
    virtual void post_identifier(Identifier* in);
    virtual void post_param_index(PARAM_INDEX* in);
    virtual void post_foreign(FOREIGN* in);
    virtual void post_class_name(CLASS_NAME* in);
    virtual void post_interface_name(INTERFACE_NAME* in);
    virtual void post_method_name(METHOD_NAME* in);
    virtual void post_variable_name(VARIABLE_NAME* in);
    virtual void post_op(OP* in);
    virtual void post_int(INT* in);
    virtual void post_real(REAL* in);
    virtual void post_string(STRING* in);
    virtual void post_bool(BOOL* in);
    virtual void post_nil(NIL* in);
    virtual void post_cast(CAST* in);
    virtual void post_constant_name(CONSTANT_NAME* in);
    virtual void post_field_name(FIELD_NAME* in);
    virtual void post_label_name(LABEL_NAME* in);
    virtual void post_ht_iterator(HT_ITERATOR* in);
/* Visit the children of a node */
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
    virtual void children_class_alias(Class_alias* in);
    virtual void children_interface_alias(Interface_alias* in);
    virtual void children_method_alias(Method_alias* in);
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
    virtual void children_unset(Unset* in);
    virtual void children_isset(Isset* in);
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
    virtual void children_actual_parameter(Actual_parameter* in);
    virtual void children_variable_method(Variable_method* in);
    virtual void children_variable_variable(Variable_variable* in);
    virtual void children_variable_class(Variable_class* in);
    virtual void children_variable_field(Variable_field* in);
    virtual void children_static_array(Static_array* in);
    virtual void children_static_array_elem(Static_array_elem* in);
    virtual void children_branch(Branch* in);
    virtual void children_goto(Goto* in);
    virtual void children_label(Label* in);
    virtual void children_foreach_reset(Foreach_reset* in);
    virtual void children_foreach_next(Foreach_next* in);
    virtual void children_foreach_end(Foreach_end* in);
    virtual void children_foreach_has_key(Foreach_has_key* in);
    virtual void children_foreach_get_key(Foreach_get_key* in);
    virtual void children_foreach_get_val(Foreach_get_val* in);
    virtual void children_param_is_ref(Param_is_ref* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_param_index(PARAM_INDEX* in);
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
    virtual void children_label_name(LABEL_NAME* in);
    virtual void children_ht_iterator(HT_ITERATOR* in);
/* Unparser support */
public:
    virtual void visit_marker(char const* name, bool value);
    virtual void visit_null(char const* name_space, char const* type_id);
    virtual void visit_null_list(char const* name_space, char const* type_id);
    virtual void pre_list(char const* name_space, char const* type_id, int size);
    virtual void post_list(char const* name_space, char const* type_id, int size);
/* Invoke the chain of pre-visit methods along the inheritance hierachy */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_php_script_chain(PHP_script* in);
    virtual void pre_class_def_chain(Class_def* in);
    virtual void pre_class_mod_chain(Class_mod* in);
    virtual void pre_interface_def_chain(Interface_def* in);
    virtual void pre_method_chain(Method* in);
    virtual void pre_signature_chain(Signature* in);
    virtual void pre_method_mod_chain(Method_mod* in);
    virtual void pre_formal_parameter_chain(Formal_parameter* in);
    virtual void pre_type_chain(Type* in);
    virtual void pre_attribute_chain(Attribute* in);
    virtual void pre_attr_mod_chain(Attr_mod* in);
    virtual void pre_name_with_default_chain(Name_with_default* in);
    virtual void pre_class_alias_chain(Class_alias* in);
    virtual void pre_interface_alias_chain(Interface_alias* in);
    virtual void pre_method_alias_chain(Method_alias* in);
    virtual void pre_return_chain(Return* in);
    virtual void pre_static_declaration_chain(Static_declaration* in);
    virtual void pre_global_chain(Global* in);
    virtual void pre_try_chain(Try* in);
    virtual void pre_catch_chain(Catch* in);
    virtual void pre_throw_chain(Throw* in);
    virtual void pre_assign_var_chain(Assign_var* in);
    virtual void pre_assign_field_chain(Assign_field* in);
    virtual void pre_assign_array_chain(Assign_array* in);
    virtual void pre_assign_var_var_chain(Assign_var_var* in);
    virtual void pre_assign_next_chain(Assign_next* in);
    virtual void pre_pre_op_chain(Pre_op* in);
    virtual void pre_eval_expr_chain(Eval_expr* in);
    virtual void pre_unset_chain(Unset* in);
    virtual void pre_isset_chain(Isset* in);
    virtual void pre_field_access_chain(Field_access* in);
    virtual void pre_array_access_chain(Array_access* in);
    virtual void pre_array_next_chain(Array_next* in);
    virtual void pre_cast_chain(Cast* in);
    virtual void pre_unary_op_chain(Unary_op* in);
    virtual void pre_bin_op_chain(Bin_op* in);
    virtual void pre_constant_chain(Constant* in);
    virtual void pre_instanceof_chain(Instanceof* in);
    virtual void pre_method_invocation_chain(Method_invocation* in);
    virtual void pre_new_chain(New* in);
    virtual void pre_actual_parameter_chain(Actual_parameter* in);
    virtual void pre_variable_method_chain(Variable_method* in);
    virtual void pre_variable_variable_chain(Variable_variable* in);
    virtual void pre_variable_class_chain(Variable_class* in);
    virtual void pre_variable_field_chain(Variable_field* in);
    virtual void pre_static_array_chain(Static_array* in);
    virtual void pre_static_array_elem_chain(Static_array_elem* in);
    virtual void pre_branch_chain(Branch* in);
    virtual void pre_goto_chain(Goto* in);
    virtual void pre_label_chain(Label* in);
    virtual void pre_foreach_reset_chain(Foreach_reset* in);
    virtual void pre_foreach_next_chain(Foreach_next* in);
    virtual void pre_foreach_end_chain(Foreach_end* in);
    virtual void pre_foreach_has_key_chain(Foreach_has_key* in);
    virtual void pre_foreach_get_key_chain(Foreach_get_key* in);
    virtual void pre_foreach_get_val_chain(Foreach_get_val* in);
    virtual void pre_param_is_ref_chain(Param_is_ref* in);
    virtual void pre_param_index_chain(PARAM_INDEX* in);
    virtual void pre_foreign_chain(FOREIGN* in);
    virtual void pre_class_name_chain(CLASS_NAME* in);
    virtual void pre_interface_name_chain(INTERFACE_NAME* in);
    virtual void pre_method_name_chain(METHOD_NAME* in);
    virtual void pre_variable_name_chain(VARIABLE_NAME* in);
    virtual void pre_op_chain(OP* in);
    virtual void pre_int_chain(INT* in);
    virtual void pre_real_chain(REAL* in);
    virtual void pre_string_chain(STRING* in);
    virtual void pre_bool_chain(BOOL* in);
    virtual void pre_nil_chain(NIL* in);
    virtual void pre_cast_chain(CAST* in);
    virtual void pre_constant_name_chain(CONSTANT_NAME* in);
    virtual void pre_field_name_chain(FIELD_NAME* in);
    virtual void pre_label_name_chain(LABEL_NAME* in);
    virtual void pre_ht_iterator_chain(HT_ITERATOR* in);
/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_php_script_chain(PHP_script* in);
    virtual void post_class_def_chain(Class_def* in);
    virtual void post_class_mod_chain(Class_mod* in);
    virtual void post_interface_def_chain(Interface_def* in);
    virtual void post_method_chain(Method* in);
    virtual void post_signature_chain(Signature* in);
    virtual void post_method_mod_chain(Method_mod* in);
    virtual void post_formal_parameter_chain(Formal_parameter* in);
    virtual void post_type_chain(Type* in);
    virtual void post_attribute_chain(Attribute* in);
    virtual void post_attr_mod_chain(Attr_mod* in);
    virtual void post_name_with_default_chain(Name_with_default* in);
    virtual void post_class_alias_chain(Class_alias* in);
    virtual void post_interface_alias_chain(Interface_alias* in);
    virtual void post_method_alias_chain(Method_alias* in);
    virtual void post_return_chain(Return* in);
    virtual void post_static_declaration_chain(Static_declaration* in);
    virtual void post_global_chain(Global* in);
    virtual void post_try_chain(Try* in);
    virtual void post_catch_chain(Catch* in);
    virtual void post_throw_chain(Throw* in);
    virtual void post_assign_var_chain(Assign_var* in);
    virtual void post_assign_field_chain(Assign_field* in);
    virtual void post_assign_array_chain(Assign_array* in);
    virtual void post_assign_var_var_chain(Assign_var_var* in);
    virtual void post_assign_next_chain(Assign_next* in);
    virtual void post_pre_op_chain(Pre_op* in);
    virtual void post_eval_expr_chain(Eval_expr* in);
    virtual void post_unset_chain(Unset* in);
    virtual void post_isset_chain(Isset* in);
    virtual void post_field_access_chain(Field_access* in);
    virtual void post_array_access_chain(Array_access* in);
    virtual void post_array_next_chain(Array_next* in);
    virtual void post_cast_chain(Cast* in);
    virtual void post_unary_op_chain(Unary_op* in);
    virtual void post_bin_op_chain(Bin_op* in);
    virtual void post_constant_chain(Constant* in);
    virtual void post_instanceof_chain(Instanceof* in);
    virtual void post_method_invocation_chain(Method_invocation* in);
    virtual void post_new_chain(New* in);
    virtual void post_actual_parameter_chain(Actual_parameter* in);
    virtual void post_variable_method_chain(Variable_method* in);
    virtual void post_variable_variable_chain(Variable_variable* in);
    virtual void post_variable_class_chain(Variable_class* in);
    virtual void post_variable_field_chain(Variable_field* in);
    virtual void post_static_array_chain(Static_array* in);
    virtual void post_static_array_elem_chain(Static_array_elem* in);
    virtual void post_branch_chain(Branch* in);
    virtual void post_goto_chain(Goto* in);
    virtual void post_label_chain(Label* in);
    virtual void post_foreach_reset_chain(Foreach_reset* in);
    virtual void post_foreach_next_chain(Foreach_next* in);
    virtual void post_foreach_end_chain(Foreach_end* in);
    virtual void post_foreach_has_key_chain(Foreach_has_key* in);
    virtual void post_foreach_get_key_chain(Foreach_get_key* in);
    virtual void post_foreach_get_val_chain(Foreach_get_val* in);
    virtual void post_param_is_ref_chain(Param_is_ref* in);
    virtual void post_param_index_chain(PARAM_INDEX* in);
    virtual void post_foreign_chain(FOREIGN* in);
    virtual void post_class_name_chain(CLASS_NAME* in);
    virtual void post_interface_name_chain(INTERFACE_NAME* in);
    virtual void post_method_name_chain(METHOD_NAME* in);
    virtual void post_variable_name_chain(VARIABLE_NAME* in);
    virtual void post_op_chain(OP* in);
    virtual void post_int_chain(INT* in);
    virtual void post_real_chain(REAL* in);
    virtual void post_string_chain(STRING* in);
    virtual void post_bool_chain(BOOL* in);
    virtual void post_nil_chain(NIL* in);
    virtual void post_cast_chain(CAST* in);
    virtual void post_constant_name_chain(CONSTANT_NAME* in);
    virtual void post_field_name_chain(FIELD_NAME* in);
    virtual void post_label_name_chain(LABEL_NAME* in);
    virtual void post_ht_iterator_chain(HT_ITERATOR* in);
/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
public:
    virtual void visit_statement_list(Statement_list* in);
    virtual void visit_statement(Statement* in);
    virtual void visit_class_mod(Class_mod* in);
    virtual void visit_class_name(CLASS_NAME* in);
    virtual void visit_interface_name_list(INTERFACE_NAME_list* in);
    virtual void visit_member_list(Member_list* in);
    virtual void visit_member(Member* in);
    virtual void visit_interface_name(INTERFACE_NAME* in);
    virtual void visit_signature(Signature* in);
    virtual void visit_method_mod(Method_mod* in);
    virtual void visit_method_name(METHOD_NAME* in);
    virtual void visit_formal_parameter_list(Formal_parameter_list* in);
    virtual void visit_formal_parameter(Formal_parameter* in);
    virtual void visit_type(Type* in);
    virtual void visit_name_with_default(Name_with_default* in);
    virtual void visit_attr_mod(Attr_mod* in);
    virtual void visit_variable_name(VARIABLE_NAME* in);
    virtual void visit_static_value(Static_value* in);
    virtual void visit_rvalue(Rvalue* in);
    virtual void visit_variable_name(Variable_name* in);
    virtual void visit_catch_list(Catch_list* in);
    virtual void visit_catch(Catch* in);
    virtual void visit_expr(Expr* in);
    virtual void visit_target(Target* in);
    virtual void visit_field_name(Field_name* in);
    virtual void visit_op(OP* in);
    virtual void visit_rvalue_list(Rvalue_list* in);
    virtual void visit_cast(CAST* in);
    virtual void visit_constant_name(CONSTANT_NAME* in);
    virtual void visit_class_name(Class_name* in);
    virtual void visit_method_name(Method_name* in);
    virtual void visit_actual_parameter_list(Actual_parameter_list* in);
    virtual void visit_actual_parameter(Actual_parameter* in);
    virtual void visit_static_array_elem_list(Static_array_elem_list* in);
    virtual void visit_static_array_elem(Static_array_elem* in);
    virtual void visit_static_array_key(Static_array_key* in);
    virtual void visit_label_name(LABEL_NAME* in);
    virtual void visit_ht_iterator(HT_ITERATOR* in);
    virtual void visit_param_index(PARAM_INDEX* in);
    virtual void visit_php_script(PHP_script* in);
/* Invoke the right pre-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_statement_chain(Statement* in);
    virtual void pre_member_chain(Member* in);
    virtual void pre_static_value_chain(Static_value* in);
    virtual void pre_rvalue_chain(Rvalue* in);
    virtual void pre_variable_name_chain(Variable_name* in);
    virtual void pre_expr_chain(Expr* in);
    virtual void pre_target_chain(Target* in);
    virtual void pre_field_name_chain(Field_name* in);
    virtual void pre_class_name_chain(Class_name* in);
    virtual void pre_method_name_chain(Method_name* in);
    virtual void pre_static_array_key_chain(Static_array_key* in);
/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_statement_chain(Statement* in);
    virtual void post_member_chain(Member* in);
    virtual void post_static_value_chain(Static_value* in);
    virtual void post_rvalue_chain(Rvalue* in);
    virtual void post_variable_name_chain(Variable_name* in);
    virtual void post_expr_chain(Expr* in);
    virtual void post_target_chain(Target* in);
    virtual void post_field_name_chain(Field_name* in);
    virtual void post_class_name_chain(Class_name* in);
    virtual void post_method_name_chain(Method_name* in);
    virtual void post_static_array_key_chain(Static_array_key* in);
/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void children_statement(Statement* in);
    virtual void children_member(Member* in);
    virtual void children_static_value(Static_value* in);
    virtual void children_rvalue(Rvalue* in);
    virtual void children_variable_name(Variable_name* in);
    virtual void children_expr(Expr* in);
    virtual void children_target(Target* in);
    virtual void children_field_name(Field_name* in);
    virtual void children_class_name(Class_name* in);
    virtual void children_method_name(Method_name* in);
    virtual void children_static_array_key(Static_array_key* in);
};
}


#endif
