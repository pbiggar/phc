#ifndef _AST_H_
#define _AST_H_

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


namespace AST{
class Node;
class PHP_script;
class Class_mod;
class Signature;
class Method_mod;
class Formal_parameter;
class Type;
class Attr_mod;
class Name_with_default;
class Directive;
class List_element;
class Variable_name;
class Target;
class Array_elem;
class Method_name;
class Actual_parameter;
class Class_name;
class Commented_node;
class Source_rep;
class HT_ITERATOR;
class Statement;
class Member;
class Switch_case;
class Catch;
class Expr;
class Nested_list_elements;
class Reflection;
class Identifier;
class Class_def;
class Interface_def;
class Method;
class Attribute;
class If;
class While;
class Do;
class For;
class Foreach;
class Switch;
class Break;
class Continue;
class Return;
class Static_declaration;
class Global;
class Declare;
class Try;
class Throw;
class Eval_expr;
class Nop;
class Branch;
class Goto;
class Label;
class Foreach_reset;
class Foreach_next;
class Foreach_end;
class Foreach_has_key;
class Foreach_get_key;
class Foreach_get_val;
class Literal;
class Assignment;
class Op_assignment;
class List_assignment;
class Cast;
class Unary_op;
class Bin_op;
class Conditional_expr;
class Ignore_errors;
class Constant;
class Instanceof;
class Variable;
class Pre_op;
class Post_op;
class Array;
class Method_invocation;
class New;
class CLASS_NAME;
class INTERFACE_NAME;
class METHOD_NAME;
class VARIABLE_NAME;
class DIRECTIVE_NAME;
class LABEL_NAME;
class OP;
class CAST;
class CONSTANT_NAME;
class INT;
class REAL;
class STRING;
class BOOL;
class NIL;

class Transform;
class Visitor;

// Node ::= PHP_script | Class_mod | Signature | Method_mod | Formal_parameter | Type | Attr_mod | Name_with_default | Directive | List_element | Variable_name | Target | Array_elem | Method_name | Actual_parameter | Class_name | Commented_node | Source_rep | HT_ITERATOR<long>;
class Node : virtual public Object
{
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
    virtual void assert_valid() = 0;
public:
    AttrMap* attrs;
    //  Return the line number of the node (or 0 if unknown)
    int get_line_number();
    //  Return the filename of the node (or NULL if unknown)
    String* get_filename();
    Node();
    void clone_mixin_from(Node* in);
    void assert_mixin_valid();
    bool is_mixin_equal(Node* in);
};

// PHP_script ::= Statement* ;
class PHP_script : virtual public Node, virtual public IR
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
    virtual void assert_valid();
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
    virtual void assert_valid();
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

// Name_with_default ::= VARIABLE_NAME Expr? ;
class Name_with_default : virtual public Node
{
public:
    Name_with_default(VARIABLE_NAME* variable_name, Expr* expr);
protected:
    Name_with_default();
public:
    VARIABLE_NAME* variable_name;
    Expr* expr;
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
    virtual void assert_valid();
};

// Directive ::= DIRECTIVE_NAME Expr ;
class Directive : virtual public Node
{
public:
    Directive(DIRECTIVE_NAME* directive_name, Expr* expr);
protected:
    Directive();
public:
    DIRECTIVE_NAME* directive_name;
    Expr* expr;
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
    virtual Directive* clone();
public:
    virtual void assert_valid();
};

// List_element ::= Variable | Nested_list_elements;
class List_element : virtual public Node
{
public:
    List_element();
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
    virtual List_element* clone() = 0;
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
    virtual void assert_valid() = 0;
};

// Target ::= Expr | CLASS_NAME;
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
    static const int ID = 57;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Array_elem* clone();
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
    virtual void assert_valid() = 0;
};

