#include "AST_factory.h"

namespace AST{
// If type_id corresponds to AST node, the elements in args must
// correspond to the children of the node.
// 
// If type_id corresponds to a list (of the form "..._list"),
// the elements of arg must be of the same type as the elements
// in the list, and all elements in args are added to the list.
// 
// If type_id corresponds to a token (terminal symbol), args must
// contain a single node of type String. Terminal symbols
// with non-default values are not supported.
Object* AST_factory::create(char const* type_id, List<Object*>* args)
{
    List<Object*>::const_iterator i = args->begin();
    if(!strcmp(type_id, "AST_php_script"))
    {
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_php_script(statements);
    }
    if(!strcmp(type_id, "AST_class_def"))
    {
    	AST_class_mod* class_mod = dynamic_cast<AST_class_mod*>(*i++);
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	Token_class_name* extends = dynamic_cast<Token_class_name*>(*i++);
    	List<Token_interface_name*>* implements = dynamic_cast<List<Token_interface_name*>*>(*i++);
    	List<AST_member*>* members = dynamic_cast<List<AST_member*>*>(*i++);
    	assert(i == args->end());
    	return new AST_class_def(class_mod, class_name, extends, implements, members);
    }
    if(!strcmp(type_id, "AST_class_mod"))
    {
    	bool is_abstract = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_final = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new AST_class_mod(is_abstract, is_final);
    }
    if(!strcmp(type_id, "AST_interface_def"))
    {
    	Token_interface_name* interface_name = dynamic_cast<Token_interface_name*>(*i++);
    	List<Token_interface_name*>* extends = dynamic_cast<List<Token_interface_name*>*>(*i++);
    	List<AST_member*>* members = dynamic_cast<List<AST_member*>*>(*i++);
    	assert(i == args->end());
    	return new AST_interface_def(interface_name, extends, members);
    }
    if(!strcmp(type_id, "AST_method"))
    {
    	AST_signature* signature = dynamic_cast<AST_signature*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_method(signature, statements);
    }
    if(!strcmp(type_id, "AST_signature"))
    {
    	AST_method_mod* method_mod = dynamic_cast<AST_method_mod*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Token_method_name* method_name = dynamic_cast<Token_method_name*>(*i++);
    	List<AST_formal_parameter*>* formal_parameters = dynamic_cast<List<AST_formal_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new AST_signature(method_mod, is_ref, method_name, formal_parameters);
    }
    if(!strcmp(type_id, "AST_method_mod"))
    {
    	bool is_public = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_protected = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_private = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_static = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_abstract = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_final = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new AST_method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
    }
    if(!strcmp(type_id, "AST_formal_parameter"))
    {
    	AST_type* type = dynamic_cast<AST_type*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_formal_parameter(type, is_ref, variable_name, expr);
    }
    if(!strcmp(type_id, "AST_type"))
    {
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	assert(i == args->end());
    	return new AST_type(class_name);
    }
    if(!strcmp(type_id, "AST_attribute"))
    {
    	AST_attr_mod* attr_mod = dynamic_cast<AST_attr_mod*>(*i++);
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_attribute(attr_mod, variable_name, expr);
    }
    if(!strcmp(type_id, "AST_attr_mod"))
    {
    	bool is_public = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_protected = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_private = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_static = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_const = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new AST_attr_mod(is_public, is_protected, is_private, is_static, is_const);
    }
    if(!strcmp(type_id, "AST_if"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	List<AST_statement*>* iftrue = dynamic_cast<List<AST_statement*>*>(*i++);
    	List<AST_statement*>* iffalse = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_if(expr, iftrue, iffalse);
    }
    if(!strcmp(type_id, "AST_while"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_while(expr, statements);
    }
    if(!strcmp(type_id, "AST_do"))
    {
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_do(statements, expr);
    }
    if(!strcmp(type_id, "AST_for"))
    {
    	AST_expr* init = dynamic_cast<AST_expr*>(*i++);
    	AST_expr* cond = dynamic_cast<AST_expr*>(*i++);
    	AST_expr* incr = dynamic_cast<AST_expr*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_for(init, cond, incr, statements);
    }
    if(!strcmp(type_id, "AST_foreach"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	AST_variable* key = dynamic_cast<AST_variable*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	AST_variable* val = dynamic_cast<AST_variable*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_foreach(expr, key, is_ref, val, statements);
    }
    if(!strcmp(type_id, "AST_switch"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	List<AST_switch_case*>* switch_cases = dynamic_cast<List<AST_switch_case*>*>(*i++);
    	assert(i == args->end());
    	return new AST_switch(expr, switch_cases);
    }
    if(!strcmp(type_id, "AST_switch_case"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_switch_case(expr, statements);
    }
    if(!strcmp(type_id, "AST_break"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_break(expr);
    }
    if(!strcmp(type_id, "AST_continue"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_continue(expr);
    }
    if(!strcmp(type_id, "AST_return"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_return(expr);
    }
    if(!strcmp(type_id, "AST_static_declaration"))
    {
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_static_declaration(variable_name, expr);
    }
    if(!strcmp(type_id, "AST_global"))
    {
    	AST_variable_name* variable_name = dynamic_cast<AST_variable_name*>(*i++);
    	assert(i == args->end());
    	return new AST_global(variable_name);
    }
    if(!strcmp(type_id, "AST_declare"))
    {
    	List<AST_directive*>* directives = dynamic_cast<List<AST_directive*>*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_declare(directives, statements);
    }
    if(!strcmp(type_id, "AST_directive"))
    {
    	Token_directive_name* directive_name = dynamic_cast<Token_directive_name*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_directive(directive_name, expr);
    }
    if(!strcmp(type_id, "AST_try"))
    {
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	List<AST_catch*>* catches = dynamic_cast<List<AST_catch*>*>(*i++);
    	assert(i == args->end());
    	return new AST_try(statements, catches);
    }
    if(!strcmp(type_id, "AST_catch"))
    {
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	Token_variable_name* variable_name = dynamic_cast<Token_variable_name*>(*i++);
    	List<AST_statement*>* statements = dynamic_cast<List<AST_statement*>*>(*i++);
    	assert(i == args->end());
    	return new AST_catch(class_name, variable_name, statements);
    }
    if(!strcmp(type_id, "AST_throw"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_throw(expr);
    }
    if(!strcmp(type_id, "AST_eval_expr"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_eval_expr(expr);
    }
    if(!strcmp(type_id, "AST_nop"))
    {
    	assert(i == args->end());
    	return new AST_nop();
    }
    if(!strcmp(type_id, "AST_branch"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	Token_label_name* iftrue = dynamic_cast<Token_label_name*>(*i++);
    	Token_label_name* iffalse = dynamic_cast<Token_label_name*>(*i++);
    	assert(i == args->end());
    	return new AST_branch(expr, iftrue, iffalse);
    }
    if(!strcmp(type_id, "AST_goto"))
    {
    	Token_label_name* label_name = dynamic_cast<Token_label_name*>(*i++);
    	assert(i == args->end());
    	return new AST_goto(label_name);
    }
    if(!strcmp(type_id, "AST_label"))
    {
    	Token_label_name* label_name = dynamic_cast<Token_label_name*>(*i++);
    	assert(i == args->end());
    	return new AST_label(label_name);
    }
    if(!strcmp(type_id, "AST_assignment"))
    {
    	AST_variable* variable = dynamic_cast<AST_variable*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_assignment(variable, is_ref, expr);
    }
    if(!strcmp(type_id, "AST_op_assignment"))
    {
    	AST_variable* variable = dynamic_cast<AST_variable*>(*i++);
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_op_assignment(variable, op, expr);
    }
    if(!strcmp(type_id, "AST_list_assignment"))
    {
    	List<AST_list_element*>* list_elements = dynamic_cast<List<AST_list_element*>*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_list_assignment(list_elements, expr);
    }
    if(!strcmp(type_id, "AST_nested_list_elements"))
    {
    	List<AST_list_element*>* list_elements = dynamic_cast<List<AST_list_element*>*>(*i++);
    	assert(i == args->end());
    	return new AST_nested_list_elements(list_elements);
    }
    if(!strcmp(type_id, "AST_cast"))
    {
    	Token_cast* cast = dynamic_cast<Token_cast*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_cast(cast, expr);
    }
    if(!strcmp(type_id, "AST_unary_op"))
    {
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_unary_op(op, expr);
    }
    if(!strcmp(type_id, "AST_bin_op"))
    {
    	AST_expr* left = dynamic_cast<AST_expr*>(*i++);
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	AST_expr* right = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_bin_op(left, op, right);
    }
    if(!strcmp(type_id, "AST_conditional_expr"))
    {
    	AST_expr* cond = dynamic_cast<AST_expr*>(*i++);
    	AST_expr* iftrue = dynamic_cast<AST_expr*>(*i++);
    	AST_expr* iffalse = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_conditional_expr(cond, iftrue, iffalse);
    }
    if(!strcmp(type_id, "AST_ignore_errors"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_ignore_errors(expr);
    }
    if(!strcmp(type_id, "AST_constant"))
    {
    	Token_class_name* class_name = dynamic_cast<Token_class_name*>(*i++);
    	Token_constant_name* constant_name = dynamic_cast<Token_constant_name*>(*i++);
    	assert(i == args->end());
    	return new AST_constant(class_name, constant_name);
    }
    if(!strcmp(type_id, "AST_instanceof"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	AST_class_name* class_name = dynamic_cast<AST_class_name*>(*i++);
    	assert(i == args->end());
    	return new AST_instanceof(expr, class_name);
    }
    if(!strcmp(type_id, "AST_variable"))
    {
    	AST_target* target = dynamic_cast<AST_target*>(*i++);
    	AST_variable_name* variable_name = dynamic_cast<AST_variable_name*>(*i++);
    	List<AST_expr*>* array_indices = dynamic_cast<List<AST_expr*>*>(*i++);
    	assert(i == args->end());
    	return new AST_variable(target, variable_name, array_indices);
    }
    if(!strcmp(type_id, "AST_reflection"))
    {
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_reflection(expr);
    }
    if(!strcmp(type_id, "AST_pre_op"))
    {
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	AST_variable* variable = dynamic_cast<AST_variable*>(*i++);
    	assert(i == args->end());
    	return new AST_pre_op(op, variable);
    }
    if(!strcmp(type_id, "AST_post_op"))
    {
    	AST_variable* variable = dynamic_cast<AST_variable*>(*i++);
    	Token_op* op = dynamic_cast<Token_op*>(*i++);
    	assert(i == args->end());
    	return new AST_post_op(variable, op);
    }
    if(!strcmp(type_id, "AST_array"))
    {
    	List<AST_array_elem*>* array_elems = dynamic_cast<List<AST_array_elem*>*>(*i++);
    	assert(i == args->end());
    	return new AST_array(array_elems);
    }
    if(!strcmp(type_id, "AST_array_elem"))
    {
    	AST_expr* key = dynamic_cast<AST_expr*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	AST_expr* val = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_array_elem(key, is_ref, val);
    }
    if(!strcmp(type_id, "AST_method_invocation"))
    {
    	AST_target* target = dynamic_cast<AST_target*>(*i++);
    	AST_method_name* method_name = dynamic_cast<AST_method_name*>(*i++);
    	List<AST_actual_parameter*>* actual_parameters = dynamic_cast<List<AST_actual_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new AST_method_invocation(target, method_name, actual_parameters);
    }
    if(!strcmp(type_id, "AST_actual_parameter"))
    {
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	AST_expr* expr = dynamic_cast<AST_expr*>(*i++);
    	assert(i == args->end());
    	return new AST_actual_parameter(is_ref, expr);
    }
    if(!strcmp(type_id, "AST_new"))
    {
    	AST_class_name* class_name = dynamic_cast<AST_class_name*>(*i++);
    	List<AST_actual_parameter*>* actual_parameters = dynamic_cast<List<AST_actual_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new AST_new(class_name, actual_parameters);
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
    if(!strcmp(type_id, "Token_directive_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_directive_name(value);
    }
    if(!strcmp(type_id, "Token_label_name"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new Token_label_name(value);
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
    if(!strcmp(type_id, "AST_statement_list"))
    {
    	List<AST_statement*>* list = new List<AST_statement*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_statement*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Token_interface_name_list"))
    {
    	List<Token_interface_name*>* list = new List<Token_interface_name*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Token_interface_name*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_member_list"))
    {
    	List<AST_member*>* list = new List<AST_member*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_member*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_formal_parameter_list"))
    {
    	List<AST_formal_parameter*>* list = new List<AST_formal_parameter*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_formal_parameter*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_switch_case_list"))
    {
    	List<AST_switch_case*>* list = new List<AST_switch_case*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_switch_case*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_directive_list"))
    {
    	List<AST_directive*>* list = new List<AST_directive*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_directive*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_catch_list"))
    {
    	List<AST_catch*>* list = new List<AST_catch*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_catch*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_list_element_list"))
    {
    	List<AST_list_element*>* list = new List<AST_list_element*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_list_element*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_expr_list"))
    {
    	List<AST_expr*>* list = new List<AST_expr*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_expr*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_array_elem_list"))
    {
    	List<AST_array_elem*>* list = new List<AST_array_elem*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_array_elem*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "AST_actual_parameter_list"))
    {
    	List<AST_actual_parameter*>* list = new List<AST_actual_parameter*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<AST_actual_parameter*>(*i++));
    	return list;
    }
    assert(0);
    return NULL;
}
}

