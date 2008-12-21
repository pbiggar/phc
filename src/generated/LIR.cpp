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

Cond::Cond()
{
}

Zvp::Zvp()
{
}

Zvpp::Zvpp()
{
}

Identifier::Identifier()
{
}

Opt_param::Opt_param()
{
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
    visitor->visit_int(this);
}

void INT::transform_children(Transform* transform)
{
    transform->children_int(this);
}

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

bool INT::match_value(INT* that)
{
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
}

void INT::assert_value_valid()
{
    // Assume value is valid
}

bool INT::is_valid()
{
    {
		return (value == 0 || value == 1);
	}
}

Method::Method(COMMENT* comment, UNINTERPRETED* entry, Piece_list* pieces, UNINTERPRETED* exit)
{
    this->comment = comment;
    this->entry = entry;
    this->pieces = pieces;
    this->exit = exit;
}

Method::Method()
{
    this->comment = 0;
    this->entry = 0;
    this->pieces = 0;
    this->exit = 0;
}

void Method::visit(Visitor* visitor)
{
    visitor->visit_piece(this);
}

void Method::transform_children(Transform* transform)
{
    transform->children_piece(this);
}

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
    
    if(this->comment == NULL)
    {
    	if(that->comment != NULL && !that->comment->match(this->comment))
    		return false;
    }
    else if(!this->comment->match(that->comment))
    	return false;
    
    if(this->entry == NULL)
    {
    	if(that->entry != NULL && !that->entry->match(this->entry))
    		return false;
    }
    else if(!this->entry->match(that->entry))
    	return false;
    
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
    
    if(this->exit == NULL)
    {
    	if(that->exit != NULL && !that->exit->match(this->exit))
    		return false;
    }
    else if(!this->exit->match(that->exit))
    	return false;
    
    return true;
}

bool Method::equals(Node* in)
{
    Method* that = dynamic_cast<Method*>(in);
    if(that == NULL) return false;
    
    if(this->comment == NULL || that->comment == NULL)
    {
    	if(this->comment != NULL || that->comment != NULL)
    		return false;
    }
    else if(!this->comment->equals(that->comment))
    	return false;
    
    if(this->entry == NULL || that->entry == NULL)
    {
    	if(this->entry != NULL || that->entry != NULL)
    		return false;
    }
    else if(!this->entry->equals(that->entry))
    	return false;
    
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
    
    if(this->exit == NULL || that->exit == NULL)
    {
    	if(this->exit != NULL || that->exit != NULL)
    		return false;
    }
    else if(!this->exit->equals(that->exit))
    	return false;
    
    return true;
}

Method* Method::clone()
{
    COMMENT* comment = this->comment ? this->comment->clone() : NULL;
    UNINTERPRETED* entry = this->entry ? this->entry->clone() : NULL;
    Piece_list* pieces = NULL;
    if(this->pieces != NULL)
    {
    	Piece_list::const_iterator i;
    	pieces = new Piece_list;
    	for(i = this->pieces->begin(); i != this->pieces->end(); i++)
    		pieces->push_back(*i ? (*i)->clone() : NULL);
    }
    UNINTERPRETED* exit = this->exit ? this->exit->clone() : NULL;
    Method* clone = new Method(comment, entry, pieces, exit);
    return clone;
}

Node* Method::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->comment != NULL)
    {
    	Node* comment_res = this->comment->find(in);
    	if (comment_res) return comment_res;
    }
    
    if (this->entry != NULL)
    {
    	Node* entry_res = this->entry->find(in);
    	if (entry_res) return entry_res;
    }
    
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
    
    if (this->exit != NULL)
    {
    	Node* exit_res = this->exit->find(in);
    	if (exit_res) return exit_res;
    }
    
    return NULL;
}

void Method::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->comment != NULL)
    	this->comment->find_all(in, out);
    
    if (this->entry != NULL)
    	this->entry->find_all(in, out);
    
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
    
    if (this->exit != NULL)
    	this->exit->find_all(in, out);
    
}