// Actual_parameter ::= is_ref:"&" Expr ;
class Actual_parameter : virtual public Node
{
public:
    Actual_parameter(bool is_ref, Expr* expr);
protected:
    Actual_parameter();
public:
    bool is_ref;
    Expr* expr;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 59;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Actual_parameter* clone();
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
    virtual void assert_valid() = 0;
};

// Commented_node ::= Member | Statement | Interface_def | Class_def | Switch_case | Catch;
class Commented_node : virtual public Node
{
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
    virtual Commented_node* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    Commented_node();
    //  Return the comments associated with the node
    List<String*>* get_comments();
};

// Source_rep ::= Identifier | Literal;
class Source_rep : virtual public Node
{
public:
    Source_rep();
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
    virtual Source_rep* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
    bool has_source_rep();
    String* get_source_rep();
    void set_source_rep(String* source_rep);
};

class HT_ITERATOR : virtual public Node
{
public:
    HT_ITERATOR(long value);
protected:
    HT_ITERATOR();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    long value;
public:
    static const int ID = 61;
    virtual int classid();
public:
    virtual bool match(Node* in);
    virtual bool match_value(HT_ITERATOR* that);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(HT_ITERATOR* that);
public:
    virtual HT_ITERATOR* clone();
    virtual long clone_value();
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
public:
    String* get_value_as_string();
};

// Statement ::= Class_def | Interface_def | Method | Return | Static_declaration | Global | Try | Throw | Eval_expr | If | While | Do | For | Foreach | Switch | Break | Continue | Declare | Nop | Label | Goto | Branch | Foreach_next | Foreach_reset | Foreach_end;
class Statement : virtual public Commented_node
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
    virtual void assert_valid() = 0;
};

// Member ::= Method | Attribute;
class Member : virtual public Commented_node
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
    virtual void assert_valid() = 0;
};

// Switch_case ::= Expr? Statement* ;
class Switch_case : virtual public Commented_node
{
public:
    Switch_case(Expr* expr, List<Statement*>* statements);
protected:
    Switch_case();
public:
    Expr* expr;
    List<Statement*>* statements;
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
    virtual Switch_case* clone();
public:
    virtual void assert_valid();
};

// Catch ::= CLASS_NAME VARIABLE_NAME Statement* ;
class Catch : virtual public Commented_node
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
    static const int ID = 28;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Catch* clone();
public:
    virtual void assert_valid();
};

// Expr ::= Assignment | Cast | Unary_op | Bin_op | Constant | Instanceof | Variable | Pre_op | Method_invocation | New | Literal | Op_assignment | List_assignment | Post_op | Array | Conditional_expr | Ignore_errors | Foreach_has_key | Foreach_get_key | Foreach_get_val;
class Expr : virtual public Target
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
    virtual void assert_valid() = 0;
};

// Nested_list_elements ::= List_element?* ;
class Nested_list_elements : virtual public List_element
{
public:
    Nested_list_elements(List<List_element*>* list_elements);
protected:
    Nested_list_elements();
public:
    List<List_element*>* list_elements;
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
    virtual Nested_list_elements* clone();
public:
    virtual void assert_valid();
};

// Reflection ::= Expr ;
class Reflection : virtual public Variable_name, virtual public Method_name, virtual public Class_name
{
public:
    Reflection(Expr* expr);
protected:
    Reflection();
public:
    Expr* expr;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 53;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Reflection* clone();
public:
    virtual void assert_valid();
};

// Identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | CAST<String*> | OP | CONSTANT_NAME | LABEL_NAME | DIRECTIVE_NAME;
class Identifier : virtual public Source_rep
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
    virtual void assert_valid() = 0;
};

// Class_def ::= Class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* Member* ;
class Class_def : virtual public Statement, virtual public Commented_node
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
    virtual void assert_valid();
public:
    Class_def(Class_mod* mod);
    Class_def(const char* name);
    void add_member(Member* member);
    //  Returns NULL if the method could not be found
    Method* get_method(const char* name);
};

