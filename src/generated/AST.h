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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


class AST_node;
class AST_php_script;
class AST_class_mod;
class AST_signature;
class AST_method_mod;
class AST_formal_parameter;
class AST_type;
class AST_attr_mod;
class AST_directive;
class AST_list_element;
class AST_variable_name;
class AST_target;
class AST_array_elem;
class AST_method_name;
class AST_actual_parameter;
class AST_class_name;
class AST_commented_node;
class AST_identifier;
class AST_interface_def;
class AST_class_def;
class AST_member;
class AST_statement;
class AST_switch_case;
class AST_catch;
class AST_expr;
class AST_list_elements;
class AST_reflection;
class Token_interface_name;
class Token_class_name;
class Token_method_name;
class Token_variable_name;
class Token_directive_name;
class Token_cast;
class Token_op;
class Token_constant_name;
class AST_method;
class AST_attribute;
class AST_if;
class AST_while;
class AST_do;
class AST_for;
class AST_foreach;
class AST_switch;
class AST_break;
class AST_continue;
class AST_return;
class AST_static_declaration;
class AST_unset;
class AST_declare;
class AST_try;
class AST_throw;
class AST_eval_expr;
class AST_nop;
class AST_literal;
class AST_assignment;
class AST_list_assignment;
class AST_cast;
class AST_unary_op;
class AST_bin_op;
class AST_conditional_expr;
class AST_ignore_errors;
class AST_constant;
class AST_instanceof;
class AST_variable;
class AST_pre_op;
class AST_post_op;
class AST_array;
class AST_method_invocation;
class AST_new;
class AST_clone;
class Token_int;
class Token_real;
class Token_string;
class Token_bool;
class Token_null;

class AST_transform;
class AST_visitor;

// node ::= php_script | class_mod | signature | method_mod | formal_parameter | type | attr_mod | directive | list_element | variable_name | target | array_elem | method_name | actual_parameter | class_name | commented_node | expr | identifier;
class AST_node : virtual public Object
{
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_node* clone() = 0;
public:
    AttrMap* attrs;
    //  Return the line number of the node (or 0 if unknown)
    int get_line_number();
    //  Return the filename of the node (or NULL if unknown)
    String* get_filename();
    AST_node();
friend class AST_transform;
friend class AST_visitor;
};

// php_script ::= interface_def* class_def* ;
class AST_php_script : virtual public AST_node
{
public:
    AST_php_script(List<AST_interface_def*>* interface_defs, List<AST_class_def*>* class_defs);
public:
    List<AST_interface_def*>* interface_defs;
    List<AST_class_def*>* class_defs;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_php_script* clone();
public:
    AST_php_script();
    //  Returns NULL if the class could not be found
    AST_class_def* get_class_def(const char* name);
public:
    void visit(AST_visitor* visitor);
    void transform(AST_transform* transform);
friend class AST_transform;
friend class AST_visitor;
};

// class_mod ::= "abstract"? "final"? ;
class AST_class_mod : virtual public AST_node
{
public:
    AST_class_mod(bool is_abstract, bool is_final);
protected:
    AST_class_mod();
public:
    bool is_abstract;
    bool is_final;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_class_mod* clone();
friend class AST_transform;
friend class AST_visitor;
};

// signature ::= method_mod is_ref:"&" METHOD_NAME formal_parameter* ;
class AST_signature : virtual public AST_node
{
public:
    AST_signature(AST_method_mod* method_mod, bool is_ref, Token_method_name* method_name, List<AST_formal_parameter*>* formal_parameters);
protected:
    AST_signature();
public:
    AST_method_mod* method_mod;
    bool is_ref;
    Token_method_name* method_name;
    List<AST_formal_parameter*>* formal_parameters;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_signature* clone();
public:
    AST_signature(const char* name);
friend class AST_transform;
friend class AST_visitor;
};

// method_mod ::= "public"? "protected"? "private"? "static"? "abstract"? "final"? ;
class AST_method_mod : virtual public AST_node
{
public:
    AST_method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final);
protected:
    AST_method_mod();
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_abstract;
    bool is_final;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_method_mod* clone();
