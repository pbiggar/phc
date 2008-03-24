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

MIR_unparser::MIR_unparser (ostream& os): os(os), entry_node(NULL)
{
}

void MIR_unparser::pre_node (Node* in)
{
	// We want to print the top-most node, but we dont know what kind of node we
	// will be passed. So only print the top-level node, and ignore all others.
	if (entry_node != NULL)
		return;

	entry_node = in;

	// TODO It would be useful to be able to print the MIR in its MIR form. To
	// get the interpretable form, we would upper the MIR before being passed,
	// which would convert the foreach_* to functions. Then the standard form
	// would merely convert it directly, allowing it to be printed verbatim.
	// TODO: This goes well with the foreign idea.
	AST::Node* ast = (new MIR_to_AST ())->fold_node (in);
	ast->visit (new AST_unparser (os));
}


void MIR_unparser::post_node (Node* in)
{
	if (entry_node == in)
		entry_node = NULL;
}
