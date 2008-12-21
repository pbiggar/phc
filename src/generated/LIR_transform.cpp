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

void Transform::pre_declare(Declare* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_declare_p(Declare_p* in, Statement_list* out)
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

void Transform::pre_separate(Separate* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_set_is_ref(Set_is_ref* in, Statement_list* out)
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

void Transform::pre_overwrite(Overwrite* in, Statement_list* out)
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

Cond* Transform::pre_equals_p(Equals_p* in)
{
    return in;
}

Cond* Transform::pre_not(Not* in)
{
    return in;
}

Cond* Transform::pre_in_change_on_write(In_change_on_write* in)
{
    return in;
}

Cond* Transform::pre_in_copy_on_write(In_copy_on_write* in)
{
    return in;
}

Cond* Transform::pre_true(True* in)
{
    return in;
}

Cond* Transform::pre_false(False* in)
{
    return in;
}

Zvp* Transform::pre_uninit(Uninit* in)
{
    return in;
}

Null* Transform::pre_null(Null* in)
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

Zvp* Transform::pre_clone(Clone* in)
{
    return in;
}

void Transform::pre_symtable_fetch(Symtable_fetch* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_symtable_insert(Symtable_insert* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_opt(Opt* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::pre_profile(Profile* in, Statement_list* out)
{
    out->push_back(in);
}

INT* Transform::pre_int(INT* in)
{
    return in;
}

UNINTERPRETED* Transform::pre_uninterpreted(UNINTERPRETED* in)
{
    return in;
}

COMMENT* Transform::pre_comment(COMMENT* in)
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

ZVP* Transform::pre_zvp(ZVP* in)
{
    return in;
}

ZVPP* Transform::pre_zvpp(ZVPP* in)
{
    return in;
}

Zvp* Transform::pre_literal(LITERAL* in)
{
    return in;
}

SYMTABLE* Transform::pre_symtable(SYMTABLE* in)
{
    return in;
}

STRING* Transform::pre_string(STRING* in)
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

void Transform::post_declare(Declare* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_declare_p(Declare_p* in, Statement_list* out)
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

void Transform::post_separate(Separate* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_set_is_ref(Set_is_ref* in, Statement_list* out)
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

void Transform::post_overwrite(Overwrite* in, Statement_list* out)
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

Cond* Transform::post_equals_p(Equals_p* in)
{
    return in;
}

Cond* Transform::post_not(Not* in)
{
    return in;
}

Cond* Transform::post_in_change_on_write(In_change_on_write* in)
{
    return in;
}

Cond* Transform::post_in_copy_on_write(In_copy_on_write* in)
{
    return in;
}

Cond* Transform::post_true(True* in)
{
    return in;
}

Cond* Transform::post_false(False* in)
{
    return in;
}

Zvp* Transform::post_uninit(Uninit* in)
{
    return in;
}

Null* Transform::post_null(Null* in)
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

Zvp* Transform::post_clone(Clone* in)
{
    return in;
}

void Transform::post_symtable_fetch(Symtable_fetch* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_symtable_insert(Symtable_insert* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_opt(Opt* in, Statement_list* out)
{
    out->push_back(in);
}

void Transform::post_profile(Profile* in, Statement_list* out)
{
    out->push_back(in);
}

INT* Transform::post_int(INT* in)
{
    return in;
}

UNINTERPRETED* Transform::post_uninterpreted(UNINTERPRETED* in)
{
    return in;
}

COMMENT* Transform::post_comment(COMMENT* in)
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

ZVP* Transform::post_zvp(ZVP* in)
{
    return in;
}

ZVPP* Transform::post_zvpp(ZVPP* in)
{
    return in;
}

Zvp* Transform::post_literal(LITERAL* in)
{
    return in;
}

SYMTABLE* Transform::post_symtable(SYMTABLE* in)
{
    return in;
}

STRING* Transform::post_string(STRING* in)
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
    in->iftrue = transform_statement_list(in->iftrue);
    in->iffalse = transform_statement_list(in->iffalse);
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

void Transform::children_declare(Declare* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_declare_p(Declare_p* in)
{
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_inc_ref(Inc_ref* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_allocate(Allocate* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_separate(Separate* in)
{
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_set_is_ref(Set_is_ref* in)
{
    in->zvp = transform_zvp(in->zvp);
    in->_int = transform_int(in->_int);
}

void Transform::children_dec_ref(Dec_ref* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_destruct(Destruct* in)
{
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_overwrite(Overwrite* in)
{
    in->lhs = transform_zvp(in->lhs);
    in->rhs = transform_zvp(in->rhs);
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

void Transform::children_equals_p(Equals_p* in)
{
    in->lhs = transform_zvpp(in->lhs);
    in->rhs = transform_zvpp(in->rhs);
}

void Transform::children_not(Not* in)
{
    in->cond = transform_cond(in->cond);
}

void Transform::children_in_change_on_write(In_change_on_write* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_in_copy_on_write(In_copy_on_write* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_true(True* in)
{
}

void Transform::children_false(False* in)
{
}

void Transform::children_uninit(Uninit* in)
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

void Transform::children_clone(Clone* in)
{
    in->zvp = transform_zvp(in->zvp);
}

void Transform::children_symtable_fetch(Symtable_fetch* in)
{
    in->symtable = transform_symtable(in->symtable);
    in->name = transform_string(in->name);
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_symtable_insert(Symtable_insert* in)
{
    in->symtable = transform_symtable(in->symtable);
    in->name = transform_string(in->name);
    in->zvpp = transform_zvpp(in->zvpp);
}

void Transform::children_opt(Opt* in)
{
    in->param = transform_opt_param(in->param);
    in->value = transform_string(in->value);
}

void Transform::children_profile(Profile* in)
{
    in->name = transform_string(in->name);
}

/* Tokens don't have children, so these methods do nothing by default */
void Transform::children_int(INT* in)
{
}

void Transform::children_uninterpreted(UNINTERPRETED* in)
{
}

void Transform::children_comment(COMMENT* in)
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

void Transform::children_zvpp(ZVPP* in)
{
}

void Transform::children_literal(LITERAL* in)
{
}

void Transform::children_symtable(SYMTABLE* in)
{
}

void Transform::children_string(STRING* in)
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

ZVP* Transform::transform_zvp(ZVP* in)
{
    if(in == NULL) return NULL;
    
    ZVP* out;
    
    out = pre_zvp(in);
    if(out != NULL)
    {
    	children_zvp(out);
    	out = post_zvp(out);
    }
    
    return out;
}

ZVPP* Transform::transform_zvpp(ZVPP* in)
{
    if(in == NULL) return NULL;
    
    ZVPP* out;
    
    out = pre_zvpp(in);
    if(out != NULL)
    {
    	children_zvpp(out);
    	out = post_zvpp(out);
    }
    
    return out;
}

INT* Transform::transform_int(INT* in)
{
    if(in == NULL) return NULL;
    
    INT* out;
    
    out = pre_int(in);
    if(out != NULL)
    {
    	children_int(out);
    	out = post_int(out);
    }
    
    return out;
}

SYMTABLE* Transform::transform_symtable(SYMTABLE* in)
{
    if(in == NULL) return NULL;
    
    SYMTABLE* out;
    
    out = pre_symtable(in);
    if(out != NULL)
    {
    	children_symtable(out);
    	out = post_symtable(out);
    }
    
    return out;
}

STRING* Transform::transform_string(STRING* in)
{
    if(in == NULL) return NULL;
    
    STRING* out;
    
    out = pre_string(in);
    if(out != NULL)
    {
    	children_string(out);
    	out = post_string(out);
    }
    
    return out;
}

Opt_param* Transform::transform_opt_param(Opt_param* in)
{
    if(in == NULL) return NULL;
    
    Opt_param* out;
    
    out = pre_opt_param(in);
    if(out != NULL)
    {
    	children_opt_param(out);
    	out = post_opt_param(out);
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
    case Declare::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_declare(dynamic_cast<Declare*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Declare_p::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_declare_p(dynamic_cast<Declare_p*>(in), local_out);
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
    case Set_is_ref::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_set_is_ref(dynamic_cast<Set_is_ref*>(in), local_out);
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
    case Overwrite::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_overwrite(dynamic_cast<Overwrite*>(in), local_out);
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
    case Symtable_fetch::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_symtable_fetch(dynamic_cast<Symtable_fetch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Symtable_insert::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_symtable_insert(dynamic_cast<Symtable_insert*>(in), local_out);
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
    case Opt::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_opt(dynamic_cast<Opt*>(in), local_out);
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
    case Profile::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		pre_profile(dynamic_cast<Profile*>(in), local_out);
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
    case Equals_p::ID: return pre_equals_p(dynamic_cast<Equals_p*>(in));
    case Not::ID: return pre_not(dynamic_cast<Not*>(in));
    case In_copy_on_write::ID: return pre_in_copy_on_write(dynamic_cast<In_copy_on_write*>(in));
    case In_change_on_write::ID: return pre_in_change_on_write(dynamic_cast<In_change_on_write*>(in));
    case True::ID: return pre_true(dynamic_cast<True*>(in));
    case False::ID: return pre_false(dynamic_cast<False*>(in));
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
    case Uninit::ID: return pre_uninit(dynamic_cast<Uninit*>(in));
    case Clone::ID: return pre_clone(dynamic_cast<Clone*>(in));
    }
    assert(0);
}

Zvpp* Transform::pre_zvpp(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID: return pre_ref(dynamic_cast<Ref*>(in));
    case ZVPP::ID: return pre_zvpp(dynamic_cast<ZVPP*>(in));
    case Null::ID: return pre_null(dynamic_cast<Null*>(in));
    }
    assert(0);
}

Opt_param* Transform::pre_opt_param(Opt_param* in)
{
    switch(in->classid())
    {
    case ZVPP::ID: return pre_zvpp(dynamic_cast<ZVPP*>(in));
    case ZVP::ID: return pre_zvp(dynamic_cast<ZVP*>(in));
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
    case Declare::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_declare(dynamic_cast<Declare*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Declare_p::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_declare_p(dynamic_cast<Declare_p*>(in), local_out);
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
    case Set_is_ref::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_set_is_ref(dynamic_cast<Set_is_ref*>(in), local_out);
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
    case Overwrite::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_overwrite(dynamic_cast<Overwrite*>(in), local_out);
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
    case Symtable_fetch::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_symtable_fetch(dynamic_cast<Symtable_fetch*>(in), local_out);
    		for(i = local_out->begin(); i != local_out->end(); i++)
    			out->push_back(*i);
    	}
    	return;
    case Symtable_insert::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_symtable_insert(dynamic_cast<Symtable_insert*>(in), local_out);
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
    case Opt::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_opt(dynamic_cast<Opt*>(in), local_out);
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
    case Profile::ID: 
    	{
    		Statement_list* local_out = new Statement_list;
    		Statement_list::const_iterator i;
    		post_profile(dynamic_cast<Profile*>(in), local_out);
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
    case Equals_p::ID: return post_equals_p(dynamic_cast<Equals_p*>(in));
    case Not::ID: return post_not(dynamic_cast<Not*>(in));
    case In_copy_on_write::ID: return post_in_copy_on_write(dynamic_cast<In_copy_on_write*>(in));
    case In_change_on_write::ID: return post_in_change_on_write(dynamic_cast<In_change_on_write*>(in));
    case True::ID: return post_true(dynamic_cast<True*>(in));
    case False::ID: return post_false(dynamic_cast<False*>(in));
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
    case Uninit::ID: return post_uninit(dynamic_cast<Uninit*>(in));
    case Clone::ID: return post_clone(dynamic_cast<Clone*>(in));
    }
    assert(0);
}

Zvpp* Transform::post_zvpp(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID: return post_ref(dynamic_cast<Ref*>(in));
    case ZVPP::ID: return post_zvpp(dynamic_cast<ZVPP*>(in));
    case Null::ID: return post_null(dynamic_cast<Null*>(in));
    }
    assert(0);
}

Opt_param* Transform::post_opt_param(Opt_param* in)
{
    switch(in->classid())
    {
    case ZVPP::ID: return post_zvpp(dynamic_cast<ZVPP*>(in));
    case ZVP::ID: return post_zvp(dynamic_cast<ZVP*>(in));
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
    case Declare::ID:
    	children_declare(dynamic_cast<Declare*>(in));
    	break;
    case Declare_p::ID:
    	children_declare_p(dynamic_cast<Declare_p*>(in));
    	break;
    case Inc_ref::ID:
    	children_inc_ref(dynamic_cast<Inc_ref*>(in));
    	break;
    case Dec_ref::ID:
    	children_dec_ref(dynamic_cast<Dec_ref*>(in));
    	break;
    case Set_is_ref::ID:
    	children_set_is_ref(dynamic_cast<Set_is_ref*>(in));
    	break;
    case Destruct::ID:
    	children_destruct(dynamic_cast<Destruct*>(in));
    	break;
    case Allocate::ID:
    	children_allocate(dynamic_cast<Allocate*>(in));
    	break;
    case Overwrite::ID:
    	children_overwrite(dynamic_cast<Overwrite*>(in));
    	break;
    case Separate::ID:
    	children_separate(dynamic_cast<Separate*>(in));
    	break;
    case Symtable_fetch::ID:
    	children_symtable_fetch(dynamic_cast<Symtable_fetch*>(in));
    	break;
    case Symtable_insert::ID:
    	children_symtable_insert(dynamic_cast<Symtable_insert*>(in));
    	break;
    case If::ID:
    	children_if(dynamic_cast<If*>(in));
    	break;
    case Opt::ID:
    	children_opt(dynamic_cast<Opt*>(in));
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
    case Profile::ID:
    	children_profile(dynamic_cast<Profile*>(in));
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
    case Equals_p::ID:
    	children_equals_p(dynamic_cast<Equals_p*>(in));
    	break;
    case Not::ID:
    	children_not(dynamic_cast<Not*>(in));
    	break;
    case In_copy_on_write::ID:
    	children_in_copy_on_write(dynamic_cast<In_copy_on_write*>(in));
    	break;
    case In_change_on_write::ID:
    	children_in_change_on_write(dynamic_cast<In_change_on_write*>(in));
    	break;
    case True::ID:
    	children_true(dynamic_cast<True*>(in));
    	break;
    case False::ID:
    	children_false(dynamic_cast<False*>(in));
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
    case Uninit::ID:
    	children_uninit(dynamic_cast<Uninit*>(in));
    	break;
    case Clone::ID:
    	children_clone(dynamic_cast<Clone*>(in));
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
    case Null::ID:
    	children_null(dynamic_cast<Null*>(in));
    	break;
    }
}

void Transform::children_opt_param(Opt_param* in)
{
    switch(in->classid())
    {
    case ZVPP::ID:
    	children_zvpp(dynamic_cast<ZVPP*>(in));
    	break;
    case ZVP::ID:
    	children_zvp(dynamic_cast<ZVP*>(in));
    	break;
    }
}
}

