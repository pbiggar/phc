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
 * specify for For (which does not have a corresponding HIR construct) is
 * simplify HIR::Statement*. For some constructs, specifying HIR::Node*
 * suffices.
 */

class AST_to_HIR : virtual public GC_obj, public AST::Fold
<
 HIR::Actual_parameter*,	// Actual_parameter*
 HIR::Expr*,					// Array*
 HIR::Static_array_elem*,	// Array_elem*
 HIR::Expr*,					// Assignment*
 HIR::Attr_mod*,				// Attr_mod*
 HIR::Attribute*,				// Attribute*
 HIR::BOOL*,					// BOOL*
 HIR::Bin_op*,					// Bin_op*
 HIR::Break*,					// Break*
 HIR::CAST*,					// CAST*
 HIR::CLASS_NAME*,			// CLASS_NAME*
 HIR::CONSTANT_NAME*,		// CONSTANT_NAME*
 HIR::Cast*,					// Cast*
 HIR::Catch*,					// Catch*
 HIR::Class_def*,				// Class_def*
 HIR::Class_mod*,				// Class_mod*
 HIR::Class_name*,			// Class_name*
 HIR::Node*,					// Commented_node*
 HIR::Expr*,					// Conditional_expr*
 HIR::Constant*,				// Constant*
 HIR::Continue*,				// Continue*
 HIR::Identifier*,			// DIRECTIVE_NAME*
 HIR::Statement*,				// Declare*
 HIR::Statement*,				// Directive*
 HIR::Statement*,				// Do*
 HIR::Statement*,				// Eval_expr*
 HIR::Expr*,					// Expr*
 HIR::FOREIGN*,				// FOREIGN*
 HIR::Statement*,				// For*
 HIR::Foreach*,				// Foreach*
 HIR::Formal_parameter*,	// Formal_parameter*
 HIR::Global*,					// Global*
 HIR::INT*,						// INT*
 HIR::INTERFACE_NAME*,		// INTERFACE_NAME*
 HIR::Identifier*,			// Identifier*
 HIR::If*,						// If*
 HIR::Expr*,					// Ignore_errors*
 HIR::Instanceof*,			// Instanceof*
 HIR::Interface_def*,		// Interface_def*
 HIR::Expr*,					// List_assignment*
 HIR::Expr*,					//	List_element*
 HIR::Literal*,				// Literal*
 HIR::METHOD_NAME*,			// METHOD_NAME*
 HIR::Member*,					// Member*
 HIR::Method*,					// Method*
 HIR::Expr*,					// Method_invocation*
 HIR::Method_mod*,			// Method_mod*
 HIR::Method_name*,			// Method_name*
 HIR::NIL*,						// NIL*
 HIR::Name_with_default*,	// Name_with_default*
 HIR::Expr*,					// Nested_list_elements*
 HIR::Expr*,					// New*
 HIR::Node*,					// Node*
 HIR::Statement*,				// Nop*
 HIR::OP*,						// OP*
 HIR::Expr*,					// Op_assignment*
 HIR::PHP_script*,			// PHP_script*
 HIR::Expr*,					// Post_op*
 HIR::Expr*,					// Pre_op*
 HIR::REAL*,					// REAL*
 HIR::None*,					// Reflection*
 HIR::Return*,					// Return*
 HIR::STRING*,					// STRING*
 HIR::Signature*,				// Signature*
 HIR::Node*,					// Source_rep*
 HIR::Statement*,				// Statement*
 HIR::Static_declaration*,	// Static_declaration*
 HIR::Statement*,				// Switch*
 HIR::Node*,					// Switch_case*
 HIR::Node*,					// Target* - HIR::Targets have VARIABLE_NAME expr, so we cant fold to them directly
 HIR::Throw*,					// Throw*
 HIR::Try*,						// Try*
 HIR::Type*,					// Type*
 HIR::Unary_op*,				// Unary_op*
 HIR::VARIABLE_NAME*,		// VARIABLE_NAME*
 HIR::Expr*,					// Variable* - HIR::Variable is split into multiple type
 HIR::Variable_name*,		// Variable_name*
 HIR::Loop*						// While*
