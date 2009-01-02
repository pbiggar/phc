/*
 * phc -- the open source php compiler
 * see doc/license/readme.license for licensing information
 *
 * Check the MICG - types and otherwise.
 */

#ifndef PHC_MICG_CHECKER
#define PHC_MICG_CHECKER

#include "MICG.h"
#include "MICG_visitor.h"

#include "lib/String.h"
#include "lib/Map.h"

class MICG_checker : public MICG::Visitor, public GC_obj
{
	string macro_name;

	// param_name -> type_name
	Map <string, string> symtable;

public:
	// TODO: check that if there are multiple macros of the same name, they are
	// consistent in using the 'list' signature.

	void pre_macro (MICG::Macro* in)
	{
		macro_name = *in->signature->macro_name->value;
	}

	void pre_formal_parameter (MICG::Formal_parameter* in)
	{
		string type_name = *in->type_name->value;
		string param_name = *in->param_name->value;
		if (symtable.has (param_name))
			phc_internal_error ("More than 1 parameter named %s in %s",
			in, param_name.c_str(), macro_name.c_str());

		symtable[param_name] = type_name;
	}

	void pre_lookup (MICG::Lookup* lookup)
	{
		// TODO: Check the type is Token or Node
	}

	void pre_param_name (MICG::PARAM_NAME* in)
	{
		string param_name = *in->value;

		if (!symtable.has (param_name))
			phc_internal_error ("%d:%d No param named %s in %s",
				in, in->get_line_number(), in->get_column_number (),
				param_name.c_str (), macro_name.c_str ());
	}

	void pre_interpolation (MICG::Interpolation* in)
	{
		// Check the type is a string or Token
	}

	void pre_equals (MICG::Equals* in)
	{
	}
};


#endif // PHC_MICG_CHECKER
