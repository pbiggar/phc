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

// Iterate through the macros til we find one whose rules match the PARAMS.
// Fail otherwise.
Macro*
MICG_gen::get_macro (string name, Object_list* params)
{
	foreach (Macro* m, macros[name])
	{
		if (suitable (m, params))
			return m;
	}

	if (macros[name].size () == 0)
		phc_internal_error ("There is no macro named %s", name.c_str ());

	//		string formals = get_formals_as_string (
	//			macros[macro_name].front()->signature->formal_parameters);

	phc_internal_error ("No macro named %s matches the params: ", name.c_str ());
	assert (0);
}

void
MICG_gen::add_macro_def (string str, string filename)
{
	MICG_parser parser;
	foreach (Macro* m, *parser.parse (str, filename))
		add_macro (m);
}

string
MICG_gen::instantiate (string macro_name, Object_list* params) 
{
	Macro* m = get_macro (macro_name, params);

	// Coerce the data appropriately.
	Symtable* symtable = get_symtable (macro_name, m->signature->formal_parameters, params);
	return instantiate_body (m->body, symtable);
}

string
MICG_gen::instantiate (string macro_name, Object* obj1, Object* obj2) 
{
	// Get the parameters, converting them to appropriate types.
	Object_list* params = new Object_list ();
	params->push_back (obj1);
	params->push_back (obj2);

	return instantiate (macro_name, params);
}

bool
MICG_gen::suitable (Macro* macro, Object_list* params)
{
	Symtable* symtable = get_symtable (
			*macro->signature->macro_name->value, 
			macro->signature->formal_parameters,
			params);

	// Check if the rules match.
	foreach (Rule* rule, *macro->rules)
	{
		if (Lookup* l = dynamic_cast <Lookup*> (rule))
		{
			String* str = dyc<String> (symtable->get_lookup (l, true));
			if (*str == MICG_FALSE)
				return false;
		}
		else if (Equals* e = dynamic_cast<Equals*> (rule))
		{
			String* left = dyc<String> (symtable->get_expr (e->left, true));
			String* right = dyc<String> (symtable->get_expr (e->right, true));

			if (*left != *right)
				return false;
		}
		else
			phc_unreachable ();
	}

	return true;
}

void
MICG_gen::register_callback (string name, callback_t callback)
{
	if (callbacks.has (name))
		phc_internal_error ("Attempt to redefine existing callback %s",
				name.c_str ());

	callbacks[name] = callback;
}

string
MICG_gen::callback (string name, String* param)
{
	if (!callbacks.has (name))
		phc_internal_error ("No callback '%s' registered", name.c_str ());

	return callbacks[name](*param);
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
		type_name, demangle (obj, true), tn.c_str ());
}

string
MICG_gen::instantiate_body (Body* body, Symtable* symtable)
{
	stringstream ss;
	foreach (Body_part* body_part, *body->body_parts)
	{
		if (C_CODE* c_code = dynamic_cast<C_CODE*> (body_part))
		{
			ss << *c_code->value;
		}
		else if (Interpolation* interp = dynamic_cast<Interpolation*> (body_part))
		{
			Object* obj =
				symtable->get_expr (reinterpret_cast<Expr*> (interp), false);

			if (!isa<String> (obj) && !isa<MIR::Identifier> (obj))
				phc_internal_error ("Cannot interpolate %s", interp,
				demangle (obj));

			ss << *symtable->convert_to_string (obj);
		}
		else if (Macro_call* mc = dynamic_cast<Macro_call*> (body_part))
		{
			Object_list* params = new Object_list;
			foreach (Actual_parameter* ap, *mc->actual_parameters)
			{
				params->push_back (
					symtable->get_expr (reinterpret_cast<Expr*> (ap)));
			}
			ss << instantiate (*mc->macro_name->value, params);
		}
		else if (Callback* cb = dynamic_cast<Callback*> (body_part))
		{
			Object_list* params = new Object_list;
			foreach (Actual_parameter* ap, *cb->actual_parameters)
			{
				params->push_back (
					symtable->get_expr (reinterpret_cast<Expr*> (ap)));
			}
			if (params->size() != 1)
				phc_internal_error (
					"Exactly 1 parameter required for a callback", cb);

			ss << callback (*cb->macro_name->value,
					symtable->convert_to_string (params->front ()));
		}
		else
			phc_unreachable ();
	}
	return ss.str ();
}


/*
 * Symtable
 */

Object*
Symtable::get_lookup (Lookup* in, bool coerce)
{
	string param_name = *in->param_name->value;
	string attr_name = *in->attr_name->value;

	assert (this->has (param_name));
	MIR::Node* node = dyc<MIR::Node> (this->get (param_name));

	// We are interested in attributes of either prefix, but are not interested
	// in writing out the full prefices.
	string ann1 = "phc.codegen.";
	string ann2 = "phc.optimize.";

	ann1.append (attr_name);
	ann2.append (attr_name);

	Object* result;
	if (node->attrs->has (ann1))
		result = node->attrs->get (ann1);
	else if (node->attrs->has (ann2))
		result = node->attrs->get (ann2);
	else if (coerce)
		result = new Boolean (false);
	else
		phc_internal_error (
			"Attempt to access invalid attribute '%s' without coercion",
			in, attr_name.c_str ());


	if (coerce || isa<Boolean> (result))
		result = convert_to_string (result);

	return result;
}

Object*
Symtable::get_param (PARAM_NAME* param, bool coerce)
{
	Object* result = this->get (*param->value);

	if (coerce || isa<Boolean> (result))
		result = convert_to_string (result);

	return result;
}

// If coerce is true, coerce the data to a String or Boolean.
Object*
Symtable::get_expr (Expr* in, bool coerce)
{
	// Caution: because a caller uses reinterpret_cast, a dynamic_cast doesnt
	// work. However, a dyc() works just fine.
	if (isa<STRING> (in))
		return dyc<STRING> (in)->value;

	if (isa<Lookup> (in))
		return this->get_lookup (dyc<Lookup> (in), coerce);

	if (isa<PARAM_NAME> (in))
		return this->get_param (dyc<PARAM_NAME> (in), coerce);
	
	phc_unreachable ();
}

String*
Symtable::convert_to_string (Object* in)
{
	if (Boolean* b = dynamic_cast<Boolean*> (in))
	{
		if (b->value ())
			return s(MICG_TRUE);
		else
			return s(MICG_FALSE);
	}

	if (MIR::Identifier* id = dynamic_cast<MIR::Identifier*> (in))
		return id->get_value_as_string ();

	if (String* str = dynamic_cast<String*> (in))
		return str;

	return s(MICG_TRUE);
}
