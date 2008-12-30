/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap visitors for the pass queue.
 */

#ifndef PHC_VISITOR_PASS_H
#define PHC_VISITOR_PASS_H

namespace AST { class Visitor; }
namespace HIR { class Visitor; }
namespace MIR { class Visitor; }

// TODO generic visitors, not AST viistors
class Visitor_pass : public Pass
{
	AST::Visitor* ast_visitor;
	HIR::Visitor* hir_visitor;
	MIR::Visitor* mir_visitor;

public:

	Visitor_pass (AST::Visitor* v, String* name, String* description)
	{
		this->name = name;
		this->description = description;
		ast_visitor = v;
		hir_visitor = NULL;
		mir_visitor = NULL;
	}

	Visitor_pass (HIR::Visitor* v, String* name, String* description)
	{
		this->name = name;
		this->description = description;
		ast_visitor = NULL;
		hir_visitor = v;
		mir_visitor = NULL;
	}

	Visitor_pass (MIR::Visitor* v, String* name, String* description)
	{
		this->name = name;
		this->description = description;
		ast_visitor = NULL;
		hir_visitor = NULL;
		mir_visitor = v;
	}




	void run (IR::PHP_script* in, Pass_manager* pm)
	{
		if (ast_visitor)
			in->visit (ast_visitor);
		else if (hir_visitor)
			in->visit (hir_visitor);
		else
			in->visit (mir_visitor);
	}
};

#endif // PHC_VISITOR_PASS_H
