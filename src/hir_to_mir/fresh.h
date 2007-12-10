/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#ifndef PHC_FRESH_H
#define PHC_FRESH_H

#include "AST.h"

AST::Variable* fresh_var (string prefix);
AST::Label* fresh_label ();
String* fresh(string prefix);
AST::HT_ITERATOR* fresh_iter ();

#endif // PHC_FRESH_H
