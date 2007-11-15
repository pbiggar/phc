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
#include <stack>


class AST_unparser : public virtual AST::AST_visitor, public virtual PHP_unparser
{

public:
	AST_unparser(ostream& os = cout);

public:
	void children_php_script(AST::AST_php_script* in);
	void children_interface_def(AST::AST_interface_def* in);
	void children_class_def(AST::AST_class_def* in);
	void children_class_mod(AST::AST_class_mod* in);
	void children_method(AST::AST_method* in);
	void children_signature(AST::AST_signature* in);
	void children_method_mod(AST::AST_method_mod* in);
	void children_formal_parameter(AST::AST_formal_parameter* in);
	void children_type(AST::AST_type* in);
	void children_attribute(AST::AST_attribute* in);
	void children_attr_mod(AST::AST_attr_mod* in);
	void children_if(AST::AST_if* in);
	void children_while(AST::AST_while* in);
	void children_do(AST::AST_do* in);
	void children_for(AST::AST_for* in);
	void children_foreach(AST::AST_foreach* in);
	void children_switch(AST::AST_switch* in);
	void children_switch_case(AST::AST_switch_case* in);
	void children_break(AST::AST_break* in);
	void children_continue(AST::AST_continue* in);
	void children_return(AST::AST_return* in);
	void children_static_declaration(AST::AST_static_declaration* in);
	void children_global(AST::AST_global* in);
	void children_declare(AST::AST_declare* in);
	void children_directive(AST::AST_directive* in);
	void children_try(AST::AST_try* in);
	void children_catch(AST::AST_catch* in);
	void post_catch_chain(AST::AST_catch* in);
	void children_throw(AST::AST_throw* in);
	void children_eval_expr(AST::AST_eval_expr* in);
	void children_assignment(AST::AST_assignment* in);
	void children_op_assignment(AST::AST_op_assignment* in);
	void children_list_assignment(AST::AST_list_assignment* in);
	void children_cast(AST::AST_cast* in);
	void children_unary_op(AST::AST_unary_op* in);
	void children_bin_op(AST::AST_bin_op* in);
	void children_conditional_expr(AST::AST_conditional_expr* in);
	void children_ignore_errors(AST::AST_ignore_errors* in);
	void children_constant(AST::AST_constant* in);
	void children_instanceof(AST::AST_instanceof* in);
	void children_variable(AST::AST_variable* in);
	void children_reflection(AST::AST_reflection* in);
	void children_pre_op(AST::AST_pre_op* in);
	void children_post_op(AST::AST_post_op* in);
	void children_array(AST::AST_array* in);
	void children_array_elem(AST::AST_array_elem* in);
	void children_method_invocation(AST::AST_method_invocation* in);
	void children_actual_parameter(AST::AST_actual_parameter* in);
	void children_new(AST::AST_new* in);
	void children_branch (AST::AST_branch* in);
	void children_goto(AST::AST_goto* in);
	void children_label(AST::AST_label* in);
	void children_nop(AST::AST_nop* in);
	void children_name_with_default(AST::AST_name_with_default* in);

	void children_interface_name(AST::Token_interface_name* in);
	void children_class_name(AST::Token_class_name* in);
	void children_method_name(AST::Token_method_name* in);
	void children_variable_name(AST::Token_variable_name* in);
	void children_directive_name(AST::Token_directive_name* in);
	void children_cast(AST::Token_cast* in);
	void children_op(AST::Token_op* in);
	void children_constant_name(AST::Token_constant_name* in);
	void children_int(AST::Token_int* in);
	void children_real(AST::Token_real* in);
	void children_string(AST::Token_string* in);
	void children_bool(AST::Token_bool* in);
	void children_null(AST::Token_null* in);
	void children_label_name(AST::Token_label_name* in);
	
	void visit_interface_name_list(List<AST::Token_interface_name*>* in);
	void visit_member_list(List<AST::AST_member*>* in);
	void visit_statement_list(List<AST::AST_statement*>* in);
	void visit_formal_parameter_list(List<AST::AST_formal_parameter*>* in);
	void visit_switch_case_list(List<AST::AST_switch_case*>* in);
	void visit_directive_list(List<AST::AST_directive*>* in);
	void visit_catch_list(List<AST::AST_catch*>* in);
	void visit_list_element_list(List<AST::AST_list_element*>* in);
	void visit_expr_list(List<AST::AST_expr*>* in);
	void visit_array_elem_list(List<AST::AST_array_elem*>* in);
	void visit_actual_parameter_list(List<AST::AST_actual_parameter*>* in);
	void visit_name_with_default_list(List<AST::AST_name_with_default*>* in);

	void pre_node(AST::AST_node* in);
	void pre_expr(AST::AST_expr* in);
	void post_expr(AST::AST_expr* in);
	void pre_commented_node(AST::AST_commented_node* in);
	void post_commented_node(AST::AST_commented_node* in);

	void pre_variable (AST::AST_variable* in);
	void pre_method_invocation (AST::AST_method_invocation* in);
	void pre_global (AST::AST_global* in);

// State concerning unparsing in-string syntax
protected:
	stack<bool> in_string;
	stack<AST::Token_op*> last_op;
};

#endif // PHC_AST_UNPARSER 
