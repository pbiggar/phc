/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax
 */

#ifndef PHC_PHP_UNPARSER
#define PHC_PHP_UNPARSER

#include "AST_visitor.h"

void debug (AST_node* in);

class PHP_unparser : public virtual AST_visitor
{
// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	PHP_unparser(ostream& os = cout);

// Unparsing
protected:
	ostream& os;
	int indent_level;
	bool at_start_of_line;

	void echo(const char* str);
	void echo_nl(const char* s);
	void echo(String* str);

	void echo_escaped(string *s);
	void inc_indent();
	void dec_indent();
	void newline();
	void output_tabs();
	void empty_line();
	void space_or_newline();

public:
	void children_php_script(AST_php_script* in);
	void children_interface_def(AST_interface_def* in);
	void children_class_def(AST_class_def* in);
	void children_class_mod(AST_class_mod* in);
	void children_method(AST_method* in);
	void children_signature(AST_signature* in);
	void children_method_mod(AST_method_mod* in);
	void children_formal_parameter(AST_formal_parameter* in);
	void children_type(AST_type* in);
	void children_attribute(AST_attribute* in);
	void children_attr_mod(AST_attr_mod* in);
	void children_if(AST_if* in);
	void children_while(AST_while* in);
	void children_do(AST_do* in);
	void children_for(AST_for* in);
	void children_foreach(AST_foreach* in);
	void children_switch(AST_switch* in);
	void children_switch_case(AST_switch_case* in);
	void children_break(AST_break* in);
	void children_continue(AST_continue* in);
	void children_return(AST_return* in);
	void children_static_declaration(AST_static_declaration* in);
	void children_global(AST_global* in);
	void children_unset(AST_unset* in);
	void children_declare(AST_declare* in);
	void children_directive(AST_directive* in);
	void children_try(AST_try* in);
	void children_catch(AST_catch* in);
	void post_catch_chain(AST_catch* in);
	void children_throw(AST_throw* in);
	void children_eval_expr(AST_eval_expr* in);
	void children_assignment(AST_assignment* in);
	void children_list_assignment(AST_list_assignment* in);
	void children_cast(AST_cast* in);
	void children_unary_op(AST_unary_op* in);
	void children_bin_op(AST_bin_op* in);
	void children_conditional_expr(AST_conditional_expr* in);
	void children_ignore_errors(AST_ignore_errors* in);
	void children_constant(AST_constant* in);
	void children_instanceof(AST_instanceof* in);
	void children_variable(AST_variable* in);
	void children_reflection(AST_reflection* in);
	void children_pre_op(AST_pre_op* in);
	void children_post_op(AST_post_op* in);
	void children_array(AST_array* in);
	void children_array_elem(AST_array_elem* in);
	void children_method_invocation(AST_method_invocation* in);
	void children_actual_parameter(AST_actual_parameter* in);
	void children_new(AST_new* in);
	void children_clone(AST_clone* in);
	void children_branch (AST_branch* in);
	void children_goto(AST_goto* in);
	void children_label(AST_label* in);
	void children_interface_name(Token_interface_name* in);
	void children_class_name(Token_class_name* in);
	void children_method_name(Token_method_name* in);
	void children_variable_name(Token_variable_name* in);
	void children_directive_name(Token_directive_name* in);
	void children_cast(Token_cast* in);
	void children_op(Token_op* in);
	void children_constant_name(Token_constant_name* in);
	void children_int(Token_int* in);
	void children_real(Token_real* in);
	void children_string(Token_string* in);
	void children_bool(Token_bool* in);
	void children_null(Token_null* in);
	void children_label_name(Token_label_name* in);
	
	void visit_interface_name_list(List<Token_interface_name*>* in);
	void visit_member_list(List<AST_member*>* in);
	void visit_statement_list(List<AST_statement*>* in);
	void visit_formal_parameter_list(List<AST_formal_parameter*>* in);
	void visit_switch_case_list(List<AST_switch_case*>* in);
	void visit_directive_list(List<AST_directive*>* in);
	void visit_catch_list(List<AST_catch*>* in);
	void visit_list_element_list(List<AST_list_element*>* in);
	void visit_expr_list(List<AST_expr*>* in);
	void visit_array_elem_list(List<AST_array_elem*>* in);
	void visit_actual_parameter_list(List<AST_actual_parameter*>* in);

	void pre_node(AST_node* in);
	void pre_expr(AST_expr* in);
	void post_expr(AST_expr* in);
	void pre_commented_node(AST_commented_node* in);
	void post_commented_node(AST_commented_node* in);
};

#endif // PHC_PHP_UNPARSER 
