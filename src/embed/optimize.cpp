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
PHP::fold_unary_op (OP* op, Literal* lit)
{
	stringstream ss;
	MIR_unparser (ss, true).unparse (op);
	MIR_unparser (ss, true).unparse (lit);
	String* code = new String (ss.str());

	zval value;
	bool ret = eval_string (code, &value, lit);
	if (!ret)
	{
		assert (0); // TODO, or should never happen?
	}

	Literal* result = zval_to_mir_literal (&value);
	zval_dtor (&value); // clear out string structure
	return result;
}


bool
PHP::is_true (MIR::Literal* in)
{
	String* code = in->get_value_as_string ();

	zval value;
	bool ret = eval_string (code, &value, in);
	assert (ret);

	bool result = zend_is_true (&value);
	zval_dtor (&value); // clear out string structure
	return result;
}


MIR::Literal*
PHP::cast_to (MIR::CAST* cast, MIR::Literal* in)
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
		ss << "(" << type << ")" << *in->get_value_as_string ();

		zval value;
		bool ret = eval_string (s(ss.str()), &value, in);
		assert (ret);

		Literal* result = zval_to_mir_literal (&value);
		zval_dtor (&value); // clear out string structure
		return result;
	}
	else
		return in;
}




#else // HAVE_EMBED

static void
fail()
{
	phc_error ("Optimizations require the PHP SAPI");
}

bool
PHP::is_pure_function (MIR::METHOD_NAME*)
{
	fail();
}


Literal*
PHP::fold_unary_op (OP* op, Literal* lit)
{
	fail();
}

bool
PHP::is_true (MIR::Literal* literal)
{
	fail();
}


MIR::Literal*
PHP::cast_to (MIR::CAST* cast, MIR::Literal* literal)
{
	fail();
}

#endif // HAVE_EMBED
