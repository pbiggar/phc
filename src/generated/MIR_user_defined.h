#ifndef _MIR_USER_DEFINED_H_
#define _MIR_USER_DEFINED_H_

#ifndef MAKETEA_USER_DEFINED
#error "MAKETEA_USER_DEFINED macro undefined"
#endif

namespace MIR{
class Node;
class PHP_script;
class Statement;
class Class_mod;
class Member;
class Signature;
class Method_mod;
class Formal_parameter;
class Type;
class Attr_mod;
class Name_with_default;
class Catch;
class Expr;
class Target;
class Actual_parameter;
class Method_name;
class Class_name;
class Field_name;
class Static_value;
class Static_array_elem;
class Static_array_key;
class Identifier;
class PARAM_INDEX;
class Class_def;
class Interface_def;
class Method;
class Attribute;
class Class_alias;
class Interface_alias;
class Method_alias;
class Return;
class Static_declaration;
class Global;
class Try;
class Throw;
class Assign_var;
class Assign_field;
class Assign_array;
class Assign_var_var;
class Assign_next;
class Pre_op;
class Eval_expr;
class Unset;
class Isset;
class Rvalue;
class Field_access;
class Array_access;
class Array_next;
class Cast;
class Unary_op;
class Bin_op;
class Constant;
class Instanceof;
class Method_invocation;
class New;
class Variable_name;
class Variable_method;
class Variable_class;
class Variable_field;
class Static_array;
class Branch;
class Goto;
class Label;
class Foreach_reset;
class Foreach_next;
class Foreach_end;
class Foreach_has_key;
class Foreach_get_key;
class Foreach_get_val;
class Param_is_ref;
class FOREIGN;
class CLASS_NAME;
class INTERFACE_NAME;
class METHOD_NAME;
class OP;
class CAST;
class CONSTANT_NAME;
class FIELD_NAME;
class LABEL_NAME;
class HT_ITERATOR;
class Literal;
class Variable_variable;
class VARIABLE_NAME;
class INT;
class REAL;
class STRING;
class BOOL;
class NIL;
class None;

}

