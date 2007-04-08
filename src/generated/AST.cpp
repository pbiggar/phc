#include "AST.h"
#include "AST_transform.h"
#include "AST_visitor.h"

//  Return the line number of the node (or 0 if unknown)
int AST_node::get_line_number()
{
    #line 171 "src/generated_src/phc.tea"
{
		Integer* i = dynamic_cast<Integer*>(attrs->get("phc.line_number"));
		if(i != NULL)
			return i->value();
		else
			return 0;
	}
}

//  Return the filename of the node (or NULL if unknown)
String* AST_node::get_filename()
{
    #line 181 "src/generated_src/phc.tea"
{
		return dynamic_cast<String*>(attrs->get("phc.filename"));
	}
}

AST_node::AST_node()
{
    #line 186 "src/generated_src/phc.tea"
{
		// Constructor gets called because all classes inherit from
		// AST_node virtually; also, because maketea knows AST_node is
		// abstract, it won't add a constructor itself
		attrs = new AttrMap();
	}
}

void AST_node::clone_mixin_from(AST_node* in)
{
    #line 194 "src/generated_src/phc.tea"
{
		attrs = in->attrs->clone();
	}
}

AST_php_script::AST_php_script(List<AST_statement*>* statements)
{
    this->statements = statements;
}

AST_php_script::AST_php_script()
{
    this->statements = 0;
}

void AST_php_script::visit(AST_visitor* visitor)
{
    visitor->visit_php_script(this);
}

void AST_php_script::transform_children(AST_transform* transform)
{
    transform->children_php_script(this);
}

int AST_php_script::classid()
{
    return ID;
}

