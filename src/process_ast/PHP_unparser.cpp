/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include <iostream>
#include <iomanip> 
#include "PHP_unparser.h" 
#include "cmdline.h"

extern struct gengetopt_args_info args_info;

using namespace std;

void debug (AST_node *in)
{
	static PHP_unparser *pup = new PHP_unparser (cerr);
	in->visit (pup);
}

void PHP_unparser::echo(const char* str)
{
	output_tabs();
	os << str;
}

void PHP_unparser::echo_nl(const char* s)
{
	echo(s);
	newline();
}

void PHP_unparser::echo(String* str)
{
	output_tabs();
	os << *str;
}

void PHP_unparser::echo_escaped(string *s)
{
	output_tabs();

	string::iterator i;
	for(i = s->begin(); i != s->end(); i++)
	{
		switch(*i)
		{
			case '\n':
				os << "\\n";
				break;
			case '\r':
				os << "\\r";
				break;
			case '\t':
				os << "\\t";
				break;
			case '\\':
			case '$':
			case '"':
				os << "\\" << *i;
				break;
			default:
				if(*i < 32 || *i == 127)
				{
					os << "\\x" << setw(2) <<
						setfill('0') << hex << uppercase << (unsigned long int)(unsigned char)*i;
					os << resetiosflags(cout.flags());
				}
				else
					os << *i;
				break;
		}
	}
}

void PHP_unparser::inc_indent()
{
	indent_level++;
	newline();
}

void PHP_unparser::dec_indent()
{
	indent_level--;
	newline();
}

void PHP_unparser::newline()
{
	if(!at_start_of_line)
	{
		at_start_of_line = true;
		os << endl;
	}
}

void PHP_unparser::output_tabs()
{
	if(at_start_of_line)
		for(long i = 0; i < indent_level; i++)
			os << args_info.tab_arg;

	at_start_of_line = false;
}

void PHP_unparser::empty_line()
{
	at_start_of_line = true;
	os << endl;
}

void PHP_unparser::space_or_newline()
{
	if(args_info.next_line_curlies_flag)
		newline();
	else
		echo(" ");
}

PHP_unparser::PHP_unparser(ostream& os) : os(os)
{
	indent_level = 0;
	at_start_of_line = true;
}

void PHP_unparser::children_php_script(AST_php_script* in)
{
	echo("<?php");
	inc_indent();

	// We don't want to output the { and }, so we manually traverse the list
	List<AST_statement*>::const_iterator i;
	for(i = in->statements->begin(); i != in->statements->end(); i++)
		visit_statement(*i);

	dec_indent();
	echo_nl("?>");
}

void PHP_unparser::children_interface_def(AST_interface_def* in)
{
	echo("interface ");
	visit_interface_name(in->interface_name);

	if(!in->extends->empty())
	{
		echo(" extends ");
		visit_interface_name_list(in->extends);
	}
	
	visit_member_list(in->members);
}

void PHP_unparser::children_class_def(AST_class_def* in)
{
	visit_class_mod(in->class_mod);
	echo("class ");
	visit_class_name(in->class_name);

	if(in->extends != NULL)
	{
		echo(" extends ");
		visit_class_name(in->extends);
	}
	
	if(!in->implements->empty())
	{
		echo(" implements ");
		visit_interface_name_list(in->implements);
	}
	
	visit_member_list(in->members);
}

void PHP_unparser::children_class_mod(AST_class_mod* in)
{
	if(in->is_abstract) echo("abstract ");
	if(in->is_final) echo("final ");
}

void PHP_unparser::children_method(AST_method* in)
{
	visit_signature(in->signature);
	if(in->statements != NULL)
	{
		newline();
		visit_statement_list(in->statements);
		newline();
	}
	else
		// Abstract method
		echo_nl(";");
}

void PHP_unparser::children_signature(AST_signature* in)
{
	visit_method_mod(in->method_mod);
	echo("function ");
	if(in->is_ref) echo("&");
	visit_method_name(in->method_name);
	visit_formal_parameter_list(in->formal_parameters);
}

void PHP_unparser::children_method_mod(AST_method_mod* in)
{
	if(in->is_public)		echo("public ");
	if(in->is_protected)	echo("protected ");
	if(in->is_private)	echo("private ");
	if(in->is_static)		echo("static ");
	if(in->is_abstract)	echo("abstract ");
	if(in->is_final)		echo("final ");
}

void PHP_unparser::children_formal_parameter(AST_formal_parameter* in)
{
	visit_type(in->type);
	if(in->is_ref) echo("&");
	echo("$");
	visit_variable_name(in->variable_name);
	if(in->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->expr);
	}
}

