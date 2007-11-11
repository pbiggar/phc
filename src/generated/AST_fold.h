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
#include <list>
#include <string>
#include <assert.h>
using namespace std;


#include "AST.h"
namespace AST{
template
<class _AST_node,
 class _AST_php_script,
 class _AST_statement,
 class _AST_class_def,
 class _AST_class_mod,
 class _AST_interface_def,
 class _AST_member,
 class _AST_method,
 class _AST_signature,
 class _AST_method_mod,
 class _AST_formal_parameter,
 class _AST_type,
 class _AST_attribute,
 class _AST_attr_mod,
 class _AST_name_with_default,
 class _AST_if,
 class _AST_while,
 class _AST_do,
 class _AST_for,
 class _AST_foreach,
 class _AST_switch,
 class _AST_switch_case,
 class _AST_break,
 class _AST_continue,
 class _AST_return,
 class _AST_static_declaration,
 class _AST_global,
 class _AST_declare,
 class _AST_directive,
 class _AST_try,
 class _AST_catch,
 class _AST_throw,
 class _AST_eval_expr,
 class _AST_nop,
 class _AST_branch,
 class _AST_goto,
 class _AST_label,
 class _AST_expr,
 class _AST_literal,
 class _AST_assignment,
 class _AST_op_assignment,
 class _AST_list_assignment,
 class _AST_list_element,
 class _AST_nested_list_elements,
 class _AST_cast,
 class _AST_unary_op,
 class _AST_bin_op,
 class _AST_conditional_expr,
 class _AST_ignore_errors,
 class _AST_constant,
 class _AST_instanceof,
 class _AST_variable,
 class _AST_variable_name,
 class _AST_reflection,
 class _AST_target,
 class _AST_pre_op,
 class _AST_post_op,
 class _AST_array,
 class _AST_array_elem,
 class _AST_method_invocation,
 class _AST_method_name,
 class _AST_actual_parameter,
 class _AST_new,
 class _AST_class_name,
 class _AST_commented_node,
 class _AST_identifier,
 class _Token_class_name,
 class _Token_interface_name,
 class _Token_method_name,
 class _Token_variable_name,
 class _Token_directive_name,
 class _Token_label_name,
 class _Token_int,
 class _Token_real,
 class _Token_string,
 class _Token_bool,
 class _Token_null,
 class _Token_op,
 class _Token_cast,
 class _Token_constant_name>
class AST_fold
{
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _AST_php_script fold_php_script(AST_php_script* in)
	{
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_php_script(in, statements);
	}

	virtual _AST_class_def fold_class_def(AST_class_def* in)
	{
		_AST_class_mod class_mod = 0;
		if(in->class_mod != NULL) class_mod = fold_class_mod(in->class_mod);
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_Token_class_name extends = 0;
		if(in->extends != NULL) extends = fold_class_name(in->extends);
		List<_Token_interface_name>* implements = new List<_Token_interface_name>;
		{
			List<Token_interface_name*>::const_iterator i;
			for(i = in->implements->begin(); i != in->implements->end(); i++)
				if(*i != NULL) implements->push_back(fold_interface_name(*i));
				else implements->push_back(0);
		}
		List<_AST_member>* members = new List<_AST_member>;
		{
			List<AST_member*>::const_iterator i;
			for(i = in->members->begin(); i != in->members->end(); i++)
				if(*i != NULL) members->push_back(fold_member(*i));
				else members->push_back(0);
		}
		return fold_impl_class_def(in, class_mod, class_name, extends, implements, members);
	}

	virtual _AST_class_mod fold_class_mod(AST_class_mod* in)
	{
		bool is_abstract = in->is_abstract;
		bool is_final = in->is_final;
		return fold_impl_class_mod(in, is_abstract, is_final);
	}

	virtual _AST_interface_def fold_interface_def(AST_interface_def* in)
	{
		_Token_interface_name interface_name = 0;
		if(in->interface_name != NULL) interface_name = fold_interface_name(in->interface_name);
		List<_Token_interface_name>* extends = new List<_Token_interface_name>;
		{
			List<Token_interface_name*>::const_iterator i;
			for(i = in->extends->begin(); i != in->extends->end(); i++)
				if(*i != NULL) extends->push_back(fold_interface_name(*i));
				else extends->push_back(0);
		}
		List<_AST_member>* members = new List<_AST_member>;
		{
			List<AST_member*>::const_iterator i;
			for(i = in->members->begin(); i != in->members->end(); i++)
				if(*i != NULL) members->push_back(fold_member(*i));
				else members->push_back(0);
		}
		return fold_impl_interface_def(in, interface_name, extends, members);
	}

	virtual _AST_method fold_method(AST_method* in)
	{
		_AST_signature signature = 0;
		if(in->signature != NULL) signature = fold_signature(in->signature);
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_method(in, signature, statements);
	}

	virtual _AST_signature fold_signature(AST_signature* in)
	{
		_AST_method_mod method_mod = 0;
		if(in->method_mod != NULL) method_mod = fold_method_mod(in->method_mod);
		bool is_ref = in->is_ref;
		_Token_method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		List<_AST_formal_parameter>* formal_parameters = new List<_AST_formal_parameter>;
		{
			List<AST_formal_parameter*>::const_iterator i;
			for(i = in->formal_parameters->begin(); i != in->formal_parameters->end(); i++)
				if(*i != NULL) formal_parameters->push_back(fold_formal_parameter(*i));
				else formal_parameters->push_back(0);
		}
		return fold_impl_signature(in, method_mod, is_ref, method_name, formal_parameters);
	}

	virtual _AST_method_mod fold_method_mod(AST_method_mod* in)
	{
		bool is_public = in->is_public;
		bool is_protected = in->is_protected;
		bool is_private = in->is_private;
		bool is_static = in->is_static;
		bool is_abstract = in->is_abstract;
		bool is_final = in->is_final;
		return fold_impl_method_mod(in, is_public, is_protected, is_private, is_static, is_abstract, is_final);
	}

