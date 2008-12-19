#ifndef _LIR_H_
#define _LIR_H_

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
#include "lib/AttrMap.h"
#include "process_ir/IR.h"
#include "process_lir/LIR_PHP_script_hack.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


namespace LIR{
class Node;
class C_file;
class Piece;
class Statement;
class Cond;
class Zvp;
class Zvpp;
class Identifier;
class Opt_param;
class INT;
class Method;
class Block;
class Action;
class If;
class Is_ref;
class Equals;
class Equals_p;
class Not;
class Is_change_on_write;
class Is_copy_on_write;
class True;
class False;
class Uninit;
class Null;
class Deref;
class Ref;
class Clone;
class Opt;
class Profile;
class UNINTERPRETED;
class COMMENT;
class INTRINSIC;
class API_CALL;
class CODE;
class ZVP;
class ZVPP;
class LITERAL;
class SYMTABLE;
class STRING;
class Assign_zvp;
class Assign_zvpp;
class Declare;
class Declare_p;
class Inc_ref;
class Allocate;
class Separate;
class Set_is_ref;
class Dec_ref;
class Destruct;
class Overwrite;
class Symtable_fetch;
class Symtable_insert;
class None;

typedef List<Node*> Node_list;
typedef List<C_file*> C_file_list;
typedef List<Piece*> Piece_list;
typedef List<Statement*> Statement_list;
typedef List<Cond*> Cond_list;
typedef List<Zvp*> Zvp_list;
typedef List<Zvpp*> Zvpp_list;
typedef List<Identifier*> Identifier_list;
typedef List<Opt_param*> Opt_param_list;
typedef List<INT*> INT_list;
typedef List<Method*> Method_list;
typedef List<Block*> Block_list;
typedef List<Action*> Action_list;
typedef List<If*> If_list;
typedef List<Is_ref*> Is_ref_list;
typedef List<Equals*> Equals_list;
typedef List<Equals_p*> Equals_p_list;
typedef List<Not*> Not_list;
typedef List<Is_change_on_write*> Is_change_on_write_list;
typedef List<Is_copy_on_write*> Is_copy_on_write_list;
typedef List<True*> True_list;
typedef List<False*> False_list;
typedef List<Uninit*> Uninit_list;
typedef List<Null*> Null_list;
typedef List<Deref*> Deref_list;
typedef List<Ref*> Ref_list;
typedef List<Clone*> Clone_list;
typedef List<Opt*> Opt_list;
typedef List<Profile*> Profile_list;
typedef List<UNINTERPRETED*> UNINTERPRETED_list;
typedef List<COMMENT*> COMMENT_list;
typedef List<INTRINSIC*> INTRINSIC_list;
typedef List<API_CALL*> API_CALL_list;
typedef List<CODE*> CODE_list;
typedef List<ZVP*> ZVP_list;
typedef List<ZVPP*> ZVPP_list;
typedef List<LITERAL*> LITERAL_list;
typedef List<SYMTABLE*> SYMTABLE_list;
typedef List<STRING*> STRING_list;
typedef List<Assign_zvp*> Assign_zvp_list;
typedef List<Assign_zvpp*> Assign_zvpp_list;
typedef List<Declare*> Declare_list;
typedef List<Declare_p*> Declare_p_list;
typedef List<Inc_ref*> Inc_ref_list;
typedef List<Allocate*> Allocate_list;
typedef List<Separate*> Separate_list;
typedef List<Set_is_ref*> Set_is_ref_list;
typedef List<Dec_ref*> Dec_ref_list;
typedef List<Destruct*> Destruct_list;
typedef List<Overwrite*> Overwrite_list;
typedef List<Symtable_fetch*> Symtable_fetch_list;
typedef List<Symtable_insert*> Symtable_insert_list;
typedef List<None*> None_list;

class Transform;
class Visitor;

/* Node ::= C_file | Piece | Statement | Cond | Zvp | Zvpp | Identifier | Opt_param | INT<long>; */
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
};

/* C_file ::= Piece* ; */
class C_file : virtual public Node, virtual public IR::PHP_script
{
public:
    C_file(Piece_list* pieces);
public:
    Piece_list* pieces;
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
    virtual C_file* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    C_file();
};

