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

bool
PHP::is_pure_function (METHOD_NAME* in)
{
	// TODO theres a lot more functions here, such as string functions
	string name = *in->value;
	return   name == "abs"
			|| name == "acos"
			|| name == "acosh"
			|| name == "addslashes"
			|| name == "asin"
			|| name == "asinh"
			|| name == "atan"
			|| name == "atan2"
			|| name == "atanh"
			|| name == "base_convert"
			|| name == "basename"
			|| name == "bindec"
			|| name == "ceil"
			|| name == "chop"
			|| name == "chr"
			|| name == "cos"
			|| name == "cosh"
			|| name == "crc32"
			|| name == "decbin"
			|| name == "decbin"
			|| name == "dechex"
			|| name == "dechex"
			|| name == "decoct"
			|| name == "decoct"
			|| name == "deg2rad"
			|| name == "dirname"
			|| name == "doubleval"
			|| name == "exp"
			|| name == "expm1"
			|| name == "floor"
			|| name == "floatval"
			|| name == "fmod"
			|| name == "getrandmax"
			|| name == "getrandmax"
			|| name == "gettype"
			|| name == "hexdec"
			|| name == "hexdec"
			|| name == "htmlentities"
			|| name == "htmlspecialchars"
			|| name == "hypot"
			|| name == "intval"
			|| name == "ip2long"
			|| name == "is_array"
			|| name == "is_binary"
			|| name == "is_bool"
			|| name == "is_buffer"
			|| name == "is_double"
			|| name == "is_finite"
			|| name == "is_float"
			|| name == "is_infinite"
			|| name == "is_int"
			|| name == "is_integer"
			|| name == "is_long"
			|| name == "is_nan"
			|| name == "is_null"
			|| name == "is_numeric"
			|| name == "is_object"
			|| name == "is_real"
			|| name == "is_resource"
			|| name == "is_scalar"
			|| name == "is_string"
			|| name == "is_unicode"
			|| name == "lcg_value"
			|| name == "log"
			|| name == "log10"
			|| name == "log1p"
			|| name == "long2ip"
			|| name == "ltrim"
			|| name == "max"
			|| name == "md5"
			|| name == "min"
			|| name == "mt_getrandmax"
			|| name == "mt_getrandmax"
			|| name == "octdec"
			|| name == "octdec"
			|| name == "ord"
			|| name == "php_egg_logo_guide"
			|| name == "php_logo_guide"
			|| name == "pi"
			|| name == "pi"
			|| name == "pow"
			|| name == "rad2deg"
			|| name == "realpath"
			|| name == "round"
			|| name == "rtrim"
			|| name == "sha1"
			|| name == "sin"
			|| name == "sinh"
			|| name == "sqrt"
			|| name == "strcasecmp"
			|| name == "strcmp"
			|| name == "strlen"
			|| name == "strncasecmp"
			|| name == "strncmp"
			|| name == "str_pad"
			|| name == "str_repeat"
			|| name == "strtoupper"
			|| name == "strtoupper"
			|| name == "strval"
			|| name == "substr"
			|| name == "tan"
			|| name == "tanh"
			|| name == "trim"
			|| name == "version_compare"
			|| name == "zend_function"
			|| name == "zend_logo_guide"
			;
}

Literal*
eval_to_literal (stringstream& code)
{
	String* code_str = s(code.str());

	zval value;
	bool ret = eval_string (code_str, &value);
	if (!ret) // true/false not SUCCESS/FAILURE
		return NULL;

	Literal* result = zval_to_mir_literal (&value);
	zval_dtor (&value); // clear out string structure
	return result;
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

	// Assume this can fail for no good reason (maybe wrong number of params),
	// and that we must recover from it.
	// TODO: warn in this case.
	zval value;
	if (eval_string (s(ss.str()), &value))
	{
		Literal* result = zval_to_mir_literal (&value);
		zval_dtor (&value); // clear out string structure
		return result;
	}
	else
		return NULL;
}

Literal*
PHP::fold_pre_op (Literal* use, OP* op)
{
	stringstream ss;
	ss << "$temp = ";
	MIR_unparser (ss, true).unparse (use);
	ss << "; " << *op->value << "$temp;";


	// Assume this can fail for no good reason (bad types?) and that we must
	// recover from it.
	// TODO: warn in this case.
	zval value;
	if (eval_string (s("$temp"), &value, NULL, s(ss.str ())))
	{
		Literal* result = zval_to_mir_literal (&value);
		zval_dtor (&value); // clear out string structure
		return result;
	}
	else
		return NULL;
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
