/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience debugging functions.
 */

/* XML_unparser takes a while to compile, and its use of
 * templates means it cant be separated. As a result, we want
 * to avoid include XML_unparser everywhere. Instead, we just
 * include this */

#ifndef PHC_DEBUG
#define PHC_DEBUG

#include "generated/HIR.h"

/* Dump the XML for anynode to stderr. A global function. */
// these are split so they're easy to call from the debugger
void debug (AST::AST_node* in);
void xdebug (AST::AST_node* in);
void xadebug (AST::AST_node* in);

void debug (HIR::HIR_node* in);
void xdebug (HIR::HIR_node* in);
void xadebug (HIR::HIR_node* in);

#endif


