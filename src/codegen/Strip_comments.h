/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Strip all comments from the HIR
 */

#ifndef PHC_STRIP_COMMENTS
#define PHC_STRIP_COMMENTS

#include "HIR_visitor.h"

class Strip_comments : public virtual HIR::Visitor
{
public:
	void pre_commented_node(HIR::Commented_node* in);
};

#endif // PHC_STRIP_COMMENTS
