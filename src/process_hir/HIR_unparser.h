/*
 * phc -- the open source HIR compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to HIR syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"
#include "process_ast/PHP_unparser.h"

using namespace HIR;

void debug (HIR_node* in);

class HIR_unparser : public virtual HIR_visitor, public virtual PHP_unparser
{
// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	HIR_unparser(ostream& os = cout);

// Unparsing
public:
	void children_php_script(HIR_php_script* in);
	void children_interface_def(HIR_interface_def* in);
	void children_class_def(HIR_class_def* in);
	void children_class_mod(HIR_class_mod* in);
	void children_method(HIR_method* in);
	void children_signature(HIR_signature* in);
	void children_method_mod(HIR_method_mod* in);
	void children_formal_parameter(HIR_formal_parameter* in);
	void children_type(HIR_type* in);
	void children_attribute(HIR_attribute* in);
	void children_attr_mod(HIR_attr_mod* in);
	void children_return(HIR_return* in);
	void children_static_declaration(HIR_static_declaration* in);
	void children_global(HIR_global* in);
	void children_try(HIR_try* in);
	void children_catch(HIR_catch* in);
	void post_catch_chain(HIR_catch* in);
	void children_throw(HIR_throw* in);
	void children_eval_expr(HIR_eval_expr* in);
	void children_assignment(HIR_assignment* in);
	void children_cast(HIR_cast* in);
	void children_unary_op(HIR_unary_op* in);
	void children_bin_op(HIR_bin_op* in);
	void children_constant(HIR_constant* in);
	void children_instanceof(HIR_instanceof* in);
	void children_variable(HIR_variable* in);
	void children_reflection(HIR_reflection* in);
	void children_pre_op(HIR_pre_op* in);
	void children_array(HIR_array* in);
	void children_array_elem(HIR_array_elem* in);
	void children_method_invocation(HIR_method_invocation* in);
	void children_actual_parameter(HIR_actual_parameter* in);
	void children_new(HIR_new* in);
	void children_branch (HIR_branch* in);
	void children_goto(HIR_goto* in);
	void children_label(HIR_label* in);
	void children_interface_name(Token_interface_name* in);
	void children_class_name(Token_class_name* in);
	void children_method_name(Token_method_name* in);
	void children_variable_name(Token_variable_name* in);
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
	void visit_member_list(List<HIR_member*>* in);
	void visit_statement_list(List<HIR_statement*>* in);
	void visit_formal_parameter_list(List<HIR_formal_parameter*>* in);
	void visit_catch_list(List<HIR_catch*>* in);
	void visit_expr_list(List<HIR_expr*>* in);
	void visit_array_elem_list(List<HIR_array_elem*>* in);
	void visit_actual_parameter_list(List<HIR_actual_parameter*>* in);

	void pre_node(HIR_node* in);
	void pre_expr(HIR_expr* in);
	void post_expr(HIR_expr* in);

	void pre_variable (HIR_variable* in);
	void pre_method_invocation (HIR_method_invocation* in);
	void pre_global (HIR_global* in);
};

#endif // PHC_HIR_UNPARSER 
