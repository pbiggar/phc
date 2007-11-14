/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"
#include "process_ast/PHP_unparser.h"

void debug (HIR::HIR_node* in);

class HIR_unparser : public virtual HIR::HIR_visitor, public virtual PHP_unparser
{
// Constructor; pass in a different ostream to write to a file/string instead
// of standard output
public:
	HIR_unparser(ostream& os = cout);

// Unparsing
public:
	void children_php_script(HIR::HIR_php_script* in);
	void children_interface_def(HIR::HIR_interface_def* in);
	void children_class_def(HIR::HIR_class_def* in);
	void children_class_mod(HIR::HIR_class_mod* in);
	void children_method(HIR::HIR_method* in);
	void children_signature(HIR::HIR_signature* in);
	void children_method_mod(HIR::HIR_method_mod* in);
	void children_formal_parameter(HIR::HIR_formal_parameter* in);
	void children_type(HIR::HIR_type* in);
	void children_attribute(HIR::HIR_attribute* in);
	void children_attr_mod(HIR::HIR_attr_mod* in);
	void children_return(HIR::HIR_return* in);
	void children_static_declaration(HIR::HIR_static_declaration* in);
	void children_global(HIR::HIR_global* in);
	void children_try(HIR::HIR_try* in);
	void children_catch(HIR::HIR_catch* in);
	void post_catch_chain(HIR::HIR_catch* in);
	void children_throw(HIR::HIR_throw* in);
	void children_eval_expr(HIR::HIR_eval_expr* in);
	void children_assignment(HIR::HIR_assignment* in);
	void children_cast(HIR::HIR_cast* in);
	void children_unary_op(HIR::HIR_unary_op* in);
	void children_bin_op(HIR::HIR_bin_op* in);
	void children_constant(HIR::HIR_constant* in);
	void children_instanceof(HIR::HIR_instanceof* in);
	void children_variable(HIR::HIR_variable* in);
	void children_reflection(HIR::HIR_reflection* in);
	void children_pre_op(HIR::HIR_pre_op* in);
	void children_array(HIR::HIR_array* in);
	void children_array_elem(HIR::HIR_array_elem* in);
	void children_method_invocation(HIR::HIR_method_invocation* in);
	void children_actual_parameter(HIR::HIR_actual_parameter* in);
	void children_new(HIR::HIR_new* in);
	void children_branch (HIR::HIR_branch* in);
	void children_goto(HIR::HIR_goto* in);
	void children_label(HIR::HIR_label* in);
	void children_name_with_default(HIR::HIR_name_with_default* in);

	void children_interface_name(HIR::Token_interface_name* in);
	void children_class_name(HIR::Token_class_name* in);
	void children_method_name(HIR::Token_method_name* in);
	void children_variable_name(HIR::Token_variable_name* in);
	void children_cast(HIR::Token_cast* in);
	void children_op(HIR::Token_op* in);
	void children_constant_name(HIR::Token_constant_name* in);
	void children_int(HIR::Token_int* in);
	void children_real(HIR::Token_real* in);
	void children_string(HIR::Token_string* in);
	void children_bool(HIR::Token_bool* in);
	void children_null(HIR::Token_null* in);
	void children_label_name(HIR::Token_label_name* in);
	
	void visit_interface_name_list(List<HIR::Token_interface_name*>* in);
	void visit_member_list(List<HIR::HIR_member*>* in);
	void visit_statement_list(List<HIR::HIR_statement*>* in);
	void visit_formal_parameter_list(List<HIR::HIR_formal_parameter*>* in);
	void visit_catch_list(List<HIR::HIR_catch*>* in);
	void visit_expr_list(List<HIR::HIR_expr*>* in);
	void visit_array_elem_list(List<HIR::HIR_array_elem*>* in);
	void visit_actual_parameter_list(List<HIR::HIR_actual_parameter*>* in);
	void visit_name_with_default_list(List<HIR::HIR_name_with_default*>* in);

	void pre_node(HIR::HIR_node* in);
	void pre_expr(HIR::HIR_expr* in);
	void post_expr(HIR::HIR_expr* in);

	void pre_variable (HIR::HIR_variable* in);
	void pre_method_invocation (HIR::HIR_method_invocation* in);
	void pre_global (HIR::HIR_global* in);
};

#endif // PHC_HIR_UNPARSER 
