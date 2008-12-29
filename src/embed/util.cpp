/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap the embedded PHP run-time - utility functions.
 */

#include "util.h"
#include "process_ir/General.h"
#include "process_ast/AST_unparser.h"
#include <assert.h>

// other #includes are in the #else block of HAVE_PHP5

#if HAVE_EMBED

#include <sapi/embed/php_embed.h>
#include <Zend/zend.h>

// Use the one from embed.cpp
#ifdef ZTS
extern void ***tsrm_ls;
#endif

using namespace std;

template<
	class Literal,
	class NIL,
	class INT,
	class REAL,
	class BOOL,
	class STRING
>
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


AST::Literal* zval_to_ast_literal (zval* value)
{
	return zval_to_literal<
		AST::Literal,
		AST::NIL,
		AST::INT,
		AST::REAL,
		AST::BOOL,
		AST::STRING> (value);
}

HIR::Literal* zval_to_hir_literal (zval* value)
{
	return zval_to_literal<
		HIR::Literal,
		HIR::NIL,
		HIR::INT,
		HIR::REAL,
		HIR::BOOL,
		HIR::STRING> (value);
}

MIR::Literal* zval_to_mir_literal (zval* value)
{
	return zval_to_literal<
		MIR::Literal,
		MIR::NIL,
		MIR::INT,
		MIR::REAL,
		MIR::BOOL,
		MIR::STRING> (value);
}


/* Wrap eval_string, trapping errors and warnings */

// TODO: This isn't re-entrant. I'm not sure how to pass state to
// handle_php_error_cb
static IR::Node* current_anchor;

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

void handle_php_error_cb(
		int type, 
		const char *error_filename, 
		const uint error_lineno,
		const char *format,
		va_list argp)
{
	if (current_anchor)
		phc_warning (
				format, 
				argp, 
				current_anchor->get_filename(), 
				current_anchor->get_line_number (),
				0);
	else
	{
		if (debugging_enabled)
		{
			// TODO: correct length?
			char string[1000];
			snprintf (string, 990, format, argp);
			cdebug << string << endl;
		}
	}

	zend_bailout (); // goto zend_catch
}

// Eval CODE with the PHP interpreter, catch and warn in the case of errors,
// using ANCHOR's filename and line number, then return true/false for
// success/failure.
bool eval_string (String* code, zval* result, IR::Node* anchor, String* prepare)
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
		DEBUG ("Eval'ing string: " << *code);
		if (prepare)
		{
			DEBUG ("with prep: " << *prepare);
		}

		if (prepare)
		{
			zend_eval_string (
					const_cast<char*>(prepare->c_str ()), 
					NULL, // so that it doesnt add a 'return' statement
					const_cast<char*>("phc eval")
					TSRMLS_CC);
		}


		zend_eval_string (
			const_cast<char*>(code->c_str ()), 
			result, 
			const_cast<char*>("phc eval")
			TSRMLS_CC);
	}
	zend_catch
	{
		return false;
	}
	zend_end_try ();
	return true;
}

#endif // HAVE_EMBED
