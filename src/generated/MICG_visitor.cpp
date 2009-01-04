#include "MICG_visitor.h"

namespace MICG{
Visitor::~Visitor()
{
}

/* Invoked before the children are visited */
void Visitor::pre_node(Node* in)
{
}

void Visitor::pre_all(All* in)
{
}

void Visitor::pre_macro(Macro* in)
{
}

void Visitor::pre_signature(Signature* in)
{
}

void Visitor::pre_formal_parameter(Formal_parameter* in)
{
}

void Visitor::pre_rule(Rule* in)
{
}

void Visitor::pre_lookup(Lookup* in)
{
}

void Visitor::pre_equals(Equals* in)
{
}

void Visitor::pre_expr(Expr* in)
{
}

void Visitor::pre_param(Param* in)
{
}

void Visitor::pre_body(Body* in)
{
}

void Visitor::pre_body_part(Body_part* in)
{
}

void Visitor::pre_interpolation(Interpolation* in)
{
}

void Visitor::pre_macro_call(Macro_call* in)
{
}

void Visitor::pre_callback(Callback* in)
{
}

void Visitor::pre_identifier(Identifier* in)
{
}

void Visitor::pre_macro_name(MACRO_NAME* in)
{
}

void Visitor::pre_type_name(TYPE_NAME* in)
{
}

void Visitor::pre_param_name(PARAM_NAME* in)
{
}

void Visitor::pre_attr_name(ATTR_NAME* in)
{
}

void Visitor::pre_string(STRING* in)
{
}

void Visitor::pre_c_code(C_CODE* in)
{
}

/* Invoked after the children have been visited */
void Visitor::post_node(Node* in)
{
}

void Visitor::post_all(All* in)
{
}

void Visitor::post_macro(Macro* in)
{
}

void Visitor::post_signature(Signature* in)
{
}

void Visitor::post_formal_parameter(Formal_parameter* in)
{
}

void Visitor::post_rule(Rule* in)
{
}

void Visitor::post_lookup(Lookup* in)
{
}

void Visitor::post_equals(Equals* in)
{
}

void Visitor::post_expr(Expr* in)
{
}

void Visitor::post_param(Param* in)
{
}

void Visitor::post_body(Body* in)
{
}

void Visitor::post_body_part(Body_part* in)
{
}

void Visitor::post_interpolation(Interpolation* in)
{
}

void Visitor::post_macro_call(Macro_call* in)
{
}

void Visitor::post_callback(Callback* in)
{
}

void Visitor::post_identifier(Identifier* in)
{
}

void Visitor::post_macro_name(MACRO_NAME* in)
{
}

void Visitor::post_type_name(TYPE_NAME* in)
{
}

void Visitor::post_param_name(PARAM_NAME* in)
{
}

void Visitor::post_attr_name(ATTR_NAME* in)
{
}

void Visitor::post_string(STRING* in)
{
}

void Visitor::post_c_code(C_CODE* in)
{
}

/* Visit the children of a node */
void Visitor::children_all(All* in)
{
    visit_macro_list(in->macros);
}

void Visitor::children_macro(Macro* in)
{
    visit_signature(in->signature);
    visit_rule_list(in->rules);
    visit_body(in->body);
}

void Visitor::children_signature(Signature* in)
{
    visit_macro_name(in->macro_name);
    visit_formal_parameter_list(in->formal_parameters);
}

void Visitor::children_formal_parameter(Formal_parameter* in)
{
    visit_type_name(in->type_name);
    visit_param_name(in->param_name);
}

void Visitor::children_lookup(Lookup* in)
{
    visit_param_name(in->param_name);
    visit_attr_name(in->attr_name);
}

void Visitor::children_equals(Equals* in)
{
    visit_expr(in->left);
    visit_expr(in->right);
}

void Visitor::children_param(Param* in)
{
    visit_param_name(in->param_name);
    visit_attr_name_list(in->attr_names);
}

void Visitor::children_body(Body* in)
{
    visit_body_part_list(in->body_parts);
}

void Visitor::children_macro_call(Macro_call* in)
{
    visit_macro_name(in->macro_name);
    visit_expr_list(in->exprs);
}

void Visitor::children_callback(Callback* in)
{
    visit_macro_name(in->macro_name);
    visit_expr_list(in->exprs);
}

/* Tokens don't have children, so these methods do nothing by default */
void Visitor::children_macro_name(MACRO_NAME* in)
{
}

void Visitor::children_type_name(TYPE_NAME* in)
{
}

void Visitor::children_param_name(PARAM_NAME* in)
{
}

void Visitor::children_attr_name(ATTR_NAME* in)
{
}

void Visitor::children_string(STRING* in)
{
}

void Visitor::children_c_code(C_CODE* in)
{
}

/* Unparser support */
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

/* Invoke the chain of pre-visit methods along the inheritance hierachy */
/* Do not override unless you know what you are doing */
void Visitor::pre_all_chain(All* in)
{
    pre_node((Node*) in);
    pre_all((All*) in);
}

void Visitor::pre_macro_chain(Macro* in)
{
    pre_node((Node*) in);
    pre_macro((Macro*) in);
}

void Visitor::pre_signature_chain(Signature* in)
{
    pre_node((Node*) in);
    pre_signature((Signature*) in);
}

void Visitor::pre_formal_parameter_chain(Formal_parameter* in)
{
    pre_node((Node*) in);
    pre_formal_parameter((Formal_parameter*) in);
}

void Visitor::pre_lookup_chain(Lookup* in)
{
    pre_node((Node*) in);
    pre_rule((Rule*) in);
    pre_expr((Expr*) in);
    pre_body_part((Body_part*) in);
    pre_interpolation((Interpolation*) in);
    pre_lookup((Lookup*) in);
}

void Visitor::pre_equals_chain(Equals* in)
{
    pre_node((Node*) in);
    pre_rule((Rule*) in);
    pre_equals((Equals*) in);
}

void Visitor::pre_param_chain(Param* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_param((Param*) in);
}

void Visitor::pre_body_chain(Body* in)
{
    pre_node((Node*) in);
    pre_body((Body*) in);
}

void Visitor::pre_macro_call_chain(Macro_call* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_body_part((Body_part*) in);
    pre_macro_call((Macro_call*) in);
}

void Visitor::pre_callback_chain(Callback* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_body_part((Body_part*) in);
    pre_callback((Callback*) in);
}

void Visitor::pre_macro_name_chain(MACRO_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_macro_name((MACRO_NAME*) in);
}

void Visitor::pre_type_name_chain(TYPE_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_type_name((TYPE_NAME*) in);
}

void Visitor::pre_param_name_chain(PARAM_NAME* in)
{
    pre_node((Node*) in);
    pre_body_part((Body_part*) in);
    pre_interpolation((Interpolation*) in);
    pre_identifier((Identifier*) in);
    pre_param_name((PARAM_NAME*) in);
}

void Visitor::pre_attr_name_chain(ATTR_NAME* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_attr_name((ATTR_NAME*) in);
}

void Visitor::pre_string_chain(STRING* in)
{
    pre_node((Node*) in);
    pre_expr((Expr*) in);
    pre_identifier((Identifier*) in);
    pre_string((STRING*) in);
}

void Visitor::pre_c_code_chain(C_CODE* in)
{
    pre_node((Node*) in);
    pre_body_part((Body_part*) in);
    pre_identifier((Identifier*) in);
    pre_c_code((C_CODE*) in);
}

/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
void Visitor::post_all_chain(All* in)
{
    post_all((All*) in);
    post_node((Node*) in);
}

void Visitor::post_macro_chain(Macro* in)
{
    post_macro((Macro*) in);
    post_node((Node*) in);
}

void Visitor::post_signature_chain(Signature* in)
{
    post_signature((Signature*) in);
    post_node((Node*) in);
}

void Visitor::post_formal_parameter_chain(Formal_parameter* in)
{
    post_formal_parameter((Formal_parameter*) in);
    post_node((Node*) in);
}

void Visitor::post_lookup_chain(Lookup* in)
{
    post_lookup((Lookup*) in);
    post_interpolation((Interpolation*) in);
    post_body_part((Body_part*) in);
    post_expr((Expr*) in);
    post_rule((Rule*) in);
    post_node((Node*) in);
}

void Visitor::post_equals_chain(Equals* in)
{
    post_equals((Equals*) in);
    post_rule((Rule*) in);
    post_node((Node*) in);
}

void Visitor::post_param_chain(Param* in)
{
    post_param((Param*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_body_chain(Body* in)
{
    post_body((Body*) in);
    post_node((Node*) in);
}

void Visitor::post_macro_call_chain(Macro_call* in)
{
    post_macro_call((Macro_call*) in);
    post_body_part((Body_part*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_callback_chain(Callback* in)
{
    post_callback((Callback*) in);
    post_body_part((Body_part*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_macro_name_chain(MACRO_NAME* in)
{
    post_macro_name((MACRO_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_type_name_chain(TYPE_NAME* in)
{
    post_type_name((TYPE_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_param_name_chain(PARAM_NAME* in)
{
    post_param_name((PARAM_NAME*) in);
    post_identifier((Identifier*) in);
    post_interpolation((Interpolation*) in);
    post_body_part((Body_part*) in);
    post_node((Node*) in);
}

void Visitor::post_attr_name_chain(ATTR_NAME* in)
{
    post_attr_name((ATTR_NAME*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_string_chain(STRING* in)
{
    post_string((STRING*) in);
    post_identifier((Identifier*) in);
    post_expr((Expr*) in);
    post_node((Node*) in);
}

void Visitor::post_c_code_chain(C_CODE* in)
{
    post_c_code((C_CODE*) in);
    post_identifier((Identifier*) in);
    post_body_part((Body_part*) in);
    post_node((Node*) in);
}

/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
void Visitor::visit_macro_list(Macro_list* in)
{
    Macro_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MICG", "Macro");
    else
    {
    	pre_list("MICG", "Macro", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_macro(*i);
    	}
    
    	post_list("MICG", "Macro", in->size());
    }
}

void Visitor::visit_macro(Macro* in)
{
    if(in == NULL)
    	visit_null("MICG", "Macro");
    else
    {
    	pre_macro_chain(in);
    	children_macro(in);
    	post_macro_chain(in);
    }
}

void Visitor::visit_signature(Signature* in)
{
    if(in == NULL)
    	visit_null("MICG", "Signature");
    else
    {
    	pre_signature_chain(in);
    	children_signature(in);
    	post_signature_chain(in);
    }
}

void Visitor::visit_rule_list(Rule_list* in)
{
    Rule_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MICG", "Rule");
    else
    {
    	pre_list("MICG", "Rule", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_rule(*i);
    	}
    
    	post_list("MICG", "Rule", in->size());
    }
}

void Visitor::visit_rule(Rule* in)
{
    if(in == NULL)
    	visit_null("MICG", "Rule");
    else
    {
    	pre_rule_chain(in);
    	children_rule(in);
    	post_rule_chain(in);
    }
}

void Visitor::visit_body(Body* in)
{
    if(in == NULL)
    	visit_null("MICG", "Body");
    else
    {
    	pre_body_chain(in);
    	children_body(in);
    	post_body_chain(in);
    }
}

void Visitor::visit_macro_name(MACRO_NAME* in)
{
    if(in == NULL)
    	visit_null("MICG", "MACRO_NAME");
    else
    {
    	pre_macro_name_chain(in);
    	children_macro_name(in);
    	post_macro_name_chain(in);
    }
}

void Visitor::visit_formal_parameter_list(Formal_parameter_list* in)
{
    Formal_parameter_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MICG", "Formal_parameter");
    else
    {
    	pre_list("MICG", "Formal_parameter", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_formal_parameter(*i);
    	}
    
    	post_list("MICG", "Formal_parameter", in->size());
    }
}

void Visitor::visit_formal_parameter(Formal_parameter* in)
{
    if(in == NULL)
    	visit_null("MICG", "Formal_parameter");
    else
    {
    	pre_formal_parameter_chain(in);
    	children_formal_parameter(in);
    	post_formal_parameter_chain(in);
    }
}

void Visitor::visit_type_name(TYPE_NAME* in)
{
    if(in == NULL)
    	visit_null("MICG", "TYPE_NAME");
    else
    {
    	pre_type_name_chain(in);
    	children_type_name(in);
    	post_type_name_chain(in);
    }
}

void Visitor::visit_param_name(PARAM_NAME* in)
{
    if(in == NULL)
    	visit_null("MICG", "PARAM_NAME");
    else
    {
    	pre_param_name_chain(in);
    	children_param_name(in);
    	post_param_name_chain(in);
    }
}

void Visitor::visit_attr_name(ATTR_NAME* in)
{
    if(in == NULL)
    	visit_null("MICG", "ATTR_NAME");
    else
    {
    	pre_attr_name_chain(in);
    	children_attr_name(in);
    	post_attr_name_chain(in);
    }
}

void Visitor::visit_expr(Expr* in)
{
    if(in == NULL)
    	visit_null("MICG", "Expr");
    else
    {
    	pre_expr_chain(in);
    	children_expr(in);
    	post_expr_chain(in);
    }
}

void Visitor::visit_attr_name_list(ATTR_NAME_list* in)
{
    ATTR_NAME_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MICG", "ATTR_NAME");
    else
    {
    	pre_list("MICG", "ATTR_NAME", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_attr_name(*i);
    	}
    
    	post_list("MICG", "ATTR_NAME", in->size());
    }
}

void Visitor::visit_body_part_list(Body_part_list* in)
{
    Body_part_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MICG", "Body_part");
    else
    {
    	pre_list("MICG", "Body_part", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_body_part(*i);
    	}
    
    	post_list("MICG", "Body_part", in->size());
    }
}

void Visitor::visit_body_part(Body_part* in)
{
    if(in == NULL)
    	visit_null("MICG", "Body_part");
    else
    {
    	pre_body_part_chain(in);
    	children_body_part(in);
    	post_body_part_chain(in);
    }
}

void Visitor::visit_expr_list(Expr_list* in)
{
    Expr_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("MICG", "Expr");
    else
    {
    	pre_list("MICG", "Expr", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_expr(*i);
    	}
    
    	post_list("MICG", "Expr", in->size());
    }
}

void Visitor::visit_all(All* in)
{
    if(in == NULL)
    	visit_null("MICG", "All");
    else
    {
    	pre_all_chain(in);
    	children_all(in);
    	post_all_chain(in);
    }
}

/* Invoke the right pre-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
void Visitor::pre_rule_chain(Rule* in)
{
    switch(in->classid())
    {
    case Equals::ID:
    	pre_equals_chain(dynamic_cast<Equals*>(in));
    	break;
    case Lookup::ID:
    	pre_lookup_chain(dynamic_cast<Lookup*>(in));
    	break;
    }
}

void Visitor::pre_expr_chain(Expr* in)
{
    switch(in->classid())
    {
    case Param::ID:
    	pre_param_chain(dynamic_cast<Param*>(in));
    	break;
    case STRING::ID:
    	pre_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case Lookup::ID:
    	pre_lookup_chain(dynamic_cast<Lookup*>(in));
    	break;
    case Macro_call::ID:
    	pre_macro_call_chain(dynamic_cast<Macro_call*>(in));
    	break;
    case Callback::ID:
    	pre_callback_chain(dynamic_cast<Callback*>(in));
    	break;
    }
}

void Visitor::pre_body_part_chain(Body_part* in)
{
    switch(in->classid())
    {
    case C_CODE::ID:
    	pre_c_code_chain(dynamic_cast<C_CODE*>(in));
    	break;
    case Lookup::ID:
    	pre_lookup_chain(dynamic_cast<Lookup*>(in));
    	break;
    case PARAM_NAME::ID:
    	pre_param_name_chain(dynamic_cast<PARAM_NAME*>(in));
    	break;
    case Macro_call::ID:
    	pre_macro_call_chain(dynamic_cast<Macro_call*>(in));
    	break;
    case Callback::ID:
    	pre_callback_chain(dynamic_cast<Callback*>(in));
    	break;
    }
}

/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
void Visitor::post_rule_chain(Rule* in)
{
    switch(in->classid())
    {
    case Equals::ID:
    	post_equals_chain(dynamic_cast<Equals*>(in));
    	break;
    case Lookup::ID:
    	post_lookup_chain(dynamic_cast<Lookup*>(in));
    	break;
    }
}

void Visitor::post_expr_chain(Expr* in)
{
    switch(in->classid())
    {
    case Param::ID:
    	post_param_chain(dynamic_cast<Param*>(in));
    	break;
    case STRING::ID:
    	post_string_chain(dynamic_cast<STRING*>(in));
    	break;
    case Lookup::ID:
    	post_lookup_chain(dynamic_cast<Lookup*>(in));
    	break;
    case Macro_call::ID:
    	post_macro_call_chain(dynamic_cast<Macro_call*>(in));
    	break;
    case Callback::ID:
    	post_callback_chain(dynamic_cast<Callback*>(in));
    	break;
    }
}

void Visitor::post_body_part_chain(Body_part* in)
{
    switch(in->classid())
    {
    case C_CODE::ID:
    	post_c_code_chain(dynamic_cast<C_CODE*>(in));
    	break;
    case Lookup::ID:
    	post_lookup_chain(dynamic_cast<Lookup*>(in));
    	break;
    case PARAM_NAME::ID:
    	post_param_name_chain(dynamic_cast<PARAM_NAME*>(in));
    	break;
    case Macro_call::ID:
    	post_macro_call_chain(dynamic_cast<Macro_call*>(in));
    	break;
    case Callback::ID:
    	post_callback_chain(dynamic_cast<Callback*>(in));
    	break;
    }
}

/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */
void Visitor::children_rule(Rule* in)
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

void Visitor::children_expr(Expr* in)
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

void Visitor::children_body_part(Body_part* in)
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

