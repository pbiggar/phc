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
	foreach (Macro* m, macros[name])
	{
		if (m->signature->formal_parameters->size () != in->signature->formal_parameters->size ())
			phc_internal_error ("Macro signature %s does not match other signatures", m, name.c_str ());
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

	phc_internal_error ("No macro named %s matches the params: ", name.c_str ());
	phc_unreachable ();
}

void
MICG_gen::add_macro_def (string str, string filename)
{
	MICG_parser parser;
	foreach (Macro* m, *parser.parse (str, filename))
		add_macro (m);
}

string
MICG_gen::instantiate (string macro_name, Object_list* params, Node* anchor)
{
	if (anchor == NULL)
	{
		if (macros[macro_name].size () == 0)
			phc_internal_error ("There is no macro named %s, called from C++ code",
				macro_name.c_str ());
	}
	else
	{
		if (macros[macro_name].size () == 0)
			phc_internal_error ("There is no macro named %s",
				anchor, macro_name.c_str ());
	}

	// In order to get the macro that matches these params, we first need to
	// expand the list parameters. But that needs a macro. But to get the right
	// macro, we need the full parameters. Not only that, but we actually want
	// different macros based on their list element. So we make the rule that if
	// there are multiple macros of the same name, they must use the 'list' type
	// consistently. Then we can just take the first macro, and use it to expand
	// the parameters, and still get the correct macro for each parameter list.

	if (macros[macro_name].size () == 0)
		phc_internal_error ("There is no macro named %s", macro_name.c_str ());

	Macro* first_macro = macros[macro_name].front ();

	if (params->size() != first_macro->signature->formal_parameters->size ())
	{
		if (anchor == NULL)
			phc_internal_error (	"Wrong number of parameters in macro instantiated in C++ code: "
										"%s called with %d instead of %d",
										macro_name.c_str(), params->size(),
										first_macro->signature->formal_parameters->size ());
		else
			phc_internal_error (	"Wrong number of parameters in macro call: "
										"%s called with %d instead of %d",
										anchor, 
										macro_name.c_str(), params->size(), 
										first_macro->signature->formal_parameters->size ());
	}


	// Expand lists here.
	stringstream ss;
	foreach (Object_list* actual_params, *this->expand_list_params (first_macro, params))
	{
		Macro* m = get_macro (macro_name, actual_params);
		DEBUG ("Entering " << macro_name << ":" << m->get_line_number () << *to_string_rep (actual_params));
		Symtable* symtable = get_symtable (m, actual_params);
		ss << instantiate_body (m->body, symtable);
		DEBUG ("Exiting " << macro_name << ":" << m->get_line_number () << *to_string_rep (actual_params));
	}
	return ss.str ();
}

bool
MICG_gen::suitable (Macro* macro, Object_list* params)
{
	Symtable* symtable = get_symtable (macro, params);

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
			String* left = dyc<String> (get_expr (e->left, symtable, true));
			String* right = dyc<String> (get_expr (e->right, symtable, true));

			if (*left != *right)
				return false;
		}
		else
			phc_unreachable ();
	}

	return true;
}

void
MICG_gen::register_callback (string name, callback_t callback, int param_count)
{
	if (callbacks.has (name))
		phc_internal_error ("Attempt to redefine existing callback %s",
				name.c_str ());

	callbacks[name] = make_pair (callback, param_count);
}

string
MICG_gen::callback (MACRO_NAME* macro_name, Object_list* params)
{
	string name = *macro_name->value;
	DEBUG ("Calling callback " << name << *to_string_rep (params));

	if (!callbacks.has (name))
		phc_internal_error ("No callback '%s' registered", macro_name, name.c_str ());

	callback_t sig;
	unsigned int param_count;
	tie (sig, param_count) = callbacks[name];

	if (params->size() != param_count)
		phc_internal_error ("Callback '%s' requires %d parameter, called with %d: %s",
			macro_name, name.c_str (), param_count, params->size(), to_string_rep (params)->c_str());

	string result = sig(params);
	DEBUG ("Leaving callback " << name << *to_string_rep (params));
	return result;
}

