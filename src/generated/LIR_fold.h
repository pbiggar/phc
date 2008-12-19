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
 class _Declare,
 class _Declare_p,
 class _Deref,
 class _Destruct,
 class _Equals,
 class _Equals_p,
 class _False,
 class _INT,
 class _INTRINSIC,
 class _Identifier,
 class _If,
 class _Inc_ref,
 class _Is_change_on_write,
 class _Is_copy_on_write,
 class _Is_ref,
 class _LITERAL,
 class _Method,
 class _Node,
 class _Not,
 class _Null,
 class _Opt,
 class _Opt_param,
 class _Overwrite,
 class _Piece,
 class _Profile,
 class _Ref,
 class _STRING,
 class _SYMTABLE,
 class _Separate,
 class _Set_is_ref,
 class _Statement,
 class _Symtable_fetch,
 class _Symtable_insert,
 class _True,
 class _UNINTERPRETED,
 class _Uninit,
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
   typedef Fold<_API_CALL, _Action, _Allocate, _Assign_zvp, _Assign_zvpp, _Block, _CODE, _COMMENT, _C_file, _Clone, _Cond, _Dec_ref, _Declare, _Declare_p, _Deref, _Destruct, _Equals, _Equals_p, _False, _INT, _INTRINSIC, _Identifier, _If, _Inc_ref, _Is_change_on_write, _Is_copy_on_write, _Is_ref, _LITERAL, _Method, _Node, _Not, _Null, _Opt, _Opt_param, _Overwrite, _Piece, _Profile, _Ref, _STRING, _SYMTABLE, _Separate, _Set_is_ref, _Statement, _Symtable_fetch, _Symtable_insert, _True, _UNINTERPRETED, _Uninit, _ZVP, _ZVPP, _Zvp, _Zvpp, _List> parent;
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

	virtual _Declare fold_declare(Declare* in)
	{
		_ZVP zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_declare(in, zvp);
	}

	virtual _Declare_p fold_declare_p(Declare_p* in)
	{
		_ZVPP zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_declare_p(in, zvpp);
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

	virtual _Separate fold_separate(Separate* in)
	{
		_Zvpp zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_separate(in, zvpp);
	}

	virtual _Set_is_ref fold_set_is_ref(Set_is_ref* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		_INT _int = 0;
		if(in->_int != NULL) _int = fold_int(in->_int);
		return fold_impl_set_is_ref(in, zvp, _int);
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

	virtual _Overwrite fold_overwrite(Overwrite* in)
	{
		_Zvp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvp(in->lhs);
		_Zvp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvp(in->rhs);
		return fold_impl_overwrite(in, lhs, rhs);
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

	virtual _Equals_p fold_equals_p(Equals_p* in)
	{
		_Zvpp lhs = 0;
		if(in->lhs != NULL) lhs = fold_zvpp(in->lhs);
		_Zvpp rhs = 0;
		if(in->rhs != NULL) rhs = fold_zvpp(in->rhs);
		return fold_impl_equals_p(in, lhs, rhs);
	}

	virtual _Not fold_not(Not* in)
	{
		_Cond cond = 0;
		if(in->cond != NULL) cond = fold_cond(in->cond);
		return fold_impl_not(in, cond);
	}

	virtual _Is_change_on_write fold_is_change_on_write(Is_change_on_write* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_is_change_on_write(in, zvp);
	}

	virtual _Is_copy_on_write fold_is_copy_on_write(Is_copy_on_write* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_is_copy_on_write(in, zvp);
	}

	virtual _True fold_true(True* in)
	{
		return fold_impl_true(in);
	}

	virtual _False fold_false(False* in)
	{
		return fold_impl_false(in);
	}

	virtual _Uninit fold_uninit(Uninit* in)
	{
		return fold_impl_uninit(in);
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

	virtual _Clone fold_clone(Clone* in)
	{
		_Zvp zvp = 0;
		if(in->zvp != NULL) zvp = fold_zvp(in->zvp);
		return fold_impl_clone(in, zvp);
	}

	virtual _Symtable_fetch fold_symtable_fetch(Symtable_fetch* in)
	{
		_SYMTABLE symtable = 0;
		if(in->symtable != NULL) symtable = fold_symtable(in->symtable);
		_STRING name = 0;
		if(in->name != NULL) name = fold_string(in->name);
		_ZVPP zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_symtable_fetch(in, symtable, name, zvpp);
	}

	virtual _Symtable_insert fold_symtable_insert(Symtable_insert* in)
	{
		_SYMTABLE symtable = 0;
		if(in->symtable != NULL) symtable = fold_symtable(in->symtable);
		_STRING name = 0;
		if(in->name != NULL) name = fold_string(in->name);
		_ZVPP zvpp = 0;
		if(in->zvpp != NULL) zvpp = fold_zvpp(in->zvpp);
		return fold_impl_symtable_insert(in, symtable, name, zvpp);
	}

	virtual _Opt fold_opt(Opt* in)
	{
		_Opt_param param = 0;
		if(in->param != NULL) param = fold_opt_param(in->param);
		_STRING value = 0;
		if(in->value != NULL) value = fold_string(in->value);
		return fold_impl_opt(in, param, value);
	}

	virtual _Profile fold_profile(Profile* in)
	{
		_STRING name = 0;
		if(in->name != NULL) name = fold_string(in->name);
		return fold_impl_profile(in, name);
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
	virtual _Declare fold_impl_declare(Declare* orig, _ZVP zvp) { assert(0); };
	virtual _Declare_p fold_impl_declare_p(Declare_p* orig, _ZVPP zvpp) { assert(0); };
	virtual _Inc_ref fold_impl_inc_ref(Inc_ref* orig, _Zvp zvp) { assert(0); };
	virtual _Allocate fold_impl_allocate(Allocate* orig, _Zvp zvp) { assert(0); };
	virtual _Separate fold_impl_separate(Separate* orig, _Zvpp zvpp) { assert(0); };
	virtual _Set_is_ref fold_impl_set_is_ref(Set_is_ref* orig, _Zvp zvp, _INT _int) { assert(0); };
	virtual _Dec_ref fold_impl_dec_ref(Dec_ref* orig, _Zvp zvp) { assert(0); };
	virtual _Destruct fold_impl_destruct(Destruct* orig, _Zvpp zvpp) { assert(0); };
	virtual _Overwrite fold_impl_overwrite(Overwrite* orig, _Zvp lhs, _Zvp rhs) { assert(0); };
	virtual _Is_ref fold_impl_is_ref(Is_ref* orig, _Zvp zvp) { assert(0); };
	virtual _Equals fold_impl_equals(Equals* orig, _Zvp lhs, _Zvp rhs) { assert(0); };
	virtual _Equals_p fold_impl_equals_p(Equals_p* orig, _Zvpp lhs, _Zvpp rhs) { assert(0); };
	virtual _Not fold_impl_not(Not* orig, _Cond cond) { assert(0); };
	virtual _Is_change_on_write fold_impl_is_change_on_write(Is_change_on_write* orig, _Zvp zvp) { assert(0); };
	virtual _Is_copy_on_write fold_impl_is_copy_on_write(Is_copy_on_write* orig, _Zvp zvp) { assert(0); };
	virtual _True fold_impl_true(True* orig) { assert(0); };
	virtual _False fold_impl_false(False* orig) { assert(0); };
	virtual _Uninit fold_impl_uninit(Uninit* orig) { assert(0); };
	virtual _Null fold_impl_null(Null* orig) { assert(0); };
	virtual _Deref fold_impl_deref(Deref* orig, _Zvpp zvpp) { assert(0); };
	virtual _Ref fold_impl_ref(Ref* orig, _Zvp zvp) { assert(0); };
	virtual _Clone fold_impl_clone(Clone* orig, _Zvp zvp) { assert(0); };
	virtual _Symtable_fetch fold_impl_symtable_fetch(Symtable_fetch* orig, _SYMTABLE symtable, _STRING name, _ZVPP zvpp) { assert(0); };
	virtual _Symtable_insert fold_impl_symtable_insert(Symtable_insert* orig, _SYMTABLE symtable, _STRING name, _ZVPP zvpp) { assert(0); };
	virtual _Opt fold_impl_opt(Opt* orig, _Opt_param param, _STRING value) { assert(0); };
	virtual _Profile fold_impl_profile(Profile* orig, _STRING name) { assert(0); };

	virtual _INT fold_int(INT* orig) { assert(0); };
	virtual _UNINTERPRETED fold_uninterpreted(UNINTERPRETED* orig) { assert(0); };
	virtual _COMMENT fold_comment(COMMENT* orig) { assert(0); };
	virtual _INTRINSIC fold_intrinsic(INTRINSIC* orig) { assert(0); };
	virtual _API_CALL fold_api_call(API_CALL* orig) { assert(0); };
	virtual _CODE fold_code(CODE* orig) { assert(0); };
	virtual _ZVP fold_zvp(ZVP* orig) { assert(0); };
	virtual _ZVPP fold_zvpp(ZVPP* orig) { assert(0); };
	virtual _LITERAL fold_literal(LITERAL* orig) { assert(0); };
	virtual _SYMTABLE fold_symtable(SYMTABLE* orig) { assert(0); };
	virtual _STRING fold_string(STRING* orig) { assert(0); };


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
			case Declare::ID:
				return fold_declare(dynamic_cast<Declare*>(in));
			case Declare_p::ID:
				return fold_declare_p(dynamic_cast<Declare_p*>(in));
			case Inc_ref::ID:
				return fold_inc_ref(dynamic_cast<Inc_ref*>(in));
			case Dec_ref::ID:
				return fold_dec_ref(dynamic_cast<Dec_ref*>(in));
			case Set_is_ref::ID:
				return fold_set_is_ref(dynamic_cast<Set_is_ref*>(in));
			case Destruct::ID:
				return fold_destruct(dynamic_cast<Destruct*>(in));
			case Allocate::ID:
				return fold_allocate(dynamic_cast<Allocate*>(in));
			case Overwrite::ID:
				return fold_overwrite(dynamic_cast<Overwrite*>(in));
			case Separate::ID:
				return fold_separate(dynamic_cast<Separate*>(in));
			case Symtable_fetch::ID:
				return fold_symtable_fetch(dynamic_cast<Symtable_fetch*>(in));
			case Symtable_insert::ID:
				return fold_symtable_insert(dynamic_cast<Symtable_insert*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case Opt::ID:
				return fold_opt(dynamic_cast<Opt*>(in));
			case INTRINSIC::ID:
				return fold_intrinsic(dynamic_cast<INTRINSIC*>(in));
			case API_CALL::ID:
				return fold_api_call(dynamic_cast<API_CALL*>(in));
			case CODE::ID:
				return fold_code(dynamic_cast<CODE*>(in));
			case Profile::ID:
				return fold_profile(dynamic_cast<Profile*>(in));
			case Is_ref::ID:
				return fold_is_ref(dynamic_cast<Is_ref*>(in));
			case Equals::ID:
				return fold_equals(dynamic_cast<Equals*>(in));
			case Equals_p::ID:
				return fold_equals_p(dynamic_cast<Equals_p*>(in));
			case Not::ID:
				return fold_not(dynamic_cast<Not*>(in));
			case Is_copy_on_write::ID:
				return fold_is_copy_on_write(dynamic_cast<Is_copy_on_write*>(in));
			case Is_change_on_write::ID:
				return fold_is_change_on_write(dynamic_cast<Is_change_on_write*>(in));
			case True::ID:
				return fold_true(dynamic_cast<True*>(in));
			case False::ID:
				return fold_false(dynamic_cast<False*>(in));
			case Deref::ID:
				return fold_deref(dynamic_cast<Deref*>(in));
			case ZVP::ID:
				return fold_zvp(dynamic_cast<ZVP*>(in));
			case Null::ID:
				return fold_null(dynamic_cast<Null*>(in));
			case LITERAL::ID:
				return fold_literal(dynamic_cast<LITERAL*>(in));
			case Uninit::ID:
				return fold_uninit(dynamic_cast<Uninit*>(in));
			case Clone::ID:
				return fold_clone(dynamic_cast<Clone*>(in));
			case Ref::ID:
				return fold_ref(dynamic_cast<Ref*>(in));
			case ZVPP::ID:
				return fold_zvpp(dynamic_cast<ZVPP*>(in));
			case SYMTABLE::ID:
				return fold_symtable(dynamic_cast<SYMTABLE*>(in));
			case COMMENT::ID:
				return fold_comment(dynamic_cast<COMMENT*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
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
			case Declare::ID:
				return fold_declare(dynamic_cast<Declare*>(in));
			case Declare_p::ID:
				return fold_declare_p(dynamic_cast<Declare_p*>(in));
			case Inc_ref::ID:
				return fold_inc_ref(dynamic_cast<Inc_ref*>(in));
			case Dec_ref::ID:
				return fold_dec_ref(dynamic_cast<Dec_ref*>(in));
			case Set_is_ref::ID:
				return fold_set_is_ref(dynamic_cast<Set_is_ref*>(in));
			case Destruct::ID:
				return fold_destruct(dynamic_cast<Destruct*>(in));
			case Allocate::ID:
				return fold_allocate(dynamic_cast<Allocate*>(in));
			case Overwrite::ID:
				return fold_overwrite(dynamic_cast<Overwrite*>(in));
			case Separate::ID:
				return fold_separate(dynamic_cast<Separate*>(in));
			case Symtable_fetch::ID:
				return fold_symtable_fetch(dynamic_cast<Symtable_fetch*>(in));
			case Symtable_insert::ID:
				return fold_symtable_insert(dynamic_cast<Symtable_insert*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case Opt::ID:
				return fold_opt(dynamic_cast<Opt*>(in));
			case INTRINSIC::ID:
				return fold_intrinsic(dynamic_cast<INTRINSIC*>(in));
			case API_CALL::ID:
				return fold_api_call(dynamic_cast<API_CALL*>(in));
			case CODE::ID:
				return fold_code(dynamic_cast<CODE*>(in));
			case Profile::ID:
				return fold_profile(dynamic_cast<Profile*>(in));
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
			case Declare::ID:
				return fold_declare(dynamic_cast<Declare*>(in));
			case Declare_p::ID:
				return fold_declare_p(dynamic_cast<Declare_p*>(in));
			case Inc_ref::ID:
				return fold_inc_ref(dynamic_cast<Inc_ref*>(in));
			case Dec_ref::ID:
				return fold_dec_ref(dynamic_cast<Dec_ref*>(in));
			case Set_is_ref::ID:
				return fold_set_is_ref(dynamic_cast<Set_is_ref*>(in));
			case Destruct::ID:
				return fold_destruct(dynamic_cast<Destruct*>(in));
			case Allocate::ID:
				return fold_allocate(dynamic_cast<Allocate*>(in));
			case Overwrite::ID:
				return fold_overwrite(dynamic_cast<Overwrite*>(in));
			case Separate::ID:
				return fold_separate(dynamic_cast<Separate*>(in));
			case Symtable_fetch::ID:
				return fold_symtable_fetch(dynamic_cast<Symtable_fetch*>(in));
			case Symtable_insert::ID:
				return fold_symtable_insert(dynamic_cast<Symtable_insert*>(in));
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
			case Equals_p::ID:
				return fold_equals_p(dynamic_cast<Equals_p*>(in));
			case Not::ID:
				return fold_not(dynamic_cast<Not*>(in));
			case Is_copy_on_write::ID:
				return fold_is_copy_on_write(dynamic_cast<Is_copy_on_write*>(in));
			case Is_change_on_write::ID:
				return fold_is_change_on_write(dynamic_cast<Is_change_on_write*>(in));
			case True::ID:
				return fold_true(dynamic_cast<True*>(in));
			case False::ID:
				return fold_false(dynamic_cast<False*>(in));
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
			case Uninit::ID:
				return fold_uninit(dynamic_cast<Uninit*>(in));
			case Clone::ID:
				return fold_clone(dynamic_cast<Clone*>(in));
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
			case Null::ID:
				return fold_null(dynamic_cast<Null*>(in));
		}
		assert(0);
	}

	virtual _Identifier fold_identifier(Identifier* in)
	{
		switch(in->classid())
		{
			case ZVPP::ID:
				return fold_zvpp(dynamic_cast<ZVPP*>(in));
			case ZVP::ID:
				return fold_zvp(dynamic_cast<ZVP*>(in));
			case SYMTABLE::ID:
				return fold_symtable(dynamic_cast<SYMTABLE*>(in));
			case LITERAL::ID:
				return fold_literal(dynamic_cast<LITERAL*>(in));
			case UNINTERPRETED::ID:
				return fold_uninterpreted(dynamic_cast<UNINTERPRETED*>(in));
			case COMMENT::ID:
				return fold_comment(dynamic_cast<COMMENT*>(in));
			case CODE::ID:
				return fold_code(dynamic_cast<CODE*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
		}
		assert(0);
	}

	virtual _Opt_param fold_opt_param(Opt_param* in)
	{
		switch(in->classid())
		{
			case ZVPP::ID:
				return fold_zvpp(dynamic_cast<ZVPP*>(in));
			case ZVP::ID:
				return fold_zvp(dynamic_cast<ZVP*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T, template <class _Tp, class _Alloc = typename List<_Tp>::allocator_type> class _List>
class Uniform_fold : public Fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, _List> {};
}

