/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower AST constructs into simpler constructs which are still PHP.
 */

#ifndef PHC_EARLY_LOWER_CONTROL_FLOW_H
#define PHC_EARLY_LOWER_CONTROL_FLOW_H

#include "HIR_lower_expr.h"

class Early_lower_control_flow : public HIR::Transform
{
	public:
		void post_for (HIR::For*, List<HIR::Statement*>*);
		void post_do (HIR::Do*, List<HIR::Statement*>*);
		void post_while (HIR::While* in, List<HIR::Statement*>* out);

};

#endif // PHC_EARLY_LOWER_CONTROL_FLOW_H
