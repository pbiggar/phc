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


#include "AST.h"
namespace AST{
template
<class _Actual_parameter,
 class _Array,
 class _Array_elem,
 class _Assignment,
 class _Attr_mod,
 class _Attribute,
 class _BOOL,
 class _Bin_op,
 class _Break,
 class _CAST,
 class _CLASS_NAME,
 class _CONSTANT_NAME,
 class _Cast,
 class _Catch,
 class _Class_def,
 class _Class_mod,
 class _Class_name,
 class _Commented_node,
 class _Conditional_expr,
 class _Constant,
 class _Continue,
 class _DIRECTIVE_NAME,
 class _Declare,
 class _Directive,
 class _Do,
 class _Eval_expr,
 class _Expr,
 class _FOREIGN,
 class _For,
 class _Foreach,
 class _Formal_parameter,
 class _Global,
 class _INT,
 class _INTERFACE_NAME,
 class _Identifier,
 class _If,
 class _Ignore_errors,
 class _Instanceof,
 class _Interface_def,
 class _List_assignment,
 class _List_element,
 class _Literal,
 class _METHOD_NAME,
 class _Member,
 class _Method,
 class _Method_invocation,
 class _Method_mod,
 class _Method_name,
 class _NIL,
 class _Name_with_default,
 class _Nested_list_elements,
 class _New,
 class _Node,
 class _Nop,
 class _OP,
 class _Op_assignment,
 class _PHP_script,
 class _Post_op,
 class _Pre_op,
 class _REAL,
 class _Reflection,
 class _Return,
 class _STRING,
 class _Signature,
 class _Source_rep,
 class _Statement,
 class _Static_declaration,
 class _Switch,
 class _Switch_case,
 class _Target,
 class _Throw,
 class _Try,
 class _Type,
 class _Unary_op,
 class _VARIABLE_NAME,
 class _Variable,
 class _Variable_name,
 class _While,
 template <typename _Tp, typename _Alloc = typename List<_Tp>::allocator_type> class _List = List
>
class Fold
{
// Access this class from subclasses without copying out the template instantiation
public:
   typedef Fold<_Actual_parameter, _Array, _Array_elem, _Assignment, _Attr_mod, _Attribute, _BOOL, _Bin_op, _Break, _CAST, _CLASS_NAME, _CONSTANT_NAME, _Cast, _Catch, _Class_def, _Class_mod, _Class_name, _Commented_node, _Conditional_expr, _Constant, _Continue, _DIRECTIVE_NAME, _Declare, _Directive, _Do, _Eval_expr, _Expr, _FOREIGN, _For, _Foreach, _Formal_parameter, _Global, _INT, _INTERFACE_NAME, _Identifier, _If, _Ignore_errors, _Instanceof, _Interface_def, _List_assignment, _List_element, _Literal, _METHOD_NAME, _Member, _Method, _Method_invocation, _Method_mod, _Method_name, _NIL, _Name_with_default, _Nested_list_elements, _New, _Node, _Nop, _OP, _Op_assignment, _PHP_script, _Post_op, _Pre_op, _REAL, _Reflection, _Return, _STRING, _Signature, _Source_rep, _Statement, _Static_declaration, _Switch, _Switch_case, _Target, _Throw, _Try, _Type, _Unary_op, _VARIABLE_NAME, _Variable, _Variable_name, _While, _List> parent;
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
		bool is_ref = in->is_ref;
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
		_List<_Name_with_default>* vars = 0;
	
		{
			vars = new _List<_Name_with_default>;
			typename _List<Name_with_default*>::const_iterator i;
			for(i = in->vars->begin(); i != in->vars->end(); i++)
				if(*i != NULL) vars->push_back(fold_name_with_default(*i));
				else vars->push_back(0);
		}
		return fold_impl_attribute(in, attr_mod, vars);
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
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_List<_Statement>* iftrue = 0;
	
		{
			iftrue = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->iftrue->begin(); i != in->iftrue->end(); i++)
				if(*i != NULL) iftrue->push_back(fold_statement(*i));
				else iftrue->push_back(0);
		}
		_List<_Statement>* iffalse = 0;
	
