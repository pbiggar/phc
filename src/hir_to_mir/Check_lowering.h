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

class Check_lowering : public AST::Visitor
{
	public:
		void post_while(AST::While* in);
		void post_do(AST::Do* in);
		void post_for(AST::For* in);
		void post_foreach(AST::Foreach* in);
		void post_switch(AST::Switch* in);
		void post_if(AST::If* in);
		void post_break(AST::Break* in);
		void post_continue(AST::Continue* in);
		void post_conditional_expr (AST::Conditional_expr* in);
		void post_bin_op (AST::Bin_op* in);
};

#endif // PHC_CHECK_LOWERING_H
