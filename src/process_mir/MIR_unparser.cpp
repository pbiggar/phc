/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include <boost/lexical_cast.hpp>

#include "MIR_unparser.h" 
#include "MIR_to_AST.h" 

#include "process_mir/Alias_uppering.h"
#include "process_mir/Goto_uppering.h"
#include "process_mir/Foreach_uppering.h"
#include "process_mir/Param_is_ref_uppering.h"
#include "process_mir/Main_uppering.h"


using namespace std;
using namespace MIR;

string unparse (MIR::Node* in)
{
	stringstream ss;
	MIR_unparser (ss, true).unparse (in);

	return ss.str ();
}


MIR_unparser::MIR_unparser (ostream& os, bool in_php)
: PHP_unparser (os, in_php)
, ast_unparser (ups)
{
	folder = new MIR_to_AST ();
}

MIR_unparser::MIR_unparser (Unparser_state* ups)
: PHP_unparser (ups)
, ast_unparser (ups)
{
	folder = new MIR_to_AST ();
}

void MIR_unparser::unparse (IR::Node* in)
{
	// Folding a VARIABLE_NAME doesnt return an AST::VARIABLE_NAME
	if (isa<VARIABLE_NAME> (in))
	{
		VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);
		ast_unparser.unparse (
			new AST::VARIABLE_NAME(var_name->value));
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
		Node* mir = dyc<Node> (in);
		AST::Node* ast = folder->fold_node (mir);
		if (ast)
			ast_unparser.unparse (ast);
		else
			dyc<MIR::Node> (in)->visit (this);
	}
}

void
MIR_unparser::unparse_uppered (IR::PHP_script* in)
{
	MIR::PHP_script* mir = in->as_MIR ()->clone ();
	mir->transform_children (new Foreach_uppering);
	mir->transform_children (new Param_is_ref_uppering);
	mir->transform_children (new Alias_uppering);
	mir->visit (new Main_uppering);
	mir->visit (new Goto_uppering);
	AST::PHP_script* ast = (new MIR_to_AST ())->fold_php_script (mir);
	AST_unparser().unparse (ast) ;
}


void MIR_unparser::pre_foreign (FOREIGN* in)
{
	in->unparse (ups);
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
	echo (";");
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
	dec_indent ();
	visit_label_name (in->label_name);
	echo_nl(":");
	inc_indent ();
}

void MIR_unparser::children_label_name (LABEL_NAME* in)
{
	echo(in->value);
}

void MIR_unparser::children_param_is_ref (Param_is_ref* in)
{
	echo ("param_is_ref (");
	if (in->target)
	{
		echo ("$");
		unparse (in->target);
	}
	else
		echo ("NULL");

	echo (", \"");
	ast_unparser.unparse (folder->fold_method_name (in->method_name));
	echo ("\", ");
	echo (lexical_cast <string> (in->param_index->value));
	echo (")");
}

void MIR_unparser::children_class_alias (Class_alias* in)
{
	echo ("class_alias (\"");
	echo (in->alias->value);
	echo ("\", \"");
	echo (in->class_name->value);
	echo ("\");");
}

void MIR_unparser::children_interface_alias (Interface_alias* in)
{
	echo ("interface_alias (\"");
	echo (in->alias->value);
	echo ("\", \"");
	echo (in->interface_name->value);
	echo ("\");");
}

void MIR_unparser::children_method_alias (Method_alias* in)
{
	echo ("method_alias (\"");
	echo (in->alias->value);
	echo ("\", \"");
	echo (in->method_name->value);
	echo ("\");");
}
