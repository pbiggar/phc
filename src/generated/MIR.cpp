#include "MIR.h"
#include "MIR_transform.h"
#include "MIR_visitor.h"

namespace MIR{
Node::Node()
{
}

void Node::clone_mixin_from(Node* in)
{
    {
		attrs->clone_all_from (in->attrs);
	}
}

void Node::assert_mixin_valid()
{
    {
		assert(attrs != NULL);

		string key;
		Object* value;
		foreach (tie (key, value), *this->attrs)
		{
			if (key != "phc.line_number"
				&& key != "phc.filename")
			{
				assert(value != NULL);
			}
		}
	}
}

PHP_script::PHP_script(Statement_list* statements)
{
    this->statements = statements;
}

PHP_script::PHP_script()
{
    this->statements = 0;
}

void PHP_script::visit(Visitor* visitor)
{
    visitor->visit_php_script(this);
}

void PHP_script::transform_children(Transform* transform)
{
    transform->children_php_script(this);
}

const int PHP_script::ID;
int PHP_script::classid()
{
    return ID;
}

bool PHP_script::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    PHP_script* that = dynamic_cast<PHP_script*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    return true;
}

bool PHP_script::equals(Node* in)
{
    PHP_script* that = dynamic_cast<PHP_script*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    return true;
}

PHP_script* PHP_script::clone()
{
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    PHP_script* clone = new PHP_script(statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* PHP_script::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void PHP_script::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void PHP_script::assert_valid()
{
    assert(statements != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Statement::Statement()
{
}

Class_mod::Class_mod(bool is_abstract, bool is_final)
{
    this->is_abstract = is_abstract;
    this->is_final = is_final;
}

Class_mod::Class_mod()
{
    this->is_abstract = 0;
    this->is_final = 0;
}

void Class_mod::visit(Visitor* visitor)
{
    visitor->visit_class_mod(this);
}

void Class_mod::transform_children(Transform* transform)
{
    transform->children_class_mod(this);
}

const int Class_mod::ID;
int Class_mod::classid()
{
    return ID;
}

bool Class_mod::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Class_mod* that = dynamic_cast<Class_mod*>(in);
    if(that == NULL) return false;
    
    that->is_abstract = this->is_abstract;
    that->is_final = this->is_final;
    return true;
}

bool Class_mod::equals(Node* in)
{
    Class_mod* that = dynamic_cast<Class_mod*>(in);
    if(that == NULL) return false;
    
    if(this->is_abstract != that->is_abstract)
    	return false;
    
    if(this->is_final != that->is_final)
    	return false;
    
    return true;
}

Class_mod* Class_mod::clone()
{
    bool is_abstract = this->is_abstract;
    bool is_final = this->is_final;
    Class_mod* clone = new Class_mod(is_abstract, is_final);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Class_mod::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Class_mod::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Class_mod::assert_valid()
{
    Node::assert_mixin_valid();
}

Member::Member()
{
}

Signature::Signature(Method_mod* method_mod, bool pass_rest_by_ref, bool return_by_ref, METHOD_NAME* method_name, Formal_parameter_list* formal_parameters)
{
    this->method_mod = method_mod;
    this->pass_rest_by_ref = pass_rest_by_ref;
    this->return_by_ref = return_by_ref;
    this->method_name = method_name;
    this->formal_parameters = formal_parameters;
}

Signature::Signature()
{
    this->method_mod = 0;
    this->pass_rest_by_ref = 0;
    this->return_by_ref = 0;
    this->method_name = 0;
    this->formal_parameters = 0;
}

void Signature::visit(Visitor* visitor)
{
    visitor->visit_signature(this);
}

void Signature::transform_children(Transform* transform)
{
    transform->children_signature(this);
}

const int Signature::ID;
int Signature::classid()
{
    return ID;
}

bool Signature::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Signature* that = dynamic_cast<Signature*>(in);
    if(that == NULL) return false;
    
    if(this->method_mod == NULL)
    {
    	if(that->method_mod != NULL && !that->method_mod->match(this->method_mod))
    		return false;
    }
    else if(!this->method_mod->match(that->method_mod))
    	return false;
    
    that->pass_rest_by_ref = this->pass_rest_by_ref;
    that->return_by_ref = this->return_by_ref;
    if(this->method_name == NULL)
    {
    	if(that->method_name != NULL && !that->method_name->match(this->method_name))
    		return false;
    }
    else if(!this->method_name->match(that->method_name))
    	return false;
    
    if(this->formal_parameters != NULL && that->formal_parameters != NULL)
    {
    	Formal_parameter_list::const_iterator i, j;
    	for(
    		i = this->formal_parameters->begin(), j = that->formal_parameters->begin();
    		i != this->formal_parameters->end() && j != that->formal_parameters->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->formal_parameters->end() || j != that->formal_parameters->end())
    		return false;
    }
    
    return true;
}

bool Signature::equals(Node* in)
{
    Signature* that = dynamic_cast<Signature*>(in);
    if(that == NULL) return false;
    
    if(this->method_mod == NULL || that->method_mod == NULL)
    {
    	if(this->method_mod != NULL || that->method_mod != NULL)
    		return false;
    }
    else if(!this->method_mod->equals(that->method_mod))
    	return false;
    
    if(this->pass_rest_by_ref != that->pass_rest_by_ref)
    	return false;
    
    if(this->return_by_ref != that->return_by_ref)
    	return false;
    
    if(this->method_name == NULL || that->method_name == NULL)
    {
    	if(this->method_name != NULL || that->method_name != NULL)
    		return false;
    }
    else if(!this->method_name->equals(that->method_name))
    	return false;
    
    if(this->formal_parameters == NULL || that->formal_parameters == NULL)
    {
    	if(this->formal_parameters != NULL || that->formal_parameters != NULL)
    		return false;
    }
    else
    {
    	Formal_parameter_list::const_iterator i, j;
    	for(
    		i = this->formal_parameters->begin(), j = that->formal_parameters->begin();
    		i != this->formal_parameters->end() && j != that->formal_parameters->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->formal_parameters->end() || j != that->formal_parameters->end())
    		return false;
    }
    
    return true;
}

Signature* Signature::clone()
{
    Method_mod* method_mod = this->method_mod ? this->method_mod->clone() : NULL;
    bool pass_rest_by_ref = this->pass_rest_by_ref;
    bool return_by_ref = this->return_by_ref;
    METHOD_NAME* method_name = this->method_name ? this->method_name->clone() : NULL;
    Formal_parameter_list* formal_parameters = NULL;
    if(this->formal_parameters != NULL)
    {
    	Formal_parameter_list::const_iterator i;
    	formal_parameters = new Formal_parameter_list;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    		formal_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    Signature* clone = new Signature(method_mod, pass_rest_by_ref, return_by_ref, method_name, formal_parameters);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Signature::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->method_mod != NULL)
    {
    	Node* method_mod_res = this->method_mod->find(in);
    	if (method_mod_res) return method_mod_res;
    }
    
    if (this->method_name != NULL)
    {
    	Node* method_name_res = this->method_name->find(in);
    	if (method_name_res) return method_name_res;
    }
    
    if(this->formal_parameters != NULL)
    {
    	Formal_parameter_list::const_iterator i;
    	for(
    		i = this->formal_parameters->begin();
    		i != this->formal_parameters->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Signature::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->method_mod != NULL)
    	this->method_mod->find_all(in, out);
    
    if (this->method_name != NULL)
    	this->method_name->find_all(in, out);
    
    if(this->formal_parameters != NULL)
    {
    	Formal_parameter_list::const_iterator i;
    	for(
    		i = this->formal_parameters->begin();
    		i != this->formal_parameters->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Signature::assert_valid()
{
    assert(method_mod != NULL);
    method_mod->assert_valid();
    assert(method_name != NULL);
    method_name->assert_valid();
    assert(formal_parameters != NULL);
    {
    	Formal_parameter_list::const_iterator i;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Signature::Signature(const char* name)
{
    {
		this->method_mod = Method_mod::new_PUBLIC();
		this->pass_rest_by_ref = false;
		this->return_by_ref = false;
		this->method_name = new METHOD_NAME(name);
		this->formal_parameters = new Formal_parameter_list;
	}
}

/*  Returns if the parameter at index PARAM_INDEX is passed by reference. */
bool Signature::is_param_passed_by_ref(int param_index)
{
    {
		if (this->formal_parameters->size () > (unsigned int)(param_index))
			return formal_parameters->at (param_index)->is_ref;
		else
			return this->pass_rest_by_ref;
	}
}

Method_mod::Method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final)
{
    this->is_public = is_public;
    this->is_protected = is_protected;
    this->is_private = is_private;
    this->is_static = is_static;
    this->is_abstract = is_abstract;
    this->is_final = is_final;
}

void Method_mod::visit(Visitor* visitor)
{
    visitor->visit_method_mod(this);
}

void Method_mod::transform_children(Transform* transform)
{
    transform->children_method_mod(this);
}

const int Method_mod::ID;
int Method_mod::classid()
{
    return ID;
}

bool Method_mod::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Method_mod* that = dynamic_cast<Method_mod*>(in);
    if(that == NULL) return false;
    
    that->is_public = this->is_public;
    that->is_protected = this->is_protected;
    that->is_private = this->is_private;
    that->is_static = this->is_static;
    that->is_abstract = this->is_abstract;
    that->is_final = this->is_final;
    return true;
}

bool Method_mod::equals(Node* in)
{
    Method_mod* that = dynamic_cast<Method_mod*>(in);
    if(that == NULL) return false;
    
    if(this->is_public != that->is_public)
    	return false;
    
    if(this->is_protected != that->is_protected)
    	return false;
    
    if(this->is_private != that->is_private)
    	return false;
    
    if(this->is_static != that->is_static)
    	return false;
    
    if(this->is_abstract != that->is_abstract)
    	return false;
    
    if(this->is_final != that->is_final)
    	return false;
    
    return true;
}

Method_mod* Method_mod::clone()
{
    bool is_public = this->is_public;
    bool is_protected = this->is_protected;
    bool is_private = this->is_private;
    bool is_static = this->is_static;
    bool is_abstract = this->is_abstract;
    bool is_final = this->is_final;
    Method_mod* clone = new Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Method_mod::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Method_mod::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Method_mod::assert_valid()
{
    Node::assert_mixin_valid();
}

Method_mod::Method_mod()
{
    {
		is_public = false;
		is_protected = false;
		is_private = false;
		is_static = false;
		is_abstract = false;
		is_final = false;
	}
}

Method_mod::Method_mod(Method_mod* a, Method_mod* b)
{
    {
		this->is_public 		= a->is_public		|| b->is_public;
		this->is_protected	= a->is_protected	|| b->is_protected;
		this->is_private		= a->is_private	|| b->is_private;
		this->is_static		= a->is_static		|| b->is_static;
		this->is_abstract		= a->is_abstract	|| b->is_abstract;
		this->is_final			= a->is_final		|| b->is_final;
	}
}

Method_mod* Method_mod::new_PUBLIC()
{
    {
		return new Method_mod(true, false, false, false, false, false);		
	}
}

Method_mod* Method_mod::new_PROTECTED()
{
    { 
		return new Method_mod(false, true, false, false, false, false);		
	}
}

Method_mod* Method_mod::new_PRIVATE()
{
    { 
		return new Method_mod(false, false, true, false, false, false);		
	}
}

Method_mod* Method_mod::new_STATIC()
{
    { 
		return new Method_mod(false, false, false, true, false, false);		
	}
}

Method_mod* Method_mod::new_ABSTRACT()
{
    { 
		return new Method_mod(false, false, false, false, true, false);		
	}
}

Method_mod* Method_mod::new_FINAL()
{
    { 
		return new Method_mod(false, false, false, false, false, true);		
	}
}

Formal_parameter::Formal_parameter(Type* type, bool is_ref, Name_with_default* var)
{
    this->type = type;
    this->is_ref = is_ref;
    this->var = var;
}

Formal_parameter::Formal_parameter()
{
    this->type = 0;
    this->is_ref = 0;
    this->var = 0;
}

void Formal_parameter::visit(Visitor* visitor)
{
    visitor->visit_formal_parameter(this);
}

void Formal_parameter::transform_children(Transform* transform)
{
    transform->children_formal_parameter(this);
}

const int Formal_parameter::ID;
int Formal_parameter::classid()
{
    return ID;
}

bool Formal_parameter::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Formal_parameter* that = dynamic_cast<Formal_parameter*>(in);
    if(that == NULL) return false;
    
    if(this->type == NULL)
    {
    	if(that->type != NULL && !that->type->match(this->type))
    		return false;
    }
    else if(!this->type->match(that->type))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->var == NULL)
    {
    	if(that->var != NULL && !that->var->match(this->var))
    		return false;
    }
    else if(!this->var->match(that->var))
    	return false;
    
    return true;
}

bool Formal_parameter::equals(Node* in)
{
    Formal_parameter* that = dynamic_cast<Formal_parameter*>(in);
    if(that == NULL) return false;
    
    if(this->type == NULL || that->type == NULL)
    {
    	if(this->type != NULL || that->type != NULL)
    		return false;
    }
    else if(!this->type->equals(that->type))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->var == NULL || that->var == NULL)
    {
    	if(this->var != NULL || that->var != NULL)
    		return false;
    }
    else if(!this->var->equals(that->var))
    	return false;
    
    return true;
}

Formal_parameter* Formal_parameter::clone()
{
    Type* type = this->type ? this->type->clone() : NULL;
    bool is_ref = this->is_ref;
    Name_with_default* var = this->var ? this->var->clone() : NULL;
    Formal_parameter* clone = new Formal_parameter(type, is_ref, var);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Formal_parameter::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->type != NULL)
    {
    	Node* type_res = this->type->find(in);
    	if (type_res) return type_res;
    }
    
    if (this->var != NULL)
    {
    	Node* var_res = this->var->find(in);
    	if (var_res) return var_res;
    }
    
    return NULL;
}

void Formal_parameter::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->type != NULL)
    	this->type->find_all(in, out);
    
    if (this->var != NULL)
    	this->var->find_all(in, out);
    
}

void Formal_parameter::assert_valid()
{
    assert(type != NULL);
    type->assert_valid();
    assert(var != NULL);
    var->assert_valid();
    Node::assert_mixin_valid();
}

Formal_parameter::Formal_parameter(Type* type, VARIABLE_NAME* name)
{
    {
		this->type = type;
		this->is_ref = false;
		this->var = new Name_with_default(name, NULL);
	}
}

Formal_parameter::Formal_parameter(Type* type, bool is_ref, VARIABLE_NAME* name)
{
    { 
		this->type = type;
		this->is_ref = is_ref;
		this->var = new Name_with_default(name, NULL);
	}
}

Type::Type(CLASS_NAME* class_name)
{
    this->class_name = class_name;
}

Type::Type()
{
    this->class_name = 0;
}

void Type::visit(Visitor* visitor)
{
    visitor->visit_type(this);
}

void Type::transform_children(Transform* transform)
{
    transform->children_type(this);
}

const int Type::ID;
int Type::classid()
{
    return ID;
}

bool Type::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Type* that = dynamic_cast<Type*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    return true;
}

bool Type::equals(Node* in)
{
    Type* that = dynamic_cast<Type*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    return true;
}

Type* Type::clone()
{
    CLASS_NAME* class_name = this->class_name ? this->class_name->clone() : NULL;
    Type* clone = new Type(class_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Type::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    return NULL;
}

void Type::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
}

void Type::assert_valid()
{
    if(class_name != NULL) class_name->assert_valid();
    Node::assert_mixin_valid();
}

Attr_mod::Attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const)
{
    this->is_public = is_public;
    this->is_protected = is_protected;
    this->is_private = is_private;
    this->is_static = is_static;
    this->is_const = is_const;
}

void Attr_mod::visit(Visitor* visitor)
{
    visitor->visit_attr_mod(this);
}

void Attr_mod::transform_children(Transform* transform)
{
    transform->children_attr_mod(this);
}

const int Attr_mod::ID;
int Attr_mod::classid()
{
    return ID;
}

bool Attr_mod::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Attr_mod* that = dynamic_cast<Attr_mod*>(in);
    if(that == NULL) return false;
    
    that->is_public = this->is_public;
    that->is_protected = this->is_protected;
    that->is_private = this->is_private;
    that->is_static = this->is_static;
    that->is_const = this->is_const;
    return true;
}

bool Attr_mod::equals(Node* in)
{
    Attr_mod* that = dynamic_cast<Attr_mod*>(in);
    if(that == NULL) return false;
    
    if(this->is_public != that->is_public)
    	return false;
    
    if(this->is_protected != that->is_protected)
    	return false;
    
    if(this->is_private != that->is_private)
    	return false;
    
    if(this->is_static != that->is_static)
    	return false;
    
    if(this->is_const != that->is_const)
    	return false;
    
    return true;
}

