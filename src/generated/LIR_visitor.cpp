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

void Visitor::pre_piece(Piece* in)
{
}

void Visitor::pre_method(Method* in)
{
}

void Visitor::pre_block(Block* in)
{
}

void Visitor::pre_statement(Statement* in)
{
}

void Visitor::pre_action(Action* in)
{
}

void Visitor::pre_if(If* in)
{
}

void Visitor::pre_cond(Cond* in)
{
}

void Visitor::pre_assign_zvp(Assign_zvp* in)
{
}

void Visitor::pre_assign_zvpp(Assign_zvpp* in)
{
}

void Visitor::pre_declare(Declare* in)
{
}

void Visitor::pre_declare_p(Declare_p* in)
{
}

void Visitor::pre_inc_ref(Inc_ref* in)
{
}

void Visitor::pre_allocate(Allocate* in)
{
}

void Visitor::pre_separate(Separate* in)
{
}

void Visitor::pre_set_is_ref(Set_is_ref* in)
{
}

void Visitor::pre_dec_ref(Dec_ref* in)
{
}

void Visitor::pre_destruct(Destruct* in)
{
}

void Visitor::pre_overwrite(Overwrite* in)
{
}

void Visitor::pre_is_ref(Is_ref* in)
{
}

void Visitor::pre_equals(Equals* in)
{
}

void Visitor::pre_equals_p(Equals_p* in)
{
}

void Visitor::pre_not(Not* in)
{
}

void Visitor::pre_is_change_on_write(Is_change_on_write* in)
{
}

void Visitor::pre_is_copy_on_write(Is_copy_on_write* in)
{
}

void Visitor::pre_true(True* in)
{
}

void Visitor::pre_false(False* in)
{
}

void Visitor::pre_zvp(Zvp* in)
{
}

void Visitor::pre_zvpp(Zvpp* in)
{
}

void Visitor::pre_uninit(Uninit* in)
{
}

void Visitor::pre_null(Null* in)
{
}

void Visitor::pre_deref(Deref* in)
{
}

void Visitor::pre_ref(Ref* in)
{
}

void Visitor::pre_clone(Clone* in)
{
}

void Visitor::pre_symtable_fetch(Symtable_fetch* in)
{
}

void Visitor::pre_symtable_insert(Symtable_insert* in)
{
}

void Visitor::pre_identifier(Identifier* in)
{
}

void Visitor::pre_opt(Opt* in)
{
}

void Visitor::pre_opt_param(Opt_param* in)
{
}

void Visitor::pre_int(INT* in)
{
}

void Visitor::pre_uninterpreted(UNINTERPRETED* in)
{
}

void Visitor::pre_comment(COMMENT* in)
{
}

void Visitor::pre_intrinsic(INTRINSIC* in)
{
}

void Visitor::pre_api_call(API_CALL* in)
{
}

void Visitor::pre_code(CODE* in)
{
}

void Visitor::pre_zvp(ZVP* in)
{
}

void Visitor::pre_zvpp(ZVPP* in)
{
}

void Visitor::pre_literal(LITERAL* in)
{
}

void Visitor::pre_symtable(SYMTABLE* in)
{
}

void Visitor::pre_string(STRING* in)
{
}

/* Invoked after the children have been visited */
void Visitor::post_node(Node* in)
{
}

void Visitor::post_c_file(C_file* in)
{
}

void Visitor::post_piece(Piece* in)
{
}

void Visitor::post_method(Method* in)
{
}

void Visitor::post_block(Block* in)
{
}

void Visitor::post_statement(Statement* in)
{
}

void Visitor::post_action(Action* in)
{
}

void Visitor::post_if(If* in)
{
}

void Visitor::post_cond(Cond* in)
{
}

void Visitor::post_assign_zvp(Assign_zvp* in)
{
}

void Visitor::post_assign_zvpp(Assign_zvpp* in)
{
}

void Visitor::post_declare(Declare* in)
{
}

void Visitor::post_declare_p(Declare_p* in)
{
}

void Visitor::post_inc_ref(Inc_ref* in)
{
}

void Visitor::post_allocate(Allocate* in)
{
}

void Visitor::post_separate(Separate* in)
{
}

void Visitor::post_set_is_ref(Set_is_ref* in)
{
}

void Visitor::post_dec_ref(Dec_ref* in)
{
}

void Visitor::post_destruct(Destruct* in)
{
}

void Visitor::post_overwrite(Overwrite* in)
{
}

void Visitor::post_is_ref(Is_ref* in)
{
}

void Visitor::post_equals(Equals* in)
{
}

