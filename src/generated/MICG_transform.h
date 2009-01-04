#ifndef _MICG_TRANSFORM_H_
#define _MICG_TRANSFORM_H_

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
class Transform
{
public:
    virtual ~Transform();
/* Invoked before the children are transformed */
public:
    virtual All* pre_all(All* in);
    virtual void pre_macro(Macro* in, Macro_list* out);
    virtual Signature* pre_signature(Signature* in);
    virtual void pre_formal_parameter(Formal_parameter* in, Formal_parameter_list* out);
    virtual Lookup* pre_lookup(Lookup* in);
    virtual void pre_equals(Equals* in, Rule_list* out);
    virtual Expr* pre_param(Param* in);
    virtual Body* pre_body(Body* in);
    virtual Macro_call* pre_macro_call(Macro_call* in);
    virtual Callback* pre_callback(Callback* in);
    virtual MACRO_NAME* pre_macro_name(MACRO_NAME* in);
    virtual TYPE_NAME* pre_type_name(TYPE_NAME* in);
    virtual PARAM_NAME* pre_param_name(PARAM_NAME* in);
    virtual ATTR_NAME* pre_attr_name(ATTR_NAME* in);
    virtual Expr* pre_string(STRING* in);
    virtual void pre_c_code(C_CODE* in, Body_part_list* out);
/* Invoked after the children have been transformed */
public:
    virtual All* post_all(All* in);
    virtual void post_macro(Macro* in, Macro_list* out);
    virtual Signature* post_signature(Signature* in);
    virtual void post_formal_parameter(Formal_parameter* in, Formal_parameter_list* out);
    virtual Lookup* post_lookup(Lookup* in);
    virtual void post_equals(Equals* in, Rule_list* out);
    virtual Expr* post_param(Param* in);
    virtual Body* post_body(Body* in);
    virtual Macro_call* post_macro_call(Macro_call* in);
    virtual Callback* post_callback(Callback* in);
    virtual MACRO_NAME* post_macro_name(MACRO_NAME* in);
    virtual TYPE_NAME* post_type_name(TYPE_NAME* in);
    virtual PARAM_NAME* post_param_name(PARAM_NAME* in);
    virtual ATTR_NAME* post_attr_name(ATTR_NAME* in);
    virtual Expr* post_string(STRING* in);
    virtual void post_c_code(C_CODE* in, Body_part_list* out);
/* Transform the children of the node */
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
/* Call the pre-transform, transform-children post-transform methods in order */
/* Do not override unless you know what you are doing */
public:
    virtual Macro_list* transform_macro_list(Macro_list* in);
    virtual Macro_list* transform_macro(Macro* in);
    virtual Signature* transform_signature(Signature* in);
    virtual Rule_list* transform_rule_list(Rule_list* in);
    virtual Rule_list* transform_rule(Rule* in);
    virtual Body* transform_body(Body* in);
    virtual MACRO_NAME* transform_macro_name(MACRO_NAME* in);
    virtual Formal_parameter_list* transform_formal_parameter_list(Formal_parameter_list* in);
    virtual Formal_parameter_list* transform_formal_parameter(Formal_parameter* in);
    virtual TYPE_NAME* transform_type_name(TYPE_NAME* in);
    virtual PARAM_NAME* transform_param_name(PARAM_NAME* in);
    virtual ATTR_NAME* transform_attr_name(ATTR_NAME* in);
    virtual Expr* transform_expr(Expr* in);
    virtual ATTR_NAME_list* transform_attr_name_list(ATTR_NAME_list* in);
    virtual Body_part_list* transform_body_part_list(Body_part_list* in);
    virtual Body_part_list* transform_body_part(Body_part* in);
    virtual Expr_list* transform_expr_list(Expr_list* in);
    virtual All* transform_all(All* in);
/* Invoke the right pre-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void pre_rule(Rule* in, Rule_list* out);
    virtual Expr* pre_expr(Expr* in);
    virtual void pre_body_part(Body_part* in, Body_part_list* out);
/* Invoke the right post-transform (manual dispatching) */
/* Do not override unless you know what you are doing */
public:
    virtual void post_rule(Rule* in, Rule_list* out);
    virtual Expr* post_expr(Expr* in);
    virtual void post_body_part(Body_part* in, Body_part_list* out);
/* Invoke the right transform-children (manual dispatching) */
/* Do not override unless you what you are doing */
public:
    virtual void children_rule(Rule* in);
    virtual void children_expr(Expr* in);
    virtual void children_body_part(Body_part* in);
};
}


#endif
