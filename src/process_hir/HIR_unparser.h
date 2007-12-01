/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"
#include "process_ir/PHP_unparser.h"

class HIR_unparser : public virtual HIR::Visitor, public virtual PHP_unparser
{
// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	HIR_unparser(ostream& os = cout);

// Unparsing
public:
	void children_php_script(HIR::PHP_script* in);
	void children_interface_def(HIR::Interface_def* in);
	void children_class_def(HIR::Class_def* in);
	void children_class_mod(HIR::Class_mod* in);
	void children_method(HIR::Method* in);
	void children_signature(HIR::Signature* in);
	void children_method_mod(HIR::Method_mod* in);
	void children_formal_parameter(HIR::Formal_parameter* in);
	void children_type(HIR::Type* in);
	void children_attribute(HIR::Attribute* in);
	void children_attr_mod(HIR::Attr_mod* in);
	void children_return(HIR::Return* in);
	void children_static_declaration(HIR::Static_declaration* in);
	void children_global(HIR::Global* in);
	void children_try(HIR::Try* in);
	void children_catch(HIR::Catch* in);
	void post_catch_chain(HIR::Catch* in);
	void children_throw(HIR::Throw* in);
	void children_eval_expr(HIR::Eval_expr* in);
	void children_assignment(HIR::Assignment* in);
	void children_cast(HIR::Cast* in);
	void children_unary_op(HIR::Unary_op* in);
	void children_bin_op(HIR::Bin_op* in);
	void children_constant(HIR::Constant* in);
	void children_instanceof(HIR::Instanceof* in);
	void children_variable(HIR::Variable* in);
	void children_reflection(HIR::Reflection* in);
	void children_pre_op(HIR::Pre_op* in);
	void children_array(HIR::Array* in);
	void children_array_elem(HIR::Array_elem* in);
	void children_method_invocation(HIR::Method_invocation* in);
	void children_actual_parameter(HIR::Actual_parameter* in);
	void children_new(HIR::New* in);
	void children_branch (HIR::Branch* in);
	void children_goto(HIR::Goto* in);
	void children_label(HIR::Label* in);
	void children_name_with_default(HIR::Name_with_default* in);

	void children_interface_name(HIR::INTERFACE_NAME* in);
	void children_class_name(HIR::CLASS_NAME* in);
	void children_method_name(HIR::METHOD_NAME* in);
	void children_variable_name(HIR::VARIABLE_NAME* in);
	void children_cast(HIR::CAST* in);
	void children_op(HIR::OP* in);
	void children_constant_name(HIR::CONSTANT_NAME* in);
	void children_int(HIR::INT* in);
	void children_real(HIR::REAL* in);
	void children_string(HIR::STRING* in);
	void children_bool(HIR::BOOL* in);
	void children_nil(HIR::NIL* in);
	void children_label_name(HIR::LABEL_NAME* in);
	
	void visit_interface_name_list(List<HIR::INTERFACE_NAME*>* in);
	void visit_member_list(List<HIR::Member*>* in);
	void visit_statement_list(List<HIR::Statement*>* in);
	void visit_formal_parameter_list(List<HIR::Formal_parameter*>* in);
	void visit_catch_list(List<HIR::Catch*>* in);
	void visit_expr_list(List<HIR::Expr*>* in);
	void visit_array_elem_list(List<HIR::Array_elem*>* in);
	void visit_actual_parameter_list(List<HIR::Actual_parameter*>* in);
	void visit_name_with_default_list(List<HIR::Name_with_default*>* in);

	void pre_node(HIR::Node* in);
	void pre_expr(HIR::Expr* in);
	void post_expr(HIR::Expr* in);

	void pre_variable (HIR::Variable* in);
	void pre_method_invocation (HIR::Method_invocation* in);
	void pre_global (HIR::Global* in);
};

#endif // PHC_HIR_UNPARSER 
