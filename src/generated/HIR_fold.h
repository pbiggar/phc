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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


#include "HIR.h"
namespace HIR{
template
<class _Node,
 class _PHP_script,
 class _Statement,
 class _Class_def,
 class _Class_mod,
 class _Interface_def,
 class _Member,
 class _Method,
 class _Signature,
 class _Method_mod,
 class _Formal_parameter,
 class _Type,
 class _Attribute,
 class _Attr_mod,
 class _Name_with_default,
 class _If,
 class _Loop,
 class _Foreach,
 class _Break,
 class _Continue,
 class _Return,
 class _Static_declaration,
 class _Global,
 class _Try,
 class _Catch,
 class _Throw,
 class _Eval_expr,
 class _Foreign,
 class _Foreign_statement,
 class _Foreign_expr,
 class _Expr,
 class _Literal,
 class _Assignment,
 class _Op_assignment,
 class _Cast,
 class _Unary_op,
 class _Bin_op,
 class _Constant,
 class _Instanceof,
 class _Variable,
 class _Variable_name,
 class _Reflection,
 class _Target,
 class _Pre_op,
 class _Array,
 class _Array_elem,
 class _Method_invocation,
 class _Method_name,
 class _Actual_parameter,
 class _New,
 class _Class_name,
 class _Identifier,
 class _CLASS_NAME,
 class _INTERFACE_NAME,
 class _METHOD_NAME,
 class _VARIABLE_NAME,
 class _INT,
 class _REAL,
 class _STRING,
 class _BOOL,
 class _NIL,
 class _OP,
 class _CAST,
 class _CONSTANT_NAME>
class Fold
{
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _PHP_script fold_php_script(PHP_script* in)
	{
		List<_Statement>* statements = 0;
	
		{
			statements = new List<_Statement>;
			List<Statement*>::const_iterator i;
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
		List<_INTERFACE_NAME>* implements = 0;
	
		{
			implements = new List<_INTERFACE_NAME>;
			List<INTERFACE_NAME*>::const_iterator i;
			for(i = in->implements->begin(); i != in->implements->end(); i++)
				if(*i != NULL) implements->push_back(fold_interface_name(*i));
				else implements->push_back(0);
		}
		List<_Member>* members = 0;
	
		{
			members = new List<_Member>;
			List<Member*>::const_iterator i;
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
		List<_INTERFACE_NAME>* extends = 0;
	
		{
			extends = new List<_INTERFACE_NAME>;
			List<INTERFACE_NAME*>::const_iterator i;
			for(i = in->extends->begin(); i != in->extends->end(); i++)
				if(*i != NULL) extends->push_back(fold_interface_name(*i));
				else extends->push_back(0);
		}
		List<_Member>* members = 0;
	
		{
			members = new List<_Member>;
			List<Member*>::const_iterator i;
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
		List<_Statement>* statements = 0;
	if (in->statements)
		{
			statements = new List<_Statement>;
			List<Statement*>::const_iterator i;
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
		bool is_ref = in->is_ref;
		_METHOD_NAME method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		List<_Formal_parameter>* formal_parameters = 0;
	
		{
			formal_parameters = new List<_Formal_parameter>;
			List<Formal_parameter*>::const_iterator i;
			for(i = in->formal_parameters->begin(); i != in->formal_parameters->end(); i++)
				if(*i != NULL) formal_parameters->push_back(fold_formal_parameter(*i));
				else formal_parameters->push_back(0);
		}
		return fold_impl_signature(in, method_mod, is_ref, method_name, formal_parameters);
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
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_name_with_default(in, variable_name, expr);
	}

	virtual _If fold_if(If* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_Statement>* iftrue = 0;
	
		{
			iftrue = new List<_Statement>;
			List<Statement*>::const_iterator i;
			for(i = in->iftrue->begin(); i != in->iftrue->end(); i++)
				if(*i != NULL) iftrue->push_back(fold_statement(*i));
				else iftrue->push_back(0);
		}
		List<_Statement>* iffalse = 0;
	
		{
			iffalse = new List<_Statement>;
			List<Statement*>::const_iterator i;
			for(i = in->iffalse->begin(); i != in->iffalse->end(); i++)
				if(*i != NULL) iffalse->push_back(fold_statement(*i));
				else iffalse->push_back(0);
		}
		return fold_impl_if(in, variable_name, iftrue, iffalse);
	}

	virtual _Loop fold_loop(Loop* in)
	{
		List<_Statement>* statements = 0;
	
		{
			statements = new List<_Statement>;
			List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_loop(in, statements);
	}

	virtual _Foreach fold_foreach(Foreach* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Variable key = 0;
		if(in->key != NULL) key = fold_variable(in->key);
		bool is_ref = in->is_ref;
		_Variable val = 0;
		if(in->val != NULL) val = fold_variable(in->val);
		List<_Statement>* statements = 0;
	
		{
			statements = new List<_Statement>;
			List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_foreach(in, variable_name, key, is_ref, val, statements);
	}

	virtual _Break fold_break(Break* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_break(in, expr);
	}

	virtual _Continue fold_continue(Continue* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_continue(in, expr);
	}

	virtual _Return fold_return(Return* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_return(in, expr);
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
		List<_Statement>* statements = 0;
	
		{
			statements = new List<_Statement>;
			List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		List<_Catch>* catches = 0;
	
		{
			catches = new List<_Catch>;
			List<Catch*>::const_iterator i;
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
		List<_Statement>* statements = 0;
	
		{
			statements = new List<_Statement>;
			List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_catch(in, class_name, variable_name, statements);
	}

	virtual _Throw fold_throw(Throw* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_throw(in, expr);
	}

	virtual _Eval_expr fold_eval_expr(Eval_expr* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_eval_expr(in, expr);
	}

	virtual _Foreign_statement fold_foreign_statement(Foreign_statement* in)
	{
		return fold_impl_foreign_statement(in);
	}

	virtual _Foreign_expr fold_foreign_expr(Foreign_expr* in)
	{
		return fold_impl_foreign_expr(in);
	}

	virtual _Assignment fold_assignment(Assignment* in)
	{
		_Variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		bool is_ref = in->is_ref;
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_assignment(in, variable, is_ref, expr);
	}

	virtual _Op_assignment fold_op_assignment(Op_assignment* in)
	{
		_Variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_op_assignment(in, variable, op, expr);
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
		_VARIABLE_NAME left = 0;
		if(in->left != NULL) left = fold_variable_name(in->left);
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_VARIABLE_NAME right = 0;
		if(in->right != NULL) right = fold_variable_name(in->right);
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

	virtual _Variable fold_variable(Variable* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_VARIABLE_NAME>* array_indices = 0;
	
		{
			array_indices = new List<_VARIABLE_NAME>;
			List<VARIABLE_NAME*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_variable_name(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_variable(in, target, variable_name, array_indices);
	}

	virtual _Reflection fold_reflection(Reflection* in)
	{
		_VARIABLE_NAME variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_reflection(in, variable_name);
	}

	virtual _Pre_op fold_pre_op(Pre_op* in)
	{
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		return fold_impl_pre_op(in, op, variable);
	}

	virtual _Array fold_array(Array* in)
	{
		List<_Array_elem>* array_elems = 0;
	
		{
			array_elems = new List<_Array_elem>;
			List<Array_elem*>::const_iterator i;
			for(i = in->array_elems->begin(); i != in->array_elems->end(); i++)
				if(*i != NULL) array_elems->push_back(fold_array_elem(*i));
				else array_elems->push_back(0);
		}
		return fold_impl_array(in, array_elems);
	}

	virtual _Array_elem fold_array_elem(Array_elem* in)
	{
		_Expr key = 0;
		if(in->key != NULL) key = fold_expr(in->key);
		bool is_ref = in->is_ref;
		_Expr val = 0;
		if(in->val != NULL) val = fold_expr(in->val);
		return fold_impl_array_elem(in, key, is_ref, val);
	}

	virtual _Method_invocation fold_method_invocation(Method_invocation* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		List<_Actual_parameter>* actual_parameters = 0;
	
		{
			actual_parameters = new List<_Actual_parameter>;
			List<Actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_method_invocation(in, target, method_name, actual_parameters);
	}

	virtual _Actual_parameter fold_actual_parameter(Actual_parameter* in)
	{
		bool is_ref = in->is_ref;
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_actual_parameter(in, is_ref, expr);
	}

	virtual _New fold_new(New* in)
	{
		_Class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		List<_Actual_parameter>* actual_parameters = 0;
	
		{
			actual_parameters = new List<_Actual_parameter>;
			List<Actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_new(in, class_name, actual_parameters);
	}



// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _PHP_script fold_impl_php_script(PHP_script* orig, List<_Statement>* statements) { assert(0); };
	virtual _Class_def fold_impl_class_def(Class_def* orig, _Class_mod class_mod, _CLASS_NAME class_name, _CLASS_NAME extends, List<_INTERFACE_NAME>* implements, List<_Member>* members) { assert(0); };
	virtual _Class_mod fold_impl_class_mod(Class_mod* orig, bool is_abstract, bool is_final) { assert(0); };
	virtual _Interface_def fold_impl_interface_def(Interface_def* orig, _INTERFACE_NAME interface_name, List<_INTERFACE_NAME>* extends, List<_Member>* members) { assert(0); };
	virtual _Method fold_impl_method(Method* orig, _Signature signature, List<_Statement>* statements) { assert(0); };
	virtual _Signature fold_impl_signature(Signature* orig, _Method_mod method_mod, bool is_ref, _METHOD_NAME method_name, List<_Formal_parameter>* formal_parameters) { assert(0); };
	virtual _Method_mod fold_impl_method_mod(Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) { assert(0); };
	virtual _Formal_parameter fold_impl_formal_parameter(Formal_parameter* orig, _Type type, bool is_ref, _Name_with_default var) { assert(0); };
	virtual _Type fold_impl_type(Type* orig, _CLASS_NAME class_name) { assert(0); };
	virtual _Attribute fold_impl_attribute(Attribute* orig, _Attr_mod attr_mod, _Name_with_default var) { assert(0); };
	virtual _Attr_mod fold_impl_attr_mod(Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) { assert(0); };
	virtual _Name_with_default fold_impl_name_with_default(Name_with_default* orig, _VARIABLE_NAME variable_name, _Expr expr) { assert(0); };
	virtual _If fold_impl_if(If* orig, _VARIABLE_NAME variable_name, List<_Statement>* iftrue, List<_Statement>* iffalse) { assert(0); };
	virtual _Loop fold_impl_loop(Loop* orig, List<_Statement>* statements) { assert(0); };
	virtual _Foreach fold_impl_foreach(Foreach* orig, _VARIABLE_NAME variable_name, _Variable key, bool is_ref, _Variable val, List<_Statement>* statements) { assert(0); };
	virtual _Break fold_impl_break(Break* orig, _Expr expr) { assert(0); };
	virtual _Continue fold_impl_continue(Continue* orig, _Expr expr) { assert(0); };
	virtual _Return fold_impl_return(Return* orig, _Expr expr) { assert(0); };
	virtual _Static_declaration fold_impl_static_declaration(Static_declaration* orig, _Name_with_default var) { assert(0); };
	virtual _Global fold_impl_global(Global* orig, _Variable_name variable_name) { assert(0); };
	virtual _Try fold_impl_try(Try* orig, List<_Statement>* statements, List<_Catch>* catches) { assert(0); };
	virtual _Catch fold_impl_catch(Catch* orig, _CLASS_NAME class_name, _VARIABLE_NAME variable_name, List<_Statement>* statements) { assert(0); };
	virtual _Throw fold_impl_throw(Throw* orig, _Expr expr) { assert(0); };
	virtual _Eval_expr fold_impl_eval_expr(Eval_expr* orig, _Expr expr) { assert(0); };
	virtual _Foreign_statement fold_impl_foreign_statement(Foreign_statement* orig) { assert(0); };
	virtual _Foreign_expr fold_impl_foreign_expr(Foreign_expr* orig) { assert(0); };
	virtual _Assignment fold_impl_assignment(Assignment* orig, _Variable variable, bool is_ref, _Expr expr) { assert(0); };
	virtual _Op_assignment fold_impl_op_assignment(Op_assignment* orig, _Variable variable, _OP op, _Expr expr) { assert(0); };
	virtual _Cast fold_impl_cast(Cast* orig, _CAST cast, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Unary_op fold_impl_unary_op(Unary_op* orig, _OP op, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Bin_op fold_impl_bin_op(Bin_op* orig, _VARIABLE_NAME left, _OP op, _VARIABLE_NAME right) { assert(0); };
	virtual _Constant fold_impl_constant(Constant* orig, _CLASS_NAME class_name, _CONSTANT_NAME constant_name) { assert(0); };
	virtual _Instanceof fold_impl_instanceof(Instanceof* orig, _VARIABLE_NAME variable_name, _Class_name class_name) { assert(0); };
	virtual _Variable fold_impl_variable(Variable* orig, _Target target, _Variable_name variable_name, List<_VARIABLE_NAME>* array_indices) { assert(0); };
	virtual _Reflection fold_impl_reflection(Reflection* orig, _VARIABLE_NAME variable_name) { assert(0); };
	virtual _Pre_op fold_impl_pre_op(Pre_op* orig, _OP op, _Variable variable) { assert(0); };
	virtual _Array fold_impl_array(Array* orig, List<_Array_elem>* array_elems) { assert(0); };
	virtual _Array_elem fold_impl_array_elem(Array_elem* orig, _Expr key, bool is_ref, _Expr val) { assert(0); };
	virtual _Method_invocation fold_impl_method_invocation(Method_invocation* orig, _Target target, _Method_name method_name, List<_Actual_parameter>* actual_parameters) { assert(0); };
	virtual _Actual_parameter fold_impl_actual_parameter(Actual_parameter* orig, bool is_ref, _Expr expr) { assert(0); };
	virtual _New fold_impl_new(New* orig, _Class_name class_name, List<_Actual_parameter>* actual_parameters) { assert(0); };

	virtual _CLASS_NAME fold_class_name(CLASS_NAME* orig) { assert(0); };
	virtual _INTERFACE_NAME fold_interface_name(INTERFACE_NAME* orig) { assert(0); };
	virtual _METHOD_NAME fold_method_name(METHOD_NAME* orig) { assert(0); };
	virtual _VARIABLE_NAME fold_variable_name(VARIABLE_NAME* orig) { assert(0); };
	virtual _INT fold_int(INT* orig) { assert(0); };
	virtual _REAL fold_real(REAL* orig) { assert(0); };
	virtual _STRING fold_string(STRING* orig) { assert(0); };
	virtual _BOOL fold_bool(BOOL* orig) { assert(0); };
	virtual _NIL fold_nil(NIL* orig) { assert(0); };
	virtual _OP fold_op(OP* orig) { assert(0); };
	virtual _CAST fold_cast(CAST* orig) { assert(0); };
	virtual _CONSTANT_NAME fold_constant_name(CONSTANT_NAME* orig) { assert(0); };


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
			case Return::ID:
				return fold_return(dynamic_cast<Return*>(in));
			case Static_declaration::ID:
				return fold_static_declaration(dynamic_cast<Static_declaration*>(in));
			case Global::ID:
				return fold_global(dynamic_cast<Global*>(in));
			case Assignment::ID:
				return fold_assignment(dynamic_cast<Assignment*>(in));
			case Try::ID:
				return fold_try(dynamic_cast<Try*>(in));
			case Throw::ID:
				return fold_throw(dynamic_cast<Throw*>(in));
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case Loop::ID:
				return fold_loop(dynamic_cast<Loop*>(in));
			case Foreach::ID:
				return fold_foreach(dynamic_cast<Foreach*>(in));
			case Break::ID:
				return fold_break(dynamic_cast<Break*>(in));
			case Continue::ID:
				return fold_continue(dynamic_cast<Continue*>(in));
			case Foreign_statement::ID:
				return fold_foreign_statement(dynamic_cast<Foreign_statement*>(in));
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
			case Foreign_expr::ID:
				return fold_foreign_expr(dynamic_cast<Foreign_expr*>(in));
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case Reflection::ID:
				return fold_reflection(dynamic_cast<Reflection*>(in));
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
			case Variable::ID:
				return fold_variable(dynamic_cast<Variable*>(in));
			case Pre_op::ID:
				return fold_pre_op(dynamic_cast<Pre_op*>(in));
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
			case Op_assignment::ID:
				return fold_op_assignment(dynamic_cast<Op_assignment*>(in));
			case Array::ID:
				return fold_array(dynamic_cast<Array*>(in));
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
			case Array_elem::ID:
				return fold_array_elem(dynamic_cast<Array_elem*>(in));
			case METHOD_NAME::ID:
				return fold_method_name(dynamic_cast<METHOD_NAME*>(in));
			case Actual_parameter::ID:
				return fold_actual_parameter(dynamic_cast<Actual_parameter*>(in));
			case INTERFACE_NAME::ID:
				return fold_interface_name(dynamic_cast<INTERFACE_NAME*>(in));
			case CAST::ID:
				return fold_cast(dynamic_cast<CAST*>(in));
			case OP::ID:
				return fold_op(dynamic_cast<OP*>(in));
			case CONSTANT_NAME::ID:
				return fold_constant_name(dynamic_cast<CONSTANT_NAME*>(in));
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
			case Return::ID:
				return fold_return(dynamic_cast<Return*>(in));
			case Static_declaration::ID:
				return fold_static_declaration(dynamic_cast<Static_declaration*>(in));
			case Global::ID:
				return fold_global(dynamic_cast<Global*>(in));
			case Assignment::ID:
				return fold_assignment(dynamic_cast<Assignment*>(in));
			case Try::ID:
				return fold_try(dynamic_cast<Try*>(in));
			case Throw::ID:
				return fold_throw(dynamic_cast<Throw*>(in));
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case Loop::ID:
				return fold_loop(dynamic_cast<Loop*>(in));
			case Foreach::ID:
				return fold_foreach(dynamic_cast<Foreach*>(in));
			case Break::ID:
				return fold_break(dynamic_cast<Break*>(in));
			case Continue::ID:
				return fold_continue(dynamic_cast<Continue*>(in));
			case Foreign_statement::ID:
				return fold_foreign_statement(dynamic_cast<Foreign_statement*>(in));
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

	virtual _Foreign fold_foreign(Foreign* in)
	{
		switch(in->classid())
		{
			case Foreign_statement::ID:
				return fold_foreign_statement(dynamic_cast<Foreign_statement*>(in));
			case Foreign_expr::ID:
				return fold_foreign_expr(dynamic_cast<Foreign_expr*>(in));
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
			case Variable::ID:
				return fold_variable(dynamic_cast<Variable*>(in));
			case Pre_op::ID:
				return fold_pre_op(dynamic_cast<Pre_op*>(in));
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
			case Op_assignment::ID:
				return fold_op_assignment(dynamic_cast<Op_assignment*>(in));
			case Array::ID:
				return fold_array(dynamic_cast<Array*>(in));
			case Foreign_expr::ID:
				return fold_foreign_expr(dynamic_cast<Foreign_expr*>(in));
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

	virtual _Variable_name fold_variable_name(Variable_name* in)
	{
		switch(in->classid())
		{
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case Reflection::ID:
				return fold_reflection(dynamic_cast<Reflection*>(in));
		}
		assert(0);
	}

	virtual _Target fold_target(Target* in)
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
			case Variable::ID:
				return fold_variable(dynamic_cast<Variable*>(in));
			case Pre_op::ID:
				return fold_pre_op(dynamic_cast<Pre_op*>(in));
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
			case Op_assignment::ID:
				return fold_op_assignment(dynamic_cast<Op_assignment*>(in));
			case Array::ID:
				return fold_array(dynamic_cast<Array*>(in));
			case Foreign_expr::ID:
				return fold_foreign_expr(dynamic_cast<Foreign_expr*>(in));
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
			case Reflection::ID:
				return fold_reflection(dynamic_cast<Reflection*>(in));
		}
		assert(0);
	}

	virtual _Class_name fold_class_name(Class_name* in)
	{
		switch(in->classid())
		{
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
			case Reflection::ID:
				return fold_reflection(dynamic_cast<Reflection*>(in));
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
			case CAST::ID:
				return fold_cast(dynamic_cast<CAST*>(in));
			case OP::ID:
				return fold_op(dynamic_cast<OP*>(in));
			case CONSTANT_NAME::ID:
				return fold_constant_name(dynamic_cast<CONSTANT_NAME*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T>
class Uniform_fold : public Fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T> {};
}

