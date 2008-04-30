#include "MIR_visitor.h"

namespace MIR{
Visitor::~Visitor()
{
}

// Invoked before the children are visited
void Visitor::pre_node(Node* in)
{
}

void Visitor::pre_php_script(PHP_script* in)
{
}

void Visitor::pre_statement(Statement* in)
{
}

void Visitor::pre_class_def(Class_def* in)
{
}

void Visitor::pre_class_mod(Class_mod* in)
{
}

void Visitor::pre_interface_def(Interface_def* in)
{
}

void Visitor::pre_member(Member* in)
{
}

void Visitor::pre_method(Method* in)
{
}

void Visitor::pre_signature(Signature* in)
{
}

void Visitor::pre_method_mod(Method_mod* in)
{
}

void Visitor::pre_formal_parameter(Formal_parameter* in)
{
}

void Visitor::pre_type(Type* in)
{
}

void Visitor::pre_attribute(Attribute* in)
{
}

void Visitor::pre_attr_mod(Attr_mod* in)
{
}

void Visitor::pre_name_with_default(Name_with_default* in)
{
}

void Visitor::pre_return(Return* in)
{
}

void Visitor::pre_static_declaration(Static_declaration* in)
{
}

void Visitor::pre_global(Global* in)
{
}

void Visitor::pre_try(Try* in)
{
}

void Visitor::pre_catch(Catch* in)
{
}

void Visitor::pre_throw(Throw* in)
{
}

void Visitor::pre_eval_expr(Eval_expr* in)
{
}

void Visitor::pre_branch(Branch* in)
{
}

void Visitor::pre_goto(Goto* in)
{
}

void Visitor::pre_label(Label* in)
{
}

void Visitor::pre_foreach_reset(Foreach_reset* in)
{
}

void Visitor::pre_foreach_next(Foreach_next* in)
{
}

void Visitor::pre_foreach_end(Foreach_end* in)
{
}

void Visitor::pre_foreach_has_key(Foreach_has_key* in)
{
}

void Visitor::pre_foreach_get_key(Foreach_get_key* in)
{
}

void Visitor::pre_foreach_get_val(Foreach_get_val* in)
{
}

void Visitor::pre_expr(Expr* in)
{
}

void Visitor::pre_literal(Literal* in)
{
}

void Visitor::pre_assignment(Assignment* in)
{
}

void Visitor::pre_cast(Cast* in)
{
}

void Visitor::pre_unary_op(Unary_op* in)
{
}

void Visitor::pre_bin_op(Bin_op* in)
{
}

void Visitor::pre_constant(Constant* in)
{
}

void Visitor::pre_instanceof(Instanceof* in)
{
}

void Visitor::pre_variable(Variable* in)
{
}

void Visitor::pre_variable_name(Variable_name* in)
{
}

void Visitor::pre_reflection(Reflection* in)
{
}

void Visitor::pre_target(Target* in)
{
}

void Visitor::pre_pre_op(Pre_op* in)
{
}

void Visitor::pre_array(Array* in)
{
}

void Visitor::pre_array_elem(Array_elem* in)
{
}

void Visitor::pre_method_invocation(Method_invocation* in)
{
}

void Visitor::pre_method_name(Method_name* in)
{
}

void Visitor::pre_actual_parameter(Actual_parameter* in)
{
}

void Visitor::pre_new(New* in)
{
}

void Visitor::pre_class_name(Class_name* in)
{
}

void Visitor::pre_identifier(Identifier* in)
{
}

void Visitor::pre_ht_iterator(HT_ITERATOR* in)
{
}

void Visitor::pre_class_name(CLASS_NAME* in)
{
}

void Visitor::pre_interface_name(INTERFACE_NAME* in)
{
}

void Visitor::pre_method_name(METHOD_NAME* in)
{
}

void Visitor::pre_variable_name(VARIABLE_NAME* in)
{
}

void Visitor::pre_label_name(LABEL_NAME* in)
{
}

void Visitor::pre_int(INT* in)
{
}

void Visitor::pre_real(REAL* in)
{
}

void Visitor::pre_string(STRING* in)
{
}

void Visitor::pre_bool(BOOL* in)
{
}

void Visitor::pre_nil(NIL* in)
{
}

void Visitor::pre_cast(CAST* in)
{
}

void Visitor::pre_op(OP* in)
{
}

void Visitor::pre_constant_name(CONSTANT_NAME* in)
{
}

// Invoked after the children have been visited
void Visitor::post_node(Node* in)
{
}

void Visitor::post_php_script(PHP_script* in)
{
}

void Visitor::post_statement(Statement* in)
{
}

void Visitor::post_class_def(Class_def* in)
{
}

void Visitor::post_class_mod(Class_mod* in)
{
}

void Visitor::post_interface_def(Interface_def* in)
{
}

void Visitor::post_member(Member* in)
{
}

void Visitor::post_method(Method* in)
{
}

void Visitor::post_signature(Signature* in)
{
}

void Visitor::post_method_mod(Method_mod* in)
{
}

void Visitor::post_formal_parameter(Formal_parameter* in)
{
}

void Visitor::post_type(Type* in)
{
}

void Visitor::post_attribute(Attribute* in)
{
}

void Visitor::post_attr_mod(Attr_mod* in)
{
}

void Visitor::post_name_with_default(Name_with_default* in)
{
}

void Visitor::post_return(Return* in)
{
}

void Visitor::post_static_declaration(Static_declaration* in)
{
}

void Visitor::post_global(Global* in)
{
}

void Visitor::post_try(Try* in)
{
}

void Visitor::post_catch(Catch* in)
{
}

void Visitor::post_throw(Throw* in)
{
}

void Visitor::post_eval_expr(Eval_expr* in)
{
}

void Visitor::post_branch(Branch* in)
{
}

void Visitor::post_goto(Goto* in)
{
}

void Visitor::post_label(Label* in)
{
}

void Visitor::post_foreach_reset(Foreach_reset* in)
{
}

void Visitor::post_foreach_next(Foreach_next* in)
{
}

void Visitor::post_foreach_end(Foreach_end* in)
{
}

void Visitor::post_foreach_has_key(Foreach_has_key* in)
{
}

void Visitor::post_foreach_get_key(Foreach_get_key* in)
{
}

void Visitor::post_foreach_get_val(Foreach_get_val* in)
{
}

void Visitor::post_expr(Expr* in)
{
}

void Visitor::post_literal(Literal* in)
{
}

void Visitor::post_assignment(Assignment* in)
{
}

void Visitor::post_cast(Cast* in)
{
}

void Visitor::post_unary_op(Unary_op* in)
{
}

void Visitor::post_bin_op(Bin_op* in)
{
}

void Visitor::post_constant(Constant* in)
{
}

void Visitor::post_instanceof(Instanceof* in)
{
}

void Visitor::post_variable(Variable* in)
{
}

void Visitor::post_variable_name(Variable_name* in)
{
}

void Visitor::post_reflection(Reflection* in)
{
}

void Visitor::post_target(Target* in)
{
}

void Visitor::post_pre_op(Pre_op* in)
{
}

void Visitor::post_array(Array* in)
{
}

void Visitor::post_array_elem(Array_elem* in)
{
}

void Visitor::post_method_invocation(Method_invocation* in)
{
}

void Visitor::post_method_name(Method_name* in)
{
}

void Visitor::post_actual_parameter(Actual_parameter* in)
{
}

void Visitor::post_new(New* in)
{
}

void Visitor::post_class_name(Class_name* in)
{
}

void Visitor::post_identifier(Identifier* in)
{
}

void Visitor::post_ht_iterator(HT_ITERATOR* in)
{
}

void Visitor::post_class_name(CLASS_NAME* in)
{
}

void Visitor::post_interface_name(INTERFACE_NAME* in)
{
}

void Visitor::post_method_name(METHOD_NAME* in)
{
}

void Visitor::post_variable_name(VARIABLE_NAME* in)
{
}

void Visitor::post_label_name(LABEL_NAME* in)
{
}

void Visitor::post_int(INT* in)
{
}

void Visitor::post_real(REAL* in)
{
}

void Visitor::post_string(STRING* in)
{
}

void Visitor::post_bool(BOOL* in)
{
}

void Visitor::post_nil(NIL* in)
{
}

void Visitor::post_cast(CAST* in)
{
}

void Visitor::post_op(OP* in)
{
}

void Visitor::post_constant_name(CONSTANT_NAME* in)
{
}

// Visit the children of a node
void Visitor::children_php_script(PHP_script* in)
{
    visit_statement_list(in->statements);
}

void Visitor::children_class_def(Class_def* in)
{
    visit_class_mod(in->class_mod);
    visit_class_name(in->class_name);
    visit_class_name(in->extends);
    visit_interface_name_list(in->implements);
    visit_member_list(in->members);
}

void Visitor::children_class_mod(Class_mod* in)
{
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void Visitor::children_interface_def(Interface_def* in)
{
    visit_interface_name(in->interface_name);
    visit_interface_name_list(in->extends);
    visit_member_list(in->members);
}

void Visitor::children_method(Method* in)
{
    visit_signature(in->signature);
    visit_statement_list(in->statements);
}

void Visitor::children_signature(Signature* in)
{
    visit_method_mod(in->method_mod);
    visit_marker("is_ref", in->is_ref);
    visit_method_name(in->method_name);
    visit_formal_parameter_list(in->formal_parameters);
}

void Visitor::children_method_mod(Method_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_abstract", in->is_abstract);
    visit_marker("is_final", in->is_final);
}

void Visitor::children_formal_parameter(Formal_parameter* in)
{
    visit_type(in->type);
    visit_marker("is_ref", in->is_ref);
    visit_name_with_default(in->var);
}

void Visitor::children_type(Type* in)
{
    visit_class_name(in->class_name);
}

void Visitor::children_attribute(Attribute* in)
{
    visit_attr_mod(in->attr_mod);
    visit_name_with_default(in->var);
}

void Visitor::children_attr_mod(Attr_mod* in)
{
    visit_marker("is_public", in->is_public);
    visit_marker("is_protected", in->is_protected);
    visit_marker("is_private", in->is_private);
    visit_marker("is_static", in->is_static);
    visit_marker("is_const", in->is_const);
}

void Visitor::children_name_with_default(Name_with_default* in)
{
    visit_variable_name(in->variable_name);
    visit_expr(in->expr);
}

void Visitor::children_return(Return* in)
{
    visit_expr(in->expr);
}

void Visitor::children_static_declaration(Static_declaration* in)
{
    visit_name_with_default(in->var);
}

void Visitor::children_global(Global* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_try(Try* in)
{
    visit_statement_list(in->statements);
    visit_catch_list(in->catches);
}

void Visitor::children_catch(Catch* in)
{
    visit_class_name(in->class_name);
    visit_variable_name(in->variable_name);
    visit_statement_list(in->statements);
}

void Visitor::children_throw(Throw* in)
{
    visit_expr(in->expr);
}

void Visitor::children_eval_expr(Eval_expr* in)
{
    visit_expr(in->expr);
}

void Visitor::children_branch(Branch* in)
{
    visit_variable_name(in->variable_name);
    visit_label_name(in->iftrue);
    visit_label_name(in->iffalse);
}

void Visitor::children_goto(Goto* in)
{
    visit_label_name(in->label_name);
}

void Visitor::children_label(Label* in)
{
    visit_label_name(in->label_name);
}

void Visitor::children_foreach_reset(Foreach_reset* in)
{
    visit_variable_name(in->array);
    visit_ht_iterator(in->iter);
}

void Visitor::children_foreach_next(Foreach_next* in)
{
    visit_variable_name(in->array);
    visit_ht_iterator(in->iter);
}

void Visitor::children_foreach_end(Foreach_end* in)
{
    visit_variable_name(in->array);
    visit_ht_iterator(in->iter);
}

void Visitor::children_foreach_has_key(Foreach_has_key* in)
{
    visit_variable_name(in->array);
    visit_ht_iterator(in->iter);
}

void Visitor::children_foreach_get_key(Foreach_get_key* in)
{
    visit_variable_name(in->array);
    visit_ht_iterator(in->iter);
}

void Visitor::children_foreach_get_val(Foreach_get_val* in)
{
    visit_variable_name(in->array);
    visit_variable_name(in->key);
    visit_ht_iterator(in->iter);
}

void Visitor::children_assignment(Assignment* in)
{
    visit_variable(in->variable);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->expr);
}

void Visitor::children_cast(Cast* in)
{
    visit_cast(in->cast);
    visit_variable_name(in->variable_name);
}

void Visitor::children_unary_op(Unary_op* in)
{
    visit_op(in->op);
    visit_variable_name(in->variable_name);
}

void Visitor::children_bin_op(Bin_op* in)
{
    visit_variable_name(in->left);
    visit_op(in->op);
    visit_variable_name(in->right);
}

void Visitor::children_constant(Constant* in)
{
    visit_class_name(in->class_name);
    visit_constant_name(in->constant_name);
}

void Visitor::children_instanceof(Instanceof* in)
{
    visit_variable_name(in->variable_name);
    visit_class_name(in->class_name);
}

void Visitor::children_variable(Variable* in)
{
    visit_target(in->target);
    visit_variable_name(in->variable_name);
    visit_variable_name_list(in->array_indices);
}

void Visitor::children_reflection(Reflection* in)
{
    visit_variable_name(in->variable_name);
}

void Visitor::children_pre_op(Pre_op* in)
{
    visit_op(in->op);
    visit_variable(in->variable);
}

void Visitor::children_array(Array* in)
{
    visit_array_elem_list(in->array_elems);
}

void Visitor::children_array_elem(Array_elem* in)
{
    visit_expr(in->key);
    visit_marker("is_ref", in->is_ref);
    visit_expr(in->val);
}

void Visitor::children_method_invocation(Method_invocation* in)
{
    visit_target(in->target);
    visit_method_name(in->method_name);
    visit_actual_parameter_list(in->actual_parameters);
}

void Visitor::children_actual_parameter(Actual_parameter* in)
{
    visit_marker("is_ref", in->is_ref);
    visit_target(in->target);
    visit_variable_name(in->variable_name);
    visit_variable_name_list(in->array_indices);
}

void Visitor::children_new(New* in)
{
    visit_class_name(in->class_name);
    visit_actual_parameter_list(in->actual_parameters);
}

// Tokens don't have children, so these methods do nothing by default
void Visitor::children_ht_iterator(HT_ITERATOR* in)
{
}

void Visitor::children_class_name(CLASS_NAME* in)
{
}

void Visitor::children_interface_name(INTERFACE_NAME* in)
{
}

void Visitor::children_method_name(METHOD_NAME* in)
{
}

void Visitor::children_variable_name(VARIABLE_NAME* in)
{
}

void Visitor::children_label_name(LABEL_NAME* in)
{
}

void Visitor::children_int(INT* in)
{
}

void Visitor::children_real(REAL* in)
{
}

void Visitor::children_string(STRING* in)
{
}

void Visitor::children_bool(BOOL* in)
{
}

void Visitor::children_nil(NIL* in)
{
}

void Visitor::children_cast(CAST* in)
{
}

void Visitor::children_op(OP* in)
{
}

void Visitor::children_constant_name(CONSTANT_NAME* in)
{
}

// Unparser support
void Visitor::visit_marker(char const* name, bool value)
{
}

void Visitor::visit_null(char const* name_space, char const* type_id)
{
}

void Visitor::visit_null_list(char const* name_space, char const* type_id)
{
}

void Visitor::pre_list(char const* name_space, char const* type_id, int size)
{
}

void Visitor::post_list(char const* name_space, char const* type_id, int size)
{
}

// Invoke the chain of pre-visit methods along the inheritance hierachy
// Do not override unless you know what you are doing
void Visitor::pre_php_script_chain(PHP_script* in)
{
    pre_node((Node*) in);
    pre_php_script((PHP_script*) in);
}

void Visitor::pre_class_def_chain(Class_def* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_class_def((Class_def*) in);
}

void Visitor::pre_class_mod_chain(Class_mod* in)
{
    pre_node((Node*) in);
    pre_class_mod((Class_mod*) in);
}

void Visitor::pre_interface_def_chain(Interface_def* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_interface_def((Interface_def*) in);
}

void Visitor::pre_method_chain(Method* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_member((Member*) in);
    pre_method((Method*) in);
}

void Visitor::pre_signature_chain(Signature* in)
{
    pre_node((Node*) in);
    pre_signature((Signature*) in);
}

void Visitor::pre_method_mod_chain(Method_mod* in)
{
    pre_node((Node*) in);
    pre_method_mod((Method_mod*) in);
}

void Visitor::pre_formal_parameter_chain(Formal_parameter* in)
{
    pre_node((Node*) in);
    pre_formal_parameter((Formal_parameter*) in);
}

void Visitor::pre_type_chain(Type* in)
{
    pre_node((Node*) in);
    pre_type((Type*) in);
}

void Visitor::pre_attribute_chain(Attribute* in)
{
    pre_node((Node*) in);
    pre_member((Member*) in);
    pre_attribute((Attribute*) in);
}

void Visitor::pre_attr_mod_chain(Attr_mod* in)
{
    pre_node((Node*) in);
    pre_attr_mod((Attr_mod*) in);
}

void Visitor::pre_name_with_default_chain(Name_with_default* in)
{
    pre_node((Node*) in);
    pre_name_with_default((Name_with_default*) in);
}

void Visitor::pre_return_chain(Return* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_return((Return*) in);
}

void Visitor::pre_static_declaration_chain(Static_declaration* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_static_declaration((Static_declaration*) in);
}

void Visitor::pre_global_chain(Global* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_global((Global*) in);
}

void Visitor::pre_try_chain(Try* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_try((Try*) in);
}

void Visitor::pre_catch_chain(Catch* in)
{
    pre_node((Node*) in);
    pre_catch((Catch*) in);
}

void Visitor::pre_throw_chain(Throw* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_throw((Throw*) in);
}

void Visitor::pre_eval_expr_chain(Eval_expr* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_eval_expr((Eval_expr*) in);
}

void Visitor::pre_branch_chain(Branch* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_branch((Branch*) in);
}

void Visitor::pre_goto_chain(Goto* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_goto((Goto*) in);
}

void Visitor::pre_label_chain(Label* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_label((Label*) in);
}

void Visitor::pre_foreach_reset_chain(Foreach_reset* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_foreach_reset((Foreach_reset*) in);
}

void Visitor::pre_foreach_next_chain(Foreach_next* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_foreach_next((Foreach_next*) in);
}

void Visitor::pre_foreach_end_chain(Foreach_end* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_foreach_end((Foreach_end*) in);
}

void Visitor::pre_foreach_has_key_chain(Foreach_has_key* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_foreach_has_key((Foreach_has_key*) in);
}

void Visitor::pre_foreach_get_key_chain(Foreach_get_key* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_foreach_get_key((Foreach_get_key*) in);
}

void Visitor::pre_foreach_get_val_chain(Foreach_get_val* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_foreach_get_val((Foreach_get_val*) in);
}

void Visitor::pre_assignment_chain(Assignment* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_assignment((Assignment*) in);
}

void Visitor::pre_cast_chain(Cast* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_cast((Cast*) in);
}

void Visitor::pre_unary_op_chain(Unary_op* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_unary_op((Unary_op*) in);
}

void Visitor::pre_bin_op_chain(Bin_op* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_bin_op((Bin_op*) in);
}

void Visitor::pre_constant_chain(Constant* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_constant((Constant*) in);
}

void Visitor::pre_instanceof_chain(Instanceof* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_instanceof((Instanceof*) in);
}

void Visitor::pre_variable_chain(Variable* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_variable((Variable*) in);
}

void Visitor::pre_reflection_chain(Reflection* in)
{
    pre_node((Node*) in);
    pre_variable_name((Variable_name*) in);
    pre_method_name((Method_name*) in);
    pre_class_name((Class_name*) in);
    pre_reflection((Reflection*) in);
}

void Visitor::pre_pre_op_chain(Pre_op* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_pre_op((Pre_op*) in);
}

void Visitor::pre_array_chain(Array* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_array((Array*) in);
}

void Visitor::pre_array_elem_chain(Array_elem* in)
{
    pre_node((Node*) in);
    pre_array_elem((Array_elem*) in);
}

void Visitor::pre_method_invocation_chain(Method_invocation* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_method_invocation((Method_invocation*) in);
}

void Visitor::pre_actual_parameter_chain(Actual_parameter* in)
{
    pre_node((Node*) in);
    pre_actual_parameter((Actual_parameter*) in);
}

void Visitor::pre_new_chain(New* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_new((New*) in);
}

void Visitor::pre_ht_iterator_chain(HT_ITERATOR* in)
{
    pre_node((Node*) in);
    pre_ht_iterator((HT_ITERATOR*) in);
}

void Visitor::pre_class_name_chain(CLASS_NAME* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_class_name((Class_name*) in);
    pre_identifier((Identifier*) in);
    pre_class_name((CLASS_NAME*) in);
}

void Visitor::pre_interface_name_chain(INTERFACE_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_interface_name((INTERFACE_NAME*) in);
}

void Visitor::pre_method_name_chain(METHOD_NAME* in)
{
    pre_node((Node*) in);
    pre_method_name((Method_name*) in);
    pre_identifier((Identifier*) in);
    pre_method_name((METHOD_NAME*) in);
}

void Visitor::pre_variable_name_chain(VARIABLE_NAME* in)
{
    pre_node((Node*) in);
    pre_variable_name((Variable_name*) in);
    pre_identifier((Identifier*) in);
    pre_variable_name((VARIABLE_NAME*) in);
}

void Visitor::pre_label_name_chain(LABEL_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_label_name((LABEL_NAME*) in);
}

void Visitor::pre_int_chain(INT* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_literal((Literal*) in);
    pre_int((INT*) in);
}

void Visitor::pre_real_chain(REAL* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_literal((Literal*) in);
    pre_real((REAL*) in);
}

void Visitor::pre_string_chain(STRING* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_literal((Literal*) in);
    pre_string((STRING*) in);
}

void Visitor::pre_bool_chain(BOOL* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_literal((Literal*) in);
    pre_bool((BOOL*) in);
}

void Visitor::pre_nil_chain(NIL* in)
{
    pre_node((Node*) in);
    pre_target((Target*) in);
    pre_expr((Expr*) in);
    pre_literal((Literal*) in);
    pre_nil((NIL*) in);
}

void Visitor::pre_cast_chain(CAST* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_cast((CAST*) in);
}

void Visitor::pre_op_chain(OP* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_op((OP*) in);
}

void Visitor::pre_constant_name_chain(CONSTANT_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_constant_name((CONSTANT_NAME*) in);
}

// Invoke the chain of post-visit methods along the inheritance hierarchy
// (invoked in opposite order to the pre-chain)
// Do not override unless you know what you are doing
void Visitor::post_php_script_chain(PHP_script* in)
{
    post_php_script((PHP_script*) in);
    post_node((Node*) in);
}

void Visitor::post_class_def_chain(Class_def* in)
{
    post_class_def((Class_def*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_class_mod_chain(Class_mod* in)
{
    post_class_mod((Class_mod*) in);
    post_node((Node*) in);
}

void Visitor::post_interface_def_chain(Interface_def* in)
{
    post_interface_def((Interface_def*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_method_chain(Method* in)
{
    post_method((Method*) in);
    post_member((Member*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_signature_chain(Signature* in)
{
    post_signature((Signature*) in);
    post_node((Node*) in);
}

void Visitor::post_method_mod_chain(Method_mod* in)
{
    post_method_mod((Method_mod*) in);
    post_node((Node*) in);
}

void Visitor::post_formal_parameter_chain(Formal_parameter* in)
{
    post_formal_parameter((Formal_parameter*) in);
    post_node((Node*) in);
}

void Visitor::post_type_chain(Type* in)
{
    post_type((Type*) in);
    post_node((Node*) in);
}

void Visitor::post_attribute_chain(Attribute* in)
{
    post_attribute((Attribute*) in);
    post_member((Member*) in);
    post_node((Node*) in);
}

void Visitor::post_attr_mod_chain(Attr_mod* in)
{
    post_attr_mod((Attr_mod*) in);
    post_node((Node*) in);
}

void Visitor::post_name_with_default_chain(Name_with_default* in)
{
    post_name_with_default((Name_with_default*) in);
    post_node((Node*) in);
}

void Visitor::post_return_chain(Return* in)
{
    post_return((Return*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_static_declaration_chain(Static_declaration* in)
{
    post_static_declaration((Static_declaration*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_global_chain(Global* in)
{
    post_global((Global*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_try_chain(Try* in)
{
    post_try((Try*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_catch_chain(Catch* in)
{
    post_catch((Catch*) in);
    post_node((Node*) in);
}

void Visitor::post_throw_chain(Throw* in)
{
    post_throw((Throw*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_eval_expr_chain(Eval_expr* in)
{
    post_eval_expr((Eval_expr*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_branch_chain(Branch* in)
{
    post_branch((Branch*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_goto_chain(Goto* in)
{
    post_goto((Goto*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_label_chain(Label* in)
{
    post_label((Label*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_reset_chain(Foreach_reset* in)
{
    post_foreach_reset((Foreach_reset*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_next_chain(Foreach_next* in)
{
    post_foreach_next((Foreach_next*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_end_chain(Foreach_end* in)
{
    post_foreach_end((Foreach_end*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_has_key_chain(Foreach_has_key* in)
{
    post_foreach_has_key((Foreach_has_key*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_get_key_chain(Foreach_get_key* in)
{
    post_foreach_get_key((Foreach_get_key*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_foreach_get_val_chain(Foreach_get_val* in)
{
    post_foreach_get_val((Foreach_get_val*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_assignment_chain(Assignment* in)
{
    post_assignment((Assignment*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_cast_chain(Cast* in)
{
    post_cast((Cast*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_unary_op_chain(Unary_op* in)
{
    post_unary_op((Unary_op*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_bin_op_chain(Bin_op* in)
{
    post_bin_op((Bin_op*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_constant_chain(Constant* in)
{
    post_constant((Constant*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_instanceof_chain(Instanceof* in)
{
    post_instanceof((Instanceof*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_variable_chain(Variable* in)
{
    post_variable((Variable*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_reflection_chain(Reflection* in)
{
    post_reflection((Reflection*) in);
    post_class_name((Class_name*) in);
    post_method_name((Method_name*) in);
    post_variable_name((Variable_name*) in);
    post_node((Node*) in);
}

void Visitor::post_pre_op_chain(Pre_op* in)
{
    post_pre_op((Pre_op*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_array_chain(Array* in)
{
    post_array((Array*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_array_elem_chain(Array_elem* in)
{
    post_array_elem((Array_elem*) in);
    post_node((Node*) in);
}

void Visitor::post_method_invocation_chain(Method_invocation* in)
{
    post_method_invocation((Method_invocation*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_actual_parameter_chain(Actual_parameter* in)
{
    post_actual_parameter((Actual_parameter*) in);
    post_node((Node*) in);
}

void Visitor::post_new_chain(New* in)
{
    post_new((New*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_ht_iterator_chain(HT_ITERATOR* in)
{
    post_ht_iterator((HT_ITERATOR*) in);
    post_node((Node*) in);
}

void Visitor::post_class_name_chain(CLASS_NAME* in)
{
    post_class_name((CLASS_NAME*) in);
    post_identifier((Identifier*) in);
    post_class_name((Class_name*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_interface_name_chain(INTERFACE_NAME* in)
{
    post_interface_name((INTERFACE_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_method_name_chain(METHOD_NAME* in)
{
    post_method_name((METHOD_NAME*) in);
    post_identifier((Identifier*) in);
    post_method_name((Method_name*) in);
    post_node((Node*) in);
}

void Visitor::post_variable_name_chain(VARIABLE_NAME* in)
{
    post_variable_name((VARIABLE_NAME*) in);
    post_identifier((Identifier*) in);
    post_variable_name((Variable_name*) in);
    post_node((Node*) in);
}

void Visitor::post_label_name_chain(LABEL_NAME* in)
{
    post_label_name((LABEL_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_int_chain(INT* in)
{
    post_int((INT*) in);
    post_literal((Literal*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_real_chain(REAL* in)
{
    post_real((REAL*) in);
    post_literal((Literal*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_string_chain(STRING* in)
{
    post_string((STRING*) in);
    post_literal((Literal*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_bool_chain(BOOL* in)
{
    post_bool((BOOL*) in);
    post_literal((Literal*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_nil_chain(NIL* in)
{
    post_nil((NIL*) in);
    post_literal((Literal*) in);
    post_expr((Expr*) in);
    post_target((Target*) in);
    post_node((Node*) in);
}

void Visitor::post_cast_chain(CAST* in)
{
    post_cast((CAST*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_op_chain(OP* in)
{
    post_op((OP*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_constant_name_chain(CONSTANT_NAME* in)
{
    post_constant_name((CONSTANT_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

// Call the pre-chain, visit children and post-chain in order
// Do not override unless you know what you are doing
void Visitor::visit_statement_list(List<Statement*>* in)
{
    List<Statement*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "Statement");
    else
    {
    	pre_list("MIR", "Statement", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_statement(*i);
    	}
    
    	post_list("MIR", "Statement", in->size());
    }
}

void Visitor::visit_statement(Statement* in)
{
    if(in == NULL)
    	visit_null("MIR", "Statement");
    else
    {
    	pre_statement_chain(in);
    	children_statement(in);
    	post_statement_chain(in);
    }
}

void Visitor::visit_class_mod(Class_mod* in)
{
    if(in == NULL)
    	visit_null("MIR", "Class_mod");
    else
    {
    	pre_class_mod_chain(in);
    	children_class_mod(in);
    	post_class_mod_chain(in);
    }
}

void Visitor::visit_class_name(CLASS_NAME* in)
{
    if(in == NULL)
    	visit_null("MIR", "CLASS_NAME");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void Visitor::visit_interface_name_list(List<INTERFACE_NAME*>* in)
{
    List<INTERFACE_NAME*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "INTERFACE_NAME");
    else
    {
    	pre_list("MIR", "INTERFACE_NAME", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_interface_name(*i);
    	}
    
    	post_list("MIR", "INTERFACE_NAME", in->size());
    }
}

void Visitor::visit_member_list(List<Member*>* in)
{
    List<Member*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "Member");
    else
    {
    	pre_list("MIR", "Member", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_member(*i);
    	}
    
    	post_list("MIR", "Member", in->size());
    }
}

void Visitor::visit_member(Member* in)
{
    if(in == NULL)
    	visit_null("MIR", "Member");
    else
    {
    	pre_member_chain(in);
    	children_member(in);
    	post_member_chain(in);
    }
}

void Visitor::visit_interface_name(INTERFACE_NAME* in)
{
    if(in == NULL)
    	visit_null("MIR", "INTERFACE_NAME");
    else
    {
    	pre_interface_name_chain(in);
    	children_interface_name(in);
    	post_interface_name_chain(in);
    }
}

void Visitor::visit_signature(Signature* in)
{
    if(in == NULL)
    	visit_null("MIR", "Signature");
    else
    {
    	pre_signature_chain(in);
    	children_signature(in);
    	post_signature_chain(in);
    }
}

void Visitor::visit_method_mod(Method_mod* in)
{
    if(in == NULL)
    	visit_null("MIR", "Method_mod");
    else
    {
    	pre_method_mod_chain(in);
    	children_method_mod(in);
    	post_method_mod_chain(in);
    }
}

void Visitor::visit_method_name(METHOD_NAME* in)
{
    if(in == NULL)
    	visit_null("MIR", "METHOD_NAME");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void Visitor::visit_formal_parameter_list(List<Formal_parameter*>* in)
{
    List<Formal_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "Formal_parameter");
    else
    {
    	pre_list("MIR", "Formal_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_formal_parameter(*i);
    	}
    
    	post_list("MIR", "Formal_parameter", in->size());
    }
}

void Visitor::visit_formal_parameter(Formal_parameter* in)
{
    if(in == NULL)
    	visit_null("MIR", "Formal_parameter");
    else
    {
    	pre_formal_parameter_chain(in);
    	children_formal_parameter(in);
    	post_formal_parameter_chain(in);
    }
}

void Visitor::visit_type(Type* in)
{
    if(in == NULL)
    	visit_null("MIR", "Type");
    else
    {
    	pre_type_chain(in);
    	children_type(in);
    	post_type_chain(in);
    }
}

void Visitor::visit_name_with_default(Name_with_default* in)
{
    if(in == NULL)
    	visit_null("MIR", "Name_with_default");
    else
    {
    	pre_name_with_default_chain(in);
    	children_name_with_default(in);
    	post_name_with_default_chain(in);
    }
}

void Visitor::visit_attr_mod(Attr_mod* in)
{
    if(in == NULL)
    	visit_null("MIR", "Attr_mod");
    else
    {
    	pre_attr_mod_chain(in);
    	children_attr_mod(in);
    	post_attr_mod_chain(in);
    }
}

void Visitor::visit_variable_name(VARIABLE_NAME* in)
{
    if(in == NULL)
    	visit_null("MIR", "VARIABLE_NAME");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void Visitor::visit_expr(Expr* in)
{
    if(in == NULL)
    	visit_null("MIR", "Expr");
    else
    {
    	pre_expr_chain(in);
    	children_expr(in);
    	post_expr_chain(in);
    }
}

void Visitor::visit_variable_name(Variable_name* in)
{
    if(in == NULL)
    	visit_null("MIR", "Variable_name");
    else
    {
    	pre_variable_name_chain(in);
    	children_variable_name(in);
    	post_variable_name_chain(in);
    }
}

void Visitor::visit_catch_list(List<Catch*>* in)
{
    List<Catch*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "Catch");
    else
    {
    	pre_list("MIR", "Catch", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_catch(*i);
    	}
    
    	post_list("MIR", "Catch", in->size());
    }
}

void Visitor::visit_catch(Catch* in)
{
    if(in == NULL)
    	visit_null("MIR", "Catch");
    else
    {
    	pre_catch_chain(in);
    	children_catch(in);
    	post_catch_chain(in);
    }
}

void Visitor::visit_label_name(LABEL_NAME* in)
{
    if(in == NULL)
    	visit_null("MIR", "LABEL_NAME");
    else
    {
    	pre_label_name_chain(in);
    	children_label_name(in);
    	post_label_name_chain(in);
    }
}

void Visitor::visit_ht_iterator(HT_ITERATOR* in)
{
    if(in == NULL)
    	visit_null("MIR", "HT_ITERATOR");
    else
    {
    	pre_ht_iterator_chain(in);
    	children_ht_iterator(in);
    	post_ht_iterator_chain(in);
    }
}

void Visitor::visit_variable(Variable* in)
{
    if(in == NULL)
    	visit_null("MIR", "Variable");
    else
    {
    	pre_variable_chain(in);
    	children_variable(in);
    	post_variable_chain(in);
    }
}

void Visitor::visit_cast(CAST* in)
{
    if(in == NULL)
    	visit_null("MIR", "CAST");
    else
    {
    	pre_cast_chain(in);
    	children_cast(in);
    	post_cast_chain(in);
    }
}

void Visitor::visit_op(OP* in)
{
    if(in == NULL)
    	visit_null("MIR", "OP");
    else
    {
    	pre_op_chain(in);
    	children_op(in);
    	post_op_chain(in);
    }
}

void Visitor::visit_constant_name(CONSTANT_NAME* in)
{
    if(in == NULL)
    	visit_null("MIR", "CONSTANT_NAME");
    else
    {
    	pre_constant_name_chain(in);
    	children_constant_name(in);
    	post_constant_name_chain(in);
    }
}

void Visitor::visit_class_name(Class_name* in)
{
    if(in == NULL)
    	visit_null("MIR", "Class_name");
    else
    {
    	pre_class_name_chain(in);
    	children_class_name(in);
    	post_class_name_chain(in);
    }
}

void Visitor::visit_target(Target* in)
{
    if(in == NULL)
    	visit_null("MIR", "Target");
    else
    {
    	pre_target_chain(in);
    	children_target(in);
    	post_target_chain(in);
    }
}

void Visitor::visit_variable_name_list(List<VARIABLE_NAME*>* in)
{
    List<VARIABLE_NAME*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "VARIABLE_NAME");
    else
    {
    	pre_list("MIR", "VARIABLE_NAME", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_variable_name(*i);
    	}
    
    	post_list("MIR", "VARIABLE_NAME", in->size());
    }
}

void Visitor::visit_array_elem_list(List<Array_elem*>* in)
{
    List<Array_elem*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "Array_elem");
    else
    {
    	pre_list("MIR", "Array_elem", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_array_elem(*i);
    	}
    
    	post_list("MIR", "Array_elem", in->size());
    }
}

void Visitor::visit_array_elem(Array_elem* in)
{
    if(in == NULL)
    	visit_null("MIR", "Array_elem");
    else
    {
    	pre_array_elem_chain(in);
    	children_array_elem(in);
    	post_array_elem_chain(in);
    }
}

void Visitor::visit_method_name(Method_name* in)
{
    if(in == NULL)
    	visit_null("MIR", "Method_name");
    else
    {
    	pre_method_name_chain(in);
    	children_method_name(in);
    	post_method_name_chain(in);
    }
}

void Visitor::visit_actual_parameter_list(List<Actual_parameter*>* in)
{
    List<Actual_parameter*>::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MIR", "Actual_parameter");
    else
    {
    	pre_list("MIR", "Actual_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_actual_parameter(*i);
    	}
    
    	post_list("MIR", "Actual_parameter", in->size());
    }
}

void Visitor::visit_actual_parameter(Actual_parameter* in)
{
    if(in == NULL)
    	visit_null("MIR", "Actual_parameter");
    else
    {
    	pre_actual_parameter_chain(in);
    	children_actual_parameter(in);
    	post_actual_parameter_chain(in);
    }
}

void Visitor::visit_php_script(PHP_script* in)
{
    if(in == NULL)
    	visit_null("MIR", "PHP_script");
    else
    {
    	pre_php_script_chain(in);
    	children_php_script(in);
    	post_php_script_chain(in);
    }
}

// Invoke the right pre-chain (manual dispatching)
// Do not override unless you know what you are doing
void Visitor::pre_statement_chain(Statement* in)
{
    switch(in->classid())
    {
    case Class_def::ID:
    	pre_class_def_chain(dynamic_cast<Class_def*>(in));
    	break;
    case Interface_def::ID:
    	pre_interface_def_chain(dynamic_cast<Interface_def*>(in));
    	break;
    case Method::ID:
    	pre_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Return::ID:
    	pre_return_chain(dynamic_cast<Return*>(in));
    	break;
    case Static_declaration::ID:
    	pre_static_declaration_chain(dynamic_cast<Static_declaration*>(in));
    	break;
    case Global::ID:
    	pre_global_chain(dynamic_cast<Global*>(in));
    	break;
    case Try::ID:
    	pre_try_chain(dynamic_cast<Try*>(in));
    	break;
    case Throw::ID:
    	pre_throw_chain(dynamic_cast<Throw*>(in));
    	break;
    case Eval_expr::ID:
    	pre_eval_expr_chain(dynamic_cast<Eval_expr*>(in));
    	break;
    case Label::ID:
    	pre_label_chain(dynamic_cast<Label*>(in));
    	break;
    case Goto::ID:
    	pre_goto_chain(dynamic_cast<Goto*>(in));
    	break;
    case Branch::ID:
    	pre_branch_chain(dynamic_cast<Branch*>(in));
    	break;
    case Foreach_next::ID:
    	pre_foreach_next_chain(dynamic_cast<Foreach_next*>(in));
    	break;
    case Foreach_reset::ID:
    	pre_foreach_reset_chain(dynamic_cast<Foreach_reset*>(in));
    	break;
    case Foreach_end::ID:
    	pre_foreach_end_chain(dynamic_cast<Foreach_end*>(in));
    	break;
    }
}

void Visitor::pre_member_chain(Member* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	pre_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Attribute::ID:
    	pre_attribute_chain(dynamic_cast<Attribute*>(in));
    	break;
    }
}

void Visitor::pre_expr_chain(Expr* in)
{
    switch(in->classid())
    {
    case Assignment::ID:
    	pre_assignment_chain(dynamic_cast<Assignment*>(in));
    	break;
    case Cast::ID:
    	pre_cast_chain(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	pre_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<Instanceof*>(in));
    	break;
    case Variable::ID:
    	pre_variable_chain(dynamic_cast<Variable*>(in));
    	break;
    case Pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<Pre_op*>(in));
    	break;
    case Method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	pre_new_chain(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	pre_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	pre_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	pre_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	pre_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	pre_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Array::ID:
    	pre_array_chain(dynamic_cast<Array*>(in));
    	break;
    case Foreach_has_key::ID:
    	pre_foreach_has_key_chain(dynamic_cast<Foreach_has_key*>(in));
    	break;
    case Foreach_get_key::ID:
    	pre_foreach_get_key_chain(dynamic_cast<Foreach_get_key*>(in));
    	break;
    case Foreach_get_val::ID:
    	pre_foreach_get_val_chain(dynamic_cast<Foreach_get_val*>(in));
    	break;
    }
}

void Visitor::pre_variable_name_chain(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	pre_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Reflection::ID:
    	pre_reflection_chain(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Visitor::pre_class_name_chain(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	pre_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Reflection::ID:
    	pre_reflection_chain(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Visitor::pre_target_chain(Target* in)
{
    switch(in->classid())
    {
    case Assignment::ID:
    	pre_assignment_chain(dynamic_cast<Assignment*>(in));
    	break;
    case Cast::ID:
    	pre_cast_chain(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	pre_unary_op_chain(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	pre_bin_op_chain(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	pre_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	pre_instanceof_chain(dynamic_cast<Instanceof*>(in));
    	break;
    case Variable::ID:
    	pre_variable_chain(dynamic_cast<Variable*>(in));
    	break;
    case Pre_op::ID:
    	pre_pre_op_chain(dynamic_cast<Pre_op*>(in));
    	break;
    case Method_invocation::ID:
    	pre_method_invocation_chain(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	pre_new_chain(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	pre_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	pre_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	pre_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	pre_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	pre_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Array::ID:
    	pre_array_chain(dynamic_cast<Array*>(in));
    	break;
    case Foreach_has_key::ID:
    	pre_foreach_has_key_chain(dynamic_cast<Foreach_has_key*>(in));
    	break;
    case Foreach_get_key::ID:
    	pre_foreach_get_key_chain(dynamic_cast<Foreach_get_key*>(in));
    	break;
    case Foreach_get_val::ID:
    	pre_foreach_get_val_chain(dynamic_cast<Foreach_get_val*>(in));
    	break;
    case CLASS_NAME::ID:
    	pre_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Visitor::pre_method_name_chain(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	pre_method_name_chain(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Reflection::ID:
    	pre_reflection_chain(dynamic_cast<Reflection*>(in));
    	break;
    }
}

// Invoke the right post-chain (manual dispatching)
// Do not override unless you know what you are doing
void Visitor::post_statement_chain(Statement* in)
{
    switch(in->classid())
    {
    case Class_def::ID:
    	post_class_def_chain(dynamic_cast<Class_def*>(in));
    	break;
    case Interface_def::ID:
    	post_interface_def_chain(dynamic_cast<Interface_def*>(in));
    	break;
    case Method::ID:
    	post_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Return::ID:
    	post_return_chain(dynamic_cast<Return*>(in));
    	break;
    case Static_declaration::ID:
    	post_static_declaration_chain(dynamic_cast<Static_declaration*>(in));
    	break;
    case Global::ID:
    	post_global_chain(dynamic_cast<Global*>(in));
    	break;
    case Try::ID:
    	post_try_chain(dynamic_cast<Try*>(in));
    	break;
    case Throw::ID:
    	post_throw_chain(dynamic_cast<Throw*>(in));
    	break;
    case Eval_expr::ID:
    	post_eval_expr_chain(dynamic_cast<Eval_expr*>(in));
    	break;
    case Label::ID:
    	post_label_chain(dynamic_cast<Label*>(in));
    	break;
    case Goto::ID:
    	post_goto_chain(dynamic_cast<Goto*>(in));
    	break;
    case Branch::ID:
    	post_branch_chain(dynamic_cast<Branch*>(in));
    	break;
    case Foreach_next::ID:
    	post_foreach_next_chain(dynamic_cast<Foreach_next*>(in));
    	break;
    case Foreach_reset::ID:
    	post_foreach_reset_chain(dynamic_cast<Foreach_reset*>(in));
    	break;
    case Foreach_end::ID:
    	post_foreach_end_chain(dynamic_cast<Foreach_end*>(in));
    	break;
    }
}

void Visitor::post_member_chain(Member* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	post_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Attribute::ID:
    	post_attribute_chain(dynamic_cast<Attribute*>(in));
    	break;
    }
}

void Visitor::post_expr_chain(Expr* in)
{
    switch(in->classid())
    {
    case Assignment::ID:
    	post_assignment_chain(dynamic_cast<Assignment*>(in));
    	break;
    case Cast::ID:
    	post_cast_chain(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	post_unary_op_chain(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	post_bin_op_chain(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	post_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	post_instanceof_chain(dynamic_cast<Instanceof*>(in));
    	break;
    case Variable::ID:
    	post_variable_chain(dynamic_cast<Variable*>(in));
    	break;
    case Pre_op::ID:
    	post_pre_op_chain(dynamic_cast<Pre_op*>(in));
    	break;
    case Method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	post_new_chain(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	post_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	post_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	post_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	post_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	post_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Array::ID:
    	post_array_chain(dynamic_cast<Array*>(in));
    	break;
    case Foreach_has_key::ID:
    	post_foreach_has_key_chain(dynamic_cast<Foreach_has_key*>(in));
    	break;
    case Foreach_get_key::ID:
    	post_foreach_get_key_chain(dynamic_cast<Foreach_get_key*>(in));
    	break;
    case Foreach_get_val::ID:
    	post_foreach_get_val_chain(dynamic_cast<Foreach_get_val*>(in));
    	break;
    }
}

void Visitor::post_variable_name_chain(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	post_variable_name_chain(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Reflection::ID:
    	post_reflection_chain(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Visitor::post_class_name_chain(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	post_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Reflection::ID:
    	post_reflection_chain(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Visitor::post_target_chain(Target* in)
{
    switch(in->classid())
    {
    case Assignment::ID:
    	post_assignment_chain(dynamic_cast<Assignment*>(in));
    	break;
    case Cast::ID:
    	post_cast_chain(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	post_unary_op_chain(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	post_bin_op_chain(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	post_constant_chain(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	post_instanceof_chain(dynamic_cast<Instanceof*>(in));
    	break;
    case Variable::ID:
    	post_variable_chain(dynamic_cast<Variable*>(in));
    	break;
    case Pre_op::ID:
    	post_pre_op_chain(dynamic_cast<Pre_op*>(in));
    	break;
    case Method_invocation::ID:
    	post_method_invocation_chain(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	post_new_chain(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	post_int_chain(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	post_real_chain(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	post_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	post_bool_chain(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	post_nil_chain(dynamic_cast<NIL*>(in));
    	break;
    case Array::ID:
    	post_array_chain(dynamic_cast<Array*>(in));
    	break;
    case Foreach_has_key::ID:
    	post_foreach_has_key_chain(dynamic_cast<Foreach_has_key*>(in));
    	break;
    case Foreach_get_key::ID:
    	post_foreach_get_key_chain(dynamic_cast<Foreach_get_key*>(in));
    	break;
    case Foreach_get_val::ID:
    	post_foreach_get_val_chain(dynamic_cast<Foreach_get_val*>(in));
    	break;
    case CLASS_NAME::ID:
    	post_class_name_chain(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Visitor::post_method_name_chain(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	post_method_name_chain(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Reflection::ID:
    	post_reflection_chain(dynamic_cast<Reflection*>(in));
    	break;
    }
}

// Invoke the right visit-children (manual dispatching)
// Do not override unless you know what you are doing
void Visitor::children_statement(Statement* in)
{
    switch(in->classid())
    {
    case Class_def::ID:
    	children_class_def(dynamic_cast<Class_def*>(in));
    	break;
    case Interface_def::ID:
    	children_interface_def(dynamic_cast<Interface_def*>(in));
    	break;
    case Method::ID:
    	children_method(dynamic_cast<Method*>(in));
    	break;
    case Return::ID:
    	children_return(dynamic_cast<Return*>(in));
    	break;
    case Static_declaration::ID:
    	children_static_declaration(dynamic_cast<Static_declaration*>(in));
    	break;
    case Global::ID:
    	children_global(dynamic_cast<Global*>(in));
    	break;
    case Try::ID:
    	children_try(dynamic_cast<Try*>(in));
    	break;
    case Throw::ID:
    	children_throw(dynamic_cast<Throw*>(in));
    	break;
    case Eval_expr::ID:
    	children_eval_expr(dynamic_cast<Eval_expr*>(in));
    	break;
    case Label::ID:
    	children_label(dynamic_cast<Label*>(in));
    	break;
    case Goto::ID:
    	children_goto(dynamic_cast<Goto*>(in));
    	break;
    case Branch::ID:
    	children_branch(dynamic_cast<Branch*>(in));
    	break;
    case Foreach_next::ID:
    	children_foreach_next(dynamic_cast<Foreach_next*>(in));
    	break;
    case Foreach_reset::ID:
    	children_foreach_reset(dynamic_cast<Foreach_reset*>(in));
    	break;
    case Foreach_end::ID:
    	children_foreach_end(dynamic_cast<Foreach_end*>(in));
    	break;
    }
}

void Visitor::children_member(Member* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	children_method(dynamic_cast<Method*>(in));
    	break;
    case Attribute::ID:
    	children_attribute(dynamic_cast<Attribute*>(in));
    	break;
    }
}

void Visitor::children_expr(Expr* in)
{
    switch(in->classid())
    {
    case Assignment::ID:
    	children_assignment(dynamic_cast<Assignment*>(in));
    	break;
    case Cast::ID:
    	children_cast(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	children_unary_op(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	children_bin_op(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	children_instanceof(dynamic_cast<Instanceof*>(in));
    	break;
    case Variable::ID:
    	children_variable(dynamic_cast<Variable*>(in));
    	break;
    case Pre_op::ID:
    	children_pre_op(dynamic_cast<Pre_op*>(in));
    	break;
    case Method_invocation::ID:
    	children_method_invocation(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	children_new(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	children_int(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	children_real(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	children_bool(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	children_nil(dynamic_cast<NIL*>(in));
    	break;
    case Array::ID:
    	children_array(dynamic_cast<Array*>(in));
    	break;
    case Foreach_has_key::ID:
    	children_foreach_has_key(dynamic_cast<Foreach_has_key*>(in));
    	break;
    case Foreach_get_key::ID:
    	children_foreach_get_key(dynamic_cast<Foreach_get_key*>(in));
    	break;
    case Foreach_get_val::ID:
    	children_foreach_get_val(dynamic_cast<Foreach_get_val*>(in));
    	break;
    }
}

void Visitor::children_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Reflection::ID:
    	children_reflection(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Visitor::children_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Reflection::ID:
    	children_reflection(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Visitor::children_target(Target* in)
{
    switch(in->classid())
    {
    case Assignment::ID:
    	children_assignment(dynamic_cast<Assignment*>(in));
    	break;
    case Cast::ID:
    	children_cast(dynamic_cast<Cast*>(in));
    	break;
    case Unary_op::ID:
    	children_unary_op(dynamic_cast<Unary_op*>(in));
    	break;
    case Bin_op::ID:
    	children_bin_op(dynamic_cast<Bin_op*>(in));
    	break;
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    case Instanceof::ID:
    	children_instanceof(dynamic_cast<Instanceof*>(in));
    	break;
    case Variable::ID:
    	children_variable(dynamic_cast<Variable*>(in));
    	break;
    case Pre_op::ID:
    	children_pre_op(dynamic_cast<Pre_op*>(in));
    	break;
    case Method_invocation::ID:
    	children_method_invocation(dynamic_cast<Method_invocation*>(in));
    	break;
    case New::ID:
    	children_new(dynamic_cast<New*>(in));
    	break;
    case INT::ID:
    	children_int(dynamic_cast<INT*>(in));
    	break;
    case REAL::ID:
    	children_real(dynamic_cast<REAL*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case BOOL::ID:
    	children_bool(dynamic_cast<BOOL*>(in));
    	break;
    case NIL::ID:
    	children_nil(dynamic_cast<NIL*>(in));
    	break;
    case Array::ID:
    	children_array(dynamic_cast<Array*>(in));
    	break;
    case Foreach_has_key::ID:
    	children_foreach_has_key(dynamic_cast<Foreach_has_key*>(in));
    	break;
    case Foreach_get_key::ID:
    	children_foreach_get_key(dynamic_cast<Foreach_get_key*>(in));
    	break;
    case Foreach_get_val::ID:
    	children_foreach_get_val(dynamic_cast<Foreach_get_val*>(in));
    	break;
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Visitor::children_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	children_method_name(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Reflection::ID:
    	children_reflection(dynamic_cast<Reflection*>(in));
    	break;
    }
}
}

