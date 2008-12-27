/*
 * phc -- the open source php compiler
 * see doc/license/readme.license for licensing information
 *
 * macro-inlined code generator (pronounced 'mig', like wig)
 */

#include "MICG_gen.h"
#include "MICG_checker.h"
#include "MICG.h"
#include "MIR.h"
#include "parsing/MICG_parser.h"
#include "process_ir/General.h"
#include "lib/String.h"

using namespace MICG;
using namespace std;
using namespace boost;

// TODO: Pattern, Template, Macro, etc, are all used for the same thing. Just use 'Macro'.
void
MICG_gen::add_macro (MICG::Macro* in)
{
	string name = *in->signature->macro_name->value;

	// Check the signature matches the others'.
	foreach (Macro* t, macros[name])
	{
		if (t->signature->formal_parameters->size () != in->signature->formal_parameters->size ())
			phc_internal_error ("Macro signature %s does not match other signatures", name.c_str ());
	}

	in->visit (new MICG_checker);

	// Deliberately defer checking the signatures at 'run-time'. We don't want
	// to check the types are the same, as we don't want to encode an
	// inheritence hierarchy. We don't want to check the names are the same, as
	// they provide context.

	macros[name].push_back (in);
}

void
MICG_gen::add_macro_def (string str)
{
	MICG_parser parser;
	foreach (Macro* m, *parser.parse (str))
		add_macro (m);
}


string
MICG_gen::instantiate (string macro_name, Object* obj1, Object* obj2) 
{
	// Get the parameters, converting them to appropriate types.
	Object_list* params = new Object_list ();
	params->push_back (obj1);
	params->push_back (obj2);

	// Find the appropriate macro.
	Macro* m = NULL;
	foreach (m, macros[macro_name])
	{
		if (suitable (m, params))
			break;
	}
	if (m == NULL)
	{
		if (macros[macro_name].size () == 0)
			phc_internal_error ("There is no macro named %s", macro_name.c_str ());

//		string formals = get_formals_as_string (
//			macros[macro_name].front()->signature->formal_parameters);

		phc_internal_error ("No macro named %s matches the params: ", macro_name.c_str ());
	}

	// Coerce the data appropriately.
	Symtable* symtable = get_symtable (macro_name, m->signature->formal_parameters, params);
	return instantiate_body (m->body, symtable);
}

Object*
Symtable::get_attr (string param_name, string attr_name)
{
	MIR::Node* node = dyc<MIR::Node> (get (param_name));

	// We are interested in attributes of either prefix, but are not interested
	// in writing out the full prefices.
	string ann1 = "phc.codegen.";
	string ann2 = "phc.optimize.";

	ann1.append (attr_name);
	ann2.append (attr_name);

	if (node->attrs->has (ann1))
		return node->attrs->get (ann1);
		
	if (node->attrs->has (ann2))
		return node->attrs->get (ann2);

	phc_internal_error ("Cannot find attribute %s in param %s",
		attr_name.c_str (), param_name.c_str ());

	assert (0);
}

bool
MICG_gen::suitable (Macro* macro, Object_list* params)
{
	Symtable* symtable = get_symtable (*macro->signature->macro_name->value, 
		macro->signature->formal_parameters, params);

	// Check if the rules match.
	foreach (Rule* rule, *macro->rules)
	{
		if (Lookup* l = dynamic_cast <Lookup*> (rule))
		{
			Object* obj = symtable->get_attr (*l->param_name->value, *l->attr_name->value);
			if (isa<String> (obj))
				phc_internal_error ("Expecting Boolean in lookup, got string");

			return dyc<Boolean> (obj)->value();
		}
		else if (Equals* e = dynamic_cast<Equals*> (rule))
		{
//			String* lhs = e->left

			assert (0);
		}
	}

	// The types can be check in instantiate_body
	assert (0);
}

MICG::Symtable*
MICG_gen::get_symtable (string macro_name, Formal_parameter_list* fps, Object_list* params)
{
	// Check the size first
	int num_params = params->size ();
	int expected_num_params = fps->size ();
	if (expected_num_params != num_params)
		phc_internal_error ("Incorrect number of parameters in %s (expected %d, got %d)",
			macro_name.c_str (), expected_num_params, num_params);


	// Dont destroy the list
	params = params->clone ();

	Symtable* result = new Symtable;
	foreach (Formal_parameter* fp, *fps)
	{
		check_type (fp->type_name, params->front ());
		(*result)[*fp->param_name->value] = params->front();
		params->pop_front();
	}
	return result;
}


void
MICG_gen::check_type (TYPE_NAME* type_name, Object* obj)
{
	string tn = *type_name->value;
	if (tn == "string"
		&& (isa<String> (obj) || isa<MIR::Identifier> (obj)))
		return;

	if (tn == "token" && isa<MIR::Identifier> (obj))
		return;

	if (tn == "node" && isa<MIR::Node> (obj))
		return;

	phc_internal_error ("Object of type %s does not match expected type %s",
		demangle (obj, true), tn.c_str ());
}

string
MICG_gen::instantiate_body (Body* body, Symtable* symtable)
{
	assert (0);
}
