/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check there are no gotos or labels left.
 */

#ifndef PHC_CHECK_UPPERING_H
#define PHC_CHECK_UPPERING_H

#include "Check_lowering.h"


class Check_uppering : public Check_lowering
{
	public:

		// these statements are removed
		void post_goto (AST::Goto* in);
		void post_label (AST::Label* in);

		// these statements are re-added
		void post_continue (AST::Continue* in);
		void post_switch (AST::Switch* in);
		void post_if (AST::If* in);
		void post_break (AST::Break* in);
		void post_while (AST::While* in);
};

#endif // PHC_CHECK_UPPERING_H
