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


#include "HIR.h"
namespace HIR{
template
<class _HIR_node,
 class _HIR_php_script,
 class _HIR_statement,
 class _HIR_class_def,
 class _HIR_class_mod,
 class _HIR_interface_def,
 class _HIR_member,
 class _HIR_method,
 class _HIR_signature,
 class _HIR_method_mod,
 class _HIR_formal_parameter,
 class _HIR_type,
 class _HIR_attribute,
 class _HIR_attr_mod,
 class _HIR_if,
 class _HIR_while,
 class _HIR_do,
 class _HIR_for,
 class _HIR_foreach,
 class _HIR_switch,
 class _HIR_switch_case,
 class _HIR_break,
 class _HIR_continue,
 class _HIR_return,
 class _HIR_static_declaration,
 class _HIR_global,
 class _HIR_declare,
 class _HIR_directive,
 class _HIR_try,
 class _HIR_catch,
 class _HIR_throw,
 class _HIR_eval_expr,
 class _HIR_nop,
 class _HIR_branch,
 class _HIR_goto,
 class _HIR_label,
 class _HIR_expr,
 class _HIR_literal,
 class _HIR_assignment,
 class _HIR_op_assignment,
 class _HIR_list_assignment,
 class _HIR_list_element,
 class _HIR_nested_list_elements,
 class _HIR_cast,
 class _HIR_unary_op,
 class _HIR_bin_op,
 class _HIR_conditional_expr,
 class _HIR_ignore_errors,
 class _HIR_constant,
 class _HIR_instanceof,
 class _HIR_variable,
 class _HIR_variable_name,
 class _HIR_reflection,
 class _HIR_target,
 class _HIR_pre_op,
 class _HIR_post_op,
 class _HIR_array,
 class _HIR_array_elem,
 class _HIR_method_invocation,
 class _HIR_method_name,
 class _HIR_actual_parameter,
 class _HIR_new,
 class _HIR_class_name,
 class _HIR_commented_node,
 class _HIR_identifier,
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
class HIR_fold
{
// Recursively fold the children before folding the parent
// This methods form the client API for a fold, but should not be
// overridden unless you know what you are doing
public:
	virtual _HIR_php_script fold_php_script(HIR_php_script* in)
	{
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_php_script(in, statements);
	}

	virtual _HIR_class_def fold_class_def(HIR_class_def* in)
	{
		_HIR_class_mod class_mod = 0;
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
		List<_HIR_member>* members = new List<_HIR_member>;
		{
			List<HIR_member*>::const_iterator i;
			for(i = in->members->begin(); i != in->members->end(); i++)
				if(*i != NULL) members->push_back(fold_member(*i));
				else members->push_back(0);
		}
		return fold_impl_class_def(in, class_mod, class_name, extends, implements, members);
	}

	virtual _HIR_class_mod fold_class_mod(HIR_class_mod* in)
	{
		bool is_abstract = in->is_abstract;
		bool is_final = in->is_final;
		return fold_impl_class_mod(in, is_abstract, is_final);
	}

	virtual _HIR_interface_def fold_interface_def(HIR_interface_def* in)
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
		List<_HIR_member>* members = new List<_HIR_member>;
		{
			List<HIR_member*>::const_iterator i;
			for(i = in->members->begin(); i != in->members->end(); i++)
				if(*i != NULL) members->push_back(fold_member(*i));
				else members->push_back(0);
		}
		return fold_impl_interface_def(in, interface_name, extends, members);
	}

	virtual _HIR_method fold_method(HIR_method* in)
	{
		_HIR_signature signature = 0;
		if(in->signature != NULL) signature = fold_signature(in->signature);
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_method(in, signature, statements);
	}

	virtual _HIR_signature fold_signature(HIR_signature* in)
	{
		_HIR_method_mod method_mod = 0;
		if(in->method_mod != NULL) method_mod = fold_method_mod(in->method_mod);
		bool is_ref = in->is_ref;
		_Token_method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		List<_HIR_formal_parameter>* formal_parameters = new List<_HIR_formal_parameter>;
		{
			List<HIR_formal_parameter*>::const_iterator i;
			for(i = in->formal_parameters->begin(); i != in->formal_parameters->end(); i++)
				if(*i != NULL) formal_parameters->push_back(fold_formal_parameter(*i));
				else formal_parameters->push_back(0);
		}
		return fold_impl_signature(in, method_mod, is_ref, method_name, formal_parameters);
	}

	virtual _HIR_method_mod fold_method_mod(HIR_method_mod* in)
	{
		bool is_public = in->is_public;
		bool is_protected = in->is_protected;
		bool is_private = in->is_private;
		bool is_static = in->is_static;
		bool is_abstract = in->is_abstract;
		bool is_final = in->is_final;
		return fold_impl_method_mod(in, is_public, is_protected, is_private, is_static, is_abstract, is_final);
	}

	virtual _HIR_formal_parameter fold_formal_parameter(HIR_formal_parameter* in)
	{
		_HIR_type type = 0;
		if(in->type != NULL) type = fold_type(in->type);
		bool is_ref = in->is_ref;
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_formal_parameter(in, type, is_ref, variable_name, expr);
	}

