/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Optimization through the PHP interpreter.
 */

#include "embed.h"
#include "util.h"
#include "lib/String.h"
#include "process_ir/General.h"
#include "MIR.h"
#include "process_mir/MIR_unparser.h"

#if HAVE_EMBED

#include <sapi/embed/php_embed.h>
#include <Zend/zend.h>

// Use the one from embed.cpp
#ifdef ZTS
extern void ***tsrm_ls;
#endif

using namespace MIR;



Literal*
eval_to_literal (stringstream& code, String* prep = NULL)
{
	String* code_str = s(code.str());

	zval value;
	if (eval_string (code_str, &value, NULL, prep))
	{
		Literal* result = zval_to_mir_literal (&value);
		zval_dtor (&value); // clear out string structure
		return result;
	}
	else
		return NULL;
}

Literal*
PHP::fold_unary_op (OP* op, Literal* lit)
{
	stringstream ss;
	MIR_unparser (ss, true).unparse (op);
	MIR_unparser (ss, true).unparse (lit); // literals need "" sometimes

	return eval_to_literal (ss);
}

Literal*
PHP::fold_bin_op (Literal* left, OP* op, Literal* right)
{
	stringstream ss;
	MIR_unparser (ss, true).unparse (left);
	ss << " ";
	MIR_unparser (ss, true).unparse (op);
	ss << " ";
	MIR_unparser (ss, true).unparse (right);

	return eval_to_literal (ss);
}

Literal*
PHP::fold_string_index (Literal* array, Literal* index)
{
	stringstream prep;
	prep << "$temp = ";
	MIR_unparser (prep, true).unparse (array);
	prep << ";";

	stringstream code;
	code  << "$temp[";
	MIR_unparser (code, true).unparse (index);
	code << "];";

	return eval_to_literal (code, s(prep.str()));
}


bool
PHP::is_true (Literal* lit)
{
	stringstream ss;
	ss << "(bool)" << *lit->get_value_as_string ();

	Literal* result = eval_to_literal (ss);

	return dyc<BOOL> (result)->value;
}


Literal*
PHP::cast_to (CAST* cast, Literal* lit)
{
	// TODO add canonicalization pass to convert to lowercase
	string type = *cast->value;
	if (	type == "integer"
		|| type == "int"
		|| type == "string"
		|| type == "binary"
		|| type == "real"
		|| type == "double"
		|| type == "float"
		|| type == "bool"
		|| type == "boolean"
		|| type == "unset") // NULL
	{
		stringstream ss;
		ss << "(" << type << ")" << *lit->get_value_as_string ();

		return eval_to_literal (ss);
	}

	return NULL;
}

Signature*
PHP::get_signature (METHOD_NAME* method_name)
{
	zval fn;
	INIT_PZVAL (&fn);
	ZVAL_STRING (&fn, const_cast<char*> (method_name->value->c_str ()), 0);

	zend_fcall_info fci;
	zend_fcall_info_cache fcic;
	int result = zend_fcall_info_init (&fn, &fci, &fcic TSRMLS_CC);

	zend_function* func = fcic.function_handler;
	if (result != SUCCESS)
		return NULL;

	Signature* sig = new Signature (method_name->value->c_str ());

	sig->pass_rest_by_ref = func->common.pass_rest_by_reference; 
	sig->return_by_ref = func->common.return_reference;

	for (unsigned int i = 0; i < func->common.num_args; i++)
	{
		stringstream ss;
		ss << "unknown" << i;

		Formal_parameter* param = 
			new Formal_parameter (
				NULL, // TODO
				ARG_MUST_BE_SENT_BY_REF (func, i+1),
				new VARIABLE_NAME (s (ss.str ())));

		sig->formal_parameters->push_back (param);
	}
	return sig;
}


Literal*
PHP::call_function (METHOD_NAME* name, Literal_list* params)
{
	stringstream ss;
	ss << *name->value << " (";
	foreach (Literal* param, *params)
	{
		MIR_unparser (ss, true).unparse (param);

		// No ", " after last param.
		if (param != params->back ())
			ss << ", ";
	}
	ss << ");";

	return eval_to_literal (ss);
}

Literal*
PHP::fold_pre_op (Literal* use, OP* op)
{
	stringstream prep;
	prep << "$temp = ";
	MIR_unparser (prep, true).unparse (use);
	prep << "; " << *op->value << "$temp;";

	stringstream ss;
	ss << "$temp";

	return eval_to_literal (ss, s(prep.str ()));
}


Literal*
PHP::fold_constant (Constant* in)
{
	stringstream ss;
	MIR_unparser (ss, true).unparse (in);

	zval value;

	// returns 1 for success, 0 for failure (not SUCCESS/FAILURE)!
	int zend_result = zend_get_constant (
		const_cast<char*> (ss.str().c_str ()),
		ss.str().size (),
		&value TSRMLS_CC);

	if (zend_result == 0)
		return NULL;
	
	assert (zend_result == 1);
	Literal* result = zval_to_mir_literal (&value);
	zval_dtor (&value); // clear out string structure
	return result;
}


#else // HAVE_EMBED

#define FAIL(SIG) SIG { phc_error ("Optimizations require the PHP SAPI"); }

FAIL (bool PHP::is_pure_function (METHOD_NAME*))
FAIL (Literal* PHP::fold_unary_op (OP*, Literal*))
FAIL (bool PHP::is_true (Literal*));
FAIL (Literal* PHP::cast_to (CAST*, Literal*))
FAIL (Literal* PHP::call_function (METHOD_NAME*, Literal_list*))
FAIL (Literal* PHP::fold_pre_op (Literal* use, OP* op))
FAIL (Literal* PHP::fold_constant (Constant* in))

#endif // HAVE_EMBED
