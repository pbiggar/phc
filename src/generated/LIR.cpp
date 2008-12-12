#include "LIR.h"
#include "LIR_transform.h"
#include "LIR_visitor.h"

namespace LIR{
Node::Node()
{
}

C_file::C_file(Piece_list* pieces)
{
    this->pieces = pieces;
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
    
    if(this->pieces != NULL && that->pieces != NULL)
    {
    	Piece_list::const_iterator i, j;
    	for(
    		i = this->pieces->begin(), j = that->pieces->begin();
    		i != this->pieces->end() && j != that->pieces->end();
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
    	if(i != this->pieces->end() || j != that->pieces->end())
    		return false;
    }
    
    return true;
}

bool C_file::equals(Node* in)
{
    C_file* that = dynamic_cast<C_file*>(in);
    if(that == NULL) return false;
    
    if(this->pieces == NULL || that->pieces == NULL)
    {
    	if(this->pieces != NULL || that->pieces != NULL)
    		return false;
    }
    else
    {
    	Piece_list::const_iterator i, j;
    	for(
    		i = this->pieces->begin(), j = that->pieces->begin();
    		i != this->pieces->end() && j != that->pieces->end();
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
    	if(i != this->pieces->end() || j != that->pieces->end())
    		return false;
    }
    
    return true;
}

C_file* C_file::clone()
{
    Piece_list* pieces = NULL;
    if(this->pieces != NULL)
    {
    	Piece_list::const_iterator i;
    	pieces = new Piece_list;
    	for(i = this->pieces->begin(); i != this->pieces->end(); i++)
    		pieces->push_back(*i ? (*i)->clone() : NULL);
    }
    C_file* clone = new C_file(pieces);
    return clone;
}

Node* C_file::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if(this->pieces != NULL)
    {
    	Piece_list::const_iterator i;
    	for(
    		i = this->pieces->begin();
    		i != this->pieces->end();
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
    
    if(this->pieces != NULL)
    {
    	Piece_list::const_iterator i;
    	for(
    		i = this->pieces->begin();
    		i != this->pieces->end();
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
    assert(pieces != NULL);
    {
    	Piece_list::const_iterator i;
    	for(i = this->pieces->begin(); i != this->pieces->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
}

C_file::C_file()
{
    {
		pieces = new Piece_list;
	}
}

Piece::Piece()
{
}

Statement::Statement()
{
}

Cond::Cond(Is_ref* is_ref)
{
    this->is_ref = is_ref;
}

Cond::Cond()
{
    this->is_ref = 0;
}

void Cond::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void Cond::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int Cond::classid()
{
    return ID;
}

bool Cond::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Cond* that = dynamic_cast<Cond*>(in);
    if(that == NULL) return false;
    
    if(this->is_ref == NULL)
    {
    	if(that->is_ref != NULL && !that->is_ref->match(this->is_ref))
    		return false;
    }
    else if(!this->is_ref->match(that->is_ref))
    	return false;
    
    return true;
}

bool Cond::equals(Node* in)
{
    Cond* that = dynamic_cast<Cond*>(in);
    if(that == NULL) return false;
    
    if(this->is_ref == NULL || that->is_ref == NULL)
    {
    	if(this->is_ref != NULL || that->is_ref != NULL)
    		return false;
    }
    else if(!this->is_ref->equals(that->is_ref))
    	return false;
    
    return true;
}

Cond* Cond::clone()
{
    Is_ref* is_ref = this->is_ref ? this->is_ref->clone() : NULL;
    Cond* clone = new Cond(is_ref);
    return clone;
}

Node* Cond::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->is_ref != NULL)
    {
    	Node* is_ref_res = this->is_ref->find(in);
    	if (is_ref_res) return is_ref_res;
    }
    
    return NULL;
}

void Cond::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->is_ref != NULL)
    	this->is_ref->find_all(in, out);
    
}

void Cond::assert_valid()
{
    assert(is_ref != NULL);
    is_ref->assert_valid();
}

Is_ref::Is_ref(Zvp* zvp)
{
    this->zvp = zvp;
}

Is_ref::Is_ref()
{
    this->zvp = 0;
}

void Is_ref::visit(Visitor* visitor)
{
    visitor->visit_is_ref(this);
}

void Is_ref::transform_children(Transform* transform)
{
    transform->children_is_ref(this);
}

int Is_ref::classid()
{
    return ID;
}

bool Is_ref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Is_ref* that = dynamic_cast<Is_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Is_ref::equals(Node* in)
{
    Is_ref* that = dynamic_cast<Is_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL || that->zvp == NULL)
    {
    	if(this->zvp != NULL || that->zvp != NULL)
    		return false;
    }
    else if(!this->zvp->equals(that->zvp))
    	return false;
    
    return true;
}

Is_ref* Is_ref::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    Is_ref* clone = new Is_ref(zvp);
    return clone;
}

Node* Is_ref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvp != NULL)
    {
    	Node* zvp_res = this->zvp->find(in);
    	if (zvp_res) return zvp_res;
    }
    
    return NULL;
}