// Interface_def ::= INTERFACE_NAME extends:INTERFACE_NAME* Member* ;
class Interface_def : virtual public Statement, virtual public Commented_node
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
    virtual void assert_valid();
};

// Attribute ::= Attr_mod vars:Name_with_default* ;
class Attribute : virtual public Member
{
public:
    Attribute(Attr_mod* attr_mod, List<Name_with_default*>* vars);
protected:
    Attribute();
public:
    Attr_mod* attr_mod;
    List<Name_with_default*>* vars;
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
    virtual void assert_valid();
};

// If ::= Expr iftrue:Statement* iffalse:Statement* ;
class If : virtual public Statement
{
public:
    If(Expr* expr, List<Statement*>* iftrue, List<Statement*>* iffalse);
protected:
    If();
public:
    Expr* expr;
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
    virtual void assert_valid();
public:
    If(Expr* expr);
};

// While ::= Expr Statement* ;
class While : virtual public Statement
{
public:
    While(Expr* expr, List<Statement*>* statements);
protected:
    While();
public:
    Expr* expr;
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
    virtual While* clone();
public:
    virtual void assert_valid();
};

// Do ::= Statement* Expr ;
class Do : virtual public Statement
{
public:
    Do(List<Statement*>* statements, Expr* expr);
protected:
    Do();
public:
    List<Statement*>* statements;
    Expr* expr;
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
    virtual Do* clone();
public:
    virtual void assert_valid();
};

// For ::= init:Expr? cond:Expr? incr:Expr? Statement* ;
class For : virtual public Statement
{
public:
    For(Expr* init, Expr* cond, Expr* incr, List<Statement*>* statements);
protected:
    For();
public:
    Expr* init;
    Expr* cond;
    Expr* incr;
    List<Statement*>* statements;
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
    virtual For* clone();
public:
    virtual void assert_valid();
};

// Foreach ::= Expr key:Variable? is_ref:"&" val:Variable Statement* ;
class Foreach : virtual public Statement
{
public:
    Foreach(Expr* expr, Variable* key, bool is_ref, Variable* val, List<Statement*>* statements);
protected:
    Foreach();
public:
    Expr* expr;
    Variable* key;
    bool is_ref;
    Variable* val;
    List<Statement*>* statements;
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
    virtual Foreach* clone();
public:
    virtual void assert_valid();
};

// Switch ::= Expr Switch_case* ;
class Switch : virtual public Statement
{
public:
    Switch(Expr* expr, List<Switch_case*>* switch_cases);
protected:
    Switch();
public:
    Expr* expr;
    List<Switch_case*>* switch_cases;
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
    virtual Switch* clone();
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
    static const int ID = 20;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Break* clone();
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
    static const int ID = 21;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Continue* clone();
public:
    virtual void assert_valid();
};

// Return ::= Expr? ;
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
    static const int ID = 22;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Return* clone();
public:
    virtual void assert_valid();
};

// Static_declaration ::= vars:Name_with_default* ;
class Static_declaration : virtual public Statement
{
public:
    Static_declaration(List<Name_with_default*>* vars);
protected:
    Static_declaration();
public:
    List<Name_with_default*>* vars;
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
    virtual Static_declaration* clone();
public:
    virtual void assert_valid();
};

// Global ::= Variable_name* ;
class Global : virtual public Statement
{
public:
    Global(List<Variable_name*>* variable_names);
protected:
    Global();
public:
    List<Variable_name*>* variable_names;
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
    virtual Global* clone();
public:
    virtual void assert_valid();
};

// Declare ::= Directive* Statement* ;
class Declare : virtual public Statement
{
public:
    Declare(List<Directive*>* directives, List<Statement*>* statements);
protected:
    Declare();
public:
    List<Directive*>* directives;
    List<Statement*>* statements;
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
    virtual Declare* clone();
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
    static const int ID = 27;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Try* clone();
public:
    virtual void assert_valid();
};