Attr_mod* Attr_mod::clone()
{
    bool is_public = this->is_public;
    bool is_protected = this->is_protected;
    bool is_private = this->is_private;
    bool is_static = this->is_static;
    bool is_const = this->is_const;
    Attr_mod* clone = new Attr_mod(is_public, is_protected, is_private, is_static, is_const);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Attr_mod::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Attr_mod::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Attr_mod::assert_valid()
{
    Node::assert_mixin_valid();
}

Attr_mod::Attr_mod()
{
    {
		is_public = false;
		is_protected = false;
		is_private = false;
		is_static = false;
		is_const = false;
	}
}

Attr_mod::Attr_mod(Method_mod* mm)
{
    {
		if(mm->is_final)
			phc_error("The final modifier is only allowed for methods", mm);

		this->is_public = mm->is_public;
		this->is_protected = mm->is_protected;
		this->is_private = mm->is_private;
		this->is_static = mm->is_static;
		this->is_const = false;
	}
}

Attr_mod* Attr_mod::new_PUBLIC()
{
    {
		return new Attr_mod(true, false, false, false, false);
	}
}

Attr_mod* Attr_mod::new_PROTECTED()
{
    { 
		return new Attr_mod(false, true, false, false, false);
	}
}

Attr_mod* Attr_mod::new_PRIVATE()
{
    {
		return new Attr_mod(false, false, true, false, false);
	}
}

Attr_mod* Attr_mod::new_STATIC()
{
    {
		return new Attr_mod(false, false, false, true, false);
	}
}

Attr_mod* Attr_mod::new_CONST()
{
    {
		return new Attr_mod(false, false, false, false, true);
	}
}

Name_with_default::Name_with_default(VARIABLE_NAME* variable_name, Static_value* default_value)
{
    this->variable_name = variable_name;
    this->default_value = default_value;
}

Name_with_default::Name_with_default()
{
    this->variable_name = 0;
    this->default_value = 0;
}

void Name_with_default::visit(Visitor* visitor)
{
    visitor->visit_name_with_default(this);
}

void Name_with_default::transform_children(Transform* transform)
{
    transform->children_name_with_default(this);
}

const int Name_with_default::ID;
int Name_with_default::classid()
{
    return ID;
}

bool Name_with_default::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Name_with_default* that = dynamic_cast<Name_with_default*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->default_value == NULL)
    {
    	if(that->default_value != NULL && !that->default_value->match(this->default_value))
    		return false;
    }
    else if(!this->default_value->match(that->default_value))
    	return false;
    
    return true;
}

bool Name_with_default::equals(Node* in)
{
    Name_with_default* that = dynamic_cast<Name_with_default*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->default_value == NULL || that->default_value == NULL)
    {
    	if(this->default_value != NULL || that->default_value != NULL)
    		return false;
    }
    else if(!this->default_value->equals(that->default_value))
    	return false;
    
    return true;
}

Name_with_default* Name_with_default::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Static_value* default_value = this->default_value ? this->default_value->clone() : NULL;
    Name_with_default* clone = new Name_with_default(variable_name, default_value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Name_with_default::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if (this->default_value != NULL)
    {
    	Node* default_value_res = this->default_value->find(in);
    	if (default_value_res) return default_value_res;
    }
    
    return NULL;
}

void Name_with_default::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if (this->default_value != NULL)
    	this->default_value->find_all(in, out);
    
}

void Name_with_default::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    if(default_value != NULL) default_value->assert_valid();
    Node::assert_mixin_valid();
}

Catch::Catch(CLASS_NAME* class_name, VARIABLE_NAME* variable_name, Statement_list* statements)
{
    this->class_name = class_name;
    this->variable_name = variable_name;
    this->statements = statements;
}

Catch::Catch()
{
    this->class_name = 0;
    this->variable_name = 0;
    this->statements = 0;
}

void Catch::visit(Visitor* visitor)
{
    visitor->visit_catch(this);
}

void Catch::transform_children(Transform* transform)
{
    transform->children_catch(this);
}

const int Catch::ID;
int Catch::classid()
{
    return ID;
}

bool Catch::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Catch* that = dynamic_cast<Catch*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    return true;
}

bool Catch::equals(Node* in)
{
    Catch* that = dynamic_cast<Catch*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    return true;
}

Catch* Catch::clone()
{
    CLASS_NAME* class_name = this->class_name ? this->class_name->clone() : NULL;
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Catch* clone = new Catch(class_name, variable_name, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Catch::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Catch::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Catch::assert_valid()
{
    assert(class_name != NULL);
    class_name->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(statements != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Expr::Expr()
{
}

Target::Target()
{
}

Actual_parameter::Actual_parameter(bool is_ref, Rvalue* rvalue)
{
    this->is_ref = is_ref;
    this->rvalue = rvalue;
}

Actual_parameter::Actual_parameter()
{
    this->is_ref = 0;
    this->rvalue = 0;
}

void Actual_parameter::visit(Visitor* visitor)
{
    visitor->visit_actual_parameter(this);
}

void Actual_parameter::transform_children(Transform* transform)
{
    transform->children_actual_parameter(this);
}

const int Actual_parameter::ID;
int Actual_parameter::classid()
{
    return ID;
}

bool Actual_parameter::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Actual_parameter* that = dynamic_cast<Actual_parameter*>(in);
    if(that == NULL) return false;
    
    that->is_ref = this->is_ref;
    if(this->rvalue == NULL)
    {
    	if(that->rvalue != NULL && !that->rvalue->match(this->rvalue))
    		return false;
    }
    else if(!this->rvalue->match(that->rvalue))
    	return false;
    
    return true;
}

bool Actual_parameter::equals(Node* in)
{
    Actual_parameter* that = dynamic_cast<Actual_parameter*>(in);
    if(that == NULL) return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->rvalue == NULL || that->rvalue == NULL)
    {
    	if(this->rvalue != NULL || that->rvalue != NULL)
    		return false;
    }
    else if(!this->rvalue->equals(that->rvalue))
    	return false;
    
    return true;
}

Actual_parameter* Actual_parameter::clone()
{
    bool is_ref = this->is_ref;
    Rvalue* rvalue = this->rvalue ? this->rvalue->clone() : NULL;
    Actual_parameter* clone = new Actual_parameter(is_ref, rvalue);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Actual_parameter::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->rvalue != NULL)
    {
    	Node* rvalue_res = this->rvalue->find(in);
    	if (rvalue_res) return rvalue_res;
    }
    
    return NULL;
}

void Actual_parameter::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->rvalue != NULL)
    	this->rvalue->find_all(in, out);
    
}

void Actual_parameter::assert_valid()
{
    assert(rvalue != NULL);
    rvalue->assert_valid();
    Node::assert_mixin_valid();
}

Method_name::Method_name()
{
}

Class_name::Class_name()
{
}

Field_name::Field_name()
{
}

Static_value::Static_value()
{
}

Static_array_elem::Static_array_elem(Static_array_key* key, bool is_ref, Static_value* val)
{
    this->key = key;
    this->is_ref = is_ref;
    this->val = val;
}

Static_array_elem::Static_array_elem()
{
    this->key = 0;
    this->is_ref = 0;
    this->val = 0;
}

void Static_array_elem::visit(Visitor* visitor)
{
    visitor->visit_static_array_elem(this);
}

void Static_array_elem::transform_children(Transform* transform)
{
    transform->children_static_array_elem(this);
}

const int Static_array_elem::ID;
int Static_array_elem::classid()
{
    return ID;
}

bool Static_array_elem::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Static_array_elem* that = dynamic_cast<Static_array_elem*>(in);
    if(that == NULL) return false;
    
    if(this->key == NULL)
    {
    	if(that->key != NULL && !that->key->match(this->key))
    		return false;
    }
    else if(!this->key->match(that->key))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->val == NULL)
    {
    	if(that->val != NULL && !that->val->match(this->val))
    		return false;
    }
    else if(!this->val->match(that->val))
    	return false;
    
    return true;
}

bool Static_array_elem::equals(Node* in)
{
    Static_array_elem* that = dynamic_cast<Static_array_elem*>(in);
    if(that == NULL) return false;
    
    if(this->key == NULL || that->key == NULL)
    {
    	if(this->key != NULL || that->key != NULL)
    		return false;
    }
    else if(!this->key->equals(that->key))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->val == NULL || that->val == NULL)
    {
    	if(this->val != NULL || that->val != NULL)
    		return false;
    }
    else if(!this->val->equals(that->val))
    	return false;
    
    return true;
}

Static_array_elem* Static_array_elem::clone()
{
    Static_array_key* key = this->key ? this->key->clone() : NULL;
    bool is_ref = this->is_ref;
    Static_value* val = this->val ? this->val->clone() : NULL;
    Static_array_elem* clone = new Static_array_elem(key, is_ref, val);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Static_array_elem::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->key != NULL)
    {
    	Node* key_res = this->key->find(in);
    	if (key_res) return key_res;
    }
    
    if (this->val != NULL)
    {
    	Node* val_res = this->val->find(in);
    	if (val_res) return val_res;
    }
    
    return NULL;
}

void Static_array_elem::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->key != NULL)
    	this->key->find_all(in, out);
    
    if (this->val != NULL)
    	this->val->find_all(in, out);
    
}

void Static_array_elem::assert_valid()
{
    if(key != NULL) key->assert_valid();
    assert(val != NULL);
    val->assert_valid();
    Node::assert_mixin_valid();
}

Static_array_key::Static_array_key()
{
}

Identifier::Identifier()
{
}

PARAM_INDEX::PARAM_INDEX(int value)
{
    this->value = value;
}

PARAM_INDEX::PARAM_INDEX()
{
    this->value = 0;
}

void PARAM_INDEX::visit(Visitor* visitor)
{
    visitor->visit_param_index(this);
}

void PARAM_INDEX::transform_children(Transform* transform)
{
    transform->children_param_index(this);
}

const int PARAM_INDEX::ID;
int PARAM_INDEX::classid()
{
    return ID;
}

bool PARAM_INDEX::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    PARAM_INDEX* that = dynamic_cast<PARAM_INDEX*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool PARAM_INDEX::match_value(PARAM_INDEX* that)
{
    return true;
}