void Is_ref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Is_ref::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

Zvp::Zvp()
{
}

Zvpp::Zvpp()
{
}

Block::Block(Statement_list* statements)
{
    this->statements = statements;
}

Block::Block()
{
    this->statements = 0;
}

void Block::visit(Visitor* visitor)
{
    visitor->visit_piece(this);
}

void Block::transform_children(Transform* transform)
{
    transform->children_piece(this);
}

int Block::classid()
{
    return ID;
}

bool Block::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Block* that = dynamic_cast<Block*>(in);
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

bool Block::equals(Node* in)
{
    Block* that = dynamic_cast<Block*>(in);
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

Block* Block::clone()
{
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Block* clone = new Block(statements);
    return clone;
}

Node* Block::find(Node* in)
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

void Block::find_all(Node* in, Node_list* out)
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

void Block::assert_valid()
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
}

Action::Action()
{
}

If::If(Cond* cond, Statement_list* if_true, Statement_list* if_false)
{
    this->cond = cond;
    this->if_true = if_true;
    this->if_false = if_false;
}

If::If()
{
    this->cond = 0;
    this->if_true = 0;
    this->if_false = 0;
}

void If::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void If::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

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
    
    if(this->cond == NULL)
    {
    	if(that->cond != NULL && !that->cond->match(this->cond))
    		return false;
    }
    else if(!this->cond->match(that->cond))
    	return false;
    
    if(this->if_true != NULL && that->if_true != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->if_true->begin(), j = that->if_true->begin();
    		i != this->if_true->end() && j != that->if_true->end();
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
    	if(i != this->if_true->end() || j != that->if_true->end())
    		return false;
    }
    
    if(this->if_false != NULL && that->if_false != NULL)
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->if_false->begin(), j = that->if_false->begin();
    		i != this->if_false->end() && j != that->if_false->end();
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
    	if(i != this->if_false->end() || j != that->if_false->end())
    		return false;
    }
    
    return true;
}

