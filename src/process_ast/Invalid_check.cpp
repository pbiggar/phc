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

bool is_literal (AST_expr* in)
{
	return ( dynamic_cast <AST_literal*> (in) 
				|| dynamic_cast <AST_array*> (in)
				|| dynamic_cast <AST_constant*> (in));
}


class Check_deep_literals : public AST_visitor
{
public:

	bool non_literal_found;
	Check_deep_literals () : non_literal_found (false) {}
	// we could override everything with an error, but we just need
	// expressions
	void pre_expr (AST_expr *in)
	{
		if (!is_literal (in))
			non_literal_found = true;
	}
};

/* Returns TRUE if any non-literals were found */
bool check_deep_literals (AST_node *in)
{
	Check_deep_literals cdl;
	in->visit (&cdl);
	return cdl.non_literal_found;
}

void Invalid_check::error (const char* message, AST_node* node)
{
	if (use_ice)
		phc_internal_error (message, node);
	else
		phc_error (message, node);
}

void Invalid_check::pre_statement (AST_statement* in)
{
	// $x[]; or $x[][0]
	// These are represented as lists with NULL entries
	Wildcard<AST_variable> *wild = new Wildcard<AST_variable> ();

	if (in->match (new AST_eval_expr (wild)))
	{
		if (wild->value->array_indices)
		{
			List<AST_expr*>::const_iterator i;
			for (i = wild->value->array_indices->begin (); i != wild->value->array_indices->end (); i++)
			{
				if (*i == NULL)
					error ("Cannot use [] for reading", in);
			}
		}
	}
}

void Invalid_check::pre_assignment (AST_assignment* in)
{
	// $x =& array (); or $x =& 5;
	// These are syntax errors, but we're able to add them later
	// (especially in foreach lowering)
	
	if (in->expr == NULL)
		return;

	if (in->is_ref)
		if (is_literal (in->expr))
			error ("Cannot assign a reference to a literal", in->expr);
}

void Invalid_check::pre_foreach (AST_foreach* in)
{
	// foreach (21 as $x) {}
	// PHP only gives this as a warning, but its using run-time
	// values, and we know this is a semantic error.
	
	if (dynamic_cast<AST_literal*> (in->expr))
	{
		error ("Invalid (literal) expression supplied for foreach()",
			in->expr);
	}
}

void Invalid_check::pre_interface_def (AST_interface_def* in)
{
	// interface X { $var x; }
	// Interfaces arent allowed have non-const attributes
	List<AST_member*>::const_iterator i;
	for (i = in->members->begin (); i != in->members->end (); i++)
	{
		Wildcard<AST_attr_mod> *attr_mod = new Wildcard<AST_attr_mod>;

		if ((*i)->match (
			new AST_attribute (
				attr_mod, 
				new Wildcard<Token_variable_name>, 
				new Wildcard<AST_expr>))
			)
			if (!attr_mod->value->is_const)
				error ("Interfaces may not include member variables", 
					attr_mod->value);
	}
}


void Invalid_check::pre_directive (AST_directive *in)
{
	// declare (ticks = $x)
	// Declaration directives must have literal arguments. There's no
	// reason that non-literals wouldnt be ok, but thats php for you

	
	// ticks is case insensitive
	if (in->directive_name->value->ci_compare ("ticks"))
	{
		// This error message is taken from php
		if (!(dynamic_cast <AST_literal*>(in->expr)))
			error ("Cannot convert to ordinal value", in->expr);
	}
	else
	{
		// TODO should be a warning perhaps?
		error ("PHP only supports the 'ticks' directive", in->directive_name);
	}
}

void Invalid_check::pre_formal_parameter (AST_formal_parameter* in)
{
	//   function x ($x = f()) {} // also a syntax error

	if (in->expr == NULL)
		return;

	if (check_deep_literals (in->expr))
		error ("Default value of a formal parameter must be a literal value or an array", in->expr);
}

void Invalid_check::pre_method_invocation (AST_method_invocation* in)
{
	// the 'use' builtin isnt actually builtin yet
	if (in->match (new AST_method_invocation (
							NULL,
							new Token_method_name(new String ("use")),
							NULL)))
	{
		error ("'use' builtin not yet a part of PHP. Please use include_once() or require_once()", in);
	}
}

void Invalid_check::pre_attribute (AST_attribute* in)
{
	// class X {
	//   var $x = f(); // also a syntax error
	// }
	if (in->expr == NULL)
		return;

	if (check_deep_literals (in->expr))
		error ("Default value of an attribute must be a literal value or an array", in->expr);
}

void Invalid_check::pre_static_declaration (AST_static_declaration* in)
{
	// function X () {
	//   static $x = f(); // also a syntax error
	// }
	if (in->expr == NULL)
		return;

	if (check_deep_literals (in->expr))
		error ("Default value of a static declaration must be a literal value or an array", in->expr);
}
