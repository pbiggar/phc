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
#include "lib/Object.h"

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
class HIR_to_MIR : virtual public GC_obj, public HIR::Fold
<
 MIR::Node*,					// Actual_parameter*
 MIR::Array_access*,			// Array_access*
 MIR::Array_next*,			// Array_next*
 MIR::Assign_array*,			// Assign_array*
 MIR::Assign_field*,			// Assign_field*
 MIR::Assign_next*,			// Assign_next*
 MIR::Assign_var*,			// Assign_var*
 MIR::Assign_var_var*,		// Assign_var_var*
 MIR::Attr_mod*,				// Attr_mod*
 MIR::Attribute*,				// Attribute*
 MIR::BOOL*,					// BOOL*
 MIR::Bin_op*,					// Bin_op*
 MIR::Statement*,				// Break*
 MIR::CAST*,					// CAST*
 MIR::CLASS_NAME*,			// CLASS_NAME*
 MIR::CONSTANT_NAME*,		// CONSTANT_NAME*
 MIR::Cast*,					// Cast*
 MIR::Catch*,					// Catch*
 MIR::Class_def*,				// Class_def*
 MIR::Class_mod*,				// Class_mod*
 MIR::Class_name*,			// Class_name*
 MIR::Constant*,				// Constant*
 MIR::Statement*,				// Continue*
 MIR::Eval_expr*,				// Eval_expr*
 MIR::Expr*,					// Expr*
 MIR::FIELD_NAME*,			// FIELD_NAME*
 MIR::None*,					// FOREIGN*
 MIR::Field_access*,			// Field_access*
 MIR::Field_name*,			// Field_name*
 MIR::Statement*,				// Foreach*
 MIR::Formal_parameter*,	// Formal_parameter*
 MIR::Global*,					// Global*
 MIR::INT*,						// INT*
 MIR::INTERFACE_NAME*,		// INTERFACE_NAME*
 MIR::Identifier*,			// Identifier*
 MIR::Statement*,				// If*
 MIR::Instanceof*,			// Instanceof*
 MIR::Interface_def*,		// Interface_def*
 MIR::Literal*,				// Literal*
 MIR::Statement*,				// Loop*
 MIR::METHOD_NAME*,			// METHOD_NAME*
 MIR::Member*,					// Member*
 MIR::Method*,					// Method*
 MIR::Expr*,					// Method_invocation*
 MIR::Method_mod*,			// Method_mod*
 MIR::Method_name*,			// Method_name*
 MIR::NIL*,						// NIL*
 MIR::Name_with_default*,	// Name_with_default*
 MIR::New*,						// New*
 MIR::Node*,					// Node*
 MIR::OP*,						// OP*
 MIR::PHP_script*,			// PHP_script*
 MIR::Pre_op*,					// Pre_op*
 MIR::REAL*,					// REAL*
 MIR::Return*,					// Return*
 MIR::Rvalue*,					// Rvalue*
 MIR::STRING*,					// STRING*
 MIR::Signature*,				// Signature*
 MIR::Statement*,				// Statement*
 MIR::Static_array*,			// Static_array*
 MIR::Static_array_elem*,	// Static_array_elem*
 MIR::Static_array_key*,	// Static_array_key*
 MIR::Static_declaration*,	// Static_declaration*
 MIR::Static_value*,			// Static_value*
 MIR::Target*,					// Target*
 MIR::Throw*,					// Throw*
 MIR::Try*,						// Try*
 MIR::Type*,					// Type*
 MIR::Unary_op*,				// Unary_op*
 MIR::VARIABLE_NAME*,		// VARIABLE_NAME*
 MIR::Node*,					// Variable_actual_parameter
 MIR::Variable_class*,		// Variable_class*
 MIR::Variable_field*,		// Variable_field*
 MIR::Variable_method*,		// Variable_method*
 MIR::Variable_name*,		// Variable_name*
 MIR::Variable_variable*	// Variable_variable*