MICG::Symtable*
MICG_gen::get_symtable (Macro* macro, Object_list* params)
{
	Formal_parameter_list* fps = macro->signature->formal_parameters;
	string name = *macro->signature->macro_name->value;

	// Check the size first
	int num_params = params->size ();
	int expected_num_params = fps->size ();
	if (expected_num_params != num_params)
		phc_internal_error ("Incorrect number of parameters in %s (expected %d, got %d)",
			macro, name.c_str (), expected_num_params, num_params);


	Object_list::const_iterator i = params->begin ();

	Symtable* result = new Symtable;
	foreach (Formal_parameter* fp, *fps)
	{
		result->add_parameter (fp->param_name, fp->type_name, *i);
		i++;
	}
	return result;
}

Object*
Symtable::get (PARAM_NAME* in, bool coerce)
{
	check_param (in);

	string name = *in->value;

	if (coerce)
		phc_TODO ();

	return obj_map[name];
}


void
Symtable::check_param (PARAM_NAME* in)
{
	string name = *in->value;

	if (!obj_map.has (name))
		phc_internal_error ("No parameter named %s", in, name.c_str ());

	Object* obj = obj_map [name];
	string tn = *type_map [name]->value;

	assert (type_map.has (name));

	if (tn == "string"
		&& (isa<String> (obj) || isa<MIR::Identifier> (obj)))
		return;

	if (tn == "token" && isa<MIR::Identifier> (obj))
		return;

	if (tn == "node" && isa<MIR::Node> (obj))
		return;

	// For lists, allow all object lists, and check their type later. We can
	// pass lists for nodes of any type, so dont type check it.
	if (isa<Object_list> (obj))
		return;

	// We want to be able to pass NULLS straight through to other calls. Errors
	// should only be when we try to 'dereference' it.
	if (obj == NULL)
		return;

	string actual_type = (obj == NULL) ? "NULL" : demangle (obj, true);

	phc_internal_error ("Object of type %s does not match expected type %s",
		in, actual_type.c_str (), tn.c_str (), tn.c_str ());
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
			Object* obj;
			if (PARAM_NAME* pn = dynamic_cast<PARAM_NAME*> (interp))
				obj = get_expr (new Param (pn), symtable, false);

			else if (Lookup* lu = dynamic_cast<Lookup*> (interp))
				obj = get_expr (lu, symtable, false);

			else phc_unreachable ();

			if (!isa<String> (obj) && !isa<MIR::Identifier> (obj))
				phc_internal_error ("Cannot interpolate %s", interp,
				demangle (obj));

			ss << *convert_to_string (obj);
		}
		else if (Macro_call* mc = dynamic_cast<Macro_call*> (body_part))
		{
			ss << *exec (mc, symtable);
		}
		else if (Callback* cb = dynamic_cast<Callback*> (body_part))
		{
			ss << *exec (cb, symtable);
		}
		else
			phc_unreachable ();
	}
	return ss.str ();
}

String*
MICG_gen::exec (Macro_call* mc, Symtable* symtable)
{
	return s(instantiate (*mc->macro_name->value, get_expr_list (mc->exprs, symtable), mc));
}

String*
MICG_gen::exec (Callback* cb, Symtable* symtable)
{
	return s (callback (cb->macro_name, get_expr_list (cb->exprs, symtable)));
}



/*
 * Symtable
 */

MIR::Node*
Symtable::get_node (PARAM_NAME* in)
{
	string name = *in->value;
	Object* obj = this->get (in);
	if (!isa<MIR::Node> (obj))
		phc_internal_error ("Expecting a node for param %s (type %s), got a %s",
			in, name.c_str(), type_map[name]->value->c_str (), demangle (obj, true));

	return dyc<MIR::Node> (obj);
}

void
Symtable::add_parameter (PARAM_NAME* param_name, TYPE_NAME* type_name, Object* param)
{
	obj_map [*param_name->value] = param;
	type_map [*param_name->value] = type_name;
}

