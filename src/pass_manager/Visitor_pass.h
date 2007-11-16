/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap visitors for the pass queue.
 */

#ifndef PHC_VISITOR_PASS_H
#define PHC_VISITOR_PASS_H

#include "AST_visitor.h"

// TODO generic visitors, not AST viistors
class AST_visitor_pass : public Pass
{
	AST::AST_visitor* visitor;

public:

	AST_visitor_pass (AST::AST_visitor* v)
	{
		visitor = v;
	}

	void run (AST::AST_php_script* in, Pass_manager* pm)
	{
		in->visit (visitor);
	}
};

#endif // PHC_VISITOR_PASS_H
