#include "MICG_transform.h"

namespace MICG{
Transform::~Transform()
{
}

/* Invoked before the children are transformed */
Template* Transform::pre_template(Template* in)
{
    return in;
}

Signature* Transform::pre_signature(Signature* in)
{
    return in;
}

void Transform::pre_formal_parameter(Formal_parameter* in, Formal_parameter_list* out)
{
    out->push_back(in);
}

void Transform::pre_rule(Rule* in, Rule_list* out)
{
    out->push_back(in);
}

Lookup* Transform::pre_lookup(Lookup* in)
{
    return in;
}

Expr* Transform::pre_equals(Equals* in)
{
    return in;
}

Body* Transform::pre_body(Body* in)
{
    return in;
}

void Transform::pre_macro_call(Macro_call* in, Body_part_list* out)
{
    out->push_back(in);
}

PATTERN_NAME* Transform::pre_pattern_name(PATTERN_NAME* in)
{
    return in;
}

TYPE* Transform::pre_type(TYPE* in)
{
    return in;
}

ATTR_NAME* Transform::pre_attr_name(ATTR_NAME* in)
{
    return in;
}

PARAM_NAME* Transform::pre_param_name(PARAM_NAME* in)
{
    return in;
}

STRING* Transform::pre_string(STRING* in)
{
    return in;
}

void Transform::pre_c_code(C_CODE* in, Body_part_list* out)
{
    out->push_back(in);
}

/* Invoked after the children have been transformed */
Template* Transform::post_template(Template* in)
{
    return in;
}

Signature* Transform::post_signature(Signature* in)
{
    return in;
}

void Transform::post_formal_parameter(Formal_parameter* in, Formal_parameter_list* out)
{
    out->push_back(in);
}

void Transform::post_rule(Rule* in, Rule_list* out)
{
    out->push_back(in);
}

Lookup* Transform::post_lookup(Lookup* in)
{
    return in;
}

Expr* Transform::post_equals(Equals* in)
{
    return in;
}

Body* Transform::post_body(Body* in)
{
    return in;
}

void Transform::post_macro_call(Macro_call* in, Body_part_list* out)
{
    out->push_back(in);
}

PATTERN_NAME* Transform::post_pattern_name(PATTERN_NAME* in)
{
    return in;
}

TYPE* Transform::post_type(TYPE* in)
{
    return in;
}

ATTR_NAME* Transform::post_attr_name(ATTR_NAME* in)
{
    return in;
}

PARAM_NAME* Transform::post_param_name(PARAM_NAME* in)
{
    return in;
}

STRING* Transform::post_string(STRING* in)
{
    return in;
}

void Transform::post_c_code(C_CODE* in, Body_part_list* out)
{
    out->push_back(in);
}

/* Transform the children of the node */
void Transform::children_template(Template* in)
{
    in->signature = transform_signature(in->signature);
    in->rules = transform_rule_list(in->rules);
    in->body = transform_body(in->body);
}

void Transform::children_signature(Signature* in)
{
    in->pattern_name = transform_pattern_name(in->pattern_name);
    in->formal_parameters = transform_formal_parameter_list(in->formal_parameters);
}

void Transform::children_formal_parameter(Formal_parameter* in)
{
    in->type = transform_type(in->type);
    in->param_name = transform_param_name(in->param_name);
}

void Transform::children_rule(Rule* in)
{
    in->expr = transform_expr(in->expr);
}

void Transform::children_lookup(Lookup* in)
{
    in->param_name = transform_param_name(in->param_name);
    in->attr_name = transform_attr_name(in->attr_name);
}

void Transform::children_equals(Equals* in)
{
    in->left = transform_expr(in->left);
    in->right = transform_expr(in->right);
}

void Transform::children_body(Body* in)
{
    in->body_parts = transform_body_part_list(in->body_parts);
}

void Transform::children_macro_call(Macro_call* in)
{
    in->pattern_name = transform_pattern_name(in->pattern_name);
    in->actual_parameters = transform_actual_parameter_list(in->actual_parameters);
}

/* Tokens don't have children, so these methods do nothing by default */
void Transform::children_pattern_name(PATTERN_NAME* in)
{
}

void Transform::children_type(TYPE* in)
{
}

void Transform::children_attr_name(ATTR_NAME* in)
{
}

void Transform::children_param_name(PARAM_NAME* in)
{
}

void Transform::children_string(STRING* in)
{
}

void Transform::children_c_code(C_CODE* in)
{
}

/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
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

Rule_list* Transform::transform_rule_list(Rule_list* in)
{
    Rule_list::const_iterator i;
    Rule_list* out = new Rule_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_rule(*i));
    }
    
    return out;
}

