/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * An unparser using the guidelines Zend coding guidelines; see:
 * http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include <AST.h>
#include <iostream>
#include <AST_visitor.h>
#include <lib/demangle.h>
#include <process_ast/PHP_unparser.h>
#include <process_ast/Zend_style_unparser.h>

using namespace std;

/* Statische Variable initialisieren */
int Zend_Style_Unparser::array_elem_counter = 0;
int Zend_Style_Unparser::concat_counter = 0;
int Zend_Style_Unparser::logic_counter = 0;
bool Zend_Style_Unparser::is_method_invocation = false;
bool Zend_Style_Unparser::in_if_expression = false;

void 
Zend_Style_Unparser::pre_commented_node(AST_commented_node* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	for(i = comments->begin(); i != comments->end(); i++)
	{
		echo(*i);
		newline();
	}
}


void 
Zend_Style_Unparser::children_attribute(AST_attribute* in)
{
	in->attr_mod->visit(this);
	// Class attributes get a dollar sign, with the exception of const attributes
	if(!in->attr_mod->is_const) echo("$"); 
	in->variable_name->visit(this);
	if(in->expr != NULL)
	{
		echo(" = ");
		in->expr->visit(this);
	}
	echo_nl(";");
	empty_line();
}

void 
Zend_Style_Unparser::children_class_def(AST_class_def* in)
{
	in->class_mod->visit(this);
	echo("class ");
	in->class_name->visit(this);

	if(in->extends != NULL)
	{
		echo(" extends ");
		in->extends->visit(this);
	}

	if(!in->implements->empty())
	{
		echo(" implements ");
		in->implements->visit(this);
	}

	newline();
	echo_nl("{");
	inc_indent();
	in->members->visit(this);
	dec_indent();
	echo_nl("}");
}

void 
Zend_Style_Unparser::children_php_script(AST_php_script* in)
{
	echo("<?php");
	newline();

	// visit the interface definitions
	in->interface_defs->visit(this);

	// visit the class definitions, put %MAIN% to the beginning
	AST_class_def_list::const_iterator i;
	i = in->class_defs->end();
	i--;
	AST_class_def* class_def_main = dynamic_cast<AST_class_def*>(*i);

	inside_main = true;

	class_def_main->members->visit(this);
	inside_main = false;

	for(i = in->class_defs->begin(); i != in->class_defs->end(); i++)
	{
		AST_class_def* class_def = dynamic_cast<AST_class_def*>(*i);
		if(!(class_def && *class_def->class_name->value == "%MAIN%")) {
			class_def->visit(this);
		}
	}

	echo_nl("?>");
}

// exactly the same, except not putting out a newline after the expression
void 
Zend_Style_Unparser::children_if(AST_if* in)
{
	if(in->attrs->get_boolean("phc.unparser.is_elseif")->value())
		echo(" elseif (");
	else
		echo("if (");

	in_if_expression = true;
	in->expr->visit(this);
	in_if_expression = false;            

	echo(") ");

	in->iftrue->visit(this);

	if(!in->iffalse->empty())
	{
		AST_if* elseif = dynamic_cast<AST_if*>(in->iffalse->front());

		if(elseif && elseif->attrs->get_boolean("phc.unparser.is_elseif")->value())
		{
			elseif->visit(this);
		}
		else
		{
			echo(" else ");
			in->iffalse->visit(this);
		}

	}
	newline();
}

void 
Zend_Style_Unparser::children_while(AST_while* in)
{
	echo("while (");
	in->expr->visit(this);
	echo(") ");
	in->statements->visit(this);
	newline();
}

// "%run%" is treated specially in AST_member_list
void 
Zend_Style_Unparser::children_method(AST_method* in)
{
	in->signature->visit(this);
	newline();
	if(in->statements != NULL) {
		in->statements->visit(this);
		newline(); 
		newline();
	} else {
		// Abstract method
		echo_nl(";");
		newline();
	}
}

void 
Zend_Style_Unparser::children_do(AST_do* in)
{
	echo_nl("do");
	in->statements->visit(this);
	newline();
	echo("while (");
	in->expr->visit(this);
	echo_nl(");");
}

void 
Zend_Style_Unparser::children_for(AST_for* in)
{
	echo("for (");
	if(in->init != NULL) in->init->visit(this);
	echo("; ");
	if(in->cond != NULL) in->cond->visit(this);
	echo("; ");
	if(in->incr != NULL) in->incr->visit(this);
	echo(") ");
	in->statements->visit(this);
	newline();
}

