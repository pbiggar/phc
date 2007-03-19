/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * User-defined tree processing
 */

#include "AST.h"

void process_ast(AST_php_script* php_script)
{
	/*
	 * The preferred way of extending phc (in versions >= 0.1.7) is through plugins
	 * Use this method only if you want to hardcode your extension into phc
	 *
	 * See http://www.phpcompiler.org/doc for more details.
	 */
}
