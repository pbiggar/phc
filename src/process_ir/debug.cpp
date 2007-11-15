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

/* Dump the XML for anynode to stderr. A global function. */
// these are split so they're easy to call from the debugger

void debug (AST::AST_node *in)
{
	static AST_unparser *pup = new AST_unparser (cerr);
	in->visit (pup);
}

void xdebug (AST::AST_node* in)
{
	AST_XML_unparser *xup = new AST_XML_unparser (cerr, false);
	in->visit (xup);
}

void xadebug (AST::AST_node* in)
{
	AST_XML_unparser *xup = new AST_XML_unparser (cerr, true);
	in->visit (xup);
}


void debug (HIR::HIR_node *in)
{
	static HIR_unparser *pup = new HIR_unparser (cerr);
	in->visit (pup);
}

void xdebug (HIR::HIR_node* in)
{
	HIR_XML_unparser *xup = new HIR_XML_unparser (cerr, false);
	in->visit (xup);
}

void xadebug (HIR::HIR_node* in)
{
	HIR_XML_unparser *xup = new HIR_XML_unparser (cerr, true);
	in->visit (xup);
}
