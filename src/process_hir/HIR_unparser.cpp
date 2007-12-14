/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include "process_ast/AST_unparser.h"
#include "HIR_unparser.h" 
#include "HIR_to_AST.h" 

using namespace std;
using namespace HIR;

HIR_unparser::HIR_unparser (ostream& os): os(os)
{
}

void HIR_unparser::pre_node (Node* in)
{
	AST::Node* ast = (new HIR_to_AST ())->fold_node (in);
	ast -> visit (new AST_unparser ());
}
