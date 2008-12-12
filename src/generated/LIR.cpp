#include "LIR.h"
#include "LIR_transform.h"
#include "LIR_visitor.h"

namespace LIR{
Node::Node()
{
}

C_file::C_file(CODE_list* codes)
{
    this->codes = codes;
}

C_file::C_file()
{
    this->codes = 0;
}

void C_file::visit(Visitor* visitor)
{
    visitor->visit_c_file(this);
}

void C_file::transform_children(Transform* transform)
{
    transform->children_c_file(this);
}

int C_file::classid()
{
    return ID;
}

bool C_file::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    C_file* that = dynamic_cast<C_file*>(in);
    if(that == NULL) return false;
    
    if(this->codes != NULL && that->codes != NULL)
    {
    	CODE_list::const_iterator i, j;
    	for(
    		i = this->codes->begin(), j = that->codes->begin();
    		i != this->codes->end() && j != that->codes->end();
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
    	if(i != this->codes->end() || j != that->codes->end())
    		return false;
    }
    
    return true;
}

bool C_file::equals(Node* in)
{
    C_file* that = dynamic_cast<C_file*>(in);
    if(that == NULL) return false;
    
    if(this->codes == NULL || that->codes == NULL)
    {
    	if(this->codes != NULL || that->codes != NULL)
    		return false;
    }
    else
    {
    	CODE_list::const_iterator i, j;
    	for(
    		i = this->codes->begin(), j = that->codes->begin();
    		i != this->codes->end() && j != that->codes->end();
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
    	if(i != this->codes->end() || j != that->codes->end())
    		return false;
    }
    
    return true;
}

C_file* C_file::clone()
{
    CODE_list* codes = NULL;
    if(this->codes != NULL)
    {
    	CODE_list::const_iterator i;
    	codes = new CODE_list;
    	for(i = this->codes->begin(); i != this->codes->end(); i++)
    		codes->push_back(*i ? (*i)->clone() : NULL);
    }
    C_file* clone = new C_file(codes);
    return clone;
}

Node* C_file::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->codes != NULL)
    {
    	CODE_list::const_iterator i;
    	for(
    		i = this->codes->begin();
    		i != this->codes->end();
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

void C_file::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if(this->codes != NULL)
    {
    	CODE_list::const_iterator i;
    	for(
    		i = this->codes->begin();
    		i != this->codes->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
}

void C_file::assert_valid()
{
    assert(codes != NULL);
    {
    	CODE_list::const_iterator i;
    	for(i = this->codes->begin(); i != this->codes->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
}

CODE::CODE(String* value)
{
    this->value = value;
}

CODE::CODE()
{
    this->value = 0;
}

void CODE::visit(Visitor* visitor)
{
    visitor->visit_code(this);
}

void CODE::transform_children(Transform* transform)
{
    transform->children_code(this);
}

int CODE::classid()
{
    return ID;
}

bool CODE::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    CODE* that = dynamic_cast<CODE*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    else
    	return true;
}

bool CODE::match_value(CODE* that)
{
    return true;
}

bool CODE::equals(Node* in)
{
    CODE* that = dynamic_cast<CODE*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    return true;
}

bool CODE::equals_value(CODE* that)
{
    return (*this->value == *that->value);
}

CODE* CODE::clone()
{
    value = clone_value();
    CODE* clone = new CODE(value);
    return clone;
}

String* CODE::clone_value()
{
    return value;
}

Node* CODE::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void CODE::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void CODE::assert_valid()
{
    assert_value_valid();
}

void CODE::assert_value_valid()
{
    // Assume value is valid
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