bool PARAM_INDEX::equals(Node* in)
{
    PARAM_INDEX* that = dynamic_cast<PARAM_INDEX*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

bool PARAM_INDEX::equals_value(PARAM_INDEX* that)
{
    return (this->value == that->value);
}

PARAM_INDEX* PARAM_INDEX::clone()
{
    value = clone_value();
    PARAM_INDEX* clone = new PARAM_INDEX(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

int PARAM_INDEX::clone_value()
{
    return value;
}

Node* PARAM_INDEX::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void PARAM_INDEX::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void PARAM_INDEX::assert_valid()
{
    assert_value_valid();
    Node::assert_mixin_valid();
}

void PARAM_INDEX::assert_value_valid()
{
    // Assume value is valid
}

String* PARAM_INDEX::get_value_as_string()
{
    {
		return new String (boost::lexical_cast<string> (value));
	}
}

Class_def::Class_def(Class_mod* class_mod, CLASS_NAME* class_name, CLASS_NAME* extends, INTERFACE_NAME_list* implements, Member_list* members)
{
    this->class_mod = class_mod;
    this->class_name = class_name;
    this->extends = extends;
    this->implements = implements;
    this->members = members;
}

Class_def::Class_def()
{
    this->class_mod = 0;
    this->class_name = 0;
    this->extends = 0;
    this->implements = 0;
    this->members = 0;
}

void Class_def::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Class_def::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Class_def::ID;
int Class_def::classid()
{
    return ID;
}

bool Class_def::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Class_def* that = dynamic_cast<Class_def*>(in);
    if(that == NULL) return false;
    
    if(this->class_mod == NULL)
    {
    	if(that->class_mod != NULL && !that->class_mod->match(this->class_mod))
    		return false;
    }
    else if(!this->class_mod->match(that->class_mod))
    	return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    if(this->extends == NULL)
    {
    	if(that->extends != NULL && !that->extends->match(this->extends))
    		return false;
    }
    else if(!this->extends->match(that->extends))
    	return false;
    
    if(this->implements != NULL && that->implements != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i, j;
    	for(
    		i = this->implements->begin(), j = that->implements->begin();
    		i != this->implements->end() && j != that->implements->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->implements->end() || j != that->implements->end())
    		return false;
    }
    
    if(this->members != NULL && that->members != NULL)
    {
    	Member_list::const_iterator i, j;
    	for(
    		i = this->members->begin(), j = that->members->begin();
    		i != this->members->end() && j != that->members->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->members->end() || j != that->members->end())
    		return false;
    }
    
    return true;
}

bool Class_def::equals(Node* in)
{
    Class_def* that = dynamic_cast<Class_def*>(in);
    if(that == NULL) return false;
    
    if(this->class_mod == NULL || that->class_mod == NULL)
    {
    	if(this->class_mod != NULL || that->class_mod != NULL)
    		return false;
    }
    else if(!this->class_mod->equals(that->class_mod))
    	return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    if(this->extends == NULL || that->extends == NULL)
    {
    	if(this->extends != NULL || that->extends != NULL)
    		return false;
    }
    else if(!this->extends->equals(that->extends))
    	return false;
    
    if(this->implements == NULL || that->implements == NULL)
    {
    	if(this->implements != NULL || that->implements != NULL)
    		return false;
    }
    else
    {
    	INTERFACE_NAME_list::const_iterator i, j;
    	for(
    		i = this->implements->begin(), j = that->implements->begin();
    		i != this->implements->end() && j != that->implements->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->implements->end() || j != that->implements->end())
    		return false;
    }
    
    if(this->members == NULL || that->members == NULL)
    {
    	if(this->members != NULL || that->members != NULL)
    		return false;
    }
    else
    {
    	Member_list::const_iterator i, j;
    	for(
    		i = this->members->begin(), j = that->members->begin();
    		i != this->members->end() && j != that->members->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->members->end() || j != that->members->end())
    		return false;
    }
    
    return true;
}

Class_def* Class_def::clone()
{
    Class_mod* class_mod = this->class_mod ? this->class_mod->clone() : NULL;
    CLASS_NAME* class_name = this->class_name ? this->class_name->clone() : NULL;
    CLASS_NAME* extends = this->extends ? this->extends->clone() : NULL;
    INTERFACE_NAME_list* implements = NULL;
    if(this->implements != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i;
    	implements = new INTERFACE_NAME_list;
    	for(i = this->implements->begin(); i != this->implements->end(); i++)
    		implements->push_back(*i ? (*i)->clone() : NULL);
    }
    Member_list* members = NULL;
    if(this->members != NULL)
    {
    	Member_list::const_iterator i;
    	members = new Member_list;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    		members->push_back(*i ? (*i)->clone() : NULL);
    }
    Class_def* clone = new Class_def(class_mod, class_name, extends, implements, members);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Class_def::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->class_mod != NULL)
    {
    	Node* class_mod_res = this->class_mod->find(in);
    	if (class_mod_res) return class_mod_res;
    }
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    if (this->extends != NULL)
    {
    	Node* extends_res = this->extends->find(in);
    	if (extends_res) return extends_res;
    }
    
    if(this->implements != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i;
    	for(
    		i = this->implements->begin();
    		i != this->implements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if(this->members != NULL)
    {
    	Member_list::const_iterator i;
    	for(
    		i = this->members->begin();
    		i != this->members->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Class_def::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->class_mod != NULL)
    	this->class_mod->find_all(in, out);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
    if (this->extends != NULL)
    	this->extends->find_all(in, out);
    
    if(this->implements != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i;
    	for(
    		i = this->implements->begin();
    		i != this->implements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if(this->members != NULL)
    {
    	Member_list::const_iterator i;
    	for(
    		i = this->members->begin();
    		i != this->members->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Class_def::assert_valid()
{
    assert(class_mod != NULL);
    class_mod->assert_valid();
    assert(class_name != NULL);
    class_name->assert_valid();
    if(extends != NULL) extends->assert_valid();
    assert(implements != NULL);
    {
    	INTERFACE_NAME_list::const_iterator i;
    	for(i = this->implements->begin(); i != this->implements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(members != NULL);
    {
    	Member_list::const_iterator i;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Class_def::Class_def(Class_mod* mod)
{
    {
		this->class_mod = mod;
		this->class_name = NULL;
		this->extends = NULL;
		this->implements = new INTERFACE_NAME_list;
		this->members = new Member_list;
	}
}

Class_def::Class_def(const char* name)
{
    {
		this->class_mod = new Class_mod(false, false);
		this->class_name = new CLASS_NAME(new String(name));
		this->extends = NULL;
		this->implements = new INTERFACE_NAME_list;
		this->members = new Member_list;
	}
}

void Class_def::add_member(Member* member)
{
    {
		this->members->push_back(member);
	}
}

/*  Returns NULL if the method could not be found */
Method* Class_def::get_method(const char* name)
{
    {
		foreach (Member* m, *members)
		{
			Method* method = dynamic_cast<Method*>(m);
			if(method && *method->signature->method_name->value == name)
				return method;
		}

		return NULL;
	}
}

Interface_def::Interface_def(INTERFACE_NAME* interface_name, INTERFACE_NAME_list* extends, Member_list* members)
{
    this->interface_name = interface_name;
    this->extends = extends;
    this->members = members;
}

Interface_def::Interface_def()
{
    this->interface_name = 0;
    this->extends = 0;
    this->members = 0;
}

void Interface_def::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Interface_def::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Interface_def::ID;
int Interface_def::classid()
{
    return ID;
}

bool Interface_def::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Interface_def* that = dynamic_cast<Interface_def*>(in);
    if(that == NULL) return false;
    
    if(this->interface_name == NULL)
    {
    	if(that->interface_name != NULL && !that->interface_name->match(this->interface_name))
    		return false;
    }
    else if(!this->interface_name->match(that->interface_name))
    	return false;
    
    if(this->extends != NULL && that->extends != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i, j;
    	for(
    		i = this->extends->begin(), j = that->extends->begin();
    		i != this->extends->end() && j != that->extends->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->extends->end() || j != that->extends->end())
    		return false;
    }
    
    if(this->members != NULL && that->members != NULL)
    {
    	Member_list::const_iterator i, j;
    	for(
    		i = this->members->begin(), j = that->members->begin();
    		i != this->members->end() && j != that->members->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->members->end() || j != that->members->end())
    		return false;
    }
    
    return true;
}

bool Interface_def::equals(Node* in)
{
    Interface_def* that = dynamic_cast<Interface_def*>(in);
    if(that == NULL) return false;
    
    if(this->interface_name == NULL || that->interface_name == NULL)
    {
    	if(this->interface_name != NULL || that->interface_name != NULL)
    		return false;
    }
    else if(!this->interface_name->equals(that->interface_name))
    	return false;
    
    if(this->extends == NULL || that->extends == NULL)
    {
    	if(this->extends != NULL || that->extends != NULL)
    		return false;
    }
    else
    {
    	INTERFACE_NAME_list::const_iterator i, j;
    	for(
    		i = this->extends->begin(), j = that->extends->begin();
    		i != this->extends->end() && j != that->extends->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->extends->end() || j != that->extends->end())
    		return false;
    }
    
    if(this->members == NULL || that->members == NULL)
    {
    	if(this->members != NULL || that->members != NULL)
    		return false;
    }
    else
    {
    	Member_list::const_iterator i, j;
    	for(
    		i = this->members->begin(), j = that->members->begin();
    		i != this->members->end() && j != that->members->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->members->end() || j != that->members->end())
    		return false;
    }
    
    return true;
}

Interface_def* Interface_def::clone()
{
    INTERFACE_NAME* interface_name = this->interface_name ? this->interface_name->clone() : NULL;
    INTERFACE_NAME_list* extends = NULL;
    if(this->extends != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i;
    	extends = new INTERFACE_NAME_list;
    	for(i = this->extends->begin(); i != this->extends->end(); i++)
    		extends->push_back(*i ? (*i)->clone() : NULL);
    }
    Member_list* members = NULL;
    if(this->members != NULL)
    {
    	Member_list::const_iterator i;
    	members = new Member_list;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    		members->push_back(*i ? (*i)->clone() : NULL);
    }
    Interface_def* clone = new Interface_def(interface_name, extends, members);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Interface_def::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->interface_name != NULL)
    {
    	Node* interface_name_res = this->interface_name->find(in);
    	if (interface_name_res) return interface_name_res;
    }
    
    if(this->extends != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i;
    	for(
    		i = this->extends->begin();
    		i != this->extends->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if(this->members != NULL)
    {
    	Member_list::const_iterator i;
    	for(
    		i = this->members->begin();
    		i != this->members->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Interface_def::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->interface_name != NULL)
    	this->interface_name->find_all(in, out);
    
    if(this->extends != NULL)
    {
    	INTERFACE_NAME_list::const_iterator i;
    	for(
    		i = this->extends->begin();
    		i != this->extends->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if(this->members != NULL)
    {
    	Member_list::const_iterator i;
    	for(
    		i = this->members->begin();
    		i != this->members->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Interface_def::assert_valid()
{
    assert(interface_name != NULL);
    interface_name->assert_valid();
    assert(extends != NULL);
    {
    	INTERFACE_NAME_list::const_iterator i;
    	for(i = this->extends->begin(); i != this->extends->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(members != NULL);
    {
    	Member_list::const_iterator i;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Method::Method(Signature* signature, Statement_list* statements)
{
    this->signature = signature;
    this->statements = statements;
}

Method::Method()
{
    this->signature = 0;
    this->statements = 0;
}

void Method::visit(Visitor* visitor)
{
    visitor->visit_member(this);
}

void Method::transform_children(Transform* transform)
{
    transform->children_member(this);
}

const int Method::ID;
int Method::classid()
{
    return ID;
}

bool Method::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Method* that = dynamic_cast<Method*>(in);
    if(that == NULL) return false;
    
    if(this->signature == NULL)
    {
    	if(that->signature != NULL && !that->signature->match(this->signature))
    		return false;
    }
    else if(!this->signature->match(that->signature))
    	return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    return true;
}

bool Method::equals(Node* in)
{
    Method* that = dynamic_cast<Method*>(in);
    if(that == NULL) return false;
    
    if(this->signature == NULL || that->signature == NULL)
    {
    	if(this->signature != NULL || that->signature != NULL)
    		return false;
    }
    else if(!this->signature->equals(that->signature))
    	return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    return true;
}

Method* Method::clone()
{
    Signature* signature = this->signature ? this->signature->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Method* clone = new Method(signature, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Method::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->signature != NULL)
    {
    	Node* signature_res = this->signature->find(in);
    	if (signature_res) return signature_res;
    }
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Method::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->signature != NULL)
    	this->signature->find_all(in, out);
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Method::assert_valid()
{
    assert(signature != NULL);
    signature->assert_valid();
    if(statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Attribute::Attribute(Attr_mod* attr_mod, Name_with_default* var)
{
    this->attr_mod = attr_mod;
    this->var = var;
}

Attribute::Attribute()
{
    this->attr_mod = 0;
    this->var = 0;
}

void Attribute::visit(Visitor* visitor)
{
    visitor->visit_member(this);
}

void Attribute::transform_children(Transform* transform)
{
    transform->children_member(this);
}

const int Attribute::ID;
int Attribute::classid()
{
    return ID;
}

bool Attribute::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Attribute* that = dynamic_cast<Attribute*>(in);
    if(that == NULL) return false;
    
    if(this->attr_mod == NULL)
    {
    	if(that->attr_mod != NULL && !that->attr_mod->match(this->attr_mod))
    		return false;
    }
    else if(!this->attr_mod->match(that->attr_mod))
    	return false;
    
    if(this->var == NULL)
    {
    	if(that->var != NULL && !that->var->match(this->var))
    		return false;
    }
    else if(!this->var->match(that->var))
    	return false;
    
    return true;
}

bool Attribute::equals(Node* in)
{
    Attribute* that = dynamic_cast<Attribute*>(in);
    if(that == NULL) return false;
    
    if(this->attr_mod == NULL || that->attr_mod == NULL)
    {
    	if(this->attr_mod != NULL || that->attr_mod != NULL)
    		return false;
    }
    else if(!this->attr_mod->equals(that->attr_mod))
    	return false;
    
    if(this->var == NULL || that->var == NULL)
    {
    	if(this->var != NULL || that->var != NULL)
    		return false;
    }
    else if(!this->var->equals(that->var))
    	return false;
    
    return true;
}

Attribute* Attribute::clone()
{
    Attr_mod* attr_mod = this->attr_mod ? this->attr_mod->clone() : NULL;
    Name_with_default* var = this->var ? this->var->clone() : NULL;
    Attribute* clone = new Attribute(attr_mod, var);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Attribute::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->attr_mod != NULL)
    {
    	Node* attr_mod_res = this->attr_mod->find(in);
    	if (attr_mod_res) return attr_mod_res;
    }
    
    if (this->var != NULL)
    {
    	Node* var_res = this->var->find(in);
    	if (var_res) return var_res;
    }
    
    return NULL;
}

void Attribute::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->attr_mod != NULL)
    	this->attr_mod->find_all(in, out);
    
    if (this->var != NULL)
    	this->var->find_all(in, out);
    
}

void Attribute::assert_valid()
{
    assert(attr_mod != NULL);
    attr_mod->assert_valid();
    assert(var != NULL);
    var->assert_valid();
    Node::assert_mixin_valid();
}

Class_alias::Class_alias(CLASS_NAME* alias, CLASS_NAME* class_name)
{
    this->alias = alias;
    this->class_name = class_name;
}

Class_alias::Class_alias()
{
    this->alias = 0;
    this->class_name = 0;
}

void Class_alias::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Class_alias::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Class_alias::ID;
int Class_alias::classid()
{
    return ID;
}

bool Class_alias::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Class_alias* that = dynamic_cast<Class_alias*>(in);
    if(that == NULL) return false;
    
    if(this->alias == NULL)
    {
    	if(that->alias != NULL && !that->alias->match(this->alias))
    		return false;
    }
    else if(!this->alias->match(that->alias))
    	return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    return true;
}

bool Class_alias::equals(Node* in)
{
    Class_alias* that = dynamic_cast<Class_alias*>(in);
    if(that == NULL) return false;
    
    if(this->alias == NULL || that->alias == NULL)
    {
    	if(this->alias != NULL || that->alias != NULL)
    		return false;
    }
    else if(!this->alias->equals(that->alias))
    	return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    return true;
}

Class_alias* Class_alias::clone()
{
    CLASS_NAME* alias = this->alias ? this->alias->clone() : NULL;
    CLASS_NAME* class_name = this->class_name ? this->class_name->clone() : NULL;
    Class_alias* clone = new Class_alias(alias, class_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Class_alias::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->alias != NULL)
    {
    	Node* alias_res = this->alias->find(in);
    	if (alias_res) return alias_res;
    }
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    return NULL;
}

void Class_alias::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->alias != NULL)
    	this->alias->find_all(in, out);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
}

void Class_alias::assert_valid()
{
    assert(alias != NULL);
    alias->assert_valid();
    assert(class_name != NULL);
    class_name->assert_valid();
    Node::assert_mixin_valid();
}

Interface_alias::Interface_alias(INTERFACE_NAME* alias, INTERFACE_NAME* interface_name)
{
    this->alias = alias;
    this->interface_name = interface_name;
}

Interface_alias::Interface_alias()
{
    this->alias = 0;
    this->interface_name = 0;
}

void Interface_alias::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Interface_alias::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Interface_alias::ID;
int Interface_alias::classid()
{
    return ID;
}

bool Interface_alias::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Interface_alias* that = dynamic_cast<Interface_alias*>(in);
    if(that == NULL) return false;
    
    if(this->alias == NULL)
    {
    	if(that->alias != NULL && !that->alias->match(this->alias))
    		return false;
    }
    else if(!this->alias->match(that->alias))
    	return false;
    
    if(this->interface_name == NULL)
    {
    	if(that->interface_name != NULL && !that->interface_name->match(this->interface_name))
    		return false;
    }
    else if(!this->interface_name->match(that->interface_name))
    	return false;
    
    return true;
}

bool Interface_alias::equals(Node* in)
{
    Interface_alias* that = dynamic_cast<Interface_alias*>(in);
    if(that == NULL) return false;
    
    if(this->alias == NULL || that->alias == NULL)
    {
    	if(this->alias != NULL || that->alias != NULL)
    		return false;
    }
    else if(!this->alias->equals(that->alias))
    	return false;
    
    if(this->interface_name == NULL || that->interface_name == NULL)
    {
    	if(this->interface_name != NULL || that->interface_name != NULL)
    		return false;
    }
    else if(!this->interface_name->equals(that->interface_name))
    	return false;
    
    return true;
}

Interface_alias* Interface_alias::clone()
{
    INTERFACE_NAME* alias = this->alias ? this->alias->clone() : NULL;
    INTERFACE_NAME* interface_name = this->interface_name ? this->interface_name->clone() : NULL;
    Interface_alias* clone = new Interface_alias(alias, interface_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Interface_alias::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->alias != NULL)
    {
    	Node* alias_res = this->alias->find(in);
    	if (alias_res) return alias_res;
    }
    
    if (this->interface_name != NULL)
    {
    	Node* interface_name_res = this->interface_name->find(in);
    	if (interface_name_res) return interface_name_res;
    }
    
    return NULL;
}

void Interface_alias::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->alias != NULL)
    	this->alias->find_all(in, out);
    
    if (this->interface_name != NULL)
    	this->interface_name->find_all(in, out);
    
}

void Interface_alias::assert_valid()
{
    assert(alias != NULL);
    alias->assert_valid();
    assert(interface_name != NULL);
    interface_name->assert_valid();
    Node::assert_mixin_valid();
}

Method_alias::Method_alias(METHOD_NAME* alias, METHOD_NAME* method_name)
{
    this->alias = alias;
    this->method_name = method_name;
}

Method_alias::Method_alias()
{
    this->alias = 0;
    this->method_name = 0;
}

void Method_alias::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Method_alias::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Method_alias::ID;
int Method_alias::classid()
{
    return ID;
}

bool Method_alias::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Method_alias* that = dynamic_cast<Method_alias*>(in);
    if(that == NULL) return false;
    
    if(this->alias == NULL)
    {
    	if(that->alias != NULL && !that->alias->match(this->alias))
    		return false;
    }
    else if(!this->alias->match(that->alias))
    	return false;
    
    if(this->method_name == NULL)
    {
    	if(that->method_name != NULL && !that->method_name->match(this->method_name))
    		return false;
    }
    else if(!this->method_name->match(that->method_name))
    	return false;
    
    return true;
}

bool Method_alias::equals(Node* in)
{
    Method_alias* that = dynamic_cast<Method_alias*>(in);
    if(that == NULL) return false;
    
    if(this->alias == NULL || that->alias == NULL)
    {
    	if(this->alias != NULL || that->alias != NULL)
    		return false;
    }
    else if(!this->alias->equals(that->alias))
    	return false;
    
    if(this->method_name == NULL || that->method_name == NULL)
    {
    	if(this->method_name != NULL || that->method_name != NULL)
    		return false;
    }
    else if(!this->method_name->equals(that->method_name))
    	return false;
    
    return true;
}

Method_alias* Method_alias::clone()
{
    METHOD_NAME* alias = this->alias ? this->alias->clone() : NULL;
    METHOD_NAME* method_name = this->method_name ? this->method_name->clone() : NULL;
    Method_alias* clone = new Method_alias(alias, method_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Method_alias::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->alias != NULL)
    {
    	Node* alias_res = this->alias->find(in);
    	if (alias_res) return alias_res;
    }
    
    if (this->method_name != NULL)
    {
    	Node* method_name_res = this->method_name->find(in);
    	if (method_name_res) return method_name_res;
    }
    
    return NULL;
}

void Method_alias::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->alias != NULL)
    	this->alias->find_all(in, out);
    
    if (this->method_name != NULL)
    	this->method_name->find_all(in, out);
    
}

void Method_alias::assert_valid()
{
    assert(alias != NULL);
    alias->assert_valid();
    assert(method_name != NULL);
    method_name->assert_valid();
    Node::assert_mixin_valid();
}

Return::Return(Rvalue* rvalue)
{
    this->rvalue = rvalue;
}

Return::Return()
{
    this->rvalue = 0;
}

void Return::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Return::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Return::ID;
int Return::classid()
{
    return ID;
}

bool Return::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Return* that = dynamic_cast<Return*>(in);
    if(that == NULL) return false;
    
    if(this->rvalue == NULL)
    {
    	if(that->rvalue != NULL && !that->rvalue->match(this->rvalue))
    		return false;
    }
    else if(!this->rvalue->match(that->rvalue))
    	return false;
    
    return true;
}

bool Return::equals(Node* in)
{
    Return* that = dynamic_cast<Return*>(in);
    if(that == NULL) return false;
    
    if(this->rvalue == NULL || that->rvalue == NULL)
    {
    	if(this->rvalue != NULL || that->rvalue != NULL)
    		return false;
    }
    else if(!this->rvalue->equals(that->rvalue))
    	return false;
    
    return true;
}

Return* Return::clone()
{
    Rvalue* rvalue = this->rvalue ? this->rvalue->clone() : NULL;
    Return* clone = new Return(rvalue);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Return::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->rvalue != NULL)
    {
    	Node* rvalue_res = this->rvalue->find(in);
    	if (rvalue_res) return rvalue_res;
    }
    
    return NULL;
}

void Return::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->rvalue != NULL)
    	this->rvalue->find_all(in, out);
    
}

void Return::assert_valid()
{
    assert(rvalue != NULL);
    rvalue->assert_valid();
    Node::assert_mixin_valid();
}

Static_declaration::Static_declaration(Name_with_default* var)
{
    this->var = var;
}

Static_declaration::Static_declaration()
{
    this->var = 0;
}

void Static_declaration::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Static_declaration::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Static_declaration::ID;
int Static_declaration::classid()
{
    return ID;
}

bool Static_declaration::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Static_declaration* that = dynamic_cast<Static_declaration*>(in);
    if(that == NULL) return false;
    
    if(this->var == NULL)
    {
    	if(that->var != NULL && !that->var->match(this->var))
    		return false;
    }
    else if(!this->var->match(that->var))
    	return false;
    
    return true;
}

bool Static_declaration::equals(Node* in)
{
    Static_declaration* that = dynamic_cast<Static_declaration*>(in);
    if(that == NULL) return false;
    
    if(this->var == NULL || that->var == NULL)
    {
    	if(this->var != NULL || that->var != NULL)
    		return false;
    }
    else if(!this->var->equals(that->var))
    	return false;
    
    return true;
}

Static_declaration* Static_declaration::clone()
{
    Name_with_default* var = this->var ? this->var->clone() : NULL;
    Static_declaration* clone = new Static_declaration(var);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Static_declaration::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->var != NULL)
    {
    	Node* var_res = this->var->find(in);
    	if (var_res) return var_res;
    }
    
    return NULL;
}

void Static_declaration::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->var != NULL)
    	this->var->find_all(in, out);
    
}

void Static_declaration::assert_valid()
{
    assert(var != NULL);
    var->assert_valid();
    Node::assert_mixin_valid();
}

Global::Global(Variable_name* variable_name)
{
    this->variable_name = variable_name;
}

Global::Global()
{
    this->variable_name = 0;
}

void Global::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Global::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Global::ID;
int Global::classid()
{
    return ID;
}

bool Global::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Global* that = dynamic_cast<Global*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Global::equals(Node* in)
{
    Global* that = dynamic_cast<Global*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Global* Global::clone()
{
    Variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Global* clone = new Global(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Global::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Global::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Global::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Try::Try(Statement_list* statements, Catch_list* catches)
{
    this->statements = statements;
    this->catches = catches;
}

Try::Try()
{
    this->statements = 0;
    this->catches = 0;
}

void Try::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Try::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Try::ID;
int Try::classid()
{
    return ID;
}

bool Try::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Try* that = dynamic_cast<Try*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    if(this->catches != NULL && that->catches != NULL)
    {
    	Catch_list::const_iterator i, j;
    	for(
    		i = this->catches->begin(), j = that->catches->begin();
    		i != this->catches->end() && j != that->catches->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->catches->end() || j != that->catches->end())
    		return false;
    }
    
    return true;
}

bool Try::equals(Node* in)
{
    Try* that = dynamic_cast<Try*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->statements->begin(), j = that->statements->begin();
    		i != this->statements->end() && j != that->statements->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->statements->end() || j != that->statements->end())
    		return false;
    }
    
    if(this->catches == NULL || that->catches == NULL)
    {
    	if(this->catches != NULL || that->catches != NULL)
    		return false;
    }
    else
    {
    	Catch_list::const_iterator i, j;
    	for(
    		i = this->catches->begin(), j = that->catches->begin();
    		i != this->catches->end() && j != that->catches->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->catches->end() || j != that->catches->end())
    		return false;
    }
    
    return true;
}

Try* Try::clone()
{
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Catch_list* catches = NULL;
    if(this->catches != NULL)
    {
    	Catch_list::const_iterator i;
    	catches = new Catch_list;
    	for(i = this->catches->begin(); i != this->catches->end(); i++)
    		catches->push_back(*i ? (*i)->clone() : NULL);
    }
    Try* clone = new Try(statements, catches);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Try::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if(this->catches != NULL)
    {
    	Catch_list::const_iterator i;
    	for(
    		i = this->catches->begin();
    		i != this->catches->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Try::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->statements->begin();
    		i != this->statements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if(this->catches != NULL)
    {
    	Catch_list::const_iterator i;
    	for(
    		i = this->catches->begin();
    		i != this->catches->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Try::assert_valid()
{
    assert(statements != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(catches != NULL);
    {
    	Catch_list::const_iterator i;
    	for(i = this->catches->begin(); i != this->catches->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Throw::Throw(VARIABLE_NAME* variable_name)
{
    this->variable_name = variable_name;
}

Throw::Throw()
{
    this->variable_name = 0;
}

void Throw::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Throw::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Throw::ID;
int Throw::classid()
{
    return ID;
}

bool Throw::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Throw* that = dynamic_cast<Throw*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Throw::equals(Node* in)
{
    Throw* that = dynamic_cast<Throw*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Throw* Throw::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Throw* clone = new Throw(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Throw::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Throw::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Throw::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Assign_var::Assign_var()
{
    this->lhs = 0;
    this->is_ref = 0;
    this->rhs = 0;
}

void Assign_var::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_var::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Assign_var::ID;
int Assign_var::classid()
{
    return ID;
}

bool Assign_var::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_var* that = dynamic_cast<Assign_var*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_var::equals(Node* in)
{
    Assign_var* that = dynamic_cast<Assign_var*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->rhs == NULL || that->rhs == NULL)
    {
    	if(this->rhs != NULL || that->rhs != NULL)
    		return false;
    }
    else if(!this->rhs->equals(that->rhs))
    	return false;
    
    return true;
}

Assign_var* Assign_var::clone()
{
    VARIABLE_NAME* lhs = this->lhs ? this->lhs->clone() : NULL;
    bool is_ref = this->is_ref;
    Expr* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_var* clone = new Assign_var(lhs, is_ref, rhs);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Assign_var::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->lhs != NULL)
    {
    	Node* lhs_res = this->lhs->find(in);
    	if (lhs_res) return lhs_res;
    }
    
    if (this->rhs != NULL)
    {
    	Node* rhs_res = this->rhs->find(in);
    	if (rhs_res) return rhs_res;
    }
    
    return NULL;
}

void Assign_var::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_var::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
    Node::assert_mixin_valid();
}

Assign_var::Assign_var(VARIABLE_NAME* lhs, Expr* rhs)
{
    {
		this->lhs = lhs;
		this->is_ref = false;
		this->rhs = rhs;
	}
}

Assign_var::Assign_var(VARIABLE_NAME* lhs, bool is_ref, Expr* rhs)
{
    {
		this->lhs = lhs;
		this->is_ref = is_ref;
		this->rhs = rhs;
	}
}

Assign_field::Assign_field(Target* target, Field_name* field_name, bool is_ref, Rvalue* rhs)
{
    this->target = target;
    this->field_name = field_name;
    this->is_ref = is_ref;
    this->rhs = rhs;
}

Assign_field::Assign_field()
{
    this->target = 0;
    this->field_name = 0;
    this->is_ref = 0;
    this->rhs = 0;
}

void Assign_field::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_field::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Assign_field::ID;
int Assign_field::classid()
{
    return ID;
}

bool Assign_field::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_field* that = dynamic_cast<Assign_field*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL)
    {
    	if(that->target != NULL && !that->target->match(this->target))
    		return false;
    }
    else if(!this->target->match(that->target))
    	return false;
    
    if(this->field_name == NULL)
    {
    	if(that->field_name != NULL && !that->field_name->match(this->field_name))
    		return false;
    }
    else if(!this->field_name->match(that->field_name))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_field::equals(Node* in)
{
    Assign_field* that = dynamic_cast<Assign_field*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL || that->target == NULL)
    {
    	if(this->target != NULL || that->target != NULL)
    		return false;
    }
    else if(!this->target->equals(that->target))
    	return false;
    
    if(this->field_name == NULL || that->field_name == NULL)
    {
    	if(this->field_name != NULL || that->field_name != NULL)
    		return false;
    }
    else if(!this->field_name->equals(that->field_name))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->rhs == NULL || that->rhs == NULL)
    {
    	if(this->rhs != NULL || that->rhs != NULL)
    		return false;
    }
    else if(!this->rhs->equals(that->rhs))
    	return false;
    
    return true;
}

Assign_field* Assign_field::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Field_name* field_name = this->field_name ? this->field_name->clone() : NULL;
    bool is_ref = this->is_ref;
    Rvalue* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_field* clone = new Assign_field(target, field_name, is_ref, rhs);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Assign_field::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->target != NULL)
    {
    	Node* target_res = this->target->find(in);
    	if (target_res) return target_res;
    }
    
    if (this->field_name != NULL)
    {
    	Node* field_name_res = this->field_name->find(in);
    	if (field_name_res) return field_name_res;
    }
    
    if (this->rhs != NULL)
    {
    	Node* rhs_res = this->rhs->find(in);
    	if (rhs_res) return rhs_res;
    }
    
    return NULL;
}

void Assign_field::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->field_name != NULL)
    	this->field_name->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_field::assert_valid()
{
    assert(target != NULL);
    target->assert_valid();
    assert(field_name != NULL);
    field_name->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
    Node::assert_mixin_valid();
}

Assign_array::Assign_array(VARIABLE_NAME* lhs, Rvalue* index, bool is_ref, Rvalue* rhs)
{
    this->lhs = lhs;
    this->index = index;
    this->is_ref = is_ref;
    this->rhs = rhs;
}

Assign_array::Assign_array()
{
    this->lhs = 0;
    this->index = 0;
    this->is_ref = 0;
    this->rhs = 0;
}

void Assign_array::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_array::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Assign_array::ID;
int Assign_array::classid()
{
    return ID;
}

bool Assign_array::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_array* that = dynamic_cast<Assign_array*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    if(this->index == NULL)
    {
    	if(that->index != NULL && !that->index->match(this->index))
    		return false;
    }
    else if(!this->index->match(that->index))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_array::equals(Node* in)
{
    Assign_array* that = dynamic_cast<Assign_array*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
    	return false;
    
    if(this->index == NULL || that->index == NULL)
    {
    	if(this->index != NULL || that->index != NULL)
    		return false;
    }
    else if(!this->index->equals(that->index))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->rhs == NULL || that->rhs == NULL)
    {
    	if(this->rhs != NULL || that->rhs != NULL)
    		return false;
    }
    else if(!this->rhs->equals(that->rhs))
    	return false;
    
    return true;
}

Assign_array* Assign_array::clone()
{
    VARIABLE_NAME* lhs = this->lhs ? this->lhs->clone() : NULL;
    Rvalue* index = this->index ? this->index->clone() : NULL;
    bool is_ref = this->is_ref;
    Rvalue* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_array* clone = new Assign_array(lhs, index, is_ref, rhs);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Assign_array::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->lhs != NULL)
    {
    	Node* lhs_res = this->lhs->find(in);
    	if (lhs_res) return lhs_res;
    }
    
    if (this->index != NULL)
    {
    	Node* index_res = this->index->find(in);
    	if (index_res) return index_res;
    }
    
    if (this->rhs != NULL)
    {
    	Node* rhs_res = this->rhs->find(in);
    	if (rhs_res) return rhs_res;
    }
    
    return NULL;
}

void Assign_array::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->index != NULL)
    	this->index->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_array::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(index != NULL);
    index->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
    Node::assert_mixin_valid();
}

Assign_var_var::Assign_var_var(VARIABLE_NAME* lhs, bool is_ref, Rvalue* rhs)
{
    this->lhs = lhs;
    this->is_ref = is_ref;
    this->rhs = rhs;
}

Assign_var_var::Assign_var_var()
{
    this->lhs = 0;
    this->is_ref = 0;
    this->rhs = 0;
}

void Assign_var_var::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_var_var::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Assign_var_var::ID;
int Assign_var_var::classid()
{
    return ID;
}

bool Assign_var_var::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_var_var* that = dynamic_cast<Assign_var_var*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_var_var::equals(Node* in)
{
    Assign_var_var* that = dynamic_cast<Assign_var_var*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->rhs == NULL || that->rhs == NULL)
    {
    	if(this->rhs != NULL || that->rhs != NULL)
    		return false;
    }
    else if(!this->rhs->equals(that->rhs))
    	return false;
    
    return true;
}

