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
#include "process_ir/Foreach.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


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
class FOREIGN;
class CLASS_NAME;
class INTERFACE_NAME;
class METHOD_NAME;
class VARIABLE_NAME;
class DIRECTIVE_NAME;
class OP;
class CAST;
class CONSTANT_NAME;
class INT;
class REAL;
class STRING;
class BOOL;
class NIL;
class None;

typedef List<Node*> Node_list;
typedef List<PHP_script*> PHP_script_list;
typedef List<Class_mod*> Class_mod_list;
typedef List<Signature*> Signature_list;
typedef List<Method_mod*> Method_mod_list;
typedef List<Formal_parameter*> Formal_parameter_list;
typedef List<Type*> Type_list;
typedef List<Attr_mod*> Attr_mod_list;
typedef List<Name_with_default*> Name_with_default_list;
typedef List<Directive*> Directive_list;
typedef List<List_element*> List_element_list;
typedef List<Variable_name*> Variable_name_list;
typedef List<Target*> Target_list;
typedef List<Array_elem*> Array_elem_list;
typedef List<Method_name*> Method_name_list;
typedef List<Actual_parameter*> Actual_parameter_list;
typedef List<Class_name*> Class_name_list;
typedef List<Commented_node*> Commented_node_list;
typedef List<Source_rep*> Source_rep_list;
typedef List<Statement*> Statement_list;
typedef List<Member*> Member_list;
typedef List<Switch_case*> Switch_case_list;
typedef List<Catch*> Catch_list;
typedef List<Expr*> Expr_list;
typedef List<Nested_list_elements*> Nested_list_elements_list;
typedef List<Reflection*> Reflection_list;
typedef List<Identifier*> Identifier_list;
typedef List<Class_def*> Class_def_list;
typedef List<Interface_def*> Interface_def_list;
typedef List<Method*> Method_list;
typedef List<Attribute*> Attribute_list;
typedef List<If*> If_list;
typedef List<While*> While_list;
typedef List<Do*> Do_list;
typedef List<For*> For_list;
typedef List<Foreach*> Foreach_list;
typedef List<Switch*> Switch_list;
typedef List<Break*> Break_list;
typedef List<Continue*> Continue_list;
typedef List<Return*> Return_list;
typedef List<Static_declaration*> Static_declaration_list;
typedef List<Global*> Global_list;
typedef List<Declare*> Declare_list;
typedef List<Try*> Try_list;
typedef List<Throw*> Throw_list;
typedef List<Eval_expr*> Eval_expr_list;
typedef List<Nop*> Nop_list;
typedef List<Literal*> Literal_list;
typedef List<Assignment*> Assignment_list;
typedef List<Op_assignment*> Op_assignment_list;
typedef List<List_assignment*> List_assignment_list;
typedef List<Cast*> Cast_list;
typedef List<Unary_op*> Unary_op_list;
typedef List<Bin_op*> Bin_op_list;
typedef List<Conditional_expr*> Conditional_expr_list;
typedef List<Ignore_errors*> Ignore_errors_list;
typedef List<Constant*> Constant_list;
typedef List<Instanceof*> Instanceof_list;
typedef List<Variable*> Variable_list;
typedef List<Pre_op*> Pre_op_list;
typedef List<Post_op*> Post_op_list;
typedef List<Array*> Array_list;
typedef List<Method_invocation*> Method_invocation_list;
typedef List<New*> New_list;
typedef List<FOREIGN*> FOREIGN_list;
typedef List<CLASS_NAME*> CLASS_NAME_list;
typedef List<INTERFACE_NAME*> INTERFACE_NAME_list;
typedef List<METHOD_NAME*> METHOD_NAME_list;
typedef List<VARIABLE_NAME*> VARIABLE_NAME_list;
typedef List<DIRECTIVE_NAME*> DIRECTIVE_NAME_list;
typedef List<OP*> OP_list;
typedef List<CAST*> CAST_list;
typedef List<CONSTANT_NAME*> CONSTANT_NAME_list;
typedef List<INT*> INT_list;
typedef List<REAL*> REAL_list;
typedef List<STRING*> STRING_list;
typedef List<BOOL*> BOOL_list;
typedef List<NIL*> NIL_list;
typedef List<None*> None_list;

