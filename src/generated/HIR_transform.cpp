#include "HIR_transform.h"

namespace HIR{
HIR_transform::~HIR_transform()
{
}

// Invoked before the children are transformed
HIR_php_script* HIR_transform::pre_php_script(HIR_php_script* in)
{
    return in;
}

void HIR_transform::pre_class_def(HIR_class_def* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

HIR_class_mod* HIR_transform::pre_class_mod(HIR_class_mod* in)
{
    return in;
}

void HIR_transform::pre_interface_def(HIR_interface_def* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_method(HIR_method* in, List<HIR_method*>* out)
{
    out->push_back(in);
}

HIR_signature* HIR_transform::pre_signature(HIR_signature* in)
{
    return in;
}

HIR_method_mod* HIR_transform::pre_method_mod(HIR_method_mod* in)
{
    return in;
}

void HIR_transform::pre_formal_parameter(HIR_formal_parameter* in, List<HIR_formal_parameter*>* out)
{
    out->push_back(in);
}

HIR_type* HIR_transform::pre_type(HIR_type* in)
{
    return in;
}

void HIR_transform::pre_attribute(HIR_attribute* in, List<HIR_member*>* out)
{
    out->push_back(in);
}

HIR_attr_mod* HIR_transform::pre_attr_mod(HIR_attr_mod* in)
{
    return in;
}

HIR_name_with_default* HIR_transform::pre_name_with_default(HIR_name_with_default* in)
{
    return in;
}

void HIR_transform::pre_return(HIR_return* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_static_declaration(HIR_static_declaration* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_global(HIR_global* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_try(HIR_try* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_catch(HIR_catch* in, List<HIR_catch*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_throw(HIR_throw* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_eval_expr(HIR_eval_expr* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_branch(HIR_branch* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_goto(HIR_goto* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::pre_label(HIR_label* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

HIR_expr* HIR_transform::pre_assignment(HIR_assignment* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_cast(HIR_cast* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_unary_op(HIR_unary_op* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_bin_op(HIR_bin_op* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_constant(HIR_constant* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_instanceof(HIR_instanceof* in)
{
    return in;
}

HIR_variable* HIR_transform::pre_variable(HIR_variable* in)
{
    return in;
}

HIR_reflection* HIR_transform::pre_reflection(HIR_reflection* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_pre_op(HIR_pre_op* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_array(HIR_array* in)
{
    return in;
}

void HIR_transform::pre_array_elem(HIR_array_elem* in, List<HIR_array_elem*>* out)
{
    out->push_back(in);
}

HIR_expr* HIR_transform::pre_method_invocation(HIR_method_invocation* in)
{
    return in;
}

void HIR_transform::pre_actual_parameter(HIR_actual_parameter* in, List<HIR_actual_parameter*>* out)
{
    out->push_back(in);
}

HIR_expr* HIR_transform::pre_new(HIR_new* in)
{
    return in;
}

Token_class_name* HIR_transform::pre_class_name(Token_class_name* in)
{
    return in;
}

Token_interface_name* HIR_transform::pre_interface_name(Token_interface_name* in)
{
    return in;
}

Token_method_name* HIR_transform::pre_method_name(Token_method_name* in)
{
    return in;
}

Token_variable_name* HIR_transform::pre_variable_name(Token_variable_name* in)
{
    return in;
}

Token_label_name* HIR_transform::pre_label_name(Token_label_name* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_int(Token_int* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_real(Token_real* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_string(Token_string* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_bool(Token_bool* in)
{
    return in;
}

HIR_expr* HIR_transform::pre_null(Token_null* in)
{
    return in;
}

Token_cast* HIR_transform::pre_cast(Token_cast* in)
{
    return in;
}

Token_op* HIR_transform::pre_op(Token_op* in)
{
    return in;
}

Token_constant_name* HIR_transform::pre_constant_name(Token_constant_name* in)
{
    return in;
}

// Invoked after the children have been transformed
HIR_php_script* HIR_transform::post_php_script(HIR_php_script* in)
{
    return in;
}

void HIR_transform::post_class_def(HIR_class_def* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

HIR_class_mod* HIR_transform::post_class_mod(HIR_class_mod* in)
{
    return in;
}

void HIR_transform::post_interface_def(HIR_interface_def* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_method(HIR_method* in, List<HIR_method*>* out)
{
    out->push_back(in);
}

HIR_signature* HIR_transform::post_signature(HIR_signature* in)
{
    return in;
}

HIR_method_mod* HIR_transform::post_method_mod(HIR_method_mod* in)
{
    return in;
}

void HIR_transform::post_formal_parameter(HIR_formal_parameter* in, List<HIR_formal_parameter*>* out)
{
    out->push_back(in);
}

HIR_type* HIR_transform::post_type(HIR_type* in)
{
    return in;
}

void HIR_transform::post_attribute(HIR_attribute* in, List<HIR_member*>* out)
{
    out->push_back(in);
}

HIR_attr_mod* HIR_transform::post_attr_mod(HIR_attr_mod* in)
{
    return in;
}

HIR_name_with_default* HIR_transform::post_name_with_default(HIR_name_with_default* in)
{
    return in;
}

void HIR_transform::post_return(HIR_return* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_static_declaration(HIR_static_declaration* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_global(HIR_global* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_try(HIR_try* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_catch(HIR_catch* in, List<HIR_catch*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_throw(HIR_throw* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_eval_expr(HIR_eval_expr* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_branch(HIR_branch* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_goto(HIR_goto* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

void HIR_transform::post_label(HIR_label* in, List<HIR_statement*>* out)
{
    out->push_back(in);
}

HIR_expr* HIR_transform::post_assignment(HIR_assignment* in)
{
    return in;
}

HIR_expr* HIR_transform::post_cast(HIR_cast* in)
{
    return in;
}

HIR_expr* HIR_transform::post_unary_op(HIR_unary_op* in)
{
    return in;
}

HIR_expr* HIR_transform::post_bin_op(HIR_bin_op* in)
{
    return in;
}

HIR_expr* HIR_transform::post_constant(HIR_constant* in)
{
    return in;
}

HIR_expr* HIR_transform::post_instanceof(HIR_instanceof* in)
{
    return in;
}

HIR_variable* HIR_transform::post_variable(HIR_variable* in)
{
    return in;
}

HIR_reflection* HIR_transform::post_reflection(HIR_reflection* in)
{
    return in;
}

HIR_expr* HIR_transform::post_pre_op(HIR_pre_op* in)
{
    return in;
}

HIR_expr* HIR_transform::post_array(HIR_array* in)
{
    return in;
}

void HIR_transform::post_array_elem(HIR_array_elem* in, List<HIR_array_elem*>* out)
{
    out->push_back(in);
}

HIR_expr* HIR_transform::post_method_invocation(HIR_method_invocation* in)
{
    return in;
}

void HIR_transform::post_actual_parameter(HIR_actual_parameter* in, List<HIR_actual_parameter*>* out)
{
    out->push_back(in);
}

HIR_expr* HIR_transform::post_new(HIR_new* in)
{
    return in;
}

Token_class_name* HIR_transform::post_class_name(Token_class_name* in)
{
    return in;
}

Token_interface_name* HIR_transform::post_interface_name(Token_interface_name* in)
{
    return in;
}

Token_method_name* HIR_transform::post_method_name(Token_method_name* in)
{
    return in;
}

Token_variable_name* HIR_transform::post_variable_name(Token_variable_name* in)
{
    return in;
}

Token_label_name* HIR_transform::post_label_name(Token_label_name* in)
{
    return in;
}

HIR_expr* HIR_transform::post_int(Token_int* in)
{
    return in;
}

HIR_expr* HIR_transform::post_real(Token_real* in)
{
    return in;
}

HIR_expr* HIR_transform::post_string(Token_string* in)
{
    return in;
}

HIR_expr* HIR_transform::post_bool(Token_bool* in)
{
    return in;
}

HIR_expr* HIR_transform::post_null(Token_null* in)
{
    return in;
}

Token_cast* HIR_transform::post_cast(Token_cast* in)
{
    return in;
}

Token_op* HIR_transform::post_op(Token_op* in)
{
    return in;
}

Token_constant_name* HIR_transform::post_constant_name(Token_constant_name* in)
{
    return in;
}

// Transform the children of the node
void HIR_transform::children_php_script(HIR_php_script* in)
{
    in->statements = transform_statement_list(in->statements);
}

void HIR_transform::children_class_def(HIR_class_def* in)
{
    in->class_mod = transform_class_mod(in->class_mod);
    in->class_name = transform_class_name(in->class_name);
    in->extends = transform_class_name(in->extends);
    in->implements = transform_interface_name_list(in->implements);
    in->members = transform_member_list(in->members);
}

void HIR_transform::children_class_mod(HIR_class_mod* in)
{
}

void HIR_transform::children_interface_def(HIR_interface_def* in)
{
    in->interface_name = transform_interface_name(in->interface_name);
    in->extends = transform_interface_name_list(in->extends);
    in->members = transform_member_list(in->members);
}

void HIR_transform::children_method(HIR_method* in)
{
    in->signature = transform_signature(in->signature);
    in->statements = transform_statement_list(in->statements);
}

void HIR_transform::children_signature(HIR_signature* in)
{
    in->method_mod = transform_method_mod(in->method_mod);
    in->method_name = transform_method_name(in->method_name);
    in->formal_parameters = transform_formal_parameter_list(in->formal_parameters);
}

void HIR_transform::children_method_mod(HIR_method_mod* in)
{
}

void HIR_transform::children_formal_parameter(HIR_formal_parameter* in)
{
    in->type = transform_type(in->type);
    in->var = transform_name_with_default(in->var);
}

void HIR_transform::children_type(HIR_type* in)
{
    in->class_name = transform_class_name(in->class_name);
}

void HIR_transform::children_attribute(HIR_attribute* in)
{
    in->attr_mod = transform_attr_mod(in->attr_mod);
    in->var = transform_name_with_default(in->var);
}

void HIR_transform::children_attr_mod(HIR_attr_mod* in)
{
}

void HIR_transform::children_name_with_default(HIR_name_with_default* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_return(HIR_return* in)
{
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_static_declaration(HIR_static_declaration* in)
{
    in->var = transform_name_with_default(in->var);
}

void HIR_transform::children_global(HIR_global* in)
{
    in->variable_name = transform_variable_name(in->variable_name);
}

void HIR_transform::children_try(HIR_try* in)
{
    in->statements = transform_statement_list(in->statements);
    in->catches = transform_catch_list(in->catches);
}

void HIR_transform::children_catch(HIR_catch* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->variable_name = transform_variable_name(in->variable_name);
    in->statements = transform_statement_list(in->statements);
}

void HIR_transform::children_throw(HIR_throw* in)
{
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_eval_expr(HIR_eval_expr* in)
{
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_branch(HIR_branch* in)
{
    in->expr = transform_expr(in->expr);
    in->iftrue = transform_label_name(in->iftrue);
    in->iffalse = transform_label_name(in->iffalse);
}

void HIR_transform::children_goto(HIR_goto* in)
{
    in->label_name = transform_label_name(in->label_name);
}

void HIR_transform::children_label(HIR_label* in)
{
    in->label_name = transform_label_name(in->label_name);
}

void HIR_transform::children_assignment(HIR_assignment* in)
{
    in->variable = transform_variable(in->variable);
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_cast(HIR_cast* in)
{
    in->cast = transform_cast(in->cast);
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_unary_op(HIR_unary_op* in)
{
    in->op = transform_op(in->op);
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_bin_op(HIR_bin_op* in)
{
    in->left = transform_expr(in->left);
    in->op = transform_op(in->op);
    in->right = transform_expr(in->right);
}

void HIR_transform::children_constant(HIR_constant* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->constant_name = transform_constant_name(in->constant_name);
}

void HIR_transform::children_instanceof(HIR_instanceof* in)
{
    in->expr = transform_expr(in->expr);
    in->class_name = transform_class_name(in->class_name);
}

void HIR_transform::children_variable(HIR_variable* in)
{
    in->target = transform_target(in->target);
    in->variable_name = transform_variable_name(in->variable_name);
    in->array_indices = transform_expr_list(in->array_indices);
}

void HIR_transform::children_reflection(HIR_reflection* in)
{
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_pre_op(HIR_pre_op* in)
{
    in->op = transform_op(in->op);
    in->variable = transform_variable(in->variable);
}

void HIR_transform::children_array(HIR_array* in)
{
    in->array_elems = transform_array_elem_list(in->array_elems);
}

void HIR_transform::children_array_elem(HIR_array_elem* in)
{
    in->key = transform_expr(in->key);
    in->val = transform_expr(in->val);
}

void HIR_transform::children_method_invocation(HIR_method_invocation* in)
{
    in->target = transform_target(in->target);
    in->method_name = transform_method_name(in->method_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

void HIR_transform::children_actual_parameter(HIR_actual_parameter* in)
{
    in->expr = transform_expr(in->expr);
}

void HIR_transform::children_new(HIR_new* in)
{
    in->class_name = transform_class_name(in->class_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

// Tokens don't have children, so these methods do nothing by default
void HIR_transform::children_class_name(Token_class_name* in)
{
}

void HIR_transform::children_interface_name(Token_interface_name* in)
{
}

void HIR_transform::children_method_name(Token_method_name* in)
{
}

void HIR_transform::children_variable_name(Token_variable_name* in)
{
}

void HIR_transform::children_label_name(Token_label_name* in)
{
}

void HIR_transform::children_int(Token_int* in)
{
}

void HIR_transform::children_real(Token_real* in)
{
}

void HIR_transform::children_string(Token_string* in)
{
}

void HIR_transform::children_bool(Token_bool* in)
{
}

void HIR_transform::children_null(Token_null* in)
{
}

void HIR_transform::children_cast(Token_cast* in)
{
}

void HIR_transform::children_op(Token_op* in)
{
}

void HIR_transform::children_constant_name(Token_constant_name* in)
{
}

// Call the pre-transform, transform-children post-transform methods in order
// Do not override unless you know what you are doing
List<HIR_statement*>* HIR_transform::transform_statement_list(List<HIR_statement*>* in)
{
    List<HIR_statement*>::const_iterator i;
    List<HIR_statement*>* out = new List<HIR_statement*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_statement(*i));
    }
    
    return out;
}

List<HIR_statement*>* HIR_transform::transform_statement(HIR_statement* in)
{
    List<HIR_statement*>::const_iterator i;
    List<HIR_statement*>* out1 = new List<HIR_statement*>;
    List<HIR_statement*>* out2 = new List<HIR_statement*>;
    
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

HIR_class_mod* HIR_transform::transform_class_mod(HIR_class_mod* in)
{
    if(in == NULL) return NULL;
    
    HIR_class_mod* out;
    
    out = pre_class_mod(in);
    if(out != NULL)
    {
    	children_class_mod(out);
    	out = post_class_mod(out);
    }
    
    return out;
}

Token_class_name* HIR_transform::transform_class_name(Token_class_name* in)
{
    if(in == NULL) return NULL;
    
    Token_class_name* out;
    
    out = pre_class_name(in);
    if(out != NULL)
    {
    	children_class_name(out);
    	out = post_class_name(out);
    }
    
    return out;
}

List<Token_interface_name*>* HIR_transform::transform_interface_name_list(List<Token_interface_name*>* in)
{
    List<Token_interface_name*>::const_iterator i;
    List<Token_interface_name*>* out = new List<Token_interface_name*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_interface_name(*i));
    }
    
    return out;
}

List<HIR_member*>* HIR_transform::transform_member_list(List<HIR_member*>* in)
{
    List<HIR_member*>::const_iterator i;
    List<HIR_member*>* out = new List<HIR_member*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_member(*i));
    }
    
    return out;
}

List<HIR_member*>* HIR_transform::transform_member(HIR_member* in)
{
    List<HIR_member*>::const_iterator i;
    List<HIR_member*>* out1 = new List<HIR_member*>;
    List<HIR_member*>* out2 = new List<HIR_member*>;
    
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

Token_interface_name* HIR_transform::transform_interface_name(Token_interface_name* in)
{
    if(in == NULL) return NULL;
    
    Token_interface_name* out;
    
    out = pre_interface_name(in);
    if(out != NULL)
    {
    	children_interface_name(out);
    	out = post_interface_name(out);
    }
    
    return out;
}

HIR_signature* HIR_transform::transform_signature(HIR_signature* in)
{
    if(in == NULL) return NULL;
    
    HIR_signature* out;
    
    out = pre_signature(in);
    if(out != NULL)
    {
    	children_signature(out);
    	out = post_signature(out);
    }
    
    return out;
}

HIR_method_mod* HIR_transform::transform_method_mod(HIR_method_mod* in)
{
    if(in == NULL) return NULL;
    
    HIR_method_mod* out;
    
    out = pre_method_mod(in);
    if(out != NULL)
    {
    	children_method_mod(out);
    	out = post_method_mod(out);
    }
    
    return out;
}

Token_method_name* HIR_transform::transform_method_name(Token_method_name* in)
{
    if(in == NULL) return NULL;
    
    Token_method_name* out;
    
    out = pre_method_name(in);
    if(out != NULL)
    {
    	children_method_name(out);
    	out = post_method_name(out);
    }
    
    return out;
}

List<HIR_formal_parameter*>* HIR_transform::transform_formal_parameter_list(List<HIR_formal_parameter*>* in)
{
    List<HIR_formal_parameter*>::const_iterator i;
    List<HIR_formal_parameter*>* out = new List<HIR_formal_parameter*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_formal_parameter(*i));
    }
    
    return out;
}

List<HIR_formal_parameter*>* HIR_transform::transform_formal_parameter(HIR_formal_parameter* in)
{
    List<HIR_formal_parameter*>::const_iterator i;
    List<HIR_formal_parameter*>* out1 = new List<HIR_formal_parameter*>;
    List<HIR_formal_parameter*>* out2 = new List<HIR_formal_parameter*>;
    
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

HIR_type* HIR_transform::transform_type(HIR_type* in)
{
    if(in == NULL) return NULL;
    
    HIR_type* out;
    
    out = pre_type(in);
    if(out != NULL)
    {
    	children_type(out);
    	out = post_type(out);
    }
    
    return out;
}

HIR_name_with_default* HIR_transform::transform_name_with_default(HIR_name_with_default* in)
{
    if(in == NULL) return NULL;
    
    HIR_name_with_default* out;
    
    out = pre_name_with_default(in);
    if(out != NULL)
    {
    	children_name_with_default(out);
    	out = post_name_with_default(out);
    }
    
    return out;
}

HIR_attr_mod* HIR_transform::transform_attr_mod(HIR_attr_mod* in)
{
    if(in == NULL) return NULL;
    
    HIR_attr_mod* out;
    
    out = pre_attr_mod(in);
    if(out != NULL)
    {
    	children_attr_mod(out);
    	out = post_attr_mod(out);
    }
    
    return out;
}

Token_variable_name* HIR_transform::transform_variable_name(Token_variable_name* in)
{
    if(in == NULL) return NULL;
    
    Token_variable_name* out;
    
    out = pre_variable_name(in);
    if(out != NULL)
    {
    	children_variable_name(out);
    	out = post_variable_name(out);
    }
    
    return out;
}

HIR_expr* HIR_transform::transform_expr(HIR_expr* in)
{
    if(in == NULL) return NULL;
    
    HIR_expr* out;
    
    out = pre_expr(in);
    if(out != NULL)
    {
    	children_expr(out);
    	out = post_expr(out);
    }
    
    return out;
}

HIR_variable_name* HIR_transform::transform_variable_name(HIR_variable_name* in)
{
    if(in == NULL) return NULL;
    
    HIR_variable_name* out;
    
    out = pre_variable_name(in);
    if(out != NULL)
    {
    	children_variable_name(out);
    	out = post_variable_name(out);
    }
    
    return out;
}

List<HIR_catch*>* HIR_transform::transform_catch_list(List<HIR_catch*>* in)
{
    List<HIR_catch*>::const_iterator i;
    List<HIR_catch*>* out = new List<HIR_catch*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_catch(*i));
    }
    
    return out;
}

List<HIR_catch*>* HIR_transform::transform_catch(HIR_catch* in)
{
    List<HIR_catch*>::const_iterator i;
    List<HIR_catch*>* out1 = new List<HIR_catch*>;
    List<HIR_catch*>* out2 = new List<HIR_catch*>;
    
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

Token_label_name* HIR_transform::transform_label_name(Token_label_name* in)
{
    if(in == NULL) return NULL;
    
    Token_label_name* out;
    
    out = pre_label_name(in);
    if(out != NULL)
    {
    	children_label_name(out);
    	out = post_label_name(out);
    }
    
    return out;
}

HIR_variable* HIR_transform::transform_variable(HIR_variable* in)
{
    if(in == NULL) return NULL;
    
    HIR_variable* out;
    
    out = pre_variable(in);
    if(out != NULL)
    {
    	children_variable(out);
    	out = post_variable(out);
    }
    
    return out;
}

Token_cast* HIR_transform::transform_cast(Token_cast* in)
{
    if(in == NULL) return NULL;
    
    Token_cast* out;
    
    out = pre_cast(in);
    if(out != NULL)
    {
    	children_cast(out);
    	out = post_cast(out);
    }
    
    return out;
}

Token_op* HIR_transform::transform_op(Token_op* in)
{
    if(in == NULL) return NULL;
    
    Token_op* out;
    
    out = pre_op(in);
    if(out != NULL)
    {
    	children_op(out);
    	out = post_op(out);
    }
    
    return out;
}

Token_constant_name* HIR_transform::transform_constant_name(Token_constant_name* in)
{
    if(in == NULL) return NULL;
    
    Token_constant_name* out;
    
    out = pre_constant_name(in);
    if(out != NULL)
    {
    	children_constant_name(out);
    	out = post_constant_name(out);
    }
    
    return out;
}

HIR_class_name* HIR_transform::transform_class_name(HIR_class_name* in)
{
    if(in == NULL) return NULL;
    
    HIR_class_name* out;
    
    out = pre_class_name(in);
    if(out != NULL)
    {
    	children_class_name(out);
    	out = post_class_name(out);
    }
    
    return out;
}

HIR_target* HIR_transform::transform_target(HIR_target* in)
{
    if(in == NULL) return NULL;
    
    HIR_target* out;
    
    out = pre_target(in);
    if(out != NULL)
    {
    	children_target(out);
    	out = post_target(out);
    }
    
    return out;
}

List<HIR_expr*>* HIR_transform::transform_expr_list(List<HIR_expr*>* in)
{
    List<HIR_expr*>::const_iterator i;
    List<HIR_expr*>* out = new List<HIR_expr*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_expr(*i));
    }
    
    return out;
}

List<HIR_array_elem*>* HIR_transform::transform_array_elem_list(List<HIR_array_elem*>* in)
{
    List<HIR_array_elem*>::const_iterator i;
    List<HIR_array_elem*>* out = new List<HIR_array_elem*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_array_elem(*i));
    }
    
    return out;
}

List<HIR_array_elem*>* HIR_transform::transform_array_elem(HIR_array_elem* in)
{
    List<HIR_array_elem*>::const_iterator i;
    List<HIR_array_elem*>* out1 = new List<HIR_array_elem*>;
    List<HIR_array_elem*>* out2 = new List<HIR_array_elem*>;
    
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

HIR_method_name* HIR_transform::transform_method_name(HIR_method_name* in)
{
    if(in == NULL) return NULL;
    
    HIR_method_name* out;
    
    out = pre_method_name(in);
    if(out != NULL)
    {
    	children_method_name(out);
    	out = post_method_name(out);
    }
    
    return out;
}

List<HIR_actual_parameter*>* HIR_transform::transform_actual_parameter_list(List<HIR_actual_parameter*>* in)
{
    List<HIR_actual_parameter*>::const_iterator i;
    List<HIR_actual_parameter*>* out = new List<HIR_actual_parameter*>;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_actual_parameter(*i));
    }
    
    return out;
}

List<HIR_actual_parameter*>* HIR_transform::transform_actual_parameter(HIR_actual_parameter* in)
{
    List<HIR_actual_parameter*>::const_iterator i;
    List<HIR_actual_parameter*>* out1 = new List<HIR_actual_parameter*>;
    List<HIR_actual_parameter*>* out2 = new List<HIR_actual_parameter*>;
    
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

HIR_php_script* HIR_transform::transform_php_script(HIR_php_script* in)
{
    if(in == NULL) return NULL;
    
    HIR_php_script* out;
    
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
void HIR_transform::pre_statement(HIR_statement* in, List<HIR_statement*>* out)
{
    switch(in->classid())
    {
    case HIR_class_def::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_class_def(dynamic_cast<HIR_class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_interface_def::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_interface_def(dynamic_cast<HIR_interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_method::ID: 
    	{
    		List<HIR_method*>* local_out = new List<HIR_method*>;
    		List<HIR_method*>::const_iterator i;
    		pre_method(dynamic_cast<HIR_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_return::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_return(dynamic_cast<HIR_return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_static_declaration::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_static_declaration(dynamic_cast<HIR_static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_global::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_global(dynamic_cast<HIR_global*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_try::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_try(dynamic_cast<HIR_try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_throw::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_throw(dynamic_cast<HIR_throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_eval_expr::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_eval_expr(dynamic_cast<HIR_eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_label::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_label(dynamic_cast<HIR_label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_goto::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_goto(dynamic_cast<HIR_goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_branch::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		pre_branch(dynamic_cast<HIR_branch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

void HIR_transform::pre_member(HIR_member* in, List<HIR_member*>* out)
{
    switch(in->classid())
    {
    case HIR_method::ID: 
    	{
    		List<HIR_method*>* local_out = new List<HIR_method*>;
    		List<HIR_method*>::const_iterator i;
    		pre_method(dynamic_cast<HIR_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_attribute::ID: 
    	{
    		List<HIR_member*>* local_out = new List<HIR_member*>;
    		List<HIR_member*>::const_iterator i;
    		pre_attribute(dynamic_cast<HIR_attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

HIR_expr* HIR_transform::pre_expr(HIR_expr* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID: return pre_assignment(dynamic_cast<HIR_assignment*>(in));
    case HIR_cast::ID: return pre_cast(dynamic_cast<HIR_cast*>(in));
    case HIR_unary_op::ID: return pre_unary_op(dynamic_cast<HIR_unary_op*>(in));
    case HIR_bin_op::ID: return pre_bin_op(dynamic_cast<HIR_bin_op*>(in));
    case HIR_constant::ID: return pre_constant(dynamic_cast<HIR_constant*>(in));
    case HIR_instanceof::ID: return pre_instanceof(dynamic_cast<HIR_instanceof*>(in));
    case HIR_variable::ID: return pre_variable(dynamic_cast<HIR_variable*>(in));
    case HIR_pre_op::ID: return pre_pre_op(dynamic_cast<HIR_pre_op*>(in));
    case HIR_array::ID: return pre_array(dynamic_cast<HIR_array*>(in));
    case HIR_method_invocation::ID: return pre_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    case HIR_new::ID: return pre_new(dynamic_cast<HIR_new*>(in));
    case Token_int::ID: return pre_int(dynamic_cast<Token_int*>(in));
    case Token_real::ID: return pre_real(dynamic_cast<Token_real*>(in));
    case Token_string::ID: return pre_string(dynamic_cast<Token_string*>(in));
    case Token_bool::ID: return pre_bool(dynamic_cast<Token_bool*>(in));
    case Token_null::ID: return pre_null(dynamic_cast<Token_null*>(in));
    }
    assert(0);
}

HIR_variable_name* HIR_transform::pre_variable_name(HIR_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID: return pre_variable_name(dynamic_cast<Token_variable_name*>(in));
    case HIR_reflection::ID: return pre_reflection(dynamic_cast<HIR_reflection*>(in));
    }
    assert(0);
}

HIR_class_name* HIR_transform::pre_class_name(HIR_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID: return pre_class_name(dynamic_cast<Token_class_name*>(in));
    case HIR_reflection::ID: return pre_reflection(dynamic_cast<HIR_reflection*>(in));
    }
    assert(0);
}

HIR_target* HIR_transform::pre_target(HIR_target* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID: return pre_assignment(dynamic_cast<HIR_assignment*>(in));
    case HIR_cast::ID: return pre_cast(dynamic_cast<HIR_cast*>(in));
    case HIR_unary_op::ID: return pre_unary_op(dynamic_cast<HIR_unary_op*>(in));
    case HIR_bin_op::ID: return pre_bin_op(dynamic_cast<HIR_bin_op*>(in));
    case HIR_constant::ID: return pre_constant(dynamic_cast<HIR_constant*>(in));
    case HIR_instanceof::ID: return pre_instanceof(dynamic_cast<HIR_instanceof*>(in));
    case HIR_variable::ID: return pre_variable(dynamic_cast<HIR_variable*>(in));
    case HIR_pre_op::ID: return pre_pre_op(dynamic_cast<HIR_pre_op*>(in));
    case HIR_array::ID: return pre_array(dynamic_cast<HIR_array*>(in));
    case HIR_method_invocation::ID: return pre_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    case HIR_new::ID: return pre_new(dynamic_cast<HIR_new*>(in));
    case Token_int::ID: return pre_int(dynamic_cast<Token_int*>(in));
    case Token_real::ID: return pre_real(dynamic_cast<Token_real*>(in));
    case Token_string::ID: return pre_string(dynamic_cast<Token_string*>(in));
    case Token_bool::ID: return pre_bool(dynamic_cast<Token_bool*>(in));
    case Token_null::ID: return pre_null(dynamic_cast<Token_null*>(in));
    case Token_class_name::ID: return pre_class_name(dynamic_cast<Token_class_name*>(in));
    }
    assert(0);
}

HIR_method_name* HIR_transform::pre_method_name(HIR_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID: return pre_method_name(dynamic_cast<Token_method_name*>(in));
    case HIR_reflection::ID: return pre_reflection(dynamic_cast<HIR_reflection*>(in));
    }
    assert(0);
}

// Invoke the right post-transform (manual dispatching)
// Do not override unless you know what you are doing
void HIR_transform::post_statement(HIR_statement* in, List<HIR_statement*>* out)
{
    switch(in->classid())
    {
    case HIR_class_def::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_class_def(dynamic_cast<HIR_class_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_interface_def::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_interface_def(dynamic_cast<HIR_interface_def*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_method::ID: 
    	{
    		List<HIR_method*>* local_out = new List<HIR_method*>;
    		List<HIR_method*>::const_iterator i;
    		post_method(dynamic_cast<HIR_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_return::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_return(dynamic_cast<HIR_return*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_static_declaration::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_static_declaration(dynamic_cast<HIR_static_declaration*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_global::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_global(dynamic_cast<HIR_global*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_try::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_try(dynamic_cast<HIR_try*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_throw::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_throw(dynamic_cast<HIR_throw*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_eval_expr::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_eval_expr(dynamic_cast<HIR_eval_expr*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_label::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_label(dynamic_cast<HIR_label*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_goto::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_goto(dynamic_cast<HIR_goto*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_branch::ID: 
    	{
    		List<HIR_statement*>* local_out = new List<HIR_statement*>;
    		List<HIR_statement*>::const_iterator i;
    		post_branch(dynamic_cast<HIR_branch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

void HIR_transform::post_member(HIR_member* in, List<HIR_member*>* out)
{
    switch(in->classid())
    {
    case HIR_method::ID: 
    	{
    		List<HIR_method*>* local_out = new List<HIR_method*>;
    		List<HIR_method*>::const_iterator i;
    		post_method(dynamic_cast<HIR_method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case HIR_attribute::ID: 
    	{
    		List<HIR_member*>* local_out = new List<HIR_member*>;
    		List<HIR_member*>::const_iterator i;
    		post_attribute(dynamic_cast<HIR_attribute*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

HIR_expr* HIR_transform::post_expr(HIR_expr* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID: return post_assignment(dynamic_cast<HIR_assignment*>(in));
    case HIR_cast::ID: return post_cast(dynamic_cast<HIR_cast*>(in));
    case HIR_unary_op::ID: return post_unary_op(dynamic_cast<HIR_unary_op*>(in));
    case HIR_bin_op::ID: return post_bin_op(dynamic_cast<HIR_bin_op*>(in));
    case HIR_constant::ID: return post_constant(dynamic_cast<HIR_constant*>(in));
    case HIR_instanceof::ID: return post_instanceof(dynamic_cast<HIR_instanceof*>(in));
    case HIR_variable::ID: return post_variable(dynamic_cast<HIR_variable*>(in));
    case HIR_pre_op::ID: return post_pre_op(dynamic_cast<HIR_pre_op*>(in));
    case HIR_array::ID: return post_array(dynamic_cast<HIR_array*>(in));
    case HIR_method_invocation::ID: return post_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    case HIR_new::ID: return post_new(dynamic_cast<HIR_new*>(in));
    case Token_int::ID: return post_int(dynamic_cast<Token_int*>(in));
    case Token_real::ID: return post_real(dynamic_cast<Token_real*>(in));
    case Token_string::ID: return post_string(dynamic_cast<Token_string*>(in));
    case Token_bool::ID: return post_bool(dynamic_cast<Token_bool*>(in));
    case Token_null::ID: return post_null(dynamic_cast<Token_null*>(in));
    }
    assert(0);
}

HIR_variable_name* HIR_transform::post_variable_name(HIR_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID: return post_variable_name(dynamic_cast<Token_variable_name*>(in));
    case HIR_reflection::ID: return post_reflection(dynamic_cast<HIR_reflection*>(in));
    }
    assert(0);
}

HIR_class_name* HIR_transform::post_class_name(HIR_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID: return post_class_name(dynamic_cast<Token_class_name*>(in));
    case HIR_reflection::ID: return post_reflection(dynamic_cast<HIR_reflection*>(in));
    }
    assert(0);
}

HIR_target* HIR_transform::post_target(HIR_target* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID: return post_assignment(dynamic_cast<HIR_assignment*>(in));
    case HIR_cast::ID: return post_cast(dynamic_cast<HIR_cast*>(in));
    case HIR_unary_op::ID: return post_unary_op(dynamic_cast<HIR_unary_op*>(in));
    case HIR_bin_op::ID: return post_bin_op(dynamic_cast<HIR_bin_op*>(in));
    case HIR_constant::ID: return post_constant(dynamic_cast<HIR_constant*>(in));
    case HIR_instanceof::ID: return post_instanceof(dynamic_cast<HIR_instanceof*>(in));
    case HIR_variable::ID: return post_variable(dynamic_cast<HIR_variable*>(in));
    case HIR_pre_op::ID: return post_pre_op(dynamic_cast<HIR_pre_op*>(in));
    case HIR_array::ID: return post_array(dynamic_cast<HIR_array*>(in));
    case HIR_method_invocation::ID: return post_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    case HIR_new::ID: return post_new(dynamic_cast<HIR_new*>(in));
    case Token_int::ID: return post_int(dynamic_cast<Token_int*>(in));
    case Token_real::ID: return post_real(dynamic_cast<Token_real*>(in));
    case Token_string::ID: return post_string(dynamic_cast<Token_string*>(in));
    case Token_bool::ID: return post_bool(dynamic_cast<Token_bool*>(in));
    case Token_null::ID: return post_null(dynamic_cast<Token_null*>(in));
    case Token_class_name::ID: return post_class_name(dynamic_cast<Token_class_name*>(in));
    }
    assert(0);
}

HIR_method_name* HIR_transform::post_method_name(HIR_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID: return post_method_name(dynamic_cast<Token_method_name*>(in));
    case HIR_reflection::ID: return post_reflection(dynamic_cast<HIR_reflection*>(in));
    }
    assert(0);
}

// Invoke the right transform-children (manual dispatching)
// Do not override unless you what you are doing
void HIR_transform::children_statement(HIR_statement* in)
{
    switch(in->classid())
    {
    case HIR_class_def::ID:
    	children_class_def(dynamic_cast<HIR_class_def*>(in));
    	break;
    case HIR_interface_def::ID:
    	children_interface_def(dynamic_cast<HIR_interface_def*>(in));
    	break;
    case HIR_method::ID:
    	children_method(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_return::ID:
    	children_return(dynamic_cast<HIR_return*>(in));
    	break;
    case HIR_static_declaration::ID:
    	children_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
    	break;
    case HIR_global::ID:
    	children_global(dynamic_cast<HIR_global*>(in));
    	break;
    case HIR_try::ID:
    	children_try(dynamic_cast<HIR_try*>(in));
    	break;
    case HIR_throw::ID:
    	children_throw(dynamic_cast<HIR_throw*>(in));
    	break;
    case HIR_eval_expr::ID:
    	children_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
    	break;
    case HIR_label::ID:
    	children_label(dynamic_cast<HIR_label*>(in));
    	break;
    case HIR_goto::ID:
    	children_goto(dynamic_cast<HIR_goto*>(in));
    	break;
    case HIR_branch::ID:
    	children_branch(dynamic_cast<HIR_branch*>(in));
    	break;
    }
}

void HIR_transform::children_member(HIR_member* in)
{
    switch(in->classid())
    {
    case HIR_method::ID:
    	children_method(dynamic_cast<HIR_method*>(in));
    	break;
    case HIR_attribute::ID:
    	children_attribute(dynamic_cast<HIR_attribute*>(in));
    	break;
    }
}

void HIR_transform::children_expr(HIR_expr* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	children_assignment(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	children_cast(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	children_unary_op(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	children_bin_op(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	children_constant(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	children_instanceof(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	children_variable(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	children_pre_op(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	children_array(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	children_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	children_new(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    }
}

void HIR_transform::children_variable_name(HIR_variable_name* in)
{
    switch(in->classid())
    {
    case Token_variable_name::ID:
    	children_variable_name(dynamic_cast<Token_variable_name*>(in));
    	break;
    case HIR_reflection::ID:
    	children_reflection(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_transform::children_class_name(HIR_class_name* in)
{
    switch(in->classid())
    {
    case Token_class_name::ID:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    case HIR_reflection::ID:
    	children_reflection(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}

void HIR_transform::children_target(HIR_target* in)
{
    switch(in->classid())
    {
    case HIR_assignment::ID:
    	children_assignment(dynamic_cast<HIR_assignment*>(in));
    	break;
    case HIR_cast::ID:
    	children_cast(dynamic_cast<HIR_cast*>(in));
    	break;
    case HIR_unary_op::ID:
    	children_unary_op(dynamic_cast<HIR_unary_op*>(in));
    	break;
    case HIR_bin_op::ID:
    	children_bin_op(dynamic_cast<HIR_bin_op*>(in));
    	break;
    case HIR_constant::ID:
    	children_constant(dynamic_cast<HIR_constant*>(in));
    	break;
    case HIR_instanceof::ID:
    	children_instanceof(dynamic_cast<HIR_instanceof*>(in));
    	break;
    case HIR_variable::ID:
    	children_variable(dynamic_cast<HIR_variable*>(in));
    	break;
    case HIR_pre_op::ID:
    	children_pre_op(dynamic_cast<HIR_pre_op*>(in));
    	break;
    case HIR_array::ID:
    	children_array(dynamic_cast<HIR_array*>(in));
    	break;
    case HIR_method_invocation::ID:
    	children_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
    	break;
    case HIR_new::ID:
    	children_new(dynamic_cast<HIR_new*>(in));
    	break;
    case Token_int::ID:
    	children_int(dynamic_cast<Token_int*>(in));
    	break;
    case Token_real::ID:
    	children_real(dynamic_cast<Token_real*>(in));
    	break;
    case Token_string::ID:
    	children_string(dynamic_cast<Token_string*>(in));
    	break;
    case Token_bool::ID:
    	children_bool(dynamic_cast<Token_bool*>(in));
    	break;
    case Token_null::ID:
    	children_null(dynamic_cast<Token_null*>(in));
    	break;
    case Token_class_name::ID:
    	children_class_name(dynamic_cast<Token_class_name*>(in));
    	break;
    }
}

void HIR_transform::children_method_name(HIR_method_name* in)
{
    switch(in->classid())
    {
    case Token_method_name::ID:
    	children_method_name(dynamic_cast<Token_method_name*>(in));
    	break;
    case HIR_reflection::ID:
    	children_reflection(dynamic_cast<HIR_reflection*>(in));
    	break;
    }
}
}

