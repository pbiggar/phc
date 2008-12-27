#include "MICG.h"
#include "MICG_transform.h"
#include "MICG_visitor.h"

namespace MICG{
Node::Node()
{
}

Template::Template(Signature* signature, Rule_list* rules, Body* body)
{
    this->signature = signature;
    this->rules = rules;
    this->body = body;
}

Template::Template()
{
    this->signature = 0;
    this->rules = 0;
    this->body = 0;
}

void Template::visit(Visitor* visitor)
{
    visitor->visit_template(this);
}

void Template::transform_children(Transform* transform)
{
    transform->children_template(this);
}

int Template::classid()
{
    return ID;
}

bool Template::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Template* that = dynamic_cast<Template*>(in);
    if(that == NULL) return false;
    
    if(this->signature == NULL)
    {
    	if(that->signature != NULL && !that->signature->match(this->signature))
    		return false;
    }
    else if(!this->signature->match(that->signature))
    	return false;
    
    if(this->rules != NULL && that->rules != NULL)
    {
    	Rule_list::const_iterator i, j;
    	for(
    		i = this->rules->begin(), j = that->rules->begin();
    		i != this->rules->end() && j != that->rules->end();
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
    	if(i != this->rules->end() || j != that->rules->end())
    		return false;
    }
    
    if(this->body == NULL)
    {
    	if(that->body != NULL && !that->body->match(this->body))
    		return false;
    }
    else if(!this->body->match(that->body))
    	return false;
    
    return true;
}

bool Template::equals(Node* in)
{
    Template* that = dynamic_cast<Template*>(in);
    if(that == NULL) return false;
    
    if(this->signature == NULL || that->signature == NULL)
    {
    	if(this->signature != NULL || that->signature != NULL)
    		return false;
    }
    else if(!this->signature->equals(that->signature))
    	return false;
    
    if(this->rules == NULL || that->rules == NULL)
    {
    	if(this->rules != NULL || that->rules != NULL)
    		return false;
    }
    else
    {
    	Rule_list::const_iterator i, j;
    	for(
    		i = this->rules->begin(), j = that->rules->begin();
    		i != this->rules->end() && j != that->rules->end();
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
    	if(i != this->rules->end() || j != that->rules->end())
    		return false;
    }
    
    if(this->body == NULL || that->body == NULL)
    {
    	if(this->body != NULL || that->body != NULL)
    		return false;
    }
    else if(!this->body->equals(that->body))
    	return false;
    
    return true;
}

Template* Template::clone()
{
    Signature* signature = this->signature ? this->signature->clone() : NULL;
    Rule_list* rules = NULL;
    if(this->rules != NULL)
    {
    	Rule_list::const_iterator i;
    	rules = new Rule_list;
    	for(i = this->rules->begin(); i != this->rules->end(); i++)
    		rules->push_back(*i ? (*i)->clone() : NULL);
    }
    Body* body = this->body ? this->body->clone() : NULL;
    Template* clone = new Template(signature, rules, body);
    return clone;
}

Node* Template::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->signature != NULL)
    {
    	Node* signature_res = this->signature->find(in);
    	if (signature_res) return signature_res;
    }
    
    if(this->rules != NULL)
    {
    	Rule_list::const_iterator i;
    	for(
    		i = this->rules->begin();
    		i != this->rules->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if (this->body != NULL)
    {
    	Node* body_res = this->body->find(in);
    	if (body_res) return body_res;
    }
    
    return NULL;
}

void Template::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->signature != NULL)
    	this->signature->find_all(in, out);
    
