#include "MICG_transform.h"

namespace MICG{
Transform::~Transform()
{
}

/* Invoked before the children are transformed */
All* Transform::pre_all(All* in)
{
    return in;
}

void Transform::pre_macro(Macro* in, Macro_list* out)
{
    out->push_back(in);
}

Signature* Transform::pre_signature(Signature* in)
{
    return in;
}

void Transform::pre_formal_parameter(Formal_parameter* in, Formal_parameter_list* out)
{
    out->push_back(in);
}

Lookup* Transform::pre_lookup(Lookup* in)
{
    return in;
}

void Transform::pre_equals(Equals* in, Rule_list* out)
{
    out->push_back(in);
}

Expr* Transform::pre_param(Param* in)
{
    return in;
}

Body* Transform::pre_body(Body* in)
{
    return in;
}

Macro_call* Transform::pre_macro_call(Macro_call* in)
{
    return in;
}

Callback* Transform::pre_callback(Callback* in)
{
    return in;
}

MACRO_NAME* Transform::pre_macro_name(MACRO_NAME* in)
{
    return in;
}

TYPE_NAME* Transform::pre_type_name(TYPE_NAME* in)
{
    return in;
}

PARAM_NAME* Transform::pre_param_name(PARAM_NAME* in)
{
    return in;
}

ATTR_NAME* Transform::pre_attr_name(ATTR_NAME* in)
{
    return in;
}

Expr* Transform::pre_string(STRING* in)
{
    return in;
}

void Transform::pre_c_code(C_CODE* in, Body_part_list* out)
{
    out->push_back(in);
}

/* Invoked after the children have been transformed */
All* Transform::post_all(All* in)
{
    return in;
}

void Transform::post_macro(Macro* in, Macro_list* out)
{
    out->push_back(in);
}

Signature* Transform::post_signature(Signature* in)
{
    return in;
}

void Transform::post_formal_parameter(Formal_parameter* in, Formal_parameter_list* out)
{
    out->push_back(in);
}

Lookup* Transform::post_lookup(Lookup* in)
{
    return in;
}

void Transform::post_equals(Equals* in, Rule_list* out)
{
    out->push_back(in);
}

Expr* Transform::post_param(Param* in)
{
    return in;
}

Body* Transform::post_body(Body* in)
{
    return in;
}

Macro_call* Transform::post_macro_call(Macro_call* in)
{
    return in;
}

Callback* Transform::post_callback(Callback* in)
{
    return in;
}

MACRO_NAME* Transform::post_macro_name(MACRO_NAME* in)
{
    return in;
}

TYPE_NAME* Transform::post_type_name(TYPE_NAME* in)
{
    return in;
}

PARAM_NAME* Transform::post_param_name(PARAM_NAME* in)
{
    return in;
}

ATTR_NAME* Transform::post_attr_name(ATTR_NAME* in)
{
    return in;
}

Expr* Transform::post_string(STRING* in)
{
    return in;
}

void Transform::post_c_code(C_CODE* in, Body_part_list* out)
{
    out->push_back(in);
}

/* Transform the children of the node */
void Transform::children_all(All* in)
{
    in->macros = transform_macro_list(in->macros);
}

void Transform::children_macro(Macro* in)
{
    in->signature = transform_signature(in->signature);
    in->rules = transform_rule_list(in->rules);
    in->body = transform_body(in->body);
}

void Transform::children_signature(Signature* in)
{
    in->macro_name = transform_macro_name(in->macro_name);
    in->formal_parameters = transform_formal_parameter_list(in->formal_parameters);
}

void Transform::children_formal_parameter(Formal_parameter* in)
{
    in->type_name = transform_type_name(in->type_name);
    in->param_name = transform_param_name(in->param_name);
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

void Transform::children_param(Param* in)
{
    in->param_name = transform_param_name(in->param_name);
    in->attr_names = transform_attr_name_list(in->attr_names);
}

void Transform::children_body(Body* in)
{
    in->body_parts = transform_body_part_list(in->body_parts);
}

void Transform::children_macro_call(Macro_call* in)
{
    in->macro_name = transform_macro_name(in->macro_name);
    in->exprs = transform_expr_list(in->exprs);
}

void Transform::children_callback(Callback* in)
{
    in->macro_name = transform_macro_name(in->macro_name);
    in->exprs = transform_expr_list(in->exprs);
}

/* Tokens don't have children, so these methods do nothing by default */
void Transform::children_macro_name(MACRO_NAME* in)
{
}

void Transform::children_type_name(TYPE_NAME* in)
{
}

void Transform::children_param_name(PARAM_NAME* in)
{
}

void Transform::children_attr_name(ATTR_NAME* in)
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
Macro_list* Transform::transform_macro_list(Macro_list* in)
{
    Macro_list::const_iterator i;
    Macro_list* out = new Macro_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_macro(*i));
    }
    
    return out;
}

