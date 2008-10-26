/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower AST constructs into simpler constructs which are still PHP.
 */

#ifndef PHC_EARLY_LOWER_CONTROL_FLOW_H
#define PHC_EARLY_LOWER_CONTROL_FLOW_H

#include "AST_transform.h"

class Early_lower_control_flow : public AST::Transform, virtual public GC_obj
{
public:
	void post_foreach (AST::Foreach* in, AST::Statement_list* out);
	void post_for (AST::For*, AST::Statement_list*);
	void post_do (AST::Do*, AST::Statement_list*);
	void post_while (AST::While* in, AST::Statement_list* out);
	void pre_switch(AST::Switch* in, AST::Statement_list* out);
};

#endif // PHC_EARLY_LOWER_CONTROL_FLOW_H