void Method::assert_valid()
{
    assert(comment != NULL);
    comment->assert_valid();
    assert(entry != NULL);
    entry->assert_valid();
    assert(pieces != NULL);
    {
    	Piece_list::const_iterator i;
    	for(i = this->pieces->begin(); i != this->pieces->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(exit != NULL);
    exit->assert_valid();
}

Block::Block(COMMENT* comment, Statement_list* statements)
{
    this->comment = comment;
    this->statements = statements;
}

Block::Block()
{
    this->comment = 0;
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
    
    if(this->comment == NULL)
    {
    	if(that->comment != NULL && !that->comment->match(this->comment))
    		return false;
    }
    else if(!this->comment->match(that->comment))
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

bool Block::equals(Node* in)
{
    Block* that = dynamic_cast<Block*>(in);
    if(that == NULL) return false;
    
    if(this->comment == NULL || that->comment == NULL)
    {
    	if(this->comment != NULL || that->comment != NULL)
    		return false;
    }
    else if(!this->comment->equals(that->comment))
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

Block* Block::clone()
{
    COMMENT* comment = this->comment ? this->comment->clone() : NULL;
    Statement_list* statements = NULL;
    if(this->statements != NULL)
    {
    	Statement_list::const_iterator i;
    	statements = new Statement_list;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    Block* clone = new Block(comment, statements);
    return clone;
}

Node* Block::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->comment != NULL)
    {
    	Node* comment_res = this->comment->find(in);
    	if (comment_res) return comment_res;
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

void Block::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->comment != NULL)
    	this->comment->find_all(in, out);
    
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
    assert(comment != NULL);
    comment->assert_valid();
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

Block::Block(String* comment, Statement_list* statements)
{
    {
		this->comment = new COMMENT (comment);
		this->statements = statements;
	}
}

Action::Action()
{
}

If::If(Cond* cond, Statement_list* iftrue, Statement_list* iffalse)
{
    this->cond = cond;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

If::If()
{
    this->cond = 0;
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
    
    return true;
}

If* If::clone()
{
    Cond* cond = this->cond ? this->cond->clone() : NULL;
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
    If* clone = new If(cond, iftrue, iffalse);
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
    
    if (this->cond != NULL)
    	this->cond->find_all(in, out);
    
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
    assert(cond != NULL);
    cond->assert_valid();
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
    visitor->visit_cond(this);
}

void Is_ref::transform_children(Transform* transform)
{
    transform->children_cond(this);
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

Equals::Equals(Zvp* lhs, Zvp* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

Equals::Equals()
{
    this->lhs = 0;
    this->rhs = 0;
}

void Equals::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void Equals::transform_children(Transform* transform)
{
    transform->children_cond(this);
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

bool Equals::equals(Node* in)
{
    Equals* that = dynamic_cast<Equals*>(in);
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

Equals* Equals::clone()
{
    Zvp* lhs = this->lhs ? this->lhs->clone() : NULL;
    Zvp* rhs = this->rhs ? this->rhs->clone() : NULL;
    Equals* clone = new Equals(lhs, rhs);
    return clone;
}

Node* Equals::find(Node* in)
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

void Equals::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Equals::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
}

Equals_p::Equals_p(Zvpp* lhs, Zvpp* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

Equals_p::Equals_p()
{
    this->lhs = 0;
    this->rhs = 0;
}

void Equals_p::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void Equals_p::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int Equals_p::classid()
{
    return ID;
}

bool Equals_p::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Equals_p* that = dynamic_cast<Equals_p*>(in);
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

bool Equals_p::equals(Node* in)
{
    Equals_p* that = dynamic_cast<Equals_p*>(in);
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

Equals_p* Equals_p::clone()
{
    Zvpp* lhs = this->lhs ? this->lhs->clone() : NULL;
    Zvpp* rhs = this->rhs ? this->rhs->clone() : NULL;
    Equals_p* clone = new Equals_p(lhs, rhs);
    return clone;
}

Node* Equals_p::find(Node* in)
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

void Equals_p::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Equals_p::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
}

Not::Not(Cond* cond)
{
    this->cond = cond;
}

Not::Not()
{
    this->cond = 0;
}

void Not::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void Not::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int Not::classid()
{
    return ID;
}

bool Not::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Not* that = dynamic_cast<Not*>(in);
    if(that == NULL) return false;
    
    if(this->cond == NULL)
    {
    	if(that->cond != NULL && !that->cond->match(this->cond))
    		return false;
    }
    else if(!this->cond->match(that->cond))
    	return false;
    
    return true;
}

bool Not::equals(Node* in)
{
    Not* that = dynamic_cast<Not*>(in);
    if(that == NULL) return false;
    
    if(this->cond == NULL || that->cond == NULL)
    {
    	if(this->cond != NULL || that->cond != NULL)
    		return false;
    }
    else if(!this->cond->equals(that->cond))
    	return false;
    
    return true;
}

Not* Not::clone()
{
    Cond* cond = this->cond ? this->cond->clone() : NULL;
    Not* clone = new Not(cond);
    return clone;
}

Node* Not::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->cond != NULL)
    {
    	Node* cond_res = this->cond->find(in);
    	if (cond_res) return cond_res;
    }
    
    return NULL;
}

void Not::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->cond != NULL)
    	this->cond->find_all(in, out);
    
}

void Not::assert_valid()
{
    assert(cond != NULL);
    cond->assert_valid();
}

In_change_on_write::In_change_on_write(Zvp* zvp)
{
    this->zvp = zvp;
}

In_change_on_write::In_change_on_write()
{
    this->zvp = 0;
}

void In_change_on_write::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void In_change_on_write::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int In_change_on_write::classid()
{
    return ID;
}

bool In_change_on_write::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    In_change_on_write* that = dynamic_cast<In_change_on_write*>(in);
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

bool In_change_on_write::equals(Node* in)
{
    In_change_on_write* that = dynamic_cast<In_change_on_write*>(in);
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

In_change_on_write* In_change_on_write::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    In_change_on_write* clone = new In_change_on_write(zvp);
    return clone;
}

Node* In_change_on_write::find(Node* in)
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

void In_change_on_write::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void In_change_on_write::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

In_copy_on_write::In_copy_on_write(Zvp* zvp)
{
    this->zvp = zvp;
}

In_copy_on_write::In_copy_on_write()
{
    this->zvp = 0;
}

void In_copy_on_write::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void In_copy_on_write::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int In_copy_on_write::classid()
{
    return ID;
}

bool In_copy_on_write::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    In_copy_on_write* that = dynamic_cast<In_copy_on_write*>(in);
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

bool In_copy_on_write::equals(Node* in)
{
    In_copy_on_write* that = dynamic_cast<In_copy_on_write*>(in);
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

In_copy_on_write* In_copy_on_write::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    In_copy_on_write* clone = new In_copy_on_write(zvp);
    return clone;
}

Node* In_copy_on_write::find(Node* in)
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

void In_copy_on_write::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void In_copy_on_write::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

True::True()
{
}

void True::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void True::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int True::classid()
{
    return ID;
}

bool True::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    True* that = dynamic_cast<True*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool True::equals(Node* in)
{
    True* that = dynamic_cast<True*>(in);
    if(that == NULL) return false;
    
    return true;
}

True* True::clone()
{
    True* clone = new True();
    return clone;
}

Node* True::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void True::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void True::assert_valid()
{
}

False::False()
{
}

void False::visit(Visitor* visitor)
{
    visitor->visit_cond(this);
}

void False::transform_children(Transform* transform)
{
    transform->children_cond(this);
}

int False::classid()
{
    return ID;
}

bool False::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    False* that = dynamic_cast<False*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool False::equals(Node* in)
{
    False* that = dynamic_cast<False*>(in);
    if(that == NULL) return false;
    
    return true;
}

False* False::clone()
{
    False* clone = new False();
    return clone;
}

Node* False::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void False::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void False::assert_valid()
{
}

Uninit::Uninit()
{
}

void Uninit::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void Uninit::transform_children(Transform* transform)
{
    transform->children_zvp(this);
}

int Uninit::classid()
{
    return ID;
}

bool Uninit::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Uninit* that = dynamic_cast<Uninit*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool Uninit::equals(Node* in)
{
    Uninit* that = dynamic_cast<Uninit*>(in);
    if(that == NULL) return false;
    
    return true;
}

Uninit* Uninit::clone()
{
    Uninit* clone = new Uninit();
    return clone;
}

Node* Uninit::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void Uninit::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
}

void Uninit::assert_valid()
{
}

Null::Null()
{
}

void Null::visit(Visitor* visitor)
{
    visitor->visit_zvpp(this);
}

void Null::transform_children(Transform* transform)
{
    transform->children_zvpp(this);
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

Clone::Clone(Zvp* zvp)
{
    this->zvp = zvp;
}

Clone::Clone()
{
    this->zvp = 0;
}

void Clone::visit(Visitor* visitor)
{
    visitor->visit_zvp(this);
}

void Clone::transform_children(Transform* transform)
{
    transform->children_zvp(this);
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
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Clone::equals(Node* in)
{
    Clone* that = dynamic_cast<Clone*>(in);
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

Clone* Clone::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    Clone* clone = new Clone(zvp);
    return clone;
}

Node* Clone::find(Node* in)
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

void Clone::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Clone::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

Opt::Opt(Opt_param* param, STRING* value)
{
    this->param = param;
    this->value = value;
}

Opt::Opt()
{
    this->param = 0;
    this->value = 0;
}

void Opt::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Opt::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Opt::classid()
{
    return ID;
}

bool Opt::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Opt* that = dynamic_cast<Opt*>(in);
    if(that == NULL) return false;
    
    if(this->param == NULL)
    {
    	if(that->param != NULL && !that->param->match(this->param))
    		return false;
    }
    else if(!this->param->match(that->param))
    	return false;
    
    if(this->value == NULL)
    {
    	if(that->value != NULL && !that->value->match(this->value))
    		return false;
    }
    else if(!this->value->match(that->value))
    	return false;
    
    return true;
}

bool Opt::equals(Node* in)
{
    Opt* that = dynamic_cast<Opt*>(in);
    if(that == NULL) return false;
    
    if(this->param == NULL || that->param == NULL)
    {
    	if(this->param != NULL || that->param != NULL)
    		return false;
    }
    else if(!this->param->equals(that->param))
    	return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(!this->value->equals(that->value))
    	return false;
    
    return true;
}

Opt* Opt::clone()
{
    Opt_param* param = this->param ? this->param->clone() : NULL;
    STRING* value = this->value ? this->value->clone() : NULL;
    Opt* clone = new Opt(param, value);
    return clone;
}

Node* Opt::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->param != NULL)
    {
    	Node* param_res = this->param->find(in);
    	if (param_res) return param_res;
    }
    
    if (this->value != NULL)
    {
    	Node* value_res = this->value->find(in);
    	if (value_res) return value_res;
    }
    
    return NULL;
}

void Opt::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->param != NULL)
    	this->param->find_all(in, out);
    
    if (this->value != NULL)
    	this->value->find_all(in, out);
    
}

