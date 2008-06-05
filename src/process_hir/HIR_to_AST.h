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
<
 AST::Actual_parameter*,	// Actual_parameter*
 AST::Array*,					// Array*
 AST::Array_elem*,			// Array_elem*
 AST::Eval_expr*,				// Assign_array*
 AST::Eval_expr*,				// Assign_var*
 AST::Eval_expr*,				// Assign_var_var*
 AST::Attr_mod*,				// Attr_mod*
 AST::Attribute*,				// Attribute*
 AST::BOOL*,					// BOOL*
 AST::Bin_op*,					// Bin_op*
 AST::Break*,					// Break*
 AST::CAST*,					// CAST*
 AST::CLASS_NAME*,			// CLASS_NAME*
 AST::CONSTANT_NAME*, 		// CONSTANT_NAME*
 AST::Cast*,					// Cast*
 AST::Catch*,					// Catch*
 AST::Class_def*,				// Class_def*
 AST::Class_mod*,				// Class_mod*
 AST::Class_name*,			// Class_name*
 AST::Constant*,				// Constant*
 AST::Continue*,				// Continue*
 AST::Expr*,					// Expr*
 AST::Expr*,					// Expr_invocation*
 AST::Foreach*,				// Foreach*
 AST::Foreign*,				// Foreign*
 AST::Foreign_expr*,			// Foreign_expr*
 AST::Foreign_statement*,	// Foreign_statement*
 AST::Formal_parameter*,	// Formal_parameter*
 AST::Global*,					// Global*
 AST::INT*,						// INT*
 AST::INTERFACE_NAME*,		// INTERFACE_NAME*
 AST::Identifier*,			// Identifier*
 AST::If*,						// If*
 AST::Instanceof*,			// Instanceof*
 AST::Interface_def*,		// Interface_def*
 AST::Eval_expr*,				// Invoke_expr*
 AST::Literal*,				// Literal*
 AST::While*,					// Loop*
 AST::METHOD_NAME*,			// METHOD_NAME*
 AST::Member*,					// Member*
 AST::Method*,					// Method*
 AST::Method_invocation*,	// Method_invocation*
 AST::Method_mod*,			// Method_mod*
 AST::Method_name*,			// Method_name*
 AST::NIL*,						// NIL*
 AST::Name_with_default*,	// Name_with_default*
 AST::New*,						// New*
 AST::Node*,					// Node*
 AST::OP*,						// OP*
 AST::PHP_script*,			// PHP_script*
 AST::Pre_op*,					// Pre_op*
 AST::Eval_expr*,				// Push_array*
 AST::REAL*,					// REAL*
 AST::Reflection*,			// Reflection*
 AST::Return*,					// Return*
 AST::STRING*,					// STRING*
 AST::Signature*,				// Signature*
 AST::Statement*,				// Statement*
 AST::Static_declaration*,	// Static_declaration*
 AST::Target*,					// Target*
 AST::Throw*,					// Throw*
 AST::Try*,						// Try*
 AST::Type*,					// Type*
 AST::Unary_op*,				// Unary_op*
 AST::VARIABLE_NAME*,		// VARIABLE_NAME*
 AST::Variable*,				// Variable*
 AST::Variable_name*			// Variable_name*