bool If::equals(Node* in)
{
    If* that = dynamic_cast<If*>(in);
    if(that == NULL) return false;
    
    if(this->cond == NULL || that->cond == NULL)
    {
    	if(this->cond != NULL || that->cond != NULL)
    		return false;
    }
    else if(!this->cond->equals(that->cond))
    	return false;
    
    if(this->if_true == NULL || that->if_true == NULL)
    {
    	if(this->if_true != NULL || that->if_true != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->if_true->begin(), j = that->if_true->begin();
    		i != this->if_true->end() && j != that->if_true->end();
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
    	if(i != this->if_true->end() || j != that->if_true->end())
    		return false;
    }
    
    if(this->if_false == NULL || that->if_false == NULL)
    {
    	if(this->if_false != NULL || that->if_false != NULL)
    		return false;
    }
    else
    {
    	Statement_list::const_iterator i, j;
    	for(
    		i = this->if_false->begin(), j = that->if_false->begin();
    		i != this->if_false->end() && j != that->if_false->end();
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
    	if(i != this->if_false->end() || j != that->if_false->end())
    		return false;
    }
    
    return true;
}

If* If::clone()
{
    Cond* cond = this->cond ? this->cond->clone() : NULL;
    Statement_list* if_true = NULL;
    if(this->if_true != NULL)
    {
    	Statement_list::const_iterator i;
    	if_true = new Statement_list;
    	for(i = this->if_true->begin(); i != this->if_true->end(); i++)
    		if_true->push_back(*i ? (*i)->clone() : NULL);
    }
    Statement_list* if_false = NULL;
    if(this->if_false != NULL)
    {
    	Statement_list::const_iterator i;
    	if_false = new Statement_list;
    	for(i = this->if_false->begin(); i != this->if_false->end(); i++)
    		if_false->push_back(*i ? (*i)->clone() : NULL);
    }
    If* clone = new If(cond, if_true, if_false);
    return clone;
}

Node* If::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->cond != NULL)
    {
    	Node* cond_res = this->cond->find(in);
    	if (cond_res) return cond_res;
    }
    
    if(this->if_true != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->if_true->begin();
    		i != this->if_true->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			Node* res = (*i)->find (in);
    			if (res) return res;
    		}
    	}
    }
    
    if(this->if_false != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->if_false->begin();
    		i != this->if_false->end();
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
    
    if (this->cond != NULL)
    	this->cond->find_all(in, out);
    
    if(this->if_true != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->if_true->begin();
    		i != this->if_true->end();
    		i++)
    	{
    		if(*i != NULL)
    		{
    			(*i)->find_all (in, out);
    		}
    	}
    }
    
    if(this->if_false != NULL)
    {
    	Statement_list::const_iterator i;
    	for(
    		i = this->if_false->begin();
    		i != this->if_false->end();
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
    assert(cond != NULL);
    cond->assert_valid();
    assert(if_true != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->if_true->begin(); i != this->if_true->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(if_false != NULL);
    {
    	Statement_list::const_iterator i;
    	for(i = this->if_false->begin(); i != this->if_false->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
}

Uninitialized::Uninitialized()
{
}

void Uninitialized::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void Uninitialized::transform_children(Transform* transform)
{
    transform->children_zvp(this);
}

int Uninitialized::classid()
{
    return ID;
}

bool Uninitialized::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Uninitialized* that = dynamic_cast<Uninitialized*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool Uninitialized::equals(Node* in)
{
    Uninitialized* that = dynamic_cast<Uninitialized*>(in);
    if(that == NULL) return false;
    
    return true;
}

Uninitialized* Uninitialized::clone()
{
    Uninitialized* clone = new Uninitialized();
    return clone;
}

Node* Uninitialized::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Uninitialized::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Uninitialized::assert_valid()
{
}

Null::Null()
{
}

void Null::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void Null::transform_children(Transform* transform)
{
    transform->children_zvp(this);
}

int Null::classid()
{
    return ID;
}

bool Null::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Null* that = dynamic_cast<Null*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool Null::equals(Node* in)
{
    Null* that = dynamic_cast<Null*>(in);
    if(that == NULL) return false;
    
    return true;
}

Null* Null::clone()
{
    Null* clone = new Null();
    return clone;
}

Node* Null::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Null::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Null::assert_valid()
{
}

Deref::Deref(Zvpp* zvpp)
{
    this->zvpp = zvpp;
}

Deref::Deref()
{
    this->zvpp = 0;
}

void Deref::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void Deref::transform_children(Transform* transform)
{
    transform->children_zvp(this);
}

int Deref::classid()
{
    return ID;
}

bool Deref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Deref* that = dynamic_cast<Deref*>(in);
    if(that == NULL) return false;
    
    if(this->zvpp == NULL)
    {
    	if(that->zvpp != NULL && !that->zvpp->match(this->zvpp))
    		return false;
    }
    else if(!this->zvpp->match(that->zvpp))
    	return false;
    
    return true;
}

bool Deref::equals(Node* in)
{
    Deref* that = dynamic_cast<Deref*>(in);
    if(that == NULL) return false;
    
    if(this->zvpp == NULL || that->zvpp == NULL)
    {
    	if(this->zvpp != NULL || that->zvpp != NULL)
    		return false;
    }
    else if(!this->zvpp->equals(that->zvpp))
    	return false;
    
    return true;
}

Deref* Deref::clone()
{
    Zvpp* zvpp = this->zvpp ? this->zvpp->clone() : NULL;
    Deref* clone = new Deref(zvpp);
    return clone;
}

Node* Deref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvpp != NULL)
    {
    	Node* zvpp_res = this->zvpp->find(in);
    	if (zvpp_res) return zvpp_res;
    }
    
    return NULL;
}

void Deref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvpp != NULL)
    	this->zvpp->find_all(in, out);
    
}

