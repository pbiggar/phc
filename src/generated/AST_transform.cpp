#include "AST_transform.h"

namespace AST{
Transform::~Transform()
{
}

// Invoked before the children are transformed
PHP_script* Transform::pre_php_script(PHP_script* in)
{
    return in;
}

void Transform::pre_class_def(Class_def* in, List<Statement*>* out)
{
    out->push_back(in);
}

Class_mod* Transform::pre_class_mod(Class_mod* in)
{
    return in;
}

void Transform::pre_interface_def(Interface_def* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_method(Method* in, List<Method*>* out)
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

void Transform::pre_formal_parameter(Formal_parameter* in, List<Formal_parameter*>* out)
{
    out->push_back(in);
}

Type* Transform::pre_type(Type* in)
{
    return in;
}

void Transform::pre_attribute(Attribute* in, List<Member*>* out)
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

void Transform::pre_if(If* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_while(While* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_do(Do* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_for(For* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_foreach(Foreach* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_switch(Switch* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_switch_case(Switch_case* in, List<Switch_case*>* out)
{
    out->push_back(in);
}

void Transform::pre_break(Break* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_continue(Continue* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_return(Return* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_static_declaration(Static_declaration* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_global(Global* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_declare(Declare* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_directive(Directive* in, List<Directive*>* out)
{
    out->push_back(in);
}

void Transform::pre_try(Try* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_catch(Catch* in, List<Catch*>* out)
{
    out->push_back(in);
}

void Transform::pre_throw(Throw* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_eval_expr(Eval_expr* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_nop(Nop* in, List<Statement*>* out)
{
    out->push_back(in);
}

Foreign* Transform::pre_foreign(Foreign* in)
{
    return in;
}

void Transform::pre_branch(Branch* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_goto(Goto* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::pre_label(Label* in, List<Statement*>* out)
{
    out->push_back(in);
}

Expr* Transform::pre_assignment(Assignment* in)
{
    return in;
}

Expr* Transform::pre_op_assignment(Op_assignment* in)
{
    return in;
}

Expr* Transform::pre_list_assignment(List_assignment* in)
{
    return in;
}

void Transform::pre_nested_list_elements(Nested_list_elements* in, List<List_element*>* out)
{
    out->push_back(in);
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

Expr* Transform::pre_conditional_expr(Conditional_expr* in)
{
    return in;
}

Expr* Transform::pre_ignore_errors(Ignore_errors* in)
{
    return in;
}

Expr* Transform::pre_constant(Constant* in)
{
    return in;
}

Expr* Transform::pre_instanceof(Instanceof* in)
{
    return in;
}

Variable* Transform::pre_variable(Variable* in)
{
    return in;
}

Reflection* Transform::pre_reflection(Reflection* in)
{
    return in;
}

Expr* Transform::pre_pre_op(Pre_op* in)
{
    return in;
}

Expr* Transform::pre_post_op(Post_op* in)
{
    return in;
}

Expr* Transform::pre_array(Array* in)
{
    return in;
}

void Transform::pre_array_elem(Array_elem* in, List<Array_elem*>* out)
{
    out->push_back(in);
}

Expr* Transform::pre_method_invocation(Method_invocation* in)
{
    return in;
}

void Transform::pre_actual_parameter(Actual_parameter* in, List<Actual_parameter*>* out)
{
    out->push_back(in);
}

Expr* Transform::pre_new(New* in)
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

DIRECTIVE_NAME* Transform::pre_directive_name(DIRECTIVE_NAME* in)
{
    return in;
}

LABEL_NAME* Transform::pre_label_name(LABEL_NAME* in)
{
    return in;
}

Expr* Transform::pre_int(INT* in)
{
    return in;
}

Expr* Transform::pre_real(REAL* in)
{
    return in;
}

Expr* Transform::pre_string(STRING* in)
{
    return in;
}

Expr* Transform::pre_bool(BOOL* in)
{
    return in;
}

Expr* Transform::pre_nil(NIL* in)
{
    return in;
}

OP* Transform::pre_op(OP* in)
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

// Invoked after the children have been transformed
PHP_script* Transform::post_php_script(PHP_script* in)
{
    return in;
}

void Transform::post_class_def(Class_def* in, List<Statement*>* out)
{
    out->push_back(in);
}

Class_mod* Transform::post_class_mod(Class_mod* in)
{
    return in;
}

void Transform::post_interface_def(Interface_def* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_method(Method* in, List<Method*>* out)
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

void Transform::post_formal_parameter(Formal_parameter* in, List<Formal_parameter*>* out)
{
    out->push_back(in);
}

Type* Transform::post_type(Type* in)
{
    return in;
}

void Transform::post_attribute(Attribute* in, List<Member*>* out)
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

void Transform::post_if(If* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_while(While* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_do(Do* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_for(For* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_foreach(Foreach* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_switch(Switch* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_switch_case(Switch_case* in, List<Switch_case*>* out)
{
    out->push_back(in);
}

void Transform::post_break(Break* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_continue(Continue* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_return(Return* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_static_declaration(Static_declaration* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_global(Global* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_declare(Declare* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_directive(Directive* in, List<Directive*>* out)
{
    out->push_back(in);
}

void Transform::post_try(Try* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_catch(Catch* in, List<Catch*>* out)
{
    out->push_back(in);
}

void Transform::post_throw(Throw* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_eval_expr(Eval_expr* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_nop(Nop* in, List<Statement*>* out)
{
    out->push_back(in);
}

Foreign* Transform::post_foreign(Foreign* in)
{
    return in;
}

void Transform::post_branch(Branch* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_goto(Goto* in, List<Statement*>* out)
{
    out->push_back(in);
}

void Transform::post_label(Label* in, List<Statement*>* out)
{
    out->push_back(in);
}

Expr* Transform::post_assignment(Assignment* in)
{
    return in;
}

Expr* Transform::post_op_assignment(Op_assignment* in)
{
    return in;
}

Expr* Transform::post_list_assignment(List_assignment* in)
{
    return in;
}

void Transform::post_nested_list_elements(Nested_list_elements* in, List<List_element*>* out)
{
    out->push_back(in);
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

Expr* Transform::post_conditional_expr(Conditional_expr* in)
{
    return in;
}

Expr* Transform::post_ignore_errors(Ignore_errors* in)
{
    return in;
}

Expr* Transform::post_constant(Constant* in)
{
    return in;
}

Expr* Transform::post_instanceof(Instanceof* in)
{
    return in;
}

Variable* Transform::post_variable(Variable* in)
{
    return in;
}

Reflection* Transform::post_reflection(Reflection* in)
{
    return in;
}

Expr* Transform::post_pre_op(Pre_op* in)
{
    return in;
}

Expr* Transform::post_post_op(Post_op* in)
{
    return in;
}

Expr* Transform::post_array(Array* in)
{
    return in;
}

void Transform::post_array_elem(Array_elem* in, List<Array_elem*>* out)
{
    out->push_back(in);
}

Expr* Transform::post_method_invocation(Method_invocation* in)
{
    return in;
}

void Transform::post_actual_parameter(Actual_parameter* in, List<Actual_parameter*>* out)
{
    out->push_back(in);
}

Expr* Transform::post_new(New* in)
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

DIRECTIVE_NAME* Transform::post_directive_name(DIRECTIVE_NAME* in)
{
    return in;
}

LABEL_NAME* Transform::post_label_name(LABEL_NAME* in)
{
    return in;
}

Expr* Transform::post_int(INT* in)
{
    return in;
}

Expr* Transform::post_real(REAL* in)
{
    return in;
}

Expr* Transform::post_string(STRING* in)
{
    return in;
}

Expr* Transform::post_bool(BOOL* in)
{
    return in;
}

Expr* Transform::post_nil(NIL* in)
{
    return in;
}

OP* Transform::post_op(OP* in)
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

// Transform the children of the node
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
    in->vars = transform_name_with_default_list(in->vars);
}

void Transform::children_attr_mod(Attr_mod* in)
{
}

void Transform::children_name_with_default(Name_with_default* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->expr = transform_expr(in->expr);
}

void Transform::children_if(If* in)
{
    in->expr = transform_expr(in->expr);
    in->iftrue = transform_statement_list(in->iftrue);
    in->iffalse = transform_statement_list(in->iffalse);
}

void Transform::children_while(While* in)
{
    in->expr = transform_expr(in->expr);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_do(Do* in)
{
    in->statements = transform_statement_list(in->statements);
    in->expr = transform_expr(in->expr);
}

void Transform::children_for(For* in)
{
    in->init = transform_expr(in->init);
    in->cond = transform_expr(in->cond);
    in->incr = transform_expr(in->incr);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_foreach(Foreach* in)
{
    in->expr = transform_expr(in->expr);
    in->key = transform_variable(in->key);
    in->val = transform_variable(in->val);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_switch(Switch* in)
{
    in->expr = transform_expr(in->expr);
    in->switch_cases = transform_switch_case_list(in->switch_cases);
}

void Transform::children_switch_case(Switch_case* in)
{
    in->expr = transform_expr(in->expr);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_break(Break* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_continue(Continue* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_return(Return* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_static_declaration(Static_declaration* in)
{
    in->vars = transform_name_with_default_list(in->vars);
}

void Transform::children_global(Global* in)
{
    in->variable_names = transform_variable_name_list(in->variable_names);
}

void Transform::children_declare(Declare* in)
{
    in->directives = transform_directive_list(in->directives);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_directive(Directive* in)
{
    in->directive_name = transform_directive_name(in->directive_name);
    in->expr = transform_expr(in->expr);
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
    in->expr = transform_expr(in->expr);
}

void Transform::children_eval_expr(Eval_expr* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_nop(Nop* in)
{
}

void Transform::children_foreign(Foreign* in)
{
}

void Transform::children_branch(Branch* in)
{
    in->expr = transform_expr(in->expr);
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

void Transform::children_assignment(Assignment* in)
{
    in->variable = transform_variable(in->variable);
    in->expr = transform_expr(in->expr);
}

void Transform::children_op_assignment(Op_assignment* in)
{
    in->variable = transform_variable(in->variable);
    in->op = transform_op(in->op);
    in->expr = transform_expr(in->expr);
}

void Transform::children_list_assignment(List_assignment* in)
{
    in->list_elements = transform_list_element_list(in->list_elements);
    in->expr = transform_expr(in->expr);
}

void Transform::children_nested_list_elements(Nested_list_elements* in)
{
    in->list_elements = transform_list_element_list(in->list_elements);
}

void Transform::children_cast(Cast* in)
{
    in->cast = transform_cast(in->cast);
    in->expr = transform_expr(in->expr);
}

void Transform::children_unary_op(Unary_op* in)
{
    in->op = transform_op(in->op);
    in->expr = transform_expr(in->expr);
}

void Transform::children_bin_op(Bin_op* in)
{
    in->left = transform_expr(in->left);
    in->op = transform_op(in->op);
    in->right = transform_expr(in->right);
}

void Transform::children_conditional_expr(Conditional_expr* in)
{
    in->cond = transform_expr(in->cond);
    in->iftrue = transform_expr(in->iftrue);
    in->iffalse = transform_expr(in->iffalse);
}

void Transform::children_ignore_errors(Ignore_errors* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_constant(Constant* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->constant_name = transform_constant_name(in->constant_name);
}

void Transform::children_instanceof(Instanceof* in)
{
    in->expr = transform_expr(in->expr);
    in->class_name = transform_class_name(in->class_name);
}

void Transform::children_variable(Variable* in)
{
    in->target = transform_target(in->target);
    in->variable_name = transform_variable_name(in->variable_name);
    in->array_indices = transform_expr_list(in->array_indices);
}

void Transform::children_reflection(Reflection* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_pre_op(Pre_op* in)
{
    in->op = transform_op(in->op);
    in->variable = transform_variable(in->variable);
}

void Transform::children_post_op(Post_op* in)
{
    in->variable = transform_variable(in->variable);
    in->op = transform_op(in->op);
}

void Transform::children_array(Array* in)
{
    in->array_elems = transform_array_elem_list(in->array_elems);
}

void Transform::children_array_elem(Array_elem* in)
{
    in->key = transform_expr(in->key);
    in->val = transform_expr(in->val);
}

void Transform::children_method_invocation(Method_invocation* in)
{
    in->target = transform_target(in->target);
    in->method_name = transform_method_name(in->method_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

void Transform::children_actual_parameter(Actual_parameter* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_new(New* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

// Tokens don't have children, so these methods do nothing by default
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

void Transform::children_directive_name(DIRECTIVE_NAME* in)
{
}

void Transform::children_label_name(LABEL_NAME* in)
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

void Transform::children_op(OP* in)
{
}

void Transform::children_cast(CAST* in)
{
}

void Transform::children_constant_name(CONSTANT_NAME* in)
{
}

// Call the pre-transform, transform-children post-transform methods in order
// Do not override unless you know what you are doing
List<Statement*>* Transform::transform_statement_list(List<Statement*>* in)
{
    List<Statement*>::const_iterator i;
    List<Statement*>* out = new List<Statement*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_statement(*i));
    }
    
    return out;
}

List<Statement*>* Transform::transform_statement(Statement* in)
{
    List<Statement*>::const_iterator i;
    List<Statement*>* out1 = new List<Statement*>;
    List<Statement*>* out2 = new List<Statement*>;
    
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

List<INTERFACE_NAME*>* Transform::transform_interface_name_list(List<INTERFACE_NAME*>* in)
{
    List<INTERFACE_NAME*>::const_iterator i;
    List<INTERFACE_NAME*>* out = new List<INTERFACE_NAME*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_interface_name(*i));
    }
    
    return out;
}

List<Member*>* Transform::transform_member_list(List<Member*>* in)
{
    List<Member*>::const_iterator i;
    List<Member*>* out = new List<Member*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_member(*i));
    }
    
    return out;
}

List<Member*>* Transform::transform_member(Member* in)
{
    List<Member*>::const_iterator i;
    List<Member*>* out1 = new List<Member*>;
    List<Member*>* out2 = new List<Member*>;
    
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

List<Formal_parameter*>* Transform::transform_formal_parameter_list(List<Formal_parameter*>* in)
{
    List<Formal_parameter*>::const_iterator i;
    List<Formal_parameter*>* out = new List<Formal_parameter*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_formal_parameter(*i));
    }
    
    return out;
}

List<Formal_parameter*>* Transform::transform_formal_parameter(Formal_parameter* in)
{
    List<Formal_parameter*>::const_iterator i;
    List<Formal_parameter*>* out1 = new List<Formal_parameter*>;
    List<Formal_parameter*>* out2 = new List<Formal_parameter*>;
    
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

List<Name_with_default*>* Transform::transform_name_with_default_list(List<Name_with_default*>* in)
{
    List<Name_with_default*>::const_iterator i;
    List<Name_with_default*>* out = new List<Name_with_default*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_name_with_default(*i));
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

Variable* Transform::transform_variable(Variable* in)
{
    if(in == NULL) return NULL;
    
    Variable* out;
    
    out = pre_variable(in);
    if(out != NULL)
    {
    	children_variable(out);
    	out = post_variable(out);
    }
    
    return out;
}

List<Switch_case*>* Transform::transform_switch_case_list(List<Switch_case*>* in)
{
    List<Switch_case*>::const_iterator i;
    List<Switch_case*>* out = new List<Switch_case*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_switch_case(*i));
    }
    
    return out;
}

List<Switch_case*>* Transform::transform_switch_case(Switch_case* in)
{
    List<Switch_case*>::const_iterator i;
    List<Switch_case*>* out1 = new List<Switch_case*>;
    List<Switch_case*>* out2 = new List<Switch_case*>;
    
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

List<Variable_name*>* Transform::transform_variable_name_list(List<Variable_name*>* in)
{
    List<Variable_name*>::const_iterator i;
    List<Variable_name*>* out = new List<Variable_name*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_variable_name(*i));
    }
    
    return out;
}

List<Directive*>* Transform::transform_directive_list(List<Directive*>* in)
{
    List<Directive*>::const_iterator i;
    List<Directive*>* out = new List<Directive*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_directive(*i));
    }
    
    return out;
}

List<Directive*>* Transform::transform_directive(Directive* in)
{
    List<Directive*>::const_iterator i;
    List<Directive*>* out1 = new List<Directive*>;
    List<Directive*>* out2 = new List<Directive*>;
    
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

DIRECTIVE_NAME* Transform::transform_directive_name(DIRECTIVE_NAME* in)
{
    if(in == NULL) return NULL;
    
    DIRECTIVE_NAME* out;
    
    out = pre_directive_name(in);
    if(out != NULL)
    {
    	children_directive_name(out);
    	out = post_directive_name(out);
    }
    
    return out;
}

List<Catch*>* Transform::transform_catch_list(List<Catch*>* in)
{
    List<Catch*>::const_iterator i;
    List<Catch*>* out = new List<Catch*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_catch(*i));
    }
    
    return out;
}

List<Catch*>* Transform::transform_catch(Catch* in)
{
    List<Catch*>::const_iterator i;
    List<Catch*>* out1 = new List<Catch*>;
    List<Catch*>* out2 = new List<Catch*>;
    
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

List<List_element*>* Transform::transform_list_element_list(List<List_element*>* in)
{
    List<List_element*>::const_iterator i;
    List<List_element*>* out = new List<List_element*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_list_element(*i));
    }
    
    return out;
}

List<List_element*>* Transform::transform_list_element(List_element* in)
{
    List<List_element*>::const_iterator i;
    List<List_element*>* out1 = new List<List_element*>;
    List<List_element*>* out2 = new List<List_element*>;
    
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

List<Expr*>* Transform::transform_expr_list(List<Expr*>* in)
{
    List<Expr*>::const_iterator i;
    List<Expr*>* out = new List<Expr*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_expr(*i));
    }
    
    return out;
}

List<Array_elem*>* Transform::transform_array_elem_list(List<Array_elem*>* in)
{
    List<Array_elem*>::const_iterator i;
    List<Array_elem*>* out = new List<Array_elem*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_array_elem(*i));
    }
    
    return out;
}

List<Array_elem*>* Transform::transform_array_elem(Array_elem* in)
{
    List<Array_elem*>::const_iterator i;
    List<Array_elem*>* out1 = new List<Array_elem*>;
    List<Array_elem*>* out2 = new List<Array_elem*>;
    
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

List<Actual_parameter*>* Transform::transform_actual_parameter_list(List<Actual_parameter*>* in)
{
    List<Actual_parameter*>::const_iterator i;
    List<Actual_parameter*>* out = new List<Actual_parameter*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_actual_parameter(*i));
    }
    
    return out;
}

List<Actual_parameter*>* Transform::transform_actual_parameter(Actual_parameter* in)
{
    List<Actual_parameter*>::const_iterator i;
    List<Actual_parameter*>* out1 = new List<Actual_parameter*>;
    List<Actual_parameter*>* out2 = new List<Actual_parameter*>;
    
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

// Invoke the right pre-transform (manual dispatching)
// Do not override unless you know what you are doing
void Transform::pre_statement(Statement* in, List<Statement*>* out)
{
    switch(in->classid())
    {
    case Class_def::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_class_def(dynamic_cast<Class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Interface_def::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_interface_def(dynamic_cast<Interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Method::ID: 
    	{
    		List<Method*>* local_out = new List<Method*>;
    		List<Method*>::const_iterator i;
    		pre_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Return::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_return(dynamic_cast<Return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Static_declaration::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_static_declaration(dynamic_cast<Static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Global::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_global(dynamic_cast<Global*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Try::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_try(dynamic_cast<Try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Throw::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_throw(dynamic_cast<Throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Eval_expr::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_eval_expr(dynamic_cast<Eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case If::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_if(dynamic_cast<If*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case While::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_while(dynamic_cast<While*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Do::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_do(dynamic_cast<Do*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case For::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_for(dynamic_cast<For*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_foreach(dynamic_cast<Foreach*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Switch::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_switch(dynamic_cast<Switch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Break::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_break(dynamic_cast<Break*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Continue::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_continue(dynamic_cast<Continue*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Declare::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_declare(dynamic_cast<Declare*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Nop::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_nop(dynamic_cast<Nop*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Label::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_label(dynamic_cast<Label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Goto::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_goto(dynamic_cast<Goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Branch::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		pre_branch(dynamic_cast<Branch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreign::ID: 
    	out->push_back(pre_foreign(dynamic_cast<Foreign*>(in)));
    	return;
    }
    assert(0);
}

void Transform::pre_member(Member* in, List<Member*>* out)
{
    switch(in->classid())
    {
    case Method::ID: 
    	{
    		List<Method*>* local_out = new List<Method*>;
    		List<Method*>::const_iterator i;
    		pre_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Attribute::ID: 
    	{
    		List<Member*>* local_out = new List<Member*>;
    		List<Member*>::const_iterator i;
    		pre_attribute(dynamic_cast<Attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Expr* Transform::pre_expr(Expr* in)
{
    switch(in->classid())
    {
    case Assignment::ID: return pre_assignment(dynamic_cast<Assignment*>(in));
    case Cast::ID: return pre_cast(dynamic_cast<Cast*>(in));
    case Unary_op::ID: return pre_unary_op(dynamic_cast<Unary_op*>(in));
    case Bin_op::ID: return pre_bin_op(dynamic_cast<Bin_op*>(in));
    case Constant::ID: return pre_constant(dynamic_cast<Constant*>(in));
    case Instanceof::ID: return pre_instanceof(dynamic_cast<Instanceof*>(in));
    case Variable::ID: return pre_variable(dynamic_cast<Variable*>(in));
    case Pre_op::ID: return pre_pre_op(dynamic_cast<Pre_op*>(in));
    case Method_invocation::ID: return pre_method_invocation(dynamic_cast<Method_invocation*>(in));
    case New::ID: return pre_new(dynamic_cast<New*>(in));
    case INT::ID: return pre_int(dynamic_cast<INT*>(in));
    case REAL::ID: return pre_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return pre_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return pre_nil(dynamic_cast<NIL*>(in));
    case Op_assignment::ID: return pre_op_assignment(dynamic_cast<Op_assignment*>(in));
    case List_assignment::ID: return pre_list_assignment(dynamic_cast<List_assignment*>(in));
    case Post_op::ID: return pre_post_op(dynamic_cast<Post_op*>(in));
    case Array::ID: return pre_array(dynamic_cast<Array*>(in));
    case Conditional_expr::ID: return pre_conditional_expr(dynamic_cast<Conditional_expr*>(in));
    case Ignore_errors::ID: return pre_ignore_errors(dynamic_cast<Ignore_errors*>(in));
    case Foreign::ID: return pre_foreign(dynamic_cast<Foreign*>(in));
    }
    assert(0);
}

Variable_name* Transform::pre_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID: return pre_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case Reflection::ID: return pre_reflection(dynamic_cast<Reflection*>(in));
    }
    assert(0);
}

void Transform::pre_list_element(List_element* in, List<List_element*>* out)
{
    switch(in->classid())
    {
    case Variable::ID: 
    	out->push_back(pre_variable(dynamic_cast<Variable*>(in)));
    	return;
    case Nested_list_elements::ID: 
    	{
    		List<List_element*>* local_out = new List<List_element*>;
    		List<List_element*>::const_iterator i;
    		pre_nested_list_elements(dynamic_cast<Nested_list_elements*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Class_name* Transform::pre_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID: return pre_class_name(dynamic_cast<CLASS_NAME*>(in));
    case Reflection::ID: return pre_reflection(dynamic_cast<Reflection*>(in));
    }
    assert(0);
}

Target* Transform::pre_target(Target* in)
{
    switch(in->classid())
    {
    case Assignment::ID: return pre_assignment(dynamic_cast<Assignment*>(in));
    case Cast::ID: return pre_cast(dynamic_cast<Cast*>(in));
    case Unary_op::ID: return pre_unary_op(dynamic_cast<Unary_op*>(in));
    case Bin_op::ID: return pre_bin_op(dynamic_cast<Bin_op*>(in));
    case Constant::ID: return pre_constant(dynamic_cast<Constant*>(in));
    case Instanceof::ID: return pre_instanceof(dynamic_cast<Instanceof*>(in));
    case Variable::ID: return pre_variable(dynamic_cast<Variable*>(in));
    case Pre_op::ID: return pre_pre_op(dynamic_cast<Pre_op*>(in));
    case Method_invocation::ID: return pre_method_invocation(dynamic_cast<Method_invocation*>(in));
    case New::ID: return pre_new(dynamic_cast<New*>(in));
    case INT::ID: return pre_int(dynamic_cast<INT*>(in));
    case REAL::ID: return pre_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return pre_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return pre_nil(dynamic_cast<NIL*>(in));
    case Op_assignment::ID: return pre_op_assignment(dynamic_cast<Op_assignment*>(in));
    case List_assignment::ID: return pre_list_assignment(dynamic_cast<List_assignment*>(in));
    case Post_op::ID: return pre_post_op(dynamic_cast<Post_op*>(in));
    case Array::ID: return pre_array(dynamic_cast<Array*>(in));
    case Conditional_expr::ID: return pre_conditional_expr(dynamic_cast<Conditional_expr*>(in));
    case Ignore_errors::ID: return pre_ignore_errors(dynamic_cast<Ignore_errors*>(in));
    case Foreign::ID: return pre_foreign(dynamic_cast<Foreign*>(in));
    case CLASS_NAME::ID: return pre_class_name(dynamic_cast<CLASS_NAME*>(in));
    }
    assert(0);
}

Method_name* Transform::pre_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID: return pre_method_name(dynamic_cast<METHOD_NAME*>(in));
    case Reflection::ID: return pre_reflection(dynamic_cast<Reflection*>(in));
    }
    assert(0);
}

// Invoke the right post-transform (manual dispatching)
// Do not override unless you know what you are doing
void Transform::post_statement(Statement* in, List<Statement*>* out)
{
    switch(in->classid())
    {
    case Class_def::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_class_def(dynamic_cast<Class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Interface_def::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_interface_def(dynamic_cast<Interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Method::ID: 
    	{
    		List<Method*>* local_out = new List<Method*>;
    		List<Method*>::const_iterator i;
    		post_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Return::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_return(dynamic_cast<Return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Static_declaration::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_static_declaration(dynamic_cast<Static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Global::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_global(dynamic_cast<Global*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Try::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_try(dynamic_cast<Try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Throw::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_throw(dynamic_cast<Throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Eval_expr::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_eval_expr(dynamic_cast<Eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case If::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_if(dynamic_cast<If*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case While::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_while(dynamic_cast<While*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Do::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_do(dynamic_cast<Do*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case For::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_for(dynamic_cast<For*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreach::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_foreach(dynamic_cast<Foreach*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Switch::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_switch(dynamic_cast<Switch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Break::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_break(dynamic_cast<Break*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Continue::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_continue(dynamic_cast<Continue*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Declare::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_declare(dynamic_cast<Declare*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Nop::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_nop(dynamic_cast<Nop*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Label::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_label(dynamic_cast<Label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Goto::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_goto(dynamic_cast<Goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Branch::ID: 
    	{
    		List<Statement*>* local_out = new List<Statement*>;
    		List<Statement*>::const_iterator i;
    		post_branch(dynamic_cast<Branch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Foreign::ID: 
    	out->push_back(post_foreign(dynamic_cast<Foreign*>(in)));
    	return;
    }
    assert(0);
}

void Transform::post_member(Member* in, List<Member*>* out)
{
    switch(in->classid())
    {
    case Method::ID: 
    	{
    		List<Method*>* local_out = new List<Method*>;
    		List<Method*>::const_iterator i;
    		post_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Attribute::ID: 
    	{
    		List<Member*>* local_out = new List<Member*>;
    		List<Member*>::const_iterator i;
    		post_attribute(dynamic_cast<Attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Expr* Transform::post_expr(Expr* in)
{
    switch(in->classid())
    {
    case Assignment::ID: return post_assignment(dynamic_cast<Assignment*>(in));
    case Cast::ID: return post_cast(dynamic_cast<Cast*>(in));
    case Unary_op::ID: return post_unary_op(dynamic_cast<Unary_op*>(in));
    case Bin_op::ID: return post_bin_op(dynamic_cast<Bin_op*>(in));
    case Constant::ID: return post_constant(dynamic_cast<Constant*>(in));
    case Instanceof::ID: return post_instanceof(dynamic_cast<Instanceof*>(in));
    case Variable::ID: return post_variable(dynamic_cast<Variable*>(in));
    case Pre_op::ID: return post_pre_op(dynamic_cast<Pre_op*>(in));
    case Method_invocation::ID: return post_method_invocation(dynamic_cast<Method_invocation*>(in));
    case New::ID: return post_new(dynamic_cast<New*>(in));
    case INT::ID: return post_int(dynamic_cast<INT*>(in));
    case REAL::ID: return post_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return post_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return post_nil(dynamic_cast<NIL*>(in));
    case Op_assignment::ID: return post_op_assignment(dynamic_cast<Op_assignment*>(in));
    case List_assignment::ID: return post_list_assignment(dynamic_cast<List_assignment*>(in));
    case Post_op::ID: return post_post_op(dynamic_cast<Post_op*>(in));
    case Array::ID: return post_array(dynamic_cast<Array*>(in));
    case Conditional_expr::ID: return post_conditional_expr(dynamic_cast<Conditional_expr*>(in));
    case Ignore_errors::ID: return post_ignore_errors(dynamic_cast<Ignore_errors*>(in));
    case Foreign::ID: return post_foreign(dynamic_cast<Foreign*>(in));
    }
    assert(0);
}

Variable_name* Transform::post_variable_name(Variable_name* in)
{
    switch(in->classid())
    {
    case VARIABLE_NAME::ID: return post_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
    case Reflection::ID: return post_reflection(dynamic_cast<Reflection*>(in));
    }
    assert(0);
}

void Transform::post_list_element(List_element* in, List<List_element*>* out)
{
    switch(in->classid())
    {
    case Variable::ID: 
    	out->push_back(post_variable(dynamic_cast<Variable*>(in)));
    	return;
    case Nested_list_elements::ID: 
    	{
    		List<List_element*>* local_out = new List<List_element*>;
    		List<List_element*>::const_iterator i;
    		post_nested_list_elements(dynamic_cast<Nested_list_elements*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Class_name* Transform::post_class_name(Class_name* in)
{
    switch(in->classid())
    {
    case CLASS_NAME::ID: return post_class_name(dynamic_cast<CLASS_NAME*>(in));
    case Reflection::ID: return post_reflection(dynamic_cast<Reflection*>(in));
    }
    assert(0);
}

Target* Transform::post_target(Target* in)
{
    switch(in->classid())
    {
    case Assignment::ID: return post_assignment(dynamic_cast<Assignment*>(in));
    case Cast::ID: return post_cast(dynamic_cast<Cast*>(in));
    case Unary_op::ID: return post_unary_op(dynamic_cast<Unary_op*>(in));
    case Bin_op::ID: return post_bin_op(dynamic_cast<Bin_op*>(in));
    case Constant::ID: return post_constant(dynamic_cast<Constant*>(in));
    case Instanceof::ID: return post_instanceof(dynamic_cast<Instanceof*>(in));
    case Variable::ID: return post_variable(dynamic_cast<Variable*>(in));
    case Pre_op::ID: return post_pre_op(dynamic_cast<Pre_op*>(in));
    case Method_invocation::ID: return post_method_invocation(dynamic_cast<Method_invocation*>(in));
    case New::ID: return post_new(dynamic_cast<New*>(in));
    case INT::ID: return post_int(dynamic_cast<INT*>(in));
    case REAL::ID: return post_real(dynamic_cast<REAL*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case BOOL::ID: return post_bool(dynamic_cast<BOOL*>(in));
    case NIL::ID: return post_nil(dynamic_cast<NIL*>(in));
    case Op_assignment::ID: return post_op_assignment(dynamic_cast<Op_assignment*>(in));
    case List_assignment::ID: return post_list_assignment(dynamic_cast<List_assignment*>(in));
    case Post_op::ID: return post_post_op(dynamic_cast<Post_op*>(in));
    case Array::ID: return post_array(dynamic_cast<Array*>(in));
    case Conditional_expr::ID: return post_conditional_expr(dynamic_cast<Conditional_expr*>(in));
    case Ignore_errors::ID: return post_ignore_errors(dynamic_cast<Ignore_errors*>(in));
    case Foreign::ID: return post_foreign(dynamic_cast<Foreign*>(in));
    case CLASS_NAME::ID: return post_class_name(dynamic_cast<CLASS_NAME*>(in));
    }
    assert(0);
}

Method_name* Transform::post_method_name(Method_name* in)
{
    switch(in->classid())
    {
    case METHOD_NAME::ID: return post_method_name(dynamic_cast<METHOD_NAME*>(in));
    case Reflection::ID: return post_reflection(dynamic_cast<Reflection*>(in));
    }
    assert(0);
}

// Invoke the right transform-children (manual dispatching)
// Do not override unless you what you are doing
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
    case If::ID:
    	children_if(dynamic_cast<If*>(in));
    	break;
    case While::ID:
    	children_while(dynamic_cast<While*>(in));
    	break;
    case Do::ID:
    	children_do(dynamic_cast<Do*>(in));
    	break;
    case For::ID:
    	children_for(dynamic_cast<For*>(in));
    	break;
    case Foreach::ID:
    	children_foreach(dynamic_cast<Foreach*>(in));
    	break;
    case Switch::ID:
    	children_switch(dynamic_cast<Switch*>(in));
    	break;
    case Break::ID:
    	children_break(dynamic_cast<Break*>(in));
    	break;
    case Continue::ID:
    	children_continue(dynamic_cast<Continue*>(in));
    	break;
    case Declare::ID:
    	children_declare(dynamic_cast<Declare*>(in));
    	break;
    case Nop::ID:
    	children_nop(dynamic_cast<Nop*>(in));
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
    case Foreign::ID:
    	children_foreign(dynamic_cast<Foreign*>(in));
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

void Transform::children_expr(Expr* in)
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
    case Op_assignment::ID:
    	children_op_assignment(dynamic_cast<Op_assignment*>(in));
    	break;
    case List_assignment::ID:
    	children_list_assignment(dynamic_cast<List_assignment*>(in));
    	break;
    case Post_op::ID:
    	children_post_op(dynamic_cast<Post_op*>(in));
    	break;
    case Array::ID:
    	children_array(dynamic_cast<Array*>(in));
    	break;
    case Conditional_expr::ID:
    	children_conditional_expr(dynamic_cast<Conditional_expr*>(in));
    	break;
    case Ignore_errors::ID:
    	children_ignore_errors(dynamic_cast<Ignore_errors*>(in));
    	break;
    case Foreign::ID:
    	children_foreign(dynamic_cast<Foreign*>(in));
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
    case Reflection::ID:
    	children_reflection(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Transform::children_list_element(List_element* in)
{
    switch(in->classid())
    {
    case Variable::ID:
    	children_variable(dynamic_cast<Variable*>(in));
    	break;
    case Nested_list_elements::ID:
    	children_nested_list_elements(dynamic_cast<Nested_list_elements*>(in));
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
    case Reflection::ID:
    	children_reflection(dynamic_cast<Reflection*>(in));
    	break;
    }
}

void Transform::children_target(Target* in)
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
    case Op_assignment::ID:
    	children_op_assignment(dynamic_cast<Op_assignment*>(in));
    	break;
    case List_assignment::ID:
    	children_list_assignment(dynamic_cast<List_assignment*>(in));
    	break;
    case Post_op::ID:
    	children_post_op(dynamic_cast<Post_op*>(in));
    	break;
    case Array::ID:
    	children_array(dynamic_cast<Array*>(in));
    	break;
    case Conditional_expr::ID:
    	children_conditional_expr(dynamic_cast<Conditional_expr*>(in));
    	break;
    case Ignore_errors::ID:
    	children_ignore_errors(dynamic_cast<Ignore_errors*>(in));
    	break;
    case Foreign::ID:
    	children_foreign(dynamic_cast<Foreign*>(in));
    	break;
    case CLASS_NAME::ID:
    	children_class_name(dynamic_cast<CLASS_NAME*>(in));
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
    case Reflection::ID:
    	children_reflection(dynamic_cast<Reflection*>(in));
    	break;
    }
}
}