    if(this->rules != NULL)
    {
    	Rule_list::const_iterator i;
    	for(
    		i = this->rules->begin();
    		i != this->rules->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if (this->body != NULL)
    	this->body->find_all(in, out);
    
}

void Template::assert_valid()
{
    assert(signature != NULL);
    signature->assert_valid();
    assert(rules != NULL);
    {
    	Rule_list::const_iterator i;
    	for(i = this->rules->begin(); i != this->rules->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(body != NULL);
    body->assert_valid();
}

Signature::Signature(PATTERN_NAME* pattern_name, Formal_parameter_list* formal_parameters)
{
    this->pattern_name = pattern_name;
    this->formal_parameters = formal_parameters;
}

Signature::Signature()
{
    this->pattern_name = 0;
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
    
    if(this->pattern_name == NULL)
    {
    	if(that->pattern_name != NULL && !that->pattern_name->match(this->pattern_name))
    		return false;
    }
    else if(!this->pattern_name->match(that->pattern_name))
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
    
    if(this->pattern_name == NULL || that->pattern_name == NULL)
    {
    	if(this->pattern_name != NULL || that->pattern_name != NULL)
    		return false;
    }
    else if(!this->pattern_name->equals(that->pattern_name))
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
    PATTERN_NAME* pattern_name = this->pattern_name ? this->pattern_name->clone() : NULL;
    Formal_parameter_list* formal_parameters = NULL;
    if(this->formal_parameters != NULL)
    {
    	Formal_parameter_list::const_iterator i;
    	formal_parameters = new Formal_parameter_list;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    		formal_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    Signature* clone = new Signature(pattern_name, formal_parameters);
    return clone;
}

Node* Signature::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->pattern_name != NULL)
    {
    	Node* pattern_name_res = this->pattern_name->find(in);
    	if (pattern_name_res) return pattern_name_res;
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
    
    if (this->pattern_name != NULL)
    	this->pattern_name->find_all(in, out);
    
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
    assert(pattern_name != NULL);
    pattern_name->assert_valid();
    assert(formal_parameters != NULL);
    {
    	Formal_parameter_list::const_iterator i;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
}

Formal_parameter::Formal_parameter(TYPE* type, PARAM_NAME* param_name)
{
    this->type = type;
    this->param_name = param_name;
}

Formal_parameter::Formal_parameter()
{
    this->type = 0;
    this->param_name = 0;
}

void Formal_parameter::visit(Visitor* visitor)
{
    visitor->visit_formal_parameter(this);
}

void Formal_parameter::transform_children(Transform* transform)
{
    transform->children_formal_parameter(this);
}

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
    
    if(this->param_name == NULL)
    {
    	if(that->param_name != NULL && !that->param_name->match(this->param_name))
    		return false;
    }
    else if(!this->param_name->match(that->param_name))
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
    
    if(this->param_name == NULL || that->param_name == NULL)
    {
    	if(this->param_name != NULL || that->param_name != NULL)
    		return false;
    }
    else if(!this->param_name->equals(that->param_name))
    	return false;
    
    return true;
}

Formal_parameter* Formal_parameter::clone()
{
    TYPE* type = this->type ? this->type->clone() : NULL;
    PARAM_NAME* param_name = this->param_name ? this->param_name->clone() : NULL;
    Formal_parameter* clone = new Formal_parameter(type, param_name);
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
    
    if (this->param_name != NULL)
    {
    	Node* param_name_res = this->param_name->find(in);
    	if (param_name_res) return param_name_res;
    }
    
    return NULL;
}

void Formal_parameter::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->type != NULL)
    	this->type->find_all(in, out);
    
    if (this->param_name != NULL)
    	this->param_name->find_all(in, out);
    
}

void Formal_parameter::assert_valid()
{
    assert(type != NULL);
    type->assert_valid();
    assert(param_name != NULL);
    param_name->assert_valid();
}

Rule::Rule(Expr* expr)
{
    this->expr = expr;
}

Rule::Rule()
{
    this->expr = 0;
}

void Rule::visit(Visitor* visitor)
{
    visitor->visit_rule(this);
}

void Rule::transform_children(Transform* transform)
{
    transform->children_rule(this);
}

int Rule::classid()
{
    return ID;
}

bool Rule::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Rule* that = dynamic_cast<Rule*>(in);
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

bool Rule::equals(Node* in)
{
    Rule* that = dynamic_cast<Rule*>(in);
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

Rule* Rule::clone()
{
    Expr* expr = this->expr ? this->expr->clone() : NULL;
    Rule* clone = new Rule(expr);
    return clone;
}

Node* Rule::find(Node* in)
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

void Rule::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->expr != NULL)
    	this->expr->find_all(in, out);
    
}

void Rule::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
}

Expr::Expr()
{
}

Body::Body(Body_part_list* body_parts)
{
    this->body_parts = body_parts;
}

Body::Body()
{
    this->body_parts = 0;
}

void Body::visit(Visitor* visitor)
{
    visitor->visit_body(this);
}

void Body::transform_children(Transform* transform)
{
    transform->children_body(this);
}

int Body::classid()
{
    return ID;
}

bool Body::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Body* that = dynamic_cast<Body*>(in);
    if(that == NULL) return false;
    
    if(this->body_parts != NULL && that->body_parts != NULL)
    {
    	Body_part_list::const_iterator i, j;
    	for(
    		i = this->body_parts->begin(), j = that->body_parts->begin();
    		i != this->body_parts->end() && j != that->body_parts->end();
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
    	if(i != this->body_parts->end() || j != that->body_parts->end())
    		return false;
    }
    
    return true;
}

