#ifndef _MICG_VISITOR_H_
#define _MICG_VISITOR_H_

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
#include "process_ir/IR.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "MICG.h"

namespace MICG{
class Visitor
{
public:
    virtual ~Visitor();
/* Invoked before the children are visited */
public:
    virtual void pre_node(Node* in);
    virtual void pre_all(All* in);
    virtual void pre_macro(Macro* in);
    virtual void pre_signature(Signature* in);
    virtual void pre_formal_parameter(Formal_parameter* in);
    virtual void pre_rule(Rule* in);
    virtual void pre_lookup(Lookup* in);
    virtual void pre_equals(Equals* in);
    virtual void pre_expr(Expr* in);
    virtual void pre_param(Param* in);
    virtual void pre_body(Body* in);
    virtual void pre_body_part(Body_part* in);
    virtual void pre_interpolation(Interpolation* in);
    virtual void pre_macro_call(Macro_call* in);
    virtual void pre_callback(Callback* in);
    virtual void pre_identifier(Identifier* in);
    virtual void pre_macro_name(MACRO_NAME* in);
    virtual void pre_type_name(TYPE_NAME* in);
    virtual void pre_param_name(PARAM_NAME* in);
    virtual void pre_attr_name(ATTR_NAME* in);
    virtual void pre_string(STRING* in);
    virtual void pre_c_code(C_CODE* in);
/* Invoked after the children have been visited */
public:
    virtual void post_node(Node* in);
    virtual void post_all(All* in);
    virtual void post_macro(Macro* in);
    virtual void post_signature(Signature* in);
    virtual void post_formal_parameter(Formal_parameter* in);
    virtual void post_rule(Rule* in);
    virtual void post_lookup(Lookup* in);
    virtual void post_equals(Equals* in);
    virtual void post_expr(Expr* in);
    virtual void post_param(Param* in);
    virtual void post_body(Body* in);
    virtual void post_body_part(Body_part* in);
    virtual void post_interpolation(Interpolation* in);
    virtual void post_macro_call(Macro_call* in);
    virtual void post_callback(Callback* in);
    virtual void post_identifier(Identifier* in);
    virtual void post_macro_name(MACRO_NAME* in);
    virtual void post_type_name(TYPE_NAME* in);
    virtual void post_param_name(PARAM_NAME* in);
    virtual void post_attr_name(ATTR_NAME* in);
    virtual void post_string(STRING* in);
    virtual void post_c_code(C_CODE* in);
/* Visit the children of a node */
public:
    virtual void children_all(All* in);
    virtual void children_macro(Macro* in);
    virtual void children_signature(Signature* in);
    virtual void children_formal_parameter(Formal_parameter* in);
    virtual void children_lookup(Lookup* in);
    virtual void children_equals(Equals* in);
    virtual void children_param(Param* in);
    virtual void children_body(Body* in);
    virtual void children_macro_call(Macro_call* in);
    virtual void children_callback(Callback* in);
/* Tokens don't have children, so these methods do nothing by default */
public:
    virtual void children_macro_name(MACRO_NAME* in);
    virtual void children_type_name(TYPE_NAME* in);
    virtual void children_param_name(PARAM_NAME* in);
    virtual void children_attr_name(ATTR_NAME* in);
    virtual void children_string(STRING* in);
    virtual void children_c_code(C_CODE* in);
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
    virtual void pre_all_chain(All* in);
    virtual void pre_macro_chain(Macro* in);
    virtual void pre_signature_chain(Signature* in);
    virtual void pre_formal_parameter_chain(Formal_parameter* in);
    virtual void pre_lookup_chain(Lookup* in);
    virtual void pre_equals_chain(Equals* in);
    virtual void pre_param_chain(Param* in);
    virtual void pre_body_chain(Body* in);
    virtual void pre_macro_call_chain(Macro_call* in);
    virtual void pre_callback_chain(Callback* in);
    virtual void pre_macro_name_chain(MACRO_NAME* in);
    virtual void pre_type_name_chain(TYPE_NAME* in);
    virtual void pre_param_name_chain(PARAM_NAME* in);
    virtual void pre_attr_name_chain(ATTR_NAME* in);
    virtual void pre_string_chain(STRING* in);
    virtual void pre_c_code_chain(C_CODE* in);
/* Invoke the chain of post-visit methods along the inheritance hierarchy */
/* (invoked in opposite order to the pre-chain) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_all_chain(All* in);
    virtual void post_macro_chain(Macro* in);
    virtual void post_signature_chain(Signature* in);
    virtual void post_formal_parameter_chain(Formal_parameter* in);
    virtual void post_lookup_chain(Lookup* in);
    virtual void post_equals_chain(Equals* in);
    virtual void post_param_chain(Param* in);
    virtual void post_body_chain(Body* in);
    virtual void post_macro_call_chain(Macro_call* in);
    virtual void post_callback_chain(Callback* in);
    virtual void post_macro_name_chain(MACRO_NAME* in);
    virtual void post_type_name_chain(TYPE_NAME* in);
    virtual void post_param_name_chain(PARAM_NAME* in);
    virtual void post_attr_name_chain(ATTR_NAME* in);
    virtual void post_string_chain(STRING* in);
    virtual void post_c_code_chain(C_CODE* in);
/* Call the pre-chain, visit children and post-chain in order */
/* Do not override unless you know what you are doing */
public:
    virtual void visit_macro_list(Macro_list* in);
    virtual void visit_macro(Macro* in);
    virtual void visit_signature(Signature* in);
    virtual void visit_rule_list(Rule_list* in);
    virtual void visit_rule(Rule* in);
    virtual void visit_body(Body* in);
    virtual void visit_macro_name(MACRO_NAME* in);
    virtual void visit_formal_parameter_list(Formal_parameter_list* in);
    virtual void visit_formal_parameter(Formal_parameter* in);
    virtual void visit_type_name(TYPE_NAME* in);
    virtual void visit_param_name(PARAM_NAME* in);
    virtual void visit_attr_name(ATTR_NAME* in);
    virtual void visit_expr(Expr* in);
    virtual void visit_attr_name_list(ATTR_NAME_list* in);
    virtual void visit_body_part_list(Body_part_list* in);
    virtual void visit_body_part(Body_part* in);
    virtual void visit_expr_list(Expr_list* in);
    virtual void visit_all(All* in);
/* Invoke the right pre-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_rule_chain(Rule* in);
    virtual void pre_expr_chain(Expr* in);
    virtual void pre_body_part_chain(Body_part* in);
/* Invoke the right post-chain (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_rule_chain(Rule* in);
    virtual void post_expr_chain(Expr* in);
    virtual void post_body_part_chain(Body_part* in);
/* Invoke the right visit-children (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void children_rule(Rule* in);
    virtual void children_expr(Expr* in);
    virtual void children_body_part(Body_part* in);
};
}


#endif
