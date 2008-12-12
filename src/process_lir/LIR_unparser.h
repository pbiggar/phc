/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the LIR to C
 */

#ifndef PHC_LIR_UNPARSER
#define PHC_LIR_UNPARSER

#include "LIR_visitor.h"
#include "process_ir/PHP_unparser.h"

class LIR_unparser : public virtual PHP_unparser, public virtual LIR::Visitor
{
public:
	LIR_unparser (std::ostream& os = std::cout, bool in_php = false);
	LIR_unparser (Unparser_state* ups);

	void unparse (IR::Node* in);

public:

	void post_uninterpreted (LIR::UNINTERPRETED* in);
	void post_code (LIR::CODE* in);
	void children_block (LIR::Block* in);
	void pre_comment (LIR::COMMENT* in);
};

#endif // PHC_LIR_UNPARSER 
