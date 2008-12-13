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
	void children_statement_list (LIR::Statement_list* in);
	void children_if (LIR::If* in);
	void children_equals (LIR::Equals* in);
	void children_not_equals (LIR::Not_equals* in);
	void children_zvp (LIR::ZVP* in);
	void children_zvpp (LIR::ZVPP* in);
	void children_deref (LIR::Deref* in);
	void children_ref (LIR::Ref* in);


};

#endif // PHC_LIR_UNPARSER 