	virtual _AST_formal_parameter fold_formal_parameter(AST_formal_parameter* in)
	{
		_AST_type type = 0;
		if(in->type != NULL) type = fold_type(in->type);
		bool is_ref = in->is_ref;
		_AST_name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_formal_parameter(in, type, is_ref, var);
	}

	virtual _AST_type fold_type(AST_type* in)
	{
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_type(in, class_name);
	}

	virtual _AST_attribute fold_attribute(AST_attribute* in)
	{
		_AST_attr_mod attr_mod = 0;
		if(in->attr_mod != NULL) attr_mod = fold_attr_mod(in->attr_mod);
		List<_AST_name_with_default>* vars = new List<_AST_name_with_default>;
		{
			List<AST_name_with_default*>::const_iterator i;
			for(i = in->vars->begin(); i != in->vars->end(); i++)
				if(*i != NULL) vars->push_back(fold_name_with_default(*i));
				else vars->push_back(0);
		}
		return fold_impl_attribute(in, attr_mod, vars);
	}

	virtual _AST_attr_mod fold_attr_mod(AST_attr_mod* in)
	{
		bool is_public = in->is_public;
		bool is_protected = in->is_protected;
		bool is_private = in->is_private;
		bool is_static = in->is_static;
		bool is_const = in->is_const;
		return fold_impl_attr_mod(in, is_public, is_protected, is_private, is_static, is_const);
	}

	virtual _AST_name_with_default fold_name_with_default(AST_name_with_default* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_name_with_default(in, variable_name, expr);
	}

