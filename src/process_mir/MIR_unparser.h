/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax
 */

#ifndef PHC_MIR_UNPARSER
#define PHC_MIR_UNPARSER

#include "MIR.h"
#include "process_ast/AST_unparser.h"

class MIR_unparser
{
public:
	MIR_unparser(ostream& os = cout, bool in_php = false);
	void unparse (IR::Node* in);

protected:
	AST_unparser ast_unparser;
};

#endif // PHC_MIR_UNPARSER 
