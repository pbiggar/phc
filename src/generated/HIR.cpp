#include "HIR.h"
#include "HIR_transform.h"
#include "HIR_visitor.h"

namespace HIR{
//  Return the line number of the node (or 0 if unknown)
int HIR_node::get_line_number()
{
    {
		Integer* i = dynamic_cast<Integer*>(attrs->get("phc.line_number"));
		if(i != NULL)
			return i->value();
		else
			return 0;
	}
}

//  Return the filename of the node (or NULL if unknown)
String* HIR_node::get_filename()
{
    {
		return dynamic_cast<String*>(attrs->get("phc.filename"));
	}
}

HIR_node::HIR_node()
{
    {
		// Constructor gets called because all classes inherit from
		// HIR_node virtually; also, because maketea knows HIR_node is
		// abstract, it won't add a constructor itself
		attrs = new AttrMap();
	}
}

void HIR_node::clone_mixin_from(HIR_node* in)
{
    {
		attrs = in->attrs->clone();
	}
}

void HIR_node::assert_mixin_valid()
{
    {
		assert(attrs != NULL);

		AttrMap::const_iterator i;
		for(i = attrs->begin(); i != attrs->end(); i++)
		{
			if ((*i).first != "phc.line_number"
				&& (*i).first != "phc.filename")
			{
				assert((*i).second != NULL);
			}
		}
	}
}

bool HIR_node::is_mixin_equal(HIR_node* in)
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

//  Return the comments associated with the node
List<String*>* HIR_node::get_comments()
{
    {
		List<String*>* comments = dynamic_cast<List<String*>*>(attrs->get("phc.comments"));
		return comments;
	}
}

HIR_php_script::HIR_php_script(List<HIR_statement*>* statements)
{
    this->statements = statements;
}

HIR_php_script::HIR_php_script()
{
    this->statements = 0;
}

void HIR_php_script::visit(HIR_visitor* visitor)
{
    visitor->visit_php_script(this);
}

void HIR_php_script::transform_children(HIR_transform* transform)
{
    transform->children_php_script(this);
}

int HIR_php_script::classid()
{
    return ID;
}

bool HIR_php_script::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_php_script* that = dynamic_cast<HIR_php_script*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i, j;
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

bool HIR_php_script::equals(HIR_node* in)
{
    HIR_php_script* that = dynamic_cast<HIR_php_script*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	List<HIR_statement*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_php_script* HIR_php_script::clone()
{
    List<HIR_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i;
    	statements = new List<HIR_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_php_script* clone = new HIR_php_script(statements);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_php_script::assert_valid()
{
    assert(statements != NULL);
    {
    	List<HIR_statement*>::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_statement::HIR_statement()
{
}

HIR_class_mod::HIR_class_mod(bool is_abstract, bool is_final)
{
    this->is_abstract = is_abstract;
    this->is_final = is_final;
}

HIR_class_mod::HIR_class_mod()
{
    this->is_abstract = 0;
    this->is_final = 0;
}

void HIR_class_mod::visit(HIR_visitor* visitor)
{
    visitor->visit_class_mod(this);
}

void HIR_class_mod::transform_children(HIR_transform* transform)
{
    transform->children_class_mod(this);
}

int HIR_class_mod::classid()
{
    return ID;
}

bool HIR_class_mod::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_class_mod* that = dynamic_cast<HIR_class_mod*>(in);
    if(that == NULL) return false;
    
    that->is_abstract = this->is_abstract;
    that->is_final = this->is_final;
    return true;
}

bool HIR_class_mod::equals(HIR_node* in)
{
    HIR_class_mod* that = dynamic_cast<HIR_class_mod*>(in);
    if(that == NULL) return false;
    
    if(this->is_abstract != that->is_abstract)
    	return false;
    
    if(this->is_final != that->is_final)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_class_mod* HIR_class_mod::clone()
{
    bool is_abstract = this->is_abstract;
    bool is_final = this->is_final;
    HIR_class_mod* clone = new HIR_class_mod(is_abstract, is_final);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_class_mod::assert_valid()
{
    HIR_node::assert_mixin_valid();
}

HIR_member::HIR_member()
{
}

HIR_signature::HIR_signature(HIR_method_mod* method_mod, bool is_ref, Token_method_name* method_name, List<HIR_formal_parameter*>* formal_parameters)
{
    this->method_mod = method_mod;
    this->is_ref = is_ref;
    this->method_name = method_name;
    this->formal_parameters = formal_parameters;
}

HIR_signature::HIR_signature()
{
    this->method_mod = 0;
    this->is_ref = 0;
    this->method_name = 0;
    this->formal_parameters = 0;
}

void HIR_signature::visit(HIR_visitor* visitor)
{
    visitor->visit_signature(this);
}

void HIR_signature::transform_children(HIR_transform* transform)
{
    transform->children_signature(this);
}

int HIR_signature::classid()
{
    return ID;
}

bool HIR_signature::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_signature* that = dynamic_cast<HIR_signature*>(in);
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
    	List<HIR_formal_parameter*>::const_iterator i, j;
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

bool HIR_signature::equals(HIR_node* in)
{
    HIR_signature* that = dynamic_cast<HIR_signature*>(in);
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
    	List<HIR_formal_parameter*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_signature* HIR_signature::clone()
{
    HIR_method_mod* method_mod = this->method_mod ? this->method_mod->clone() : NULL;
    bool is_ref = this->is_ref;
    Token_method_name* method_name = this->method_name ? this->method_name->clone() : NULL;
    List<HIR_formal_parameter*>* formal_parameters = NULL;
    if(this->formal_parameters != NULL)
    {
    	List<HIR_formal_parameter*>::const_iterator i;
    	formal_parameters = new List<HIR_formal_parameter*>;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    		formal_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_signature* clone = new HIR_signature(method_mod, is_ref, method_name, formal_parameters);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_signature::assert_valid()
{
    assert(method_mod != NULL);
    method_mod->assert_valid();
    assert(method_name != NULL);
    method_name->assert_valid();
    assert(formal_parameters != NULL);
    {
    	List<HIR_formal_parameter*>::const_iterator i;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_signature::HIR_signature(const char* name)
{
    {
		this->method_mod = HIR_method_mod::new_PUBLIC();
		this->is_ref = false;
		this->method_name = new Token_method_name(new String(name));
		this->formal_parameters = new List<HIR_formal_parameter*>;
	}
}

HIR_method_mod::HIR_method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final)
{
    this->is_public = is_public;
    this->is_protected = is_protected;
    this->is_private = is_private;
    this->is_static = is_static;
    this->is_abstract = is_abstract;
    this->is_final = is_final;
}

void HIR_method_mod::visit(HIR_visitor* visitor)
{
    visitor->visit_method_mod(this);
}

void HIR_method_mod::transform_children(HIR_transform* transform)
{
    transform->children_method_mod(this);
}

int HIR_method_mod::classid()
{
    return ID;
}

bool HIR_method_mod::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_method_mod* that = dynamic_cast<HIR_method_mod*>(in);
    if(that == NULL) return false;
    
    that->is_public = this->is_public;
    that->is_protected = this->is_protected;
    that->is_private = this->is_private;
    that->is_static = this->is_static;
    that->is_abstract = this->is_abstract;
    that->is_final = this->is_final;
    return true;
}

bool HIR_method_mod::equals(HIR_node* in)
{
    HIR_method_mod* that = dynamic_cast<HIR_method_mod*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_method_mod* HIR_method_mod::clone()
{
    bool is_public = this->is_public;
    bool is_protected = this->is_protected;
    bool is_private = this->is_private;
    bool is_static = this->is_static;
    bool is_abstract = this->is_abstract;
    bool is_final = this->is_final;
    HIR_method_mod* clone = new HIR_method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_method_mod::assert_valid()
{
    HIR_node::assert_mixin_valid();
}

HIR_method_mod::HIR_method_mod()
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

HIR_method_mod::HIR_method_mod(HIR_method_mod* a, HIR_method_mod* b)
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

HIR_method_mod* HIR_method_mod::new_PUBLIC()
{
    {
		return new HIR_method_mod(true, false, false, false, false, false);		
	}
}

HIR_method_mod* HIR_method_mod::new_PROTECTED()
{
    { 
		return new HIR_method_mod(false, true, false, false, false, false);		
	}
}

HIR_method_mod* HIR_method_mod::new_PRIVATE()
{
    { 
		return new HIR_method_mod(false, false, true, false, false, false);		
	}
}

HIR_method_mod* HIR_method_mod::new_STATIC()
{
    { 
		return new HIR_method_mod(false, false, false, true, false, false);		
	}
}

HIR_method_mod* HIR_method_mod::new_ABSTRACT()
{
    { 
		return new HIR_method_mod(false, false, false, false, true, false);		
	}
}

HIR_method_mod* HIR_method_mod::new_FINAL()
{
    { 
		return new HIR_method_mod(false, false, false, false, false, true);		
	}
}

HIR_formal_parameter::HIR_formal_parameter(HIR_type* type, bool is_ref, HIR_name_with_default* var)
{
    this->type = type;
    this->is_ref = is_ref;
    this->var = var;
}

HIR_formal_parameter::HIR_formal_parameter()
{
    this->type = 0;
    this->is_ref = 0;
    this->var = 0;
}

void HIR_formal_parameter::visit(HIR_visitor* visitor)
{
    visitor->visit_formal_parameter(this);
}

void HIR_formal_parameter::transform_children(HIR_transform* transform)
{
    transform->children_formal_parameter(this);
}

int HIR_formal_parameter::classid()
{
    return ID;
}

bool HIR_formal_parameter::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_formal_parameter* that = dynamic_cast<HIR_formal_parameter*>(in);
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

bool HIR_formal_parameter::equals(HIR_node* in)
{
    HIR_formal_parameter* that = dynamic_cast<HIR_formal_parameter*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_formal_parameter* HIR_formal_parameter::clone()
{
    HIR_type* type = this->type ? this->type->clone() : NULL;
    bool is_ref = this->is_ref;
    HIR_name_with_default* var = this->var ? this->var->clone() : NULL;
    HIR_formal_parameter* clone = new HIR_formal_parameter(type, is_ref, var);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_formal_parameter::assert_valid()
{
    assert(type != NULL);
    type->assert_valid();
    assert(var != NULL);
    var->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_formal_parameter::HIR_formal_parameter(HIR_type* type, Token_variable_name* name)
{
    {
		this->type = type;
		this->is_ref = false;
		this->var = new HIR_name_with_default(name, NULL);
	}
}

HIR_formal_parameter::HIR_formal_parameter(HIR_type* type, bool is_ref, Token_variable_name* name)
{
    { 
		this->type = type;
		this->is_ref = is_ref;
		this->var = new HIR_name_with_default(name, NULL);
	}
}

HIR_type::HIR_type(Token_class_name* class_name)
{
    this->class_name = class_name;
}

HIR_type::HIR_type()
{
    this->class_name = 0;
}

void HIR_type::visit(HIR_visitor* visitor)
{
    visitor->visit_type(this);
}

void HIR_type::transform_children(HIR_transform* transform)
{
    transform->children_type(this);
}

int HIR_type::classid()
{
    return ID;
}

bool HIR_type::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_type* that = dynamic_cast<HIR_type*>(in);
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

bool HIR_type::equals(HIR_node* in)
{
    HIR_type* that = dynamic_cast<HIR_type*>(in);
    if(that == NULL) return false;
    
    if(this->class_name == NULL || that->class_name == NULL)
    {
    	if(this->class_name != NULL || that->class_name != NULL)
    		return false;
    }
    else if(!this->class_name->equals(that->class_name))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_type* HIR_type::clone()
{
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    HIR_type* clone = new HIR_type(class_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_type::assert_valid()
{
    if(class_name != NULL) class_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_attr_mod::HIR_attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const)
{
    this->is_public = is_public;
    this->is_protected = is_protected;
    this->is_private = is_private;
    this->is_static = is_static;
    this->is_const = is_const;
}

void HIR_attr_mod::visit(HIR_visitor* visitor)
{
    visitor->visit_attr_mod(this);
}

void HIR_attr_mod::transform_children(HIR_transform* transform)
{
    transform->children_attr_mod(this);
}

int HIR_attr_mod::classid()
{
    return ID;
}

bool HIR_attr_mod::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_attr_mod* that = dynamic_cast<HIR_attr_mod*>(in);
    if(that == NULL) return false;
    
    that->is_public = this->is_public;
    that->is_protected = this->is_protected;
    that->is_private = this->is_private;
    that->is_static = this->is_static;
    that->is_const = this->is_const;
    return true;
}

bool HIR_attr_mod::equals(HIR_node* in)
{
    HIR_attr_mod* that = dynamic_cast<HIR_attr_mod*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_attr_mod* HIR_attr_mod::clone()
{
    bool is_public = this->is_public;
    bool is_protected = this->is_protected;
    bool is_private = this->is_private;
    bool is_static = this->is_static;
    bool is_const = this->is_const;
    HIR_attr_mod* clone = new HIR_attr_mod(is_public, is_protected, is_private, is_static, is_const);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_attr_mod::assert_valid()
{
    HIR_node::assert_mixin_valid();
}

HIR_attr_mod::HIR_attr_mod()
{
    {
		is_public = false;
		is_protected = false;
		is_private = false;
		is_static = false;
		is_const = false;
	}
}

HIR_attr_mod::HIR_attr_mod(HIR_method_mod* mm)
{
    {
		if(mm->is_final)
			phc_error("The final modifier is only allowed for methods", mm->get_filename(), mm->get_line_number());

		this->is_public = mm->is_public;
		this->is_protected = mm->is_protected;
		this->is_private = mm->is_private;
		this->is_static = mm->is_static;
		this->is_const = false;
	}
}

HIR_attr_mod* HIR_attr_mod::new_PUBLIC()
{
    {
		return new HIR_attr_mod(true, false, false, false, false);
	}
}

HIR_attr_mod* HIR_attr_mod::new_PROTECTED()
{
    { 
		return new HIR_attr_mod(false, true, false, false, false);
	}
}

HIR_attr_mod* HIR_attr_mod::new_PRIVATE()
{
    {
		return new HIR_attr_mod(false, false, true, false, false);
	}
}

HIR_attr_mod* HIR_attr_mod::new_STATIC()
{
    {
		return new HIR_attr_mod(false, false, false, true, false);
	}
}

HIR_attr_mod* HIR_attr_mod::new_CONST()
{
    {
		return new HIR_attr_mod(false, false, false, false, true);
	}
}

HIR_name_with_default::HIR_name_with_default(Token_variable_name* variable_name, HIR_expr* expr)
{
    this->variable_name = variable_name;
    this->expr = expr;
}

HIR_name_with_default::HIR_name_with_default()
{
    this->variable_name = 0;
    this->expr = 0;
}

void HIR_name_with_default::visit(HIR_visitor* visitor)
{
    visitor->visit_name_with_default(this);
}

void HIR_name_with_default::transform_children(HIR_transform* transform)
{
    transform->children_name_with_default(this);
}

int HIR_name_with_default::classid()
{
    return ID;
}

bool HIR_name_with_default::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_name_with_default* that = dynamic_cast<HIR_name_with_default*>(in);
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

bool HIR_name_with_default::equals(HIR_node* in)
{
    HIR_name_with_default* that = dynamic_cast<HIR_name_with_default*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_name_with_default* HIR_name_with_default::clone()
{
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    HIR_name_with_default* clone = new HIR_name_with_default(variable_name, expr);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_name_with_default::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    if(expr != NULL) expr->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_catch::HIR_catch(Token_class_name* class_name, Token_variable_name* variable_name, List<HIR_statement*>* statements)
{
    this->class_name = class_name;
    this->variable_name = variable_name;
    this->statements = statements;
}

HIR_catch::HIR_catch()
{
    this->class_name = 0;
    this->variable_name = 0;
    this->statements = 0;
}

void HIR_catch::visit(HIR_visitor* visitor)
{
    visitor->visit_catch(this);
}

void HIR_catch::transform_children(HIR_transform* transform)
{
    transform->children_catch(this);
}

int HIR_catch::classid()
{
    return ID;
}

bool HIR_catch::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_catch* that = dynamic_cast<HIR_catch*>(in);
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
    	List<HIR_statement*>::const_iterator i, j;
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

bool HIR_catch::equals(HIR_node* in)
{
    HIR_catch* that = dynamic_cast<HIR_catch*>(in);
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
    	List<HIR_statement*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_catch* HIR_catch::clone()
{
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    List<HIR_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i;
    	statements = new List<HIR_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_catch* clone = new HIR_catch(class_name, variable_name, statements);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_catch::assert_valid()
{
    assert(class_name != NULL);
    class_name->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(statements != NULL);
    {
    	List<HIR_statement*>::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_variable_name::HIR_variable_name()
{
}

HIR_target::HIR_target()
{
}

HIR_array_elem::HIR_array_elem(HIR_expr* key, bool is_ref, HIR_expr* val)
{
    this->key = key;
    this->is_ref = is_ref;
    this->val = val;
}

HIR_array_elem::HIR_array_elem()
{
    this->key = 0;
    this->is_ref = 0;
    this->val = 0;
}

void HIR_array_elem::visit(HIR_visitor* visitor)
{
    visitor->visit_array_elem(this);
}

void HIR_array_elem::transform_children(HIR_transform* transform)
{
    transform->children_array_elem(this);
}

int HIR_array_elem::classid()
{
    return ID;
}

bool HIR_array_elem::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_array_elem* that = dynamic_cast<HIR_array_elem*>(in);
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

bool HIR_array_elem::equals(HIR_node* in)
{
    HIR_array_elem* that = dynamic_cast<HIR_array_elem*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_array_elem* HIR_array_elem::clone()
{
    HIR_expr* key = this->key ? this->key->clone() : NULL;
    bool is_ref = this->is_ref;
    HIR_expr* val = this->val ? this->val->clone() : NULL;
    HIR_array_elem* clone = new HIR_array_elem(key, is_ref, val);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_array_elem::assert_valid()
{
    if(key != NULL) key->assert_valid();
    assert(val != NULL);
    val->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_method_name::HIR_method_name()
{
}

HIR_actual_parameter::HIR_actual_parameter(bool is_ref, HIR_expr* expr)
{
    this->is_ref = is_ref;
    this->expr = expr;
}

HIR_actual_parameter::HIR_actual_parameter()
{
    this->is_ref = 0;
    this->expr = 0;
}

void HIR_actual_parameter::visit(HIR_visitor* visitor)
{
    visitor->visit_actual_parameter(this);
}

void HIR_actual_parameter::transform_children(HIR_transform* transform)
{
    transform->children_actual_parameter(this);
}

int HIR_actual_parameter::classid()
{
    return ID;
}

bool HIR_actual_parameter::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_actual_parameter* that = dynamic_cast<HIR_actual_parameter*>(in);
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

bool HIR_actual_parameter::equals(HIR_node* in)
{
    HIR_actual_parameter* that = dynamic_cast<HIR_actual_parameter*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_actual_parameter* HIR_actual_parameter::clone()
{
    bool is_ref = this->is_ref;
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    HIR_actual_parameter* clone = new HIR_actual_parameter(is_ref, expr);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_actual_parameter::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_class_name::HIR_class_name()
{
}

HIR_identifier::HIR_identifier()
{
}

HIR_class_def::HIR_class_def(HIR_class_mod* class_mod, Token_class_name* class_name, Token_class_name* extends, List<Token_interface_name*>* implements, List<HIR_member*>* members)
{
    this->class_mod = class_mod;
    this->class_name = class_name;
    this->extends = extends;
    this->implements = implements;
    this->members = members;
}

HIR_class_def::HIR_class_def()
{
    this->class_mod = 0;
    this->class_name = 0;
    this->extends = 0;
    this->implements = 0;
    this->members = 0;
}

void HIR_class_def::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_class_def::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_class_def::classid()
{
    return ID;
}

bool HIR_class_def::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_class_def* that = dynamic_cast<HIR_class_def*>(in);
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
    	List<Token_interface_name*>::const_iterator i, j;
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
    	List<HIR_member*>::const_iterator i, j;
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

bool HIR_class_def::equals(HIR_node* in)
{
    HIR_class_def* that = dynamic_cast<HIR_class_def*>(in);
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
    	List<Token_interface_name*>::const_iterator i, j;
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
    	List<HIR_member*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_class_def* HIR_class_def::clone()
{
    HIR_class_mod* class_mod = this->class_mod ? this->class_mod->clone() : NULL;
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Token_class_name* extends = this->extends ? this->extends->clone() : NULL;
    List<Token_interface_name*>* implements = NULL;
    if(this->implements != NULL)
    {
    	List<Token_interface_name*>::const_iterator i;
    	implements = new List<Token_interface_name*>;
    	for(i = this->implements->begin(); i != this->implements->end(); i++)
    		implements->push_back(*i ? (*i)->clone() : NULL);
    }
    List<HIR_member*>* members = NULL;
    if(this->members != NULL)
    {
    	List<HIR_member*>::const_iterator i;
    	members = new List<HIR_member*>;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    		members->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_class_def* clone = new HIR_class_def(class_mod, class_name, extends, implements, members);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_class_def::assert_valid()
{
    assert(class_mod != NULL);
    class_mod->assert_valid();
    assert(class_name != NULL);
    class_name->assert_valid();
    if(extends != NULL) extends->assert_valid();
    assert(implements != NULL);
    {
    	List<Token_interface_name*>::const_iterator i;
    	for(i = this->implements->begin(); i != this->implements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(members != NULL);
    {
    	List<HIR_member*>::const_iterator i;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_class_def::HIR_class_def(HIR_class_mod* mod)
{
    {
		this->class_mod = mod;
		this->class_name = NULL;
		this->extends = NULL;
		this->implements = new List<Token_interface_name*>;
		this->members = new List<HIR_member*>;
	}
}

HIR_class_def::HIR_class_def(const char* name)
{
    {
		this->class_mod = new HIR_class_mod(false, false);
		this->class_name = new Token_class_name(new String(name));
		this->extends = NULL;
		this->implements = new List<Token_interface_name*>;
		this->members = new List<HIR_member*>;
	}
}

void HIR_class_def::add_member(HIR_member* member)
{
    {
		this->members->push_back(member);
	}
}

//  Returns NULL if the method could not be found
HIR_method* HIR_class_def::get_method(const char* name)
{
    {
		List<HIR_member*>::const_iterator i;
		for(i = members->begin(); i != members->end(); i++)
		{
			HIR_method* method = dynamic_cast<HIR_method*>(*i);
			if(method && *method->signature->method_name->value == name)
				return method;
		}

		return NULL;
	}
}

HIR_interface_def::HIR_interface_def(Token_interface_name* interface_name, List<Token_interface_name*>* extends, List<HIR_member*>* members)
{
    this->interface_name = interface_name;
    this->extends = extends;
    this->members = members;
}

HIR_interface_def::HIR_interface_def()
{
    this->interface_name = 0;
    this->extends = 0;
    this->members = 0;
}

void HIR_interface_def::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_interface_def::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_interface_def::classid()
{
    return ID;
}

bool HIR_interface_def::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_interface_def* that = dynamic_cast<HIR_interface_def*>(in);
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
    	List<Token_interface_name*>::const_iterator i, j;
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
    	List<HIR_member*>::const_iterator i, j;
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

bool HIR_interface_def::equals(HIR_node* in)
{
    HIR_interface_def* that = dynamic_cast<HIR_interface_def*>(in);
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
    	List<Token_interface_name*>::const_iterator i, j;
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
    	List<HIR_member*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_interface_def* HIR_interface_def::clone()
{
    Token_interface_name* interface_name = this->interface_name ? this->interface_name->clone() : NULL;
    List<Token_interface_name*>* extends = NULL;
    if(this->extends != NULL)
    {
    	List<Token_interface_name*>::const_iterator i;
    	extends = new List<Token_interface_name*>;
    	for(i = this->extends->begin(); i != this->extends->end(); i++)
    		extends->push_back(*i ? (*i)->clone() : NULL);
    }
    List<HIR_member*>* members = NULL;
    if(this->members != NULL)
    {
    	List<HIR_member*>::const_iterator i;
    	members = new List<HIR_member*>;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    		members->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_interface_def* clone = new HIR_interface_def(interface_name, extends, members);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_interface_def::assert_valid()
{
    assert(interface_name != NULL);
    interface_name->assert_valid();
    assert(extends != NULL);
    {
    	List<Token_interface_name*>::const_iterator i;
    	for(i = this->extends->begin(); i != this->extends->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(members != NULL);
    {
    	List<HIR_member*>::const_iterator i;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_method::HIR_method(HIR_signature* signature, List<HIR_statement*>* statements)
{
    this->signature = signature;
    this->statements = statements;
}

HIR_method::HIR_method()
{
    this->signature = 0;
    this->statements = 0;
}

void HIR_method::visit(HIR_visitor* visitor)
{
    visitor->visit_member(this);
}

void HIR_method::transform_children(HIR_transform* transform)
{
    transform->children_member(this);
}

int HIR_method::classid()
{
    return ID;
}

bool HIR_method::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_method* that = dynamic_cast<HIR_method*>(in);
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
    	List<HIR_statement*>::const_iterator i, j;
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

bool HIR_method::equals(HIR_node* in)
{
    HIR_method* that = dynamic_cast<HIR_method*>(in);
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
    	List<HIR_statement*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_method* HIR_method::clone()
{
    HIR_signature* signature = this->signature ? this->signature->clone() : NULL;
    List<HIR_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i;
    	statements = new List<HIR_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_method* clone = new HIR_method(signature, statements);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_method::assert_valid()
{
    assert(signature != NULL);
    signature->assert_valid();
    if(statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_attribute::HIR_attribute(HIR_attr_mod* attr_mod, HIR_name_with_default* var)
{
    this->attr_mod = attr_mod;
    this->var = var;
}

HIR_attribute::HIR_attribute()
{
    this->attr_mod = 0;
    this->var = 0;
}

void HIR_attribute::visit(HIR_visitor* visitor)
{
    visitor->visit_member(this);
}

void HIR_attribute::transform_children(HIR_transform* transform)
{
    transform->children_member(this);
}

int HIR_attribute::classid()
{
    return ID;
}

bool HIR_attribute::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_attribute* that = dynamic_cast<HIR_attribute*>(in);
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

bool HIR_attribute::equals(HIR_node* in)
{
    HIR_attribute* that = dynamic_cast<HIR_attribute*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_attribute* HIR_attribute::clone()
{
    HIR_attr_mod* attr_mod = this->attr_mod ? this->attr_mod->clone() : NULL;
    HIR_name_with_default* var = this->var ? this->var->clone() : NULL;
    HIR_attribute* clone = new HIR_attribute(attr_mod, var);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_attribute::assert_valid()
{
    assert(attr_mod != NULL);
    attr_mod->assert_valid();
    assert(var != NULL);
    var->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_return::HIR_return(HIR_expr* expr)
{
    this->expr = expr;
}

HIR_return::HIR_return()
{
    this->expr = 0;
}

void HIR_return::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_return::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_return::classid()
{
    return ID;
}

bool HIR_return::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_return* that = dynamic_cast<HIR_return*>(in);
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

bool HIR_return::equals(HIR_node* in)
{
    HIR_return* that = dynamic_cast<HIR_return*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_return* HIR_return::clone()
{
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    HIR_return* clone = new HIR_return(expr);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_return::assert_valid()
{
    if(expr != NULL) expr->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_static_declaration::HIR_static_declaration(HIR_name_with_default* var)
{
    this->var = var;
}

HIR_static_declaration::HIR_static_declaration()
{
    this->var = 0;
}

void HIR_static_declaration::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_static_declaration::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_static_declaration::classid()
{
    return ID;
}

bool HIR_static_declaration::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_static_declaration* that = dynamic_cast<HIR_static_declaration*>(in);
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

bool HIR_static_declaration::equals(HIR_node* in)
{
    HIR_static_declaration* that = dynamic_cast<HIR_static_declaration*>(in);
    if(that == NULL) return false;
    
    if(this->var == NULL || that->var == NULL)
    {
    	if(this->var != NULL || that->var != NULL)
    		return false;
    }
    else if(!this->var->equals(that->var))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_static_declaration* HIR_static_declaration::clone()
{
    HIR_name_with_default* var = this->var ? this->var->clone() : NULL;
    HIR_static_declaration* clone = new HIR_static_declaration(var);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_static_declaration::assert_valid()
{
    assert(var != NULL);
    var->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_global::HIR_global(HIR_variable_name* variable_name)
{
    this->variable_name = variable_name;
}

HIR_global::HIR_global()
{
    this->variable_name = 0;
}

void HIR_global::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_global::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_global::classid()
{
    return ID;
}

bool HIR_global::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_global* that = dynamic_cast<HIR_global*>(in);
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

bool HIR_global::equals(HIR_node* in)
{
    HIR_global* that = dynamic_cast<HIR_global*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_global* HIR_global::clone()
{
    HIR_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    HIR_global* clone = new HIR_global(variable_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_global::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_try::HIR_try(List<HIR_statement*>* statements, List<HIR_catch*>* catches)
{
    this->statements = statements;
    this->catches = catches;
}

HIR_try::HIR_try()
{
    this->statements = 0;
    this->catches = 0;
}

void HIR_try::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_try::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_try::classid()
{
    return ID;
}

bool HIR_try::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_try* that = dynamic_cast<HIR_try*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i, j;
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
    	List<HIR_catch*>::const_iterator i, j;
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

bool HIR_try::equals(HIR_node* in)
{
    HIR_try* that = dynamic_cast<HIR_try*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	List<HIR_statement*>::const_iterator i, j;
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
    	List<HIR_catch*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_try* HIR_try::clone()
{
    List<HIR_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<HIR_statement*>::const_iterator i;
    	statements = new List<HIR_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    List<HIR_catch*>* catches = NULL;
    if(this->catches != NULL)
    {
    	List<HIR_catch*>::const_iterator i;
    	catches = new List<HIR_catch*>;
    	for(i = this->catches->begin(); i != this->catches->end(); i++)
    		catches->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_try* clone = new HIR_try(statements, catches);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_try::assert_valid()
{
    assert(statements != NULL);
    {
    	List<HIR_statement*>::const_iterator i;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    assert(catches != NULL);
    {
    	List<HIR_catch*>::const_iterator i;
    	for(i = this->catches->begin(); i != this->catches->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_throw::HIR_throw(HIR_expr* expr)
{
    this->expr = expr;
}

HIR_throw::HIR_throw()
{
    this->expr = 0;
}

void HIR_throw::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_throw::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_throw::classid()
{
    return ID;
}

bool HIR_throw::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_throw* that = dynamic_cast<HIR_throw*>(in);
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

bool HIR_throw::equals(HIR_node* in)
{
    HIR_throw* that = dynamic_cast<HIR_throw*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_throw* HIR_throw::clone()
{
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    HIR_throw* clone = new HIR_throw(expr);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_throw::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_eval_expr::HIR_eval_expr(HIR_expr* expr)
{
    this->expr = expr;
    _init();
}

HIR_eval_expr::HIR_eval_expr()
{
    this->expr = 0;
    _init();
}

void HIR_eval_expr::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_eval_expr::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_eval_expr::classid()
{
    return ID;
}

bool HIR_eval_expr::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_eval_expr* that = dynamic_cast<HIR_eval_expr*>(in);
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

bool HIR_eval_expr::equals(HIR_node* in)
{
    HIR_eval_expr* that = dynamic_cast<HIR_eval_expr*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_eval_expr* HIR_eval_expr::clone()
{
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    HIR_eval_expr* clone = new HIR_eval_expr(expr);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_eval_expr::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    HIR_node::assert_mixin_valid();
}

void HIR_eval_expr::_init()
{
    {
		assert (expr != NULL);
	}
}

HIR_branch::HIR_branch(HIR_expr* expr, Token_label_name* iftrue, Token_label_name* iffalse)
{
    this->expr = expr;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

HIR_branch::HIR_branch()
{
    this->expr = 0;
    this->iftrue = 0;
    this->iffalse = 0;
}

void HIR_branch::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_branch::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_branch::classid()
{
    return ID;
}

bool HIR_branch::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_branch* that = dynamic_cast<HIR_branch*>(in);
    if(that == NULL) return false;
    
    if(this->expr == NULL)
    {
    	if(that->expr != NULL && !that->expr->match(this->expr))
    		return false;
    }
    else if(!this->expr->match(that->expr))
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

bool HIR_branch::equals(HIR_node* in)
{
    HIR_branch* that = dynamic_cast<HIR_branch*>(in);
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
    else if(!this->iftrue->equals(that->iftrue))
    	return false;
    
    if(this->iffalse == NULL || that->iffalse == NULL)
    {
    	if(this->iffalse != NULL || that->iffalse != NULL)
    		return false;
    }
    else if(!this->iffalse->equals(that->iffalse))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_branch* HIR_branch::clone()
{
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    Token_label_name* iftrue = this->iftrue ? this->iftrue->clone() : NULL;
    Token_label_name* iffalse = this->iffalse ? this->iffalse->clone() : NULL;
    HIR_branch* clone = new HIR_branch(expr, iftrue, iffalse);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_branch::assert_valid()
{
    assert(expr != NULL);
    expr->assert_valid();
    assert(iftrue != NULL);
    iftrue->assert_valid();
    assert(iffalse != NULL);
    iffalse->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_goto::HIR_goto(Token_label_name* label_name)
{
    this->label_name = label_name;
}

HIR_goto::HIR_goto()
{
    this->label_name = 0;
}

void HIR_goto::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_goto::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_goto::classid()
{
    return ID;
}

bool HIR_goto::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_goto* that = dynamic_cast<HIR_goto*>(in);
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

bool HIR_goto::equals(HIR_node* in)
{
    HIR_goto* that = dynamic_cast<HIR_goto*>(in);
    if(that == NULL) return false;
    
    if(this->label_name == NULL || that->label_name == NULL)
    {
    	if(this->label_name != NULL || that->label_name != NULL)
    		return false;
    }
    else if(!this->label_name->equals(that->label_name))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_goto* HIR_goto::clone()
{
    Token_label_name* label_name = this->label_name ? this->label_name->clone() : NULL;
    HIR_goto* clone = new HIR_goto(label_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_goto::assert_valid()
{
    assert(label_name != NULL);
    label_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_label::HIR_label(Token_label_name* label_name)
{
    this->label_name = label_name;
}

HIR_label::HIR_label()
{
    this->label_name = 0;
}

void HIR_label::visit(HIR_visitor* visitor)
{
    visitor->visit_statement(this);
}

void HIR_label::transform_children(HIR_transform* transform)
{
    transform->children_statement(this);
}

int HIR_label::classid()
{
    return ID;
}

bool HIR_label::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_label* that = dynamic_cast<HIR_label*>(in);
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

bool HIR_label::equals(HIR_node* in)
{
    HIR_label* that = dynamic_cast<HIR_label*>(in);
    if(that == NULL) return false;
    
    if(this->label_name == NULL || that->label_name == NULL)
    {
    	if(this->label_name != NULL || that->label_name != NULL)
    		return false;
    }
    else if(!this->label_name->equals(that->label_name))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_label* HIR_label::clone()
{
    Token_label_name* label_name = this->label_name ? this->label_name->clone() : NULL;
    HIR_label* clone = new HIR_label(label_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_label::assert_valid()
{
    assert(label_name != NULL);
    label_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_expr::HIR_expr()
{
}

HIR_reflection::HIR_reflection(Token_variable_name* variable_name)
{
    this->variable_name = variable_name;
}

HIR_reflection::HIR_reflection()
{
    this->variable_name = 0;
}

void HIR_reflection::visit(HIR_visitor* visitor)
{
    visitor->visit_class_name(this);
}

void HIR_reflection::transform_children(HIR_transform* transform)
{
    transform->children_class_name(this);
}

int HIR_reflection::classid()
{
    return ID;
}

bool HIR_reflection::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_reflection* that = dynamic_cast<HIR_reflection*>(in);
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

bool HIR_reflection::equals(HIR_node* in)
{
    HIR_reflection* that = dynamic_cast<HIR_reflection*>(in);
    if(that == NULL) return false;
    
    if(this->variable_name == NULL || that->variable_name == NULL)
    {
    	if(this->variable_name != NULL || that->variable_name != NULL)
    		return false;
    }
    else if(!this->variable_name->equals(that->variable_name))
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_reflection* HIR_reflection::clone()
{
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    HIR_reflection* clone = new HIR_reflection(variable_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_reflection::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

Token_class_name::Token_class_name(String* value)
{
    this->value = value;
}

Token_class_name::Token_class_name()
{
    this->value = 0;
}

void Token_class_name::visit(HIR_visitor* visitor)
{
    visitor->visit_class_name(this);
}

void Token_class_name::transform_children(HIR_transform* transform)
{
    transform->children_class_name(this);
}

String* Token_class_name::get_value_as_string()
{
    return value;
}

int Token_class_name::classid()
{
    return ID;
}

bool Token_class_name::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_class_name* that = dynamic_cast<Token_class_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_class_name::equals(HIR_node* in)
{
    Token_class_name* that = dynamic_cast<Token_class_name*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_class_name* Token_class_name::clone()
{
    String* value = new String(*this->value);
    Token_class_name* clone = new Token_class_name(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_class_name::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_interface_name::Token_interface_name(String* value)
{
    this->value = value;
}

Token_interface_name::Token_interface_name()
{
    this->value = 0;
}

void Token_interface_name::visit(HIR_visitor* visitor)
{
    visitor->visit_interface_name(this);
}

void Token_interface_name::transform_children(HIR_transform* transform)
{
    transform->children_interface_name(this);
}

String* Token_interface_name::get_value_as_string()
{
    return value;
}

int Token_interface_name::classid()
{
    return ID;
}

bool Token_interface_name::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_interface_name* that = dynamic_cast<Token_interface_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_interface_name::equals(HIR_node* in)
{
    Token_interface_name* that = dynamic_cast<Token_interface_name*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_interface_name* Token_interface_name::clone()
{
    String* value = new String(*this->value);
    Token_interface_name* clone = new Token_interface_name(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_interface_name::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_method_name::Token_method_name(String* value)
{
    this->value = value;
}

Token_method_name::Token_method_name()
{
    this->value = 0;
}

void Token_method_name::visit(HIR_visitor* visitor)
{
    visitor->visit_method_name(this);
}

void Token_method_name::transform_children(HIR_transform* transform)
{
    transform->children_method_name(this);
}

String* Token_method_name::get_value_as_string()
{
    return value;
}

int Token_method_name::classid()
{
    return ID;
}

bool Token_method_name::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_method_name* that = dynamic_cast<Token_method_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_method_name::equals(HIR_node* in)
{
    Token_method_name* that = dynamic_cast<Token_method_name*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_method_name* Token_method_name::clone()
{
    String* value = new String(*this->value);
    Token_method_name* clone = new Token_method_name(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_method_name::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_variable_name::Token_variable_name(String* value)
{
    this->value = value;
}

Token_variable_name::Token_variable_name()
{
    this->value = 0;
}

void Token_variable_name::visit(HIR_visitor* visitor)
{
    visitor->visit_variable_name(this);
}

void Token_variable_name::transform_children(HIR_transform* transform)
{
    transform->children_variable_name(this);
}

String* Token_variable_name::get_value_as_string()
{
    return value;
}

int Token_variable_name::classid()
{
    return ID;
}

bool Token_variable_name::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_variable_name* that = dynamic_cast<Token_variable_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_variable_name::equals(HIR_node* in)
{
    Token_variable_name* that = dynamic_cast<Token_variable_name*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_variable_name* Token_variable_name::clone()
{
    String* value = new String(*this->value);
    Token_variable_name* clone = new Token_variable_name(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_variable_name::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_label_name::Token_label_name(String* value)
{
    this->value = value;
}

Token_label_name::Token_label_name()
{
    this->value = 0;
}

void Token_label_name::visit(HIR_visitor* visitor)
{
    visitor->visit_label_name(this);
}

void Token_label_name::transform_children(HIR_transform* transform)
{
    transform->children_label_name(this);
}

String* Token_label_name::get_value_as_string()
{
    return value;
}

int Token_label_name::classid()
{
    return ID;
}

bool Token_label_name::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_label_name* that = dynamic_cast<Token_label_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_label_name::equals(HIR_node* in)
{
    Token_label_name* that = dynamic_cast<Token_label_name*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_label_name* Token_label_name::clone()
{
    String* value = new String(*this->value);
    Token_label_name* clone = new Token_label_name(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_label_name::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_cast::Token_cast(String* value)
{
    this->value = value;
}

Token_cast::Token_cast()
{
    this->value = 0;
}

void Token_cast::visit(HIR_visitor* visitor)
{
    visitor->visit_cast(this);
}

void Token_cast::transform_children(HIR_transform* transform)
{
    transform->children_cast(this);
}

String* Token_cast::get_value_as_string()
{
    return value;
}

int Token_cast::classid()
{
    return ID;
}

bool Token_cast::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_cast* that = dynamic_cast<Token_cast*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_cast::equals(HIR_node* in)
{
    Token_cast* that = dynamic_cast<Token_cast*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_cast* Token_cast::clone()
{
    String* value = new String(*this->value);
    Token_cast* clone = new Token_cast(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_cast::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_op::Token_op(String* value)
{
    this->value = value;
}

Token_op::Token_op()
{
    this->value = 0;
}

void Token_op::visit(HIR_visitor* visitor)
{
    visitor->visit_op(this);
}

void Token_op::transform_children(HIR_transform* transform)
{
    transform->children_op(this);
}

String* Token_op::get_value_as_string()
{
    return value;
}

int Token_op::classid()
{
    return ID;
}

bool Token_op::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_op* that = dynamic_cast<Token_op*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_op::equals(HIR_node* in)
{
    Token_op* that = dynamic_cast<Token_op*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_op* Token_op::clone()
{
    String* value = new String(*this->value);
    Token_op* clone = new Token_op(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_op::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

Token_constant_name::Token_constant_name(String* value)
{
    this->value = value;
}

Token_constant_name::Token_constant_name()
{
    this->value = 0;
}

void Token_constant_name::visit(HIR_visitor* visitor)
{
    visitor->visit_constant_name(this);
}

void Token_constant_name::transform_children(HIR_transform* transform)
{
    transform->children_constant_name(this);
}

String* Token_constant_name::get_value_as_string()
{
    return value;
}

int Token_constant_name::classid()
{
    return ID;
}

bool Token_constant_name::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_constant_name* that = dynamic_cast<Token_constant_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_constant_name::equals(HIR_node* in)
{
    Token_constant_name* that = dynamic_cast<Token_constant_name*>(in);
    if(that == NULL) return false;
    
    if(this->value == NULL || that->value == NULL)
    {
    	if(this->value != NULL || that->value != NULL)
    		return false;
    }
    else if(*this->value != *that->value)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_constant_name* Token_constant_name::clone()
{
    String* value = new String(*this->value);
    Token_constant_name* clone = new Token_constant_name(value);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_constant_name::assert_valid()
{
    assert(value != NULL);
    HIR_node::assert_mixin_valid();
}

HIR_literal::HIR_literal()
{
}

HIR_assignment::HIR_assignment(HIR_variable* variable, bool is_ref, HIR_expr* expr)
{
    this->variable = variable;
    this->is_ref = is_ref;
    this->expr = expr;
}

HIR_assignment::HIR_assignment()
{
    this->variable = 0;
    this->is_ref = 0;
    this->expr = 0;
}

void HIR_assignment::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_assignment::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_assignment::classid()
{
    return ID;
}

bool HIR_assignment::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_assignment* that = dynamic_cast<HIR_assignment*>(in);
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

bool HIR_assignment::equals(HIR_node* in)
{
    HIR_assignment* that = dynamic_cast<HIR_assignment*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_assignment* HIR_assignment::clone()
{
    HIR_variable* variable = this->variable ? this->variable->clone() : NULL;
    bool is_ref = this->is_ref;
    HIR_expr* expr = this->expr ? this->expr->clone() : NULL;
    HIR_assignment* clone = new HIR_assignment(variable, is_ref, expr);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_assignment::assert_valid()
{
    assert(variable != NULL);
    variable->assert_valid();
    assert(expr != NULL);
    expr->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_cast::HIR_cast(Token_cast* cast, Token_variable_name* variable_name)
{
    this->cast = cast;
    this->variable_name = variable_name;
}

HIR_cast::HIR_cast()
{
    this->cast = 0;
    this->variable_name = 0;
}

void HIR_cast::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_cast::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_cast::classid()
{
    return ID;
}

bool HIR_cast::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_cast* that = dynamic_cast<HIR_cast*>(in);
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

bool HIR_cast::equals(HIR_node* in)
{
    HIR_cast* that = dynamic_cast<HIR_cast*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_cast* HIR_cast::clone()
{
    Token_cast* cast = this->cast ? this->cast->clone() : NULL;
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    HIR_cast* clone = new HIR_cast(cast, variable_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_cast::assert_valid()
{
    assert(cast != NULL);
    cast->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_cast::HIR_cast(const char* cast, Token_variable_name* variable_name)
{
    {
		this->cast = new Token_cast(new String(cast));
		this->variable_name = variable_name;
	}
}

HIR_unary_op::HIR_unary_op(Token_op* op, Token_variable_name* variable_name)
{
    this->op = op;
    this->variable_name = variable_name;
}

HIR_unary_op::HIR_unary_op()
{
    this->op = 0;
    this->variable_name = 0;
}

void HIR_unary_op::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_unary_op::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_unary_op::classid()
{
    return ID;
}

bool HIR_unary_op::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_unary_op* that = dynamic_cast<HIR_unary_op*>(in);
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

bool HIR_unary_op::equals(HIR_node* in)
{
    HIR_unary_op* that = dynamic_cast<HIR_unary_op*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_unary_op* HIR_unary_op::clone()
{
    Token_op* op = this->op ? this->op->clone() : NULL;
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    HIR_unary_op* clone = new HIR_unary_op(op, variable_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_unary_op::assert_valid()
{
    assert(op != NULL);
    op->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_unary_op::HIR_unary_op(Token_variable_name* variable_name, const char* op)
{
    {
		this->variable_name = variable_name;
		this->op = new Token_op(new String(op));
	}
}

HIR_bin_op::HIR_bin_op(Token_variable_name* left, Token_op* op, Token_variable_name* right)
{
    this->left = left;
    this->op = op;
    this->right = right;
}

HIR_bin_op::HIR_bin_op()
{
    this->left = 0;
    this->op = 0;
    this->right = 0;
}

void HIR_bin_op::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_bin_op::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_bin_op::classid()
{
    return ID;
}

bool HIR_bin_op::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_bin_op* that = dynamic_cast<HIR_bin_op*>(in);
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

bool HIR_bin_op::equals(HIR_node* in)
{
    HIR_bin_op* that = dynamic_cast<HIR_bin_op*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_bin_op* HIR_bin_op::clone()
{
    Token_variable_name* left = this->left ? this->left->clone() : NULL;
    Token_op* op = this->op ? this->op->clone() : NULL;
    Token_variable_name* right = this->right ? this->right->clone() : NULL;
    HIR_bin_op* clone = new HIR_bin_op(left, op, right);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_bin_op::assert_valid()
{
    assert(left != NULL);
    left->assert_valid();
    assert(op != NULL);
    op->assert_valid();
    assert(right != NULL);
    right->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_bin_op::HIR_bin_op(Token_variable_name* left, Token_variable_name* right, const char* op)
{
    {
		this->left = left;
		this->op = new Token_op(new String(op));
		this->right = right;
	}
}

HIR_constant::HIR_constant(Token_class_name* class_name, Token_constant_name* constant_name)
{
    this->class_name = class_name;
    this->constant_name = constant_name;
}

HIR_constant::HIR_constant()
{
    this->class_name = 0;
    this->constant_name = 0;
}

void HIR_constant::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_constant::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_constant::classid()
{
    return ID;
}

bool HIR_constant::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_constant* that = dynamic_cast<HIR_constant*>(in);
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

bool HIR_constant::equals(HIR_node* in)
{
    HIR_constant* that = dynamic_cast<HIR_constant*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_constant* HIR_constant::clone()
{
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Token_constant_name* constant_name = this->constant_name ? this->constant_name->clone() : NULL;
    HIR_constant* clone = new HIR_constant(class_name, constant_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_constant::assert_valid()
{
    if(class_name != NULL) class_name->assert_valid();
    assert(constant_name != NULL);
    constant_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_instanceof::HIR_instanceof(Token_variable_name* variable_name, HIR_class_name* class_name)
{
    this->variable_name = variable_name;
    this->class_name = class_name;
}

HIR_instanceof::HIR_instanceof()
{
    this->variable_name = 0;
    this->class_name = 0;
}

void HIR_instanceof::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_instanceof::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_instanceof::classid()
{
    return ID;
}

bool HIR_instanceof::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_instanceof* that = dynamic_cast<HIR_instanceof*>(in);
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

bool HIR_instanceof::equals(HIR_node* in)
{
    HIR_instanceof* that = dynamic_cast<HIR_instanceof*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_instanceof* HIR_instanceof::clone()
{
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    HIR_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    HIR_instanceof* clone = new HIR_instanceof(variable_name, class_name);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_instanceof::assert_valid()
{
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(class_name != NULL);
    class_name->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_variable::HIR_variable(HIR_target* target, HIR_variable_name* variable_name, List<HIR_expr*>* array_indices)
{
    this->target = target;
    this->variable_name = variable_name;
    this->array_indices = array_indices;
}

HIR_variable::HIR_variable()
{
    this->target = 0;
    this->variable_name = 0;
    this->array_indices = 0;
}

void HIR_variable::visit(HIR_visitor* visitor)
{
    visitor->visit_variable(this);
}

void HIR_variable::transform_children(HIR_transform* transform)
{
    transform->children_variable(this);
}

int HIR_variable::classid()
{
    return ID;
}

bool HIR_variable::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_variable* that = dynamic_cast<HIR_variable*>(in);
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
    	List<HIR_expr*>::const_iterator i, j;
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

bool HIR_variable::equals(HIR_node* in)
{
    HIR_variable* that = dynamic_cast<HIR_variable*>(in);
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
    	List<HIR_expr*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_variable* HIR_variable::clone()
{
    HIR_target* target = this->target ? this->target->clone() : NULL;
    HIR_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    List<HIR_expr*>* array_indices = NULL;
    if(this->array_indices != NULL)
    {
    	List<HIR_expr*>::const_iterator i;
    	array_indices = new List<HIR_expr*>;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    		array_indices->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_variable* clone = new HIR_variable(target, variable_name, array_indices);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_variable::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(variable_name != NULL);
    variable_name->assert_valid();
    assert(array_indices != NULL);
    {
    	List<HIR_expr*>::const_iterator i;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    	{
    		if(*i != NULL) (*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_variable::HIR_variable(HIR_variable_name* name)
{
    {
		this->target = NULL;
		this->variable_name = name;
		this->array_indices = new List<HIR_expr*>;
	}
}

HIR_pre_op::HIR_pre_op(Token_op* op, HIR_variable* variable)
{
    this->op = op;
    this->variable = variable;
}

HIR_pre_op::HIR_pre_op()
{
    this->op = 0;
    this->variable = 0;
}

void HIR_pre_op::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_pre_op::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_pre_op::classid()
{
    return ID;
}

bool HIR_pre_op::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_pre_op* that = dynamic_cast<HIR_pre_op*>(in);
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

bool HIR_pre_op::equals(HIR_node* in)
{
    HIR_pre_op* that = dynamic_cast<HIR_pre_op*>(in);
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_pre_op* HIR_pre_op::clone()
{
    Token_op* op = this->op ? this->op->clone() : NULL;
    HIR_variable* variable = this->variable ? this->variable->clone() : NULL;
    HIR_pre_op* clone = new HIR_pre_op(op, variable);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_pre_op::assert_valid()
{
    assert(op != NULL);
    op->assert_valid();
    assert(variable != NULL);
    variable->assert_valid();
    HIR_node::assert_mixin_valid();
}

HIR_pre_op::HIR_pre_op(HIR_variable* var, const char* op)
{
    {
		this->variable = var;
		this->op = new Token_op(new String(op));
	}
}

HIR_array::HIR_array(List<HIR_array_elem*>* array_elems)
{
    this->array_elems = array_elems;
}

HIR_array::HIR_array()
{
    this->array_elems = 0;
}

void HIR_array::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_array::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_array::classid()
{
    return ID;
}

bool HIR_array::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_array* that = dynamic_cast<HIR_array*>(in);
    if(that == NULL) return false;
    
    if(this->array_elems != NULL && that->array_elems != NULL)
    {
    	List<HIR_array_elem*>::const_iterator i, j;
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

bool HIR_array::equals(HIR_node* in)
{
    HIR_array* that = dynamic_cast<HIR_array*>(in);
    if(that == NULL) return false;
    
    if(this->array_elems == NULL || that->array_elems == NULL)
    {
    	if(this->array_elems != NULL || that->array_elems != NULL)
    		return false;
    }
    else
    {
    	List<HIR_array_elem*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_array* HIR_array::clone()
{
    List<HIR_array_elem*>* array_elems = NULL;
    if(this->array_elems != NULL)
    {
    	List<HIR_array_elem*>::const_iterator i;
    	array_elems = new List<HIR_array_elem*>;
    	for(i = this->array_elems->begin(); i != this->array_elems->end(); i++)
    		array_elems->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_array* clone = new HIR_array(array_elems);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_array::assert_valid()
{
    assert(array_elems != NULL);
    {
    	List<HIR_array_elem*>::const_iterator i;
    	for(i = this->array_elems->begin(); i != this->array_elems->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_method_invocation::HIR_method_invocation(HIR_target* target, HIR_method_name* method_name, List<HIR_actual_parameter*>* actual_parameters)
{
    this->target = target;
    this->method_name = method_name;
    this->actual_parameters = actual_parameters;
}

HIR_method_invocation::HIR_method_invocation()
{
    this->target = 0;
    this->method_name = 0;
    this->actual_parameters = 0;
}

void HIR_method_invocation::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_method_invocation::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_method_invocation::classid()
{
    return ID;
}

bool HIR_method_invocation::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_method_invocation* that = dynamic_cast<HIR_method_invocation*>(in);
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
    	List<HIR_actual_parameter*>::const_iterator i, j;
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

bool HIR_method_invocation::equals(HIR_node* in)
{
    HIR_method_invocation* that = dynamic_cast<HIR_method_invocation*>(in);
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
    	List<HIR_actual_parameter*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_method_invocation* HIR_method_invocation::clone()
{
    HIR_target* target = this->target ? this->target->clone() : NULL;
    HIR_method_name* method_name = this->method_name ? this->method_name->clone() : NULL;
    List<HIR_actual_parameter*>* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	List<HIR_actual_parameter*>::const_iterator i;
    	actual_parameters = new List<HIR_actual_parameter*>;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_method_invocation* clone = new HIR_method_invocation(target, method_name, actual_parameters);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_method_invocation::assert_valid()
{
    if(target != NULL) target->assert_valid();
    assert(method_name != NULL);
    method_name->assert_valid();
    assert(actual_parameters != NULL);
    {
    	List<HIR_actual_parameter*>::const_iterator i;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

HIR_method_invocation::HIR_method_invocation(const char* name, HIR_expr* arg)
{
    { 
		this->target = NULL;
		this->method_name = new Token_method_name(new String(name));
		this->actual_parameters = new List<HIR_actual_parameter*>;
		this->actual_parameters->push_back(new HIR_actual_parameter(false, arg));
	}
}

HIR_method_invocation::HIR_method_invocation(Token_method_name* name, HIR_expr* arg)
{
    { 
		this->target = NULL;
		this->method_name = name; 
		this->actual_parameters = new List<HIR_actual_parameter*>;
		this->actual_parameters->push_back(new HIR_actual_parameter(false, arg));
	}
}

HIR_new::HIR_new(HIR_class_name* class_name, List<HIR_actual_parameter*>* actual_parameters)
{
    this->class_name = class_name;
    this->actual_parameters = actual_parameters;
}

HIR_new::HIR_new()
{
    this->class_name = 0;
    this->actual_parameters = 0;
}

void HIR_new::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void HIR_new::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

int HIR_new::classid()
{
    return ID;
}

bool HIR_new::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    HIR_new* that = dynamic_cast<HIR_new*>(in);
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
    	List<HIR_actual_parameter*>::const_iterator i, j;
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

bool HIR_new::equals(HIR_node* in)
{
    HIR_new* that = dynamic_cast<HIR_new*>(in);
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
    	List<HIR_actual_parameter*>::const_iterator i, j;
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
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

HIR_new* HIR_new::clone()
{
    HIR_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    List<HIR_actual_parameter*>* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	List<HIR_actual_parameter*>::const_iterator i;
    	actual_parameters = new List<HIR_actual_parameter*>;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    HIR_new* clone = new HIR_new(class_name, actual_parameters);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void HIR_new::assert_valid()
{
    assert(class_name != NULL);
    class_name->assert_valid();
    assert(actual_parameters != NULL);
    {
    	List<HIR_actual_parameter*>::const_iterator i;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    	{
    		assert(*i != NULL);
    		(*i)->assert_valid();
    	}
    }
    HIR_node::assert_mixin_valid();
}

Token_int::Token_int(long value, String* source_rep)
{
    this->value = value;
    this->source_rep = source_rep;
}

Token_int::Token_int()
{
    this->value = 0;
    this->source_rep = 0;
}

void Token_int::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_int::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

String* Token_int::get_source_rep()
{
    return source_rep;
}

int Token_int::classid()
{
    return ID;
}

bool Token_int::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_int* that = dynamic_cast<Token_int*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    
    if(this->source_rep != NULL && that->source_rep != NULL)
    	return (*this->source_rep == *that->source_rep);
    else
    	return true;
}

bool Token_int::match_value(Token_int* that)
{
    return true;
}

bool Token_int::equals(HIR_node* in)
{
    Token_int* that = dynamic_cast<Token_int*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    if(this->source_rep == NULL || that->source_rep == NULL)
    {
    	if(this->source_rep != NULL || that->source_rep != NULL)
    		return false;
    }
    else if(*this->source_rep != *that->source_rep)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

bool Token_int::equals_value(Token_int* that)
{
    return (this->value == that->value);
}

Token_int* Token_int::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_int* clone = new Token_int(value, source_rep);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

long Token_int::clone_value()
{
    return value;
}

void Token_int::assert_valid()
{
    assert_value_valid();
    HIR_node::assert_mixin_valid();
}

void Token_int::assert_value_valid()
{
    // Assume value is valid
}

//  Constructors can't call virtual functions, so we create a non-virtual to
//  do the work. This is then called by the virtual function, and is also
//  safely called from the constructor.
String* Token_int::_get_value_as_string()
{
    {
		std::ostringstream os;
		os << value;
		return new String(os.str());
	}
}

String* Token_int::get_value_as_string()
{
    {
		return _get_value_as_string ();
	}
}

Token_int::Token_int(int v)
{
    {
		value = v;
		source_rep = _get_value_as_string ();
	}
}

Token_real::Token_real(double value, String* source_rep)
{
    this->value = value;
    this->source_rep = source_rep;
}

Token_real::Token_real()
{
    this->value = 0;
    this->source_rep = 0;
}

void Token_real::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_real::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

String* Token_real::get_source_rep()
{
    return source_rep;
}

int Token_real::classid()
{
    return ID;
}

bool Token_real::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_real* that = dynamic_cast<Token_real*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    
    if(this->source_rep != NULL && that->source_rep != NULL)
    	return (*this->source_rep == *that->source_rep);
    else
    	return true;
}

bool Token_real::match_value(Token_real* that)
{
    return true;
}

bool Token_real::equals(HIR_node* in)
{
    Token_real* that = dynamic_cast<Token_real*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    if(this->source_rep == NULL || that->source_rep == NULL)
    {
    	if(this->source_rep != NULL || that->source_rep != NULL)
    		return false;
    }
    else if(*this->source_rep != *that->source_rep)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

bool Token_real::equals_value(Token_real* that)
{
    return (this->value == that->value);
}

Token_real* Token_real::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_real* clone = new Token_real(value, source_rep);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

double Token_real::clone_value()
{
    return value;
}

void Token_real::assert_valid()
{
    assert_value_valid();
    HIR_node::assert_mixin_valid();
}

void Token_real::assert_value_valid()
{
    // Assume value is valid
}

//  See comment in Token_int::_get_value_as_string ()
String* Token_real::_get_value_as_string()
{
    {
		std::ostringstream os;
		// setprecision(20) outputs as many digits as required, with
		// a maximum of 20
		os << setprecision(20) << value;
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

String* Token_real::get_value_as_string()
{
    {
		return _get_value_as_string ();
	}
}

Token_real::Token_real(double v)
{
    {
		value = v;
		source_rep = _get_value_as_string ();
	}
}

Token_string::Token_string(String* value, String* source_rep)
{
    this->value = value;
    this->source_rep = source_rep;
}

Token_string::Token_string()
{
    this->value = 0;
    this->source_rep = 0;
}

void Token_string::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_string::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

String* Token_string::get_source_rep()
{
    return source_rep;
}

int Token_string::classid()
{
    return ID;
}

bool Token_string::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_string* that = dynamic_cast<Token_string*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    
    if(this->source_rep != NULL && that->source_rep != NULL)
    	return (*this->source_rep == *that->source_rep);
    else
    	return true;
}

bool Token_string::match_value(Token_string* that)
{
    return true;
}

bool Token_string::equals(HIR_node* in)
{
    Token_string* that = dynamic_cast<Token_string*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    if(this->source_rep == NULL || that->source_rep == NULL)
    {
    	if(this->source_rep != NULL || that->source_rep != NULL)
    		return false;
    }
    else if(*this->source_rep != *that->source_rep)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

bool Token_string::equals_value(Token_string* that)
{
    return (*this->value == *that->value);
}

Token_string* Token_string::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_string* clone = new Token_string(value, source_rep);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_string::assert_valid()
{
    assert_value_valid();
    HIR_node::assert_mixin_valid();
}

void Token_string::assert_value_valid()
{
    // Assume value is valid
}

String* Token_string::get_value_as_string()
{
    {
		return value;
	}
}

bool Token_string::is_value_valid()
{
    {
		return value != NULL;
	}
}

String* Token_string::clone_value()
{
    {
		return value->clone();
	}
}

Token_string::Token_string(String* v)
{
    {
		value = v;
		source_rep = v;
	}
}

Token_bool::Token_bool(bool value, String* source_rep)
{
    this->value = value;
    this->source_rep = source_rep;
}

Token_bool::Token_bool()
{
    this->value = 0;
    this->source_rep = 0;
}

void Token_bool::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_bool::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

String* Token_bool::get_source_rep()
{
    return source_rep;
}

int Token_bool::classid()
{
    return ID;
}

bool Token_bool::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_bool* that = dynamic_cast<Token_bool*>(in);
    if(that == NULL) return false;
    
    if(!match_value(that))
    	return false;
    
    if(this->source_rep != NULL && that->source_rep != NULL)
    	return (*this->source_rep == *that->source_rep);
    else
    	return true;
}

bool Token_bool::match_value(Token_bool* that)
{
    return true;
}

bool Token_bool::equals(HIR_node* in)
{
    Token_bool* that = dynamic_cast<Token_bool*>(in);
    if(that == NULL) return false;
    
    if(!equals_value(that))
    	return false;
    
    if(this->source_rep == NULL || that->source_rep == NULL)
    {
    	if(this->source_rep != NULL || that->source_rep != NULL)
    		return false;
    }
    else if(*this->source_rep != *that->source_rep)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

bool Token_bool::equals_value(Token_bool* that)
{
    return (this->value == that->value);
}

Token_bool* Token_bool::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_bool* clone = new Token_bool(value, source_rep);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

bool Token_bool::clone_value()
{
    return value;
}

void Token_bool::assert_valid()
{
    assert_value_valid();
    HIR_node::assert_mixin_valid();
}

void Token_bool::assert_value_valid()
{
    // Assume value is valid
}

//  See comment in Token_int::_get_value_as_string ()
String* Token_bool::_get_value_as_string()
{
    {
		if(value)
			return new String("True");
		else
			return new String("False");
	}
}

String* Token_bool::get_value_as_string()
{
    {
		return _get_value_as_string ();
	}
}

Token_bool::Token_bool(bool v)
{
    {
		value = v;
		source_rep = _get_value_as_string ();
	}
}

Token_null::Token_null(String* source_rep)
{
    this->source_rep = source_rep;
}

void Token_null::visit(HIR_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_null::transform_children(HIR_transform* transform)
{
    transform->children_expr(this);
}

String* Token_null::get_source_rep()
{
    return source_rep;
}

int Token_null::classid()
{
    return ID;
}

bool Token_null::match(HIR_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_null* that = dynamic_cast<Token_null*>(in);
    if(that == NULL) return false;
    
    if(this->source_rep != NULL && that->source_rep != NULL)
    	return (*this->source_rep == *that->source_rep);
    else
    	return true;
}

bool Token_null::equals(HIR_node* in)
{
    Token_null* that = dynamic_cast<Token_null*>(in);
    if(that == NULL) return false;
    
    if(this->source_rep == NULL || that->source_rep == NULL)
    {
    	if(this->source_rep != NULL || that->source_rep != NULL)
    		return false;
    }
    else if(*this->source_rep != *that->source_rep)
    	return false;
    
    if(!HIR_node::is_mixin_equal(that)) return false;
    return true;
}

Token_null* Token_null::clone()
{
    String* source_rep = new String(*this->source_rep);
    Token_null* clone = new Token_null(source_rep);
    clone->HIR_node::clone_mixin_from(this);
    return clone;
}

void Token_null::assert_valid()
{
    HIR_node::assert_mixin_valid();
}

String* Token_null::get_value_as_string()
{
    {
		return new String("NULL");
	}
}

Token_null::Token_null()
{
    {
		source_rep = new String ("NULL");
	}
}

}

