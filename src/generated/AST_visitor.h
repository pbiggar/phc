#ifndef _AST_VISITOR_H_
#define _AST_VISITOR_H_

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


#include "AST.h"

namespace AST{
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
    virtual void pre_if(If* in);
    virtual void pre_while(While* in);
    virtual void pre_do(Do* in);
    virtual void pre_for(For* in);
    virtual void pre_foreach(Foreach* in);
    virtual void pre_switch(Switch* in);
    virtual void pre_switch_case(Switch_case* in);
    virtual void pre_break(Break* in);
    virtual void pre_continue(Continue* in);
    virtual void pre_return(Return* in);
    virtual void pre_static_declaration(Static_declaration* in);
    virtual void pre_global(Global* in);
    virtual void pre_declare(Declare* in);
    virtual void pre_directive(Directive* in);
    virtual void pre_try(Try* in);
    virtual void pre_catch(Catch* in);
    virtual void pre_throw(Throw* in);
    virtual void pre_eval_expr(Eval_expr* in);
    virtual void pre_nop(Nop* in);
    virtual void pre_expr(Expr* in);
    virtual void pre_literal(Literal* in);
    virtual void pre_assignment(Assignment* in);
    virtual void pre_op_assignment(Op_assignment* in);
    virtual void pre_list_assignment(List_assignment* in);
    virtual void pre_list_element(List_element* in);
    virtual void pre_nested_list_elements(Nested_list_elements* in);
    virtual void pre_cast(Cast* in);
    virtual void pre_unary_op(Unary_op* in);
    virtual void pre_bin_op(Bin_op* in);
    virtual void pre_conditional_expr(Conditional_expr* in);
    virtual void pre_ignore_errors(Ignore_errors* in);
    virtual void pre_constant(Constant* in);
    virtual void pre_instanceof(Instanceof* in);
    virtual void pre_variable(Variable* in);
    virtual void pre_variable_name(Variable_name* in);
    virtual void pre_reflection(Reflection* in);
    virtual void pre_target(Target* in);
    virtual void pre_pre_op(Pre_op* in);
    virtual void pre_post_op(Post_op* in);
    virtual void pre_array(Array* in);
    virtual void pre_array_elem(Array_elem* in);
    virtual void pre_method_invocation(Method_invocation* in);
    virtual void pre_method_name(Method_name* in);
    virtual void pre_actual_parameter(Actual_parameter* in);
    virtual void pre_new(New* in);
    virtual void pre_class_name(Class_name* in);
    virtual void pre_commented_node(Commented_node* in);
    virtual void pre_identifier(Identifier* in);
    virtual void pre_source_rep(Source_rep* in);
    virtual void pre_foreign(FOREIGN* in);
    virtual void pre_class_name(CLASS_NAME* in);
    virtual void pre_interface_name(INTERFACE_NAME* in);
    virtual void pre_method_name(METHOD_NAME* in);
    virtual void pre_variable_name(VARIABLE_NAME* in);
    virtual void pre_directive_name(DIRECTIVE_NAME* in);
    virtual void pre_int(INT* in);
    virtual void pre_real(REAL* in);
    virtual void pre_string(STRING* in);
    virtual void pre_bool(BOOL* in);
    virtual void pre_nil(NIL* in);
    virtual void pre_op(OP* in);
    virtual void pre_cast(CAST* in);
    virtual void pre_constant_name(CONSTANT_NAME* in);
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
    virtual void post_if(If* in);
    virtual void post_while(While* in);
    virtual void post_do(Do* in);
    virtual void post_for(For* in);
    virtual void post_foreach(Foreach* in);
    virtual void post_switch(Switch* in);
    virtual void post_switch_case(Switch_case* in);
    virtual void post_break(Break* in);
    virtual void post_continue(Continue* in);
    virtual void post_return(Return* in);
    virtual void post_static_declaration(Static_declaration* in);
    virtual void post_global(Global* in);
    virtual void post_declare(Declare* in);
    virtual void post_directive(Directive* in);
    virtual void post_try(Try* in);
    virtual void post_catch(Catch* in);
    virtual void post_throw(Throw* in);
    virtual void post_eval_expr(Eval_expr* in);
    virtual void post_nop(Nop* in);
    virtual void post_expr(Expr* in);
    virtual void post_literal(Literal* in);
    virtual void post_assignment(Assignment* in);
    virtual void post_op_assignment(Op_assignment* in);
    virtual void post_list_assignment(List_assignment* in);
    virtual void post_list_element(List_element* in);
    virtual void post_nested_list_elements(Nested_list_elements* in);
    virtual void post_cast(Cast* in);
    virtual void post_unary_op(Unary_op* in);
    virtual void post_bin_op(Bin_op* in);
    virtual void post_conditional_expr(Conditional_expr* in);
    virtual void post_ignore_errors(Ignore_errors* in);
    virtual void post_constant(Constant* in);
    virtual void post_instanceof(Instanceof* in);
    virtual void post_variable(Variable* in);
    virtual void post_variable_name(Variable_name* in);
    virtual void post_reflection(Reflection* in);
    virtual void post_target(Target* in);
    virtual void post_pre_op(Pre_op* in);
    virtual void post_post_op(Post_op* in);
    virtual void post_array(Array* in);
    virtual void post_array_elem(Array_elem* in);
    virtual void post_method_invocation(Method_invocation* in);
    virtual void post_method_name(Method_name* in);
    virtual void post_actual_parameter(Actual_parameter* in);
    virtual void post_new(New* in);
    virtual void post_class_name(Class_name* in);
    virtual void post_commented_node(Commented_node* in);
    virtual void post_identifier(Identifier* in);
    virtual void post_source_rep(Source_rep* in);
    virtual void post_foreign(FOREIGN* in);
    virtual void post_class_name(CLASS_NAME* in);
    virtual void post_interface_name(INTERFACE_NAME* in);
    virtual void post_method_name(METHOD_NAME* in);
    virtual void post_variable_name(VARIABLE_NAME* in);
    virtual void post_directive_name(DIRECTIVE_NAME* in);
    virtual void post_int(INT* in);
    virtual void post_real(REAL* in);
    virtual void post_string(STRING* in);
    virtual void post_bool(BOOL* in);
    virtual void post_nil(NIL* in);
    virtual void post_op(OP* in);
    virtual void post_cast(CAST* in);
    virtual void post_constant_name(CONSTANT_NAME* in);
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
    virtual void children_if(If* in);
    virtual void children_while(While* in);
    virtual void children_do(Do* in);
    virtual void children_for(For* in);
    virtual void children_foreach(Foreach* in);
    virtual void children_switch(Switch* in);
    virtual void children_switch_case(Switch_case* in);
    virtual void children_break(Break* in);
    virtual void children_continue(Continue* in);
    virtual void children_return(Return* in);
    virtual void children_static_declaration(Static_declaration* in);
    virtual void children_global(Global* in);
    virtual void children_declare(Declare* in);
    virtual void children_directive(Directive* in);
    virtual void children_try(Try* in);
    virtual void children_catch(Catch* in);
    virtual void children_throw(Throw* in);
    virtual void children_eval_expr(Eval_expr* in);
    virtual void children_nop(Nop* in);
    virtual void children_assignment(Assignment* in);
    virtual void children_op_assignment(Op_assignment* in);
    virtual void children_list_assignment(List_assignment* in);
    virtual void children_nested_list_elements(Nested_list_elements* in);
    virtual void children_cast(Cast* in);
    virtual void children_unary_op(Unary_op* in);
    virtual void children_bin_op(Bin_op* in);
    virtual void children_conditional_expr(Conditional_expr* in);
    virtual void children_ignore_errors(Ignore_errors* in);
    virtual void children_constant(Constant* in);
    virtual void children_instanceof(Instanceof* in);
    virtual void children_variable(Variable* in);
    virtual void children_reflection(Reflection* in);
    virtual void children_pre_op(Pre_op* in);
    virtual void children_post_op(Post_op* in);
    virtual void children_array(Array* in);
    virtual void children_array_elem(Array_elem* in);
    virtual void children_method_invocation(Method_invocation* in);
    virtual void children_actual_parameter(Actual_parameter* in);
    virtual void children_new(New* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_foreign(FOREIGN* in);
    virtual void children_class_name(CLASS_NAME* in);
    virtual void children_interface_name(INTERFACE_NAME* in);
    virtual void children_method_name(METHOD_NAME* in);
    virtual void children_variable_name(VARIABLE_NAME* in);
    virtual void children_directive_name(DIRECTIVE_NAME* in);
    virtual void children_int(INT* in);
    virtual void children_real(REAL* in);
    virtual void children_string(STRING* in);
    virtual void children_bool(BOOL* in);
    virtual void children_nil(NIL* in);
    virtual void children_op(OP* in);
    virtual void children_cast(CAST* in);
    virtual void children_constant_name(CONSTANT_NAME* in);
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
    virtual void pre_if_chain(If* in);
    virtual void pre_while_chain(While* in);
    virtual void pre_do_chain(Do* in);
    virtual void pre_for_chain(For* in);
    virtual void pre_foreach_chain(Foreach* in);
    virtual void pre_switch_chain(Switch* in);
    virtual void pre_switch_case_chain(Switch_case* in);
    virtual void pre_break_chain(Break* in);
    virtual void pre_continue_chain(Continue* in);
    virtual void pre_return_chain(Return* in);
    virtual void pre_static_declaration_chain(Static_declaration* in);
    virtual void pre_global_chain(Global* in);
    virtual void pre_declare_chain(Declare* in);
    virtual void pre_directive_chain(Directive* in);
    virtual void pre_try_chain(Try* in);
    virtual void pre_catch_chain(Catch* in);
    virtual void pre_throw_chain(Throw* in);
    virtual void pre_eval_expr_chain(Eval_expr* in);
    virtual void pre_nop_chain(Nop* in);
    virtual void pre_assignment_chain(Assignment* in);
    virtual void pre_op_assignment_chain(Op_assignment* in);
    virtual void pre_list_assignment_chain(List_assignment* in);
    virtual void pre_nested_list_elements_chain(Nested_list_elements* in);
    virtual void pre_cast_chain(Cast* in);
    virtual void pre_unary_op_chain(Unary_op* in);
    virtual void pre_bin_op_chain(Bin_op* in);
    virtual void pre_conditional_expr_chain(Conditional_expr* in);
    virtual void pre_ignore_errors_chain(Ignore_errors* in);
    virtual void pre_constant_chain(Constant* in);
    virtual void pre_instanceof_chain(Instanceof* in);
    virtual void pre_variable_chain(Variable* in);
    virtual void pre_reflection_chain(Reflection* in);
    virtual void pre_pre_op_chain(Pre_op* in);
    virtual void pre_post_op_chain(Post_op* in);
    virtual void pre_array_chain(Array* in);
    virtual void pre_array_elem_chain(Array_elem* in);
    virtual void pre_method_invocation_chain(Method_invocation* in);
    virtual void pre_actual_parameter_chain(Actual_parameter* in);
    virtual void pre_new_chain(New* in);
    virtual void pre_foreign_chain(FOREIGN* in);
    virtual void pre_class_name_chain(CLASS_NAME* in);
    virtual void pre_interface_name_chain(INTERFACE_NAME* in);
    virtual void pre_method_name_chain(METHOD_NAME* in);
    virtual void pre_variable_name_chain(VARIABLE_NAME* in);
    virtual void pre_directive_name_chain(DIRECTIVE_NAME* in);
    virtual void pre_int_chain(INT* in);
    virtual void pre_real_chain(REAL* in);
    virtual void pre_string_chain(STRING* in);
    virtual void pre_bool_chain(BOOL* in);
    virtual void pre_nil_chain(NIL* in);
    virtual void pre_op_chain(OP* in);
    virtual void pre_cast_chain(CAST* in);
    virtual void pre_constant_name_chain(CONSTANT_NAME* in);
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
    virtual void post_if_chain(If* in);
    virtual void post_while_chain(While* in);
    virtual void post_do_chain(Do* in);
    virtual void post_for_chain(For* in);
    virtual void post_foreach_chain(Foreach* in);
    virtual void post_switch_chain(Switch* in);
    virtual void post_switch_case_chain(Switch_case* in);
    virtual void post_break_chain(Break* in);
    virtual void post_continue_chain(Continue* in);
    virtual void post_return_chain(Return* in);
    virtual void post_static_declaration_chain(Static_declaration* in);
    virtual void post_global_chain(Global* in);
    virtual void post_declare_chain(Declare* in);
    virtual void post_directive_chain(Directive* in);
    virtual void post_try_chain(Try* in);
    virtual void post_catch_chain(Catch* in);
    virtual void post_throw_chain(Throw* in);
    virtual void post_eval_expr_chain(Eval_expr* in);
    virtual void post_nop_chain(Nop* in);
    virtual void post_assignment_chain(Assignment* in);
    virtual void post_op_assignment_chain(Op_assignment* in);
    virtual void post_list_assignment_chain(List_assignment* in);
    virtual void post_nested_list_elements_chain(Nested_list_elements* in);
    virtual void post_cast_chain(Cast* in);
    virtual void post_unary_op_chain(Unary_op* in);
    virtual void post_bin_op_chain(Bin_op* in);
    virtual void post_conditional_expr_chain(Conditional_expr* in);
    virtual void post_ignore_errors_chain(Ignore_errors* in);
    virtual void post_constant_chain(Constant* in);
    virtual void post_instanceof_chain(Instanceof* in);
    virtual void post_variable_chain(Variable* in);
    virtual void post_reflection_chain(Reflection* in);
    virtual void post_pre_op_chain(Pre_op* in);
    virtual void post_post_op_chain(Post_op* in);
    virtual void post_array_chain(Array* in);
    virtual void post_array_elem_chain(Array_elem* in);
    virtual void post_method_invocation_chain(Method_invocation* in);
    virtual void post_actual_parameter_chain(Actual_parameter* in);
    virtual void post_new_chain(New* in);
    virtual void post_foreign_chain(FOREIGN* in);
    virtual void post_class_name_chain(CLASS_NAME* in);
    virtual void post_interface_name_chain(INTERFACE_NAME* in);
    virtual void post_method_name_chain(METHOD_NAME* in);
    virtual void post_variable_name_chain(VARIABLE_NAME* in);
    virtual void post_directive_name_chain(DIRECTIVE_NAME* in);
    virtual void post_int_chain(INT* in);
    virtual void post_real_chain(REAL* in);
    virtual void post_string_chain(STRING* in);
    virtual void post_bool_chain(BOOL* in);
    virtual void post_nil_chain(NIL* in);
    virtual void post_op_chain(OP* in);
    virtual void post_cast_chain(CAST* in);
    virtual void post_constant_name_chain(CONSTANT_NAME* in);
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
    virtual void visit_name_with_default_list(Name_with_default_list* in);
    virtual void visit_variable_name(VARIABLE_NAME* in);
    virtual void visit_expr(Expr* in);
    virtual void visit_variable(Variable* in);
    virtual void visit_switch_case_list(Switch_case_list* in);
    virtual void visit_switch_case(Switch_case* in);
    virtual void visit_variable_name_list(Variable_name_list* in);
    virtual void visit_directive_list(Directive_list* in);
    virtual void visit_directive(Directive* in);
    virtual void visit_directive_name(DIRECTIVE_NAME* in);
    virtual void visit_catch_list(Catch_list* in);
    virtual void visit_catch(Catch* in);
    virtual void visit_op(OP* in);
    virtual void visit_list_element_list(List_element_list* in);
    virtual void visit_list_element(List_element* in);
    virtual void visit_cast(CAST* in);
    virtual void visit_constant_name(CONSTANT_NAME* in);
    virtual void visit_class_name(Class_name* in);
    virtual void visit_target(Target* in);
    virtual void visit_variable_name(Variable_name* in);
    virtual void visit_expr_list(Expr_list* in);
    virtual void visit_array_elem_list(Array_elem_list* in);
    virtual void visit_array_elem(Array_elem* in);
    virtual void visit_method_name(Method_name* in);
    virtual void visit_actual_parameter_list(Actual_parameter_list* in);
    virtual void visit_actual_parameter(Actual_parameter* in);
    virtual void visit_php_script(PHP_script* in);
/* Invoke the right pre-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_statement_chain(Statement* in);
    virtual void pre_member_chain(Member* in);
    virtual void pre_expr_chain(Expr* in);
    virtual void pre_variable_name_chain(Variable_name* in);
    virtual void pre_list_element_chain(List_element* in);
    virtual void pre_class_name_chain(Class_name* in);
    virtual void pre_target_chain(Target* in);
    virtual void pre_method_name_chain(Method_name* in);
/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_statement_chain(Statement* in);
    virtual void post_member_chain(Member* in);
    virtual void post_expr_chain(Expr* in);
    virtual void post_variable_name_chain(Variable_name* in);
    virtual void post_list_element_chain(List_element* in);
    virtual void post_class_name_chain(Class_name* in);
    virtual void post_target_chain(Target* in);
    virtual void post_method_name_chain(Method_name* in);
/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void children_statement(Statement* in);
    virtual void children_member(Member* in);
    virtual void children_expr(Expr* in);
    virtual void children_variable_name(Variable_name* in);
    virtual void children_list_element(List_element* in);
    virtual void children_class_name(Class_name* in);
    virtual void children_target(Target* in);
    virtual void children_method_name(Method_name* in);
};
}


#endif