Assign_var_var* Assign_var_var::clone()
{
    VARIABLE_NAME* lhs = this->lhs ? this->lhs->clone() : NULL;
    bool is_ref = this->is_ref;
    Rvalue* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_var_var* clone = new Assign_var_var(lhs, is_ref, rhs);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Assign_var_var::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->lhs != NULL)
    {
    	Node* lhs_res = this->lhs->find(in);
    	if (lhs_res) return lhs_res;
    }
    
    if (this->rhs != NULL)
    {
    	Node* rhs_res = this->rhs->find(in);
    	if (rhs_res) return rhs_res;
    }
    
    return NULL;
}

void Assign_var_var::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_var_var::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
    Node::assert_mixin_valid();
}

Assign_next::Assign_next(VARIABLE_NAME* lhs, bool is_ref, Rvalue* rhs)
{
    this->lhs = lhs;
    this->is_ref = is_ref;
    this->rhs = rhs;
}

Assign_next::Assign_next()
{
    this->lhs = 0;
    this->is_ref = 0;
    this->rhs = 0;
}

void Assign_next::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_next::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Assign_next::ID;
int Assign_next::classid()
{
    return ID;
}

bool Assign_next::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_next* that = dynamic_cast<Assign_next*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_next::equals(Node* in)
{
    Assign_next* that = dynamic_cast<Assign_next*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->rhs == NULL || that->rhs == NULL)
    {
    	if(this->rhs != NULL || that->rhs != NULL)
    		return false;
    }
    else if(!this->rhs->equals(that->rhs))
    	return false;
    
    return true;
}

Assign_next* Assign_next::clone()
{
    VARIABLE_NAME* lhs = this->lhs ? this->lhs->clone() : NULL;
    bool is_ref = this->is_ref;
    Rvalue* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_next* clone = new Assign_next(lhs, is_ref, rhs);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Assign_next::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->lhs != NULL)
    {
    	Node* lhs_res = this->lhs->find(in);
    	if (lhs_res) return lhs_res;
    }
    
    if (this->rhs != NULL)
    {
    	Node* rhs_res = this->rhs->find(in);
    	if (rhs_res) return rhs_res;
    }
    
    return NULL;
}

void Assign_next::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_next::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
    Node::assert_mixin_valid();
}

Pre_op::Pre_op(OP* op, VARIABLE_NAME* variable_name)
{
    this->op = op;
    this->variable_name = variable_name;
}

Pre_op::Pre_op()
{
    this->op = 0;
    this->variable_name = 0;
}

void Pre_op::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Pre_op::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Pre_op::ID;
int Pre_op::classid()
{
    return ID;
}

bool Pre_op::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Pre_op* that = dynamic_cast<Pre_op*>(in);
    if(that == NULL) return false;
    
    if(this->op == NULL)
    {
    	if(that->op != NULL && !that->op->match(this->op))
    		return false;
    }
    else if(!this->op->match(that->op))
    	return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Pre_op::equals(Node* in)
{
    Pre_op* that = dynamic_cast<Pre_op*>(in);
    if(that == NULL) return false;
    
    if(this->op == NULL || that->op == NULL)
    {
    	if(this->op != NULL || that->op != NULL)
    		return false;
    }
    else if(!this->op->equals(that->op))
    	return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Pre_op* Pre_op::clone()
{
    OP* op = this->op ? this->op->clone() : NULL;
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Pre_op* clone = new Pre_op(op, variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Pre_op::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->op != NULL)
    {
    	Node* op_res = this->op->find(in);
    	if (op_res) return op_res;
    }
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Pre_op::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Pre_op::assert_valid()
{
    assert(op != NULL);
    op->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Pre_op::Pre_op(VARIABLE_NAME* variable_name, const char* op)
{
    {
		this->variable_name = variable_name;
		this->op = new OP(new String(op));
	}
}

Eval_expr::Eval_expr(Expr* expr)
{
    this->expr = expr;
}

Eval_expr::Eval_expr()
{
    this->expr = 0;
}

void Eval_expr::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Eval_expr::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Eval_expr::ID;
int Eval_expr::classid()
{
    return ID;
}

bool Eval_expr::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Eval_expr* that = dynamic_cast<Eval_expr*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Eval_expr::equals(Node* in)
{
    Eval_expr* that = dynamic_cast<Eval_expr*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    return true;
}

Eval_expr* Eval_expr::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Eval_expr* clone = new Eval_expr(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Eval_expr::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Eval_expr::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Eval_expr::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Unset::Unset(Target* target, Variable_name* variable_name, Rvalue_list* array_indices)
{
    this->target = target;
    this->variable_name = variable_name;
    this->array_indices = array_indices;
}

Unset::Unset()
{
    this->target = 0;
    this->variable_name = 0;
    this->array_indices = 0;
}

void Unset::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Unset::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Unset::ID;
int Unset::classid()
{
    return ID;
}

bool Unset::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Unset* that = dynamic_cast<Unset*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL)
    {
    	if(that->target != NULL && !that->target->match(this->target))
    		return false;
    }
    else if(!this->target->match(that->target))
    	return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->array_indices != NULL && that->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i, j;
    	for(
    		i = this->array_indices->begin(), j = that->array_indices->begin();
    		i != this->array_indices->end() && j != that->array_indices->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->array_indices->end() || j != that->array_indices->end())
    		return false;
    }
    
    return true;
}

bool Unset::equals(Node* in)
{
    Unset* that = dynamic_cast<Unset*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL || that->target == NULL)
    {
    	if(this->target != NULL || that->target != NULL)
    		return false;
    }
    else if(!this->target->equals(that->target))
    	return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->array_indices == NULL || that->array_indices == NULL)
    {
    	if(this->array_indices != NULL || that->array_indices != NULL)
    		return false;
    }
    else
    {
    	Rvalue_list::const_iterator i, j;
    	for(
    		i = this->array_indices->begin(), j = that->array_indices->begin();
    		i != this->array_indices->end() && j != that->array_indices->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->array_indices->end() || j != that->array_indices->end())
    		return false;
    }
    
    return true;
}