void Opt::assert_valid()
{
    assert(param != NULL);
    param->assert_valid();
    assert(value != NULL);
    value->assert_valid();
}

Profile::Profile(STRING* name)
{
    this->name = name;
}

Profile::Profile()
{
    this->name = 0;
}

void Profile::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Profile::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Profile::classid()
{
    return ID;
}

bool Profile::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Profile* that = dynamic_cast<Profile*>(in);
    if(that == NULL) return false;
    
    if(this->name == NULL)
    {
    	if(that->name != NULL && !that->name->match(this->name))
    		return false;
    }
    else if(!this->name->match(that->name))
    	return false;
    
    return true;
}

bool Profile::equals(Node* in)
{
    Profile* that = dynamic_cast<Profile*>(in);
    if(that == NULL) return false;
    
    if(this->name == NULL || that->name == NULL)
    {
    	if(this->name != NULL || that->name != NULL)
    		return false;
    }
    else if(!this->name->equals(that->name))
    	return false;
    
    return true;
}

Profile* Profile::clone()
{
    STRING* name = this->name ? this->name->clone() : NULL;
    Profile* clone = new Profile(name);
    return clone;
}

Node* Profile::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->name != NULL)
    {
    	Node* name_res = this->name->find(in);
    	if (name_res) return name_res;
    }
    
    return NULL;
}

