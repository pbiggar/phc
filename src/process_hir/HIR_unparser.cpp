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

HIR_unparser::HIR_unparser::HIR_unparser (ostream& os, bool in_php)
: PHP_unparser (os, in_php)
, ast_unparser (os, in_php, this)
{
}

void HIR_unparser::unparse (IR::Node* in)
{
	Node* hir = dynamic_cast<Node*> (in);
	AST::Node* ast = (new HIR_to_AST ())->fold_node (hir);
	ast_unparser.unparse (ast);
}

void HIR_unparser::unparse_foreign (IR::Node* in)
{
	Node* mir = dynamic_cast<Node*> (in);
	mir->visit (this);
}

/* Nodes which are foreign in the AST */
void HIR_unparser::children_foreach_reset (Foreach_reset* in)
{
	echo ("foreach_reset($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (");");
}

void HIR_unparser::children_foreach_next (Foreach_next* in)
{
	echo ("foreach_next($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (");");
}

void HIR_unparser::children_foreach_end (Foreach_end* in)
{
	echo ("foreach_end($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (");");
}

void HIR_unparser::children_foreach_has_key (Foreach_has_key* in)
{
	echo ("foreach_has_key($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (")");
}

void HIR_unparser::children_foreach_get_key (Foreach_get_key* in)
{
	echo ("foreach_get_key($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (")");
}

void HIR_unparser::children_foreach_get_val (Foreach_get_val* in)
{
	echo ("foreach_get_val($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (")");
}


void HIR_unparser::children_ht_iterator(HT_ITERATOR* in)
{
	// we leave out the $ to handle in the same manner as VARIABLE_NAME
	echo (in->get_value_as_string ());
}
