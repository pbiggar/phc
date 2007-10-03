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
class AST_statement;
class AST_member;
class AST_switch_case;
class AST_catch;
class AST_expr;
class AST_nested_list_elements;
class AST_reflection;
class Token_class_name;
class Token_interface_name;
class Token_method_name;
class Token_variable_name;
class Token_label_name;
class Token_directive_name;
class Token_op;
class Token_cast;
class Token_constant_name;
class AST_class_def;
class AST_interface_def;
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
class AST_branch;
class AST_goto;
class AST_label;
class AST_static_declaration;
class AST_global;
class AST_unset;
class AST_declare;
class AST_try;
class AST_throw;
class AST_eval_expr;
class AST_nop;
class AST_literal;
class AST_assignment;
class AST_op_assignment;
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

// node ::= php_script | class_mod | signature | method_mod | formal_parameter | type | attr_mod | directive | list_element | variable_name | target | array_elem | method_name | actual_parameter | class_name | commented_node | identifier;
class AST_node : virtual public Object
{
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_node* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    AttrMap* attrs;
    //  Return the line number of the node (or 0 if unknown)
    int get_line_number();
    //  Return the filename of the node (or NULL if unknown)
    String* get_filename();
    AST_node();
    void clone_mixin_from(AST_node* in);
    void assert_mixin_valid();
    bool is_mixin_equal(AST_node* in);
};

// php_script ::= statement* ;
class AST_php_script : virtual public AST_node
{
public:
    AST_php_script(List<AST_statement*>* statements);
protected:
    AST_php_script();
public:
    List<AST_statement*>* statements;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 1;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_php_script* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 3;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_class_mod* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 6;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_signature* clone();
public:
    virtual void assert_valid();
public:
    AST_signature(const char* name);
};

// method_mod ::= "public"? "protected"? "private"? "static"? "abstract"? "final"? ;
class AST_method_mod : virtual public AST_node
{
public:
    AST_method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final);
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_abstract;
    bool is_final;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 7;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_method_mod* clone();
public:
    virtual void assert_valid();
public:
    AST_method_mod();
    AST_method_mod(AST_method_mod* a, AST_method_mod* b);
    static AST_method_mod* new_PUBLIC();
    static AST_method_mod* new_PROTECTED();
    static AST_method_mod* new_PRIVATE();
    static AST_method_mod* new_STATIC();
    static AST_method_mod* new_ABSTRACT();
    static AST_method_mod* new_FINAL();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 8;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_formal_parameter* clone();
public:
    virtual void assert_valid();
public:
    AST_formal_parameter(AST_type* type, Token_variable_name* name);
    AST_formal_parameter(AST_type* type, bool is_ref, Token_variable_name* name);
};

// type ::= CLASS_NAME? ;
class AST_type : virtual public AST_node
{
public:
    AST_type(Token_class_name* class_name);
protected:
    AST_type();
public:
    Token_class_name* class_name;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 9;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_type* clone();
public:
    virtual void assert_valid();
};

// attr_mod ::= "public"? "protected"? "private"? "static"? "const"? ;
class AST_attr_mod : virtual public AST_node
{
public:
    AST_attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const);
public:
    bool is_public;
    bool is_protected;
    bool is_private;
    bool is_static;
    bool is_const;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 11;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_attr_mod* clone();
public:
    virtual void assert_valid();
public:
    AST_attr_mod();
    AST_attr_mod(AST_method_mod* mm);
    static AST_attr_mod* new_PUBLIC();
    static AST_attr_mod* new_PROTECTED();
    static AST_attr_mod* new_PRIVATE();
    static AST_attr_mod* new_STATIC();
    static AST_attr_mod* new_CONST();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 29;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_directive* clone();
public:
    virtual void assert_valid();
};

