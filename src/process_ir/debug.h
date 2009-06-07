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

#include <ostream>
namespace AST { class Node; }
namespace HIR { class Node; }
namespace MIR { class Node; }

#define CHECK_DEBUG() do { if (!debugging_enabled) return;} while (0)
#define DEBUG(A) do { if (debugging_enabled) { cdebug << A << std::endl; } } while (0)

void phc_pause ();

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

extern std::ostream& cdebug;
void enable_cdebug ();
void disable_cdebug ();

#endif // PHC_DEBUG