	virtual _AST_if fold_if(AST_if* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_AST_statement>* iftrue = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->iftrue->begin(); i != in->iftrue->end(); i++)
				if(*i != NULL) iftrue->push_back(fold_statement(*i));
				else iftrue->push_back(0);
		}
		List<_AST_statement>* iffalse = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->iffalse->begin(); i != in->iffalse->end(); i++)
				if(*i != NULL) iffalse->push_back(fold_statement(*i));
				else iffalse->push_back(0);
		}
		return fold_impl_if(in, expr, iftrue, iffalse);
	}

	virtual _AST_while fold_while(AST_while* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_while(in, expr, statements);
	}

	virtual _AST_do fold_do(AST_do* in)
	{
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_do(in, statements, expr);
	}

	virtual _AST_for fold_for(AST_for* in)
	{
		_AST_expr init = 0;
		if(in->init != NULL) init = fold_expr(in->init);
		_AST_expr cond = 0;
		if(in->cond != NULL) cond = fold_expr(in->cond);
		_AST_expr incr = 0;
		if(in->incr != NULL) incr = fold_expr(in->incr);
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_for(in, init, cond, incr, statements);
	}

	virtual _AST_foreach fold_foreach(AST_foreach* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_AST_variable key = 0;
		if(in->key != NULL) key = fold_variable(in->key);
		bool is_ref = in->is_ref;
		_AST_variable val = 0;
		if(in->val != NULL) val = fold_variable(in->val);
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_foreach(in, expr, key, is_ref, val, statements);
	}

	virtual _AST_switch fold_switch(AST_switch* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_AST_switch_case>* switch_cases = new List<_AST_switch_case>;
		{
			List<AST_switch_case*>::const_iterator i;
			for(i = in->switch_cases->begin(); i != in->switch_cases->end(); i++)
				if(*i != NULL) switch_cases->push_back(fold_switch_case(*i));
				else switch_cases->push_back(0);
		}
		return fold_impl_switch(in, expr, switch_cases);
	}

	virtual _AST_switch_case fold_switch_case(AST_switch_case* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_switch_case(in, expr, statements);
	}

	virtual _AST_break fold_break(AST_break* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_break(in, expr);
	}

	virtual _AST_continue fold_continue(AST_continue* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_continue(in, expr);
	}

	virtual _AST_return fold_return(AST_return* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_return(in, expr);
	}

	virtual _AST_static_declaration fold_static_declaration(AST_static_declaration* in)
	{
		List<_AST_name_with_default>* vars = new List<_AST_name_with_default>;
		{
			List<AST_name_with_default*>::const_iterator i;
			for(i = in->vars->begin(); i != in->vars->end(); i++)
				if(*i != NULL) vars->push_back(fold_name_with_default(*i));
				else vars->push_back(0);
		}
		return fold_impl_static_declaration(in, vars);
	}

	virtual _AST_global fold_global(AST_global* in)
	{
		List<_AST_variable_name>* variable_names = new List<_AST_variable_name>;
		{
			List<AST_variable_name*>::const_iterator i;
			for(i = in->variable_names->begin(); i != in->variable_names->end(); i++)
				if(*i != NULL) variable_names->push_back(fold_variable_name(*i));
				else variable_names->push_back(0);
		}
		return fold_impl_global(in, variable_names);
	}

	virtual _AST_declare fold_declare(AST_declare* in)
	{
		List<_AST_directive>* directives = new List<_AST_directive>;
		{
			List<AST_directive*>::const_iterator i;
			for(i = in->directives->begin(); i != in->directives->end(); i++)
				if(*i != NULL) directives->push_back(fold_directive(*i));
				else directives->push_back(0);
		}
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_declare(in, directives, statements);
	}

	virtual _AST_directive fold_directive(AST_directive* in)
	{
		_Token_directive_name directive_name = 0;
		if(in->directive_name != NULL) directive_name = fold_directive_name(in->directive_name);
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_directive(in, directive_name, expr);
	}

	virtual _AST_try fold_try(AST_try* in)
	{
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		List<_AST_catch>* catches = new List<_AST_catch>;
		{
			List<AST_catch*>::const_iterator i;
			for(i = in->catches->begin(); i != in->catches->end(); i++)
				if(*i != NULL) catches->push_back(fold_catch(*i));
				else catches->push_back(0);
		}
		return fold_impl_try(in, statements, catches);
	}

	virtual _AST_catch fold_catch(AST_catch* in)
	{
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_AST_statement>* statements = new List<_AST_statement>;
		{
			List<AST_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_catch(in, class_name, variable_name, statements);
	}

	virtual _AST_throw fold_throw(AST_throw* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_throw(in, expr);
	}

	virtual _AST_eval_expr fold_eval_expr(AST_eval_expr* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_eval_expr(in, expr);
	}

	virtual _AST_nop fold_nop(AST_nop* in)
	{
		return fold_impl_nop(in);
	}

	virtual _AST_branch fold_branch(AST_branch* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_Token_label_name iftrue = 0;
		if(in->iftrue != NULL) iftrue = fold_label_name(in->iftrue);
		_Token_label_name iffalse = 0;
		if(in->iffalse != NULL) iffalse = fold_label_name(in->iffalse);
		return fold_impl_branch(in, expr, iftrue, iffalse);
	}

	virtual _AST_goto fold_goto(AST_goto* in)
	{
		_Token_label_name label_name = 0;
		if(in->label_name != NULL) label_name = fold_label_name(in->label_name);
		return fold_impl_goto(in, label_name);
	}

	virtual _AST_label fold_label(AST_label* in)
	{
		_Token_label_name label_name = 0;
		if(in->label_name != NULL) label_name = fold_label_name(in->label_name);
		return fold_impl_label(in, label_name);
	}

	virtual _AST_assignment fold_assignment(AST_assignment* in)
	{
		_AST_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		bool is_ref = in->is_ref;
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_assignment(in, variable, is_ref, expr);
	}

	virtual _AST_op_assignment fold_op_assignment(AST_op_assignment* in)
	{
		_AST_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_op_assignment(in, variable, op, expr);
	}

	virtual _AST_list_assignment fold_list_assignment(AST_list_assignment* in)
	{
		List<_AST_list_element>* list_elements = new List<_AST_list_element>;
		{
			List<AST_list_element*>::const_iterator i;
			for(i = in->list_elements->begin(); i != in->list_elements->end(); i++)
				if(*i != NULL) list_elements->push_back(fold_list_element(*i));
				else list_elements->push_back(0);
		}
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_list_assignment(in, list_elements, expr);
	}

	virtual _AST_nested_list_elements fold_nested_list_elements(AST_nested_list_elements* in)
	{
		List<_AST_list_element>* list_elements = new List<_AST_list_element>;
		{
			List<AST_list_element*>::const_iterator i;
			for(i = in->list_elements->begin(); i != in->list_elements->end(); i++)
				if(*i != NULL) list_elements->push_back(fold_list_element(*i));
				else list_elements->push_back(0);
		}
		return fold_impl_nested_list_elements(in, list_elements);
	}

	virtual _AST_cast fold_cast(AST_cast* in)
	{
		_Token_cast cast = 0;
		if(in->cast != NULL) cast = fold_cast(in->cast);
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_cast(in, cast, expr);
	}

	virtual _AST_unary_op fold_unary_op(AST_unary_op* in)
	{
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_unary_op(in, op, expr);
	}

	virtual _AST_bin_op fold_bin_op(AST_bin_op* in)
	{
		_AST_expr left = 0;
		if(in->left != NULL) left = fold_expr(in->left);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_AST_expr right = 0;
		if(in->right != NULL) right = fold_expr(in->right);
		return fold_impl_bin_op(in, left, op, right);
	}

	virtual _AST_conditional_expr fold_conditional_expr(AST_conditional_expr* in)
	{
		_AST_expr cond = 0;
		if(in->cond != NULL) cond = fold_expr(in->cond);
		_AST_expr iftrue = 0;
		if(in->iftrue != NULL) iftrue = fold_expr(in->iftrue);
		_AST_expr iffalse = 0;
		if(in->iffalse != NULL) iffalse = fold_expr(in->iffalse);
		return fold_impl_conditional_expr(in, cond, iftrue, iffalse);
	}

	virtual _AST_ignore_errors fold_ignore_errors(AST_ignore_errors* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_ignore_errors(in, expr);
	}

	virtual _AST_constant fold_constant(AST_constant* in)
	{
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_Token_constant_name constant_name = 0;
		if(in->constant_name != NULL) constant_name = fold_constant_name(in->constant_name);
		return fold_impl_constant(in, class_name, constant_name);
	}

	virtual _AST_instanceof fold_instanceof(AST_instanceof* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_AST_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_instanceof(in, expr, class_name);
	}

	virtual _AST_variable fold_variable(AST_variable* in)
	{
		_AST_target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_AST_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_AST_expr>* array_indices = new List<_AST_expr>;
		{
			List<AST_expr*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_expr(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_variable(in, target, variable_name, array_indices);
	}

	virtual _AST_reflection fold_reflection(AST_reflection* in)
	{
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_reflection(in, expr);
	}

	virtual _AST_pre_op fold_pre_op(AST_pre_op* in)
	{
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_AST_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		return fold_impl_pre_op(in, op, variable);
	}

	virtual _AST_post_op fold_post_op(AST_post_op* in)
	{
		_AST_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		return fold_impl_post_op(in, variable, op);
	}

	virtual _AST_array fold_array(AST_array* in)
	{
		List<_AST_array_elem>* array_elems = new List<_AST_array_elem>;
		{
			List<AST_array_elem*>::const_iterator i;
			for(i = in->array_elems->begin(); i != in->array_elems->end(); i++)
				if(*i != NULL) array_elems->push_back(fold_array_elem(*i));
				else array_elems->push_back(0);
		}
		return fold_impl_array(in, array_elems);
	}

	virtual _AST_array_elem fold_array_elem(AST_array_elem* in)
	{
		_AST_expr key = 0;
		if(in->key != NULL) key = fold_expr(in->key);
		bool is_ref = in->is_ref;
		_AST_expr val = 0;
		if(in->val != NULL) val = fold_expr(in->val);
		return fold_impl_array_elem(in, key, is_ref, val);
	}

	virtual _AST_method_invocation fold_method_invocation(AST_method_invocation* in)
	{
		_AST_target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_AST_method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		List<_AST_actual_parameter>* actual_parameters = new List<_AST_actual_parameter>;
		{
			List<AST_actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_method_invocation(in, target, method_name, actual_parameters);
	}

	virtual _AST_actual_parameter fold_actual_parameter(AST_actual_parameter* in)
	{
		bool is_ref = in->is_ref;
		_AST_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_actual_parameter(in, is_ref, expr);
	}

	virtual _AST_new fold_new(AST_new* in)
	{
		_AST_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		List<_AST_actual_parameter>* actual_parameters = new List<_AST_actual_parameter>;
		{
			List<AST_actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_new(in, class_name, actual_parameters);
	}


// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _AST_php_script fold_impl_php_script(AST_php_script* orig, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_class_def fold_impl_class_def(AST_class_def* orig, _AST_class_mod class_mod, _Token_class_name class_name, _Token_class_name extends, List<_Token_interface_name>* implements, List<_AST_member>* members) { assert(0); };
	virtual _AST_class_mod fold_impl_class_mod(AST_class_mod* orig, bool is_abstract, bool is_final) { assert(0); };
	virtual _AST_interface_def fold_impl_interface_def(AST_interface_def* orig, _Token_interface_name interface_name, List<_Token_interface_name>* extends, List<_AST_member>* members) { assert(0); };
	virtual _AST_method fold_impl_method(AST_method* orig, _AST_signature signature, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_signature fold_impl_signature(AST_signature* orig, _AST_method_mod method_mod, bool is_ref, _Token_method_name method_name, List<_AST_formal_parameter>* formal_parameters) { assert(0); };
	virtual _AST_method_mod fold_impl_method_mod(AST_method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) { assert(0); };
	virtual _AST_formal_parameter fold_impl_formal_parameter(AST_formal_parameter* orig, _AST_type type, bool is_ref, _AST_name_with_default var) { assert(0); };
	virtual _AST_type fold_impl_type(AST_type* orig, _Token_class_name class_name) { assert(0); };
	virtual _AST_attribute fold_impl_attribute(AST_attribute* orig, _AST_attr_mod attr_mod, List<_AST_name_with_default>* vars) { assert(0); };
	virtual _AST_attr_mod fold_impl_attr_mod(AST_attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) { assert(0); };
	virtual _AST_name_with_default fold_impl_name_with_default(AST_name_with_default* orig, _Token_variable_name variable_name, _AST_expr expr) { assert(0); };
	virtual _AST_if fold_impl_if(AST_if* orig, _AST_expr expr, List<_AST_statement>* iftrue, List<_AST_statement>* iffalse) { assert(0); };
	virtual _AST_while fold_impl_while(AST_while* orig, _AST_expr expr, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_do fold_impl_do(AST_do* orig, List<_AST_statement>* statements, _AST_expr expr) { assert(0); };
	virtual _AST_for fold_impl_for(AST_for* orig, _AST_expr init, _AST_expr cond, _AST_expr incr, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_foreach fold_impl_foreach(AST_foreach* orig, _AST_expr expr, _AST_variable key, bool is_ref, _AST_variable val, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_switch fold_impl_switch(AST_switch* orig, _AST_expr expr, List<_AST_switch_case>* switch_cases) { assert(0); };
	virtual _AST_switch_case fold_impl_switch_case(AST_switch_case* orig, _AST_expr expr, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_break fold_impl_break(AST_break* orig, _AST_expr expr) { assert(0); };
	virtual _AST_continue fold_impl_continue(AST_continue* orig, _AST_expr expr) { assert(0); };
	virtual _AST_return fold_impl_return(AST_return* orig, _AST_expr expr) { assert(0); };
	virtual _AST_static_declaration fold_impl_static_declaration(AST_static_declaration* orig, List<_AST_name_with_default>* vars) { assert(0); };
	virtual _AST_global fold_impl_global(AST_global* orig, List<_AST_variable_name>* variable_names) { assert(0); };
	virtual _AST_declare fold_impl_declare(AST_declare* orig, List<_AST_directive>* directives, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_directive fold_impl_directive(AST_directive* orig, _Token_directive_name directive_name, _AST_expr expr) { assert(0); };
	virtual _AST_try fold_impl_try(AST_try* orig, List<_AST_statement>* statements, List<_AST_catch>* catches) { assert(0); };
	virtual _AST_catch fold_impl_catch(AST_catch* orig, _Token_class_name class_name, _Token_variable_name variable_name, List<_AST_statement>* statements) { assert(0); };
	virtual _AST_throw fold_impl_throw(AST_throw* orig, _AST_expr expr) { assert(0); };
	virtual _AST_eval_expr fold_impl_eval_expr(AST_eval_expr* orig, _AST_expr expr) { assert(0); };
	virtual _AST_nop fold_impl_nop(AST_nop* orig) { assert(0); };
	virtual _AST_branch fold_impl_branch(AST_branch* orig, _AST_expr expr, _Token_label_name iftrue, _Token_label_name iffalse) { assert(0); };
	virtual _AST_goto fold_impl_goto(AST_goto* orig, _Token_label_name label_name) { assert(0); };
	virtual _AST_label fold_impl_label(AST_label* orig, _Token_label_name label_name) { assert(0); };
	virtual _AST_assignment fold_impl_assignment(AST_assignment* orig, _AST_variable variable, bool is_ref, _AST_expr expr) { assert(0); };
	virtual _AST_op_assignment fold_impl_op_assignment(AST_op_assignment* orig, _AST_variable variable, _Token_op op, _AST_expr expr) { assert(0); };
	virtual _AST_list_assignment fold_impl_list_assignment(AST_list_assignment* orig, List<_AST_list_element>* list_elements, _AST_expr expr) { assert(0); };
	virtual _AST_nested_list_elements fold_impl_nested_list_elements(AST_nested_list_elements* orig, List<_AST_list_element>* list_elements) { assert(0); };
	virtual _AST_cast fold_impl_cast(AST_cast* orig, _Token_cast cast, _AST_expr expr) { assert(0); };
	virtual _AST_unary_op fold_impl_unary_op(AST_unary_op* orig, _Token_op op, _AST_expr expr) { assert(0); };
	virtual _AST_bin_op fold_impl_bin_op(AST_bin_op* orig, _AST_expr left, _Token_op op, _AST_expr right) { assert(0); };
	virtual _AST_conditional_expr fold_impl_conditional_expr(AST_conditional_expr* orig, _AST_expr cond, _AST_expr iftrue, _AST_expr iffalse) { assert(0); };
	virtual _AST_ignore_errors fold_impl_ignore_errors(AST_ignore_errors* orig, _AST_expr expr) { assert(0); };
	virtual _AST_constant fold_impl_constant(AST_constant* orig, _Token_class_name class_name, _Token_constant_name constant_name) { assert(0); };
	virtual _AST_instanceof fold_impl_instanceof(AST_instanceof* orig, _AST_expr expr, _AST_class_name class_name) { assert(0); };
	virtual _AST_variable fold_impl_variable(AST_variable* orig, _AST_target target, _AST_variable_name variable_name, List<_AST_expr>* array_indices) { assert(0); };
	virtual _AST_reflection fold_impl_reflection(AST_reflection* orig, _AST_expr expr) { assert(0); };
	virtual _AST_pre_op fold_impl_pre_op(AST_pre_op* orig, _Token_op op, _AST_variable variable) { assert(0); };
	virtual _AST_post_op fold_impl_post_op(AST_post_op* orig, _AST_variable variable, _Token_op op) { assert(0); };
	virtual _AST_array fold_impl_array(AST_array* orig, List<_AST_array_elem>* array_elems) { assert(0); };
	virtual _AST_array_elem fold_impl_array_elem(AST_array_elem* orig, _AST_expr key, bool is_ref, _AST_expr val) { assert(0); };
	virtual _AST_method_invocation fold_impl_method_invocation(AST_method_invocation* orig, _AST_target target, _AST_method_name method_name, List<_AST_actual_parameter>* actual_parameters) { assert(0); };
	virtual _AST_actual_parameter fold_impl_actual_parameter(AST_actual_parameter* orig, bool is_ref, _AST_expr expr) { assert(0); };
	virtual _AST_new fold_impl_new(AST_new* orig, _AST_class_name class_name, List<_AST_actual_parameter>* actual_parameters) { assert(0); };

	virtual _Token_class_name fold_class_name(Token_class_name* orig) { assert(0); };
	virtual _Token_interface_name fold_interface_name(Token_interface_name* orig) { assert(0); };
	virtual _Token_method_name fold_method_name(Token_method_name* orig) { assert(0); };
	virtual _Token_variable_name fold_variable_name(Token_variable_name* orig) { assert(0); };
	virtual _Token_directive_name fold_directive_name(Token_directive_name* orig) { assert(0); };
	virtual _Token_label_name fold_label_name(Token_label_name* orig) { assert(0); };
	virtual _Token_int fold_int(Token_int* orig) { assert(0); };
	virtual _Token_real fold_real(Token_real* orig) { assert(0); };
	virtual _Token_string fold_string(Token_string* orig) { assert(0); };
	virtual _Token_bool fold_bool(Token_bool* orig) { assert(0); };
	virtual _Token_null fold_null(Token_null* orig) { assert(0); };
	virtual _Token_op fold_op(Token_op* orig) { assert(0); };
	virtual _Token_cast fold_cast(Token_cast* orig) { assert(0); };
	virtual _Token_constant_name fold_constant_name(Token_constant_name* orig) { assert(0); };

// Manual dispatching for abstract classes
// Override only if you know what you are doing!
	virtual _AST_node fold_node(AST_node* in)
	{
		switch(in->classid())
		{
			case AST_php_script::ID:
				return fold_php_script(dynamic_cast<AST_php_script*>(in));
			case AST_class_mod::ID:
				return fold_class_mod(dynamic_cast<AST_class_mod*>(in));
			case AST_signature::ID:
				return fold_signature(dynamic_cast<AST_signature*>(in));
			case AST_method_mod::ID:
				return fold_method_mod(dynamic_cast<AST_method_mod*>(in));
			case AST_formal_parameter::ID:
				return fold_formal_parameter(dynamic_cast<AST_formal_parameter*>(in));
			case AST_type::ID:
				return fold_type(dynamic_cast<AST_type*>(in));
			case AST_attr_mod::ID:
				return fold_attr_mod(dynamic_cast<AST_attr_mod*>(in));
			case AST_name_with_default::ID:
				return fold_name_with_default(dynamic_cast<AST_name_with_default*>(in));
			case AST_directive::ID:
				return fold_directive(dynamic_cast<AST_directive*>(in));
			case AST_variable::ID:
				return fold_variable(dynamic_cast<AST_variable*>(in));
			case AST_nested_list_elements::ID:
				return fold_nested_list_elements(dynamic_cast<AST_nested_list_elements*>(in));
			case Token_variable_name::ID:
				return fold_variable_name(dynamic_cast<Token_variable_name*>(in));
			case AST_reflection::ID:
				return fold_reflection(dynamic_cast<AST_reflection*>(in));
			case AST_assignment::ID:
				return fold_assignment(dynamic_cast<AST_assignment*>(in));
			case AST_op_assignment::ID:
				return fold_op_assignment(dynamic_cast<AST_op_assignment*>(in));
			case AST_list_assignment::ID:
				return fold_list_assignment(dynamic_cast<AST_list_assignment*>(in));
			case AST_cast::ID:
				return fold_cast(dynamic_cast<AST_cast*>(in));
			case AST_unary_op::ID:
				return fold_unary_op(dynamic_cast<AST_unary_op*>(in));
			case AST_bin_op::ID:
				return fold_bin_op(dynamic_cast<AST_bin_op*>(in));
			case AST_conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
			case AST_ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
			case AST_constant::ID:
				return fold_constant(dynamic_cast<AST_constant*>(in));
			case AST_instanceof::ID:
				return fold_instanceof(dynamic_cast<AST_instanceof*>(in));
			case AST_pre_op::ID:
				return fold_pre_op(dynamic_cast<AST_pre_op*>(in));
			case AST_post_op::ID:
				return fold_post_op(dynamic_cast<AST_post_op*>(in));
			case AST_array::ID:
				return fold_array(dynamic_cast<AST_array*>(in));
			case AST_method_invocation::ID:
				return fold_method_invocation(dynamic_cast<AST_method_invocation*>(in));
			case AST_new::ID:
				return fold_new(dynamic_cast<AST_new*>(in));
			case Token_int::ID:
				return fold_int(dynamic_cast<Token_int*>(in));
			case Token_real::ID:
				return fold_real(dynamic_cast<Token_real*>(in));
			case Token_string::ID:
				return fold_string(dynamic_cast<Token_string*>(in));
			case Token_bool::ID:
				return fold_bool(dynamic_cast<Token_bool*>(in));
			case Token_null::ID:
				return fold_null(dynamic_cast<Token_null*>(in));
			case Token_class_name::ID:
				return fold_class_name(dynamic_cast<Token_class_name*>(in));
			case AST_array_elem::ID:
				return fold_array_elem(dynamic_cast<AST_array_elem*>(in));
			case Token_method_name::ID:
				return fold_method_name(dynamic_cast<Token_method_name*>(in));
			case AST_actual_parameter::ID:
				return fold_actual_parameter(dynamic_cast<AST_actual_parameter*>(in));
			case AST_method::ID:
				return fold_method(dynamic_cast<AST_method*>(in));
			case AST_attribute::ID:
				return fold_attribute(dynamic_cast<AST_attribute*>(in));
			case AST_class_def::ID:
				return fold_class_def(dynamic_cast<AST_class_def*>(in));
			case AST_interface_def::ID:
				return fold_interface_def(dynamic_cast<AST_interface_def*>(in));
			case AST_if::ID:
				return fold_if(dynamic_cast<AST_if*>(in));
			case AST_while::ID:
				return fold_while(dynamic_cast<AST_while*>(in));
			case AST_do::ID:
				return fold_do(dynamic_cast<AST_do*>(in));
			case AST_for::ID:
				return fold_for(dynamic_cast<AST_for*>(in));
			case AST_foreach::ID:
				return fold_foreach(dynamic_cast<AST_foreach*>(in));
			case AST_switch::ID:
				return fold_switch(dynamic_cast<AST_switch*>(in));
			case AST_break::ID:
				return fold_break(dynamic_cast<AST_break*>(in));
			case AST_continue::ID:
				return fold_continue(dynamic_cast<AST_continue*>(in));
			case AST_return::ID:
				return fold_return(dynamic_cast<AST_return*>(in));
			case AST_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<AST_static_declaration*>(in));
			case AST_global::ID:
				return fold_global(dynamic_cast<AST_global*>(in));
			case AST_declare::ID:
				return fold_declare(dynamic_cast<AST_declare*>(in));
			case AST_try::ID:
				return fold_try(dynamic_cast<AST_try*>(in));
			case AST_throw::ID:
				return fold_throw(dynamic_cast<AST_throw*>(in));
			case AST_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<AST_eval_expr*>(in));
			case AST_nop::ID:
				return fold_nop(dynamic_cast<AST_nop*>(in));
			case AST_label::ID:
				return fold_label(dynamic_cast<AST_label*>(in));
			case AST_goto::ID:
				return fold_goto(dynamic_cast<AST_goto*>(in));
			case AST_branch::ID:
				return fold_branch(dynamic_cast<AST_branch*>(in));
			case AST_switch_case::ID:
				return fold_switch_case(dynamic_cast<AST_switch_case*>(in));
			case AST_catch::ID:
				return fold_catch(dynamic_cast<AST_catch*>(in));
			case Token_interface_name::ID:
				return fold_interface_name(dynamic_cast<Token_interface_name*>(in));
			case Token_directive_name::ID:
				return fold_directive_name(dynamic_cast<Token_directive_name*>(in));
			case Token_cast::ID:
				return fold_cast(dynamic_cast<Token_cast*>(in));
			case Token_op::ID:
				return fold_op(dynamic_cast<Token_op*>(in));
			case Token_constant_name::ID:
				return fold_constant_name(dynamic_cast<Token_constant_name*>(in));
			case Token_label_name::ID:
				return fold_label_name(dynamic_cast<Token_label_name*>(in));
		}
		assert(0);
	}

	virtual _AST_statement fold_statement(AST_statement* in)
	{
		switch(in->classid())
		{
			case AST_class_def::ID:
				return fold_class_def(dynamic_cast<AST_class_def*>(in));
			case AST_interface_def::ID:
				return fold_interface_def(dynamic_cast<AST_interface_def*>(in));
			case AST_method::ID:
				return fold_method(dynamic_cast<AST_method*>(in));
			case AST_if::ID:
				return fold_if(dynamic_cast<AST_if*>(in));
			case AST_while::ID:
				return fold_while(dynamic_cast<AST_while*>(in));
			case AST_do::ID:
				return fold_do(dynamic_cast<AST_do*>(in));
			case AST_for::ID:
				return fold_for(dynamic_cast<AST_for*>(in));
			case AST_foreach::ID:
				return fold_foreach(dynamic_cast<AST_foreach*>(in));
			case AST_switch::ID:
				return fold_switch(dynamic_cast<AST_switch*>(in));
			case AST_break::ID:
				return fold_break(dynamic_cast<AST_break*>(in));
			case AST_continue::ID:
				return fold_continue(dynamic_cast<AST_continue*>(in));
			case AST_return::ID:
				return fold_return(dynamic_cast<AST_return*>(in));
			case AST_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<AST_static_declaration*>(in));
			case AST_global::ID:
				return fold_global(dynamic_cast<AST_global*>(in));
			case AST_declare::ID:
				return fold_declare(dynamic_cast<AST_declare*>(in));
			case AST_try::ID:
				return fold_try(dynamic_cast<AST_try*>(in));
			case AST_throw::ID:
				return fold_throw(dynamic_cast<AST_throw*>(in));
			case AST_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<AST_eval_expr*>(in));
			case AST_nop::ID:
				return fold_nop(dynamic_cast<AST_nop*>(in));
			case AST_label::ID:
				return fold_label(dynamic_cast<AST_label*>(in));
			case AST_goto::ID:
				return fold_goto(dynamic_cast<AST_goto*>(in));
			case AST_branch::ID:
				return fold_branch(dynamic_cast<AST_branch*>(in));
		}
		assert(0);
	}

	virtual _AST_member fold_member(AST_member* in)
	{
		switch(in->classid())
		{
			case AST_method::ID:
				return fold_method(dynamic_cast<AST_method*>(in));
			case AST_attribute::ID:
				return fold_attribute(dynamic_cast<AST_attribute*>(in));
		}
		assert(0);
	}

	virtual _AST_expr fold_expr(AST_expr* in)
	{
		switch(in->classid())
		{
			case AST_assignment::ID:
				return fold_assignment(dynamic_cast<AST_assignment*>(in));
			case AST_op_assignment::ID:
				return fold_op_assignment(dynamic_cast<AST_op_assignment*>(in));
			case AST_list_assignment::ID:
				return fold_list_assignment(dynamic_cast<AST_list_assignment*>(in));
			case AST_cast::ID:
				return fold_cast(dynamic_cast<AST_cast*>(in));
			case AST_unary_op::ID:
				return fold_unary_op(dynamic_cast<AST_unary_op*>(in));
			case AST_bin_op::ID:
				return fold_bin_op(dynamic_cast<AST_bin_op*>(in));
			case AST_conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
			case AST_ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
			case AST_constant::ID:
				return fold_constant(dynamic_cast<AST_constant*>(in));
			case AST_instanceof::ID:
				return fold_instanceof(dynamic_cast<AST_instanceof*>(in));
			case AST_variable::ID:
				return fold_variable(dynamic_cast<AST_variable*>(in));
			case AST_pre_op::ID:
				return fold_pre_op(dynamic_cast<AST_pre_op*>(in));
			case AST_post_op::ID:
				return fold_post_op(dynamic_cast<AST_post_op*>(in));
			case AST_array::ID:
				return fold_array(dynamic_cast<AST_array*>(in));
			case AST_method_invocation::ID:
				return fold_method_invocation(dynamic_cast<AST_method_invocation*>(in));
			case AST_new::ID:
				return fold_new(dynamic_cast<AST_new*>(in));
			case Token_int::ID:
				return fold_int(dynamic_cast<Token_int*>(in));
			case Token_real::ID:
				return fold_real(dynamic_cast<Token_real*>(in));
			case Token_string::ID:
				return fold_string(dynamic_cast<Token_string*>(in));
			case Token_bool::ID:
				return fold_bool(dynamic_cast<Token_bool*>(in));
			case Token_null::ID:
				return fold_null(dynamic_cast<Token_null*>(in));
		}
		assert(0);
	}

	virtual _AST_literal fold_literal(AST_literal* in)
	{
		switch(in->classid())
		{
			case Token_int::ID:
				return fold_int(dynamic_cast<Token_int*>(in));
			case Token_real::ID:
				return fold_real(dynamic_cast<Token_real*>(in));
			case Token_string::ID:
				return fold_string(dynamic_cast<Token_string*>(in));
			case Token_bool::ID:
				return fold_bool(dynamic_cast<Token_bool*>(in));
			case Token_null::ID:
				return fold_null(dynamic_cast<Token_null*>(in));
		}
		assert(0);
	}

	virtual _AST_list_element fold_list_element(AST_list_element* in)
	{
		switch(in->classid())
		{
			case AST_variable::ID:
				return fold_variable(dynamic_cast<AST_variable*>(in));
			case AST_nested_list_elements::ID:
				return fold_nested_list_elements(dynamic_cast<AST_nested_list_elements*>(in));
		}
		assert(0);
	}

	virtual _AST_variable_name fold_variable_name(AST_variable_name* in)
	{
		switch(in->classid())
		{
			case Token_variable_name::ID:
				return fold_variable_name(dynamic_cast<Token_variable_name*>(in));
			case AST_reflection::ID:
				return fold_reflection(dynamic_cast<AST_reflection*>(in));
		}
		assert(0);
	}

	virtual _AST_target fold_target(AST_target* in)
	{
		switch(in->classid())
		{
			case AST_assignment::ID:
				return fold_assignment(dynamic_cast<AST_assignment*>(in));
			case AST_op_assignment::ID:
				return fold_op_assignment(dynamic_cast<AST_op_assignment*>(in));
			case AST_list_assignment::ID:
				return fold_list_assignment(dynamic_cast<AST_list_assignment*>(in));
			case AST_cast::ID:
				return fold_cast(dynamic_cast<AST_cast*>(in));
			case AST_unary_op::ID:
				return fold_unary_op(dynamic_cast<AST_unary_op*>(in));
			case AST_bin_op::ID:
				return fold_bin_op(dynamic_cast<AST_bin_op*>(in));
			case AST_conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<AST_conditional_expr*>(in));
			case AST_ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<AST_ignore_errors*>(in));
			case AST_constant::ID:
				return fold_constant(dynamic_cast<AST_constant*>(in));
			case AST_instanceof::ID:
				return fold_instanceof(dynamic_cast<AST_instanceof*>(in));
			case AST_variable::ID:
				return fold_variable(dynamic_cast<AST_variable*>(in));
			case AST_pre_op::ID:
				return fold_pre_op(dynamic_cast<AST_pre_op*>(in));
			case AST_post_op::ID:
				return fold_post_op(dynamic_cast<AST_post_op*>(in));
			case AST_array::ID:
				return fold_array(dynamic_cast<AST_array*>(in));
			case AST_method_invocation::ID:
				return fold_method_invocation(dynamic_cast<AST_method_invocation*>(in));
			case AST_new::ID:
				return fold_new(dynamic_cast<AST_new*>(in));
			case Token_int::ID:
				return fold_int(dynamic_cast<Token_int*>(in));
			case Token_real::ID:
				return fold_real(dynamic_cast<Token_real*>(in));
			case Token_string::ID:
				return fold_string(dynamic_cast<Token_string*>(in));
			case Token_bool::ID:
				return fold_bool(dynamic_cast<Token_bool*>(in));
			case Token_null::ID:
				return fold_null(dynamic_cast<Token_null*>(in));
			case Token_class_name::ID:
				return fold_class_name(dynamic_cast<Token_class_name*>(in));
		}
		assert(0);
	}

	virtual _AST_method_name fold_method_name(AST_method_name* in)
	{
		switch(in->classid())
		{
			case Token_method_name::ID:
				return fold_method_name(dynamic_cast<Token_method_name*>(in));
			case AST_reflection::ID:
				return fold_reflection(dynamic_cast<AST_reflection*>(in));
		}
		assert(0);
	}

	virtual _AST_class_name fold_class_name(AST_class_name* in)
	{
		switch(in->classid())
		{
			case Token_class_name::ID:
				return fold_class_name(dynamic_cast<Token_class_name*>(in));
			case AST_reflection::ID:
				return fold_reflection(dynamic_cast<AST_reflection*>(in));
		}
		assert(0);
	}

	virtual _AST_commented_node fold_commented_node(AST_commented_node* in)
	{
		switch(in->classid())
		{
			case AST_method::ID:
				return fold_method(dynamic_cast<AST_method*>(in));
			case AST_attribute::ID:
				return fold_attribute(dynamic_cast<AST_attribute*>(in));
			case AST_class_def::ID:
				return fold_class_def(dynamic_cast<AST_class_def*>(in));
			case AST_interface_def::ID:
				return fold_interface_def(dynamic_cast<AST_interface_def*>(in));
			case AST_if::ID:
				return fold_if(dynamic_cast<AST_if*>(in));
			case AST_while::ID:
				return fold_while(dynamic_cast<AST_while*>(in));
			case AST_do::ID:
				return fold_do(dynamic_cast<AST_do*>(in));
			case AST_for::ID:
				return fold_for(dynamic_cast<AST_for*>(in));
			case AST_foreach::ID:
				return fold_foreach(dynamic_cast<AST_foreach*>(in));
			case AST_switch::ID:
				return fold_switch(dynamic_cast<AST_switch*>(in));
			case AST_break::ID:
				return fold_break(dynamic_cast<AST_break*>(in));
			case AST_continue::ID:
				return fold_continue(dynamic_cast<AST_continue*>(in));
			case AST_return::ID:
				return fold_return(dynamic_cast<AST_return*>(in));
			case AST_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<AST_static_declaration*>(in));
			case AST_global::ID:
				return fold_global(dynamic_cast<AST_global*>(in));
			case AST_declare::ID:
				return fold_declare(dynamic_cast<AST_declare*>(in));
			case AST_try::ID:
				return fold_try(dynamic_cast<AST_try*>(in));
			case AST_throw::ID:
				return fold_throw(dynamic_cast<AST_throw*>(in));
			case AST_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<AST_eval_expr*>(in));
			case AST_nop::ID:
				return fold_nop(dynamic_cast<AST_nop*>(in));
			case AST_label::ID:
				return fold_label(dynamic_cast<AST_label*>(in));
			case AST_goto::ID:
				return fold_goto(dynamic_cast<AST_goto*>(in));
			case AST_branch::ID:
				return fold_branch(dynamic_cast<AST_branch*>(in));
			case AST_switch_case::ID:
				return fold_switch_case(dynamic_cast<AST_switch_case*>(in));
			case AST_catch::ID:
				return fold_catch(dynamic_cast<AST_catch*>(in));
		}
		assert(0);
	}

	virtual _AST_identifier fold_identifier(AST_identifier* in)
	{
		switch(in->classid())
		{
			case Token_interface_name::ID:
				return fold_interface_name(dynamic_cast<Token_interface_name*>(in));
			case Token_class_name::ID:
				return fold_class_name(dynamic_cast<Token_class_name*>(in));
			case Token_method_name::ID:
				return fold_method_name(dynamic_cast<Token_method_name*>(in));
			case Token_variable_name::ID:
				return fold_variable_name(dynamic_cast<Token_variable_name*>(in));
			case Token_directive_name::ID:
				return fold_directive_name(dynamic_cast<Token_directive_name*>(in));
			case Token_cast::ID:
				return fold_cast(dynamic_cast<Token_cast*>(in));
			case Token_op::ID:
				return fold_op(dynamic_cast<Token_op*>(in));
			case Token_constant_name::ID:
				return fold_constant_name(dynamic_cast<Token_constant_name*>(in));
			case Token_label_name::ID:
				return fold_label_name(dynamic_cast<Token_label_name*>(in));
		}
		assert(0);
	}


};

template<class T>
class AST_uniform_fold : public AST_fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T> {};
}