bool Body::equals(Node* in)
{
    Body* that = dynamic_cast<Body*>(in);
    if(that == NULL) return false;
    
    if(this->body_parts == NULL || that->body_parts == NULL)
    {
    	if(this->body_parts != NULL || that->body_parts != NULL)
    		return false;
    }
    else
    {
    	Body_part_list::const_iterator i, j;
    	for(
    		i = this->body_parts->begin(), j = that->body_parts->begin();
    		i != this->body_parts->end() && j != that->body_parts->end();
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
    	if(i != this->body_parts->end() || j != that->body_parts->end())
    		return false;
    }
    
    return true;
}

Body* Body::clone()
{
    Body_part_list* body_parts = NULL;
    if(this->body_parts != NULL)
    {
    	Body_part_list::const_iterator i;
    	body_parts = new Body_part_list;
    	for(i = this->body_parts->begin(); i != this->body_parts->end(); i++)
    		body_parts->push_back(*i ? (*i)->clone() : NULL);
    }
    Body* clone = new Body(body_parts);
    return clone;
}

Node* Body::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->body_parts != NULL)
    {
    	Body_part_list::const_iterator i;
    	for(
    		i = this->body_parts->begin();
    		i != this->body_parts->end();
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

void Body::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->body_parts != NULL)
    {
    	Body_part_list::const_iterator i;
    	for(
    		i = this->body_parts->begin();
    		i != this->body_parts->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void Body::assert_valid()
{
    assert(body_parts != NULL);
    {
    	Body_part_list::const_iterator i;
    	for(i = this->body_parts->begin(); i != this->body_parts->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
}

Body_part::Body_part()
{
}

Actual_parameter::Actual_parameter()
{
}

PATTERN_NAME::PATTERN_NAME(String* value)
{
    this->value = value;
}

PATTERN_NAME::PATTERN_NAME()
{
    this->value = 0;
}

void PATTERN_NAME::visit(Visitor* visitor)
{
    visitor->visit_pattern_name(this);
}

void PATTERN_NAME::transform_children(Transform* transform)
{
    transform->children_pattern_name(this);
}

String* PATTERN_NAME::get_value_as_string()
{
    return value;
}

int PATTERN_NAME::classid()
{
    return ID;
}

bool PATTERN_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    PATTERN_NAME* that = dynamic_cast<PATTERN_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool PATTERN_NAME::equals(Node* in)
{
    PATTERN_NAME* that = dynamic_cast<PATTERN_NAME*>(in);
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

PATTERN_NAME* PATTERN_NAME::clone()
{
    String* value = new String(*this->value);
    PATTERN_NAME* clone = new PATTERN_NAME(value);
    return clone;
}

Node* PATTERN_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void PATTERN_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void PATTERN_NAME::assert_valid()
{
    assert(value != NULL);
}

TYPE::TYPE(String* value)
{
    this->value = value;
}

TYPE::TYPE()
{
    this->value = 0;
}

void TYPE::visit(Visitor* visitor)
{
    visitor->visit_type(this);
}

void TYPE::transform_children(Transform* transform)
{
    transform->children_type(this);
}

String* TYPE::get_value_as_string()
{
    return value;
}

int TYPE::classid()
{
    return ID;
}

bool TYPE::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    TYPE* that = dynamic_cast<TYPE*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool TYPE::equals(Node* in)
{
    TYPE* that = dynamic_cast<TYPE*>(in);
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

TYPE* TYPE::clone()
{
    String* value = new String(*this->value);
    TYPE* clone = new TYPE(value);
    return clone;
}

Node* TYPE::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void TYPE::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void TYPE::assert_valid()
{
    assert(value != NULL);
}

ATTR_NAME::ATTR_NAME(String* value)
{
    this->value = value;
}

ATTR_NAME::ATTR_NAME()
{
    this->value = 0;
}

void ATTR_NAME::visit(Visitor* visitor)
{
    visitor->visit_attr_name(this);
}

void ATTR_NAME::transform_children(Transform* transform)
{
    transform->children_attr_name(this);
}

String* ATTR_NAME::get_value_as_string()
{
    return value;
}

int ATTR_NAME::classid()
{
    return ID;
}

bool ATTR_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    ATTR_NAME* that = dynamic_cast<ATTR_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool ATTR_NAME::equals(Node* in)
{
    ATTR_NAME* that = dynamic_cast<ATTR_NAME*>(in);
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

ATTR_NAME* ATTR_NAME::clone()
{
    String* value = new String(*this->value);
    ATTR_NAME* clone = new ATTR_NAME(value);
    return clone;
}

Node* ATTR_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void ATTR_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void ATTR_NAME::assert_valid()
{
    assert(value != NULL);
}

Equals::Equals(Expr* left, Expr* right)
{
    this->left = left;
    this->right = right;
}

Equals::Equals()
{
    this->left = 0;
    this->right = 0;
}

void Equals::visit(Visitor* visitor)
{
    visitor->visit_expr(this);
}

void Equals::transform_children(Transform* transform)
{
    transform->children_expr(this);
}

int Equals::classid()
{
    return ID;
}

bool Equals::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Equals* that = dynamic_cast<Equals*>(in);
    if(that == NULL) return false;
    
    if(this->left == NULL)
    {
    	if(that->left != NULL && !that->left->match(this->left))
    		return false;
    }
    else if(!this->left->match(that->left))
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

bool Equals::equals(Node* in)
{
    Equals* that = dynamic_cast<Equals*>(in);
    if(that == NULL) return false;
    
    if(this->left == NULL || that->left == NULL)
    {
    	if(this->left != NULL || that->left != NULL)
    		return false;
    }
    else if(!this->left->equals(that->left))
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

Equals* Equals::clone()
{
    Expr* left = this->left ? this->left->clone() : NULL;
    Expr* right = this->right ? this->right->clone() : NULL;
    Equals* clone = new Equals(left, right);
    return clone;
}

Node* Equals::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->left != NULL)
    {
    	Node* left_res = this->left->find(in);
    	if (left_res) return left_res;
    }
    
    if (this->right != NULL)
    {
    	Node* right_res = this->right->find(in);
    	if (right_res) return right_res;
    }
    
    return NULL;
}

void Equals::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->left != NULL)
    	this->left->find_all(in, out);
    
    if (this->right != NULL)
    	this->right->find_all(in, out);
    
}

void Equals::assert_valid()
{
    assert(left != NULL);
    left->assert_valid();
    assert(right != NULL);
    right->assert_valid();
}

Macro_call::Macro_call(PATTERN_NAME* pattern_name, Actual_parameter_list* actual_parameters)
{
    this->pattern_name = pattern_name;
    this->actual_parameters = actual_parameters;
}

Macro_call::Macro_call()
{
    this->pattern_name = 0;
    this->actual_parameters = 0;
}

void Macro_call::visit(Visitor* visitor)
{
    visitor->visit_body_part(this);
}

void Macro_call::transform_children(Transform* transform)
{
    transform->children_body_part(this);
}

int Macro_call::classid()
{
    return ID;
}

bool Macro_call::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Macro_call* that = dynamic_cast<Macro_call*>(in);
    if(that == NULL) return false;
    
    if(this->pattern_name == NULL)
    {
    	if(that->pattern_name != NULL && !that->pattern_name->match(this->pattern_name))
    		return false;
    }
    else if(!this->pattern_name->match(that->pattern_name))
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

bool Macro_call::equals(Node* in)
{
    Macro_call* that = dynamic_cast<Macro_call*>(in);
    if(that == NULL) return false;
    
    if(this->pattern_name == NULL || that->pattern_name == NULL)
    {
    	if(this->pattern_name != NULL || that->pattern_name != NULL)
    		return false;
    }
    else if(!this->pattern_name->equals(that->pattern_name))
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

Macro_call* Macro_call::clone()
{
    PATTERN_NAME* pattern_name = this->pattern_name ? this->pattern_name->clone() : NULL;
    Actual_parameter_list* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	Actual_parameter_list::const_iterator i;
    	actual_parameters = new Actual_parameter_list;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    Macro_call* clone = new Macro_call(pattern_name, actual_parameters);
    return clone;
}

Node* Macro_call::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->pattern_name != NULL)
    {
    	Node* pattern_name_res = this->pattern_name->find(in);
    	if (pattern_name_res) return pattern_name_res;
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

void Macro_call::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->pattern_name != NULL)
    	this->pattern_name->find_all(in, out);
    
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

void Macro_call::assert_valid()
{
    assert(pattern_name != NULL);
    pattern_name->assert_valid();
    assert(actual_parameters != NULL);
    {
    	Actual_parameter_list::const_iterator i;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
}

Interpolation::Interpolation()
{
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
    visitor->visit_actual_parameter(this);
}

void STRING::transform_children(Transform* transform)
{
    transform->children_actual_parameter(this);
}

String* STRING::get_value_as_string()
{
    return value;
}

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
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool STRING::equals(Node* in)
{
    STRING* that = dynamic_cast<STRING*>(in);
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

STRING* STRING::clone()
{
    String* value = new String(*this->value);
    STRING* clone = new STRING(value);
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
    assert(value != NULL);
}

C_CODE::C_CODE(String* value)
{
    this->value = value;
}

C_CODE::C_CODE()
{
    this->value = 0;
}

void C_CODE::visit(Visitor* visitor)
{
    visitor->visit_body_part(this);
}

void C_CODE::transform_children(Transform* transform)
{
    transform->children_body_part(this);
}

String* C_CODE::get_value_as_string()
{
    return value;
}

int C_CODE::classid()
{
    return ID;
}

bool C_CODE::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    C_CODE* that = dynamic_cast<C_CODE*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool C_CODE::equals(Node* in)
{
    C_CODE* that = dynamic_cast<C_CODE*>(in);
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

C_CODE* C_CODE::clone()
{
    String* value = new String(*this->value);
    C_CODE* clone = new C_CODE(value);
    return clone;
}

Node* C_CODE::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void C_CODE::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void C_CODE::assert_valid()
{
    assert(value != NULL);
}

Lookup::Lookup(PARAM_NAME* param_name, ATTR_NAME* attr_name)
{
    this->param_name = param_name;
    this->attr_name = attr_name;
}

Lookup::Lookup()
{
    this->param_name = 0;
    this->attr_name = 0;
}

void Lookup::visit(Visitor* visitor)
{
    visitor->visit_body_part(this);
}

void Lookup::transform_children(Transform* transform)
{
    transform->children_body_part(this);
}

int Lookup::classid()
{
    return ID;
}

bool Lookup::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Lookup* that = dynamic_cast<Lookup*>(in);
    if(that == NULL) return false;
    
    if(this->param_name == NULL)
    {
    	if(that->param_name != NULL && !that->param_name->match(this->param_name))
    		return false;
    }
    else if(!this->param_name->match(that->param_name))
    	return false;
    
    if(this->attr_name == NULL)
    {
    	if(that->attr_name != NULL && !that->attr_name->match(this->attr_name))
    		return false;
    }
    else if(!this->attr_name->match(that->attr_name))
    	return false;
    
    return true;
}

bool Lookup::equals(Node* in)
{
    Lookup* that = dynamic_cast<Lookup*>(in);
    if(that == NULL) return false;
    
    if(this->param_name == NULL || that->param_name == NULL)
    {
    	if(this->param_name != NULL || that->param_name != NULL)
    		return false;
    }
    else if(!this->param_name->equals(that->param_name))
    	return false;
    
    if(this->attr_name == NULL || that->attr_name == NULL)
    {
    	if(this->attr_name != NULL || that->attr_name != NULL)
    		return false;
    }
    else if(!this->attr_name->equals(that->attr_name))
    	return false;
    
    return true;
}

Lookup* Lookup::clone()
{
    PARAM_NAME* param_name = this->param_name ? this->param_name->clone() : NULL;
    ATTR_NAME* attr_name = this->attr_name ? this->attr_name->clone() : NULL;
    Lookup* clone = new Lookup(param_name, attr_name);
    return clone;
}

Node* Lookup::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->param_name != NULL)
    {
    	Node* param_name_res = this->param_name->find(in);
    	if (param_name_res) return param_name_res;
    }
    
    if (this->attr_name != NULL)
    {
    	Node* attr_name_res = this->attr_name->find(in);
    	if (attr_name_res) return attr_name_res;
    }
    
    return NULL;
}

void Lookup::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->param_name != NULL)
    	this->param_name->find_all(in, out);
    
    if (this->attr_name != NULL)
    	this->attr_name->find_all(in, out);
    
}

void Lookup::assert_valid()
{
    assert(param_name != NULL);
    param_name->assert_valid();
    assert(attr_name != NULL);
    attr_name->assert_valid();
}

PARAM_NAME::PARAM_NAME(String* value)
{
    this->value = value;
}

PARAM_NAME::PARAM_NAME()
{
    this->value = 0;
}

void PARAM_NAME::visit(Visitor* visitor)
{
    visitor->visit_param_name(this);
}

void PARAM_NAME::transform_children(Transform* transform)
{
    transform->children_param_name(this);
}

String* PARAM_NAME::get_value_as_string()
{
    return value;
}

int PARAM_NAME::classid()
{
    return ID;
}

bool PARAM_NAME::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    PARAM_NAME* that = dynamic_cast<PARAM_NAME*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool PARAM_NAME::equals(Node* in)
{
    PARAM_NAME* that = dynamic_cast<PARAM_NAME*>(in);
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

PARAM_NAME* PARAM_NAME::clone()
{
    String* value = new String(*this->value);
    PARAM_NAME* clone = new PARAM_NAME(value);
    return clone;
}

Node* PARAM_NAME::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void PARAM_NAME::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void PARAM_NAME::assert_valid()
{
    assert(value != NULL);
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

