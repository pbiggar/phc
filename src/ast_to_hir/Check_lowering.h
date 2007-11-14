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

class Check_lowering : public AST::AST_visitor
{
	public:
		void post_while(AST::AST_while* in);
		void post_do(AST::AST_do* in);
		void post_for(AST::AST_for* in);
		void post_foreach(AST::AST_foreach* in);
		void post_switch(AST::AST_switch* in);
		void post_if(AST::AST_if* in);
		void post_break(AST::AST_break* in);
		void post_continue(AST::AST_continue* in);
		void post_conditional_expr (AST::AST_conditional_expr* in);
		void post_bin_op (AST::AST_bin_op* in);
};

#endif // PHC_CHECK_LOWERING_H
