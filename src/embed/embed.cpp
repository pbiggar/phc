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

using namespace AST;

// other #includes are in the #else block of HAVE_PHP5

#if HAVE_EMBED

#include <sapi/embed/php_embed.h>
#include <Zend/zend.h>

// copied straight from book, p266
#ifdef ZTS
static void ***tsrm_ls;
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
}

void PHP::shutdown_php ()
{
	assert (is_started);
	is_started = false;

	php_embed_shutdown (TSRMLS_C);
}

Literal* zval_to_literal (zval* value)
{
	switch (Z_TYPE_P (value))
	{
		case IS_NULL:
			return new NIL ();
		case IS_LONG:
			return new INT (Z_LVAL_P (value));
		case IS_DOUBLE:
			return new REAL (Z_DVAL_P (value));
		case IS_BOOL:
			return new BOOL (Z_BVAL_P (value));
		case IS_STRING:
			return new STRING (
				new String (
					Z_STRVAL_P (value), 
					Z_STRLEN_P (value)));
		default:
			/* We only want literals */
			assert (0);
	}
}


unsigned long PHP::get_hash (String* string)
{
  return zend_get_hash_value (const_cast <char*> (string->c_str ()), string->size () + 1);
}


/* Wrap eval_string, trapping errors and warnings */

// TODO: This isn't re-entrant. I'm not sure how to pass state to handle_php_error_cb
static AST::Node* current_anchor;

/* Handlers for PHP errors */
int myapp_php_ub_write(const char *str, unsigned int str_length TSRMLS_DC)
{
	assert (0);
}

void handle_php_log_message(char *message) 
{
	assert (0);
}

void handle_php_sapi_error(int type, const char *fmt, ...) 
{
	assert (0);
}

int handle_php_ub_write(const char *str, unsigned int str_length TSRMLS_DC)
{
	assert (0);
}

void handle_php_error_cb(int type, const char *error_filename, const uint error_lineno,
const char *format, va_list argp)
{
	phc_warning (format, argp, current_anchor->get_filename(), current_anchor->get_line_number ());
	zend_bailout (); // goto zend_catch
}

// Eval CODE with the PHP interpreter, catch and warn in the case of errors,
// using ANCHOR's filename and line number, then return true/false for
// success/failure.
bool eval_string (String* code, zval* result, Node* anchor)
{
	// Save the anchor for filenames and linenumbers
	current_anchor = anchor;

	// Divert output and error
	zend_error_cb = handle_php_error_cb;
	php_embed_module.ub_write = handle_php_ub_write;
	php_embed_module.log_message = handle_php_log_message;
	php_embed_module.sapi_error = handle_php_sapi_error;
	zend_first_try 
	{
		zend_eval_string (const_cast<char*>(code->c_str ()), result, "Evaluate literal" TSRMLS_CC);
	}
	zend_catch
	{
		return false;
	}
	zend_end_try ();
	return true;
}

Literal* PHP::convert_token (Literal *in)
{
	String* code = in->get_source_rep ();
	assert (code);

	zval value;
	bool ret_val = eval_string (code, &value, in);
	assert (ret_val);

	Literal* result = zval_to_literal (&value);
	result->attrs->clone_all_from (in->attrs);
	return result;
}


Expr* PHP::fold_constant_expr (Expr* in)
{
	// Avoid parse errors due to '{'
	Expr* clone = in->clone ();
	clone->attrs->erase_with_prefix ("phc.unparser");

	stringstream ss;
	clone->visit (new AST_unparser (ss, true));
	String* code = new String (ss.str());


	zval value;
	bool ret = eval_string (code, &value, in);
	if (!ret)
	{
		cdebug << "Error, can not fold constants: ";
		debug (in);
		return in;
	}

	Literal* result = zval_to_literal (&value);
	zval_dtor (&value); // clear out string structure
	result->attrs->clone_all_from (in->attrs);
	return result;
}

#else

#include <errno.h>
#include <limits.h>

bool PHP::is_started = false;

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

bool PHP::is_available ()
{
	return false;
}

Expr* PHP::fold_constant_expr (Expr* in)
{
	return in;
}

#endif
