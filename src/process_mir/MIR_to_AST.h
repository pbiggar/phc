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
#include "lib/Stack.h"

/*
 * Those MIR nodes that should no longer appear in the AST do not have an
 * implementation in this translation, so that we inherit the default assert(0)
 * implementation from MIR_fold. However, to satisfy the typechecker, we must
 * still provide a reasonble type for these nodes. For example, the type we
 * specify for For (which does not have a corresponding AST construct) is
 * simplify AST::Statement*. For some constructs, specifying AST::Node*
 * suffices.
 */
class MIR_to_AST : virtual public GC_obj, public MIR::Fold
<
 AST::Actual_parameter*,	// Actual_parameter*
 AST::Variable*,				// Array_access*
 AST::Variable*,				// Array_next*
 AST::Eval_expr*,				// Assign_array*
 AST::Eval_expr*,				// Assign_field*
 AST::Eval_expr*,				// Assign_next*
 AST::Eval_expr*,				// Assign_var*
 AST::Eval_expr*,				// Assign_var_var*
 AST::Attr_mod*,				// Attr_mod*
 AST::Attribute*,				// Attribute*
 AST::BOOL*,					// BOOL*
 AST::Bin_op*,					// Bin_op*
 AST::FOREIGN*,				// Branch*
 AST::CAST*,					// CAST*
 AST::CLASS_NAME*,			// CLASS_NAME*
 AST::CONSTANT_NAME*,		// CONSTANT_NAME*
 AST::Cast*,					// Cast*
 AST::Catch*,					// Catch*
 AST::FOREIGN*,				// Class_alias*
 AST::Class_def*,				// Class_def*
 AST::Class_mod*,				// Class_mod*
 AST::Class_name*,			// Class_name*
 AST::Constant*,				// Constant*
 AST::Eval_expr*,				// Eval_expr*
 AST::Expr*,					// Expr*
 AST::VARIABLE_NAME*,		// FIELD_NAME*
 AST::None*,					// FOREIGN* -- Expr or Statement
 AST::Variable*,				// Field_access*
 AST::Variable_name*,		// Field_name*
 AST::FOREIGN*,				// Foreach_end*
 AST::FOREIGN*,				// Foreach_get_key*
 AST::FOREIGN*,				// Foreach_get_val*
 AST::FOREIGN*,				// Foreach_has_key*
 AST::FOREIGN*,				// Foreach_next*
 AST::FOREIGN*,				// Foreach_reset*
 AST::Formal_parameter*,	// Formal_parameter*
 AST::Global*,					// Global*
 AST::FOREIGN*,				// Goto*
 AST::Identifier*,			// HT_ITERATOR* - is really a FOREIGN
 AST::INT*,						// INT*
 AST::INTERFACE_NAME*,		// INTERFACE_NAME*
 AST::Identifier*,			// Identifier*
 AST::Instanceof*,			// Instanceof*
 AST::FOREIGN*,				// Interface_alias*
 AST::Interface_def*,		// Interface_def*
 AST::Method_invocation*,	// Isset*
 AST::Identifier*,			// LABEL_NAME*
 AST::FOREIGN*,				// Label*
 AST::Literal*,				// Literal*
 AST::METHOD_NAME*,			// METHOD_NAME*
 AST::Member*,					// Member*
 AST::Method*,					// Method*
 AST::FOREIGN*,				// Method_alias*
 AST::Method_invocation*,	// Method_invocation*
 AST::Method_mod*,			// Method_mod*
 AST::Method_name*,			// Method_name*
 AST::NIL*,						// NIL*
 AST::Name_with_default*,	// Name_with_default*
 AST::New*,						// New*
 AST::Node*,					// Node*
 AST::OP*,						// OP*
 AST::Node*,					// PARAM_INDEX*
 AST::PHP_script*,			// PHP_script*
 AST::FOREIGN*,				// Param_is_ref*
 AST::Eval_expr*,				// Pre_op*
 AST::REAL*,					// REAL*
 AST::Return*,					// Return*
 AST::Expr*,					// Rvalue*
 AST::STRING*,					// STRING*
 AST::Signature*,				// Signature*
 AST::Statement*,				// Statement*
 AST::Array*,					// Static_array*
 AST::Array_elem*,			// Static_array_elem*
 AST::Expr*,					// Static_array_key*
 AST::Static_declaration*,	// Static_declaration*
 AST::Expr*,					// Static_value*
 AST::Node*,					// Target* - Targets have VARIABLE_NAME expr, so wont fold nicely to AST::Target
 AST::Throw*,					// Throw*
 AST::Try*,						// Try*
 AST::Type*,					// Type*
 AST::Unary_op*,				// Unary_op*
 AST::Eval_expr*,				// Unset*
 AST::None*,					// VARIABLE_NAME* - Variable or Variable_name
 AST::Reflection*,			// Variable_class*
 AST::Reflection*,			// Variable_field*
 AST::Reflection*,			// Variable_method*
 AST::Variable_name*,		// Variable_name*
 AST::None*						// Variable_variable* - Reflection or Variable
