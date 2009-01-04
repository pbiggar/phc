#ifndef _MICG_H_
#define _MICG_H_

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
#include "process_ir/IR.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


namespace MICG{
class Node;
class All;
class Macro;
class Signature;
class Formal_parameter;
class Rule;
class Expr;
class Body;
class Body_part;
class Identifier;
class Equals;
class Param;
class Interpolation;
class Macro_call;
class Callback;
class MACRO_NAME;
class TYPE_NAME;
class ATTR_NAME;
class STRING;
class C_CODE;
class Lookup;
class PARAM_NAME;
class None;

typedef List<Node*> Node_list;
typedef List<All*> All_list;
typedef List<Macro*> Macro_list;
typedef List<Signature*> Signature_list;
typedef List<Formal_parameter*> Formal_parameter_list;
typedef List<Rule*> Rule_list;
typedef List<Expr*> Expr_list;
typedef List<Body*> Body_list;
typedef List<Body_part*> Body_part_list;
typedef List<Identifier*> Identifier_list;
typedef List<Equals*> Equals_list;
typedef List<Param*> Param_list;
typedef List<Interpolation*> Interpolation_list;
typedef List<Macro_call*> Macro_call_list;
typedef List<Callback*> Callback_list;
typedef List<MACRO_NAME*> MACRO_NAME_list;
typedef List<TYPE_NAME*> TYPE_NAME_list;
typedef List<ATTR_NAME*> ATTR_NAME_list;
typedef List<STRING*> STRING_list;
typedef List<C_CODE*> C_CODE_list;
typedef List<Lookup*> Lookup_list;
typedef List<PARAM_NAME*> PARAM_NAME_list;
typedef List<None*> None_list;

class Transform;
class Visitor;

/* Node ::= All | Macro | Signature | Formal_parameter | Rule | Expr | Body | Body_part | Identifier; */
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

/* All ::= Macro* ; */
class All : virtual public Node
{
public:
    All(Macro_list* macros);
protected:
    All();
public:
    Macro_list* macros;
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
    virtual All* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Macro ::= Signature Rule* Body ; */
class Macro : virtual public Node
{
public:
    Macro(Signature* signature, Rule_list* rules, Body* body);
protected:
    Macro();
public:
    Signature* signature;
    Rule_list* rules;
    Body* body;
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
    virtual Macro* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Signature ::= MACRO_NAME Formal_parameter* ; */
class Signature : virtual public Node
{
public:
    Signature(MACRO_NAME* macro_name, Formal_parameter_list* formal_parameters);
protected:
    Signature();
public:
    MACRO_NAME* macro_name;
    Formal_parameter_list* formal_parameters;
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
    virtual Signature* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Formal_parameter ::= TYPE_NAME PARAM_NAME ; */
class Formal_parameter : virtual public Node
{
public:
    Formal_parameter(TYPE_NAME* type_name, PARAM_NAME* param_name);
protected:
    Formal_parameter();
public:
    TYPE_NAME* type_name;
    PARAM_NAME* param_name;
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
    virtual Formal_parameter* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Rule ::= Equals | Lookup; */
class Rule : virtual public Node
{
public:
    Rule();
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
    virtual Rule* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Expr ::= Param | STRING | Lookup | Macro_call | Callback; */
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

/* Body ::= Body_part* ; */
class Body : virtual public Node
{
public:
    Body(Body_part_list* body_parts);
protected:
    Body();
public:
    Body_part_list* body_parts;
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
    virtual Body* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Body_part ::= C_CODE | Interpolation | Macro_call | Callback; */
class Body_part : virtual public Node
{
public:
    Body_part();
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
    virtual Body_part* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Identifier ::= MACRO_NAME | TYPE_NAME | PARAM_NAME | ATTR_NAME | STRING | C_CODE; */
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

/* Equals ::= left:Expr right:Expr ; */
class Equals : virtual public Rule
{
public:
    Equals(Expr* left, Expr* right);
protected:
    Equals();
public:
    Expr* left;
    Expr* right;
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
    virtual Equals* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Param ::= PARAM_NAME ATTR_NAME* ; */
class Param : virtual public Expr
{
public:
    Param(PARAM_NAME* param_name, ATTR_NAME_list* attr_names);
protected:
    Param();
public:
    PARAM_NAME* param_name;
    ATTR_NAME_list* attr_names;
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
    virtual Param* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
public:
    Param(PARAM_NAME* param_name);
};

/* Interpolation ::= Lookup | PARAM_NAME; */
class Interpolation : virtual public Body_part
{
public:
    Interpolation();
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
    virtual Interpolation* clone() = 0;
public:
    virtual Node* find(Node* in) = 0;
public:
    virtual void find_all(Node* in, Node_list* out) = 0;
public:
    virtual void assert_valid() = 0;
};

/* Macro_call ::= MACRO_NAME Expr* ; */
class Macro_call : virtual public Expr, virtual public Body_part
{
public:
    Macro_call(MACRO_NAME* macro_name, Expr_list* exprs);
protected:
    Macro_call();
public:
    MACRO_NAME* macro_name;
    Expr_list* exprs;
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
    virtual Macro_call* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Callback ::= MACRO_NAME Expr* ; */
class Callback : virtual public Expr, virtual public Body_part
{
public:
    Callback(MACRO_NAME* macro_name, Expr_list* exprs);
protected:
    Callback();
public:
    MACRO_NAME* macro_name;
    Expr_list* exprs;
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
    virtual Callback* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class MACRO_NAME : virtual public Identifier
{
public:
    MACRO_NAME(String* value);
protected:
    MACRO_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 11;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual MACRO_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class TYPE_NAME : virtual public Identifier
{
public:
    TYPE_NAME(String* value);
protected:
    TYPE_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 12;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual TYPE_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class ATTR_NAME : virtual public Identifier
{
public:
    ATTR_NAME(String* value);
protected:
    ATTR_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 14;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual ATTR_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class STRING : virtual public Expr, virtual public Identifier
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
    static const int ID = 15;
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

class C_CODE : virtual public Body_part, virtual public Identifier
{
public:
    C_CODE(String* value);
protected:
    C_CODE();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 16;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual C_CODE* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* Lookup ::= PARAM_NAME ATTR_NAME ; */
class Lookup : virtual public Rule, virtual public Expr, virtual public Interpolation
{
public:
    Lookup(PARAM_NAME* param_name, ATTR_NAME* attr_name);
protected:
    Lookup();
public:
    PARAM_NAME* param_name;
    ATTR_NAME* attr_name;
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
    virtual Lookup* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

class PARAM_NAME : virtual public Interpolation, virtual public Identifier
{
public:
    PARAM_NAME(String* value);
protected:
    PARAM_NAME();
public:
    virtual void visit(Visitor* visitor);
    virtual void transform_children(Transform* transform);
public:
    String* value;
    virtual String* get_value_as_string();
public:
    static const int ID = 13;
    virtual int classid();
public:
    virtual bool match(Node* in);
public:
    virtual bool equals(Node* in);
public:
    virtual PARAM_NAME* clone();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
};

/* The top of the class hierarchy. If the Fold will not allow you fold to anything else, try this. */
class None : virtual public Node, virtual public All, virtual public Macro, virtual public Signature, virtual public Formal_parameter, virtual public Rule, virtual public Lookup, virtual public Equals, virtual public Expr, virtual public Param, virtual public Body, virtual public Body_part, virtual public Interpolation, virtual public Macro_call, virtual public Callback, virtual public Identifier, virtual public MACRO_NAME, virtual public TYPE_NAME, virtual public PARAM_NAME, virtual public ATTR_NAME, virtual public STRING, virtual public C_CODE
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
	static const int ID = 18;
	int classid()
	{
		return ID;
	}
};

}

#endif
