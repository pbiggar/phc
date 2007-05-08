#include <stdio.h>
#include "embed.h"
#include <assert.h>
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
