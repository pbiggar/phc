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
: ast_unparser (os, in_php)
{
}

void HIR_unparser::unparse (IR::Node* in)
{
	Node* hir = dynamic_cast<Node*> (in);
	AST::Node* ast = (new HIR_to_AST ())->fold_node (hir);
	ast_unparser.unparse (ast);
}
