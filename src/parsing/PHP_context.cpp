/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser context for the PHP parser 
 */

#include "PHP_context.h"

PHP_context::PHP_context(std::istream& input, String* filename)
: stream (input)
{	
	init_scanner(NULL);

	php_script = NULL;
	current_method = new String("");
	current_class = new String("");

	this->filename = filename;
	source_line = 1;
	mt_index = 0;
	mt_count = 0;
	last_commented_node = 0;
	hash_bang = NULL;
	
	attach_to_previous = false;
	after_arrow = false;
	starts_line = true;

	heredoc_attr = NULL;
}

int PHP_lex (YYSTYPE* yylval, void* scanner);
int PHP_parse (PHP_context* context);

bool
PHP_context::lex ()
{
	return PHP_lex (mt_lval, scanner);
}


bool
PHP_context::parse ()
{
	return PHP_parse (this) == 0;
}

PHP_context::~PHP_context()
{
	destroy_scanner();
}
