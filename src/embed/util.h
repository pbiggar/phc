/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap the embedded PHP run-time - utility functions
 */

#ifndef PHC_EMBED_UTIL_H
#define PHC_EMBED_UTIL_H

#include <assert.h>

#if HAVE_EMBED

AST::Literal* zval_to_ast_literal (zval* value);
HIR::Literal* zval_to_hir_literal (zval* value);
MIR::Literal* zval_to_mir_literal (zval* value);

/* Wrap eval_string, trapping errors and warnings. Eval CODE with the PHP
 * interpreter, catch and warn in the case of errors, using ANCHOR's filename
 * and line number, then return true/false for success/failure.
 */
bool eval_string (String* code, zval* result, IR::Node* anchor);


#endif // HAVE_EMBED


#endif // PHC_EMBED_UTIL_H
