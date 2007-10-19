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

using namespace AST;

class Goto_uppering : public AST_visitor
{
private:
	AST_variable *next;
	Token_string *start;
	Token_string *end;
	AST_switch *switching;

public:
	Goto_uppering ();

	List<AST_statement*>* convert_statement_list (List<AST_statement*> *in);
	
	void pre_php_script (AST_php_script *in);
	void pre_method (AST_method *in);
	void post_php_script (AST_php_script* in);
};

#endif // PHC_GOTO_UPPERING_H
