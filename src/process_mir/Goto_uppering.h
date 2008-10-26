/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert goto statements, branches and labels into a FSM, which will consist
 * of a while loop, a switch statement, a state variable, and a lot of
 * continues.
 */

#ifndef PHC_GOTO_UPPERING
#define PHC_GOTO_UPPERING

#include "MIR_visitor.h"
#include "AST.h"

class Goto_uppering : public MIR::Visitor, virtual public GC_obj
{
private:
	AST::Variable* ast_next;
	MIR::VARIABLE_NAME* next;
	AST::Switch* switching;

public:
	Goto_uppering ();

	MIR::Statement_list* convert_statement_list (MIR::Statement_list *in);
	
	void pre_php_script (MIR::PHP_script* in);
	void pre_method (MIR::Method *in);
};

#endif // PHC_GOTO_UPPERING