Unset* Unset::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Rvalue_list* array_indices = NULL;
    if(this->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i;
    	array_indices = new Rvalue_list;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    		array_indices->push_back(*i ? (*i)->clone() : NULL);
    }
    Unset* clone = new Unset(target, variable_name, array_indices);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Unset::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->target != NULL)
    {
    	Node* target_res = this->target->find(in);
    	if (target_res) return target_res;
    }
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if(this->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i;
    	for(
    		i = this->array_indices->begin();
    		i != this->array_indices->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Unset::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if(this->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i;
    	for(
    		i = this->array_indices->begin();
    		i != this->array_indices->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Unset::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(array_indices != NULL);
    {
    	Rvalue_list::const_iterator i;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Isset::Isset(Target* target, Variable_name* variable_name, Rvalue_list* array_indices)
{
    this->target = target;
    this->variable_name = variable_name;
    this->array_indices = array_indices;
}

Isset::Isset()
{
    this->target = 0;
    this->variable_name = 0;
    this->array_indices = 0;
}

void Isset::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Isset::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Isset::ID;
int Isset::classid()
{
    return ID;
}

bool Isset::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Isset* that = dynamic_cast<Isset*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL)
    {
    	if(that->target != NULL && !that->target->match(this->target))
    		return false;
    }
    else if(!this->target->match(that->target))
    	return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->array_indices != NULL && that->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i, j;
    	for(
    		i = this->array_indices->begin(), j = that->array_indices->begin();
    		i != this->array_indices->end() && j != that->array_indices->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->array_indices->end() || j != that->array_indices->end())
    		return false;
    }
    
    return true;
}

bool Isset::equals(Node* in)
{
    Isset* that = dynamic_cast<Isset*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL || that->target == NULL)
    {
    	if(this->target != NULL || that->target != NULL)
    		return false;
    }
    else if(!this->target->equals(that->target))
    	return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->array_indices == NULL || that->array_indices == NULL)
    {
    	if(this->array_indices != NULL || that->array_indices != NULL)
    		return false;
    }
    else
    {
    	Rvalue_list::const_iterator i, j;
    	for(
    		i = this->array_indices->begin(), j = that->array_indices->begin();
    		i != this->array_indices->end() && j != that->array_indices->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->array_indices->end() || j != that->array_indices->end())
    		return false;
    }
    
    return true;
}

Isset* Isset::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Rvalue_list* array_indices = NULL;
    if(this->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i;
    	array_indices = new Rvalue_list;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    		array_indices->push_back(*i ? (*i)->clone() : NULL);
    }
    Isset* clone = new Isset(target, variable_name, array_indices);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Isset::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->target != NULL)
    {
    	Node* target_res = this->target->find(in);
    	if (target_res) return target_res;
    }
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if(this->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i;
    	for(
    		i = this->array_indices->begin();
    		i != this->array_indices->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Isset::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if(this->array_indices != NULL)
    {
    	Rvalue_list::const_iterator i;
    	for(
    		i = this->array_indices->begin();
    		i != this->array_indices->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Isset::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(array_indices != NULL);
    {
    	Rvalue_list::const_iterator i;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Rvalue::Rvalue()
{
}

Field_access::Field_access(Target* target, Field_name* field_name)
{
    this->target = target;
    this->field_name = field_name;
}

Field_access::Field_access()
{
    this->target = 0;
    this->field_name = 0;
}

void Field_access::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Field_access::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Field_access::ID;
int Field_access::classid()
{
    return ID;
}

bool Field_access::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Field_access* that = dynamic_cast<Field_access*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL)
    {
    	if(that->target != NULL && !that->target->match(this->target))
    		return false;
    }
    else if(!this->target->match(that->target))
    	return false;
    
    if(this->field_name == NULL)
    {
    	if(that->field_name != NULL && !that->field_name->match(this->field_name))
    		return false;
    }
    else if(!this->field_name->match(that->field_name))
    	return false;
    
    return true;
}

bool Field_access::equals(Node* in)
{
    Field_access* that = dynamic_cast<Field_access*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL || that->target == NULL)
    {
    	if(this->target != NULL || that->target != NULL)
    		return false;
    }
    else if(!this->target->equals(that->target))
    	return false;
    
    if(this->field_name == NULL || that->field_name == NULL)
    {
    	if(this->field_name != NULL || that->field_name != NULL)
    		return false;
    }
    else if(!this->field_name->equals(that->field_name))
    	return false;
    
    return true;
}

Field_access* Field_access::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Field_name* field_name = this->field_name ? this->field_name->clone() : NULL;
    Field_access* clone = new Field_access(target, field_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Field_access::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->target != NULL)
    {
    	Node* target_res = this->target->find(in);
    	if (target_res) return target_res;
    }
    
    if (this->field_name != NULL)
    {
    	Node* field_name_res = this->field_name->find(in);
    	if (field_name_res) return field_name_res;
    }
    
    return NULL;
}

void Field_access::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->field_name != NULL)
    	this->field_name->find_all(in, out);
    
}

void Field_access::assert_valid()
{
    assert(target != NULL);
    target->assert_valid();
    assert(field_name != NULL);
    field_name->assert_valid();
    Node::assert_mixin_valid();
}

Field_access::Field_access(Target* target, const char* name)
{
    {
		this->target = target;
		this->field_name = new FIELD_NAME (name);
	}
}

Array_access::Array_access(VARIABLE_NAME* variable_name, Rvalue* index)
{
    this->variable_name = variable_name;
    this->index = index;
}

Array_access::Array_access()
{
    this->variable_name = 0;
    this->index = 0;
}

void Array_access::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Array_access::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Array_access::ID;
int Array_access::classid()
{
    return ID;
}

bool Array_access::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Array_access* that = dynamic_cast<Array_access*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->index == NULL)
    {
    	if(that->index != NULL && !that->index->match(this->index))
    		return false;
    }
    else if(!this->index->match(that->index))
    	return false;
    
    return true;
}

bool Array_access::equals(Node* in)
{
    Array_access* that = dynamic_cast<Array_access*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->index == NULL || that->index == NULL)
    {
    	if(this->index != NULL || that->index != NULL)
    		return false;
    }
    else if(!this->index->equals(that->index))
    	return false;
    
    return true;
}

Array_access* Array_access::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Rvalue* index = this->index ? this->index->clone() : NULL;
    Array_access* clone = new Array_access(variable_name, index);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Array_access::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if (this->index != NULL)
    {
    	Node* index_res = this->index->find(in);
    	if (index_res) return index_res;
    }
    
    return NULL;
}

void Array_access::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if (this->index != NULL)
    	this->index->find_all(in, out);
    
}

void Array_access::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(index != NULL);
    index->assert_valid();
    Node::assert_mixin_valid();
}

Array_next::Array_next(VARIABLE_NAME* variable_name)
{
    this->variable_name = variable_name;
}

Array_next::Array_next()
{
    this->variable_name = 0;
}

void Array_next::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Array_next::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Array_next::ID;
int Array_next::classid()
{
    return ID;
}

bool Array_next::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Array_next* that = dynamic_cast<Array_next*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Array_next::equals(Node* in)
{
    Array_next* that = dynamic_cast<Array_next*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Array_next* Array_next::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Array_next* clone = new Array_next(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Array_next::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Array_next::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Array_next::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Cast::Cast(CAST* cast, VARIABLE_NAME* variable_name)
{
    this->cast = cast;
    this->variable_name = variable_name;
}

Cast::Cast()
{
    this->cast = 0;
    this->variable_name = 0;
}

void Cast::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Cast::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Cast::ID;
int Cast::classid()
{
    return ID;
}

bool Cast::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Cast* that = dynamic_cast<Cast*>(in);
    if(that == NULL) return false;
    
    if(this->cast == NULL)
    {
    	if(that->cast != NULL && !that->cast->match(this->cast))
    		return false;
    }
    else if(!this->cast->match(that->cast))
    	return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Cast::equals(Node* in)
{
    Cast* that = dynamic_cast<Cast*>(in);
    if(that == NULL) return false;
    
    if(this->cast == NULL || that->cast == NULL)
    {
    	if(this->cast != NULL || that->cast != NULL)
    		return false;
    }
    else if(!this->cast->equals(that->cast))
    	return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Cast* Cast::clone()
{
    CAST* cast = this->cast ? this->cast->clone() : NULL;
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Cast* clone = new Cast(cast, variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Cast::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->cast != NULL)
    {
    	Node* cast_res = this->cast->find(in);
    	if (cast_res) return cast_res;
    }
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Cast::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->cast != NULL)
    	this->cast->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Cast::assert_valid()
{
    assert(cast != NULL);
    cast->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Cast::Cast(const char* type, VARIABLE_NAME* variable_name)
{
    {
		this->cast = new CAST(new String(type));
		this->variable_name = variable_name;
	}
}

Unary_op::Unary_op(OP* op, VARIABLE_NAME* variable_name)
{
    this->op = op;
    this->variable_name = variable_name;
}

Unary_op::Unary_op()
{
    this->op = 0;
    this->variable_name = 0;
}

void Unary_op::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Unary_op::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Unary_op::ID;
int Unary_op::classid()
{
    return ID;
}

bool Unary_op::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Unary_op* that = dynamic_cast<Unary_op*>(in);
    if(that == NULL) return false;
    
    if(this->op == NULL)
    {
    	if(that->op != NULL && !that->op->match(this->op))
    		return false;
    }
    else if(!this->op->match(that->op))
    	return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Unary_op::equals(Node* in)
{
    Unary_op* that = dynamic_cast<Unary_op*>(in);
    if(that == NULL) return false;
    
    if(this->op == NULL || that->op == NULL)
    {
    	if(this->op != NULL || that->op != NULL)
    		return false;
    }
    else if(!this->op->equals(that->op))
    	return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Unary_op* Unary_op::clone()
{
    OP* op = this->op ? this->op->clone() : NULL;
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Unary_op* clone = new Unary_op(op, variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Unary_op::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->op != NULL)
    {
    	Node* op_res = this->op->find(in);
    	if (op_res) return op_res;
    }
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Unary_op::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Unary_op::assert_valid()
{
    assert(op != NULL);
    op->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Unary_op::Unary_op(VARIABLE_NAME* variable_name, const char* op)
{
    {
		this->variable_name = variable_name;
		this->op = new OP(new String(op));
	}
}

Bin_op::Bin_op(Rvalue* left, OP* op, Rvalue* right)
{
    this->left = left;
    this->op = op;
    this->right = right;
}

Bin_op::Bin_op()
{
    this->left = 0;
    this->op = 0;
    this->right = 0;
}

void Bin_op::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Bin_op::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Bin_op::ID;
int Bin_op::classid()
{
    return ID;
}

bool Bin_op::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Bin_op* that = dynamic_cast<Bin_op*>(in);
    if(that == NULL) return false;
    
    if(this->left == NULL)
    {
    	if(that->left != NULL && !that->left->match(this->left))
    		return false;
    }
    else if(!this->left->match(that->left))
    	return false;
    
    if(this->op == NULL)
    {
    	if(that->op != NULL && !that->op->match(this->op))
    		return false;
    }
    else if(!this->op->match(that->op))
    	return false;
    
    if(this->right == NULL)
    {
    	if(that->right != NULL && !that->right->match(this->right))
    		return false;
    }
    else if(!this->right->match(that->right))
    	return false;
    
    return true;
}

bool Bin_op::equals(Node* in)
{
    Bin_op* that = dynamic_cast<Bin_op*>(in);
    if(that == NULL) return false;
    
    if(this->left == NULL || that->left == NULL)
    {
    	if(this->left != NULL || that->left != NULL)
    		return false;
    }
    else if(!this->left->equals(that->left))
    	return false;
    
    if(this->op == NULL || that->op == NULL)
    {
    	if(this->op != NULL || that->op != NULL)
    		return false;
    }
    else if(!this->op->equals(that->op))
    	return false;
    
    if(this->right == NULL || that->right == NULL)
    {
    	if(this->right != NULL || that->right != NULL)
    		return false;
    }
    else if(!this->right->equals(that->right))
    	return false;
    
    return true;
}

Bin_op* Bin_op::clone()
{
    Rvalue* left = this->left ? this->left->clone() : NULL;
    OP* op = this->op ? this->op->clone() : NULL;
    Rvalue* right = this->right ? this->right->clone() : NULL;
    Bin_op* clone = new Bin_op(left, op, right);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Bin_op::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->left != NULL)
    {
    	Node* left_res = this->left->find(in);
    	if (left_res) return left_res;
    }
    
    if (this->op != NULL)
    {
    	Node* op_res = this->op->find(in);
    	if (op_res) return op_res;
    }
    
    if (this->right != NULL)
    {
    	Node* right_res = this->right->find(in);
    	if (right_res) return right_res;
    }
    
    return NULL;
}

void Bin_op::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->left != NULL)
    	this->left->find_all(in, out);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
    if (this->right != NULL)
    	this->right->find_all(in, out);
    
}

void Bin_op::assert_valid()
{
    assert(left != NULL);
    left->assert_valid();
    assert(op != NULL);
    op->assert_valid();
    assert(right != NULL);
    right->assert_valid();
    Node::assert_mixin_valid();
}

Bin_op::Bin_op(VARIABLE_NAME* left, VARIABLE_NAME* right, const char* op)
{
    {
		this->left = left;
		this->op = new OP(new String(op));
		this->right = right;
	}
}

Constant::Constant(CLASS_NAME* class_name, CONSTANT_NAME* constant_name)
{
    this->class_name = class_name;
    this->constant_name = constant_name;
}

Constant::Constant()
{
    this->class_name = 0;
    this->constant_name = 0;
}

void Constant::visit(Visitor* visitor)
{
    visitor->visit_static_array_key(this);
}

void Constant::transform_children(Transform* transform)
{
    transform->children_static_array_key(this);
}

const int Constant::ID;
int Constant::classid()
{
    return ID;
}

bool Constant::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Constant* that = dynamic_cast<Constant*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    if(this->constant_name == NULL)
    {
    	if(that->constant_name != NULL && !that->constant_name->match(this->constant_name))
    		return false;
    }
    else if(!this->constant_name->match(that->constant_name))
    	return false;
    
    return true;
}

bool Constant::equals(Node* in)
{
    Constant* that = dynamic_cast<Constant*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    if(this->constant_name == NULL || that->constant_name == NULL)
    {
    	if(this->constant_name != NULL || that->constant_name != NULL)
    		return false;
    }
    else if(!this->constant_name->equals(that->constant_name))
    	return false;
    
    return true;
}

Constant* Constant::clone()
{
    CLASS_NAME* class_name = this->class_name ? this->class_name->clone() : NULL;
    CONSTANT_NAME* constant_name = this->constant_name ? this->constant_name->clone() : NULL;
    Constant* clone = new Constant(class_name, constant_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Constant::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    if (this->constant_name != NULL)
    {
    	Node* constant_name_res = this->constant_name->find(in);
    	if (constant_name_res) return constant_name_res;
    }
    
    return NULL;
}

void Constant::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
    if (this->constant_name != NULL)
    	this->constant_name->find_all(in, out);
    
}

void Constant::assert_valid()
{
    if(class_name != NULL) class_name->assert_valid();
    assert(constant_name != NULL);
    constant_name->assert_valid();
    Node::assert_mixin_valid();
}

Instanceof::Instanceof(VARIABLE_NAME* variable_name, Class_name* class_name)
{
    this->variable_name = variable_name;
    this->class_name = class_name;
}

Instanceof::Instanceof()
{
    this->variable_name = 0;
    this->class_name = 0;
}

void Instanceof::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Instanceof::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Instanceof::ID;
int Instanceof::classid()
{
    return ID;
}

bool Instanceof::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Instanceof* that = dynamic_cast<Instanceof*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    return true;
}

bool Instanceof::equals(Node* in)
{
    Instanceof* that = dynamic_cast<Instanceof*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    return true;
}

Instanceof* Instanceof::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Instanceof* clone = new Instanceof(variable_name, class_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Instanceof::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    return NULL;
}

void Instanceof::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
}

void Instanceof::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(class_name != NULL);
    class_name->assert_valid();
    Node::assert_mixin_valid();
}

Method_invocation::Method_invocation(Target* target, Method_name* method_name, Actual_parameter_list* actual_parameters)
{
    this->target = target;
    this->method_name = method_name;
    this->actual_parameters = actual_parameters;
}

Method_invocation::Method_invocation()
{
    this->target = 0;
    this->method_name = 0;
    this->actual_parameters = 0;
}

void Method_invocation::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Method_invocation::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Method_invocation::ID;
int Method_invocation::classid()
{
    return ID;
}

bool Method_invocation::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Method_invocation* that = dynamic_cast<Method_invocation*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL)
    {
    	if(that->target != NULL && !that->target->match(this->target))
    		return false;
    }
    else if(!this->target->match(that->target))
    	return false;
    
    if(this->method_name == NULL)
    {
    	if(that->method_name != NULL && !that->method_name->match(this->method_name))
    		return false;
    }
    else if(!this->method_name->match(that->method_name))
    	return false;
    
    if(this->actual_parameters != NULL && that->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i, j;
    	for(
    		i = this->actual_parameters->begin(), j = that->actual_parameters->begin();
    		i != this->actual_parameters->end() && j != that->actual_parameters->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->actual_parameters->end() || j != that->actual_parameters->end())
    		return false;
    }
    
    return true;
}

