#ifndef _LIR_TRANSFORM_H_
#define _LIR_TRANSFORM_H_

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
class Transform
{
public:
    virtual ~Transform();
/* Invoked before the children are transformed */
public:
    virtual C_file* pre_c_file(C_file* in);
    virtual void pre_method(Method* in, Piece_list* out);
    virtual void pre_block(Block* in, Piece_list* out);
    virtual void pre_if(If* in, Statement_list* out);
    virtual void pre_assign_zvp(Assign_zvp* in, Statement_list* out);
    virtual void pre_assign_zvpp(Assign_zvpp* in, Statement_list* out);
    virtual void pre_declare(Declare* in, Statement_list* out);
    virtual void pre_declare_p(Declare_p* in, Statement_list* out);
    virtual void pre_inc_ref(Inc_ref* in, Statement_list* out);
    virtual void pre_allocate(Allocate* in, Statement_list* out);
    virtual void pre_separate(Separate* in, Statement_list* out);
    virtual void pre_set_is_ref(Set_is_ref* in, Statement_list* out);
    virtual void pre_dec_ref(Dec_ref* in, Statement_list* out);
    virtual void pre_destruct(Destruct* in, Statement_list* out);
    virtual void pre_overwrite(Overwrite* in, Statement_list* out);
    virtual Cond* pre_is_ref(Is_ref* in);
    virtual Cond* pre_equals(Equals* in);
    virtual Cond* pre_equals_p(Equals_p* in);
    virtual Cond* pre_not(Not* in);
    virtual Cond* pre_is_change_on_write(Is_change_on_write* in);
    virtual Cond* pre_is_copy_on_write(Is_copy_on_write* in);
    virtual Zvp* pre_uninit(Uninit* in);
    virtual Null* pre_null(Null* in);
    virtual Zvp* pre_deref(Deref* in);
    virtual Zvpp* pre_ref(Ref* in);
    virtual Zvp* pre_clone(Clone* in);
    virtual void pre_symtable_fetch(Symtable_fetch* in, Statement_list* out);
    virtual void pre_symtable_insert(Symtable_insert* in, Statement_list* out);
    virtual COMMENT* pre_comment(COMMENT* in);
    virtual INT* pre_int(INT* in);
    virtual SYMTABLE* pre_symtable(SYMTABLE* in);
    virtual STRING* pre_string(STRING* in);
    virtual UNINTERPRETED* pre_uninterpreted(UNINTERPRETED* in);
    virtual void pre_intrinsic(INTRINSIC* in, Statement_list* out);
    virtual void pre_api_call(API_CALL* in, Statement_list* out);
    virtual void pre_code(CODE* in, Statement_list* out);
    virtual ZVP* pre_zvp(ZVP* in);
    virtual ZVPP* pre_zvpp(ZVPP* in);
    virtual Zvp* pre_literal(LITERAL* in);
/* Invoked after the children have been transformed */
public:
    virtual C_file* post_c_file(C_file* in);
    virtual void post_method(Method* in, Piece_list* out);
    virtual void post_block(Block* in, Piece_list* out);
    virtual void post_if(If* in, Statement_list* out);
    virtual void post_assign_zvp(Assign_zvp* in, Statement_list* out);
    virtual void post_assign_zvpp(Assign_zvpp* in, Statement_list* out);
    virtual void post_declare(Declare* in, Statement_list* out);
    virtual void post_declare_p(Declare_p* in, Statement_list* out);
    virtual void post_inc_ref(Inc_ref* in, Statement_list* out);
    virtual void post_allocate(Allocate* in, Statement_list* out);
    virtual void post_separate(Separate* in, Statement_list* out);
    virtual void post_set_is_ref(Set_is_ref* in, Statement_list* out);
    virtual void post_dec_ref(Dec_ref* in, Statement_list* out);
    virtual void post_destruct(Destruct* in, Statement_list* out);
    virtual void post_overwrite(Overwrite* in, Statement_list* out);
    virtual Cond* post_is_ref(Is_ref* in);
    virtual Cond* post_equals(Equals* in);
    virtual Cond* post_equals_p(Equals_p* in);
    virtual Cond* post_not(Not* in);
    virtual Cond* post_is_change_on_write(Is_change_on_write* in);
    virtual Cond* post_is_copy_on_write(Is_copy_on_write* in);
    virtual Zvp* post_uninit(Uninit* in);
    virtual Null* post_null(Null* in);
    virtual Zvp* post_deref(Deref* in);
    virtual Zvpp* post_ref(Ref* in);
    virtual Zvp* post_clone(Clone* in);
    virtual void post_symtable_fetch(Symtable_fetch* in, Statement_list* out);
    virtual void post_symtable_insert(Symtable_insert* in, Statement_list* out);
    virtual COMMENT* post_comment(COMMENT* in);
    virtual INT* post_int(INT* in);
    virtual SYMTABLE* post_symtable(SYMTABLE* in);
    virtual STRING* post_string(STRING* in);
    virtual UNINTERPRETED* post_uninterpreted(UNINTERPRETED* in);
    virtual void post_intrinsic(INTRINSIC* in, Statement_list* out);
    virtual void post_api_call(API_CALL* in, Statement_list* out);
    virtual void post_code(CODE* in, Statement_list* out);
    virtual ZVP* post_zvp(ZVP* in);
    virtual ZVPP* post_zvpp(ZVPP* in);
    virtual Zvp* post_literal(LITERAL* in);
/* Transform the children of the node */
public:
    virtual void children_c_file(C_file* in);
    virtual void children_method(Method* in);
    virtual void children_block(Block* in);
    virtual void children_if(If* in);
    virtual void children_assign_zvp(Assign_zvp* in);
    virtual void children_assign_zvpp(Assign_zvpp* in);
    virtual void children_declare(Declare* in);
    virtual void children_declare_p(Declare_p* in);
    virtual void children_inc_ref(Inc_ref* in);
    virtual void children_allocate(Allocate* in);
    virtual void children_separate(Separate* in);
    virtual void children_set_is_ref(Set_is_ref* in);
    virtual void children_dec_ref(Dec_ref* in);
    virtual void children_destruct(Destruct* in);
    virtual void children_overwrite(Overwrite* in);
    virtual void children_is_ref(Is_ref* in);
    virtual void children_equals(Equals* in);
    virtual void children_equals_p(Equals_p* in);
    virtual void children_not(Not* in);
    virtual void children_is_change_on_write(Is_change_on_write* in);
    virtual void children_is_copy_on_write(Is_copy_on_write* in);
    virtual void children_uninit(Uninit* in);
    virtual void children_null(Null* in);
    virtual void children_deref(Deref* in);
    virtual void children_ref(Ref* in);
    virtual void children_clone(Clone* in);
    virtual void children_symtable_fetch(Symtable_fetch* in);
    virtual void children_symtable_insert(Symtable_insert* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_comment(COMMENT* in);
    virtual void children_int(INT* in);
    virtual void children_symtable(SYMTABLE* in);
    virtual void children_string(STRING* in);
    virtual void children_uninterpreted(UNINTERPRETED* in);
    virtual void children_intrinsic(INTRINSIC* in);
    virtual void children_api_call(API_CALL* in);
    virtual void children_code(CODE* in);
    virtual void children_zvp(ZVP* in);
    virtual void children_zvpp(ZVPP* in);
    virtual void children_literal(LITERAL* in);
/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
public:
    virtual Piece_list* transform_piece_list(Piece_list* in);
    virtual Piece_list* transform_piece(Piece* in);
    virtual COMMENT* transform_comment(COMMENT* in);
    virtual UNINTERPRETED* transform_uninterpreted(UNINTERPRETED* in);
    virtual Statement_list* transform_statement_list(Statement_list* in);
    virtual Statement_list* transform_statement(Statement* in);
    virtual Cond* transform_cond(Cond* in);
    virtual Zvp* transform_zvp(Zvp* in);
    virtual Zvpp* transform_zvpp(Zvpp* in);
    virtual ZVP* transform_zvp(ZVP* in);
    virtual ZVPP* transform_zvpp(ZVPP* in);
    virtual INT* transform_int(INT* in);
    virtual SYMTABLE* transform_symtable(SYMTABLE* in);
    virtual STRING* transform_string(STRING* in);
    virtual C_file* transform_c_file(C_file* in);
/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_piece(Piece* in, Piece_list* out);
    virtual void pre_statement(Statement* in, Statement_list* out);
    virtual Cond* pre_cond(Cond* in);
    virtual Zvp* pre_zvp(Zvp* in);
    virtual Zvpp* pre_zvpp(Zvpp* in);
/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_piece(Piece* in, Piece_list* out);
    virtual void post_statement(Statement* in, Statement_list* out);
    virtual Cond* post_cond(Cond* in);
    virtual Zvp* post_zvp(Zvp* in);
    virtual Zvpp* post_zvpp(Zvpp* in);
/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
public:
    virtual void children_piece(Piece* in);
    virtual void children_statement(Statement* in);
    virtual void children_cond(Cond* in);
    virtual void children_zvp(Zvp* in);
    virtual void children_zvpp(Zvpp* in);
};
}


#endif
