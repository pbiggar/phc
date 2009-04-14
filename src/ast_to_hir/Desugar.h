/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#ifndef PHC_DESUGAR_H
#define PHC_DESUGAR_H

#include "AST_transform.h"

class Desugar : public AST::Transform, virtual public GC_obj
{
	AST::CLASS_NAME* current_class;
	AST::CLASS_NAME* parent_class;
	AST::INTERFACE_NAME* current_interface;

	AST::Expr* pre_unary_op(AST::Unary_op* in);
	void pre_declare (AST::Declare*, AST::Statement_list*);
	void pre_nop(AST::Nop*, AST::Statement_list*);
	void pre_return(AST::Return*, AST::Statement_list*);

	AST::OP* pre_op (AST::OP* in);
	AST::CAST* pre_cast (AST::CAST* in);

   void pre_method (AST::Method* in, AST::Method_list* out);
	AST::METHOD_NAME* pre_method_name (AST::METHOD_NAME* in);

	AST::Expr* pre_constant (AST::Constant* in);
   void pre_class_def (AST::Class_def* in, AST::Statement_list* out);
	AST::CLASS_NAME* pre_class_name (AST::CLASS_NAME* in);

   void pre_interface (AST::Interface_def* in, AST::Statement_list* out);
	AST::INTERFACE_NAME* pre_interface_name (AST::INTERFACE_NAME* in);
};

#endif // PHC_DESUGAR_H
