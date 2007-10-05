/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Translate the shredded and lowered AST to HIR 
 */

#ifndef PHC_AST_TO_HIR_H
#define PHC_AST_TO_HIR_H

#include "AST_fold.h"
#include "HIR.h"

class AST_to_HIR : public AST::AST_fold
<HIR::HIR_node*,
 HIR::HIR_php_script*,
 HIR::HIR_statement*,
 HIR::HIR_class_def*,
 HIR::HIR_class_mod*,
 HIR::HIR_interface_def*,
 HIR::HIR_member*,
 HIR::HIR_method*,
 HIR::HIR_signature*,
 HIR::HIR_method_mod*,
 HIR::HIR_formal_parameter*,
 HIR::HIR_type*,
 HIR::HIR_attribute*,
 HIR::HIR_attr_mod*,
 HIR::HIR_if*,
 HIR::HIR_while*,
 HIR::HIR_do*,
 HIR::HIR_for*,
 HIR::HIR_foreach*,
 HIR::HIR_switch*,
 HIR::HIR_switch_case*,
 HIR::HIR_break*,
 HIR::HIR_continue*,
 HIR::HIR_return*,
 HIR::HIR_static_declaration*,
 HIR::HIR_global*,
 HIR::HIR_declare*,
 HIR::HIR_directive*,
 HIR::HIR_try*,
 HIR::HIR_catch*,
 HIR::HIR_throw*,
 HIR::HIR_eval_expr*,
 HIR::HIR_nop*,
 HIR::HIR_branch*,
 HIR::HIR_goto*,
 HIR::HIR_label*,
 HIR::HIR_expr*,
 HIR::HIR_literal*,
 HIR::HIR_assignment*,
 HIR::HIR_op_assignment*,
 HIR::HIR_list_assignment*,
 HIR::HIR_list_element*,
 HIR::HIR_nested_list_elements*,
 HIR::HIR_cast*,
 HIR::HIR_unary_op*,
 HIR::HIR_bin_op*,
 HIR::HIR_conditional_expr*,
 HIR::HIR_ignore_errors*,
 HIR::HIR_constant*,
 HIR::HIR_instanceof*,
 HIR::HIR_variable*,
 HIR::HIR_variable_name*,
 HIR::HIR_reflection*,
 HIR::HIR_target*,
 HIR::HIR_pre_op*,
 HIR::HIR_post_op*,
 HIR::HIR_array*,
 HIR::HIR_array_elem*,
 HIR::HIR_method_invocation*,
 HIR::HIR_method_name*,
 HIR::HIR_actual_parameter*,
 HIR::HIR_new*,
 HIR::HIR_class_name*,
 HIR::HIR_commented_node*,
 HIR::HIR_identifier*,
 HIR::Token_class_name*,
 HIR::Token_interface_name*,
 HIR::Token_method_name*,
 HIR::Token_variable_name*,
 HIR::Token_directive_name*,
 HIR::Token_label_name*,
 HIR::Token_int*,
 HIR::Token_real*,
 HIR::Token_string*,
 HIR::Token_bool*,
 HIR::Token_null*,
 HIR::Token_op*,
 HIR::Token_cast*,
 HIR::Token_constant_name*>
{
	HIR::HIR_php_script* fold_impl_php_script(AST::AST_php_script* orig, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_php_script* result;
		result = new HIR::HIR_php_script(statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_class_def* fold_impl_class_def(AST::AST_class_def* orig, HIR::HIR_class_mod* class_mod, HIR::Token_class_name* class_name, HIR::Token_class_name* extends, List<HIR::Token_interface_name*>* implements, List<HIR::HIR_member*>* members) 
	{
		HIR::HIR_class_def* result;
		result = new HIR::HIR_class_def(class_mod, class_name, extends, implements, members);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_class_mod* fold_impl_class_mod(AST::AST_class_mod* orig, bool is_abstract, bool is_final) 
	{
		HIR::HIR_class_mod* result;
		result = new HIR::HIR_class_mod(is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_interface_def* fold_impl_interface_def(AST::AST_interface_def* orig, HIR::Token_interface_name* interface_name, List<HIR::Token_interface_name*>* extends, List<HIR::HIR_member*>* members) 
	{
		HIR::HIR_interface_def* result;
		result = new HIR::HIR_interface_def(interface_name, extends, members);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_method* fold_impl_method(AST::AST_method* orig, HIR::HIR_signature* signature, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_method* result;
		result = new HIR::HIR_method(signature, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_signature* fold_impl_signature(AST::AST_signature* orig, HIR::HIR_method_mod* method_mod, bool is_ref, HIR::Token_method_name* method_name, List<HIR::HIR_formal_parameter*>* formal_parameters) 
	{
		HIR::HIR_signature* result;
		result = new HIR::HIR_signature(method_mod, is_ref, method_name, formal_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_method_mod* fold_impl_method_mod(AST::AST_method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		HIR::HIR_method_mod* result;
		result = new HIR::HIR_method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_formal_parameter* fold_impl_formal_parameter(AST::AST_formal_parameter* orig, HIR::HIR_type* type, bool is_ref, HIR::Token_variable_name* variable_name, HIR::HIR_expr* expr) 
	{
		HIR::HIR_formal_parameter* result;
		result = new HIR::HIR_formal_parameter(type, is_ref, variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_type* fold_impl_type(AST::AST_type* orig, HIR::Token_class_name* class_name) 
	{
		HIR::HIR_type* result;
		result = new HIR::HIR_type(class_name);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_attribute* fold_impl_attribute(AST::AST_attribute* orig, HIR::HIR_attr_mod* attr_mod, HIR::Token_variable_name* variable_name, HIR::HIR_expr* expr) 
	{
		HIR::HIR_attribute* result;
		result = new HIR::HIR_attribute(attr_mod, variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_attr_mod* fold_impl_attr_mod(AST::AST_attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		HIR::HIR_attr_mod* result;
		result = new HIR::HIR_attr_mod(is_public, is_protected, is_private, is_static, is_const);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_if* fold_impl_if(AST::AST_if* orig, HIR::HIR_expr* expr, List<HIR::HIR_statement*>* iftrue, List<HIR::HIR_statement*>* iffalse) 
	{
		HIR::HIR_if* result;
		result = new HIR::HIR_if(expr, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_while* fold_impl_while(AST::AST_while* orig, HIR::HIR_expr* expr, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_while* result;
		result = new HIR::HIR_while(expr, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_do* fold_impl_do(AST::AST_do* orig, List<HIR::HIR_statement*>* statements, HIR::HIR_expr* expr) 
	{
		HIR::HIR_do* result;
		result = new HIR::HIR_do(statements, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_for* fold_impl_for(AST::AST_for* orig, HIR::HIR_expr* init, HIR::HIR_expr* cond, HIR::HIR_expr* incr, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_for* result;
		result = new HIR::HIR_for(init, cond, incr, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_foreach* fold_impl_foreach(AST::AST_foreach* orig, HIR::HIR_expr* expr, HIR::HIR_variable* key, bool is_ref, HIR::HIR_variable* val, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_foreach* result;
		result = new HIR::HIR_foreach(expr, key, is_ref, val, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_switch* fold_impl_switch(AST::AST_switch* orig, HIR::HIR_expr* expr, List<HIR::HIR_switch_case*>* switch_cases) 
	{
		HIR::HIR_switch* result;
		result = new HIR::HIR_switch(expr, switch_cases);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_switch_case* fold_impl_switch_case(AST::AST_switch_case* orig, HIR::HIR_expr* expr, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_switch_case* result;
		result = new HIR::HIR_switch_case(expr, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_break* fold_impl_break(AST::AST_break* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_break* result;
		result = new HIR::HIR_break(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_continue* fold_impl_continue(AST::AST_continue* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_continue* result;
		result = new HIR::HIR_continue(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_return* fold_impl_return(AST::AST_return* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_return* result;
		result = new HIR::HIR_return(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_static_declaration* fold_impl_static_declaration(AST::AST_static_declaration* orig, HIR::Token_variable_name* variable_name, HIR::HIR_expr* expr) 
	{
		HIR::HIR_static_declaration* result;
		result = new HIR::HIR_static_declaration(variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_global* fold_impl_global(AST::AST_global* orig, HIR::HIR_variable_name* variable_name) 
	{
		HIR::HIR_global* result;
		result = new HIR::HIR_global(variable_name);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_declare* fold_impl_declare(AST::AST_declare* orig, List<HIR::HIR_directive*>* directives, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_declare* result;
		result = new HIR::HIR_declare(directives, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_directive* fold_impl_directive(AST::AST_directive* orig, HIR::Token_directive_name* directive_name, HIR::HIR_expr* expr) 
	{
		HIR::HIR_directive* result;
		result = new HIR::HIR_directive(directive_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_try* fold_impl_try(AST::AST_try* orig, List<HIR::HIR_statement*>* statements, List<HIR::HIR_catch*>* catches) 
	{
		HIR::HIR_try* result;
		result = new HIR::HIR_try(statements, catches);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_catch* fold_impl_catch(AST::AST_catch* orig, HIR::Token_class_name* class_name, HIR::Token_variable_name* variable_name, List<HIR::HIR_statement*>* statements) 
	{
		HIR::HIR_catch* result;
		result = new HIR::HIR_catch(class_name, variable_name, statements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_throw* fold_impl_throw(AST::AST_throw* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_throw* result;
		result = new HIR::HIR_throw(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_eval_expr* fold_impl_eval_expr(AST::AST_eval_expr* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_eval_expr* result;
		result = new HIR::HIR_eval_expr(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_nop* fold_impl_nop(AST::AST_nop* orig) 
	{
		HIR::HIR_nop* result;
		result = new HIR::HIR_nop();
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_branch* fold_impl_branch(AST::AST_branch* orig, HIR::HIR_expr* expr, HIR::Token_label_name* iftrue, HIR::Token_label_name* iffalse) 
	{
		HIR::HIR_branch* result;
		result = new HIR::HIR_branch(expr, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_goto* fold_impl_goto(AST::AST_goto* orig, HIR::Token_label_name* label_name) 
	{
		HIR::HIR_goto* result;
		result = new HIR::HIR_goto(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_label* fold_impl_label(AST::AST_label* orig, HIR::Token_label_name* label_name) 
	{
		HIR::HIR_label* result;
		result = new HIR::HIR_label(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_assignment* fold_impl_assignment(AST::AST_assignment* orig, HIR::HIR_variable* variable, bool is_ref, HIR::HIR_expr* expr) 
	{
		HIR::HIR_assignment* result;
		result = new HIR::HIR_assignment(variable, is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_op_assignment* fold_impl_op_assignment(AST::AST_op_assignment* orig, HIR::HIR_variable* variable, HIR::Token_op* op, HIR::HIR_expr* expr) 
	{
		HIR::HIR_op_assignment* result;
		result = new HIR::HIR_op_assignment(variable, op, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_list_assignment* fold_impl_list_assignment(AST::AST_list_assignment* orig, List<HIR::HIR_list_element*>* list_elements, HIR::HIR_expr* expr) 
	{
		HIR::HIR_list_assignment* result;
		result = new HIR::HIR_list_assignment(list_elements, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_nested_list_elements* fold_impl_nested_list_elements(AST::AST_nested_list_elements* orig, List<HIR::HIR_list_element*>* list_elements) 
	{
		HIR::HIR_nested_list_elements* result;
		result = new HIR::HIR_nested_list_elements(list_elements);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_cast* fold_impl_cast(AST::AST_cast* orig, HIR::Token_cast* cast, HIR::HIR_expr* expr) 
	{
		HIR::HIR_cast* result;
		result = new HIR::HIR_cast(cast, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_unary_op* fold_impl_unary_op(AST::AST_unary_op* orig, HIR::Token_op* op, HIR::HIR_expr* expr) 
	{
		HIR::HIR_unary_op* result;
		result = new HIR::HIR_unary_op(op, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_bin_op* fold_impl_bin_op(AST::AST_bin_op* orig, HIR::HIR_expr* left, HIR::Token_op* op, HIR::HIR_expr* right) 
	{
		HIR::HIR_bin_op* result;
		result = new HIR::HIR_bin_op(left, op, right);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_conditional_expr* fold_impl_conditional_expr(AST::AST_conditional_expr* orig, HIR::HIR_expr* cond, HIR::HIR_expr* iftrue, HIR::HIR_expr* iffalse) 
	{
		HIR::HIR_conditional_expr* result;
		result = new HIR::HIR_conditional_expr(cond, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_ignore_errors* fold_impl_ignore_errors(AST::AST_ignore_errors* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_ignore_errors* result;
		result = new HIR::HIR_ignore_errors(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_constant* fold_impl_constant(AST::AST_constant* orig, HIR::Token_class_name* class_name, HIR::Token_constant_name* constant_name) 
	{
		HIR::HIR_constant* result;
		result = new HIR::HIR_constant(class_name, constant_name);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_instanceof* fold_impl_instanceof(AST::AST_instanceof* orig, HIR::HIR_expr* expr, HIR::HIR_class_name* class_name) 
	{
		HIR::HIR_instanceof* result;
		result = new HIR::HIR_instanceof(expr, class_name);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_variable* fold_impl_variable(AST::AST_variable* orig, HIR::HIR_target* target, HIR::HIR_variable_name* variable_name, List<HIR::HIR_expr*>* array_indices) 
	{
		HIR::HIR_variable* result;
		result = new HIR::HIR_variable(target, variable_name, array_indices);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_reflection* fold_impl_reflection(AST::AST_reflection* orig, HIR::HIR_expr* expr) 
	{
		HIR::HIR_reflection* result;
		result = new HIR::HIR_reflection(expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_pre_op* fold_impl_pre_op(AST::AST_pre_op* orig, HIR::Token_op* op, HIR::HIR_variable* variable) 
	{
		HIR::HIR_pre_op* result;
		result = new HIR::HIR_pre_op(op, variable);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_post_op* fold_impl_post_op(AST::AST_post_op* orig, HIR::HIR_variable* variable, HIR::Token_op* op) 
	{
		HIR::HIR_post_op* result;
		result = new HIR::HIR_post_op(variable, op);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_array* fold_impl_array(AST::AST_array* orig, List<HIR::HIR_array_elem*>* array_elems) 
	{
		HIR::HIR_array* result;
		result = new HIR::HIR_array(array_elems);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_array_elem* fold_impl_array_elem(AST::AST_array_elem* orig, HIR::HIR_expr* key, bool is_ref, HIR::HIR_expr* val) 
	{
		HIR::HIR_array_elem* result;
		result = new HIR::HIR_array_elem(key, is_ref, val);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_method_invocation* fold_impl_method_invocation(AST::AST_method_invocation* orig, HIR::HIR_target* target, HIR::HIR_method_name* method_name, List<HIR::HIR_actual_parameter*>* actual_parameters) 
	{
		HIR::HIR_method_invocation* result;
		result = new HIR::HIR_method_invocation(target, method_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_actual_parameter* fold_impl_actual_parameter(AST::AST_actual_parameter* orig, bool is_ref, HIR::HIR_expr* expr) 
	{
		HIR::HIR_actual_parameter* result;
		result = new HIR::HIR_actual_parameter(is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_new* fold_impl_new(AST::AST_new* orig, HIR::HIR_class_name* class_name, List<HIR::HIR_actual_parameter*>* actual_parameters) 
	{
		HIR::HIR_new* result;
		result = new HIR::HIR_new(class_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_class_name* fold_class_name(AST::Token_class_name* orig) 
	{
		HIR::Token_class_name* result;
		result = new HIR::Token_class_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_interface_name* fold_interface_name(AST::Token_interface_name* orig) 
	{
		HIR::Token_interface_name* result;
		result = new HIR::Token_interface_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_method_name* fold_method_name(AST::Token_method_name* orig) 
	{
		HIR::Token_method_name* result;
		result = new HIR::Token_method_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_variable_name* fold_variable_name(AST::Token_variable_name* orig) 
	{
		HIR::Token_variable_name* result;
		result = new HIR::Token_variable_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_directive_name* fold_directive_name(AST::Token_directive_name* orig) 
	{
		HIR::Token_directive_name* result;
		result = new HIR::Token_directive_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_label_name* fold_label_name(AST::Token_label_name* orig) 
	{
		HIR::Token_label_name* result;
		result = new HIR::Token_label_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_int* fold_int(AST::Token_int* orig) 
	{
		HIR::Token_int* result;
		result = new HIR::Token_int(orig->value, orig->source_rep);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_real* fold_real(AST::Token_real* orig) 
	{
		HIR::Token_real* result;
		result = new HIR::Token_real(orig->value, orig->source_rep);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_string* fold_string(AST::Token_string* orig) 
	{
		HIR::Token_string* result;
		result = new HIR::Token_string(orig->value, orig->source_rep);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_bool* fold_bool(AST::Token_bool* orig) 
	{
		HIR::Token_bool* result;
		result = new HIR::Token_bool(orig->value, orig->source_rep);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_null* fold_null(AST::Token_null* orig) 
	{
		HIR::Token_null* result;
		result = new HIR::Token_null(orig->source_rep);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_op* fold_op(AST::Token_op* orig) 
	{
		HIR::Token_op* result;
		result = new HIR::Token_op(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_cast* fold_cast(AST::Token_cast* orig) 
	{
		HIR::Token_cast* result;
		result = new HIR::Token_cast(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	HIR::Token_constant_name* fold_constant_name(AST::Token_constant_name* orig) 
	{
		HIR::Token_constant_name* result;
		result = new HIR::Token_constant_name(orig->value);
		result->attrs = orig->attrs;
		return result;
	}
};

#endif // PHC_AST_TO_HIR_H 