void 
Zend_Style_Unparser::children_foreach(AST_foreach* in)
{
	echo("foreach (");
	in->expr->visit(this);
	echo(" as ");
	if(in->key != NULL) 
	{
		in->key->visit(this);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	in->val->visit(this);
	echo(") ");
	in->statements->visit(this);
	newline();
}

void 
Zend_Style_Unparser::children_switch(AST_switch* in)
{
	echo("switch (");
	in->expr->visit(this);
	echo(") ");
	in->switch_cases->visit(this);
}


void 
Zend_Style_Unparser::children_declare(AST_declare* in)
{
	echo("declare");
	in->directives->visit(this);

	if(!in->statements->empty()) {
		in->statements->visit(this);
		newline();
	} else {
		echo_nl(";");
	}
}

void 
Zend_Style_Unparser::children_try(AST_try* in)
{
	echo("try ");
	in->statements->visit(this);
	echo(" ");
	in->catches->visit(this);
}

void 
Zend_Style_Unparser::children_catch(AST_catch* in)
{
	echo("catch (");
	in->class_name->visit(this);
	echo(" $");
	in->variable_name->visit(this);
	echo(") ");
	in->statements->visit(this);
	newline();
}



void 
Zend_Style_Unparser::children_statement_list(AST_statement_list* in)
{
	echo("{");
	inc_indent();

	List<AST_statement*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		(*i)->visit(this);

	dec_indent();
	echo("}");
}

void 
Zend_Style_Unparser::pre_array_elem(AST_array_elem* in)
{
	if(!is_method_invocation) {
		array_elem_counter++;
		if(array_elem_counter > 0) {
			newline();
			indent_level++;
		} 
	}

}

void 
Zend_Style_Unparser::post_array_elem(AST_array_elem* in)
{
	if(!is_method_invocation) {
		if(array_elem_counter > 0) {
			indent_level--;
		} 

		array_elem_counter--;
	}

}

void 
Zend_Style_Unparser::children_actual_parameter(AST_actual_parameter* in)
{
	is_method_invocation = true;

	if(in->is_ref) echo("&");
	in->expr->visit(this);

	is_method_invocation = false;
}

void 
Zend_Style_Unparser::children_member_list(AST_member_list* in)
{
	AST_method* run = NULL;
	bool is_first = true;

	// Dieser Schleifendurchlauf dient nur dazu, die %run%-Methode zu ermitteln
	List<AST_member*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		AST_method* method = dynamic_cast<AST_method*>(*i);

		if(!method && inside_main)
		{
			continue;
		}

		if(method && *method->signature->method_name->value == "%run%")
		{
			run = method;	
		}
	}


	// Treat %run% specially
	// Rather than calling visit, we iterate over the vector manually
	// to avoid PHP_unparser::the opening and closing curlies
	if(inside_main)
	{
		assert(run);
		if(!is_first) empty_line();
		List<AST_statement*>::const_iterator j;
		for(j = run->statements->begin(); j != run->statements->end(); j++) {
			(*j)->visit(this);
			echo("\n");
		}
	}

	for(i = in->begin(); i != in->end(); i++)
	{
		AST_method* method = dynamic_cast<AST_method*>(*i);

		// Don't output attributes of %MAIN%
		if(!method && inside_main)
		{
			continue;
		}

		if(method && *method->signature->method_name->value == "%run%")
		{
		}
		// Otherwise, unparse the class member as normal
		else
		{		
			if(!is_first && method) empty_line();
			(*i)->visit(this);
			is_first = false;
		}
	}

}

void 
Zend_Style_Unparser::children_bin_op(AST_bin_op* in)
{
	in->left->visit(this);
	// We output "3 + 5", but "3, 5"
	/*
		if(*in->op->value != "," && *in->op->value != ".") echo(" "); 
	 */

	if(!in_if_expression) {
		// Erlaube nur maximal 2 Konkatenationen in einer Zeile
		if(*in->op->value == ".") {
			concat_counter++;
			if((concat_counter % 2) == 0) {
				newline();
				indent_level++;
			}
		}
	}

	/*
		else {
		if(*in->op->value == "||" || *in->op->value == "&&") {
		logic_counter++;
		if((logic_counter > 2) && (((logic_counter+1) % 2) == 0)) {
		echo("jonny");
		cout << logic_counter;
		newline();
		indent_level++;
		}
		}

		}

	 */
	echo(" ");
	in->op->visit(this);
	echo(" ");

	if(!in_if_expression) {
		if(*in->op->value == ".") {
			if((concat_counter % 2) == 0) {
				indent_level--;
			}
		}
	} 

	/*
		else {
		if(*in->op->value == "||" || *in->op->value == "&&") {
		if((logic_counter > 2) && (((logic_counter+1) % 2) == 0)) {
		logic_counter--;
		indent_level--;
		}
		}

		}
	 */

	in->right->visit(this);
}
