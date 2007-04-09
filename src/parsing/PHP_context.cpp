/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser context for the PHP parser 
 */

#include "PHP_context.h"

PHP_context::PHP_context(FILE* input, String* filename)
{	
	init_scanner(input);

	php_script = NULL;
	current_method = new String("[outside any method]");
	current_class = new String("[outside any class]");

	this->filename = filename;
	source_line = 1;
	mt_index = 0;
	mt_count = 0;
	last_commented_node = 0;
	
	attach_to_previous = false;
	after_arrow = false;
	starts_line = true;
}

PHP_context::~PHP_context()
{
	destroy_scanner();
}
