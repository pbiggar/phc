#include "MIR_transform.h"

namespace MIR{
Transform::~Transform()
{
}

/* Invoked before the children are transformed */
PHP_script* Transform::pre_php_script(PHP_script* in)
{
    return in;
}

void Transform::pre_class_def(Class_def* in, Statement_list* out)
{
    out->push_back(in);
}

Class_mod* Transform::pre_class_mod(Class_mod* in)
{
    return in;
}

void Transform::pre_interface_def(Interface_def* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_method(Method* in, Method_list* out)
{
    out->push_back(in);
}

Signature* Transform::pre_signature(Signature* in)
{
    return in;
}

Method_mod* Transform::pre_method_mod(Method_mod* in)
{
    return in;
}

void Transform::pre_formal_parameter(Formal_parameter* in, Formal_parameter_list* out)
{
    out->push_back(in);
}

Type* Transform::pre_type(Type* in)
{
    return in;
}

void Transform::pre_attribute(Attribute* in, Member_list* out)
{
    out->push_back(in);
}

Attr_mod* Transform::pre_attr_mod(Attr_mod* in)
{
    return in;
}

Name_with_default* Transform::pre_name_with_default(Name_with_default* in)
{
    return in;
}

void Transform::pre_class_alias(Class_alias* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_interface_alias(Interface_alias* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_method_alias(Method_alias* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_return(Return* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_static_declaration(Static_declaration* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_global(Global* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_try(Try* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_catch(Catch* in, Catch_list* out)
{
    out->push_back(in);
}

void Transform::pre_throw(Throw* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_var(Assign_var* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_field(Assign_field* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_array(Assign_array* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_var_var(Assign_var_var* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_next(Assign_next* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_pre_op(Pre_op* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_eval_expr(Eval_expr* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_unset(Unset* in, Statement_list* out)
{
    out->push_back(in);
}

Expr* Transform::pre_isset(Isset* in)
{
    return in;
}

Expr* Transform::pre_field_access(Field_access* in)
{
    return in;
}

Expr* Transform::pre_array_access(Array_access* in)
{
    return in;
}

Expr* Transform::pre_array_next(Array_next* in)
{
    return in;
}

Expr* Transform::pre_cast(Cast* in)
{
    return in;
}

Expr* Transform::pre_unary_op(Unary_op* in)
{
    return in;
}

Expr* Transform::pre_bin_op(Bin_op* in)
{
    return in;
}

Constant* Transform::pre_constant(Constant* in)
{
    return in;
}

Expr* Transform::pre_instanceof(Instanceof* in)
{
    return in;
}

Expr* Transform::pre_method_invocation(Method_invocation* in)
{
    return in;
}

Expr* Transform::pre_new(New* in)
{
    return in;
}

void Transform::pre_actual_parameter(Actual_parameter* in, Actual_parameter_list* out)
{
    out->push_back(in);
}

Method_name* Transform::pre_variable_method(Variable_method* in)
{
    return in;
}

Variable_name* Transform::pre_variable_variable(Variable_variable* in)
{
    return in;
}

Class_name* Transform::pre_variable_class(Variable_class* in)
{
    return in;
}

Field_name* Transform::pre_variable_field(Variable_field* in)
{
    return in;
}

Static_value* Transform::pre_static_array(Static_array* in)
{
    return in;
}

void Transform::pre_static_array_elem(Static_array_elem* in, Static_array_elem_list* out)
{
    out->push_back(in);
}

void Transform::pre_branch(Branch* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_goto(Goto* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_label(Label* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_foreach_reset(Foreach_reset* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_foreach_next(Foreach_next* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_foreach_end(Foreach_end* in, Statement_list* out)
{
    out->push_back(in);
}

Expr* Transform::pre_foreach_has_key(Foreach_has_key* in)
{
    return in;
}

Expr* Transform::pre_foreach_get_key(Foreach_get_key* in)
{
    return in;
}

Expr* Transform::pre_foreach_get_val(Foreach_get_val* in)
{
    return in;
}

Expr* Transform::pre_param_is_ref(Param_is_ref* in)
{
    return in;
}

PARAM_INDEX* Transform::pre_param_index(PARAM_INDEX* in)
{
    return in;
}

FOREIGN* Transform::pre_foreign(FOREIGN* in)
{
    return in;
}

CLASS_NAME* Transform::pre_class_name(CLASS_NAME* in)
{
    return in;
}

INTERFACE_NAME* Transform::pre_interface_name(INTERFACE_NAME* in)
{
    return in;
}

METHOD_NAME* Transform::pre_method_name(METHOD_NAME* in)
{
    return in;
}

VARIABLE_NAME* Transform::pre_variable_name(VARIABLE_NAME* in)
{
    return in;
}

OP* Transform::pre_op(OP* in)
{
    return in;
}

Literal* Transform::pre_int(INT* in)
{
    return in;
}

Literal* Transform::pre_real(REAL* in)
{
    return in;
}

Literal* Transform::pre_string(STRING* in)
{
    return in;
}

Literal* Transform::pre_bool(BOOL* in)
{
    return in;
}

Literal* Transform::pre_nil(NIL* in)
{
    return in;
}

CAST* Transform::pre_cast(CAST* in)
{
    return in;
}

CONSTANT_NAME* Transform::pre_constant_name(CONSTANT_NAME* in)
{
    return in;
}

Field_name* Transform::pre_field_name(FIELD_NAME* in)
{
    return in;
}

LABEL_NAME* Transform::pre_label_name(LABEL_NAME* in)
{
    return in;
}

HT_ITERATOR* Transform::pre_ht_iterator(HT_ITERATOR* in)
{
    return in;
}

/* Invoked after the children have been transformed */
PHP_script* Transform::post_php_script(PHP_script* in)
{
    return in;
}

void Transform::post_class_def(Class_def* in, Statement_list* out)
{
    out->push_back(in);
}

Class_mod* Transform::post_class_mod(Class_mod* in)
{
    return in;
}

void Transform::post_interface_def(Interface_def* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_method(Method* in, Method_list* out)
{
    out->push_back(in);
}

Signature* Transform::post_signature(Signature* in)
{
    return in;
}

Method_mod* Transform::post_method_mod(Method_mod* in)
{
    return in;
}

void Transform::post_formal_parameter(Formal_parameter* in, Formal_parameter_list* out)
{
    out->push_back(in);
}

Type* Transform::post_type(Type* in)
{
    return in;
}

void Transform::post_attribute(Attribute* in, Member_list* out)
{
    out->push_back(in);
}

Attr_mod* Transform::post_attr_mod(Attr_mod* in)
{
    return in;
}

Name_with_default* Transform::post_name_with_default(Name_with_default* in)
{
    return in;
}

void Transform::post_class_alias(Class_alias* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_interface_alias(Interface_alias* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_method_alias(Method_alias* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_return(Return* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_static_declaration(Static_declaration* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_global(Global* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_try(Try* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_catch(Catch* in, Catch_list* out)
{
    out->push_back(in);
}

void Transform::post_throw(Throw* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_var(Assign_var* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_field(Assign_field* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_array(Assign_array* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_var_var(Assign_var_var* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_next(Assign_next* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_pre_op(Pre_op* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_eval_expr(Eval_expr* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_unset(Unset* in, Statement_list* out)
{
    out->push_back(in);
}

Expr* Transform::post_isset(Isset* in)
{
    return in;
}

Expr* Transform::post_field_access(Field_access* in)
{
    return in;
}

Expr* Transform::post_array_access(Array_access* in)
{
    return in;
}

Expr* Transform::post_array_next(Array_next* in)
{
    return in;
}

Expr* Transform::post_cast(Cast* in)
{
    return in;
}

Expr* Transform::post_unary_op(Unary_op* in)
{
    return in;
}

Expr* Transform::post_bin_op(Bin_op* in)
{
    return in;
}

Constant* Transform::post_constant(Constant* in)
{
    return in;
}

Expr* Transform::post_instanceof(Instanceof* in)
{
    return in;
}

Expr* Transform::post_method_invocation(Method_invocation* in)
{
    return in;
}

Expr* Transform::post_new(New* in)
{
    return in;
}

void Transform::post_actual_parameter(Actual_parameter* in, Actual_parameter_list* out)
{
    out->push_back(in);
}

Method_name* Transform::post_variable_method(Variable_method* in)
{
    return in;
}

Variable_name* Transform::post_variable_variable(Variable_variable* in)
{
    return in;
}

Class_name* Transform::post_variable_class(Variable_class* in)
{
    return in;
}

Field_name* Transform::post_variable_field(Variable_field* in)
{
    return in;
}

Static_value* Transform::post_static_array(Static_array* in)
{
    return in;
}

void Transform::post_static_array_elem(Static_array_elem* in, Static_array_elem_list* out)
{
    out->push_back(in);
}

void Transform::post_branch(Branch* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_goto(Goto* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_label(Label* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_foreach_reset(Foreach_reset* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_foreach_next(Foreach_next* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_foreach_end(Foreach_end* in, Statement_list* out)
{
    out->push_back(in);
}

Expr* Transform::post_foreach_has_key(Foreach_has_key* in)
{
    return in;
}

Expr* Transform::post_foreach_get_key(Foreach_get_key* in)
{
    return in;
}

Expr* Transform::post_foreach_get_val(Foreach_get_val* in)
{
    return in;
}

Expr* Transform::post_param_is_ref(Param_is_ref* in)
{
    return in;
}

PARAM_INDEX* Transform::post_param_index(PARAM_INDEX* in)
{
    return in;
}

FOREIGN* Transform::post_foreign(FOREIGN* in)
{
    return in;
}

CLASS_NAME* Transform::post_class_name(CLASS_NAME* in)
{
    return in;
}

INTERFACE_NAME* Transform::post_interface_name(INTERFACE_NAME* in)
{
    return in;
}

METHOD_NAME* Transform::post_method_name(METHOD_NAME* in)
{
    return in;
}

VARIABLE_NAME* Transform::post_variable_name(VARIABLE_NAME* in)
{
    return in;
}

OP* Transform::post_op(OP* in)
{
    return in;
}

Literal* Transform::post_int(INT* in)
{
    return in;
}

Literal* Transform::post_real(REAL* in)
{
    return in;
}

Literal* Transform::post_string(STRING* in)
{
    return in;
}

Literal* Transform::post_bool(BOOL* in)
{
    return in;
}

Literal* Transform::post_nil(NIL* in)
{
    return in;
}

CAST* Transform::post_cast(CAST* in)
{
    return in;
}

CONSTANT_NAME* Transform::post_constant_name(CONSTANT_NAME* in)
{
    return in;
}

Field_name* Transform::post_field_name(FIELD_NAME* in)
{
    return in;
}

LABEL_NAME* Transform::post_label_name(LABEL_NAME* in)
{
    return in;
}

HT_ITERATOR* Transform::post_ht_iterator(HT_ITERATOR* in)
{
    return in;
}

/* Transform the children of the node */
void Transform::children_php_script(PHP_script* in)
{
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_class_def(Class_def* in)
{
    in->class_mod = transform_class_mod(in->class_mod);
    in->class_name = transform_class_name(in->class_name);
    in->extends = transform_class_name(in->extends);
    in->implements = transform_interface_name_list(in->implements);
    in->members = transform_member_list(in->members);
}

void Transform::children_class_mod(Class_mod* in)
{
}

void Transform::children_interface_def(Interface_def* in)
{
    in->interface_name = transform_interface_name(in->interface_name);
    in->extends = transform_interface_name_list(in->extends);
    in->members = transform_member_list(in->members);
}

void Transform::children_method(Method* in)
{
    in->signature = transform_signature(in->signature);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_signature(Signature* in)
{
    in->method_mod = transform_method_mod(in->method_mod);
    in->method_name = transform_method_name(in->method_name);
    in->formal_parameters = transform_formal_parameter_list(in->formal_parameters);
}

void Transform::children_method_mod(Method_mod* in)
{
}

void Transform::children_formal_parameter(Formal_parameter* in)
{
    in->type = transform_type(in->type);
    in->var = transform_name_with_default(in->var);
}

void Transform::children_type(Type* in)
{
    in->class_name = transform_class_name(in->class_name);
}

void Transform::children_attribute(Attribute* in)
{
    in->attr_mod = transform_attr_mod(in->attr_mod);
    in->var = transform_name_with_default(in->var);
}

void Transform::children_attr_mod(Attr_mod* in)
{
}

void Transform::children_name_with_default(Name_with_default* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->default_value = transform_static_value(in->default_value);
}

void Transform::children_class_alias(Class_alias* in)
{
    in->alias = transform_class_name(in->alias);
    in->class_name = transform_class_name(in->class_name);
}

void Transform::children_interface_alias(Interface_alias* in)
{
    in->alias = transform_interface_name(in->alias);
    in->interface_name = transform_interface_name(in->interface_name);
}

void Transform::children_method_alias(Method_alias* in)
{
    in->alias = transform_method_name(in->alias);
    in->method_name = transform_method_name(in->method_name);
}

void Transform::children_return(Return* in)
{
    in->rvalue = transform_rvalue(in->rvalue);
}

void Transform::children_static_declaration(Static_declaration* in)
{
    in->var = transform_name_with_default(in->var);
}

void Transform::children_global(Global* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_try(Try* in)
{
    in->statements = transform_statement_list(in->statements);
    in->catches = transform_catch_list(in->catches);
}

void Transform::children_catch(Catch* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->variable_name = transform_variable_name(in->variable_name);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_throw(Throw* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_assign_var(Assign_var* in)
{
    in->lhs = transform_variable_name(in->lhs);
    in->rhs = transform_expr(in->rhs);
}

void Transform::children_assign_field(Assign_field* in)
{
    in->target = transform_target(in->target);
    in->field_name = transform_field_name(in->field_name);
    in->rhs = transform_rvalue(in->rhs);
}

void Transform::children_assign_array(Assign_array* in)
{
    in->lhs = transform_variable_name(in->lhs);
    in->index = transform_rvalue(in->index);
    in->rhs = transform_rvalue(in->rhs);
}

void Transform::children_assign_var_var(Assign_var_var* in)
{
    in->lhs = transform_variable_name(in->lhs);
    in->rhs = transform_rvalue(in->rhs);
}

void Transform::children_assign_next(Assign_next* in)
{
    in->lhs = transform_variable_name(in->lhs);
    in->rhs = transform_rvalue(in->rhs);
}

void Transform::children_pre_op(Pre_op* in)
{
    in->op = transform_op(in->op);
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_eval_expr(Eval_expr* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_unset(Unset* in)
{
    in->target = transform_target(in->target);
    in->variable_name = transform_variable_name(in->variable_name);
    in->array_indices = transform_rvalue_list(in->array_indices);
}

void Transform::children_isset(Isset* in)
{
    in->target = transform_target(in->target);
    in->variable_name = transform_variable_name(in->variable_name);
    in->array_indices = transform_rvalue_list(in->array_indices);
}

void Transform::children_field_access(Field_access* in)
{
    in->target = transform_target(in->target);
    in->field_name = transform_field_name(in->field_name);
}

void Transform::children_array_access(Array_access* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->index = transform_rvalue(in->index);
}

void Transform::children_array_next(Array_next* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_cast(Cast* in)
{
    in->cast = transform_cast(in->cast);
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_unary_op(Unary_op* in)
{
    in->op = transform_op(in->op);
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_bin_op(Bin_op* in)
{
    in->left = transform_rvalue(in->left);
    in->op = transform_op(in->op);
    in->right = transform_rvalue(in->right);
}

void Transform::children_constant(Constant* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->constant_name = transform_constant_name(in->constant_name);
}

void Transform::children_instanceof(Instanceof* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->class_name = transform_class_name(in->class_name);
}

void Transform::children_method_invocation(Method_invocation* in)
{
    in->target = transform_target(in->target);
    in->method_name = transform_method_name(in->method_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

void Transform::children_new(New* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

void Transform::children_actual_parameter(Actual_parameter* in)
{
    in->rvalue = transform_rvalue(in->rvalue);
}

void Transform::children_variable_method(Variable_method* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_variable_variable(Variable_variable* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_variable_class(Variable_class* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_variable_field(Variable_field* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void Transform::children_static_array(Static_array* in)
{
    in->static_array_elems = transform_static_array_elem_list(in->static_array_elems);
}

void Transform::children_static_array_elem(Static_array_elem* in)
{
    in->key = transform_static_array_key(in->key);
    in->val = transform_static_value(in->val);
}

void Transform::children_branch(Branch* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->iftrue = transform_label_name(in->iftrue);
    in->iffalse = transform_label_name(in->iffalse);
}

void Transform::children_goto(Goto* in)
{
    in->label_name = transform_label_name(in->label_name);
}

void Transform::children_label(Label* in)
{
    in->label_name = transform_label_name(in->label_name);
}

void Transform::children_foreach_reset(Foreach_reset* in)
{
    in->array = transform_variable_name(in->array);
    in->iter = transform_ht_iterator(in->iter);
}

void Transform::children_foreach_next(Foreach_next* in)
{
    in->array = transform_variable_name(in->array);
    in->iter = transform_ht_iterator(in->iter);
}

void Transform::children_foreach_end(Foreach_end* in)
{
    in->array = transform_variable_name(in->array);
    in->iter = transform_ht_iterator(in->iter);
}

void Transform::children_foreach_has_key(Foreach_has_key* in)
{
    in->array = transform_variable_name(in->array);
    in->iter = transform_ht_iterator(in->iter);
}

void Transform::children_foreach_get_key(Foreach_get_key* in)
{
    in->array = transform_variable_name(in->array);
    in->iter = transform_ht_iterator(in->iter);
}

void Transform::children_foreach_get_val(Foreach_get_val* in)
{
    in->array = transform_variable_name(in->array);
    in->iter = transform_ht_iterator(in->iter);
}

void Transform::children_param_is_ref(Param_is_ref* in)
{
    in->target = transform_target(in->target);
    in->method_name = transform_method_name(in->method_name);
    in->param_index = transform_param_index(in->param_index);
}

/* Tokens don't have children, so these methods do nothing by default */
void Transform::children_param_index(PARAM_INDEX* in)
{
}

void Transform::children_foreign(FOREIGN* in)
{
}

void Transform::children_class_name(CLASS_NAME* in)
{
}

void Transform::children_interface_name(INTERFACE_NAME* in)
{
}

void Transform::children_method_name(METHOD_NAME* in)
{
}

void Transform::children_variable_name(VARIABLE_NAME* in)
{
}

void Transform::children_op(OP* in)
{
}

void Transform::children_int(INT* in)
{
}

void Transform::children_real(REAL* in)
{
}

void Transform::children_string(STRING* in)
{
}

void Transform::children_bool(BOOL* in)
{
}

void Transform::children_nil(NIL* in)
{
}

void Transform::children_cast(CAST* in)
{
}

void Transform::children_constant_name(CONSTANT_NAME* in)
{
}

void Transform::children_field_name(FIELD_NAME* in)
{
}

void Transform::children_label_name(LABEL_NAME* in)
{
}

void Transform::children_ht_iterator(HT_ITERATOR* in)
{
}

/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
Statement_list* Transform::transform_statement_list(Statement_list* in)
{
    Statement_list::const_iterator i;
    Statement_list* out = new Statement_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_statement(*i));
    }
    
    return out;
}

Statement_list* Transform::transform_statement(Statement* in)
{
    Statement_list::const_iterator i;
    Statement_list* out1 = new Statement_list;
    Statement_list* out2 = new Statement_list;
    
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

Class_mod* Transform::transform_class_mod(Class_mod* in)
{
    if(in == NULL) return NULL;
    
    Class_mod* out;
    
    out = pre_class_mod(in);
    if(out != NULL)
    {
    	children_class_mod(out);
    	out = post_class_mod(out);
    }
    
    return out;
}

CLASS_NAME* Transform::transform_class_name(CLASS_NAME* in)
{
    if(in == NULL) return NULL;
    
    CLASS_NAME* out;
    
    out = pre_class_name(in);
    if(out != NULL)
    {
    	children_class_name(out);
    	out = post_class_name(out);
    }
    
    return out;
}

INTERFACE_NAME_list* Transform::transform_interface_name_list(INTERFACE_NAME_list* in)
{
    INTERFACE_NAME_list::const_iterator i;
    INTERFACE_NAME_list* out = new INTERFACE_NAME_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_interface_name(*i));
    }
    
    return out;
}

Member_list* Transform::transform_member_list(Member_list* in)
{
    Member_list::const_iterator i;
    Member_list* out = new Member_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_member(*i));
    }
    
    return out;
}

Member_list* Transform::transform_member(Member* in)
{
    Member_list::const_iterator i;
    Member_list* out1 = new Member_list;
    Member_list* out2 = new Member_list;
    
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

INTERFACE_NAME* Transform::transform_interface_name(INTERFACE_NAME* in)
{
    if(in == NULL) return NULL;
    
    INTERFACE_NAME* out;
    
    out = pre_interface_name(in);
    if(out != NULL)
    {
    	children_interface_name(out);
    	out = post_interface_name(out);
    }
    
    return out;
}

Signature* Transform::transform_signature(Signature* in)
{
    if(in == NULL) return NULL;
    
    Signature* out;
    
    out = pre_signature(in);
    if(out != NULL)
    {
    	children_signature(out);
    	out = post_signature(out);
    }
    
    return out;
}

Method_mod* Transform::transform_method_mod(Method_mod* in)
{
    if(in == NULL) return NULL;
    
    Method_mod* out;
    
    out = pre_method_mod(in);
    if(out != NULL)
    {
    	children_method_mod(out);
    	out = post_method_mod(out);
    }
    
    return out;
}

METHOD_NAME* Transform::transform_method_name(METHOD_NAME* in)
{
    if(in == NULL) return NULL;
    
    METHOD_NAME* out;
    
    out = pre_method_name(in);
    if(out != NULL)
    {
    	children_method_name(out);
    	out = post_method_name(out);
    }
    
    return out;
}

Formal_parameter_list* Transform::transform_formal_parameter_list(Formal_parameter_list* in)
{
    Formal_parameter_list::const_iterator i;
    Formal_parameter_list* out = new Formal_parameter_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_formal_parameter(*i));
    }
    
    return out;
}

Formal_parameter_list* Transform::transform_formal_parameter(Formal_parameter* in)
{
    Formal_parameter_list::const_iterator i;
    Formal_parameter_list* out1 = new Formal_parameter_list;
    Formal_parameter_list* out2 = new Formal_parameter_list;
    
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

Type* Transform::transform_type(Type* in)
{
    if(in == NULL) return NULL;
    
    Type* out;
    
    out = pre_type(in);
    if(out != NULL)
    {
    	children_type(out);
    	out = post_type(out);
    }
    
    return out;
}

Name_with_default* Transform::transform_name_with_default(Name_with_default* in)
{
    if(in == NULL) return NULL;
    
    Name_with_default* out;
    
    out = pre_name_with_default(in);
    if(out != NULL)
    {
    	children_name_with_default(out);
    	out = post_name_with_default(out);
    }
    
    return out;
}

Attr_mod* Transform::transform_attr_mod(Attr_mod* in)
{
    if(in == NULL) return NULL;
    
    Attr_mod* out;
    
    out = pre_attr_mod(in);
    if(out != NULL)
    {
    	children_attr_mod(out);
    	out = post_attr_mod(out);
    }
    
    return out;
}

VARIABLE_NAME* Transform::transform_variable_name(VARIABLE_NAME* in)
{
    if(in == NULL) return NULL;
    
    VARIABLE_NAME* out;
    
    out = pre_variable_name(in);
    if(out != NULL)
    {
    	children_variable_name(out);
    	out = post_variable_name(out);
    }
    
    return out;
}

Static_value* Transform::transform_static_value(Static_value* in)
{
    if(in == NULL) return NULL;
    
    Static_value* out;
    
    out = pre_static_value(in);
    if(out != NULL)
    {
    	children_static_value(out);
    	out = post_static_value(out);
    }
    
    return out;
}

Rvalue* Transform::transform_rvalue(Rvalue* in)
{
    if(in == NULL) return NULL;
    
    Rvalue* out;
    
    out = pre_rvalue(in);
    if(out != NULL)
    {
    	children_rvalue(out);
    	out = post_rvalue(out);
    }
    
    return out;
}

Variable_name* Transform::transform_variable_name(Variable_name* in)
{
    if(in == NULL) return NULL;
    
    Variable_name* out;
    
    out = pre_variable_name(in);
    if(out != NULL)
    {
    	children_variable_name(out);
    	out = post_variable_name(out);
    }
    
    return out;
}

Catch_list* Transform::transform_catch_list(Catch_list* in)
{
    Catch_list::const_iterator i;
    Catch_list* out = new Catch_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_catch(*i));
    }
    
    return out;
}

Catch_list* Transform::transform_catch(Catch* in)
{
    Catch_list::const_iterator i;
    Catch_list* out1 = new Catch_list;
    Catch_list* out2 = new Catch_list;
    
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

Expr* Transform::transform_expr(Expr* in)
{
    if(in == NULL) return NULL;
    
    Expr* out;
    
    out = pre_expr(in);
    if(out != NULL)
    {
    	children_expr(out);
    	out = post_expr(out);
    }
    
    return out;
}

Target* Transform::transform_target(Target* in)
{
    if(in == NULL) return NULL;
    
    Target* out;
    
    out = pre_target(in);
    if(out != NULL)
    {
    	children_target(out);
    	out = post_target(out);
    }
    
    return out;
}

Field_name* Transform::transform_field_name(Field_name* in)
{
    if(in == NULL) return NULL;
    
    Field_name* out;
    
    out = pre_field_name(in);
    if(out != NULL)
    {
    	children_field_name(out);
    	out = post_field_name(out);
    }
    
    return out;
}

OP* Transform::transform_op(OP* in)
{
    if(in == NULL) return NULL;
    
    OP* out;
    
    out = pre_op(in);
    if(out != NULL)
    {
    	children_op(out);
    	out = post_op(out);
    }
    
    return out;
}

Rvalue_list* Transform::transform_rvalue_list(Rvalue_list* in)
{
    Rvalue_list::const_iterator i;
    Rvalue_list* out = new Rvalue_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_rvalue(*i));
    }
    
    return out;
}

CAST* Transform::transform_cast(CAST* in)
{
    if(in == NULL) return NULL;
    
    CAST* out;
    
    out = pre_cast(in);
    if(out != NULL)
    {
    	children_cast(out);
    	out = post_cast(out);
    }
    
    return out;
}

CONSTANT_NAME* Transform::transform_constant_name(CONSTANT_NAME* in)
{
    if(in == NULL) return NULL;
    
    CONSTANT_NAME* out;
    
    out = pre_constant_name(in);
    if(out != NULL)
    {
    	children_constant_name(out);
    	out = post_constant_name(out);
    }
    
    return out;
}

Class_name* Transform::transform_class_name(Class_name* in)
{
    if(in == NULL) return NULL;
    
    Class_name* out;
    
    out = pre_class_name(in);
    if(out != NULL)
    {
    	children_class_name(out);
    	out = post_class_name(out);
    }
    
    return out;
}

Method_name* Transform::transform_method_name(Method_name* in)
{
    if(in == NULL) return NULL;
    
    Method_name* out;
    
    out = pre_method_name(in);
    if(out != NULL)
    {
    	children_method_name(out);
    	out = post_method_name(out);
    }
    
    return out;
}

Actual_parameter_list* Transform::transform_actual_parameter_list(Actual_parameter_list* in)
{
    Actual_parameter_list::const_iterator i;
    Actual_parameter_list* out = new Actual_parameter_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_actual_parameter(*i));
    }
    
    return out;
}

Actual_parameter_list* Transform::transform_actual_parameter(Actual_parameter* in)
{
    Actual_parameter_list::const_iterator i;
    Actual_parameter_list* out1 = new Actual_parameter_list;
    Actual_parameter_list* out2 = new Actual_parameter_list;
    
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

Static_array_elem_list* Transform::transform_static_array_elem_list(Static_array_elem_list* in)
{
    Static_array_elem_list::const_iterator i;
    Static_array_elem_list* out = new Static_array_elem_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_static_array_elem(*i));
    }
    
    return out;
}

Static_array_elem_list* Transform::transform_static_array_elem(Static_array_elem* in)
{
    Static_array_elem_list::const_iterator i;
    Static_array_elem_list* out1 = new Static_array_elem_list;
    Static_array_elem_list* out2 = new Static_array_elem_list;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_static_array_elem(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_static_array_elem(*i);
    		post_static_array_elem(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

Static_array_key* Transform::transform_static_array_key(Static_array_key* in)
{
    if(in == NULL) return NULL;
    
    Static_array_key* out;
    
    out = pre_static_array_key(in);
    if(out != NULL)
    {
    	children_static_array_key(out);
    	out = post_static_array_key(out);
    }
    
    return out;
}

LABEL_NAME* Transform::transform_label_name(LABEL_NAME* in)
{
    if(in == NULL) return NULL;
    
    LABEL_NAME* out;
    
    out = pre_label_name(in);
    if(out != NULL)
    {
    	children_label_name(out);
    	out = post_label_name(out);
    }
    
    return out;
}

HT_ITERATOR* Transform::transform_ht_iterator(HT_ITERATOR* in)
{
    if(in == NULL) return NULL;
    
    HT_ITERATOR* out;
    
    out = pre_ht_iterator(in);
    if(out != NULL)
    {
    	children_ht_iterator(out);
    	out = post_ht_iterator(out);
    }
    
    return out;
}

PARAM_INDEX* Transform::transform_param_index(PARAM_INDEX* in)
{
    if(in == NULL) return NULL;
    
    PARAM_INDEX* out;
    
    out = pre_param_index(in);
    if(out != NULL)
    {
    	children_param_index(out);
    	out = post_param_index(out);
    }
    
    return out;
}

PHP_script* Transform::transform_php_script(PHP_script* in)
{
    if(in == NULL) return NULL;
    
    PHP_script* out;
    
    out = pre_php_script(in);
    if(out != NULL)
    {
    	children_php_script(out);
    	out = post_php_script(out);
    }
    
    return out;
}

/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
void Transform::pre_statement(Statement* in, Statement_list* out)
{
    switch(in->classid())
    {
    case Class_def::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_class_def(dynamic_cast<Class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Interface_def::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_interface_def(dynamic_cast<Interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Method::ID: 
    	{
    		Method_list* local_out = new Method_list;
    		Method_list::const_iterator i;
    		pre_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Class_alias::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_class_alias(dynamic_cast<Class_alias*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Interface_alias::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_interface_alias(dynamic_cast<Interface_alias*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Method_alias::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_method_alias(dynamic_cast<Method_alias*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Return::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_return(dynamic_cast<Return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Static_declaration::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_static_declaration(dynamic_cast<Static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Global::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_global(dynamic_cast<Global*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Try::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_try(dynamic_cast<Try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Throw::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_throw(dynamic_cast<Throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_var::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_var(dynamic_cast<Assign_var*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_var_var::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_var_var(dynamic_cast<Assign_var_var*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_array::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_array(dynamic_cast<Assign_array*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_next::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_next(dynamic_cast<Assign_next*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_field::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_field(dynamic_cast<Assign_field*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Eval_expr::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_eval_expr(dynamic_cast<Eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Pre_op::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_pre_op(dynamic_cast<Pre_op*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Unset::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_unset(dynamic_cast<Unset*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Label::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_label(dynamic_cast<Label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Goto::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_goto(dynamic_cast<Goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Branch::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_branch(dynamic_cast<Branch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach_next::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_foreach_next(dynamic_cast<Foreach_next*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach_reset::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_foreach_reset(dynamic_cast<Foreach_reset*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach_end::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_foreach_end(dynamic_cast<Foreach_end*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case FOREIGN::ID: 
    	out->push_back(pre_foreign(dynamic_cast<FOREIGN*>(in)));
    	return;
    }
    assert(0);
}

void Transform::pre_member(Member* in, Member_list* out)
{
    switch(in->classid())
    {
    case Method::ID: 
    	{
    		Method_list* local_out = new Method_list;
    		Method_list::const_iterator i;
    		pre_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Attribute::ID: 
    	{
    		Member_list* local_out = new Member_list;
    		Member_list::const_iterator i;
    		pre_attribute(dynamic_cast<Attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Static_value* Transform::pre_static_value(Static_value* in)
{
    switch(in->classid())
    {
    case INT::ID: return pre_int(dynamic_cast<INT*>(in));
    case REAL::ID: return pre_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return pre_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return pre_nil(dynamic_cast<NIL*>(in));
    case Static_array::ID: return pre_static_array(dynamic_cast<Static_array*>(in));
    case Constant::ID: return pre_constant(dynamic_cast<Constant*>(in));
    }
    assert(0);
}

Rvalue* Transform::pre_rvalue(Rvalue* in)
{
    switch(in->classid())
    {
    case INT::ID: return pre_int(dynamic_cast<INT*>(in));
    case REAL::ID: return pre_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return pre_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return pre_nil(dynamic_cast<NIL*>(in));
    case VARIABLE_NAME::ID: return pre_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    }
    assert(0);
}

Variable_name* Transform::pre_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID: return pre_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case Variable_variable::ID: return pre_variable_variable(dynamic_cast<Variable_variable*>(in));
    }
    assert(0);
}

Expr* Transform::pre_expr(Expr* in)
{
    switch(in->classid())
    {
    case Cast::ID: return pre_cast(dynamic_cast<Cast*>(in));
    case Unary_op::ID: return pre_unary_op(dynamic_cast<Unary_op*>(in));
    case Bin_op::ID: return pre_bin_op(dynamic_cast<Bin_op*>(in));
    case Constant::ID: return pre_constant(dynamic_cast<Constant*>(in));
    case Instanceof::ID: return pre_instanceof(dynamic_cast<Instanceof*>(in));
    case Method_invocation::ID: return pre_method_invocation(dynamic_cast<Method_invocation*>(in));
    case New::ID: return pre_new(dynamic_cast<New*>(in));
    case INT::ID: return pre_int(dynamic_cast<INT*>(in));
    case REAL::ID: return pre_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return pre_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return pre_nil(dynamic_cast<NIL*>(in));
    case VARIABLE_NAME::ID: return pre_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case Variable_variable::ID: return pre_variable_variable(dynamic_cast<Variable_variable*>(in));
    case Array_access::ID: return pre_array_access(dynamic_cast<Array_access*>(in));
    case Field_access::ID: return pre_field_access(dynamic_cast<Field_access*>(in));
    case Array_next::ID: return pre_array_next(dynamic_cast<Array_next*>(in));
    case FOREIGN::ID: return pre_foreign(dynamic_cast<FOREIGN*>(in));
    case Isset::ID: return pre_isset(dynamic_cast<Isset*>(in));
    case Foreach_has_key::ID: return pre_foreach_has_key(dynamic_cast<Foreach_has_key*>(in));
    case Foreach_get_key::ID: return pre_foreach_get_key(dynamic_cast<Foreach_get_key*>(in));
    case Foreach_get_val::ID: return pre_foreach_get_val(dynamic_cast<Foreach_get_val*>(in));
    case Param_is_ref::ID: return pre_param_is_ref(dynamic_cast<Param_is_ref*>(in));
    }
    assert(0);
}

Target* Transform::pre_target(Target* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID: return pre_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case CLASS_NAME::ID: return pre_class_name(dynamic_cast<CLASS_NAME*>(in));
    }
    assert(0);
}

Field_name* Transform::pre_field_name(Field_name* in)
{
    switch(in->classid())
    {
    case FIELD_NAME::ID: return pre_field_name(dynamic_cast<FIELD_NAME*>(in));
    case Variable_field::ID: return pre_variable_field(dynamic_cast<Variable_field*>(in));
    }
    assert(0);
}

Class_name* Transform::pre_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID: return pre_class_name(dynamic_cast<CLASS_NAME*>(in));
    case Variable_class::ID: return pre_variable_class(dynamic_cast<Variable_class*>(in));
    }
    assert(0);
}

Method_name* Transform::pre_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID: return pre_method_name(dynamic_cast<METHOD_NAME*>(in));
    case Variable_method::ID: return pre_variable_method(dynamic_cast<Variable_method*>(in));
    }
    assert(0);
}

Static_array_key* Transform::pre_static_array_key(Static_array_key* in)
{
    switch(in->classid())
    {
    case INT::ID: return pre_int(dynamic_cast<INT*>(in));
    case REAL::ID: return pre_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return pre_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return pre_nil(dynamic_cast<NIL*>(in));
    case Constant::ID: return pre_constant(dynamic_cast<Constant*>(in));
    }
    assert(0);
}

/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
void Transform::post_statement(Statement* in, Statement_list* out)
{
    switch(in->classid())
    {
    case Class_def::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_class_def(dynamic_cast<Class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Interface_def::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_interface_def(dynamic_cast<Interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Method::ID: 
    	{
    		Method_list* local_out = new Method_list;
    		Method_list::const_iterator i;
    		post_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Class_alias::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_class_alias(dynamic_cast<Class_alias*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Interface_alias::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_interface_alias(dynamic_cast<Interface_alias*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Method_alias::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_method_alias(dynamic_cast<Method_alias*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Return::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_return(dynamic_cast<Return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Static_declaration::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_static_declaration(dynamic_cast<Static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Global::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_global(dynamic_cast<Global*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Try::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_try(dynamic_cast<Try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Throw::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_throw(dynamic_cast<Throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_var::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_var(dynamic_cast<Assign_var*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_var_var::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_var_var(dynamic_cast<Assign_var_var*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_array::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_array(dynamic_cast<Assign_array*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_next::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_next(dynamic_cast<Assign_next*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_field::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_field(dynamic_cast<Assign_field*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Eval_expr::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_eval_expr(dynamic_cast<Eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Pre_op::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_pre_op(dynamic_cast<Pre_op*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Unset::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_unset(dynamic_cast<Unset*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Label::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_label(dynamic_cast<Label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Goto::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_goto(dynamic_cast<Goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Branch::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_branch(dynamic_cast<Branch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach_next::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_foreach_next(dynamic_cast<Foreach_next*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach_reset::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_foreach_reset(dynamic_cast<Foreach_reset*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach_end::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_foreach_end(dynamic_cast<Foreach_end*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case FOREIGN::ID: 
    	out->push_back(post_foreign(dynamic_cast<FOREIGN*>(in)));
    	return;
    }
    assert(0);
}

void Transform::post_member(Member* in, Member_list* out)
{
    switch(in->classid())
    {
    case Method::ID: 
    	{
    		Method_list* local_out = new Method_list;
    		Method_list::const_iterator i;
    		post_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Attribute::ID: 
    	{
    		Member_list* local_out = new Member_list;
    		Member_list::const_iterator i;
    		post_attribute(dynamic_cast<Attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Static_value* Transform::post_static_value(Static_value* in)
{
    switch(in->classid())
    {
    case INT::ID: return post_int(dynamic_cast<INT*>(in));
    case REAL::ID: return post_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return post_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return post_nil(dynamic_cast<NIL*>(in));
    case Static_array::ID: return post_static_array(dynamic_cast<Static_array*>(in));
    case Constant::ID: return post_constant(dynamic_cast<Constant*>(in));
    }
    assert(0);
}

Rvalue* Transform::post_rvalue(Rvalue* in)
{
    switch(in->classid())
    {
    case INT::ID: return post_int(dynamic_cast<INT*>(in));
    case REAL::ID: return post_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return post_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return post_nil(dynamic_cast<NIL*>(in));
    case VARIABLE_NAME::ID: return post_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    }
    assert(0);
}

Variable_name* Transform::post_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID: return post_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case Variable_variable::ID: return post_variable_variable(dynamic_cast<Variable_variable*>(in));
    }
    assert(0);
}

Expr* Transform::post_expr(Expr* in)
{
    switch(in->classid())
    {
    case Cast::ID: return post_cast(dynamic_cast<Cast*>(in));
    case Unary_op::ID: return post_unary_op(dynamic_cast<Unary_op*>(in));
    case Bin_op::ID: return post_bin_op(dynamic_cast<Bin_op*>(in));
    case Constant::ID: return post_constant(dynamic_cast<Constant*>(in));
    case Instanceof::ID: return post_instanceof(dynamic_cast<Instanceof*>(in));
    case Method_invocation::ID: return post_method_invocation(dynamic_cast<Method_invocation*>(in));
    case New::ID: return post_new(dynamic_cast<New*>(in));
    case INT::ID: return post_int(dynamic_cast<INT*>(in));
    case REAL::ID: return post_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return post_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return post_nil(dynamic_cast<NIL*>(in));
    case VARIABLE_NAME::ID: return post_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case Variable_variable::ID: return post_variable_variable(dynamic_cast<Variable_variable*>(in));
    case Array_access::ID: return post_array_access(dynamic_cast<Array_access*>(in));
    case Field_access::ID: return post_field_access(dynamic_cast<Field_access*>(in));
    case Array_next::ID: return post_array_next(dynamic_cast<Array_next*>(in));
    case FOREIGN::ID: return post_foreign(dynamic_cast<FOREIGN*>(in));
    case Isset::ID: return post_isset(dynamic_cast<Isset*>(in));
    case Foreach_has_key::ID: return post_foreach_has_key(dynamic_cast<Foreach_has_key*>(in));
    case Foreach_get_key::ID: return post_foreach_get_key(dynamic_cast<Foreach_get_key*>(in));
    case Foreach_get_val::ID: return post_foreach_get_val(dynamic_cast<Foreach_get_val*>(in));
    case Param_is_ref::ID: return post_param_is_ref(dynamic_cast<Param_is_ref*>(in));
    }
    assert(0);
}

Target* Transform::post_target(Target* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID: return post_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case CLASS_NAME::ID: return post_class_name(dynamic_cast<CLASS_NAME*>(in));
    }
    assert(0);
}

Field_name* Transform::post_field_name(Field_name* in)
{
    switch(in->classid())
    {
    case FIELD_NAME::ID: return post_field_name(dynamic_cast<FIELD_NAME*>(in));
    case Variable_field::ID: return post_variable_field(dynamic_cast<Variable_field*>(in));
    }
    assert(0);
}

Class_name* Transform::post_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID: return post_class_name(dynamic_cast<CLASS_NAME*>(in));
    case Variable_class::ID: return post_variable_class(dynamic_cast<Variable_class*>(in));
    }
    assert(0);
}

Method_name* Transform::post_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID: return post_method_name(dynamic_cast<METHOD_NAME*>(in));
    case Variable_method::ID: return post_variable_method(dynamic_cast<Variable_method*>(in));
    }
    assert(0);
}

Static_array_key* Transform::post_static_array_key(Static_array_key* in)
{
    switch(in->classid())
    {
    case INT::ID: return post_int(dynamic_cast<INT*>(in));
    case REAL::ID: return post_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return post_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return post_nil(dynamic_cast<NIL*>(in));
    case Constant::ID: return post_constant(dynamic_cast<Constant*>(in));
    }
    assert(0);
}

/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
void Transform::children_statement(Statement* in)
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
    case Class_alias::ID:
    	children_class_alias(dynamic_cast<Class_alias*>(in));
    	break;
    case Interface_alias::ID:
    	children_interface_alias(dynamic_cast<Interface_alias*>(in));
    	break;
    case Method_alias::ID:
    	children_method_alias(dynamic_cast<Method_alias*>(in));
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
    case Assign_var::ID:
    	children_assign_var(dynamic_cast<Assign_var*>(in));
    	break;
    case Assign_var_var::ID:
    	children_assign_var_var(dynamic_cast<Assign_var_var*>(in));
    	break;
    case Assign_array::ID:
    	children_assign_array(dynamic_cast<Assign_array*>(in));
    	break;
    case Assign_next::ID:
    	children_assign_next(dynamic_cast<Assign_next*>(in));
    	break;
    case Assign_field::ID:
    	children_assign_field(dynamic_cast<Assign_field*>(in));
    	break;
    case Eval_expr::ID:
    	children_eval_expr(dynamic_cast<Eval_expr*>(in));
    	break;
    case Pre_op::ID:
    	children_pre_op(dynamic_cast<Pre_op*>(in));
    	break;
    case Unset::ID:
    	children_unset(dynamic_cast<Unset*>(in));
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
    case FOREIGN::ID:
    	children_foreign(dynamic_cast<FOREIGN*>(in));
    	break;
    }
}

void Transform::children_member(Member* in)
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

void Transform::children_static_value(Static_value* in)
{
    switch(in->classid())
    {
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
    case Static_array::ID:
    	children_static_array(dynamic_cast<Static_array*>(in));
    	break;
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    }
}

void Transform::children_rvalue(Rvalue* in)
{
    switch(in->classid())
    {
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
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    }
}

void Transform::children_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	children_variable_variable(dynamic_cast<Variable_variable*>(in));
    	break;
    }
}

void Transform::children_expr(Expr* in)
{
    switch(in->classid())
    {
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
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case Variable_variable::ID:
    	children_variable_variable(dynamic_cast<Variable_variable*>(in));
    	break;
    case Array_access::ID:
    	children_array_access(dynamic_cast<Array_access*>(in));
    	break;
    case Field_access::ID:
    	children_field_access(dynamic_cast<Field_access*>(in));
    	break;
    case Array_next::ID:
    	children_array_next(dynamic_cast<Array_next*>(in));
    	break;
    case FOREIGN::ID:
    	children_foreign(dynamic_cast<FOREIGN*>(in));
    	break;
    case Isset::ID:
    	children_isset(dynamic_cast<Isset*>(in));
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
    case Param_is_ref::ID:
    	children_param_is_ref(dynamic_cast<Param_is_ref*>(in));
    	break;
    }
}

void Transform::children_target(Target* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID:
    	children_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    	break;
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
    	break;
    }
}

void Transform::children_field_name(Field_name* in)
{
    switch(in->classid())
    {
    case FIELD_NAME::ID:
    	children_field_name(dynamic_cast<FIELD_NAME*>(in));
    	break;
    case Variable_field::ID:
    	children_variable_field(dynamic_cast<Variable_field*>(in));
    	break;
    }
}

void Transform::children_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
    	break;
    case Variable_class::ID:
    	children_variable_class(dynamic_cast<Variable_class*>(in));
    	break;
    }
}

void Transform::children_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID:
    	children_method_name(dynamic_cast<METHOD_NAME*>(in));
    	break;
    case Variable_method::ID:
    	children_variable_method(dynamic_cast<Variable_method*>(in));
    	break;
    }
}

void Transform::children_static_array_key(Static_array_key* in)
{
    switch(in->classid())
    {
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
    case Constant::ID:
    	children_constant(dynamic_cast<Constant*>(in));
    	break;
    }
}
}