>
{
	AST::Reflection* reflection;
	Stack<AST::VARIABLE_NAME*> var_names;
	AST::Statement* foreign_statement;

	// Indicates non-NULL for target.
	AST::None* non_null_ptr;

public:
	MIR_to_AST ()
	{
		reflection = NULL;
		foreign_statement = NULL;

		// We can't instantiate a None (must use a pointer sized object)
		non_null_ptr = reinterpret_cast <AST::None*> (new AST::INT (0));
	}

	AST::VARIABLE_NAME* get_var_name ()
	{
		assert (!var_names.empty());
		AST::VARIABLE_NAME* result = var_names.top ();
		var_names.pop ();
		return result;
	}

	AST::Variable* wrap_var_name (AST::Node* var_name)
	{
		if (var_name == NULL)
			return NULL;

		return new AST::Variable (get_var_name ());
	}

	AST::Expr_list* wrap_var_name_list (AST::None_list* var_names)
	{
		AST::Expr_list* result = new AST::Expr_list;
		foreach (AST::None* n, *var_names)
		{
			// Process in reverse order off the stack
			result->push_front (wrap_var_name (n));
		}
		return result;
	}

	AST::Expr_list* wrap_var_name_in_list (AST::None* var_name)
	{
		// Dont turn $x into $x[]
		if (var_name == NULL)
			return new AST::Expr_list;

		return wrap_var_name_list (new AST::None_list (var_name));
	}

	/* VARIABLE_NAMEs are converted to None. CLASS_NAMEs are returned in one
	 * piece, but their static type is Node. However, Target is optional, so
	 * NULL indicates that there is no target. Therefore, we cannot use NULL as
	 * the return type of VARIABLE_NAME. We cant use an arbitrary integer in
	 * case a pointer of the same value exists, so we allocate non_null_ptr,
	 * which cannot have the same address as any other value.*/ 
	AST::Target* wrap_target (AST::Node* target)
	{
		// Target is generally optional
		if (target == NULL)
			return NULL;

		// VARIABLE_NAME returns that it is a non-null
		if (target == non_null_ptr)
			return wrap_var_name (target);

		return dyc<AST::CLASS_NAME> (target);
	}

public:

	AST::PHP_script* fold_impl_php_script(MIR::PHP_script* orig, AST::Statement_list* statements) 
	{
		// If we forget to pop a var_name, there will be some left on the stack.
		assert (var_names.size() == 0);

		AST::PHP_script* result;
		result = new AST::PHP_script(statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Class_def* fold_impl_class_def(MIR::Class_def* orig, AST::Class_mod* class_mod, AST::CLASS_NAME* class_name, AST::CLASS_NAME* extends, AST::INTERFACE_NAME_list* implements, AST::Member_list* members) 
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

	AST::Interface_def* fold_impl_interface_def(MIR::Interface_def* orig, AST::INTERFACE_NAME* interface_name, AST::INTERFACE_NAME_list* extends, AST::Member_list* members) 
	{
		AST::Interface_def* result;
		result = new AST::Interface_def(interface_name, extends, members);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method* fold_impl_method(MIR::Method* orig, AST::Signature* signature, AST::Statement_list* statements) 
	{
		AST::Method* result;
		result = new AST::Method(signature, statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Signature* fold_impl_signature(MIR::Signature* orig, AST::Method_mod* method_mod, bool pass_rest_by_ref, bool return_by_ref, AST::METHOD_NAME* method_name, AST::Formal_parameter_list* formal_parameters) 
	{
		AST::Signature* result;
		result = new AST::Signature(method_mod, return_by_ref, method_name, formal_parameters);
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
		result = new AST::Attribute(attr_mod, new AST::Name_with_default_list (var));
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
	
	AST::Name_with_default* fold_impl_name_with_default(MIR::Name_with_default* orig, AST::None* variable_name, AST::Expr* expr) 
	{ 
		AST::Name_with_default* result;
		result = new AST::Name_with_default(get_var_name (), expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Return* fold_impl_return(MIR::Return* orig, AST::Expr* expr) 
	{
		AST::Return* result;
		result = new AST::Return (expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Static_declaration* fold_impl_static_declaration(MIR::Static_declaration* orig, AST::Name_with_default* var) 
	{
		AST::Static_declaration* result;
		result = new AST::Static_declaration(new AST::Name_with_default_list (var));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Global* fold_impl_global(MIR::Global* orig, AST::Variable_name* variable_name) 
	{
		AST::Global* result;
		result = new AST::Global(new AST::Variable_name_list (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Try* fold_impl_try(MIR::Try* orig, AST::Statement_list* statements, AST::Catch_list* catches) 
	{
		AST::Try* result;
		result = new AST::Try(statements, catches);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Catch* fold_impl_catch(MIR::Catch* orig, AST::CLASS_NAME* class_name, AST::None* variable_name, AST::Statement_list* statements) 
	{
		AST::Catch* result;
		result = new AST::Catch(class_name, get_var_name (), statements);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Throw* fold_impl_throw(MIR::Throw* orig, AST::None* variable_name) 
	{
		AST::Throw* result;
		result = new AST::Throw(wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Eval_expr* fold_impl_assign_var (MIR::Assign_var* orig, AST::None* lhs, bool is_ref, AST::Expr* rhs) 
	{
		AST::Assignment* result;
		result = new AST::Assignment(
			wrap_var_name (lhs),
			is_ref, 
			rhs);
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_assign_var_var (MIR::Assign_var_var* orig, AST::None* lhs, bool is_ref, AST::Expr* rhs) 
	{
		AST::VARIABLE_NAME* lhs_var = get_var_name ();

		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				NULL,
				new AST::Reflection (
					new AST::Variable (lhs_var)),
				new AST::Expr_list), 
			is_ref,
			rhs);
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_assign_array (MIR::Assign_array* orig, AST::None* lhs, AST::Expr* index, bool is_ref, AST::Expr* rhs) 
	{
		AST::VARIABLE_NAME* lhs_var = get_var_name ();

		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				NULL,
				lhs_var,
				new AST::Expr_list (index)),
			is_ref,
			rhs);
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_assign_next (MIR::Assign_next* orig, AST::None* lhs, bool is_ref, AST::Expr* rhs) 
	{
		AST::VARIABLE_NAME* lhs_var = get_var_name ();

		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				NULL,
				lhs_var,
				new AST::Expr_list (
					NULL)),
			is_ref,
			rhs);
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_assign_field (MIR::Assign_field* orig, AST::Node* target, AST::Variable_name* lhs, bool is_ref, AST::Expr* rhs) 
	{
		// The order is important.
		AST::Target* target_var = wrap_target (target);

		AST::Assignment* result;
		result = new AST::Assignment(
			new AST::Variable (
				target_var,
				lhs,
				new AST::Expr_list),
			is_ref,
			rhs);
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Eval_expr* fold_impl_eval_expr (MIR::Eval_expr* orig, AST::Expr* expr) 
	{
		AST::Eval_expr* result;
		result = new AST::Eval_expr(expr);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Cast* fold_impl_cast(MIR::Cast* orig, AST::CAST* cast, AST::None* variable_name) 
	{
		AST::Cast* result;
		result = new AST::Cast(cast, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Unary_op* fold_impl_unary_op(MIR::Unary_op* orig, AST::OP* op, AST::None* variable_name) 
	{
		AST::Unary_op* result;
		result = new AST::Unary_op(op, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Bin_op* fold_impl_bin_op(MIR::Bin_op* orig, AST::Expr* left, AST::OP* op, AST::Expr* right) 
	{
		AST::Bin_op* result;
		result = new AST::Bin_op(left, op, right);
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

	AST::Instanceof* fold_impl_instanceof(MIR::Instanceof* orig, AST::None* variable_name, AST::Class_name* class_name) 
	{
		AST::Instanceof* result;
		result = new AST::Instanceof(wrap_var_name (variable_name), class_name);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Variable* fold_impl_array_access (MIR::Array_access* orig, AST::None* variable_name, AST::Expr* index)
	{
		AST::Variable* result;
		result = new AST::Variable (
			NULL, 
			get_var_name (), 
			new AST::Expr_list (index));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Variable* fold_impl_array_next (MIR::Array_next* orig, AST::None* variable_name)
	{
		AST::Variable* result;
		result = new AST::Variable (
			NULL, 
			get_var_name (), 
			new AST::Expr_list (NULL));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Variable* fold_impl_field_access (MIR::Field_access* orig, AST::Node* target, AST::Variable_name* variable_name)
	{
		AST::Variable* result;
		result = new AST::Variable(
			wrap_target (target),
			variable_name,
			new AST::Expr_list);
		result->attrs = orig->attrs;
		return result;
	}

	/* A variable-variable may be converted to a Variable (for Exprs) or a
	 * Reflection (for Variable_name).
	 */
	AST::Variable_name* fold_variable_name (MIR::Variable_name* orig)
	{
		if (isa<MIR::Variable_variable> (orig))
		{
			fold_variable_variable (dyc<MIR::Variable_variable> (orig));
			AST::Reflection* result = this->reflection;
			assert (result);

			this->reflection = NULL;
			return result;
		}
		else
		{
			fold_variable_name (dyc<MIR::VARIABLE_NAME> (orig));
			return get_var_name ();
		}
	}

	AST::Expr* fold_expr (MIR::Expr* orig)
	{
		if (isa<MIR::Variable_variable> (orig))
		{
			fold_variable_variable (dyc<MIR::Variable_variable> (orig));
			assert (this->reflection);

			AST::Variable* result;
			result = new AST::Variable (
				NULL,
				this->reflection,
				new AST::Expr_list);
			result->attrs = orig->attrs;

			this->reflection = NULL;
			return result;
		}
		else if (isa<MIR::VARIABLE_NAME> (orig))
			return wrap_var_name (fold_variable_name (dyc<MIR::VARIABLE_NAME> (orig)));
		else
			return parent::fold_expr (orig);
	}

	AST::Expr* fold_rvalue (MIR::Rvalue* orig)
	{
		if (isa<MIR::VARIABLE_NAME> (orig))
			return wrap_var_name (fold_variable_name (dyc<MIR::VARIABLE_NAME> (orig)));
		else
			return parent::fold_rvalue (orig);
	}

	AST::None* fold_impl_variable_variable(MIR::Variable_variable* orig, AST::None* variable_name) 
	{
		// Return NULL, and the users of this use this->reflection.
		assert (this->reflection == NULL);

		AST::Reflection* result;
		result = new AST::Reflection(wrap_var_name (variable_name));
		result->attrs = orig->attrs;

		this->reflection = result;
		return NULL;
	}

	AST::Reflection* fold_impl_variable_method (MIR::Variable_method* orig, AST::None* variable_name) 
	{
		AST::Reflection* result;
		result = new AST::Reflection (wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Reflection* fold_impl_variable_class (MIR::Variable_class* orig, AST::None* variable_name) 
	{
		AST::Reflection* result;
		result = new AST::Reflection (wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Reflection* fold_impl_variable_field (MIR::Variable_field* orig, AST::None* variable_name) 
	{
		AST::Reflection* result;
		result = new AST::Reflection (wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return result;
	}

	AST::Eval_expr* fold_impl_pre_op(MIR::Pre_op* orig, AST::OP* op, AST::None* variable_name)
	{
		AST::Pre_op* result;
		result = new AST::Pre_op(op, wrap_var_name (variable_name));
		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Array* fold_impl_static_array(MIR::Static_array* orig, AST::Array_elem_list* array_elems)
	{
		AST::Array* result;
		result = new AST::Array(array_elems);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Array_elem* fold_impl_static_array_elem(MIR::Static_array_elem* orig, AST::Expr* key, bool is_ref, AST::Expr* val)
	{
		AST::Array_elem* result;
		result = new AST::Array_elem (key, is_ref, val);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Method_invocation* fold_impl_method_invocation(MIR::Method_invocation* orig, AST::Node* target, AST::Method_name* method_name, AST::Actual_parameter_list* actual_parameters) 
	{
		AST::Method_invocation* result;
		result = new AST::Method_invocation(
			wrap_target (target),
			method_name, 
			actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	AST::Actual_parameter* fold_impl_actual_parameter(MIR::Actual_parameter* orig, bool is_ref, AST::Expr* expr)
	{
		AST::Actual_parameter* result;
		result = new AST::Actual_parameter(
			is_ref,
			expr);
		result->attrs = orig->attrs;
		return result;
	}


	AST::New* fold_impl_new(MIR::New* orig, AST::Class_name* class_name, AST::Actual_parameter_list* actual_parameters) 
	{
		AST::New* result;
		result = new AST::New(class_name, actual_parameters);
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

	// Provide public access
	using parent::fold_method_name;

	AST::METHOD_NAME* fold_method_name(MIR::METHOD_NAME* orig) 
	{
		AST::METHOD_NAME* result;
		result = new AST::METHOD_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	AST::None* fold_variable_name(MIR::VARIABLE_NAME* orig) 
	{
		AST::VARIABLE_NAME* result;
		result = new AST::VARIABLE_NAME(orig->value);
		result->attrs = orig->attrs;

		var_names.push (result);

		// See comment in wrap_target ().
		return non_null_ptr;
	}

	AST::VARIABLE_NAME* fold_field_name (MIR::FIELD_NAME* orig) 
	{
		AST::VARIABLE_NAME* result;
		result = new AST::VARIABLE_NAME (orig->value);
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

	AST::Statement* fold_statement (MIR::Statement* orig)
	{
		if (isa<MIR::FOREIGN> (orig))
		{
			fold_foreign (dyc<MIR::FOREIGN> (orig));
			AST::Statement* result = this->foreign_statement;
			assert (result);
			this->foreign_statement = NULL;
			return result;
		}
		else
			return parent::fold_statement (orig);
	}


	/* The only foreign node so far is a while */
	AST::None* fold_foreign (MIR::FOREIGN* orig)
	{
		AST::While* result;
		result = dynamic_cast<AST::While*> (orig->value);
		assert (result);

		foreign_statement = result;
		return NULL;
	}

	/* MIR types without an AST equivalent. */

	AST::FOREIGN* fold_impl_branch(MIR::Branch* orig, AST::None* variable_name, AST::Identifier* iftrue, AST::Identifier* iffalse) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_goto(MIR::Goto* orig, AST::Identifier* label_name) 
	{
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_label(MIR::Label* orig, AST::Identifier* label_name) 
	{
		return new AST::FOREIGN (orig);
	}

	AST::Identifier* fold_label_name(MIR::LABEL_NAME* orig) 
	{
		// do nothing. LABEL_NAMEs are always wrapped, but there will be an
		// attempt to fold them, so we need to supply a definition so that it
		// doesnt fail.
		return NULL;
	}

	AST::FOREIGN* fold_impl_foreach_reset (MIR::Foreach_reset* orig, AST::None* array, AST::Identifier* iter) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_foreach_next (MIR::Foreach_next* orig, AST::None* array, AST::Identifier* iter) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_foreach_end (MIR::Foreach_end* orig, AST::None* array, AST::Identifier* iter) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_foreach_has_key (MIR::Foreach_has_key* orig, AST::None* array, AST::Identifier* iter) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_foreach_get_key (MIR::Foreach_get_key* orig, AST::None* array, AST::Identifier* iter) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_impl_foreach_get_val (MIR::Foreach_get_val* orig, AST::None* array, AST::Identifier* iter) 
	{
		get_var_name ();
		return new AST::FOREIGN (orig);
	}

	AST::Identifier* fold_ht_iterator (MIR::HT_ITERATOR* orig)
	{
		// We dont care what happens to this, since it's always wrapped in another FOREIGN
		return NULL;
	}

	AST::Node* fold_param_index (MIR::PARAM_INDEX* orig)
	{
		// We don't care what happens, since it will be removed by folding a Param_is_ref
		return NULL;
	}

	AST::FOREIGN* fold_param_is_ref (MIR::Param_is_ref* orig)
	{
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_method_alias (MIR::Method_alias* orig)
	{
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_class_alias (MIR::Class_alias* orig)
	{
		return new AST::FOREIGN (orig);
	}

	AST::FOREIGN* fold_interface_alias (MIR::Interface_alias* orig)
	{
		return new AST::FOREIGN (orig);
	}

	AST::Eval_expr* fold_impl_unset (MIR::Unset* orig, AST::Node* target, AST::Variable_name* variable_name, AST::Expr_list* array_indices) 
	{
		AST::Method_invocation* result;
		result = new AST::Method_invocation (
			NULL,
			new AST::METHOD_NAME (s("unset")),
			new AST::Actual_parameter_list (
				new AST::Actual_parameter (
					false,
					new AST::Variable (
						wrap_target (target),
						variable_name,
						array_indices))));

		result->attrs = orig->attrs;
		return new AST::Eval_expr (result);
	}

	AST::Method_invocation* fold_impl_isset (MIR::Isset* orig, AST::Node* target, AST::Variable_name* variable_name, AST::Expr_list* array_indices) 
	{
		AST::Method_invocation* result;
		result = new AST::Method_invocation (
			NULL,
			new AST::METHOD_NAME (s("isset")),
			new AST::Actual_parameter_list (
				new AST::Actual_parameter (
					false,
					new AST::Variable (
						wrap_target (target),
						variable_name,
						array_indices))));

		result->attrs = orig->attrs;
		return result;
	}

	~MIR_to_AST () {}
};

#endif // PHC_MIR_TO_AST_H 
