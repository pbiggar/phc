#include <iostream>
#include <sstream>
#include <iomanip>
#include "boost/lexical_cast.hpp"
#include "lib/error.h"
#include "lib/Object.h"
#include "lib/List.h"
#include "lib/String.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/AttrMap.h"
#include "process_ir/IR.h"
#include "process_lir/LIR_PHP_script_hack.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "LIR.h"
namespace LIR{
template
<class _API_CALL,
 class _Action,
 class _Allocate,
 class _Assign_zvp,
 class _Assign_zvpp,
 class _Block,
 class _CODE,
 class _COMMENT,
 class _C_file,
 class _Clone,
 class _Cond,
 class _Dec_ref,
 class _Deref,
 class _Destruct,
 class _Equals,
 class _INTRINSIC,
 class _If,
 class _Inc_ref,
 class _Is_ref,
 class _LITERAL,
 class _Method,
 class _Node,
 class _Not_equals,
 class _Null,
 class _Piece,
 class _Ref,
 class _Separate,
 class _Statement,
 class _UNINTERPRETED,
 class _Uninitialized,
 class _ZVP,
 class _ZVPP,
 class _Zvp,
 class _Zvpp,
 template <typename _Tp, typename _Alloc = typename List<_Tp>::allocator_type> class _List = List
>
class Fold
{
// Access this class from subclasses without copying out the template instantiation
public:
   typedef Fold<_API_CALL, _Action, _Allocate, _Assign_zvp, _Assign_zvpp, _Block, _CODE, _COMMENT, _C_file, _Clone, _Cond, _Dec_ref, _Deref, _Destruct, _Equals, _INTRINSIC, _If, _Inc_ref, _Is_ref, _LITERAL, _Method, _Node, _Not_equals, _Null, _Piece, _Ref, _Separate, _Statement, _UNINTERPRETED, _Uninitialized, _ZVP, _ZVPP, _Zvp, _Zvpp, _List> parent;
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _C_file fold_c_file(C_file* in)
	{
		_List<_Piece>* pieces = 0;
	
		{
			pieces = new _List<_Piece>;
			typename _List<Piece*>::const_iterator i;
			for(i = in->pieces->begin(); i != in->pieces->end(); i++)
				if(*i != NULL) pieces->push_back(fold_piece(*i));
				else pieces->push_back(0);
		}
		return fold_impl_c_file(in, pieces);
	}

	virtual _Method fold_method(Method* in)
	{
		_COMMENT comment = 0;
		if(in->comment != NULL) comment = fold_comment(in->comment);
		_UNINTERPRETED entry = 0;
		if(in->entry != NULL) entry = fold_uninterpreted(in->entry);
		_List<_Piece>* pieces = 0;
	
		{
			pieces = new _List<_Piece>;
			typename _List<Piece*>::const_iterator i;
			for(i = in->pieces->begin(); i != in->pieces->end(); i++)
				if(*i != NULL) pieces->push_back(fold_piece(*i));
				else pieces->push_back(0);
		}
		_UNINTERPRETED exit = 0;
		if(in->exit != NULL) exit = fold_uninterpreted(in->exit);
		return fold_impl_method(in, comment, entry, pieces, exit);
	}

	virtual _Block fold_block(Block* in)
	{
		_COMMENT comment = 0;
		if(in->comment != NULL) comment = fold_comment(in->comment);
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_block(in, comment, statements);
	}

	virtual _If fold_if(If* in)
	{
		_Cond cond = 0;
		if(in->cond != NULL) cond = fold_cond(in->cond);
		_List<_Statement>* iftrue = 0;
	
		{
			iftrue = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->iftrue->begin(); i != in->iftrue->end(); i++)
				if(*i != NULL) iftrue->push_back(fold_statement(*i));
				else iftrue->push_back(0);
		}
		_List<_Statement>* iffalse = 0;
	
