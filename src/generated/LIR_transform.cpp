#include "LIR_transform.h"

namespace LIR{
Transform::~Transform()
{
}

/* Invoked before the children are transformed */
C_file* Transform::pre_c_file(C_file* in)
{
    return in;
}

void Transform::pre_code(CODE* in, CODE_list* out)
{
    out->push_back(in);
}

/* Invoked after the children have been transformed */
C_file* Transform::post_c_file(C_file* in)
{
    return in;
}

void Transform::post_code(CODE* in, CODE_list* out)
{
    out->push_back(in);
}

/* Transform the children of the node */
void Transform::children_c_file(C_file* in)
{
    in->codes = transform_code_list(in->codes);
}

/* Tokens don't have children, so these methods do nothing by default */
void Transform::children_code(CODE* in)
{
}

/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
CODE_list* Transform::transform_code_list(CODE_list* in)
{
    CODE_list::const_iterator i;
    CODE_list* out = new CODE_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_code(*i));
    }
    
    return out;
}

CODE_list* Transform::transform_code(CODE* in)
{
    CODE_list::const_iterator i;
    CODE_list* out1 = new CODE_list;
    CODE_list* out2 = new CODE_list;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_code(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_code(*i);
    		post_code(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

C_file* Transform::transform_c_file(C_file* in)
{
    if(in == NULL) return NULL;
    
    C_file* out;
    
    out = pre_c_file(in);
    if(out != NULL)
    {
    	children_c_file(out);
    	out = post_c_file(out);
    }
    
    return out;
}

/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */}

