/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience functions and headers
 */

#ifndef PHC_GENERAL
#define PHC_GENERAL

#include "debug.h"
#include "Foreach.h"
#include "Clone_blank_mixins.h"

#include "HIR.h"
#include "AST.h"

// 'new String' must be the most typed function in phv
String* s (string s);


/* Lower IN by running all the passes between "hir" and NAME on it. */
List<HIR::Statement*>* lower_hir (String* name, HIR::Statement* in);

/* Lower IN by running all the passes between "ast" and NAME on it. */
List<AST::Statement*>* lower_ast (String* name, AST::Statement* in);
List<AST::Statement*>* lower_ast (String* name, List<AST::Statement*>* in);


/* Parse CODE into a list of HIR statements, using NODE as the source for
 * filenames and line numbers. */
List<HIR::Statement*>* parse_to_hir (String* code, HIR::Node* node);

/* Parse CODE into a list of AST statements, using NODE as the source for
 * filenames and line numbers. */
List<AST::Statement*>* parse_to_ast (String* code, AST::Node* node);


#endif // PHC_GENERAL
