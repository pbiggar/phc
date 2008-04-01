/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"
#include "process_ast/AST_unparser.h"


class HIR_unparser : public virtual HIR::Visitor
{
protected:
	AST_unparser ast_unparser;
	HIR::Node* entry_node;

public:
	HIR_unparser(ostream& os = cout, bool in_php = false);
	void pre_node (HIR::Node* in);
	void post_node (HIR::Node* in);
};

#endif // PHC_HIR_UNPARSER 