// Throw ::= Expr ;
class Throw : virtual public Statement
{
public:
    Throw(Expr* expr);
protected:
    Throw();
public:
    Expr* expr;
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
    virtual Throw* clone();
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
    static const int ID = 30;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Eval_expr* clone();
public:
    virtual void assert_valid();
public:
    void _init();
};

// Nop ::= ;
class Nop : virtual public Statement
{
public:
    Nop();
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
    virtual Nop* clone();
public:
    virtual void assert_valid();
};

// Branch ::= Expr iftrue:LABEL_NAME iffalse:LABEL_NAME ;
class Branch : virtual public Statement
{
public:
    Branch(Expr* expr, LABEL_NAME* iftrue, LABEL_NAME* iffalse);
protected:
    Branch();
public:
    Expr* expr;
    LABEL_NAME* iftrue;
    LABEL_NAME* iffalse;
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
    virtual Branch* clone();
public:
    virtual void assert_valid();
};

// Goto ::= LABEL_NAME ;
class Goto : virtual public Statement
{
public:
    Goto(LABEL_NAME* label_name);
protected:
    Goto();
public:
    LABEL_NAME* label_name;
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
    virtual Goto* clone();
public:
    virtual void assert_valid();
};

// Label ::= LABEL_NAME ;
class Label : virtual public Statement
{
public:
    Label(LABEL_NAME* label_name);
protected:
    Label();
public:
    LABEL_NAME* label_name;
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
    virtual Label* clone();
public:
    virtual void assert_valid();
};

// Foreach_reset ::= array:VARIABLE_NAME iter:HT_ITERATOR<long> ;
class Foreach_reset : virtual public Statement
{
public:
    Foreach_reset(VARIABLE_NAME* array, HT_ITERATOR* iter);
protected:
    Foreach_reset();
public:
    VARIABLE_NAME* array;
    HT_ITERATOR* iter;
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
    virtual Foreach_reset* clone();
public:
    virtual void assert_valid();
};

// Foreach_next ::= array:VARIABLE_NAME iter:HT_ITERATOR<long> ;
class Foreach_next : virtual public Statement
{
public:
    Foreach_next(VARIABLE_NAME* array, HT_ITERATOR* iter);
protected:
    Foreach_next();
public:
    VARIABLE_NAME* array;
    HT_ITERATOR* iter;
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
    virtual Foreach_next* clone();
public:
    virtual void assert_valid();
};

// Foreach_end ::= array:VARIABLE_NAME iter:HT_ITERATOR<long> ;
class Foreach_end : virtual public Statement
{
public:
    Foreach_end(VARIABLE_NAME* array, HT_ITERATOR* iter);
protected:
    Foreach_end();
public:
    VARIABLE_NAME* array;
    HT_ITERATOR* iter;
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
    virtual Foreach_end* clone();
public:
    virtual void assert_valid();
};

// Foreach_has_key ::= array:VARIABLE_NAME iter:HT_ITERATOR<long> ;
class Foreach_has_key : virtual public Expr
{
public:
    Foreach_has_key(VARIABLE_NAME* array, HT_ITERATOR* iter);
protected:
    Foreach_has_key();
public:
    VARIABLE_NAME* array;
    HT_ITERATOR* iter;
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
    virtual Foreach_has_key* clone();
public:
    virtual void assert_valid();
};

// Foreach_get_key ::= array:VARIABLE_NAME iter:HT_ITERATOR<long> ;
class Foreach_get_key : virtual public Expr
{
public:
    Foreach_get_key(VARIABLE_NAME* array, HT_ITERATOR* iter);
protected:
    Foreach_get_key();
public:
    VARIABLE_NAME* array;
    HT_ITERATOR* iter;
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
    virtual Foreach_get_key* clone();
public:
    virtual void assert_valid();
};

