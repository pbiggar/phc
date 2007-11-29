#include "HIR_factory.h"

namespace HIR{
// If type_id corresponds to HIR node, the elements in args must
// correspond to the children of the node.
// 
// If type_id corresponds to a list (of the form "..._list"),
// the elements of arg must be of the same type as the elements
// in the list, and all elements in args are added to the list.
// 
// If type_id corresponds to a token (terminal symbol), args must
// contain a single node of type String. Terminal symbols
// with non-default values are not supported.
Object* HIR_factory::create(char const* type_id, List<Object*>* args)
{
    List<Object*>::const_iterator i = args->begin();
    if(!strcmp(type_id, "HIR_php_script"))
    {
    	List<HIR_statement*>* statements = dynamic_cast<List<HIR_statement*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_php_script(statements);
    }
    if(!strcmp(type_id, "HIR_class_def"))
    {
    	HIR_class_mod* class_mod = dynamic_cast<HIR_class_mod*>(*i++);
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	Token_class_name* extends = dynamic_cast<Token_class_name*>(*i++);
    	List<Token_interface_name*>* implements = dynamic_cast<List<Token_interface_name*>*>(*i++);
    	List<HIR_member*>* members = dynamic_cast<List<HIR_member*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_class_def(class_mod, class_name, extends, implements, members);
    }
    if(!strcmp(type_id, "HIR_class_mod"))
    {
    	bool is_abstract = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_final = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new HIR_class_mod(is_abstract, is_final);
    }
    if(!strcmp(type_id, "HIR_interface_def"))
    {
    	Token_interface_name* interface_name = dynamic_cast<Token_interface_name*>(*i++);
    	List<Token_interface_name*>* extends = dynamic_cast<List<Token_interface_name*>*>(*i++);
    	List<HIR_member*>* members = dynamic_cast<List<HIR_member*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_interface_def(interface_name, extends, members);
    }
    if(!strcmp(type_id, "HIR_method"))
    {
    	HIR_signature* signature = dynamic_cast<HIR_signature*>(*i++);
    	List<HIR_statement*>* statements = dynamic_cast<List<HIR_statement*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_method(signature, statements);
    }
    if(!strcmp(type_id, "HIR_signature"))
    {
    	HIR_method_mod* method_mod = dynamic_cast<HIR_method_mod*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Token_method_name* method_name = dynamic_cast<Token_method_name*>(*i++);
    	List<HIR_formal_parameter*>* formal_parameters = dynamic_cast<List<HIR_formal_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_signature(method_mod, is_ref, method_name, formal_parameters);
    }
    if(!strcmp(type_id, "HIR_method_mod"))
    {
    	bool is_public = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_protected = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_private = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_static = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_abstract = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_final = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new HIR_method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
    }
    if(!strcmp(type_id, "HIR_formal_parameter"))
    {
    	HIR_type* type = dynamic_cast<HIR_type*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	HIR_name_with_default* var = dynamic_cast<HIR_name_with_default*>(*i++);
    	assert(i == args->end());
    	return new HIR_formal_parameter(type, is_ref, var);
    }
    if(!strcmp(type_id, "HIR_type"))
    {
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_type(class_name);
    }
    if(!strcmp(type_id, "HIR_attribute"))
    {
    	HIR_attr_mod* attr_mod = dynamic_cast<HIR_attr_mod*>(*i++);
    	HIR_name_with_default* var = dynamic_cast<HIR_name_with_default*>(*i++);
    	assert(i == args->end());
    	return new HIR_attribute(attr_mod, var);
    }
    if(!strcmp(type_id, "HIR_attr_mod"))
    {
    	bool is_public = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_protected = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_private = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_static = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_const = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new HIR_attr_mod(is_public, is_protected, is_private, is_static, is_const);
    }
    if(!strcmp(type_id, "HIR_name_with_default"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	HIR_expr* expr = dynamic_cast<HIR_expr*>(*i++);
    	assert(i == args->end());
    	return new HIR_name_with_default(variable_name, expr);
    }
    if(!strcmp(type_id, "HIR_return"))
    {
    	HIR_expr* expr = dynamic_cast<HIR_expr*>(*i++);
    	assert(i == args->end());
    	return new HIR_return(expr);
    }
    if(!strcmp(type_id, "HIR_static_declaration"))
    {
    	HIR_name_with_default* var = dynamic_cast<HIR_name_with_default*>(*i++);
    	assert(i == args->end());
    	return new HIR_static_declaration(var);
    }
    if(!strcmp(type_id, "HIR_global"))
    {
    	HIR_variable_name* variable_name = dynamic_cast<HIR_variable_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_global(variable_name);
    }
    if(!strcmp(type_id, "HIR_try"))
    {
    	List<HIR_statement*>* statements = dynamic_cast<List<HIR_statement*>*>(*i++);
    	List<HIR_catch*>* catches = dynamic_cast<List<HIR_catch*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_try(statements, catches);
    }
    if(!strcmp(type_id, "HIR_catch"))
    {
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	List<HIR_statement*>* statements = dynamic_cast<List<HIR_statement*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_catch(class_name, variable_name, statements);
    }
    if(!strcmp(type_id, "HIR_throw"))
    {
    	HIR_expr* expr = dynamic_cast<HIR_expr*>(*i++);
    	assert(i == args->end());
    	return new HIR_throw(expr);
    }
    if(!strcmp(type_id, "HIR_eval_expr"))
    {
    	HIR_expr* expr = dynamic_cast<HIR_expr*>(*i++);
    	assert(i == args->end());
    	return new HIR_eval_expr(expr);
    }
    if(!strcmp(type_id, "HIR_branch"))
    {
    	HIR_expr* expr = dynamic_cast<HIR_expr*>(*i++);
    	Token_label_name* iftrue = dynamic_cast<Token_label_name*>(*i++);
    	Token_label_name* iffalse = dynamic_cast<Token_label_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_branch(expr, iftrue, iffalse);
    }
    if(!strcmp(type_id, "HIR_goto"))
    {
    	Token_label_name* label_name = dynamic_cast<Token_label_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_goto(label_name);
    }
    if(!strcmp(type_id, "HIR_label"))
    {
    	Token_label_name* label_name = dynamic_cast<Token_label_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_label(label_name);
    }
    if(!strcmp(type_id, "HIR_foreach_reset"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	Token_ht_iterator* ht_iterator = dynamic_cast<Token_ht_iterator*>(*i++);
    	assert(i == args->end());
    	return new HIR_foreach_reset(variable_name, ht_iterator);
    }
    if(!strcmp(type_id, "HIR_foreach_next"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	Token_ht_iterator* ht_iterator = dynamic_cast<Token_ht_iterator*>(*i++);
    	assert(i == args->end());
    	return new HIR_foreach_next(variable_name, ht_iterator);
    }
    if(!strcmp(type_id, "HIR_foreach_end"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	Token_ht_iterator* ht_iterator = dynamic_cast<Token_ht_iterator*>(*i++);
    	assert(i == args->end());
    	return new HIR_foreach_end(variable_name, ht_iterator);
    }
    if(!strcmp(type_id, "HIR_foreach_has_key"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	Token_ht_iterator* ht_iterator = dynamic_cast<Token_ht_iterator*>(*i++);
    	assert(i == args->end());
    	return new HIR_foreach_has_key(variable_name, ht_iterator);
    }
    if(!strcmp(type_id, "HIR_foreach_get_key"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	Token_ht_iterator* ht_iterator = dynamic_cast<Token_ht_iterator*>(*i++);
    	assert(i == args->end());
    	return new HIR_foreach_get_key(variable_name, ht_iterator);
    }
    if(!strcmp(type_id, "HIR_foreach_get_data"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	Token_ht_iterator* ht_iterator = dynamic_cast<Token_ht_iterator*>(*i++);
    	assert(i == args->end());
    	return new HIR_foreach_get_data(variable_name, ht_iterator);
    }
    if(!strcmp(type_id, "HIR_assignment"))
    {
    	HIR_variable* variable = dynamic_cast<HIR_variable*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	HIR_expr* expr = dynamic_cast<HIR_expr*>(*i++);
    	assert(i == args->end());
    	return new HIR_assignment(variable, is_ref, expr);
    }
    if(!strcmp(type_id, "HIR_cast"))
    {
    	Token_cast* cast = dynamic_cast<Token_cast*>(*i++);
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_cast(cast, variable_name);
    }
    if(!strcmp(type_id, "HIR_unary_op"))
    {
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_unary_op(op, variable_name);
    }
    if(!strcmp(type_id, "HIR_bin_op"))
    {
    	Token_variable_name* left = dynamic_cast<Token_variable_name*>(*i++);
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	Token_variable_name* right = dynamic_cast<Token_variable_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_bin_op(left, op, right);
    }
    if(!strcmp(type_id, "HIR_constant"))
    {
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	Token_constant_name* constant_name = dynamic_cast<Token_constant_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_constant(class_name, constant_name);
    }
    if(!strcmp(type_id, "HIR_instanceof"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	HIR_class_name* class_name = dynamic_cast<HIR_class_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_instanceof(variable_name, class_name);
    }
    if(!strcmp(type_id, "HIR_variable"))
    {
    	HIR_target* target = dynamic_cast<HIR_target*>(*i++);
    	HIR_variable_name* variable_name = dynamic_cast<HIR_variable_name*>(*i++);
    	List<Token_variable_name*>* array_indices = dynamic_cast<List<Token_variable_name*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_variable(target, variable_name, array_indices);
    }
    if(!strcmp(type_id, "HIR_reflection"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	assert(i == args->end());
    	return new HIR_reflection(variable_name);
    }
    if(!strcmp(type_id, "HIR_pre_op"))
    {
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	HIR_variable* variable = dynamic_cast<HIR_variable*>(*i++);
    	assert(i == args->end());
    	return new HIR_pre_op(op, variable);
    }
    if(!strcmp(type_id, "HIR_array"))
    {
    	List<HIR_array_elem*>* array_elems = dynamic_cast<List<HIR_array_elem*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_array(array_elems);
    }
    if(!strcmp(type_id, "HIR_array_elem"))
    {
    	HIR_expr* key = dynamic_cast<HIR_expr*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	HIR_expr* val = dynamic_cast<HIR_expr*>(*i++);
    	assert(i == args->end());
    	return new HIR_array_elem(key, is_ref, val);
    }
    if(!strcmp(type_id, "HIR_method_invocation"))
    {
    	HIR_target* target = dynamic_cast<HIR_target*>(*i++);
    	HIR_method_name* method_name = dynamic_cast<HIR_method_name*>(*i++);
    	List<HIR_actual_parameter*>* actual_parameters = dynamic_cast<List<HIR_actual_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_method_invocation(target, method_name, actual_parameters);
    }
    if(!strcmp(type_id, "HIR_actual_parameter"))
    {
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	HIR_target* target = dynamic_cast<HIR_target*>(*i++);
    	HIR_variable_name* variable_name = dynamic_cast<HIR_variable_name*>(*i++);
    	List<Token_variable_name*>* array_indices = dynamic_cast<List<Token_variable_name*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_actual_parameter(is_ref, target, variable_name, array_indices);
    }
    if(!strcmp(type_id, "HIR_new"))
    {
    	HIR_class_name* class_name = dynamic_cast<HIR_class_name*>(*i++);
    	List<HIR_actual_parameter*>* actual_parameters = dynamic_cast<List<HIR_actual_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new HIR_new(class_name, actual_parameters);
    }
    if(!strcmp(type_id, "Token_class_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_class_name(value);
    }
    if(!strcmp(type_id, "Token_interface_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_interface_name(value);
    }
    if(!strcmp(type_id, "Token_method_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_method_name(value);
    }
    if(!strcmp(type_id, "Token_variable_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_variable_name(value);
    }
    if(!strcmp(type_id, "Token_label_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_label_name(value);
    }
    if(!strcmp(type_id, "Token_ht_iterator"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_ht_iterator(value);
    }
    if(!strcmp(type_id, "Token_cast"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_cast(value);
    }
    if(!strcmp(type_id, "Token_op"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_op(value);
    }
    if(!strcmp(type_id, "Token_constant_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_constant_name(value);
    }
    if(!strcmp(type_id, "HIR_statement_list"))
    {
    	List<HIR_statement*>* list = new List<HIR_statement*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<HIR_statement*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Token_interface_name_list"))
    {
    	List<Token_interface_name*>* list = new List<Token_interface_name*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Token_interface_name*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "HIR_member_list"))
    {
    	List<HIR_member*>* list = new List<HIR_member*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<HIR_member*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "HIR_formal_parameter_list"))
    {
    	List<HIR_formal_parameter*>* list = new List<HIR_formal_parameter*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<HIR_formal_parameter*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "HIR_catch_list"))
    {
    	List<HIR_catch*>* list = new List<HIR_catch*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<HIR_catch*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Token_variable_name_list"))
    {
    	List<Token_variable_name*>* list = new List<Token_variable_name*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Token_variable_name*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "HIR_array_elem_list"))
    {
    	List<HIR_array_elem*>* list = new List<HIR_array_elem*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<HIR_array_elem*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "HIR_actual_parameter_list"))
    {
    	List<HIR_actual_parameter*>* list = new List<HIR_actual_parameter*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<HIR_actual_parameter*>(*i++));
    	return list;
    }
    assert(0);
    return NULL;
}
}

