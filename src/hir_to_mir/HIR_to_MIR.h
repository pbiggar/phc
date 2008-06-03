/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Translate the shredded and lowered AST to HIR 
 */

#ifndef PHC_HIR_TO_MIR_H
#define PHC_HIR_TO_MIR_H

#include "HIR_fold.h"
#include "MIR.h"
#include "process_ir/General.h"

/*
 * Those AST nodes that should no longer appear in the HIR do not have an
 * implementation in this translation, so that we inherit the default assert(0)
 * implementation from AST_fold. However, to satisfy the typechecker, we must
 * still provide a reasonble type for these nodes. For example, the type we
 * specify for For (which does not have a corresponding HIR construct) is
 * simplify HIR::Statement*. For some constructs, specifying HIR::Node*
 * suffices.
 */
class HIR_to_MIR : public HIR::Fold
<MIR::Node*,				// Node*
 MIR::PHP_script*,			// PHP_script*
 MIR::Statement*,			// Statement*
 MIR::Class_def*,			// Class_def*
 MIR::Class_mod*,			// Class_mod*
 MIR::Interface_def*,		// Interface_def*
 MIR::Member*,				// Member*
 MIR::Method*,				// Method*
 MIR::Signature*,			// Signature*
 MIR::Method_mod*,			// Method_mod*
 MIR::Formal_parameter*,	// Formal_parameter*
 MIR::Type*,				// Type*
 MIR::Attribute*,			// Attribute*
 MIR::Attr_mod*,			// Attr_mod*
 MIR::Name_with_default*,	// Name_with_default*
 MIR::Statement*,			// If*
 MIR::Statement*,			// While*
 MIR::Statement*,			// Foreach*
 MIR::Statement*,			// Break*
 MIR::Statement*,			// Continue*
 MIR::Return*,				// Return*
 MIR::Static_declaration*,	// Static_declaration*
 MIR::Global*,				// Global*
 MIR::Try*,					// Try*
 MIR::Catch*,				// Catch*
 MIR::Throw*,				// Throw*
 MIR::Eval_expr*,			// Eval_expr*
 MIR::Node*,			// Foreign*
 MIR::Statement*,			// Foreign_statement*
 MIR::Expr*,			// Foreign_expr*
 MIR::Expr*,				// Expr*
 MIR::Literal*,				// Literal*
 MIR::Assignment*,			// Assignment*
 MIR::Expr*,				// Op_assignment*
 MIR::Cast*,				// Cast*
 MIR::Unary_op*,			// Unary_op*
 MIR::Bin_op*,				// Bin_op*
 MIR::Constant*,			// Constant*
 MIR::Instanceof*,			// Instanceof*
 MIR::Variable*,			// Variable*
 MIR::Variable_name*,		// Variable_name*
 MIR::Reflection*,			// Reflection*
 MIR::Target*,				// Target*
 MIR::Pre_op*,				// Pre_op*
 MIR::Array*,				// Array*
 MIR::Array_elem*,			// Array_elem*
 MIR::Method_invocation*,	// Method_invocation*
 MIR::Method_name*,			// Method_name*
 MIR::Actual_parameter*,	// Actual_parameter*
 MIR::New*,					// New*
 MIR::Class_name*,			// Class_name*
 MIR::Identifier*,			// Identifier*
 MIR::CLASS_NAME*,		// CLASS_NAME*
 MIR::INTERFACE_NAME*,	// INTERFACE_NAME*
 MIR::METHOD_NAME*,		// METHOD_NAME*
 MIR::VARIABLE_NAME*,		// VARIABLE_NAME*
 MIR::INT*,				// INT*
 MIR::REAL*,				// REAL*
 MIR::STRING*,			// STRING*
 MIR::BOOL*,				// BOOL*
 MIR::NIL*,				// NIL*
 MIR::OP*,				// OP*
 MIR::CAST*,				// CAST*
 MIR::CONSTANT_NAME*>		// CONSTANT_NAME*
{
public:
	MIR::PHP_script* fold_impl_php_script(HIR::PHP_script* orig, List<MIR::Statement*>* statements) 
	{
		MIR::PHP_script* result;
		result = new MIR::PHP_script(statements);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Class_def* fold_impl_class_def(HIR::Class_def* orig, MIR::Class_mod* class_mod, MIR::CLASS_NAME* class_name, MIR::CLASS_NAME* extends, List<MIR::INTERFACE_NAME*>* implements, List<MIR::Member*>* members) 
	{
		MIR::Class_def* result;
		result = new MIR::Class_def(class_mod, class_name, extends, implements, members);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Class_mod* fold_impl_class_mod(HIR::Class_mod* orig, bool is_abstract, bool is_final) 
	{
		MIR::Class_mod* result;
		result = new MIR::Class_mod(is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Interface_def* fold_impl_interface_def(HIR::Interface_def* orig, MIR::INTERFACE_NAME* interface_name, List<MIR::INTERFACE_NAME*>* extends, List<MIR::Member*>* members) 
	{
		MIR::Interface_def* result;
		result = new MIR::Interface_def(interface_name, extends, members);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Method* fold_impl_method(HIR::Method* orig, MIR::Signature* signature, List<MIR::Statement*>* statements) 
	{
		MIR::Method* result;
		result = new MIR::Method(signature, statements);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Signature* fold_impl_signature(HIR::Signature* orig, MIR::Method_mod* method_mod, bool is_ref, MIR::METHOD_NAME* method_name, List<MIR::Formal_parameter*>* formal_parameters) 
	{
		MIR::Signature* result;
		result = new MIR::Signature(method_mod, is_ref, method_name, formal_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Method_mod* fold_impl_method_mod(HIR::Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		MIR::Method_mod* result;
		result = new MIR::Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Formal_parameter* fold_impl_formal_parameter(HIR::Formal_parameter* orig, MIR::Type* type, bool is_ref, MIR::Name_with_default* var) 
	{
		MIR::Formal_parameter* result;
		result = new MIR::Formal_parameter(type, is_ref, var);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Type* fold_impl_type(HIR::Type* orig, MIR::CLASS_NAME* class_name) 
	{
		MIR::Type* result;
		result = new MIR::Type(class_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Attribute* fold_impl_attribute(HIR::Attribute* orig, MIR::Attr_mod* attr_mod, MIR::Name_with_default* var) 
	{
		MIR::Attribute* result;
		result = new MIR::Attribute(attr_mod, var);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Attr_mod* fold_impl_attr_mod(HIR::Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		MIR::Attr_mod* result;
		result = new MIR::Attr_mod(is_public, is_protected, is_private, is_static, is_const);
		result->attrs = orig->attrs;
		return result;
	}
	
	MIR::Name_with_default* fold_impl_name_with_default(HIR::Name_with_default* orig, MIR::VARIABLE_NAME* variable_name, MIR::Expr* expr) 
	{ 
		MIR::Name_with_default* result;
		result = new MIR::Name_with_default(variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Return* fold_impl_return(HIR::Return* orig, MIR::Expr* expr) 
	{
		MIR::Return* result;
		result = new MIR::Return(expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Static_declaration* fold_impl_static_declaration(HIR::Static_declaration* orig, MIR::Name_with_default* var) 
	{
		MIR::Static_declaration* result;
		result = new MIR::Static_declaration(var);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Global* fold_impl_global(HIR::Global* orig, MIR::Variable_name* variable_name) 
	{
		MIR::Global* result;
		result = new MIR::Global(variable_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Try* fold_impl_try(HIR::Try* orig, List<MIR::Statement*>* statements, List<MIR::Catch*>* catches) 
	{
		MIR::Try* result;
		result = new MIR::Try(statements, catches);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Catch* fold_impl_catch(HIR::Catch* orig, MIR::CLASS_NAME* class_name, MIR::VARIABLE_NAME* variable_name, List<MIR::Statement*>* statements) 
	{
		MIR::Catch* result;
		result = new MIR::Catch(class_name, variable_name, statements);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Throw* fold_impl_throw(HIR::Throw* orig, MIR::Expr* expr) 
	{
		MIR::Throw* result;
		result = new MIR::Throw(expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Eval_expr* fold_impl_eval_expr(HIR::Eval_expr* orig, MIR::Expr* expr) 
	{
		MIR::Eval_expr* result;
		result = new MIR::Eval_expr(expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Expr* fold_impl_foreign_expr (HIR::Foreign_expr* orig)
	{
		// It should already be suitable to put in the MIR
		return dynamic_cast<MIR::Expr*> (orig->foreign);
	}

	MIR::Statement* fold_impl_foreign_statement (HIR::Foreign_statement* orig)
	{
		// It should already be suitable to put in the MIR
		return dynamic_cast<MIR::Statement*> (orig->foreign);
	}

	MIR::Assignment* fold_impl_assignment(HIR::Assignment* orig, MIR::Variable* variable, bool is_ref, MIR::Expr* expr) 
	{
		MIR::Assignment* result;
		result = new MIR::Assignment(variable, is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::VARIABLE_NAME* var_name_from_expr (MIR::Expr* expr)
	{
		if (expr == NULL) // $x[]
			return NULL;

		MIR::Variable* var = dynamic_cast<MIR::Variable*> (expr);
		assert (var);
		assert (var->target == NULL);
		assert (var->variable_name);
		assert (var->array_indices->size () == 0);

		MIR::VARIABLE_NAME* var_name = dynamic_cast<MIR::VARIABLE_NAME*> (var->variable_name);
		assert (var_name);
		return var_name;
	}

	MIR::Cast* fold_impl_cast(HIR::Cast* orig, MIR::CAST* cast, MIR::VARIABLE_NAME* expr) 
	{
		MIR::Cast* result;
		result = new MIR::Cast(cast, expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Unary_op* fold_impl_unary_op(HIR::Unary_op* orig, MIR::OP* op, MIR::VARIABLE_NAME* expr) 
	{
		MIR::Unary_op* result;
		result = new MIR::Unary_op(op, expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Bin_op* fold_impl_bin_op(HIR::Bin_op* orig, MIR::VARIABLE_NAME* left, MIR::OP* op, MIR::VARIABLE_NAME* right) 
	{
		MIR::Bin_op* result;
		result = new MIR::Bin_op(left, op, right);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Constant* fold_impl_constant(HIR::Constant* orig, MIR::CLASS_NAME* class_name, MIR::CONSTANT_NAME* constant_name) 
	{
		MIR::Constant* result;
		result = new MIR::Constant(class_name, constant_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Instanceof* fold_impl_instanceof(HIR::Instanceof* orig, MIR::VARIABLE_NAME* variable_name, MIR::Class_name* class_name) 
	{
		MIR::Instanceof* result;
		result = new MIR::Instanceof(variable_name, class_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Variable* fold_impl_variable(HIR::Variable* orig, MIR::Target* target, MIR::Variable_name* variable_name, List<MIR::VARIABLE_NAME*>* array_indices) 
	{
		MIR::Variable* result;
		result = new MIR::Variable(target, variable_name, array_indices);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Reflection* fold_impl_reflection(HIR::Reflection* orig, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Reflection* result;
		result = new MIR::Reflection(variable_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Pre_op* fold_impl_pre_op(HIR::Pre_op* orig, MIR::OP* op, MIR::Variable* variable) 
	{
		MIR::Pre_op* result;
		result = new MIR::Pre_op(op, variable);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Array* fold_impl_array(HIR::Array* orig, List<MIR::Array_elem*>* array_elems) 
	{
		MIR::Array* result;
		result = new MIR::Array(array_elems);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Array_elem* fold_impl_array_elem(HIR::Array_elem* orig, MIR::Expr* key, bool is_ref, MIR::Expr* val) 
	{
		MIR::Array_elem* result;
		result = new MIR::Array_elem(key, is_ref, val);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Method_invocation* fold_impl_method_invocation(HIR::Method_invocation* orig, MIR::Target* target, MIR::Method_name* method_name, List<MIR::Actual_parameter*>* actual_parameters) 
	{
		MIR::Method_invocation* result;
		result = new MIR::Method_invocation(target, method_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Actual_parameter* fold_impl_actual_parameter(HIR::Actual_parameter* orig, bool is_ref, MIR::Expr* expr) 
	{
		MIR::Variable* var = dynamic_cast<MIR::Variable*> (expr);
		assert (var);

		MIR::Actual_parameter* result;
		result = new MIR::Actual_parameter(is_ref, var->target, var->variable_name, var->array_indices);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::New* fold_impl_new(HIR::New* orig, MIR::Class_name* class_name, List<MIR::Actual_parameter*>* actual_parameters) 
	{
		MIR::New* result;
		result = new MIR::New(class_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::CLASS_NAME* fold_class_name(HIR::CLASS_NAME* orig) 
	{
		MIR::CLASS_NAME* result;
		result = new MIR::CLASS_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::INTERFACE_NAME* fold_interface_name(HIR::INTERFACE_NAME* orig) 
	{
		MIR::INTERFACE_NAME* result;
		result = new MIR::INTERFACE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::METHOD_NAME* fold_method_name(HIR::METHOD_NAME* orig) 
	{
		MIR::METHOD_NAME* result;
		result = new MIR::METHOD_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::VARIABLE_NAME* fold_variable_name(HIR::VARIABLE_NAME* orig) 
	{
		MIR::VARIABLE_NAME* result;
		result = new MIR::VARIABLE_NAME(orig->value);
		result->attrs = orig->attrs->clone ();
		return result;
	}

	MIR::INT* fold_int(HIR::INT* orig) 
	{
		MIR::INT* result;
		result = new MIR::INT(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::REAL* fold_real(HIR::REAL* orig) 
	{
		MIR::REAL* result;
		result = new MIR::REAL(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::STRING* fold_string(HIR::STRING* orig) 
	{
		MIR::STRING* result;
		result = new MIR::STRING(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::BOOL* fold_bool(HIR::BOOL* orig) 
	{
		MIR::BOOL* result;
		result = new MIR::BOOL(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::NIL* fold_nil(HIR::NIL* orig) 
	{
		MIR::NIL* result;
		result = new MIR::NIL();
		result->attrs = orig->attrs;
		return result;
	}

	MIR::OP* fold_op(HIR::OP* orig) 
	{
		MIR::OP* result;
		result = new MIR::OP(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::CAST* fold_cast(HIR::CAST* orig) 
	{
		MIR::CAST* result;
		result = new MIR::CAST(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::CONSTANT_NAME* fold_constant_name(HIR::CONSTANT_NAME* orig) 
	{
		MIR::CONSTANT_NAME* result;
		result = new MIR::CONSTANT_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

 	~HIR_to_MIR () {}
};

#endif // PHC_HIR_TO_MIR_H 
