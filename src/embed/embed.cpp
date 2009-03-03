/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap the embedded PHP run-time
 */

#include "embed.h"
#include "process_ir/General.h"
#include "process_ast/AST_unparser.h"
#include <assert.h>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

// other #includes are in the #else block of HAVE_PHP5

using namespace AST;

#if HAVE_EMBED

#include <sapi/embed/php_embed.h>
#include <Zend/zend.h>

#include "util.h"

// copied straight from book, p266
#ifdef ZTS
void ***tsrm_ls;
#endif

bool PHP::is_started = false;

bool PHP::is_available ()
{
	return true;
}

void PHP::startup_php ()
{
	assert (is_started == false);
	is_started = true;

	php_embed_init (0, NULL PTSRMLS_CC);

	// Prevent the Zend engine from stopping after time runs out.
	int result = zend_alter_ini_entry (
				"max_execution_time", sizeof ("max_execution_time"),
				"0", sizeof ("0"),
				PHP_INI_ALL, PHP_INI_STAGE_RUNTIME);
	assert (result == SUCCESS);
}

void PHP::shutdown_php ()
{
	assert (is_started);
	is_started = false;

	php_embed_shutdown (TSRMLS_C);
}

unsigned long PHP::get_hash (String* string)
{
	return zend_get_hash_value (
		const_cast <char*> (string->c_str ()), 
		string->size () + 1);
}

Literal* PHP::convert_token (Literal *in)
{
	String* code = in->get_source_rep ();
	assert (code);

	zval value;
	bool ret = eval_string (code, &value, in);
	assert (ret);

	Literal* result = zval_to_ast_literal (&value);
	result->attrs->clone_all_from (in->attrs);
	return result;
}


Expr* PHP::fold_constant_expr (Expr* in)
{
	// Avoid parse errors due to '{'
	Expr* clone = in->clone ();
	clone->attrs->erase_with_prefix ("phc.unparser");

	stringstream ss;
	AST_unparser (ss, true).unparse (clone);
	String* code = new String (ss.str());


	zval value;
	bool ret = eval_string (code, &value, in);
	if (!ret)
	{
		DEBUG ("Error, can not fold constants: ");
		debug (in);
		return in;
	}

	Literal* result = zval_to_ast_literal (&value);
	zval_dtor (&value); // clear out string structure
	result->attrs->clone_all_from (in->attrs);
	return result;
}


void
PHP::set_ini_entry (String* key, String* value)
{
	// Keep track of entered keys
	PHP::altered_ini_entries.insert (*key);


	int result = zend_alter_ini_entry (
				const_cast<char*> (key->c_str ()),
				key->size () + 1, // include NULL byte
				const_cast<char*> (value->c_str()),
				value->size (), // dont include NULL byte
				PHP_INI_ALL,
				PHP_INI_STAGE_RUNTIME);


	assert (result == SUCCESS);
	// check the value changed
	assert (zend_ini_string (const_cast<char*> (key->c_str ()), key->size () + 1, 0) == *value);
}

Set<string> PHP::altered_ini_entries;

String_list*
PHP::get_altered_ini_entries ()
{
	String_list* result = new String_list;

	foreach (string entry, PHP::altered_ini_entries)
		result->push_back (s(entry));

	return result;
}

String_list*
PHP::get_include_paths ()
{
	String_list* result = new String_list;

	String* ini = new String (zend_ini_string ("include_path", sizeof ("include_path"), 0));

	// Split the string using ':' as delimiter
	std::vector <string> dirs;
	boost::algorithm::split (dirs, *ini, boost::algorithm::is_any_of(":"));
	foreach (string dir, dirs)
	{
		result->push_back (s (dir));
	}

	return result;
}

String* 
PHP::get_ini_entry (String* key)
{
	return s (zend_ini_string (const_cast<char*> (key->c_str ()), key->size () + 1, 0));
}

#else

#include <errno.h>
#include <limits.h>

