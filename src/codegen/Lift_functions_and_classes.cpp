/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__" 
 *
 * TODO: at the moment, all this pass does is move any statements other than
 * function and class definitions into a method "main". It does not yet deal
 * with dynamic function/class definitions.
 */

#include "Lift_functions_and_classes.h"

void Lift_functions_and_classes::children_php_script(AST_php_script* in)
{
	current_scope = GLOBAL_SCOPE;
	main = new List<AST_statement*>;

	AST_transform::children_php_script(in);

	in->statements->push_back(new AST_method(
		new AST_signature(
			new AST_method_mod(),
			false,
			new Token_method_name(new String("__MAIN__")),
			new List<AST_formal_parameter*>),
		main));
}

void Lift_functions_and_classes::pre_class_def(AST_class_def* in, List<AST_statement*>* out)
{
	out->push_back(in);
}

void Lift_functions_and_classes::pre_interface_def(AST_interface_def* in, List<AST_statement*>* out)
{
	out->push_back(in);
}

void Lift_functions_and_classes::pre_method(AST_method* in, List<AST_method*>* out)
{
	out->push_back(in);
	current_scope = LOCAL_SCOPE;
}

void Lift_functions_and_classes::post_method(AST_method* in, List<AST_method*>* out)
{
	out->push_back(in);
	current_scope = GLOBAL_SCOPE;
}

void Lift_functions_and_classes::pre_if(AST_if* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_while(AST_while* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_do(AST_do* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_for(AST_for* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_foreach(AST_foreach* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_switch(AST_switch* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_break(AST_break* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_continue(AST_continue* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_return(AST_return* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_static_declaration(AST_static_declaration* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_unset(AST_unset* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_declare(AST_declare* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_try(AST_try* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_throw(AST_throw* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}

void Lift_functions_and_classes::pre_nop(AST_nop* in, List<AST_statement*>* out)
{
	if(current_scope == LOCAL_SCOPE)
		out->push_back(in);
	else
		main->push_back(in);
}
