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
			|| name == "exp"
			|| name == "expm1"
			|| name == "floor"
			|| name == "fmod"
			|| name == "getrandmax"
			|| name == "getrandmax"
			|| name == "hexdec"
			|| name == "hexdec"
			|| name == "htmlentities"
			|| name == "htmlspecialchars"
			|| name == "hypot"
			|| name == "intval"
			|| name == "ip2long"
			|| name == "is_finite"
			|| name == "is_infinite"
			|| name == "is_nan"
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
eval_to_literal (stringstream& code, Node* anchor)
{
	String* code_str = s(code.str());

	DEBUG ("Eval'ing string: " << *code_str);

	zval value;
	bool ret = eval_string (code_str, &value, anchor);
	assert (ret); // true/false not SUCCESS/FAILURE

	Literal* result = zval_to_mir_literal (&value);
	zval_dtor (&value); // clear out string structure
	return result;

}

Literal*
PHP::fold_unary_op (OP* op, Literal* lit)
{
	stringstream ss;
	MIR_unparser (ss, true).unparse (op);
	MIR_unparser (ss, true).unparse (lit);

	return eval_to_literal (ss, lit);
}


bool
PHP::is_true (MIR::Literal* lit)
{
	stringstream ss;
	ss << "(bool)" << *lit->get_value_as_string ();

	return eval_to_literal (ss, lit);
}


MIR::Literal*
PHP::cast_to (MIR::CAST* cast, MIR::Literal* lit)
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

		return eval_to_literal (ss, lit);
	}

	return lit;
}


Literal*
PHP::call_function (MIR::METHOD_NAME* name, MIR::Literal_list* params)
{
	stringstream ss;
	ss << *name->value << " (";
	foreach (Literal* param, *params)
	{
		ss << *param->get_value_as_string ();
		if (param != params->back ())
			ss << ", ";
	}
	
	ss << ");";

	return eval_to_literal (ss, name);
}




#else // HAVE_EMBED

#define FAIL(SIG) SIG { phc_error ("Optimizations require the PHP SAPI"); }

FAIL (bool PHP::is_pure_function (MIR::METHOD_NAME*))
FAIL (Literal* PHP::fold_unary_op (OP* op, Literal* lit))
FAIL (bool PHP::is_true (MIR::Literal* literal));
FAIL (MIR::Literal* PHP::cast_to (MIR::CAST* cast, MIR::Literal* literal))
FAIL (Literal* PHP::call_function (MIR::METHOD_NAME* in, MIR::Literal_list* params))

#endif // HAVE_EMBED