void Profile::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->name != NULL)
    	this->name->find_all(in, out);
    
}

void Profile::assert_valid()
{
    assert(name != NULL);
    name->assert_valid();
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
    visitor->visit_uninterpreted(this);
}

void UNINTERPRETED::transform_children(Transform* transform)
{
    transform->children_uninterpreted(this);
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

COMMENT::COMMENT(String* value)
{
    this->value = value;
}

COMMENT::COMMENT()
{
    this->value = 0;
}

void COMMENT::visit(Visitor* visitor)
{
    visitor->visit_comment(this);
}

void COMMENT::transform_children(Transform* transform)
{
    transform->children_comment(this);
}

String* COMMENT::get_value_as_string()
{
    return value;
}

int COMMENT::classid()
{
    return ID;
}

bool COMMENT::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    COMMENT* that = dynamic_cast<COMMENT*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool COMMENT::equals(Node* in)
{
    COMMENT* that = dynamic_cast<COMMENT*>(in);
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

COMMENT* COMMENT::clone()
{
    String* value = new String(*this->value);
    COMMENT* clone = new COMMENT(value);
    return clone;
}

Node* COMMENT::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void COMMENT::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void COMMENT::assert_valid()
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

CODE::CODE(string value)
{
    {
		this->value = new String (value);
	}
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

ZVP::ZVP(string value)
{
    {
		this->value = new String (value);
	}
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

ZVPP::ZVPP(string value)
{
    {
		this->value = new String (value);
	}
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

SYMTABLE::SYMTABLE(String* value)
{
    this->value = value;
}

SYMTABLE::SYMTABLE()
{
    this->value = 0;
}

void SYMTABLE::visit(Visitor* visitor)
{
    visitor->visit_symtable(this);
}

void SYMTABLE::transform_children(Transform* transform)
{
    transform->children_symtable(this);
}

String* SYMTABLE::get_value_as_string()
{
    return value;
}

int SYMTABLE::classid()
{
    return ID;
}

bool SYMTABLE::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    SYMTABLE* that = dynamic_cast<SYMTABLE*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool SYMTABLE::equals(Node* in)
{
    SYMTABLE* that = dynamic_cast<SYMTABLE*>(in);
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

SYMTABLE* SYMTABLE::clone()
{
    String* value = new String(*this->value);
    SYMTABLE* clone = new SYMTABLE(value);
    return clone;
}

Node* SYMTABLE::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    return NULL;
}

void SYMTABLE::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
}

void SYMTABLE::assert_valid()
{
    assert(value != NULL);
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
    visitor->visit_string(this);
}

void STRING::transform_children(Transform* transform)
{
    transform->children_string(this);
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

Declare::Declare(ZVP* zvp)
{
    this->zvp = zvp;
}

Declare::Declare()
{
    this->zvp = 0;
}

void Declare::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Declare::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

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
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    return true;
}

bool Declare::equals(Node* in)
{
    Declare* that = dynamic_cast<Declare*>(in);
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

Declare* Declare::clone()
{
    ZVP* zvp = this->zvp ? this->zvp->clone() : NULL;
    Declare* clone = new Declare(zvp);
    return clone;
}

Node* Declare::find(Node* in)
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

void Declare::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
}

void Declare::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
}

Declare_p::Declare_p(ZVPP* zvpp)
{
    this->zvpp = zvpp;
}

Declare_p::Declare_p()
{
    this->zvpp = 0;
}

void Declare_p::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Declare_p::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Declare_p::classid()
{
    return ID;
}

bool Declare_p::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Declare_p* that = dynamic_cast<Declare_p*>(in);
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

bool Declare_p::equals(Node* in)
{
    Declare_p* that = dynamic_cast<Declare_p*>(in);
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

Declare_p* Declare_p::clone()
{
    ZVPP* zvpp = this->zvpp ? this->zvpp->clone() : NULL;
    Declare_p* clone = new Declare_p(zvpp);
    return clone;
}

Node* Declare_p::find(Node* in)
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

void Declare_p::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvpp != NULL)
    	this->zvpp->find_all(in, out);
    
}

void Declare_p::assert_valid()
{
    assert(zvpp != NULL);
    zvpp->assert_valid();
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

Set_is_ref::Set_is_ref(Zvp* zvp, INT* _int)
{
    this->zvp = zvp;
    this->_int = _int;
}

Set_is_ref::Set_is_ref()
{
    this->zvp = 0;
    this->_int = 0;
}

void Set_is_ref::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Set_is_ref::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Set_is_ref::classid()
{
    return ID;
}

bool Set_is_ref::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Set_is_ref* that = dynamic_cast<Set_is_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL)
    {
    	if(that->zvp != NULL && !that->zvp->match(this->zvp))
    		return false;
    }
    else if(!this->zvp->match(that->zvp))
    	return false;
    
    if(this->_int == NULL)
    {
    	if(that->_int != NULL && !that->_int->match(this->_int))
    		return false;
    }
    else if(!this->_int->match(that->_int))
    	return false;
    
    return true;
}

bool Set_is_ref::equals(Node* in)
{
    Set_is_ref* that = dynamic_cast<Set_is_ref*>(in);
    if(that == NULL) return false;
    
    if(this->zvp == NULL || that->zvp == NULL)
    {
    	if(this->zvp != NULL || that->zvp != NULL)
    		return false;
    }
    else if(!this->zvp->equals(that->zvp))
    	return false;
    
    if(this->_int == NULL || that->_int == NULL)
    {
    	if(this->_int != NULL || that->_int != NULL)
    		return false;
    }
    else if(!this->_int->equals(that->_int))
    	return false;
    
    return true;
}

Set_is_ref* Set_is_ref::clone()
{
    Zvp* zvp = this->zvp ? this->zvp->clone() : NULL;
    INT* _int = this->_int ? this->_int->clone() : NULL;
    Set_is_ref* clone = new Set_is_ref(zvp, _int);
    return clone;
}

Node* Set_is_ref::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->zvp != NULL)
    {
    	Node* zvp_res = this->zvp->find(in);
    	if (zvp_res) return zvp_res;
    }
    
    if (this->_int != NULL)
    {
    	Node* _int_res = this->_int->find(in);
    	if (_int_res) return _int_res;
    }
    
    return NULL;
}

