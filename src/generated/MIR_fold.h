#include <iostream>
#include <sstream>
#include <iomanip>
#include "lib/error.h"
#include "lib/Object.h"
#include "lib/List.h"
#include "lib/String.h"
#include "lib/Boolean.h"
#include "lib/Integer.h"
#include "lib/AttrMap.h"
#include "process_ir/IR.h"
#include "process_ir/Foreach.h"
#include <list>
#include <string>
#include <cstring>
#include <cassert>


#include "MIR.h"
namespace MIR{
template
<class _Actual_parameter,
 class _Array_access,
 class _Array_next,
 class _Assign_array,
 class _Assign_field,
 class _Assign_next,
 class _Assign_var,
 class _Assign_var_var,
 class _Attr_mod,
 class _Attribute,
 class _BOOL,
 class _Bin_op,
 class _Branch,
 class _CAST,
 class _CLASS_NAME,
 class _CONSTANT_NAME,
 class _Cast,
 class _Catch,
 class _Class_alias,
 class _Class_def,
 class _Class_mod,
 class _Class_name,
 class _Constant,
 class _Eval_expr,
 class _Expr,
 class _FIELD_NAME,
 class _FOREIGN,
 class _Field_access,
 class _Field_name,
 class _Foreach_end,
 class _Foreach_get_key,
 class _Foreach_get_val,
 class _Foreach_has_key,
 class _Foreach_next,
 class _Foreach_reset,
 class _Formal_parameter,
 class _Global,
 class _Goto,
 class _HT_ITERATOR,
 class _INT,
 class _INTERFACE_NAME,
 class _Identifier,
 class _Instanceof,
 class _Interface_alias,
 class _Interface_def,
 class _Isset,
 class _LABEL_NAME,
 class _Label,
 class _Literal,
 class _METHOD_NAME,
 class _Member,
 class _Method,
 class _Method_alias,
 class _Method_invocation,
 class _Method_mod,
 class _Method_name,
 class _NIL,
 class _Name_with_default,
 class _New,
 class _Node,
 class _OP,
 class _PARAM_INDEX,
 class _PHP_script,
 class _Param_is_ref,
 class _Pre_op,
 class _REAL,
 class _Return,
 class _Rvalue,
 class _STRING,
 class _Signature,
 class _Statement,
 class _Static_array,
 class _Static_array_elem,
 class _Static_array_key,
 class _Static_declaration,
 class _Static_value,
 class _Target,
 class _Throw,
 class _Try,
 class _Type,
 class _Unary_op,
 class _Unset,
 class _VARIABLE_NAME,
 class _Variable_class,
 class _Variable_field,
 class _Variable_method,
 class _Variable_name,
 class _Variable_variable,
 template <typename _Tp, typename _Alloc = typename List<_Tp>::allocator_type> class _List = List
>
class Fold
{
// Access this class from subclasses without copying out the template instantiation
public:
   typedef Fold<_Actual_parameter, _Array_access, _Array_next, _Assign_array, _Assign_field, _Assign_next, _Assign_var, _Assign_var_var, _Attr_mod, _Attribute, _BOOL, _Bin_op, _Branch, _CAST, _CLASS_NAME, _CONSTANT_NAME, _Cast, _Catch, _Class_alias, _Class_def, _Class_mod, _Class_name, _Constant, _Eval_expr, _Expr, _FIELD_NAME, _FOREIGN, _Field_access, _Field_name, _Foreach_end, _Foreach_get_key, _Foreach_get_val, _Foreach_has_key, _Foreach_next, _Foreach_reset, _Formal_parameter, _Global, _Goto, _HT_ITERATOR, _INT, _INTERFACE_NAME, _Identifier, _Instanceof, _Interface_alias, _Interface_def, _Isset, _LABEL_NAME, _Label, _Literal, _METHOD_NAME, _Member, _Method, _Method_alias, _Method_invocation, _Method_mod, _Method_name, _NIL, _Name_with_default, _New, _Node, _OP, _PARAM_INDEX, _PHP_script, _Param_is_ref, _Pre_op, _REAL, _Return, _Rvalue, _STRING, _Signature, _Statement, _Static_array, _Static_array_elem, _Static_array_key, _Static_declaration, _Static_value, _Target, _Throw, _Try, _Type, _Unary_op, _Unset, _VARIABLE_NAME, _Variable_class, _Variable_field, _Variable_method, _Variable_name, _Variable_variable, _List> parent;
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _PHP_script fold_php_script(PHP_script* in)
	{
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_php_script(in, statements);
	}

	virtual _Class_def fold_class_def(Class_def* in)
	{
		_Class_mod class_mod = 0;
		if(in->class_mod != NULL) class_mod = fold_class_mod(in->class_mod);
		_CLASS_NAME class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_CLASS_NAME extends = 0;
		if(in->extends != NULL) extends = fold_class_name(in->extends);
		_List<_INTERFACE_NAME>* implements = 0;
	
		{
			implements = new _List<_INTERFACE_NAME>;
			typename _List<INTERFACE_NAME*>::const_iterator i;
			for(i = in->implements->begin(); i != in->implements->end(); i++)
				if(*i != NULL) implements->push_back(fold_interface_name(*i));
				else implements->push_back(0);
		}
		_List<_Member>* members = 0;
	
		{
			members = new _List<_Member>;
			typename _List<Member*>::const_iterator i;
			for(i = in->members->begin(); i != in->members->end(); i++)
				if(*i != NULL) members->push_back(fold_member(*i));
				else members->push_back(0);
		}
		return fold_impl_class_def(in, class_mod, class_name, extends, implements, members);
	}

	virtual _Class_mod fold_class_mod(Class_mod* in)
	{
		bool is_abstract = in->is_abstract;
		bool is_final = in->is_final;
		return fold_impl_class_mod(in, is_abstract, is_final);
	}