bool Method_invocation::equals(Node* in)
{
    Method_invocation* that = dynamic_cast<Method_invocation*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL || that->target == NULL)
    {
    	if(this->target != NULL || that->target != NULL)
    		return false;
    }
    else if(!this->target->equals(that->target))
    	return false;
    
    if(this->method_name == NULL || that->method_name == NULL)
    {
    	if(this->method_name != NULL || that->method_name != NULL)
    		return false;
    }
    else if(!this->method_name->equals(that->method_name))
    	return false;
    
    if(this->actual_parameters == NULL || that->actual_parameters == NULL)
    {
    	if(this->actual_parameters != NULL || that->actual_parameters != NULL)
    		return false;
    }
    else
    {
    	Actual_parameter_list::const_iterator i, j;
    	for(
    		i = this->actual_parameters->begin(), j = that->actual_parameters->begin();
    		i != this->actual_parameters->end() && j != that->actual_parameters->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->actual_parameters->end() || j != that->actual_parameters->end())
    		return false;
    }
    
    return true;
}

Method_invocation* Method_invocation::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Method_name* method_name = this->method_name ? this->method_name->clone() : NULL;
    Actual_parameter_list* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	actual_parameters = new Actual_parameter_list;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    Method_invocation* clone = new Method_invocation(target, method_name, actual_parameters);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Method_invocation::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->target != NULL)
    {
    	Node* target_res = this->target->find(in);
    	if (target_res) return target_res;
    }
    
    if (this->method_name != NULL)
    {
    	Node* method_name_res = this->method_name->find(in);
    	if (method_name_res) return method_name_res;
    }
    
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	for(
    		i = this->actual_parameters->begin();
    		i != this->actual_parameters->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Method_invocation::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->method_name != NULL)
    	this->method_name->find_all(in, out);
    
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	for(
    		i = this->actual_parameters->begin();
    		i != this->actual_parameters->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Method_invocation::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(method_name != NULL);
    method_name->assert_valid();
    assert(actual_parameters != NULL);
    {
    	Actual_parameter_list::const_iterator i;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Method_invocation::Method_invocation(const char* name, Actual_parameter* arg)
{
    { 
		this->target = NULL;
		this->method_name = new METHOD_NAME(name);
		this->actual_parameters = new Actual_parameter_list (arg);
	}
}

Method_invocation::Method_invocation(METHOD_NAME* name, Actual_parameter* arg)
{
    { 
		this->target = NULL;
		this->method_name = name; 
		this->actual_parameters = new Actual_parameter_list (arg);
	}
}

New::New(Class_name* class_name, Actual_parameter_list* actual_parameters)
{
    this->class_name = class_name;
    this->actual_parameters = actual_parameters;
}

New::New()
{
    this->class_name = 0;
    this->actual_parameters = 0;
}

void New::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void New::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int New::ID;
int New::classid()
{
    return ID;
}

bool New::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    New* that = dynamic_cast<New*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL)
    {
    	if(that->class_name != NULL && !that->class_name->match(this->class_name))
    		return false;
    }
    else if(!this->class_name->match(that->class_name))
    	return false;
    
    if(this->actual_parameters != NULL && that->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i, j;
    	for(
    		i = this->actual_parameters->begin(), j = that->actual_parameters->begin();
    		i != this->actual_parameters->end() && j != that->actual_parameters->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->actual_parameters->end() || j != that->actual_parameters->end())
    		return false;
    }
    
    return true;
}

bool New::equals(Node* in)
{
    New* that = dynamic_cast<New*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    if(this->actual_parameters == NULL || that->actual_parameters == NULL)
    {
    	if(this->actual_parameters != NULL || that->actual_parameters != NULL)
    		return false;
    }
    else
    {
    	Actual_parameter_list::const_iterator i, j;
    	for(
    		i = this->actual_parameters->begin(), j = that->actual_parameters->begin();
    		i != this->actual_parameters->end() && j != that->actual_parameters->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->actual_parameters->end() || j != that->actual_parameters->end())
    		return false;
    }
    
    return true;
}

New* New::clone()
{
    Class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Actual_parameter_list* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	actual_parameters = new Actual_parameter_list;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    New* clone = new New(class_name, actual_parameters);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* New::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->class_name != NULL)
    {
    	Node* class_name_res = this->class_name->find(in);
    	if (class_name_res) return class_name_res;
    }
    
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	for(
    		i = this->actual_parameters->begin();
    		i != this->actual_parameters->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void New::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	for(
    		i = this->actual_parameters->begin();
    		i != this->actual_parameters->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void New::assert_valid()
{
    assert(class_name != NULL);
    class_name->assert_valid();
    assert(actual_parameters != NULL);
    {
    	Actual_parameter_list::const_iterator i;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Variable_name::Variable_name()
{
}

Variable_method::Variable_method(VARIABLE_NAME* variable_name)
{
    this->variable_name = variable_name;
}

Variable_method::Variable_method()
{
    this->variable_name = 0;
}

void Variable_method::visit(Visitor* visitor)
{
    visitor->visit_method_name(this);
}

void Variable_method::transform_children(Transform* transform)
{
    transform->children_method_name(this);
}

const int Variable_method::ID;
int Variable_method::classid()
{
    return ID;
}

bool Variable_method::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Variable_method* that = dynamic_cast<Variable_method*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Variable_method::equals(Node* in)
{
    Variable_method* that = dynamic_cast<Variable_method*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Variable_method* Variable_method::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Variable_method* clone = new Variable_method(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Variable_method::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Variable_method::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Variable_method::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Variable_class::Variable_class(VARIABLE_NAME* variable_name)
{
    this->variable_name = variable_name;
}

Variable_class::Variable_class()
{
    this->variable_name = 0;
}

void Variable_class::visit(Visitor* visitor)
{
    visitor->visit_class_name(this);
}

void Variable_class::transform_children(Transform* transform)
{
    transform->children_class_name(this);
}

const int Variable_class::ID;
int Variable_class::classid()
{
    return ID;
}

bool Variable_class::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Variable_class* that = dynamic_cast<Variable_class*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Variable_class::equals(Node* in)
{
    Variable_class* that = dynamic_cast<Variable_class*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Variable_class* Variable_class::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Variable_class* clone = new Variable_class(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Variable_class::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Variable_class::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Variable_class::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Variable_field::Variable_field(VARIABLE_NAME* variable_name)
{
    this->variable_name = variable_name;
}

Variable_field::Variable_field()
{
    this->variable_name = 0;
}

void Variable_field::visit(Visitor* visitor)
{
    visitor->visit_field_name(this);
}

void Variable_field::transform_children(Transform* transform)
{
    transform->children_field_name(this);
}

const int Variable_field::ID;
int Variable_field::classid()
{
    return ID;
}

bool Variable_field::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Variable_field* that = dynamic_cast<Variable_field*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Variable_field::equals(Node* in)
{
    Variable_field* that = dynamic_cast<Variable_field*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Variable_field* Variable_field::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Variable_field* clone = new Variable_field(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Variable_field::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Variable_field::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Variable_field::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

Static_array::Static_array(Static_array_elem_list* static_array_elems)
{
    this->static_array_elems = static_array_elems;
}

Static_array::Static_array()
{
    this->static_array_elems = 0;
}

void Static_array::visit(Visitor* visitor)
{
    visitor->visit_static_value(this);
}

void Static_array::transform_children(Transform* transform)
{
    transform->children_static_value(this);
}

const int Static_array::ID;
int Static_array::classid()
{
    return ID;
}

bool Static_array::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Static_array* that = dynamic_cast<Static_array*>(in);
    if(that == NULL) return false;
    
    if(this->static_array_elems != NULL && that->static_array_elems != NULL)
    {
    	Static_array_elem_list::const_iterator i, j;
    	for(
    		i = this->static_array_elems->begin(), j = that->static_array_elems->begin();
    		i != this->static_array_elems->end() && j != that->static_array_elems->end();
    		i++, j++)
    	{
    		if(*i == NULL)
    		{
    			if(*j != NULL && !(*j)->match(*i))
    				return false;
    		}
    		else if(!(*i)->match(*j))
    			return false;
    	}
    	if(i != this->static_array_elems->end() || j != that->static_array_elems->end())
    		return false;
    }
    
    return true;
}

bool Static_array::equals(Node* in)
{
    Static_array* that = dynamic_cast<Static_array*>(in);
    if(that == NULL) return false;
    
    if(this->static_array_elems == NULL || that->static_array_elems == NULL)
    {
    	if(this->static_array_elems != NULL || that->static_array_elems != NULL)
    		return false;
    }
    else
    {
    	Static_array_elem_list::const_iterator i, j;
    	for(
    		i = this->static_array_elems->begin(), j = that->static_array_elems->begin();
    		i != this->static_array_elems->end() && j != that->static_array_elems->end();
    		i++, j++)
    	{
    		if(*i == NULL || *j == NULL)
    		{
    			if(*i != NULL || *j != NULL)
    				return false;
    		}
    		else if(!(*i)->equals(*j))
    			return false;
    	}
    	if(i != this->static_array_elems->end() || j != that->static_array_elems->end())
    		return false;
    }
    
    return true;
}

Static_array* Static_array::clone()
{
    Static_array_elem_list* static_array_elems = NULL;
    if(this->static_array_elems != NULL)
    {
    	Static_array_elem_list::const_iterator i;
    	static_array_elems = new Static_array_elem_list;
    	for(i = this->static_array_elems->begin(); i != this->static_array_elems->end(); i++)
    		static_array_elems->push_back(*i ? (*i)->clone() : NULL);
    }
    Static_array* clone = new Static_array(static_array_elems);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Static_array::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->static_array_elems != NULL)
    {
    	Static_array_elem_list::const_iterator i;
    	for(
    		i = this->static_array_elems->begin();
    		i != this->static_array_elems->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    return NULL;
}

void Static_array::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->static_array_elems != NULL)
    {
    	Static_array_elem_list::const_iterator i;
    	for(
    		i = this->static_array_elems->begin();
    		i != this->static_array_elems->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Static_array::assert_valid()
{
    assert(static_array_elems != NULL);
    {
    	Static_array_elem_list::const_iterator i;
    	for(i = this->static_array_elems->begin(); i != this->static_array_elems->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Branch::Branch(VARIABLE_NAME* variable_name, LABEL_NAME* iftrue, LABEL_NAME* iffalse)
{
    this->variable_name = variable_name;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

Branch::Branch()
{
    this->variable_name = 0;
    this->iftrue = 0;
    this->iffalse = 0;
}

void Branch::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Branch::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Branch::ID;
int Branch::classid()
{
    return ID;
}

bool Branch::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Branch* that = dynamic_cast<Branch*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    if(this->iftrue == NULL)
    {
    	if(that->iftrue != NULL && !that->iftrue->match(this->iftrue))
    		return false;
    }
    else if(!this->iftrue->match(that->iftrue))
    	return false;
    
    if(this->iffalse == NULL)
    {
    	if(that->iffalse != NULL && !that->iffalse->match(this->iffalse))
    		return false;
    }
    else if(!this->iffalse->match(that->iffalse))
    	return false;
    
    return true;
}

bool Branch::equals(Node* in)
{
    Branch* that = dynamic_cast<Branch*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(this->iftrue == NULL || that->iftrue == NULL)
    {
    	if(this->iftrue != NULL || that->iftrue != NULL)
    		return false;
    }
    else if(!this->iftrue->equals(that->iftrue))
    	return false;
    
    if(this->iffalse == NULL || that->iffalse == NULL)
    {
    	if(this->iffalse != NULL || that->iffalse != NULL)
    		return false;
    }
    else if(!this->iffalse->equals(that->iffalse))
    	return false;
    
    return true;
}

Branch* Branch::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    LABEL_NAME* iftrue = this->iftrue ? this->iftrue->clone() : NULL;
    LABEL_NAME* iffalse = this->iffalse ? this->iffalse->clone() : NULL;
    Branch* clone = new Branch(variable_name, iftrue, iffalse);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Branch::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    if (this->iftrue != NULL)
    {
    	Node* iftrue_res = this->iftrue->find(in);
    	if (iftrue_res) return iftrue_res;
    }
    
    if (this->iffalse != NULL)
    {
    	Node* iffalse_res = this->iffalse->find(in);
    	if (iffalse_res) return iffalse_res;
    }
    
    return NULL;
}

void Branch::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if (this->iftrue != NULL)
    	this->iftrue->find_all(in, out);
    
    if (this->iffalse != NULL)
    	this->iffalse->find_all(in, out);
    
}

void Branch::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(iftrue != NULL);
    iftrue->assert_valid();
    assert(iffalse != NULL);
    iffalse->assert_valid();
    Node::assert_mixin_valid();
}

Goto::Goto(LABEL_NAME* label_name)
{
    this->label_name = label_name;
}

Goto::Goto()
{
    this->label_name = 0;
}

void Goto::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Goto::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Goto::ID;
int Goto::classid()
{
    return ID;
}

bool Goto::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Goto* that = dynamic_cast<Goto*>(in);
    if(that == NULL) return false;
    
    if(this->label_name == NULL)
    {
    	if(that->label_name != NULL && !that->label_name->match(this->label_name))
    		return false;
    }
    else if(!this->label_name->match(that->label_name))
    	return false;
    
    return true;
}

bool Goto::equals(Node* in)
{
    Goto* that = dynamic_cast<Goto*>(in);
    if(that == NULL) return false;
    
    if(this->label_name == NULL || that->label_name == NULL)
    {
    	if(this->label_name != NULL || that->label_name != NULL)
    		return false;
    }
    else if(!this->label_name->equals(that->label_name))
    	return false;
    
    return true;
}

Goto* Goto::clone()
{
    LABEL_NAME* label_name = this->label_name ? this->label_name->clone() : NULL;
    Goto* clone = new Goto(label_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Goto::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->label_name != NULL)
    {
    	Node* label_name_res = this->label_name->find(in);
    	if (label_name_res) return label_name_res;
    }
    
    return NULL;
}

void Goto::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->label_name != NULL)
    	this->label_name->find_all(in, out);
    
}

void Goto::assert_valid()
{
    assert(label_name != NULL);
    label_name->assert_valid();
    Node::assert_mixin_valid();
}

Label::Label(LABEL_NAME* label_name)
{
    this->label_name = label_name;
}

Label::Label()
{
    this->label_name = 0;
}

void Label::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Label::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Label::ID;
int Label::classid()
{
    return ID;
}

bool Label::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Label* that = dynamic_cast<Label*>(in);
    if(that == NULL) return false;
    
    if(this->label_name == NULL)
    {
    	if(that->label_name != NULL && !that->label_name->match(this->label_name))
    		return false;
    }
    else if(!this->label_name->match(that->label_name))
    	return false;
    
    return true;
}

bool Label::equals(Node* in)
{
    Label* that = dynamic_cast<Label*>(in);
    if(that == NULL) return false;
    
    if(this->label_name == NULL || that->label_name == NULL)
    {
    	if(this->label_name != NULL || that->label_name != NULL)
    		return false;
    }
    else if(!this->label_name->equals(that->label_name))
    	return false;
    
    return true;
}

Label* Label::clone()
{
    LABEL_NAME* label_name = this->label_name ? this->label_name->clone() : NULL;
    Label* clone = new Label(label_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Label::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->label_name != NULL)
    {
    	Node* label_name_res = this->label_name->find(in);
    	if (label_name_res) return label_name_res;
    }
    
    return NULL;
}

void Label::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->label_name != NULL)
    	this->label_name->find_all(in, out);
    
}

void Label::assert_valid()
{
    assert(label_name != NULL);
    label_name->assert_valid();
    Node::assert_mixin_valid();
}

Foreach_reset::Foreach_reset(VARIABLE_NAME* array, HT_ITERATOR* iter)
{
    this->array = array;
    this->iter = iter;
}

Foreach_reset::Foreach_reset()
{
    this->array = 0;
    this->iter = 0;
}

void Foreach_reset::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Foreach_reset::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Foreach_reset::ID;
int Foreach_reset::classid()
{
    return ID;
}

bool Foreach_reset::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach_reset* that = dynamic_cast<Foreach_reset*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL)
    {
    	if(that->array != NULL && !that->array->match(this->array))
    		return false;
    }
    else if(!this->array->match(that->array))
    	return false;
    
    if(this->iter == NULL)
    {
    	if(that->iter != NULL && !that->iter->match(this->iter))
    		return false;
    }
    else if(!this->iter->match(that->iter))
    	return false;
    
    return true;
}

bool Foreach_reset::equals(Node* in)
{
    Foreach_reset* that = dynamic_cast<Foreach_reset*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL || that->array == NULL)
    {
    	if(this->array != NULL || that->array != NULL)
    		return false;
    }
    else if(!this->array->equals(that->array))
    	return false;
    
    if(this->iter == NULL || that->iter == NULL)
    {
    	if(this->iter != NULL || that->iter != NULL)
    		return false;
    }
    else if(!this->iter->equals(that->iter))
    	return false;
    
    return true;
}

Foreach_reset* Foreach_reset::clone()
{
    VARIABLE_NAME* array = this->array ? this->array->clone() : NULL;
    HT_ITERATOR* iter = this->iter ? this->iter->clone() : NULL;
    Foreach_reset* clone = new Foreach_reset(array, iter);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach_reset::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->array != NULL)
    {
    	Node* array_res = this->array->find(in);
    	if (array_res) return array_res;
    }
    
    if (this->iter != NULL)
    {
    	Node* iter_res = this->iter->find(in);
    	if (iter_res) return iter_res;
    }
    
    return NULL;
}

void Foreach_reset::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->array != NULL)
    	this->array->find_all(in, out);
    
    if (this->iter != NULL)
    	this->iter->find_all(in, out);
    
}