bool AST_php_script::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_php_script* that = dynamic_cast<AST_php_script*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_php_script::equals(AST_node* in)
{
    AST_php_script* that = dynamic_cast<AST_php_script*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	List<AST_statement*>::const_iterator i, j;
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

AST_php_script* AST_php_script::clone()
{
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_php_script* clone = new AST_php_script(statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_class_mod::AST_class_mod(bool is_abstract, bool is_final)
{
    this->is_abstract = is_abstract;
    this->is_final = is_final;
}

AST_class_mod::AST_class_mod()
{
    this->is_abstract = 0;
    this->is_final = 0;
}

void AST_class_mod::visit(AST_visitor* visitor)
{
    visitor->visit_class_mod(this);
}

void AST_class_mod::transform_children(AST_transform* transform)
{
    transform->children_class_mod(this);
}

int AST_class_mod::classid()
{
    return ID;
}

bool AST_class_mod::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_class_mod* that = dynamic_cast<AST_class_mod*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool AST_class_mod::equals(AST_node* in)
{
    AST_class_mod* that = dynamic_cast<AST_class_mod*>(in);
    if(that == NULL) return false;
    
    if(this->is_abstract != that->is_abstract)
    	return false;
    
    if(this->is_final != that->is_final)
    	return false;
    
    return true;
}

AST_class_mod* AST_class_mod::clone()
{
    bool is_abstract = this->is_abstract;
    bool is_final = this->is_final;
    AST_class_mod* clone = new AST_class_mod(is_abstract, is_final);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_signature::AST_signature(AST_method_mod* method_mod, bool is_ref, Token_method_name* method_name, List<AST_formal_parameter*>* formal_parameters)
{
    this->method_mod = method_mod;
    this->is_ref = is_ref;
    this->method_name = method_name;
    this->formal_parameters = formal_parameters;
}

AST_signature::AST_signature()
{
    this->method_mod = 0;
    this->is_ref = 0;
    this->method_name = 0;
    this->formal_parameters = 0;
}

void AST_signature::visit(AST_visitor* visitor)
{
    visitor->visit_signature(this);
}

void AST_signature::transform_children(AST_transform* transform)
{
    transform->children_signature(this);
}

int AST_signature::classid()
{
    return ID;
}

bool AST_signature::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_signature* that = dynamic_cast<AST_signature*>(in);
    if(that == NULL) return false;
    
    if(this->method_mod == NULL)
    {
    	if(that->method_mod != NULL && !that->method_mod->match(this->method_mod))
    		return false;
    }
    else if(!this->method_mod->match(that->method_mod))
    	return false;
    
    if(this->method_name == NULL)
    {
    	if(that->method_name != NULL && !that->method_name->match(this->method_name))
    		return false;
    }
    else if(!this->method_name->match(that->method_name))
    	return false;
    
    if(this->formal_parameters != NULL && that->formal_parameters != NULL)
    {
    	List<AST_formal_parameter*>::const_iterator i, j;
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

bool AST_signature::equals(AST_node* in)
{
    AST_signature* that = dynamic_cast<AST_signature*>(in);
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
    	List<AST_formal_parameter*>::const_iterator i, j;
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

AST_signature::AST_signature(const char* name)
{
    #line 220 "src/generated_src/phc.tea"
{
		this->method_mod = AST_method_mod::new_PUBLIC();
		this->is_ref = false;
		this->method_name = new Token_method_name(new String(name));
		this->formal_parameters = new List<AST_formal_parameter*>;
	}
}

AST_signature* AST_signature::clone()
{
    AST_method_mod* method_mod = this->method_mod ? this->method_mod->clone() : NULL;
    bool is_ref = this->is_ref;
    Token_method_name* method_name = this->method_name ? this->method_name->clone() : NULL;
    List<AST_formal_parameter*>* formal_parameters = NULL;
    if(this->formal_parameters != NULL)
    {
    	List<AST_formal_parameter*>::const_iterator i;
    	formal_parameters = new List<AST_formal_parameter*>;
    	for(i = this->formal_parameters->begin(); i != this->formal_parameters->end(); i++)
    		formal_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_signature* clone = new AST_signature(method_mod, is_ref, method_name, formal_parameters);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_method_mod::AST_method_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final)
{
    this->is_public = is_public;
    this->is_protected = is_protected;
    this->is_private = is_private;
    this->is_static = is_static;
    this->is_abstract = is_abstract;
    this->is_final = is_final;
}

void AST_method_mod::visit(AST_visitor* visitor)
{
    visitor->visit_method_mod(this);
}

void AST_method_mod::transform_children(AST_transform* transform)
{
    transform->children_method_mod(this);
}

int AST_method_mod::classid()
{
    return ID;
}

bool AST_method_mod::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_method_mod* that = dynamic_cast<AST_method_mod*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool AST_method_mod::equals(AST_node* in)
{
    AST_method_mod* that = dynamic_cast<AST_method_mod*>(in);
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

AST_method_mod::AST_method_mod()
{
    #line 232 "src/generated_src/phc.tea"
{
		is_public = false;
		is_protected = false;
		is_private = false;
		is_static = false;
		is_abstract = false;
		is_final = false;
	}
}

AST_method_mod::AST_method_mod(AST_method_mod* a, AST_method_mod* b)
{
    #line 242 "src/generated_src/phc.tea"
{
		this->is_public 		= a->is_public		|| b->is_public;
		this->is_protected	= a->is_protected	|| b->is_protected;
		this->is_private		= a->is_private	|| b->is_private;
		this->is_static		= a->is_static		|| b->is_static;
		this->is_abstract		= a->is_abstract	|| b->is_abstract;
		this->is_final			= a->is_final		|| b->is_final;
	}
}

AST_method_mod* AST_method_mod::new_PUBLIC()
{
    #line 252 "src/generated_src/phc.tea"
{
		return new AST_method_mod(true, false, false, false, false, false);		
	}
}

AST_method_mod* AST_method_mod::new_PROTECTED()
{
    #line 257 "src/generated_src/phc.tea"
{ 
		return new AST_method_mod(false, true, false, false, false, false);		
	}
}

AST_method_mod* AST_method_mod::new_PRIVATE()
{
    #line 262 "src/generated_src/phc.tea"
{ 
		return new AST_method_mod(false, false, true, false, false, false);		
	}
}

AST_method_mod* AST_method_mod::new_STATIC()
{
    #line 267 "src/generated_src/phc.tea"
{ 
		return new AST_method_mod(false, false, false, true, false, false);		
	}
}

AST_method_mod* AST_method_mod::new_ABSTRACT()
{
    #line 272 "src/generated_src/phc.tea"
{ 
		return new AST_method_mod(false, false, false, false, true, false);		
	}
}

AST_method_mod* AST_method_mod::new_FINAL()
{
    #line 277 "src/generated_src/phc.tea"
{ 
		return new AST_method_mod(false, false, false, false, false, true);		
	}
}

AST_method_mod* AST_method_mod::clone()
{
    bool is_public = this->is_public;
    bool is_protected = this->is_protected;
    bool is_private = this->is_private;
    bool is_static = this->is_static;
    bool is_abstract = this->is_abstract;
    bool is_final = this->is_final;
    AST_method_mod* clone = new AST_method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_formal_parameter::AST_formal_parameter(AST_type* type, bool is_ref, Token_variable_name* variable_name, AST_expr* expr)
{
    this->type = type;
    this->is_ref = is_ref;
    this->variable_name = variable_name;
    this->expr = expr;
}

AST_formal_parameter::AST_formal_parameter()
{
    this->type = 0;
    this->is_ref = 0;
    this->variable_name = 0;
    this->expr = 0;
}

void AST_formal_parameter::visit(AST_visitor* visitor)
{
    visitor->visit_formal_parameter(this);
}

void AST_formal_parameter::transform_children(AST_transform* transform)
{
    transform->children_formal_parameter(this);
}

int AST_formal_parameter::classid()
{
    return ID;
}

bool AST_formal_parameter::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_formal_parameter* that = dynamic_cast<AST_formal_parameter*>(in);
    if(that == NULL) return false;
    
    if(this->type == NULL)
    {
    	if(that->type != NULL && !that->type->match(this->type))
    		return false;
    }
    else if(!this->type->match(that->type))
    	return false;
    
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

bool AST_formal_parameter::equals(AST_node* in)
{
    AST_formal_parameter* that = dynamic_cast<AST_formal_parameter*>(in);
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
    
    return true;
}

AST_formal_parameter::AST_formal_parameter(AST_type* type, Token_variable_name* name)
{
    #line 376 "src/generated_src/phc.tea"
{
		this->type = type;
		this->is_ref = false;
		this->variable_name = name;
		this->expr = NULL;
	}
}

AST_formal_parameter::AST_formal_parameter(AST_type* type, bool is_ref, Token_variable_name* name)
{
    #line 384 "src/generated_src/phc.tea"
{ 
		this->type = type;
		this->is_ref = is_ref;
		this->variable_name = name;
		this->expr = NULL;
	}
}

AST_formal_parameter* AST_formal_parameter::clone()
{
    AST_type* type = this->type ? this->type->clone() : NULL;
    bool is_ref = this->is_ref;
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_formal_parameter* clone = new AST_formal_parameter(type, is_ref, variable_name, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_type::AST_type(bool is_array, Token_class_name* class_name)
{
    this->is_array = is_array;
    this->class_name = class_name;
}

AST_type::AST_type()
{
    this->is_array = 0;
    this->class_name = 0;
}

void AST_type::visit(AST_visitor* visitor)
{
    visitor->visit_type(this);
}

void AST_type::transform_children(AST_transform* transform)
{
    transform->children_type(this);
}

int AST_type::classid()
{
    return ID;
}

bool AST_type::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_type* that = dynamic_cast<AST_type*>(in);
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

bool AST_type::equals(AST_node* in)
{
    AST_type* that = dynamic_cast<AST_type*>(in);
    if(that == NULL) return false;
    
    if(this->is_array != that->is_array)
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

AST_type* AST_type::clone()
{
    bool is_array = this->is_array;
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    AST_type* clone = new AST_type(is_array, class_name);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_attr_mod::AST_attr_mod(bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const)
{
    this->is_public = is_public;
    this->is_protected = is_protected;
    this->is_private = is_private;
    this->is_static = is_static;
    this->is_const = is_const;
}

void AST_attr_mod::visit(AST_visitor* visitor)
{
    visitor->visit_attr_mod(this);
}

void AST_attr_mod::transform_children(AST_transform* transform)
{
    transform->children_attr_mod(this);
}

int AST_attr_mod::classid()
{
    return ID;
}

bool AST_attr_mod::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_attr_mod* that = dynamic_cast<AST_attr_mod*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool AST_attr_mod::equals(AST_node* in)
{
    AST_attr_mod* that = dynamic_cast<AST_attr_mod*>(in);
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

AST_attr_mod::AST_attr_mod()
{
    #line 396 "src/generated_src/phc.tea"
{
		is_public = false;
		is_protected = false;
		is_private = false;
		is_static = false;
		is_const = false;
	}
}

AST_attr_mod::AST_attr_mod(AST_method_mod* mm)
{
    #line 405 "src/generated_src/phc.tea"
{
		if(mm->is_final)
			phc_error(ERR_FINAL_VARS, mm->get_filename(), mm->get_line_number());

		this->is_public = mm->is_public;
		this->is_protected = mm->is_protected;
		this->is_private = mm->is_private;
		this->is_static = mm->is_static;
		this->is_const = false;
	}
}

AST_attr_mod* AST_attr_mod::new_PUBLIC()
{
    #line 417 "src/generated_src/phc.tea"
{
		return new AST_attr_mod(true, false, false, false, false);
	}
}

AST_attr_mod* AST_attr_mod::new_PROTECTED()
{
    #line 422 "src/generated_src/phc.tea"
{ 
		return new AST_attr_mod(false, true, false, false, false);
	}
}

AST_attr_mod* AST_attr_mod::new_PRIVATE()
{
    #line 427 "src/generated_src/phc.tea"
{
		return new AST_attr_mod(false, false, true, false, false);
	}
}

AST_attr_mod* AST_attr_mod::new_STATIC()
{
    #line 432 "src/generated_src/phc.tea"
{
		return new AST_attr_mod(false, false, false, true, false);
	}
}

AST_attr_mod* AST_attr_mod::new_CONST()
{
    #line 437 "src/generated_src/phc.tea"
{
		return new AST_attr_mod(false, false, false, false, true);
	}
}

AST_attr_mod* AST_attr_mod::clone()
{
    bool is_public = this->is_public;
    bool is_protected = this->is_protected;
    bool is_private = this->is_private;
    bool is_static = this->is_static;
    bool is_const = this->is_const;
    AST_attr_mod* clone = new AST_attr_mod(is_public, is_protected, is_private, is_static, is_const);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_directive::AST_directive(Token_directive_name* directive_name, AST_expr* expr)
{
    this->directive_name = directive_name;
    this->expr = expr;
}

AST_directive::AST_directive()
{
    this->directive_name = 0;
    this->expr = 0;
}

void AST_directive::visit(AST_visitor* visitor)
{
    visitor->visit_directive(this);
}

void AST_directive::transform_children(AST_transform* transform)
{
    transform->children_directive(this);
}

int AST_directive::classid()
{
    return ID;
}

bool AST_directive::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_directive* that = dynamic_cast<AST_directive*>(in);
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

bool AST_directive::equals(AST_node* in)
{
    AST_directive* that = dynamic_cast<AST_directive*>(in);
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
    
    return true;
}

AST_directive* AST_directive::clone()
{
    Token_directive_name* directive_name = this->directive_name ? this->directive_name->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_directive* clone = new AST_directive(directive_name, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_list_element::AST_list_element()
{
}

AST_variable_name::AST_variable_name()
{
}

AST_target::AST_target()
{
}

AST_array_elem::AST_array_elem(AST_expr* key, bool is_ref, AST_expr* val)
{
    this->key = key;
    this->is_ref = is_ref;
    this->val = val;
}

AST_array_elem::AST_array_elem()
{
    this->key = 0;
    this->is_ref = 0;
    this->val = 0;
}

void AST_array_elem::visit(AST_visitor* visitor)
{
    visitor->visit_array_elem(this);
}

void AST_array_elem::transform_children(AST_transform* transform)
{
    transform->children_array_elem(this);
}

int AST_array_elem::classid()
{
    return ID;
}

bool AST_array_elem::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_array_elem* that = dynamic_cast<AST_array_elem*>(in);
    if(that == NULL) return false;
    
    if(this->key == NULL)
    {
    	if(that->key != NULL && !that->key->match(this->key))
    		return false;
    }
    else if(!this->key->match(that->key))
    	return false;
    
    if(this->val == NULL)
    {
    	if(that->val != NULL && !that->val->match(this->val))
    		return false;
    }
    else if(!this->val->match(that->val))
    	return false;
    
    return true;
}

bool AST_array_elem::equals(AST_node* in)
{
    AST_array_elem* that = dynamic_cast<AST_array_elem*>(in);
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

AST_array_elem* AST_array_elem::clone()
{
    AST_expr* key = this->key ? this->key->clone() : NULL;
    bool is_ref = this->is_ref;
    AST_expr* val = this->val ? this->val->clone() : NULL;
    AST_array_elem* clone = new AST_array_elem(key, is_ref, val);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_method_name::AST_method_name()
{
}

AST_actual_parameter::AST_actual_parameter(bool is_ref, AST_expr* expr)
{
    this->is_ref = is_ref;
    this->expr = expr;
}

AST_actual_parameter::AST_actual_parameter()
{
    this->is_ref = 0;
    this->expr = 0;
}

void AST_actual_parameter::visit(AST_visitor* visitor)
{
    visitor->visit_actual_parameter(this);
}

void AST_actual_parameter::transform_children(AST_transform* transform)
{
    transform->children_actual_parameter(this);
}

int AST_actual_parameter::classid()
{
    return ID;
}

bool AST_actual_parameter::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_actual_parameter* that = dynamic_cast<AST_actual_parameter*>(in);
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

bool AST_actual_parameter::equals(AST_node* in)
{
    AST_actual_parameter* that = dynamic_cast<AST_actual_parameter*>(in);
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
    
    return true;
}

AST_actual_parameter* AST_actual_parameter::clone()
{
    bool is_ref = this->is_ref;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_actual_parameter* clone = new AST_actual_parameter(is_ref, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_class_name::AST_class_name()
{
}

AST_commented_node::AST_commented_node()
{
    #line 203 "src/generated_src/phc.tea"
{
		attrs->set("phc.comments", new List<String*>);
	}
}

//  Return the comments associated with the node
List<String*>* AST_commented_node::get_comments()
{
    #line 209 "src/generated_src/phc.tea"
{
		List<String*>* comments = dynamic_cast<List<String*>*>(attrs->get("phc.comments"));
		assert(comments);
		return comments;
	}
}

AST_identifier::AST_identifier()
{
}

AST_statement::AST_statement()
{
}

AST_member::AST_member()
{
}

AST_switch_case::AST_switch_case(AST_expr* expr, List<AST_statement*>* statements)
{
    this->expr = expr;
    this->statements = statements;
}

AST_switch_case::AST_switch_case()
{
    this->expr = 0;
    this->statements = 0;
}

void AST_switch_case::visit(AST_visitor* visitor)
{
    visitor->visit_switch_case(this);
}

void AST_switch_case::transform_children(AST_transform* transform)
{
    transform->children_switch_case(this);
}

int AST_switch_case::classid()
{
    return ID;
}

bool AST_switch_case::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_switch_case* that = dynamic_cast<AST_switch_case*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_switch_case::equals(AST_node* in)
{
    AST_switch_case* that = dynamic_cast<AST_switch_case*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_switch_case* AST_switch_case::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_switch_case* clone = new AST_switch_case(expr, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_catch::AST_catch(Token_class_name* class_name, Token_variable_name* variable_name, List<AST_statement*>* statements)
{
    this->class_name = class_name;
    this->variable_name = variable_name;
    this->statements = statements;
}

AST_catch::AST_catch()
{
    this->class_name = 0;
    this->variable_name = 0;
    this->statements = 0;
}

void AST_catch::visit(AST_visitor* visitor)
{
    visitor->visit_catch(this);
}

void AST_catch::transform_children(AST_transform* transform)
{
    transform->children_catch(this);
}

int AST_catch::classid()
{
    return ID;
}

bool AST_catch::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_catch* that = dynamic_cast<AST_catch*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_catch::equals(AST_node* in)
{
    AST_catch* that = dynamic_cast<AST_catch*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_catch* AST_catch::clone()
{
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_catch* clone = new AST_catch(class_name, variable_name, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_expr::AST_expr()
{
    #line 487 "src/generated_src/phc.tea"
{
		attrs->set("phc.unparser.needs_brackets", new Boolean(false));
	}
}

AST_list_elements::AST_list_elements(List<AST_list_element*>* list_elements)
{
    this->list_elements = list_elements;
}

AST_list_elements::AST_list_elements()
{
    this->list_elements = 0;
}

void AST_list_elements::visit(AST_visitor* visitor)
{
    visitor->visit_list_elements(this);
}

void AST_list_elements::transform_children(AST_transform* transform)
{
    transform->children_list_elements(this);
}

int AST_list_elements::classid()
{
    return ID;
}

bool AST_list_elements::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_list_elements* that = dynamic_cast<AST_list_elements*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements != NULL && that->list_elements != NULL)
    {
    	List<AST_list_element*>::const_iterator i, j;
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

bool AST_list_elements::equals(AST_node* in)
{
    AST_list_elements* that = dynamic_cast<AST_list_elements*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements == NULL || that->list_elements == NULL)
    {
    	if(this->list_elements != NULL || that->list_elements != NULL)
    		return false;
    }
    else
    {
    	List<AST_list_element*>::const_iterator i, j;
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
    
    return true;
}

AST_list_elements* AST_list_elements::clone()
{
    List<AST_list_element*>* list_elements = NULL;
    if(this->list_elements != NULL)
    {
    	List<AST_list_element*>::const_iterator i;
    	list_elements = new List<AST_list_element*>;
    	for(i = this->list_elements->begin(); i != this->list_elements->end(); i++)
    		list_elements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_list_elements* clone = new AST_list_elements(list_elements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_reflection::AST_reflection(AST_expr* expr)
{
    this->expr = expr;
}

AST_reflection::AST_reflection()
{
    this->expr = 0;
}

void AST_reflection::visit(AST_visitor* visitor)
{
    visitor->visit_variable_name(this);
}

void AST_reflection::transform_children(AST_transform* transform)
{
    transform->children_variable_name(this);
}

int AST_reflection::classid()
{
    return ID;
}

bool AST_reflection::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_reflection* that = dynamic_cast<AST_reflection*>(in);
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

bool AST_reflection::equals(AST_node* in)
{
    AST_reflection* that = dynamic_cast<AST_reflection*>(in);
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

AST_reflection* AST_reflection::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_reflection* clone = new AST_reflection(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_class_name::Token_class_name(String* value)
{
    this->value = value;
}

Token_class_name::Token_class_name()
{
    this->value = 0;
}

void Token_class_name::visit(AST_visitor* visitor)
{
    visitor->visit_class_name(this);
}

void Token_class_name::transform_children(AST_transform* transform)
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

bool Token_class_name::match(AST_node* in)
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

bool Token_class_name::equals(AST_node* in)
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
    
    return true;
}

Token_class_name* Token_class_name::clone()
{
    String* value = new String(*this->value);
    Token_class_name* clone = new Token_class_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_interface_name::Token_interface_name(String* value)
{
    this->value = value;
}

Token_interface_name::Token_interface_name()
{
    this->value = 0;
}

void Token_interface_name::visit(AST_visitor* visitor)
{
    visitor->visit_interface_name(this);
}

void Token_interface_name::transform_children(AST_transform* transform)
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

bool Token_interface_name::match(AST_node* in)
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

bool Token_interface_name::equals(AST_node* in)
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
    
    return true;
}

Token_interface_name* Token_interface_name::clone()
{
    String* value = new String(*this->value);
    Token_interface_name* clone = new Token_interface_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_method_name::Token_method_name(String* value)
{
    this->value = value;
}

Token_method_name::Token_method_name()
{
    this->value = 0;
}

void Token_method_name::visit(AST_visitor* visitor)
{
    visitor->visit_method_name(this);
}

void Token_method_name::transform_children(AST_transform* transform)
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

bool Token_method_name::match(AST_node* in)
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

bool Token_method_name::equals(AST_node* in)
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
    
    return true;
}

Token_method_name* Token_method_name::clone()
{
    String* value = new String(*this->value);
    Token_method_name* clone = new Token_method_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_variable_name::Token_variable_name(String* value)
{
    this->value = value;
}

Token_variable_name::Token_variable_name()
{
    this->value = 0;
}

void Token_variable_name::visit(AST_visitor* visitor)
{
    visitor->visit_variable_name(this);
}

void Token_variable_name::transform_children(AST_transform* transform)
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

bool Token_variable_name::match(AST_node* in)
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

bool Token_variable_name::equals(AST_node* in)
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
    
    return true;
}

Token_variable_name* Token_variable_name::clone()
{
    String* value = new String(*this->value);
    Token_variable_name* clone = new Token_variable_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_directive_name::Token_directive_name(String* value)
{
    this->value = value;
}

Token_directive_name::Token_directive_name()
{
    this->value = 0;
}

void Token_directive_name::visit(AST_visitor* visitor)
{
    visitor->visit_directive_name(this);
}

void Token_directive_name::transform_children(AST_transform* transform)
{
    transform->children_directive_name(this);
}

String* Token_directive_name::get_value_as_string()
{
    return value;
}

int Token_directive_name::classid()
{
    return ID;
}

bool Token_directive_name::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    Token_directive_name* that = dynamic_cast<Token_directive_name*>(in);
    if(that == NULL) return false;
    
    if(this->value != NULL && that->value != NULL)
    	return (*this->value == *that->value);
    else
    	return true;
}

bool Token_directive_name::equals(AST_node* in)
{
    Token_directive_name* that = dynamic_cast<Token_directive_name*>(in);
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

Token_directive_name* Token_directive_name::clone()
{
    String* value = new String(*this->value);
    Token_directive_name* clone = new Token_directive_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_label_name::Token_label_name(String* value)
{
    this->value = value;
}

Token_label_name::Token_label_name()
{
    this->value = 0;
}

void Token_label_name::visit(AST_visitor* visitor)
{
    visitor->visit_label_name(this);
}

void Token_label_name::transform_children(AST_transform* transform)
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

bool Token_label_name::match(AST_node* in)
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

bool Token_label_name::equals(AST_node* in)
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
    
    return true;
}

Token_label_name* Token_label_name::clone()
{
    String* value = new String(*this->value);
    Token_label_name* clone = new Token_label_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_cast::Token_cast(String* value)
{
    this->value = value;
}

Token_cast::Token_cast()
{
    this->value = 0;
}

void Token_cast::visit(AST_visitor* visitor)
{
    visitor->visit_cast(this);
}

void Token_cast::transform_children(AST_transform* transform)
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

bool Token_cast::match(AST_node* in)
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

bool Token_cast::equals(AST_node* in)
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
    
    return true;
}

Token_cast* Token_cast::clone()
{
    String* value = new String(*this->value);
    Token_cast* clone = new Token_cast(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_op::Token_op(String* value)
{
    this->value = value;
}

Token_op::Token_op()
{
    this->value = 0;
}

void Token_op::visit(AST_visitor* visitor)
{
    visitor->visit_op(this);
}

void Token_op::transform_children(AST_transform* transform)
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

bool Token_op::match(AST_node* in)
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

bool Token_op::equals(AST_node* in)
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
    
    return true;
}

Token_op* Token_op::clone()
{
    String* value = new String(*this->value);
    Token_op* clone = new Token_op(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_constant_name::Token_constant_name(String* value)
{
    this->value = value;
}

Token_constant_name::Token_constant_name()
{
    this->value = 0;
}

void Token_constant_name::visit(AST_visitor* visitor)
{
    visitor->visit_constant_name(this);
}

void Token_constant_name::transform_children(AST_transform* transform)
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

bool Token_constant_name::match(AST_node* in)
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

bool Token_constant_name::equals(AST_node* in)
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
    
    return true;
}

Token_constant_name* Token_constant_name::clone()
{
    String* value = new String(*this->value);
    Token_constant_name* clone = new Token_constant_name(value);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_class_def::AST_class_def(AST_class_mod* class_mod, Token_class_name* class_name, Token_class_name* extends, List<Token_interface_name*>* implements, List<AST_member*>* members)
{
    this->class_mod = class_mod;
    this->class_name = class_name;
    this->extends = extends;
    this->implements = implements;
    this->members = members;
}

AST_class_def::AST_class_def()
{
    this->class_mod = 0;
    this->class_name = 0;
    this->extends = 0;
    this->implements = 0;
    this->members = 0;
}

void AST_class_def::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_class_def::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_class_def::classid()
{
    return ID;
}

bool AST_class_def::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_class_def* that = dynamic_cast<AST_class_def*>(in);
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
    	List<AST_member*>::const_iterator i, j;
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

bool AST_class_def::equals(AST_node* in)
{
    AST_class_def* that = dynamic_cast<AST_class_def*>(in);
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
    	List<AST_member*>::const_iterator i, j;
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

AST_class_def::AST_class_def(AST_class_mod* mod)
{
    #line 286 "src/generated_src/phc.tea"
{
		this->class_mod = mod;
		this->class_name = NULL;
		this->extends = NULL;
		this->implements = new List<Token_interface_name*>;
		this->members = new List<AST_member*>;
	}
}

AST_class_def::AST_class_def(char* name)
{
    #line 295 "src/generated_src/phc.tea"
{
		this->class_mod = new AST_class_mod(false, false);
		this->class_name = new Token_class_name(new String(name));
		this->extends = NULL;
		this->implements = new List<Token_interface_name*>;
		this->members = new List<AST_member*>;
	}
}

void AST_class_def::add_member(AST_member* member)
{
    #line 304 "src/generated_src/phc.tea"
{
		this->members->push_back(member);
	}
}

//  Returns NULL if the method could not be found
AST_method* AST_class_def::get_method(const char* name)
{
    #line 310 "src/generated_src/phc.tea"
{
		List<AST_member*>::const_iterator i;
		for(i = members->begin(); i != members->end(); i++)
		#line 313 "src/generated_src/phc.tea"
{
			AST_method* method = dynamic_cast<AST_method*>(*i);
			if(method && *method->signature->method_name->value == name)
				return method;
		}

		return NULL;
	}
}

AST_class_def* AST_class_def::clone()
{
    AST_class_mod* class_mod = this->class_mod ? this->class_mod->clone() : NULL;
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
    List<AST_member*>* members = NULL;
    if(this->members != NULL)
    {
    	List<AST_member*>::const_iterator i;
    	members = new List<AST_member*>;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    		members->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_class_def* clone = new AST_class_def(class_mod, class_name, extends, implements, members);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_interface_def::AST_interface_def(Token_interface_name* interface_name, List<Token_interface_name*>* extends, List<AST_member*>* members)
{
    this->interface_name = interface_name;
    this->extends = extends;
    this->members = members;
}

AST_interface_def::AST_interface_def()
{
    this->interface_name = 0;
    this->extends = 0;
    this->members = 0;
}

void AST_interface_def::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_interface_def::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_interface_def::classid()
{
    return ID;
}

bool AST_interface_def::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_interface_def* that = dynamic_cast<AST_interface_def*>(in);
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
    	List<AST_member*>::const_iterator i, j;
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

bool AST_interface_def::equals(AST_node* in)
{
    AST_interface_def* that = dynamic_cast<AST_interface_def*>(in);
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
    	List<AST_member*>::const_iterator i, j;
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

AST_interface_def* AST_interface_def::clone()
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
    List<AST_member*>* members = NULL;
    if(this->members != NULL)
    {
    	List<AST_member*>::const_iterator i;
    	members = new List<AST_member*>;
    	for(i = this->members->begin(); i != this->members->end(); i++)
    		members->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_interface_def* clone = new AST_interface_def(interface_name, extends, members);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_method::AST_method(AST_signature* signature, List<AST_statement*>* statements)
{
    this->signature = signature;
    this->statements = statements;
}

AST_method::AST_method()
{
    this->signature = 0;
    this->statements = 0;
}

void AST_method::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_method::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_method::classid()
{
    return ID;
}

bool AST_method::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_method* that = dynamic_cast<AST_method*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_method::equals(AST_node* in)
{
    AST_method* that = dynamic_cast<AST_method*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_method* AST_method::clone()
{
    AST_signature* signature = this->signature ? this->signature->clone() : NULL;
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_method* clone = new AST_method(signature, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_attribute::AST_attribute(AST_attr_mod* attr_mod, Token_variable_name* variable_name, AST_expr* expr)
{
    this->attr_mod = attr_mod;
    this->variable_name = variable_name;
    this->expr = expr;
}

AST_attribute::AST_attribute()
{
    this->attr_mod = 0;
    this->variable_name = 0;
    this->expr = 0;
}

void AST_attribute::visit(AST_visitor* visitor)
{
    visitor->visit_member(this);
}

void AST_attribute::transform_children(AST_transform* transform)
{
    transform->children_member(this);
}

int AST_attribute::classid()
{
    return ID;
}

bool AST_attribute::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_attribute* that = dynamic_cast<AST_attribute*>(in);
    if(that == NULL) return false;
    
    if(this->attr_mod == NULL)
    {
    	if(that->attr_mod != NULL && !that->attr_mod->match(this->attr_mod))
    		return false;
    }
    else if(!this->attr_mod->match(that->attr_mod))
    	return false;
    
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

bool AST_attribute::equals(AST_node* in)
{
    AST_attribute* that = dynamic_cast<AST_attribute*>(in);
    if(that == NULL) return false;
    
    if(this->attr_mod == NULL || that->attr_mod == NULL)
    {
    	if(this->attr_mod != NULL || that->attr_mod != NULL)
    		return false;
    }
    else if(!this->attr_mod->equals(that->attr_mod))
    	return false;
    
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
    
    return true;
}

AST_attribute* AST_attribute::clone()
{
    AST_attr_mod* attr_mod = this->attr_mod ? this->attr_mod->clone() : NULL;
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_attribute* clone = new AST_attribute(attr_mod, variable_name, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_if::AST_if(AST_expr* expr, List<AST_statement*>* iftrue, List<AST_statement*>* iffalse)
{
    this->expr = expr;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

AST_if::AST_if()
{
    this->expr = 0;
    this->iftrue = 0;
    this->iffalse = 0;
}

void AST_if::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_if::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_if::classid()
{
    return ID;
}

bool AST_if::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_if* that = dynamic_cast<AST_if*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_if::equals(AST_node* in)
{
    AST_if* that = dynamic_cast<AST_if*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_if* AST_if::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    List<AST_statement*>* iftrue = NULL;
    if(this->iftrue != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	iftrue = new List<AST_statement*>;
    	for(i = this->iftrue->begin(); i != this->iftrue->end(); i++)
    		iftrue->push_back(*i ? (*i)->clone() : NULL);
    }
    List<AST_statement*>* iffalse = NULL;
    if(this->iffalse != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	iffalse = new List<AST_statement*>;
    	for(i = this->iffalse->begin(); i != this->iffalse->end(); i++)
    		iffalse->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_if* clone = new AST_if(expr, iftrue, iffalse);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_while::AST_while(AST_expr* expr, List<AST_statement*>* statements)
{
    this->expr = expr;
    this->statements = statements;
}

AST_while::AST_while()
{
    this->expr = 0;
    this->statements = 0;
}

void AST_while::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_while::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_while::classid()
{
    return ID;
}

bool AST_while::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_while* that = dynamic_cast<AST_while*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_while::equals(AST_node* in)
{
    AST_while* that = dynamic_cast<AST_while*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_while* AST_while::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_while* clone = new AST_while(expr, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_do::AST_do(List<AST_statement*>* statements, AST_expr* expr)
{
    this->statements = statements;
    this->expr = expr;
}

AST_do::AST_do()
{
    this->statements = 0;
    this->expr = 0;
}

void AST_do::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_do::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_do::classid()
{
    return ID;
}

bool AST_do::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_do* that = dynamic_cast<AST_do*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_do::equals(AST_node* in)
{
    AST_do* that = dynamic_cast<AST_do*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	List<AST_statement*>::const_iterator i, j;
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
    
    return true;
}

AST_do* AST_do::clone()
{
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_do* clone = new AST_do(statements, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_for::AST_for(AST_expr* init, AST_expr* cond, AST_expr* incr, List<AST_statement*>* statements)
{
    this->init = init;
    this->cond = cond;
    this->incr = incr;
    this->statements = statements;
}

AST_for::AST_for()
{
    this->init = 0;
    this->cond = 0;
    this->incr = 0;
    this->statements = 0;
}

void AST_for::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_for::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_for::classid()
{
    return ID;
}

bool AST_for::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_for* that = dynamic_cast<AST_for*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_for::equals(AST_node* in)
{
    AST_for* that = dynamic_cast<AST_for*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_for* AST_for::clone()
{
    AST_expr* init = this->init ? this->init->clone() : NULL;
    AST_expr* cond = this->cond ? this->cond->clone() : NULL;
    AST_expr* incr = this->incr ? this->incr->clone() : NULL;
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_for* clone = new AST_for(init, cond, incr, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_foreach::AST_foreach(AST_expr* expr, AST_variable* key, bool is_ref, AST_variable* val, List<AST_statement*>* statements)
{
    this->expr = expr;
    this->key = key;
    this->is_ref = is_ref;
    this->val = val;
    this->statements = statements;
}

AST_foreach::AST_foreach()
{
    this->expr = 0;
    this->key = 0;
    this->is_ref = 0;
    this->val = 0;
    this->statements = 0;
}

void AST_foreach::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_foreach::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_foreach::classid()
{
    return ID;
}

bool AST_foreach::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_foreach* that = dynamic_cast<AST_foreach*>(in);
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
    
    if(this->val == NULL)
    {
    	if(that->val != NULL && !that->val->match(this->val))
    		return false;
    }
    else if(!this->val->match(that->val))
    	return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_foreach::equals(AST_node* in)
{
    AST_foreach* that = dynamic_cast<AST_foreach*>(in);
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_foreach* AST_foreach::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_variable* key = this->key ? this->key->clone() : NULL;
    bool is_ref = this->is_ref;
    AST_variable* val = this->val ? this->val->clone() : NULL;
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_foreach* clone = new AST_foreach(expr, key, is_ref, val, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_switch::AST_switch(AST_expr* expr, List<AST_switch_case*>* switch_cases)
{
    this->expr = expr;
    this->switch_cases = switch_cases;
}

AST_switch::AST_switch()
{
    this->expr = 0;
    this->switch_cases = 0;
}

void AST_switch::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_switch::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_switch::classid()
{
    return ID;
}

bool AST_switch::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_switch* that = dynamic_cast<AST_switch*>(in);
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
    	List<AST_switch_case*>::const_iterator i, j;
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

bool AST_switch::equals(AST_node* in)
{
    AST_switch* that = dynamic_cast<AST_switch*>(in);
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
    	List<AST_switch_case*>::const_iterator i, j;
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
    
    return true;
}

AST_switch* AST_switch::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    List<AST_switch_case*>* switch_cases = NULL;
    if(this->switch_cases != NULL)
    {
    	List<AST_switch_case*>::const_iterator i;
    	switch_cases = new List<AST_switch_case*>;
    	for(i = this->switch_cases->begin(); i != this->switch_cases->end(); i++)
    		switch_cases->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_switch* clone = new AST_switch(expr, switch_cases);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_break::AST_break(AST_expr* expr)
{
    this->expr = expr;
}

AST_break::AST_break()
{
    this->expr = 0;
}

void AST_break::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_break::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_break::classid()
{
    return ID;
}

bool AST_break::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_break* that = dynamic_cast<AST_break*>(in);
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

bool AST_break::equals(AST_node* in)
{
    AST_break* that = dynamic_cast<AST_break*>(in);
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

AST_break* AST_break::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_break* clone = new AST_break(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_continue::AST_continue(AST_expr* expr)
{
    this->expr = expr;
}

AST_continue::AST_continue()
{
    this->expr = 0;
}

void AST_continue::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_continue::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_continue::classid()
{
    return ID;
}

bool AST_continue::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_continue* that = dynamic_cast<AST_continue*>(in);
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

bool AST_continue::equals(AST_node* in)
{
    AST_continue* that = dynamic_cast<AST_continue*>(in);
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

AST_continue* AST_continue::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_continue* clone = new AST_continue(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_return::AST_return(AST_expr* expr)
{
    this->expr = expr;
}

AST_return::AST_return()
{
    this->expr = 0;
}

void AST_return::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_return::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_return::classid()
{
    return ID;
}

bool AST_return::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_return* that = dynamic_cast<AST_return*>(in);
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

bool AST_return::equals(AST_node* in)
{
    AST_return* that = dynamic_cast<AST_return*>(in);
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

AST_return* AST_return::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_return* clone = new AST_return(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_static_declaration::AST_static_declaration(Token_variable_name* variable_name, AST_expr* expr)
{
    this->variable_name = variable_name;
    this->expr = expr;
}

AST_static_declaration::AST_static_declaration()
{
    this->variable_name = 0;
    this->expr = 0;
}

void AST_static_declaration::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_static_declaration::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_static_declaration::classid()
{
    return ID;
}

bool AST_static_declaration::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_static_declaration* that = dynamic_cast<AST_static_declaration*>(in);
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

bool AST_static_declaration::equals(AST_node* in)
{
    AST_static_declaration* that = dynamic_cast<AST_static_declaration*>(in);
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
    
    return true;
}

AST_static_declaration* AST_static_declaration::clone()
{
    Token_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_static_declaration* clone = new AST_static_declaration(variable_name, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_unset::AST_unset(AST_variable* variable)
{
    this->variable = variable;
}

AST_unset::AST_unset()
{
    this->variable = 0;
}

void AST_unset::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_unset::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_unset::classid()
{
    return ID;
}

bool AST_unset::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_unset* that = dynamic_cast<AST_unset*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL)
    {
    	if(that->variable != NULL && !that->variable->match(this->variable))
    		return false;
    }
    else if(!this->variable->match(that->variable))
    	return false;
    
    return true;
}

bool AST_unset::equals(AST_node* in)
{
    AST_unset* that = dynamic_cast<AST_unset*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL || that->variable == NULL)
    {
    	if(this->variable != NULL || that->variable != NULL)
    		return false;
    }
    else if(!this->variable->equals(that->variable))
    	return false;
    
    return true;
}

AST_unset* AST_unset::clone()
{
    AST_variable* variable = this->variable ? this->variable->clone() : NULL;
    AST_unset* clone = new AST_unset(variable);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_declare::AST_declare(List<AST_directive*>* directives, List<AST_statement*>* statements)
{
    this->directives = directives;
    this->statements = statements;
}

AST_declare::AST_declare()
{
    this->directives = 0;
    this->statements = 0;
}

void AST_declare::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_declare::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_declare::classid()
{
    return ID;
}

bool AST_declare::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_declare* that = dynamic_cast<AST_declare*>(in);
    if(that == NULL) return false;
    
    if(this->directives != NULL && that->directives != NULL)
    {
    	List<AST_directive*>::const_iterator i, j;
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
    	List<AST_statement*>::const_iterator i, j;
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

bool AST_declare::equals(AST_node* in)
{
    AST_declare* that = dynamic_cast<AST_declare*>(in);
    if(that == NULL) return false;
    
    if(this->directives == NULL || that->directives == NULL)
    {
    	if(this->directives != NULL || that->directives != NULL)
    		return false;
    }
    else
    {
    	List<AST_directive*>::const_iterator i, j;
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
    	List<AST_statement*>::const_iterator i, j;
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

AST_declare* AST_declare::clone()
{
    List<AST_directive*>* directives = NULL;
    if(this->directives != NULL)
    {
    	List<AST_directive*>::const_iterator i;
    	directives = new List<AST_directive*>;
    	for(i = this->directives->begin(); i != this->directives->end(); i++)
    		directives->push_back(*i ? (*i)->clone() : NULL);
    }
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_declare* clone = new AST_declare(directives, statements);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_try::AST_try(List<AST_statement*>* statements, List<AST_catch*>* catches)
{
    this->statements = statements;
    this->catches = catches;
}

AST_try::AST_try()
{
    this->statements = 0;
    this->catches = 0;
}

void AST_try::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_try::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_try::classid()
{
    return ID;
}

bool AST_try::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_try* that = dynamic_cast<AST_try*>(in);
    if(that == NULL) return false;
    
    if(this->statements != NULL && that->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i, j;
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
    	List<AST_catch*>::const_iterator i, j;
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

bool AST_try::equals(AST_node* in)
{
    AST_try* that = dynamic_cast<AST_try*>(in);
    if(that == NULL) return false;
    
    if(this->statements == NULL || that->statements == NULL)
    {
    	if(this->statements != NULL || that->statements != NULL)
    		return false;
    }
    else
    {
    	List<AST_statement*>::const_iterator i, j;
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
    	List<AST_catch*>::const_iterator i, j;
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

AST_try* AST_try::clone()
{
    List<AST_statement*>* statements = NULL;
    if(this->statements != NULL)
    {
    	List<AST_statement*>::const_iterator i;
    	statements = new List<AST_statement*>;
    	for(i = this->statements->begin(); i != this->statements->end(); i++)
    		statements->push_back(*i ? (*i)->clone() : NULL);
    }
    List<AST_catch*>* catches = NULL;
    if(this->catches != NULL)
    {
    	List<AST_catch*>::const_iterator i;
    	catches = new List<AST_catch*>;
    	for(i = this->catches->begin(); i != this->catches->end(); i++)
    		catches->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_try* clone = new AST_try(statements, catches);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_throw::AST_throw(AST_expr* expr)
{
    this->expr = expr;
}

AST_throw::AST_throw()
{
    this->expr = 0;
}

void AST_throw::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_throw::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_throw::classid()
{
    return ID;
}

bool AST_throw::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_throw* that = dynamic_cast<AST_throw*>(in);
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

bool AST_throw::equals(AST_node* in)
{
    AST_throw* that = dynamic_cast<AST_throw*>(in);
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

AST_throw* AST_throw::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_throw* clone = new AST_throw(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_eval_expr::AST_eval_expr(AST_expr* expr)
{
    this->expr = expr;
}

AST_eval_expr::AST_eval_expr()
{
    this->expr = 0;
}

void AST_eval_expr::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_eval_expr::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_eval_expr::classid()
{
    return ID;
}

bool AST_eval_expr::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_eval_expr* that = dynamic_cast<AST_eval_expr*>(in);
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

bool AST_eval_expr::equals(AST_node* in)
{
    AST_eval_expr* that = dynamic_cast<AST_eval_expr*>(in);
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

AST_eval_expr* AST_eval_expr::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_eval_expr* clone = new AST_eval_expr(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_nop::AST_nop()
{
}

void AST_nop::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_nop::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_nop::classid()
{
    return ID;
}

bool AST_nop::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_nop* that = dynamic_cast<AST_nop*>(in);
    if(that == NULL) return false;
    
    return true;
}

bool AST_nop::equals(AST_node* in)
{
    AST_nop* that = dynamic_cast<AST_nop*>(in);
    if(that == NULL) return false;
    
    return true;
}

AST_nop* AST_nop::clone()
{
    AST_nop* clone = new AST_nop();
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_goto::AST_goto(Token_label_name* label_name)
{
    this->label_name = label_name;
}

AST_goto::AST_goto()
{
    this->label_name = 0;
}

void AST_goto::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_goto::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_goto::classid()
{
    return ID;
}

bool AST_goto::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_goto* that = dynamic_cast<AST_goto*>(in);
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

bool AST_goto::equals(AST_node* in)
{
    AST_goto* that = dynamic_cast<AST_goto*>(in);
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

AST_goto* AST_goto::clone()
{
    Token_label_name* label_name = this->label_name ? this->label_name->clone() : NULL;
    AST_goto* clone = new AST_goto(label_name);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_label::AST_label(Token_label_name* label_name)
{
    this->label_name = label_name;
}

AST_label::AST_label()
{
    this->label_name = 0;
}

void AST_label::visit(AST_visitor* visitor)
{
    visitor->visit_statement(this);
}

void AST_label::transform_children(AST_transform* transform)
{
    transform->children_statement(this);
}

int AST_label::classid()
{
    return ID;
}

bool AST_label::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_label* that = dynamic_cast<AST_label*>(in);
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

bool AST_label::equals(AST_node* in)
{
    AST_label* that = dynamic_cast<AST_label*>(in);
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

AST_label* AST_label::clone()
{
    Token_label_name* label_name = this->label_name ? this->label_name->clone() : NULL;
    AST_label* clone = new AST_label(label_name);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_literal::AST_literal()
{
}

AST_assignment::AST_assignment(AST_variable* variable, bool is_ref, AST_expr* expr)
{
    this->variable = variable;
    this->is_ref = is_ref;
    this->expr = expr;
}

AST_assignment::AST_assignment()
{
    this->variable = 0;
    this->is_ref = 0;
    this->expr = 0;
}

void AST_assignment::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_assignment::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_assignment::classid()
{
    return ID;
}

bool AST_assignment::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_assignment* that = dynamic_cast<AST_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->variable == NULL)
    {
    	if(that->variable != NULL && !that->variable->match(this->variable))
    		return false;
    }
    else if(!this->variable->match(that->variable))
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

bool AST_assignment::equals(AST_node* in)
{
    AST_assignment* that = dynamic_cast<AST_assignment*>(in);
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
    
    return true;
}

AST_assignment* AST_assignment::clone()
{
    AST_variable* variable = this->variable ? this->variable->clone() : NULL;
    bool is_ref = this->is_ref;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_assignment* clone = new AST_assignment(variable, is_ref, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_list_assignment::AST_list_assignment(AST_list_elements* list_elements, AST_expr* expr)
{
    this->list_elements = list_elements;
    this->expr = expr;
}

AST_list_assignment::AST_list_assignment()
{
    this->list_elements = 0;
    this->expr = 0;
}

void AST_list_assignment::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_list_assignment::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_list_assignment::classid()
{
    return ID;
}

bool AST_list_assignment::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_list_assignment* that = dynamic_cast<AST_list_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements == NULL)
    {
    	if(that->list_elements != NULL && !that->list_elements->match(this->list_elements))
    		return false;
    }
    else if(!this->list_elements->match(that->list_elements))
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

bool AST_list_assignment::equals(AST_node* in)
{
    AST_list_assignment* that = dynamic_cast<AST_list_assignment*>(in);
    if(that == NULL) return false;
    
    if(this->list_elements == NULL || that->list_elements == NULL)
    {
    	if(this->list_elements != NULL || that->list_elements != NULL)
    		return false;
    }
    else if(!this->list_elements->equals(that->list_elements))
    	return false;
    
    if(this->expr == NULL || that->expr == NULL)
    {
    	if(this->expr != NULL || that->expr != NULL)
    		return false;
    }
    else if(!this->expr->equals(that->expr))
    	return false;
    
    return true;
}

AST_list_assignment* AST_list_assignment::clone()
{
    AST_list_elements* list_elements = this->list_elements ? this->list_elements->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_list_assignment* clone = new AST_list_assignment(list_elements, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_cast::AST_cast(Token_cast* cast, AST_expr* expr)
{
    this->cast = cast;
    this->expr = expr;
}

AST_cast::AST_cast()
{
    this->cast = 0;
    this->expr = 0;
}

void AST_cast::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_cast::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_cast::classid()
{
    return ID;
}

bool AST_cast::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_cast* that = dynamic_cast<AST_cast*>(in);
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

bool AST_cast::equals(AST_node* in)
{
    AST_cast* that = dynamic_cast<AST_cast*>(in);
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
    
    return true;
}

AST_cast::AST_cast(char* cast, AST_expr* expr)
{
    #line 496 "src/generated_src/phc.tea"
{
		this->cast = new Token_cast(new String(cast));
		this->expr = expr;
	}
}

AST_cast* AST_cast::clone()
{
    Token_cast* cast = this->cast ? this->cast->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_cast* clone = new AST_cast(cast, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_unary_op::AST_unary_op(Token_op* op, AST_expr* expr)
{
    this->op = op;
    this->expr = expr;
}

AST_unary_op::AST_unary_op()
{
    this->op = 0;
    this->expr = 0;
}

void AST_unary_op::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_unary_op::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_unary_op::classid()
{
    return ID;
}

bool AST_unary_op::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_unary_op* that = dynamic_cast<AST_unary_op*>(in);
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

bool AST_unary_op::equals(AST_node* in)
{
    AST_unary_op* that = dynamic_cast<AST_unary_op*>(in);
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
    
    return true;
}

AST_unary_op::AST_unary_op(AST_expr* expr, char* op)
{
    #line 477 "src/generated_src/phc.tea"
{
		this->expr = expr;
		this->op = new Token_op(new String(op));
	}
}

AST_unary_op* AST_unary_op::clone()
{
    Token_op* op = this->op ? this->op->clone() : NULL;
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_unary_op* clone = new AST_unary_op(op, expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_bin_op::AST_bin_op(AST_expr* left, Token_op* op, AST_expr* right)
{
    this->left = left;
    this->op = op;
    this->right = right;
}

AST_bin_op::AST_bin_op()
{
    this->left = 0;
    this->op = 0;
    this->right = 0;
}

void AST_bin_op::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_bin_op::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_bin_op::classid()
{
    return ID;
}

bool AST_bin_op::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_bin_op* that = dynamic_cast<AST_bin_op*>(in);
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

bool AST_bin_op::equals(AST_node* in)
{
    AST_bin_op* that = dynamic_cast<AST_bin_op*>(in);
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

AST_bin_op::AST_bin_op(AST_expr* left, AST_expr* right, char* op)
{
    #line 446 "src/generated_src/phc.tea"
{
		this->left = left;
		this->op = new Token_op(new String(op));
		this->right = right;
	}
}

AST_bin_op* AST_bin_op::clone()
{
    AST_expr* left = this->left ? this->left->clone() : NULL;
    Token_op* op = this->op ? this->op->clone() : NULL;
    AST_expr* right = this->right ? this->right->clone() : NULL;
    AST_bin_op* clone = new AST_bin_op(left, op, right);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_conditional_expr::AST_conditional_expr(AST_expr* cond, AST_expr* iftrue, AST_expr* iffalse)
{
    this->cond = cond;
    this->iftrue = iftrue;
    this->iffalse = iffalse;
}

AST_conditional_expr::AST_conditional_expr()
{
    this->cond = 0;
    this->iftrue = 0;
    this->iffalse = 0;
}

void AST_conditional_expr::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_conditional_expr::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_conditional_expr::classid()
{
    return ID;
}

bool AST_conditional_expr::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_conditional_expr* that = dynamic_cast<AST_conditional_expr*>(in);
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

bool AST_conditional_expr::equals(AST_node* in)
{
    AST_conditional_expr* that = dynamic_cast<AST_conditional_expr*>(in);
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
    
    return true;
}

AST_conditional_expr* AST_conditional_expr::clone()
{
    AST_expr* cond = this->cond ? this->cond->clone() : NULL;
    AST_expr* iftrue = this->iftrue ? this->iftrue->clone() : NULL;
    AST_expr* iffalse = this->iffalse ? this->iffalse->clone() : NULL;
    AST_conditional_expr* clone = new AST_conditional_expr(cond, iftrue, iffalse);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_ignore_errors::AST_ignore_errors(AST_expr* expr)
{
    this->expr = expr;
}

AST_ignore_errors::AST_ignore_errors()
{
    this->expr = 0;
}

void AST_ignore_errors::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_ignore_errors::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_ignore_errors::classid()
{
    return ID;
}

bool AST_ignore_errors::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_ignore_errors* that = dynamic_cast<AST_ignore_errors*>(in);
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

bool AST_ignore_errors::equals(AST_node* in)
{
    AST_ignore_errors* that = dynamic_cast<AST_ignore_errors*>(in);
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

AST_ignore_errors* AST_ignore_errors::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_ignore_errors* clone = new AST_ignore_errors(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_constant::AST_constant(Token_class_name* class_name, Token_constant_name* constant_name)
{
    this->class_name = class_name;
    this->constant_name = constant_name;
}

AST_constant::AST_constant()
{
    this->class_name = 0;
    this->constant_name = 0;
}

void AST_constant::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_constant::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_constant::classid()
{
    return ID;
}

bool AST_constant::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_constant* that = dynamic_cast<AST_constant*>(in);
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

bool AST_constant::equals(AST_node* in)
{
    AST_constant* that = dynamic_cast<AST_constant*>(in);
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

AST_constant::AST_constant(char* class_name, Token_constant_name* constant_name)
{
    #line 506 "src/generated_src/phc.tea"
{
		this->class_name = new Token_class_name(new String(class_name));
		this->constant_name = constant_name;
	}
}

AST_constant* AST_constant::clone()
{
    Token_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    Token_constant_name* constant_name = this->constant_name ? this->constant_name->clone() : NULL;
    AST_constant* clone = new AST_constant(class_name, constant_name);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_instanceof::AST_instanceof(AST_expr* expr, AST_class_name* class_name)
{
    this->expr = expr;
    this->class_name = class_name;
}

AST_instanceof::AST_instanceof()
{
    this->expr = 0;
    this->class_name = 0;
}

void AST_instanceof::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_instanceof::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_instanceof::classid()
{
    return ID;
}

bool AST_instanceof::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_instanceof* that = dynamic_cast<AST_instanceof*>(in);
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

bool AST_instanceof::equals(AST_node* in)
{
    AST_instanceof* that = dynamic_cast<AST_instanceof*>(in);
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
    
    return true;
}

AST_instanceof* AST_instanceof::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    AST_instanceof* clone = new AST_instanceof(expr, class_name);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_variable::AST_variable(AST_target* target, AST_variable_name* variable_name, List<AST_expr*>* array_indices, AST_expr* string_index)
{
    this->target = target;
    this->variable_name = variable_name;
    this->array_indices = array_indices;
    this->string_index = string_index;
}

AST_variable::AST_variable()
{
    this->target = 0;
    this->variable_name = 0;
    this->array_indices = 0;
    this->string_index = 0;
}

void AST_variable::visit(AST_visitor* visitor)
{
    visitor->visit_variable(this);
}

void AST_variable::transform_children(AST_transform* transform)
{
    transform->children_variable(this);
}

int AST_variable::classid()
{
    return ID;
}

bool AST_variable::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_variable* that = dynamic_cast<AST_variable*>(in);
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
    	List<AST_expr*>::const_iterator i, j;
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
    
    if(this->string_index == NULL)
    {
    	if(that->string_index != NULL && !that->string_index->match(this->string_index))
    		return false;
    }
    else if(!this->string_index->match(that->string_index))
    	return false;
    
    return true;
}

bool AST_variable::equals(AST_node* in)
{
    AST_variable* that = dynamic_cast<AST_variable*>(in);
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
    	List<AST_expr*>::const_iterator i, j;
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
    
    if(this->string_index == NULL || that->string_index == NULL)
    {
    	if(this->string_index != NULL || that->string_index != NULL)
    		return false;
    }
    else if(!this->string_index->equals(that->string_index))
    	return false;
    
    return true;
}

AST_variable::AST_variable(AST_variable_name* name)
{
    #line 327 "src/generated_src/phc.tea"
{
		this->target = NULL;
		this->variable_name = name;
		this->array_indices = new List<AST_expr*>;
		this->string_index = NULL;
	}
}

void AST_variable::_init()
{
    #line 335 "src/generated_src/phc.tea"
{
		attrs->set("phc.parser.function_params", NULL);
	}
}

AST_variable* AST_variable::clone()
{
    AST_target* target = this->target ? this->target->clone() : NULL;
    AST_variable_name* variable_name = this->variable_name ? this->variable_name->clone() : NULL;
    List<AST_expr*>* array_indices = NULL;
    if(this->array_indices != NULL)
    {
    	List<AST_expr*>::const_iterator i;
    	array_indices = new List<AST_expr*>;
    	for(i = this->array_indices->begin(); i != this->array_indices->end(); i++)
    		array_indices->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_expr* string_index = this->string_index ? this->string_index->clone() : NULL;
    AST_variable* clone = new AST_variable(target, variable_name, array_indices, string_index);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_pre_op::AST_pre_op(Token_op* op, AST_variable* variable)
{
    this->op = op;
    this->variable = variable;
}

AST_pre_op::AST_pre_op()
{
    this->op = 0;
    this->variable = 0;
}

void AST_pre_op::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_pre_op::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_pre_op::classid()
{
    return ID;
}

bool AST_pre_op::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_pre_op* that = dynamic_cast<AST_pre_op*>(in);
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

bool AST_pre_op::equals(AST_node* in)
{
    AST_pre_op* that = dynamic_cast<AST_pre_op*>(in);
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
    
    return true;
}

AST_pre_op::AST_pre_op(AST_variable* var, char* op)
{
    #line 467 "src/generated_src/phc.tea"
{
		this->variable = var;
		this->op = new Token_op(new String(op));
	}
}

AST_pre_op* AST_pre_op::clone()
{
    Token_op* op = this->op ? this->op->clone() : NULL;
    AST_variable* variable = this->variable ? this->variable->clone() : NULL;
    AST_pre_op* clone = new AST_pre_op(op, variable);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_post_op::AST_post_op(AST_variable* variable, Token_op* op)
{
    this->variable = variable;
    this->op = op;
}

AST_post_op::AST_post_op()
{
    this->variable = 0;
    this->op = 0;
}

void AST_post_op::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_post_op::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_post_op::classid()
{
    return ID;
}

bool AST_post_op::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_post_op* that = dynamic_cast<AST_post_op*>(in);
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

bool AST_post_op::equals(AST_node* in)
{
    AST_post_op* that = dynamic_cast<AST_post_op*>(in);
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
    
    return true;
}

AST_post_op::AST_post_op(AST_variable* var, char* op)
{
    #line 457 "src/generated_src/phc.tea"
{
		this->variable = var;
		this->op = new Token_op(new String(op));
	}
}

AST_post_op* AST_post_op::clone()
{
    AST_variable* variable = this->variable ? this->variable->clone() : NULL;
    Token_op* op = this->op ? this->op->clone() : NULL;
    AST_post_op* clone = new AST_post_op(variable, op);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_array::AST_array(List<AST_array_elem*>* array_elems)
{
    this->array_elems = array_elems;
}

AST_array::AST_array()
{
    this->array_elems = 0;
}

void AST_array::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_array::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_array::classid()
{
    return ID;
}

bool AST_array::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_array* that = dynamic_cast<AST_array*>(in);
    if(that == NULL) return false;
    
    if(this->array_elems != NULL && that->array_elems != NULL)
    {
    	List<AST_array_elem*>::const_iterator i, j;
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

bool AST_array::equals(AST_node* in)
{
    AST_array* that = dynamic_cast<AST_array*>(in);
    if(that == NULL) return false;
    
    if(this->array_elems == NULL || that->array_elems == NULL)
    {
    	if(this->array_elems != NULL || that->array_elems != NULL)
    		return false;
    }
    else
    {
    	List<AST_array_elem*>::const_iterator i, j;
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
    
    return true;
}

AST_array* AST_array::clone()
{
    List<AST_array_elem*>* array_elems = NULL;
    if(this->array_elems != NULL)
    {
    	List<AST_array_elem*>::const_iterator i;
    	array_elems = new List<AST_array_elem*>;
    	for(i = this->array_elems->begin(); i != this->array_elems->end(); i++)
    		array_elems->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_array* clone = new AST_array(array_elems);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_method_invocation::AST_method_invocation(AST_target* target, AST_method_name* method_name, List<AST_actual_parameter*>* actual_parameters)
{
    this->target = target;
    this->method_name = method_name;
    this->actual_parameters = actual_parameters;
}

AST_method_invocation::AST_method_invocation()
{
    this->target = 0;
    this->method_name = 0;
    this->actual_parameters = 0;
}

void AST_method_invocation::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_method_invocation::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_method_invocation::classid()
{
    return ID;
}

bool AST_method_invocation::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_method_invocation* that = dynamic_cast<AST_method_invocation*>(in);
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
    	List<AST_actual_parameter*>::const_iterator i, j;
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

bool AST_method_invocation::equals(AST_node* in)
{
    AST_method_invocation* that = dynamic_cast<AST_method_invocation*>(in);
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
    	List<AST_actual_parameter*>::const_iterator i, j;
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

//  For internal use only!
AST_method_invocation::AST_method_invocation(const char* name, AST_expr* arg)
{
    #line 345 "src/generated_src/phc.tea"
{ 
		// This leaves the tree in an inconsistent state
		this->target = NULL;
		this->method_name = new Token_method_name(new String(name));
		this->actual_parameters = new List<AST_actual_parameter*>;
		this->actual_parameters->push_back(new AST_actual_parameter(false, arg));
	}
}

//  For internal use only!
AST_method_invocation::AST_method_invocation(Token_method_name* name, AST_expr* arg)
{
    #line 355 "src/generated_src/phc.tea"
{ 
		this->target = NULL;
		this->method_name = name; 
		this->actual_parameters = new List<AST_actual_parameter*>;
		this->actual_parameters->push_back(new AST_actual_parameter(false, arg));
	}
}

//  This does in fact create a valid subtree
AST_method_invocation::AST_method_invocation(const char* target, const char* name, AST_expr* arg)
{
    #line 364 "src/generated_src/phc.tea"
{
		this->target = new Token_class_name(new String(target));
		this->method_name = new Token_method_name(new String(name));
		this->actual_parameters = new List<AST_actual_parameter*>;
		this->actual_parameters->push_back(new AST_actual_parameter(false, arg));
	}
}

AST_method_invocation* AST_method_invocation::clone()
{
    AST_target* target = this->target ? this->target->clone() : NULL;
    AST_method_name* method_name = this->method_name ? this->method_name->clone() : NULL;
    List<AST_actual_parameter*>* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	List<AST_actual_parameter*>::const_iterator i;
    	actual_parameters = new List<AST_actual_parameter*>;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_method_invocation* clone = new AST_method_invocation(target, method_name, actual_parameters);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_new::AST_new(AST_class_name* class_name, List<AST_actual_parameter*>* actual_parameters)
{
    this->class_name = class_name;
    this->actual_parameters = actual_parameters;
}

AST_new::AST_new()
{
    this->class_name = 0;
    this->actual_parameters = 0;
}

void AST_new::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_new::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_new::classid()
{
    return ID;
}

bool AST_new::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_new* that = dynamic_cast<AST_new*>(in);
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
    	List<AST_actual_parameter*>::const_iterator i, j;
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

bool AST_new::equals(AST_node* in)
{
    AST_new* that = dynamic_cast<AST_new*>(in);
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
    	List<AST_actual_parameter*>::const_iterator i, j;
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

AST_new* AST_new::clone()
{
    AST_class_name* class_name = this->class_name ? this->class_name->clone() : NULL;
    List<AST_actual_parameter*>* actual_parameters = NULL;
    if(this->actual_parameters != NULL)
    {
    	List<AST_actual_parameter*>::const_iterator i;
    	actual_parameters = new List<AST_actual_parameter*>;
    	for(i = this->actual_parameters->begin(); i != this->actual_parameters->end(); i++)
    		actual_parameters->push_back(*i ? (*i)->clone() : NULL);
    }
    AST_new* clone = new AST_new(class_name, actual_parameters);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

AST_clone::AST_clone(AST_expr* expr)
{
    this->expr = expr;
}

AST_clone::AST_clone()
{
    this->expr = 0;
}

void AST_clone::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void AST_clone::transform_children(AST_transform* transform)
{
    transform->children_expr(this);
}

int AST_clone::classid()
{
    return ID;
}

bool AST_clone::match(AST_node* in)
{
    __WILDCARD__* joker;
    joker = dynamic_cast<__WILDCARD__*>(in);
    if(joker != NULL && joker->match(this))
    	return true;
    
    AST_clone* that = dynamic_cast<AST_clone*>(in);
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

bool AST_clone::equals(AST_node* in)
{
    AST_clone* that = dynamic_cast<AST_clone*>(in);
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

AST_clone* AST_clone::clone()
{
    AST_expr* expr = this->expr ? this->expr->clone() : NULL;
    AST_clone* clone = new AST_clone(expr);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

Token_int::Token_int(int value, String* source_rep)
{
    this->value = value;
    this->source_rep = source_rep;
}

Token_int::Token_int()
{
    this->value = 0;
    this->source_rep = 0;
}

void Token_int::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_int::transform_children(AST_transform* transform)
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

bool Token_int::match(AST_node* in)
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

bool Token_int::equals(AST_node* in)
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
    
    return true;
}

bool Token_int::equals_value(Token_int* that)
{
    return (this->value == that->value);
}

String* Token_int::get_value_as_string()
{
    #line 529 "src/generated_src/phc.tea"
{
		std::ostringstream os;
		os << value;
		return new String(os.str());
	}
}

Token_int* Token_int::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_int* clone = new Token_int(value, source_rep);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

int Token_int::clone_value()
{
    return value;
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

void Token_real::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_real::transform_children(AST_transform* transform)
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

bool Token_real::match(AST_node* in)
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

bool Token_real::equals(AST_node* in)
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
    
    return true;
}

bool Token_real::equals_value(Token_real* that)
{
    return (this->value == that->value);
}

String* Token_real::get_value_as_string()
{
    #line 540 "src/generated_src/phc.tea"
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

Token_real* Token_real::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_real* clone = new Token_real(value, source_rep);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

double Token_real::clone_value()
{
    return value;
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

void Token_string::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_string::transform_children(AST_transform* transform)
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

bool Token_string::match(AST_node* in)
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

bool Token_string::equals(AST_node* in)
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
    
    return true;
}

bool Token_string::equals_value(Token_string* that)
{
    return (*this->value == *that->value);
}

String* Token_string::get_value_as_string()
{
    #line 574 "src/generated_src/phc.tea"
{
		return value;
	}
}

Token_string* Token_string::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_string* clone = new Token_string(value, source_rep);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

String* Token_string::clone_value()
{
    return value;
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

void Token_bool::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_bool::transform_children(AST_transform* transform)
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

bool Token_bool::match(AST_node* in)
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

bool Token_bool::equals(AST_node* in)
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
    
    return true;
}

bool Token_bool::equals_value(Token_bool* that)
{
    return (this->value == that->value);
}

String* Token_bool::get_value_as_string()
{
    #line 562 "src/generated_src/phc.tea"
{
		if(value)
			return new String("True");
		else
			return new String("False");
	}
}

Token_bool* Token_bool::clone()
{
    String* source_rep = new String(*this->source_rep);
    value = clone_value();
    Token_bool* clone = new Token_bool(value, source_rep);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}

bool Token_bool::clone_value()
{
    return value;
}

Token_null::Token_null(String* source_rep)
{
    this->source_rep = source_rep;
}

Token_null::Token_null()
{
    this->source_rep = 0;
}

void Token_null::visit(AST_visitor* visitor)
{
    visitor->visit_expr(this);
}

void Token_null::transform_children(AST_transform* transform)
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

bool Token_null::match(AST_node* in)
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

bool Token_null::equals(AST_node* in)
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
    
    return true;
}

String* Token_null::get_value_as_string()
{
    #line 583 "src/generated_src/phc.tea"
{
		return new String("NULL");
	}
}

Token_null* Token_null::clone()
{
    String* source_rep = new String(*this->source_rep);
    Token_null* clone = new Token_null(source_rep);
    clone->AST_node::clone_mixin_from(this);
    return clone;
}