	virtual _HIR_type fold_type(HIR_type* in)
	{
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_type(in, class_name);
	}

	virtual _HIR_attribute fold_attribute(HIR_attribute* in)
	{
		_HIR_attr_mod attr_mod = 0;
		if(in->attr_mod != NULL) attr_mod = fold_attr_mod(in->attr_mod);
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_attribute(in, attr_mod, variable_name, expr);
	}

	virtual _HIR_attr_mod fold_attr_mod(HIR_attr_mod* in)
	{
		bool is_public = in->is_public;
		bool is_protected = in->is_protected;
		bool is_private = in->is_private;
		bool is_static = in->is_static;
		bool is_const = in->is_const;
		return fold_impl_attr_mod(in, is_public, is_protected, is_private, is_static, is_const);
	}

	virtual _HIR_if fold_if(HIR_if* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_HIR_statement>* iftrue = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->iftrue->begin(); i != in->iftrue->end(); i++)
				if(*i != NULL) iftrue->push_back(fold_statement(*i));
				else iftrue->push_back(0);
		}
		List<_HIR_statement>* iffalse = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->iffalse->begin(); i != in->iffalse->end(); i++)
				if(*i != NULL) iffalse->push_back(fold_statement(*i));
				else iffalse->push_back(0);
		}
		return fold_impl_if(in, expr, iftrue, iffalse);
	}

	virtual _HIR_while fold_while(HIR_while* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_while(in, expr, statements);
	}

	virtual _HIR_do fold_do(HIR_do* in)
	{
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_do(in, statements, expr);
	}

	virtual _HIR_for fold_for(HIR_for* in)
	{
		_HIR_expr init = 0;
		if(in->init != NULL) init = fold_expr(in->init);
		_HIR_expr cond = 0;
		if(in->cond != NULL) cond = fold_expr(in->cond);
		_HIR_expr incr = 0;
		if(in->incr != NULL) incr = fold_expr(in->incr);
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_for(in, init, cond, incr, statements);
	}

	virtual _HIR_foreach fold_foreach(HIR_foreach* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_HIR_variable key = 0;
		if(in->key != NULL) key = fold_variable(in->key);
		bool is_ref = in->is_ref;
		_HIR_variable val = 0;
		if(in->val != NULL) val = fold_variable(in->val);
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_foreach(in, expr, key, is_ref, val, statements);
	}

	virtual _HIR_switch fold_switch(HIR_switch* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_HIR_switch_case>* switch_cases = new List<_HIR_switch_case>;
		{
			List<HIR_switch_case*>::const_iterator i;
			for(i = in->switch_cases->begin(); i != in->switch_cases->end(); i++)
				if(*i != NULL) switch_cases->push_back(fold_switch_case(*i));
				else switch_cases->push_back(0);
		}
		return fold_impl_switch(in, expr, switch_cases);
	}

	virtual _HIR_switch_case fold_switch_case(HIR_switch_case* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_switch_case(in, expr, statements);
	}

	virtual _HIR_break fold_break(HIR_break* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_break(in, expr);
	}

	virtual _HIR_continue fold_continue(HIR_continue* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_continue(in, expr);
	}

	virtual _HIR_return fold_return(HIR_return* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_return(in, expr);
	}

	virtual _HIR_static_declaration fold_static_declaration(HIR_static_declaration* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_static_declaration(in, variable_name, expr);
	}

	virtual _HIR_global fold_global(HIR_global* in)
	{
		_HIR_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_global(in, variable_name);
	}

	virtual _HIR_declare fold_declare(HIR_declare* in)
	{
		List<_HIR_directive>* directives = new List<_HIR_directive>;
		{
			List<HIR_directive*>::const_iterator i;
			for(i = in->directives->begin(); i != in->directives->end(); i++)
				if(*i != NULL) directives->push_back(fold_directive(*i));
				else directives->push_back(0);
		}
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_declare(in, directives, statements);
	}

	virtual _HIR_directive fold_directive(HIR_directive* in)
	{
		_Token_directive_name directive_name = 0;
		if(in->directive_name != NULL) directive_name = fold_directive_name(in->directive_name);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_directive(in, directive_name, expr);
	}

	virtual _HIR_try fold_try(HIR_try* in)
	{
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		List<_HIR_catch>* catches = new List<_HIR_catch>;
		{
			List<HIR_catch*>::const_iterator i;
			for(i = in->catches->begin(); i != in->catches->end(); i++)
				if(*i != NULL) catches->push_back(fold_catch(*i));
				else catches->push_back(0);
		}
		return fold_impl_try(in, statements, catches);
	}

	virtual _HIR_catch fold_catch(HIR_catch* in)
	{
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_HIR_statement>* statements = new List<_HIR_statement>;
		{
			List<HIR_statement*>::const_iterator i;
			for(i = in->statements->begin(); i != in->statements->end(); i++)
				if(*i != NULL) statements->push_back(fold_statement(*i));
				else statements->push_back(0);
		}
		return fold_impl_catch(in, class_name, variable_name, statements);
	}

	virtual _HIR_throw fold_throw(HIR_throw* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_throw(in, expr);
	}

	virtual _HIR_eval_expr fold_eval_expr(HIR_eval_expr* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_eval_expr(in, expr);
	}

	virtual _HIR_nop fold_nop(HIR_nop* in)
	{
		return fold_impl_nop(in);
	}

	virtual _HIR_branch fold_branch(HIR_branch* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_Token_label_name iftrue = 0;
		if(in->iftrue != NULL) iftrue = fold_label_name(in->iftrue);
		_Token_label_name iffalse = 0;
		if(in->iffalse != NULL) iffalse = fold_label_name(in->iffalse);
		return fold_impl_branch(in, expr, iftrue, iffalse);
	}

	virtual _HIR_goto fold_goto(HIR_goto* in)
	{
		_Token_label_name label_name = 0;
		if(in->label_name != NULL) label_name = fold_label_name(in->label_name);
		return fold_impl_goto(in, label_name);
	}

	virtual _HIR_label fold_label(HIR_label* in)
	{
		_Token_label_name label_name = 0;
		if(in->label_name != NULL) label_name = fold_label_name(in->label_name);
		return fold_impl_label(in, label_name);
	}

	virtual _HIR_assignment fold_assignment(HIR_assignment* in)
	{
		_HIR_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		bool is_ref = in->is_ref;
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_assignment(in, variable, is_ref, expr);
	}

	virtual _HIR_op_assignment fold_op_assignment(HIR_op_assignment* in)
	{
		_HIR_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_op_assignment(in, variable, op, expr);
	}

	virtual _HIR_list_assignment fold_list_assignment(HIR_list_assignment* in)
	{
		List<_HIR_list_element>* list_elements = new List<_HIR_list_element>;
		{
			List<HIR_list_element*>::const_iterator i;
			for(i = in->list_elements->begin(); i != in->list_elements->end(); i++)
				if(*i != NULL) list_elements->push_back(fold_list_element(*i));
				else list_elements->push_back(0);
		}
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_list_assignment(in, list_elements, expr);
	}

	virtual _HIR_nested_list_elements fold_nested_list_elements(HIR_nested_list_elements* in)
	{
		List<_HIR_list_element>* list_elements = new List<_HIR_list_element>;
		{
			List<HIR_list_element*>::const_iterator i;
			for(i = in->list_elements->begin(); i != in->list_elements->end(); i++)
				if(*i != NULL) list_elements->push_back(fold_list_element(*i));
				else list_elements->push_back(0);
		}
		return fold_impl_nested_list_elements(in, list_elements);
	}

	virtual _HIR_cast fold_cast(HIR_cast* in)
	{
		_Token_cast cast = 0;
		if(in->cast != NULL) cast = fold_cast(in->cast);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_cast(in, cast, expr);
	}

	virtual _HIR_unary_op fold_unary_op(HIR_unary_op* in)
	{
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_unary_op(in, op, expr);
	}

	virtual _HIR_bin_op fold_bin_op(HIR_bin_op* in)
	{
		_HIR_expr left = 0;
		if(in->left != NULL) left = fold_expr(in->left);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_HIR_expr right = 0;
		if(in->right != NULL) right = fold_expr(in->right);
		return fold_impl_bin_op(in, left, op, right);
	}

	virtual _HIR_conditional_expr fold_conditional_expr(HIR_conditional_expr* in)
	{
		_HIR_expr cond = 0;
		if(in->cond != NULL) cond = fold_expr(in->cond);
		_HIR_expr iftrue = 0;
		if(in->iftrue != NULL) iftrue = fold_expr(in->iftrue);
		_HIR_expr iffalse = 0;
		if(in->iffalse != NULL) iffalse = fold_expr(in->iffalse);
		return fold_impl_conditional_expr(in, cond, iftrue, iffalse);
	}

	virtual _HIR_ignore_errors fold_ignore_errors(HIR_ignore_errors* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_ignore_errors(in, expr);
	}

	virtual _HIR_constant fold_constant(HIR_constant* in)
	{
		_Token_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		_Token_constant_name constant_name = 0;
		if(in->constant_name != NULL) constant_name = fold_constant_name(in->constant_name);
		return fold_impl_constant(in, class_name, constant_name);
	}

	virtual _HIR_instanceof fold_instanceof(HIR_instanceof* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		_HIR_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_instanceof(in, expr, class_name);
	}

	virtual _HIR_variable fold_variable(HIR_variable* in)
	{
		_HIR_target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_HIR_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_HIR_expr>* array_indices = new List<_HIR_expr>;
		{
			List<HIR_expr*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_expr(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_variable(in, target, variable_name, array_indices);
	}

	virtual _HIR_reflection fold_reflection(HIR_reflection* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_reflection(in, expr);
	}

	virtual _HIR_pre_op fold_pre_op(HIR_pre_op* in)
	{
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_HIR_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		return fold_impl_pre_op(in, op, variable);
	}

	virtual _HIR_post_op fold_post_op(HIR_post_op* in)
	{
		_HIR_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		return fold_impl_post_op(in, variable, op);
	}

	virtual _HIR_array fold_array(HIR_array* in)
	{
		List<_HIR_array_elem>* array_elems = new List<_HIR_array_elem>;
		{
			List<HIR_array_elem*>::const_iterator i;
			for(i = in->array_elems->begin(); i != in->array_elems->end(); i++)
				if(*i != NULL) array_elems->push_back(fold_array_elem(*i));
				else array_elems->push_back(0);
		}
		return fold_impl_array(in, array_elems);
	}

	virtual _HIR_array_elem fold_array_elem(HIR_array_elem* in)
	{
		_HIR_expr key = 0;
		if(in->key != NULL) key = fold_expr(in->key);
		bool is_ref = in->is_ref;
		_HIR_expr val = 0;
		if(in->val != NULL) val = fold_expr(in->val);
		return fold_impl_array_elem(in, key, is_ref, val);
	}

	virtual _HIR_method_invocation fold_method_invocation(HIR_method_invocation* in)
	{
		_HIR_target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_HIR_method_name method_name = 0;
		if(in->method_name != NULL) method_name = fold_method_name(in->method_name);
		List<_HIR_actual_parameter>* actual_parameters = new List<_HIR_actual_parameter>;
		{
			List<HIR_actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_method_invocation(in, target, method_name, actual_parameters);
	}

	virtual _HIR_actual_parameter fold_actual_parameter(HIR_actual_parameter* in)
	{
		bool is_ref = in->is_ref;
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_actual_parameter(in, is_ref, expr);
	}

	virtual _HIR_new fold_new(HIR_new* in)
	{
		_HIR_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		List<_HIR_actual_parameter>* actual_parameters = new List<_HIR_actual_parameter>;
		{
			List<HIR_actual_parameter*>::const_iterator i;
			for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
				if(*i != NULL) actual_parameters->push_back(fold_actual_parameter(*i));
				else actual_parameters->push_back(0);
		}
		return fold_impl_new(in, class_name, actual_parameters);
	}


// The user-defined folds
// Override these methods to get specific functionality
public:
	virtual _HIR_php_script fold_impl_php_script(HIR_php_script* orig, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_class_def fold_impl_class_def(HIR_class_def* orig, _HIR_class_mod class_mod, _Token_class_name class_name, _Token_class_name extends, List<_Token_interface_name>* implements, List<_HIR_member>* members) { assert(0); };
	virtual _HIR_class_mod fold_impl_class_mod(HIR_class_mod* orig, bool is_abstract, bool is_final) { assert(0); };
	virtual _HIR_interface_def fold_impl_interface_def(HIR_interface_def* orig, _Token_interface_name interface_name, List<_Token_interface_name>* extends, List<_HIR_member>* members) { assert(0); };
	virtual _HIR_method fold_impl_method(HIR_method* orig, _HIR_signature signature, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_signature fold_impl_signature(HIR_signature* orig, _HIR_method_mod method_mod, bool is_ref, _Token_method_name method_name, List<_HIR_formal_parameter>* formal_parameters) { assert(0); };
	virtual _HIR_method_mod fold_impl_method_mod(HIR_method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) { assert(0); };
	virtual _HIR_formal_parameter fold_impl_formal_parameter(HIR_formal_parameter* orig, _HIR_type type, bool is_ref, _Token_variable_name variable_name, _HIR_expr expr) { assert(0); };
	virtual _HIR_type fold_impl_type(HIR_type* orig, _Token_class_name class_name) { assert(0); };
	virtual _HIR_attribute fold_impl_attribute(HIR_attribute* orig, _HIR_attr_mod attr_mod, _Token_variable_name variable_name, _HIR_expr expr) { assert(0); };
	virtual _HIR_attr_mod fold_impl_attr_mod(HIR_attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) { assert(0); };
	virtual _HIR_if fold_impl_if(HIR_if* orig, _HIR_expr expr, List<_HIR_statement>* iftrue, List<_HIR_statement>* iffalse) { assert(0); };
	virtual _HIR_while fold_impl_while(HIR_while* orig, _HIR_expr expr, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_do fold_impl_do(HIR_do* orig, List<_HIR_statement>* statements, _HIR_expr expr) { assert(0); };
	virtual _HIR_for fold_impl_for(HIR_for* orig, _HIR_expr init, _HIR_expr cond, _HIR_expr incr, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_foreach fold_impl_foreach(HIR_foreach* orig, _HIR_expr expr, _HIR_variable key, bool is_ref, _HIR_variable val, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_switch fold_impl_switch(HIR_switch* orig, _HIR_expr expr, List<_HIR_switch_case>* switch_cases) { assert(0); };
	virtual _HIR_switch_case fold_impl_switch_case(HIR_switch_case* orig, _HIR_expr expr, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_break fold_impl_break(HIR_break* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_continue fold_impl_continue(HIR_continue* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_return fold_impl_return(HIR_return* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_static_declaration fold_impl_static_declaration(HIR_static_declaration* orig, _Token_variable_name variable_name, _HIR_expr expr) { assert(0); };
	virtual _HIR_global fold_impl_global(HIR_global* orig, _HIR_variable_name variable_name) { assert(0); };
	virtual _HIR_declare fold_impl_declare(HIR_declare* orig, List<_HIR_directive>* directives, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_directive fold_impl_directive(HIR_directive* orig, _Token_directive_name directive_name, _HIR_expr expr) { assert(0); };
	virtual _HIR_try fold_impl_try(HIR_try* orig, List<_HIR_statement>* statements, List<_HIR_catch>* catches) { assert(0); };
	virtual _HIR_catch fold_impl_catch(HIR_catch* orig, _Token_class_name class_name, _Token_variable_name variable_name, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_throw fold_impl_throw(HIR_throw* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_eval_expr fold_impl_eval_expr(HIR_eval_expr* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_nop fold_impl_nop(HIR_nop* orig) { assert(0); };
	virtual _HIR_branch fold_impl_branch(HIR_branch* orig, _HIR_expr expr, _Token_label_name iftrue, _Token_label_name iffalse) { assert(0); };
	virtual _HIR_goto fold_impl_goto(HIR_goto* orig, _Token_label_name label_name) { assert(0); };
	virtual _HIR_label fold_impl_label(HIR_label* orig, _Token_label_name label_name) { assert(0); };
	virtual _HIR_assignment fold_impl_assignment(HIR_assignment* orig, _HIR_variable variable, bool is_ref, _HIR_expr expr) { assert(0); };
	virtual _HIR_op_assignment fold_impl_op_assignment(HIR_op_assignment* orig, _HIR_variable variable, _Token_op op, _HIR_expr expr) { assert(0); };
	virtual _HIR_list_assignment fold_impl_list_assignment(HIR_list_assignment* orig, List<_HIR_list_element>* list_elements, _HIR_expr expr) { assert(0); };
	virtual _HIR_nested_list_elements fold_impl_nested_list_elements(HIR_nested_list_elements* orig, List<_HIR_list_element>* list_elements) { assert(0); };
	virtual _HIR_cast fold_impl_cast(HIR_cast* orig, _Token_cast cast, _HIR_expr expr) { assert(0); };
	virtual _HIR_unary_op fold_impl_unary_op(HIR_unary_op* orig, _Token_op op, _HIR_expr expr) { assert(0); };
	virtual _HIR_bin_op fold_impl_bin_op(HIR_bin_op* orig, _HIR_expr left, _Token_op op, _HIR_expr right) { assert(0); };
	virtual _HIR_conditional_expr fold_impl_conditional_expr(HIR_conditional_expr* orig, _HIR_expr cond, _HIR_expr iftrue, _HIR_expr iffalse) { assert(0); };
	virtual _HIR_ignore_errors fold_impl_ignore_errors(HIR_ignore_errors* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_constant fold_impl_constant(HIR_constant* orig, _Token_class_name class_name, _Token_constant_name constant_name) { assert(0); };
	virtual _HIR_instanceof fold_impl_instanceof(HIR_instanceof* orig, _HIR_expr expr, _HIR_class_name class_name) { assert(0); };
	virtual _HIR_variable fold_impl_variable(HIR_variable* orig, _HIR_target target, _HIR_variable_name variable_name, List<_HIR_expr>* array_indices) { assert(0); };
	virtual _HIR_reflection fold_impl_reflection(HIR_reflection* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_pre_op fold_impl_pre_op(HIR_pre_op* orig, _Token_op op, _HIR_variable variable) { assert(0); };
	virtual _HIR_post_op fold_impl_post_op(HIR_post_op* orig, _HIR_variable variable, _Token_op op) { assert(0); };
	virtual _HIR_array fold_impl_array(HIR_array* orig, List<_HIR_array_elem>* array_elems) { assert(0); };
	virtual _HIR_array_elem fold_impl_array_elem(HIR_array_elem* orig, _HIR_expr key, bool is_ref, _HIR_expr val) { assert(0); };
	virtual _HIR_method_invocation fold_impl_method_invocation(HIR_method_invocation* orig, _HIR_target target, _HIR_method_name method_name, List<_HIR_actual_parameter>* actual_parameters) { assert(0); };
	virtual _HIR_actual_parameter fold_impl_actual_parameter(HIR_actual_parameter* orig, bool is_ref, _HIR_expr expr) { assert(0); };
	virtual _HIR_new fold_impl_new(HIR_new* orig, _HIR_class_name class_name, List<_HIR_actual_parameter>* actual_parameters) { assert(0); };

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
	virtual _HIR_node fold_node(HIR_node* in)
	{
		switch(in->classid())
		{
			case HIR_php_script::ID:
				return fold_php_script(dynamic_cast<HIR_php_script*>(in));
			case HIR_class_mod::ID:
				return fold_class_mod(dynamic_cast<HIR_class_mod*>(in));
			case HIR_signature::ID:
				return fold_signature(dynamic_cast<HIR_signature*>(in));
			case HIR_method_mod::ID:
				return fold_method_mod(dynamic_cast<HIR_method_mod*>(in));
			case HIR_formal_parameter::ID:
				return fold_formal_parameter(dynamic_cast<HIR_formal_parameter*>(in));
			case HIR_type::ID:
				return fold_type(dynamic_cast<HIR_type*>(in));
			case HIR_attr_mod::ID:
				return fold_attr_mod(dynamic_cast<HIR_attr_mod*>(in));
			case HIR_directive::ID:
				return fold_directive(dynamic_cast<HIR_directive*>(in));
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_nested_list_elements::ID:
				return fold_nested_list_elements(dynamic_cast<HIR_nested_list_elements*>(in));
			case Token_variable_name::ID:
				return fold_variable_name(dynamic_cast<Token_variable_name*>(in));
			case HIR_reflection::ID:
				return fold_reflection(dynamic_cast<HIR_reflection*>(in));
			case HIR_assignment::ID:
				return fold_assignment(dynamic_cast<HIR_assignment*>(in));
			case HIR_op_assignment::ID:
				return fold_op_assignment(dynamic_cast<HIR_op_assignment*>(in));
			case HIR_list_assignment::ID:
				return fold_list_assignment(dynamic_cast<HIR_list_assignment*>(in));
			case HIR_cast::ID:
				return fold_cast(dynamic_cast<HIR_cast*>(in));
			case HIR_unary_op::ID:
				return fold_unary_op(dynamic_cast<HIR_unary_op*>(in));
			case HIR_bin_op::ID:
				return fold_bin_op(dynamic_cast<HIR_bin_op*>(in));
			case HIR_conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<HIR_conditional_expr*>(in));
			case HIR_ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<HIR_ignore_errors*>(in));
			case HIR_constant::ID:
				return fold_constant(dynamic_cast<HIR_constant*>(in));
			case HIR_instanceof::ID:
				return fold_instanceof(dynamic_cast<HIR_instanceof*>(in));
			case HIR_pre_op::ID:
				return fold_pre_op(dynamic_cast<HIR_pre_op*>(in));
			case HIR_post_op::ID:
				return fold_post_op(dynamic_cast<HIR_post_op*>(in));
			case HIR_array::ID:
				return fold_array(dynamic_cast<HIR_array*>(in));
			case HIR_method_invocation::ID:
				return fold_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
			case HIR_new::ID:
				return fold_new(dynamic_cast<HIR_new*>(in));
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
			case HIR_array_elem::ID:
				return fold_array_elem(dynamic_cast<HIR_array_elem*>(in));
			case Token_method_name::ID:
				return fold_method_name(dynamic_cast<Token_method_name*>(in));
			case HIR_actual_parameter::ID:
				return fold_actual_parameter(dynamic_cast<HIR_actual_parameter*>(in));
			case HIR_method::ID:
				return fold_method(dynamic_cast<HIR_method*>(in));
			case HIR_attribute::ID:
				return fold_attribute(dynamic_cast<HIR_attribute*>(in));
			case HIR_class_def::ID:
				return fold_class_def(dynamic_cast<HIR_class_def*>(in));
			case HIR_interface_def::ID:
				return fold_interface_def(dynamic_cast<HIR_interface_def*>(in));
			case HIR_if::ID:
				return fold_if(dynamic_cast<HIR_if*>(in));
			case HIR_while::ID:
				return fold_while(dynamic_cast<HIR_while*>(in));
			case HIR_do::ID:
				return fold_do(dynamic_cast<HIR_do*>(in));
			case HIR_for::ID:
				return fold_for(dynamic_cast<HIR_for*>(in));
			case HIR_foreach::ID:
				return fold_foreach(dynamic_cast<HIR_foreach*>(in));
			case HIR_switch::ID:
				return fold_switch(dynamic_cast<HIR_switch*>(in));
			case HIR_break::ID:
				return fold_break(dynamic_cast<HIR_break*>(in));
			case HIR_continue::ID:
				return fold_continue(dynamic_cast<HIR_continue*>(in));
			case HIR_return::ID:
				return fold_return(dynamic_cast<HIR_return*>(in));
			case HIR_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
			case HIR_global::ID:
				return fold_global(dynamic_cast<HIR_global*>(in));
			case HIR_declare::ID:
				return fold_declare(dynamic_cast<HIR_declare*>(in));
			case HIR_try::ID:
				return fold_try(dynamic_cast<HIR_try*>(in));
			case HIR_throw::ID:
				return fold_throw(dynamic_cast<HIR_throw*>(in));
			case HIR_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
			case HIR_nop::ID:
				return fold_nop(dynamic_cast<HIR_nop*>(in));
			case HIR_label::ID:
				return fold_label(dynamic_cast<HIR_label*>(in));
			case HIR_goto::ID:
				return fold_goto(dynamic_cast<HIR_goto*>(in));
			case HIR_branch::ID:
				return fold_branch(dynamic_cast<HIR_branch*>(in));
			case HIR_switch_case::ID:
				return fold_switch_case(dynamic_cast<HIR_switch_case*>(in));
			case HIR_catch::ID:
				return fold_catch(dynamic_cast<HIR_catch*>(in));
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

	virtual _HIR_statement fold_statement(HIR_statement* in)
	{
		switch(in->classid())
		{
			case HIR_class_def::ID:
				return fold_class_def(dynamic_cast<HIR_class_def*>(in));
			case HIR_interface_def::ID:
				return fold_interface_def(dynamic_cast<HIR_interface_def*>(in));
			case HIR_method::ID:
				return fold_method(dynamic_cast<HIR_method*>(in));
			case HIR_if::ID:
				return fold_if(dynamic_cast<HIR_if*>(in));
			case HIR_while::ID:
				return fold_while(dynamic_cast<HIR_while*>(in));
			case HIR_do::ID:
				return fold_do(dynamic_cast<HIR_do*>(in));
			case HIR_for::ID:
				return fold_for(dynamic_cast<HIR_for*>(in));
			case HIR_foreach::ID:
				return fold_foreach(dynamic_cast<HIR_foreach*>(in));
			case HIR_switch::ID:
				return fold_switch(dynamic_cast<HIR_switch*>(in));
			case HIR_break::ID:
				return fold_break(dynamic_cast<HIR_break*>(in));
			case HIR_continue::ID:
				return fold_continue(dynamic_cast<HIR_continue*>(in));
			case HIR_return::ID:
				return fold_return(dynamic_cast<HIR_return*>(in));
			case HIR_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
			case HIR_global::ID:
				return fold_global(dynamic_cast<HIR_global*>(in));
			case HIR_declare::ID:
				return fold_declare(dynamic_cast<HIR_declare*>(in));
			case HIR_try::ID:
				return fold_try(dynamic_cast<HIR_try*>(in));
			case HIR_throw::ID:
				return fold_throw(dynamic_cast<HIR_throw*>(in));
			case HIR_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
			case HIR_nop::ID:
				return fold_nop(dynamic_cast<HIR_nop*>(in));
			case HIR_label::ID:
				return fold_label(dynamic_cast<HIR_label*>(in));
			case HIR_goto::ID:
				return fold_goto(dynamic_cast<HIR_goto*>(in));
			case HIR_branch::ID:
				return fold_branch(dynamic_cast<HIR_branch*>(in));
		}
		assert(0);
	}

	virtual _HIR_member fold_member(HIR_member* in)
	{
		switch(in->classid())
		{
			case HIR_method::ID:
				return fold_method(dynamic_cast<HIR_method*>(in));
			case HIR_attribute::ID:
				return fold_attribute(dynamic_cast<HIR_attribute*>(in));
		}
		assert(0);
	}

	virtual _HIR_expr fold_expr(HIR_expr* in)
	{
		switch(in->classid())
		{
			case HIR_assignment::ID:
				return fold_assignment(dynamic_cast<HIR_assignment*>(in));
			case HIR_op_assignment::ID:
				return fold_op_assignment(dynamic_cast<HIR_op_assignment*>(in));
			case HIR_list_assignment::ID:
				return fold_list_assignment(dynamic_cast<HIR_list_assignment*>(in));
			case HIR_cast::ID:
				return fold_cast(dynamic_cast<HIR_cast*>(in));
			case HIR_unary_op::ID:
				return fold_unary_op(dynamic_cast<HIR_unary_op*>(in));
			case HIR_bin_op::ID:
				return fold_bin_op(dynamic_cast<HIR_bin_op*>(in));
			case HIR_conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<HIR_conditional_expr*>(in));
			case HIR_ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<HIR_ignore_errors*>(in));
			case HIR_constant::ID:
				return fold_constant(dynamic_cast<HIR_constant*>(in));
			case HIR_instanceof::ID:
				return fold_instanceof(dynamic_cast<HIR_instanceof*>(in));
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_pre_op::ID:
				return fold_pre_op(dynamic_cast<HIR_pre_op*>(in));
			case HIR_post_op::ID:
				return fold_post_op(dynamic_cast<HIR_post_op*>(in));
			case HIR_array::ID:
				return fold_array(dynamic_cast<HIR_array*>(in));
			case HIR_method_invocation::ID:
				return fold_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
			case HIR_new::ID:
				return fold_new(dynamic_cast<HIR_new*>(in));
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

	virtual _HIR_literal fold_literal(HIR_literal* in)
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

	virtual _HIR_list_element fold_list_element(HIR_list_element* in)
	{
		switch(in->classid())
		{
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_nested_list_elements::ID:
				return fold_nested_list_elements(dynamic_cast<HIR_nested_list_elements*>(in));
		}
		assert(0);
	}

	virtual _HIR_variable_name fold_variable_name(HIR_variable_name* in)
	{
		switch(in->classid())
		{
			case Token_variable_name::ID:
				return fold_variable_name(dynamic_cast<Token_variable_name*>(in));
			case HIR_reflection::ID:
				return fold_reflection(dynamic_cast<HIR_reflection*>(in));
		}
		assert(0);
	}

	virtual _HIR_target fold_target(HIR_target* in)
	{
		switch(in->classid())
		{
			case HIR_assignment::ID:
				return fold_assignment(dynamic_cast<HIR_assignment*>(in));
			case HIR_op_assignment::ID:
				return fold_op_assignment(dynamic_cast<HIR_op_assignment*>(in));
			case HIR_list_assignment::ID:
				return fold_list_assignment(dynamic_cast<HIR_list_assignment*>(in));
			case HIR_cast::ID:
				return fold_cast(dynamic_cast<HIR_cast*>(in));
			case HIR_unary_op::ID:
				return fold_unary_op(dynamic_cast<HIR_unary_op*>(in));
			case HIR_bin_op::ID:
				return fold_bin_op(dynamic_cast<HIR_bin_op*>(in));
			case HIR_conditional_expr::ID:
				return fold_conditional_expr(dynamic_cast<HIR_conditional_expr*>(in));
			case HIR_ignore_errors::ID:
				return fold_ignore_errors(dynamic_cast<HIR_ignore_errors*>(in));
			case HIR_constant::ID:
				return fold_constant(dynamic_cast<HIR_constant*>(in));
			case HIR_instanceof::ID:
				return fold_instanceof(dynamic_cast<HIR_instanceof*>(in));
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_pre_op::ID:
				return fold_pre_op(dynamic_cast<HIR_pre_op*>(in));
			case HIR_post_op::ID:
				return fold_post_op(dynamic_cast<HIR_post_op*>(in));
			case HIR_array::ID:
				return fold_array(dynamic_cast<HIR_array*>(in));
			case HIR_method_invocation::ID:
				return fold_method_invocation(dynamic_cast<HIR_method_invocation*>(in));
			case HIR_new::ID:
				return fold_new(dynamic_cast<HIR_new*>(in));
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

	virtual _HIR_method_name fold_method_name(HIR_method_name* in)
	{
		switch(in->classid())
		{
			case Token_method_name::ID:
				return fold_method_name(dynamic_cast<Token_method_name*>(in));
			case HIR_reflection::ID:
				return fold_reflection(dynamic_cast<HIR_reflection*>(in));
		}
		assert(0);
	}

	virtual _HIR_class_name fold_class_name(HIR_class_name* in)
	{
		switch(in->classid())
		{
			case Token_class_name::ID:
				return fold_class_name(dynamic_cast<Token_class_name*>(in));
			case HIR_reflection::ID:
				return fold_reflection(dynamic_cast<HIR_reflection*>(in));
		}
		assert(0);
	}

	virtual _HIR_commented_node fold_commented_node(HIR_commented_node* in)
	{
		switch(in->classid())
		{
			case HIR_method::ID:
				return fold_method(dynamic_cast<HIR_method*>(in));
			case HIR_attribute::ID:
				return fold_attribute(dynamic_cast<HIR_attribute*>(in));
			case HIR_class_def::ID:
				return fold_class_def(dynamic_cast<HIR_class_def*>(in));
			case HIR_interface_def::ID:
				return fold_interface_def(dynamic_cast<HIR_interface_def*>(in));
			case HIR_if::ID:
				return fold_if(dynamic_cast<HIR_if*>(in));
			case HIR_while::ID:
				return fold_while(dynamic_cast<HIR_while*>(in));
			case HIR_do::ID:
				return fold_do(dynamic_cast<HIR_do*>(in));
			case HIR_for::ID:
				return fold_for(dynamic_cast<HIR_for*>(in));
			case HIR_foreach::ID:
				return fold_foreach(dynamic_cast<HIR_foreach*>(in));
			case HIR_switch::ID:
				return fold_switch(dynamic_cast<HIR_switch*>(in));
			case HIR_break::ID:
				return fold_break(dynamic_cast<HIR_break*>(in));
			case HIR_continue::ID:
				return fold_continue(dynamic_cast<HIR_continue*>(in));
			case HIR_return::ID:
				return fold_return(dynamic_cast<HIR_return*>(in));
			case HIR_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
			case HIR_global::ID:
				return fold_global(dynamic_cast<HIR_global*>(in));
			case HIR_declare::ID:
				return fold_declare(dynamic_cast<HIR_declare*>(in));
			case HIR_try::ID:
				return fold_try(dynamic_cast<HIR_try*>(in));
			case HIR_throw::ID:
				return fold_throw(dynamic_cast<HIR_throw*>(in));
			case HIR_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
			case HIR_nop::ID:
				return fold_nop(dynamic_cast<HIR_nop*>(in));
			case HIR_label::ID:
				return fold_label(dynamic_cast<HIR_label*>(in));
			case HIR_goto::ID:
				return fold_goto(dynamic_cast<HIR_goto*>(in));
			case HIR_branch::ID:
				return fold_branch(dynamic_cast<HIR_branch*>(in));
			case HIR_switch_case::ID:
				return fold_switch_case(dynamic_cast<HIR_switch_case*>(in));
			case HIR_catch::ID:
				return fold_catch(dynamic_cast<HIR_catch*>(in));
		}
		assert(0);
	}

	virtual _HIR_identifier fold_identifier(HIR_identifier* in)
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
class HIR_uniform_fold : public HIR_fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T> {};
}

