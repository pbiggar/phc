/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience debugging functions.
 */

#include "process_ir/debug.h"
#include "process_ir/XML_unparser.h"

/* Dump the XML for anynode to stderr. A global function. */
// these are split so they're easy to call from the debugger
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
