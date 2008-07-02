/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include "MIR_unparser.h" 
#include "MIR_to_AST.h" 

using namespace std;
using namespace MIR;

MIR_unparser::MIR_unparser (ostream& os, bool in_php)
: PHP_unparser (os, in_php)
{
	ast_unparser = new AST_unparser (this);
}

MIR_unparser::MIR_unparser (Unparser_state* ups)
: PHP_unparser (ups)
{
	ast_unparser = new AST_unparser (this);
}

void MIR_unparser::unparse (IR::Node* in)
{
	Node* mir = dynamic_cast<Node*> (in);
	AST::Node* ast = (new MIR_to_AST ())->fold_node (mir);

	// We dont return foreign_expr
	if (ast == NULL)
		unparse_foreign (in);
	else
		ast_unparser->unparse (ast);
}

void MIR_unparser::unparse_foreign (IR::Node* in)
{
	Node* mir = dynamic_cast<Node*> (in);
	mir->visit (this);
}

/* Nodes which are foreign in the AST */
void MIR_unparser::children_foreach_reset (Foreach_reset* in)
{
	echo ("foreach_reset($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (");");
}

void MIR_unparser::children_foreach_next (Foreach_next* in)
{
	echo ("foreach_next($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (");");
}

void MIR_unparser::children_foreach_end (Foreach_end* in)
{
	echo ("foreach_end($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (");");
}

void MIR_unparser::children_foreach_has_key (Foreach_has_key* in)
{
	echo ("foreach_has_key($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (")");
}

void MIR_unparser::children_foreach_get_key (Foreach_get_key* in)
{
	echo ("foreach_get_key($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (")");
}

void MIR_unparser::children_foreach_get_val (Foreach_get_val* in)
{
	echo ("foreach_get_val($");
	visit_variable_name (in->array);
	echo (", ");
	visit_ht_iterator (in->iter);
	echo (")");
}


void MIR_unparser::children_ht_iterator(HT_ITERATOR* in)
{
	echo (in->get_value_as_string ());
}

void MIR_unparser::children_variable_name (VARIABLE_NAME* in)
{
	// we leave out the $ to handle in the same manner as VARIABLE_NAME
	echo (in->value);
}

/* This is simpler than the other if, since there's no user-written code to
 * maintain, and the statements can only be gotos */
void MIR_unparser::children_branch(Branch* in)
{
	echo("if (");
	bool in_if_expression = true;
	visit_variable_name(in->variable_name);
	in_if_expression = false;
	echo(") goto ");
	visit_label_name (in->iftrue);
	echo (" else goto ");
	visit_label_name (in->iffalse);
	echo (";");

	newline();
}

void MIR_unparser::children_goto (Goto* in)
{
	echo ("goto ");
	visit_label_name (in->label_name);
	echo_nl (";");
}

void MIR_unparser::children_label (Label* in)
{
	visit_label_name (in->label_name);
	echo_nl(":");
}

void MIR_unparser::children_label_name (LABEL_NAME* in)
{
	echo(in->value);
}
