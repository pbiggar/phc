/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Translate the shredded and lowered HIR to AST 
 */

#ifndef PHC_HIR_TO_AST_H
#define PHC_HIR_TO_AST_H

#include "HIR_fold.h"
#include "AST.h"
#include "process_ir/General.h"

/*
 * Those HIR nodes that should no longer appear in the AST do not have an
 * implementation in this translation, so that we inherit the default assert(0)
 * implementation from HIR_fold. However, to satisfy the typechecker, we must
 * still provide a reasonble type for these nodes. For example, the type we
 * specify for For (which does not have a corresponding AST construct) is
 * simplify AST::Statement*. For some constructs, specifying AST::Node*
 * suffices.
 */
class HIR_to_AST : public HIR::Fold
<AST::Node*,				// Node*
 AST::PHP_script*,			// PHP_script*
 AST::Statement*,			// Statement*
 AST::Class_def*,			// Class_def*
 AST::Class_mod*,			// Class_mod*
 AST::Interface_def*,		// Interface_def*
 AST::Member*,				// Member*
 AST::Method*,				// Method*
 AST::Signature*,			// Signature*
 AST::Method_mod*,			// Method_mod*
 AST::Formal_parameter*,	// Formal_parameter*
 AST::Type*,				// Type*
 AST::Attribute*,			// Attribute*
 AST::Attr_mod*,			// Attr_mod*
 AST::Name_with_default*,	// Name_with_default*
 AST::If*,			// If*
 AST::While*,			// Loop*
 AST::Foreach*,			// Foreach*
 AST::Switch*,			// Switch*
 AST::Switch_case*,				// Switch_case*
 AST::Break*,			// Break*
 AST::Continue*,			// Continue*
 AST::Return*,				// Return*
 AST::Static_declaration*,	// Static_declaration*
 AST::Global*,				// Global*
 AST::Try*,					// Try*
 AST::Catch*,				// Catch*
 AST::Throw*,				// Throw*
 AST::Eval_expr*,			// Eval_expr*
 AST::Branch*,				// Branch*
 AST::Goto*,				// Goto*
 AST::Label*,				// Label*
 AST::Foreach_reset*,	// Foreach_reset*
 AST::Foreach_next*,	// Foreach_next*
 AST::Foreach_end*,	// Foreach_end*
 AST::Foreach_has_key*,	// Foreach_has_key*
 AST::Foreach_get_key*,	// Foreach_get_key*
 AST::Foreach_get_val*,	// Foreach_get_val*
 AST::Expr*,				// Expr*
 AST::Literal*,				// Literal*
 AST::Assignment*,			// Assignment*
 AST::Op_assignment*,				// Op_assignment*
 AST::List_assignment*,				// List_assignment*
 AST::List_element*,				// List_element*
 AST::Nested_list_elements*,				// Nested_list_elements*
 AST::Cast*,				// Cast*
 AST::Unary_op*,			// Unary_op*
 AST::Bin_op*,				// Bin_op*
 AST::Conditional_expr*,				// Conditional_expr*
 AST::Ignore_errors*,				// Ignore_errors*
 AST::Constant*,			// Constant*
 AST::Instanceof*,			// Instanceof*
 AST::Variable*,			// Variable*
 AST::Variable_name*,		// Variable_name*
 AST::Reflection*,			// Reflection*
 AST::Target*,				// Target*
 AST::Pre_op*,				// Pre_op*
 AST::Post_op*,				// Post_op*
 AST::Array*,				// Array*
 AST::Array_elem*,			// Array_elem*
 AST::Method_invocation*,	// Method_invocation*
 AST::Method_name*,			// Method_name*
 AST::Actual_parameter*,	// Actual_parameter*
 AST::New*,					// New*
 AST::Class_name*,			// Class_name*
 AST::Commented_node*,				// Commented_node*
 AST::Identifier*,			// Identifier*
 AST::HT_ITERATOR*,		// HT_ITERATOR*
 AST::CLASS_NAME*,		// CLASS_NAME*
 AST::INTERFACE_NAME*,	// INTERFACE_NAME*
 AST::METHOD_NAME*,		// METHOD_NAME*
 AST::VARIABLE_NAME*,		// VARIABLE_NAME*
 AST::LABEL_NAME*,		// LABEL_NAME*
 AST::INT*,				// INT*
 AST::REAL*,				// REAL*
 AST::STRING*,			// STRING*
 AST::BOOL*,				// BOOL*
 AST::NIL*,				// NIL*
 AST::OP*,				// OP*
 AST::CAST*,				// CAST*
 AST::CONSTANT_NAME*>		// CONSTANT_NAME*
{
	AST::PHP_script* fold_impl_php_script(HIR::PHP_script* orig, List<AST::Statement*>* statements) 
	{
		AST::PHP_script* result;
		result = new AST::PHP_script(statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Class_def* fold_impl_class_def(HIR::Class_def* orig, AST::Class_mod* class_mod, AST::CLASS_NAME* class_name, AST::CLASS_NAME* extends, List<AST::INTERFACE_NAME*>* implements, List<AST::Member*>* members) 
	{
		AST::Class_def* result;
		result = new AST::Class_def(class_mod, class_name, extends, implements, members);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Class_mod* fold_impl_class_mod(HIR::Class_mod* orig, bool is_abstract, bool is_final) 
	{
		AST::Class_mod* result;
		result = new AST::Class_mod(is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Interface_def* fold_impl_interface_def(HIR::Interface_def* orig, AST::INTERFACE_NAME* interface_name, List<AST::INTERFACE_NAME*>* extends, List<AST::Member*>* members) 
	{
		AST::Interface_def* result;
		result = new AST::Interface_def(interface_name, extends, members);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method* fold_impl_method(HIR::Method* orig, AST::Signature* signature, List<AST::Statement*>* statements) 
	{
		AST::Method* result;
		result = new AST::Method(signature, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Signature* fold_impl_signature(HIR::Signature* orig, AST::Method_mod* method_mod, bool is_ref, AST::METHOD_NAME* method_name, List<AST::Formal_parameter*>* formal_parameters) 
	{
		AST::Signature* result;
		result = new AST::Signature(method_mod, is_ref, method_name, formal_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method_mod* fold_impl_method_mod(HIR::Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		AST::Method_mod* result;
		result = new AST::Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Formal_parameter* fold_impl_formal_parameter(HIR::Formal_parameter* orig, AST::Type* type, bool is_ref, AST::Name_with_default* var) 
	{
		AST::Formal_parameter* result;
		result = new AST::Formal_parameter(type, is_ref, var);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Type* fold_impl_type(HIR::Type* orig, AST::CLASS_NAME* class_name) 
	{
		AST::Type* result;
		result = new AST::Type(class_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Attribute* fold_impl_attribute(HIR::Attribute* orig, AST::Attr_mod* attr_mod, List<AST::Name_with_default*>* vars) 
	{
//		assert(vars->size() == 1); // TODO reinstate this

		AST::Attribute* result;
		result = new AST::Attribute(attr_mod, vars);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Attr_mod* fold_impl_attr_mod(HIR::Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		AST::Attr_mod* result;
		result = new AST::Attr_mod(is_public, is_protected, is_private, is_static, is_const);
		result->attrs = orig->attrs;
		return result;
	}
	
	AST::Name_with_default* fold_impl_name_with_default(HIR::Name_with_default* orig, AST::VARIABLE_NAME* variable_name, AST::Expr* expr) 
	{ 
		AST::Name_with_default* result;
		result = new AST::Name_with_default(variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Return* fold_impl_return(HIR::Return* orig, AST::Expr* expr) 
	{
		AST::Return* result;
		result = new AST::Return(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Static_declaration* fold_impl_static_declaration(HIR::Static_declaration* orig, List<AST::Name_with_default*>* vars) 
	{
		assert(vars->size() == 1);

		AST::Static_declaration* result;
		result = new AST::Static_declaration(vars);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Global* fold_impl_global(HIR::Global* orig, List<AST::Variable_name*>* variable_names) 
	{
		// AST only takes a single variable per global; should be been taken care of in the shredder
		// TODO reinstate
//		assert(variable_names->size() == 1);
		
		AST::Global* result;
		result = new AST::Global(variable_names);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Try* fold_impl_try(HIR::Try* orig, List<AST::Statement*>* statements, List<AST::Catch*>* catches) 
	{
		AST::Try* result;
		result = new AST::Try(statements, catches);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Catch* fold_impl_catch(HIR::Catch* orig, AST::CLASS_NAME* class_name, AST::VARIABLE_NAME* variable_name, List<AST::Statement*>* statements) 
	{
		AST::Catch* result;
		result = new AST::Catch(class_name, variable_name, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Throw* fold_impl_throw(HIR::Throw* orig, AST::Expr* expr) 
	{
		AST::Throw* result;
		result = new AST::Throw(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Eval_expr* fold_impl_eval_expr(HIR::Eval_expr* orig, AST::Expr* expr) 
	{
		AST::Eval_expr* result;
		result = new AST::Eval_expr(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Branch* fold_impl_branch(HIR::Branch* orig, AST::Expr* expr, AST::LABEL_NAME* iftrue, AST::LABEL_NAME* iffalse) 
	{
		AST::Branch* result;
		result = new AST::Branch(expr, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Goto* fold_impl_goto(HIR::Goto* orig, AST::LABEL_NAME* label_name) 
	{
		AST::Goto* result;
		result = new AST::Goto(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Label* fold_impl_label(HIR::Label* orig, AST::LABEL_NAME* label_name) 
	{
		AST::Label* result;
		result = new AST::Label(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Break* fold_impl_break (HIR::Break* orig, AST::Expr* expr)
	{
		AST::Break* result;
		result = new AST::Break (expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::If* fold_impl_if(HIR::If* orig, AST::Expr* expr, List<AST::Statement*>* iftrue, List<AST::Statement*>* iffalse)
	{
		AST::If* result;
		result = new AST::If (expr, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Conditional_expr* fold_impl_conditional_expr (HIR::Conditional_expr* orig, AST::Expr* cond, AST::Expr* iftrue, AST::Expr* iffalse)
	{
		AST::Conditional_expr* result;
		result = new AST::Conditional_expr (cond, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Op_assignment* fold_impl_op_assignment(HIR::Op_assignment* orig, AST::Variable* variable, AST::OP* op, AST::Expr* expr)
	{
		AST::Op_assignment* result;
		result = new AST::Op_assignment (variable, op, expr);
		result->attrs = orig->attrs;
		return result;
	}


	AST::While* fold_impl_loop (HIR::Loop* orig, List<AST::Statement*>* statements)
	{
		AST::While* result;
		result = new AST::While(new AST::BOOL (true), statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach* fold_impl_foreach (HIR::Foreach* orig, AST::Expr* expr, AST::Variable* key, bool is_ref, AST::Variable* val, List<AST::Statement*>* statements)
	{
		AST::Foreach* result;
		result = new AST::Foreach(expr, key, is_ref, val, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Ignore_errors* fold_impl_ignore_errors(HIR::Ignore_errors* orig, AST::Expr* expr)
	{
		AST::Ignore_errors* result;
		result = new AST::Ignore_errors (expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Switch* fold_impl_switch(HIR::Switch* orig, AST::Expr* expr, List<AST::Switch_case*>* switch_cases)
	{
		AST::Switch* result;
		result = new AST::Switch (expr, switch_cases);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Continue* fold_impl_continue(HIR::Continue* orig, AST::Expr* expr)
	{
		AST::Continue* result;
		result = new AST::Continue(expr);
		result->attrs = orig->attrs;
		return result;
	}


	AST::List_assignment* fold_impl_list_assignment(HIR::List_assignment* orig, List<AST::List_element*>* list_elements, AST::Expr* expr)
	{
		AST::List_assignment* result;
		result = new AST::List_assignment(list_elements, expr);
		result->attrs = orig->attrs;
		return result;
	}


	AST::Nested_list_elements* fold_impl_nested_list_elements(HIR::Nested_list_elements* orig, List<AST::List_element*>* list_elements)
	{
		AST::Nested_list_elements* result;
		result = new AST::Nested_list_elements(list_elements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Switch_case* fold_impl_switch_case(HIR::Switch_case* orig, AST::Expr* expr, List<AST::Statement*>* statements)
	{
		AST::Switch_case* result;
		result = new AST::Switch_case (expr, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_reset* fold_impl_foreach_reset (HIR::Foreach_reset* orig, AST::Variable* variable, AST::HT_ITERATOR* ht_iterator) 
	{
		AST::Foreach_reset* result;
		result = new AST::Foreach_reset (variable, ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}


	AST::Foreach_next* fold_impl_foreach_next (HIR::Foreach_next* orig, AST::Variable* variable, AST::HT_ITERATOR* ht_iterator) 
	{
		AST::Foreach_next* result;
		result = new AST::Foreach_next (variable, ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_end* fold_impl_foreach_end (HIR::Foreach_end* orig, AST::Variable* variable, AST::HT_ITERATOR* ht_iterator) 
	{
		AST::Foreach_end* result;
		result = new AST::Foreach_end (variable, ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_has_key* fold_impl_foreach_has_key (HIR::Foreach_has_key* orig, AST::Variable* variable, AST::HT_ITERATOR* ht_iterator) 
	{
		AST::Foreach_has_key* result;
		result = new AST::Foreach_has_key (variable, ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_get_key* fold_impl_foreach_get_key (HIR::Foreach_get_key* orig, AST::Variable* variable, AST::HT_ITERATOR* ht_iterator) 
	{
		AST::Foreach_get_key* result;
		result = new AST::Foreach_get_key (variable, ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_get_val* fold_impl_foreach_get_val (HIR::Foreach_get_val* orig, AST::Variable* variable, AST::HT_ITERATOR* ht_iterator) 
	{
		AST::Foreach_get_val* result;
		result = new AST::Foreach_get_val (variable, ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}
	
	AST::Assignment* fold_impl_assignment(HIR::Assignment* orig, AST::Variable* variable, bool is_ref, AST::Expr* expr) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(variable, is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Cast* fold_impl_cast(HIR::Cast* orig, AST::CAST* cast, AST::Expr* expr) 
	{
		AST::Cast* result;
		result = new AST::Cast(cast, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Unary_op* fold_impl_unary_op(HIR::Unary_op* orig, AST::OP* op, AST::Expr* expr) 
	{
		AST::Unary_op* result;
		result = new AST::Unary_op(op, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Bin_op* fold_impl_bin_op(HIR::Bin_op* orig, AST::Expr* left, AST::OP* op, AST::Expr* right) 
	{
		AST::Bin_op* result;
		result = new AST::Bin_op(left, op, right);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Constant* fold_impl_constant(HIR::Constant* orig, AST::CLASS_NAME* class_name, AST::CONSTANT_NAME* constant_name) 
	{
		AST::Constant* result;
		result = new AST::Constant(class_name, constant_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Instanceof* fold_impl_instanceof(HIR::Instanceof* orig, AST::Expr* expr, AST::Class_name* class_name) 
	{
		AST::Instanceof* result;
		result = new AST::Instanceof(expr, class_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Variable* fold_impl_variable(HIR::Variable* orig, AST::Target* target, AST::Variable_name* variable_name, List<AST::Expr*>* array_indices) 
	{
		AST::Variable* result;
		result = new AST::Variable(target, variable_name, array_indices);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Reflection* fold_impl_reflection(HIR::Reflection* orig, AST::Expr* expr) 
	{
		AST::Reflection* result;
		result = new AST::Reflection (expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Pre_op* fold_impl_pre_op(HIR::Pre_op* orig, AST::OP* op, AST::Variable* variable) 
	{
		AST::Pre_op* result;
		result = new AST::Pre_op(op, variable);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Post_op* fold_impl_post_op(HIR::Post_op* orig, AST::Variable* variable, AST::OP* op)
	{
		AST::Post_op* result;
		result = new AST::Post_op(variable, op);
		result->attrs = orig->attrs;
		return result;
	}


	AST::Array* fold_impl_array(HIR::Array* orig, List<AST::Array_elem*>* array_elems) 
	{
		AST::Array* result;
		result = new AST::Array(array_elems);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Array_elem* fold_impl_array_elem(HIR::Array_elem* orig, AST::Expr* key, bool is_ref, AST::Expr* val) 
	{
		AST::Array_elem* result;
		result = new AST::Array_elem(key, is_ref, val);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method_invocation* fold_impl_method_invocation(HIR::Method_invocation* orig, AST::Target* target, AST::Method_name* method_name, List<AST::Actual_parameter*>* actual_parameters) 
	{
		AST::Method_invocation* result;
		result = new AST::Method_invocation(target, method_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Actual_parameter* fold_impl_actual_parameter(HIR::Actual_parameter* orig, bool is_ref, AST::Expr* expr) 
	{
		AST::Actual_parameter* result;
		result = new AST::Actual_parameter(is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::New* fold_impl_new(HIR::New* orig, AST::Class_name* class_name, List<AST::Actual_parameter*>* actual_parameters) 
	{
		AST::New* result;
		result = new AST::New(class_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::HT_ITERATOR* fold_ht_iterator (HIR::HT_ITERATOR* orig)
	{
		AST::HT_ITERATOR* result;
		result = new AST::HT_ITERATOR (orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::CLASS_NAME* fold_class_name(HIR::CLASS_NAME* orig) 
	{
		AST::CLASS_NAME* result;
		result = new AST::CLASS_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::INTERFACE_NAME* fold_interface_name(HIR::INTERFACE_NAME* orig) 
	{
		AST::INTERFACE_NAME* result;
		result = new AST::INTERFACE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::METHOD_NAME* fold_method_name(HIR::METHOD_NAME* orig) 
	{
		AST::METHOD_NAME* result;
		result = new AST::METHOD_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::VARIABLE_NAME* fold_variable_name(HIR::VARIABLE_NAME* orig) 
	{
		AST::VARIABLE_NAME* result;
		result = new AST::VARIABLE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::LABEL_NAME* fold_label_name(HIR::LABEL_NAME* orig) 
	{
		AST::LABEL_NAME* result;
		result = new AST::LABEL_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::INT* fold_int(HIR::INT* orig) 
	{
		AST::INT* result;
		result = new AST::INT(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::REAL* fold_real(HIR::REAL* orig) 
	{
		AST::REAL* result;
		result = new AST::REAL(orig->value);
		result->attrs = orig->attrs;
		result->source_rep = orig->source_rep;
		return result;
	}

	AST::STRING* fold_string(HIR::STRING* orig) 
	{
		AST::STRING* result;
		result = new AST::STRING(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::BOOL* fold_bool(HIR::BOOL* orig) 
	{
		AST::BOOL* result;
		result = new AST::BOOL(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::NIL* fold_nil(HIR::NIL* orig) 
	{
		AST::NIL* result;
		result = new AST::NIL();
		result->attrs = orig->attrs;
		return result;
	}

	AST::OP* fold_op(HIR::OP* orig) 
	{
		AST::OP* result;
		result = new AST::OP(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::CAST* fold_cast(HIR::CAST* orig) 
	{
		AST::CAST* result;
		result = new AST::CAST(orig->value, orig->source_rep);
		result->attrs = orig->attrs;
		return result;
	}

	AST::CONSTANT_NAME* fold_constant_name(HIR::CONSTANT_NAME* orig) 
	{
		AST::CONSTANT_NAME* result;
		result = new AST::CONSTANT_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	~HIR_to_AST () {}
};

#endif // PHC_HIR_TO_AST_H 