// Foreach_get_val ::= array:VARIABLE_NAME key:VARIABLE_NAME iter:HT_ITERATOR<long> ;
class Foreach_get_val : virtual public Expr
{
public:
    Foreach_get_val(VARIABLE_NAME* array, VARIABLE_NAME* key, HT_ITERATOR* iter);
protected:
    Foreach_get_val();
public:
    VARIABLE_NAME* array;
    VARIABLE_NAME* key;
    HT_ITERATOR* iter;
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
    virtual Foreach_get_val* clone();
public:
    virtual void assert_valid();
};

// Literal ::= INT<long> | REAL<double> | STRING<String*> | BOOL<bool> | NIL<>;
class Literal : virtual public Expr, virtual public Source_rep
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
    virtual void assert_valid() = 0;
};

// Assignment ::= Variable is_ref:"&" Expr ;
class Assignment : virtual public Expr
{
public:
    Assignment(Variable* variable, bool is_ref, Expr* expr);
protected:
    Assignment();
public:
    Variable* variable;
    bool is_ref;
    Expr* expr;
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
    virtual Assignment* clone();
public:
    virtual void assert_valid();
};

// Op_assignment ::= Variable OP Expr ;
class Op_assignment : virtual public Expr
{
public:
    Op_assignment(Variable* variable, OP* op, Expr* expr);
protected:
    Op_assignment();
public:
    Variable* variable;
    OP* op;
    Expr* expr;
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
    virtual Op_assignment* clone();
public:
    virtual void assert_valid();
public:
    Op_assignment(Variable* variable, const char* op, Expr* expr);
};

// List_assignment ::= List_element?* Expr ;
class List_assignment : virtual public Expr
{
public:
    List_assignment(List<List_element*>* list_elements, Expr* expr);
protected:
    List_assignment();
public:
    List<List_element*>* list_elements;
    Expr* expr;
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
    virtual List_assignment* clone();
public:
    virtual void assert_valid();
};

// Cast ::= CAST<String*> Expr ;
class Cast : virtual public Expr
{
public:
    Cast(CAST* cast, Expr* expr);
protected:
    Cast();
public:
    CAST* cast;
    Expr* expr;
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
    virtual Cast* clone();
public:
    virtual void assert_valid();
public:
    Cast(const char* type, String* source_rep, Expr* expr);
};

// Unary_op ::= OP Expr ;
class Unary_op : virtual public Expr
{
public:
    Unary_op(OP* op, Expr* expr);
protected:
    Unary_op();
public:
    OP* op;
    Expr* expr;
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
    virtual Unary_op* clone();
public:
    virtual void assert_valid();
public:
    Unary_op(Expr* expr, const char* op);
};

// Bin_op ::= left:Expr OP right:Expr ;
class Bin_op : virtual public Expr
{
public:
    Bin_op(Expr* left, OP* op, Expr* right);
protected:
    Bin_op();
public:
    Expr* left;
    OP* op;
    Expr* right;
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
    virtual Bin_op* clone();
public:
    virtual void assert_valid();
public:
    Bin_op(Expr* left, Expr* right, const char* op);
};

// Conditional_expr ::= cond:Expr iftrue:Expr iffalse:Expr ;
class Conditional_expr : virtual public Expr
{
public:
    Conditional_expr(Expr* cond, Expr* iftrue, Expr* iffalse);
protected:
    Conditional_expr();
public:
    Expr* cond;
    Expr* iftrue;
    Expr* iffalse;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 48;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Conditional_expr* clone();
public:
    virtual void assert_valid();
};

// Ignore_errors ::= Expr ;
class Ignore_errors : virtual public Expr
{
public:
    Ignore_errors(Expr* expr);
protected:
    Ignore_errors();
public:
    Expr* expr;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 49;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Ignore_errors* clone();
public:
    virtual void assert_valid();
};

// Constant ::= CLASS_NAME? CONSTANT_NAME ;
class Constant : virtual public Expr
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
    static const int ID = 50;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Constant* clone();
public:
    virtual void assert_valid();
};

