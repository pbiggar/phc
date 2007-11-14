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


class Goto_uppering : public AST::AST_visitor
{
private:
	AST::AST_variable *next;
	AST::Token_string *start;
	AST::Token_string *end;
	AST::AST_switch *switching;

public:
	Goto_uppering ();

	List<AST::AST_statement*>* convert_statement_list (List<AST::AST_statement*> *in);
	
	void pre_php_script (AST::AST_php_script *in);
	void pre_method (AST::AST_method *in);
	void post_php_script (AST::AST_php_script* in);
};

#endif // PHC_GOTO_UPPERING_H