bool PHP::is_started = false;

bool PHP::is_available ()
{
	return false;
}

void PHP::startup_php ()
{

	assert (is_started == false);
	is_started = true;
}

void PHP::shutdown_php ()
{
	assert (is_started);
	is_started = false;
}

Literal* PHP::convert_token (Literal *token)
{
	assert (is_started);

	// Add the naive value
	if (INT* in = dynamic_cast<INT*> (token))
		in->value = strtol(in->get_source_rep ()->c_str(), NULL, 0);
	else if (REAL* in = dynamic_cast<REAL*> (token))
		in->value = lexical_cast<double> (*in->get_source_rep ());


	/* Handle INT overflows and underflows */
	INT* in = dynamic_cast<INT*> (token);
	if (in == NULL)
		return token;

	errno = 0; // clear this since we need to know if strtol sets it

	// we need to know about overflow, so we use strtol here, and strtoll later
	strtol(in->get_source_rep ()->c_str(), NULL, 0);

	// if theres overflow, it gets converted to a real, except if its
	// specfied in hex, and its greater than 0x100000000, in which case it
	// becomes int(MAX_INT)
	if(errno == ERANGE)
	{
		errno = 0;
		// check for a hexadecimal integer in the right range
		if (		in->get_source_rep()->compare(0, 2, "0x", 2) == 0
				or in->get_source_rep()->compare(0, 2, "0X", 2) == 0
				or in->get_source_rep()->compare(0, 3, "-0x", 3) == 0
				or in->get_source_rep()->compare(0, 3, "-0X", 3) == 0
			)
		{
			if(strtoll(in->get_source_rep()->c_str(), NULL, 16) > (long long)(ULONG_MAX))
			{
				assert(errno == 0);
				INT* i = new INT(LONG_MAX, in->get_source_rep ());
				i->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
				return i;
			}
			else
			{
				assert(errno == 0);
				if(strtoll(in->get_source_rep ()->c_str(), NULL, 16) < -(long long)(ULONG_MAX))
				{
					assert(errno == 0);
					// Why LONG_MIN + 1? Well. Ask the PHP folks :)
					INT* i = new INT(LONG_MIN + 1, in->get_source_rep ());
					i->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
					return i;
				}
				else
				{
					assert(errno == 0);
					// some platforms (cygwin and solaris at least) dont like atof (or strtod) on
					// hex numbers, despite it being part of the C standard for a very
					// long time. Since we're processing digits, we can safely go the long way.
					double value = static_cast<double>(strtoll(in->get_source_rep ()->c_str(), NULL, 16));
					assert(errno == 0);
					REAL* r = new REAL(value, in->get_source_rep ());
					r->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
					return r;
				}
			}
		}

		// get a real in the case of overflow
		double value = strtod(in->get_source_rep ()->c_str(), (char **)NULL);
		assert(errno == 0);
		REAL* r = new REAL(value, in->get_source_rep ());
		r->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
		return r;
	}
	else
	{
		return in;
	}
}

unsigned long PHP::get_hash (String* string)
{
	// TODO people who dont have PHP installed may still want to see
	// generated C code (perhaps to be cross compiled?)
	assert (0);
}

Expr* PHP::fold_constant_expr (Expr* in)
{
	return in;
}

void
PHP::set_ini_entry (String* key, String* value)
{
}

String_list*
PHP::get_include_paths ()
{
	return new String_list;
}

String_list*
PHP::get_altered_ini_entries ()
{
	return new String_list;
}

String*
PHP::get_ini_entry (String*)
{
	return new String;
}

#endif


/*
 * These dont actually use embed
 */

//TODO: inform PHP at run-time that these have been included
// We dont actually need to involve the PHP run-time here
static Set<string> included;

bool
PHP::is_included (String* filename)
{
	// TODO: assert absolute filename
	return included.has (*filename);
}

void
PHP::add_include (String* filename)
{
	// TODO: assert absolute filename
	included.insert (*filename);
}


