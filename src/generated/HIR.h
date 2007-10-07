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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


namespace HIR{
class HIR_node;
class HIR_php_script;
class HIR_statement;
class HIR_class_mod;
class HIR_member;
class HIR_signature;
class HIR_method_mod;
class HIR_formal_parameter;
class HIR_type;
class HIR_attr_mod;
class HIR_catch;
class HIR_variable_name;
class HIR_target;
class HIR_array_elem;
class HIR_method_name;
class HIR_actual_parameter;
class HIR_class_name;
class HIR_identifier;
class HIR_class_def;
class HIR_interface_def;
class HIR_method;
class HIR_attribute;
class HIR_return;
class HIR_static_declaration;
class HIR_global;
class HIR_try;
class HIR_throw;
class HIR_eval_expr;
class HIR_branch;
class HIR_goto;
class HIR_label;
class HIR_expr;
class HIR_reflection;
class Token_class_name;
class Token_interface_name;
class Token_method_name;
class Token_variable_name;
class Token_label_name;
class Token_cast;
class Token_op;
class Token_constant_name;
class HIR_literal;
class HIR_assignment;
class HIR_cast;
class HIR_unary_op;
class HIR_bin_op;
class HIR_constant;
class HIR_instanceof;
class HIR_variable;
class HIR_pre_op;
class HIR_array;
class HIR_method_invocation;
class HIR_new;
class Token_int;
class Token_real;
class Token_string;
class Token_bool;
class Token_null;

class HIR_transform;
class HIR_visitor;

// node ::= php_script | statement | class_mod | member | signature | method_mod | formal_parameter | type | attr_mod | catch | variable_name | target | array_elem | method_name | actual_parameter | class_name | identifier;
class HIR_node : virtual public Object
{
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_node* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    AttrMap* attrs;
    //  Return the line number of the node (or 0 if unknown)
    int get_line_number();
    //  Return the filename of the node (or NULL if unknown)
    String* get_filename();
    HIR_node();
    void clone_mixin_from(HIR_node* in);
    void assert_mixin_valid();
    bool is_mixin_equal(HIR_node* in);
    //  Return the comments associated with the node
    List<String*>* get_comments();
};

// php_script ::= statement* ;
class HIR_php_script : virtual public HIR_node
{
public:
    HIR_php_script(List<HIR_statement*>* statements);
protected:
    HIR_php_script();
public:
    List<HIR_statement*>* statements;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 1;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_php_script* clone();
public:
    virtual void assert_valid();
};

// statement ::= class_def | interface_def | method | return | static_declaration | global | try | throw | eval_expr | label | goto | branch;
class HIR_statement : virtual public HIR_node
{
public:
    HIR_statement();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_statement* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// class_mod ::= "abstract"? "final"? ;
class HIR_class_mod : virtual public HIR_node
{
public:
    HIR_class_mod(bool is_abstract, bool is_final);
protected:
    HIR_class_mod();
public:
    bool is_abstract;
    bool is_final;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 3;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_class_mod* clone();
public:
    virtual void assert_valid();
};

// member ::= method | attribute;
class HIR_member : virtual public HIR_node
{
public:
    HIR_member();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_member* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// signature ::= method_mod is_ref:"&" METHOD_NAME formal_parameter* ;
class HIR_signature : virtual public HIR_node
{
public:
    HIR_signature(HIR_method_mod* method_mod, bool is_ref, Token_method_name* method_name, List<HIR_formal_parameter*>* formal_parameters);
protected:
    HIR_signature();
public:
    HIR_method_mod* method_mod;
    bool is_ref;
    Token_method_name* method_name;
    List<HIR_formal_parameter*>* formal_parameters;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 6;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_signature* clone();
public:
    virtual void assert_valid();
public:
    HIR_signature(const char* name);
};

// method_mod ::= "public"? "protected"? "private"? "static"? "abstract"? "final"? ;
class HIR_method_mod : virtual public HIR_node
{
public:
    HIR_method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final);
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_abstract;
    bool is_final;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 7;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_method_mod* clone();
public:
    virtual void assert_valid();
public:
    HIR_method_mod();
    HIR_method_mod(HIR_method_mod* a, HIR_method_mod* b);
    static HIR_method_mod* new_PUBLIC();
    static HIR_method_mod* new_PROTECTED();
    static HIR_method_mod* new_PRIVATE();
    static HIR_method_mod* new_STATIC();
    static HIR_method_mod* new_ABSTRACT();
    static HIR_method_mod* new_FINAL();
};

// formal_parameter ::= type is_ref:"&" VARIABLE_NAME expr? ;
class HIR_formal_parameter : virtual public HIR_node
{
public:
    HIR_formal_parameter(HIR_type* type, bool is_ref, Token_variable_name* variable_name, HIR_expr* expr);
protected:
    HIR_formal_parameter();
public:
    HIR_type* type;
    bool is_ref;
    Token_variable_name* variable_name;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 8;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_formal_parameter* clone();
public:
    virtual void assert_valid();
public:
    HIR_formal_parameter(HIR_type* type, Token_variable_name* name);
    HIR_formal_parameter(HIR_type* type, bool is_ref, Token_variable_name* name);
};

// type ::= CLASS_NAME? ;
class HIR_type : virtual public HIR_node
{
public:
    HIR_type(Token_class_name* class_name);
protected:
    HIR_type();
public:
    Token_class_name* class_name;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 9;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_type* clone();
public:
    virtual void assert_valid();
};

// attr_mod ::= "public"? "protected"? "private"? "static"? "const"? ;
class HIR_attr_mod : virtual public HIR_node
{
public:
    HIR_attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const);
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_const;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 11;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_attr_mod* clone();
public:
    virtual void assert_valid();
public:
    HIR_attr_mod();
    HIR_attr_mod(HIR_method_mod* mm);
    static HIR_attr_mod* new_PUBLIC();
    static HIR_attr_mod* new_PROTECTED();
    static HIR_attr_mod* new_PRIVATE();
    static HIR_attr_mod* new_STATIC();
    static HIR_attr_mod* new_CONST();
};

// catch ::= CLASS_NAME VARIABLE_NAME statement* ;
class HIR_catch : virtual public HIR_node
{
public:
    HIR_catch(Token_class_name* class_name, Token_variable_name* variable_name, List<HIR_statement*>* statements);
protected:
    HIR_catch();
public:
    Token_class_name* class_name;
    Token_variable_name* variable_name;
    List<HIR_statement*>* statements;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 16;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_catch* clone();
public:
    virtual void assert_valid();
};

// variable_name ::= VARIABLE_NAME | reflection;
class HIR_variable_name : virtual public HIR_node
{
public:
    HIR_variable_name();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_variable_name* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// target ::= expr | CLASS_NAME;
class HIR_target : virtual public HIR_node
{
public:
    HIR_target();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_target* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// array_elem ::= key:expr? is_ref:"&" val:expr ;
class HIR_array_elem : virtual public HIR_node
{
public:
    HIR_array_elem(HIR_expr* key, bool is_ref, HIR_expr* val);
protected:
    HIR_array_elem();
public:
    HIR_expr* key;
    bool is_ref;
    HIR_expr* val;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 32;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_array_elem* clone();
public:
    virtual void assert_valid();
};

// method_name ::= METHOD_NAME | reflection;
class HIR_method_name : virtual public HIR_node
{
public:
    HIR_method_name();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_method_name* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// actual_parameter ::= is_ref:"&" expr ;
class HIR_actual_parameter : virtual public HIR_node
{
public:
    HIR_actual_parameter(bool is_ref, HIR_expr* expr);
protected:
    HIR_actual_parameter();
public:
    bool is_ref;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 34;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_actual_parameter* clone();
public:
    virtual void assert_valid();
};

// class_name ::= CLASS_NAME | reflection;
class HIR_class_name : virtual public HIR_node
{
public:
    HIR_class_name();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_class_name* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | CAST | OP | CONSTANT_NAME | LABEL_NAME;
class HIR_identifier : virtual public HIR_node
{
public:
    HIR_identifier();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_identifier* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
};

// class_def ::= class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* member* ;
class HIR_class_def : virtual public HIR_statement
{
public:
    HIR_class_def(HIR_class_mod* class_mod, Token_class_name* class_name, Token_class_name* extends, List<Token_interface_name*>* implements, List<HIR_member*>* members);
protected:
    HIR_class_def();
public:
    HIR_class_mod* class_mod;
    Token_class_name* class_name;
    Token_class_name* extends;
    List<Token_interface_name*>* implements;
    List<HIR_member*>* members;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 2;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_class_def* clone();
public:
    virtual void assert_valid();
public:
    HIR_class_def(HIR_class_mod* mod);
    HIR_class_def(const char* name);
    void add_member(HIR_member* member);
    //  Returns NULL if the method could not be found
    HIR_method* get_method(const char* name);
};

// interface_def ::= INTERFACE_NAME extends:INTERFACE_NAME* member* ;
class HIR_interface_def : virtual public HIR_statement
{
public:
    HIR_interface_def(Token_interface_name* interface_name, List<Token_interface_name*>* extends, List<HIR_member*>* members);
protected:
    HIR_interface_def();
public:
    Token_interface_name* interface_name;
    List<Token_interface_name*>* extends;
    List<HIR_member*>* members;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 4;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_interface_def* clone();
public:
    virtual void assert_valid();
};

// method ::= signature statement*? ;
class HIR_method : virtual public HIR_statement, virtual public HIR_member
{
public:
    HIR_method(HIR_signature* signature, List<HIR_statement*>* statements);
protected:
    HIR_method();
public:
    HIR_signature* signature;
    List<HIR_statement*>* statements;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 5;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_method* clone();
public:
    virtual void assert_valid();
};

// attribute ::= attr_mod VARIABLE_NAME expr? ;
class HIR_attribute : virtual public HIR_member
{
public:
    HIR_attribute(HIR_attr_mod* attr_mod, Token_variable_name* variable_name, HIR_expr* expr);
protected:
    HIR_attribute();
public:
    HIR_attr_mod* attr_mod;
    Token_variable_name* variable_name;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 10;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_attribute* clone();
public:
    virtual void assert_valid();
};

// return ::= expr? ;
class HIR_return : virtual public HIR_statement
{
public:
    HIR_return(HIR_expr* expr);
protected:
    HIR_return();
public:
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 12;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_return* clone();
public:
    virtual void assert_valid();
};

// static_declaration ::= VARIABLE_NAME expr? ;
class HIR_static_declaration : virtual public HIR_statement
{
public:
    HIR_static_declaration(Token_variable_name* variable_name, HIR_expr* expr);
protected:
    HIR_static_declaration();
public:
    Token_variable_name* variable_name;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 13;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_static_declaration* clone();
public:
    virtual void assert_valid();
};

// global ::= variable_name ;
class HIR_global : virtual public HIR_statement
{
public:
    HIR_global(HIR_variable_name* variable_name);
protected:
    HIR_global();
public:
    HIR_variable_name* variable_name;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 14;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_global* clone();
public:
    virtual void assert_valid();
};

// try ::= statement* catches:catch* ;
class HIR_try : virtual public HIR_statement
{
public:
    HIR_try(List<HIR_statement*>* statements, List<HIR_catch*>* catches);
protected:
    HIR_try();
public:
    List<HIR_statement*>* statements;
    List<HIR_catch*>* catches;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 15;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_try* clone();
public:
    virtual void assert_valid();
};

// throw ::= expr ;
class HIR_throw : virtual public HIR_statement
{
public:
    HIR_throw(HIR_expr* expr);
protected:
    HIR_throw();
public:
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 17;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_throw* clone();
public:
    virtual void assert_valid();
};

// eval_expr ::= expr ;
class HIR_eval_expr : virtual public HIR_statement
{
public:
    HIR_eval_expr(HIR_expr* expr);
protected:
    HIR_eval_expr();
public:
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 18;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_eval_expr* clone();
public:
    virtual void assert_valid();
public:
    void _init();
};

// branch ::= expr iftrue:LABEL_NAME iffalse:LABEL_NAME ;
class HIR_branch : virtual public HIR_statement
{
public:
    HIR_branch(HIR_expr* expr, Token_label_name* iftrue, Token_label_name* iffalse);
protected:
    HIR_branch();
public:
    HIR_expr* expr;
    Token_label_name* iftrue;
    Token_label_name* iffalse;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 19;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_branch* clone();
public:
    virtual void assert_valid();
};

// goto ::= LABEL_NAME ;
class HIR_goto : virtual public HIR_statement
{
public:
    HIR_goto(Token_label_name* label_name);
protected:
    HIR_goto();
public:
    Token_label_name* label_name;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 20;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_goto* clone();
public:
    virtual void assert_valid();
};

// label ::= LABEL_NAME ;
class HIR_label : virtual public HIR_statement
{
public:
    HIR_label(Token_label_name* label_name);
protected:
    HIR_label();
public:
    Token_label_name* label_name;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 21;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_label* clone();
public:
    virtual void assert_valid();
};

// expr ::= assignment | cast | unary_op | bin_op | constant | instanceof | variable | pre_op | array | method_invocation | new | literal;
class HIR_expr : virtual public HIR_target
{
public:
    HIR_expr();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_expr* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// reflection ::= expr ;
class HIR_reflection : virtual public HIR_variable_name, virtual public HIR_method_name, virtual public HIR_class_name
{
public:
    HIR_reflection(HIR_expr* expr);
protected:
    HIR_reflection();
public:
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 29;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_reflection* clone();
public:
    virtual void assert_valid();
};

class Token_class_name : virtual public HIR_target, virtual public HIR_class_name, virtual public HIR_identifier
{
public:
    Token_class_name(String* value);
protected:
    Token_class_name();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 36;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_class_name* clone();
public:
    virtual void assert_valid();
};

class Token_interface_name : virtual public HIR_identifier
{
public:
    Token_interface_name(String* value);
protected:
    Token_interface_name();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 37;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_interface_name* clone();
public:
    virtual void assert_valid();
};

class Token_method_name : virtual public HIR_method_name, virtual public HIR_identifier
{
public:
    Token_method_name(String* value);
protected:
    Token_method_name();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 38;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_method_name* clone();
public:
    virtual void assert_valid();
};

class Token_variable_name : virtual public HIR_variable_name, virtual public HIR_identifier
{
public:
    Token_variable_name(String* value);
protected:
    Token_variable_name();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 39;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_variable_name* clone();
public:
    virtual void assert_valid();
};

class Token_label_name : virtual public HIR_identifier
{
public:
    Token_label_name(String* value);
protected:
    Token_label_name();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 40;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_label_name* clone();
public:
    virtual void assert_valid();
};

class Token_cast : virtual public HIR_identifier
{
public:
    Token_cast(String* value);
protected:
    Token_cast();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 46;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_cast* clone();
public:
    virtual void assert_valid();
};

class Token_op : virtual public HIR_identifier
{
public:
    Token_op(String* value);
protected:
    Token_op();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 47;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_op* clone();
public:
    virtual void assert_valid();
};

class Token_constant_name : virtual public HIR_identifier
{
public:
    Token_constant_name(String* value);
protected:
    Token_constant_name();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 48;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_constant_name* clone();
public:
    virtual void assert_valid();
};

// literal ::= INT<long> | REAL<double> | STRING<String*> | BOOL<bool> | NULL<>;
class HIR_literal : virtual public HIR_expr
{
public:
    HIR_literal();
public:
    virtual void visit(HIR_visitor* visitor) = 0;
    virtual void transform_children(HIR_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(HIR_node* in) = 0;
public:
    virtual bool equals(HIR_node* in) = 0;
public:
    virtual HIR_literal* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
    virtual String* get_source_rep() = 0;
};

// assignment ::= variable is_ref:"&" expr ;
class HIR_assignment : virtual public HIR_expr
{
public:
    HIR_assignment(HIR_variable* variable, bool is_ref, HIR_expr* expr);
protected:
    HIR_assignment();
public:
    HIR_variable* variable;
    bool is_ref;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 22;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_assignment* clone();
public:
    virtual void assert_valid();
};

// cast ::= CAST expr ;
class HIR_cast : virtual public HIR_expr
{
public:
    HIR_cast(Token_cast* cast, HIR_expr* expr);
protected:
    HIR_cast();
public:
    Token_cast* cast;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 23;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_cast* clone();
public:
    virtual void assert_valid();
public:
    HIR_cast(const char* cast, HIR_expr* expr);
};

// unary_op ::= OP expr ;
class HIR_unary_op : virtual public HIR_expr
{
public:
    HIR_unary_op(Token_op* op, HIR_expr* expr);
protected:
    HIR_unary_op();
public:
    Token_op* op;
    HIR_expr* expr;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 24;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_unary_op* clone();
public:
    virtual void assert_valid();
public:
    HIR_unary_op(HIR_expr* expr, const char* op);
};

// bin_op ::= left:expr OP right:expr ;
class HIR_bin_op : virtual public HIR_expr
{
public:
    HIR_bin_op(HIR_expr* left, Token_op* op, HIR_expr* right);
protected:
    HIR_bin_op();
public:
    HIR_expr* left;
    Token_op* op;
    HIR_expr* right;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 25;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_bin_op* clone();
public:
    virtual void assert_valid();
public:
    HIR_bin_op(HIR_expr* left, HIR_expr* right, const char* op);
};

// constant ::= CLASS_NAME? CONSTANT_NAME ;
class HIR_constant : virtual public HIR_expr
{
public:
    HIR_constant(Token_class_name* class_name, Token_constant_name* constant_name);
protected:
    HIR_constant();
public:
    Token_class_name* class_name;
    Token_constant_name* constant_name;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 26;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_constant* clone();
public:
    virtual void assert_valid();
};

// instanceof ::= expr class_name ;
class HIR_instanceof : virtual public HIR_expr
{
public:
    HIR_instanceof(HIR_expr* expr, HIR_class_name* class_name);
protected:
    HIR_instanceof();
public:
    HIR_expr* expr;
    HIR_class_name* class_name;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 27;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_instanceof* clone();
public:
    virtual void assert_valid();
};

// variable ::= target? variable_name array_indices:expr?* ;
class HIR_variable : virtual public HIR_expr
{
public:
    HIR_variable(HIR_target* target, HIR_variable_name* variable_name, List<HIR_expr*>* array_indices);
protected:
    HIR_variable();
public:
    HIR_target* target;
    HIR_variable_name* variable_name;
    List<HIR_expr*>* array_indices;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 28;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_variable* clone();
public:
    virtual void assert_valid();
public:
    HIR_variable(HIR_variable_name* name);
};

// pre_op ::= OP variable ;
class HIR_pre_op : virtual public HIR_expr
{
public:
    HIR_pre_op(Token_op* op, HIR_variable* variable);
protected:
    HIR_pre_op();
public:
    Token_op* op;
    HIR_variable* variable;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 30;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_pre_op* clone();
public:
    virtual void assert_valid();
public:
    HIR_pre_op(HIR_variable* var, const char* op);
};

// array ::= array_elem* ;
class HIR_array : virtual public HIR_expr
{
public:
    HIR_array(List<HIR_array_elem*>* array_elems);
protected:
    HIR_array();
public:
    List<HIR_array_elem*>* array_elems;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 31;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_array* clone();
public:
    virtual void assert_valid();
};

// method_invocation ::= target? method_name actual_parameter* ;
class HIR_method_invocation : virtual public HIR_expr
{
public:
    HIR_method_invocation(HIR_target* target, HIR_method_name* method_name, List<HIR_actual_parameter*>* actual_parameters);
protected:
    HIR_method_invocation();
public:
    HIR_target* target;
    HIR_method_name* method_name;
    List<HIR_actual_parameter*>* actual_parameters;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 33;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_method_invocation* clone();
public:
    virtual void assert_valid();
public:
    HIR_method_invocation(const char* name, HIR_expr* arg);
    HIR_method_invocation(Token_method_name* name, HIR_expr* arg);
};

// new ::= class_name actual_parameter* ;
class HIR_new : virtual public HIR_expr
{
public:
    HIR_new(HIR_class_name* class_name, List<HIR_actual_parameter*>* actual_parameters);
protected:
    HIR_new();
public:
    HIR_class_name* class_name;
    List<HIR_actual_parameter*>* actual_parameters;
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    static const int ID = 35;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual HIR_new* clone();
public:
    virtual void assert_valid();
};

class Token_int : virtual public HIR_literal
{
public:
    Token_int(long value, String* source_rep);
protected:
    Token_int();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    long value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 41;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
    virtual bool match_value(Token_int* that);
public:
    virtual bool equals(HIR_node* in);
    virtual bool equals_value(Token_int* that);
public:
    virtual Token_int* clone();
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
    Token_int(int v);
};

class Token_real : virtual public HIR_literal
{
public:
    Token_real(double value, String* source_rep);
protected:
    Token_real();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    double value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 42;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
    virtual bool match_value(Token_real* that);
public:
    virtual bool equals(HIR_node* in);
    virtual bool equals_value(Token_real* that);
public:
    virtual Token_real* clone();
    virtual double clone_value();
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in Token_int::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    Token_real(double v);
};

class Token_string : virtual public HIR_literal
{
public:
    Token_string(String* value, String* source_rep);
protected:
    Token_string();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 43;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
    virtual bool match_value(Token_string* that);
public:
    virtual bool equals(HIR_node* in);
    virtual bool equals_value(Token_string* that);
public:
    virtual Token_string* clone();
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
public:
    virtual String* get_value_as_string();
    bool is_value_valid();
    String* clone_value();
    Token_string(String* v);
};

class Token_bool : virtual public HIR_literal
{
public:
    Token_bool(bool value, String* source_rep);
protected:
    Token_bool();
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    bool value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 44;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
    virtual bool match_value(Token_bool* that);
public:
    virtual bool equals(HIR_node* in);
    virtual bool equals_value(Token_bool* that);
public:
    virtual Token_bool* clone();
    virtual bool clone_value();
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in Token_int::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    Token_bool(bool v);
};

class Token_null : virtual public HIR_literal
{
public:
    Token_null(String* source_rep);
public:
    virtual void visit(HIR_visitor* visitor);
    virtual void transform_children(HIR_transform* transform);
public:
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 45;
    virtual int classid();
public:
    virtual bool match(HIR_node* in);
public:
    virtual bool equals(HIR_node* in);
public:
    virtual Token_null* clone();
public:
    virtual void assert_valid();
public:
    virtual String* get_value_as_string();
    Token_null();
};


class __WILDCARD__
{
public:
	virtual ~__WILDCARD__() {}

public:
	virtual bool match(HIR_node* in) = 0;
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

	virtual bool match(HIR_node* in)
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

	virtual bool equals(HIR_node* in)
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

	virtual void visit(HIR_visitor* visitor)
	{
		if(value != NULL)
			value->visit(visitor);
	}

	virtual void transform_children(HIR_transform* transform)
	{
		if(value != NULL)
			value->transform_children(transform);
	}

public:
	static const int ID = 49;
	int classid()
	{
		return ID;
	}
};

}

#endif
