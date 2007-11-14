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

/*
 * Those AST nodes that should no longer appear in the HIR do not have an
 * implementation in this translation, so that we inherit the default assert(0)
 * implementation from AST_fold. However, to satisfy the typechecker, we must
 * still provide a reasonble type for these nodes. For example, the type we
 * specify for AST_for (which does not have a corresponding HIR construct) is
 * simplify HIR::HIR_statement*. For some constructs, specifying HIR::HIR_node*
 * suffices.
 */
class AST_to_HIR : public AST::AST_fold
<HIR::HIR_node*,				// AST_node*
 HIR::HIR_php_script*,			// AST_php_script*
 HIR::HIR_statement*,			// AST_statement*
 HIR::HIR_class_def*,			// AST_class_def*
 HIR::HIR_class_mod*,			// AST_class_mod*
 HIR::HIR_interface_def*,		// AST_interface_def*
 HIR::HIR_member*,				// AST_member*
 HIR::HIR_method*,				// AST_method*
 HIR::HIR_signature*,			// AST_signature*
 HIR::HIR_method_mod*,			// AST_method_mod*
 HIR::HIR_formal_parameter*,	// AST_formal_parameter*
 HIR::HIR_type*,				// AST_type*
 HIR::HIR_attribute*,			// AST_attribute*
 HIR::HIR_attr_mod*,			// AST_attr_mod*
 HIR::HIR_name_with_default*,	// AST_name_with_default*
 HIR::HIR_statement*,			// AST_if*
 HIR::HIR_statement*,			// AST_while*
 HIR::HIR_statement*,			// AST_do*
 HIR::HIR_statement*,			// AST_for*
 HIR::HIR_statement*,			// AST_foreach*
 HIR::HIR_statement*,			// AST_switch*
 HIR::HIR_node*,				// AST_switch_case*
 HIR::HIR_statement*,			// AST_break*
 HIR::HIR_statement*,			// AST_continue*
 HIR::HIR_return*,				// AST_return*
 HIR::HIR_static_declaration*,	// AST_static_declaration*
 HIR::HIR_global*,				// AST_global*
 HIR::HIR_statement*,			// AST_declare*
 HIR::HIR_node*,				// AST_directive*
 HIR::HIR_try*,					// AST_try*
 HIR::HIR_catch*,				// AST_catch*
 HIR::HIR_throw*,				// AST_throw*
 HIR::HIR_eval_expr*,			// AST_eval_expr*
 HIR::HIR_statement*,			// AST_nop*
 HIR::HIR_branch*,				// AST_branch*
 HIR::HIR_goto*,				// AST_goto*
 HIR::HIR_label*,				// AST_label*
 HIR::HIR_expr*,				// AST_expr*
 HIR::HIR_literal*,				// AST_literal*
 HIR::HIR_assignment*,			// AST_assignment*
 HIR::HIR_expr*,				// AST_op_assignment*
 HIR::HIR_expr*,				// AST_list_assignment*
 HIR::HIR_node*,				// AST_list_element*
 HIR::HIR_node*,				// AST_nested_list_elements*
 HIR::HIR_cast*,				// AST_cast*
 HIR::HIR_unary_op*,			// AST_unary_op*
 HIR::HIR_bin_op*,				// AST_bin_op*
 HIR::HIR_expr*,				// AST_conditional_expr*
 HIR::HIR_expr*,				// AST_ignore_errors*
 HIR::HIR_constant*,			// AST_constant*
 HIR::HIR_instanceof*,			// AST_instanceof*
 HIR::HIR_variable*,			// AST_variable*
 HIR::HIR_variable_name*,		// AST_variable_name*
 HIR::HIR_reflection*,			// AST_reflection*
 HIR::HIR_target*,				// AST_target*
 HIR::HIR_pre_op*,				// AST_pre_op*
 HIR::HIR_expr*,				// AST_post_op*
 HIR::HIR_array*,				// AST_array*
 HIR::HIR_array_elem*,			// AST_array_elem*
 HIR::HIR_method_invocation*,	// AST_method_invocation*
 HIR::HIR_method_name*,			// AST_method_name*
 HIR::HIR_actual_parameter*,	// AST_actual_parameter*
 HIR::HIR_new*,					// AST_new*
 HIR::HIR_class_name*,			// AST_class_name*
 HIR::HIR_node*,				// AST_commented_node*
 HIR::HIR_identifier*,			// AST_identifier*
 HIR::Token_class_name*,		// Token_class_name*
 HIR::Token_interface_name*,	// Token_interface_name*
 HIR::Token_method_name*,		// Token_method_name*
 HIR::Token_variable_name*,		// Token_variable_name*
 HIR::HIR_identifier*,			// Token_directive_name*
 HIR::Token_label_name*,		// Token_label_name*
 HIR::Token_int*,				// Token_int*
 HIR::Token_real*,				// Token_real*
 HIR::Token_string*,			// Token_string*
 HIR::Token_bool*,				// Token_bool*
 HIR::Token_null*,				// Token_null*
 HIR::Token_op*,				// Token_op*
 HIR::Token_cast*,				// Token_cast*
 HIR::Token_constant_name*>		// Token_constant_name*
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

	HIR::HIR_formal_parameter* fold_impl_formal_parameter(AST::AST_formal_parameter* orig, HIR::HIR_type* type, bool is_ref, HIR::HIR_name_with_default* var) 
	{
		HIR::HIR_formal_parameter* result;
		result = new HIR::HIR_formal_parameter(type, is_ref, var);
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

	HIR::HIR_attribute* fold_impl_attribute(AST::AST_attribute* orig, HIR::HIR_attr_mod* attr_mod, List<HIR::HIR_name_with_default*>* vars) 
	{
		assert(vars->size() == 1);

		HIR::HIR_attribute* result;
		result = new HIR::HIR_attribute(attr_mod, vars->front());
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
	
	HIR::HIR_name_with_default* fold_impl_name_with_default(AST::AST_name_with_default* orig, HIR::Token_variable_name* variable_name, HIR::HIR_expr* expr) 
	{ 
		HIR::HIR_name_with_default* result;
		result = new HIR::HIR_name_with_default(variable_name, expr);
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

	HIR::HIR_static_declaration* fold_impl_static_declaration(AST::AST_static_declaration* orig, List<HIR::HIR_name_with_default*>* vars) 
	{
		assert(vars->size() == 1);

		HIR::HIR_static_declaration* result;
		result = new HIR::HIR_static_declaration(vars->front());
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_global* fold_impl_global(AST::AST_global* orig, List<HIR::HIR_variable_name*>* variable_names) 
	{
		// HIR only takes a single variable per global; should be been taken care of in the shredder
		assert(variable_names->size() == 1);
		
		HIR::HIR_global* result;
		result = new HIR::HIR_global(variable_names->front());
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

	HIR::Token_variable_name* var_name_from_expr (HIR::HIR_expr* expr)
	{
		HIR::HIR_variable* var = dynamic_cast<HIR::HIR_variable*> (expr);
		assert (var);
		assert (var->array_indices->size () == 0);
		HIR::HIR_variable_name* var_name = var->variable_name;
		assert (var_name);
		HIR::Token_variable_name* token = dynamic_cast<HIR::Token_variable_name*> (var_name);
		assert (token);
		return token;
	}

	HIR::HIR_cast* fold_impl_cast(AST::AST_cast* orig, HIR::Token_cast* cast, HIR::HIR_expr* expr) 
	{
		HIR::HIR_cast* result;
		result = new HIR::HIR_cast(cast, var_name_from_expr (expr));
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_unary_op* fold_impl_unary_op(AST::AST_unary_op* orig, HIR::Token_op* op, HIR::HIR_expr* expr) 
	{
		HIR::HIR_unary_op* result;
		result = new HIR::HIR_unary_op(op, var_name_from_expr (expr));
		result->attrs = orig->attrs;
		return result;
	}

	HIR::HIR_bin_op* fold_impl_bin_op(AST::AST_bin_op* orig, HIR::HIR_expr* left, HIR::Token_op* op, HIR::HIR_expr* right) 
	{
		HIR::HIR_bin_op* result;
		result = new HIR::HIR_bin_op(var_name_from_expr (left), op, var_name_from_expr (right));
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
		result = new HIR::HIR_instanceof(var_name_from_expr (expr), class_name);
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
		result = new HIR::HIR_reflection(var_name_from_expr (expr));
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

	~AST_to_HIR () {}
};

#endif // PHC_AST_TO_HIR_H 
