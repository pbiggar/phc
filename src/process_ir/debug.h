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

#include "AST.h"
#include "HIR.h"
#include "MIR.h"
#include "LIR.h"
#include <ostream>

#define CHECK_DEBUG() if (!debugging_enabled) return;
#define DEBUG(A) do { if (debugging_enabled) { cdebug << A << std::endl; } } while (0)

extern bool debugging_enabled;

/* Dump the XML for anynode to stderr. A global function. */
// TODO: These are split so they're easy to call from the debugger. But that
// doesn't seem to work in gdb.
void debug (AST::Node* in);
void xdebug (AST::Node* in);
void xadebug (AST::Node* in);

void debug (HIR::Node* in);
void xdebug (HIR::Node* in);
void xadebug (HIR::Node* in);

void debug (MIR::Node* in);
void xdebug (MIR::Node* in);
void xadebug (MIR::Node* in);

void debug (LIR::Node* in);
void xdebug (LIR::Node* in);
void xadebug (LIR::Node* in);


extern std::ostream& cdebug;
void enable_cdebug ();
void disable_cdebug ();

#endif // PHC_DEBUG