void Visitor::post_equals_p(Equals_p* in)
{
}

void Visitor::post_not(Not* in)
{
}

void Visitor::post_is_change_on_write(Is_change_on_write* in)
{
}

void Visitor::post_is_copy_on_write(Is_copy_on_write* in)
{
}

void Visitor::post_true(True* in)
{
}

void Visitor::post_false(False* in)
{
}

void Visitor::post_zvp(Zvp* in)
{
}

void Visitor::post_zvpp(Zvpp* in)
{
}

void Visitor::post_uninit(Uninit* in)
{
}

void Visitor::post_null(Null* in)
{
}

void Visitor::post_deref(Deref* in)
{
}

void Visitor::post_ref(Ref* in)
{
}

void Visitor::post_clone(Clone* in)
{
}

void Visitor::post_symtable_fetch(Symtable_fetch* in)
{
}

void Visitor::post_symtable_insert(Symtable_insert* in)
{
}

void Visitor::post_identifier(Identifier* in)
{
}

void Visitor::post_opt(Opt* in)
{
}

void Visitor::post_opt_param(Opt_param* in)
{
}

void Visitor::post_int(INT* in)
{
}

void Visitor::post_uninterpreted(UNINTERPRETED* in)
{
}

void Visitor::post_comment(COMMENT* in)
{
}

void Visitor::post_intrinsic(INTRINSIC* in)
{
}

void Visitor::post_api_call(API_CALL* in)
{
}

void Visitor::post_code(CODE* in)
{
}

void Visitor::post_zvp(ZVP* in)
{
}

void Visitor::post_zvpp(ZVPP* in)
{
}

void Visitor::post_literal(LITERAL* in)
{
}

void Visitor::post_symtable(SYMTABLE* in)
{
}

void Visitor::post_string(STRING* in)
{
}

/* Visit the children of a node */
void Visitor::children_c_file(C_file* in)
{
    visit_piece_list(in->pieces);
}

void Visitor::children_method(Method* in)
{
    visit_comment(in->comment);
    visit_uninterpreted(in->entry);
    visit_piece_list(in->pieces);
    visit_uninterpreted(in->exit);
}

void Visitor::children_block(Block* in)
{
    visit_comment(in->comment);
    visit_statement_list(in->statements);
}

void Visitor::children_if(If* in)
{
    visit_cond(in->cond);
    visit_statement_list(in->iftrue);
    visit_statement_list(in->iffalse);
}

void Visitor::children_assign_zvp(Assign_zvp* in)
{
    visit_zvp(in->lhs);
    visit_zvp(in->rhs);
}

void Visitor::children_assign_zvpp(Assign_zvpp* in)
{
    visit_zvpp(in->lhs);
    visit_zvpp(in->rhs);
}

