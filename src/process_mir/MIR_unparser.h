/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax
 */

#ifndef PHC_MIR_UNPARSER
#define PHC_MIR_UNPARSER

#include "MIR_visitor.h"
#include "process_ast/AST_unparser.h"


class MIR_unparser : public virtual MIR::Visitor
{
protected:
	AST_unparser ast_unparser;
	MIR::Node* entry_node;

public:
	MIR_unparser(ostream& os = cout, bool in_php = false);
	void pre_node (MIR::Node* in);
	void post_node (MIR::Node* in);
};

#endif // PHC_MIR_UNPARSER 