>
{

	AST::Variable* wrap_var_name (AST::VARIABLE_NAME* var_name)
	{
		if (var_name == NULL)
			return NULL;

		return new AST::Variable (var_name);
	}

	List<AST::Expr*>* wrap_var_name_list (List<AST::VARIABLE_NAME*>* var_names)
	{
		List<AST::Expr*>* result = new List<AST::Expr*>;
		for_lci (var_names, AST::VARIABLE_NAME, i)
		{
			result->push_back (wrap_var_name (*i));
		}
		return result;
	}



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

	AST::Attribute* fold_impl_attribute(HIR::Attribute* orig, AST::Attr_mod* attr_mod, AST::Name_with_default* var) 
	{
		AST::Attribute* result;
		result = new AST::Attribute(attr_mod, new List<AST::Name_with_default*> (var));
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

	AST::Static_declaration* fold_impl_static_declaration(HIR::Static_declaration* orig, AST::Name_with_default* var) 
	{
		AST::Static_declaration* result;
		result = new AST::Static_declaration(new List<AST::Name_with_default*> (var));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Global* fold_impl_global(HIR::Global* orig, AST::Variable_name* variable_name) 
	{
		AST::Global* result;
		result = new AST::Global(new List<AST::Variable_name*> (variable_name));
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

	AST::Foreign_expr* fold_impl_foreign_expr(HIR::Foreign_expr* orig)
	{
		AST::Foreign_expr* result;
		result = new AST::Foreign_expr (orig->foreign);
		result->attrs = orig->attrs;
		return result;
	};

	AST::Foreign_statement* fold_impl_foreign_statement (HIR::Foreign_statement* orig) 
	{ 
		AST::Foreign_statement* result;
		result = new AST::Foreign_statement (orig->foreign);
		result->attrs = orig->attrs;
		return result;
	};

	AST::Break* fold_impl_break (HIR::Break* orig, AST::Expr* expr)
	{
		AST::Break* result;
		result = new AST::Break (expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::If* fold_impl_if(HIR::If* orig, AST::VARIABLE_NAME* variable_name, List<AST::Statement*>* iftrue, List<AST::Statement*>* iffalse)
	{
		AST::If* result;
		result = new AST::If (wrap_var_name (variable_name), iftrue, iffalse);
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

	AST::Foreach* fold_impl_foreach (HIR::Foreach* orig, AST::VARIABLE_NAME* expr, AST::VARIABLE_NAME* key, bool is_ref, AST::VARIABLE_NAME* val, List<AST::Statement*>* statements)
	{
		AST::Foreach* result;
		result = new AST::Foreach(wrap_var_name (expr), wrap_var_name (key), is_ref, wrap_var_name (val), statements);
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

	AST::Eval_expr* fold_impl_assign_var (HIR::Assign_var* orig, AST::Target* target, AST::VARIABLE_NAME* lhs, bool is_ref, AST::Expr* rhs) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				target, 
				lhs,
				new List<AST::Expr*>),
			is_ref, 
			rhs);
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_assign_var_var (HIR::Assign_var_var* orig, AST::Target* target, AST::VARIABLE_NAME* lhs, bool is_ref, AST::VARIABLE_NAME* rhs) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				target,
				new AST::Reflection (
					wrap_var_name (lhs)),
				new List<AST::Expr*>), 
			is_ref, 
			wrap_var_name (rhs));
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_assign_array (HIR::Assign_array* orig, AST::Target* target, AST::VARIABLE_NAME* lhs, AST::VARIABLE_NAME* index, bool is_ref, AST::VARIABLE_NAME* rhs) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				target, 
				lhs, 
				new List<AST::Expr*> (
					wrap_var_name (index))), 
			is_ref, 
			wrap_var_name (rhs));
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_push_array (HIR::Push_array* orig, AST::Target* target, AST::VARIABLE_NAME* lhs, bool is_ref, AST::VARIABLE_NAME* rhs) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				target,
				lhs,
				new List<AST::Expr*> (
					NULL)),
				is_ref,
				wrap_var_name (rhs));
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_invoke_expr (HIR::Invoke_expr* orig, AST::Expr* expr) 
	{
		return new AST::Eval_expr (expr);
	}

	AST::Cast* fold_impl_cast(HIR::Cast* orig, AST::CAST* cast, AST::VARIABLE_NAME* variable_name) 
	{
		AST::Cast* result;
		result = new AST::Cast(cast, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Unary_op* fold_impl_unary_op(HIR::Unary_op* orig, AST::OP* op, AST::VARIABLE_NAME* variable_name) 
	{
		AST::Unary_op* result;
		result = new AST::Unary_op(op, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Bin_op* fold_impl_bin_op(HIR::Bin_op* orig, AST::VARIABLE_NAME* left, AST::OP* op, AST::VARIABLE_NAME* right) 
	{
		AST::Bin_op* result;
		result = new AST::Bin_op(wrap_var_name (left), op, wrap_var_name (right));
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

	AST::Instanceof* fold_impl_instanceof(HIR::Instanceof* orig, AST::VARIABLE_NAME* variable_name, AST::Class_name* class_name) 
	{
		AST::Instanceof* result;
		result = new AST::Instanceof(wrap_var_name (variable_name), class_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Variable* fold_impl_variable(HIR::Variable* orig, AST::Target* target, AST::Variable_name* variable_name, List<AST::VARIABLE_NAME*>* array_indices) 
	{
		AST::Variable* result;
		result = new AST::Variable(target, variable_name, wrap_var_name_list (array_indices));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Reflection* fold_impl_reflection(HIR::Reflection* orig, AST::VARIABLE_NAME* variable_name) 
	{
		AST::Reflection* result;
		result = new AST::Reflection (wrap_var_name (variable_name));
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

	AST::Actual_parameter* fold_impl_actual_parameter(HIR::Actual_parameter* orig, bool is_ref, AST::Target* target, AST::Variable_name* variable_name, List<AST::VARIABLE_NAME*>* array_indices) 
	{
		AST::Actual_parameter* result;
		result = new AST::Actual_parameter(is_ref, new AST::Variable (target, variable_name, wrap_var_name_list (array_indices)));
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
		result = new AST::CAST(orig->value);
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
