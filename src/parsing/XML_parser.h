/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the AST in XML format
 */

#ifndef PHC_XML_PARSER_H
#define PHC_XML_PARSER_H

#include "config.h"

#ifdef HAVE_XERCES
#include "AST.h"
AST::PHP_script* parse_ast_xml_file(String* filename);
AST::PHP_script* parse_ast_xml_buffer(String* buffer);
AST::PHP_script* parse_ast_xml_stdin();
#endif // HAVE_XERCES

#endif // PHC_XML_PARSER_H
