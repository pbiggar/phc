/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate nodes so they can be correctly shredded.
 */

#ifndef PHC_ANNOTATE_H
#define PHC_ANNOTATE_H

#include "AST_visitor.h"

class Annotate : public AST::AST_visitor
{
	// only generate array elements if this is set
	bool generate_array_temps;
	bool return_by_ref;

public:

	Annotate();
	void pre_node(AST::AST_node* in);
	void pre_assignment(AST::AST_assignment* in);
	void pre_op_assignment(AST::AST_op_assignment* in);
	void pre_post_op (AST::AST_post_op* in);
	void pre_pre_op (AST::AST_pre_op* in);
	void pre_attribute(AST::AST_attribute* in);
	void post_attribute(AST::AST_attribute* in);
	void pre_array_elem (AST::AST_array_elem* in);
	void pre_static_declaration(AST::AST_static_declaration* in);
	void post_static_declaration(AST::AST_static_declaration* in);
	void pre_directive (AST::AST_directive* in);
	void pre_formal_parameter (AST::AST_formal_parameter* in);
	void post_formal_parameter (AST::AST_formal_parameter* in);
	void pre_name_with_default (AST::AST_name_with_default* in);
	void pre_method (AST::AST_method* in);
	void post_method (AST::AST_method* in);
	void post_return (AST::AST_return* in);
	void post_method_invocation (AST::AST_method_invocation* in);
	void pre_eval_expr (AST::AST_eval_expr* in);
};

#endif // PHC_ANNOTATE_H
