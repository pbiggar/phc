/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Common ancestor for the IRs 
 */

#include "IR.h"
#include "AST.h"
#include "HIR.h"
#include "ast_to_hir/AST_to_HIR.h"


void IR::assert_valid()
{
	if(is_AST())
		as_AST()->assert_valid();
	else
		as_HIR()->assert_valid();
}

void IR::visit(AST::Visitor* ast_visitor)
{
	as_AST()->visit(ast_visitor);
}

void IR::visit(HIR::Visitor* hir_visitor)
{
	as_HIR()->visit(hir_visitor);
}

void IR::visit(AST::Visitor* ast_visitor, HIR::Visitor* hir_visitor)
{
	if(is_AST())
		visit(ast_visitor);
	else
		visit(hir_visitor);
}

void IR::transform_children(AST::Transform* ast_transform)
{
	as_AST()->transform_children(ast_transform);
}

void IR::transform_children(HIR::Transform* hir_transform)
{
	as_HIR()->transform_children(hir_transform);
}

void IR::transform_children(AST::Transform* ast_transform, HIR::Transform* hir_transform)
{
	if(is_AST())
		transform_children(ast_transform);
	else
		transform_children(hir_transform);
}

bool IR::is_AST()
{
	return dynamic_cast<AST::PHP_script*>(this) != NULL;
}

bool IR::is_HIR()
{
	return dynamic_cast<HIR::PHP_script*>(this) != NULL;
}

AST::PHP_script* IR::as_AST()
{
	AST::PHP_script* ast = dynamic_cast<AST::PHP_script*>(this);
	assert(ast != NULL);
	return ast;
}

HIR::PHP_script* IR::as_HIR()
{
	HIR::PHP_script* hir = dynamic_cast<HIR::PHP_script*>(this);
	assert(hir != NULL);
	return hir;
}

IR* IR::fold_lower ()
{
	if (is_AST ())
		return (new AST_to_HIR ())->fold_php_script (as_AST ());
	else 
		return NULL;
}