		{
			iffalse = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->iffalse->begin(); i != in->iffalse->end(); i++)
				if(*i != NULL) iffalse->push_back(fold_statement(*i));
				else iffalse->push_back(0);
		}
		return fold_impl_if(in, cond, iftrue, iffalse);
	}

	virtual _Assign_zvp fold_assign_zvp(Assign_zvp* in)
	{
		_Zvp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvp(in->lhs);
		_Zvp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvp(in->rhs);
		return fold_impl_assign_zvp(in, lhs, rhs);
	}

	virtual _Assign_zvpp fold_assign_zvpp(Assign_zvpp* in)
	{
		_Zvpp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvpp(in->lhs);
		_Zvpp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvpp(in->rhs);
		return fold_impl_assign_zvpp(in, lhs, rhs);
	}

	virtual _Inc_ref fold_inc_ref(Inc_ref* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_inc_ref(in, zvp);
	}

	virtual _Allocate fold_allocate(Allocate* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_allocate(in, zvp);
	}

	virtual _Clone fold_clone(Clone* in)
	{
		_Zvp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvp(in->lhs);
		_Zvp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvp(in->rhs);
		return fold_impl_clone(in, lhs, rhs);
	}

	virtual _Separate fold_separate(Separate* in)
	{
		_Zvpp zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_separate(in, zvpp);
	}

	virtual _Dec_ref fold_dec_ref(Dec_ref* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_dec_ref(in, zvp);
	}

	virtual _Destruct fold_destruct(Destruct* in)
	{
		_Zvpp zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_destruct(in, zvpp);
	}

	virtual _Is_ref fold_is_ref(Is_ref* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_is_ref(in, zvp);
	}

	virtual _Equals fold_equals(Equals* in)
	{
		_Zvp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvp(in->lhs);
		_Zvp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvp(in->rhs);
		return fold_impl_equals(in, lhs, rhs);
	}

	virtual _Not_equals fold_not_equals(Not_equals* in)
	{
		_Zvp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvp(in->lhs);
		_Zvp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvp(in->rhs);
		return fold_impl_not_equals(in, lhs, rhs);
	}

	virtual _Uninitialized fold_uninitialized(Uninitialized* in)
	{
		return fold_impl_uninitialized(in);
	}

	virtual _Null fold_null(Null* in)
	{
		return fold_impl_null(in);
	}

	virtual _Deref fold_deref(Deref* in)
	{
		_Zvpp zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_deref(in, zvpp);
	}

	virtual _Ref fold_ref(Ref* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_ref(in, zvp);
	}



// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _C_file fold_impl_c_file(C_file* orig, _List<_Piece>* pieces) { assert(0); };
	virtual _Method fold_impl_method(Method* orig, _COMMENT comment, _UNINTERPRETED entry, _List<_Piece>* pieces, _UNINTERPRETED exit) { assert(0); };
	virtual _Block fold_impl_block(Block* orig, _COMMENT comment, _List<_Statement>* statements) { assert(0); };
	virtual _If fold_impl_if(If* orig, _Cond cond, _List<_Statement>* iftrue, _List<_Statement>* iffalse) { assert(0); };
	virtual _Assign_zvp fold_impl_assign_zvp(Assign_zvp* orig, _Zvp lhs, _Zvp rhs) { assert(0); };
	virtual _Assign_zvpp fold_impl_assign_zvpp(Assign_zvpp* orig, _Zvpp lhs, _Zvpp rhs) { assert(0); };
	virtual _Inc_ref fold_impl_inc_ref(Inc_ref* orig, _Zvp zvp) { assert(0); };
	virtual _Allocate fold_impl_allocate(Allocate* orig, _Zvp zvp) { assert(0); };
	virtual _Clone fold_impl_clone(Clone* orig, _Zvp lhs, _Zvp rhs) { assert(0); };
	virtual _Separate fold_impl_separate(Separate* orig, _Zvpp zvpp) { assert(0); };
	virtual _Dec_ref fold_impl_dec_ref(Dec_ref* orig, _Zvp zvp) { assert(0); };
	virtual _Destruct fold_impl_destruct(Destruct* orig, _Zvpp zvpp) { assert(0); };
	virtual _Is_ref fold_impl_is_ref(Is_ref* orig, _Zvp zvp) { assert(0); };
	virtual _Equals fold_impl_equals(Equals* orig, _Zvp lhs, _Zvp rhs) { assert(0); };
	virtual _Not_equals fold_impl_not_equals(Not_equals* orig, _Zvp lhs, _Zvp rhs) { assert(0); };
	virtual _Uninitialized fold_impl_uninitialized(Uninitialized* orig) { assert(0); };
	virtual _Null fold_impl_null(Null* orig) { assert(0); };
	virtual _Deref fold_impl_deref(Deref* orig, _Zvpp zvpp) { assert(0); };
	virtual _Ref fold_impl_ref(Ref* orig, _Zvp zvp) { assert(0); };

	virtual _COMMENT fold_comment(COMMENT* orig) { assert(0); };
	virtual _UNINTERPRETED fold_uninterpreted(UNINTERPRETED* orig) { assert(0); };
	virtual _INTRINSIC fold_intrinsic(INTRINSIC* orig) { assert(0); };
	virtual _API_CALL fold_api_call(API_CALL* orig) { assert(0); };
	virtual _CODE fold_code(CODE* orig) { assert(0); };
	virtual _ZVP fold_zvp(ZVP* orig) { assert(0); };
	virtual _LITERAL fold_literal(LITERAL* orig) { assert(0); };
	virtual _ZVPP fold_zvpp(ZVPP* orig) { assert(0); };