void Deref::assert_valid()
{
    assert(zvpp != NULL);
    zvpp->assert_valid();
}

Ref::Ref(Zvp* zvp)
{
    this->zvp = zvp;
}

Ref::Ref()
{
    this->zvp = 0;
}

void Ref::visit(Visitor* visitor)
{
    visitor->visit_zvpp(this);
}

void Ref::transform_children(Transform* transform)
{
    transform->children_zvpp(this);
}

int Ref::classid()
{
    return ID;
}

bool Ref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Ref* that = dynamic_cast<Ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Ref::equals(Node* in)
{
    Ref* that = dynamic_cast<Ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL || that->zvp == NULL)
    {
    	if(this->zvp != NULL || that->zvp != NULL)
    		return false;
    }
    else if(!this->zvp->equals(that->zvp))
    	return false;
    
    return true;
}

Ref* Ref::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    Ref* clone = new Ref(zvp);
    return clone;
}

Node* Ref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvp != NULL)
    {
    	Node* zvp_res = this->zvp->find(in);
    	if (zvp_res) return zvp_res;
    }
    
    return NULL;
}

void Ref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Ref::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

UNINTERPRETED::UNINTERPRETED(String* value)
{
    this->value = value;
}

UNINTERPRETED::UNINTERPRETED()
{
    this->value = 0;
}

void UNINTERPRETED::visit(Visitor* visitor)
{
    visitor->visit_piece(this);
}

void UNINTERPRETED::transform_children(Transform* transform)
{
    transform->children_piece(this);
}

String* UNINTERPRETED::get_value_as_string()
{
    return value;
}

int UNINTERPRETED::classid()
{
    return ID;
}