Rule_list* Transform::transform_rule(Rule* in)
{
    Rule_list::const_iterator i;
    Rule_list* out1 = new Rule_list;
    Rule_list* out2 = new Rule_list;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_rule(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_rule(*i);
    		post_rule(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

Body* Transform::transform_body(Body* in)
{
    if(in == NULL) return NULL;
    
    Body* out;
    
    out = pre_body(in);
    if(out != NULL)
    {
    	children_body(out);
    	out = post_body(out);
    }
    
    return out;
}

PATTERN_NAME* Transform::transform_pattern_name(PATTERN_NAME* in)
{
    if(in == NULL) return NULL;
    
    PATTERN_NAME* out;
    
    out = pre_pattern_name(in);
    if(out != NULL)
    {
    	children_pattern_name(out);
    	out = post_pattern_name(out);
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

TYPE* Transform::transform_type(TYPE* in)
{
    if(in == NULL) return NULL;
    
    TYPE* out;
    
    out = pre_type(in);
    if(out != NULL)
    {
    	children_type(out);
    	out = post_type(out);
    }
    
    return out;
}

PARAM_NAME* Transform::transform_param_name(PARAM_NAME* in)
{
    if(in == NULL) return NULL;
    
    PARAM_NAME* out;
    
    out = pre_param_name(in);
    if(out != NULL)
    {
    	children_param_name(out);
    	out = post_param_name(out);
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

ATTR_NAME* Transform::transform_attr_name(ATTR_NAME* in)
{
    if(in == NULL) return NULL;
    
    ATTR_NAME* out;
    
    out = pre_attr_name(in);
    if(out != NULL)
    {
    	children_attr_name(out);
    	out = post_attr_name(out);
    }
    
    return out;
}

Body_part_list* Transform::transform_body_part_list(Body_part_list* in)
{
    Body_part_list::const_iterator i;
    Body_part_list* out = new Body_part_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_body_part(*i));
    }
    
    return out;
}

Body_part_list* Transform::transform_body_part(Body_part* in)
{
    Body_part_list::const_iterator i;
    Body_part_list* out1 = new Body_part_list;
    Body_part_list* out2 = new Body_part_list;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_body_part(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_body_part(*i);
    		post_body_part(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
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

Template* Transform::transform_template(Template* in)
{
    if(in == NULL) return NULL;
    
    Template* out;
    
    out = pre_template(in);
    if(out != NULL)
    {
    	children_template(out);
    	out = post_template(out);
    }
    
    return out;
}

/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
Expr* Transform::pre_expr(Expr* in)
{
    switch(in->classid())
    {
    case Equals::ID: return pre_equals(dynamic_cast<Equals*>(in));
    case Lookup::ID: return pre_lookup(dynamic_cast<Lookup*>(in));
    case PARAM_NAME::ID: return pre_param_name(dynamic_cast<PARAM_NAME*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    }
    assert(0);
}

void Transform::pre_body_part(Body_part* in, Body_part_list* out)
{
    switch(in->classid())
    {
    case C_CODE::ID: 
    	{
    		Body_part_list* local_out = new Body_part_list;
    		Body_part_list::const_iterator i;
    		pre_c_code(dynamic_cast<C_CODE*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Macro_call::ID: 
    	{
    		Body_part_list* local_out = new Body_part_list;
    		Body_part_list::const_iterator i;
    		pre_macro_call(dynamic_cast<Macro_call*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Lookup::ID: 
    	out->push_back(pre_lookup(dynamic_cast<Lookup*>(in)));
    	return;
    case PARAM_NAME::ID: 
    	out->push_back(pre_param_name(dynamic_cast<PARAM_NAME*>(in)));
    	return;
    }
    assert(0);
}

void Transform::pre_actual_parameter(Actual_parameter* in, Actual_parameter_list* out)
{
    switch(in->classid())
    {
    case STRING::ID: 
    	out->push_back(pre_string(dynamic_cast<STRING*>(in)));
    	return;
    case PARAM_NAME::ID: 
    	out->push_back(pre_param_name(dynamic_cast<PARAM_NAME*>(in)));
    	return;
    }
    assert(0);
}

/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
Expr* Transform::post_expr(Expr* in)
{
    switch(in->classid())
    {
    case Equals::ID: return post_equals(dynamic_cast<Equals*>(in));
    case Lookup::ID: return post_lookup(dynamic_cast<Lookup*>(in));
    case PARAM_NAME::ID: return post_param_name(dynamic_cast<PARAM_NAME*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    }
    assert(0);
}

void Transform::post_body_part(Body_part* in, Body_part_list* out)
{
    switch(in->classid())
    {
    case C_CODE::ID: 
    	{
    		Body_part_list* local_out = new Body_part_list;
    		Body_part_list::const_iterator i;
    		post_c_code(dynamic_cast<C_CODE*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Macro_call::ID: 
    	{
    		Body_part_list* local_out = new Body_part_list;
    		Body_part_list::const_iterator i;
    		post_macro_call(dynamic_cast<Macro_call*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Lookup::ID: 
    	out->push_back(post_lookup(dynamic_cast<Lookup*>(in)));
    	return;
    case PARAM_NAME::ID: 
    	out->push_back(post_param_name(dynamic_cast<PARAM_NAME*>(in)));
    	return;
    }
    assert(0);
}

void Transform::post_actual_parameter(Actual_parameter* in, Actual_parameter_list* out)
{
    switch(in->classid())
    {
    case STRING::ID: 
    	out->push_back(post_string(dynamic_cast<STRING*>(in)));
    	return;
    case PARAM_NAME::ID: 
    	out->push_back(post_param_name(dynamic_cast<PARAM_NAME*>(in)));
    	return;
    }
    assert(0);
}

/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
void Transform::children_expr(Expr* in)
{
    switch(in->classid())
    {
    case Equals::ID:
    	children_equals(dynamic_cast<Equals*>(in));
    	break;
    case Lookup::ID:
    	children_lookup(dynamic_cast<Lookup*>(in));
    	break;
    case PARAM_NAME::ID:
    	children_param_name(dynamic_cast<PARAM_NAME*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    }
}

void Transform::children_body_part(Body_part* in)
{
    switch(in->classid())
    {
    case C_CODE::ID:
    	children_c_code(dynamic_cast<C_CODE*>(in));
    	break;
    case Macro_call::ID:
    	children_macro_call(dynamic_cast<Macro_call*>(in));
    	break;
    case Lookup::ID:
    	children_lookup(dynamic_cast<Lookup*>(in));
    	break;
    case PARAM_NAME::ID:
    	children_param_name(dynamic_cast<PARAM_NAME*>(in));
    	break;
    }
}

void Transform::children_actual_parameter(Actual_parameter* in)
{
    switch(in->classid())
    {
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case PARAM_NAME::ID:
    	children_param_name(dynamic_cast<PARAM_NAME*>(in));
    	break;
    }
}
}

