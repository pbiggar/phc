/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check there are no gotos or labels left.
 */

#ifndef PHC_CHECK_UPPERING_H
#define PHC_CHECK_UPPERING_H

#include "AST_visitor.h"

class Check_uppering : public AST_visitor
{
	public:
		void post_goto (AST_goto* in);
		void post_label (AST_label* in);
};

#endif // PHC_CHECK_UPPERING_H