bool UNINTERPRETED::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    UNINTERPRETED* that = dynamic_cast<UNINTERPRETED*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool UNINTERPRETED::equals(Node* in)
{
    UNINTERPRETED* that = dynamic_cast<UNINTERPRETED*>(in);
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

UNINTERPRETED* UNINTERPRETED::clone()
{
    String* value = new String(*this->value);
    UNINTERPRETED* clone = new UNINTERPRETED(value);
    return clone;
}

Node* UNINTERPRETED::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void UNINTERPRETED::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void UNINTERPRETED::assert_valid()
{
    assert(value != NULL);
}

INTRINSIC::INTRINSIC(String* value)
{
    this->value = value;
}

INTRINSIC::INTRINSIC()
{
    this->value = 0;
}

void INTRINSIC::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void INTRINSIC::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

String* INTRINSIC::get_value_as_string()
{
    return value;
}

int INTRINSIC::classid()
{
    return ID;
}

bool INTRINSIC::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    INTRINSIC* that = dynamic_cast<INTRINSIC*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool INTRINSIC::equals(Node* in)
{
    INTRINSIC* that = dynamic_cast<INTRINSIC*>(in);
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

INTRINSIC* INTRINSIC::clone()
{
    String* value = new String(*this->value);
    INTRINSIC* clone = new INTRINSIC(value);
    return clone;
}

Node* INTRINSIC::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void INTRINSIC::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void INTRINSIC::assert_valid()
{
    assert(value != NULL);
}

API_CALL::API_CALL(String* value)
{
    this->value = value;
}

API_CALL::API_CALL()
{
    this->value = 0;
}

void API_CALL::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void API_CALL::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

String* API_CALL::get_value_as_string()
{
    return value;
}

int API_CALL::classid()
{
    return ID;
}

bool API_CALL::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    API_CALL* that = dynamic_cast<API_CALL*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool API_CALL::equals(Node* in)
{
    API_CALL* that = dynamic_cast<API_CALL*>(in);
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

API_CALL* API_CALL::clone()
{
    String* value = new String(*this->value);
    API_CALL* clone = new API_CALL(value);
    return clone;
}

Node* API_CALL::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void API_CALL::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void API_CALL::assert_valid()
{
    assert(value != NULL);
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
    visitor->visit_statement(this);
}

void CODE::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

String* CODE::get_value_as_string()
{
    return value;
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
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool CODE::equals(Node* in)
{
    CODE* that = dynamic_cast<CODE*>(in);
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

CODE* CODE::clone()
{
    String* value = new String(*this->value);
    CODE* clone = new CODE(value);
    return clone;
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
    assert(value != NULL);
}

ZVP::ZVP(String* value)
{
    this->value = value;
}

ZVP::ZVP()
{
    this->value = 0;
}

void ZVP::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void ZVP::transform_children(Transform* transform)
{
    transform->children_zvp(this);
}

String* ZVP::get_value_as_string()
{
    return value;
}

int ZVP::classid()
{
    return ID;
}

bool ZVP::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    ZVP* that = dynamic_cast<ZVP*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool ZVP::equals(Node* in)
{
    ZVP* that = dynamic_cast<ZVP*>(in);
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

ZVP* ZVP::clone()
{
    String* value = new String(*this->value);
    ZVP* clone = new ZVP(value);
    return clone;
}

Node* ZVP::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void ZVP::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void ZVP::assert_valid()
{
    assert(value != NULL);
}

LITERAL::LITERAL(String* value)
{
    this->value = value;
}

LITERAL::LITERAL()
{
    this->value = 0;
}

void LITERAL::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void LITERAL::transform_children(Transform* transform)
{
    transform->children_zvp(this);
}

String* LITERAL::get_value_as_string()
{
    return value;
}

int LITERAL::classid()
{
    return ID;
}

bool LITERAL::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    LITERAL* that = dynamic_cast<LITERAL*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool LITERAL::equals(Node* in)
{
    LITERAL* that = dynamic_cast<LITERAL*>(in);
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

LITERAL* LITERAL::clone()
{
    String* value = new String(*this->value);
    LITERAL* clone = new LITERAL(value);
    return clone;
}

Node* LITERAL::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void LITERAL::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void LITERAL::assert_valid()
{
    assert(value != NULL);
}

ZVPP::ZVPP(String* value)
{
    this->value = value;
}

ZVPP::ZVPP()
{
    this->value = 0;
}

void ZVPP::visit(Visitor* visitor)
{
    visitor->visit_zvpp(this);
}

void ZVPP::transform_children(Transform* transform)
{
    transform->children_zvpp(this);
}

String* ZVPP::get_value_as_string()
{
    return value;
}

int ZVPP::classid()
{
    return ID;
}

bool ZVPP::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    ZVPP* that = dynamic_cast<ZVPP*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool ZVPP::equals(Node* in)
{
    ZVPP* that = dynamic_cast<ZVPP*>(in);
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

ZVPP* ZVPP::clone()
{
    String* value = new String(*this->value);
    ZVPP* clone = new ZVPP(value);
    return clone;
}

Node* ZVPP::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void ZVPP::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void ZVPP::assert_valid()
{
    assert(value != NULL);
}

Assign_zvp::Assign_zvp(Zvp* lhs, Zvp* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

Assign_zvp::Assign_zvp()
{
    this->lhs = 0;
    this->rhs = 0;
}

void Assign_zvp::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_zvp::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Assign_zvp::classid()
{
    return ID;
}

bool Assign_zvp::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_zvp* that = dynamic_cast<Assign_zvp*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_zvp::equals(Node* in)
{
    Assign_zvp* that = dynamic_cast<Assign_zvp*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
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

Assign_zvp* Assign_zvp::clone()
{
    Zvp* lhs = this->lhs ? this->lhs->clone() : NULL;
    Zvp* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_zvp* clone = new Assign_zvp(lhs, rhs);
    return clone;
}

Node* Assign_zvp::find(Node* in)
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

void Assign_zvp::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_zvp::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
}

Assign_zvpp::Assign_zvpp(Zvpp* lhs, Zvpp* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

Assign_zvpp::Assign_zvpp()
{
    this->lhs = 0;
    this->rhs = 0;
}

void Assign_zvpp::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Assign_zvpp::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Assign_zvpp::classid()
{
    return ID;
}

bool Assign_zvpp::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Assign_zvpp* that = dynamic_cast<Assign_zvpp*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Assign_zvpp::equals(Node* in)
{
    Assign_zvpp* that = dynamic_cast<Assign_zvpp*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
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

Assign_zvpp* Assign_zvpp::clone()
{
    Zvpp* lhs = this->lhs ? this->lhs->clone() : NULL;
    Zvpp* rhs = this->rhs ? this->rhs->clone() : NULL;
    Assign_zvpp* clone = new Assign_zvpp(lhs, rhs);
    return clone;
}

Node* Assign_zvpp::find(Node* in)
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

void Assign_zvpp::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Assign_zvpp::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
}

Inc_ref::Inc_ref(Zvp* zvp)
{
    this->zvp = zvp;
}

Inc_ref::Inc_ref()
{
    this->zvp = 0;
}

void Inc_ref::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Inc_ref::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Inc_ref::classid()
{
    return ID;
}

bool Inc_ref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Inc_ref* that = dynamic_cast<Inc_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Inc_ref::equals(Node* in)
{
    Inc_ref* that = dynamic_cast<Inc_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL || that->zvp == NULL)
    {
    	if(this->zvp != NULL || that->zvp != NULL)
    		return false;
    }
    else if(!this->zvp->equals(that->zvp))
    	return false;
    
    return true;
}

Inc_ref* Inc_ref::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    Inc_ref* clone = new Inc_ref(zvp);
    return clone;
}

Node* Inc_ref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvp != NULL)
    {
    	Node* zvp_res = this->zvp->find(in);
    	if (zvp_res) return zvp_res;
    }
    
    return NULL;
}

void Inc_ref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Inc_ref::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

Allocate::Allocate(Zvp* zvp)
{
    this->zvp = zvp;
}

Allocate::Allocate()
{
    this->zvp = 0;
}

void Allocate::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Allocate::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Allocate::classid()
{
    return ID;
}

bool Allocate::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Allocate* that = dynamic_cast<Allocate*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Allocate::equals(Node* in)
{
    Allocate* that = dynamic_cast<Allocate*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL || that->zvp == NULL)
    {
    	if(this->zvp != NULL || that->zvp != NULL)
    		return false;
    }
    else if(!this->zvp->equals(that->zvp))
    	return false;
    
    return true;
}

Allocate* Allocate::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    Allocate* clone = new Allocate(zvp);
    return clone;
}

Node* Allocate::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvp != NULL)
    {
    	Node* zvp_res = this->zvp->find(in);
    	if (zvp_res) return zvp_res;
    }
    
    return NULL;
}

void Allocate::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Allocate::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

Clone::Clone(Zvp* lhs, Zvp* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

Clone::Clone()
{
    this->lhs = 0;
    this->rhs = 0;
}

void Clone::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Clone::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Clone::classid()
{
    return ID;
}

bool Clone::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Clone* that = dynamic_cast<Clone*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL)
    {
    	if(that->lhs != NULL && !that->lhs->match(this->lhs))
    		return false;
    }
    else if(!this->lhs->match(that->lhs))
    	return false;
    
    if(this->rhs == NULL)
    {
    	if(that->rhs != NULL && !that->rhs->match(this->rhs))
    		return false;
    }
    else if(!this->rhs->match(that->rhs))
    	return false;
    
    return true;
}

bool Clone::equals(Node* in)
{
    Clone* that = dynamic_cast<Clone*>(in);
    if(that == NULL) return false;
    
    if(this->lhs == NULL || that->lhs == NULL)
    {
    	if(this->lhs != NULL || that->lhs != NULL)
    		return false;
    }
    else if(!this->lhs->equals(that->lhs))
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

Clone* Clone::clone()
{
    Zvp* lhs = this->lhs ? this->lhs->clone() : NULL;
    Zvp* rhs = this->rhs ? this->rhs->clone() : NULL;
    Clone* clone = new Clone(lhs, rhs);
    return clone;
}

Node* Clone::find(Node* in)
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

void Clone::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Clone::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
}

Separate::Separate(Zvpp* zvpp)
{
    this->zvpp = zvpp;
}

Separate::Separate()
{
    this->zvpp = 0;
}

void Separate::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Separate::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Separate::classid()
{
    return ID;
}

bool Separate::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Separate* that = dynamic_cast<Separate*>(in);
    if(that == NULL) return false;
    
    if(this->zvpp == NULL)
    {
    	if(that->zvpp != NULL && !that->zvpp->match(this->zvpp))
    		return false;
    }
    else if(!this->zvpp->match(that->zvpp))
    	return false;
    
    return true;
}