Object*
Symtable::get_lookup (Lookup* in, bool coerce)
{
	string attr_name = *in->attr_name->value;

	MIR::Node* node = this->get_node (in->param_name);

	// We are interested in attributes of either prefix, but are not interested
	// in writing out the full prefices.
	string ann1 = "phc.codegen.";
	string ann2 = "phc.optimize.";

	ann1.append (attr_name);
	ann2.append (attr_name);

	Object* result = NULL;
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
		result = MICG_gen::convert_to_string (result);

	return result;
}

Object*
Symtable::get_param (Param* in, bool coerce)
{
	Object* result = this->get (in->param_name);

	// Add specified attributes
	if (in->attr_names->size() > 0)
	{
		if (!isa<MIR::Node> (result))
			phc_internal_error ("Trying to add attributes to a non-node (type %s)",
				in, demangle (in));

		result = result->clone (); // dont damage the parameter.
		foreach (ATTR_NAME* an, *in->attr_names)
		{
			stringstream ss;
			ss << "phc.codegen." << *an->value;
			dyc<MIR::Node>(result)->attrs->set_true (ss.str());
		}
	}

	if (coerce || isa<Boolean> (result))
		result = MICG_gen::convert_to_string (result);

	return result;
}

// If coerce is true, coerce the data to a String or Boolean.
Object*
MICG_gen::get_expr (Expr* in, Symtable* symtable, bool coerce)
{
	// Caution: because a caller uses reinterpret_cast, a dynamic_cast doesnt
	// work. However, a dyc() works just fine.
	if (isa<STRING> (in))
		return dyc<STRING> (in)->value;

	if (isa<Lookup> (in))
		return symtable->get_lookup (dyc<Lookup> (in), coerce);

	if (isa<Param> (in))
		return symtable->get_param (dyc<Param> (in), coerce);
	
	if (isa<Macro_call> (in))
		return exec (dyc<Macro_call> (in), symtable);

	if (isa<Callback> (in))
		return exec (dyc<Callback> (in), symtable);

	phc_unreachable ();
}

String*
MICG_gen::convert_to_string (Object* in)
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

String*
MICG_gen::to_string_rep (Object_list* in)
{
	stringstream ss;
	ss << "(";
	foreach (Object* obj, *in)
	{
		String* str = convert_to_string (obj);
		ss 
		<< ((obj == NULL) ? "NULL" : demangle (obj))
		<< ": " << *str << ", ";
	}
	ss << ")";
	return s(ss.str());
}

Object_list*
MICG_gen::get_expr_list (Expr_list* exprs, Symtable* symtable, bool coerce)
{
	Object_list* result = new Object_list;

	foreach (Expr* e, *exprs)
		result->push_back (get_expr (e, symtable, coerce));

	return result;
}



List<Object_list*>*
MICG_gen::expand_list_params (MICG::Macro* m, Object_list* params)
{
	assert (m->signature->formal_parameters->size () == params->size());

	params = params->clone (); // dont damage the parameter.

	Object_list* former = new Object_list; // the params before the list parameter

	// Get the params up until the list parameter, and put them into former;
	foreach (Formal_parameter* fp, *m->signature->formal_parameters)
	{
		Object* param = params->front ();
		if (isa<Object_list> (param) && *fp->type_name->value != "list")
			break;

		former->push_back (param);
		params->pop_front ();
	}

	// No list.
	if (params->size () == 0)
		return new List<Object_list*> (former);

	// The head of PARAMS is now the list parameter.
	Object_list* list_param = dyc<Object_list> (params->front ());
	params->pop_front ();

	// Create the new lists
	List<Object_list*>* result = new List<Object_list*>;
	foreach (Object* elem, *list_param)
	{
		Object_list* param_list = former->clone();
		param_list->push_back (elem);
		param_list->push_back_all (params->clone ());

		result->push_back (param_list);
	}


	return result;
}