void Set_is_ref::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->zvp != NULL)
    	this->zvp->find_all(in, out);
    
    if (this->_int != NULL)
    	this->_int->find_all(in, out);
    
}

void Set_is_ref::assert_valid()
{
    assert(zvp != NULL);
    zvp->assert_valid();
    assert(_int != NULL);
    _int->assert_valid();
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

Overwrite::Overwrite(Zvp* lhs, Zvp* rhs)
{
    this->lhs = lhs;
    this->rhs = rhs;
}

Overwrite::Overwrite()
{
    this->lhs = 0;
    this->rhs = 0;
}

void Overwrite::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Overwrite::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Overwrite::classid()
{
    return ID;
}

bool Overwrite::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Overwrite* that = dynamic_cast<Overwrite*>(in);
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

bool Overwrite::equals(Node* in)
{
    Overwrite* that = dynamic_cast<Overwrite*>(in);
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

Overwrite* Overwrite::clone()
{
    Zvp* lhs = this->lhs ? this->lhs->clone() : NULL;
    Zvp* rhs = this->rhs ? this->rhs->clone() : NULL;
    Overwrite* clone = new Overwrite(lhs, rhs);
    return clone;
}

Node* Overwrite::find(Node* in)
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

void Overwrite::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->lhs != NULL)
    	this->lhs->find_all(in, out);
    
    if (this->rhs != NULL)
    	this->rhs->find_all(in, out);
    
}

