/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate nodes so they can be correctly shredded.
 */

#ifndef PHC_HIR_ANNOTATE_H
#define PHC_HIR_ANNOTATE_H

#include "HIR_visitor.h"

namespace HIR
{
	class Annotate : public HIR::Visitor
	{
		// only generate array elements if this is set
		bool generate_array_temps;
		bool return_by_ref;

	public:

		Annotate();
		void pre_node(HIR::Node* in);
		void pre_assignment(HIR::Assignment* in);
		void pre_op_assignment(HIR::Op_assignment* in);
		void pre_pre_op (HIR::Pre_op* in);
		void pre_attribute(HIR::Attribute* in);
		void post_attribute(HIR::Attribute* in);
		void pre_array_elem (HIR::Array_elem* in);
		void pre_static_declaration(HIR::Static_declaration* in);
		void post_static_declaration(HIR::Static_declaration* in);
		void pre_formal_parameter (HIR::Formal_parameter* in);
		void post_formal_parameter (HIR::Formal_parameter* in);
		void pre_name_with_default (HIR::Name_with_default* in);
		void pre_method (HIR::Method* in);
		void post_method (HIR::Method* in);
		void post_return (HIR::Return* in);
		void post_method_invocation (HIR::Method_invocation* in);
		void pre_eval_expr (HIR::Eval_expr* in);
		void pre_break (HIR::Break* in);
	};
}

#endif // PHC_HIR_ANNOTATE_H
