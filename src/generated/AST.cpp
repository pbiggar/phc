#include "AST.h"
#include "AST_transform.h"
#include "AST_visitor.h"

namespace AST{
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

bool Node::is_mixin_equal(Node* in)
{
    {
		// Compare line number and filename
		// (We can't compare the entire attrs map because Object cannot
		// necessarily be compared for equality)

		if(get_line_number() != in->get_line_number())
			return false;

		if(get_filename() == NULL)
		{
			if(in->get_filename() != NULL)
				return false;
		}
		else
		{
			if(*get_filename() != *in->get_filename())
				return false;
		}

		return true;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Signature::Signature(Method_mod* method_mod, bool is_ref, METHOD_NAME* method_name, Formal_parameter_list* formal_parameters)
{
    this->method_mod = method_mod;
    this->is_ref = is_ref;
    this->method_name = method_name;
    this->formal_parameters = formal_parameters;
}

Signature::Signature()
{
    this->method_mod = 0;
    this->is_ref = 0;
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
    
    that->is_ref = this->is_ref;
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
    
    if(this->is_ref != that->is_ref)
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Signature* Signature::clone()
{
    Method_mod* method_mod = this->method_mod ? this->method_mod->clone() : NULL;
    bool is_ref = this->is_ref;
    METHOD_NAME* method_name = this->method_name ? this->method_name->clone() : NULL;
    Formal_parameter_list* formal_parameters = NULL;
    if(this->formal_parameters != NULL)
    {
    	Formal_parameter_list::const_iterator i;
    	formal_parameters = new Formal_parameter_list;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    		formal_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    Signature* clone = new Signature(method_mod, is_ref, method_name, formal_parameters);
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
		this->is_ref = false;
		this->method_name = new METHOD_NAME(name);
		this->formal_parameters = new Formal_parameter_list;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Name_with_default::Name_with_default(VARIABLE_NAME* variable_name, Expr* expr)
{
    this->variable_name = variable_name;
    this->expr = expr;
}

Name_with_default::Name_with_default()
{
    this->variable_name = 0;
    this->expr = 0;
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Name_with_default* Name_with_default::clone()
{
    VARIABLE_NAME* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Name_with_default* clone = new Name_with_default(variable_name, expr);
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
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Name_with_default::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Name_with_default::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    if(expr != NULL) expr->assert_valid();
    Node::assert_mixin_valid();
}

Directive::Directive(DIRECTIVE_NAME* directive_name, Expr* expr)
{
    this->directive_name = directive_name;
    this->expr = expr;
}

Directive::Directive()
{
    this->directive_name = 0;
    this->expr = 0;
}

void Directive::visit(Visitor* visitor)
{
    visitor->visit_directive(this);
}

void Directive::transform_children(Transform* transform)
{
    transform->children_directive(this);
}

const int Directive::ID;
int Directive::classid()
{
    return ID;
}

bool Directive::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Directive* that = dynamic_cast<Directive*>(in);
    if(that == NULL) return false;
    
    if(this->directive_name == NULL)
    {
    	if(that->directive_name != NULL && !that->directive_name->match(this->directive_name))
    		return false;
    }
    else if(!this->directive_name->match(that->directive_name))
    	return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Directive::equals(Node* in)
{
    Directive* that = dynamic_cast<Directive*>(in);
    if(that == NULL) return false;
    
    if(this->directive_name == NULL || that->directive_name == NULL)
    {
    	if(this->directive_name != NULL || that->directive_name != NULL)
    		return false;
    }
    else if(!this->directive_name->equals(that->directive_name))
    	return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Directive* Directive::clone()
{
    DIRECTIVE_NAME* directive_name = this->directive_name ? this->directive_name->clone() : NULL;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Directive* clone = new Directive(directive_name, expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Directive::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->directive_name != NULL)
    {
    	Node* directive_name_res = this->directive_name->find(in);
    	if (directive_name_res) return directive_name_res;
    }
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Directive::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->directive_name != NULL)
    	this->directive_name->find_all(in, out);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Directive::assert_valid()
{
    assert(directive_name != NULL);
    directive_name->assert_valid();
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

List_element::List_element()
{
}

Variable_name::Variable_name()
{
}

Target::Target()
{
}

Array_elem::Array_elem(Expr* key, bool is_ref, Expr* val)
{
    this->key = key;
    this->is_ref = is_ref;
    this->val = val;
}

Array_elem::Array_elem()
{
    this->key = 0;
    this->is_ref = 0;
    this->val = 0;
}

void Array_elem::visit(Visitor* visitor)
{
    visitor->visit_array_elem(this);
}

void Array_elem::transform_children(Transform* transform)
{
    transform->children_array_elem(this);
}

const int Array_elem::ID;
int Array_elem::classid()
{
    return ID;
}

bool Array_elem::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Array_elem* that = dynamic_cast<Array_elem*>(in);
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

bool Array_elem::equals(Node* in)
{
    Array_elem* that = dynamic_cast<Array_elem*>(in);
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Array_elem* Array_elem::clone()
{
    Expr* key = this->key ? this->key->clone() : NULL;
    bool is_ref = this->is_ref;
    Expr* val = this->val ? this->val->clone() : NULL;
    Array_elem* clone = new Array_elem(key, is_ref, val);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Array_elem::find(Node* in)
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

void Array_elem::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->key != NULL)
    	this->key->find_all(in, out);
    
    if (this->val != NULL)
    	this->val->find_all(in, out);
    
}

void Array_elem::assert_valid()
{
    if(key != NULL) key->assert_valid();
    assert(val != NULL);
    val->assert_valid();
    Node::assert_mixin_valid();
}

Method_name::Method_name()
{
}

Actual_parameter::Actual_parameter(bool is_ref, Expr* expr)
{
    this->is_ref = is_ref;
    this->expr = expr;
}

Actual_parameter::Actual_parameter()
{
    this->is_ref = 0;
    this->expr = 0;
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
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Actual_parameter::equals(Node* in)
{
    Actual_parameter* that = dynamic_cast<Actual_parameter*>(in);
    if(that == NULL) return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Actual_parameter* Actual_parameter::clone()
{
    bool is_ref = this->is_ref;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Actual_parameter* clone = new Actual_parameter(is_ref, expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Actual_parameter::find(Node* in)
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

void Actual_parameter::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Actual_parameter::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Class_name::Class_name()
{
}

Commented_node::Commented_node()
{
    {
		attrs->set ("phc.comments", new String_list);
	}
}

/*  Return the comments associated with the node */
List<String*>* Commented_node::get_comments()
{
    {
		String_list* comments = dynamic_cast<String_list*>(attrs->get("phc.comments"));

		if (comments == NULL)
			return new String_list;

		return comments;
	}
}

Source_rep::Source_rep()
{
}

bool Source_rep::has_source_rep()
{
    {
		return (dynamic_cast<String*> (attrs->get ("phc.unparser.source_rep")) != NULL);
	}
}

String* Source_rep::get_source_rep()
{
    {
		String* result = dynamic_cast<String*> (attrs->get ("phc.unparser.source_rep"));
		if (result == NULL)
			result = get_value_as_string ();

		return result;
	}
}

void Source_rep::set_source_rep(String* source_rep)
{
    {
		assert (source_rep != NULL);
		attrs->set ("phc.unparser.source_rep", source_rep);
	}
}

Statement::Statement()
{
}

Member::Member()
{
}

Switch_case::Switch_case(Expr* expr, Statement_list* statements)
{
    this->expr = expr;
    this->statements = statements;
}

Switch_case::Switch_case()
{
    this->expr = 0;
    this->statements = 0;
}

void Switch_case::visit(Visitor* visitor)
{
    visitor->visit_switch_case(this);
}

void Switch_case::transform_children(Transform* transform)
{
    transform->children_switch_case(this);
}

const int Switch_case::ID;
int Switch_case::classid()
{
    return ID;
}

bool Switch_case::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Switch_case* that = dynamic_cast<Switch_case*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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

bool Switch_case::equals(Node* in)
{
    Switch_case* that = dynamic_cast<Switch_case*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Switch_case* Switch_case::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Switch_case* clone = new Switch_case(expr, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Switch_case::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
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

void Switch_case::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
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

void Switch_case::assert_valid()
{
    if(expr != NULL) expr->assert_valid();
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Nested_list_elements::Nested_list_elements(List_element_list* list_elements)
{
    this->list_elements = list_elements;
}

Nested_list_elements::Nested_list_elements()
{
    this->list_elements = 0;
}

void Nested_list_elements::visit(Visitor* visitor)
{
    visitor->visit_list_element(this);
}

void Nested_list_elements::transform_children(Transform* transform)
{
    transform->children_list_element(this);
}

const int Nested_list_elements::ID;
int Nested_list_elements::classid()
{
    return ID;
}

bool Nested_list_elements::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Nested_list_elements* that = dynamic_cast<Nested_list_elements*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements != NULL && that->list_elements != NULL)
    {
    	List_element_list::const_iterator i, j;
    	for(
    		i = this->list_elements->begin(), j = that->list_elements->begin();
    		i != this->list_elements->end() && j != that->list_elements->end();
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
    	if(i != this->list_elements->end() || j != that->list_elements->end())
    		return false;
    }
    
    return true;
}

bool Nested_list_elements::equals(Node* in)
{
    Nested_list_elements* that = dynamic_cast<Nested_list_elements*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements == NULL || that->list_elements == NULL)
    {
    	if(this->list_elements != NULL || that->list_elements != NULL)
    		return false;
    }
    else
    {
    	List_element_list::const_iterator i, j;
    	for(
    		i = this->list_elements->begin(), j = that->list_elements->begin();
    		i != this->list_elements->end() && j != that->list_elements->end();
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
    	if(i != this->list_elements->end() || j != that->list_elements->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Nested_list_elements* Nested_list_elements::clone()
{
    List_element_list* list_elements = NULL;
    if(this->list_elements != NULL)
    {
    	List_element_list::const_iterator i;
    	list_elements = new List_element_list;
    	for(i = this->list_elements->begin(); i != this->list_elements->end(); i++)
    		list_elements->push_back(*i ? (*i)->clone() : NULL);
    }
    Nested_list_elements* clone = new Nested_list_elements(list_elements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Nested_list_elements::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->list_elements != NULL)
    {
    	List_element_list::const_iterator i;
    	for(
    		i = this->list_elements->begin();
    		i != this->list_elements->end();
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

void Nested_list_elements::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->list_elements != NULL)
    {
    	List_element_list::const_iterator i;
    	for(
    		i = this->list_elements->begin();
    		i != this->list_elements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Nested_list_elements::assert_valid()
{
    assert(list_elements != NULL);
    {
    	List_element_list::const_iterator i;
    	for(i = this->list_elements->begin(); i != this->list_elements->end(); i++)
    	{
    		if(*i != NULL) (*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Reflection::Reflection(Expr* expr)
{
    this->expr = expr;
}

Reflection::Reflection()
{
    this->expr = 0;
}

void Reflection::visit(Visitor* visitor)
{
    visitor->visit_class_name(this);
}

void Reflection::transform_children(Transform* transform)
{
    transform->children_class_name(this);
}

const int Reflection::ID;
int Reflection::classid()
{
    return ID;
}

bool Reflection::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Reflection* that = dynamic_cast<Reflection*>(in);
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

bool Reflection::equals(Node* in)
{
    Reflection* that = dynamic_cast<Reflection*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Reflection* Reflection::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Reflection* clone = new Reflection(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Reflection::find(Node* in)
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

void Reflection::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Reflection::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Identifier::Identifier()
{
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    visitor->visit_statement(this);
}

void Method::transform_children(Transform* transform)
{
    transform->children_statement(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Attribute::Attribute(Attr_mod* attr_mod, Name_with_default_list* vars)
{
    this->attr_mod = attr_mod;
    this->vars = vars;
}

Attribute::Attribute()
{
    this->attr_mod = 0;
    this->vars = 0;
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
    
    if(this->vars != NULL && that->vars != NULL)
    {
    	Name_with_default_list::const_iterator i, j;
    	for(
    		i = this->vars->begin(), j = that->vars->begin();
    		i != this->vars->end() && j != that->vars->end();
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
    	if(i != this->vars->end() || j != that->vars->end())
    		return false;
    }
    
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
    
    if(this->vars == NULL || that->vars == NULL)
    {
    	if(this->vars != NULL || that->vars != NULL)
    		return false;
    }
    else
    {
    	Name_with_default_list::const_iterator i, j;
    	for(
    		i = this->vars->begin(), j = that->vars->begin();
    		i != this->vars->end() && j != that->vars->end();
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
    	if(i != this->vars->end() || j != that->vars->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Attribute* Attribute::clone()
{
    Attr_mod* attr_mod = this->attr_mod ? this->attr_mod->clone() : NULL;
    Name_with_default_list* vars = NULL;
    if(this->vars != NULL)
    {
    	Name_with_default_list::const_iterator i;
    	vars = new Name_with_default_list;
    	for(i = this->vars->begin(); i != this->vars->end(); i++)
    		vars->push_back(*i ? (*i)->clone() : NULL);
    }
    Attribute* clone = new Attribute(attr_mod, vars);
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
    
    if(this->vars != NULL)
    {
    	Name_with_default_list::const_iterator i;
    	for(
    		i = this->vars->begin();
    		i != this->vars->end();
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

void Attribute::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->attr_mod != NULL)
    	this->attr_mod->find_all(in, out);
    
    if(this->vars != NULL)
    {
    	Name_with_default_list::const_iterator i;
    	for(
    		i = this->vars->begin();
    		i != this->vars->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Attribute::assert_valid()
{
    assert(attr_mod != NULL);
    attr_mod->assert_valid();
    assert(vars != NULL);
    {
    	Name_with_default_list::const_iterator i;
    	for(i = this->vars->begin(); i != this->vars->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

If::If(Expr* expr, Statement_list* iftrue, Statement_list* iffalse)
{
    this->expr = expr;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

If::If()
{
    this->expr = 0;
    this->iftrue = 0;
    this->iffalse = 0;
}

void If::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void If::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int If::ID;
int If::classid()
{
    return ID;
}

bool If::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    If* that = dynamic_cast<If*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    if(this->iftrue != NULL && that->iftrue != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->iftrue->begin(), j = that->iftrue->begin();
    		i != this->iftrue->end() && j != that->iftrue->end();
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
    	if(i != this->iftrue->end() || j != that->iftrue->end())
    		return false;
    }
    
    if(this->iffalse != NULL && that->iffalse != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->iffalse->begin(), j = that->iffalse->begin();
    		i != this->iffalse->end() && j != that->iffalse->end();
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
    	if(i != this->iffalse->end() || j != that->iffalse->end())
    		return false;
    }
    
    return true;
}

bool If::equals(Node* in)
{
    If* that = dynamic_cast<If*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(this->iftrue == NULL || that->iftrue == NULL)
    {
    	if(this->iftrue != NULL || that->iftrue != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->iftrue->begin(), j = that->iftrue->begin();
    		i != this->iftrue->end() && j != that->iftrue->end();
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
    	if(i != this->iftrue->end() || j != that->iftrue->end())
    		return false;
    }
    
    if(this->iffalse == NULL || that->iffalse == NULL)
    {
    	if(this->iffalse != NULL || that->iffalse != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->iffalse->begin(), j = that->iffalse->begin();
    		i != this->iffalse->end() && j != that->iffalse->end();
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
    	if(i != this->iffalse->end() || j != that->iffalse->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

If* If::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Statement_list* iftrue = NULL;
    if(this->iftrue != NULL)
    {
    	Statement_list::const_iterator i;
    	iftrue = new Statement_list;
    	for(i = this->iftrue->begin(); i != this->iftrue->end(); i++)
    		iftrue->push_back(*i ? (*i)->clone() : NULL);
    }
    Statement_list* iffalse = NULL;
    if(this->iffalse != NULL)
    {
    	Statement_list::const_iterator i;
    	iffalse = new Statement_list;
    	for(i = this->iffalse->begin(); i != this->iffalse->end(); i++)
    		iffalse->push_back(*i ? (*i)->clone() : NULL);
    }
    If* clone = new If(expr, iftrue, iffalse);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* If::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    if(this->iftrue != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->iftrue->begin();
    		i != this->iftrue->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if(this->iffalse != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->iffalse->begin();
    		i != this->iffalse->end();
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

void If::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
    if(this->iftrue != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->iftrue->begin();
    		i != this->iftrue->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if(this->iffalse != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->iffalse->begin();
    		i != this->iffalse->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void If::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    assert(iftrue != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->iftrue->begin(); i != this->iftrue->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(iffalse != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->iffalse->begin(); i != this->iffalse->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

If::If(Expr* expr)
{
    {
		If (expr, new Statement_list, new Statement_list);
	}
}

While::While(Expr* expr, Statement_list* statements)
{
    this->expr = expr;
    this->statements = statements;
}

While::While()
{
    this->expr = 0;
    this->statements = 0;
}

void While::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void While::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int While::ID;
int While::classid()
{
    return ID;
}

bool While::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    While* that = dynamic_cast<While*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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

bool While::equals(Node* in)
{
    While* that = dynamic_cast<While*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

While* While::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    While* clone = new While(expr, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* While::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
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

void While::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
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

void While::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
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

Do::Do(Statement_list* statements, Expr* expr)
{
    this->statements = statements;
    this->expr = expr;
}

Do::Do()
{
    this->statements = 0;
    this->expr = 0;
}

void Do::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Do::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Do::ID;
int Do::classid()
{
    return ID;
}

bool Do::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Do* that = dynamic_cast<Do*>(in);
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Do::equals(Node* in)
{
    Do* that = dynamic_cast<Do*>(in);
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
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Do* Do::clone()
{
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Do* clone = new Do(statements, expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Do::find(Node* in)
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
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Do::find_all(Node* in, Node_list* out)
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
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Do::assert_valid()
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
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

For::For(Expr* init, Expr* cond, Expr* incr, Statement_list* statements)
{
    this->init = init;
    this->cond = cond;
    this->incr = incr;
    this->statements = statements;
}

For::For()
{
    this->init = 0;
    this->cond = 0;
    this->incr = 0;
    this->statements = 0;
}

void For::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void For::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int For::ID;
int For::classid()
{
    return ID;
}

bool For::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    For* that = dynamic_cast<For*>(in);
    if(that == NULL) return false;
    
    if(this->init == NULL)
    {
    	if(that->init != NULL && !that->init->match(this->init))
    		return false;
    }
    else if(!this->init->match(that->init))
    	return false;
    
    if(this->cond == NULL)
    {
    	if(that->cond != NULL && !that->cond->match(this->cond))
    		return false;
    }
    else if(!this->cond->match(that->cond))
    	return false;
    
    if(this->incr == NULL)
    {
    	if(that->incr != NULL && !that->incr->match(this->incr))
    		return false;
    }
    else if(!this->incr->match(that->incr))
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

bool For::equals(Node* in)
{
    For* that = dynamic_cast<For*>(in);
    if(that == NULL) return false;
    
    if(this->init == NULL || that->init == NULL)
    {
    	if(this->init != NULL || that->init != NULL)
    		return false;
    }
    else if(!this->init->equals(that->init))
    	return false;
    
    if(this->cond == NULL || that->cond == NULL)
    {
    	if(this->cond != NULL || that->cond != NULL)
    		return false;
    }
    else if(!this->cond->equals(that->cond))
    	return false;
    
    if(this->incr == NULL || that->incr == NULL)
    {
    	if(this->incr != NULL || that->incr != NULL)
    		return false;
    }
    else if(!this->incr->equals(that->incr))
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

For* For::clone()
{
    Expr* init = this->init ? this->init->clone() : NULL;
    Expr* cond = this->cond ? this->cond->clone() : NULL;
    Expr* incr = this->incr ? this->incr->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    For* clone = new For(init, cond, incr, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* For::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->init != NULL)
    {
    	Node* init_res = this->init->find(in);
    	if (init_res) return init_res;
    }
    
    if (this->cond != NULL)
    {
    	Node* cond_res = this->cond->find(in);
    	if (cond_res) return cond_res;
    }
    
    if (this->incr != NULL)
    {
    	Node* incr_res = this->incr->find(in);
    	if (incr_res) return incr_res;
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

void For::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->init != NULL)
    	this->init->find_all(in, out);
    
    if (this->cond != NULL)
    	this->cond->find_all(in, out);
    
    if (this->incr != NULL)
    	this->incr->find_all(in, out);
    
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

void For::assert_valid()
{
    if(init != NULL) init->assert_valid();
    if(cond != NULL) cond->assert_valid();
    if(incr != NULL) incr->assert_valid();
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

Foreach::Foreach(Expr* expr, Variable* key, bool is_ref, Variable* val, Statement_list* statements)
{
    this->expr = expr;
    this->key = key;
    this->is_ref = is_ref;
    this->val = val;
    this->statements = statements;
}

Foreach::Foreach()
{
    this->expr = 0;
    this->key = 0;
    this->is_ref = 0;
    this->val = 0;
    this->statements = 0;
}

void Foreach::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Foreach::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Foreach::ID;
int Foreach::classid()
{
    return ID;
}

bool Foreach::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Foreach* that = dynamic_cast<Foreach*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
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

bool Foreach::equals(Node* in)
{
    Foreach* that = dynamic_cast<Foreach*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Foreach* Foreach::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Variable* key = this->key ? this->key->clone() : NULL;
    bool is_ref = this->is_ref;
    Variable* val = this->val ? this->val->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Foreach* clone = new Foreach(expr, key, is_ref, val, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Foreach::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
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

void Foreach::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
    if (this->key != NULL)
    	this->key->find_all(in, out);
    
    if (this->val != NULL)
    	this->val->find_all(in, out);
    
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

void Foreach::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    if(key != NULL) key->assert_valid();
    assert(val != NULL);
    val->assert_valid();
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

Switch::Switch(Expr* expr, Switch_case_list* switch_cases)
{
    this->expr = expr;
    this->switch_cases = switch_cases;
}

Switch::Switch()
{
    this->expr = 0;
    this->switch_cases = 0;
}

void Switch::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Switch::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Switch::ID;
int Switch::classid()
{
    return ID;
}

bool Switch::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Switch* that = dynamic_cast<Switch*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    if(this->switch_cases != NULL && that->switch_cases != NULL)
    {
    	Switch_case_list::const_iterator i, j;
    	for(
    		i = this->switch_cases->begin(), j = that->switch_cases->begin();
    		i != this->switch_cases->end() && j != that->switch_cases->end();
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
    	if(i != this->switch_cases->end() || j != that->switch_cases->end())
    		return false;
    }
    
    return true;
}

bool Switch::equals(Node* in)
{
    Switch* that = dynamic_cast<Switch*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(this->switch_cases == NULL || that->switch_cases == NULL)
    {
    	if(this->switch_cases != NULL || that->switch_cases != NULL)
    		return false;
    }
    else
    {
    	Switch_case_list::const_iterator i, j;
    	for(
    		i = this->switch_cases->begin(), j = that->switch_cases->begin();
    		i != this->switch_cases->end() && j != that->switch_cases->end();
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
    	if(i != this->switch_cases->end() || j != that->switch_cases->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Switch* Switch::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Switch_case_list* switch_cases = NULL;
    if(this->switch_cases != NULL)
    {
    	Switch_case_list::const_iterator i;
    	switch_cases = new Switch_case_list;
    	for(i = this->switch_cases->begin(); i != this->switch_cases->end(); i++)
    		switch_cases->push_back(*i ? (*i)->clone() : NULL);
    }
    Switch* clone = new Switch(expr, switch_cases);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Switch::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    if(this->switch_cases != NULL)
    {
    	Switch_case_list::const_iterator i;
    	for(
    		i = this->switch_cases->begin();
    		i != this->switch_cases->end();
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

void Switch::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
    if(this->switch_cases != NULL)
    {
    	Switch_case_list::const_iterator i;
    	for(
    		i = this->switch_cases->begin();
    		i != this->switch_cases->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Switch::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    assert(switch_cases != NULL);
    {
    	Switch_case_list::const_iterator i;
    	for(i = this->switch_cases->begin(); i != this->switch_cases->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Break::Break(Expr* expr)
{
    this->expr = expr;
}

Break::Break()
{
    this->expr = 0;
}

void Break::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Break::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Break::ID;
int Break::classid()
{
    return ID;
}

bool Break::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Break* that = dynamic_cast<Break*>(in);
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

bool Break::equals(Node* in)
{
    Break* that = dynamic_cast<Break*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Break* Break::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Break* clone = new Break(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Break::find(Node* in)
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

void Break::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Break::assert_valid()
{
    if(expr != NULL) expr->assert_valid();
    Node::assert_mixin_valid();
}

Continue::Continue(Expr* expr)
{
    this->expr = expr;
}

Continue::Continue()
{
    this->expr = 0;
}

void Continue::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Continue::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Continue::ID;
int Continue::classid()
{
    return ID;
}

bool Continue::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Continue* that = dynamic_cast<Continue*>(in);
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

bool Continue::equals(Node* in)
{
    Continue* that = dynamic_cast<Continue*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Continue* Continue::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Continue* clone = new Continue(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Continue::find(Node* in)
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

void Continue::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Continue::assert_valid()
{
    if(expr != NULL) expr->assert_valid();
    Node::assert_mixin_valid();
}

Return::Return(Expr* expr)
{
    this->expr = expr;
}

Return::Return()
{
    this->expr = 0;
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Return::equals(Node* in)
{
    Return* that = dynamic_cast<Return*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Return* Return::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Return* clone = new Return(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Return::find(Node* in)
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

void Return::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Return::assert_valid()
{
    if(expr != NULL) expr->assert_valid();
    Node::assert_mixin_valid();
}

Static_declaration::Static_declaration(Name_with_default_list* vars)
{
    this->vars = vars;
}

Static_declaration::Static_declaration()
{
    this->vars = 0;
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
    
    if(this->vars != NULL && that->vars != NULL)
    {
    	Name_with_default_list::const_iterator i, j;
    	for(
    		i = this->vars->begin(), j = that->vars->begin();
    		i != this->vars->end() && j != that->vars->end();
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
    	if(i != this->vars->end() || j != that->vars->end())
    		return false;
    }
    
    return true;
}

bool Static_declaration::equals(Node* in)
{
    Static_declaration* that = dynamic_cast<Static_declaration*>(in);
    if(that == NULL) return false;
    
    if(this->vars == NULL || that->vars == NULL)
    {
    	if(this->vars != NULL || that->vars != NULL)
    		return false;
    }
    else
    {
    	Name_with_default_list::const_iterator i, j;
    	for(
    		i = this->vars->begin(), j = that->vars->begin();
    		i != this->vars->end() && j != that->vars->end();
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
    	if(i != this->vars->end() || j != that->vars->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Static_declaration* Static_declaration::clone()
{
    Name_with_default_list* vars = NULL;
    if(this->vars != NULL)
    {
    	Name_with_default_list::const_iterator i;
    	vars = new Name_with_default_list;
    	for(i = this->vars->begin(); i != this->vars->end(); i++)
    		vars->push_back(*i ? (*i)->clone() : NULL);
    }
    Static_declaration* clone = new Static_declaration(vars);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Static_declaration::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->vars != NULL)
    {
    	Name_with_default_list::const_iterator i;
    	for(
    		i = this->vars->begin();
    		i != this->vars->end();
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

void Static_declaration::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->vars != NULL)
    {
    	Name_with_default_list::const_iterator i;
    	for(
    		i = this->vars->begin();
    		i != this->vars->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Static_declaration::assert_valid()
{
    assert(vars != NULL);
    {
    	Name_with_default_list::const_iterator i;
    	for(i = this->vars->begin(); i != this->vars->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Global::Global(Variable_name_list* variable_names)
{
    this->variable_names = variable_names;
}

Global::Global()
{
    this->variable_names = 0;
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
    
    if(this->variable_names != NULL && that->variable_names != NULL)
    {
    	Variable_name_list::const_iterator i, j;
    	for(
    		i = this->variable_names->begin(), j = that->variable_names->begin();
    		i != this->variable_names->end() && j != that->variable_names->end();
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
    	if(i != this->variable_names->end() || j != that->variable_names->end())
    		return false;
    }
    
    return true;
}

bool Global::equals(Node* in)
{
    Global* that = dynamic_cast<Global*>(in);
    if(that == NULL) return false;
    
    if(this->variable_names == NULL || that->variable_names == NULL)
    {
    	if(this->variable_names != NULL || that->variable_names != NULL)
    		return false;
    }
    else
    {
    	Variable_name_list::const_iterator i, j;
    	for(
    		i = this->variable_names->begin(), j = that->variable_names->begin();
    		i != this->variable_names->end() && j != that->variable_names->end();
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
    	if(i != this->variable_names->end() || j != that->variable_names->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Global* Global::clone()
{
    Variable_name_list* variable_names = NULL;
    if(this->variable_names != NULL)
    {
    	Variable_name_list::const_iterator i;
    	variable_names = new Variable_name_list;
    	for(i = this->variable_names->begin(); i != this->variable_names->end(); i++)
    		variable_names->push_back(*i ? (*i)->clone() : NULL);
    }
    Global* clone = new Global(variable_names);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Global::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->variable_names != NULL)
    {
    	Variable_name_list::const_iterator i;
    	for(
    		i = this->variable_names->begin();
    		i != this->variable_names->end();
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

void Global::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->variable_names != NULL)
    {
    	Variable_name_list::const_iterator i;
    	for(
    		i = this->variable_names->begin();
    		i != this->variable_names->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Global::assert_valid()
{
    assert(variable_names != NULL);
    {
    	Variable_name_list::const_iterator i;
    	for(i = this->variable_names->begin(); i != this->variable_names->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Declare::Declare(Directive_list* directives, Statement_list* statements)
{
    this->directives = directives;
    this->statements = statements;
}

Declare::Declare()
{
    this->directives = 0;
    this->statements = 0;
}

void Declare::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Declare::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Declare::ID;
int Declare::classid()
{
    return ID;
}

bool Declare::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Declare* that = dynamic_cast<Declare*>(in);
    if(that == NULL) return false;
    
    if(this->directives != NULL && that->directives != NULL)
    {
    	Directive_list::const_iterator i, j;
    	for(
    		i = this->directives->begin(), j = that->directives->begin();
    		i != this->directives->end() && j != that->directives->end();
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
    	if(i != this->directives->end() || j != that->directives->end())
    		return false;
    }
    
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

bool Declare::equals(Node* in)
{
    Declare* that = dynamic_cast<Declare*>(in);
    if(that == NULL) return false;
    
    if(this->directives == NULL || that->directives == NULL)
    {
    	if(this->directives != NULL || that->directives != NULL)
    		return false;
    }
    else
    {
    	Directive_list::const_iterator i, j;
    	for(
    		i = this->directives->begin(), j = that->directives->begin();
    		i != this->directives->end() && j != that->directives->end();
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
    	if(i != this->directives->end() || j != that->directives->end())
    		return false;
    }
    
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Declare* Declare::clone()
{
    Directive_list* directives = NULL;
    if(this->directives != NULL)
    {
    	Directive_list::const_iterator i;
    	directives = new Directive_list;
    	for(i = this->directives->begin(); i != this->directives->end(); i++)
    		directives->push_back(*i ? (*i)->clone() : NULL);
    }
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Declare* clone = new Declare(directives, statements);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Declare::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->directives != NULL)
    {
    	Directive_list::const_iterator i;
    	for(
    		i = this->directives->begin();
    		i != this->directives->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
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

void Declare::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->directives != NULL)
    {
    	Directive_list::const_iterator i;
    	for(
    		i = this->directives->begin();
    		i != this->directives->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
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
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Declare::assert_valid()
{
    assert(directives != NULL);
    {
    	Directive_list::const_iterator i;
    	for(i = this->directives->begin(); i != this->directives->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Throw::Throw(Expr* expr)
{
    this->expr = expr;
}

Throw::Throw()
{
    this->expr = 0;
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Throw::equals(Node* in)
{
    Throw* that = dynamic_cast<Throw*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Throw* Throw::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Throw* clone = new Throw(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Throw::find(Node* in)
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

void Throw::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Throw::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Eval_expr::Eval_expr(Expr* expr)
{
    this->expr = expr;
    _init();
}

Eval_expr::Eval_expr()
{
    this->expr = 0;
    _init();
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

void Eval_expr::_init()
{
    {
		assert (expr != NULL);
	}
}

Nop::Nop()
{
}

void Nop::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Nop::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

const int Nop::ID;
int Nop::classid()
{
    return ID;
}

bool Nop::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Nop* that = dynamic_cast<Nop*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool Nop::equals(Node* in)
{
    Nop* that = dynamic_cast<Nop*>(in);
    if(that == NULL) return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Nop* Nop::clone()
{
    Nop* clone = new Nop();
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Nop::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Nop::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Nop::assert_valid()
{
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

Assignment::Assignment(Variable* variable, bool is_ref, Expr* expr)
{
    this->variable = variable;
    this->is_ref = is_ref;
    this->expr = expr;
}

Assignment::Assignment()
{
    this->variable = 0;
    this->is_ref = 0;
    this->expr = 0;
}

void Assignment::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Assignment::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Assignment::ID;
int Assignment::classid()
{
    return ID;
}

bool Assignment::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assignment* that = dynamic_cast<Assignment*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL)
    {
    	if(that->variable != NULL && !that->variable->match(this->variable))
    		return false;
    }
    else if(!this->variable->match(that->variable))
    	return false;
    
    that->is_ref = this->is_ref;
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Assignment::equals(Node* in)
{
    Assignment* that = dynamic_cast<Assignment*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL || that->variable == NULL)
    {
    	if(this->variable != NULL || that->variable != NULL)
    		return false;
    }
    else if(!this->variable->equals(that->variable))
    	return false;
    
    if(this->is_ref != that->is_ref)
    	return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Assignment* Assignment::clone()
{
    Variable* variable = this->variable ? this->variable->clone() : NULL;
    bool is_ref = this->is_ref;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Assignment* clone = new Assignment(variable, is_ref, expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Assignment::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable != NULL)
    {
    	Node* variable_res = this->variable->find(in);
    	if (variable_res) return variable_res;
    }
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Assignment::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable != NULL)
    	this->variable->find_all(in, out);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Assignment::assert_valid()
{
    assert(variable != NULL);
    variable->assert_valid();
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Op_assignment::Op_assignment(Variable* variable, OP* op, Expr* expr)
{
    this->variable = variable;
    this->op = op;
    this->expr = expr;
}

Op_assignment::Op_assignment()
{
    this->variable = 0;
    this->op = 0;
    this->expr = 0;
}

void Op_assignment::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Op_assignment::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Op_assignment::ID;
int Op_assignment::classid()
{
    return ID;
}

bool Op_assignment::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Op_assignment* that = dynamic_cast<Op_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL)
    {
    	if(that->variable != NULL && !that->variable->match(this->variable))
    		return false;
    }
    else if(!this->variable->match(that->variable))
    	return false;
    
    if(this->op == NULL)
    {
    	if(that->op != NULL && !that->op->match(this->op))
    		return false;
    }
    else if(!this->op->match(that->op))
    	return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool Op_assignment::equals(Node* in)
{
    Op_assignment* that = dynamic_cast<Op_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL || that->variable == NULL)
    {
    	if(this->variable != NULL || that->variable != NULL)
    		return false;
    }
    else if(!this->variable->equals(that->variable))
    	return false;
    
    if(this->op == NULL || that->op == NULL)
    {
    	if(this->op != NULL || that->op != NULL)
    		return false;
    }
    else if(!this->op->equals(that->op))
    	return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Op_assignment* Op_assignment::clone()
{
    Variable* variable = this->variable ? this->variable->clone() : NULL;
    OP* op = this->op ? this->op->clone() : NULL;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Op_assignment* clone = new Op_assignment(variable, op, expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Op_assignment::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable != NULL)
    {
    	Node* variable_res = this->variable->find(in);
    	if (variable_res) return variable_res;
    }
    
    if (this->op != NULL)
    {
    	Node* op_res = this->op->find(in);
    	if (op_res) return op_res;
    }
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Op_assignment::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable != NULL)
    	this->variable->find_all(in, out);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Op_assignment::assert_valid()
{
    assert(variable != NULL);
    variable->assert_valid();
    assert(op != NULL);
    op->assert_valid();
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Op_assignment::Op_assignment(Variable* variable, const char* op, Expr* expr)
{
    {
      this->variable = variable;
      this->op = new OP(new String(op));
      this->expr = expr;
   }
}

List_assignment::List_assignment(List_element_list* list_elements, Expr* expr)
{
    this->list_elements = list_elements;
    this->expr = expr;
}

List_assignment::List_assignment()
{
    this->list_elements = 0;
    this->expr = 0;
}

void List_assignment::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void List_assignment::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int List_assignment::ID;
int List_assignment::classid()
{
    return ID;
}

bool List_assignment::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    List_assignment* that = dynamic_cast<List_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements != NULL && that->list_elements != NULL)
    {
    	List_element_list::const_iterator i, j;
    	for(
    		i = this->list_elements->begin(), j = that->list_elements->begin();
    		i != this->list_elements->end() && j != that->list_elements->end();
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
    	if(i != this->list_elements->end() || j != that->list_elements->end())
    		return false;
    }
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
    	return false;
    
    return true;
}

bool List_assignment::equals(Node* in)
{
    List_assignment* that = dynamic_cast<List_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements == NULL || that->list_elements == NULL)
    {
    	if(this->list_elements != NULL || that->list_elements != NULL)
    		return false;
    }
    else
    {
    	List_element_list::const_iterator i, j;
    	for(
    		i = this->list_elements->begin(), j = that->list_elements->begin();
    		i != this->list_elements->end() && j != that->list_elements->end();
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
    	if(i != this->list_elements->end() || j != that->list_elements->end())
    		return false;
    }
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

List_assignment* List_assignment::clone()
{
    List_element_list* list_elements = NULL;
    if(this->list_elements != NULL)
    {
    	List_element_list::const_iterator i;
    	list_elements = new List_element_list;
    	for(i = this->list_elements->begin(); i != this->list_elements->end(); i++)
    		list_elements->push_back(*i ? (*i)->clone() : NULL);
    }
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    List_assignment* clone = new List_assignment(list_elements, expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* List_assignment::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->list_elements != NULL)
    {
    	List_element_list::const_iterator i;
    	for(
    		i = this->list_elements->begin();
    		i != this->list_elements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void List_assignment::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->list_elements != NULL)
    {
    	List_element_list::const_iterator i;
    	for(
    		i = this->list_elements->begin();
    		i != this->list_elements->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void List_assignment::assert_valid()
{
    assert(list_elements != NULL);
    {
    	List_element_list::const_iterator i;
    	for(i = this->list_elements->begin(); i != this->list_elements->end(); i++)
    	{
    		if(*i != NULL) (*i)->assert_valid();
    	}
    }
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Cast::Cast(CAST* cast, Expr* expr)
{
    this->cast = cast;
    this->expr = expr;
}

Cast::Cast()
{
    this->cast = 0;
    this->expr = 0;
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Cast* Cast::clone()
{
    CAST* cast = this->cast ? this->cast->clone() : NULL;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Cast* clone = new Cast(cast, expr);
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
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Cast::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->cast != NULL)
    	this->cast->find_all(in, out);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Cast::assert_valid()
{
    assert(cast != NULL);
    cast->assert_valid();
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Cast::Cast(const char* type, String* source_rep, Expr* expr)
{
    {
		this->cast = new CAST(new String(type));
		this->cast->set_source_rep (source_rep);
		this->expr = expr;
	}
}

Unary_op::Unary_op(OP* op, Expr* expr)
{
    this->op = op;
    this->expr = expr;
}

Unary_op::Unary_op()
{
    this->op = 0;
    this->expr = 0;
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Unary_op* Unary_op::clone()
{
    OP* op = this->op ? this->op->clone() : NULL;
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Unary_op* clone = new Unary_op(op, expr);
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
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
    }
    
    return NULL;
}

void Unary_op::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Unary_op::assert_valid()
{
    assert(op != NULL);
    op->assert_valid();
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
}

Unary_op::Unary_op(Expr* expr, const char* op)
{
    {
		this->expr = expr;
		this->op = new OP(new String(op));
	}
}

Bin_op::Bin_op(Expr* left, OP* op, Expr* right)
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Bin_op* Bin_op::clone()
{
    Expr* left = this->left ? this->left->clone() : NULL;
    OP* op = this->op ? this->op->clone() : NULL;
    Expr* right = this->right ? this->right->clone() : NULL;
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

Bin_op::Bin_op(Expr* left, Expr* right, const char* op)
{
    {
		this->left = left;
		this->op = new OP(new String(op));
		this->right = right;
	}
}

Conditional_expr::Conditional_expr(Expr* cond, Expr* iftrue, Expr* iffalse)
{
    this->cond = cond;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

Conditional_expr::Conditional_expr()
{
    this->cond = 0;
    this->iftrue = 0;
    this->iffalse = 0;
}

void Conditional_expr::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Conditional_expr::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Conditional_expr::ID;
int Conditional_expr::classid()
{
    return ID;
}

bool Conditional_expr::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Conditional_expr* that = dynamic_cast<Conditional_expr*>(in);
    if(that == NULL) return false;
    
    if(this->cond == NULL)
    {
    	if(that->cond != NULL && !that->cond->match(this->cond))
    		return false;
    }
    else if(!this->cond->match(that->cond))
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

bool Conditional_expr::equals(Node* in)
{
    Conditional_expr* that = dynamic_cast<Conditional_expr*>(in);
    if(that == NULL) return false;
    
    if(this->cond == NULL || that->cond == NULL)
    {
    	if(this->cond != NULL || that->cond != NULL)
    		return false;
    }
    else if(!this->cond->equals(that->cond))
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Conditional_expr* Conditional_expr::clone()
{
    Expr* cond = this->cond ? this->cond->clone() : NULL;
    Expr* iftrue = this->iftrue ? this->iftrue->clone() : NULL;
    Expr* iffalse = this->iffalse ? this->iffalse->clone() : NULL;
    Conditional_expr* clone = new Conditional_expr(cond, iftrue, iffalse);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Conditional_expr::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->cond != NULL)
    {
    	Node* cond_res = this->cond->find(in);
    	if (cond_res) return cond_res;
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

void Conditional_expr::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->cond != NULL)
    	this->cond->find_all(in, out);
    
    if (this->iftrue != NULL)
    	this->iftrue->find_all(in, out);
    
    if (this->iffalse != NULL)
    	this->iffalse->find_all(in, out);
    
}

void Conditional_expr::assert_valid()
{
    assert(cond != NULL);
    cond->assert_valid();
    assert(iftrue != NULL);
    iftrue->assert_valid();
    assert(iffalse != NULL);
    iffalse->assert_valid();
    Node::assert_mixin_valid();
}

Ignore_errors::Ignore_errors(Expr* expr)
{
    this->expr = expr;
}

Ignore_errors::Ignore_errors()
{
    this->expr = 0;
}

void Ignore_errors::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Ignore_errors::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Ignore_errors::ID;
int Ignore_errors::classid()
{
    return ID;
}

bool Ignore_errors::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Ignore_errors* that = dynamic_cast<Ignore_errors*>(in);
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

bool Ignore_errors::equals(Node* in)
{
    Ignore_errors* that = dynamic_cast<Ignore_errors*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Ignore_errors* Ignore_errors::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Ignore_errors* clone = new Ignore_errors(expr);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Ignore_errors::find(Node* in)
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

void Ignore_errors::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Ignore_errors::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    Node::assert_mixin_valid();
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
    visitor->visit_expr(this);
}

void Constant::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Instanceof::Instanceof(Expr* expr, Class_name* class_name)
{
    this->expr = expr;
    this->class_name = class_name;
}

Instanceof::Instanceof()
{
    this->expr = 0;
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
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Instanceof* Instanceof::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Instanceof* clone = new Instanceof(expr, class_name);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Instanceof::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->expr != NULL)
    {
    	Node* expr_res = this->expr->find(in);
    	if (expr_res) return expr_res;
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
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
    if (this->class_name != NULL)
    	this->class_name->find_all(in, out);
    
}

void Instanceof::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    assert(class_name != NULL);
    class_name->assert_valid();
    Node::assert_mixin_valid();
}

Variable::Variable(Target* target, Variable_name* variable_name, Expr_list* array_indices)
{
    this->target = target;
    this->variable_name = variable_name;
    this->array_indices = array_indices;
}

Variable::Variable()
{
    this->target = 0;
    this->variable_name = 0;
    this->array_indices = 0;
}

void Variable::visit(Visitor* visitor)
{
    visitor->visit_variable(this);
}

void Variable::transform_children(Transform* transform)
{
    transform->children_variable(this);
}

const int Variable::ID;
int Variable::classid()
{
    return ID;
}

bool Variable::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Variable* that = dynamic_cast<Variable*>(in);
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
    	Expr_list::const_iterator i, j;
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

bool Variable::equals(Node* in)
{
    Variable* that = dynamic_cast<Variable*>(in);
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
    	Expr_list::const_iterator i, j;
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
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Variable* Variable::clone()
{
    Target* target = this->target ? this->target->clone() : NULL;
    Variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    Expr_list* array_indices = NULL;
    if(this->array_indices != NULL)
    {
    	Expr_list::const_iterator i;
    	array_indices = new Expr_list;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    		array_indices->push_back(*i ? (*i)->clone() : NULL);
    }
    Variable* clone = new Variable(target, variable_name, array_indices);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Variable::find(Node* in)
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
    	Expr_list::const_iterator i;
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

void Variable::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->target != NULL)
    	this->target->find_all(in, out);
    
    if (this->variable_name != NULL)
    	this->variable_name->find_all(in, out);
    
    if(this->array_indices != NULL)
    {
    	Expr_list::const_iterator i;
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

void Variable::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(array_indices != NULL);
    {
    	Expr_list::const_iterator i;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    	{
    		if(*i != NULL) (*i)->assert_valid();
    	}
    }
    Node::assert_mixin_valid();
}

Variable::Variable(Variable_name* name)
{
    {
		this->target = NULL;
		this->variable_name = name;
		this->array_indices = new Expr_list;
	}
}

bool Variable::is_simple_variable()
{
    {
		return (
				target == NULL
			&& array_indices->size () == 0
			&& dynamic_cast<VARIABLE_NAME*> (variable_name));
	}
}

Pre_op::Pre_op(OP* op, Variable* variable)
{
    this->op = op;
    this->variable = variable;
}

Pre_op::Pre_op()
{
    this->op = 0;
    this->variable = 0;
}

void Pre_op::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Pre_op::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(this->variable == NULL)
    {
    	if(that->variable != NULL && !that->variable->match(this->variable))
    		return false;
    }
    else if(!this->variable->match(that->variable))
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
    
    if(this->variable == NULL || that->variable == NULL)
    {
    	if(this->variable != NULL || that->variable != NULL)
    		return false;
    }
    else if(!this->variable->equals(that->variable))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Pre_op* Pre_op::clone()
{
    OP* op = this->op ? this->op->clone() : NULL;
    Variable* variable = this->variable ? this->variable->clone() : NULL;
    Pre_op* clone = new Pre_op(op, variable);
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
    
    if (this->variable != NULL)
    {
    	Node* variable_res = this->variable->find(in);
    	if (variable_res) return variable_res;
    }
    
    return NULL;
}

void Pre_op::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
    if (this->variable != NULL)
    	this->variable->find_all(in, out);
    
}

void Pre_op::assert_valid()
{
    assert(op != NULL);
    op->assert_valid();
    assert(variable != NULL);
    variable->assert_valid();
    Node::assert_mixin_valid();
}

Pre_op::Pre_op(Variable* var, const char* op)
{
    {
		this->variable = var;
		this->op = new OP(new String(op));
	}
}

Post_op::Post_op(Variable* variable, OP* op)
{
    this->variable = variable;
    this->op = op;
}

Post_op::Post_op()
{
    this->variable = 0;
    this->op = 0;
}

void Post_op::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Post_op::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Post_op::ID;
int Post_op::classid()
{
    return ID;
}

bool Post_op::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Post_op* that = dynamic_cast<Post_op*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL)
    {
    	if(that->variable != NULL && !that->variable->match(this->variable))
    		return false;
    }
    else if(!this->variable->match(that->variable))
    	return false;
    
    if(this->op == NULL)
    {
    	if(that->op != NULL && !that->op->match(this->op))
    		return false;
    }
    else if(!this->op->match(that->op))
    	return false;
    
    return true;
}

bool Post_op::equals(Node* in)
{
    Post_op* that = dynamic_cast<Post_op*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL || that->variable == NULL)
    {
    	if(this->variable != NULL || that->variable != NULL)
    		return false;
    }
    else if(!this->variable->equals(that->variable))
    	return false;
    
    if(this->op == NULL || that->op == NULL)
    {
    	if(this->op != NULL || that->op != NULL)
    		return false;
    }
    else if(!this->op->equals(that->op))
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Post_op* Post_op::clone()
{
    Variable* variable = this->variable ? this->variable->clone() : NULL;
    OP* op = this->op ? this->op->clone() : NULL;
    Post_op* clone = new Post_op(variable, op);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Post_op::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->variable != NULL)
    {
    	Node* variable_res = this->variable->find(in);
    	if (variable_res) return variable_res;
    }
    
    if (this->op != NULL)
    {
    	Node* op_res = this->op->find(in);
    	if (op_res) return op_res;
    }
    
    return NULL;
}

void Post_op::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->variable != NULL)
    	this->variable->find_all(in, out);
    
    if (this->op != NULL)
    	this->op->find_all(in, out);
    
}

void Post_op::assert_valid()
{
    assert(variable != NULL);
    variable->assert_valid();
    assert(op != NULL);
    op->assert_valid();
    Node::assert_mixin_valid();
}

Post_op::Post_op(Variable* var, const char* op)
{
    {
		this->variable = var;
		this->op = new OP(new String(op));
	}
}

Array::Array(Array_elem_list* array_elems)
{
    this->array_elems = array_elems;
}

Array::Array()
{
    this->array_elems = 0;
}

void Array::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Array::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

const int Array::ID;
int Array::classid()
{
    return ID;
}

bool Array::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Array* that = dynamic_cast<Array*>(in);
    if(that == NULL) return false;
    
    if(this->array_elems != NULL && that->array_elems != NULL)
    {
    	Array_elem_list::const_iterator i, j;
    	for(
    		i = this->array_elems->begin(), j = that->array_elems->begin();
    		i != this->array_elems->end() && j != that->array_elems->end();
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
    	if(i != this->array_elems->end() || j != that->array_elems->end())
    		return false;
    }
    
    return true;
}

bool Array::equals(Node* in)
{
    Array* that = dynamic_cast<Array*>(in);
    if(that == NULL) return false;
    
    if(this->array_elems == NULL || that->array_elems == NULL)
    {
    	if(this->array_elems != NULL || that->array_elems != NULL)
    		return false;
    }
    else
    {
    	Array_elem_list::const_iterator i, j;
    	for(
    		i = this->array_elems->begin(), j = that->array_elems->begin();
    		i != this->array_elems->end() && j != that->array_elems->end();
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
    	if(i != this->array_elems->end() || j != that->array_elems->end())
    		return false;
    }
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

Array* Array::clone()
{
    Array_elem_list* array_elems = NULL;
    if(this->array_elems != NULL)
    {
    	Array_elem_list::const_iterator i;
    	array_elems = new Array_elem_list;
    	for(i = this->array_elems->begin(); i != this->array_elems->end(); i++)
    		array_elems->push_back(*i ? (*i)->clone() : NULL);
    }
    Array* clone = new Array(array_elems);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* Array::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->array_elems != NULL)
    {
    	Array_elem_list::const_iterator i;
    	for(
    		i = this->array_elems->begin();
    		i != this->array_elems->end();
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

void Array::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->array_elems != NULL)
    {
    	Array_elem_list::const_iterator i;
    	for(
    		i = this->array_elems->begin();
    		i != this->array_elems->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Array::assert_valid()
{
    assert(array_elems != NULL);
    {
    	Array_elem_list::const_iterator i;
    	for(i = this->array_elems->begin(); i != this->array_elems->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

Method_invocation::Method_invocation(const char* name, Expr* arg)
{
    { 
		this->target = NULL;
		this->method_name = new METHOD_NAME(name);
		Actual_parameter* actual_parameter = new Actual_parameter (false, arg);
		actual_parameter->copy_location (arg);
		this->actual_parameters = new Actual_parameter_list (actual_parameter);
	}
}

Method_invocation::Method_invocation(METHOD_NAME* name, Expr* arg)
{
    { 
		this->target = NULL;
		this->method_name = name; 
		Actual_parameter* actual_parameter = new Actual_parameter (false, arg);
		actual_parameter->copy_location (arg);
		this->actual_parameters = new Actual_parameter_list (actual_parameter);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    visitor->visit_statement(this);
}

void FOREIGN::transform_children(Transform* transform)
{
    transform->children_statement(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

VARIABLE_NAME::VARIABLE_NAME(String* value)
{
    this->value = value;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

VARIABLE_NAME::VARIABLE_NAME(const char* name)
{
    {
		this->value = new String (name);
	}
}

DIRECTIVE_NAME::DIRECTIVE_NAME(String* value)
{
    this->value = value;
}

DIRECTIVE_NAME::DIRECTIVE_NAME()
{
    this->value = 0;
}

void DIRECTIVE_NAME::visit(Visitor* visitor)
{
    visitor->visit_directive_name(this);
}

void DIRECTIVE_NAME::transform_children(Transform* transform)
{
    transform->children_directive_name(this);
}

String* DIRECTIVE_NAME::get_value_as_string()
{
    return value;
}

const int DIRECTIVE_NAME::ID;
int DIRECTIVE_NAME::classid()
{
    return ID;
}

bool DIRECTIVE_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    DIRECTIVE_NAME* that = dynamic_cast<DIRECTIVE_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool DIRECTIVE_NAME::equals(Node* in)
{
    DIRECTIVE_NAME* that = dynamic_cast<DIRECTIVE_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!Node::is_mixin_equal(that)) return false;
    return true;
}

DIRECTIVE_NAME* DIRECTIVE_NAME::clone()
{
    String* value = new String(*this->value);
    DIRECTIVE_NAME* clone = new DIRECTIVE_NAME(value);
    clone->Node::clone_mixin_from(this);
    return clone;
}

Node* DIRECTIVE_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void DIRECTIVE_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void DIRECTIVE_NAME::assert_valid()
{
    assert(value != NULL);
    Node::assert_mixin_valid();
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    
    if(!Node::is_mixin_equal(that)) return false;
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
    visitor->visit_expr(this);
}

void INT::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

INT::INT(long v, String* source_rep)
{
    {
		value = v;
		set_source_rep (source_rep);
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
    visitor->visit_expr(this);
}

void REAL::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

REAL::REAL(double v, String* source_rep)
{
    {
		value = v;
		set_source_rep (source_rep);
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
    visitor->visit_expr(this);
}

void STRING::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

STRING::STRING(String* v, String* source_rep)
{
    {
		value = v;
		set_source_rep (source_rep);
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
    visitor->visit_expr(this);
}

void BOOL::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

BOOL::BOOL(bool v, String* source_rep)
{
    {
		value = v;
		set_source_rep (source_rep);
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
    visitor->visit_expr(this);
}

void NIL::transform_children(Transform* transform)
{
    transform->children_expr(this);
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
    
    if(!Node::is_mixin_equal(that)) return false;
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

NIL::NIL(String* source_rep)
{
    {
		set_source_rep (source_rep);
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

