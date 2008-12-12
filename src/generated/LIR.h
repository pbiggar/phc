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
class CODE;
class None;

typedef List<Node*> Node_list;
typedef List<C_file*> C_file_list;
typedef List<CODE*> CODE_list;
typedef List<None*> None_list;

class Transform;
class Visitor;

/* Node ::= C_file | CODE<String*>; */
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

/* C_file ::= CODE<String*>* ; */
class C_file : virtual public Node, virtual public IR::PHP_script
{
public:
    C_file(CODE_list* codes);
protected:
    C_file();
public:
    CODE_list* codes;
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
};

class CODE : virtual public Node
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
public:
    static const int ID = 2;
    virtual int classid();
public:
    virtual bool match(Node* in);
    virtual bool match_value(CODE* that);
public:
    virtual bool equals(Node* in);
    virtual bool equals_value(CODE* that);
public:
    virtual CODE* clone();
    virtual String* clone_value();
public:
    virtual Node* find(Node* in);
public:
    virtual void find_all(Node* in, Node_list* out);
public:
    virtual void assert_valid();
    virtual void assert_value_valid();
};

/* The top of the class hierarchy. If the Fold will not allow you fold to anything else, try this. */
class None : virtual public Node, virtual public C_file, virtual public CODE
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
	static const int ID = 4;
	int classid()
	{
		return ID;
	}
};

}

#endif
