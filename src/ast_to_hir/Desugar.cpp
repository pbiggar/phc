/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#include "Desugar.h"
#include "process_ir/fresh.h"

using namespace AST;


// NOP statements are removed
void Desugar::pre_nop(Nop* in, Statement_list* out)
{
	// Leave "out" empty 
}

// Replace "-x" by "0 - x"
Expr* Desugar::pre_unary_op(Unary_op* in)
{
	if(*in->op->value == "-") return new Bin_op(
			new INT(0),
			in->op,
			in->expr);
	else
		return in;
}

// TODO can we remove this?
// All return statements must get an argument (NULL if none specified)
void Desugar::pre_return(Return* in, Statement_list* out)
{
	if(in->expr == NULL)
	{
		in->expr = new NIL();
		in->expr->attrs->set_true ("phc.codegen.unused");
	}

	out->push_back(in);
}

void Desugar::pre_declare (Declare* in, Statement_list* out)
{
	// Just remove declare statements, they dont make sense in a compiler.
}

/* Case-insensitivity
 *
 * The following are not case-sensitive:
 *		class names
 *		interface names
 *		method names
 *		casts
 *
 *	However, we can only change casts since the others are needed for error
 *	messages.
 *
 * The following are case-sensitive
 *		constant names
 *		variable names
 *
 *	We don't care about directives.
 *
 *	We must only change their names when they are accessed, not when they are
 *	declared.
 */
OP*
Desugar::pre_op (OP* in)
{
	in->value = in->value->to_lower();

	if (*in->value == "and")
		in->value = s("&&");
	else if (*in->value == "or")
		in->value = s("||");
	else if (*in->value == "<>")
		in->value = s("!=");

	return in;
}

void
Desugar::pre_method (Method* in, Method_list* out)
{
	out->push_back (in);
}

METHOD_NAME*
Desugar::pre_method_name (METHOD_NAME* in)
{
	return in;
}


void
Desugar::pre_class_def (Class_def* in, Statement_list* out)
{
	// Store for self::.
	current_class = in->class_name;

	// Store for parent::.
	parent_class = in->extends;

	out->push_back (in);
}

Expr*
Desugar::pre_constant (Constant* in)
{
	return in;
}

CLASS_NAME*
Desugar::pre_class_name (CLASS_NAME* in)
{
	if (*in->value == "self")
	{
		// self:: means the current class name.
		in->value = current_class->value->clone();
	}
	else if (*in->value == "parent")
	{

		if (this->parent_class == NULL)
		{
			// We would ideally like to replace this with a run-time warning, but that's a bit awkward.
			phc_warning ("Attempt to use 'parent::' in a class with no parent class", in);
		}
		else
		{
			// parent:: means the parent class name
			in->value = parent_class->value->clone();
		}
	}

	return in;
}


void
Desugar::pre_interface (Interface_def* in, Statement_list* out)
{
	// TODO: anything special for parent here?
	// Store for self::.
	current_interface = in->interface_name;

	out->push_back (in);
}

INTERFACE_NAME*
Desugar::pre_interface_name (INTERFACE_NAME* in)
{
	if (*in->value == "self")
	{
		in->value = current_class->value->clone();
	}

	return in;
}

CAST*
Desugar::pre_cast (CAST* in)
{
	in->value = in->value->to_lower ();

	// Choosing the names for this is hard. We could use our IR names, but NIL
	// isnt valid (isn't valid means it wont parse). We could use PHPs IS_*
	// names, but long isnt valid.  The manual uses NULL, but 'null' isnt valid,
	// so we'll use
	//
	//		array
	//		bool
	//		int
	//		object
	//		real
	//		string
	//		unset
	//
	//	These are our IR names, except using unset for NIL. That should be simple
	//	enough to remember.


	Map<string, string> cast_names;
	cast_names["array"]		= "array";
	cast_names["binary"]		= "string";
	cast_names["boolean"]	= "bool";
	cast_names["bool"]		= "bool";
	cast_names["double"	]	= "real";
	cast_names["float"]		= "real";
	cast_names["integer"]	= "int";
	cast_names["int"]			= "int";
	cast_names["object"]		= "object";
	cast_names["real"]		= "real";
	cast_names["string"]		= "string";
	cast_names["unset"]		= "unset";

	assert (cast_names.has (*in->value));

	in->value = s (cast_names[*in->value]);

	return in;
}