/* Piece ::= Method | Block | UNINTERPRETED; */
class Piece : virtual public Node
{
public:
    Piece();
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
    virtual Piece* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Statement ::= Action | If | Opt | INTRINSIC | API_CALL | CODE | Profile; */
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

/* Cond ::= Is_ref | Equals | Equals_p | Not | Is_copy_on_write | Is_change_on_write | True | False; */
class Cond : virtual public Node
{
public:
    Cond();
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
    virtual Cond* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Zvp ::= Deref | ZVP | Null | LITERAL | Uninit | Clone; */
class Zvp : virtual public Node
{
public:
    Zvp();
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
    virtual Zvp* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Zvpp ::= Ref | ZVPP | Null; */
class Zvpp : virtual public Node
{
public:
    Zvpp();
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
    virtual Zvpp* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Identifier ::= ZVPP | ZVP | SYMTABLE | LITERAL | UNINTERPRETED | COMMENT | CODE | STRING; */
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

/* Opt_param ::= ZVPP | ZVP; */
class Opt_param : virtual public Node
{
public:
    Opt_param();
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
    virtual Opt_param* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

class INT : virtual public Node
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
    static const int ID = 33;
    virtual int classid();
public:
    virtual bool match(Node* in);
    virtual bool match_value(INT* that);
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
public:
    bool is_valid();
};

/* Method ::= COMMENT entry:UNINTERPRETED Piece* exit:UNINTERPRETED ; */
class Method : virtual public Piece
{
public:
    Method(COMMENT* comment, UNINTERPRETED* entry, Piece_list* pieces, UNINTERPRETED* exit);
protected:
    Method();
public:
    COMMENT* comment;
    UNINTERPRETED* entry;
    Piece_list* pieces;
    UNINTERPRETED* exit;
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
    virtual Method* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Block ::= COMMENT Statement* ; */
class Block : virtual public Piece
{
public:
    Block(COMMENT* comment, Statement_list* statements);
protected:
    Block();
public:
    COMMENT* comment;
    Statement_list* statements;
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
    virtual Block* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Block(String* comment, Statement_list* statements);
};

/* Action ::= Assign_zvp | Assign_zvpp | Declare | Declare_p | Inc_ref | Dec_ref | Set_is_ref | Destruct | Allocate | Overwrite | Separate | Symtable_fetch | Symtable_insert; */
class Action : virtual public Statement
{
public:
    Action();
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
    virtual Action* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* If ::= Cond iftrue:Statement* iffalse:Statement* ; */
class If : virtual public Statement
{
public:
    If(Cond* cond, Statement_list* iftrue, Statement_list* iffalse);
protected:
    If();
public:
    Cond* cond;
    Statement_list* iftrue;
    Statement_list* iffalse;
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
    virtual If* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Is_ref ::= Zvp ; */
class Is_ref : virtual public Cond
{
public:
    Is_ref(Zvp* zvp);
protected:
    Is_ref();
public:
    Zvp* zvp;
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
    virtual Is_ref* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Equals ::= lhs:Zvp rhs:Zvp ; */
class Equals : virtual public Cond
{
public:
    Equals(Zvp* lhs, Zvp* rhs);
protected:
    Equals();
public:
    Zvp* lhs;
    Zvp* rhs;
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
    virtual Equals* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Equals_p ::= lhs:Zvpp rhs:Zvpp ; */
class Equals_p : virtual public Cond
{
public:
    Equals_p(Zvpp* lhs, Zvpp* rhs);
protected:
    Equals_p();
public:
    Zvpp* lhs;
    Zvpp* rhs;
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
    virtual Equals_p* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Not ::= Cond ; */
class Not : virtual public Cond
{
public:
    Not(Cond* cond);
protected:
    Not();
public:
    Cond* cond;
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
    virtual Not* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Is_change_on_write ::= Zvp ; */
class Is_change_on_write : virtual public Cond
{
public:
    Is_change_on_write(Zvp* zvp);
protected:
    Is_change_on_write();
public:
    Zvp* zvp;
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
    virtual Is_change_on_write* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Is_copy_on_write ::= Zvp ; */
class Is_copy_on_write : virtual public Cond
{
public:
    Is_copy_on_write(Zvp* zvp);
protected:
    Is_copy_on_write();
public:
    Zvp* zvp;
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
    virtual Is_copy_on_write* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* True ::= ; */
class True : virtual public Cond
{
public:
    True();
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
    virtual True* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* False ::= ; */
class False : virtual public Cond
{
public:
    False();
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
    virtual False* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Uninit ::= ; */
class Uninit : virtual public Zvp
{
public:
    Uninit();
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
    virtual Uninit* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Null ::= ; */
class Null : virtual public Zvp, virtual public Zvpp
{
public:
    Null();
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
    virtual Null* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Deref ::= Zvpp ; */
class Deref : virtual public Zvp
{
public:
    Deref(Zvpp* zvpp);
protected:
    Deref();
public:
    Zvpp* zvpp;
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
    virtual Deref* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Ref ::= Zvp ; */
class Ref : virtual public Zvpp
{
public:
    Ref(Zvp* zvp);
protected:
    Ref();
public:
    Zvp* zvp;
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
    virtual Ref* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Clone ::= Zvp ; */
class Clone : virtual public Zvp
{
public:
    Clone(Zvp* zvp);
protected:
    Clone();
public:
    Zvp* zvp;
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
    virtual Clone* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Opt ::= param:Opt_param value:STRING ; */
class Opt : virtual public Statement
{
public:
    Opt(Opt_param* param, STRING* value);
protected:
    Opt();
public:
    Opt_param* param;
    STRING* value;
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
    virtual Opt* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Profile ::= name:STRING ; */
class Profile : virtual public Statement
{
public:
    Profile(STRING* name);
protected:
    Profile();
public:
    STRING* name;
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
    virtual Profile* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class UNINTERPRETED : virtual public Piece, virtual public Identifier
{
public:
    UNINTERPRETED(String* value);
protected:
    UNINTERPRETED();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 34;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual UNINTERPRETED* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class COMMENT : virtual public Identifier
{
public:
    COMMENT(String* value);
protected:
    COMMENT();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 35;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual COMMENT* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class INTRINSIC : virtual public Statement
{
public:
    INTRINSIC(String* value);
protected:
    INTRINSIC();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 36;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual INTRINSIC* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class API_CALL : virtual public Statement
{
public:
    API_CALL(String* value);
protected:
    API_CALL();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 37;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual API_CALL* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class CODE : virtual public Statement, virtual public Identifier
{
public:
    CODE(String* value);
protected:
    CODE();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 38;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual CODE* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    CODE(string value);
};

class ZVP : virtual public Zvp, virtual public Identifier, virtual public Opt_param
{
public:
    ZVP(String* value);
protected:
    ZVP();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 39;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual ZVP* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    ZVP(string value);
};

class ZVPP : virtual public Zvpp, virtual public Identifier, virtual public Opt_param
{
public:
    ZVPP(String* value);
protected:
    ZVPP();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 40;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual ZVPP* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    ZVPP(string value);
};

class LITERAL : virtual public Zvp, virtual public Identifier
{
public:
    LITERAL(String* value);
protected:
    LITERAL();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 41;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual LITERAL* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class SYMTABLE : virtual public Identifier
{
public:
    SYMTABLE(String* value);
protected:
    SYMTABLE();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 42;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual SYMTABLE* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class STRING : virtual public Identifier
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
    virtual String* get_value_as_string();
public:
    static const int ID = 43;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual STRING* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Assign_zvp ::= lhs:Zvp rhs:Zvp ; */
class Assign_zvp : virtual public Action
{
public:
    Assign_zvp(Zvp* lhs, Zvp* rhs);
protected:
    Assign_zvp();
public:
    Zvp* lhs;
    Zvp* rhs;
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
    virtual Assign_zvp* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Assign_zvpp ::= lhs:Zvpp rhs:Zvpp ; */
class Assign_zvpp : virtual public Action
{
public:
    Assign_zvpp(Zvpp* lhs, Zvpp* rhs);
protected:
    Assign_zvpp();
public:
    Zvpp* lhs;
    Zvpp* rhs;
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
    virtual Assign_zvpp* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Declare ::= ZVP ; */
class Declare : virtual public Action
{
public:
    Declare(ZVP* zvp);
protected:
    Declare();
public:
    ZVP* zvp;
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
    virtual Declare* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Declare_p ::= ZVPP ; */
class Declare_p : virtual public Action
{
public:
    Declare_p(ZVPP* zvpp);
protected:
    Declare_p();
public:
    ZVPP* zvpp;
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
    virtual Declare_p* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Inc_ref ::= Zvp ; */
class Inc_ref : virtual public Action
{
public:
    Inc_ref(Zvp* zvp);
protected:
    Inc_ref();
public:
    Zvp* zvp;
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
    virtual Inc_ref* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Allocate ::= Zvp ; */
class Allocate : virtual public Action
{
public:
    Allocate(Zvp* zvp);
protected:
    Allocate();
public:
    Zvp* zvp;
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
    virtual Allocate* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Separate ::= Zvpp ; */
class Separate : virtual public Action
{
public:
    Separate(Zvpp* zvpp);
protected:
    Separate();
public:
    Zvpp* zvpp;
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
    virtual Separate* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Set_is_ref ::= Zvp INT<long> ; */
class Set_is_ref : virtual public Action
{
public:
    Set_is_ref(Zvp* zvp, INT* _int);
protected:
    Set_is_ref();
public:
    Zvp* zvp;
    INT* _int;
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
    virtual Set_is_ref* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Dec_ref ::= Zvp ; */
class Dec_ref : virtual public Action
{
public:
    Dec_ref(Zvp* zvp);
protected:
    Dec_ref();
public:
    Zvp* zvp;
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
    virtual Dec_ref* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Destruct ::= Zvpp ; */
class Destruct : virtual public Action
{
public:
    Destruct(Zvpp* zvpp);
protected:
    Destruct();
public:
    Zvpp* zvpp;
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
    virtual Destruct* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Overwrite ::= lhs:Zvp rhs:Zvp ; */
class Overwrite : virtual public Action
{
public:
    Overwrite(Zvp* lhs, Zvp* rhs);
protected:
    Overwrite();
public:
    Zvp* lhs;
    Zvp* rhs;
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
    virtual Overwrite* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Symtable_fetch ::= SYMTABLE name:STRING ZVPP ; */
class Symtable_fetch : virtual public Action
{
public:
    Symtable_fetch(SYMTABLE* symtable, STRING* name, ZVPP* zvpp);
protected:
    Symtable_fetch();
public:
    SYMTABLE* symtable;
    STRING* name;
    ZVPP* zvpp;
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
    virtual Symtable_fetch* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Symtable_insert ::= SYMTABLE name:STRING ZVPP ; */
class Symtable_insert : virtual public Action
{
public:
    Symtable_insert(SYMTABLE* symtable, STRING* name, ZVPP* zvpp);
protected:
    Symtable_insert();
public:
    SYMTABLE* symtable;
    STRING* name;
    ZVPP* zvpp;
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
    virtual Symtable_insert* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* The top of the class hierarchy. If the Fold will not allow you fold to anything else, try this. */
class None : virtual public Node, virtual public C_file, virtual public Piece, virtual public Method, virtual public Block, virtual public Statement, virtual public Action, virtual public If, virtual public Cond, virtual public Assign_zvp, virtual public Assign_zvpp, virtual public Declare, virtual public Declare_p, virtual public Inc_ref, virtual public Allocate, virtual public Separate, virtual public Set_is_ref, virtual public Dec_ref, virtual public Destruct, virtual public Overwrite, virtual public Is_ref, virtual public Equals, virtual public Equals_p, virtual public Not, virtual public Is_change_on_write, virtual public Is_copy_on_write, virtual public True, virtual public False, virtual public Zvp, virtual public Zvpp, virtual public Uninit, virtual public Null, virtual public Deref, virtual public Ref, virtual public Clone, virtual public Symtable_fetch, virtual public Symtable_insert, virtual public Identifier, virtual public Opt, virtual public Opt_param, virtual public Profile, virtual public INT, virtual public UNINTERPRETED, virtual public COMMENT, virtual public INTRINSIC, virtual public API_CALL, virtual public CODE, virtual public ZVP, virtual public ZVPP, virtual public LITERAL, virtual public SYMTABLE, virtual public STRING
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
	static const int ID = 45;
	int classid()
	{
		return ID;
	}
};

}

#endif