void Overwrite::assert_valid()
{
    assert(lhs != NULL);
    lhs->assert_valid();
    assert(rhs != NULL);
    rhs->assert_valid();
}

Symtable_fetch::Symtable_fetch(SYMTABLE* symtable, STRING* name, ZVPP* zvpp)
{
    this->symtable = symtable;
    this->name = name;
    this->zvpp = zvpp;
}

Symtable_fetch::Symtable_fetch()
{
    this->symtable = 0;
    this->name = 0;
    this->zvpp = 0;
}

void Symtable_fetch::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Symtable_fetch::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Symtable_fetch::classid()
{
    return ID;
}

bool Symtable_fetch::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Symtable_fetch* that = dynamic_cast<Symtable_fetch*>(in);
    if(that == NULL) return false;
    
    if(this->symtable == NULL)
    {
    	if(that->symtable != NULL && !that->symtable->match(this->symtable))
    		return false;
    }
    else if(!this->symtable->match(that->symtable))
    	return false;
    
    if(this->name == NULL)
    {
    	if(that->name != NULL && !that->name->match(this->name))
    		return false;
    }
    else if(!this->name->match(that->name))
    	return false;
    
    if(this->zvpp == NULL)
    {
    	if(that->zvpp != NULL && !that->zvpp->match(this->zvpp))
    		return false;
    }
    else if(!this->zvpp->match(that->zvpp))
    	return false;
    
    return true;
}