// list_element ::= variable | nested_list_elements;
class AST_list_element : virtual public AST_node
{
public:
    AST_list_element();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_list_element* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// variable_name ::= VARIABLE_NAME | reflection;
class AST_variable_name : virtual public AST_node
{
public:
    AST_variable_name();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_variable_name* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// target ::= expr | CLASS_NAME;
class AST_target : virtual public AST_node
{
public:
    AST_target();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_target* clone() = 0;
public:
    virtual void assert_valid() = 0;
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 51;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_array_elem* clone();
public:
    virtual void assert_valid();
};

// method_name ::= METHOD_NAME | reflection;
class AST_method_name : virtual public AST_node
{
public:
    AST_method_name();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_method_name* clone() = 0;
public:
    virtual void assert_valid() = 0;
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 53;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_actual_parameter* clone();
public:
    virtual void assert_valid();
};

// class_name ::= CLASS_NAME | reflection;
class AST_class_name : virtual public AST_node
{
public:
    AST_class_name();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_class_name* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// commented_node ::= member | statement | interface_def | class_def | switch_case | catch;
class AST_commented_node : virtual public AST_node
{
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_commented_node* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    AST_commented_node();
    //  Return the comments associated with the node
    List<String*>* get_comments();
};

// identifier ::= INTERFACE_NAME | CLASS_NAME | METHOD_NAME | VARIABLE_NAME | DIRECTIVE_NAME | CAST | OP | CONSTANT_NAME | LABEL_NAME;
class AST_identifier : virtual public AST_node
{
public:
    AST_identifier();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_identifier* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
};

// statement ::= class_def | interface_def | method | if | while | do | for | foreach | switch | break | continue | return | static_declaration | global | unset | declare | try | throw | eval_expr | nop | label | goto | branch;
class AST_statement : virtual public AST_commented_node
{
public:
    AST_statement();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_statement* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// member ::= method | attribute;
class AST_member : virtual public AST_commented_node
{
public:
    AST_member();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_member* clone() = 0;
public:
    virtual void assert_valid() = 0;
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 18;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_switch_case* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 31;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_catch* clone();
public:
    virtual void assert_valid();
};

// expr ::= assignment | op_assignment | list_assignment | cast | unary_op | bin_op | conditional_expr | ignore_errors | constant | instanceof | variable | pre_op | post_op | array | method_invocation | new | clone | literal;
class AST_expr : virtual public AST_target
{
public:
    AST_expr();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_expr* clone() = 0;
public:
    virtual void assert_valid() = 0;
};

// nested_list_elements ::= list_element?* ;
class AST_nested_list_elements : virtual public AST_list_element
{
public:
    AST_nested_list_elements(List<AST_list_element*>* list_elements);
protected:
    AST_nested_list_elements();
public:
    List<AST_list_element*>* list_elements;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 38;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_nested_list_elements* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 47;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_reflection* clone();
public:
    virtual void assert_valid();
};

class Token_class_name : virtual public AST_target, virtual public AST_class_name, virtual public AST_identifier
{
public:
    Token_class_name(String* value);
protected:
    Token_class_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 56;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_class_name* clone();
public:
    virtual void assert_valid();
};

class Token_interface_name : virtual public AST_identifier
{
public:
    Token_interface_name(String* value);
protected:
    Token_interface_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 57;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_interface_name* clone();
public:
    virtual void assert_valid();
};

class Token_method_name : virtual public AST_method_name, virtual public AST_identifier
{
public:
    Token_method_name(String* value);
protected:
    Token_method_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 58;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_method_name* clone();
public:
    virtual void assert_valid();
};

class Token_variable_name : virtual public AST_variable_name, virtual public AST_identifier
{
public:
    Token_variable_name(String* value);
protected:
    Token_variable_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 59;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_variable_name* clone();
public:
    virtual void assert_valid();
};

class Token_label_name : virtual public AST_identifier
{
public:
    Token_label_name(String* value);
protected:
    Token_label_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 60;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_label_name* clone();
public:
    virtual void assert_valid();
};

class Token_directive_name : virtual public AST_identifier
{
public:
    Token_directive_name(String* value);
protected:
    Token_directive_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 61;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_directive_name* clone();
public:
    virtual void assert_valid();
};

class Token_op : virtual public AST_identifier
{
public:
    Token_op(String* value);
protected:
    Token_op();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 67;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_op* clone();
public:
    virtual void assert_valid();
};

class Token_cast : virtual public AST_identifier
{
public:
    Token_cast(String* value);
protected:
    Token_cast();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 68;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_cast* clone();
public:
    virtual void assert_valid();
};

class Token_constant_name : virtual public AST_identifier
{
public:
    Token_constant_name(String* value);
protected:
    Token_constant_name();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 69;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual Token_constant_name* clone();
public:
    virtual void assert_valid();
};

// class_def ::= class_mod CLASS_NAME extends:CLASS_NAME? implements:INTERFACE_NAME* member* ;
class AST_class_def : virtual public AST_statement, virtual public AST_commented_node
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 2;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_class_def* clone();
public:
    virtual void assert_valid();
public:
    AST_class_def(AST_class_mod* mod);
    AST_class_def(const char* name);
    void add_member(AST_member* member);
    //  Returns NULL if the method could not be found
    AST_method* get_method(const char* name);
};

// interface_def ::= INTERFACE_NAME extends:INTERFACE_NAME* member* ;
class AST_interface_def : virtual public AST_statement, virtual public AST_commented_node
{
public:
    AST_interface_def(Token_interface_name* interface_name, List<Token_interface_name*>* extends, List<AST_member*>* members);
protected:
    AST_interface_def();
public:
    Token_interface_name* interface_name;
    List<Token_interface_name*>* extends;
    List<AST_member*>* members;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 4;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_interface_def* clone();
public:
    virtual void assert_valid();
};

// method ::= signature statement*? ;
class AST_method : virtual public AST_statement, virtual public AST_member
{
public:
    AST_method(AST_signature* signature, List<AST_statement*>* statements);
protected:
    AST_method();
public:
    AST_signature* signature;
    List<AST_statement*>* statements;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 5;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_method* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 10;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_attribute* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 12;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_if* clone();
public:
    virtual void assert_valid();
public:
    AST_if(AST_expr* expr);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 13;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_while* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 14;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_do* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 15;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_for* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 16;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_foreach* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 17;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_switch* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 19;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_break* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 20;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_continue* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 21;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_return* clone();
public:
    virtual void assert_valid();
};

// branch ::= expr iftrue:LABEL_NAME iffalse:LABEL_NAME ;
class AST_branch : virtual public AST_statement
{
public:
    AST_branch(AST_expr* expr, Token_label_name* iftrue, Token_label_name* iffalse);
protected:
    AST_branch();
public:
    AST_expr* expr;
    Token_label_name* iftrue;
    Token_label_name* iffalse;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 22;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_branch* clone();
public:
    virtual void assert_valid();
};

// goto ::= LABEL_NAME ;
class AST_goto : virtual public AST_statement
{
public:
    AST_goto(Token_label_name* label_name);
protected:
    AST_goto();
public:
    Token_label_name* label_name;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 23;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_goto* clone();
public:
    virtual void assert_valid();
};

// label ::= LABEL_NAME ;
class AST_label : virtual public AST_statement
{
public:
    AST_label(Token_label_name* label_name);
protected:
    AST_label();
public:
    Token_label_name* label_name;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 24;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_label* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 25;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_static_declaration* clone();
public:
    virtual void assert_valid();
};

// global ::= variable_name ;
class AST_global : virtual public AST_statement
{
public:
    AST_global(AST_variable_name* variable_name);
protected:
    AST_global();
public:
    AST_variable_name* variable_name;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 26;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_global* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 27;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_unset* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 28;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_declare* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 30;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_try* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 32;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_throw* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 33;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_eval_expr* clone();
public:
    virtual void assert_valid();
public:
    void _init();
};

// nop ::= ;
class AST_nop : virtual public AST_statement
{
public:
    AST_nop();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 34;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_nop* clone();
public:
    virtual void assert_valid();
};

// literal ::= INT<long> | REAL<double> | STRING<String*> | BOOL<bool> | NULL<>;
class AST_literal : virtual public AST_expr
{
public:
    AST_literal();
public:
    virtual void visit(AST_visitor* visitor) = 0;
    virtual void transform_children(AST_transform* transform) = 0;
public:
    virtual int classid() = 0;
public:
    virtual bool match(AST_node* in) = 0;
public:
    virtual bool equals(AST_node* in) = 0;
public:
    virtual AST_literal* clone() = 0;
public:
    virtual void assert_valid() = 0;
public:
    virtual String* get_value_as_string() = 0;
    virtual String* get_source_rep() = 0;
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 35;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_assignment* clone();
public:
    virtual void assert_valid();
};

// op_assignment ::= variable OP expr ;
class AST_op_assignment : virtual public AST_expr
{
public:
    AST_op_assignment(AST_variable* variable, Token_op* op, AST_expr* expr);
protected:
    AST_op_assignment();
public:
    AST_variable* variable;
    Token_op* op;
    AST_expr* expr;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 36;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_op_assignment* clone();
public:
    virtual void assert_valid();
public:
    AST_op_assignment(AST_variable* variable, const char* op, AST_expr* expr);
};

// list_assignment ::= list_element?* expr ;
class AST_list_assignment : virtual public AST_expr
{
public:
    AST_list_assignment(List<AST_list_element*>* list_elements, AST_expr* expr);
protected:
    AST_list_assignment();
public:
    List<AST_list_element*>* list_elements;
    AST_expr* expr;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 37;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_list_assignment* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 39;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_cast* clone();
public:
    virtual void assert_valid();
public:
    AST_cast(const char* cast, AST_expr* expr);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 40;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_unary_op* clone();
public:
    virtual void assert_valid();
public:
    AST_unary_op(AST_expr* expr, const char* op);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 41;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_bin_op* clone();
public:
    virtual void assert_valid();
public:
    AST_bin_op(AST_expr* left, AST_expr* right, const char* op);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 42;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_conditional_expr* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 43;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_ignore_errors* clone();
public:
    virtual void assert_valid();
};

// constant ::= CLASS_NAME? CONSTANT_NAME ;
class AST_constant : virtual public AST_expr
{
public:
    AST_constant(Token_class_name* class_name, Token_constant_name* constant_name);
protected:
    AST_constant();
public:
    Token_class_name* class_name;
    Token_constant_name* constant_name;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 44;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_constant* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 45;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_instanceof* clone();
public:
    virtual void assert_valid();
};

// variable ::= target? variable_name array_indices:expr?* ;
class AST_variable : virtual public AST_expr, virtual public AST_list_element
{
public:
    AST_variable(AST_target* target, AST_variable_name* variable_name, List<AST_expr*>* array_indices);
protected:
    AST_variable();
public:
    AST_target* target;
    AST_variable_name* variable_name;
    List<AST_expr*>* array_indices;
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 46;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_variable* clone();
public:
    virtual void assert_valid();
public:
    AST_variable(AST_variable_name* name);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 48;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_pre_op* clone();
public:
    virtual void assert_valid();
public:
    AST_pre_op(AST_variable* var, const char* op);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 49;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_post_op* clone();
public:
    virtual void assert_valid();
public:
    AST_post_op(AST_variable* var, const char* op);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 50;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_array* clone();
public:
    virtual void assert_valid();
};

// method_invocation ::= target? method_name actual_parameter* ;
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 52;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_method_invocation* clone();
public:
    virtual void assert_valid();
public:
    //  For internal use only!
    AST_method_invocation(const char* name, AST_expr* arg);
    //  For internal use only!
    AST_method_invocation(Token_method_name* name, AST_expr* arg);
    //  This does in fact create a valid subtree
    AST_method_invocation(const char* target, const char* name, AST_expr* arg);
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 54;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_new* clone();
public:
    virtual void assert_valid();
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
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    static const int ID = 55;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
public:
    virtual AST_clone* clone();
public:
    virtual void assert_valid();
};

class Token_int : virtual public AST_literal
{
public:
    Token_int(long value, String* source_rep);
protected:
    Token_int();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    long value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 62;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
    virtual bool match_value(Token_int* that);
public:
    virtual bool equals(AST_node* in);
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

class Token_real : virtual public AST_literal
{
public:
    Token_real(double value, String* source_rep);
protected:
    Token_real();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    double value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 63;
    virtual int classid();
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
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in Token_int::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    Token_real(double v);
};

class Token_string : virtual public AST_literal
{
public:
    Token_string(String* value, String* source_rep);
protected:
    Token_string();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 64;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
    virtual bool match_value(Token_string* that);
public:
    virtual bool equals(AST_node* in);
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

class Token_bool : virtual public AST_literal
{
public:
    Token_bool(bool value, String* source_rep);
protected:
    Token_bool();
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    bool value;
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 65;
    virtual int classid();
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
    virtual void assert_valid();
    virtual void assert_value_valid();
private:
    //  See comment in Token_int::_get_value_as_string ()
    String* _get_value_as_string();
public:
    virtual String* get_value_as_string();
    Token_bool(bool v);
};

class Token_null : virtual public AST_literal
{
public:
    Token_null(String* source_rep);
public:
    virtual void visit(AST_visitor* visitor);
    virtual void transform_children(AST_transform* transform);
public:
    String* source_rep;
    virtual String* get_source_rep();
public:
    static const int ID = 66;
    virtual int classid();
public:
    virtual bool match(AST_node* in);
public:
    virtual bool equals(AST_node* in);
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
	virtual bool match(AST_node* in) = 0;
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
		if(value != NULL)
			return new Wildcard(value->clone());
		else
			return new Wildcard(NULL);
	}

	virtual bool equals(AST_node* in)
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

	virtual void visit(AST_visitor* visitor)
	{
		if(value != NULL)
			value->visit(visitor);
	}

	virtual void transform_children(AST_transform* transform)
	{
		if(value != NULL)
			value->transform_children(transform);
	}

public:
	static const int ID = 70;
	int classid()
	{
		return ID;
	}
};


#endif
