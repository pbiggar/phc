/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate nodes so they can be correctly shredded.
 */

#ifndef PHC_ANNOTATE_H
#define PHC_ANNOTATE_H

#include "AST_visitor.h"

class Annotate : public AST::Visitor, virtual public GC_obj
{
	// only generate array elements if this is set
	bool generate_array_temps;
	bool return_by_ref;

	public:

	Annotate();
	void pre_assignment(AST::Assignment* in);
	void pre_op_assignment(AST::Op_assignment* in);
	void pre_post_op (AST::Post_op* in);
	void pre_pre_op (AST::Pre_op* in);
	void pre_attribute(AST::Attribute* in);
	void post_attribute(AST::Attribute* in);
	void pre_array_elem (AST::Array_elem* in);
	void pre_static_declaration(AST::Static_declaration* in);
	void post_static_declaration(AST::Static_declaration* in);
	void pre_directive (AST::Directive* in);
	void pre_formal_parameter (AST::Formal_parameter* in);
	void post_formal_parameter (AST::Formal_parameter* in);
	void pre_name_with_default (AST::Name_with_default* in);
	void pre_method (AST::Method* in);
	void post_method (AST::Method* in);
	void post_return (AST::Return* in);
	void post_method_invocation (AST::Method_invocation* in);
	void pre_eval_expr (AST::Eval_expr* in);
	void pre_while (AST::While* in);
	void pre_break (AST::Break* in);
};

#endif // PHC_ANNOTATE_H
