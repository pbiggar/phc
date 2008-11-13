/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Make implicit parts of a script explicit for the Code Generator.
 */

#include "Clarify.h"
#include "process_ir/General.h"

using namespace MIR;

// TODO: deal with all superglobals 
// TODO: _ENV
// TODO: HTTP_ENV_VARS
// TODO: _POST
// TODO: HTTP_POST_VARS
// TODO: _GET
// TODO: HTTP_GET_VARS
// TODO: _COOKIE
// TODO: HTTP_COOKIE_VARS
// TODO: _FILES
// TODO: HTTP_POST_FILES
// TODO: _REQUEST


void Clarify::post_method (MIR::Method* in)
{
	if (in->statements == NULL)
		return;

	String_list* var_names = new String_list;
	var_names->push_back (s("GLOBALS"));
// Without these, its much easier to read CFGs in SSA form.
//	var_names->push_back (s("_ENV"));
//	var_names->push_back (s("HTTP_ENV_VARS"));
//	var_names->push_back (s("_POST"));
//	var_names->push_back (s("HTTP_POST_VARS"));
//	var_names->push_back (s("_GET"));
//	var_names->push_back (s("HTTP_GET_VARS"));
//	var_names->push_back (s("_COOKIE"));
//	var_names->push_back (s("HTTP_COOKIE_VARS"));
//	var_names->push_back (s("_FILES"));
//	var_names->push_back (s("HTTP_FILES_VARS"));
//	var_names->push_back (s("_REQUEST"));
//	var_names->push_back (s("HTTP_REQUEST_VARS"));
	foreach (String *s, *var_names)
	{
		in->statements->push_front (new Global (new VARIABLE_NAME (s)));
	}
}
