/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */

#include <iostream>
#include "XML_unparser.h"
#include "lib/base64.h"
#include "lib/demangle.h"
#include "cmdline.h"

using namespace std;

extern struct gengetopt_args_info args_info;

/* Dump the XML for anynode to stderr. A global function. */
void xdebug (AST_node* in)
{
	XML_unparser *xup = new XML_unparser (cerr, false);
	in->visit (xup);
}

void xadebug (AST_node* in)
{
	XML_unparser *xup = new XML_unparser (cerr, true);
	in->visit (xup);
}

void XML_unparser::print_indent()
{
	for(int i = 0; i < indent; i++)
		os << args_info.tab_arg;
}

bool XML_unparser::needs_encoding(String* str)
{
	String::const_iterator i;
	
	for(i = str->begin(); i != str->end(); i++)
	{
		if(*i < 32)
			return true;

		if(*i > 126)
			return true;

		if(*i == '<' || *i == '>' || *i == '&')
			return true;
	}

	return false;
}

XML_unparser::XML_unparser(ostream& os, bool print_attrs)
: os(os), print_attrs (print_attrs)
{
	indent = 0;
}

XML_unparser::~XML_unparser() 
{
}

void XML_unparser::pre_node(AST_node* in)
{
	bool is_root = dynamic_cast<AST_php_script*>(in);
	
	if(is_root)
		os << "<?xml version=\"1.0\"?>" << endl;

	print_indent();
	os << "<" << demangle(in);
	
	if(is_root)
	{
		os << " xmlns=\"http://www.phpcompiler.org/phc-1.0\"";
		os << " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"";
	}

	os << ">" << endl;
	indent++;

	if(print_attrs) print_attributes(in);
}

void XML_unparser::print_attributes(AST_node* in)
{
	if(in->attrs->size() == 0)
	{
		print_indent();
		os << "<attrs />" << endl;
	}
	else
	{
		print_indent();
		os << "<attrs>" << endl;
		indent++;

		AttrMap::const_iterator i;
		for(i = in->attrs->begin(); i != in->attrs->end(); i++)
		{
			print_attribute((*i).first, (*i).second);
		}
			
		indent--;
		print_indent();
		os << "</attrs>" << endl;
	}
}

void XML_unparser::print_attribute(string name, Object* attr)
{
	print_indent();

	if(String* str = dynamic_cast<String*>(attr))
	{
		os << "<attr key=\"" << name << "\"><string>" << *str << "</string></attr>" << endl;
	}
	else if(Integer* i = dynamic_cast<Integer*>(attr))
	{
		os << "<attr key=\"" << name << "\"><integer>" << i->value () << "</integer></attr>" << endl;
	}
	else if(Boolean* b = dynamic_cast<Boolean*>(attr))
	{
		os << "<attr key=\"" << name << "\"><bool>" << (b->value() ? "true" : "false") << "</bool></attr>" << endl;
	}
	else if(List<String*>* ls = dynamic_cast<List<String*>*>(attr))
	{
		os << "<attr key=\"" << name << "\"><string_list>" << endl;
		indent++;

		List<String*>::const_iterator j;
		for(j = ls->begin(); j != ls->end(); j++)
		{
			print_indent();
			os << "<string";

			if(needs_encoding(*j))
			{
				os << " encoding=\"base64\">";
				os << *base64_encode(*j);
			}
			else	
			{
				os << ">";
				os << **j;
			}

			os << "</string>" << endl;
		}

		indent--;
		print_indent();
		os << "</string_list></attr>" << endl;
	}
	else
		phc_warning("Don't know how to deal with attribute '%s' of type '%s'", name.c_str(), demangle(attr));	
}

void XML_unparser::post_node(AST_node* in)
{
	indent--;
	print_indent();
	os << "</" << demangle(in) << ">" << endl;
}

void XML_unparser::pre_identifier(AST_identifier* in)
{
	String* value = in->get_value_as_string();

	print_indent();
	if(needs_encoding(value))
		os << "<value encoding=\"base64\">" << *base64_encode(value) << "</value>" << endl;
	else
		os << "<value>" << *value << "</value>" << endl;;

}

void XML_unparser::pre_literal(AST_literal* in)
{
	String* value = in->get_value_as_string();
	String* source_rep = in->get_source_rep();

	// Token_null does not have a value
	if(!dynamic_cast<Token_null*>(in))
	{
		print_indent();
		if(needs_encoding(value))
			os << "<value encoding=\"base64\">" << *base64_encode(value) << "</value>" << endl;
		else	
			os << "<value>" << *value << "</value>" << endl;
	}

	print_indent();
	if(needs_encoding(source_rep))
		os << "<source_rep encoding=\"base64\">" << *base64_encode(source_rep) << "</source_rep>" << endl;
	else	
		os << "<source_rep>" << *source_rep << "</source_rep>" << endl;
}

void XML_unparser::visit_marker(const char* name, bool value)
{
	print_indent();
	os << "<bool>" 
		<< "<!-- " << name << " -->"
		<< (value ? "true" : "false") << "</bool>" << endl;
}

void XML_unparser::visit_null(const char* type_id)
{
	print_indent();
	os << "<" << type_id << " xsi:nil=\"true\" />" << endl;
}

void XML_unparser::visit_null_list(const char* type_id)
{
	print_indent();
	os << "<" << type_id << "_list xsi:nil=\"true\" />" << endl;
}

void XML_unparser::pre_list(const char* type_id, int size)
{
	print_indent();
	os << "<" << type_id << "_list>" << endl;
	indent++;
}

void XML_unparser::post_list(const char* type_id, int size)
{
	indent--;
	print_indent();
	os << "</" << type_id << "_list>" << endl;
}
