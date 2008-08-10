/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include "HIR_unparser.h" 
#include "HIR_to_AST.h" 

using namespace std;
using namespace HIR;

HIR_unparser::HIR_unparser (ostream& os, bool in_php)
: PHP_unparser (os, in_php)
, ast_unparser (ups)
{
}

HIR_unparser::HIR_unparser (Unparser_state* ups)
: PHP_unparser (ups)
, ast_unparser (ups)
{
}

void HIR_unparser::unparse (IR::Node* in)
{
	// Folding a VARIABLE_NAME doesnt return an AST::VARIABLE_NAME
	if (isa<VARIABLE_NAME> (in))
	{
		VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);
		ast_unparser.unparse (
			new AST::VARIABLE_NAME (
				var_name->value));
	}
	else if (isa<Variable_variable> (in))
	{
		Variable_variable* var_var = dyc<Variable_variable> (in);
		ast_unparser.unparse (
			new AST::Reflection (
				new AST::Variable (
					new AST::VARIABLE_NAME (
						var_var->variable_name->value))));
	}
	else
	{
		Node* hir = dyc<Node> (in);
		AST::Node* ast = (new HIR_to_AST ())->fold_node (hir);
		if (ast)
			ast_unparser.unparse (ast);
		else
			dyc<HIR::Node> (in)->visit (this);
	}
}

void HIR_unparser::pre_foreign (FOREIGN* in)
{
	in->unparse (ups);
}
