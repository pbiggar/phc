/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check for invalid PHP, which otherwise fits within the constraints of
 * our language. This should be run after the parser so we dont operate
 * on invalid code, and any time we worry we may generate invalid code in
 * the HIR.
 */
#include "Invalid_check.h"
#include "process_ir/General.h"

using namespace AST;

void check (IR::PHP_script* in, bool use_ice)
{
	in->assert_valid();

	if (in->is_AST())
	{
		in->visit(new Invalid_check (use_ice));
	}
}

bool is_ref_literal (Expr* in)
{
	return (	dynamic_cast <Literal*> (in) 
			|| dynamic_cast <Array*> (in)
			|| dynamic_cast <Constant*> (in));
}

Invalid_check::Invalid_check (bool use_ice) 
: Pass ()
, use_ice (use_ice)
, class_def (NULL)
{
	this->name = new String ("check");
	this->description = new String ("Check for invalid PHP statements");
}



void Invalid_check::run (IR::PHP_script* in, Pass_manager* pm)
{
	in->visit(this);
	// Indicate that after this pass, ICEs should be used.
	pm->check = true;
}

class Contains_only_deep_literals : public Visitor, virtual public GC_obj
{
public:

	bool non_literal_found;
	Contains_only_deep_literals () : non_literal_found (false) {}
	// we could override everything with an error, but we just need
	// expressions
	void pre_expr (Expr *in)
	{
		if (!is_ref_literal (in))
			non_literal_found = true;
	}
};

/* Returns TRUE if any non-literals were found */
bool contains_only_deep_literals (Node *in)
{
	Contains_only_deep_literals cdl;
	in->visit (&cdl);
	return not cdl.non_literal_found;
}

void Invalid_check::error (const char* message, Node* node)
{
	if (use_ice)
		phc_internal_error (message, node);
	else
		phc_error (message, node);
}

/* Returns true if any push operator found */
bool check_for_push_operator (Variable* in)
{
	if (in->array_indices)
	{
		foreach (Expr* expr, *in->array_indices)
		{
			if (expr == NULL)
				return true;
		}
	}
	return false;
}

void Invalid_check::pre_statement (Statement* in)
{
	// $x[]; or $x[][0]
	// These are represented as lists with NULL entries
	Wildcard<Variable> *wild = new Wildcard<Variable> ();

	if (in->match (new Eval_expr (wild)))
	{
	  if (check_for_push_operator (wild->value))
		 error ("Cannot use [] for reading", wild->value);
	}
}

void Invalid_check::pre_assignment (Assignment* in)
{
	// $x =& array (); or $x =& 5;
	// These are syntax errors, but we're able to add them later
	// (especially in foreach lowering)
	
	if (in->expr == NULL)
		return;

	if (in->is_ref)
		if (is_ref_literal (in->expr))
			error ("Cannot assign a reference to a literal", in->expr);
}

void Invalid_check::pre_foreach (Foreach* in)
{
	// foreach (21 as $x) {}
	// PHP only gives this as a warning, but its using run-time
	// values, and we know this is a semantic error.
	
	if (dynamic_cast<Literal*> (in->expr))
	{
		error ("Invalid (literal) expression supplied for foreach()",
			in->expr);
	}
}

void Invalid_check::pre_interface_def (Interface_def* in)
{
	// interface X { $var x; }
	// Interfaces arent allowed have non-const attributes
	foreach (Member* m, *in->members)
	{
		Wildcard<Attr_mod> *attr_mod = new Wildcard<Attr_mod>;

		if (m->match (new Attribute (attr_mod, NULL)))
			if (!attr_mod->value->is_const)
				error ("Interfaces may not include member variables", 
					attr_mod->value);
	}
}

void
Invalid_check::pre_class_def (Class_def* in)
{
  if (class_def)
    error ("Class declarations may not be nested", in);

  this->class_def = in;
}

void
Invalid_check::post_class_def (Class_def* in)
{
  this->class_def = NULL;
}


void Invalid_check::pre_directive (Directive *in)
{
	// declare (ticks = $x)
	// Declaration directives must have literal arguments. There's no
	// reason that non-literals wouldnt be ok, but thats php for you

	
	// ticks is case insensitive
	if (in->directive_name->value->ci_compare ("ticks"))
	{
		// This error message is taken from php
		if (!(dynamic_cast <Literal*>(in->expr)))
			error ("Cannot convert to ordinal value", in->expr);
	}
	else
	{
		// TODO should be a warning perhaps?
		error ("PHP only supports the 'ticks' directive", in->directive_name);
	}
}

void Invalid_check::pre_name_with_default (Name_with_default* in)
{
	if (in->expr && not contains_only_deep_literals (in->expr))
		error ("Default value of a formal parameter must be a literal value or an array", in->expr);
}

void Invalid_check::pre_attribute (Attribute* in)
{
	if (in->attr_mod->is_const)
	{
		foreach (Name_with_default* nwd, *in->vars)
		{
			if (nwd->expr->classid () == Array::ID)
				error ("Arrays are not allowed in class constants", nwd);
		}
	}
}

void Invalid_check::pre_formal_parameter (Formal_parameter* in)
{
	// function x ($x = f()) {} // syntax error
	if (in->var->expr == NULL)
		return;

	// if theres no type hint, return
	if (in->type->class_name == NULL)
		return;

	// despite the warnings, it appears that constants are OK
	if (in->var->expr->classid () == Constant::ID)
		return;

	// function f (array x = 7) {} // only allowed NULL or array
	if (*in->type->class_name->value == "array")
	{
		if (in->var->expr->classid () == NIL::ID)
			return;

		if (in->var->expr->classid () != Array::ID
				or (not contains_only_deep_literals (in->var->expr)))
			error ("Default value for parameters with array type hint can only be an array or NULL", in->var->expr);

	}
	else
	{
		// function f (int x = 7) {} // only allowed NULL
		if (in->var->expr->classid () != NIL::ID)
			error ("Default value for parameters with a class type hint can only be NULL", in->var->expr);
	}
}

void Invalid_check::pre_method_invocation (Method_invocation* in)
{
	// the 'use' builtin isnt actually builtin yet
	if (in->match (new Method_invocation (
					NULL,
					new METHOD_NAME(new String ("use")),
					NULL)))
	{
		error ("'use' builtin not yet a part of PHP. Please use include_once() or require_once()", in);
	}

	// check the parameters are readable variables (not [])
	foreach (Actual_parameter* ap, *in->actual_parameters)
	{
		Wildcard<Variable>* var = new Wildcard<Variable>;
		if (ap->match (new Actual_parameter (
						false, // ignored
						var)))
		{
			if (check_for_push_operator (var->value))
				error ("Cannot use [] for reading", var->value);
		}
	}
}

void Invalid_check::pre_array_elem (Array_elem* in)
{
	if (in->key == NULL)
		return;

	// basically, new, array and clone are errors here
	if (in->key->classid () == New::ID
		or in->key->classid () == Array::ID)
	{
		error ("Illegal offset type", in->key);
	}
}
