/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include <iostream>
#include <iomanip> 
#include "HIR_unparser.h" 
#include "cmdline.h"

extern struct gengetopt_args_info args_info;

using namespace std;
using namespace HIR;

HIR_unparser::HIR_unparser (ostream& os) : PHP_unparser (os)
{
}

void HIR_unparser::children_php_script(PHP_script* in)
{
	echo_nl("<?php");
	if(!args_info.no_leading_tab_flag) inc_indent();

	// We don't want to output the { and }, so we manually traverse the list
	List<Statement*>::const_iterator i;
	for(i = in->statements->begin(); i != in->statements->end(); i++)
		visit_statement(*i);
	
	if(!args_info.no_leading_tab_flag) dec_indent();
	echo_nl("?>");
}

void HIR_unparser::children_interface_def(Interface_def* in)
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

void HIR_unparser::children_class_def(Class_def* in)
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

void HIR_unparser::children_class_mod(Class_mod* in)
{
	if(in->is_abstract) echo("abstract ");
	if(in->is_final) echo("final ");
}

void HIR_unparser::children_method(Method* in)
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

void HIR_unparser::children_signature(Signature* in)
{
	visit_method_mod(in->method_mod);
	echo("function ");
	if(in->is_ref) echo("&");
	visit_method_name(in->method_name);
	visit_formal_parameter_list(in->formal_parameters);
}

void HIR_unparser::children_method_mod(Method_mod* in)
{
	if(in->is_public)		echo("public ");
	if(in->is_protected)	echo("protected ");
	if(in->is_private)	echo("private ");
	if(in->is_static)		echo("static ");
	if(in->is_abstract)	echo("abstract ");
	if(in->is_final)		echo("final ");
}

void HIR_unparser::children_formal_parameter(Formal_parameter* in)
{
	visit_type(in->type);
	if(in->is_ref) echo("&");
	visit_name_with_default(in->var);
}

void HIR_unparser::children_type(Type* in)
{
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo(" ");
	}
}

void HIR_unparser::children_attribute(Attribute* in)
{
	visit_attr_mod(in->attr_mod);

	// Class attributes get a dollar sign, with the exception of const attributes
	if(!in->attr_mod->is_const) echo("$"); 
	visit_variable_name(in->var->variable_name);
	if(in->var->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->var->expr);
	}

	echo(";");
	// newline is output by post_commented_node
}

void HIR_unparser::children_attr_mod(Attr_mod* in)
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


/* This is simpler than the other if, since there's no user-written code to
 * maintain, and the statements can only be gotos */
void HIR_unparser::children_branch(Branch* in)
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

void HIR_unparser::children_return(Return* in)
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

void HIR_unparser::children_static_declaration(Static_declaration* in)
{
	echo("static ");
	visit_name_with_default(in->var);
	echo(";");
	// newline output by post_commented_node
}

void HIR_unparser::children_global(Global* in)
{
	echo("global $");
	visit_variable_name(in->variable_name);
	echo(";");
	// newline output by post_commented_node
}

void HIR_unparser::children_try(Try* in)
{
	echo("try");
	space_or_newline();

	visit_statement_list(in->statements);
	space_or_newline();

	visit_catch_list(in->catches);
}

void HIR_unparser::children_catch(Catch* in)
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
void HIR_unparser::post_catch_chain(Catch* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	
	for(i = comments->begin(); i != comments->end(); i++)
	{
		assert(!((*i)->attrs->is_true("phc.unparser.comment.after")));
	}
}

void HIR_unparser::children_throw(Throw* in)
{
	echo("throw ");
	visit_expr(in->expr);
	echo(";");
	// newline output by post_commented_node
}

void HIR_unparser::children_eval_expr(Eval_expr* in)
{
	visit_expr(in->expr);
	echo(";");
	// The newline gets added by post_commented_node
}

void HIR_unparser::children_assignment(Assignment* in)
{
	visit_variable(in->variable);

	if(in->is_ref)
		echo(" =& ");
	else
		echo(" = ");

	visit_expr(in->expr);
}

void HIR_unparser::children_cast(Cast* in)
{
	echo("(");
	visit_cast(in->cast);
	echo(") ");
	visit_variable_name(in->variable_name);
}

void HIR_unparser::children_unary_op(Unary_op* in)
{
	visit_op(in->op);
	visit_variable_name(in->variable_name);
}