bool Symtable_fetch::equals(Node* in)
{
    Symtable_fetch* that = dynamic_cast<Symtable_fetch*>(in);
    if(that == NULL) return false;
    
    if(this->symtable == NULL || that->symtable == NULL)
    {
    	if(this->symtable != NULL || that->symtable != NULL)
    		return false;
    }
    else if(!this->symtable->equals(that->symtable))
    	return false;
    
    if(this->name == NULL || that->name == NULL)
    {
    	if(this->name != NULL || that->name != NULL)
    		return false;
    }
    else if(!this->name->equals(that->name))
    	return false;
    
    if(this->zvpp == NULL || that->zvpp == NULL)
    {
    	if(this->zvpp != NULL || that->zvpp != NULL)
    		return false;
    }
    else if(!this->zvpp->equals(that->zvpp))
    	return false;
    
    return true;
}

Symtable_fetch* Symtable_fetch::clone()
{
    SYMTABLE* symtable = this->symtable ? this->symtable->clone() : NULL;
    STRING* name = this->name ? this->name->clone() : NULL;
    ZVPP* zvpp = this->zvpp ? this->zvpp->clone() : NULL;
    Symtable_fetch* clone = new Symtable_fetch(symtable, name, zvpp);
    return clone;
}

Node* Symtable_fetch::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->symtable != NULL)
    {
    	Node* symtable_res = this->symtable->find(in);
    	if (symtable_res) return symtable_res;
    }
    
    if (this->name != NULL)
    {
    	Node* name_res = this->name->find(in);
    	if (name_res) return name_res;
    }
    
    if (this->zvpp != NULL)
    {
    	Node* zvpp_res = this->zvpp->find(in);
    	if (zvpp_res) return zvpp_res;
    }
    
    return NULL;
}

void Symtable_fetch::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->symtable != NULL)
    	this->symtable->find_all(in, out);
    
    if (this->name != NULL)
    	this->name->find_all(in, out);
    
    if (this->zvpp != NULL)
    	this->zvpp->find_all(in, out);
    
}