// Instanceof ::= Expr Class_name ;
class Instanceof : virtual public Expr
{
public:
    Instanceof(Expr* expr, Class_name* class_name);
protected:
    Instanceof();
public:
    Expr* expr;
    Class_name* class_name;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 51;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Instanceof* clone();
public:
    virtual void assert_valid();
};

// Variable ::= Target? Variable_name array_indices:Expr?* ;
class Variable : virtual public Expr, virtual public List_element
{
public:
    Variable(Target* target, Variable_name* variable_name, List<Expr*>* array_indices);
protected:
    Variable();
public:
    Target* target;
    Variable_name* variable_name;
    List<Expr*>* array_indices;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 52;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Variable* clone();
public:
    virtual void assert_valid();
public:
    Variable(Variable_name* name);
    bool is_simple_variable();
};

// Pre_op ::= OP Variable ;
class Pre_op : virtual public Expr
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
    static const int ID = 54;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Pre_op* clone();
public:
    virtual void assert_valid();
public:
    Pre_op(Variable* var, const char* op);
};

// Post_op ::= Variable OP ;
class Post_op : virtual public Expr
{
public:
    Post_op(Variable* variable, OP* op);
protected:
    Post_op();
public:
    Variable* variable;
    OP* op;
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    static const int ID = 55;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Post_op* clone();
public:
    virtual void assert_valid();
public:
    Post_op(Variable* var, const char* op);
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
    static const int ID = 56;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Array* clone();
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
    static const int ID = 58;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Method_invocation* clone();
public:
    virtual void assert_valid();
public:
    Method_invocation(const char* name, Expr* arg);
    Method_invocation(METHOD_NAME* name, Expr* arg);
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
    static const int ID = 60;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual New* clone();
public:
    virtual void assert_valid();
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
    static const int ID = 62;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual CLASS_NAME* clone();
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
    static const int ID = 63;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual INTERFACE_NAME* clone();
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
    static const int ID = 64;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual METHOD_NAME* clone();
public:
    virtual void assert_valid();
};

class VARIABLE_NAME : virtual public Variable_name, virtual public Identifier
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
    static const int ID = 65;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual VARIABLE_NAME* clone();
public:
    virtual void assert_valid();
};

class DIRECTIVE_NAME : virtual public Identifier
{
public:
    DIRECTIVE_NAME(String* value);
protected:
    DIRECTIVE_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 66;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual DIRECTIVE_NAME* clone();
public:
    virtual void assert_valid();
};

class LABEL_NAME : virtual public Identifier
{
public:
    LABEL_NAME(String* value);
protected:
    LABEL_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 67;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual LABEL_NAME* clone();
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
    static const int ID = 73;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual OP* clone();
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
public:
    static const int ID = 74;
    virtual int classid();
public:
    virtual bool match(Node* in);
    virtual bool match_value(CAST* that);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(CAST* that);
public:
    virtual CAST* clone();
    virtual String* clone_value();
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
public:
    String* get_value_as_string();
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
    static const int ID = 75;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual CONSTANT_NAME* clone();
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
    static const int ID = 68;
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
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  Constructors can't call virtual functions, so we create a non-virtual to
    //  do the work. This is then called by the virtual function, and is also
    //  safely called from the constructor.
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    INT(long v, String* source_rep);
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
    static const int ID = 69;
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
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in INT::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    REAL(double v, String* source_rep);
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
    static const int ID = 70;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(STRING* that);
public:
    virtual STRING* clone();
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
public:
    virtual String* get_value_as_string();
    bool is_value_valid();
    String* clone_value();
    STRING(String* v, String* source_rep);
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
    static const int ID = 71;
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
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in INT::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    BOOL(bool v, String* source_rep);
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
    static const int ID = 72;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual NIL* clone();
public:
    virtual void assert_valid();
public:
    virtual String* get_value_as_string();
    NIL(String* source_rep);
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

public:
	static const int ID = 76;
	int classid()
	{
		return ID;
	}
};

}

#endif