void HIR_unparser::children_bin_op(Bin_op* in)
{
	visit_variable_name(in->left);
	if(*in->op->value != ",") echo(" "); // We output "3 + 5", but "3, 5"
	visit_op(in->op);
	echo(" ");
	visit_variable_name(in->right);
}

void HIR_unparser::children_constant(Constant* in)
{
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo("::");
	}

	visit_constant_name(in->constant_name);
}

void HIR_unparser::children_instanceof(Instanceof* in)
{
	visit_variable_name(in->variable_name);
	echo(" instanceof ");
	visit_class_name(in->class_name);
}

void HIR_unparser::children_variable(Variable* in)
{
	Reflection* reflection;

	if(in->target != NULL)
	{
		CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(in->target);

		if(class_name)
		{
			visit_class_name(class_name);
			echo("::$");
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

	reflection = dynamic_cast<Reflection*>(in->variable_name);
	
	if(reflection)
	{
//		TODO this doesnt do anything. Bug?
//		name = dynamic_cast<Variable*>(reflection->expr);
		visit_variable_name(in->variable_name);
	}
	else
	{
		visit_variable_name(in->variable_name);
	}

	List<VARIABLE_NAME*>::const_iterator i;
	for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
	{
		if(*i && (*i)->attrs->is_true("phc.unparser.index_curlies"))
		{
			echo("{");
			if(*i) visit_variable_name (*i);
			echo("}");
		}
		else
		{
			echo("[");
			if(*i) visit_variable_name (*i);
			echo("]");
		}
	}
}

void HIR_unparser::children_reflection(Reflection* in)
{
	visit_variable_name (in->variable_name);
}

void HIR_unparser::children_pre_op(Pre_op* in)
{
	visit_op(in->op);
	visit_variable(in->variable);
}

void HIR_unparser::children_array(Array* in)
{
	echo("array");
	visit_array_elem_list(in->array_elems);
}

void HIR_unparser::children_array_elem(Array_elem* in)
{
	if(in->key != NULL)
	{
		visit_expr(in->key);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	visit_expr(in->val);
}

void HIR_unparser::children_method_invocation(Method_invocation* in)
{
	bool after_arrow = false;
	bool use_brackets = true;
	CLASS_NAME* static_method;
	METHOD_NAME* method_name;

	static_method = dynamic_cast<CLASS_NAME*>(in->target);
	if(static_method)
	{
		visit_class_name(static_method);
		echo("::");
	}
	else if(in->target != NULL)
	{
		visit_target(in->target);
		echo("->");
		after_arrow = true;
	}

	// Leave out brackets in calls in builtins
	method_name = dynamic_cast<METHOD_NAME*>(in->method_name);
	if(method_name)
	{
		use_brackets &= *method_name->value != "echo";
		use_brackets &= *method_name->value != "print";
		use_brackets &= *method_name->value != "include";
		use_brackets &= *method_name->value != "include_once";
		use_brackets &= *method_name->value != "require";
		use_brackets &= *method_name->value != "require_once";
		use_brackets &= *method_name->value != "use";
		use_brackets &= *method_name->value != "clone";
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

void HIR_unparser::children_actual_parameter(Actual_parameter* in)
{
	if(in->is_ref) echo("&");
	visit_target (in->target);
	visit_variable_name (in->variable_name);

	List<VARIABLE_NAME*>::const_iterator i;
	for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
	{
			echo("[");
			if(*i) visit_variable_name (*i);
			echo("]");
	}
}

void HIR_unparser::children_new(New* in)
{
	echo("new ");
	visit_class_name(in->class_name);
	echo("(");
	visit_actual_parameter_list(in->actual_parameters);
	echo(")");
}

void HIR_unparser::visit_interface_name_list(List<INTERFACE_NAME*>* in)
{
	List<INTERFACE_NAME*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_interface_name(*i);
	}
}

void HIR_unparser::visit_member_list(List<Member*>* in)
{
	newline();
	echo_nl("{");
	inc_indent();

	Visitor::visit_member_list(in);	

	dec_indent();
	echo_nl("}");
}

void HIR_unparser::visit_statement_list(List<Statement*>* in)
{
	echo("{");
	inc_indent();

	Visitor::visit_statement_list(in);

	dec_indent();
	echo("}");
}

void HIR_unparser::visit_formal_parameter_list(List<Formal_parameter*>* in)
{
	echo("(");
	List<Formal_parameter*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_formal_parameter(*i);
	}
	echo(")");
}

void HIR_unparser::visit_catch_list(List<Catch*>* in)
{
	List<Catch*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) space_or_newline();
		visit_catch(*i);
	}
}

void HIR_unparser::visit_expr_list(List<Expr*>* in)
{
	List<Expr*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		if(*i) visit_expr(*i);
}

void HIR_unparser::visit_array_elem_list(List<Array_elem*>* in)
{
	echo("(");

	List<Array_elem*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_array_elem(*i);
	}

	echo(")");
}