// Manual dispatching for abstract classes
// Override only if you know what you are doing!
	virtual _Node fold_node(Node* in)
	{
		switch(in->classid())
		{
			case C_file::ID:
				return fold_c_file(dynamic_cast<C_file*>(in));
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Block::ID:
				return fold_block(dynamic_cast<Block*>(in));
			case UNINTERPRETED::ID:
				return fold_uninterpreted(dynamic_cast<UNINTERPRETED*>(in));
			case Assign_zvp::ID:
				return fold_assign_zvp(dynamic_cast<Assign_zvp*>(in));
			case Assign_zvpp::ID:
				return fold_assign_zvpp(dynamic_cast<Assign_zvpp*>(in));
			case Inc_ref::ID:
				return fold_inc_ref(dynamic_cast<Inc_ref*>(in));
			case Dec_ref::ID:
				return fold_dec_ref(dynamic_cast<Dec_ref*>(in));
			case Destruct::ID:
				return fold_destruct(dynamic_cast<Destruct*>(in));
			case Allocate::ID:
				return fold_allocate(dynamic_cast<Allocate*>(in));
			case Clone::ID:
				return fold_clone(dynamic_cast<Clone*>(in));
			case Separate::ID:
				return fold_separate(dynamic_cast<Separate*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case INTRINSIC::ID:
				return fold_intrinsic(dynamic_cast<INTRINSIC*>(in));
			case API_CALL::ID:
				return fold_api_call(dynamic_cast<API_CALL*>(in));
			case CODE::ID:
				return fold_code(dynamic_cast<CODE*>(in));
			case Is_ref::ID:
				return fold_is_ref(dynamic_cast<Is_ref*>(in));
			case Equals::ID:
				return fold_equals(dynamic_cast<Equals*>(in));
			case Not_equals::ID:
				return fold_not_equals(dynamic_cast<Not_equals*>(in));
			case Deref::ID:
				return fold_deref(dynamic_cast<Deref*>(in));
			case ZVP::ID:
				return fold_zvp(dynamic_cast<ZVP*>(in));
			case Null::ID:
				return fold_null(dynamic_cast<Null*>(in));
			case LITERAL::ID:
				return fold_literal(dynamic_cast<LITERAL*>(in));
			case Uninitialized::ID:
				return fold_uninitialized(dynamic_cast<Uninitialized*>(in));
			case Ref::ID:
				return fold_ref(dynamic_cast<Ref*>(in));
			case ZVPP::ID:
				return fold_zvpp(dynamic_cast<ZVPP*>(in));
			case COMMENT::ID:
				return fold_comment(dynamic_cast<COMMENT*>(in));
		}
		assert(0);
	}

	virtual _Piece fold_piece(Piece* in)
	{
		switch(in->classid())
		{
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Block::ID:
				return fold_block(dynamic_cast<Block*>(in));
			case UNINTERPRETED::ID:
				return fold_uninterpreted(dynamic_cast<UNINTERPRETED*>(in));
		}
		assert(0);
	}

	virtual _Statement fold_statement(Statement* in)
	{
		switch(in->classid())
		{
			case Assign_zvp::ID:
				return fold_assign_zvp(dynamic_cast<Assign_zvp*>(in));
			case Assign_zvpp::ID:
				return fold_assign_zvpp(dynamic_cast<Assign_zvpp*>(in));
			case Inc_ref::ID:
				return fold_inc_ref(dynamic_cast<Inc_ref*>(in));
			case Dec_ref::ID:
				return fold_dec_ref(dynamic_cast<Dec_ref*>(in));
			case Destruct::ID:
				return fold_destruct(dynamic_cast<Destruct*>(in));
			case Allocate::ID:
				return fold_allocate(dynamic_cast<Allocate*>(in));
			case Clone::ID:
				return fold_clone(dynamic_cast<Clone*>(in));
			case Separate::ID:
				return fold_separate(dynamic_cast<Separate*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case INTRINSIC::ID:
				return fold_intrinsic(dynamic_cast<INTRINSIC*>(in));
			case API_CALL::ID:
				return fold_api_call(dynamic_cast<API_CALL*>(in));
			case CODE::ID:
				return fold_code(dynamic_cast<CODE*>(in));
		}
		assert(0);
	}

	virtual _Action fold_action(Action* in)
	{
		switch(in->classid())
		{
			case Assign_zvp::ID:
				return fold_assign_zvp(dynamic_cast<Assign_zvp*>(in));
			case Assign_zvpp::ID:
				return fold_assign_zvpp(dynamic_cast<Assign_zvpp*>(in));
			case Inc_ref::ID:
				return fold_inc_ref(dynamic_cast<Inc_ref*>(in));
			case Dec_ref::ID:
				return fold_dec_ref(dynamic_cast<Dec_ref*>(in));
			case Destruct::ID:
				return fold_destruct(dynamic_cast<Destruct*>(in));
			case Allocate::ID:
				return fold_allocate(dynamic_cast<Allocate*>(in));
			case Clone::ID:
				return fold_clone(dynamic_cast<Clone*>(in));
			case Separate::ID:
				return fold_separate(dynamic_cast<Separate*>(in));
		}
		assert(0);
	}

	virtual _Cond fold_cond(Cond* in)
	{
		switch(in->classid())
		{
			case Is_ref::ID:
				return fold_is_ref(dynamic_cast<Is_ref*>(in));
			case Equals::ID:
				return fold_equals(dynamic_cast<Equals*>(in));
			case Not_equals::ID:
				return fold_not_equals(dynamic_cast<Not_equals*>(in));
		}
		assert(0);
	}

	virtual _Zvp fold_zvp(Zvp* in)
	{
		switch(in->classid())
		{
			case Deref::ID:
				return fold_deref(dynamic_cast<Deref*>(in));
			case ZVP::ID:
				return fold_zvp(dynamic_cast<ZVP*>(in));
			case Null::ID:
				return fold_null(dynamic_cast<Null*>(in));
			case LITERAL::ID:
				return fold_literal(dynamic_cast<LITERAL*>(in));
			case Uninitialized::ID:
				return fold_uninitialized(dynamic_cast<Uninitialized*>(in));
		}
		assert(0);
	}

	virtual _Zvpp fold_zvpp(Zvpp* in)
	{
		switch(in->classid())
		{
			case Ref::ID:
				return fold_ref(dynamic_cast<Ref*>(in));
			case ZVPP::ID:
				return fold_zvpp(dynamic_cast<ZVPP*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T, template <class _Tp, class _Alloc = typename List<_Tp>::allocator_type> class _List>
class Uniform_fold : public Fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, _List> {};
}

