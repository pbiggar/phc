/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#ifndef PHC_FRESH_H
#define PHC_FRESH_H

#include "AST.h"

AST::AST_variable* fresh_var (string prefix);
AST::AST_label* fresh_label ();
String* fresh(string prefix);

#endif // PHC_FRESH_H