void HIR_unparser::visit_actual_parameter_list(List<Actual_parameter*>* in)
{
	List<Actual_parameter*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_actual_parameter(*i);
	}
}

void HIR_unparser::visit_name_with_default_list(List<Name_with_default*>* in)
{
	List<Name_with_default*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_name_with_default(*i);
	}
}

// Token classes
void HIR_unparser::children_interface_name(INTERFACE_NAME* in)
{
	echo(in->value);
}

void HIR_unparser::children_class_name(CLASS_NAME* in)
{
	echo(in->value);
}

void HIR_unparser::children_method_name(METHOD_NAME* in)
{
	echo(in->value);
}

void HIR_unparser::children_variable_name(VARIABLE_NAME* in)
{
	echo(in->value);
}

void HIR_unparser::children_cast(CAST* in)
{
	echo(in->value);
}

void HIR_unparser::children_op(OP* in)
{
	echo(in->value);
}

void HIR_unparser::children_constant_name(CONSTANT_NAME* in)
{
	echo(in->value);
}

void HIR_unparser::children_int(INT* in)
{
	echo(in->source_rep);
}

void HIR_unparser::children_real(REAL* in)
{
	echo(in->source_rep);
}

void HIR_unparser::children_string(STRING* in)
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
    // any escaping must already be present in source_rep; any strings that
    // originate from the user will be escaped as the user escaped them,
    // and any strings that originate from passes within the compiler should
    // have been escaped by those passes
		
    if(in->attrs->is_true("phc.unparser.is_singly_quoted"))
		{
			echo("'");
			echo(in->source_rep);
			echo("'");
		}
		else 
		{
      echo("\"");
			echo(in->source_rep);
			echo("\"");
		}
	}
}

void HIR_unparser::children_bool(BOOL* in)
{
	echo(in->source_rep);
}

void HIR_unparser::children_nil(NIL* in)
{
	echo(in->source_rep);
}

// Generic classes
void HIR_unparser::pre_node(Node* in)
{
	if(in->attrs->is_true("phc.unparser.starts_line") && !at_start_of_line)
	{
		newline();
		echo(args_info.tab_arg);
	}
}

/* There are a number of places where curlies are required. All of these
 * involves reflection, and some special cases in the node containing the
 * reflected variable. In general $$$$x (ie any amunt of nested variabels) is
 * ok, and anything else requires curlies. */
bool needs_curlies (Reflection* in)
{
	return false;
}

void HIR_unparser::pre_variable (Variable* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->variable_name);
	if (reflect && 
			(needs_curlies (reflect) || in->array_indices->size () > 0))
		assert (0); // this shouldnt be possible anymore
}

void HIR_unparser::pre_method_invocation (Method_invocation* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->method_name);
	if (in->target
			&& reflect && needs_curlies (reflect))
		assert (0); // this shouldnt be possible anymore
}

void HIR_unparser::pre_global (Global* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->variable_name);
	if (reflect && needs_curlies (reflect))
		assert (0); // this shouldnt be possible anymore
}

void HIR_unparser::pre_expr(Expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_user_brackets"))
		echo("(");
	if(in->attrs->is_true("phc.unparser.needs_curlies") or in->attrs->is_true("phc.unparser.needs_user_curlies"))
		echo("{");
}

void HIR_unparser::post_expr(Expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_curlies") or in->attrs->is_true("phc.unparser.needs_user_curlies"))
		echo("}");
	if(in->attrs->is_true("phc.unparser.needs_user_brackets"))
		echo(")");
}

void HIR_unparser::children_label_name (LABEL_NAME* in)
{
	echo(in->value);
}

void 
HIR_unparser::children_goto (Goto* in)
{
	echo ("goto ");
	visit_label_name (in->label_name);
	echo_nl (";");
}

void 
HIR_unparser::children_label (Label* in)
{
	visit_label_name (in->label_name);
	echo_nl(":");
}

void HIR_unparser::children_name_with_default (Name_with_default* in)
{
	echo("$");
	visit_variable_name(in->variable_name);
	if(in->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->expr);
	}
}
