/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower AST constructs into simpler constructs which are still PHP.
 */

#ifndef PHC_EARLY_LOWER_CONTROL_FLOW_H
#define PHC_EARLY_LOWER_CONTROL_FLOW_H

#include "ast_to_hir/AST_lower_expr.h"
#include "AST_transform.h"

class Early_lower_control_flow : public AST::Transform
{
	public:

		void post_foreach (AST::Foreach* in, List<AST::Statement*>* out);
		void post_for (AST::For*, List<AST::Statement*>*);
		void post_do (AST::Do*, List<AST::Statement*>*);
		void post_while (AST::While* in, List<AST::Statement*>* out);
		void pre_switch(AST::Switch* in, List<AST::Statement*>* out);

};

#endif // PHC_EARLY_LOWER_CONTROL_FLOW_H
