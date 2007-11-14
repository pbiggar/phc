/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate nodes so they can be correctly shredded.
 */

#include "Annotate.h"

using namespace AST;

Annotate::Annotate() 
: generate_array_temps(true) 
{
}

void Annotate::pre_node(AST_node* in)
{
	in->attrs->erase("phc.unparser.is_global_stmt");
	in->attrs->erase("phc.unparser.starts_line");
	in->attrs->erase("phc.unparser.needs_curlies");
	in->attrs->erase("phc.unparser.needs_user_curlies");
	in->attrs->erase("phc.unparser.needs_brackets");
	in->attrs->erase("phc.unparser.needs_user_brackets");
}

void Annotate::pre_assignment(AST_assignment* in)
{
	// Assignments of the form $$e =& $d dont work if $$e is split
	// into a temporary first
	if (in->is_ref && in->variable->variable_name->classid() == AST_reflection::ID)
		in->variable->attrs->set_true("phc.lower_expr.no_temp");

	// We need references if we shred $x[0][1][etc] = ...;
	in->variable->attrs->set_true("phc.shredder.need_addr");

	// Variables on the RHS need references if $x =& $y is being used
	Wildcard<AST_variable>* rhs = new Wildcard<AST_variable> ();
	if (in->is_ref && in->match (new AST_assignment (new Wildcard<AST_variable>(), false /*ignore*/, rhs)))
		rhs->value->attrs->set_true ("phc.shredder.need_addr");

	// Is is not necessary to generate a temporary for the
	// top-level expression of an assignment
	if (in->expr->classid () != AST_array::ID)
		in->expr->attrs->set_true("phc.lower_expr.no_temp");
}

// op_assignments are never by reference
void Annotate::pre_op_assignment(AST_op_assignment* in)
{
	// We need references if we shred $x[0][1][etc] = ...;
	in->variable->attrs->set_true("phc.shredder.need_addr");

	// We do need a temporary for the expression of the op_assignment,
	// because it will be the right operand to a binary operator
}

void Annotate::pre_post_op (AST_post_op* in)
{
	in->variable->attrs->set_true("phc.shredder.need_addr");
}

void Annotate::pre_pre_op (AST_pre_op* in)
{
	in->variable->attrs->set_true("phc.shredder.need_addr");
}

void Annotate::pre_attribute(AST_attribute* in)
{
	generate_array_temps = false;
}

void Annotate::post_attribute(AST_attribute* in)
{
	generate_array_temps = true;
}

void Annotate::pre_array_elem (AST_array_elem* in)
{
	if (generate_array_temps == false)
	{
		if(in->key)
			in->key->attrs->set_true("phc.lower_expr.no_temp");
		if(in->val)
			in->val->attrs->set_true("phc.lower_expr.no_temp");
	}
}

void Annotate::pre_static_declaration(AST_static_declaration* in)
{
	generate_array_temps = false;
}

void Annotate::post_static_declaration(AST_static_declaration* in)
{
	generate_array_temps = true;
}

void Annotate::pre_directive (AST_directive* in)
{
	// Do not generate a temp to hold the value of a directive
	// variable
	in->expr->attrs->set_true("phc.lower_expr.no_temp");
}

void Annotate::pre_formal_parameter (AST_formal_parameter* in)
{
	generate_array_temps = false;
}

void Annotate::post_formal_parameter (AST_formal_parameter* in)
{
	generate_array_temps = true;
}

void Annotate::pre_name_with_default (AST_name_with_default* in)
{
	// Never generate a temp for a default value
	if(in->expr)
		in->expr->attrs->set_true("phc.lower_expr.no_temp");
}

// TODO nested functions?
void Annotate::pre_method (AST_method* in)
{
	return_by_ref = in->signature->is_ref;
}

void Annotate::post_method (AST_method* in)
{
	return_by_ref = false;
}

void Annotate::post_return (AST_return* in)
{
	if (return_by_ref 
			&& in->expr->classid () == AST_variable::ID)
		in->expr->attrs->set_true ("phc.shredder.need_addr");
}

void Annotate::post_method_invocation (AST_method_invocation* in)
{
	/* To be able to support includes with return statements, without
	 * dataflow, we dont shred their string arguments */
	Token_method_name* name = dynamic_cast<Token_method_name*>(in->method_name);
	if (name && (
				*name->value == "include"
				or *name->value == "require" 
				or *name->value == "include_once" 
				or *name->value == "require_once"))
	{
		List<AST_actual_parameter*>::const_iterator i;
		for (i = in->actual_parameters->begin (); i != in->actual_parameters->end(); i++)
		{
			if (dynamic_cast<Token_string*> ((*i)->expr))
				(*i)->expr->attrs->set_true("phc.lower_expr.no_temp");
		}

	}

	/* It isn't correct to shred variables which may be references at
	 * run-time, but where we cannot tell if they are at compile-time. The
	 * only occurrence of this in PHP is actual parameters. */
	List<AST_actual_parameter*>::const_iterator i;
	for (i = in->actual_parameters->begin (); i != in->actual_parameters->end(); i++)
	{
		if (dynamic_cast<AST_variable*> ((*i)->expr))
			(*i)->expr->attrs->set_true("phc.shredder.dont_shred");
	}

}


/* Statements can occur nested within expressions, in which case we'd like
 * to simplify them. We mark assignments which occur as an eval_expr, then mark
 * all other assignments as being nested_stmts.
 */
void Annotate::pre_eval_expr (AST_eval_expr* in)
{
	if (in->expr->classid() == AST_assignment::ID ||
			in->expr->classid() == AST_op_assignment::ID ||
			in->expr->classid() == AST_list_assignment::ID)
	{
		in->expr->attrs->set_true("phc.shredder.non_nested_assignment");
	}

	if (in->expr->classid() == AST_method_invocation::ID)
	{
		// Do not generate temps for top-level method invocations
		in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}
}