void Symtable_fetch::assert_valid()
{
    assert(symtable != NULL);
    symtable->assert_valid();
    assert(name != NULL);
    name->assert_valid();
    assert(zvpp != NULL);
    zvpp->assert_valid();
}

Symtable_insert::Symtable_insert(SYMTABLE* symtable, STRING* name, ZVPP* zvpp)
{
    this->symtable = symtable;
    this->name = name;
    this->zvpp = zvpp;
}

Symtable_insert::Symtable_insert()
{
    this->symtable = 0;
    this->name = 0;
    this->zvpp = 0;
}

void Symtable_insert::visit(Visitor* visitor)
{
    visitor->visit_statement(this);
}

void Symtable_insert::transform_children(Transform* transform)
{
    transform->children_statement(this);
}

int Symtable_insert::classid()
{
    return ID;
}

bool Symtable_insert::match(Node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Symtable_insert* that = dynamic_cast<Symtable_insert*>(in);
    if(that == NULL) return false;
    
    if(this->symtable == NULL)
    {
    	if(that->symtable != NULL && !that->symtable->match(this->symtable))
    		return false;
    }
    else if(!this->symtable->match(that->symtable))
    	return false;
    
    if(this->name == NULL)
    {
    	if(that->name != NULL && !that->name->match(this->name))
    		return false;
    }
    else if(!this->name->match(that->name))
    	return false;
    
    if(this->zvpp == NULL)
    {
    	if(that->zvpp != NULL && !that->zvpp->match(this->zvpp))
    		return false;
    }
    else if(!this->zvpp->match(that->zvpp))
    	return false;
    
    return true;
}

bool Symtable_insert::equals(Node* in)
{
    Symtable_insert* that = dynamic_cast<Symtable_insert*>(in);
    if(that == NULL) return false;
    
    if(this->symtable == NULL || that->symtable == NULL)
    {
    	if(this->symtable != NULL || that->symtable != NULL)
    		return false;
    }
    else if(!this->symtable->equals(that->symtable))
    	return false;
    
    if(this->name == NULL || that->name == NULL)
    {
    	if(this->name != NULL || that->name != NULL)
    		return false;
    }
    else if(!this->name->equals(that->name))
    	return false;
    
    if(this->zvpp == NULL || that->zvpp == NULL)
    {
    	if(this->zvpp != NULL || that->zvpp != NULL)
    		return false;
    }
    else if(!this->zvpp->equals(that->zvpp))
    	return false;
    
    return true;
}

Symtable_insert* Symtable_insert::clone()
{
    SYMTABLE* symtable = this->symtable ? this->symtable->clone() : NULL;
    STRING* name = this->name ? this->name->clone() : NULL;
    ZVPP* zvpp = this->zvpp ? this->zvpp->clone() : NULL;
    Symtable_insert* clone = new Symtable_insert(symtable, name, zvpp);
    return clone;
}

Node* Symtable_insert::find(Node* in)
{
    if (this->match (in))
    	return this;
    
    if (this->symtable != NULL)
    {
    	Node* symtable_res = this->symtable->find(in);
    	if (symtable_res) return symtable_res;
    }
    
    if (this->name != NULL)
    {
    	Node* name_res = this->name->find(in);
    	if (name_res) return name_res;
    }
    
    if (this->zvpp != NULL)
    {
    	Node* zvpp_res = this->zvpp->find(in);
    	if (zvpp_res) return zvpp_res;
    }
    
    return NULL;
}

void Symtable_insert::find_all(Node* in, Node_list* out)
{
    if (this->match (in))
    	out->push_back (this);
    
    if (this->symtable != NULL)
    	this->symtable->find_all(in, out);
    
    if (this->name != NULL)
    	this->name->find_all(in, out);
    
    if (this->zvpp != NULL)
    	this->zvpp->find_all(in, out);
    
}

void Symtable_insert::assert_valid()
{
    assert(symtable != NULL);
    symtable->assert_valid();
    assert(name != NULL);
    name->assert_valid();
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