void Foreach_reset::assert_valid()
{
    assert(array != NULL);
    array->assert_valid();
    assert(iter != NULL);
    iter->assert_valid();
    Node::assert_mixin_valid();
}

Foreach_next::Foreach_next(VARIABLE_NAME* array, HT_ITERATOR* iter)
{
    this->array = array;
    this->iter = iter;
}

Foreach_next::Foreach_next()
{
    this->array = 0;
    this->iter = 0;
}

void Foreach_next::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Foreach_next::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Foreach_next::ID;
int Foreach_next::classid()
{
    return ID;
}

bool Foreach_next::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach_next* that = dynamic_cast<Foreach_next*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL)
    {
    	if(that->array != NULL && !that->array->match(this->array))
    		return false;
    }
    else if(!this->array->match(that->array))
    	return false;
    
    if(this->iter == NULL)
    {
    	if(that->iter != NULL && !that->iter->match(this->iter))
    		return false;
    }
    else if(!this->iter->match(that->iter))
    	return false;
    
    return true;
}

bool Foreach_next::equals(Node* in)
{
    Foreach_next* that = dynamic_cast<Foreach_next*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL || that->array == NULL)
    {
    	if(this->array != NULL || that->array != NULL)
    		return false;
    }
    else if(!this->array->equals(that->array))
    	return false;
    
    if(this->iter == NULL || that->iter == NULL)
    {
    	if(this->iter != NULL || that->iter != NULL)
    		return false;
    }
    else if(!this->iter->equals(that->iter))
    	return false;
    
    return true;
}

Foreach_next* Foreach_next::clone()
{
    VARIABLE_NAME* array = this->array ? this->array->clone() : NULL;
    HT_ITERATOR* iter = this->iter ? this->iter->clone() : NULL;
    Foreach_next* clone = new Foreach_next(array, iter);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach_next::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->array != NULL)
    {
    	Node* array_res = this->array->find(in);
    	if (array_res) return array_res;
    }
    
    if (this->iter != NULL)
    {
    	Node* iter_res = this->iter->find(in);
    	if (iter_res) return iter_res;
    }
    
    return NULL;
}

void Foreach_next::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->array != NULL)
    	this->array->find_all(in, out);
    
    if (this->iter != NULL)
    	this->iter->find_all(in, out);
    
}

void Foreach_next::assert_valid()
{
    assert(array != NULL);
    array->assert_valid();
    assert(iter != NULL);
    iter->assert_valid();
    Node::assert_mixin_valid();
}

Foreach_end::Foreach_end(VARIABLE_NAME* array, HT_ITERATOR* iter)
{
    this->array = array;
    this->iter = iter;
}

Foreach_end::Foreach_end()
{
    this->array = 0;
    this->iter = 0;
}

void Foreach_end::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Foreach_end::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Foreach_end::ID;
int Foreach_end::classid()
{
    return ID;
}

bool Foreach_end::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach_end* that = dynamic_cast<Foreach_end*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL)
    {
    	if(that->array != NULL && !that->array->match(this->array))
    		return false;
    }
    else if(!this->array->match(that->array))
    	return false;
    
    if(this->iter == NULL)
    {
    	if(that->iter != NULL && !that->iter->match(this->iter))
    		return false;
    }
    else if(!this->iter->match(that->iter))
    	return false;
    
    return true;
}

bool Foreach_end::equals(Node* in)
{
    Foreach_end* that = dynamic_cast<Foreach_end*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL || that->array == NULL)
    {
    	if(this->array != NULL || that->array != NULL)
    		return false;
    }
    else if(!this->array->equals(that->array))
    	return false;
    
    if(this->iter == NULL || that->iter == NULL)
    {
    	if(this->iter != NULL || that->iter != NULL)
    		return false;
    }
    else if(!this->iter->equals(that->iter))
    	return false;
    
    return true;
}

Foreach_end* Foreach_end::clone()
{
    VARIABLE_NAME* array = this->array ? this->array->clone() : NULL;
    HT_ITERATOR* iter = this->iter ? this->iter->clone() : NULL;
    Foreach_end* clone = new Foreach_end(array, iter);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach_end::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->array != NULL)
    {
    	Node* array_res = this->array->find(in);
    	if (array_res) return array_res;
    }
    
    if (this->iter != NULL)
    {
    	Node* iter_res = this->iter->find(in);
    	if (iter_res) return iter_res;
    }
    
    return NULL;
}

void Foreach_end::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->array != NULL)
    	this->array->find_all(in, out);
    
    if (this->iter != NULL)
    	this->iter->find_all(in, out);
    
}

void Foreach_end::assert_valid()
{
    assert(array != NULL);
    array->assert_valid();
    assert(iter != NULL);
    iter->assert_valid();
    Node::assert_mixin_valid();
}

Foreach_has_key::Foreach_has_key(VARIABLE_NAME* array, HT_ITERATOR* iter)
{
    this->array = array;
    this->iter = iter;
}

Foreach_has_key::Foreach_has_key()
{
    this->array = 0;
    this->iter = 0;
}

void Foreach_has_key::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Foreach_has_key::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Foreach_has_key::ID;
int Foreach_has_key::classid()
{
    return ID;
}

bool Foreach_has_key::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach_has_key* that = dynamic_cast<Foreach_has_key*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL)
    {
    	if(that->array != NULL && !that->array->match(this->array))
    		return false;
    }
    else if(!this->array->match(that->array))
    	return false;
    
    if(this->iter == NULL)
    {
    	if(that->iter != NULL && !that->iter->match(this->iter))
    		return false;
    }
    else if(!this->iter->match(that->iter))
    	return false;
    
    return true;
}

bool Foreach_has_key::equals(Node* in)
{
    Foreach_has_key* that = dynamic_cast<Foreach_has_key*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL || that->array == NULL)
    {
    	if(this->array != NULL || that->array != NULL)
    		return false;
    }
    else if(!this->array->equals(that->array))
    	return false;
    
    if(this->iter == NULL || that->iter == NULL)
    {
    	if(this->iter != NULL || that->iter != NULL)
    		return false;
    }
    else if(!this->iter->equals(that->iter))
    	return false;
    
    return true;
}

Foreach_has_key* Foreach_has_key::clone()
{
    VARIABLE_NAME* array = this->array ? this->array->clone() : NULL;
    HT_ITERATOR* iter = this->iter ? this->iter->clone() : NULL;
    Foreach_has_key* clone = new Foreach_has_key(array, iter);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach_has_key::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->array != NULL)
    {
    	Node* array_res = this->array->find(in);
    	if (array_res) return array_res;
    }
    
    if (this->iter != NULL)
    {
    	Node* iter_res = this->iter->find(in);
    	if (iter_res) return iter_res;
    }
    
    return NULL;
}

void Foreach_has_key::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->array != NULL)
    	this->array->find_all(in, out);
    
    if (this->iter != NULL)
    	this->iter->find_all(in, out);
    
}

void Foreach_has_key::assert_valid()
{
    assert(array != NULL);
    array->assert_valid();
    assert(iter != NULL);
    iter->assert_valid();
    Node::assert_mixin_valid();
}

Foreach_get_key::Foreach_get_key(VARIABLE_NAME* array, HT_ITERATOR* iter)
{
    this->array = array;
    this->iter = iter;
}

Foreach_get_key::Foreach_get_key()
{
    this->array = 0;
    this->iter = 0;
}

void Foreach_get_key::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Foreach_get_key::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Foreach_get_key::ID;
int Foreach_get_key::classid()
{
    return ID;
}

bool Foreach_get_key::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach_get_key* that = dynamic_cast<Foreach_get_key*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL)
    {
    	if(that->array != NULL && !that->array->match(this->array))
    		return false;
    }
    else if(!this->array->match(that->array))
    	return false;
    
    if(this->iter == NULL)
    {
    	if(that->iter != NULL && !that->iter->match(this->iter))
    		return false;
    }
    else if(!this->iter->match(that->iter))
    	return false;
    
    return true;
}

bool Foreach_get_key::equals(Node* in)
{
    Foreach_get_key* that = dynamic_cast<Foreach_get_key*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL || that->array == NULL)
    {
    	if(this->array != NULL || that->array != NULL)
    		return false;
    }
    else if(!this->array->equals(that->array))
    	return false;
    
    if(this->iter == NULL || that->iter == NULL)
    {
    	if(this->iter != NULL || that->iter != NULL)
    		return false;
    }
    else if(!this->iter->equals(that->iter))
    	return false;
    
    return true;
}

Foreach_get_key* Foreach_get_key::clone()
{
    VARIABLE_NAME* array = this->array ? this->array->clone() : NULL;
    HT_ITERATOR* iter = this->iter ? this->iter->clone() : NULL;
    Foreach_get_key* clone = new Foreach_get_key(array, iter);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach_get_key::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->array != NULL)
    {
    	Node* array_res = this->array->find(in);
    	if (array_res) return array_res;
    }
    
    if (this->iter != NULL)
    {
    	Node* iter_res = this->iter->find(in);
    	if (iter_res) return iter_res;
    }
    
    return NULL;
}

void Foreach_get_key::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->array != NULL)
    	this->array->find_all(in, out);
    
    if (this->iter != NULL)
    	this->iter->find_all(in, out);
    
}

void Foreach_get_key::assert_valid()
{
    assert(array != NULL);
    array->assert_valid();
    assert(iter != NULL);
    iter->assert_valid();
    Node::assert_mixin_valid();
}

Foreach_get_val::Foreach_get_val(VARIABLE_NAME* array, HT_ITERATOR* iter)
{
    this->array = array;
    this->iter = iter;
}

Foreach_get_val::Foreach_get_val()
{
    this->array = 0;
    this->iter = 0;
}

void Foreach_get_val::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Foreach_get_val::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Foreach_get_val::ID;
int Foreach_get_val::classid()
{
    return ID;
}

bool Foreach_get_val::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach_get_val* that = dynamic_cast<Foreach_get_val*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL)
    {
    	if(that->array != NULL && !that->array->match(this->array))
    		return false;
    }
    else if(!this->array->match(that->array))
    	return false;
    
    if(this->iter == NULL)
    {
    	if(that->iter != NULL && !that->iter->match(this->iter))
    		return false;
    }
    else if(!this->iter->match(that->iter))
    	return false;
    
    return true;
}

bool Foreach_get_val::equals(Node* in)
{
    Foreach_get_val* that = dynamic_cast<Foreach_get_val*>(in);
    if(that == NULL) return false;
    
    if(this->array == NULL || that->array == NULL)
    {
    	if(this->array != NULL || that->array != NULL)
    		return false;
    }
    else if(!this->array->equals(that->array))
    	return false;
    
    if(this->iter == NULL || that->iter == NULL)
    {
    	if(this->iter != NULL || that->iter != NULL)
    		return false;
    }
    else if(!this->iter->equals(that->iter))
    	return false;
    
    return true;
}

Foreach_get_val* Foreach_get_val::clone()
{
    VARIABLE_NAME* array = this->array ? this->array->clone() : NULL;
    HT_ITERATOR* iter = this->iter ? this->iter->clone() : NULL;
    Foreach_get_val* clone = new Foreach_get_val(array, iter);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach_get_val::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->array != NULL)
    {
    	Node* array_res = this->array->find(in);
    	if (array_res) return array_res;
    }
    
    if (this->iter != NULL)
    {
    	Node* iter_res = this->iter->find(in);
    	if (iter_res) return iter_res;
    }
    
    return NULL;
}

void Foreach_get_val::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->array != NULL)
    	this->array->find_all(in, out);
    
    if (this->iter != NULL)
    	this->iter->find_all(in, out);
    
}

void Foreach_get_val::assert_valid()
{
    assert(array != NULL);
    array->assert_valid();
    assert(iter != NULL);
    iter->assert_valid();
    Node::assert_mixin_valid();
}

Param_is_ref::Param_is_ref(Target* target, Method_name* method_name, PARAM_INDEX* param_index)
{
    this->target = target;
    this->method_name = method_name;
    this->param_index = param_index;
}

Param_is_ref::Param_is_ref()
{
    this->target = 0;
    this->method_name = 0;
    this->param_index = 0;
}

void Param_is_ref::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Param_is_ref::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Param_is_ref::ID;
int Param_is_ref::classid()
{
    return ID;
}

bool Param_is_ref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Param_is_ref* that = dynamic_cast<Param_is_ref*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL)
    {
    	if(that->target != NULL && !that->target->match(this->target))
    		return false;
    }
    else if(!this->target->match(that->target))
    	return false;
    
    if(this->method_name == NULL)
    {
    	if(that->method_name != NULL && !that->method_name->match(this->method_name))
    		return false;
    }
    else if(!this->method_name->match(that->method_name))
    	return false;
    
    if(this->param_index == NULL)
    {
    	if(that->param_index != NULL && !that->param_index->match(this->param_index))
    		return false;
    }
    else if(!this->param_index->match(that->param_index))
    	return false;
    
    return true;
}

bool Param_is_ref::equals(Node* in)
{
    Param_is_ref* that = dynamic_cast<Param_is_ref*>(in);
    if(that == NULL) return false;
    
    if(this->target == NULL || that->target == NULL)
    {
    	if(this->target != NULL || that->target != NULL)
    		return false;
    }
    else if(!this->target->equals(that->target))
    	return false;
    
    if(this->method_name == NULL || that->method_name == NULL)
    {
    	if(this->method_name != NULL || that->method_name != NULL)
    		return false;
    }
    else if(!this->method_name->equals(that->method_name))
    	return false;
    
    if(this->param_index == NULL || that->param_index == NULL)
    {
    	if(this->param_index != NULL || that->param_index != NULL)
    		return false;
    }
    else if(!this->param_index->equals(that->param_index))
    	return false;
    
    return true;
}

Param_is_ref* Param_is_ref::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Method_name* method_name = this->method_name ? this->method_name->clone() : NULL;
    PARAM_INDEX* param_index = this->param_index ? this->param_index->clone() : NULL;
    Param_is_ref* clone = new Param_is_ref(target, method_name, param_index);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Param_is_ref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->target != NULL)
    {
    	Node* target_res = this->target->find(in);
    	if (target_res) return target_res;
    }
    
    if (this->method_name != NULL)
    {
    	Node* method_name_res = this->method_name->find(in);
    	if (method_name_res) return method_name_res;
    }
    
    if (this->param_index != NULL)
    {
    	Node* param_index_res = this->param_index->find(in);
    	if (param_index_res) return param_index_res;
    }
    
    return NULL;
}

void Param_is_ref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->method_name != NULL)
    	this->method_name->find_all(in, out);
    
    if (this->param_index != NULL)
    	this->param_index->find_all(in, out);
    
}

void Param_is_ref::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(method_name != NULL);
    method_name->assert_valid();
    assert(param_index != NULL);
    param_index->assert_valid();
    Node::assert_mixin_valid();
}

FOREIGN::FOREIGN(IR::Node* value)
{
    this->value = value;
}

FOREIGN::FOREIGN()
{
    this->value = 0;
}

void FOREIGN::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void FOREIGN::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int FOREIGN::ID;
int FOREIGN::classid()
{
    return ID;
}

bool FOREIGN::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    FOREIGN* that = dynamic_cast<FOREIGN*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool FOREIGN::match_value(FOREIGN* that)
{
    return true;
}

