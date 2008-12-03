/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap the embedded PHP run-time - utility functions
 */

#ifndef PHC_EMBED_UTIL_H
#define PHC_EMBED_UTIL_H

#include <assert.h>
#include "AST.h"
#include "HIR.h"
#include "MIR.h"

#if HAVE_EMBED


#include <sapi/embed/php_embed.h>
#include <Zend/zend.h>

AST::Literal* zval_to_ast_literal (zval* value);
HIR::Literal* zval_to_hir_literal (zval* value);
MIR::Literal* zval_to_mir_literal (zval* value);

/* Wrap eval_string, trapping errors and warnings. Eval CODE with the PHP
 * interpreter. If ANCHOR is provided, warn in the case of errors, using
 * ANCHOR's filename and line number. If it is not, errors go to DEBUG.
 * Return true/false for success/failure. If PREPARE is set, execute that
 * first. Because Zend insists on add "return " to the front of every command
 * that needs a return value, you can prepare a variable using PREPARE, then
 * just name the variable in CODE, which returns CODE, but allows arbitrary
 * code to be run in PREPARE.
 */
bool eval_string (String* code, zval* result, IR::Node* anchor = NULL, String* prepare = NULL);


#endif // HAVE_EMBED


#endif // PHC_EMBED_UTIL_H
