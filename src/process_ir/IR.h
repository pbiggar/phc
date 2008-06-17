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

namespace IR
{

class Node : public Object
{
public:
	AttrMap* attrs;

	// Return the line number of the node (or 0 if unknown)
	int get_line_number()
	{
		Integer* i = dynamic_cast<Integer*>(attrs->get("phc.line_number"));
		if(i != NULL)
			return i->value();
		else
			return 0;
	}

	// Return the filename of the node. If unknown, use "<unknown>",
	// which is what the interpreter uses.
	// TODO In the future, make sure we always have filenames and
	// line numbers.
	String* get_filename()
	{
		String* result = dynamic_cast<String*>(attrs->get("phc.filename"));
		if (result == NULL)
			result = new String ("<unknown>");

		return result;
	}

	Node()
	{
		// Constructor gets called because all classes inherit from
		// Node virtually; also, because maketea knows Node is
		// abstract, it won't add a constructor itself
		attrs = new AttrMap();
	}

	virtual ~Node() {}
};


class PHP_script
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

}


/* These are copies of ideas from LLVM. All of our uses of casts can be
 * characterized as one of these. */
template <class T> bool isa(IR::Node* in) 
{ 
	return dynamic_cast<T*> (in) != NULL;
}

template <class T> T* dyc(IR::Node* in)
{ 
	T* result = dynamic_cast<T*> (in); 
	assert (result != NULL); 
	return result;
}




#endif // PHC_IR_H
