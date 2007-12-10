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

#include "AST_visitor.h"


class Goto_uppering : public AST::Visitor
{
private:
	AST::Variable *next;
	AST::STRING *start;
	AST::STRING *end;
	AST::Switch *switching;

public:
	Goto_uppering ();

	List<AST::Statement*>* convert_statement_list (List<AST::Statement*> *in);
	
	void pre_php_script (AST::PHP_script *in);
	void pre_method (AST::Method *in);
	void post_php_script (AST::PHP_script* in);
};

#endif // PHC_GOTO_UPPERING_H
