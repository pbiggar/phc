/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower the parameters of method invocations, adding a run-time check to
 * determine if the parameter is passed by reference.
 */

#include "Lower_method_invocations.h"

using namespace HIR;

/* Convert
 *
 *		$t1->x ($$var1, $t1->$var2[$i]);
 *
 *	into
 *
 *		// fetch param 0
 *		if (param_is_ref ($t1, x, 0))
 *			$T1 =& $$var1;
 *		else
 *			$T1 = $$var1;
 *
 *		// fetch param 1
 *		if (param_is_ref ($t1, x, 1))
 *		{
 *			$T2 =& $t1->$$var2;
 *			$T3 =& $T2[$i];
 *		}
 *		else
 *		{
 *			$T2 = $t1->$$var2;
 *			$T3 = $T2[$i];
 *		}
 *
 *		// Call the function
 *		$t1->x ($T1, $T3);
 */
Expr*
Lower_method_invocations::pre_method_invocation (Method_invocation* in)
{
	// Leave unset and isset in place - it still needs access to the target and
	// indices.
	METHOD_NAME* mn = dynamic_cast <METHOD_NAME*> (in->method_name);
	if (in->target == NULL && mn && *mn->value == "unset")
		return in;
	
	bool is_isset = in->target == NULL && mn && *mn->value == "isset";

	int index = 0;
	foreach (Actual_parameter* actual_param, *in->actual_parameters)
	{
		if (isa<Literal> (actual_param))
			continue;

		Variable_actual_parameter* ap = dyc<Variable_actual_parameter> (actual_param);

		// Ignore simple variables
		if (ap->target == NULL
			&& isa<VARIABLE_NAME> (ap->variable_name)
			&& ap->array_indices->size () == 0)
			continue;

		// TODO: check the is_ref flag. Make sure we don't lose this information.
		// and transform differently is this case.
		FOREIGN* param_is_ref = new FOREIGN (
			new MIR::Param_is_ref (
				in->target ? folder.fold_target (in->target) : NULL,
				folder.fold_method_name (in->method_name),
				new MIR::PARAM_INDEX (index)));

		Statement_list* iftrue = new Statement_list;
		Statement_list* iffalse = new Statement_list;

		// Shred the parameter. This is a specialized version of
		// AST_shredder::post_variable.

		VARIABLE_NAME* prev = NULL;

		// Shred variable_variables with no target.
		if (ap->target == NULL 
				&& isa<Variable_variable> (ap->variable_name))
		{
			VARIABLE_NAME* temp = fresh_var_name ("TMIr");

			iftrue->push_back(
					new Assign_var(
						temp->clone (),
						true,
						ap->variable_name));

			prev = temp;
		}

		// Shred the target
		if(ap->target)
		{
			Field_name* field_name;
			if (isa<Variable_variable> (ap->variable_name))
				field_name = new Variable_field (dyc<Variable_variable> (ap->variable_name)->variable_name->clone());
			else
				field_name = new FIELD_NAME (dyc<VARIABLE_NAME> (ap->variable_name)->value);

			field_name->attrs = ap->variable_name->attrs->clone ();

			VARIABLE_NAME* temp = fresh_var_name ("TMIt");
			iftrue->push_back (
				new Assign_var (
							temp->clone (),
							true,
							new Field_access (
								ap->target,
								field_name)));
			prev = temp;
			ap->target = NULL;
		}

		if (prev == NULL)
			prev = dyc<VARIABLE_NAME> (ap->variable_name);

		// Shred the array indices
	  // For isset, leave the last index
    unsigned exclude;
    if (is_isset)
      exclude = 1;
    else
      exclude = 0;

		while (ap->array_indices->size () > exclude)
		{
			VARIABLE_NAME* temp = fresh_var_name ("TMIi");
			iftrue->push_back(
				new Assign_var (
					temp->clone (),
					true,
					new Array_access (
						prev->clone (),
						ap->array_indices->front ())));

			prev = temp;
			ap->array_indices->pop_front();
		}

		assert (ap->target == NULL);
		assert (ap->array_indices->size() <= exclude);
		ap->variable_name = prev;

		// Copy the iftrue to iffalse, except assignments arent by reference.
		foreach (Statement* s, *iftrue)
		{
			Assign_var* assign = (dyc<Assign_var> (s))->clone ();
			assign->is_ref = false;
			iffalse->push_back (assign);
		}

    // For isset, we never pass variables by reference
    if(!is_isset)
		  pieces->push_back (
  			new If (
  				eval (check_builtin (param_is_ref)),
  				iftrue,
  				iffalse));
    else
      pieces->push_back_all (iffalse);  
	}

	return in;
}

/* Builtins don't have symbol table entries to be looked up at run-time.
 * However, we know the answer in all these cases. */
Expr*
Lower_method_invocations::check_builtin (FOREIGN* in)
{
	MIR::Param_is_ref* param_is_ref = dyc<MIR::Param_is_ref> (in->value);

	if (param_is_ref->target == NULL
		&& isa<MIR::METHOD_NAME> (param_is_ref->method_name))
	{
		String* method_name = dyc<MIR::METHOD_NAME> (param_is_ref->method_name)->value;
		if (is_builtin_function (method_name))
			return new BOOL (false);
	}

	return in;
}
