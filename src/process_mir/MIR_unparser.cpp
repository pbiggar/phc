/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include "process_ast/AST_unparser.h"
#include "MIR_unparser.h" 
#include "MIR_to_AST.h" 

using namespace std;
using namespace MIR;

MIR_unparser::MIR_unparser (ostream& os, bool in_php)
: ast_unparser (os, in_php)
{
}

void MIR_unparser::unparse (IR::Node* in)
{
	Node* mir = dynamic_cast<Node*> (in);
	AST::Node* ast = (new MIR_to_AST ())->fold_node (mir);
	ast_unparser.unparse (ast);
}
