/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience debugging functions.
 */

#include "process_ir/debug.h"
#include "process_ir/XML_unparser.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"

/* Dump the XML for anynode to stderr. A global function. */
// these are split so they're easy to call from the debugger

void debug (AST::Node *in)
{
	static AST_unparser *pup = new AST_unparser (cdebug);
	pup->unparse (in);
}

void xdebug (AST::Node* in)
{
	AST_XML_unparser *xup = new AST_XML_unparser (cdebug, false);
	in->visit (xup);
}

void xadebug (AST::Node* in)
{
	AST_XML_unparser *xup = new AST_XML_unparser (cdebug, true);
	in->visit (xup);
}

void debug (HIR::Node *in)
{
	static HIR_unparser *pup = new HIR_unparser (cdebug);
	pup->unparse (in);
}

void xdebug (HIR::Node* in)
{
	HIR_XML_unparser *xup = new HIR_XML_unparser (cdebug, false);
	in->visit (xup);
}

void xadebug (HIR::Node* in)
{
	HIR_XML_unparser *xup = new HIR_XML_unparser (cdebug, true);
	in->visit (xup);
}


void debug (MIR::Node *in)
{
	static MIR_unparser *pup = new MIR_unparser (cdebug);
	pup->unparse (in);
}

void xdebug (MIR::Node* in)
{
	MIR_XML_unparser *xup = new MIR_XML_unparser (cdebug, false);
	in->visit (xup);
}

void xadebug (MIR::Node* in)
{
	MIR_XML_unparser *xup = new MIR_XML_unparser (cdebug, true);
	in->visit (xup);
}

// set badbit. This wont print anything into the stream.
ostream cdebug_buffer (0);

// If we initialize to cdebug_buffer, then we won't be able to turn it off once
// it's on.
ostringstream initializer;
ostream& cdebug = initializer;

void enable_cdebug ()
{
	// ceer prints input to console
	cdebug.rdbuf (cerr.rdbuf());
}

void disable_cdebug ()
{
	// cdebug_buffer ignores all input
	cdebug.rdbuf (cdebug_buffer.rdbuf());
}