public:
    AST_method_mod(AST_method_mod* a, AST_method_mod* b);
    static AST_method_mod* new_PUBLIC();
    static AST_method_mod* new_PROTECTED();
    static AST_method_mod* new_PRIVATE();
    static AST_method_mod* new_STATIC();
    static AST_method_mod* new_ABSTRACT();
    static AST_method_mod* new_FINAL();
friend class AST_transform;
friend class AST_visitor;
};

// formal_parameter ::= type is_ref:"&" VARIABLE_NAME expr? ;
class AST_formal_parameter : virtual public AST_node
{
public:
    AST_formal_parameter(AST_type* type, bool is_ref, Token_variable_name* variable_name, AST_expr* expr);
protected:
    AST_formal_parameter();
public:
    AST_type* type;
    bool is_ref;
    Token_variable_name* variable_name;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_formal_parameter* clone();
public:
    AST_formal_parameter(AST_type* type, Token_variable_name* name);
    AST_formal_parameter(AST_type* type, bool is_ref, Token_variable_name* name);
friend class AST_transform;
friend class AST_visitor;
};

// type ::= "array"? CLASS_NAME? ;
class AST_type : virtual public AST_node
{
public:
    AST_type(bool is_array, Token_class_name* class_name);
protected:
    AST_type();
public:
    bool is_array;
    Token_class_name* class_name;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_type* clone();
friend class AST_transform;
friend class AST_visitor;
};

// attr_mod ::= "public"? "protected"? "private"? "static"? "const"? ;
class AST_attr_mod : virtual public AST_node
{
public:
    AST_attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const);
protected:
    AST_attr_mod();
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_const;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_attr_mod* clone();
public:
    AST_attr_mod(AST_method_mod* mm);
    static AST_attr_mod* new_PUBLIC();
    static AST_attr_mod* new_PROTECTED();
    static AST_attr_mod* new_PRIVATE();
    static AST_attr_mod* new_STATIC();
    static AST_attr_mod* new_CONST();
friend class AST_transform;
friend class AST_visitor;
};

// directive ::= DIRECTIVE_NAME expr ;
class AST_directive : virtual public AST_node
{
public:
    AST_directive(Token_directive_name* directive_name, AST_expr* expr);
protected:
    AST_directive();
public:
    Token_directive_name* directive_name;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_directive* clone();
friend class AST_transform;
friend class AST_visitor;
};

