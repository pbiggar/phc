#ifndef _LIR_VISITOR_H_
#define _LIR_VISITOR_H_

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
class Visitor
{
public:
    virtual ~Visitor();
/* Invoked before the children are visited */
public:
    virtual void pre_node(Node* in);
    virtual void pre_c_file(C_file* in);
    virtual void pre_piece(Piece* in);
    virtual void pre_method(Method* in);
    virtual void pre_block(Block* in);
    virtual void pre_statement(Statement* in);
    virtual void pre_action(Action* in);
    virtual void pre_if(If* in);
    virtual void pre_cond(Cond* in);
    virtual void pre_assign_zvp(Assign_zvp* in);
    virtual void pre_assign_zvpp(Assign_zvpp* in);
    virtual void pre_declare(Declare* in);
    virtual void pre_declare_p(Declare_p* in);
    virtual void pre_inc_ref(Inc_ref* in);
    virtual void pre_allocate(Allocate* in);
    virtual void pre_separate(Separate* in);
    virtual void pre_set_is_ref(Set_is_ref* in);
    virtual void pre_dec_ref(Dec_ref* in);
    virtual void pre_destruct(Destruct* in);
    virtual void pre_overwrite(Overwrite* in);
    virtual void pre_is_ref(Is_ref* in);
    virtual void pre_equals(Equals* in);
    virtual void pre_equals_p(Equals_p* in);
    virtual void pre_not(Not* in);
    virtual void pre_is_change_on_write(Is_change_on_write* in);
    virtual void pre_is_copy_on_write(Is_copy_on_write* in);
    virtual void pre_true(True* in);
    virtual void pre_false(False* in);
    virtual void pre_zvp(Zvp* in);
    virtual void pre_zvpp(Zvpp* in);
    virtual void pre_uninit(Uninit* in);
    virtual void pre_null(Null* in);
    virtual void pre_deref(Deref* in);
    virtual void pre_ref(Ref* in);
    virtual void pre_clone(Clone* in);
    virtual void pre_symtable_fetch(Symtable_fetch* in);
    virtual void pre_symtable_insert(Symtable_insert* in);
    virtual void pre_identifier(Identifier* in);
    virtual void pre_profile(Profile* in);
    virtual void pre_int(INT* in);
    virtual void pre_uninterpreted(UNINTERPRETED* in);
    virtual void pre_comment(COMMENT* in);
    virtual void pre_intrinsic(INTRINSIC* in);
    virtual void pre_api_call(API_CALL* in);
    virtual void pre_code(CODE* in);
    virtual void pre_zvp(ZVP* in);
    virtual void pre_zvpp(ZVPP* in);
    virtual void pre_literal(LITERAL* in);
    virtual void pre_symtable(SYMTABLE* in);
    virtual void pre_string(STRING* in);
/* Invoked after the children have been visited */
public:
    virtual void post_node(Node* in);
    virtual void post_c_file(C_file* in);
    virtual void post_piece(Piece* in);
    virtual void post_method(Method* in);
    virtual void post_block(Block* in);
    virtual void post_statement(Statement* in);
    virtual void post_action(Action* in);
    virtual void post_if(If* in);
    virtual void post_cond(Cond* in);
    virtual void post_assign_zvp(Assign_zvp* in);
    virtual void post_assign_zvpp(Assign_zvpp* in);
    virtual void post_declare(Declare* in);
    virtual void post_declare_p(Declare_p* in);
    virtual void post_inc_ref(Inc_ref* in);
    virtual void post_allocate(Allocate* in);
    virtual void post_separate(Separate* in);
    virtual void post_set_is_ref(Set_is_ref* in);
    virtual void post_dec_ref(Dec_ref* in);
    virtual void post_destruct(Destruct* in);
    virtual void post_overwrite(Overwrite* in);
    virtual void post_is_ref(Is_ref* in);
    virtual void post_equals(Equals* in);
    virtual void post_equals_p(Equals_p* in);
    virtual void post_not(Not* in);
    virtual void post_is_change_on_write(Is_change_on_write* in);
    virtual void post_is_copy_on_write(Is_copy_on_write* in);
    virtual void post_true(True* in);
    virtual void post_false(False* in);
    virtual void post_zvp(Zvp* in);
    virtual void post_zvpp(Zvpp* in);
    virtual void post_uninit(Uninit* in);
    virtual void post_null(Null* in);
    virtual void post_deref(Deref* in);
    virtual void post_ref(Ref* in);
    virtual void post_clone(Clone* in);
    virtual void post_symtable_fetch(Symtable_fetch* in);
    virtual void post_symtable_insert(Symtable_insert* in);
    virtual void post_identifier(Identifier* in);
    virtual void post_profile(Profile* in);
    virtual void post_int(INT* in);
    virtual void post_uninterpreted(UNINTERPRETED* in);
    virtual void post_comment(COMMENT* in);
    virtual void post_intrinsic(INTRINSIC* in);
    virtual void post_api_call(API_CALL* in);
    virtual void post_code(CODE* in);
    virtual void post_zvp(ZVP* in);
    virtual void post_zvpp(ZVPP* in);
    virtual void post_literal(LITERAL* in);
    virtual void post_symtable(SYMTABLE* in);
    virtual void post_string(STRING* in);
/* Visit the children of a node */
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
    virtual void children_true(True* in);
    virtual void children_false(False* in);
    virtual void children_uninit(Uninit* in);
    virtual void children_null(Null* in);
    virtual void children_deref(Deref* in);
    virtual void children_ref(Ref* in);
    virtual void children_clone(Clone* in);
    virtual void children_symtable_fetch(Symtable_fetch* in);
    virtual void children_symtable_insert(Symtable_insert* in);
    virtual void children_profile(Profile* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_int(INT* in);
    virtual void children_uninterpreted(UNINTERPRETED* in);
    virtual void children_comment(COMMENT* in);
    virtual void children_intrinsic(INTRINSIC* in);
    virtual void children_api_call(API_CALL* in);
    virtual void children_code(CODE* in);
    virtual void children_zvp(ZVP* in);
    virtual void children_zvpp(ZVPP* in);
    virtual void children_literal(LITERAL* in);
    virtual void children_symtable(SYMTABLE* in);
    virtual void children_string(STRING* in);
/* Unparser support */
public:
    virtual void visit_marker(char const* name, bool value);
    virtual void visit_null(char const* name_space, char const* type_id);
    virtual void visit_null_list(char const* name_space, char const* type_id);
    virtual void pre_list(char const* name_space, char const* type_id, int size);
    virtual void post_list(char const* name_space, char const* type_id, int size);
/* Invoke the chain of pre-visit methods along the inheritance hierachy */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_c_file_chain(C_file* in);
    virtual void pre_method_chain(Method* in);
    virtual void pre_block_chain(Block* in);
    virtual void pre_if_chain(If* in);
    virtual void pre_assign_zvp_chain(Assign_zvp* in);
    virtual void pre_assign_zvpp_chain(Assign_zvpp* in);
    virtual void pre_declare_chain(Declare* in);
    virtual void pre_declare_p_chain(Declare_p* in);
    virtual void pre_inc_ref_chain(Inc_ref* in);
    virtual void pre_allocate_chain(Allocate* in);
    virtual void pre_separate_chain(Separate* in);
    virtual void pre_set_is_ref_chain(Set_is_ref* in);
    virtual void pre_dec_ref_chain(Dec_ref* in);
    virtual void pre_destruct_chain(Destruct* in);
    virtual void pre_overwrite_chain(Overwrite* in);
    virtual void pre_is_ref_chain(Is_ref* in);
    virtual void pre_equals_chain(Equals* in);
    virtual void pre_equals_p_chain(Equals_p* in);
    virtual void pre_not_chain(Not* in);
    virtual void pre_is_change_on_write_chain(Is_change_on_write* in);
    virtual void pre_is_copy_on_write_chain(Is_copy_on_write* in);
    virtual void pre_true_chain(True* in);
    virtual void pre_false_chain(False* in);
    virtual void pre_uninit_chain(Uninit* in);
    virtual void pre_null_chain(Null* in);
    virtual void pre_deref_chain(Deref* in);
    virtual void pre_ref_chain(Ref* in);
    virtual void pre_clone_chain(Clone* in);
    virtual void pre_symtable_fetch_chain(Symtable_fetch* in);
    virtual void pre_symtable_insert_chain(Symtable_insert* in);
    virtual void pre_profile_chain(Profile* in);
    virtual void pre_int_chain(INT* in);
    virtual void pre_uninterpreted_chain(UNINTERPRETED* in);
    virtual void pre_comment_chain(COMMENT* in);
    virtual void pre_intrinsic_chain(INTRINSIC* in);
    virtual void pre_api_call_chain(API_CALL* in);
    virtual void pre_code_chain(CODE* in);
    virtual void pre_zvp_chain(ZVP* in);
    virtual void pre_zvpp_chain(ZVPP* in);
    virtual void pre_literal_chain(LITERAL* in);
    virtual void pre_symtable_chain(SYMTABLE* in);
    virtual void pre_string_chain(STRING* in);
/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_c_file_chain(C_file* in);
    virtual void post_method_chain(Method* in);
    virtual void post_block_chain(Block* in);
    virtual void post_if_chain(If* in);
    virtual void post_assign_zvp_chain(Assign_zvp* in);
    virtual void post_assign_zvpp_chain(Assign_zvpp* in);
    virtual void post_declare_chain(Declare* in);
    virtual void post_declare_p_chain(Declare_p* in);
    virtual void post_inc_ref_chain(Inc_ref* in);
    virtual void post_allocate_chain(Allocate* in);
    virtual void post_separate_chain(Separate* in);
    virtual void post_set_is_ref_chain(Set_is_ref* in);
    virtual void post_dec_ref_chain(Dec_ref* in);
    virtual void post_destruct_chain(Destruct* in);
    virtual void post_overwrite_chain(Overwrite* in);
    virtual void post_is_ref_chain(Is_ref* in);
    virtual void post_equals_chain(Equals* in);
    virtual void post_equals_p_chain(Equals_p* in);
    virtual void post_not_chain(Not* in);
    virtual void post_is_change_on_write_chain(Is_change_on_write* in);
    virtual void post_is_copy_on_write_chain(Is_copy_on_write* in);
    virtual void post_true_chain(True* in);
    virtual void post_false_chain(False* in);
    virtual void post_uninit_chain(Uninit* in);
    virtual void post_null_chain(Null* in);
    virtual void post_deref_chain(Deref* in);
    virtual void post_ref_chain(Ref* in);
    virtual void post_clone_chain(Clone* in);
    virtual void post_symtable_fetch_chain(Symtable_fetch* in);
    virtual void post_symtable_insert_chain(Symtable_insert* in);
    virtual void post_profile_chain(Profile* in);
    virtual void post_int_chain(INT* in);
    virtual void post_uninterpreted_chain(UNINTERPRETED* in);
    virtual void post_comment_chain(COMMENT* in);
    virtual void post_intrinsic_chain(INTRINSIC* in);
    virtual void post_api_call_chain(API_CALL* in);
    virtual void post_code_chain(CODE* in);
    virtual void post_zvp_chain(ZVP* in);
    virtual void post_zvpp_chain(ZVPP* in);
    virtual void post_literal_chain(LITERAL* in);
    virtual void post_symtable_chain(SYMTABLE* in);
    virtual void post_string_chain(STRING* in);
/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
public:
    virtual void visit_piece_list(Piece_list* in);
    virtual void visit_piece(Piece* in);
    virtual void visit_comment(COMMENT* in);
    virtual void visit_uninterpreted(UNINTERPRETED* in);
    virtual void visit_statement_list(Statement_list* in);
    virtual void visit_statement(Statement* in);
    virtual void visit_cond(Cond* in);
    virtual void visit_zvp(Zvp* in);
    virtual void visit_zvpp(Zvpp* in);
    virtual void visit_zvp(ZVP* in);
    virtual void visit_zvpp(ZVPP* in);
    virtual void visit_int(INT* in);
    virtual void visit_symtable(SYMTABLE* in);
    virtual void visit_string(STRING* in);
    virtual void visit_c_file(C_file* in);
/* Invoke the right pre-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_piece_chain(Piece* in);
    virtual void pre_statement_chain(Statement* in);
    virtual void pre_cond_chain(Cond* in);
    virtual void pre_zvp_chain(Zvp* in);
    virtual void pre_zvpp_chain(Zvpp* in);
/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_piece_chain(Piece* in);
    virtual void post_statement_chain(Statement* in);
    virtual void post_cond_chain(Cond* in);
    virtual void post_zvp_chain(Zvp* in);
    virtual void post_zvpp_chain(Zvpp* in);
/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void children_piece(Piece* in);
    virtual void children_statement(Statement* in);
    virtual void children_cond(Cond* in);
    virtual void children_zvp(Zvp* in);
    virtual void children_zvpp(Zvpp* in);
};
}


#endif
