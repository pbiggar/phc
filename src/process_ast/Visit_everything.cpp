/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "Visit_everything.h" 

void Visit_everything::children_class_def(AST_class_def* in)
{
	in->class_mod->visit(this);
	in->class_name->visit(this);
	if(in->extends != NULL)
		in->extends->visit(this);
	else
		visit_null("Token_class_name");
	in->implements->visit(this);
	in->members->visit(this);
}

void Visit_everything::children_class_mod(AST_class_mod* in)
{
	visit_marker("is_abstract", in->is_abstract);
	visit_marker("is_final", in->is_final);
}

void Visit_everything::children_signature(AST_signature* in)
{
	in->method_mod->visit(this);
	visit_marker("is_ref", in->is_ref);
	in->method_name->visit(this);
	in->formal_parameters->visit(this);
}

void Visit_everything::children_method(AST_method* in)
{
	in->signature->visit(this);
	if(in->statements != NULL)
		in->statements->visit(this);
	else
		visit_null("AST_statement_list");
}

void Visit_everything::children_method_mod(AST_method_mod* in)
{
	visit_marker("is_public", in->is_public);
	visit_marker("is_protected", in->is_protected);
	visit_marker("is_private", in->is_private);
	visit_marker("is_static", in->is_static);
	visit_marker("is_abstract", in->is_abstract);
	visit_marker("is_final", in->is_final);
}

void Visit_everything::children_formal_parameter(AST_formal_parameter* in)
{
	in->type->visit(this);
	visit_marker("is_ref", in->is_ref);
	in->variable_name->visit(this);
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");		
}

void Visit_everything::children_type(AST_type* in)
{
	visit_marker("is_array", in->is_array);
	if(in->class_name != NULL)
		in->class_name->visit(this);
	else
		visit_null("Token_class_name");
}

void Visit_everything::children_attribute(AST_attribute* in)
{
	in->attr_mod->visit(this);
	in->variable_name->visit(this);
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");
}

void Visit_everything::children_attr_mod(AST_attr_mod* in)
{
	visit_marker("is_public", in->is_public);
	visit_marker("is_protected", in->is_protected);
	visit_marker("is_private", in->is_private);
	visit_marker("is_static", in->is_static);
	visit_marker("is_const", in->is_const);
}

void Visit_everything::children_for(AST_for* in)
{
	if(in->init != NULL)
		in->init->visit(this);
	else
		visit_null("AST_expr");

	if(in->cond != NULL)
		in->cond->visit(this);
	else
		visit_null("AST_expr");

	if(in->incr != NULL)
		in->incr->visit(this);
	else
		visit_null("AST_expr");

	in->statements->visit(this);
}

void Visit_everything::children_foreach(AST_foreach* in)
{
	in->expr->visit(this);
	if(in->key != NULL)
		in->key->visit(this);
	else
		visit_null("AST_variable");
	visit_marker("is_ref", in->is_ref);
	in->val->visit(this);
	in->statements->visit(this);
}

void Visit_everything::children_switch_case(AST_switch_case* in)
{
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");
	in->statements->visit(this);
}

void Visit_everything::children_break(AST_break* in)
{
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");
}

void Visit_everything::children_continue(AST_continue* in)
{
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");
}

void Visit_everything::children_return(AST_return* in)
{
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");
}

void Visit_everything::children_static_declaration(AST_static_declaration* in)
{
	in->variable_name->visit(this);
	if(in->expr != NULL)
		in->expr->visit(this);
	else
		visit_null("AST_expr");
}

void Visit_everything::children_assignment(AST_assignment* in)
{
	in->variable->visit(this);
	visit_marker("is_ref", in->is_ref);
	in->expr->visit(this);
}

void Visit_everything::children_variable(AST_variable* in)
{
	if(in->target != NULL)
		in->target->visit(this);
	else
		visit_null("AST_target");
	in->variable_name->visit(this);
	in->array_indices->visit(this);
	if(in->string_index != NULL)
		in->string_index->visit(this);
	else
		visit_null("AST_expr");
}

void Visit_everything::children_array_elem(AST_array_elem* in)
{
	if(in->key != NULL)
		in->key->visit(this);
	else
		visit_null("AST_expr");
	visit_marker("is_ref", in->is_ref);
	in->val->visit(this);
}

void Visit_everything::children_actual_parameter(AST_actual_parameter* in)
{
	visit_marker("is_ref", in->is_ref);
	in->expr->visit(this);
}

void Visit_everything::children_list_element_list(AST_list_element_list* in)
{
	List<AST_list_element*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		if(*i) 
			(*i)->visit(this);
		else
			visit_null("AST_list_element");
}

void Visit_everything::children_expr_list(AST_expr_list* in)
{
	List<AST_expr*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		if(*i) 
			(*i)->visit(this);
		else
			visit_null("AST_expr");
}
