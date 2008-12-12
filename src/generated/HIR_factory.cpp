#include "HIR_factory.h"

namespace HIR{
/* If type_id corresponds to an AST node, the elements in args must */
/* correspond to the children of the node. */
/*  */
/* If type_id corresponds to a list (of the form "..._list"), */
/* the elements of arg must be of the same type as the elements */
/* in the list, and all elements in args are added to the list. */
/*  */
/* If type_id corresponds to a token (terminal symbol), args must */
/* contain a single node of type String. Terminal symbols */
/* with non-default values are not supported. */
/*  */
/* If the node type is not recognized, NULL is returned. */
Object* Node_factory::create(char const* type_id, List<Object*>* args)
{
    List<Object*>::const_iterator i = args->begin();
    if(!strcmp(type_id, "PHP_script"))
    {
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new PHP_script(statements);
    }
    if(!strcmp(type_id, "Class_def"))
    {
    	Class_mod* class_mod = dynamic_cast<Class_mod*>(*i++);
    	CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(*i++);
    	CLASS_NAME* extends = dynamic_cast<CLASS_NAME*>(*i++);
    	INTERFACE_NAME_list* implements = dynamic_cast<INTERFACE_NAME_list*>(*i++);
    	Member_list* members = dynamic_cast<Member_list*>(*i++);
    	assert(i == args->end());
    	return new Class_def(class_mod, class_name, extends, implements, members);
    }
    if(!strcmp(type_id, "Class_mod"))
    {
    	bool is_abstract = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_final = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new Class_mod(is_abstract, is_final);
    }
    if(!strcmp(type_id, "Interface_def"))
    {
    	INTERFACE_NAME* interface_name = dynamic_cast<INTERFACE_NAME*>(*i++);
    	INTERFACE_NAME_list* extends = dynamic_cast<INTERFACE_NAME_list*>(*i++);
    	Member_list* members = dynamic_cast<Member_list*>(*i++);
    	assert(i == args->end());
    	return new Interface_def(interface_name, extends, members);
    }
    if(!strcmp(type_id, "Method"))
    {
    	Signature* signature = dynamic_cast<Signature*>(*i++);
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new Method(signature, statements);
    }
    if(!strcmp(type_id, "Signature"))
    {
    	Method_mod* method_mod = dynamic_cast<Method_mod*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	METHOD_NAME* method_name = dynamic_cast<METHOD_NAME*>(*i++);
    	Formal_parameter_list* formal_parameters = dynamic_cast<Formal_parameter_list*>(*i++);
    	assert(i == args->end());
    	return new Signature(method_mod, is_ref, method_name, formal_parameters);
    }
    if(!strcmp(type_id, "Method_mod"))
    {
    	bool is_public = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_protected = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_private = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_static = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_abstract = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_final = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
    }
    if(!strcmp(type_id, "Formal_parameter"))
    {
    	Type* type = dynamic_cast<Type*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Name_with_default* var = dynamic_cast<Name_with_default*>(*i++);
    	assert(i == args->end());
    	return new Formal_parameter(type, is_ref, var);
    }
    if(!strcmp(type_id, "Type"))
    {
    	CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(*i++);
    	assert(i == args->end());
    	return new Type(class_name);
    }
    if(!strcmp(type_id, "Attribute"))
    {
    	Attr_mod* attr_mod = dynamic_cast<Attr_mod*>(*i++);
    	Name_with_default* var = dynamic_cast<Name_with_default*>(*i++);
    	assert(i == args->end());
    	return new Attribute(attr_mod, var);
    }
    if(!strcmp(type_id, "Attr_mod"))
    {
    	bool is_public = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_protected = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_private = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_static = dynamic_cast<Boolean*>(*i++)->value();
    	bool is_const = dynamic_cast<Boolean*>(*i++)->value();
    	assert(i == args->end());
    	return new Attr_mod(is_public, is_protected, is_private, is_static, is_const);
    }
    if(!strcmp(type_id, "Name_with_default"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Static_value* default_value = dynamic_cast<Static_value*>(*i++);
    	assert(i == args->end());
    	return new Name_with_default(variable_name, default_value);
    }
    if(!strcmp(type_id, "If"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Statement_list* iftrue = dynamic_cast<Statement_list*>(*i++);
    	Statement_list* iffalse = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new If(variable_name, iftrue, iffalse);
    }
    if(!strcmp(type_id, "Loop"))
    {
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new Loop(statements);
    }
    if(!strcmp(type_id, "Foreach"))
    {
    	VARIABLE_NAME* arr = dynamic_cast<VARIABLE_NAME*>(*i++);
    	VARIABLE_NAME* key = dynamic_cast<VARIABLE_NAME*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	VARIABLE_NAME* val = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new Foreach(arr, key, is_ref, val, statements);
    }
    if(!strcmp(type_id, "Break"))
    {
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Break(expr);
    }
    if(!strcmp(type_id, "Continue"))
    {
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Continue(expr);
    }
    if(!strcmp(type_id, "Return"))
    {
    	Rvalue* rvalue = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Return(rvalue);
    }
    if(!strcmp(type_id, "Static_declaration"))
    {
    	Name_with_default* var = dynamic_cast<Name_with_default*>(*i++);
    	assert(i == args->end());
    	return new Static_declaration(var);
    }
    if(!strcmp(type_id, "Global"))
    {
    	Variable_name* variable_name = dynamic_cast<Variable_name*>(*i++);
    	assert(i == args->end());
    	return new Global(variable_name);
    }
    if(!strcmp(type_id, "Try"))
    {
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	Catch_list* catches = dynamic_cast<Catch_list*>(*i++);
    	assert(i == args->end());
    	return new Try(statements, catches);
    }
    if(!strcmp(type_id, "Catch"))
    {
    	CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(*i++);
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Statement_list* statements = dynamic_cast<Statement_list*>(*i++);
    	assert(i == args->end());
    	return new Catch(class_name, variable_name, statements);
    }
    if(!strcmp(type_id, "Throw"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Throw(variable_name);
    }
    if(!strcmp(type_id, "Assign_var"))
    {
    	VARIABLE_NAME* lhs = dynamic_cast<VARIABLE_NAME*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Expr* rhs = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Assign_var(lhs, is_ref, rhs);
    }
    if(!strcmp(type_id, "Assign_field"))
    {
    	Target* target = dynamic_cast<Target*>(*i++);
    	Field_name* field_name = dynamic_cast<Field_name*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Rvalue* rhs = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Assign_field(target, field_name, is_ref, rhs);
    }
    if(!strcmp(type_id, "Assign_array"))
    {
    	VARIABLE_NAME* lhs = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Rvalue* index = dynamic_cast<Rvalue*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Rvalue* rhs = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Assign_array(lhs, index, is_ref, rhs);
    }
    if(!strcmp(type_id, "Assign_var_var"))
    {
    	VARIABLE_NAME* lhs = dynamic_cast<VARIABLE_NAME*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Rvalue* rhs = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Assign_var_var(lhs, is_ref, rhs);
    }
    if(!strcmp(type_id, "Assign_next"))
    {
    	VARIABLE_NAME* lhs = dynamic_cast<VARIABLE_NAME*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Rvalue* rhs = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Assign_next(lhs, is_ref, rhs);
    }
    if(!strcmp(type_id, "Pre_op"))
    {
    	OP* op = dynamic_cast<OP*>(*i++);
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Pre_op(op, variable_name);
    }
    if(!strcmp(type_id, "Eval_expr"))
    {
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Eval_expr(expr);
    }
    if(!strcmp(type_id, "Field_access"))
    {
    	Target* target = dynamic_cast<Target*>(*i++);
    	Field_name* field_name = dynamic_cast<Field_name*>(*i++);
    	assert(i == args->end());
    	return new Field_access(target, field_name);
    }
    if(!strcmp(type_id, "Array_access"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Rvalue* index = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Array_access(variable_name, index);
    }
    if(!strcmp(type_id, "Array_next"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Array_next(variable_name);
    }
    if(!strcmp(type_id, "Cast"))
    {
    	CAST* cast = dynamic_cast<CAST*>(*i++);
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Cast(cast, variable_name);
    }
    if(!strcmp(type_id, "Unary_op"))
    {
    	OP* op = dynamic_cast<OP*>(*i++);
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Unary_op(op, variable_name);
    }
    if(!strcmp(type_id, "Bin_op"))
    {
    	Rvalue* left = dynamic_cast<Rvalue*>(*i++);
    	OP* op = dynamic_cast<OP*>(*i++);
    	Rvalue* right = dynamic_cast<Rvalue*>(*i++);
    	assert(i == args->end());
    	return new Bin_op(left, op, right);
    }
    if(!strcmp(type_id, "Constant"))
    {
    	CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(*i++);
    	CONSTANT_NAME* constant_name = dynamic_cast<CONSTANT_NAME*>(*i++);
    	assert(i == args->end());
    	return new Constant(class_name, constant_name);
    }
    if(!strcmp(type_id, "Instanceof"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Class_name* class_name = dynamic_cast<Class_name*>(*i++);
    	assert(i == args->end());
    	return new Instanceof(variable_name, class_name);
    }
    if(!strcmp(type_id, "Method_invocation"))
    {
    	Target* target = dynamic_cast<Target*>(*i++);
    	Method_name* method_name = dynamic_cast<Method_name*>(*i++);
    	Actual_parameter_list* actual_parameters = dynamic_cast<Actual_parameter_list*>(*i++);
    	assert(i == args->end());
    	return new Method_invocation(target, method_name, actual_parameters);
    }
    if(!strcmp(type_id, "New"))
    {
    	Class_name* class_name = dynamic_cast<Class_name*>(*i++);
    	Actual_parameter_list* actual_parameters = dynamic_cast<Actual_parameter_list*>(*i++);
    	assert(i == args->end());
    	return new New(class_name, actual_parameters);
    }
    if(!strcmp(type_id, "Variable_actual_parameter"))
    {
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Target* target = dynamic_cast<Target*>(*i++);
    	Variable_name* variable_name = dynamic_cast<Variable_name*>(*i++);
    	Rvalue_list* array_indices = dynamic_cast<Rvalue_list*>(*i++);
    	assert(i == args->end());
    	return new Variable_actual_parameter(is_ref, target, variable_name, array_indices);
    }
    if(!strcmp(type_id, "Variable_method"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Variable_method(variable_name);
    }
    if(!strcmp(type_id, "Variable_variable"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Variable_variable(variable_name);
    }
    if(!strcmp(type_id, "Variable_class"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Variable_class(variable_name);
    }
    if(!strcmp(type_id, "Variable_field"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Variable_field(variable_name);
    }
    if(!strcmp(type_id, "Static_array"))
    {
    	Static_array_elem_list* static_array_elems = dynamic_cast<Static_array_elem_list*>(*i++);
    	assert(i == args->end());
    	return new Static_array(static_array_elems);
    }
    if(!strcmp(type_id, "Static_array_elem"))
    {
    	Static_array_key* key = dynamic_cast<Static_array_key*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Static_value* val = dynamic_cast<Static_value*>(*i++);
    	assert(i == args->end());
    	return new Static_array_elem(key, is_ref, val);
    }
    if(!strcmp(type_id, "CLASS_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new CLASS_NAME(value);
    }
    if(!strcmp(type_id, "INTERFACE_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new INTERFACE_NAME(value);
    }
    if(!strcmp(type_id, "METHOD_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new METHOD_NAME(value);
    }
    if(!strcmp(type_id, "VARIABLE_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new VARIABLE_NAME(value);
    }
    if(!strcmp(type_id, "OP"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new OP(value);
    }
    if(!strcmp(type_id, "CAST"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new CAST(value);
    }
    if(!strcmp(type_id, "CONSTANT_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new CONSTANT_NAME(value);
    }
    if(!strcmp(type_id, "FIELD_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new FIELD_NAME(value);
    }
    if(!strcmp(type_id, "Statement_list"))
    {
    	Statement_list* list = new Statement_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Statement*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "INTERFACE_NAME_list"))
    {
    	INTERFACE_NAME_list* list = new INTERFACE_NAME_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<INTERFACE_NAME*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Member_list"))
    {
    	Member_list* list = new Member_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Member*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Formal_parameter_list"))
    {
    	Formal_parameter_list* list = new Formal_parameter_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Formal_parameter*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Catch_list"))
    {
    	Catch_list* list = new Catch_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Catch*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Actual_parameter_list"))
    {
    	Actual_parameter_list* list = new Actual_parameter_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Actual_parameter*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Rvalue_list"))
    {
    	Rvalue_list* list = new Rvalue_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Rvalue*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Static_array_elem_list"))
    {
    	Static_array_elem_list* list = new Static_array_elem_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Static_array_elem*>(*i++));
    	return list;
    }
    return NULL;
}
}

