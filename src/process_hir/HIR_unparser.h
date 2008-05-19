/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR.h"
#include "process_ast/AST_unparser.h"

class HIR_unparser
{
public:
	HIR_unparser(ostream& os = cout, bool in_php = false);
	void unparse (IR::Node* in);

protected:
	AST_unparser ast_unparser;
};

#endif // PHC_HIR_UNPARSER 