void Visitor::children_declare(Declare* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_declare_p(Declare_p* in)
{
    visit_zvpp(in->zvpp);
}

void Visitor::children_inc_ref(Inc_ref* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_allocate(Allocate* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_separate(Separate* in)
{
    visit_zvpp(in->zvpp);
}

void Visitor::children_set_is_ref(Set_is_ref* in)
{
    visit_zvp(in->zvp);
    visit_int(in->_int);
}

void Visitor::children_dec_ref(Dec_ref* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_destruct(Destruct* in)
{
    visit_zvpp(in->zvpp);
}

void Visitor::children_overwrite(Overwrite* in)
{
    visit_zvp(in->lhs);
    visit_zvp(in->rhs);
}

void Visitor::children_is_ref(Is_ref* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_equals(Equals* in)
{
    visit_zvp(in->lhs);
    visit_zvp(in->rhs);
}

void Visitor::children_equals_p(Equals_p* in)
{
    visit_zvpp(in->lhs);
    visit_zvpp(in->rhs);
}

void Visitor::children_not(Not* in)
{
    visit_cond(in->cond);
}

void Visitor::children_is_change_on_write(Is_change_on_write* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_is_copy_on_write(Is_copy_on_write* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_true(True* in)
{
}

void Visitor::children_false(False* in)
{
}

void Visitor::children_uninit(Uninit* in)
{
}

void Visitor::children_null(Null* in)
{
}

void Visitor::children_deref(Deref* in)
{
    visit_zvpp(in->zvpp);
}

void Visitor::children_ref(Ref* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_clone(Clone* in)
{
    visit_zvp(in->zvp);
}

void Visitor::children_symtable_fetch(Symtable_fetch* in)
{
    visit_symtable(in->symtable);
    visit_string(in->name);
    visit_zvpp(in->zvpp);
}

void Visitor::children_symtable_insert(Symtable_insert* in)
{
    visit_symtable(in->symtable);
    visit_string(in->name);
    visit_zvpp(in->zvpp);
}

void Visitor::children_opt(Opt* in)
{
    visit_opt_param(in->param);
    visit_string(in->value);
}

/* Tokens don't have children, so these methods do nothing by default */
void Visitor::children_int(INT* in)
{
}

void Visitor::children_uninterpreted(UNINTERPRETED* in)
{
}

void Visitor::children_comment(COMMENT* in)
{
}

void Visitor::children_intrinsic(INTRINSIC* in)
{
}

void Visitor::children_api_call(API_CALL* in)
{
}

void Visitor::children_code(CODE* in)
{
}

void Visitor::children_zvp(ZVP* in)
{
}

void Visitor::children_zvpp(ZVPP* in)
{
}

void Visitor::children_literal(LITERAL* in)
{
}

void Visitor::children_symtable(SYMTABLE* in)
{
}

void Visitor::children_string(STRING* in)
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

void Visitor::pre_method_chain(Method* in)
{
    pre_node((Node*) in);
    pre_piece((Piece*) in);
    pre_method((Method*) in);
}

void Visitor::pre_block_chain(Block* in)
{
    pre_node((Node*) in);
    pre_piece((Piece*) in);
    pre_block((Block*) in);
}

void Visitor::pre_if_chain(If* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_if((If*) in);
}

void Visitor::pre_assign_zvp_chain(Assign_zvp* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_assign_zvp((Assign_zvp*) in);
}

void Visitor::pre_assign_zvpp_chain(Assign_zvpp* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_assign_zvpp((Assign_zvpp*) in);
}

void Visitor::pre_declare_chain(Declare* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_declare((Declare*) in);
}

void Visitor::pre_declare_p_chain(Declare_p* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_declare_p((Declare_p*) in);
}

void Visitor::pre_inc_ref_chain(Inc_ref* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_inc_ref((Inc_ref*) in);
}

void Visitor::pre_allocate_chain(Allocate* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_allocate((Allocate*) in);
}

void Visitor::pre_separate_chain(Separate* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_separate((Separate*) in);
}

void Visitor::pre_set_is_ref_chain(Set_is_ref* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_set_is_ref((Set_is_ref*) in);
}

void Visitor::pre_dec_ref_chain(Dec_ref* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_dec_ref((Dec_ref*) in);
}

void Visitor::pre_destruct_chain(Destruct* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_destruct((Destruct*) in);
}

void Visitor::pre_overwrite_chain(Overwrite* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_overwrite((Overwrite*) in);
}

void Visitor::pre_is_ref_chain(Is_ref* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_is_ref((Is_ref*) in);
}

void Visitor::pre_equals_chain(Equals* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_equals((Equals*) in);
}

void Visitor::pre_equals_p_chain(Equals_p* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_equals_p((Equals_p*) in);
}

void Visitor::pre_not_chain(Not* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_not((Not*) in);
}

void Visitor::pre_is_change_on_write_chain(Is_change_on_write* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_is_change_on_write((Is_change_on_write*) in);
}

void Visitor::pre_is_copy_on_write_chain(Is_copy_on_write* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_is_copy_on_write((Is_copy_on_write*) in);
}

void Visitor::pre_true_chain(True* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_true((True*) in);
}

void Visitor::pre_false_chain(False* in)
{
    pre_node((Node*) in);
    pre_cond((Cond*) in);
    pre_false((False*) in);
}

void Visitor::pre_uninit_chain(Uninit* in)
{
    pre_node((Node*) in);
    pre_zvp((Zvp*) in);
    pre_uninit((Uninit*) in);
}

void Visitor::pre_null_chain(Null* in)
{
    pre_node((Node*) in);
    pre_zvp((Zvp*) in);
    pre_zvpp((Zvpp*) in);
    pre_null((Null*) in);
}

void Visitor::pre_deref_chain(Deref* in)
{
    pre_node((Node*) in);
    pre_zvp((Zvp*) in);
    pre_deref((Deref*) in);
}

void Visitor::pre_ref_chain(Ref* in)
{
    pre_node((Node*) in);
    pre_zvpp((Zvpp*) in);
    pre_ref((Ref*) in);
}

void Visitor::pre_clone_chain(Clone* in)
{
    pre_node((Node*) in);
    pre_zvp((Zvp*) in);
    pre_clone((Clone*) in);
}

void Visitor::pre_symtable_fetch_chain(Symtable_fetch* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_symtable_fetch((Symtable_fetch*) in);
}

void Visitor::pre_symtable_insert_chain(Symtable_insert* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_action((Action*) in);
    pre_symtable_insert((Symtable_insert*) in);
}

void Visitor::pre_opt_chain(Opt* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_opt((Opt*) in);
}

void Visitor::pre_int_chain(INT* in)
{
    pre_node((Node*) in);
    pre_int((INT*) in);
}

void Visitor::pre_uninterpreted_chain(UNINTERPRETED* in)
{
    pre_node((Node*) in);
    pre_piece((Piece*) in);
    pre_identifier((Identifier*) in);
    pre_uninterpreted((UNINTERPRETED*) in);
}

void Visitor::pre_comment_chain(COMMENT* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_comment((COMMENT*) in);
}

void Visitor::pre_intrinsic_chain(INTRINSIC* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_intrinsic((INTRINSIC*) in);
}

void Visitor::pre_api_call_chain(API_CALL* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_api_call((API_CALL*) in);
}

void Visitor::pre_code_chain(CODE* in)
{
    pre_node((Node*) in);
    pre_statement((Statement*) in);
    pre_identifier((Identifier*) in);
    pre_code((CODE*) in);
}

void Visitor::pre_zvp_chain(ZVP* in)
{
    pre_node((Node*) in);
    pre_zvp((Zvp*) in);
    pre_identifier((Identifier*) in);
    pre_opt_param((Opt_param*) in);
    pre_zvp((ZVP*) in);
}

void Visitor::pre_zvpp_chain(ZVPP* in)
{
    pre_node((Node*) in);
    pre_zvpp((Zvpp*) in);
    pre_identifier((Identifier*) in);
    pre_opt_param((Opt_param*) in);
    pre_zvpp((ZVPP*) in);
}

void Visitor::pre_literal_chain(LITERAL* in)
{
    pre_node((Node*) in);
    pre_zvp((Zvp*) in);
    pre_identifier((Identifier*) in);
    pre_literal((LITERAL*) in);
}

void Visitor::pre_symtable_chain(SYMTABLE* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_symtable((SYMTABLE*) in);
}

void Visitor::pre_string_chain(STRING* in)
{
    pre_node((Node*) in);
    pre_identifier((Identifier*) in);
    pre_string((STRING*) in);
}

/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
void Visitor::post_c_file_chain(C_file* in)
{
    post_c_file((C_file*) in);
    post_node((Node*) in);
}

void Visitor::post_method_chain(Method* in)
{
    post_method((Method*) in);
    post_piece((Piece*) in);
    post_node((Node*) in);
}

void Visitor::post_block_chain(Block* in)
{
    post_block((Block*) in);
    post_piece((Piece*) in);
    post_node((Node*) in);
}

void Visitor::post_if_chain(If* in)
{
    post_if((If*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_assign_zvp_chain(Assign_zvp* in)
{
    post_assign_zvp((Assign_zvp*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_assign_zvpp_chain(Assign_zvpp* in)
{
    post_assign_zvpp((Assign_zvpp*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_declare_chain(Declare* in)
{
    post_declare((Declare*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_declare_p_chain(Declare_p* in)
{
    post_declare_p((Declare_p*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_inc_ref_chain(Inc_ref* in)
{
    post_inc_ref((Inc_ref*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_allocate_chain(Allocate* in)
{
    post_allocate((Allocate*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_separate_chain(Separate* in)
{
    post_separate((Separate*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_set_is_ref_chain(Set_is_ref* in)
{
    post_set_is_ref((Set_is_ref*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_dec_ref_chain(Dec_ref* in)
{
    post_dec_ref((Dec_ref*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_destruct_chain(Destruct* in)
{
    post_destruct((Destruct*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_overwrite_chain(Overwrite* in)
{
    post_overwrite((Overwrite*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_is_ref_chain(Is_ref* in)
{
    post_is_ref((Is_ref*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_equals_chain(Equals* in)
{
    post_equals((Equals*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_equals_p_chain(Equals_p* in)
{
    post_equals_p((Equals_p*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_not_chain(Not* in)
{
    post_not((Not*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_is_change_on_write_chain(Is_change_on_write* in)
{
    post_is_change_on_write((Is_change_on_write*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_is_copy_on_write_chain(Is_copy_on_write* in)
{
    post_is_copy_on_write((Is_copy_on_write*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_true_chain(True* in)
{
    post_true((True*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_false_chain(False* in)
{
    post_false((False*) in);
    post_cond((Cond*) in);
    post_node((Node*) in);
}

void Visitor::post_uninit_chain(Uninit* in)
{
    post_uninit((Uninit*) in);
    post_zvp((Zvp*) in);
    post_node((Node*) in);
}

void Visitor::post_null_chain(Null* in)
{
    post_null((Null*) in);
    post_zvpp((Zvpp*) in);
    post_zvp((Zvp*) in);
    post_node((Node*) in);
}

void Visitor::post_deref_chain(Deref* in)
{
    post_deref((Deref*) in);
    post_zvp((Zvp*) in);
    post_node((Node*) in);
}

void Visitor::post_ref_chain(Ref* in)
{
    post_ref((Ref*) in);
    post_zvpp((Zvpp*) in);
    post_node((Node*) in);
}

void Visitor::post_clone_chain(Clone* in)
{
    post_clone((Clone*) in);
    post_zvp((Zvp*) in);
    post_node((Node*) in);
}

void Visitor::post_symtable_fetch_chain(Symtable_fetch* in)
{
    post_symtable_fetch((Symtable_fetch*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_symtable_insert_chain(Symtable_insert* in)
{
    post_symtable_insert((Symtable_insert*) in);
    post_action((Action*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_opt_chain(Opt* in)
{
    post_opt((Opt*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_int_chain(INT* in)
{
    post_int((INT*) in);
    post_node((Node*) in);
}

void Visitor::post_uninterpreted_chain(UNINTERPRETED* in)
{
    post_uninterpreted((UNINTERPRETED*) in);
    post_identifier((Identifier*) in);
    post_piece((Piece*) in);
    post_node((Node*) in);
}

void Visitor::post_comment_chain(COMMENT* in)
{
    post_comment((COMMENT*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_intrinsic_chain(INTRINSIC* in)
{
    post_intrinsic((INTRINSIC*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_api_call_chain(API_CALL* in)
{
    post_api_call((API_CALL*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_code_chain(CODE* in)
{
    post_code((CODE*) in);
    post_identifier((Identifier*) in);
    post_statement((Statement*) in);
    post_node((Node*) in);
}

void Visitor::post_zvp_chain(ZVP* in)
{
    post_zvp((ZVP*) in);
    post_opt_param((Opt_param*) in);
    post_identifier((Identifier*) in);
    post_zvp((Zvp*) in);
    post_node((Node*) in);
}

void Visitor::post_zvpp_chain(ZVPP* in)
{
    post_zvpp((ZVPP*) in);
    post_opt_param((Opt_param*) in);
    post_identifier((Identifier*) in);
    post_zvpp((Zvpp*) in);
    post_node((Node*) in);
}

void Visitor::post_literal_chain(LITERAL* in)
{
    post_literal((LITERAL*) in);
    post_identifier((Identifier*) in);
    post_zvp((Zvp*) in);
    post_node((Node*) in);
}

void Visitor::post_symtable_chain(SYMTABLE* in)
{
    post_symtable((SYMTABLE*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

void Visitor::post_string_chain(STRING* in)
{
    post_string((STRING*) in);
    post_identifier((Identifier*) in);
    post_node((Node*) in);
}

/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
void Visitor::visit_piece_list(Piece_list* in)
{
    Piece_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("LIR", "Piece");
    else
    {
    	pre_list("LIR", "Piece", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_piece(*i);
    	}
    
    	post_list("LIR", "Piece", in->size());
    }
}

void Visitor::visit_piece(Piece* in)
{
    if(in == NULL)
    	visit_null("LIR", "Piece");
    else
    {
    	pre_piece_chain(in);
    	children_piece(in);
    	post_piece_chain(in);
    }
}

void Visitor::visit_comment(COMMENT* in)
{
    if(in == NULL)
    	visit_null("LIR", "COMMENT");
    else
    {
    	pre_comment_chain(in);
    	children_comment(in);
    	post_comment_chain(in);
    }
}

void Visitor::visit_uninterpreted(UNINTERPRETED* in)
{
    if(in == NULL)
    	visit_null("LIR", "UNINTERPRETED");
    else
    {
    	pre_uninterpreted_chain(in);
    	children_uninterpreted(in);
    	post_uninterpreted_chain(in);
    }
}

void Visitor::visit_statement_list(Statement_list* in)
{
    Statement_list::const_iterator i;
    
    if(in == NULL)
    	visit_null_list("LIR", "Statement");
    else
    {
    	pre_list("LIR", "Statement", in->size());
    
    	for(i = in->begin(); i != in->end(); i++)
    	{
    		visit_statement(*i);
    	}
    
    	post_list("LIR", "Statement", in->size());
    }
}

void Visitor::visit_statement(Statement* in)
{
    if(in == NULL)
    	visit_null("LIR", "Statement");
    else
    {
    	pre_statement_chain(in);
    	children_statement(in);
    	post_statement_chain(in);
    }
}

void Visitor::visit_cond(Cond* in)
{
    if(in == NULL)
    	visit_null("LIR", "Cond");
    else
    {
    	pre_cond_chain(in);
    	children_cond(in);
    	post_cond_chain(in);
    }
}

void Visitor::visit_zvp(Zvp* in)
{
    if(in == NULL)
    	visit_null("LIR", "Zvp");
    else
    {
    	pre_zvp_chain(in);
    	children_zvp(in);
    	post_zvp_chain(in);
    }
}

void Visitor::visit_zvpp(Zvpp* in)
{
    if(in == NULL)
    	visit_null("LIR", "Zvpp");
    else
    {
    	pre_zvpp_chain(in);
    	children_zvpp(in);
    	post_zvpp_chain(in);
    }
}

void Visitor::visit_zvp(ZVP* in)
{
    if(in == NULL)
    	visit_null("LIR", "ZVP");
    else
    {
    	pre_zvp_chain(in);
    	children_zvp(in);
    	post_zvp_chain(in);
    }
}

void Visitor::visit_zvpp(ZVPP* in)
{
    if(in == NULL)
    	visit_null("LIR", "ZVPP");
    else
    {
    	pre_zvpp_chain(in);
    	children_zvpp(in);
    	post_zvpp_chain(in);
    }
}

void Visitor::visit_int(INT* in)
{
    if(in == NULL)
    	visit_null("LIR", "INT");
    else
    {
    	pre_int_chain(in);
    	children_int(in);
    	post_int_chain(in);
    }
}

void Visitor::visit_symtable(SYMTABLE* in)
{
    if(in == NULL)
    	visit_null("LIR", "SYMTABLE");
    else
    {
    	pre_symtable_chain(in);
    	children_symtable(in);
    	post_symtable_chain(in);
    }
}

void Visitor::visit_string(STRING* in)
{
    if(in == NULL)
    	visit_null("LIR", "STRING");
    else
    {
    	pre_string_chain(in);
    	children_string(in);
    	post_string_chain(in);
    }
}

void Visitor::visit_opt_param(Opt_param* in)
{
    if(in == NULL)
    	visit_null("LIR", "Opt_param");
    else
    {
    	pre_opt_param_chain(in);
    	children_opt_param(in);
    	post_opt_param_chain(in);
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
void Visitor::pre_piece_chain(Piece* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	pre_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Block::ID:
    	pre_block_chain(dynamic_cast<Block*>(in));
    	break;
    case UNINTERPRETED::ID:
    	pre_uninterpreted_chain(dynamic_cast<UNINTERPRETED*>(in));
    	break;
    }
}

void Visitor::pre_statement_chain(Statement* in)
{
    switch(in->classid())
    {
    case Assign_zvp::ID:
    	pre_assign_zvp_chain(dynamic_cast<Assign_zvp*>(in));
    	break;
    case Assign_zvpp::ID:
    	pre_assign_zvpp_chain(dynamic_cast<Assign_zvpp*>(in));
    	break;
    case Declare::ID:
    	pre_declare_chain(dynamic_cast<Declare*>(in));
    	break;
    case Declare_p::ID:
    	pre_declare_p_chain(dynamic_cast<Declare_p*>(in));
    	break;
    case Inc_ref::ID:
    	pre_inc_ref_chain(dynamic_cast<Inc_ref*>(in));
    	break;
    case Dec_ref::ID:
    	pre_dec_ref_chain(dynamic_cast<Dec_ref*>(in));
    	break;
    case Set_is_ref::ID:
    	pre_set_is_ref_chain(dynamic_cast<Set_is_ref*>(in));
    	break;
    case Destruct::ID:
    	pre_destruct_chain(dynamic_cast<Destruct*>(in));
    	break;
    case Allocate::ID:
    	pre_allocate_chain(dynamic_cast<Allocate*>(in));
    	break;
    case Overwrite::ID:
    	pre_overwrite_chain(dynamic_cast<Overwrite*>(in));
    	break;
    case Separate::ID:
    	pre_separate_chain(dynamic_cast<Separate*>(in));
    	break;
    case Symtable_fetch::ID:
    	pre_symtable_fetch_chain(dynamic_cast<Symtable_fetch*>(in));
    	break;
    case Symtable_insert::ID:
    	pre_symtable_insert_chain(dynamic_cast<Symtable_insert*>(in));
    	break;
    case If::ID:
    	pre_if_chain(dynamic_cast<If*>(in));
    	break;
    case Opt::ID:
    	pre_opt_chain(dynamic_cast<Opt*>(in));
    	break;
    case INTRINSIC::ID:
    	pre_intrinsic_chain(dynamic_cast<INTRINSIC*>(in));
    	break;
    case API_CALL::ID:
    	pre_api_call_chain(dynamic_cast<API_CALL*>(in));
    	break;
    case CODE::ID:
    	pre_code_chain(dynamic_cast<CODE*>(in));
    	break;
    }
}

void Visitor::pre_cond_chain(Cond* in)
{
    switch(in->classid())
    {
    case Is_ref::ID:
    	pre_is_ref_chain(dynamic_cast<Is_ref*>(in));
    	break;
    case Equals::ID:
    	pre_equals_chain(dynamic_cast<Equals*>(in));
    	break;
    case Equals_p::ID:
    	pre_equals_p_chain(dynamic_cast<Equals_p*>(in));
    	break;
    case Not::ID:
    	pre_not_chain(dynamic_cast<Not*>(in));
    	break;
    case Is_copy_on_write::ID:
    	pre_is_copy_on_write_chain(dynamic_cast<Is_copy_on_write*>(in));
    	break;
    case Is_change_on_write::ID:
    	pre_is_change_on_write_chain(dynamic_cast<Is_change_on_write*>(in));
    	break;
    case True::ID:
    	pre_true_chain(dynamic_cast<True*>(in));
    	break;
    case False::ID:
    	pre_false_chain(dynamic_cast<False*>(in));
    	break;
    }
}

void Visitor::pre_zvp_chain(Zvp* in)
{
    switch(in->classid())
    {
    case Deref::ID:
    	pre_deref_chain(dynamic_cast<Deref*>(in));
    	break;
    case ZVP::ID:
    	pre_zvp_chain(dynamic_cast<ZVP*>(in));
    	break;
    case Null::ID:
    	pre_null_chain(dynamic_cast<Null*>(in));
    	break;
    case LITERAL::ID:
    	pre_literal_chain(dynamic_cast<LITERAL*>(in));
    	break;
    case Uninit::ID:
    	pre_uninit_chain(dynamic_cast<Uninit*>(in));
    	break;
    case Clone::ID:
    	pre_clone_chain(dynamic_cast<Clone*>(in));
    	break;
    }
}

void Visitor::pre_zvpp_chain(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID:
    	pre_ref_chain(dynamic_cast<Ref*>(in));
    	break;
    case ZVPP::ID:
    	pre_zvpp_chain(dynamic_cast<ZVPP*>(in));
    	break;
    case Null::ID:
    	pre_null_chain(dynamic_cast<Null*>(in));
    	break;
    }
}

void Visitor::pre_opt_param_chain(Opt_param* in)
{
    switch(in->classid())
    {
    case ZVPP::ID:
    	pre_zvpp_chain(dynamic_cast<ZVPP*>(in));
    	break;
    case ZVP::ID:
    	pre_zvp_chain(dynamic_cast<ZVP*>(in));
    	break;
    }
}

/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
void Visitor::post_piece_chain(Piece* in)
{
    switch(in->classid())
    {
    case Method::ID:
    	post_method_chain(dynamic_cast<Method*>(in));
    	break;
    case Block::ID:
    	post_block_chain(dynamic_cast<Block*>(in));
    	break;
    case UNINTERPRETED::ID:
    	post_uninterpreted_chain(dynamic_cast<UNINTERPRETED*>(in));
    	break;
    }
}

void Visitor::post_statement_chain(Statement* in)
{
    switch(in->classid())
    {
    case Assign_zvp::ID:
    	post_assign_zvp_chain(dynamic_cast<Assign_zvp*>(in));
    	break;
    case Assign_zvpp::ID:
    	post_assign_zvpp_chain(dynamic_cast<Assign_zvpp*>(in));
    	break;
    case Declare::ID:
    	post_declare_chain(dynamic_cast<Declare*>(in));
    	break;
    case Declare_p::ID:
    	post_declare_p_chain(dynamic_cast<Declare_p*>(in));
    	break;
    case Inc_ref::ID:
    	post_inc_ref_chain(dynamic_cast<Inc_ref*>(in));
    	break;
    case Dec_ref::ID:
    	post_dec_ref_chain(dynamic_cast<Dec_ref*>(in));
    	break;
    case Set_is_ref::ID:
    	post_set_is_ref_chain(dynamic_cast<Set_is_ref*>(in));
    	break;
    case Destruct::ID:
    	post_destruct_chain(dynamic_cast<Destruct*>(in));
    	break;
    case Allocate::ID:
    	post_allocate_chain(dynamic_cast<Allocate*>(in));
    	break;
    case Overwrite::ID:
    	post_overwrite_chain(dynamic_cast<Overwrite*>(in));
    	break;
    case Separate::ID:
    	post_separate_chain(dynamic_cast<Separate*>(in));
    	break;
    case Symtable_fetch::ID:
    	post_symtable_fetch_chain(dynamic_cast<Symtable_fetch*>(in));
    	break;
    case Symtable_insert::ID:
    	post_symtable_insert_chain(dynamic_cast<Symtable_insert*>(in));
    	break;
    case If::ID:
    	post_if_chain(dynamic_cast<If*>(in));
    	break;
    case Opt::ID:
    	post_opt_chain(dynamic_cast<Opt*>(in));
    	break;
    case INTRINSIC::ID:
    	post_intrinsic_chain(dynamic_cast<INTRINSIC*>(in));
    	break;
    case API_CALL::ID:
    	post_api_call_chain(dynamic_cast<API_CALL*>(in));
    	break;
    case CODE::ID:
    	post_code_chain(dynamic_cast<CODE*>(in));
    	break;
    }
}

void Visitor::post_cond_chain(Cond* in)
{
    switch(in->classid())
    {
    case Is_ref::ID:
    	post_is_ref_chain(dynamic_cast<Is_ref*>(in));
    	break;
    case Equals::ID:
    	post_equals_chain(dynamic_cast<Equals*>(in));
    	break;
    case Equals_p::ID:
    	post_equals_p_chain(dynamic_cast<Equals_p*>(in));
    	break;
    case Not::ID:
    	post_not_chain(dynamic_cast<Not*>(in));
    	break;
    case Is_copy_on_write::ID:
    	post_is_copy_on_write_chain(dynamic_cast<Is_copy_on_write*>(in));
    	break;
    case Is_change_on_write::ID:
    	post_is_change_on_write_chain(dynamic_cast<Is_change_on_write*>(in));
    	break;
    case True::ID:
    	post_true_chain(dynamic_cast<True*>(in));
    	break;
    case False::ID:
    	post_false_chain(dynamic_cast<False*>(in));
    	break;
    }
}

void Visitor::post_zvp_chain(Zvp* in)
{
    switch(in->classid())
    {
    case Deref::ID:
    	post_deref_chain(dynamic_cast<Deref*>(in));
    	break;
    case ZVP::ID:
    	post_zvp_chain(dynamic_cast<ZVP*>(in));
    	break;
    case Null::ID:
    	post_null_chain(dynamic_cast<Null*>(in));
    	break;
    case LITERAL::ID:
    	post_literal_chain(dynamic_cast<LITERAL*>(in));
    	break;
    case Uninit::ID:
    	post_uninit_chain(dynamic_cast<Uninit*>(in));
    	break;
    case Clone::ID:
    	post_clone_chain(dynamic_cast<Clone*>(in));
    	break;
    }
}

void Visitor::post_zvpp_chain(Zvpp* in)
{
    switch(in->classid())
    {
    case Ref::ID:
    	post_ref_chain(dynamic_cast<Ref*>(in));
    	break;
    case ZVPP::ID:
    	post_zvpp_chain(dynamic_cast<ZVPP*>(in));
    	break;
    case Null::ID:
    	post_null_chain(dynamic_cast<Null*>(in));
    	break;
    }
}

void Visitor::post_opt_param_chain(Opt_param* in)
{
    switch(in->classid())
    {
    case ZVPP::ID:
    	post_zvpp_chain(dynamic_cast<ZVPP*>(in));
    	break;
    case ZVP::ID:
    	post_zvp_chain(dynamic_cast<ZVP*>(in));
    	break;
    }
}

/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */
void Visitor::children_piece(Piece* in)
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

void Visitor::children_statement(Statement* in)
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
    }
}

void Visitor::children_cond(Cond* in)
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
    case Is_copy_on_write::ID:
    	children_is_copy_on_write(dynamic_cast<Is_copy_on_write*>(in));
    	break;
    case Is_change_on_write::ID:
    	children_is_change_on_write(dynamic_cast<Is_change_on_write*>(in));
    	break;
    case True::ID:
    	children_true(dynamic_cast<True*>(in));
    	break;
    case False::ID:
    	children_false(dynamic_cast<False*>(in));
    	break;
    }
}

void Visitor::children_zvp(Zvp* in)
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

void Visitor::children_zvpp(Zvpp* in)
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

void Visitor::children_opt_param(Opt_param* in)
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

