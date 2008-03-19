/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Strip all comments from the AST
 */

#ifndef PHC_STRIP_COMMENTS
#define PHC_STRIP_COMMENTS

#include "AST_visitor.h"

class Strip_comments : public virtual AST::Visitor
{
public:
	void pre_commented_node(AST::Commented_node* in);
};

#endif // PHC_STRIP_COMMENTS