class Transform;
class Visitor;

/* Node ::= PHP_script | Class_mod | Signature | Method_mod | Formal_parameter | Type | Attr_mod | Name_with_default | Directive | List_element | Variable_name | Target | Array_elem | Method_name | Actual_parameter | Class_name | Commented_node | Source_rep; */
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
    bool is_mixin_equal(Node* in);
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

/* Name_with_default ::= VARIABLE_NAME Expr? ; */
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Directive ::= DIRECTIVE_NAME Expr ; */
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* List_element ::= Variable | Nested_list_elements; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Variable_name ::= VARIABLE_NAME | Reflection; */
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
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Target ::= Expr | CLASS_NAME; */
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

/* Array_elem ::= key:Expr? is_ref:"&" val:Expr ; */
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
    static const int ID = 48;
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
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Method_name ::= METHOD_NAME | Reflection; */
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

/* Actual_parameter ::= is_ref:"&" Expr ; */
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
    static const int ID = 50;
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
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Class_name ::= CLASS_NAME | Reflection; */
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

/* Commented_node ::= Member | Statement | Interface_def | Class_def | Switch_case | Catch; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    Commented_node();
    /*  Return the comments associated with the node */
    List<String*>* get_comments();
};

/* Source_rep ::= Identifier | Literal; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
    bool has_source_rep();
    String* get_source_rep();
    void set_source_rep(String* source_rep);
};

/* Statement ::= Class_def | Interface_def | Method | Return | Static_declaration | Global | Try | Throw | Eval_expr | If | While | Do | For | Foreach | Switch | Break | Continue | Declare | Nop | FOREIGN<IR::Node*>; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Member ::= Method | Attribute; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Switch_case ::= Expr? Statement* ; */
class Switch_case : virtual public Commented_node
{
public:
    Switch_case(Expr* expr, Statement_list* statements);
protected:
    Switch_case();
public:
    Expr* expr;
    Statement_list* statements;
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Catch ::= CLASS_NAME VARIABLE_NAME Statement* ; */
class Catch : virtual public Commented_node
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
    static const int ID = 28;
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

/* Expr ::= Assignment | Cast | Unary_op | Bin_op | Constant | Instanceof | Variable | Pre_op | Method_invocation | New | Literal | Op_assignment | List_assignment | Post_op | Array | Conditional_expr | Ignore_errors | FOREIGN<IR::Node*>; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Nested_list_elements ::= List_element?* ; */
class Nested_list_elements : virtual public List_element
{
public:
    Nested_list_elements(List_element_list* list_elements);
protected:
    Nested_list_elements();
public:
    List_element_list* list_elements;
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
    virtual Nested_list_elements* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Reflection ::= Expr ; */
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
    static const int ID = 44;
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
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | CAST | OP | CONSTANT_NAME | DIRECTIVE_NAME; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Class_def ::= Class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* Member* ; */
class Class_def : virtual public Statement, virtual public Commented_node
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
class Interface_def : virtual public Statement, virtual public Commented_node
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

/* Attribute ::= Attr_mod vars:Name_with_default* ; */
class Attribute : virtual public Member
{
public:
    Attribute(Attr_mod* attr_mod, Name_with_default_list* vars);
protected:
    Attribute();
public:
    Attr_mod* attr_mod;
    Name_with_default_list* vars;
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

/* If ::= Expr iftrue:Statement* iffalse:Statement* ; */
class If : virtual public Statement
{
public:
    If(Expr* expr, Statement_list* iftrue, Statement_list* iffalse);
protected:
    If();
public:
    Expr* expr;
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
    If(Expr* expr);
};

/* While ::= Expr Statement* ; */
class While : virtual public Statement
{
public:
    While(Expr* expr, Statement_list* statements);
protected:
    While();
public:
    Expr* expr;
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
    virtual While* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Do ::= Statement* Expr ; */
class Do : virtual public Statement
{
public:
    Do(Statement_list* statements, Expr* expr);
protected:
    Do();
public:
    Statement_list* statements;
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* For ::= init:Expr? cond:Expr? incr:Expr? Statement* ; */
class For : virtual public Statement
{
public:
    For(Expr* init, Expr* cond, Expr* incr, Statement_list* statements);
protected:
    For();
public:
    Expr* init;
    Expr* cond;
    Expr* incr;
    Statement_list* statements;
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Foreach ::= Expr key:Variable? is_ref:"&" val:Variable Statement* ; */
class Foreach : virtual public Statement
{
public:
    Foreach(Expr* expr, Variable* key, bool is_ref, Variable* val, Statement_list* statements);
protected:
    Foreach();
public:
    Expr* expr;
    Variable* key;
    bool is_ref;
    Variable* val;
    Statement_list* statements;
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Switch ::= Expr Switch_case* ; */
class Switch : virtual public Statement
{
public:
    Switch(Expr* expr, Switch_case_list* switch_cases);
protected:
    Switch();
public:
    Expr* expr;
    Switch_case_list* switch_cases;
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
    static const int ID = 20;
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
    static const int ID = 21;
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

/* Return ::= Expr? ; */
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Static_declaration ::= vars:Name_with_default* ; */
class Static_declaration : virtual public Statement
{
public:
    Static_declaration(Name_with_default_list* vars);
protected:
    Static_declaration();
public:
    Name_with_default_list* vars;
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Global ::= Variable_name* ; */
class Global : virtual public Statement
{
public:
    Global(Variable_name_list* variable_names);
protected:
    Global();
public:
    Variable_name_list* variable_names;
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Declare ::= Directive* Statement* ; */
class Declare : virtual public Statement
{
public:
    Declare(Directive_list* directives, Statement_list* statements);
protected:
    Declare();
public:
    Directive_list* directives;
    Statement_list* statements;
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
    static const int ID = 27;
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

/* Throw ::= Expr ; */
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
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
public:
    void _init();
};

/* Nop ::= ; */
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
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Literal ::= INT<long> | REAL<double> | STRING<String*> | BOOL<bool> | NIL<>; */
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
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
public:
    /*  We wish to match on this, so it cannot be pure virtual */
    virtual String* get_value_as_string();
};

/* Assignment ::= Variable is_ref:"&" Expr ; */
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
    static const int ID = 32;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Assignment* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Op_assignment ::= Variable OP Expr ; */
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
    static const int ID = 33;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Op_assignment* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Op_assignment(Variable* variable, const char* op, Expr* expr);
};

/* List_assignment ::= List_element?* Expr ; */
class List_assignment : virtual public Expr
{
public:
    List_assignment(List_element_list* list_elements, Expr* expr);
protected:
    List_assignment();
public:
    List_element_list* list_elements;
    Expr* expr;
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
    virtual List_assignment* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Cast ::= CAST Expr ; */
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
    static const int ID = 36;
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
    Cast(const char* type, String* source_rep, Expr* expr);
};

/* Unary_op ::= OP Expr ; */
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
    static const int ID = 37;
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
    Unary_op(Expr* expr, const char* op);
};

/* Bin_op ::= left:Expr OP right:Expr ; */
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
    static const int ID = 38;
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
    Bin_op(Expr* left, Expr* right, const char* op);
};

/* Conditional_expr ::= cond:Expr iftrue:Expr iffalse:Expr ; */
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
    static const int ID = 39;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Conditional_expr* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Ignore_errors ::= Expr ; */
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
    static const int ID = 40;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Ignore_errors* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Constant ::= CLASS_NAME? CONSTANT_NAME ; */
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
    static const int ID = 41;
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

/* Instanceof ::= Expr Class_name ; */
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
    static const int ID = 42;
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

/* Variable ::= Target? Variable_name array_indices:Expr?* ; */
class Variable : virtual public Expr, virtual public List_element
{
public:
    Variable(Target* target, Variable_name* variable_name, Expr_list* array_indices);
protected:
    Variable();
public:
    Target* target;
    Variable_name* variable_name;
    Expr_list* array_indices;
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
    virtual Variable* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Variable(Variable_name* name);
    bool is_simple_variable();
};

/* Pre_op ::= OP Variable ; */
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
    static const int ID = 45;
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
    Pre_op(Variable* var, const char* op);
};

/* Post_op ::= Variable OP ; */
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
    static const int ID = 46;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual Post_op* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Post_op(Variable* var, const char* op);
};

/* Array ::= Array_elem* ; */
class Array : virtual public Expr
{
public:
    Array(Array_elem_list* array_elems);
protected:
    Array();
public:
    Array_elem_list* array_elems;
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
    virtual Array* clone();
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
    static const int ID = 49;
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
    Method_invocation(const char* name, Expr* arg);
    Method_invocation(METHOD_NAME* name, Expr* arg);
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
    static const int ID = 51;
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
    static const int ID = 52;
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
    static const int ID = 53;
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
    static const int ID = 54;
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
    static const int ID = 55;
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
    static const int ID = 56;
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
    static const int ID = 57;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual DIRECTIVE_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
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
    static const int ID = 63;
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
    static const int ID = 64;
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
    static const int ID = 65;
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
    static const int ID = 58;
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
    static const int ID = 59;
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
    static const int ID = 60;
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
    static const int ID = 61;
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
    static const int ID = 62;
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
    NIL(String* source_rep);
};

/* The top of the class hierarchy. If the Fold will not allow you fold to anything else, try this. */
class None : virtual public Node, virtual public PHP_script, virtual public Statement, virtual public Class_def, virtual public Class_mod, virtual public Interface_def, virtual public Member, virtual public Method, virtual public Signature, virtual public Method_mod, virtual public Formal_parameter, virtual public Type, virtual public Attribute, virtual public Attr_mod, virtual public Name_with_default, virtual public If, virtual public While, virtual public Do, virtual public For, virtual public Foreach, virtual public Switch, virtual public Switch_case, virtual public Break, virtual public Continue, virtual public Return, virtual public Static_declaration, virtual public Global, virtual public Declare, virtual public Directive, virtual public Try, virtual public Catch, virtual public Throw, virtual public Eval_expr, virtual public Nop, virtual public Expr, virtual public Literal, virtual public Assignment, virtual public Op_assignment, virtual public List_assignment, virtual public List_element, virtual public Nested_list_elements, virtual public Cast, virtual public Unary_op, virtual public Bin_op, virtual public Conditional_expr, virtual public Ignore_errors, virtual public Constant, virtual public Instanceof, virtual public Variable, virtual public Variable_name, virtual public Reflection, virtual public Target, virtual public Pre_op, virtual public Post_op, virtual public Array, virtual public Array_elem, virtual public Method_invocation, virtual public Method_name, virtual public Actual_parameter, virtual public New, virtual public Class_name, virtual public Commented_node, virtual public Identifier, virtual public Source_rep, virtual public FOREIGN, virtual public CLASS_NAME, virtual public INTERFACE_NAME, virtual public METHOD_NAME, virtual public VARIABLE_NAME, virtual public DIRECTIVE_NAME, virtual public INT, virtual public REAL, virtual public STRING, virtual public BOOL, virtual public NIL, virtual public OP, virtual public CAST, virtual public CONSTANT_NAME
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
	static const int ID = 67;
	int classid()
	{
		return ID;
	}
};

}

#endif
