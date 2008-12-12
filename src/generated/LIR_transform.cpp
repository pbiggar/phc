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

void Transform::pre_method(Method* in, Piece_list* out)
{
    out->push_back(in);
}

void Transform::pre_block(Block* in, Piece_list* out)
{
    out->push_back(in);
}

void Transform::pre_if(If* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_zvp(Assign_zvp* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_assign_zvpp(Assign_zvpp* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_inc_ref(Inc_ref* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_allocate(Allocate* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_clone(Clone* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_separate(Separate* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_dec_ref(Dec_ref* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_destruct(Destruct* in, Statement_list* out)
{
    out->push_back(in);
}

Cond* Transform::pre_is_ref(Is_ref* in)
{
    return in;
}

Cond* Transform::pre_equals(Equals* in)
{
    return in;
}

Zvp* Transform::pre_uninitialized(Uninitialized* in)
{
    return in;
}

Zvp* Transform::pre_null(Null* in)
{
    return in;
}

Zvp* Transform::pre_deref(Deref* in)
{
    return in;
}

Zvpp* Transform::pre_ref(Ref* in)
{
    return in;
}

COMMENT* Transform::pre_comment(COMMENT* in)
{
    return in;
}

UNINTERPRETED* Transform::pre_uninterpreted(UNINTERPRETED* in)
{
    return in;
}

void Transform::pre_intrinsic(INTRINSIC* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_api_call(API_CALL* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_code(CODE* in, Statement_list* out)
{
    out->push_back(in);
}

Zvp* Transform::pre_zvp(ZVP* in)
{
    return in;
}

Zvp* Transform::pre_literal(LITERAL* in)
{
    return in;
}

Zvpp* Transform::pre_zvpp(ZVPP* in)
{
    return in;
}

/* Invoked after the children have been transformed */
C_file* Transform::post_c_file(C_file* in)
{
    return in;
}

void Transform::post_method(Method* in, Piece_list* out)
{
    out->push_back(in);
}

void Transform::post_block(Block* in, Piece_list* out)
{
    out->push_back(in);
}

void Transform::post_if(If* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_zvp(Assign_zvp* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_assign_zvpp(Assign_zvpp* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_inc_ref(Inc_ref* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_allocate(Allocate* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_clone(Clone* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_separate(Separate* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_dec_ref(Dec_ref* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_destruct(Destruct* in, Statement_list* out)
{
    out->push_back(in);
}

Cond* Transform::post_is_ref(Is_ref* in)
{
    return in;
}

Cond* Transform::post_equals(Equals* in)
{
    return in;
}

Zvp* Transform::post_uninitialized(Uninitialized* in)
{
    return in;
}

Zvp* Transform::post_null(Null* in)
{
    return in;
}

Zvp* Transform::post_deref(Deref* in)
{
    return in;
}

Zvpp* Transform::post_ref(Ref* in)
{
    return in;
}

COMMENT* Transform::post_comment(COMMENT* in)
{
    return in;
}

UNINTERPRETED* Transform::post_uninterpreted(UNINTERPRETED* in)
{
    return in;
}

void Transform::post_intrinsic(INTRINSIC* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_api_call(API_CALL* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_code(CODE* in, Statement_list* out)
{
    out->push_back(in);
}

Zvp* Transform::post_zvp(ZVP* in)
{
    return in;
}

Zvp* Transform::post_literal(LITERAL* in)
{
    return in;
}

Zvpp* Transform::post_zvpp(ZVPP* in)
{
    return in;
}

/* Transform the children of the node */
void Transform::children_c_file(C_file* in)
{
    in->pieces = transform_piece_list(in->pieces);
}

void Transform::children_method(Method* in)
{
    in->comment = transform_comment(in->comment);
    in->entry = transform_uninterpreted(in->entry);
    in->pieces = transform_piece_list(in->pieces);
    in->exit = transform_uninterpreted(in->exit);
}

void Transform::children_block(Block* in)
{
    in->comment = transform_comment(in->comment);
    in->statements = transform_statement_list(in->statements);
}

void Transform::children_if(If* in)
{
    in->cond = transform_cond(in->cond);
    in->if_true = transform_statement_list(in->if_true);
    in->if_false = transform_statement_list(in->if_false);
}

void Transform::children_assign_zvp(Assign_zvp* in)
{
    in->lhs = transform_zvp(in->lhs);
    in->rhs = transform_zvp(in->rhs);
}

void Transform::children_assign_zvpp(Assign_zvpp* in)
{
    in->lhs = transform_zvpp(in->lhs);
    in->rhs = transform_zvpp(in->rhs);
}

void Transform::children_inc_ref(Inc_ref* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_allocate(Allocate* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_clone(Clone* in)
{
    in->lhs = transform_zvp(in->lhs);
    in->rhs = transform_zvp(in->rhs);
}

void Transform::children_separate(Separate* in)
{
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_dec_ref(Dec_ref* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_destruct(Destruct* in)
{
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_is_ref(Is_ref* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_equals(Equals* in)
{
    in->lhs = transform_zvp(in->lhs);
    in->rhs = transform_zvp(in->rhs);
}

void Transform::children_uninitialized(Uninitialized* in)
{
}

void Transform::children_null(Null* in)
{
}

void Transform::children_deref(Deref* in)
{
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_ref(Ref* in)
{
    in->zvp = transform_zvp(in->zvp);
}

/* Tokens don't have children, so these methods do nothing by default */
void Transform::children_comment(COMMENT* in)
{
}

void Transform::children_uninterpreted(UNINTERPRETED* in)
{
}

void Transform::children_intrinsic(INTRINSIC* in)
{
}

void Transform::children_api_call(API_CALL* in)
{
}

void Transform::children_code(CODE* in)
{
}

void Transform::children_zvp(ZVP* in)
{
}

void Transform::children_literal(LITERAL* in)
{
}

void Transform::children_zvpp(ZVPP* in)
{
}

/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
Piece_list* Transform::transform_piece_list(Piece_list* in)
{
    Piece_list::const_iterator i;
    Piece_list* out = new Piece_list;
    
    if(in == NULL)
    	return NULL;
    
    for(i = in->begin(); i != in->end(); i++)
    {
    	out->push_back_all(transform_piece(*i));
    }
    
    return out;
}

Piece_list* Transform::transform_piece(Piece* in)
{
    Piece_list::const_iterator i;
    Piece_list* out1 = new Piece_list;
    Piece_list* out2 = new Piece_list;
    
    if(in == NULL) out1->push_back(NULL);
    else pre_piece(in, out1);
    for(i = out1->begin(); i != out1->end(); i++)
    {
    	if(*i != NULL)
    	{
    		children_piece(*i);
    		post_piece(*i, out2);
    	}
    	else out2->push_back(NULL);
    }
    
    return out2;
}

COMMENT* Transform::transform_comment(COMMENT* in)
{
    if(in == NULL) return NULL;
    
    COMMENT* out;
    
    out = pre_comment(in);
    if(out != NULL)
    {
    	children_comment(out);
    	out = post_comment(out);
    }
    
    return out;
}

UNINTERPRETED* Transform::transform_uninterpreted(UNINTERPRETED* in)
{
    if(in == NULL) return NULL;
    
    UNINTERPRETED* out;
    
    out = pre_uninterpreted(in);
    if(out != NULL)
    {
    	children_uninterpreted(out);
    	out = post_uninterpreted(out);
    }
    
    return out;
}

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

Cond* Transform::transform_cond(Cond* in)
{
    if(in == NULL) return NULL;
    
    Cond* out;
    
    out = pre_cond(in);
    if(out != NULL)
    {
    	children_cond(out);
    	out = post_cond(out);
    }
    
    return out;
}

Zvp* Transform::transform_zvp(Zvp* in)
{
    if(in == NULL) return NULL;
    
    Zvp* out;
    
    out = pre_zvp(in);
    if(out != NULL)
    {
    	children_zvp(out);
    	out = post_zvp(out);
    }
    
    return out;
}

Zvpp* Transform::transform_zvpp(Zvpp* in)
{
    if(in == NULL) return NULL;
    
    Zvpp* out;
    
    out = pre_zvpp(in);
    if(out != NULL)
    {
    	children_zvpp(out);
    	out = post_zvpp(out);
    }
    
    return out;
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
void Transform::pre_piece(Piece* in, Piece_list* out)
{
    switch(in->classid())
    {
    case Method::ID: 
    	{
    		Piece_list* local_out = new Piece_list;
    		Piece_list::const_iterator i;
    		pre_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Block::ID: 
    	{
    		Piece_list* local_out = new Piece_list;
    		Piece_list::const_iterator i;
    		pre_block(dynamic_cast<Block*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case UNINTERPRETED::ID: 
    	out->push_back(pre_uninterpreted(dynamic_cast<UNINTERPRETED*>(in)));
    	return;
    }
    assert(0);
}

void Transform::pre_statement(Statement* in, Statement_list* out)
{
    switch(in->classid())
    {
    case Assign_zvp::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_zvp(dynamic_cast<Assign_zvp*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_zvpp::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_assign_zvpp(dynamic_cast<Assign_zvpp*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Inc_ref::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_inc_ref(dynamic_cast<Inc_ref*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Dec_ref::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_dec_ref(dynamic_cast<Dec_ref*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Destruct::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_destruct(dynamic_cast<Destruct*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Allocate::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_allocate(dynamic_cast<Allocate*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Clone::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_clone(dynamic_cast<Clone*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Separate::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_separate(dynamic_cast<Separate*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case If::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_if(dynamic_cast<If*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case INTRINSIC::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_intrinsic(dynamic_cast<INTRINSIC*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case API_CALL::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_api_call(dynamic_cast<API_CALL*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case CODE::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_code(dynamic_cast<CODE*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Cond* Transform::pre_cond(Cond* in)
{
    switch(in->classid())
    {
    case Is_ref::ID: return pre_is_ref(dynamic_cast<Is_ref*>(in));
    case Equals::ID: return pre_equals(dynamic_cast<Equals*>(in));
    }
    assert(0);
}

Zvp* Transform::pre_zvp(Zvp* in)
{
    switch(in->classid())
    {
    case Deref::ID: return pre_deref(dynamic_cast<Deref*>(in));
    case ZVP::ID: return pre_zvp(dynamic_cast<ZVP*>(in));
    case Null::ID: return pre_null(dynamic_cast<Null*>(in));
    case LITERAL::ID: return pre_literal(dynamic_cast<LITERAL*>(in));
    case Uninitialized::ID: return pre_uninitialized(dynamic_cast<Uninitialized*>(in));
    }
    assert(0);
}

Zvpp* Transform::pre_zvpp(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID: return pre_ref(dynamic_cast<Ref*>(in));
    case ZVPP::ID: return pre_zvpp(dynamic_cast<ZVPP*>(in));
    }
    assert(0);
}

/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
void Transform::post_piece(Piece* in, Piece_list* out)
{
    switch(in->classid())
    {
    case Method::ID: 
    	{
    		Piece_list* local_out = new Piece_list;
    		Piece_list::const_iterator i;
    		post_method(dynamic_cast<Method*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Block::ID: 
    	{
    		Piece_list* local_out = new Piece_list;
    		Piece_list::const_iterator i;
    		post_block(dynamic_cast<Block*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case UNINTERPRETED::ID: 
    	out->push_back(post_uninterpreted(dynamic_cast<UNINTERPRETED*>(in)));
    	return;
    }
    assert(0);
}

void Transform::post_statement(Statement* in, Statement_list* out)
{
    switch(in->classid())
    {
    case Assign_zvp::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_zvp(dynamic_cast<Assign_zvp*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Assign_zvpp::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_assign_zvpp(dynamic_cast<Assign_zvpp*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Inc_ref::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_inc_ref(dynamic_cast<Inc_ref*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Dec_ref::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_dec_ref(dynamic_cast<Dec_ref*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Destruct::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_destruct(dynamic_cast<Destruct*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Allocate::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_allocate(dynamic_cast<Allocate*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Clone::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_clone(dynamic_cast<Clone*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Separate::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_separate(dynamic_cast<Separate*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case If::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_if(dynamic_cast<If*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case INTRINSIC::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_intrinsic(dynamic_cast<INTRINSIC*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case API_CALL::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_api_call(dynamic_cast<API_CALL*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case CODE::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_code(dynamic_cast<CODE*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    }
    assert(0);
}

Cond* Transform::post_cond(Cond* in)
{
    switch(in->classid())
    {
    case Is_ref::ID: return post_is_ref(dynamic_cast<Is_ref*>(in));
    case Equals::ID: return post_equals(dynamic_cast<Equals*>(in));
    }
    assert(0);
}

Zvp* Transform::post_zvp(Zvp* in)
{
    switch(in->classid())
    {
    case Deref::ID: return post_deref(dynamic_cast<Deref*>(in));
    case ZVP::ID: return post_zvp(dynamic_cast<ZVP*>(in));
    case Null::ID: return post_null(dynamic_cast<Null*>(in));
    case LITERAL::ID: return post_literal(dynamic_cast<LITERAL*>(in));
    case Uninitialized::ID: return post_uninitialized(dynamic_cast<Uninitialized*>(in));
    }
    assert(0);
}

Zvpp* Transform::post_zvpp(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID: return post_ref(dynamic_cast<Ref*>(in));
    case ZVPP::ID: return post_zvpp(dynamic_cast<ZVPP*>(in));
    }
    assert(0);
}

/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
void Transform::children_piece(Piece* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	children_method(dynamic_cast<Method*>(in));
    	break;
    case Block::ID:
    	children_block(dynamic_cast<Block*>(in));
    	break;
    case UNINTERPRETED::ID:
    	children_uninterpreted(dynamic_cast<UNINTERPRETED*>(in));
    	break;
    }
}

void Transform::children_statement(Statement* in)
{
    switch(in->classid())
    {
    case Assign_zvp::ID:
    	children_assign_zvp(dynamic_cast<Assign_zvp*>(in));
    	break;
    case Assign_zvpp::ID:
    	children_assign_zvpp(dynamic_cast<Assign_zvpp*>(in));
    	break;
    case Inc_ref::ID:
    	children_inc_ref(dynamic_cast<Inc_ref*>(in));
    	break;
    case Dec_ref::ID:
    	children_dec_ref(dynamic_cast<Dec_ref*>(in));
    	break;
    case Destruct::ID:
    	children_destruct(dynamic_cast<Destruct*>(in));
    	break;
    case Allocate::ID:
    	children_allocate(dynamic_cast<Allocate*>(in));
    	break;
    case Clone::ID:
    	children_clone(dynamic_cast<Clone*>(in));
    	break;
    case Separate::ID:
    	children_separate(dynamic_cast<Separate*>(in));
    	break;
    case If::ID:
    	children_if(dynamic_cast<If*>(in));
    	break;
    case INTRINSIC::ID:
    	children_intrinsic(dynamic_cast<INTRINSIC*>(in));
    	break;
    case API_CALL::ID:
    	children_api_call(dynamic_cast<API_CALL*>(in));
    	break;
    case CODE::ID:
    	children_code(dynamic_cast<CODE*>(in));
    	break;
    }
}

void Transform::children_cond(Cond* in)
{
    switch(in->classid())
    {
    case Is_ref::ID:
    	children_is_ref(dynamic_cast<Is_ref*>(in));
    	break;
    case Equals::ID:
    	children_equals(dynamic_cast<Equals*>(in));
    	break;
    }
}

void Transform::children_zvp(Zvp* in)
{
    switch(in->classid())
    {
    case Deref::ID:
    	children_deref(dynamic_cast<Deref*>(in));
    	break;
    case ZVP::ID:
    	children_zvp(dynamic_cast<ZVP*>(in));
    	break;
    case Null::ID:
    	children_null(dynamic_cast<Null*>(in));
    	break;
    case LITERAL::ID:
    	children_literal(dynamic_cast<LITERAL*>(in));
    	break;
    case Uninitialized::ID:
    	children_uninitialized(dynamic_cast<Uninitialized*>(in));
    	break;
    }
}

void Transform::children_zvpp(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID:
    	children_ref(dynamic_cast<Ref*>(in));
    	break;
    case ZVPP::ID:
    	children_zvpp(dynamic_cast<ZVPP*>(in));
    	break;
    }
}
}

