/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap visitors for the pass queue.
 */

#ifndef PHC_VISITOR_PASS_H
#define PHC_VISITOR_PASS_H

#include "AST_visitor.h"
#include "HIR_visitor.h"

// TODO generic visitors, not AST viistors
class Visitor_pass : public Pass
{
	AST::Visitor* ast_visitor;
	HIR::Visitor* hir_visitor;

public:

	Visitor_pass (AST::Visitor* v)
	{
		ast_visitor = v;
		hir_visitor = NULL;
	}

	Visitor_pass (HIR::Visitor* v)
	{
		ast_visitor = NULL;
		hir_visitor = v;
	}

	void run (IR* in, Pass_manager* pm)
	{
		if (in->ast)
		{
			assert (ast_visitor);
			assert (hir_visitor == NULL);
			in->ast->visit (ast_visitor);
		}
		else
		{
			assert (in->hir);
			assert (ast_visitor == NULL);
			assert (hir_visitor);
			in->hir->visit (hir_visitor);
		}
	}
};

#endif // PHC_VISITOR_PASS_H
