/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate nodes so they can be correctly shredded.
 */

#include "AST_annotate.h"
#include "process_ir/General.h"

using namespace AST;

Annotate::Annotate() 
: generate_array_temps(true) 
{
}

void mark_var_as_lhs (AST::Variable* in)
{
	in->attrs->set_true("phc.ast_shredder.use_ref");

	if (isa<Variable> (in->target))
		mark_var_as_lhs (dyc<Variable> (in->target));
}

void Annotate::pre_assignment(Assignment* in)
{
	
	// Assignments of the form $$e =& $d dont work if $$e is split
	// into a temporary first, except if they have array_indices.
	// TODO: what about if they have targets?
	if (in->is_ref && in->variable->variable_name->classid() == Reflection::ID
		&& (!isa<Variable>(in->expr) || dyc<Variable>(in->expr)->array_indices->size () == 0))
		in->variable->attrs->set_true("phc.ast_lower_expr.no_temp");
	
	// Don't shred $$x = $y (do shred $$x[$i] = $y; dont shred $x->$$f = $y))
	if (in->variable->target == NULL
		&& in->variable->variable_name->classid() == Reflection::ID
		&& in->variable->array_indices->size () == 0)
		in->variable->attrs->set_true("phc.ast_lower_expr.no_temp");

	// We need references if we shred $x[0][1][etc] = ...;
	// TODO The final part should be $T[etc] = ...;, not $T2 =& $T[etc]; $T2 = ...;
	in->variable->attrs->set_true("phc.ast_shredder.need_addr");
	mark_var_as_lhs (in->variable);

	// Variables on the RHS need references if $x =& $y is being used
	Wildcard<Variable>* rhs = new Wildcard<Variable> ();
	if (in->is_ref && in->match (new Assignment (new Wildcard<Variable>(), false /*ignore*/, rhs)))
	{
		mark_var_as_lhs (rhs->value);
	}

	// Assignments of the form $x = 5 do not need a temporary, but all other LHS
	// forms ($$x = 5; $x[$y] = 5; $t->x; etc) do.
	if (in->expr->classid () != Array::ID
		&& in->variable->target == NULL
		&& in->match (new Assignment (
			new Variable (
				new Wildcard<Target>, 
				new Wildcard <VARIABLE_NAME>, 
				new Expr_list),
			false /*ignore*/, 
			new Wildcard<Expr>)))
		in->expr->attrs->set_true("phc.ast_lower_expr.no_temp");

	// Except for $x = {$y}[$z], which must be split
	if (in->expr->match (new Variable (
			new Wildcard<Target>,
			new Wildcard<Reflection>,
			NULL)))
		in->expr->attrs->erase ("phc.ast_lower_expr.no_temp");
}

// op_assignments are never by reference
void Annotate::pre_op_assignment(Op_assignment* in)
{
	// We need references if we shred $x[0][1][etc] = ...;
	mark_var_as_lhs (in->variable);

	// We do need a temporary for the expression of the op_assignment,
	// because it will be the right operand to a binary operator
}

void Annotate::pre_post_op (Post_op* in)
{
	in->variable->attrs->set_true("phc.ast_shredder.use_ref");
}

void Annotate::pre_pre_op (Pre_op* in)
{
	in->variable->attrs->set_true("phc.ast_shredder.use_ref");
}

void Annotate::pre_attribute(Attribute* in)
{
	generate_array_temps = false;
}

void Annotate::post_attribute(Attribute* in)
{
	generate_array_temps = true;
}

void Annotate::pre_array_elem (Array_elem* in)
{
	if (generate_array_temps == false)
	{
		if(in->key)
			in->key->attrs->set_true("phc.ast_lower_expr.no_temp");
		if(in->val)
			in->val->attrs->set_true("phc.ast_lower_expr.no_temp");
	}
}

void Annotate::pre_static_declaration(Static_declaration* in)
{
	generate_array_temps = false;
}

void Annotate::post_static_declaration(Static_declaration* in)
{
	generate_array_temps = true;
}

void Annotate::pre_directive (Directive* in)
{
	// Do not generate a temp to hold the value of a directive
	// variable
	in->expr->attrs->set_true("phc.ast_lower_expr.no_temp");
}

void Annotate::pre_formal_parameter (Formal_parameter* in)
{
	generate_array_temps = false;
}

void Annotate::post_formal_parameter (Formal_parameter* in)
{
	generate_array_temps = true;
}

void Annotate::pre_name_with_default (Name_with_default* in)
{
	// Never generate a temp for a default value
	if(in->expr)
		in->expr->attrs->set_true("phc.ast_lower_expr.no_temp");
}

// TODO nested functions?
void Annotate::pre_method (Method* in)
{
	return_by_ref = in->signature->is_ref;
}

void Annotate::post_method (Method* in)
{
	return_by_ref = false;
}

void Annotate::post_return (Return* in)
{
	if (return_by_ref 
			&& in->expr->classid () == Variable::ID)
	{
		in->expr->attrs->set_true ("phc.ast_shredder.use_ref");
	}
}

void Annotate::post_method_invocation (Method_invocation* in)
{
	// TODO: Disabled as cannot fold without it
	/* To be able to support includes with return statements, without
	 * dataflow, we dont shred their string arguments */
/*	METHOD_NAME* name = dynamic_cast<METHOD_NAME*>(in->method_name);
	if (name && (
				*name->value == "include"
				or *name->value == "require" 
				or *name->value == "include_once" 
				or *name->value == "require_once"))
	{
		Actual_parameter_list::const_iterator i;
		for (i = in->actual_parameters->begin (); i != in->actual_parameters->end(); i++)
		{
			if (dynamic_cast<STRING*> ((*i)->expr))
				(*i)->expr->attrs->set_true("phc.ast_lower_expr.no_temp");
		}

	}
*/
	/* It isn't correct to shred variables which may be references at
	 * run-time, but where we cannot tell if they are at compile-time. The
	 * only occurrence of this in PHP is actual parameters. */
	foreach (Actual_parameter* ap, *in->actual_parameters)
	{
		// We can shred variable that we know are passed by reference
		if (ap->is_ref)
		{
			ap->expr->attrs->set_true ("phc.ast_shredder.use_ref");
			ap->expr->attrs->set_true ("phc.ast_shredder.need_addr");
		}
		else if (dynamic_cast<Variable*> (ap->expr))
			ap->expr->attrs->set_true("phc.ast_shredder.dont_shred");
	}

}


/* Statements can occur nested within expressions, in which case we'd like
 * to simplify them. We mark assignments which occur as an eval_expr, then mark
 * all other assignments as being nested_stmts.
 */
void Annotate::pre_eval_expr (Eval_expr* in)
{
	if (in->expr->classid() == Assignment::ID ||
			in->expr->classid() == Op_assignment::ID ||
			in->expr->classid() == List_assignment::ID)
	{
		in->expr->attrs->set_true("phc.ast_shredder.non_nested_assignment");
	}

	if (in->expr->classid() == Method_invocation::ID)
	{
		// Do not generate temps for top-level method invocations
		in->expr->attrs->set_true("phc.ast_lower_expr.no_temp");
	}
}

/* A while should have TRUE as its parameter, after early_lower_control_flow. */
void Annotate::pre_while (While* in)
{
	in->expr->attrs->set_true("phc.ast_lower_expr.no_temp");
}

/* To print compile-time error messages for breaks, we must keep this for now.
 * When the errors are done in data-flow, we can remove this. */
void Annotate::pre_break (Break* in)
{
	if (in->expr)
		in->expr->attrs->set_true("phc.ast_lower_expr.no_temp");
}
