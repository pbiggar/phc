/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert goto statements, branches and labels into a FSM, which will consist
 * of a while loop, a switch statement, a state variable, and a lot of
 * continues.
 */

#ifndef PHC_GOTO_UPPERING_H
#define PHC_GOTO_UPPERING_H

#include "MIR_visitor.h"
#include "AST.h"


class Goto_uppering : public MIR::Visitor
{
private:
	AST::Variable* ast_next;
	MIR::VARIABLE_NAME* next;
	AST::Switch* switching;

public:
	Goto_uppering ();

	List<MIR::Statement*>* convert_statement_list (List<MIR::Statement*> *in);
	
	void pre_php_script (MIR::PHP_script *in);
	void pre_method (MIR::Method *in);
	void post_php_script (MIR::PHP_script* in);
};

#endif // PHC_GOTO_UPPERING_H
