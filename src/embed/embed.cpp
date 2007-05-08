#include <stdio.h>
#include "embed.h"
#include <assert.h>
#include <sapi/embed/php_embed.h>

AST_literal* PHP::convert_token (AST_literal *token)
{
	AST_literal* result = NULL;
	String* representation = token->get_source_rep ();
	assert (representation);

	PHP_EMBED_START_BLOCK (0, NULL)

		// prepare the string - for some reason, cant do this outside the scope
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

	PHP_EMBED_END_BLOCK ();

	// TODO - use clone or clone_mixin_from, perhaps?
	result->attrs = token->attrs;

	return result;

}
