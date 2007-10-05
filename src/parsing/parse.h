/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser wrapper. 
 *
 * Plugins should be able to call "parse", but the header files that can be
 * #included from plugins should never include any code, because this leads
 * to linker problems.
 */

#ifndef PHC_PARSE
#define PHC_PARSE

#include "AST.h"

using namespace AST;

/*
 * Parse the specified file. Searches for the file in the current working
 * directory, and in any of the directories specified in dirs (if any). 
 * If the filename is "-", assume standard input.
 *
 * Assume PHP/HTML syntax unless is_ast_xml, in which case we assume the input
 * is an AST in XML syntax.
 *
 * Tries both '/' (preferred) and '\'.
 *
 * If there is a syntax error, returns NULL.
 */ 
AST_php_script* parse(String* filename, List<String*>* dirs, bool is_ast_xml = false);

#endif // PHC_PARSE