// list_element ::= variable | list_elements;
class AST_list_element : virtual public AST_node
{
public:
    AST_list_element();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_list_element* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// variable_name ::= VARIABLE_NAME | reflection;
class AST_variable_name : virtual public AST_node
{
public:
    AST_variable_name();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_variable_name* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// target ::= expr | CLASS_NAME;
class AST_target : virtual public AST_node
{
public:
    AST_target();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_target* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// array_elem ::= key:expr? is_ref:"&" val:expr ;
class AST_array_elem : virtual public AST_node
{
public:
    AST_array_elem(AST_expr* key, bool is_ref, AST_expr* val);
protected:
    AST_array_elem();
public:
    AST_expr* key;
    bool is_ref;
    AST_expr* val;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_array_elem* clone();
friend class AST_transform;
friend class AST_visitor;
};

// method_name ::= METHOD_NAME | reflection;
class AST_method_name : virtual public AST_node
{
public:
    AST_method_name();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_method_name* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// actual_parameter ::= is_ref:"&" expr ;
class AST_actual_parameter : virtual public AST_node
{
public:
    AST_actual_parameter(bool is_ref, AST_expr* expr);
protected:
    AST_actual_parameter();
public:
    bool is_ref;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_actual_parameter* clone();
friend class AST_transform;
friend class AST_visitor;
};

// class_name ::= CLASS_NAME | reflection;
class AST_class_name : virtual public AST_node
{
public:
    AST_class_name();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_class_name* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// commented_node ::= member | statement | interface_def | class_def | switch_case | catch;
class AST_commented_node : virtual public AST_node
{
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_commented_node* clone() = 0;
public:
    AST_commented_node();
    //  Return the comments associated with the node
    List<String*>* get_comments();
friend class AST_transform;
friend class AST_visitor;
};

// identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | DIRECTIVE_NAME | CAST | OP | CONSTANT_NAME;
class AST_identifier : virtual public AST_node
{
public:
    AST_identifier();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_identifier* clone() = 0;
public:
    virtual String* get_value_as_string() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// interface_def ::= INTERFACE_NAME extends:INTERFACE_NAME* member* ;
class AST_interface_def : virtual public AST_commented_node
{
public:
    AST_interface_def(Token_interface_name* interface_name, List<Token_interface_name*>* extends, List<AST_member*>* members);
protected:
    AST_interface_def();
public:
    Token_interface_name* interface_name;
    List<Token_interface_name*>* extends;
    List<AST_member*>* members;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_interface_def* clone();
friend class AST_transform;
friend class AST_visitor;
};

// class_def ::= class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* member* ;
class AST_class_def : virtual public AST_commented_node
{
public:
    AST_class_def(AST_class_mod* class_mod, Token_class_name* class_name, Token_class_name* extends, List<Token_interface_name*>* implements, List<AST_member*>* members);
protected:
    AST_class_def();
public:
    AST_class_mod* class_mod;
    Token_class_name* class_name;
    Token_class_name* extends;
    List<Token_interface_name*>* implements;
    List<AST_member*>* members;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_class_def* clone();
public:
    AST_class_def(AST_class_mod* mod);
    AST_class_def(char* name);
    void add_member(AST_member* member);
    //  Returns NULL if the method could not be found
    AST_method* get_method(const char* name);
friend class AST_transform;
friend class AST_visitor;
};

// member ::= method | attribute;
class AST_member : virtual public AST_commented_node
{
public:
    AST_member();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_member* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// statement ::= if | while | do | for | foreach | switch | break | continue | return | static_declaration | unset | declare | try | throw | eval_expr | nop;
class AST_statement : virtual public AST_commented_node
{
public:
    AST_statement();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_statement* clone() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// switch_case ::= expr? statement* ;
class AST_switch_case : virtual public AST_commented_node
{
public:
    AST_switch_case(AST_expr* expr, List<AST_statement*>* statements);
protected:
    AST_switch_case();
public:
    AST_expr* expr;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_switch_case* clone();
friend class AST_transform;
friend class AST_visitor;
};

// catch ::= CLASS_NAME VARIABLE_NAME statement* ;
class AST_catch : virtual public AST_commented_node
{
public:
    AST_catch(Token_class_name* class_name, Token_variable_name* variable_name, List<AST_statement*>* statements);
protected:
    AST_catch();
public:
    Token_class_name* class_name;
    Token_variable_name* variable_name;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_catch* clone();
friend class AST_transform;
friend class AST_visitor;
};

// expr ::= assignment | list_assignment | cast | unary_op | bin_op | conditional_expr | ignore_errors | constant | instanceof | variable | pre_op | post_op | array | method_invocation | new | clone | literal;
class AST_expr : virtual public AST_target, virtual public AST_node
{
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_expr* clone() = 0;
public:
    AST_expr();
friend class AST_transform;
friend class AST_visitor;
};

// list_elements ::= list_element?* ;
class AST_list_elements : virtual public AST_list_element
{
public:
    AST_list_elements(List<AST_list_element*>* list_elements);
protected:
    AST_list_elements();
public:
    List<AST_list_element*>* list_elements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_list_elements* clone();
friend class AST_transform;
friend class AST_visitor;
};

// reflection ::= expr ;
class AST_reflection : virtual public AST_variable_name, virtual public AST_method_name, virtual public AST_class_name
{
public:
    AST_reflection(AST_expr* expr);
protected:
    AST_reflection();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_reflection* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_interface_name : virtual public AST_identifier
{
public:
    Token_interface_name(String* value);
protected:
    Token_interface_name();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_interface_name* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_class_name : virtual public AST_target, virtual public AST_class_name, virtual public AST_identifier
{
public:
    Token_class_name(String* value);
protected:
    Token_class_name();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_class_name* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_method_name : virtual public AST_method_name, virtual public AST_identifier
{
public:
    Token_method_name(String* value);
protected:
    Token_method_name();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_method_name* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_variable_name : virtual public AST_variable_name, virtual public AST_identifier
{
public:
    Token_variable_name(String* value);
protected:
    Token_variable_name();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_variable_name* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_directive_name : virtual public AST_identifier
{
public:
    Token_directive_name(String* value);
protected:
    Token_directive_name();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_directive_name* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_cast : virtual public AST_identifier
{
public:
    Token_cast(String* value);
protected:
    Token_cast();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_cast* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_op : virtual public AST_identifier
{
public:
    Token_op(String* value);
protected:
    Token_op();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_op* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_constant_name : virtual public AST_identifier
{
public:
    Token_constant_name(String* value);
protected:
    Token_constant_name();
private:
    virtual int classid();
public:
    String* value;
    virtual String* get_value_as_string();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_constant_name* clone();
friend class AST_transform;
friend class AST_visitor;
};

// method ::= signature statement*? ;
class AST_method : virtual public AST_member
{
public:
    AST_method(AST_signature* signature, List<AST_statement*>* statements);
protected:
    AST_method();
public:
    AST_signature* signature;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_method* clone();
friend class AST_transform;
friend class AST_visitor;
};

// attribute ::= attr_mod VARIABLE_NAME expr? ;
class AST_attribute : virtual public AST_member
{
public:
    AST_attribute(AST_attr_mod* attr_mod, Token_variable_name* variable_name, AST_expr* expr);
protected:
    AST_attribute();
public:
    AST_attr_mod* attr_mod;
    Token_variable_name* variable_name;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_attribute* clone();
friend class AST_transform;
friend class AST_visitor;
};

// if ::= expr iftrue:statement* iffalse:statement* ;
class AST_if : virtual public AST_statement
{
public:
    AST_if(AST_expr* expr, List<AST_statement*>* iftrue, List<AST_statement*>* iffalse);
protected:
    AST_if();
public:
    AST_expr* expr;
    List<AST_statement*>* iftrue;
    List<AST_statement*>* iffalse;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_if* clone();
public:
    void init();
friend class AST_transform;
friend class AST_visitor;
};

// while ::= expr statement* ;
class AST_while : virtual public AST_statement
{
public:
    AST_while(AST_expr* expr, List<AST_statement*>* statements);
protected:
    AST_while();
public:
    AST_expr* expr;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_while* clone();
friend class AST_transform;
friend class AST_visitor;
};

// do ::= statement* expr ;
class AST_do : virtual public AST_statement
{
public:
    AST_do(List<AST_statement*>* statements, AST_expr* expr);
protected:
    AST_do();
public:
    List<AST_statement*>* statements;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_do* clone();
friend class AST_transform;
friend class AST_visitor;
};

// for ::= init:expr? cond:expr? incr:expr? statement* ;
class AST_for : virtual public AST_statement
{
public:
    AST_for(AST_expr* init, AST_expr* cond, AST_expr* incr, List<AST_statement*>* statements);
protected:
    AST_for();
public:
    AST_expr* init;
    AST_expr* cond;
    AST_expr* incr;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_for* clone();
friend class AST_transform;
friend class AST_visitor;
};

// foreach ::= expr key:variable? is_ref:"&" val:variable statement* ;
class AST_foreach : virtual public AST_statement
{
public:
    AST_foreach(AST_expr* expr, AST_variable* key, bool is_ref, AST_variable* val, List<AST_statement*>* statements);
protected:
    AST_foreach();
public:
    AST_expr* expr;
    AST_variable* key;
    bool is_ref;
    AST_variable* val;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_foreach* clone();
friend class AST_transform;
friend class AST_visitor;
};

// switch ::= expr switch_case* ;
class AST_switch : virtual public AST_statement
{
public:
    AST_switch(AST_expr* expr, List<AST_switch_case*>* switch_cases);
protected:
    AST_switch();
public:
    AST_expr* expr;
    List<AST_switch_case*>* switch_cases;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_switch* clone();
friend class AST_transform;
friend class AST_visitor;
};

// break ::= expr? ;
class AST_break : virtual public AST_statement
{
public:
    AST_break(AST_expr* expr);
protected:
    AST_break();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_break* clone();
friend class AST_transform;
friend class AST_visitor;
};

// continue ::= expr? ;
class AST_continue : virtual public AST_statement
{
public:
    AST_continue(AST_expr* expr);
protected:
    AST_continue();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_continue* clone();
friend class AST_transform;
friend class AST_visitor;
};

// return ::= expr? ;
class AST_return : virtual public AST_statement
{
public:
    AST_return(AST_expr* expr);
protected:
    AST_return();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_return* clone();
friend class AST_transform;
friend class AST_visitor;
};

// static_declaration ::= VARIABLE_NAME expr? ;
class AST_static_declaration : virtual public AST_statement
{
public:
    AST_static_declaration(Token_variable_name* variable_name, AST_expr* expr);
protected:
    AST_static_declaration();
public:
    Token_variable_name* variable_name;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_static_declaration* clone();
friend class AST_transform;
friend class AST_visitor;
};

// unset ::= variable ;
class AST_unset : virtual public AST_statement
{
public:
    AST_unset(AST_variable* variable);
protected:
    AST_unset();
public:
    AST_variable* variable;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_unset* clone();
friend class AST_transform;
friend class AST_visitor;
};

// declare ::= directive* statement* ;
class AST_declare : virtual public AST_statement
{
public:
    AST_declare(List<AST_directive*>* directives, List<AST_statement*>* statements);
protected:
    AST_declare();
public:
    List<AST_directive*>* directives;
    List<AST_statement*>* statements;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_declare* clone();
friend class AST_transform;
friend class AST_visitor;
};

// try ::= statement* catches:catch* ;
class AST_try : virtual public AST_statement
{
public:
    AST_try(List<AST_statement*>* statements, List<AST_catch*>* catches);
protected:
    AST_try();
public:
    List<AST_statement*>* statements;
    List<AST_catch*>* catches;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_try* clone();
friend class AST_transform;
friend class AST_visitor;
};

// throw ::= expr ;
class AST_throw : virtual public AST_statement
{
public:
    AST_throw(AST_expr* expr);
protected:
    AST_throw();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_throw* clone();
friend class AST_transform;
friend class AST_visitor;
};

// eval_expr ::= expr ;
class AST_eval_expr : virtual public AST_statement
{
public:
    AST_eval_expr(AST_expr* expr);
protected:
    AST_eval_expr();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_eval_expr* clone();
friend class AST_transform;
friend class AST_visitor;
};

// nop ::= ;
class AST_nop : virtual public AST_statement
{
public:
    AST_nop();
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_nop* clone();
friend class AST_transform;
friend class AST_visitor;
};

// literal ::= INT<int> | REAL<double> | STRING<String*> | BOOL<bool> | NULL<>;
class AST_literal : virtual public AST_expr
{
public:
    AST_literal();
private:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_literal* clone() = 0;
public:
    virtual String* get_value_as_string() = 0;
    virtual String* get_source_rep() = 0;
friend class AST_transform;
friend class AST_visitor;
};

// assignment ::= variable is_ref:"&" expr ;
class AST_assignment : virtual public AST_expr
{
public:
    AST_assignment(AST_variable* variable, bool is_ref, AST_expr* expr);
protected:
    AST_assignment();
public:
    AST_variable* variable;
    bool is_ref;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_assignment* clone();
public:
    void init();
friend class AST_transform;
friend class AST_visitor;
};

// list_assignment ::= list_elements expr ;
class AST_list_assignment : virtual public AST_expr
{
public:
    AST_list_assignment(AST_list_elements* list_elements, AST_expr* expr);
protected:
    AST_list_assignment();
public:
    AST_list_elements* list_elements;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_list_assignment* clone();
friend class AST_transform;
friend class AST_visitor;
};

// cast ::= CAST expr ;
class AST_cast : virtual public AST_expr
{
public:
    AST_cast(Token_cast* cast, AST_expr* expr);
protected:
    AST_cast();
public:
    Token_cast* cast;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_cast* clone();
public:
    AST_cast(char* cast, AST_expr* expr);
friend class AST_transform;
friend class AST_visitor;
};

// unary_op ::= OP expr ;
class AST_unary_op : virtual public AST_expr
{
public:
    AST_unary_op(Token_op* op, AST_expr* expr);
protected:
    AST_unary_op();
public:
    Token_op* op;
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_unary_op* clone();
public:
    AST_unary_op(AST_expr* expr, char* op);
friend class AST_transform;
friend class AST_visitor;
};

// bin_op ::= left:expr OP right:expr ;
class AST_bin_op : virtual public AST_expr
{
public:
    AST_bin_op(AST_expr* left, Token_op* op, AST_expr* right);
protected:
    AST_bin_op();
public:
    AST_expr* left;
    Token_op* op;
    AST_expr* right;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_bin_op* clone();
public:
    AST_bin_op(AST_expr* left, AST_expr* right, char* op);
friend class AST_transform;
friend class AST_visitor;
};

// conditional_expr ::= cond:expr iftrue:expr iffalse:expr ;
class AST_conditional_expr : virtual public AST_expr
{
public:
    AST_conditional_expr(AST_expr* cond, AST_expr* iftrue, AST_expr* iffalse);
protected:
    AST_conditional_expr();
public:
    AST_expr* cond;
    AST_expr* iftrue;
    AST_expr* iffalse;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_conditional_expr* clone();
friend class AST_transform;
friend class AST_visitor;
};

// ignore_errors ::= expr ;
class AST_ignore_errors : virtual public AST_expr
{
public:
    AST_ignore_errors(AST_expr* expr);
protected:
    AST_ignore_errors();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_ignore_errors* clone();
friend class AST_transform;
friend class AST_visitor;
};

// constant ::= CLASS_NAME CONSTANT_NAME ;
class AST_constant : virtual public AST_expr
{
public:
    AST_constant(Token_class_name* class_name, Token_constant_name* constant_name);
protected:
    AST_constant();
public:
    Token_class_name* class_name;
    Token_constant_name* constant_name;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_constant* clone();
public:
    AST_constant(char* class_name, Token_constant_name* constant_name);
friend class AST_transform;
friend class AST_visitor;
};

// instanceof ::= expr class_name ;
class AST_instanceof : virtual public AST_expr
{
public:
    AST_instanceof(AST_expr* expr, AST_class_name* class_name);
protected:
    AST_instanceof();
public:
    AST_expr* expr;
    AST_class_name* class_name;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_instanceof* clone();
friend class AST_transform;
friend class AST_visitor;
};

// variable ::= target? variable_name array_indices:expr?* string_index:expr? ;
class AST_variable : virtual public AST_expr, virtual public AST_list_element
{
public:
    AST_variable(AST_target* target, AST_variable_name* variable_name, List<AST_expr*>* array_indices, AST_expr* string_index);
protected:
    AST_variable();
public:
    AST_target* target;
    AST_variable_name* variable_name;
    List<AST_expr*>* array_indices;
    AST_expr* string_index;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_variable* clone();
public:
    AST_variable(AST_variable_name* name);
    void init();
friend class AST_transform;
friend class AST_visitor;
};

// pre_op ::= OP variable ;
class AST_pre_op : virtual public AST_expr
{
public:
    AST_pre_op(Token_op* op, AST_variable* variable);
protected:
    AST_pre_op();
public:
    Token_op* op;
    AST_variable* variable;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_pre_op* clone();
public:
    AST_pre_op(AST_variable* var, char* op);
friend class AST_transform;
friend class AST_visitor;
};

// post_op ::= variable OP ;
class AST_post_op : virtual public AST_expr
{
public:
    AST_post_op(AST_variable* variable, Token_op* op);
protected:
    AST_post_op();
public:
    AST_variable* variable;
    Token_op* op;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_post_op* clone();
public:
    AST_post_op(AST_variable* var, char* op);
friend class AST_transform;
friend class AST_visitor;
};

// array ::= array_elem* ;
class AST_array : virtual public AST_expr
{
public:
    AST_array(List<AST_array_elem*>* array_elems);
protected:
    AST_array();
public:
    List<AST_array_elem*>* array_elems;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_array* clone();
friend class AST_transform;
friend class AST_visitor;
};

// method_invocation ::= target method_name actual_parameter* ;
class AST_method_invocation : virtual public AST_expr
{
public:
    AST_method_invocation(AST_target* target, AST_method_name* method_name, List<AST_actual_parameter*>* actual_parameters);
protected:
    AST_method_invocation();
public:
    AST_target* target;
    AST_method_name* method_name;
    List<AST_actual_parameter*>* actual_parameters;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_method_invocation* clone();
public:
    //  For internal use only!
    AST_method_invocation(const char* name, AST_expr* arg);
    //  For internal use only!
    AST_method_invocation(Token_method_name* name, AST_expr* arg);
    //  This does in fact create a valid subtree
    AST_method_invocation(const char* target, const char* name, AST_expr* arg);
friend class AST_transform;
friend class AST_visitor;
};

// new ::= class_name actual_parameter* ;
class AST_new : virtual public AST_expr
{
public:
    AST_new(AST_class_name* class_name, List<AST_actual_parameter*>* actual_parameters);
protected:
    AST_new();
public:
    AST_class_name* class_name;
    List<AST_actual_parameter*>* actual_parameters;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_new* clone();
friend class AST_transform;
friend class AST_visitor;
};

// clone ::= expr ;
class AST_clone : virtual public AST_expr
{
public:
    AST_clone(AST_expr* expr);
protected:
    AST_clone();
public:
    AST_expr* expr;
private:
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_clone* clone();
friend class AST_transform;
friend class AST_visitor;
};

class Token_int : virtual public AST_literal
{
public:
    Token_int(int value, String* source_rep);
protected:
    Token_int();
private:
    virtual int classid();
public:
    int value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    virtual bool match(AST_node* in);
    virtual bool match_value(Token_int* that);
public:
    virtual bool equals(AST_node* in);
    virtual bool equals_value(Token_int* that);
public:
    virtual Token_int* clone();
    virtual int clone_value();
public:
    virtual String* get_value_as_string();
friend class AST_transform;
friend class AST_visitor;
};

class Token_real : virtual public AST_literal
{
public:
    Token_real(double value, String* source_rep);
protected:
    Token_real();
private:
    virtual int classid();
public:
    double value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    virtual bool match(AST_node* in);
    virtual bool match_value(Token_real* that);
public:
    virtual bool equals(AST_node* in);
    virtual bool equals_value(Token_real* that);
public:
    virtual Token_real* clone();
    virtual double clone_value();
public:
    virtual String* get_value_as_string();
friend class AST_transform;
friend class AST_visitor;
};

class Token_string : virtual public AST_literal
{
public:
    Token_string(String* value, String* source_rep);
protected:
    Token_string();
private:
    virtual int classid();
public:
    String* value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    virtual bool match(AST_node* in);
    virtual bool match_value(Token_string* that);
public:
    virtual bool equals(AST_node* in);
    virtual bool equals_value(Token_string* that);
public:
    virtual Token_string* clone();
    virtual String* clone_value();
public:
    virtual String* get_value_as_string();
friend class AST_transform;
friend class AST_visitor;
};

class Token_bool : virtual public AST_literal
{
public:
    Token_bool(bool value, String* source_rep);
protected:
    Token_bool();
private:
    virtual int classid();
public:
    bool value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    virtual bool match(AST_node* in);
    virtual bool match_value(Token_bool* that);
public:
    virtual bool equals(AST_node* in);
    virtual bool equals_value(Token_bool* that);
public:
    virtual Token_bool* clone();
    virtual bool clone_value();
public:
    virtual String* get_value_as_string();
friend class AST_transform;
friend class AST_visitor;
};

class Token_null : virtual public AST_literal
{
public:
    Token_null(String* source_rep);
protected:
    Token_null();
private:
    virtual int classid();
public:
    String* source_rep;
    virtual String* get_source_rep();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_null* clone();
public:
    virtual String* get_value_as_string();
friend class AST_transform;
friend class AST_visitor;
};


class __WILDCARD__
{
public:
	virtual ~__WILDCARD__() {}

public:
	virtual void set_value(AST_node* in) = 0;
};

template<class C>
class Wildcard : public virtual C, public __WILDCARD__
{
public:
	Wildcard() {}
	Wildcard(C* v) : value(v) {}
	virtual ~Wildcard() {}

public:
	C* value;

	virtual void set_value(AST_node* in)
	{
		value = dynamic_cast<C*>(in);
	}

	virtual bool match(AST_node* in)
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
		return new Wildcard(value->clone());
	}

	virtual bool equals(AST_node* in)
	{
		Wildcard* that = dynamic_cast<Wildcard*>(in);
		if(that == NULL) return false;

		return value->equals(that->value);
	}

private:
	int classid()
	{
		return 64;
	}
};


#endif
