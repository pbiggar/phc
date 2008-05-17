/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Translate the shredded and lowered MIR to AST 
 */

#ifndef PHC_MIR_TO_AST_H
#define PHC_MIR_TO_AST_H

#include "MIR_fold.h"
#include "AST.h"
#include "process_ir/General.h"

/*
 * Those MIR nodes that should no longer appear in the AST do not have an
 * implementation in this translation, so that we inherit the default assert(0)
 * implementation from MIR_fold. However, to satisfy the typechecker, we must
 * still provide a reasonble type for these nodes. For example, the type we
 * specify for For (which does not have a corresponding AST construct) is
 * simplify AST::Statement*. For some constructs, specifying AST::Node*
 * suffices.
 */
class MIR_to_AST : public MIR::Fold
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
 AST::Return*,				// Return*
 AST::Static_declaration*,	// Static_declaration*
 AST::Global*,				// Global*
 AST::Try*,					// Try*
 AST::Catch*,				// Catch*
 AST::Throw*,				// Throw*
 AST::Eval_expr*,			// Eval_expr*
 AST::Foreign*,			// Foreign*
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
 AST::Cast*,				// Cast*
 AST::Unary_op*,			// Unary_op*
 AST::Bin_op*,				// Bin_op*
 AST::Constant*,			// Constant*
 AST::Instanceof*,			// Instanceof*
 AST::Variable*,			// Variable*
 AST::Variable_name*,		// Variable_name*
 AST::Reflection*,			// Reflection*
 AST::Target*,				// Target*
 AST::Pre_op*,				// Pre_op*
 AST::Array*,				// Array*
 AST::Array_elem*,			// Array_elem*
 AST::Method_invocation*,	// Method_invocation*
 AST::Method_name*,			// Method_name*
 AST::Actual_parameter*,	// Actual_parameter*
 AST::New*,					// New*
 AST::Class_name*,			// Class_name*
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
 AST::CAST*,				// CAST*
 AST::OP*,				// OP*
 AST::CONSTANT_NAME*>		// CONSTANT_NAME*
{


	AST::Variable* wrap_var_name (AST::VARIABLE_NAME* var_name)
	{
		if (var_name == NULL)
			return NULL;

		return new AST::Variable (NULL, var_name, new List<AST::Expr*>);
	}

	List<AST::Expr*>* wrap_var_list (List<AST::VARIABLE_NAME*>* var_names)
	{
		List<AST::Expr*>* result = new List<AST::Expr*>;
		for_lci (var_names, AST::VARIABLE_NAME, i)
		{
			result->push_back (wrap_var_name (*i));
		}
		return result;
	}



	AST::PHP_script* fold_impl_php_script(MIR::PHP_script* orig, List<AST::Statement*>* statements) 
	{
		AST::PHP_script* result;
		result = new AST::PHP_script(statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Class_def* fold_impl_class_def(MIR::Class_def* orig, AST::Class_mod* class_mod, AST::CLASS_NAME* class_name, AST::CLASS_NAME* extends, List<AST::INTERFACE_NAME*>* implements, List<AST::Member*>* members) 
	{
		AST::Class_def* result;
		result = new AST::Class_def(class_mod, class_name, extends, implements, members);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Class_mod* fold_impl_class_mod(MIR::Class_mod* orig, bool is_abstract, bool is_final) 
	{
		AST::Class_mod* result;
		result = new AST::Class_mod(is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Interface_def* fold_impl_interface_def(MIR::Interface_def* orig, AST::INTERFACE_NAME* interface_name, List<AST::INTERFACE_NAME*>* extends, List<AST::Member*>* members) 
	{
		AST::Interface_def* result;
		result = new AST::Interface_def(interface_name, extends, members);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method* fold_impl_method(MIR::Method* orig, AST::Signature* signature, List<AST::Statement*>* statements) 
	{
		AST::Method* result;
		result = new AST::Method(signature, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Signature* fold_impl_signature(MIR::Signature* orig, AST::Method_mod* method_mod, bool is_ref, AST::METHOD_NAME* method_name, List<AST::Formal_parameter*>* formal_parameters) 
	{
		AST::Signature* result;
		result = new AST::Signature(method_mod, is_ref, method_name, formal_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method_mod* fold_impl_method_mod(MIR::Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		AST::Method_mod* result;
		result = new AST::Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Formal_parameter* fold_impl_formal_parameter(MIR::Formal_parameter* orig, AST::Type* type, bool is_ref, AST::Name_with_default* var) 
	{
		AST::Formal_parameter* result;
		result = new AST::Formal_parameter(type, is_ref, var);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Type* fold_impl_type(MIR::Type* orig, AST::CLASS_NAME* class_name) 
	{
		AST::Type* result;
		result = new AST::Type(class_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Attribute* fold_impl_attribute(MIR::Attribute* orig, AST::Attr_mod* attr_mod, AST::Name_with_default* var) 
	{
		AST::Attribute* result;
		result = new AST::Attribute(attr_mod, new List<AST::Name_with_default*> (var));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Attr_mod* fold_impl_attr_mod(MIR::Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		AST::Attr_mod* result;
		result = new AST::Attr_mod(is_public, is_protected, is_private, is_static, is_const);
		result->attrs = orig->attrs;
		return result;
	}
	
	AST::Name_with_default* fold_impl_name_with_default(MIR::Name_with_default* orig, AST::VARIABLE_NAME* variable_name, AST::Expr* expr) 
	{ 
		AST::Name_with_default* result;
		result = new AST::Name_with_default(variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Return* fold_impl_return(MIR::Return* orig, AST::Expr* expr) 
	{
		AST::Return* result;
		result = new AST::Return(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Static_declaration* fold_impl_static_declaration(MIR::Static_declaration* orig, AST::Name_with_default* var) 
	{
		AST::Static_declaration* result;
		result = new AST::Static_declaration(new List<AST::Name_with_default*> (var));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Global* fold_impl_global(MIR::Global* orig, AST::Variable_name* variable_name) 
	{
		AST::Global* result;
		result = new AST::Global(new List<AST::Variable_name*> (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Try* fold_impl_try(MIR::Try* orig, List<AST::Statement*>* statements, List<AST::Catch*>* catches) 
	{
		AST::Try* result;
		result = new AST::Try(statements, catches);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Catch* fold_impl_catch(MIR::Catch* orig, AST::CLASS_NAME* class_name, AST::VARIABLE_NAME* variable_name, List<AST::Statement*>* statements) 
	{
		AST::Catch* result;
		result = new AST::Catch(class_name, variable_name, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Throw* fold_impl_throw(MIR::Throw* orig, AST::Expr* expr) 
	{
		AST::Throw* result;
		result = new AST::Throw(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Eval_expr* fold_impl_eval_expr(MIR::Eval_expr* orig, AST::Expr* expr) 
	{
		AST::Eval_expr* result;
		result = new AST::Eval_expr(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Branch* fold_impl_branch(MIR::Branch* orig, AST::VARIABLE_NAME* variable_name, AST::LABEL_NAME* iftrue, AST::LABEL_NAME* iffalse) 
	{
		AST::Branch* result;
		result = new AST::Branch(wrap_var_name (variable_name), iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Goto* fold_impl_goto(MIR::Goto* orig, AST::LABEL_NAME* label_name) 
	{
		AST::Goto* result;
		result = new AST::Goto(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Label* fold_impl_label(MIR::Label* orig, AST::LABEL_NAME* label_name) 
	{
		AST::Label* result;
		result = new AST::Label(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_reset* fold_impl_foreach_reset (MIR::Foreach_reset* orig, AST::VARIABLE_NAME* array, AST::HT_ITERATOR* iter) 
	{
		AST::Foreach_reset* result;
		result = new AST::Foreach_reset (array, iter);
		result->attrs = orig->attrs;
		return result;
	}


	AST::Foreach_next* fold_impl_foreach_next (MIR::Foreach_next* orig, AST::VARIABLE_NAME* array, AST::HT_ITERATOR* iter) 
	{
		AST::Foreach_next* result;
		result = new AST::Foreach_next (array, iter);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_end* fold_impl_foreach_end (MIR::Foreach_end* orig, AST::VARIABLE_NAME* array, AST::HT_ITERATOR* iter) 
	{
		AST::Foreach_end* result;
		result = new AST::Foreach_end (array, iter);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_has_key* fold_impl_foreach_has_key (MIR::Foreach_has_key* orig, AST::VARIABLE_NAME* array, AST::HT_ITERATOR* iter) 
	{
		AST::Foreach_has_key* result;
		result = new AST::Foreach_has_key (array, iter);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_get_key* fold_impl_foreach_get_key (MIR::Foreach_get_key* orig, AST::VARIABLE_NAME* array, AST::HT_ITERATOR* iter) 
	{
		AST::Foreach_get_key* result;
		result = new AST::Foreach_get_key (array, iter);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Foreach_get_val* fold_impl_foreach_get_val (MIR::Foreach_get_val* orig, AST::VARIABLE_NAME* array, AST::VARIABLE_NAME* key, AST::HT_ITERATOR* iter) 
	{
		AST::Foreach_get_val* result;
		result = new AST::Foreach_get_val (array, key, iter);
		result->attrs = orig->attrs;
		return result;
	}
	
	AST::Assignment* fold_impl_assignment(MIR::Assignment* orig, AST::Variable* variable, bool is_ref, AST::Expr* expr) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(variable, is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Cast* fold_impl_cast(MIR::Cast* orig, AST::CAST* cast, AST::VARIABLE_NAME* variable_name) 
	{
		AST::Cast* result;
		result = new AST::Cast(cast, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Unary_op* fold_impl_unary_op(MIR::Unary_op* orig, AST::OP* op, AST::VARIABLE_NAME* variable_name) 
	{
		AST::Unary_op* result;
		result = new AST::Unary_op(op, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Bin_op* fold_impl_bin_op(MIR::Bin_op* orig, AST::VARIABLE_NAME* left, AST::OP* op, AST::VARIABLE_NAME* right) 
	{
		AST::Bin_op* result;
		result = new AST::Bin_op(wrap_var_name (left), op, wrap_var_name (right));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Constant* fold_impl_constant(MIR::Constant* orig, AST::CLASS_NAME* class_name, AST::CONSTANT_NAME* constant_name) 
	{
		AST::Constant* result;
		result = new AST::Constant(class_name, constant_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Instanceof* fold_impl_instanceof(MIR::Instanceof* orig, AST::VARIABLE_NAME* variable_name, AST::Class_name* class_name) 
	{
		AST::Instanceof* result;
		result = new AST::Instanceof(wrap_var_name (variable_name), class_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Variable* fold_impl_variable(MIR::Variable* orig, AST::Target* target, AST::Variable_name* variable_name, List<AST::VARIABLE_NAME*>* array_indices) 
	{
		AST::Variable* result;
		List<AST::Expr*>* new_ais = new List<AST::Expr*>;
		for_lci (array_indices, AST::VARIABLE_NAME, i)
		{
			new_ais->push_back (wrap_var_name (*i));
		}

		result = new AST::Variable(target, variable_name, new_ais);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Reflection* fold_impl_reflection(MIR::Reflection* orig, AST::VARIABLE_NAME* variable_name) 
	{
		AST::Reflection* result;
		result = new AST::Reflection (wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Pre_op* fold_impl_pre_op(MIR::Pre_op* orig, AST::OP* op, AST::Variable* variable) 
	{
		AST::Pre_op* result;
		result = new AST::Pre_op(op, variable);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Array* fold_impl_array(MIR::Array* orig, List<AST::Array_elem*>* array_elems) 
	{
		AST::Array* result;
		result = new AST::Array(array_elems);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Array_elem* fold_impl_array_elem(MIR::Array_elem* orig, AST::Expr* key, bool is_ref, AST::Expr* val) 
	{
		AST::Array_elem* result;
		result = new AST::Array_elem(key, is_ref, val);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method_invocation* fold_impl_method_invocation(MIR::Method_invocation* orig, AST::Target* target, AST::Method_name* method_name, List<AST::Actual_parameter*>* actual_parameters) 
	{
		AST::Method_invocation* result;
		result = new AST::Method_invocation(target, method_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Actual_parameter* fold_impl_actual_parameter(MIR::Actual_parameter* orig, bool is_ref, AST::Target* target, AST::Variable_name* var_name, List<AST::VARIABLE_NAME*>* array_indices) 
	{
		AST::Actual_parameter* result;
		result = new AST::Actual_parameter(is_ref, new AST::Variable (target, var_name, wrap_var_list (array_indices)));
		result->attrs = orig->attrs;
		return result;
	}

	AST::New* fold_impl_new(MIR::New* orig, AST::Class_name* class_name, List<AST::Actual_parameter*>* actual_parameters) 
	{
		AST::New* result;
		result = new AST::New(class_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::HT_ITERATOR* fold_ht_iterator (MIR::HT_ITERATOR* orig)
	{
		AST::HT_ITERATOR* result;
		result = new AST::HT_ITERATOR (orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::CLASS_NAME* fold_class_name(MIR::CLASS_NAME* orig) 
	{
		AST::CLASS_NAME* result;
		result = new AST::CLASS_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::INTERFACE_NAME* fold_interface_name(MIR::INTERFACE_NAME* orig) 
	{
		AST::INTERFACE_NAME* result;
		result = new AST::INTERFACE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::METHOD_NAME* fold_method_name(MIR::METHOD_NAME* orig) 
	{
		AST::METHOD_NAME* result;
		result = new AST::METHOD_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::VARIABLE_NAME* fold_variable_name(MIR::VARIABLE_NAME* orig) 
	{
		AST::VARIABLE_NAME* result;
		result = new AST::VARIABLE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::LABEL_NAME* fold_label_name(MIR::LABEL_NAME* orig) 
	{
		AST::LABEL_NAME* result;
		result = new AST::LABEL_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::INT* fold_int(MIR::INT* orig) 
	{
		AST::INT* result;
		result = new AST::INT(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::REAL* fold_real(MIR::REAL* orig) 
	{
		AST::REAL* result;
		result = new AST::REAL(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::STRING* fold_string(MIR::STRING* orig) 
	{
		AST::STRING* result;
		result = new AST::STRING(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::BOOL* fold_bool(MIR::BOOL* orig) 
	{
		AST::BOOL* result;
		result = new AST::BOOL(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::NIL* fold_nil(MIR::NIL* orig) 
	{
		AST::NIL* result;
		result = new AST::NIL();
		result->attrs = orig->attrs;
		return result;
	}

	AST::OP* fold_op(MIR::OP* orig) 
	{
		AST::OP* result;
		result = new AST::OP(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::CAST* fold_cast(MIR::CAST* orig) 
	{
		AST::CAST* result;
		result = new AST::CAST(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::CONSTANT_NAME* fold_constant_name(MIR::CONSTANT_NAME* orig) 
	{
		AST::CONSTANT_NAME* result;
		result = new AST::CONSTANT_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	~MIR_to_AST () {}
};

#endif // PHC_MIR_TO_AST_H 