void PHP_unparser::children_type(AST_type* in)
{
	if(in->is_array) echo("array ");
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo(" ");
	}
}

void PHP_unparser::children_attribute(AST_attribute* in)
{
	visit_attr_mod(in->attr_mod);
	// Class attributes get a dollar sign, with the exception of const attributes
	if(!in->attr_mod->is_const) echo("$"); 
	visit_variable_name(in->variable_name);
	if(in->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline is output by post_commented_node
}

void PHP_unparser::children_attr_mod(AST_attr_mod* in)
{
	if(in->is_public)		echo("public ");
	if(in->is_protected)	echo("protected ");
	if(in->is_private)	echo("private ");
	if(in->is_static)		echo("static ");
	if(in->is_const)		echo("const ");

	if(!in->is_public && 
		!in->is_protected && 
		!in->is_private && 
		!in->is_static && 
		!in->is_const)
			echo("var ");
}

void PHP_unparser::children_if(AST_if* in)
{
	if(in->attrs->is_true("phc.unparser.is_elseif")) echo("else");
	echo("if (");
	visit_expr(in->expr);
	echo(")");
	space_or_newline();

	visit_statement_list(in->iftrue);

	if(!in->iffalse->empty())
	{
		AST_if* elseif = dynamic_cast<AST_if*>(in->iffalse->front());

		space_or_newline();

		if(elseif && elseif->attrs->is_true("phc.unparser.is_elseif"))
		{
			visit_statement(elseif);
		}
		else
		{
			echo("else");
			space_or_newline();

			visit_statement_list(in->iffalse);
		}
	}

	newline();
}

/* This is simpler than the other if, since there's no user-written code to
 * maintain, and the statements can only be gotos */
void PHP_unparser::children_branch(AST_branch* in)
{
	echo("if (");
	bool in_if_expression = true;
	visit_expr(in->expr);
	in_if_expression = false;
	echo(") goto ");
	visit_label_name (in->iftrue);
	echo (" else goto ");
	visit_label_name (in->iffalse);
	echo (";");

	newline();
}

void PHP_unparser::children_while(AST_while* in)
{
	echo("while (");
	visit_expr(in->expr);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
	newline();
}

void PHP_unparser::children_do(AST_do* in)
{
	echo("do");
	space_or_newline();
	visit_statement_list(in->statements);
	space_or_newline();
	echo("while (");
	visit_expr(in->expr);
	echo_nl(");");
}

void PHP_unparser::children_for(AST_for* in)
{
	echo("for(");
	if(in->init != NULL) visit_expr(in->init);
	echo("; ");
	if(in->cond != NULL) visit_expr(in->cond);
	echo("; ");
	if(in->incr != NULL) visit_expr(in->incr);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
	newline();
}

void PHP_unparser::children_foreach(AST_foreach* in)
{
	echo("foreach (");
	visit_expr(in->expr);
	echo(" as ");
	if(in->key != NULL) 
	{
		visit_variable(in->key);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	visit_variable(in->val);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
	newline();
}

void PHP_unparser::children_switch(AST_switch* in)
{
	echo("switch (");
	visit_expr(in->expr);
	echo(")");
	space_or_newline();

	visit_switch_case_list(in->switch_cases);
}

void PHP_unparser::children_switch_case(AST_switch_case* in)
{
	if(in->expr != NULL)
	{
		echo("case ");
		visit_expr(in->expr);
		echo_nl(":");
	}
	else
	{
		echo_nl("default:");
	}

	// We don't want curlies here
	inc_indent();

	List<AST_statement*>::const_iterator i;
	for(i = in->statements->begin(); i != in->statements->end(); i++)
		visit_statement(*i);

	dec_indent();
}

void PHP_unparser::children_break(AST_break* in)
{
	echo("break");
	if(in->expr != NULL)
	{
		echo(" ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void PHP_unparser::children_continue(AST_continue* in)
{
	echo("continue");
	if(in->expr != NULL)
	{
		echo(" ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void PHP_unparser::children_return(AST_return* in)
{
	echo("return");
	if(in->expr != NULL)
	{
		echo(" ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void PHP_unparser::children_static_declaration(AST_static_declaration* in)
{
	echo("static $");
	visit_variable_name(in->variable_name);
	if(in->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void PHP_unparser::children_global(AST_global* in)
{
	echo("global $");
	visit_variable_name(in->variable_name);
	echo(";");
	// newline output by post_commented_node
}

void PHP_unparser::children_unset(AST_unset* in)
{
	echo("unset(");
	visit_variable(in->variable);
	echo(");");
	// newline output by post_commented_node
}

void PHP_unparser::children_declare(AST_declare* in)
{
	echo("declare");
	visit_directive_list(in->directives);
	space_or_newline();

	if(!in->statements->empty())
	{
		visit_statement_list(in->statements);
		newline();
	}
	else
	{
		echo(";");
		// newline output by post_commented_node
	}
}

void PHP_unparser::children_directive(AST_directive* in)
{
	visit_directive_name(in->directive_name);
	echo(" = ");
	visit_expr(in->expr);
}

void PHP_unparser::children_try(AST_try* in)
{
	echo("try");
	space_or_newline();

	visit_statement_list(in->statements);
	space_or_newline();

	visit_catch_list(in->catches);
}

void PHP_unparser::children_catch(AST_catch* in)
{
	echo("catch (");
	visit_class_name(in->class_name);
	echo(" $");
	visit_variable_name(in->variable_name);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
}

// We override post_catch_chain to avoid post_commented_node adding a newline
// after every catch (which messes up the layout when using same line curlies)
// We cannot deal with after-comments here, so we just assert that they don't
// exist and wait until somebody complains :)
void PHP_unparser::post_catch_chain(AST_catch* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	
	for(i = comments->begin(); i != comments->end(); i++)
	{
		assert(!((*i)->attrs->is_true("phc.unparser.comment.after")));
	}
}

void PHP_unparser::children_throw(AST_throw* in)
{
	echo("throw ");
	visit_expr(in->expr);
	echo(";");
	// newline output by post_commented_node
}

void PHP_unparser::children_eval_expr(AST_eval_expr* in)
{
	visit_expr(in->expr);
	echo(";");
	// The newline gets added by post_commented_node
}

void PHP_unparser::children_assignment(AST_assignment* in)
{
	if(in->attrs->is_true("phc.unparser.is_opeq"))
	{
		AST_bin_op* bin_op = dynamic_cast<AST_bin_op*>(in->expr);
		assert(bin_op);

		// $a += $b;
		visit_expr(bin_op->left);
		echo(" ");
		visit_op(bin_op->op);
		echo("= ");
		visit_expr(bin_op->right);
	}
	else
	{
		visit_variable(in->variable);

		if(in->is_ref)
			echo(" =& ");
		else
			echo(" = ");

		visit_expr(in->expr);
	}
}

void PHP_unparser::children_list_assignment(AST_list_assignment* in)
{
	visit_list_elements(in->list_elements);
	echo(" = ");
	visit_expr(in->expr);
}

void PHP_unparser::children_list_elements(AST_list_elements* in)
{
	echo("list");
	visit_list_element_list(in->list_elements);
}

void PHP_unparser::children_cast(AST_cast* in)
{
	echo("(");
	visit_cast(in->cast);
	echo(") ");
	visit_expr(in->expr);
}

void PHP_unparser::children_unary_op(AST_unary_op* in)
{
	visit_op(in->op);
	visit_expr(in->expr);
}

void PHP_unparser::children_bin_op(AST_bin_op* in)
{
	visit_expr(in->left);
	if(*in->op->value != ",") echo(" "); // We output "3 + 5", but "3, 5"
	visit_op(in->op);
	echo(" ");
	visit_expr(in->right);
}

void PHP_unparser::children_conditional_expr(AST_conditional_expr* in)
{
	visit_expr(in->cond);
	echo(" ? ");
	visit_expr(in->iftrue);
	echo(" : ");
	visit_expr(in->iffalse);
}

void PHP_unparser::children_ignore_errors(AST_ignore_errors* in)
{
	echo("@");
	visit_expr(in->expr);
}

void PHP_unparser::children_constant(AST_constant* in)
{
	if((*in->class_name->value)[0] == '%')
	{
		visit_constant_name(in->constant_name);
	}
	else
	{
		visit_class_name(in->class_name);
		echo("::");
		visit_constant_name(in->constant_name);
	}
}

void PHP_unparser::children_instanceof(AST_instanceof* in)
{
	visit_expr(in->expr);
	echo(" instanceof ");
	visit_class_name(in->class_name);
}

void PHP_unparser::children_variable(AST_variable* in)
{
	AST_reflection* reflection;
	AST_variable* name = NULL;

	if(in->target != NULL)
	{
		Token_class_name* class_name = dynamic_cast<Token_class_name*>(in->target);

		if(class_name)
		{
			if((*class_name->value)[0] == '%')
			{
				echo("$");
			}
			else
			{
				visit_class_name(class_name);
				echo("::$");
			}
		}
		else
		{
			visit_target(in->target);
			echo("->");
		}
	}
	else
	{
		echo("$");
	}

	reflection = dynamic_cast<AST_reflection*>(in->variable_name);
	
	if(reflection)
	{
		name = dynamic_cast<AST_variable*>(reflection->expr);
		visit_variable_name(in->variable_name);
	}
	else
	{
		visit_variable_name(in->variable_name);
	}

	List<AST_expr*>::const_iterator i;
	for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
	{
		if(*i && (*i)->attrs->is_true("phc.unparser.index_curlies"))
		{
			echo("{");
			if(*i) visit_expr(*i);
			echo("}");
		}
		else
		{
			echo("[");
			if(*i) visit_expr(*i);
			echo("]");
		}
	}
}

void PHP_unparser::children_reflection(AST_reflection* in)
{
	visit_expr(in->expr);
}

void PHP_unparser::children_pre_op(AST_pre_op* in)
{
	visit_op(in->op);
	visit_variable(in->variable);
}

void PHP_unparser::children_post_op(AST_post_op* in)
{
	visit_variable(in->variable);
	visit_op(in->op);
}

void PHP_unparser::children_array(AST_array* in)
{
	echo("array");
	visit_array_elem_list(in->array_elems);
}

void PHP_unparser::children_array_elem(AST_array_elem* in)
{
	if(in->key != NULL)
	{
		visit_expr(in->key);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	visit_expr(in->val);
}

void PHP_unparser::children_method_invocation(AST_method_invocation* in)
{
	bool after_arrow = false;
	bool use_brackets = true;
	Token_class_name* static_method;
	Token_method_name* method_name;

	static_method = dynamic_cast<Token_class_name*>(in->target);
	if(static_method)
	{
		if((*static_method->value)[0] == '%')
		{
			// Don't print names of phc pseudo-classes
		}
		else
		{
			visit_class_name(static_method);
			echo("::");
		}
	}
	else
	{
		visit_target(in->target);
		echo("->");
		after_arrow = true;
	}

	// Leave out brackets in calls in builtins
	method_name = dynamic_cast<Token_method_name*>(in->method_name);
	if(static_method && method_name && *static_method->value == "%STDLIB%")
	{
		use_brackets &= *method_name->value != "echo";
		use_brackets &= *method_name->value != "print";
		use_brackets &= *method_name->value != "include";
		use_brackets &= *method_name->value != "include_once";
		use_brackets &= *method_name->value != "require";
		use_brackets &= *method_name->value != "require_once";
		use_brackets &= *method_name->value != "use";
	}

	if(!use_brackets)
	{
		visit_method_name(in->method_name);
		echo(" ");	
		visit_actual_parameter_list(in->actual_parameters);
	}
	else
	{
		visit_method_name(in->method_name);

		echo("(");
		visit_actual_parameter_list(in->actual_parameters);
		echo(")");
	}
}

void PHP_unparser::children_actual_parameter(AST_actual_parameter* in)
{
	if(in->is_ref) echo("&");
	visit_expr(in->expr);
}

void PHP_unparser::children_new(AST_new* in)
{
	echo("new ");
	visit_class_name(in->class_name);
	echo("(");
	visit_actual_parameter_list(in->actual_parameters);
	echo(")");
}

void PHP_unparser::children_clone(AST_clone* in)
{
	echo("clone ");
	visit_expr(in->expr);
}

void PHP_unparser::visit_interface_name_list(List<Token_interface_name*>* in)
{
	List<Token_interface_name*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_interface_name(*i);
	}
}

void PHP_unparser::visit_member_list(List<AST_member*>* in)
{
	newline();
	echo_nl("{");
	inc_indent();

	AST_visitor::visit_member_list(in);	

	dec_indent();
	echo_nl("}");
}

void PHP_unparser::visit_statement_list(List<AST_statement*>* in)
{
	echo("{");
	inc_indent();

	AST_visitor::visit_statement_list(in);

	dec_indent();
	echo("}");
}

void PHP_unparser::visit_formal_parameter_list(List<AST_formal_parameter*>* in)
{
	echo("(");
	List<AST_formal_parameter*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_formal_parameter(*i);
	}
	echo(")");
}

void PHP_unparser::visit_switch_case_list(List<AST_switch_case*>* in)
{
	echo_nl("{");
	inc_indent();

	List<AST_switch_case*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		visit_switch_case(*i);

	dec_indent();
	echo_nl("}");
}

void PHP_unparser::visit_directive_list(List<AST_directive*>* in)
{
	echo("(");

	List<AST_directive*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_directive(*i);
	}
	
	echo(")");
}

void PHP_unparser::visit_catch_list(List<AST_catch*>* in)
{
	List<AST_catch*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) space_or_newline();
		visit_catch(*i);
	}
}

void PHP_unparser::visit_list_element_list(List<AST_list_element*>* in)
{
	echo("(");

	List<AST_list_element*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		if(*i) visit_list_element(*i);
	}

	echo(")");
}

void PHP_unparser::visit_expr_list(List<AST_expr*>* in)
{
	List<AST_expr*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		if(*i) visit_expr(*i);
}

void PHP_unparser::visit_array_elem_list(List<AST_array_elem*>* in)
{
	echo("(");

	List<AST_array_elem*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_array_elem(*i);
	}

	echo(")");
}

void PHP_unparser::visit_actual_parameter_list(List<AST_actual_parameter*>* in)
{
	List<AST_actual_parameter*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_actual_parameter(*i);
	}
}

// Token classes
void PHP_unparser::children_interface_name(Token_interface_name* in)
{
	echo(in->value);
}

void PHP_unparser::children_class_name(Token_class_name* in)
{
	echo(in->value);
}

void PHP_unparser::children_method_name(Token_method_name* in)
{
	echo(in->value);
}

void PHP_unparser::children_variable_name(Token_variable_name* in)
{
	echo(in->value);
}

void PHP_unparser::children_directive_name(Token_directive_name* in)
{
	echo(in->value);
}

void PHP_unparser::children_cast(Token_cast* in)
{
	echo(in->value);
}

void PHP_unparser::children_op(Token_op* in)
{
	echo(in->value);
}

void PHP_unparser::children_constant_name(Token_constant_name* in)
{
	echo(in->value);
}

void PHP_unparser::children_int(Token_int* in)
{
	echo(in->source_rep);
}

void PHP_unparser::children_real(Token_real* in)
{
	echo(in->source_rep);
}

void PHP_unparser::children_string(Token_string* in)
{
	if(
			*in->source_rep == "__FILE__" ||
			*in->source_rep == "__CLASS__" ||
			*in->source_rep == "__METHOD__" ||
			*in->source_rep == "__FUNCTION__"
	  )
	{
		echo(in->source_rep);
	}
	else
	{
		if(in->attrs->is_true("phc.unparser.is_singly_quoted"))
		{
			string::iterator i;

			echo("'");
			// Only thing that can be escaped in an SQ string is the single quote 
			for(i = in->source_rep->begin(); i != in->source_rep->end(); i++)
			{
				if(*i == '\'') 
					os << "\\'";
				else
					os << *i;
			}
			echo("'");
		}
		else 
		{
			echo("\"");
			echo_escaped(in->source_rep);
			echo("\"");
		}
	}
}

void PHP_unparser::children_bool(Token_bool* in)
{
	echo(in->source_rep);
}

void PHP_unparser::children_null(Token_null* in)
{
	echo(in->source_rep);
}

// Generic classes
void PHP_unparser::pre_node(AST_node* in)
{
	if(in->attrs->is_true("phc.unparser.starts_line") && !at_start_of_line)
	{
		newline();
		os << args_info.tab_arg;
	}
}

void PHP_unparser::pre_expr(AST_expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_brackets"))
		echo("(");
	if(in->attrs->is_true("phc.unparser.needs_curlies"))
		echo("{");
}

void PHP_unparser::post_expr(AST_expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_curlies"))
		echo("}");
	if(in->attrs->is_true("phc.unparser.needs_brackets"))
		echo(")");
}

void PHP_unparser::pre_commented_node(AST_commented_node* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	for(i = comments->begin(); i != comments->end(); i++)
	{
		if(!(*i)->attrs->is_true("phc.unparser.comment.after"))
		{
			echo(*i);
			newline();
		}
	}
}

// Note: does not get executed for AST_catch (which overrides post_catch_chain)
void PHP_unparser::post_commented_node(AST_commented_node* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	bool output_comment = false;

	for(i = comments->begin(); i != comments->end(); i++)
	{
		if((*i)->attrs->is_true("phc.unparser.comment.after"))
		{
			if(!output_comment) echo(" ");
			echo(*i);
			newline();
			output_comment = true;
		}
	}

	if(!output_comment) newline();
}

void PHP_unparser::children_label_name (Token_label_name* in)
{
	os << *in->value;
}

void 
PHP_unparser::children_goto (AST_goto* in)
{
	echo ("goto ");
	visit_label_name (in->label_name);
	echo_nl (";");
}

void 
PHP_unparser::children_label (AST_label* in)
{
	visit_label_name (in->label_name);
	os << ":" << endl;
}
