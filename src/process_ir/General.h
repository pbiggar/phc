/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience functions and headers
 */

#ifndef PHC_GENERAL
#define PHC_GENERAL

#include "AST.h"
#include "HIR.h"
#include "MIR.h"

// 'new String' must be the most typed function in phv
String* s (string s);

/* Lower IN by running all the passes between "hir" and NAME on it. */
List<AST::Statement*>* lower_ast (String* name, AST::Statement* in);
List<AST::Statement*>* lower_ast (String* name, List<AST::Statement*>* in);
List<HIR::Statement*>* lower_hir (String* name, HIR::Statement* in);
List<HIR::Statement*>* lower_hir (String* name, List<HIR::Statement*>* in);
List<MIR::Statement*>* lower_mir (String* name, MIR::Statement* in);
List<MIR::Statement*>* lower_mir (String* name, List<MIR::Statement*>* in);


/* Parse CODE into a list of HIR statements, using NODE as the source for
 * filenames and line numbers. */
List<AST::Statement*>* parse_to_ast (String* code);
List<HIR::Statement*>* parse_to_hir (String* code);
List<MIR::Statement*>* parse_to_mir (String* code);

#include "debug.h"
#include "Foreach.h"
#include "fresh.h"
#include "Clone_blank_mixins.h"
#include "parsing/Parse_buffer.h"

#endif // PHC_GENERAL