bool Separate::equals(Node* in)
{
    Separate* that = dynamic_cast<Separate*>(in);
    if(that == NULL) return false;
    
    if(this->zvpp == NULL || that->zvpp == NULL)
    {
    	if(this->zvpp != NULL || that->zvpp != NULL)
    		return false;
    }
    else if(!this->zvpp->equals(that->zvpp))
    	return false;
    
    return true;
}

Separate* Separate::clone()
{
    Zvpp* zvpp = this->zvpp ? this->zvpp->clone() : NULL;
    Separate* clone = new Separate(zvpp);
    return clone;
}

Node* Separate::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvpp != NULL)
    {
    	Node* zvpp_res = this->zvpp->find(in);
    	if (zvpp_res) return zvpp_res;
    }
    
    return NULL;
}

void Separate::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvpp != NULL)
    	this->zvpp->find_all(in, out);
    
}

void Separate::assert_valid()
{
    assert(zvpp != NULL);
    zvpp->assert_valid();
}

Dec_ref::Dec_ref(Zvp* zvp)
{
    this->zvp = zvp;
}

Dec_ref::Dec_ref()
{
    this->zvp = 0;
}

void Dec_ref::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Dec_ref::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Dec_ref::classid()
{
    return ID;
}

bool Dec_ref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Dec_ref* that = dynamic_cast<Dec_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Dec_ref::equals(Node* in)
{
    Dec_ref* that = dynamic_cast<Dec_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL || that->zvp == NULL)
    {
    	if(this->zvp != NULL || that->zvp != NULL)
    		return false;
    }
    else if(!this->zvp->equals(that->zvp))
    	return false;
    
    return true;
}