Macro_list* Transform::transform_macro(Macro* in)
{
    Macro_list::const_iterator i;
    Macro_list* out1 = new Macro_list;
    Macro_list* out2 = new Macro_list;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_macro(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_macro(*i);
    		post_macro(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
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

MACRO_NAME* Transform::transform_macro_name(MACRO_NAME* in)
{
    if(in == NULL) return NULL;
    
    MACRO_NAME* out;
    
    out = pre_macro_name(in);
    if(out != NULL)
    {
    	children_macro_name(out);
    	out = post_macro_name(out);
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

TYPE_NAME* Transform::transform_type_name(TYPE_NAME* in)
{
    if(in == NULL) return NULL;
    
    TYPE_NAME* out;
    
    out = pre_type_name(in);
    if(out != NULL)
    {
    	children_type_name(out);
    	out = post_type_name(out);
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

ATTR_NAME_list* Transform::transform_attr_name_list(ATTR_NAME_list* in)
{
    ATTR_NAME_list::const_iterator i;
    ATTR_NAME_list* out = new ATTR_NAME_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_attr_name(*i));
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

Expr_list* Transform::transform_expr_list(Expr_list* in)
{
    Expr_list::const_iterator i;
    Expr_list* out = new Expr_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back(transform_expr(*i));
    }
    
    return out;
}

All* Transform::transform_all(All* in)
{
    if(in == NULL) return NULL;
    
    All* out;
    
    out = pre_all(in);
    if(out != NULL)
    {
    	children_all(out);
    	out = post_all(out);
    }
    
    return out;
}

/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
void Transform::pre_rule(Rule* in, Rule_list* out)
{
    switch(in->classid())
    {
    case Equals::ID: 
    	{
    		Rule_list* local_out = new Rule_list;
    		Rule_list::const_iterator i;
    		pre_equals(dynamic_cast<Equals*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Lookup::ID: 
    	out->push_back(pre_lookup(dynamic_cast<Lookup*>(in)));
    	return;
    }
    assert(0);
}

Expr* Transform::pre_expr(Expr* in)
{
    switch(in->classid())
    {
    case Param::ID: return pre_param(dynamic_cast<Param*>(in));
    case STRING::ID: return pre_string(dynamic_cast<STRING*>(in));
    case Lookup::ID: return pre_lookup(dynamic_cast<Lookup*>(in));
    case Macro_call::ID: return pre_macro_call(dynamic_cast<Macro_call*>(in));
    case Callback::ID: return pre_callback(dynamic_cast<Callback*>(in));
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
    case Lookup::ID: 
    	out->push_back(pre_lookup(dynamic_cast<Lookup*>(in)));
    	return;
    case PARAM_NAME::ID: 
    	out->push_back(pre_param_name(dynamic_cast<PARAM_NAME*>(in)));
    	return;
    case Macro_call::ID: 
    	out->push_back(pre_macro_call(dynamic_cast<Macro_call*>(in)));
    	return;
    case Callback::ID: 
    	out->push_back(pre_callback(dynamic_cast<Callback*>(in)));
    	return;
    }
    assert(0);
}

/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
void Transform::post_rule(Rule* in, Rule_list* out)
{
    switch(in->classid())
    {
    case Equals::ID: 
    	{
    		Rule_list* local_out = new Rule_list;
    		Rule_list::const_iterator i;
    		post_equals(dynamic_cast<Equals*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Lookup::ID: 
    	out->push_back(post_lookup(dynamic_cast<Lookup*>(in)));
    	return;
    }
    assert(0);
}

Expr* Transform::post_expr(Expr* in)
{
    switch(in->classid())
    {
    case Param::ID: return post_param(dynamic_cast<Param*>(in));
    case STRING::ID: return post_string(dynamic_cast<STRING*>(in));
    case Lookup::ID: return post_lookup(dynamic_cast<Lookup*>(in));
    case Macro_call::ID: return post_macro_call(dynamic_cast<Macro_call*>(in));
    case Callback::ID: return post_callback(dynamic_cast<Callback*>(in));
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
    case Lookup::ID: 
    	out->push_back(post_lookup(dynamic_cast<Lookup*>(in)));
    	return;
    case PARAM_NAME::ID: 
    	out->push_back(post_param_name(dynamic_cast<PARAM_NAME*>(in)));
    	return;
    case Macro_call::ID: 
    	out->push_back(post_macro_call(dynamic_cast<Macro_call*>(in)));
    	return;
    case Callback::ID: 
    	out->push_back(post_callback(dynamic_cast<Callback*>(in)));
    	return;
    }
    assert(0);
}

/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
void Transform::children_rule(Rule* in)
{
    switch(in->classid())
    {
    case Equals::ID:
    	children_equals(dynamic_cast<Equals*>(in));
    	break;
    case Lookup::ID:
    	children_lookup(dynamic_cast<Lookup*>(in));
    	break;
    }
}

void Transform::children_expr(Expr* in)
{
    switch(in->classid())
    {
    case Param::ID:
    	children_param(dynamic_cast<Param*>(in));
    	break;
    case STRING::ID:
    	children_string(dynamic_cast<STRING*>(in));
    	break;
    case Lookup::ID:
    	children_lookup(dynamic_cast<Lookup*>(in));
    	break;
    case Macro_call::ID:
    	children_macro_call(dynamic_cast<Macro_call*>(in));
    	break;
    case Callback::ID:
    	children_callback(dynamic_cast<Callback*>(in));
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
    case Lookup::ID:
    	children_lookup(dynamic_cast<Lookup*>(in));
    	break;
    case PARAM_NAME::ID:
    	children_param_name(dynamic_cast<PARAM_NAME*>(in));
    	break;
    case Macro_call::ID:
    	children_macro_call(dynamic_cast<Macro_call*>(in));
    	break;
    case Callback::ID:
    	children_callback(dynamic_cast<Callback*>(in));
    	break;
    }
}
}

