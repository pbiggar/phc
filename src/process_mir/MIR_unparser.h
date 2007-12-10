/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax
 */

#ifndef PHC_MIR_UNPARSER
#define PHC_MIR_UNPARSER

#include "MIR_visitor.h"
#include "process_ir/PHP_unparser.h"

class MIR_unparser : public virtual MIR::Visitor, public virtual PHP_unparser
{
// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	MIR_unparser(ostream& os = cout);

// Unparsing
public:
	void children_php_script(MIR::PHP_script* in);
	void children_interface_def(MIR::Interface_def* in);
	void children_class_def(MIR::Class_def* in);
	void children_class_mod(MIR::Class_mod* in);
	void children_method(MIR::Method* in);
	void children_signature(MIR::Signature* in);
	void children_method_mod(MIR::Method_mod* in);
	void children_formal_parameter(MIR::Formal_parameter* in);
	void children_type(MIR::Type* in);
	void children_attribute(MIR::Attribute* in);
	void children_attr_mod(MIR::Attr_mod* in);
	void children_return(MIR::Return* in);
	void children_static_declaration(MIR::Static_declaration* in);
	void children_global(MIR::Global* in);
	void children_try(MIR::Try* in);
	void children_catch(MIR::Catch* in);
	void post_catch_chain(MIR::Catch* in);
	void children_throw(MIR::Throw* in);
	void children_eval_expr(MIR::Eval_expr* in);
	void children_assignment(MIR::Assignment* in);
	void children_cast(MIR::Cast* in);
	void children_unary_op(MIR::Unary_op* in);
	void children_bin_op(MIR::Bin_op* in);
	void children_constant(MIR::Constant* in);
	void children_instanceof(MIR::Instanceof* in);
	void children_variable(MIR::Variable* in);
	void children_reflection(MIR::Reflection* in);
	void children_pre_op(MIR::Pre_op* in);
	void children_array(MIR::Array* in);
	void children_array_elem(MIR::Array_elem* in);
	void children_method_invocation(MIR::Method_invocation* in);
	void children_actual_parameter(MIR::Actual_parameter* in);
	void children_new(MIR::New* in);
	void children_branch (MIR::Branch* in);
	void children_goto(MIR::Goto* in);
	void children_label(MIR::Label* in);
	void children_name_with_default(MIR::Name_with_default* in);

	void children_interface_name(MIR::INTERFACE_NAME* in);
	void children_class_name(MIR::CLASS_NAME* in);
	void children_method_name(MIR::METHOD_NAME* in);
	void children_variable_name(MIR::VARIABLE_NAME* in);
	void children_cast(MIR::CAST* in);
	void children_op(MIR::OP* in);
	void children_constant_name(MIR::CONSTANT_NAME* in);
	void children_int(MIR::INT* in);
	void children_real(MIR::REAL* in);
	void children_string(MIR::STRING* in);
	void children_bool(MIR::BOOL* in);
	void children_nil(MIR::NIL* in);
	void children_label_name(MIR::LABEL_NAME* in);
	
	void visit_interface_name_list(List<MIR::INTERFACE_NAME*>* in);
	void visit_member_list(List<MIR::Member*>* in);
	void visit_statement_list(List<MIR::Statement*>* in);
	void visit_formal_parameter_list(List<MIR::Formal_parameter*>* in);
	void visit_catch_list(List<MIR::Catch*>* in);
	void visit_expr_list(List<MIR::Expr*>* in);
	void visit_array_elem_list(List<MIR::Array_elem*>* in);
	void visit_actual_parameter_list(List<MIR::Actual_parameter*>* in);
	void visit_name_with_default_list(List<MIR::Name_with_default*>* in);

	void pre_node(MIR::Node* in);
	void pre_expr(MIR::Expr* in);
	void post_expr(MIR::Expr* in);

	void pre_variable (MIR::Variable* in);
	void pre_method_invocation (MIR::Method_invocation* in);
	void pre_global (MIR::Global* in);
};

#endif // PHC_MIR_UNPARSER 