bool FOREIGN::equals(Node* in)
{
    FOREIGN* that = dynamic_cast<FOREIGN*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

FOREIGN* FOREIGN::clone()
{
    value = clone_value();
    FOREIGN* clone = new FOREIGN(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

IR::Node* FOREIGN::clone_value()
{
    return value;
}

Node* FOREIGN::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void FOREIGN::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void FOREIGN::assert_valid()
{
    assert_value_valid();
    Node::assert_mixin_valid();
}

void FOREIGN::assert_value_valid()
{
    // Assume value is valid
}

bool FOREIGN::equals_value(FOREIGN* that)
{
    {
		return value->equals (that->value);
	}
}

IR ::Node* FOREIGN::get_value()
{
    {
		return value;
	}
}

CLASS_NAME::CLASS_NAME(String* value)
{
    this->value = value;
}

CLASS_NAME::CLASS_NAME()
{
    this->value = 0;
}

void CLASS_NAME::visit(Visitor* visitor)
{
    visitor->visit_class_name(this);
}

void CLASS_NAME::transform_children(Transform* transform)
{
    transform->children_class_name(this);
}

String* CLASS_NAME::get_value_as_string()
{
    return value;
}

const int CLASS_NAME::ID;
int CLASS_NAME::classid()
{
    return ID;
}

bool CLASS_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    CLASS_NAME* that = dynamic_cast<CLASS_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool CLASS_NAME::equals(Node* in)
{
    CLASS_NAME* that = dynamic_cast<CLASS_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

CLASS_NAME* CLASS_NAME::clone()
{
    String* value = new String(*this->value);
    CLASS_NAME* clone = new CLASS_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* CLASS_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void CLASS_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void CLASS_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

CLASS_NAME::CLASS_NAME(const char* name)
{
    {
		this->value = new String (name);
	}
}

INTERFACE_NAME::INTERFACE_NAME(String* value)
{
    this->value = value;
}

INTERFACE_NAME::INTERFACE_NAME()
{
    this->value = 0;
}

void INTERFACE_NAME::visit(Visitor* visitor)
{
    visitor->visit_interface_name(this);
}

void INTERFACE_NAME::transform_children(Transform* transform)
{
    transform->children_interface_name(this);
}

String* INTERFACE_NAME::get_value_as_string()
{
    return value;
}

const int INTERFACE_NAME::ID;
int INTERFACE_NAME::classid()
{
    return ID;
}

bool INTERFACE_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    INTERFACE_NAME* that = dynamic_cast<INTERFACE_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool INTERFACE_NAME::equals(Node* in)
{
    INTERFACE_NAME* that = dynamic_cast<INTERFACE_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

INTERFACE_NAME* INTERFACE_NAME::clone()
{
    String* value = new String(*this->value);
    INTERFACE_NAME* clone = new INTERFACE_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* INTERFACE_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void INTERFACE_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void INTERFACE_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

METHOD_NAME::METHOD_NAME(String* value)
{
    this->value = value;
}

METHOD_NAME::METHOD_NAME()
{
    this->value = 0;
}

void METHOD_NAME::visit(Visitor* visitor)
{
    visitor->visit_method_name(this);
}

void METHOD_NAME::transform_children(Transform* transform)
{
    transform->children_method_name(this);
}

String* METHOD_NAME::get_value_as_string()
{
    return value;
}

const int METHOD_NAME::ID;
int METHOD_NAME::classid()
{
    return ID;
}

bool METHOD_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    METHOD_NAME* that = dynamic_cast<METHOD_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool METHOD_NAME::equals(Node* in)
{
    METHOD_NAME* that = dynamic_cast<METHOD_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

METHOD_NAME* METHOD_NAME::clone()
{
    String* value = new String(*this->value);
    METHOD_NAME* clone = new METHOD_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* METHOD_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void METHOD_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void METHOD_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

METHOD_NAME::METHOD_NAME(const char* name)
{
    {
		this->value = new String (name);
	}
}

OP::OP(String* value)
{
    this->value = value;
}

OP::OP()
{
    this->value = 0;
}

void OP::visit(Visitor* visitor)
{
    visitor->visit_op(this);
}

void OP::transform_children(Transform* transform)
{
    transform->children_op(this);
}

String* OP::get_value_as_string()
{
    return value;
}

const int OP::ID;
int OP::classid()
{
    return ID;
}

bool OP::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    OP* that = dynamic_cast<OP*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool OP::equals(Node* in)
{
    OP* that = dynamic_cast<OP*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

OP* OP::clone()
{
    String* value = new String(*this->value);
    OP* clone = new OP(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* OP::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void OP::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void OP::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

CAST::CAST(String* value)
{
    this->value = value;
}

CAST::CAST()
{
    this->value = 0;
}

void CAST::visit(Visitor* visitor)
{
    visitor->visit_cast(this);
}

void CAST::transform_children(Transform* transform)
{
    transform->children_cast(this);
}

String* CAST::get_value_as_string()
{
    return value;
}

const int CAST::ID;
int CAST::classid()
{
    return ID;
}

bool CAST::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    CAST* that = dynamic_cast<CAST*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool CAST::equals(Node* in)
{
    CAST* that = dynamic_cast<CAST*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

CAST* CAST::clone()
{
    String* value = new String(*this->value);
    CAST* clone = new CAST(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* CAST::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void CAST::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void CAST::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

CONSTANT_NAME::CONSTANT_NAME(String* value)
{
    this->value = value;
}

CONSTANT_NAME::CONSTANT_NAME()
{
    this->value = 0;
}

void CONSTANT_NAME::visit(Visitor* visitor)
{
    visitor->visit_constant_name(this);
}

void CONSTANT_NAME::transform_children(Transform* transform)
{
    transform->children_constant_name(this);
}

String* CONSTANT_NAME::get_value_as_string()
{
    return value;
}

const int CONSTANT_NAME::ID;
int CONSTANT_NAME::classid()
{
    return ID;
}

bool CONSTANT_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    CONSTANT_NAME* that = dynamic_cast<CONSTANT_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool CONSTANT_NAME::equals(Node* in)
{
    CONSTANT_NAME* that = dynamic_cast<CONSTANT_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

CONSTANT_NAME* CONSTANT_NAME::clone()
{
    String* value = new String(*this->value);
    CONSTANT_NAME* clone = new CONSTANT_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* CONSTANT_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void CONSTANT_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void CONSTANT_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

FIELD_NAME::FIELD_NAME(String* value)
{
    this->value = value;
}

FIELD_NAME::FIELD_NAME()
{
    this->value = 0;
}

void FIELD_NAME::visit(Visitor* visitor)
{
    visitor->visit_field_name(this);
}

void FIELD_NAME::transform_children(Transform* transform)
{
    transform->children_field_name(this);
}

String* FIELD_NAME::get_value_as_string()
{
    return value;
}

const int FIELD_NAME::ID;
int FIELD_NAME::classid()
{
    return ID;
}

bool FIELD_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    FIELD_NAME* that = dynamic_cast<FIELD_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool FIELD_NAME::equals(Node* in)
{
    FIELD_NAME* that = dynamic_cast<FIELD_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

FIELD_NAME* FIELD_NAME::clone()
{
    String* value = new String(*this->value);
    FIELD_NAME* clone = new FIELD_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* FIELD_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void FIELD_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void FIELD_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

FIELD_NAME::FIELD_NAME(const char* name)
{
    {
		this->value = new String (name);
	}
}

LABEL_NAME::LABEL_NAME(String* value)
{
    this->value = value;
}

LABEL_NAME::LABEL_NAME()
{
    this->value = 0;
}

void LABEL_NAME::visit(Visitor* visitor)
{
    visitor->visit_label_name(this);
}

void LABEL_NAME::transform_children(Transform* transform)
{
    transform->children_label_name(this);
}

String* LABEL_NAME::get_value_as_string()
{
    return value;
}

const int LABEL_NAME::ID;
int LABEL_NAME::classid()
{
    return ID;
}

bool LABEL_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    LABEL_NAME* that = dynamic_cast<LABEL_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool LABEL_NAME::equals(Node* in)
{
    LABEL_NAME* that = dynamic_cast<LABEL_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

LABEL_NAME* LABEL_NAME::clone()
{
    String* value = new String(*this->value);
    LABEL_NAME* clone = new LABEL_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* LABEL_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void LABEL_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void LABEL_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

HT_ITERATOR::HT_ITERATOR(String* value)
{
    this->value = value;
}

HT_ITERATOR::HT_ITERATOR()
{
    this->value = 0;
}

void HT_ITERATOR::visit(Visitor* visitor)
{
    visitor->visit_ht_iterator(this);
}

void HT_ITERATOR::transform_children(Transform* transform)
{
    transform->children_ht_iterator(this);
}

String* HT_ITERATOR::get_value_as_string()
{
    return value;
}

const int HT_ITERATOR::ID;
int HT_ITERATOR::classid()
{
    return ID;
}

bool HT_ITERATOR::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HT_ITERATOR* that = dynamic_cast<HT_ITERATOR*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool HT_ITERATOR::equals(Node* in)
{
    HT_ITERATOR* that = dynamic_cast<HT_ITERATOR*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

HT_ITERATOR* HT_ITERATOR::clone()
{
    String* value = new String(*this->value);
    HT_ITERATOR* clone = new HT_ITERATOR(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* HT_ITERATOR::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void HT_ITERATOR::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void HT_ITERATOR::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

Literal::Literal()
{
}

/*  We wish to match on this, so it cannot be pure virtual */
String* Literal::get_value_as_string()
{
    { assert (0); }
}

Variable_variable::Variable_variable(VARIABLE_NAME* variable_name)
{
    this->variable_name = variable_name;
}

Variable_variable::Variable_variable()
{
    this->variable_name = 0;
}

void Variable_variable::visit(Visitor* visitor)
{
    visitor->visit_variable_name(this);
}

void Variable_variable::transform_children(Transform* transform)
{
    transform->children_variable_name(this);
}

const int Variable_variable::ID;
int Variable_variable::classid()
{
    return ID;
}

bool Variable_variable::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Variable_variable* that = dynamic_cast<Variable_variable*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL)
    {
    	if(that->variable_name != NULL && !that->variable_name->match(this->variable_name))
    		return false;
    }
    else if(!this->variable_name->match(that->variable_name))
    	return false;
    
    return true;
}

bool Variable_variable::equals(Node* in)
{
    Variable_variable* that = dynamic_cast<Variable_variable*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    return true;
}

Variable_variable* Variable_variable::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Variable_variable* clone = new Variable_variable(variable_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Variable_variable::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable_name != NULL)
    {
    	Node* variable_name_res = this->variable_name->find(in);
    	if (variable_name_res) return variable_name_res;
    }
    
    return NULL;
}

void Variable_variable::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
}

void Variable_variable::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    Node::assert_mixin_valid();
}

VARIABLE_NAME::VARIABLE_NAME()
{
    this->value = 0;
}

void VARIABLE_NAME::visit(Visitor* visitor)
{
    visitor->visit_variable_name(this);
}

void VARIABLE_NAME::transform_children(Transform* transform)
{
    transform->children_variable_name(this);
}

String* VARIABLE_NAME::get_value_as_string()
{
    return value;
}

const int VARIABLE_NAME::ID;
int VARIABLE_NAME::classid()
{
    return ID;
}

bool VARIABLE_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    VARIABLE_NAME* that = dynamic_cast<VARIABLE_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool VARIABLE_NAME::equals(Node* in)
{
    VARIABLE_NAME* that = dynamic_cast<VARIABLE_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    return true;
}

VARIABLE_NAME* VARIABLE_NAME::clone()
{
    String* value = new String(*this->value);
    VARIABLE_NAME* clone = new VARIABLE_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* VARIABLE_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void VARIABLE_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void VARIABLE_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
}

VARIABLE_NAME::VARIABLE_NAME(String* name)
{
    {
		this->value = name;
	}
}

VARIABLE_NAME::VARIABLE_NAME(const char* name)
{
    {
		this->value = new String (name);
	}
}

INT::INT(long value)
{
    this->value = value;
}

INT::INT()
{
    this->value = 0;
}

void INT::visit(Visitor* visitor)
{
    visitor->visit_static_array_key(this);
}

void INT::transform_children(Transform* transform)
{
    transform->children_static_array_key(this);
}

const int INT::ID;
int INT::classid()
{
    return ID;
}

bool INT::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    INT* that = dynamic_cast<INT*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool INT::equals(Node* in)
{
    INT* that = dynamic_cast<INT*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

bool INT::equals_value(INT* that)
{
    return (this->value == that->value);
}

INT* INT::clone()
{
    value = clone_value();
    INT* clone = new INT(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

long INT::clone_value()
{
    return value;
}

Node* INT::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void INT::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void INT::assert_valid()
{
    assert_value_valid();
    Node::assert_mixin_valid();
}

void INT::assert_value_valid()
{
    // Assume value is valid
}

/*  Constructors can't call virtual functions, so we create a non-virtual to */
/*  do the work. This is then called by the virtual function, and is also */
/*  safely called from the constructor. */
String* INT::_get_value_as_string()
{
    {
		std::ostringstream os;
		os << value;
		return new String(os.str());
	}
}

String* INT::get_value_as_string()
{
    {
		return _get_value_as_string ();
	}
}

bool INT::match_value(INT* that)
{
    {
		return (that->value == value);
	}
}

REAL::REAL(double value)
{
    this->value = value;
}

REAL::REAL()
{
    this->value = 0;
}

void REAL::visit(Visitor* visitor)
{
    visitor->visit_static_array_key(this);
}

void REAL::transform_children(Transform* transform)
{
    transform->children_static_array_key(this);
}

const int REAL::ID;
int REAL::classid()
{
    return ID;
}

bool REAL::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    REAL* that = dynamic_cast<REAL*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool REAL::equals(Node* in)
{
    REAL* that = dynamic_cast<REAL*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

bool REAL::equals_value(REAL* that)
{
    return (this->value == that->value);
}

REAL* REAL::clone()
{
    value = clone_value();
    REAL* clone = new REAL(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

double REAL::clone_value()
{
    return value;
}

Node* REAL::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void REAL::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void REAL::assert_valid()
{
    assert_value_valid();
    Node::assert_mixin_valid();
}

void REAL::assert_value_valid()
{
    // Assume value is valid
}

/*  See comment in INT::_get_value_as_string () */
String* REAL::_get_value_as_string()
{
    {
		std::ostringstream os;
		// setprecision(20) outputs as many digits as required, with
		// a maximum of 20
		os << std::setprecision(20) << value;
		// unfortunately, that means that if no digits are required at
		// all (after the decimal point), the decimal point is left out
		// completely; setting the "showpoint" flag fixes this, but then
		// the STL _always_ shows all 20 digits, which is not what we 
		// want either. Hence, we insert the ".0" manually if necessary:
		string str = os.str();
		if(str.find('.') >= str.size())
			str.append(".0");

		return new String(str);
	}
}

String* REAL::get_value_as_string()
{
    {
		return _get_value_as_string ();
	}
}

bool REAL::match_value(REAL* that)
{
    {
		return (that->value == value);
	}
}

STRING::STRING(String* value)
{
    this->value = value;
}

STRING::STRING()
{
    this->value = 0;
}

void STRING::visit(Visitor* visitor)
{
    visitor->visit_static_array_key(this);
}

void STRING::transform_children(Transform* transform)
{
    transform->children_static_array_key(this);
}

const int STRING::ID;
int STRING::classid()
{
    return ID;
}

bool STRING::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    STRING* that = dynamic_cast<STRING*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool STRING::equals(Node* in)
{
    STRING* that = dynamic_cast<STRING*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

bool STRING::equals_value(STRING* that)
{
    return (*this->value == *that->value);
}

STRING* STRING::clone()
{
    value = clone_value();
    STRING* clone = new STRING(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* STRING::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void STRING::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void STRING::assert_valid()
{
    assert_value_valid();
    Node::assert_mixin_valid();
}

void STRING::assert_value_valid()
{
    // Assume value is valid
}

String* STRING::get_value_as_string()
{
    {
		return value;
	}
}

bool STRING::is_value_valid()
{
    {
		return value != NULL;
	}
}

String* STRING::clone_value()
{
    {
		return value->clone();
	}
}

bool STRING::match_value(STRING* that)
{
    {
		return (*that->value == *value);
	}
}

BOOL::BOOL(bool value)
{
    this->value = value;
}

BOOL::BOOL()
{
    this->value = 0;
}

void BOOL::visit(Visitor* visitor)
{
    visitor->visit_static_array_key(this);
}

void BOOL::transform_children(Transform* transform)
{
    transform->children_static_array_key(this);
}

const int BOOL::ID;
int BOOL::classid()
{
    return ID;
}

bool BOOL::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    BOOL* that = dynamic_cast<BOOL*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool BOOL::equals(Node* in)
{
    BOOL* that = dynamic_cast<BOOL*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

bool BOOL::equals_value(BOOL* that)
{
    return (this->value == that->value);
}

BOOL* BOOL::clone()
{
    value = clone_value();
    BOOL* clone = new BOOL(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

bool BOOL::clone_value()
{
    return value;
}

Node* BOOL::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void BOOL::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void BOOL::assert_valid()
{
    assert_value_valid();
    Node::assert_mixin_valid();
}

void BOOL::assert_value_valid()
{
    // Assume value is valid
}

/*  See comment in INT::_get_value_as_string () */
String* BOOL::_get_value_as_string()
{
    {
		if(value)
			return new String("True");
		else
			return new String("False");
	}
}

String* BOOL::get_value_as_string()
{
    {
		return _get_value_as_string ();
	}
}

bool BOOL::match_value(BOOL* that)
{
    {
		return (that->value == value);
	}
}

NIL::NIL()
{
}

void NIL::visit(Visitor* visitor)
{
    visitor->visit_static_array_key(this);
}

void NIL::transform_children(Transform* transform)
{
    transform->children_static_array_key(this);
}

const int NIL::ID;
int NIL::classid()
{
    return ID;
}

bool NIL::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    NIL* that = dynamic_cast<NIL*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool NIL::equals(Node* in)
{
    NIL* that = dynamic_cast<NIL*>(in);
    if(that == NULL) return false;
    
    return true;
}

NIL* NIL::clone()
{
    NIL* clone = new NIL();
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* NIL::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void NIL::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void NIL::assert_valid()
{
    Node::assert_mixin_valid();
}

String* NIL::get_value_as_string()
{
    {
		return new String("NULL");
	}
}

None::None()
{
}

void None::visit(Visitor* visitor)
{
    assert (0);
}

void None::transform_children(Transform* transform)
{
    assert (0);
}

None* None::clone()
{
    assert (0);
}

void None::assert_valid()
{
    assert (0);
}

String* None::get_value_as_string()
{
    assert (0);
}

int None::classid()
{
    assert (0);
}

bool None::match(Node* in)
{
    assert (0);
}

bool None::equals(Node* in)
{
    assert (0);
}

Node* None::find(Node* in)
{
    assert (0);
}

void None::find_all(Node* in, Node_list* out)
{
    assert (0);
}

}

