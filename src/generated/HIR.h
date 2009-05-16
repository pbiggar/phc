#ifndef _HIR_H_
#define _HIR_H_

#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/error.h"
#include "lib/Object.h"
#include "lib/List.h"
#include "lib/String.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/AttrMap.h"
#include "process_ir/IR.h"
#include "process_ir/Foreach.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


namespace HIR{
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
class Rvalue;
class Target;
class Actual_parameter;
class Method_name;
class Class_name;
class Field_name;
class Static_value;
class Static_array_elem;
class Static_array_key;
class Identifier;
class Class_def;
class Interface_def;
class Method;
class Attribute;
class If;
class Loop;
class Foreach;
class Break;
class Continue;
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
class Literal;
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
class Variable_actual_parameter;
class Variable_name;
class Variable_method;
class Variable_class;
class Variable_field;
class Static_array;
class FOREIGN;
class CLASS_NAME;
class INTERFACE_NAME;
class METHOD_NAME;
class OP;
class CAST;
class CONSTANT_NAME;
class FIELD_NAME;
class Variable_variable;
class VARIABLE_NAME;
class INT;
class REAL;
class STRING;
class BOOL;
class NIL;
class None;

typedef List<Node*> Node_list;
typedef List<PHP_script*> PHP_script_list;
typedef List<Statement*> Statement_list;
typedef List<Class_mod*> Class_mod_list;
typedef List<Member*> Member_list;
typedef List<Signature*> Signature_list;
typedef List<Method_mod*> Method_mod_list;
typedef List<Formal_parameter*> Formal_parameter_list;
typedef List<Type*> Type_list;
typedef List<Attr_mod*> Attr_mod_list;
typedef List<Name_with_default*> Name_with_default_list;
typedef List<Catch*> Catch_list;
typedef List<Expr*> Expr_list;
typedef List<Rvalue*> Rvalue_list;
typedef List<Target*> Target_list;
typedef List<Actual_parameter*> Actual_parameter_list;
typedef List<Method_name*> Method_name_list;
typedef List<Class_name*> Class_name_list;
typedef List<Field_name*> Field_name_list;
typedef List<Static_value*> Static_value_list;
typedef List<Static_array_elem*> Static_array_elem_list;
typedef List<Static_array_key*> Static_array_key_list;
typedef List<Identifier*> Identifier_list;
typedef List<Class_def*> Class_def_list;
typedef List<Interface_def*> Interface_def_list;
typedef List<Method*> Method_list;
typedef List<Attribute*> Attribute_list;
typedef List<If*> If_list;
typedef List<Loop*> Loop_list;
typedef List<Foreach*> Foreach_list;
typedef List<Break*> Break_list;
typedef List<Continue*> Continue_list;
typedef List<Return*> Return_list;
typedef List<Static_declaration*> Static_declaration_list;
typedef List<Global*> Global_list;
typedef List<Try*> Try_list;
typedef List<Throw*> Throw_list;
typedef List<Assign_var*> Assign_var_list;
typedef List<Assign_field*> Assign_field_list;
typedef List<Assign_array*> Assign_array_list;
typedef List<Assign_var_var*> Assign_var_var_list;
typedef List<Assign_next*> Assign_next_list;
typedef List<Pre_op*> Pre_op_list;
typedef List<Eval_expr*> Eval_expr_list;
typedef List<Literal*> Literal_list;
typedef List<Field_access*> Field_access_list;
typedef List<Array_access*> Array_access_list;
typedef List<Array_next*> Array_next_list;
typedef List<Cast*> Cast_list;
typedef List<Unary_op*> Unary_op_list;
typedef List<Bin_op*> Bin_op_list;
typedef List<Constant*> Constant_list;
typedef List<Instanceof*> Instanceof_list;
typedef List<Method_invocation*> Method_invocation_list;
typedef List<New*> New_list;
typedef List<Variable_actual_parameter*> Variable_actual_parameter_list;
typedef List<Variable_name*> Variable_name_list;
typedef List<Variable_method*> Variable_method_list;
typedef List<Variable_class*> Variable_class_list;
typedef List<Variable_field*> Variable_field_list;
typedef List<Static_array*> Static_array_list;
typedef List<FOREIGN*> FOREIGN_list;
typedef List<CLASS_NAME*> CLASS_NAME_list;
typedef List<INTERFACE_NAME*> INTERFACE_NAME_list;
typedef List<METHOD_NAME*> METHOD_NAME_list;
typedef List<OP*> OP_list;
typedef List<CAST*> CAST_list;
typedef List<CONSTANT_NAME*> CONSTANT_NAME_list;
typedef List<FIELD_NAME*> FIELD_NAME_list;
typedef List<Variable_variable*> Variable_variable_list;
typedef List<VARIABLE_NAME*> VARIABLE_NAME_list;
typedef List<INT*> INT_list;
typedef List<REAL*> REAL_list;
typedef List<STRING*> STRING_list;
typedef List<BOOL*> BOOL_list;
typedef List<NIL*> NIL_list;
typedef List<None*> None_list;

class Transform;
class Visitor;

/* Node ::= PHP_script | Statement | Class_mod | Member | Signature | Method_mod | Formal_parameter | Type | Attr_mod | Name_with_default | Catch | Expr | Rvalue | Target | Actual_parameter | Method_name | Class_name | Field_name | Static_value | Static_array_elem | Static_array_key | Identifier; */
class Node : virtual public IR::Node
{
public:
    Node();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Node* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    void clone_mixin_from(Node* in);
    void assert_mixin_valid();
};

/* PHP_script ::= Statement* ; */
class PHP_script : virtual public Node, virtual public IR::PHP_script
{
public:
    PHP_script(Statement_list* statements);
protected:
    PHP_script();
public:
    Statement_list* statements;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 1;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual PHP_script* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Statement ::= Class_def | Interface_def | Method | Return | Static_declaration | Global | Try | Throw | If | Loop | Foreach | Break | Continue | Assign_var | Assign_var_var | Assign_array | Assign_next | Assign_field | Eval_expr | Pre_op | FOREIGN<IR::Node*>; */
class Statement : virtual public Node
{
public:
    Statement();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Statement* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Class_mod ::= "abstract"? "final"? ; */
class Class_mod : virtual public Node
{
public:
    Class_mod(bool is_abstract, bool is_final);
protected:
    Class_mod();
public:
    bool is_abstract;
    bool is_final;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 3;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Class_mod* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Member ::= Method | Attribute; */
class Member : virtual public Node
{
public:
    Member();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Member* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Signature ::= Method_mod is_ref:"&" METHOD_NAME Formal_parameter* ; */
class Signature : virtual public Node
{
public:
    Signature(Method_mod* method_mod, bool is_ref, METHOD_NAME* method_name, Formal_parameter_list* formal_parameters);
protected:
    Signature();
public:
    Method_mod* method_mod;
    bool is_ref;
    METHOD_NAME* method_name;
    Formal_parameter_list* formal_parameters;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 6;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Signature* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Signature(const char* name);
};

/* Method_mod ::= "public"? "protected"? "private"? "static"? "abstract"? "final"? ; */
class Method_mod : virtual public Node
{
public:
    Method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final);
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_abstract;
    bool is_final;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 7;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Method_mod* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Method_mod();
    Method_mod(Method_mod* a, Method_mod* b);
    static Method_mod* new_PUBLIC();
    static Method_mod* new_PROTECTED();
    static Method_mod* new_PRIVATE();
    static Method_mod* new_STATIC();
    static Method_mod* new_ABSTRACT();
    static Method_mod* new_FINAL();
};

/* Formal_parameter ::= Type is_ref:"&" var:Name_with_default ; */
class Formal_parameter : virtual public Node
{
public:
    Formal_parameter(Type* type, bool is_ref, Name_with_default* var);
protected:
    Formal_parameter();
public:
    Type* type;
    bool is_ref;
    Name_with_default* var;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 8;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Formal_parameter* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Formal_parameter(Type* type, VARIABLE_NAME* name);
    Formal_parameter(Type* type, bool is_ref, VARIABLE_NAME* name);
};

/* Type ::= CLASS_NAME? ; */
class Type : virtual public Node
{
public:
    Type(CLASS_NAME* class_name);
protected:
    Type();
public:
    CLASS_NAME* class_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 9;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Type* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Attr_mod ::= "public"? "protected"? "private"? "static"? "const"? ; */
class Attr_mod : virtual public Node
{
public:
    Attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const);
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_const;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 11;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Attr_mod* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Attr_mod();
    Attr_mod(Method_mod* mm);
    static Attr_mod* new_PUBLIC();
    static Attr_mod* new_PROTECTED();
    static Attr_mod* new_PRIVATE();
    static Attr_mod* new_STATIC();
    static Attr_mod* new_CONST();
};

/* Name_with_default ::= VARIABLE_NAME default_value:Static_value? ; */
class Name_with_default : virtual public Node
{
public:
    Name_with_default(VARIABLE_NAME* variable_name, Static_value* default_value);
protected:
    Name_with_default();
public:
    VARIABLE_NAME* variable_name;
    Static_value* default_value;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 12;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Name_with_default* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Catch ::= CLASS_NAME VARIABLE_NAME Statement* ; */
class Catch : virtual public Node
{
public:
    Catch(CLASS_NAME* class_name, VARIABLE_NAME* variable_name, Statement_list* statements);
protected:
    Catch();
public:
    CLASS_NAME* class_name;
    VARIABLE_NAME* variable_name;
    Statement_list* statements;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 22;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Catch* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Expr ::= Cast | Unary_op | Bin_op | Constant | Instanceof | Method_invocation | New | Literal | Variable_name | Array_access | Field_access | Array_next | FOREIGN<IR::Node*>; */
class Expr : virtual public Node
{
public:
    Expr();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Expr* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Rvalue ::= Literal | VARIABLE_NAME; */
class Rvalue : virtual public Node
{
public:
    Rvalue();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Rvalue* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Target ::= VARIABLE_NAME | CLASS_NAME; */
class Target : virtual public Node
{
public:
    Target();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Target* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Actual_parameter ::= Literal | Variable_actual_parameter; */
class Actual_parameter : virtual public Node
{
public:
    Actual_parameter();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Actual_parameter* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Method_name ::= METHOD_NAME | Variable_method; */
class Method_name : virtual public Node
{
public:
    Method_name();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Method_name* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Class_name ::= CLASS_NAME | Variable_class; */
class Class_name : virtual public Node
{
public:
    Class_name();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Class_name* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Field_name ::= FIELD_NAME | Variable_field; */
class Field_name : virtual public Node
{
public:
    Field_name();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Field_name* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Static_value ::= Literal | Static_array | Constant; */
class Static_value : virtual public Node
{
public:
    Static_value();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Static_value* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Static_array_elem ::= key:Static_array_key? is_ref:"&" val:Static_value ; */
class Static_array_elem : virtual public Node
{
public:
    Static_array_elem(Static_array_key* key, bool is_ref, Static_value* val);
protected:
    Static_array_elem();
public:
    Static_array_key* key;
    bool is_ref;
    Static_value* val;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 47;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Static_array_elem* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Static_array_key ::= Literal | Constant; */
class Static_array_key : virtual public Node
{
public:
    Static_array_key();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Static_array_key* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | FIELD_NAME | CAST | OP | CONSTANT_NAME; */
class Identifier : virtual public Node
{
public:
    Identifier();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Identifier* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
};

/* Class_def ::= Class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* Member* ; */
class Class_def : virtual public Statement
{
public:
    Class_def(Class_mod* class_mod, CLASS_NAME* class_name, CLASS_NAME* extends, INTERFACE_NAME_list* implements, Member_list* members);
protected:
    Class_def();
public:
    Class_mod* class_mod;
    CLASS_NAME* class_name;
    CLASS_NAME* extends;
    INTERFACE_NAME_list* implements;
    Member_list* members;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 2;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Class_def* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Class_def(Class_mod* mod);
    Class_def(const char* name);
    void add_member(Member* member);
    /*  Returns NULL if the method could not be found */
    Method* get_method(const char* name);
};

/* Interface_def ::= INTERFACE_NAME extends:INTERFACE_NAME* Member* ; */
class Interface_def : virtual public Statement
{
public:
    Interface_def(INTERFACE_NAME* interface_name, INTERFACE_NAME_list* extends, Member_list* members);
protected:
    Interface_def();
public:
    INTERFACE_NAME* interface_name;
    INTERFACE_NAME_list* extends;
    Member_list* members;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 4;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Interface_def* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Method ::= Signature Statement*? ; */
class Method : virtual public Statement, virtual public Member
{
public:
    Method(Signature* signature, Statement_list* statements);
protected:
    Method();
public:
    Signature* signature;
    Statement_list* statements;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 5;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Method* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Attribute ::= Attr_mod var:Name_with_default ; */
class Attribute : virtual public Member
{
public:
    Attribute(Attr_mod* attr_mod, Name_with_default* var);
protected:
    Attribute();
public:
    Attr_mod* attr_mod;
    Name_with_default* var;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 10;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Attribute* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* If ::= VARIABLE_NAME iftrue:Statement* iffalse:Statement* ; */
class If : virtual public Statement
{
public:
    If(VARIABLE_NAME* variable_name, Statement_list* iftrue, Statement_list* iffalse);
protected:
    If();
public:
    VARIABLE_NAME* variable_name;
    Statement_list* iftrue;
    Statement_list* iffalse;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 13;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual If* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    If(VARIABLE_NAME* variable_name);
};

/* Loop ::= Statement* ; */
class Loop : virtual public Statement
{
public:
    Loop(Statement_list* statements);
protected:
    Loop();
public:
    Statement_list* statements;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 14;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Loop* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Foreach ::= arr:VARIABLE_NAME key:VARIABLE_NAME? is_ref:"&" val:VARIABLE_NAME Statement* ; */
class Foreach : virtual public Statement
{
public:
    Foreach(VARIABLE_NAME* arr, VARIABLE_NAME* key, bool is_ref, VARIABLE_NAME* val, Statement_list* statements);
protected:
    Foreach();
public:
    VARIABLE_NAME* arr;
    VARIABLE_NAME* key;
    bool is_ref;
    VARIABLE_NAME* val;
    Statement_list* statements;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 15;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Foreach* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Break ::= Expr? ; */
class Break : virtual public Statement
{
public:
    Break(Expr* expr);
protected:
    Break();
public:
    Expr* expr;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 16;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Break* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Continue ::= Expr? ; */
class Continue : virtual public Statement
{
public:
    Continue(Expr* expr);
protected:
    Continue();
public:
    Expr* expr;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 17;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Continue* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Return ::= Rvalue ; */
class Return : virtual public Statement
{
public:
    Return(Rvalue* rvalue);
protected:
    Return();
public:
    Rvalue* rvalue;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 18;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Return* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Static_declaration ::= var:Name_with_default ; */
class Static_declaration : virtual public Statement
{
public:
    Static_declaration(Name_with_default* var);
protected:
    Static_declaration();
public:
    Name_with_default* var;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 19;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Static_declaration* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Global ::= Variable_name ; */
class Global : virtual public Statement
{
public:
    Global(Variable_name* variable_name);
protected:
    Global();
public:
    Variable_name* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 20;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Global* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Try ::= Statement* catches:Catch* ; */
class Try : virtual public Statement
{
public:
    Try(Statement_list* statements, Catch_list* catches);
protected:
    Try();
public:
    Statement_list* statements;
    Catch_list* catches;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 21;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Try* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Throw ::= VARIABLE_NAME ; */
class Throw : virtual public Statement
{
public:
    Throw(VARIABLE_NAME* variable_name);
protected:
    Throw();
public:
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 23;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Throw* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Assign_var ::= lhs:VARIABLE_NAME is_ref:"&" rhs:Expr ; */
class Assign_var : virtual public Statement
{
protected:
    Assign_var();
public:
    VARIABLE_NAME* lhs;
    bool is_ref;
    Expr* rhs;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 24;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Assign_var* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Assign_var(VARIABLE_NAME* lhs, Expr* rhs);
    Assign_var(VARIABLE_NAME* lhs, bool is_ref, Expr* rhs);
};

/* Assign_field ::= Target Field_name is_ref:"&" rhs:Rvalue ; */
class Assign_field : virtual public Statement
{
public:
    Assign_field(Target* target, Field_name* field_name, bool is_ref, Rvalue* rhs);
protected:
    Assign_field();
public:
    Target* target;
    Field_name* field_name;
    bool is_ref;
    Rvalue* rhs;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 25;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Assign_field* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Assign_array ::= lhs:VARIABLE_NAME index:Rvalue is_ref:"&" rhs:Rvalue ; */
class Assign_array : virtual public Statement
{
public:
    Assign_array(VARIABLE_NAME* lhs, Rvalue* index, bool is_ref, Rvalue* rhs);
protected:
    Assign_array();
public:
    VARIABLE_NAME* lhs;
    Rvalue* index;
    bool is_ref;
    Rvalue* rhs;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 26;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Assign_array* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Assign_var_var ::= lhs:VARIABLE_NAME is_ref:"&" rhs:Rvalue ; */
class Assign_var_var : virtual public Statement
{
public:
    Assign_var_var(VARIABLE_NAME* lhs, bool is_ref, Rvalue* rhs);
protected:
    Assign_var_var();
public:
    VARIABLE_NAME* lhs;
    bool is_ref;
    Rvalue* rhs;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 27;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Assign_var_var* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Assign_next ::= lhs:VARIABLE_NAME is_ref:"&" rhs:Rvalue ; */
class Assign_next : virtual public Statement
{
public:
    Assign_next(VARIABLE_NAME* lhs, bool is_ref, Rvalue* rhs);
protected:
    Assign_next();
public:
    VARIABLE_NAME* lhs;
    bool is_ref;
    Rvalue* rhs;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 28;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Assign_next* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Pre_op ::= OP VARIABLE_NAME ; */
class Pre_op : virtual public Statement
{
public:
    Pre_op(OP* op, VARIABLE_NAME* variable_name);
protected:
    Pre_op();
public:
    OP* op;
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 29;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Pre_op* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Pre_op(VARIABLE_NAME* variable_name, const char* op);
};

/* Eval_expr ::= Expr ; */
class Eval_expr : virtual public Statement
{
public:
    Eval_expr(Expr* expr);
protected:
    Eval_expr();
public:
    Expr* expr;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 30;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Eval_expr* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Literal ::= INT<long> | REAL<double> | STRING<String*> | BOOL<bool> | NIL<>; */
class Literal : virtual public Expr, virtual public Rvalue, virtual public Actual_parameter, virtual public Static_value, virtual public Static_array_key
{
public:
    Literal();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Literal* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    /*  We wish to match on this, so it cannot be pure virtual */
    virtual String* get_value_as_string();
};

/* Field_access ::= Target Field_name ; */
class Field_access : virtual public Expr
{
public:
    Field_access(Target* target, Field_name* field_name);
protected:
    Field_access();
public:
    Target* target;
    Field_name* field_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 31;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Field_access* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Field_access(Target* target, const char* name);
};

/* Array_access ::= VARIABLE_NAME index:Rvalue ; */
class Array_access : virtual public Expr
{
public:
    Array_access(VARIABLE_NAME* variable_name, Rvalue* index);
protected:
    Array_access();
public:
    VARIABLE_NAME* variable_name;
    Rvalue* index;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 32;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Array_access* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Array_next ::= VARIABLE_NAME ; */
class Array_next : virtual public Expr
{
public:
    Array_next(VARIABLE_NAME* variable_name);
protected:
    Array_next();
public:
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 33;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Array_next* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Cast ::= CAST VARIABLE_NAME ; */
class Cast : virtual public Expr
{
public:
    Cast(CAST* cast, VARIABLE_NAME* variable_name);
protected:
    Cast();
public:
    CAST* cast;
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 34;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Cast* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Cast(const char* type, VARIABLE_NAME* variable_name);
};

/* Unary_op ::= OP VARIABLE_NAME ; */
class Unary_op : virtual public Expr
{
public:
    Unary_op(OP* op, VARIABLE_NAME* variable_name);
protected:
    Unary_op();
public:
    OP* op;
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 35;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Unary_op* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Unary_op(VARIABLE_NAME* variable_name, const char* op);
};

/* Bin_op ::= left:Rvalue OP right:Rvalue ; */
class Bin_op : virtual public Expr
{
public:
    Bin_op(Rvalue* left, OP* op, Rvalue* right);
protected:
    Bin_op();
public:
    Rvalue* left;
    OP* op;
    Rvalue* right;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 36;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Bin_op* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Bin_op(VARIABLE_NAME* left, VARIABLE_NAME* right, const char* op);
};

/* Constant ::= CLASS_NAME? CONSTANT_NAME ; */
class Constant : virtual public Expr, virtual public Static_value, virtual public Static_array_key
{
public:
    Constant(CLASS_NAME* class_name, CONSTANT_NAME* constant_name);
protected:
    Constant();
public:
    CLASS_NAME* class_name;
    CONSTANT_NAME* constant_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 37;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Constant* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Instanceof ::= VARIABLE_NAME Class_name ; */
class Instanceof : virtual public Expr
{
public:
    Instanceof(VARIABLE_NAME* variable_name, Class_name* class_name);
protected:
    Instanceof();
public:
    VARIABLE_NAME* variable_name;
    Class_name* class_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 38;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Instanceof* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Method_invocation ::= Target? Method_name Actual_parameter* ; */
class Method_invocation : virtual public Expr
{
public:
    Method_invocation(Target* target, Method_name* method_name, Actual_parameter_list* actual_parameters);
protected:
    Method_invocation();
public:
    Target* target;
    Method_name* method_name;
    Actual_parameter_list* actual_parameters;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 39;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Method_invocation* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Method_invocation(const char* name, Actual_parameter* arg);
    Method_invocation(METHOD_NAME* name, Actual_parameter* arg);
};

/* New ::= Class_name Actual_parameter* ; */
class New : virtual public Expr
{
public:
    New(Class_name* class_name, Actual_parameter_list* actual_parameters);
protected:
    New();
public:
    Class_name* class_name;
    Actual_parameter_list* actual_parameters;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 40;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual New* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Variable_actual_parameter ::= is_ref:"&" Target? Variable_name array_indices:Rvalue* ; */
class Variable_actual_parameter : virtual public Actual_parameter
{
public:
    Variable_actual_parameter(bool is_ref, Target* target, Variable_name* variable_name, Rvalue_list* array_indices);
protected:
    Variable_actual_parameter();
public:
    bool is_ref;
    Target* target;
    Variable_name* variable_name;
    Rvalue_list* array_indices;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 41;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Variable_actual_parameter* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Variable_name ::= VARIABLE_NAME | Variable_variable; */
class Variable_name : virtual public Expr
{
public:
    Variable_name();
public:
    virtual void visit(Visitor* visitor) = 0;
    virtual void transform_children(Transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(Node* in) = 0;
public:
    virtual bool equals(Node* in) = 0;
public:
    virtual Variable_name* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Variable_method ::= VARIABLE_NAME ; */
class Variable_method : virtual public Method_name
{
public:
    Variable_method(VARIABLE_NAME* variable_name);
protected:
    Variable_method();
public:
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 42;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Variable_method* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Variable_class ::= VARIABLE_NAME ; */
class Variable_class : virtual public Class_name
{
public:
    Variable_class(VARIABLE_NAME* variable_name);
protected:
    Variable_class();
public:
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 44;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Variable_class* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Variable_field ::= VARIABLE_NAME ; */
class Variable_field : virtual public Field_name
{
public:
    Variable_field(VARIABLE_NAME* variable_name);
protected:
    Variable_field();
public:
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 45;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Variable_field* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Static_array ::= Static_array_elem* ; */
class Static_array : virtual public Static_value
{
public:
    Static_array(Static_array_elem_list* static_array_elems);
protected:
    Static_array();
public:
    Static_array_elem_list* static_array_elems;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 46;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Static_array* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class FOREIGN : virtual public Statement, virtual public Expr, virtual public IR::FOREIGN
{
public:
    FOREIGN(IR::Node* value);
protected:
    FOREIGN();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    IR::Node* value;
public:
    static const int ID = 48;
    virtual int classid();
public:
    virtual bool match(Node* in);
    virtual bool match_value(FOREIGN* that);
public:
    virtual bool equals(Node* in);
public:
    virtual FOREIGN* clone();
    virtual IR::Node* clone_value();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
public:
    bool equals_value(FOREIGN* that);
    IR ::Node* get_value();
};

class CLASS_NAME : virtual public Target, virtual public Class_name, virtual public Identifier
{
public:
    CLASS_NAME(String* value);
protected:
    CLASS_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 49;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual CLASS_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    CLASS_NAME(const char* name);
};

class INTERFACE_NAME : virtual public Identifier
{
public:
    INTERFACE_NAME(String* value);
protected:
    INTERFACE_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 50;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual INTERFACE_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class METHOD_NAME : virtual public Method_name, virtual public Identifier
{
public:
    METHOD_NAME(String* value);
protected:
    METHOD_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 51;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual METHOD_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    METHOD_NAME(const char* name);
};

class OP : virtual public Identifier
{
public:
    OP(String* value);
protected:
    OP();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 53;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual OP* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class CAST : virtual public Identifier
{
public:
    CAST(String* value);
protected:
    CAST();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 59;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual CAST* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class CONSTANT_NAME : virtual public Identifier
{
public:
    CONSTANT_NAME(String* value);
protected:
    CONSTANT_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 60;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual CONSTANT_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class FIELD_NAME : virtual public Field_name, virtual public Identifier
{
public:
    FIELD_NAME(String* value);
protected:
    FIELD_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 61;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual FIELD_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    FIELD_NAME(const char* name);
};

/* Variable_variable ::= VARIABLE_NAME ; */
class Variable_variable : virtual public Variable_name
{
public:
    Variable_variable(VARIABLE_NAME* variable_name);
protected:
    Variable_variable();
public:
    VARIABLE_NAME* variable_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 43;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Variable_variable* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class VARIABLE_NAME : virtual public Rvalue, virtual public Target, virtual public Variable_name, virtual public Identifier
{
public:
    VARIABLE_NAME(String* value);
protected:
    VARIABLE_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 52;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual VARIABLE_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    VARIABLE_NAME(const char* name);
};

class INT : virtual public Literal
{
public:
    INT(long value);
protected:
    INT();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    long value;
public:
    static const int ID = 54;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(INT* that);
public:
    virtual INT* clone();
    virtual long clone_value();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    /*  Constructors can't call virtual functions, so we create a non-virtual to */
    /*  do the work. This is then called by the virtual function, and is also */
    /*  safely called from the constructor. */
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    bool match_value(INT* that);
};

class REAL : virtual public Literal
{
public:
    REAL(double value);
protected:
    REAL();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    double value;
public:
    static const int ID = 55;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(REAL* that);
public:
    virtual REAL* clone();
    virtual double clone_value();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    /*  See comment in INT::_get_value_as_string () */
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    bool match_value(REAL* that);
};

class STRING : virtual public Literal
{
public:
    STRING(String* value);
protected:
    STRING();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
public:
    static const int ID = 56;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(STRING* that);
public:
    virtual STRING* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
public:
    virtual String* get_value_as_string();
    bool is_value_valid();
    String* clone_value();
    bool match_value(STRING* that);
};

class BOOL : virtual public Literal
{
public:
    BOOL(bool value);
protected:
    BOOL();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    bool value;
public:
    static const int ID = 57;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(BOOL* that);
public:
    virtual BOOL* clone();
    virtual bool clone_value();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    /*  See comment in INT::_get_value_as_string () */
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    bool match_value(BOOL* that);
};

class NIL : virtual public Literal
{
public:
    NIL();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 58;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual NIL* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    virtual String* get_value_as_string();
};

/* The top of the class hierarchy. If the Fold will not allow you fold to anything else, try this. */
class None : virtual public Node, virtual public PHP_script, virtual public Statement, virtual public Class_def, virtual public Class_mod, virtual public Interface_def, virtual public Member, virtual public Method, virtual public Signature, virtual public Method_mod, virtual public Formal_parameter, virtual public Type, virtual public Attribute, virtual public Attr_mod, virtual public Name_with_default, virtual public If, virtual public Loop, virtual public Foreach, virtual public Break, virtual public Continue, virtual public Return, virtual public Static_declaration, virtual public Global, virtual public Try, virtual public Catch, virtual public Throw, virtual public Assign_var, virtual public Assign_field, virtual public Assign_array, virtual public Assign_var_var, virtual public Assign_next, virtual public Pre_op, virtual public Eval_expr, virtual public Expr, virtual public Literal, virtual public Rvalue, virtual public Field_access, virtual public Array_access, virtual public Array_next, virtual public Cast, virtual public Unary_op, virtual public Bin_op, virtual public Constant, virtual public Instanceof, virtual public Target, virtual public Method_invocation, virtual public New, virtual public Actual_parameter, virtual public Variable_actual_parameter, virtual public Method_name, virtual public Variable_name, virtual public Class_name, virtual public Field_name, virtual public Variable_method, virtual public Variable_variable, virtual public Variable_class, virtual public Variable_field, virtual public Static_value, virtual public Static_array, virtual public Static_array_elem, virtual public Static_array_key, virtual public Identifier, virtual public FOREIGN, virtual public CLASS_NAME, virtual public INTERFACE_NAME, virtual public METHOD_NAME, virtual public VARIABLE_NAME, virtual public OP, virtual public INT, virtual public REAL, virtual public STRING, virtual public BOOL, virtual public NIL, virtual public CAST, virtual public CONSTANT_NAME, virtual public FIELD_NAME
{
public:
    None();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
    virtual None* clone();
    virtual void assert_valid();
    virtual String* get_value_as_string();
    virtual int classid();
    virtual bool match(Node* in);
    virtual bool equals(Node* in);
    virtual Node* find(Node* in);
    virtual void find_all(Node* in, Node_list* out);
};


class __WILDCARD__
{
public:
	virtual ~__WILDCARD__() {}

public:
	virtual bool match(Node* in) = 0;
};

template<class C>
class Wildcard : public virtual C, public __WILDCARD__
{
public:
	Wildcard() : value(NULL) {}
	Wildcard(C* v) : value(v) {}
	virtual ~Wildcard() {}

public:
	C* value;

	virtual bool match(Node* in)
	{
		C* that = dynamic_cast<C*>(in);
		if(in == NULL || that != NULL)
		{
			value = that;
			return true;
		}
		return false;
	}

	virtual Wildcard* clone()
	{
		if(value != NULL)
			return new Wildcard(value->clone());
		else
			return new Wildcard(NULL);
	}

	virtual bool equals(Node* in)
	{
		Wildcard* that = dynamic_cast<Wildcard*>(in);
		if(that == NULL) return false;

		if(this->value == NULL || that->value == NULL)
		{
			if(this->value != NULL || that->value != NULL)
				return false;
		}

		return value->equals(that->value);
	}

	virtual void assert_valid()
	{
		if(value != NULL) value->assert_valid();
	}

	virtual void visit(Visitor* visitor)
	{
		if(value != NULL)
			value->visit(visitor);
	}

	virtual void transform_children(Transform* transform)
	{
		if(value != NULL)
			value->transform_children(transform);
	}

	virtual Node* find(Node* in)
	{
		assert (0); // I'm not sure what this would mean
		return NULL;
	}

	virtual void find_all(Node* in, Node_list* out)
	{
		assert (0); // I'm not sure what this would mean
	}
public:
	static const int ID = 63;
	int classid()
	{
		return ID;
	}
};

}

#endif
