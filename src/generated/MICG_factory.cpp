#include "MICG_factory.h"

namespace MICG{
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
    if(!strcmp(type_id, "Template"))
    {
    	Signature* signature = dynamic_cast<Signature*>(*i++);
    	Rule_list* rules = dynamic_cast<Rule_list*>(*i++);
    	Body* body = dynamic_cast<Body*>(*i++);
    	assert(i == args->end());
    	return new Template(signature, rules, body);
    }
    if(!strcmp(type_id, "Signature"))
    {
    	PATTERN_NAME* pattern_name = dynamic_cast<PATTERN_NAME*>(*i++);
    	Formal_parameter_list* formal_parameters = dynamic_cast<Formal_parameter_list*>(*i++);
    	assert(i == args->end());
    	return new Signature(pattern_name, formal_parameters);
    }
    if(!strcmp(type_id, "Formal_parameter"))
    {
    	TYPE* type = dynamic_cast<TYPE*>(*i++);
    	PARAM_NAME* param_name = dynamic_cast<PARAM_NAME*>(*i++);
    	assert(i == args->end());
    	return new Formal_parameter(type, param_name);
    }
    if(!strcmp(type_id, "Rule"))
    {
    	Expr* expr = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Rule(expr);
    }
    if(!strcmp(type_id, "Lookup"))
    {
    	PARAM_NAME* param_name = dynamic_cast<PARAM_NAME*>(*i++);
    	ATTR_NAME* attr_name = dynamic_cast<ATTR_NAME*>(*i++);
    	assert(i == args->end());
    	return new Lookup(param_name, attr_name);
    }
    if(!strcmp(type_id, "Equals"))
    {
    	Expr* left = dynamic_cast<Expr*>(*i++);
    	Expr* right = dynamic_cast<Expr*>(*i++);
    	assert(i == args->end());
    	return new Equals(left, right);
    }
    if(!strcmp(type_id, "Body"))
    {
    	Body_part_list* body_parts = dynamic_cast<Body_part_list*>(*i++);
    	assert(i == args->end());
    	return new Body(body_parts);
    }
    if(!strcmp(type_id, "Macro_call"))
    {
    	PATTERN_NAME* pattern_name = dynamic_cast<PATTERN_NAME*>(*i++);
    	Actual_parameter_list* actual_parameters = dynamic_cast<Actual_parameter_list*>(*i++);
    	assert(i == args->end());
    	return new Macro_call(pattern_name, actual_parameters);
    }
    if(!strcmp(type_id, "PATTERN_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new PATTERN_NAME(value);
    }
    if(!strcmp(type_id, "TYPE"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new TYPE(value);
    }
    if(!strcmp(type_id, "ATTR_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new ATTR_NAME(value);
    }
    if(!strcmp(type_id, "PARAM_NAME"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new PARAM_NAME(value);
    }
    if(!strcmp(type_id, "STRING"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new STRING(value);
    }
    if(!strcmp(type_id, "C_CODE"))
    {
    	String* value = dynamic_cast<String*>(*i++);
    	assert(i == args->end());
    	return new C_CODE(value);
    }
    if(!strcmp(type_id, "Rule_list"))
    {
    	Rule_list* list = new Rule_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Rule*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Formal_parameter_list"))
    {
    	Formal_parameter_list* list = new Formal_parameter_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Formal_parameter*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Body_part_list"))
    {
    	Body_part_list* list = new Body_part_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Body_part*>(*i++));
    	return list;
    }
    if(!strcmp(type_id, "Actual_parameter_list"))
    {
    	Actual_parameter_list* list = new Actual_parameter_list;
    	while(i != args->end())
    		list->push_back(dynamic_cast<Actual_parameter*>(*i++));
    	return list;
    }
    return NULL;
}
}

