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
#include "process_mir/MIR_unparser.h"

class HIR_unparser : public virtual PHP_unparser, public virtual HIR::Visitor
{
public:
	HIR_unparser (ostream& os = cout, bool in_php = false);
	HIR_unparser (Unparser_state* ups);

	void unparse (IR::Node* in);
	void unparse_foreign (IR::Node* in);

	void pre_foreign(HIR::Foreign* in);

protected:
	AST_unparser* ast_unparser;
	MIR_unparser* mir_unparser;
};

#endif // PHC_HIR_UNPARSER 