>		
{
	MIR::Statement* foreign_statement;
	MIR::Expr* foreign_expr;
	MIR::Unset* unset;

public:
	HIR_to_MIR ()
	{
		foreign_expr = NULL;
		foreign_statement = NULL;
		unset = NULL;
	}

	void copy_attrs (MIR::Node* target, HIR::Node* source)
	{
		target->attrs->clone_all_from (source->attrs);
		target->attrs->erase_with_prefix ("phc.hir");
	}

	using parent::fold_method_name;

public:
	MIR::PHP_script* fold_impl_php_script(HIR::PHP_script* orig, MIR::Statement_list* statements) 
	{
		MIR::PHP_script* result;
		result = new MIR::PHP_script(statements);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Class_def* fold_impl_class_def(HIR::Class_def* orig, MIR::Class_mod* class_mod, MIR::CLASS_NAME* class_name, MIR::CLASS_NAME* extends, MIR::INTERFACE_NAME_list* implements, MIR::Member_list* members) 
	{
		MIR::Class_def* result;
		result = new MIR::Class_def(class_mod, class_name, extends, implements, members);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Class_mod* fold_impl_class_mod(HIR::Class_mod* orig, bool is_abstract, bool is_final) 
	{
		MIR::Class_mod* result;
		result = new MIR::Class_mod(is_abstract, is_final);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Interface_def* fold_impl_interface_def(HIR::Interface_def* orig, MIR::INTERFACE_NAME* interface_name, MIR::INTERFACE_NAME_list* extends, MIR::Member_list* members) 
	{
		MIR::Interface_def* result;
		result = new MIR::Interface_def(interface_name, extends, members);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Method* fold_impl_method(HIR::Method* orig, MIR::Signature* signature, MIR::Statement_list* statements) 
	{
		MIR::Method* result;
		result = new MIR::Method(signature, statements);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Signature* fold_impl_signature(HIR::Signature* orig, MIR::Method_mod* method_mod, bool return_by_ref, MIR::METHOD_NAME* method_name, MIR::Formal_parameter_list* formal_parameters) 
	{
		MIR::Signature* result;
		// The HIR doesnt have a pass_rest_by_ref field
		result = new MIR::Signature(method_mod, false, return_by_ref, method_name, formal_parameters);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Method_mod* fold_impl_method_mod(HIR::Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		MIR::Method_mod* result;
		result = new MIR::Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Formal_parameter* fold_impl_formal_parameter(HIR::Formal_parameter* orig, MIR::Type* type, bool is_ref, MIR::Name_with_default* var) 
	{
		MIR::Formal_parameter* result;
		result = new MIR::Formal_parameter(type, is_ref, var);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Type* fold_impl_type(HIR::Type* orig, MIR::CLASS_NAME* class_name) 
	{
		MIR::Type* result;
		result = new MIR::Type(class_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Attribute* fold_impl_attribute(HIR::Attribute* orig, MIR::Attr_mod* attr_mod, MIR::Name_with_default* var) 
	{
		MIR::Attribute* result;
		result = new MIR::Attribute(attr_mod, var);
		copy_attrs (result, orig);
		// Attributes *must* have default values
		if(result->var->default_value == NULL)
			result->var->default_value = new MIR::NIL();
		return result;
	}

	MIR::Attr_mod* fold_impl_attr_mod(HIR::Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		MIR::Attr_mod* result;
		result = new MIR::Attr_mod(is_public, is_protected, is_private, is_static, is_const);
		copy_attrs (result, orig);
		return result;
	}
	
	MIR::Name_with_default* fold_impl_name_with_default(HIR::Name_with_default* orig, MIR::VARIABLE_NAME* variable_name, MIR::Static_value* static_value) 
	{ 
		MIR::Name_with_default* result;
		result = new MIR::Name_with_default(variable_name, static_value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Return* fold_impl_return(HIR::Return* orig, MIR::Rvalue* rvalue) 
	{
		MIR::Return* result;
		result = new MIR::Return(rvalue);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Static_declaration* fold_impl_static_declaration(HIR::Static_declaration* orig, MIR::Name_with_default* var) 
	{
		MIR::Static_declaration* result;
		result = new MIR::Static_declaration(var);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Global* fold_impl_global(HIR::Global* orig, MIR::Variable_name* variable_name) 
	{
		MIR::Global* result;
		result = new MIR::Global(variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Try* fold_impl_try(HIR::Try* orig, MIR::Statement_list* statements, MIR::Catch_list* catches) 
	{
		MIR::Try* result;
		result = new MIR::Try(statements, catches);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Catch* fold_impl_catch(HIR::Catch* orig, MIR::CLASS_NAME* class_name, MIR::VARIABLE_NAME* variable_name, MIR::Statement_list* statements) 
	{
		MIR::Catch* result;
		result = new MIR::Catch(class_name, variable_name, statements);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Throw* fold_impl_throw(HIR::Throw* orig, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Throw* result;
		result = new MIR::Throw(variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Eval_expr* fold_impl_eval_expr (HIR::Eval_expr* orig, MIR::Expr* expr) 
	{
		MIR::Eval_expr* result;
		result = new MIR::Eval_expr (expr);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Assign_var* fold_impl_assign_var (HIR::Assign_var* orig, MIR::VARIABLE_NAME* lhs, bool is_ref, MIR::Expr* rhs) 
	{
		MIR::Assign_var* result;
		result = new MIR::Assign_var (lhs, is_ref, rhs);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Assign_var_var* fold_impl_assign_var_var (HIR::Assign_var_var* orig, MIR::VARIABLE_NAME* lhs, bool is_ref, MIR::Rvalue* rhs) 
	{
		MIR::Assign_var_var* result;
		result = new MIR::Assign_var_var(lhs, is_ref, rhs);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Assign_array* fold_impl_assign_array (HIR::Assign_array* orig, MIR::VARIABLE_NAME* lhs, MIR::Rvalue* index, bool is_ref, MIR::Rvalue* rhs) 
	{
		MIR::Assign_array* result;
		result = new MIR::Assign_array (lhs, index, is_ref, rhs);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Assign_field* fold_impl_assign_field (HIR::Assign_field* orig, MIR::Target* target, MIR::Field_name* field_name, bool is_ref, MIR::Rvalue* rhs) 
	{
		MIR::Assign_field* result;
		result = new MIR::Assign_field (target, field_name, is_ref, rhs);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Assign_next* fold_impl_assign_next (HIR::Assign_next* orig, MIR::VARIABLE_NAME* lhs, bool is_ref, MIR::Rvalue* rhs) 
	{
		MIR::Assign_next* result;
		result = new MIR::Assign_next (lhs, is_ref, rhs);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Expr* fold_expr (HIR::Expr* orig)
	{
		if (!isa<HIR::FOREIGN> (orig))
			return parent::fold_expr (orig);

		fold_foreign (dyc<HIR::FOREIGN> (orig));
		MIR::Expr* expr = this->foreign_expr;
		assert (expr);
		this->foreign_expr = NULL;
		return expr;
	}

	MIR::Statement* fold_statement (HIR::Statement* orig)
	{
		if (isa<HIR::FOREIGN> (orig))
		{
			fold_foreign (dyc<HIR::FOREIGN> (orig));
			MIR::Statement* statement = this->foreign_statement;
			assert (statement);
			this->foreign_statement = NULL;
			return statement;
		}
		else if (orig->match (
			new HIR::Eval_expr (
				new HIR::Method_invocation (
					NULL,
					new HIR::METHOD_NAME ("unset"),
					NULL))))
		{
			parent::fold_statement (orig);
			MIR::Unset* unset = this->unset;
			assert (unset);
			this->unset = NULL;
			return unset;
		}
		else
			return parent::fold_statement (orig);
	}

	MIR::None* fold_foreign (HIR::FOREIGN* orig)
	{
		assert (foreign_statement == NULL);
		assert (foreign_expr == NULL);

		// Save the result, and fetch it from the caller.
		if (isa<MIR::Statement> (orig->value))
			foreign_statement = dyc<MIR::Statement> (orig->value);
		else if (isa<MIR::Expr> (orig->value))
			foreign_expr = dyc<MIR::Expr> (orig->value);
		else assert (0);

		return NULL;
	}

	MIR::Cast* fold_impl_cast(HIR::Cast* orig, MIR::CAST* cast, MIR::VARIABLE_NAME* expr) 
	{
		MIR::Cast* result;
		result = new MIR::Cast(cast, expr);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Unary_op* fold_impl_unary_op(HIR::Unary_op* orig, MIR::OP* op, MIR::VARIABLE_NAME* expr) 
	{
		MIR::Unary_op* result;
		result = new MIR::Unary_op(op, expr);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Bin_op* fold_impl_bin_op(HIR::Bin_op* orig, MIR::Rvalue* left, MIR::OP* op, MIR::Rvalue* right) 
	{
		MIR::Bin_op* result;
		result = new MIR::Bin_op(left, op, right);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Constant* fold_impl_constant(HIR::Constant* orig, MIR::CLASS_NAME* class_name, MIR::CONSTANT_NAME* constant_name) 
	{
		MIR::Constant* result;
		result = new MIR::Constant(class_name, constant_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Instanceof* fold_impl_instanceof(HIR::Instanceof* orig, MIR::VARIABLE_NAME* variable_name, MIR::Class_name* class_name) 
	{
		MIR::Instanceof* result;
		result = new MIR::Instanceof(variable_name, class_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Array_access* fold_impl_array_access(HIR::Array_access* orig, MIR::VARIABLE_NAME* variable_name, MIR::Rvalue* index)
	{
		MIR::Array_access* result;
		result = new MIR::Array_access(variable_name, index);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Array_next* fold_impl_array_next (HIR::Array_next* orig, MIR::VARIABLE_NAME* variable_name)
	{
		MIR::Array_next* result;
		result = new MIR::Array_next (variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Variable_variable* fold_impl_variable_variable(HIR::Variable_variable* orig, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Variable_variable* result;
		result = new MIR::Variable_variable(variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Variable_method* fold_impl_variable_method(HIR::Variable_method* orig, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Variable_method* result;
		result = new MIR::Variable_method(variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Variable_class* fold_impl_variable_class(HIR::Variable_class* orig, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Variable_class* result;
		result = new MIR::Variable_class(variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Variable_field* fold_impl_variable_field(HIR::Variable_field* orig, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Variable_field* result;
		result = new MIR::Variable_field(variable_name);
		copy_attrs (result, orig);
		return result;
	}

	

	MIR::Field_access* fold_impl_field_access (HIR::Field_access* orig, MIR::Target* target, MIR::Field_name* field_name) 
	{
		MIR::Field_access* result;
		result = new MIR::Field_access(target, field_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Pre_op* fold_impl_pre_op(HIR::Pre_op* orig, MIR::OP* op, MIR::VARIABLE_NAME* variable_name) 
	{
		MIR::Pre_op* result;
		result = new MIR::Pre_op(op, variable_name);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Static_array* fold_impl_static_array(HIR::Static_array* orig, MIR::Static_array_elem_list* static_array_elems)
	{
		MIR::Static_array* result;
		result = new MIR::Static_array (static_array_elems);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Static_array_elem* fold_impl_static_array_elem(HIR::Static_array_elem* orig, MIR::Static_array_key* key, bool is_ref, MIR::Static_value* val)
	{
		MIR::Static_array_elem* result;
		result = new MIR::Static_array_elem (key, is_ref, val);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Expr* fold_impl_method_invocation(HIR::Method_invocation* orig, MIR::Target* target, MIR::Method_name* method_name, MIR::Node_list* actual_parameters) 
	{
		// Unset and Isset are special and gets put straight into the MIR.
		MIR::METHOD_NAME* mn = dynamic_cast <MIR::METHOD_NAME*> (method_name);
		if (target == NULL
			&& mn
			&& (*mn->value == "unset"
				||*mn->value == "isset"))
		{
			assert (actual_parameters->size () == 1);

			HIR::Variable_actual_parameter* ap = dyc<HIR::Variable_actual_parameter> (orig->actual_parameters->front ());

			MIR::Rvalue_list* array_indices = new MIR::Rvalue_list;
			foreach (HIR::Rvalue* rvalue, *ap->array_indices)
				array_indices->push_back (fold_rvalue (rvalue));

			if (*mn->value == "unset")
			{
				unset = new MIR::Unset (
					ap->target ? fold_target (ap->target) : NULL,
					parent::fold_variable_name (ap->variable_name),
					array_indices);
				copy_attrs (unset, orig);
				return NULL;
			}
			else
			{
				MIR::Isset* result;
				result = new MIR::Isset (
					ap->target ? fold_target (ap->target) : NULL,
					parent::fold_variable_name (ap->variable_name),
					array_indices);
				copy_attrs (result, orig);
				return result;
			}
		}

		MIR::Actual_parameter_list* params = new MIR::Actual_parameter_list;
		foreach (MIR::Node* node, *actual_parameters)
		{
			if (isa<MIR::Literal> (node))
				params->push_back (new MIR::Actual_parameter (false, dyc <MIR::Literal> (node)));
			else
				params->push_back (dyc<MIR::Actual_parameter> (node));
		}

		MIR::Method_invocation* result;
		result = new MIR::Method_invocation(
			target, 
			method_name,
			params);
		copy_attrs (result, orig);
		return result;
	}

	MIR::Node* fold_impl_variable_actual_parameter (HIR::Variable_actual_parameter* orig, bool is_ref, MIR::Target* target, MIR::Variable_name* variable_name, MIR::Rvalue_list* array_indices)
	{
		// Unset and Isset can still have targets, var-vars and array_indices, so just ignore them.
		if (target
			|| array_indices->size () > 0
			|| isa<MIR::Variable_variable> (variable_name))
			return NULL;

		MIR::Actual_parameter* result;
		result = new MIR::Actual_parameter (is_ref, dyc<MIR::VARIABLE_NAME> (variable_name));
		copy_attrs (result, orig);
		return result;
	}

	MIR::New* fold_impl_new(HIR::New* orig, MIR::Class_name* class_name, MIR::Node_list* actual_parameters) 
	{
		MIR::New* result;
		result = new MIR::New(
			class_name, 
			rewrap_list<MIR::Actual_parameter> (actual_parameters));
		copy_attrs (result, orig);
		return result;
	}

	MIR::CLASS_NAME* fold_class_name(HIR::CLASS_NAME* orig) 
	{
		MIR::CLASS_NAME* result;
		result = new MIR::CLASS_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::INTERFACE_NAME* fold_interface_name(HIR::INTERFACE_NAME* orig) 
	{
		MIR::INTERFACE_NAME* result;
		result = new MIR::INTERFACE_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::METHOD_NAME* fold_method_name(HIR::METHOD_NAME* orig) 
	{
		MIR::METHOD_NAME* result;
		result = new MIR::METHOD_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::VARIABLE_NAME* fold_variable_name(HIR::VARIABLE_NAME* orig) 
	{
		MIR::VARIABLE_NAME* result;
		result = new MIR::VARIABLE_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::INT* fold_int(HIR::INT* orig) 
	{
		MIR::INT* result;
		result = new MIR::INT(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::REAL* fold_real(HIR::REAL* orig) 
	{
		MIR::REAL* result;
		result = new MIR::REAL(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::STRING* fold_string(HIR::STRING* orig) 
	{
		MIR::STRING* result;
		result = new MIR::STRING(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::BOOL* fold_bool(HIR::BOOL* orig) 
	{
		MIR::BOOL* result;
		result = new MIR::BOOL(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::NIL* fold_nil(HIR::NIL* orig) 
	{
		MIR::NIL* result;
		result = new MIR::NIL();
		copy_attrs (result, orig);
		return result;
	}

	MIR::OP* fold_op(HIR::OP* orig) 
	{
		MIR::OP* result;
		result = new MIR::OP(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::CAST* fold_cast(HIR::CAST* orig) 
	{
		MIR::CAST* result;
		result = new MIR::CAST(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::CONSTANT_NAME* fold_constant_name(HIR::CONSTANT_NAME* orig) 
	{
		MIR::CONSTANT_NAME* result;
		result = new MIR::CONSTANT_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	MIR::FIELD_NAME* fold_field_name(HIR::FIELD_NAME* orig) 
	{
		MIR::FIELD_NAME* result;
		result = new MIR::FIELD_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}



 	~HIR_to_MIR () {}
};

#endif // PHC_HIR_TO_MIR_H 