>
{
	HIR::Statement* eval_expr_assignment;
	AST::Reflection* reflection;

public:
	AST_to_HIR ()
	{
		eval_expr_assignment = NULL;
		reflection = NULL;
	}

private:
	/* HIR::Targets can be a VARIABLE_NAME, which means we need to fold them to
	 * a HIR::Node. This node can have either a CLASS_NAME, or an Expr. If it is
	 * an Expr, it must be a wrapped VARIABLE_NAME. */
	HIR::Target* unwrap_target (HIR::Node* target)
	{
		if (isa<HIR::CLASS_NAME> (target))
			return dyc<HIR::CLASS_NAME> (target);
		else
			return dyc<HIR::VARIABLE_NAME> (target);
	}

	void copy_attrs (HIR::Node* target, AST::Node* source)
	{
		target->attrs->clone_all_from (source->attrs);
		target->attrs->erase ("phc.comments");
		target->attrs->erase_with_prefix ("phc.ast");
	}

public:

	HIR::PHP_script* fold_impl_php_script(AST::PHP_script* orig, HIR::Statement_list* statements) 
	{
		HIR::PHP_script* result;
		result = new HIR::PHP_script(statements);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Class_def* fold_impl_class_def(AST::Class_def* orig, HIR::Class_mod* class_mod, HIR::CLASS_NAME* class_name, HIR::CLASS_NAME* extends, HIR::INTERFACE_NAME_list* implements, HIR::Member_list* members) 
	{
		HIR::Class_def* result;
		result = new HIR::Class_def(class_mod, class_name, extends, implements, members);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Class_mod* fold_impl_class_mod(AST::Class_mod* orig, bool is_abstract, bool is_final) 
	{
		HIR::Class_mod* result;
		result = new HIR::Class_mod(is_abstract, is_final);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Interface_def* fold_impl_interface_def(AST::Interface_def* orig, HIR::INTERFACE_NAME* interface_name, HIR::INTERFACE_NAME_list* extends, HIR::Member_list* members) 
	{
		HIR::Interface_def* result;
		result = new HIR::Interface_def(interface_name, extends, members);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Method* fold_impl_method(AST::Method* orig, HIR::Signature* signature, HIR::Statement_list* statements) 
	{
		HIR::Method* result;
		result = new HIR::Method(signature, statements);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Signature* fold_impl_signature(AST::Signature* orig, HIR::Method_mod* method_mod, bool is_ref, HIR::METHOD_NAME* method_name, HIR::Formal_parameter_list* formal_parameters) 
	{
		HIR::Signature* result;
		result = new HIR::Signature(method_mod, is_ref, method_name, formal_parameters);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Method_mod* fold_impl_method_mod(AST::Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		HIR::Method_mod* result;
		result = new HIR::Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Formal_parameter* fold_impl_formal_parameter(AST::Formal_parameter* orig, HIR::Type* type, bool is_ref, HIR::Name_with_default* var) 
	{
		HIR::Formal_parameter* result;
		result = new HIR::Formal_parameter(type, is_ref, var);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Type* fold_impl_type(AST::Type* orig, HIR::CLASS_NAME* class_name) 
	{
		HIR::Type* result;
		result = new HIR::Type(class_name);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Attribute* fold_impl_attribute(AST::Attribute* orig, HIR::Attr_mod* attr_mod, HIR::Name_with_default_list* vars) 
	{
		assert(vars->size() == 1);

		HIR::Attribute* result;
		result = new HIR::Attribute(attr_mod, vars->front ());
		copy_attrs (result, orig);
		return result;
	}

	HIR::Attr_mod* fold_impl_attr_mod(AST::Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		HIR::Attr_mod* result;
		result = new HIR::Attr_mod(is_public, is_protected, is_private, is_static, is_const);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Name_with_default* fold_impl_name_with_default(AST::Name_with_default* orig, HIR::VARIABLE_NAME* variable_name, HIR::Expr* expr) 
	{
		if (expr != NULL)
			assert (isa<HIR::Static_value> (expr));

		HIR::Name_with_default* result;
		result = new HIR::Name_with_default(
			variable_name, 
			dyc<HIR::Static_value> (expr));
		copy_attrs (result, orig);
		return result;
	}

	HIR::Return* fold_impl_return(AST::Return* orig, HIR::Expr* expr) 
	{
		HIR::Return* result;
		result = new HIR::Return(dyc<HIR::Rvalue> (expr));
		copy_attrs (result, orig);
		return result;
	}

	HIR::Static_declaration* fold_impl_static_declaration(AST::Static_declaration* orig, HIR::Name_with_default_list* vars) 
	{
		assert(vars->size() == 1);

		HIR::Static_declaration* result;
		result = new HIR::Static_declaration(vars->front ());
		copy_attrs (result, orig);
		return result;
	}

	HIR::Global* fold_impl_global(AST::Global* orig, HIR::Variable_name_list* variable_names) 
	{
		assert(variable_names->size() == 1);
		assert (variable_names->front() != NULL);
		
		HIR::Global* result;
		result = new HIR::Global(variable_names->front ());
		copy_attrs (result, orig);
		return result;
	}

	HIR::Try* fold_impl_try(AST::Try* orig, HIR::Statement_list* statements, HIR::Catch_list* catches) 
	{
		HIR::Try* result;
		result = new HIR::Try(statements, catches);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Catch* fold_impl_catch(AST::Catch* orig, HIR::CLASS_NAME* class_name, HIR::VARIABLE_NAME* variable_name, HIR::Statement_list* statements) 
	{
		HIR::Catch* result;
		result = new HIR::Catch(class_name, variable_name, statements);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Throw* fold_impl_throw(AST::Throw* orig, HIR::Expr* expr) 
	{
		HIR::Throw* result;
		result = new HIR::Throw(dyc<HIR::VARIABLE_NAME> (expr));
		copy_attrs (result, orig);
		return result;
	}

	/* fold_impl_assignment sets eval_expr_assignment, which is returned if EXPR is NULL */
	HIR::Statement* fold_impl_eval_expr(AST::Eval_expr* orig, HIR::Expr* expr) 
	{
		HIR::Statement* result;
		if (expr
			&& (expr->classid () == HIR::Method_invocation::ID
				|| expr->classid () == HIR::New::ID))
		{
			// Carry on as normal
			result = new HIR::Eval_expr (expr);
			copy_attrs (result, orig);
		}
		else
		{
			// We have an Assignment to return instead, stored in eval_expr_assignment
			assert (eval_expr_assignment);
			result = eval_expr_assignment;
			eval_expr_assignment = NULL;
		}

		return result;
	}

	HIR::Break* fold_impl_break (AST::Break* orig, HIR::Expr* expr)
	{
		HIR::Break* result;
		result = new HIR::Break (expr);
		copy_attrs (result, orig);
		return result;
	}

	HIR::If* fold_impl_if(AST::If* orig, HIR::Expr* expr, HIR::Statement_list* iftrue, HIR::Statement_list* iffalse)
	{
		HIR::If* result;
		result = new HIR::If (dyc<HIR::VARIABLE_NAME> (expr), iftrue, iffalse);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Loop* fold_impl_while (AST::While* orig, HIR::Expr* expr, HIR::Statement_list* statements)
	{
		// All while's must be true
		HIR::BOOL* b = dynamic_cast<HIR::BOOL*> (expr);
		assert (b && b->value);

		HIR::Loop* result;
		result = new HIR::Loop(statements);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Foreach* fold_impl_foreach (AST::Foreach* orig, HIR::Expr* arr, HIR::Expr* key, bool is_ref, HIR::Expr* val, HIR::Statement_list* statements)
	{
		HIR::Foreach* result;
		result = new HIR::Foreach(
			dyc<HIR::VARIABLE_NAME> (arr),
			dyc<HIR::VARIABLE_NAME> (key),
			is_ref,
			dyc<HIR::VARIABLE_NAME> (val),
			statements);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Continue* fold_impl_continue(AST::Continue* orig, HIR::Expr* expr)
	{
		HIR::Continue* result;
		result = new HIR::Continue(expr);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Expr* fold_impl_assignment(AST::Assignment* orig, HIR::Expr* lhs, bool is_ref, HIR::Expr* expr) 
	{
		assert (eval_expr_assignment == NULL);

		HIR::Field_access* field_access = dynamic_cast<HIR::Field_access*> (lhs);
		HIR::VARIABLE_NAME* var_name = dynamic_cast<HIR::VARIABLE_NAME*> (lhs);
		HIR::Variable_variable* var_var = dynamic_cast<HIR::Variable_variable*> (lhs);
		HIR::Array_access* ia = dynamic_cast<HIR::Array_access*> (lhs);
		HIR::Array_next * an = dynamic_cast<HIR::Array_next*> (lhs);

		// Var doesnt have enough information to tell us if a NULL
		// var->array_index indicates a push or a copy. So we have to look in
		// ORIG.
		
		// assign_next - $x[] = $y;
		if (an
			&& isa<HIR::Rvalue> (expr))
		{
			HIR::Assign_next* result;
			result = new HIR::Assign_next (
				an->variable_name, 
				is_ref, 
				dyc<HIR::Rvalue> (expr));
			copy_attrs (result, orig);
			eval_expr_assignment = result;
			return NULL;
		}


		// assign_array - $x[$i] = $y;
		if (ia
			&& ia->index
			&& isa<HIR::Rvalue> (expr))
		{
			HIR::Assign_array* result;
			result = new HIR::Assign_array (
				dynamic_cast<HIR::VARIABLE_NAME*> (ia->variable_name), 
				ia->index,
				is_ref,
				dyc<HIR::Rvalue> (expr));
			copy_attrs (result, orig);
			eval_expr_assignment = result;
			return NULL;
		}

		// assign_var - $x = y();
		if (var_name
			&& not var_name->attrs->is_true ("phc.codegen.unused")
			&& orig->variable->array_indices->size() == 0)
		{
			HIR::Assign_var* result;
			result = new HIR::Assign_var (var_name, is_ref, expr);
			copy_attrs (result, orig);
			eval_expr_assignment = result;
			return NULL;
		}

		// eval_expr - y();
		if (var_name
			&& var_name->attrs->is_true ("phc.codegen.unused")
			&& is_ref == false)
		{
			HIR::Eval_expr* result;
			result = new HIR::Eval_expr (expr); 
			copy_attrs (result, orig);
			eval_expr_assignment = result;
			return NULL;
		}
		
		// assign_var_var - $$x = $y;
		if (var_var
			&& not var_var->variable_name->attrs->is_true ("phc.codegen.unused")
			&& isa<HIR::Rvalue> (expr))
		{
			HIR::Assign_var_var* result;
			result = new HIR::Assign_var_var (
				var_var->variable_name, 
				is_ref, 
				dyc<HIR::Rvalue> (expr));

			copy_attrs (result, orig);
			eval_expr_assignment = result;
			return NULL;
		}

		// field_access - $x->$y = $z;
		if (field_access)
		{
			HIR::Assign_field* result;
			result = new HIR::Assign_field (
				field_access->target,
				field_access->field_name, 
				is_ref,
				dyc<HIR::Rvalue> (expr));

			copy_attrs (result, orig);
			eval_expr_assignment = result;
			return NULL;
		}

		// all cases should be handled
		assert (0);
	}

	HIR::Cast* fold_impl_cast(AST::Cast* orig, HIR::CAST* cast, HIR::Expr* expr) 
	{
		HIR::Cast* result;
		result = new HIR::Cast(cast, dyc<HIR::VARIABLE_NAME> (expr));
		copy_attrs (result, orig);
		return result;
	}

	HIR::Unary_op* fold_impl_unary_op(AST::Unary_op* orig, HIR::OP* op, HIR::Expr* expr) 
	{
		HIR::Unary_op* result;
		result = new HIR::Unary_op(op, dyc<HIR::VARIABLE_NAME> (expr));
		copy_attrs (result, orig);
		return result;
	}

	HIR::Bin_op* fold_impl_bin_op(AST::Bin_op* orig, HIR::Expr* left, HIR::OP* op, HIR::Expr* right) 
	{
		HIR::Bin_op* result;
		result = new HIR::Bin_op(dyc<HIR::Rvalue> (left), op, dyc<HIR::Rvalue> (right));
		copy_attrs (result, orig);
		return result;
	}

	HIR::Constant* fold_impl_constant(AST::Constant* orig, HIR::CLASS_NAME* class_name, HIR::CONSTANT_NAME* constant_name) 
	{
		HIR::Constant* result;
		result = new HIR::Constant(class_name, constant_name);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Instanceof* fold_impl_instanceof(AST::Instanceof* orig, HIR::Expr* expr, HIR::Class_name* class_name) 
	{
		HIR::Instanceof* result;
		result = new HIR::Instanceof(dyc<HIR::VARIABLE_NAME> (expr), class_name);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Expr* fold_impl_variable(AST::Variable* orig, HIR::Node* target, HIR::Variable_name* variable_name, HIR::Expr_list* array_indices) 
	{
		// HIR::Variables can only have 1 array_index. However,
		// HIR::Actual_parameters can have multiple array_indices. We don't have
		// the context here to tell which is which. The common case is only one
		// array_index, so we assume thats what we have here. We let
		// fold_impl_actual_parameter handle its arguments. Obviously, we
		// shouldn't fail on more than one array_index.


		// $x
		if (array_indices->size () == 0
			&& target == NULL
			&& isa<HIR::VARIABLE_NAME> (variable_name))
		{
			HIR::VARIABLE_NAME* result = dyc<HIR::VARIABLE_NAME> (variable_name);
			copy_attrs (result, orig);
			return result;
		}
		// $x[$y]
		else if (array_indices->size () == 1
				&& array_indices->front () != NULL
				&& target == NULL
				&& isa<HIR::VARIABLE_NAME> (variable_name))
		{
			HIR::Rvalue* array_index = dyc<HIR::Rvalue> (array_indices->front ());
			HIR::Array_access* result;
			result = new HIR::Array_access (
					dyc<HIR::VARIABLE_NAME> (variable_name),
					array_index);
			copy_attrs (result, orig);
			return result;
		}
		// $x[]
		else if (array_indices->size () == 1
				&& array_indices->front () == NULL
				&& target == NULL
				&& isa<HIR::VARIABLE_NAME> (variable_name))
		{
			HIR::Array_next* result;
			result = new HIR::Array_next (
					dyc<HIR::VARIABLE_NAME> (variable_name));
			copy_attrs (result, orig);
			return result;
		}
		// $$x
		else if (array_indices->size () == 0
				&& target == NULL
				&& isa<HIR::Variable_variable> (variable_name))
		{
			HIR::Variable_variable* result = dyc<HIR::Variable_variable> (variable_name);
			copy_attrs (result, orig);
			return result;
		}
		// $x->f
		else if (target)
		{
			HIR::Field_name* field_name;
			if (isa<HIR::VARIABLE_NAME> (variable_name))
				field_name = new HIR::FIELD_NAME (dyc<HIR::VARIABLE_NAME> (variable_name)->value);
			else
				field_name = new HIR::Variable_field (dyc<HIR::Variable_variable> (variable_name)->variable_name->clone ());

			field_name->attrs = variable_name->attrs->clone ();

			HIR::Field_access* result;
			result = new HIR::Field_access (
					unwrap_target (target),
					field_name);
			copy_attrs (result, orig);
			return result;
		}
		else
		{
			// Let actual_parameters handle it
			return NULL;
		}
	}


	HIR::Expr* fold_impl_pre_op(AST::Pre_op* orig, HIR::OP* op, HIR::Expr* expr) 
	{
		HIR::Pre_op* result;
		result = new HIR::Pre_op(op, dyc<HIR::VARIABLE_NAME> (expr));
		copy_attrs (result, orig);
		eval_expr_assignment = result;

		// NULL signal Eval_expr to use eval_expr_assignment
		return NULL;
	}

	HIR::Expr* fold_impl_array(AST::Array* orig, HIR::Static_array_elem_list* static_array_elems) 
	{
		HIR::Static_array* result;
		result = new HIR::Static_array(static_array_elems);
		copy_attrs (result, orig);
		return reinterpret_cast<HIR::Expr*> (result);
	}

	HIR::Static_array_elem* fold_impl_array_elem(AST::Array_elem* orig, HIR::Expr* key, bool is_ref, HIR::Expr* val) 
	{
		HIR::Static_array_elem* result;
		result = new HIR::Static_array_elem(
			dyc<HIR::Static_array_key> (key),
			is_ref,
			dyc<HIR::Static_value> (val));
		copy_attrs (result, orig);
		return result;
	}

	HIR::Expr* fold_impl_method_invocation(AST::Method_invocation* orig, HIR::Node* target, HIR::Method_name* method_name, HIR::Actual_parameter_list* actual_parameters) 
	{
		HIR::Method_invocation* result;
		result = new HIR::Method_invocation(
			unwrap_target (target),
			method_name, 
			actual_parameters);
		copy_attrs (result, orig);
		return result;
	}

	/* The HIR has no Reflection. Instead, we save the AST::Reflection, and
	 * extract a VARIABLE_NAME here. */
	HIR::VARIABLE_NAME* refl_to_var_name (AST::Node* in)
	{
		AST::Reflection* refl = dyc<AST::Reflection> (in);
		return dyc<HIR::VARIABLE_NAME> (fold_expr (refl->expr));
	}

	// Reflection is converted to Variable_name in this context.
	HIR::Variable_name* fold_variable_name(AST::Variable_name* in)
	{
		if (isa<AST::Reflection> (in))
		{
			HIR::Variable_variable* result;
			result = new HIR::Variable_variable (refl_to_var_name (in));
			copy_attrs (result, in);
			return result;
		}
		else
			return parent::fold_variable_name (in);
	}

	HIR::Method_name* fold_method_name(AST::Method_name* in)
	{
		if (isa<AST::Reflection> (in))
		{
			HIR::Variable_method* result;
			result = new HIR::Variable_method (refl_to_var_name (in));
			copy_attrs (result, in);
			return result;
		}
		else
			return parent::fold_method_name (in);
	}

	HIR::Class_name* fold_class_name(AST::Class_name* in)
	{
		if (isa<AST::Reflection> (in))
		{
			HIR::Variable_class* result;
			result = new HIR::Variable_class (refl_to_var_name (in));
			copy_attrs (result, in);
			return result;
		}
		else
			return parent::fold_class_name (in);
	}

	HIR::Actual_parameter* fold_impl_actual_parameter(AST::Actual_parameter* orig, bool is_ref, HIR::Expr* expr) 
	{
		if (isa<HIR::Literal> (expr))
			return dyc<HIR::Literal> (expr);

		// See comment in fold_impl_variable. We need to extract and fold our array_indices ourselves.
		HIR::Rvalue_list* array_indices = new HIR::Rvalue_list;
		foreach (AST::Expr* expr, *dyc<AST::Variable> (orig->expr)->array_indices)
			array_indices->push_back (dyc<HIR::Rvalue> (fold_expr (expr)));

		// fold_impl_variable rejects a number of constructs allowed here. We must fold ourselves.
		AST::Variable* param = dyc<AST::Variable> (orig->expr);
		assert (param);
		HIR::Target* target = NULL;
		if (param->target)
		{
			target = unwrap_target (fold_target (param->target));
			assert (target);
		}

		HIR::Variable_name* var_name = fold_variable_name (param->variable_name);

		HIR::Variable_actual_parameter* result;
		result = new HIR::Variable_actual_parameter (is_ref, target, var_name, array_indices);
		copy_attrs (result, orig);
		return result;
	}

	HIR::Expr* fold_impl_new(AST::New* orig, HIR::Class_name* class_name, HIR::Actual_parameter_list* actual_parameters) 
	{
		HIR::New* result;
		result = new HIR::New(class_name, actual_parameters);
		copy_attrs (result, orig);
		return result;
	}

	HIR::CLASS_NAME* fold_class_name(AST::CLASS_NAME* orig) 
	{
		HIR::CLASS_NAME* result;
		result = new HIR::CLASS_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::INTERFACE_NAME* fold_interface_name(AST::INTERFACE_NAME* orig) 
	{
		HIR::INTERFACE_NAME* result;
		result = new HIR::INTERFACE_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::METHOD_NAME* fold_method_name(AST::METHOD_NAME* orig) 
	{
		HIR::METHOD_NAME* result;
		result = new HIR::METHOD_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::VARIABLE_NAME* fold_variable_name(AST::VARIABLE_NAME* orig) 
	{
		HIR::VARIABLE_NAME* result;
		result = new HIR::VARIABLE_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::INT* fold_int(AST::INT* orig) 
	{
		HIR::INT* result;
		result = new HIR::INT(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::REAL* fold_real(AST::REAL* orig) 
	{
		HIR::REAL* result;
		result = new HIR::REAL(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::STRING* fold_string(AST::STRING* orig) 
	{
		HIR::STRING* result;
		result = new HIR::STRING(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::BOOL* fold_bool(AST::BOOL* orig) 
	{
		HIR::BOOL* result;
		result = new HIR::BOOL(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::NIL* fold_nil(AST::NIL* orig) 
	{
		HIR::NIL* result;
		result = new HIR::NIL();
		copy_attrs (result, orig);
		return result;
	}

	HIR::OP* fold_op(AST::OP* orig) 
	{
		HIR::OP* result;
		result = new HIR::OP(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::CAST* fold_cast(AST::CAST* orig) 
	{
		HIR::CAST* result;
		result = new HIR::CAST(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	HIR::CONSTANT_NAME* fold_constant_name(AST::CONSTANT_NAME* orig) 
	{
		HIR::CONSTANT_NAME* result;
		result = new HIR::CONSTANT_NAME(orig->value);
		copy_attrs (result, orig);
		return result;
	}

	~AST_to_HIR () {}
};

#endif // PHC_AST_TO_HIR_H 