		{
			iffalse = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->iffalse->begin(); i != in->iffalse->end(); i++)
				if(*i != NULL) iffalse->push_back(fold_statement(*i));
				else iffalse->push_back(0);
		}
		return fold_impl_if(in, expr, iftrue, iffalse);
	}

	virtual _While fold_while(While* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_while(in, expr, statements);
	}

	virtual _Do fold_do(Do* in)
	{
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_do(in, statements, expr);
	}

	virtual _For fold_for(For* in)
	{
		_Expr init = 0;
		if(in->init != NULL) init = fold_expr(in->init);
		_Expr cond = 0;
		if(in->cond != NULL) cond = fold_expr(in->cond);
		_Expr incr = 0;
		if(in->incr != NULL) incr = fold_expr(in->incr);
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_for(in, init, cond, incr, statements);
	}

	virtual _Foreach fold_foreach(Foreach* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_Variable key = 0;
		if(in->key != NULL) key = fold_variable(in->key);
		bool is_ref = in->is_ref;
		_Variable val = 0;
		if(in->val != NULL) val = fold_variable(in->val);
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_foreach(in, expr, key, is_ref, val, statements);
	}

	virtual _Switch fold_switch(Switch* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_List<_Switch_case>* switch_cases = 0;
	
		{
			switch_cases = new _List<_Switch_case>;
			typename _List<Switch_case*>::const_iterator i;
			for(i = in->switch_cases->begin(); i != in->switch_cases->end(); i++)
				if(*i != NULL) switch_cases->push_back(fold_switch_case(*i));
				else switch_cases->push_back(0);
		}
		return fold_impl_switch(in, expr, switch_cases);
	}

	virtual _Switch_case fold_switch_case(Switch_case* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_switch_case(in, expr, statements);
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
		_List<_Name_with_default>* vars = 0;
	
		{
			vars = new _List<_Name_with_default>;
			typename _List<Name_with_default*>::const_iterator i;
			for(i = in->vars->begin(); i != in->vars->end(); i++)
				if(*i != NULL) vars->push_back(fold_name_with_default(*i));
				else vars->push_back(0);
		}
		return fold_impl_static_declaration(in, vars);
	}

	virtual _Global fold_global(Global* in)
	{
		_List<_Variable_name>* variable_names = 0;
	
		{
			variable_names = new _List<_Variable_name>;
			typename _List<Variable_name*>::const_iterator i;
			for(i = in->variable_names->begin(); i != in->variable_names->end(); i++)
				if(*i != NULL) variable_names->push_back(fold_variable_name(*i));
				else variable_names->push_back(0);
		}
		return fold_impl_global(in, variable_names);
	}

	virtual _Declare fold_declare(Declare* in)
	{
		_List<_Directive>* directives = 0;
	
		{
			directives = new _List<_Directive>;
			typename _List<Directive*>::const_iterator i;
			for(i = in->directives->begin(); i != in->directives->end(); i++)
				if(*i != NULL) directives->push_back(fold_directive(*i));
				else directives->push_back(0);
		}
		_List<_Statement>* statements = 0;
	
		{
			statements = new _List<_Statement>;
			typename _List<Statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_declare(in, directives, statements);
	}

	virtual _Directive fold_directive(Directive* in)
	{
		_DIRECTIVE_NAME directive_name = 0;
		if(in->directive_name != NULL) directive_name = fold_directive_name(in->directive_name);
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_directive(in, directive_name, expr);
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

	virtual _Nop fold_nop(Nop* in)
	{
		return fold_impl_nop(in);
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

	virtual _List_assignment fold_list_assignment(List_assignment* in)
	{
		_List<_List_element>* list_elements = 0;
	
		{
			list_elements = new _List<_List_element>;
			typename _List<List_element*>::const_iterator i;
			for(i = in->list_elements->begin(); i != in->list_elements->end(); i++)
				if(*i != NULL) list_elements->push_back(fold_list_element(*i));
				else list_elements->push_back(0);
		}
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_list_assignment(in, list_elements, expr);
	}

	virtual _Nested_list_elements fold_nested_list_elements(Nested_list_elements* in)
	{
		_List<_List_element>* list_elements = 0;
	
		{
			list_elements = new _List<_List_element>;
			typename _List<List_element*>::const_iterator i;
			for(i = in->list_elements->begin(); i != in->list_elements->end(); i++)
				if(*i != NULL) list_elements->push_back(fold_list_element(*i));
				else list_elements->push_back(0);
		}
		return fold_impl_nested_list_elements(in, list_elements);
	}

	virtual _Cast fold_cast(Cast* in)
	{
		_CAST cast = 0;
		if(in->cast != NULL) cast = fold_cast(in->cast);
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_cast(in, cast, expr);
	}

	virtual _Unary_op fold_unary_op(Unary_op* in)
	{
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_unary_op(in, op, expr);
	}

	virtual _Bin_op fold_bin_op(Bin_op* in)
	{
		_Expr left = 0;
		if(in->left != NULL) left = fold_expr(in->left);
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Expr right = 0;
		if(in->right != NULL) right = fold_expr(in->right);
		return fold_impl_bin_op(in, left, op, right);
	}

	virtual _Conditional_expr fold_conditional_expr(Conditional_expr* in)
	{
		_Expr cond = 0;
		if(in->cond != NULL) cond = fold_expr(in->cond);
		_Expr iftrue = 0;
		if(in->iftrue != NULL) iftrue = fold_expr(in->iftrue);
		_Expr iffalse = 0;
		if(in->iffalse != NULL) iffalse = fold_expr(in->iffalse);
		return fold_impl_conditional_expr(in, cond, iftrue, iffalse);
	}

	virtual _Ignore_errors fold_ignore_errors(Ignore_errors* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_ignore_errors(in, expr);
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
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_Class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_instanceof(in, expr, class_name);
	}

	virtual _Variable fold_variable(Variable* in)
	{
		_Target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_Variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_List<_Expr>* array_indices = 0;
	
		{
			array_indices = new _List<_Expr>;
			typename _List<Expr*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_expr(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_variable(in, target, variable_name, array_indices);
	}

	virtual _Reflection fold_reflection(Reflection* in)
	{
		_Expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_reflection(in, expr);
	}

	virtual _Pre_op fold_pre_op(Pre_op* in)
	{
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		return fold_impl_pre_op(in, op, variable);
	}

	virtual _Post_op fold_post_op(Post_op* in)
	{
		_Variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		_OP op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		return fold_impl_post_op(in, variable, op);
	}

	virtual _Array fold_array(Array* in)
	{
		_List<_Array_elem>* array_elems = 0;
	
		{
			array_elems = new _List<_Array_elem>;
			typename _List<Array_elem*>::const_iterator i;
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



// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _PHP_script fold_impl_php_script(PHP_script* orig, _List<_Statement>* statements) { assert(0); };
	virtual _Class_def fold_impl_class_def(Class_def* orig, _Class_mod class_mod, _CLASS_NAME class_name, _CLASS_NAME extends, _List<_INTERFACE_NAME>* implements, _List<_Member>* members) { assert(0); };
	virtual _Class_mod fold_impl_class_mod(Class_mod* orig, bool is_abstract, bool is_final) { assert(0); };
	virtual _Interface_def fold_impl_interface_def(Interface_def* orig, _INTERFACE_NAME interface_name, _List<_INTERFACE_NAME>* extends, _List<_Member>* members) { assert(0); };
	virtual _Method fold_impl_method(Method* orig, _Signature signature, _List<_Statement>* statements) { assert(0); };
	virtual _Signature fold_impl_signature(Signature* orig, _Method_mod method_mod, bool is_ref, _METHOD_NAME method_name, _List<_Formal_parameter>* formal_parameters) { assert(0); };
	virtual _Method_mod fold_impl_method_mod(Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) { assert(0); };
	virtual _Formal_parameter fold_impl_formal_parameter(Formal_parameter* orig, _Type type, bool is_ref, _Name_with_default var) { assert(0); };
	virtual _Type fold_impl_type(Type* orig, _CLASS_NAME class_name) { assert(0); };
	virtual _Attribute fold_impl_attribute(Attribute* orig, _Attr_mod attr_mod, _List<_Name_with_default>* vars) { assert(0); };
	virtual _Attr_mod fold_impl_attr_mod(Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) { assert(0); };
	virtual _Name_with_default fold_impl_name_with_default(Name_with_default* orig, _VARIABLE_NAME variable_name, _Expr expr) { assert(0); };
	virtual _If fold_impl_if(If* orig, _Expr expr, _List<_Statement>* iftrue, _List<_Statement>* iffalse) { assert(0); };
	virtual _While fold_impl_while(While* orig, _Expr expr, _List<_Statement>* statements) { assert(0); };
	virtual _Do fold_impl_do(Do* orig, _List<_Statement>* statements, _Expr expr) { assert(0); };
	virtual _For fold_impl_for(For* orig, _Expr init, _Expr cond, _Expr incr, _List<_Statement>* statements) { assert(0); };
	virtual _Foreach fold_impl_foreach(Foreach* orig, _Expr expr, _Variable key, bool is_ref, _Variable val, _List<_Statement>* statements) { assert(0); };
	virtual _Switch fold_impl_switch(Switch* orig, _Expr expr, _List<_Switch_case>* switch_cases) { assert(0); };
	virtual _Switch_case fold_impl_switch_case(Switch_case* orig, _Expr expr, _List<_Statement>* statements) { assert(0); };
	virtual _Break fold_impl_break(Break* orig, _Expr expr) { assert(0); };
	virtual _Continue fold_impl_continue(Continue* orig, _Expr expr) { assert(0); };
	virtual _Return fold_impl_return(Return* orig, _Expr expr) { assert(0); };
	virtual _Static_declaration fold_impl_static_declaration(Static_declaration* orig, _List<_Name_with_default>* vars) { assert(0); };
	virtual _Global fold_impl_global(Global* orig, _List<_Variable_name>* variable_names) { assert(0); };
	virtual _Declare fold_impl_declare(Declare* orig, _List<_Directive>* directives, _List<_Statement>* statements) { assert(0); };
	virtual _Directive fold_impl_directive(Directive* orig, _DIRECTIVE_NAME directive_name, _Expr expr) { assert(0); };
	virtual _Try fold_impl_try(Try* orig, _List<_Statement>* statements, _List<_Catch>* catches) { assert(0); };
	virtual _Catch fold_impl_catch(Catch* orig, _CLASS_NAME class_name, _VARIABLE_NAME variable_name, _List<_Statement>* statements) { assert(0); };
	virtual _Throw fold_impl_throw(Throw* orig, _Expr expr) { assert(0); };
	virtual _Eval_expr fold_impl_eval_expr(Eval_expr* orig, _Expr expr) { assert(0); };
	virtual _Nop fold_impl_nop(Nop* orig) { assert(0); };
	virtual _Assignment fold_impl_assignment(Assignment* orig, _Variable variable, bool is_ref, _Expr expr) { assert(0); };
	virtual _Op_assignment fold_impl_op_assignment(Op_assignment* orig, _Variable variable, _OP op, _Expr expr) { assert(0); };
	virtual _List_assignment fold_impl_list_assignment(List_assignment* orig, _List<_List_element>* list_elements, _Expr expr) { assert(0); };
	virtual _Nested_list_elements fold_impl_nested_list_elements(Nested_list_elements* orig, _List<_List_element>* list_elements) { assert(0); };
	virtual _Cast fold_impl_cast(Cast* orig, _CAST cast, _Expr expr) { assert(0); };
	virtual _Unary_op fold_impl_unary_op(Unary_op* orig, _OP op, _Expr expr) { assert(0); };
	virtual _Bin_op fold_impl_bin_op(Bin_op* orig, _Expr left, _OP op, _Expr right) { assert(0); };
	virtual _Conditional_expr fold_impl_conditional_expr(Conditional_expr* orig, _Expr cond, _Expr iftrue, _Expr iffalse) { assert(0); };
	virtual _Ignore_errors fold_impl_ignore_errors(Ignore_errors* orig, _Expr expr) { assert(0); };
	virtual _Constant fold_impl_constant(Constant* orig, _CLASS_NAME class_name, _CONSTANT_NAME constant_name) { assert(0); };
	virtual _Instanceof fold_impl_instanceof(Instanceof* orig, _Expr expr, _Class_name class_name) { assert(0); };
	virtual _Variable fold_impl_variable(Variable* orig, _Target target, _Variable_name variable_name, _List<_Expr>* array_indices) { assert(0); };
	virtual _Reflection fold_impl_reflection(Reflection* orig, _Expr expr) { assert(0); };
	virtual _Pre_op fold_impl_pre_op(Pre_op* orig, _OP op, _Variable variable) { assert(0); };
	virtual _Post_op fold_impl_post_op(Post_op* orig, _Variable variable, _OP op) { assert(0); };
	virtual _Array fold_impl_array(Array* orig, _List<_Array_elem>* array_elems) { assert(0); };
	virtual _Array_elem fold_impl_array_elem(Array_elem* orig, _Expr key, bool is_ref, _Expr val) { assert(0); };
	virtual _Method_invocation fold_impl_method_invocation(Method_invocation* orig, _Target target, _Method_name method_name, _List<_Actual_parameter>* actual_parameters) { assert(0); };
	virtual _Actual_parameter fold_impl_actual_parameter(Actual_parameter* orig, bool is_ref, _Expr expr) { assert(0); };
	virtual _New fold_impl_new(New* orig, _Class_name class_name, _List<_Actual_parameter>* actual_parameters) { assert(0); };

	virtual _FOREIGN fold_foreign(FOREIGN* orig) { assert(0); };
	virtual _CLASS_NAME fold_class_name(CLASS_NAME* orig) { assert(0); };
	virtual _INTERFACE_NAME fold_interface_name(INTERFACE_NAME* orig) { assert(0); };
	virtual _METHOD_NAME fold_method_name(METHOD_NAME* orig) { assert(0); };
	virtual _VARIABLE_NAME fold_variable_name(VARIABLE_NAME* orig) { assert(0); };
	virtual _DIRECTIVE_NAME fold_directive_name(DIRECTIVE_NAME* orig) { assert(0); };
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
			case Class_mod::ID:
				return fold_class_mod(dynamic_cast<Class_mod*>(in));
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
			case Directive::ID:
				return fold_directive(dynamic_cast<Directive*>(in));
			case Variable::ID:
				return fold_variable(dynamic_cast<Variable*>(in));
			case Nested_list_elements::ID:
				return fold_nested_list_elements(dynamic_cast<Nested_list_elements*>(in));
			case VARIABLE_NAME::ID:
				return fold_variable_name(dynamic_cast<VARIABLE_NAME*>(in));
			case Reflection::ID:
				return fold_reflection(dynamic_cast<Reflection*>(in));
			case Assignment::ID:
				return fold_assignment(dynamic_cast<Assignment*>(in));
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
			case List_assignment::ID:
				return fold_list_assignment(dynamic_cast<List_assignment*>(in));
			case Post_op::ID:
				return fold_post_op(dynamic_cast<Post_op*>(in));
			case Array::ID:
				return fold_array(dynamic_cast<Array*>(in));
			case Conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<Conditional_expr*>(in));
			case Ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<Ignore_errors*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
			case CLASS_NAME::ID:
				return fold_class_name(dynamic_cast<CLASS_NAME*>(in));
			case Array_elem::ID:
				return fold_array_elem(dynamic_cast<Array_elem*>(in));
			case METHOD_NAME::ID:
				return fold_method_name(dynamic_cast<METHOD_NAME*>(in));
			case Actual_parameter::ID:
				return fold_actual_parameter(dynamic_cast<Actual_parameter*>(in));
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Attribute::ID:
				return fold_attribute(dynamic_cast<Attribute*>(in));
			case Class_def::ID:
				return fold_class_def(dynamic_cast<Class_def*>(in));
			case Interface_def::ID:
				return fold_interface_def(dynamic_cast<Interface_def*>(in));
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
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case While::ID:
				return fold_while(dynamic_cast<While*>(in));
			case Do::ID:
				return fold_do(dynamic_cast<Do*>(in));
			case For::ID:
				return fold_for(dynamic_cast<For*>(in));
			case Foreach::ID:
				return fold_foreach(dynamic_cast<Foreach*>(in));
			case Switch::ID:
				return fold_switch(dynamic_cast<Switch*>(in));
			case Break::ID:
				return fold_break(dynamic_cast<Break*>(in));
			case Continue::ID:
				return fold_continue(dynamic_cast<Continue*>(in));
			case Declare::ID:
				return fold_declare(dynamic_cast<Declare*>(in));
			case Nop::ID:
				return fold_nop(dynamic_cast<Nop*>(in));
			case Switch_case::ID:
				return fold_switch_case(dynamic_cast<Switch_case*>(in));
			case Catch::ID:
				return fold_catch(dynamic_cast<Catch*>(in));
			case INTERFACE_NAME::ID:
				return fold_interface_name(dynamic_cast<INTERFACE_NAME*>(in));
			case CAST::ID:
				return fold_cast(dynamic_cast<CAST*>(in));
			case OP::ID:
				return fold_op(dynamic_cast<OP*>(in));
			case CONSTANT_NAME::ID:
				return fold_constant_name(dynamic_cast<CONSTANT_NAME*>(in));
			case DIRECTIVE_NAME::ID:
				return fold_directive_name(dynamic_cast<DIRECTIVE_NAME*>(in));
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
			case Try::ID:
				return fold_try(dynamic_cast<Try*>(in));
			case Throw::ID:
				return fold_throw(dynamic_cast<Throw*>(in));
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case While::ID:
				return fold_while(dynamic_cast<While*>(in));
			case Do::ID:
				return fold_do(dynamic_cast<Do*>(in));
			case For::ID:
				return fold_for(dynamic_cast<For*>(in));
			case Foreach::ID:
				return fold_foreach(dynamic_cast<Foreach*>(in));
			case Switch::ID:
				return fold_switch(dynamic_cast<Switch*>(in));
			case Break::ID:
				return fold_break(dynamic_cast<Break*>(in));
			case Continue::ID:
				return fold_continue(dynamic_cast<Continue*>(in));
			case Declare::ID:
				return fold_declare(dynamic_cast<Declare*>(in));
			case Nop::ID:
				return fold_nop(dynamic_cast<Nop*>(in));
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
			case Assignment::ID:
				return fold_assignment(dynamic_cast<Assignment*>(in));
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
			case List_assignment::ID:
				return fold_list_assignment(dynamic_cast<List_assignment*>(in));
			case Post_op::ID:
				return fold_post_op(dynamic_cast<Post_op*>(in));
			case Array::ID:
				return fold_array(dynamic_cast<Array*>(in));
			case Conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<Conditional_expr*>(in));
			case Ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<Ignore_errors*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
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

	virtual _List_element fold_list_element(List_element* in)
	{
		switch(in->classid())
		{
			case Variable::ID:
				return fold_variable(dynamic_cast<Variable*>(in));
			case Nested_list_elements::ID:
				return fold_nested_list_elements(dynamic_cast<Nested_list_elements*>(in));
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
			case Assignment::ID:
				return fold_assignment(dynamic_cast<Assignment*>(in));
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
			case List_assignment::ID:
				return fold_list_assignment(dynamic_cast<List_assignment*>(in));
			case Post_op::ID:
				return fold_post_op(dynamic_cast<Post_op*>(in));
			case Array::ID:
				return fold_array(dynamic_cast<Array*>(in));
			case Conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<Conditional_expr*>(in));
			case Ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<Ignore_errors*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
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

	virtual _Commented_node fold_commented_node(Commented_node* in)
	{
		switch(in->classid())
		{
			case Method::ID:
				return fold_method(dynamic_cast<Method*>(in));
			case Attribute::ID:
				return fold_attribute(dynamic_cast<Attribute*>(in));
			case Class_def::ID:
				return fold_class_def(dynamic_cast<Class_def*>(in));
			case Interface_def::ID:
				return fold_interface_def(dynamic_cast<Interface_def*>(in));
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
			case Eval_expr::ID:
				return fold_eval_expr(dynamic_cast<Eval_expr*>(in));
			case If::ID:
				return fold_if(dynamic_cast<If*>(in));
			case While::ID:
				return fold_while(dynamic_cast<While*>(in));
			case Do::ID:
				return fold_do(dynamic_cast<Do*>(in));
			case For::ID:
				return fold_for(dynamic_cast<For*>(in));
			case Foreach::ID:
				return fold_foreach(dynamic_cast<Foreach*>(in));
			case Switch::ID:
				return fold_switch(dynamic_cast<Switch*>(in));
			case Break::ID:
				return fold_break(dynamic_cast<Break*>(in));
			case Continue::ID:
				return fold_continue(dynamic_cast<Continue*>(in));
			case Declare::ID:
				return fold_declare(dynamic_cast<Declare*>(in));
			case Nop::ID:
				return fold_nop(dynamic_cast<Nop*>(in));
			case FOREIGN::ID:
				return fold_foreign(dynamic_cast<FOREIGN*>(in));
			case Switch_case::ID:
				return fold_switch_case(dynamic_cast<Switch_case*>(in));
			case Catch::ID:
				return fold_catch(dynamic_cast<Catch*>(in));
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
			case DIRECTIVE_NAME::ID:
				return fold_directive_name(dynamic_cast<DIRECTIVE_NAME*>(in));
		}
		assert(0);
	}

	virtual _Source_rep fold_source_rep(Source_rep* in)
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
			case DIRECTIVE_NAME::ID:
				return fold_directive_name(dynamic_cast<DIRECTIVE_NAME*>(in));
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



// Virtual destructor to avoid compiler warnings
	virtual ~Fold() {}
};

template<class T, template <class _Tp, class _Alloc = typename List<_Tp>::allocator_type> class _List>
class Uniform_fold : public Fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, _List> {};
}

