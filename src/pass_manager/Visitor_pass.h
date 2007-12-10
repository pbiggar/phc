/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap visitors for the pass queue.
 */

#ifndef PHC_VISITOR_PASS_H
#define PHC_VISITOR_PASS_H

#include "AST_visitor.h"
#include "MIR_visitor.h"

// TODO generic visitors, not AST viistors
class Visitor_pass : public Pass
{
	AST::Visitor* ast_visitor;
	MIR::Visitor* mir_visitor;

public:

	Visitor_pass (AST::Visitor* v, String* name)
	{
		this->name = name;
		ast_visitor = v;
		mir_visitor = NULL;
	}

	Visitor_pass (MIR::Visitor* v, String* name)
	{
		this->name = name;
		ast_visitor = NULL;
		mir_visitor = v;
	}

	void run (IR* in, Pass_manager* pm)
	{
		if(ast_visitor != NULL)
			in->visit(ast_visitor);
		else
			in->visit(mir_visitor);
	}
};

#endif // PHC_VISITOR_PASS_H
