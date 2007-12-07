/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Common ancestor for the IRs 
 */

#ifndef PHC_IR_H
#define PHC_IR_H

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

class IR
{
// Operations that are defined over all IRs
public:
	virtual void assert_valid();

// Visit 
public:
	virtual void visit(AST::Visitor* ast_visitor);
	virtual void visit(HIR::Visitor* hir_visitor);
	virtual void visit(AST::Visitor* ast_visitor,
	                   HIR::Visitor* hir_visitor);
	
// Transform
public:
	virtual void transform_children(AST::Transform* ast_transform);
	virtual void transform_children(HIR::Transform* hir_transform);
	virtual void transform_children(AST::Transform* ast_transform,
	                                HIR::Transform* hir_transform);

// Conversion
public:
	virtual bool is_AST();
	virtual bool is_HIR();
	virtual AST::PHP_script* as_AST();
	virtual HIR::PHP_script* as_HIR();
	virtual IR* fold_lower ();

// Make sure IR is virtual
public:
	virtual ~IR() {}
};

#endif // PHC_IR_H