MAKETEA_USER_DEFINED(MIR::Node)
MAKETEA_USER_DEFINED(MIR::PHP_script)
MAKETEA_USER_DEFINED(MIR::Statement)
MAKETEA_USER_DEFINED(MIR::Class_mod)
MAKETEA_USER_DEFINED(MIR::Member)
MAKETEA_USER_DEFINED(MIR::Signature)
MAKETEA_USER_DEFINED(MIR::Method_mod)
MAKETEA_USER_DEFINED(MIR::Formal_parameter)
MAKETEA_USER_DEFINED(MIR::Type)
MAKETEA_USER_DEFINED(MIR::Attr_mod)
MAKETEA_USER_DEFINED(MIR::Name_with_default)
MAKETEA_USER_DEFINED(MIR::Catch)
MAKETEA_USER_DEFINED(MIR::Expr)
MAKETEA_USER_DEFINED(MIR::Target)
MAKETEA_USER_DEFINED(MIR::Actual_parameter)
MAKETEA_USER_DEFINED(MIR::Method_name)
MAKETEA_USER_DEFINED(MIR::Class_name)
MAKETEA_USER_DEFINED(MIR::Field_name)
MAKETEA_USER_DEFINED(MIR::Static_value)
MAKETEA_USER_DEFINED(MIR::Static_array_elem)
MAKETEA_USER_DEFINED(MIR::Static_array_key)
MAKETEA_USER_DEFINED(MIR::Identifier)
MAKETEA_USER_DEFINED(MIR::PARAM_INDEX)
MAKETEA_USER_DEFINED(MIR::Class_def)
MAKETEA_USER_DEFINED(MIR::Interface_def)
MAKETEA_USER_DEFINED(MIR::Method)
MAKETEA_USER_DEFINED(MIR::Attribute)
MAKETEA_USER_DEFINED(MIR::Class_alias)
MAKETEA_USER_DEFINED(MIR::Interface_alias)
MAKETEA_USER_DEFINED(MIR::Method_alias)
MAKETEA_USER_DEFINED(MIR::Return)
MAKETEA_USER_DEFINED(MIR::Static_declaration)
MAKETEA_USER_DEFINED(MIR::Global)
MAKETEA_USER_DEFINED(MIR::Try)
MAKETEA_USER_DEFINED(MIR::Throw)
MAKETEA_USER_DEFINED(MIR::Assign_var)
MAKETEA_USER_DEFINED(MIR::Assign_field)
MAKETEA_USER_DEFINED(MIR::Assign_array)
MAKETEA_USER_DEFINED(MIR::Assign_var_var)
MAKETEA_USER_DEFINED(MIR::Assign_next)
MAKETEA_USER_DEFINED(MIR::Pre_op)
MAKETEA_USER_DEFINED(MIR::Eval_expr)
MAKETEA_USER_DEFINED(MIR::Unset)
MAKETEA_USER_DEFINED(MIR::Isset)
MAKETEA_USER_DEFINED(MIR::Rvalue)
MAKETEA_USER_DEFINED(MIR::Field_access)
MAKETEA_USER_DEFINED(MIR::Array_access)
MAKETEA_USER_DEFINED(MIR::Array_next)
MAKETEA_USER_DEFINED(MIR::Cast)
MAKETEA_USER_DEFINED(MIR::Unary_op)
MAKETEA_USER_DEFINED(MIR::Bin_op)
MAKETEA_USER_DEFINED(MIR::Constant)
MAKETEA_USER_DEFINED(MIR::Instanceof)
MAKETEA_USER_DEFINED(MIR::Method_invocation)
MAKETEA_USER_DEFINED(MIR::New)
MAKETEA_USER_DEFINED(MIR::Variable_name)
MAKETEA_USER_DEFINED(MIR::Variable_method)
MAKETEA_USER_DEFINED(MIR::Variable_class)
MAKETEA_USER_DEFINED(MIR::Variable_field)
MAKETEA_USER_DEFINED(MIR::Static_array)
MAKETEA_USER_DEFINED(MIR::Branch)
MAKETEA_USER_DEFINED(MIR::Goto)
MAKETEA_USER_DEFINED(MIR::Label)
MAKETEA_USER_DEFINED(MIR::Foreach_reset)
MAKETEA_USER_DEFINED(MIR::Foreach_next)
MAKETEA_USER_DEFINED(MIR::Foreach_end)
MAKETEA_USER_DEFINED(MIR::Foreach_has_key)
MAKETEA_USER_DEFINED(MIR::Foreach_get_key)
MAKETEA_USER_DEFINED(MIR::Foreach_get_val)
MAKETEA_USER_DEFINED(MIR::Param_is_ref)
MAKETEA_USER_DEFINED(MIR::FOREIGN)
MAKETEA_USER_DEFINED(MIR::CLASS_NAME)
MAKETEA_USER_DEFINED(MIR::INTERFACE_NAME)
MAKETEA_USER_DEFINED(MIR::METHOD_NAME)
MAKETEA_USER_DEFINED(MIR::OP)
MAKETEA_USER_DEFINED(MIR::CAST)
MAKETEA_USER_DEFINED(MIR::CONSTANT_NAME)
MAKETEA_USER_DEFINED(MIR::FIELD_NAME)
MAKETEA_USER_DEFINED(MIR::LABEL_NAME)
MAKETEA_USER_DEFINED(MIR::HT_ITERATOR)
MAKETEA_USER_DEFINED(MIR::Literal)
MAKETEA_USER_DEFINED(MIR::Variable_variable)
MAKETEA_USER_DEFINED(MIR::VARIABLE_NAME)
MAKETEA_USER_DEFINED(MIR::INT)
MAKETEA_USER_DEFINED(MIR::REAL)
MAKETEA_USER_DEFINED(MIR::STRING)
MAKETEA_USER_DEFINED(MIR::BOOL)
MAKETEA_USER_DEFINED(MIR::NIL)
MAKETEA_USER_DEFINED(MIR::None)


#endif
