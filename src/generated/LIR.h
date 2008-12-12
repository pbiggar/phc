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
class COMMENT;
class Method;
class Block;
class Action;
class If;
class Is_ref;
class Equals;
class Uninitialized;
class Null;
class Deref;
class Ref;
class UNINTERPRETED;
class INTRINSIC;
class API_CALL;
class CODE;
class ZVP;
class LITERAL;
class ZVPP;
class Assign_zvp;
class Assign_zvpp;
class Inc_ref;
class Allocate;
class Clone;
class Separate;
class Dec_ref;
class Destruct;
class None;

typedef List<Node*> Node_list;
typedef List<C_file*> C_file_list;
typedef List<Piece*> Piece_list;
typedef List<Statement*> Statement_list;
typedef List<Cond*> Cond_list;
typedef List<Zvp*> Zvp_list;
typedef List<Zvpp*> Zvpp_list;
typedef List<COMMENT*> COMMENT_list;
typedef List<Method*> Method_list;
typedef List<Block*> Block_list;
typedef List<Action*> Action_list;
typedef List<If*> If_list;
typedef List<Is_ref*> Is_ref_list;
typedef List<Equals*> Equals_list;
typedef List<Uninitialized*> Uninitialized_list;
typedef List<Null*> Null_list;
typedef List<Deref*> Deref_list;
typedef List<Ref*> Ref_list;
typedef List<UNINTERPRETED*> UNINTERPRETED_list;
typedef List<INTRINSIC*> INTRINSIC_list;
typedef List<API_CALL*> API_CALL_list;
typedef List<CODE*> CODE_list;
typedef List<ZVP*> ZVP_list;
typedef List<LITERAL*> LITERAL_list;
typedef List<ZVPP*> ZVPP_list;
typedef List<Assign_zvp*> Assign_zvp_list;
typedef List<Assign_zvpp*> Assign_zvpp_list;
typedef List<Inc_ref*> Inc_ref_list;
typedef List<Allocate*> Allocate_list;
typedef List<Clone*> Clone_list;
typedef List<Separate*> Separate_list;
typedef List<Dec_ref*> Dec_ref_list;
typedef List<Destruct*> Destruct_list;
typedef List<None*> None_list;

class Transform;
class Visitor;

/* Node ::= C_file | Piece | Statement | Cond | Zvp | Zvpp | COMMENT; */
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

/* Statement ::= Action | If | INTRINSIC | API_CALL | CODE; */
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

/* Cond ::= Is_ref | Equals; */
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

/* Zvp ::= Deref | ZVP | Null | LITERAL | Uninitialized; */
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

/* Zvpp ::= Ref | ZVPP; */
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

class COMMENT : virtual public Node
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
    static const int ID = 19;
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

/* Action ::= Assign_zvp | Assign_zvpp | Inc_ref | Dec_ref | Destruct | Allocate | Clone | Separate; */
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

/* If ::= Cond if_true:Statement* if_false:Statement* ; */
class If : virtual public Statement
{
public:
    If(Cond* cond, Statement_list* if_true, Statement_list* if_false);
protected:
    If();
public:
    Cond* cond;
    Statement_list* if_true;
    Statement_list* if_false;
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
    static const int ID = 13;
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
    static const int ID = 14;
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

/* Uninitialized ::= ; */
class Uninitialized : virtual public Zvp
{
public:
    Uninitialized();
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
    virtual Uninitialized* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Null ::= ; */
class Null : virtual public Zvp
{
public:
    Null();
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
    static const int ID = 17;
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
    static const int ID = 18;
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

class UNINTERPRETED : virtual public Piece
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
    static const int ID = 20;
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
    static const int ID = 21;
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
    static const int ID = 22;
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

class CODE : virtual public Statement
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
    static const int ID = 23;
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

class ZVP : virtual public Zvp
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
    static const int ID = 24;
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

class LITERAL : virtual public Zvp
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
    static const int ID = 25;
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

class ZVPP : virtual public Zvpp
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
    static const int ID = 26;
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
    static const int ID = 7;
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
    static const int ID = 8;
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

/* Clone ::= lhs:Zvp rhs:Zvp ; */
class Clone : virtual public Action
{
public:
    Clone(Zvp* lhs, Zvp* rhs);
protected:
    Clone();
public:
    Zvp* lhs;
    Zvp* rhs;
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
    virtual Clone* clone();
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
    static const int ID = 10;
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
    static const int ID = 11;
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
    static const int ID = 12;
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

/* The top of the class hierarchy. If the Fold will not allow you fold to anything else, try this. */
class None : virtual public Node, virtual public C_file, virtual public Piece, virtual public Method, virtual public Block, virtual public Statement, virtual public Action, virtual public If, virtual public Cond, virtual public Assign_zvp, virtual public Assign_zvpp, virtual public Inc_ref, virtual public Allocate, virtual public Clone, virtual public Separate, virtual public Dec_ref, virtual public Destruct, virtual public Is_ref, virtual public Equals, virtual public Zvp, virtual public Zvpp, virtual public Uninitialized, virtual public Null, virtual public Deref, virtual public Ref, virtual public COMMENT, virtual public UNINTERPRETED, virtual public INTRINSIC, virtual public API_CALL, virtual public CODE, virtual public ZVP, virtual public LITERAL, virtual public ZVPP
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
	static const int ID = 28;
	int classid()
	{
		return ID;
	}
};

}

#endif
