/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Common ancestor for the IRs 
 */

#ifndef PHC_IR_H
#define PHC_IR_H

#include "lib/Object.h"
#include "lib/AttrMap.h"
#include "lib/Integer.h"
#include "lib/String.h"
#include <string>

namespace AST 
{
	class PHP_script;
	class Visitor;
	class Transform;
}

namespace HIR
{
	class PHP_script;
	class Visitor;
	class Transform;
}

namespace MIR
{
	class PHP_script;
	class Visitor;
	class Transform;
}

class Unparser_state;

namespace IR
{

class Node : virtual public Object
{
public:
	AttrMap* attrs;

	Node();

	// Return the line number of the node (or 0 if unknown)
	int get_line_number();
	int get_column_number();

	// Return the filename of the node. If unknown, use "<unknown>",
	// which is what the interpreter uses.
	// TODO In the future, make sure we always have filenames and
	// line numbers.
	String* get_filename();

	virtual Node* clone () = 0;

	// If the location isnt already there, copy it from another node.
	void copy_location (Node* source);

	// Node features.
	bool equals (IR::Node*);

	virtual ~Node() {}
};

/*
 * Maketea doesn't provide const versions, so this will have to do.
 */


class FOREIGN : virtual public Object
{
public:
	virtual void unparse (Unparser_state* ups);

	// We cant have the value here, because the token sets it.
	virtual IR::Node* get_value () = 0;

	virtual ~FOREIGN() {}
};


class PHP_script : virtual public Object
{
// Operations that are defined over all IRs
public:
	virtual void assert_valid();

// Visit 
public:
	virtual void visit(AST::Visitor* ast_visitor);
	virtual void visit(HIR::Visitor* hir_visitor);
	virtual void visit(MIR::Visitor* mir_visitor);
	virtual void visit(AST::Visitor* ast_visitor,
	                   HIR::Visitor* hir_visitor,
	                   MIR::Visitor* mir_visitor);
	
// Transform
public:
	virtual void transform_children(AST::Transform* ast_transform);
	virtual void transform_children(HIR::Transform* hir_transform);
	virtual void transform_children(MIR::Transform* mir_transform);
	virtual void transform_children(AST::Transform* ast_transform,
	                                HIR::Transform* hir_transform,
	                                MIR::Transform* mir_transform);

// Conversion
public:
	virtual bool is_AST();
	virtual bool is_HIR();
	virtual bool is_MIR();
	virtual AST::PHP_script* as_AST();
	virtual HIR::PHP_script* as_HIR();
	virtual MIR::PHP_script* as_MIR();
	virtual PHP_script* fold_lower ();

// Make sure IR is virtual
public:
	virtual ~PHP_script() {}
};

typedef List<Node*> Node_list;

}

#endif // PHC_IR_H
