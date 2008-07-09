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
{
	// We unparse by converting to AST, but keeping foreign nodes in. Unparsing
	// the foreign nodes is delegated to the MIR_unparser.
	ast_unparser = new AST_unparser (this);
	mir_unparser = new MIR_unparser (ups);
}

void HIR_unparser::unparse (IR::Node* in)
{
	// Folding a VARIABLE_NAME doesnt return an AST::VARIABLE_NAME
	if (isa<VARIABLE_NAME> (in))
	{
		VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);
		ast_unparser->unparse (
			new AST::VARIABLE_NAME (
				var_name->value));
	}
	else if (isa<Variable_variable> (in))
	{
		Variable_variable* var_var = dyc<Variable_variable> (in);
		ast_unparser->unparse (
			new AST::Reflection (
				new AST::Variable (
					new AST::VARIABLE_NAME (
						var_var->variable_name->value))));
	}
	else
	{
		Node* hir = dynamic_cast<Node*> (in);
		AST::Node* ast = (new HIR_to_AST ())->fold_node (hir);
		ast_unparser->unparse (ast);
	}
}

void HIR_unparser::unparse_foreign (IR::Node* in)
{
	Node* hir = dynamic_cast<Node*> (in);
	if (!hir)
	{
		// HIR-to-MIR will have MIR nodes, which get passed to the AST_parser,
		// and back to here. Pass them on to the MIR_unparser.
		MIR::Node* mir = dynamic_cast<MIR::Node*>(in);
		assert (mir);
		mir_unparser->unparse (mir);
	}
	else
		hir->visit (this);
}

void HIR_unparser::pre_foreign (Foreign* in)
{
	// The foreign nodes should contain a piece of the MIR
	MIR::Node* mir = dynamic_cast<MIR::Node*>(in->foreign);
	assert (mir);
	mir_unparser->unparse (mir);
}
