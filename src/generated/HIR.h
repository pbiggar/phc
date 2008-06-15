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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


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
class Variable_name;
class Target;
class Array_elem;
class Method_name;
class Actual_parameter;
class Class_name;
class Static_value;
class Static_array_elem;
class Static_array_key;
class Identifier;
class Foreign;
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
class Assign_array;
class Assign_var_var;
class Push_array;
class Eval_expr;
class Literal;
class Cast;
class Unary_op;
class Bin_op;
class Constant;
class Instanceof;
class Variable;
class Reflection;
class Pre_op;
class Array;
class Method_invocation;
class New;
class Static_array;
class Foreign_statement;
class Foreign_expr;
class CLASS_NAME;
class INTERFACE_NAME;
class METHOD_NAME;
class VARIABLE_NAME;
class CAST;
class OP;
class CONSTANT_NAME;
class INT;
class REAL;
class STRING;
class BOOL;
class NIL;

class Transform;
class Visitor;

// Node ::= PHP_script | Statement | Class_mod | Member | Signature | Method_mod | Formal_parameter | Type | Attr_mod | Name_with_default | Catch | Expr | Variable_name | Target | Array_elem | Method_name | Actual_parameter | Class_name | Static_value | Static_array_elem | Static_array_key | Identifier | Foreign;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    void clone_mixin_from(Node* in);
    void assert_mixin_valid();
    bool is_mixin_equal(Node* in);
};

// PHP_script ::= Statement* ;
class PHP_script : virtual public Node, virtual public IR::PHP_script
{
public:
    PHP_script(List<Statement*>* statements);
protected:
    PHP_script();
public:
    List<Statement*>* statements;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Statement ::= Class_def | Interface_def | Method | Return | Static_declaration | Global | Try | Throw | If | Loop | Foreach | Break | Continue | Assign_var | Assign_var_var | Assign_array | Push_array | Eval_expr | Pre_op | Foreign_statement;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Class_mod ::= "abstract"? "final"? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Member ::= Method | Attribute;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Signature ::= Method_mod is_ref:"&" METHOD_NAME Formal_parameter* ;
class Signature : virtual public Node
{
public:
    Signature(Method_mod* method_mod, bool is_ref, METHOD_NAME* method_name, List<Formal_parameter*>* formal_parameters);
protected:
    Signature();
public:
    Method_mod* method_mod;
    bool is_ref;
    METHOD_NAME* method_name;
    List<Formal_parameter*>* formal_parameters;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Signature(const char* name);
};

// Method_mod ::= "public"? "protected"? "private"? "static"? "abstract"? "final"? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
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

// Formal_parameter ::= Type is_ref:"&" var:Name_with_default ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Formal_parameter(Type* type, VARIABLE_NAME* name);
    Formal_parameter(Type* type, bool is_ref, VARIABLE_NAME* name);
};

// Type ::= CLASS_NAME? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Attr_mod ::= "public"? "protected"? "private"? "static"? "const"? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
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

