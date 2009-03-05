/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax
 */

#ifndef PHC_AST_UNPARSER
#define PHC_AST_UNPARSER

#include "AST_visitor.h"
#include "process_ir/PHP_unparser.h"
#include "lib/Stack.h"

class AST_unparser : public virtual AST::Visitor, public virtual PHP_unparser
{
public:
	AST_unparser (std::ostream& os = std::cout, bool in_php = false);
	AST_unparser (Unparser_state* ups);

	void unparse (IR::Node* in);

protected:

public:
	void children_php_script(AST::PHP_script* in);
	void children_interface_def(AST::Interface_def* in);
	void children_class_def(AST::Class_def* in);
	void children_class_mod(AST::Class_mod* in);
	void children_method(AST::Method* in);
	void children_signature(AST::Signature* in);
	void children_method_mod(AST::Method_mod* in);
	void children_formal_parameter(AST::Formal_parameter* in);
	void children_type(AST::Type* in);
	void children_attribute(AST::Attribute* in);
	void children_attr_mod(AST::Attr_mod* in);
	void children_if(AST::If* in);
	void children_while(AST::While* in);
	void children_do(AST::Do* in);
	void children_for(AST::For* in);
	void children_foreach(AST::Foreach* in);
	void children_switch(AST::Switch* in);
	void children_switch_case(AST::Switch_case* in);
	void children_break(AST::Break* in);
	void children_continue(AST::Continue* in);
	void children_return(AST::Return* in);
	void children_static_declaration(AST::Static_declaration* in);
	void children_global(AST::Global* in);
	void children_declare(AST::Declare* in);
	void children_directive(AST::Directive* in);
	void children_try(AST::Try* in);
	void children_catch(AST::Catch* in);
	void post_catch_chain(AST::Catch* in);
	void children_throw(AST::Throw* in);
	void children_eval_expr(AST::Eval_expr* in);
	void children_assignment(AST::Assignment* in);
	void children_op_assignment(AST::Op_assignment* in);
	void children_list_assignment(AST::List_assignment* in);
	void children_cast(AST::Cast* in);
	void children_unary_op(AST::Unary_op* in);
	void children_bin_op(AST::Bin_op* in);
	void children_conditional_expr(AST::Conditional_expr* in);
	void children_ignore_errors(AST::Ignore_errors* in);
	void children_constant(AST::Constant* in);
	void children_instanceof(AST::Instanceof* in);
	void children_variable(AST::Variable* in);
	void children_reflection(AST::Reflection* in);
	void children_pre_op(AST::Pre_op* in);
	void children_post_op(AST::Post_op* in);
	void children_array(AST::Array* in);
	void children_array_elem(AST::Array_elem* in);
	void children_method_invocation(AST::Method_invocation* in);
	void children_actual_parameter(AST::Actual_parameter* in);
	void children_new(AST::New* in);
	void children_nop(AST::Nop* in);
	void children_name_with_default(AST::Name_with_default* in);

	void children_interface_name(AST::INTERFACE_NAME* in);
	void children_class_name(AST::CLASS_NAME* in);
	void children_method_name(AST::METHOD_NAME* in);
	void children_variable_name(AST::VARIABLE_NAME* in);
	void children_directive_name(AST::DIRECTIVE_NAME* in);
	void children_cast(AST::CAST* in);
	void children_op(AST::OP* in);
	void children_constant_name(AST::CONSTANT_NAME* in);
	void children_int(AST::INT* in);
	void children_real(AST::REAL* in);
	void children_string(AST::STRING* in);
	void children_bool(AST::BOOL* in);
	void children_nil(AST::NIL* in);
	void children_foreign(AST::FOREIGN* in);
	void post_expr_chain (AST::Expr* in); // hack for FOREIGN
	
	void visit_interface_name_list(AST::INTERFACE_NAME_list* in);
	void visit_member_list(AST::Member_list* in);
	void visit_statement_list(AST::Statement_list* in);
	void visit_formal_parameter_list(AST::Formal_parameter_list* in);
	void visit_switch_case_list(AST::Switch_case_list* in);
	void visit_directive_list(AST::Directive_list* in);
	void visit_catch_list(AST::Catch_list* in);
	void visit_list_element_list(AST::List_element_list* in);
	void visit_expr_list(AST::Expr_list* in);
	void visit_array_elem_list(AST::Array_elem_list* in);
	void visit_actual_parameter_list(AST::Actual_parameter_list* in);
	void visit_name_with_default_list(AST::Name_with_default_list* in);

	void pre_node(AST::Node* in);
	void pre_bin_op(AST::Bin_op* in);
	void post_bin_op(AST::Bin_op* in);
	void pre_expr(AST::Expr* in);
	void post_expr(AST::Expr* in);
	void pre_commented_node(AST::Commented_node* in);
	void post_commented_node(AST::Commented_node* in);

	void pre_variable (AST::Variable* in);
	void pre_method_invocation (AST::Method_invocation* in);
	void pre_global (AST::Global* in);

// State concerning unparsing in-string syntax
protected:
	Stack<bool> in_string;
	Stack<AST::OP*> last_op;

};

#endif // PHC_AST_UNPARSER 
