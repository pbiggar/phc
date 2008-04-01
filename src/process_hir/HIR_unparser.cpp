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
, entry_node (NULL)
{
}

void HIR_unparser::pre_node (Node* in)
{
	// We want to print the top-most node, but we dont know what kind of node we
	// will be passed. So only print the top-level node, and ignore all others.
	if (entry_node != NULL)
		return;

	entry_node = in;

	// TODO It would be useful to be able to print the HIR in its HIR form. To
	// get the interpretable form, we would upper the HIR before being passed,
	// which would convert the foreach_* to functions. Then the standard form
	// would merely convert it directly, allowing it to be printed verbatim.
	// TODO: This goes well with the foreign idea.
	AST::Node* ast = (new HIR_to_AST ())->fold_node (in);
	ast->visit (&ast_unparser);
}


void HIR_unparser::post_node (Node* in)
{
	if (entry_node == in)
		entry_node = NULL;
}
