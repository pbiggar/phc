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
#include "optimize/Method_info.h"
#include "optimize/Class_info.h"

using namespace MIR;

#if !HAVE_EMBED

#define FAIL(SIG) SIG { phc_error ("Optimizations require the PHP SAPI"); }

FAIL (Literal* PHP::fold_unary_op (OP*, Literal*))
FAIL (bool PHP::is_true (Literal*));
FAIL (Literal* PHP::cast_to (CAST*, Literal*))
FAIL (String* PHP::get_string_value (Literal* lit))
FAIL (Literal* PHP::fold_bin_op (Literal* left, OP* op, Literal* right))
FAIL (Literal* PHP::fold_pre_op (Literal* use, OP* op))
FAIL (Literal* PHP::fold_constant (Constant* in))
FAIL (Literal* PHP::fold_string_index (Literal* array, Literal* index))

FAIL (Method_info* PHP::get_method_info (String*))
FAIL (Literal* PHP::call_function (METHOD_NAME*, Literal_list*))

#else // HAVE_EMBED

#include <sapi/embed/php_embed.h>
#include <Zend/zend.h>

// Use the one from embed.cpp
#ifdef ZTS
extern void ***tsrm_ls;
#endif



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
	ss << unparse (op) << unparse (lit);

	return eval_to_literal (ss);
}

Literal*
PHP::fold_bin_op (Literal* left, OP* op, Literal* right)
{
	stringstream ss;
	ss << unparse (left) << " " << unparse (op) << " " << unparse (right);

	return eval_to_literal (ss);
}

Literal*
PHP::fold_string_index (Literal* array, Literal* index)
{
	string prep = "$temp = " + unparse (array) + ";";

	stringstream code;
	code  << "$temp[" << unparse (index) << "];";

	return eval_to_literal (code, s(prep));
}


bool
PHP::is_true (Literal* lit)
{
	stringstream ss;
	ss << "(bool)(" << unparse (lit) << ")";

	Literal* result = eval_to_literal (ss);

	return dyc<BOOL> (result)->value;
}

String*
PHP::get_string_value (Literal* lit)
{
	Literal* casted = cast_to (new CAST (s("string")), lit);
	return dyc<STRING> (casted)->value;
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
		ss << "(" << type << ")" << unparse (lit);

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
		ss << unparse (param);

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
	prep
	<< "$temp = " << unparse (use) << ";"
	<< unparse (op) << "$temp;";

	stringstream ss;
	ss << "$temp";

	return eval_to_literal (ss, s(prep.str ()));
}


Literal*
PHP::fold_constant (Constant* in)
{
	string constant = unparse (in);

	zval value;

	// returns 1 for success, 0 for failure (not SUCCESS/FAILURE)!
	int zend_result = zend_get_constant (
		const_cast<char*> (constant.c_str ()),
		constant.size (),
		&value TSRMLS_CC);

	if (zend_result == 0)
		return NULL;
	
	assert (zend_result == 1);
	Literal* result = zval_to_mir_literal (&value);
	zval_dtor (&value); // clear out string structure
	return result;
}


class Internal_method_info : public Summary_method_info
{
	// TODO: what would the function caches get me?
	zend_function* func;

public:
	Internal_method_info (String* name, zend_function* func);

	bool has_implementation ();

	bool return_by_ref ();
	bool param_by_ref (int param_index);
	MIR::VARIABLE_NAME* param_name (int param_index);
	MIR::Static_value* default_param (int param_index);
	int formal_param_count ();

	bool get_side_effecting ();
};


Method_info*
PHP::get_method_info (String* name)
{
	zval fn;
	INIT_PZVAL (&fn);
	ZVAL_STRING (&fn, const_cast<char*> (name->c_str ()), 0);


	zend_fcall_info fci;
	zend_fcall_info_cache fcic;
	int result = zend_fcall_info_init (&fn, &fci, &fcic TSRMLS_CC);

	if (result != SUCCESS)
		return NULL;

	return new Internal_method_info (name, fcic.function_handler);
}


Internal_method_info::Internal_method_info (String* name, zend_function* func)
: Summary_method_info (name)
, func(func)
{
}


bool
Internal_method_info::has_implementation ()
{
	return false;
}

bool
Internal_method_info::return_by_ref ()
{
	return func->common.return_reference;
}

bool
Internal_method_info::param_by_ref (int param_index)
{
	return ARG_MUST_BE_SENT_BY_REF (func, (unsigned int)(param_index+1));
}

MIR::VARIABLE_NAME*
Internal_method_info::param_name (int param_index)
{
	return unnamed_param (param_index);
}

MIR::Static_value*
Internal_method_info::default_param (int param_index)
{
	return NULL;
}

int
Internal_method_info::formal_param_count ()
{
	return func->common.num_args;
}


bool
Internal_method_info::get_side_effecting ()
{
	string name = *this->name;
	return not (0
			|| name == "abs"
			|| name == "acos"
			|| name == "acosh"
			|| name == "addslashes"
			|| name == "asin"
			|| name == "asinh"
			|| name == "atan"
			|| name == "atan2"
			|| name == "atanh"
			|| name == "base64_decode"
			|| name == "base64_encode"
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
			|| name == "dechex"
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
			|| name == "gettype"
			|| name == "hexdec"
			|| name == "htmlentities"
			|| name == "htmlspecialchars"
			|| name == "hypot"
			|| name == "intval"
			|| name == "ip2long"
			|| name == "is_a"
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
			|| name == "is_subclass_of"
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
			|| name == "octdec"
			|| name == "ord"
			|| name == "php_egg_logo_guide"
			|| name == "php_logo_guide"
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
			|| name == "strval"
			|| name == "substr"
			|| name == "tan"
			|| name == "tanh"
			|| name == "trim"
			|| name == "version_compare"
			|| name == "zend_function"
			|| name == "zend_logo_guide"
			)
			;
}







#endif // HAVE_EMBED