// Name_with_default ::= VARIABLE_NAME default_value:Static_value? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Catch ::= CLASS_NAME VARIABLE_NAME Statement* ;
class Catch : virtual public Node
{
public:
    Catch(CLASS_NAME* class_name, VARIABLE_NAME* variable_name, List<Statement*>* statements);
protected:
    Catch();
public:
    CLASS_NAME* class_name;
    VARIABLE_NAME* variable_name;
    List<Statement*>* statements;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Expr ::= Cast | Unary_op | Bin_op | Constant | Instanceof | Variable | Method_invocation | New | Literal | Array | Foreign_expr;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Variable_name ::= VARIABLE_NAME | Reflection;
class Variable_name : virtual public Node
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Target ::= VARIABLE_NAME | CLASS_NAME;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Array_elem ::= key:Expr? is_ref:"&" val:Expr ;
class Array_elem : virtual public Node
{
public:
    Array_elem(Expr* key, bool is_ref, Expr* val);
protected:
    Array_elem();
public:
    Expr* key;
    bool is_ref;
    Expr* val;
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
    virtual Array_elem* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Method_name ::= METHOD_NAME | Reflection;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Actual_parameter ::= is_ref:"&" Target? Variable_name array_indices:VARIABLE_NAME* ;
class Actual_parameter : virtual public Node
{
public:
    Actual_parameter(bool is_ref, Target* target, Variable_name* variable_name, List<VARIABLE_NAME*>* array_indices);
protected:
    Actual_parameter();
public:
    bool is_ref;
    Target* target;
    Variable_name* variable_name;
    List<VARIABLE_NAME*>* array_indices;
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
    virtual Actual_parameter* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Class_name ::= CLASS_NAME | Reflection;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Static_value ::= Literal | Static_array | Constant;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Static_array_elem ::= key:Static_array_key? is_ref:"&" val:Static_value ;
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
    static const int ID = 43;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Static_array_key ::= Literal | Constant;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
};

// Identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | CAST | OP | CONSTANT_NAME;
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
};

// Foreign ::= Foreign_statement | Foreign_expr;
class Foreign : virtual public Node
{
public:
    Foreign();
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
    virtual Foreign* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    Foreign(IR ::Node* foreign);
    IR ::Node* foreign;
};

// Class_def ::= Class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* Member* ;
class Class_def : virtual public Statement
{
public:
    Class_def(Class_mod* class_mod, CLASS_NAME* class_name, CLASS_NAME* extends, List<INTERFACE_NAME*>* implements, List<Member*>* members);
protected:
    Class_def();
public:
    Class_mod* class_mod;
    CLASS_NAME* class_name;
    CLASS_NAME* extends;
    List<INTERFACE_NAME*>* implements;
    List<Member*>* members;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Class_def(Class_mod* mod);
    Class_def(const char* name);
    void add_member(Member* member);
    //  Returns NULL if the method could not be found
    Method* get_method(const char* name);
};

// Interface_def ::= INTERFACE_NAME extends:INTERFACE_NAME* Member* ;
class Interface_def : virtual public Statement
{
public:
    Interface_def(INTERFACE_NAME* interface_name, List<INTERFACE_NAME*>* extends, List<Member*>* members);
protected:
    Interface_def();
public:
    INTERFACE_NAME* interface_name;
    List<INTERFACE_NAME*>* extends;
    List<Member*>* members;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Method ::= Signature Statement*? ;
class Method : virtual public Statement, virtual public Member
{
public:
    Method(Signature* signature, List<Statement*>* statements);
protected:
    Method();
public:
    Signature* signature;
    List<Statement*>* statements;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Attribute ::= Attr_mod var:Name_with_default ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// If ::= VARIABLE_NAME iftrue:Statement* iffalse:Statement* ;
class If : virtual public Statement
{
public:
    If(VARIABLE_NAME* variable_name, List<Statement*>* iftrue, List<Statement*>* iffalse);
protected:
    If();
public:
    VARIABLE_NAME* variable_name;
    List<Statement*>* iftrue;
    List<Statement*>* iffalse;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    If(VARIABLE_NAME* variable_name);
};

// Loop ::= Statement* ;
class Loop : virtual public Statement
{
public:
    Loop(List<Statement*>* statements);
protected:
    Loop();
public:
    List<Statement*>* statements;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Foreach ::= arr:VARIABLE_NAME key:VARIABLE_NAME? is_ref:"&" val:VARIABLE_NAME Statement* ;
class Foreach : virtual public Statement
{
public:
    Foreach(VARIABLE_NAME* arr, VARIABLE_NAME* key, bool is_ref, VARIABLE_NAME* val, List<Statement*>* statements);
protected:
    Foreach();
public:
    VARIABLE_NAME* arr;
    VARIABLE_NAME* key;
    bool is_ref;
    VARIABLE_NAME* val;
    List<Statement*>* statements;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Break ::= Expr? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Continue ::= Expr? ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Return ::= Expr ;
class Return : virtual public Statement
{
public:
    Return(Expr* expr);
protected:
    Return();
public:
    Expr* expr;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Static_declaration ::= var:Name_with_default ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Global ::= Variable_name ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Try ::= Statement* catches:Catch* ;
class Try : virtual public Statement
{
public:
    Try(List<Statement*>* statements, List<Catch*>* catches);
protected:
    Try();
public:
    List<Statement*>* statements;
    List<Catch*>* catches;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Throw ::= VARIABLE_NAME ;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Assign_var ::= Target? lhs:VARIABLE_NAME is_ref:"&" rhs:Expr ;
class Assign_var : virtual public Statement
{
public:
    Assign_var(Target* target, VARIABLE_NAME* lhs, bool is_ref, Expr* rhs);
protected:
    Assign_var();
public:
    Target* target;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Assign_var(VARIABLE_NAME* lhs, Expr* rhs);
    Assign_var(VARIABLE_NAME* lhs, bool is_ref, Expr* rhs);
};

// Assign_array ::= Target? lhs:VARIABLE_NAME index:VARIABLE_NAME is_ref:"&" rhs:VARIABLE_NAME ;
class Assign_array : virtual public Statement
{
public:
    Assign_array(Target* target, VARIABLE_NAME* lhs, VARIABLE_NAME* index, bool is_ref, VARIABLE_NAME* rhs);
protected:
    Assign_array();
public:
    Target* target;
    VARIABLE_NAME* lhs;
    VARIABLE_NAME* index;
    bool is_ref;
    VARIABLE_NAME* rhs;
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
    virtual Assign_array* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Assign_var_var ::= Target? lhs:VARIABLE_NAME is_ref:"&" rhs:VARIABLE_NAME ;
class Assign_var_var : virtual public Statement
{
public:
    Assign_var_var(Target* target, VARIABLE_NAME* lhs, bool is_ref, VARIABLE_NAME* rhs);
protected:
    Assign_var_var();
public:
    Target* target;
    VARIABLE_NAME* lhs;
    bool is_ref;
    VARIABLE_NAME* rhs;
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
    virtual Assign_var_var* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Push_array ::= Target? lhs:VARIABLE_NAME is_ref:"&" rhs:VARIABLE_NAME ;
class Push_array : virtual public Statement
{
public:
    Push_array(Target* target, VARIABLE_NAME* lhs, bool is_ref, VARIABLE_NAME* rhs);
protected:
    Push_array();
public:
    Target* target;
    VARIABLE_NAME* lhs;
    bool is_ref;
    VARIABLE_NAME* rhs;
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
    virtual Push_array* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Eval_expr ::= Expr ;
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
    static const int ID = 28;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Literal ::= INT<long> | REAL<double> | STRING<String*> | BOOL<bool> | NIL<>;
class Literal : virtual public Expr, virtual public Static_value, virtual public Static_array_key
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
    virtual void find_all(Node* in, List<Node*>* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
};

// Cast ::= CAST VARIABLE_NAME ;
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
    static const int ID = 29;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Cast(const char* type, VARIABLE_NAME* variable_name);
};

// Unary_op ::= OP VARIABLE_NAME ;
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
    static const int ID = 30;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Unary_op(VARIABLE_NAME* variable_name, const char* op);
};

// Bin_op ::= left:VARIABLE_NAME OP right:VARIABLE_NAME ;
class Bin_op : virtual public Expr
{
public:
    Bin_op(VARIABLE_NAME* left, OP* op, VARIABLE_NAME* right);
protected:
    Bin_op();
public:
    VARIABLE_NAME* left;
    OP* op;
    VARIABLE_NAME* right;
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
    virtual Bin_op* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Bin_op(VARIABLE_NAME* left, VARIABLE_NAME* right, const char* op);
};

// Constant ::= CLASS_NAME? CONSTANT_NAME ;
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
    static const int ID = 32;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Instanceof ::= VARIABLE_NAME Class_name ;
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
    static const int ID = 33;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Variable ::= Target? Variable_name array_index:VARIABLE_NAME? ;
class Variable : virtual public Expr
{
public:
    Variable(Target* target, Variable_name* variable_name, VARIABLE_NAME* array_index);
protected:
    Variable();
public:
    Target* target;
    Variable_name* variable_name;
    VARIABLE_NAME* array_index;
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
    virtual Variable* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Variable(Variable_name* name);
    bool is_simple_variable();
};

// Reflection ::= VARIABLE_NAME ;
class Reflection : virtual public Variable_name, virtual public Method_name, virtual public Class_name
{
public:
    Reflection(VARIABLE_NAME* variable_name);
protected:
    Reflection();
public:
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
    virtual Reflection* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Pre_op ::= OP Variable ;
class Pre_op : virtual public Statement
{
public:
    Pre_op(OP* op, Variable* variable);
protected:
    Pre_op();
public:
    OP* op;
    Variable* variable;
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
    virtual Pre_op* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Pre_op(Variable* var, const char* op);
};

// Array ::= Array_elem* ;
class Array : virtual public Expr
{
public:
    Array(List<Array_elem*>* array_elems);
protected:
    Array();
public:
    List<Array_elem*>* array_elems;
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
    virtual Array* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Method_invocation ::= Target? Method_name Actual_parameter* ;
class Method_invocation : virtual public Expr
{
public:
    Method_invocation(Target* target, Method_name* method_name, List<Actual_parameter*>* actual_parameters);
protected:
    Method_invocation();
public:
    Target* target;
    Method_name* method_name;
    List<Actual_parameter*>* actual_parameters;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Method_invocation(const char* name, Actual_parameter* arg);
    Method_invocation(METHOD_NAME* name, Actual_parameter* arg);
};

// New ::= Class_name Actual_parameter* ;
class New : virtual public Expr
{
public:
    New(Class_name* class_name, List<Actual_parameter*>* actual_parameters);
protected:
    New();
public:
    Class_name* class_name;
    List<Actual_parameter*>* actual_parameters;
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
    virtual New* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Static_array ::= Static_array_elem* ;
class Static_array : virtual public Static_value
{
public:
    Static_array(List<Static_array_elem*>* static_array_elems);
protected:
    Static_array();
public:
    List<Static_array_elem*>* static_array_elems;
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
    virtual Static_array* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

// Foreign_statement ::= ;
class Foreign_statement : virtual public Statement, virtual public Foreign
{
public:
    Foreign_statement();
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
    virtual Foreign_statement* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
//  TODO: modify maketea to allow contructors with :
public:
    Foreign_statement(IR ::Node* foreign);
};

// Foreign_expr ::= ;
class Foreign_expr : virtual public Expr, virtual public Foreign
{
public:
    Foreign_expr();
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
    virtual Foreign_expr* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    Foreign_expr(IR ::Node* foreign);
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
    static const int ID = 46;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
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
    static const int ID = 47;
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
    virtual void find_all(Node* in, List<Node*>* out);
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
    static const int ID = 48;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
};

class VARIABLE_NAME : virtual public Variable_name, virtual public Target, virtual public Identifier
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
    static const int ID = 49;
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
    virtual void find_all(Node* in, List<Node*>* out);
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
    static const int ID = 55;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
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
    static const int ID = 56;
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
    virtual void find_all(Node* in, List<Node*>* out);
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
    static const int ID = 57;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
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
    static const int ID = 50;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  Constructors can't call virtual functions, so we create a non-virtual to
    //  do the work. This is then called by the virtual function, and is also
    //  safely called from the constructor.
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
    static const int ID = 51;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in INT::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
public:
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
    static const int ID = 52;
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
    virtual void find_all(Node* in, List<Node*>* out);
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
    static const int ID = 53;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in INT::_get_value_as_string ()
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
    static const int ID = 54;
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
    virtual void find_all(Node* in, List<Node*>* out);
public:
    virtual void assert_valid();
public:
    virtual String* get_value_as_string();
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

	virtual void find_all(Node* in, List<Node*>* out)
	{
		assert (0); // I'm not sure what this would mean
	}
public:
	static const int ID = 58;
	int classid()
	{
		return ID;
	}
};

}

#endif