Dec_ref* Dec_ref::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    Dec_ref* clone = new Dec_ref(zvp);
    return clone;
}

Node* Dec_ref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvp != NULL)
    {
    	Node* zvp_res = this->zvp->find(in);
    	if (zvp_res) return zvp_res;
    }
    
    return NULL;
}

void Dec_ref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Dec_ref::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

Destruct::Destruct(Zvpp* zvpp)
{
    this->zvpp = zvpp;
}

Destruct::Destruct()
{
    this->zvpp = 0;
}

void Destruct::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Destruct::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Destruct::classid()
{
    return ID;
}

bool Destruct::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Destruct* that = dynamic_cast<Destruct*>(in);
    if(that == NULL) return false;
    
    if(this->zvpp == NULL)
    {
    	if(that->zvpp != NULL && !that->zvpp->match(this->zvpp))
    		return false;
    }
    else if(!this->zvpp->match(that->zvpp))
    	return false;
    
    return true;
}

bool Destruct::equals(Node* in)
{
    Destruct* that = dynamic_cast<Destruct*>(in);
    if(that == NULL) return false;
    
    if(this->zvpp == NULL || that->zvpp == NULL)
    {
    	if(this->zvpp != NULL || that->zvpp != NULL)
    		return false;
    }
    else if(!this->zvpp->equals(that->zvpp))
    	return false;
    
    return true;
}

Destruct* Destruct::clone()
{
    Zvpp* zvpp = this->zvpp ? this->zvpp->clone() : NULL;
    Destruct* clone = new Destruct(zvpp);
    return clone;
}

Node* Destruct::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvpp != NULL)
    {
    	Node* zvpp_res = this->zvpp->find(in);
    	if (zvpp_res) return zvpp_res;
    }
    
    return NULL;
}

void Destruct::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvpp != NULL)
    	this->zvpp->find_all(in, out);
    
}

void Destruct::assert_valid()
{
    assert(zvpp != NULL);
    zvpp->assert_valid();
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

