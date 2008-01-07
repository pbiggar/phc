/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */

#ifndef PHC_XML_UNPARSER
#define PHC_XML_UNPARSER

#include <iostream>
#include "lib/base64.h"
#include "lib/demangle.h"
#include "lib/error.h"
#include "lib/String.h"
#include "lib/List.h"
#include "cmdline.h"

template
<
	class Script,
	class Node,
	class Visitor
>
class XML_unparser : public Visitor 
{
protected:
	ostream& os;
	int indent;
	bool print_attrs;

	void print_indent()
	{
		extern gengetopt_args_info args_info;
		for(int i = 0; i < indent; i++)
			os << args_info.tab_arg;
	}

	bool needs_encoding(String* str)
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

public:
	XML_unparser(ostream& os = cout, bool print_attrs = true)
		: os(os), print_attrs (print_attrs)
	{
		indent = 0;
	}

	virtual ~XML_unparser() 
	{
	}

public:

	void visit_marker(char const* name, bool value)
	{
		print_indent();
		os << "<bool>" 
			<< "<!-- " << name << " -->"
			<< (value ? "true" : "false") << "</bool>" << endl;
	}

	void visit_null(char const* type_id)
	{
		print_indent();
		os << "<" << type_id << " xsi:nil=\"true\" />" << endl;
	}

	void visit_null_list(char const* type_id)
	{
		print_indent();
		os << "<" << type_id << "_list xsi:nil=\"true\" />" << endl;
	}

	void pre_list(char const* type_id, int size)
	{
		print_indent();
		os << "<" << type_id << "_list>" << endl;
		indent++;
	}

	void post_list(char const* type_id, int size)
	{
		indent--;
		print_indent();
		os << "</" << type_id << "_list>" << endl;
	}

public:

	void pre_node(Node* in)
	{
		bool is_root = dynamic_cast<Script*>(in);

		if(is_root)
			os << "<?xml version=\"1.0\"?>" << endl;

		print_indent();
		os << "<" << demangle(in);

		if(is_root)
		{
			os << " xmlns=\"http://www.phpcompiler.org/phc-1.1\"";
			os << " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"";
		}

		os << ">" << endl;
		indent++;

		if(print_attrs) print_attributes(in);
	}

	void post_node(Node* in)
	{
		indent--;
		print_indent();
		os << "</" << demangle(in) << ">" << endl;
	}

protected:

	void maybe_encode (const char* tag_name, String* value)
	{
		os << "<" << tag_name;

		if(needs_encoding(value))
		{
			os << " encoding=\"base64\">";
			os << *base64_encode(value);
		}
		else
		{
			os << ">";
			os << *value;
		}

		os << "</" << tag_name << ">";
	}

	void print_attributes(Node* in)
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

	void print_attribute(string name, Object* attr)
	{
		print_indent();

		if(String* str = dynamic_cast<String*>(attr))
		{
			os << "<attr key=\"" << name << "\">";
			maybe_encode ("string", str);
			os << "</attr>" << endl;
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
				maybe_encode ("string", *j);
			}

			indent--;
			print_indent();
			os << "</string_list></attr>" << endl;
		}
		else if (attr == NULL)
		{
			os << "<!-- skipping NULL attribute " << name << " -->" << endl;
		}
		else
			phc_warning ("Don't know how to deal with attribute '%s' of type '%s'", name.c_str(), demangle(attr));	
	}

};

#include "AST_visitor.h"
class AST_XML_unparser : public XML_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Visitor
>
{
public:
	AST_XML_unparser(ostream& os = cout, bool print_attrs = true)
	: XML_unparser<
			AST::PHP_script,
			AST::Node,
			AST::Visitor
		> (os, print_attrs)
	{
	}
	
	void pre_identifier(AST::Identifier* in)
	{
		AST::CAST* cast = dynamic_cast<AST::CAST*>(in);

		if(cast != NULL)
		{
			print_indent();
			os << "<value>" << *cast->value << "</value>" << endl;
		}
		else
		{
			String* value = in->get_value_as_string();

			print_indent();
			maybe_encode ("value", value);
			os << endl;
		}
	}

	void pre_literal(AST::Literal* in)
	{
		String* value = in->get_value_as_string();

		// NIL does not have a value
		if(!dynamic_cast<AST::NIL*>(in))
		{
			print_indent();
			maybe_encode ("value", value);
			os << endl;
		}
	}

};

#include "HIR_visitor.h"
class HIR_XML_unparser : public XML_unparser
<
	HIR::PHP_script,
	HIR::Node,
	HIR::Visitor
>
{
public:
	HIR_XML_unparser(ostream& os = cout, bool print_attrs = true)
	: XML_unparser<
			HIR::PHP_script,
			HIR::Node,
			HIR::Visitor
		> (os, print_attrs)
	{
	}
	
	void pre_identifier(HIR::Identifier* in)
	{
		String* value = in->get_value_as_string();

		print_indent();
		maybe_encode ("value", value);
		os << endl;
	}

	void pre_literal(HIR::Literal* in)
	{
		String* value = in->get_value_as_string();

		// NIL does not have a value
		if(!dynamic_cast<HIR::NIL*>(in))
		{
			print_indent();
			maybe_encode ("value", value);
			os << endl;
		}
	}

};

#include "MIR_visitor.h"
class MIR_XML_unparser : public XML_unparser
<
	MIR::PHP_script, 
	MIR::Node, 
	MIR::Visitor
> 
{
public:
	MIR_XML_unparser(ostream& os = cout, bool print_attrs = true)
	: XML_unparser<
			MIR::PHP_script,
			MIR::Node,
			MIR::Visitor
		> (os, print_attrs)
	{
	}
	
	void pre_identifier(MIR::Identifier* in)
	{
		String* value = in->get_value_as_string();

		print_indent();
		maybe_encode ("value", value);
		os << endl;

	}

	void pre_literal(MIR::Literal* in)
	{
		String* value = in->get_value_as_string();

		// NIL does not have a value
		if(!dynamic_cast<MIR::NIL*>(in))
		{
			print_indent();
			maybe_encode ("value", value);
			os << endl;
		}
	}
};

#endif // PHC_XML_UNPARSER
