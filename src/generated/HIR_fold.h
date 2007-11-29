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
 class _HIR_name_with_default,
 class _HIR_return,
 class _HIR_static_declaration,
 class _HIR_global,
 class _HIR_try,
 class _HIR_catch,
 class _HIR_throw,
 class _HIR_eval_expr,
 class _HIR_branch,
 class _HIR_goto,
 class _HIR_label,
 class _HIR_foreach_reset,
 class _HIR_foreach_next,
 class _HIR_foreach_end,
 class _HIR_foreach_has_key,
 class _HIR_foreach_get_key,
 class _HIR_foreach_get_data,
 class _HIR_expr,
 class _HIR_literal,
 class _HIR_assignment,
 class _HIR_cast,
 class _HIR_unary_op,
 class _HIR_bin_op,
 class _HIR_constant,
 class _HIR_instanceof,
 class _HIR_variable,
 class _HIR_variable_name,
 class _HIR_reflection,
 class _HIR_target,
 class _HIR_pre_op,
 class _HIR_array,
 class _HIR_array_elem,
 class _HIR_method_invocation,
 class _HIR_method_name,
 class _HIR_actual_parameter,
 class _HIR_new,
 class _HIR_class_name,
 class _HIR_identifier,
 class _Token_class_name,
 class _Token_interface_name,
 class _Token_method_name,
 class _Token_variable_name,
 class _Token_label_name,
 class _Token_ht_iterator,
 class _Token_int,
 class _Token_real,
 class _Token_string,
 class _Token_bool,
 class _Token_null,
 class _Token_cast,
 class _Token_op,
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
		_HIR_name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_formal_parameter(in, type, is_ref, var);
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
		_HIR_name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_attribute(in, attr_mod, var);
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

	virtual _HIR_name_with_default fold_name_with_default(HIR_name_with_default* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_name_with_default(in, variable_name, expr);
	}

	virtual _HIR_return fold_return(HIR_return* in)
	{
		_HIR_expr expr = 0;
		if(in->expr != NULL) expr = fold_expr(in->expr);
		return fold_impl_return(in, expr);
	}

	virtual _HIR_static_declaration fold_static_declaration(HIR_static_declaration* in)
	{
		_HIR_name_with_default var = 0;
		if(in->var != NULL) var = fold_name_with_default(in->var);
		return fold_impl_static_declaration(in, var);
	}

	virtual _HIR_global fold_global(HIR_global* in)
	{
		_HIR_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_global(in, variable_name);
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

	virtual _HIR_foreach_reset fold_foreach_reset(HIR_foreach_reset* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Token_ht_iterator ht_iterator = 0;
		if(in->ht_iterator != NULL) ht_iterator = fold_ht_iterator(in->ht_iterator);
		return fold_impl_foreach_reset(in, variable_name, ht_iterator);
	}

	virtual _HIR_foreach_next fold_foreach_next(HIR_foreach_next* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Token_ht_iterator ht_iterator = 0;
		if(in->ht_iterator != NULL) ht_iterator = fold_ht_iterator(in->ht_iterator);
		return fold_impl_foreach_next(in, variable_name, ht_iterator);
	}

	virtual _HIR_foreach_end fold_foreach_end(HIR_foreach_end* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Token_ht_iterator ht_iterator = 0;
		if(in->ht_iterator != NULL) ht_iterator = fold_ht_iterator(in->ht_iterator);
		return fold_impl_foreach_end(in, variable_name, ht_iterator);
	}

	virtual _HIR_foreach_has_key fold_foreach_has_key(HIR_foreach_has_key* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Token_ht_iterator ht_iterator = 0;
		if(in->ht_iterator != NULL) ht_iterator = fold_ht_iterator(in->ht_iterator);
		return fold_impl_foreach_has_key(in, variable_name, ht_iterator);
	}

	virtual _HIR_foreach_get_key fold_foreach_get_key(HIR_foreach_get_key* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Token_ht_iterator ht_iterator = 0;
		if(in->ht_iterator != NULL) ht_iterator = fold_ht_iterator(in->ht_iterator);
		return fold_impl_foreach_get_key(in, variable_name, ht_iterator);
	}

	virtual _HIR_foreach_get_data fold_foreach_get_data(HIR_foreach_get_data* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_Token_ht_iterator ht_iterator = 0;
		if(in->ht_iterator != NULL) ht_iterator = fold_ht_iterator(in->ht_iterator);
		return fold_impl_foreach_get_data(in, variable_name, ht_iterator);
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

	virtual _HIR_cast fold_cast(HIR_cast* in)
	{
		_Token_cast cast = 0;
		if(in->cast != NULL) cast = fold_cast(in->cast);
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_cast(in, cast, variable_name);
	}

	virtual _HIR_unary_op fold_unary_op(HIR_unary_op* in)
	{
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_unary_op(in, op, variable_name);
	}

	virtual _HIR_bin_op fold_bin_op(HIR_bin_op* in)
	{
		_Token_variable_name left = 0;
		if(in->left != NULL) left = fold_variable_name(in->left);
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_Token_variable_name right = 0;
		if(in->right != NULL) right = fold_variable_name(in->right);
		return fold_impl_bin_op(in, left, op, right);
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
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		_HIR_class_name class_name = 0;
		if(in->class_name != NULL) class_name = fold_class_name(in->class_name);
		return fold_impl_instanceof(in, variable_name, class_name);
	}

	virtual _HIR_variable fold_variable(HIR_variable* in)
	{
		_HIR_target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_HIR_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_Token_variable_name>* array_indices = new List<_Token_variable_name>;
		{
			List<Token_variable_name*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_variable_name(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_variable(in, target, variable_name, array_indices);
	}

	virtual _HIR_reflection fold_reflection(HIR_reflection* in)
	{
		_Token_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		return fold_impl_reflection(in, variable_name);
	}

	virtual _HIR_pre_op fold_pre_op(HIR_pre_op* in)
	{
		_Token_op op = 0;
		if(in->op != NULL) op = fold_op(in->op);
		_HIR_variable variable = 0;
		if(in->variable != NULL) variable = fold_variable(in->variable);
		return fold_impl_pre_op(in, op, variable);
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
		_HIR_target target = 0;
		if(in->target != NULL) target = fold_target(in->target);
		_HIR_variable_name variable_name = 0;
		if(in->variable_name != NULL) variable_name = fold_variable_name(in->variable_name);
		List<_Token_variable_name>* array_indices = new List<_Token_variable_name>;
		{
			List<Token_variable_name*>::const_iterator i;
			for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
				if(*i != NULL) array_indices->push_back(fold_variable_name(*i));
				else array_indices->push_back(0);
		}
		return fold_impl_actual_parameter(in, is_ref, target, variable_name, array_indices);
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
	virtual _HIR_formal_parameter fold_impl_formal_parameter(HIR_formal_parameter* orig, _HIR_type type, bool is_ref, _HIR_name_with_default var) { assert(0); };
	virtual _HIR_type fold_impl_type(HIR_type* orig, _Token_class_name class_name) { assert(0); };
	virtual _HIR_attribute fold_impl_attribute(HIR_attribute* orig, _HIR_attr_mod attr_mod, _HIR_name_with_default var) { assert(0); };
	virtual _HIR_attr_mod fold_impl_attr_mod(HIR_attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) { assert(0); };
	virtual _HIR_name_with_default fold_impl_name_with_default(HIR_name_with_default* orig, _Token_variable_name variable_name, _HIR_expr expr) { assert(0); };
	virtual _HIR_return fold_impl_return(HIR_return* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_static_declaration fold_impl_static_declaration(HIR_static_declaration* orig, _HIR_name_with_default var) { assert(0); };
	virtual _HIR_global fold_impl_global(HIR_global* orig, _HIR_variable_name variable_name) { assert(0); };
	virtual _HIR_try fold_impl_try(HIR_try* orig, List<_HIR_statement>* statements, List<_HIR_catch>* catches) { assert(0); };
	virtual _HIR_catch fold_impl_catch(HIR_catch* orig, _Token_class_name class_name, _Token_variable_name variable_name, List<_HIR_statement>* statements) { assert(0); };
	virtual _HIR_throw fold_impl_throw(HIR_throw* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_eval_expr fold_impl_eval_expr(HIR_eval_expr* orig, _HIR_expr expr) { assert(0); };
	virtual _HIR_branch fold_impl_branch(HIR_branch* orig, _HIR_expr expr, _Token_label_name iftrue, _Token_label_name iffalse) { assert(0); };
	virtual _HIR_goto fold_impl_goto(HIR_goto* orig, _Token_label_name label_name) { assert(0); };
	virtual _HIR_label fold_impl_label(HIR_label* orig, _Token_label_name label_name) { assert(0); };
	virtual _HIR_foreach_reset fold_impl_foreach_reset(HIR_foreach_reset* orig, _Token_variable_name variable_name, _Token_ht_iterator ht_iterator) { assert(0); };
	virtual _HIR_foreach_next fold_impl_foreach_next(HIR_foreach_next* orig, _Token_variable_name variable_name, _Token_ht_iterator ht_iterator) { assert(0); };
	virtual _HIR_foreach_end fold_impl_foreach_end(HIR_foreach_end* orig, _Token_variable_name variable_name, _Token_ht_iterator ht_iterator) { assert(0); };
	virtual _HIR_foreach_has_key fold_impl_foreach_has_key(HIR_foreach_has_key* orig, _Token_variable_name variable_name, _Token_ht_iterator ht_iterator) { assert(0); };
	virtual _HIR_foreach_get_key fold_impl_foreach_get_key(HIR_foreach_get_key* orig, _Token_variable_name variable_name, _Token_ht_iterator ht_iterator) { assert(0); };
	virtual _HIR_foreach_get_data fold_impl_foreach_get_data(HIR_foreach_get_data* orig, _Token_variable_name variable_name, _Token_ht_iterator ht_iterator) { assert(0); };
	virtual _HIR_assignment fold_impl_assignment(HIR_assignment* orig, _HIR_variable variable, bool is_ref, _HIR_expr expr) { assert(0); };
	virtual _HIR_cast fold_impl_cast(HIR_cast* orig, _Token_cast cast, _Token_variable_name variable_name) { assert(0); };
	virtual _HIR_unary_op fold_impl_unary_op(HIR_unary_op* orig, _Token_op op, _Token_variable_name variable_name) { assert(0); };
	virtual _HIR_bin_op fold_impl_bin_op(HIR_bin_op* orig, _Token_variable_name left, _Token_op op, _Token_variable_name right) { assert(0); };
	virtual _HIR_constant fold_impl_constant(HIR_constant* orig, _Token_class_name class_name, _Token_constant_name constant_name) { assert(0); };
	virtual _HIR_instanceof fold_impl_instanceof(HIR_instanceof* orig, _Token_variable_name variable_name, _HIR_class_name class_name) { assert(0); };
	virtual _HIR_variable fold_impl_variable(HIR_variable* orig, _HIR_target target, _HIR_variable_name variable_name, List<_Token_variable_name>* array_indices) { assert(0); };
	virtual _HIR_reflection fold_impl_reflection(HIR_reflection* orig, _Token_variable_name variable_name) { assert(0); };
	virtual _HIR_pre_op fold_impl_pre_op(HIR_pre_op* orig, _Token_op op, _HIR_variable variable) { assert(0); };
	virtual _HIR_array fold_impl_array(HIR_array* orig, List<_HIR_array_elem>* array_elems) { assert(0); };
	virtual _HIR_array_elem fold_impl_array_elem(HIR_array_elem* orig, _HIR_expr key, bool is_ref, _HIR_expr val) { assert(0); };
	virtual _HIR_method_invocation fold_impl_method_invocation(HIR_method_invocation* orig, _HIR_target target, _HIR_method_name method_name, List<_HIR_actual_parameter>* actual_parameters) { assert(0); };
	virtual _HIR_actual_parameter fold_impl_actual_parameter(HIR_actual_parameter* orig, bool is_ref, _HIR_target target, _HIR_variable_name variable_name, List<_Token_variable_name>* array_indices) { assert(0); };
	virtual _HIR_new fold_impl_new(HIR_new* orig, _HIR_class_name class_name, List<_HIR_actual_parameter>* actual_parameters) { assert(0); };

	virtual _Token_class_name fold_class_name(Token_class_name* orig) { assert(0); };
	virtual _Token_interface_name fold_interface_name(Token_interface_name* orig) { assert(0); };
	virtual _Token_method_name fold_method_name(Token_method_name* orig) { assert(0); };
	virtual _Token_variable_name fold_variable_name(Token_variable_name* orig) { assert(0); };
	virtual _Token_label_name fold_label_name(Token_label_name* orig) { assert(0); };
	virtual _Token_ht_iterator fold_ht_iterator(Token_ht_iterator* orig) { assert(0); };
	virtual _Token_int fold_int(Token_int* orig) { assert(0); };
	virtual _Token_real fold_real(Token_real* orig) { assert(0); };
	virtual _Token_string fold_string(Token_string* orig) { assert(0); };
	virtual _Token_bool fold_bool(Token_bool* orig) { assert(0); };
	virtual _Token_null fold_null(Token_null* orig) { assert(0); };
	virtual _Token_cast fold_cast(Token_cast* orig) { assert(0); };
	virtual _Token_op fold_op(Token_op* orig) { assert(0); };
	virtual _Token_constant_name fold_constant_name(Token_constant_name* orig) { assert(0); };


// Manual dispatching for abstract classes
// Override only if you know what you are doing!
	virtual _HIR_node fold_node(HIR_node* in)
	{
		switch(in->classid())
		{
			case HIR_php_script::ID:
				return fold_php_script(dynamic_cast<HIR_php_script*>(in));
			case HIR_class_def::ID:
				return fold_class_def(dynamic_cast<HIR_class_def*>(in));
			case HIR_interface_def::ID:
				return fold_interface_def(dynamic_cast<HIR_interface_def*>(in));
			case HIR_method::ID:
				return fold_method(dynamic_cast<HIR_method*>(in));
			case HIR_return::ID:
				return fold_return(dynamic_cast<HIR_return*>(in));
			case HIR_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
			case HIR_global::ID:
				return fold_global(dynamic_cast<HIR_global*>(in));
			case HIR_try::ID:
				return fold_try(dynamic_cast<HIR_try*>(in));
			case HIR_throw::ID:
				return fold_throw(dynamic_cast<HIR_throw*>(in));
			case HIR_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
			case HIR_label::ID:
				return fold_label(dynamic_cast<HIR_label*>(in));
			case HIR_goto::ID:
				return fold_goto(dynamic_cast<HIR_goto*>(in));
			case HIR_branch::ID:
				return fold_branch(dynamic_cast<HIR_branch*>(in));
			case HIR_foreach_next::ID:
				return fold_foreach_next(dynamic_cast<HIR_foreach_next*>(in));
			case HIR_foreach_reset::ID:
				return fold_foreach_reset(dynamic_cast<HIR_foreach_reset*>(in));
			case HIR_foreach_end::ID:
				return fold_foreach_end(dynamic_cast<HIR_foreach_end*>(in));
			case HIR_class_mod::ID:
				return fold_class_mod(dynamic_cast<HIR_class_mod*>(in));
			case HIR_attribute::ID:
				return fold_attribute(dynamic_cast<HIR_attribute*>(in));
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
			case HIR_name_with_default::ID:
				return fold_name_with_default(dynamic_cast<HIR_name_with_default*>(in));
			case HIR_catch::ID:
				return fold_catch(dynamic_cast<HIR_catch*>(in));
			case Token_variable_name::ID:
				return fold_variable_name(dynamic_cast<Token_variable_name*>(in));
			case HIR_reflection::ID:
				return fold_reflection(dynamic_cast<HIR_reflection*>(in));
			case HIR_assignment::ID:
				return fold_assignment(dynamic_cast<HIR_assignment*>(in));
			case HIR_cast::ID:
				return fold_cast(dynamic_cast<HIR_cast*>(in));
			case HIR_unary_op::ID:
				return fold_unary_op(dynamic_cast<HIR_unary_op*>(in));
			case HIR_bin_op::ID:
				return fold_bin_op(dynamic_cast<HIR_bin_op*>(in));
			case HIR_constant::ID:
				return fold_constant(dynamic_cast<HIR_constant*>(in));
			case HIR_instanceof::ID:
				return fold_instanceof(dynamic_cast<HIR_instanceof*>(in));
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_pre_op::ID:
				return fold_pre_op(dynamic_cast<HIR_pre_op*>(in));
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
			case HIR_foreach_has_key::ID:
				return fold_foreach_has_key(dynamic_cast<HIR_foreach_has_key*>(in));
			case HIR_foreach_get_key::ID:
				return fold_foreach_get_key(dynamic_cast<HIR_foreach_get_key*>(in));
			case HIR_foreach_get_data::ID:
				return fold_foreach_get_data(dynamic_cast<HIR_foreach_get_data*>(in));
			case HIR_array::ID:
				return fold_array(dynamic_cast<HIR_array*>(in));
			case Token_class_name::ID:
				return fold_class_name(dynamic_cast<Token_class_name*>(in));
			case HIR_array_elem::ID:
				return fold_array_elem(dynamic_cast<HIR_array_elem*>(in));
			case Token_method_name::ID:
				return fold_method_name(dynamic_cast<Token_method_name*>(in));
			case HIR_actual_parameter::ID:
				return fold_actual_parameter(dynamic_cast<HIR_actual_parameter*>(in));
			case Token_interface_name::ID:
				return fold_interface_name(dynamic_cast<Token_interface_name*>(in));
			case Token_cast::ID:
				return fold_cast(dynamic_cast<Token_cast*>(in));
			case Token_op::ID:
				return fold_op(dynamic_cast<Token_op*>(in));
			case Token_constant_name::ID:
				return fold_constant_name(dynamic_cast<Token_constant_name*>(in));
			case Token_label_name::ID:
				return fold_label_name(dynamic_cast<Token_label_name*>(in));
			case Token_ht_iterator::ID:
				return fold_ht_iterator(dynamic_cast<Token_ht_iterator*>(in));
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
			case HIR_return::ID:
				return fold_return(dynamic_cast<HIR_return*>(in));
			case HIR_static_declaration::ID:
				return fold_static_declaration(dynamic_cast<HIR_static_declaration*>(in));
			case HIR_global::ID:
				return fold_global(dynamic_cast<HIR_global*>(in));
			case HIR_try::ID:
				return fold_try(dynamic_cast<HIR_try*>(in));
			case HIR_throw::ID:
				return fold_throw(dynamic_cast<HIR_throw*>(in));
			case HIR_eval_expr::ID:
				return fold_eval_expr(dynamic_cast<HIR_eval_expr*>(in));
			case HIR_label::ID:
				return fold_label(dynamic_cast<HIR_label*>(in));
			case HIR_goto::ID:
				return fold_goto(dynamic_cast<HIR_goto*>(in));
			case HIR_branch::ID:
				return fold_branch(dynamic_cast<HIR_branch*>(in));
			case HIR_foreach_next::ID:
				return fold_foreach_next(dynamic_cast<HIR_foreach_next*>(in));
			case HIR_foreach_reset::ID:
				return fold_foreach_reset(dynamic_cast<HIR_foreach_reset*>(in));
			case HIR_foreach_end::ID:
				return fold_foreach_end(dynamic_cast<HIR_foreach_end*>(in));
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
			case HIR_cast::ID:
				return fold_cast(dynamic_cast<HIR_cast*>(in));
			case HIR_unary_op::ID:
				return fold_unary_op(dynamic_cast<HIR_unary_op*>(in));
			case HIR_bin_op::ID:
				return fold_bin_op(dynamic_cast<HIR_bin_op*>(in));
			case HIR_constant::ID:
				return fold_constant(dynamic_cast<HIR_constant*>(in));
			case HIR_instanceof::ID:
				return fold_instanceof(dynamic_cast<HIR_instanceof*>(in));
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_pre_op::ID:
				return fold_pre_op(dynamic_cast<HIR_pre_op*>(in));
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
			case HIR_foreach_has_key::ID:
				return fold_foreach_has_key(dynamic_cast<HIR_foreach_has_key*>(in));
			case HIR_foreach_get_key::ID:
				return fold_foreach_get_key(dynamic_cast<HIR_foreach_get_key*>(in));
			case HIR_foreach_get_data::ID:
				return fold_foreach_get_data(dynamic_cast<HIR_foreach_get_data*>(in));
			case HIR_array::ID:
				return fold_array(dynamic_cast<HIR_array*>(in));
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
			case HIR_cast::ID:
				return fold_cast(dynamic_cast<HIR_cast*>(in));
			case HIR_unary_op::ID:
				return fold_unary_op(dynamic_cast<HIR_unary_op*>(in));
			case HIR_bin_op::ID:
				return fold_bin_op(dynamic_cast<HIR_bin_op*>(in));
			case HIR_constant::ID:
				return fold_constant(dynamic_cast<HIR_constant*>(in));
			case HIR_instanceof::ID:
				return fold_instanceof(dynamic_cast<HIR_instanceof*>(in));
			case HIR_variable::ID:
				return fold_variable(dynamic_cast<HIR_variable*>(in));
			case HIR_pre_op::ID:
				return fold_pre_op(dynamic_cast<HIR_pre_op*>(in));
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
			case HIR_foreach_has_key::ID:
				return fold_foreach_has_key(dynamic_cast<HIR_foreach_has_key*>(in));
			case HIR_foreach_get_key::ID:
				return fold_foreach_get_key(dynamic_cast<HIR_foreach_get_key*>(in));
			case HIR_foreach_get_data::ID:
				return fold_foreach_get_data(dynamic_cast<HIR_foreach_get_data*>(in));
			case HIR_array::ID:
				return fold_array(dynamic_cast<HIR_array*>(in));
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
			case Token_cast::ID:
				return fold_cast(dynamic_cast<Token_cast*>(in));
			case Token_op::ID:
				return fold_op(dynamic_cast<Token_op*>(in));
			case Token_constant_name::ID:
				return fold_constant_name(dynamic_cast<Token_constant_name*>(in));
			case Token_label_name::ID:
				return fold_label_name(dynamic_cast<Token_label_name*>(in));
			case Token_ht_iterator::ID:
				return fold_ht_iterator(dynamic_cast<Token_ht_iterator*>(in));
		}
		assert(0);
	}



// Virtual destructor to avoid compiler warnings
	virtual ~HIR_fold() {}
};

template<class T>
class HIR_uniform_fold : public HIR_fold<T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T> {};
}

