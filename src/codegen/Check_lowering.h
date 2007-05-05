/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that there are no nodes in the AST which should have been
 * lowered.
 */

#ifndef PHC_CHECK_LOWERING_H
#define PHC_CHECK_LOWERING_H

#include "AST_visitor.h"

class Check_lowering : public AST_visitor
{
	public:
		void post_while(AST_while* in);
		void post_do(AST_do* in);
		void post_for(AST_for* in);
		void post_foreach(AST_foreach* in);
		void post_switch(AST_switch* in);
		void post_if(AST_if* in);
		void post_break(AST_break* in);
		void post_continue(AST_continue* in);
};

#endif // PHC_CHECK_LOWERING_H
