#include "HIR_factory.h"

namespace HIR{
// If type_id corresponds to an AST node, the elements in args must
// correspond to the children of the node.
// 
// If type_id corresponds to a list (of the form "..._list"),
// the elements of arg must be of the same type as the elements
// in the list, and all elements in args are added to the list.
// 
// If type_id corresponds to a token (terminal symbol), args must
// contain a single node of type String. Terminal symbols
// with non-default values are not supported.
// 
// If the node type is not recognized, NULL is returned.
Object* Node_factory::create(char const* type_id, List<Object*>* args)
{
    List<Object*>::const_iterator i = args->begin();
    if(!strcmp(type_id, "PHP_script"))
    {
    	List<Statement*>* statements = dynamic_cast<List<Statement*>*>(*i++);
    	assert(i == args->end());
    	return new PHP_script(statements);
    }
    if(!strcmp(type_id, "Class_def"))
    {
    	Class_mod* class_mod = dynamic_cast<Class_mod*>(*i++);
    	CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(*i++);
    	CLASS_NAME* extends = dynamic_cast<CLASS_NAME*>(*i++);
    	List<INTERFACE_NAME*>* implements = dynamic_cast<List<INTERFACE_NAME*>*>(*i++);
    	List<Member*>* members = dynamic_cast<List<Member*>*>(*i++);
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
    	List<INTERFACE_NAME*>* extends = dynamic_cast<List<INTERFACE_NAME*>*>(*i++);
    	List<Member*>* members = dynamic_cast<List<Member*>*>(*i++);
    	assert(i == args->end());
    	return new Interface_def(interface_name, extends, members);
    }
    if(!strcmp(type_id, "Method"))
    {
    	Signature* signature = dynamic_cast<Signature*>(*i++);
    	List<Statement*>* statements = dynamic_cast<List<Statement*>*>(*i++);
    	assert(i == args->end());
    	return new Method(signature, statements);
    }
    if(!strcmp(type_id, "Signature"))
    {
    	Method_mod* method_mod = dynamic_cast<Method_mod*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	METHOD_NAME* method_name = dynamic_cast<METHOD_NAME*>(*i++);
    	List<Formal_parameter*>* formal_parameters = dynamic_cast<List<Formal_parameter*>*>(*i++);
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
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Name_with_default(variable_name, expr);
    }
    if(!strcmp(type_id, "If"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	List<Statement*>* iftrue = dynamic_cast<List<Statement*>*>(*i++);
    	List<Statement*>* iffalse = dynamic_cast<List<Statement*>*>(*i++);
    	assert(i == args->end());
    	return new If(variable_name, iftrue, iffalse);
    }
    if(!strcmp(type_id, "Loop"))
    {
    	List<Statement*>* statements = dynamic_cast<List<Statement*>*>(*i++);
    	assert(i == args->end());
    	return new Loop(statements);
    }
    if(!strcmp(type_id, "Foreach"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	Variable* key = dynamic_cast<Variable*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Variable* val = dynamic_cast<Variable*>(*i++);
    	List<Statement*>* statements = dynamic_cast<List<Statement*>*>(*i++);
    	assert(i == args->end());
    	return new Foreach(variable_name, key, is_ref, val, statements);
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
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Return(expr);
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
    	List<Statement*>* statements = dynamic_cast<List<Statement*>*>(*i++);
    	List<Catch*>* catches = dynamic_cast<List<Catch*>*>(*i++);
    	assert(i == args->end());
    	return new Try(statements, catches);
    }
    if(!strcmp(type_id, "Catch"))
    {
    	CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(*i++);
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	List<Statement*>* statements = dynamic_cast<List<Statement*>*>(*i++);
    	assert(i == args->end());
    	return new Catch(class_name, variable_name, statements);
    }
    if(!strcmp(type_id, "Throw"))
    {
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Throw(expr);
    }
    if(!strcmp(type_id, "Eval_expr"))
    {
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Eval_expr(expr);
    }
    if(!strcmp(type_id, "Foreign_expr"))
    {
    	assert(i == args->end());
    	return new Foreign_expr();
    }
    if(!strcmp(type_id, "Foreign_statement"))
    {
    	assert(i == args->end());
    	return new Foreign_statement();
    }
    if(!strcmp(type_id, "Branch"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	LABEL_NAME* iftrue = dynamic_cast<LABEL_NAME*>(*i++);
    	LABEL_NAME* iffalse = dynamic_cast<LABEL_NAME*>(*i++);
    	assert(i == args->end());
    	return new Branch(variable_name, iftrue, iffalse);
    }
    if(!strcmp(type_id, "Goto"))
    {
    	LABEL_NAME* label_name = dynamic_cast<LABEL_NAME*>(*i++);
    	assert(i == args->end());
    	return new Goto(label_name);
    }
    if(!strcmp(type_id, "Label"))
    {
    	LABEL_NAME* label_name = dynamic_cast<LABEL_NAME*>(*i++);
    	assert(i == args->end());
    	return new Label(label_name);
    }
    if(!strcmp(type_id, "Assignment"))
    {
    	Variable* variable = dynamic_cast<Variable*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Assignment(variable, is_ref, expr);
    }
    if(!strcmp(type_id, "Op_assignment"))
    {
    	Variable* variable = dynamic_cast<Variable*>(*i++);
    	OP* op = dynamic_cast<OP*>(*i++);
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Op_assignment(variable, op, expr);
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
    	VARIABLE_NAME* left = dynamic_cast<VARIABLE_NAME*>(*i++);
    	OP* op = dynamic_cast<OP*>(*i++);
    	VARIABLE_NAME* right = dynamic_cast<VARIABLE_NAME*>(*i++);
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
    if(!strcmp(type_id, "Variable"))
    {
    	Target* target = dynamic_cast<Target*>(*i++);
    	Variable_name* variable_name = dynamic_cast<Variable_name*>(*i++);
    	List<VARIABLE_NAME*>* array_indices = dynamic_cast<List<VARIABLE_NAME*>*>(*i++);
    	assert(i == args->end());
    	return new Variable(target, variable_name, array_indices);
    }
    if(!strcmp(type_id, "Reflection"))
    {
    	VARIABLE_NAME* variable_name = dynamic_cast<VARIABLE_NAME*>(*i++);
    	assert(i == args->end());
    	return new Reflection(variable_name);
    }
    if(!strcmp(type_id, "Pre_op"))
    {
    	OP* op = dynamic_cast<OP*>(*i++);
    	Variable* variable = dynamic_cast<Variable*>(*i++);
    	assert(i == args->end());
    	return new Pre_op(op, variable);
    }
    if(!strcmp(type_id, "Array"))
    {
    	List<Array_elem*>* array_elems = dynamic_cast<List<Array_elem*>*>(*i++);
    	assert(i == args->end());
    	return new Array(array_elems);
    }
    if(!strcmp(type_id, "Array_elem"))
    {
    	Expr* key = dynamic_cast<Expr*>(*i++);
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Expr* val = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Array_elem(key, is_ref, val);
    }
    if(!strcmp(type_id, "Method_invocation"))
    {
    	Target* target = dynamic_cast<Target*>(*i++);
    	Method_name* method_name = dynamic_cast<Method_name*>(*i++);
    	List<Actual_parameter*>* actual_parameters = dynamic_cast<List<Actual_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new Method_invocation(target, method_name, actual_parameters);
    }
    if(!strcmp(type_id, "Actual_parameter"))
    {
    	bool is_ref = dynamic_cast<Boolean*>(*i++)->value();
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Actual_parameter(is_ref, expr);
    }
    if(!strcmp(type_id, "New"))
    {
    	Class_name* class_name = dynamic_cast<Class_name*>(*i++);
    	List<Actual_parameter*>* actual_parameters = dynamic_cast<List<Actual_parameter*>*>(*i++);
    	assert(i == args->end());
    	return new New(class_name, actual_parameters);
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
    if(!strcmp(type_id, "LABEL_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new LABEL_NAME(value);
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
    if(!strcmp(type_id, "Statement_list"))
    {
    	List<Statement*>* list = new List<Statement*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Statement*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "INTERFACE_NAME_list"))
    {
    	List<INTERFACE_NAME*>* list = new List<INTERFACE_NAME*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<INTERFACE_NAME*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Member_list"))
    {
    	List<Member*>* list = new List<Member*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Member*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Formal_parameter_list"))
    {
    	List<Formal_parameter*>* list = new List<Formal_parameter*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Formal_parameter*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Catch_list"))
    {
    	List<Catch*>* list = new List<Catch*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Catch*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "VARIABLE_NAME_list"))
    {
    	List<VARIABLE_NAME*>* list = new List<VARIABLE_NAME*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<VARIABLE_NAME*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Array_elem_list"))
    {
    	List<Array_elem*>* list = new List<Array_elem*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Array_elem*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Actual_parameter_list"))
    {
    	List<Actual_parameter*>* list = new List<Actual_parameter*>;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Actual_parameter*>(*i++));
    	return list;
    }
    return NULL;
}
}