	virtual _Interface_def fold_interface_def(Interface_def* in)
	{
		_INTERFACE_NAME interface_name = 0;
		if(in->interface_name != NULL) interface_name = fold_interface_name(in->interface_name);
		_List<_INTERFACE_NAME>* extends = 0;
	
		{
			extends = new _List<_INTERFACE_NAME>;
			typename _List<INTERFACE_NAME*>::const_iterator i;
			for(i = in->extends->begin(); i != in->extends->end(); i++)
				if(*i != NULL) extends->push_back(fold_interface_name(*i));
				else extends->push_back(0);
		}
		_List<_Member>* members = 0;
	
		{
			members = new _List<_Member>;
			typename _List<Member*>::const_iterator i;
			for(i = in->members->begin(); i != in->members->end(); i++)
				if(*i != NULL) members->push_back(fold_member(*i));
				else members->push_back(0);
		}
		return fold_impl_interface_def(in, interface_name, extends, members);
	}

	virtual _Method fold_method(Method* in)
	{
		_Signature signature = 0;
		if(in->signature != NULL) signature = fold_signature(in->signature);
		_List<_Statement>* statements = 0;
	if (in->statements)
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_method(in, signature, statements);
	}

	virtual _Signature fold_signature(Signature* in)
	{
		_Method_mod method_mod = 0;
		if(in->method_mod != NULL) method_mod = fold_method_mod(in->method_mod);
		bool pass_rest_by_ref = in->pass_rest_by_ref;
		bool return_by_ref = in->return_by_ref;
		_METHOD_NAME method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		_List<_Formal_parameter>* formal_parameters = 0;
	
		{
			formal_parameters = new _List<_Formal_parameter>;
			typename _List<Formal_parameter*>::const_iterator i;
			for(i = in->formal_parameters->begin(); i != in->formal_parameters->end(); i++)
				if(*i != NULL) formal_parameters->push_back(fold_formal_parameter(*i));
				else formal_parameters->push_back(0);
		}
		return fold_impl_signature(in, method_mod, pass_rest_by_ref, return_by_ref, method_name, formal_parameters);
	}

	virtual _Method_mod fold_method_mod(Method_mod* in)
	{
		bool is_public = in->is_public;
		bool is_protected = in->is_protected;
		bool is_private = in->is_private;
		bool is_static = in->is_static;
		bool is_abstract = in->is_abstract;
		bool is_final = in->is_final;
		return fold_impl_method_mod(in, is_public, is_protected, is_private, is_static, is_abstract, is_final);
	}

	virtual _Formal_parameter fold_formal_parameter(Formal_parameter* in)
	{
		_Type type = 0;
		if(in->type != NULL) type = fold_type(in->type);
		bool is_ref = in->is_ref;
		_Name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_formal_parameter(in, type, is_ref, var);
	}

	virtual _Type fold_type(Type* in)
	{
		_CLASS_NAME class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_type(in, class_name);
	}

	virtual _Attribute fold_attribute(Attribute* in)
	{
		_Attr_mod attr_mod = 0;
		if(in->attr_mod != NULL) attr_mod = fold_attr_mod(in->attr_mod);
		_Name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_attribute(in, attr_mod, var);
	}

	virtual _Attr_mod fold_attr_mod(Attr_mod* in)
	{
		bool is_public = in->is_public;
		bool is_protected = in->is_protected;
		bool is_private = in->is_private;
		bool is_static = in->is_static;
		bool is_const = in->is_const;
		return fold_impl_attr_mod(in, is_public, is_protected, is_private, is_static, is_const);
	}

	virtual _Name_with_default fold_name_with_default(Name_with_default* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Static_value default_value = 0;
		if(in->default_value != NULL) default_value = fold_static_value(in->default_value);
		return fold_impl_name_with_default(in, variable_name, default_value);
	}

	virtual _Class_alias fold_class_alias(Class_alias* in)
	{
		_CLASS_NAME alias = 0;
		if(in->alias != NULL) alias = fold_class_name(in->alias);
		_CLASS_NAME class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_class_alias(in, alias, class_name);
	}

	virtual _Interface_alias fold_interface_alias(Interface_alias* in)
	{
		_INTERFACE_NAME alias = 0;
		if(in->alias != NULL) alias = fold_interface_name(in->alias);
		_INTERFACE_NAME interface_name = 0;
		if(in->interface_name != NULL) interface_name = fold_interface_name(in->interface_name);
		return fold_impl_interface_alias(in, alias, interface_name);
	}

	virtual _Method_alias fold_method_alias(Method_alias* in)
	{
		_METHOD_NAME alias = 0;
		if(in->alias != NULL) alias = fold_method_name(in->alias);
		_METHOD_NAME method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		return fold_impl_method_alias(in, alias, method_name);
	}

	virtual _Return fold_return(Return* in)
	{
		_Rvalue rvalue = 0;
		if(in->rvalue != NULL) rvalue = fold_rvalue(in->rvalue);
		return fold_impl_return(in, rvalue);
	}

	virtual _Static_declaration fold_static_declaration(Static_declaration* in)
	{
		_Name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_static_declaration(in, var);
	}

	virtual _Global fold_global(Global* in)
	{
		_Variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_global(in, variable_name);
	}

	virtual _Try fold_try(Try* in)
	{
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		_List<_Catch>* catches = 0;
	
		{
			catches = new _List<_Catch>;
			typename _List<Catch*>::const_iterator i;
			for(i = in->catches->begin(); i != in->catches->end(); i++)
				if(*i != NULL) catches->push_back(fold_catch(*i));
				else catches->push_back(0);
		}
		return fold_impl_try(in, statements, catches);
	}

	virtual _Catch fold_catch(Catch* in)
	{
		_CLASS_NAME class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_catch(in, class_name, variable_name, statements);
	}

	virtual _Throw fold_throw(Throw* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_throw(in, variable_name);
	}

	virtual _Assign_var fold_assign_var(Assign_var* in)
	{
		_VARIABLE_NAME lhs = 0;
		if(in->lhs != NULL) lhs = fold_variable_name(in->lhs);
		bool is_ref = in->is_ref;
		_Expr rhs = 0;
		if(in->rhs != NULL) rhs = fold_expr(in->rhs);
		return fold_impl_assign_var(in, lhs, is_ref, rhs);
	}

