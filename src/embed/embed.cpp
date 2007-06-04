#include "embed.h"
#include <assert.h>

// other #includes are in the #else block of HAVE_PHP5

#if HAVE_EMBED

#include <sapi/embed/php_embed.h>

// copied straight from book, p266
#ifdef ZTS
static void ***tsrm_ls;
#endif

bool PHP::is_started = false;

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

AST_literal* PHP::convert_token (AST_literal *token)
{
	assert (is_started);
	AST_literal* result = NULL;
	String* representation = token->get_source_rep ();
	assert (representation);

	// no return or semi-colon required.
	char* eval = const_cast <char*> (representation->c_str ());

	zval var;
	zend_eval_string (eval, &var, "Evaluate literal" TSRMLS_CC);

	// fetch the var
	if (Z_TYPE_P (&var) == IS_LONG)
	{
		result = new Token_int (Z_LVAL_P (&var), representation);
	}
	else if (Z_TYPE_P (&var) == IS_DOUBLE)
	{
		result = new Token_real (Z_DVAL_P (&var), representation);
	}
	else
		assert (false);

	// TODO - use clone or clone_mixin_from, perhaps?
	result->attrs = token->attrs;

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

AST_literal* PHP::convert_token (AST_literal *token)
{
	assert (is_started);

	Token_int* in = dynamic_cast<Token_int*> (token);
	if (in == NULL)
		return token;

	errno = 0; // clear this since we need to know if strtol sets it

	// we need to know about overflow, so we use strtol here, and strtoll later
	strtol(in->source_rep->c_str(), NULL, 0);

	// if theres overflow, it gets converted to a real, except if its
	// specfied in hex, and its greater than 0x100000000, in which case it
	// becomes int(MAX_INT)
	if(errno == ERANGE)
	{
		errno = 0;
		// check for a hexadecimal integer in the right range
		if (		in->source_rep->compare(0, 2, "0x", 2) == 0
				or in->source_rep->compare(0, 2, "0X", 2) == 0
				or in->source_rep->compare(0, 3, "-0x", 3) == 0
				or in->source_rep->compare(0, 3, "-0X", 3) == 0
			)
		{
			if(strtoll(in->source_rep->c_str(), NULL, 16) > (long long)(ULONG_MAX))
			{
				assert(errno == 0);
				Token_int* i = new Token_int(LONG_MAX, in->source_rep);
				i->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
				return i;
			}
			else 
			{
				assert(errno == 0);
				if(strtoll(in->source_rep->c_str(), NULL, 16) < -(long long)(ULONG_MAX))
				{
					assert(errno == 0);
					// Why LONG_MIN + 1? Well. Ask the PHP folks :)
					Token_int* i = new Token_int(LONG_MIN + 1, in->source_rep);
					i->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
					return i;
				}
				else
				{
					assert(errno == 0);
					// some platforms (cygwin and solaris at least) dont like atof (or strtod) on
					// hex numbers, despite it being part of the C standard for a very
					// long time. Since we're processing digits, we can safely go the long way.
					double value = static_cast<double>(strtoll(in->source_rep->c_str(), NULL, 16));
					assert(errno == 0);
					Token_real* r = new Token_real(value, in->source_rep);
					r->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
					return r;
				}
			}
		}

		// get a real in the case of overflow
		double value = strtod(in->source_rep->c_str(), (char **)NULL);
		assert(errno == 0);
		Token_real* r = new Token_real(value, in->source_rep);
		r->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
		return r;
	}
	else
	{
		return in;
	}
}
#endif
