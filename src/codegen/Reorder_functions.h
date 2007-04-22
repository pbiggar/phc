/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert goto statements, branches and labels into a FSM, which will consist
 * of a while loop, a switch statement, a state variable, and a lot of
 * continues.
 */

#ifndef PHC_REORDER_FUNCTIONS_H
#define PHC_REORDER_FUNCTIONS_H

#include "AST_visitor.h"

class Reorder_functions : public AST_visitor
{
public:

	void pre_php_script (AST_php_script *in);
};

#endif // PHC_REORDER_FUNCTIONS_H