	virtual _Assign_field fold_assign_field(Assign_field* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Field_name field_name = 0;
		if(in->field_name != NULL) field_name = fold_field_name(in->field_name);
		bool is_ref = in->is_ref;
		_Rvalue rhs = 0;
		if(in->rhs != NULL) rhs = fold_rvalue(in->rhs);
		return fold_impl_assign_field(in, target, field_name, is_ref, rhs);
	}

	virtual _Assign_array fold_assign_array(Assign_array* in)
	{
		_VARIABLE_NAME lhs = 0;
		if(in->lhs != NULL) lhs = fold_variable_name(in->lhs);
		_Rvalue index = 0;
		if(in->index != NULL) index = fold_rvalue(in->index);
		bool is_ref = in->is_ref;
		_Rvalue rhs = 0;
		if(in->rhs != NULL) rhs = fold_rvalue(in->rhs);
		return fold_impl_assign_array(in, lhs, index, is_ref, rhs);
	}

	virtual _Assign_var_var fold_assign_var_var(Assign_var_var* in)
	{
		_VARIABLE_NAME lhs = 0;
		if(in->lhs != NULL) lhs = fold_variable_name(in->lhs);
		bool is_ref = in->is_ref;
		_Rvalue rhs = 0;
		if(in->rhs != NULL) rhs = fold_rvalue(in->rhs);
		return fold_impl_assign_var_var(in, lhs, is_ref, rhs);
	}

	virtual _Assign_next fold_assign_next(Assign_next* in)
	{
		_VARIABLE_NAME lhs = 0;
		if(in->lhs != NULL) lhs = fold_variable_name(in->lhs);
		bool is_ref = in->is_ref;
		_Rvalue rhs = 0;
		if(in->rhs != NULL) rhs = fold_rvalue(in->rhs);
		return fold_impl_assign_next(in, lhs, is_ref, rhs);
	}

	virtual _Pre_op fold_pre_op(Pre_op* in)
	{
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_pre_op(in, op, variable_name);
	}

	virtual _Eval_expr fold_eval_expr(Eval_expr* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_eval_expr(in, expr);
	}

