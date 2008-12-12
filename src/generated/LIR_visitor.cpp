#include "LIR_visitor.h"

namespace LIR{
Visitor::~Visitor()
{
}

/* Invoked before the children are visited */
void Visitor::pre_node(Node* in)
{
}

void Visitor::pre_c_file(C_file* in)
{
}

void Visitor::pre_code(CODE* in)
{
}

/* Invoked after the children have been visited */
void Visitor::post_node(Node* in)
{
}

void Visitor::post_c_file(C_file* in)
{
}

void Visitor::post_code(CODE* in)
{
}

/* Visit the children of a node */
void Visitor::children_c_file(C_file* in)
{
    visit_code_list(in->codes);
}

/* Tokens don't have children, so these methods do nothing by default */
void Visitor::children_code(CODE* in)
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
void Visitor::pre_c_file_chain(C_file* in)
{
    pre_node((Node*) in);
    pre_c_file((C_file*) in);
}

void Visitor::pre_code_chain(CODE* in)
{
    pre_node((Node*) in);
    pre_code((CODE*) in);
}

/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
void Visitor::post_c_file_chain(C_file* in)
{
    post_c_file((C_file*) in);
    post_node((Node*) in);
}

void Visitor::post_code_chain(CODE* in)
{
    post_code((CODE*) in);
    post_node((Node*) in);
}

/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
void Visitor::visit_code_list(CODE_list* in)
{
    CODE_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("LIR", "CODE");
    else
    {
    	pre_list("LIR", "CODE", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_code(*i);
    	}
    
    	post_list("LIR", "CODE", in->size());
    }
}

void Visitor::visit_code(CODE* in)
{
    if(in == NULL)
    	visit_null("LIR", "CODE");
    else
    {
    	pre_code_chain(in);
    	children_code(in);
    	post_code_chain(in);
    }
}

void Visitor::visit_c_file(C_file* in)
{
    if(in == NULL)
    	visit_null("LIR", "C_file");
    else
    {
    	pre_c_file_chain(in);
    	children_c_file(in);
    	post_c_file_chain(in);
    }
}

/* Invoke the right pre-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */}

