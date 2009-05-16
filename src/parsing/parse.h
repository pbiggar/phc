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
AST::PHP_script* parse (String* filename, String_list* dirs);

/*
 * Perform the search as in parse(String*, String_list*), and return the
 * absolute path of the found file, or NULL if not found.
 */ 
String* search_file (String* filename, String_list* dirs);

/* Parse CODE, assuming that it comes from FILENAME:LINE_NUMBER */
AST::PHP_script* parse_code (String* code, String* filename, int line_number);


void dump_parse_tree (String* filename, String_list* dirs);

#endif // PHC_PARSE