	virtual _Unset fold_unset(Unset* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_List<_Rvalue>* array_indices = 0;
	
		{
			array_indices = new _List<_Rvalue>;
			typename _List<Rvalue*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_rvalue(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_unset(in, target, variable_name, array_indices);
	}

	virtual _Isset fold_isset(Isset* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_List<_Rvalue>* array_indices = 0;
	
		{
			array_indices = new _List<_Rvalue>;
			typename _List<Rvalue*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_rvalue(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_isset(in, target, variable_name, array_indices);
	}

	virtual _Field_access fold_field_access(Field_access* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Field_name field_name = 0;
		if(in->field_name != NULL) field_name = fold_field_name(in->field_name);
		return fold_impl_field_access(in, target, field_name);
	}

	virtual _Array_access fold_array_access(Array_access* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Rvalue index = 0;
		if(in->index != NULL) index = fold_rvalue(in->index);
		return fold_impl_array_access(in, variable_name, index);
	}

	virtual _Array_next fold_array_next(Array_next* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_array_next(in, variable_name);
	}

	virtual _Cast fold_cast(Cast* in)
	{
		_CAST cast = 0;
		if(in->cast != NULL) cast = fold_cast(in->cast);
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_cast(in, cast, variable_name);
	}

	virtual _Unary_op fold_unary_op(Unary_op* in)
	{
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_unary_op(in, op, variable_name);
	}

	virtual _Bin_op fold_bin_op(Bin_op* in)
	{
		_Rvalue left = 0;
		if(in->left != NULL) left = fold_rvalue(in->left);
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Rvalue right = 0;
		if(in->right != NULL) right = fold_rvalue(in->right);
		return fold_impl_bin_op(in, left, op, right);
	}

	virtual _Constant fold_constant(Constant* in)
	{
		_CLASS_NAME class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_CONSTANT_NAME constant_name = 0;
		if(in->constant_name != NULL) constant_name = fold_constant_name(in->constant_name);
		return fold_impl_constant(in, class_name, constant_name);
	}

	virtual _Instanceof fold_instanceof(Instanceof* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_instanceof(in, variable_name, class_name);
	}

	virtual _Method_invocation fold_method_invocation(Method_invocation* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		_List<_Actual_parameter>* actual_parameters = 0;
	
		{
			actual_parameters = new _List<_Actual_parameter>;
			typename _List<Actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_method_invocation(in, target, method_name, actual_parameters);
	}

	virtual _New fold_new(New* in)
	{
		_Class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_List<_Actual_parameter>* actual_parameters = 0;
	
		{
			actual_parameters = new _List<_Actual_parameter>;
			typename _List<Actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_new(in, class_name, actual_parameters);
	}

	virtual _Actual_parameter fold_actual_parameter(Actual_parameter* in)
	{
		bool is_ref = in->is_ref;
		_Rvalue rvalue = 0;
		if(in->rvalue != NULL) rvalue = fold_rvalue(in->rvalue);
		return fold_impl_actual_parameter(in, is_ref, rvalue);
	}

	virtual _Variable_method fold_variable_method(Variable_method* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_variable_method(in, variable_name);
	}

	virtual _Variable_variable fold_variable_variable(Variable_variable* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_variable_variable(in, variable_name);
	}

	virtual _Variable_class fold_variable_class(Variable_class* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_variable_class(in, variable_name);
	}

	virtual _Variable_field fold_variable_field(Variable_field* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_variable_field(in, variable_name);
	}

	virtual _Static_array fold_static_array(Static_array* in)
	{
		_List<_Static_array_elem>* static_array_elems = 0;
	
		{
			static_array_elems = new _List<_Static_array_elem>;
			typename _List<Static_array_elem*>::const_iterator i;
			for(i = in->static_array_elems->begin(); i != in->static_array_elems->end(); i++)
				if(*i != NULL) static_array_elems->push_back(fold_static_array_elem(*i));
				else static_array_elems->push_back(0);
		}
		return fold_impl_static_array(in, static_array_elems);
	}

	virtual _Static_array_elem fold_static_array_elem(Static_array_elem* in)
	{
		_Static_array_key key = 0;
		if(in->key != NULL) key = fold_static_array_key(in->key);
		bool is_ref = in->is_ref;
		_Static_value val = 0;
		if(in->val != NULL) val = fold_static_value(in->val);
		return fold_impl_static_array_elem(in, key, is_ref, val);
	}

	virtual _Branch fold_branch(Branch* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_LABEL_NAME iftrue = 0;
		if(in->iftrue != NULL) iftrue = fold_label_name(in->iftrue);
		_LABEL_NAME iffalse = 0;
		if(in->iffalse != NULL) iffalse = fold_label_name(in->iffalse);
		return fold_impl_branch(in, variable_name, iftrue, iffalse);
	}

	virtual _Goto fold_goto(Goto* in)
	{
		_LABEL_NAME label_name = 0;
		if(in->label_name != NULL) label_name = fold_label_name(in->label_name);
		return fold_impl_goto(in, label_name);
	}

	virtual _Label fold_label(Label* in)
	{
		_LABEL_NAME label_name = 0;
		if(in->label_name != NULL) label_name = fold_label_name(in->label_name);
		return fold_impl_label(in, label_name);
	}

	virtual _Foreach_reset fold_foreach_reset(Foreach_reset* in)
	{
		_VARIABLE_NAME array = 0;
		if(in->array != NULL) array = fold_variable_name(in->array);
		_HT_ITERATOR iter = 0;
		if(in->iter != NULL) iter = fold_ht_iterator(in->iter);
		return fold_impl_foreach_reset(in, array, iter);
	}

	virtual _Foreach_next fold_foreach_next(Foreach_next* in)
	{
		_VARIABLE_NAME array = 0;
		if(in->array != NULL) array = fold_variable_name(in->array);
		_HT_ITERATOR iter = 0;
		if(in->iter != NULL) iter = fold_ht_iterator(in->iter);
		return fold_impl_foreach_next(in, array, iter);
	}

	virtual _Foreach_end fold_foreach_end(Foreach_end* in)
	{
		_VARIABLE_NAME array = 0;
		if(in->array != NULL) array = fold_variable_name(in->array);
		_HT_ITERATOR iter = 0;
		if(in->iter != NULL) iter = fold_ht_iterator(in->iter);
		return fold_impl_foreach_end(in, array, iter);
	}

	virtual _Foreach_has_key fold_foreach_has_key(Foreach_has_key* in)
	{
		_VARIABLE_NAME array = 0;
		if(in->array != NULL) array = fold_variable_name(in->array);
		_HT_ITERATOR iter = 0;
		if(in->iter != NULL) iter = fold_ht_iterator(in->iter);
		return fold_impl_foreach_has_key(in, array, iter);
	}

	virtual _Foreach_get_key fold_foreach_get_key(Foreach_get_key* in)
	{
		_VARIABLE_NAME array = 0;
		if(in->array != NULL) array = fold_variable_name(in->array);
		_HT_ITERATOR iter = 0;
		if(in->iter != NULL) iter = fold_ht_iterator(in->iter);
		return fold_impl_foreach_get_key(in, array, iter);
	}

	virtual _Foreach_get_val fold_foreach_get_val(Foreach_get_val* in)
	{
		_VARIABLE_NAME array = 0;
		if(in->array != NULL) array = fold_variable_name(in->array);
		_HT_ITERATOR iter = 0;
		if(in->iter != NULL) iter = fold_ht_iterator(in->iter);
		return fold_impl_foreach_get_val(in, array, iter);
	}

	virtual _Param_is_ref fold_param_is_ref(Param_is_ref* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		_PARAM_INDEX param_index = 0;
		if(in->param_index != NULL) param_index = fold_param_index(in->param_index);
		return fold_impl_param_is_ref(in, target, method_name, param_index);
	}



// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _PHP_script fold_impl_php_script(PHP_script* orig, _List<_Statement>* statements) { assert(0); };
	virtual _Class_def fold_impl_class_def(Class_def* orig, _Class_mod class_mod, _CLASS_NAME class_name, _CLASS_NAME extends, _List<_INTERFACE_NAME>* implements, _List<_Member>* members) { assert(0); };
	virtual _Class_mod fold_impl_class_mod(Class_mod* orig, bool is_abstract, bool is_final) { assert(0); };
	virtual _Interface_def fold_impl_interface_def(Interface_def* orig, _INTERFACE_NAME interface_name, _List<_INTERFACE_NAME>* extends, _List<_Member>* members) { assert(0); };
	virtual _Method fold_impl_method(Method* orig, _Signature signature, _List<_Statement>* statements) { assert(0); };
	virtual _Signature fold_impl_signature(Signature* orig, _Method_mod method_mod, bool pass_rest_by_ref, bool return_by_ref, _METHOD_NAME method_name, _List<_Formal_parameter>* formal_parameters) { assert(0); };
	virtual _Method_mod fold_impl_method_mod(Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) { assert(0); };
	virtual _Formal_parameter fold_impl_formal_parameter(Formal_parameter* orig, _Type type, bool is_ref, _Name_with_default var) { assert(0); };
	virtual _Type fold_impl_type(Type* orig, _CLASS_NAME class_name) { assert(0); };
	virtual _Attribute fold_impl_attribute(Attribute* orig, _Attr_mod attr_mod, _Name_with_default var) { assert(0); };
	virtual _Attr_mod fold_impl_attr_mod(Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) { assert(0); };
	virtual _Name_with_default fold_impl_name_with_default(Name_with_default* orig, _VARIABLE_NAME variable_name, _Static_value default_value) { assert(0); };
	virtual _Class_alias fold_impl_class_alias(Class_alias* orig, _CLASS_NAME alias, _CLASS_NAME class_name) { assert(0); };
	virtual _Interface_alias fold_impl_interface_alias(Interface_alias* orig, _INTERFACE_NAME alias, _INTERFACE_NAME interface_name) { assert(0); };
	virtual _Method_alias fold_impl_method_alias(Method_alias* orig, _METHOD_NAME alias, _METHOD_NAME method_name) { assert(0); };
	virtual _Return fold_impl_return(Return* orig, _Rvalue rvalue) { assert(0); };
	virtual _Static_declaration fold_impl_static_declaration(Static_declaration* orig, _Name_with_default var) { assert(0); };
	virtual _Global fold_impl_global(Global* orig, _Variable_name variable_name) { assert(0); };
	virtual _Try fold_impl_try(Try* orig, _List<_Statement>* statements, _List<_Catch>* catches) { assert(0); };
	virtual _Catch fold_impl_catch(Catch* orig, _CLASS_NAME class_name, _VARIABLE_NAME variable_name, _List<_Statement>* statements) { assert(0); };
	virtual _Throw fold_impl_throw(Throw* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Assign_var fold_impl_assign_var(Assign_var* orig, _VARIABLE_NAME lhs, bool is_ref, _Expr rhs) { assert(0); };
	virtual _Assign_field fold_impl_assign_field(Assign_field* orig, _Target target, _Field_name field_name, bool is_ref, _Rvalue rhs) { assert(0); };
	virtual _Assign_array fold_impl_assign_array(Assign_array* orig, _VARIABLE_NAME lhs, _Rvalue index, bool is_ref, _Rvalue rhs) { assert(0); };
	virtual _Assign_var_var fold_impl_assign_var_var(Assign_var_var* orig, _VARIABLE_NAME lhs, bool is_ref, _Rvalue rhs) { assert(0); };
	virtual _Assign_next fold_impl_assign_next(Assign_next* orig, _VARIABLE_NAME lhs, bool is_ref, _Rvalue rhs) { assert(0); };
	virtual _Pre_op fold_impl_pre_op(Pre_op* orig, _OP op, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Eval_expr fold_impl_eval_expr(Eval_expr* orig, _Expr expr) { assert(0); };
	virtual _Unset fold_impl_unset(Unset* orig, _Target target, _Variable_name variable_name, _List<_Rvalue>* array_indices) { assert(0); };
	virtual _Isset fold_impl_isset(Isset* orig, _Target target, _Variable_name variable_name, _List<_Rvalue>* array_indices) { assert(0); };
	virtual _Field_access fold_impl_field_access(Field_access* orig, _Target target, _Field_name field_name) { assert(0); };
	virtual _Array_access fold_impl_array_access(Array_access* orig, _VARIABLE_NAME variable_name, _Rvalue index) { assert(0); };
	virtual _Array_next fold_impl_array_next(Array_next* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Cast fold_impl_cast(Cast* orig, _CAST cast, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Unary_op fold_impl_unary_op(Unary_op* orig, _OP op, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Bin_op fold_impl_bin_op(Bin_op* orig, _Rvalue left, _OP op, _Rvalue right) { assert(0); };
	virtual _Constant fold_impl_constant(Constant* orig, _CLASS_NAME class_name, _CONSTANT_NAME constant_name) { assert(0); };
	virtual _Instanceof fold_impl_instanceof(Instanceof* orig, _VARIABLE_NAME variable_name, _Class_name class_name) { assert(0); };
	virtual _Method_invocation fold_impl_method_invocation(Method_invocation* orig, _Target target, _Method_name method_name, _List<_Actual_parameter>* actual_parameters) { assert(0); };
	virtual _New fold_impl_new(New* orig, _Class_name class_name, _List<_Actual_parameter>* actual_parameters) { assert(0); };
	virtual _Actual_parameter fold_impl_actual_parameter(Actual_parameter* orig, bool is_ref, _Rvalue rvalue) { assert(0); };
	virtual _Variable_method fold_impl_variable_method(Variable_method* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Variable_variable fold_impl_variable_variable(Variable_variable* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Variable_class fold_impl_variable_class(Variable_class* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Variable_field fold_impl_variable_field(Variable_field* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Static_array fold_impl_static_array(Static_array* orig, _List<_Static_array_elem>* static_array_elems) { assert(0); };
	virtual _Static_array_elem fold_impl_static_array_elem(Static_array_elem* orig, _Static_array_key key, bool is_ref, _Static_value val) { assert(0); };
	virtual _Branch fold_impl_branch(Branch* orig, _VARIABLE_NAME variable_name, _LABEL_NAME iftrue, _LABEL_NAME iffalse) { assert(0); };
	virtual _Goto fold_impl_goto(Goto* orig, _LABEL_NAME label_name) { assert(0); };
	virtual _Label fold_impl_label(Label* orig, _LABEL_NAME label_name) { assert(0); };
	virtual _Foreach_reset fold_impl_foreach_reset(Foreach_reset* orig, _VARIABLE_NAME array, _HT_ITERATOR iter) { assert(0); };
	virtual _Foreach_next fold_impl_foreach_next(Foreach_next* orig, _VARIABLE_NAME array, _HT_ITERATOR iter) { assert(0); };
	virtual _Foreach_end fold_impl_foreach_end(Foreach_end* orig, _VARIABLE_NAME array, _HT_ITERATOR iter) { assert(0); };
	virtual _Foreach_has_key fold_impl_foreach_has_key(Foreach_has_key* orig, _VARIABLE_NAME array, _HT_ITERATOR iter) { assert(0); };
	virtual _Foreach_get_key fold_impl_foreach_get_key(Foreach_get_key* orig, _VARIABLE_NAME array, _HT_ITERATOR iter) { assert(0); };
	virtual _Foreach_get_val fold_impl_foreach_get_val(Foreach_get_val* orig, _VARIABLE_NAME array, _HT_ITERATOR iter) { assert(0); };
	virtual _Param_is_ref fold_impl_param_is_ref(Param_is_ref* orig, _Target target, _Method_name method_name, _PARAM_INDEX param_index) { assert(0); };

	virtual _PARAM_INDEX fold_param_index(PARAM_INDEX* orig) { assert(0); };
	virtual _FOREIGN fold_foreign(FOREIGN* orig) { assert(0); };
	virtual _CLASS_NAME fold_class_name(CLASS_NAME* orig) { assert(0); };
	virtual _INTERFACE_NAME fold_interface_name(INTERFACE_NAME* orig) { assert(0); };
	virtual _METHOD_NAME fold_method_name(METHOD_NAME* orig) { assert(0); };
	virtual _VARIABLE_NAME fold_variable_name(VARIABLE_NAME* orig) { assert(0); };
	virtual _OP fold_op(OP* orig) { assert(0); };
	virtual _INT fold_int(INT* orig) { assert(0); };
	virtual _REAL fold_real(REAL* orig) { assert(0); };
	virtual _STRING fold_string(STRING* orig) { assert(0); };
	virtual _BOOL fold_bool(BOOL* orig) { assert(0); };
	virtual _NIL fold_nil(NIL* orig) { assert(0); };
	virtual _CAST fold_cast(CAST* orig) { assert(0); };
	virtual _CONSTANT_NAME fold_constant_name(CONSTANT_NAME* orig) { assert(0); };
	virtual _FIELD_NAME fold_field_name(FIELD_NAME* orig) { assert(0); };
	virtual _LABEL_NAME fold_label_name(LABEL_NAME* orig) { assert(0); };
	virtual _HT_ITERATOR fold_ht_iterator(HT_ITERATOR* orig) { assert(0); };


// Manual dispatching for abstract classes
// Override only if you know what you are doing!
	virtual _Node fold_node(Node* in)
	{
		switch(in->classid())
		{
			case PHP_script::ID:
				return fold_php_script(dynamic_cast<PHP_script*>(in));
			case Class_def::ID:
				return fold_class_def(dynamic_cast<Class_def*>(in));
			case Interface_def::ID:
				return fold_interface_def(dynamic_cast<Interface_def*>(in));
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Class_alias::ID:
				return fold_class_alias(dynamic_cast<Class_alias*>(in));
			case Interface_alias::ID:
				return fold_interface_alias(dynamic_cast<Interface_alias*>(in));
			case Method_alias::ID:
				return fold_method_alias(dynamic_cast<Method_alias*>(in));
			case Return::ID:
				return fold_return(dynamic_cast<Return*>(in));
			case Static_declaration::ID:
				return fold_static_declaration(dynamic_cast<Static_declaration*>(in));
			case Global::ID:
				return fold_global(dynamic_cast<Global*>(in));
			case Try::ID:
				return fold_try(dynamic_cast<Try*>(in));
			case Throw::ID:
				return fold_throw(dynamic_cast<Throw*>(in));
			case Assign_var::ID:
				return fold_assign_var(dynamic_cast<Assign_var*>(in));
			case Assign_var_var::ID:
				return fold_assign_var_var(dynamic_cast<Assign_var_var*>(in));
			case Assign_array::ID:
				return fold_assign_array(dynamic_cast<Assign_array*>(in));
			case Assign_next::ID:
				return fold_assign_next(dynamic_cast<Assign_next*>(in));
			case Assign_field::ID:
				return fold_assign_field(dynamic_cast<Assign_field*>(in));
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case Pre_op::ID:
				return fold_pre_op(dynamic_cast<Pre_op*>(in));
			case Unset::ID:
				return fold_unset(dynamic_cast<Unset*>(in));
			case Label::ID:
				return fold_label(dynamic_cast<Label*>(in));
			case Goto::ID:
				return fold_goto(dynamic_cast<Goto*>(in));
			case Branch::ID:
				return fold_branch(dynamic_cast<Branch*>(in));
			case Foreach_next::ID:
				return fold_foreach_next(dynamic_cast<Foreach_next*>(in));
			case Foreach_reset::ID:
				return fold_foreach_reset(dynamic_cast<Foreach_reset*>(in));
			case Foreach_end::ID:
				return fold_foreach_end(dynamic_cast<Foreach_end*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
			case Class_mod::ID:
				return fold_class_mod(dynamic_cast<Class_mod*>(in));
			case Attribute::ID:
				return fold_attribute(dynamic_cast<Attribute*>(in));
			case Signature::ID:
				return fold_signature(dynamic_cast<Signature*>(in));
			case Method_mod::ID:
				return fold_method_mod(dynamic_cast<Method_mod*>(in));
			case Formal_parameter::ID:
				return fold_formal_parameter(dynamic_cast<Formal_parameter*>(in));
			case Type::ID:
				return fold_type(dynamic_cast<Type*>(in));
			case Attr_mod::ID:
				return fold_attr_mod(dynamic_cast<Attr_mod*>(in));
			case Name_with_default::ID:
				return fold_name_with_default(dynamic_cast<Name_with_default*>(in));
			case Catch::ID:
				return fold_catch(dynamic_cast<Catch*>(in));
			case Cast::ID:
				return fold_cast(dynamic_cast<Cast*>(in));
			case Unary_op::ID:
				return fold_unary_op(dynamic_cast<Unary_op*>(in));
			case Bin_op::ID:
				return fold_bin_op(dynamic_cast<Bin_op*>(in));
			case Constant::ID:
				return fold_constant(dynamic_cast<Constant*>(in));
			case Instanceof::ID:
				return fold_instanceof(dynamic_cast<Instanceof*>(in));
			case Method_invocation::ID:
				return fold_method_invocation(dynamic_cast<Method_invocation*>(in));
			case New::ID:
				return fold_new(dynamic_cast<New*>(in));
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
			case REAL::ID:
				return fold_real(dynamic_cast<REAL*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case BOOL::ID:
				return fold_bool(dynamic_cast<BOOL*>(in));
			case NIL::ID:
				return fold_nil(dynamic_cast<NIL*>(in));
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case Variable_variable::ID:
				return fold_variable_variable(dynamic_cast<Variable_variable*>(in));
			case Array_access::ID:
				return fold_array_access(dynamic_cast<Array_access*>(in));
			case Field_access::ID:
				return fold_field_access(dynamic_cast<Field_access*>(in));
			case Array_next::ID:
				return fold_array_next(dynamic_cast<Array_next*>(in));
			case Isset::ID:
				return fold_isset(dynamic_cast<Isset*>(in));
			case Foreach_has_key::ID:
				return fold_foreach_has_key(dynamic_cast<Foreach_has_key*>(in));
			case Foreach_get_key::ID:
				return fold_foreach_get_key(dynamic_cast<Foreach_get_key*>(in));
			case Foreach_get_val::ID:
				return fold_foreach_get_val(dynamic_cast<Foreach_get_val*>(in));
			case Param_is_ref::ID:
				return fold_param_is_ref(dynamic_cast<Param_is_ref*>(in));
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
			case Actual_parameter::ID:
				return fold_actual_parameter(dynamic_cast<Actual_parameter*>(in));
			case METHOD_NAME::ID:
				return fold_method_name(dynamic_cast<METHOD_NAME*>(in));
			case Variable_method::ID:
				return fold_variable_method(dynamic_cast<Variable_method*>(in));
			case Variable_class::ID:
				return fold_variable_class(dynamic_cast<Variable_class*>(in));
			case FIELD_NAME::ID:
				return fold_field_name(dynamic_cast<FIELD_NAME*>(in));
			case Variable_field::ID:
				return fold_variable_field(dynamic_cast<Variable_field*>(in));
			case Static_array::ID:
				return fold_static_array(dynamic_cast<Static_array*>(in));
			case Static_array_elem::ID:
				return fold_static_array_elem(dynamic_cast<Static_array_elem*>(in));
			case INTERFACE_NAME::ID:
				return fold_interface_name(dynamic_cast<INTERFACE_NAME*>(in));
			case CAST::ID:
				return fold_cast(dynamic_cast<CAST*>(in));
			case OP::ID:
				return fold_op(dynamic_cast<OP*>(in));
			case CONSTANT_NAME::ID:
				return fold_constant_name(dynamic_cast<CONSTANT_NAME*>(in));
			case LABEL_NAME::ID:
				return fold_label_name(dynamic_cast<LABEL_NAME*>(in));
			case HT_ITERATOR::ID:
				return fold_ht_iterator(dynamic_cast<HT_ITERATOR*>(in));
			case PARAM_INDEX::ID:
				return fold_param_index(dynamic_cast<PARAM_INDEX*>(in));
		}
		assert(0);
	}

	virtual _Statement fold_statement(Statement* in)
	{
		switch(in->classid())
		{
			case Class_def::ID:
				return fold_class_def(dynamic_cast<Class_def*>(in));
			case Interface_def::ID:
				return fold_interface_def(dynamic_cast<Interface_def*>(in));
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Class_alias::ID:
				return fold_class_alias(dynamic_cast<Class_alias*>(in));
			case Interface_alias::ID:
				return fold_interface_alias(dynamic_cast<Interface_alias*>(in));
			case Method_alias::ID:
				return fold_method_alias(dynamic_cast<Method_alias*>(in));
			case Return::ID:
				return fold_return(dynamic_cast<Return*>(in));
			case Static_declaration::ID:
				return fold_static_declaration(dynamic_cast<Static_declaration*>(in));
			case Global::ID:
				return fold_global(dynamic_cast<Global*>(in));
			case Try::ID:
				return fold_try(dynamic_cast<Try*>(in));
			case Throw::ID:
				return fold_throw(dynamic_cast<Throw*>(in));
			case Assign_var::ID:
				return fold_assign_var(dynamic_cast<Assign_var*>(in));
			case Assign_var_var::ID:
				return fold_assign_var_var(dynamic_cast<Assign_var_var*>(in));
			case Assign_array::ID:
				return fold_assign_array(dynamic_cast<Assign_array*>(in));
			case Assign_next::ID:
				return fold_assign_next(dynamic_cast<Assign_next*>(in));
			case Assign_field::ID:
				return fold_assign_field(dynamic_cast<Assign_field*>(in));
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case Pre_op::ID:
				return fold_pre_op(dynamic_cast<Pre_op*>(in));
			case Unset::ID:
				return fold_unset(dynamic_cast<Unset*>(in));
			case Label::ID:
				return fold_label(dynamic_cast<Label*>(in));
			case Goto::ID:
				return fold_goto(dynamic_cast<Goto*>(in));
			case Branch::ID:
				return fold_branch(dynamic_cast<Branch*>(in));
			case Foreach_next::ID:
				return fold_foreach_next(dynamic_cast<Foreach_next*>(in));
			case Foreach_reset::ID:
				return fold_foreach_reset(dynamic_cast<Foreach_reset*>(in));
			case Foreach_end::ID:
				return fold_foreach_end(dynamic_cast<Foreach_end*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
		}
		assert(0);
	}

	virtual _Member fold_member(Member* in)
	{
		switch(in->classid())
		{
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Attribute::ID:
				return fold_attribute(dynamic_cast<Attribute*>(in));
		}
		assert(0);
	}

	virtual _Expr fold_expr(Expr* in)
	{
		switch(in->classid())
		{
			case Cast::ID:
				return fold_cast(dynamic_cast<Cast*>(in));
			case Unary_op::ID:
				return fold_unary_op(dynamic_cast<Unary_op*>(in));
			case Bin_op::ID:
				return fold_bin_op(dynamic_cast<Bin_op*>(in));
			case Constant::ID:
				return fold_constant(dynamic_cast<Constant*>(in));
			case Instanceof::ID:
				return fold_instanceof(dynamic_cast<Instanceof*>(in));
			case Method_invocation::ID:
				return fold_method_invocation(dynamic_cast<Method_invocation*>(in));
			case New::ID:
				return fold_new(dynamic_cast<New*>(in));
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
			case REAL::ID:
				return fold_real(dynamic_cast<REAL*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case BOOL::ID:
				return fold_bool(dynamic_cast<BOOL*>(in));
			case NIL::ID:
				return fold_nil(dynamic_cast<NIL*>(in));
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case Variable_variable::ID:
				return fold_variable_variable(dynamic_cast<Variable_variable*>(in));
			case Array_access::ID:
				return fold_array_access(dynamic_cast<Array_access*>(in));
			case Field_access::ID:
				return fold_field_access(dynamic_cast<Field_access*>(in));
			case Array_next::ID:
				return fold_array_next(dynamic_cast<Array_next*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
			case Isset::ID:
				return fold_isset(dynamic_cast<Isset*>(in));
			case Foreach_has_key::ID:
				return fold_foreach_has_key(dynamic_cast<Foreach_has_key*>(in));
			case Foreach_get_key::ID:
				return fold_foreach_get_key(dynamic_cast<Foreach_get_key*>(in));
			case Foreach_get_val::ID:
				return fold_foreach_get_val(dynamic_cast<Foreach_get_val*>(in));
			case Param_is_ref::ID:
				return fold_param_is_ref(dynamic_cast<Param_is_ref*>(in));
		}
		assert(0);
	}

	virtual _Literal fold_literal(Literal* in)
	{
		switch(in->classid())
		{
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
			case REAL::ID:
				return fold_real(dynamic_cast<REAL*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case BOOL::ID:
				return fold_bool(dynamic_cast<BOOL*>(in));
			case NIL::ID:
				return fold_nil(dynamic_cast<NIL*>(in));
		}
		assert(0);
	}

	virtual _Rvalue fold_rvalue(Rvalue* in)
	{
		switch(in->classid())
		{
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
			case REAL::ID:
				return fold_real(dynamic_cast<REAL*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case BOOL::ID:
				return fold_bool(dynamic_cast<BOOL*>(in));
			case NIL::ID:
				return fold_nil(dynamic_cast<NIL*>(in));
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
		}
		assert(0);
	}

	virtual _Target fold_target(Target* in)
	{
		switch(in->classid())
		{
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
		}
		assert(0);
	}

	virtual _Method_name fold_method_name(Method_name* in)
	{
		switch(in->classid())
		{
			case METHOD_NAME::ID:
				return fold_method_name(dynamic_cast<METHOD_NAME*>(in));
			case Variable_method::ID:
				return fold_variable_method(dynamic_cast<Variable_method*>(in));
		}
		assert(0);
	}

	virtual _Variable_name fold_variable_name(Variable_name* in)
	{
		switch(in->classid())
		{
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case Variable_variable::ID:
				return fold_variable_variable(dynamic_cast<Variable_variable*>(in));
		}
		assert(0);
	}

	virtual _Class_name fold_class_name(Class_name* in)
	{
		switch(in->classid())
		{
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
			case Variable_class::ID:
				return fold_variable_class(dynamic_cast<Variable_class*>(in));
		}
		assert(0);
	}

	virtual _Field_name fold_field_name(Field_name* in)
	{
		switch(in->classid())
		{
			case FIELD_NAME::ID:
				return fold_field_name(dynamic_cast<FIELD_NAME*>(in));
			case Variable_field::ID:
				return fold_variable_field(dynamic_cast<Variable_field*>(in));
		}
		assert(0);
	}

	virtual _Static_value fold_static_value(Static_value* in)
	{
		switch(in->classid())
		{
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
			case REAL::ID:
				return fold_real(dynamic_cast<REAL*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case BOOL::ID:
				return fold_bool(dynamic_cast<BOOL*>(in));
			case NIL::ID:
				return fold_nil(dynamic_cast<NIL*>(in));
			case Static_array::ID:
				return fold_static_array(dynamic_cast<Static_array*>(in));
			case Constant::ID:
				return fold_constant(dynamic_cast<Constant*>(in));
		}
		assert(0);
	}

	virtual _Static_array_key fold_static_array_key(Static_array_key* in)
	{
		switch(in->classid())
		{
			case INT::ID:
				return fold_int(dynamic_cast<INT*>(in));
			case REAL::ID:
				return fold_real(dynamic_cast<REAL*>(in));
			case STRING::ID:
				return fold_string(dynamic_cast<STRING*>(in));
			case BOOL::ID:
				return fold_bool(dynamic_cast<BOOL*>(in));
			case NIL::ID:
				return fold_nil(dynamic_cast<NIL*>(in));
			case Constant::ID:
				return fold_constant(dynamic_cast<Constant*>(in));
		}
		assert(0);
	}

	virtual _Identifier fold_identifier(Identifier* in)
	{
		switch(in->classid())
		{
			case INTERFACE_NAME::ID:
				return fold_interface_name(dynamic_cast<INTERFACE_NAME*>(in));
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
			case METHOD_NAME::ID:
				return fold_method_name(dynamic_cast<METHOD_NAME*>(in));
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case FIELD_NAME::ID:
				return fold_field_name(dynamic_cast<FIELD_NAME*>(in));
			case CAST::ID:
				return fold_cast(dynamic_cast<CAST*>(in));
			case OP::ID:
				return fold_op(dynamic_cast<OP*>(in));
			case CONSTANT_NAME::ID:
				return fold_constant_name(dynamic_cast<CONSTANT_NAME*>(in));
			case LABEL_NAME::ID:
				return fold_label_name(dynamic_cast<LABEL_NAME*>(in));
			case HT_ITERATOR::ID:
				return fold_ht_iterator(dynamic_cast<HT_ITERATOR*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T, template <class _Tp, class _Alloc = typename List<_Tp>::allocator_type> class _List>
class Uniform_fold : public Fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, _List> {};
}

