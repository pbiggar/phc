#include "Oracle.h"
#include "embed/embed.h"

using namespace MIR;

Map<string, Method_info*> Oracle::infos;

// TODO: We dont put Method_mods into the signature.
void
Oracle::initialize (MIR::PHP_script* in)
{
	// TODO: add a case for the most conservative we may ever have to be.
	
	/*
	 * Add existing functions
	 */
	foreach (Statement* stmt, *in->statements)
	{
		if (Method* m = dynamic_cast<Method*> (stmt))
			add_method_info (new Method_info (m->signature->method_name->value, m));

		else if (Interface_def* i = dynamic_cast<Interface_def*> (stmt))
			phc_TODO ();

		else if (Class_def* c = dynamic_cast<Class_def*> (stmt))
			phc_TODO ();
	}

	/*
	 * Add builtins
	 */
	// TODO: return value (use null for no return value)
	// TODO: return type

	add_method_info (
		new Method_info (
			s("print"),
			new Parameter_info_list (
				new Parameter_info (
					false,
					false,
					new String_list (s("__toString")))),
			false,
			false,
			false));

}

Method_info*
Oracle::get_method_info (String* method_name)
{
	// Cached
	if (Oracle::infos.has (*method_name))
		return Oracle::infos [*method_name];

	// Lookup the embed SAPI
	Signature* sig = PHP::get_signature (new METHOD_NAME (method_name));

	// Cache it
	if (sig)
	{
		add_signature (sig);
		return get_method_info (method_name);
	}

	return NULL;
}

void
Oracle::add_signature (Signature* sig)
{
	Parameter_info_list* params = new Parameter_info_list;
	foreach (Formal_parameter* param, *sig->formal_parameters)
	{
		params->push_back (
			new Parameter_info (
				param->is_ref,
				false, 
				new String_list));
	}

	add_method_info (
		new Method_info (
			sig->method_name->value,
			params,
			!Oracle::is_pure_function (sig->method_name),
			!Oracle::is_pure_function (sig->method_name),
			sig->return_by_ref));
}

void
Oracle::add_method_info (Method_info* info)
{
	assert (!infos.has (*info->method_name));

	infos[*info->method_name] = info;
}


bool
Oracle::is_pure_function (METHOD_NAME* in)
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

bool
Oracle::is_const_function (METHOD_NAME* name)
{
	// TODO: I had this returning whether or not it affected global state, or
	// just its parameters. But if affecting its parameters can touch global
	// state, is it a good idea?
	return false;
}
