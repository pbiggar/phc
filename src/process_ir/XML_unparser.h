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
#include "process_ir/IR.h"
#include "cmdline.h"

char* get_args_info_tab ();

class XML_unparser_state
{
public:
	ostream& os;
	bool print_attrs;
	int indent;

public:
	XML_unparser_state (ostream& os, bool print_attrs);
	void print_indent();
};

void xml_unparse (AST::Node*, XML_unparser_state* state = NULL);
void xml_unparse (HIR::Node*, XML_unparser_state* state = NULL);
void xml_unparse (MIR::Node*, XML_unparser_state* state = NULL);
void xml_unparse (IR::Node*, XML_unparser_state* state = NULL);


template
<
	class Script,
	class Node,
	class Visitor,
	class Identifier,
	class Literal,
	class NIL,
	class CAST,
	class FOREIGN
>
class XML_unparser : public Visitor 
{
protected:
	string xmlns; // XML namespace
	XML_unparser_state* state;

public:
	XML_unparser(string xmlns, ostream& os = cout, bool print_attrs = true)
	: xmlns(xmlns)
	{
		state = new XML_unparser_state (os, print_attrs);
	}

	XML_unparser(string xmlns, XML_unparser_state* state)
	: xmlns(xmlns)
	, state(state)
	{
	}

	virtual ~XML_unparser() 
	{
	}

public:

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

	void visit_marker(char const* name, bool value)
	{
		state->print_indent();
		state->os << "<bool>" 
			<< "<!-- " << name << " -->"
			<< (value ? "true" : "false") << "</bool>" << endl;
	}

	void visit_null(char const* name_space, char const* type_id)
	{
		state->print_indent();
		state->os << "<" << name_space << ":" << type_id << " xsi:nil=\"true\" />" << endl;
	}

	void visit_null_list(char const* name_space, char const* type_id)
	{
		state->print_indent();
		state->os << "<" << name_space << ":" << type_id << "_list xsi:nil=\"true\" />" << endl;
	}

	void pre_list(char const* name_space, char const* type_id, int size)
	{
		state->print_indent();
		state->os << "<" << name_space << ":" << type_id << "_list>" << endl;
		state->indent++;
	}

	void post_list(char const* name_space, char const* type_id, int size)
	{
		state->indent--;
		state->print_indent();
		state->os << "</" << name_space << ":" << type_id << "_list>" << endl;
	}

public:

	
	// Demangle and convert type names qualified with a namespace into XML
	// namespaces (eg AST::If into AST:If)
	const char* demangle_xml (Node* node)
	{
		String* demangled = new String (demangle (node, true));
		size_t index = demangled->find_first_of (':');
		if (index != string::npos)
		{
			demangled->erase (index, 1);
		}
		return demangled->c_str ();
	}

	void pre_node(Node* in)
	{
		bool is_root = dynamic_cast<Script*>(in);

		if(is_root)
			state->os << "<?xml version=\"1.0\"?>" << endl;

		state->print_indent();

		state->os << "<" << demangle_xml (in);

		if(is_root)
		{
			// TODO these should have different defintions.
			state->os << " xmlns:AST=\"http://www.phpcompiler.org/phc-1.1\"";
			state->os << " xmlns:HIR=\"http://www.phpcompiler.org/phc-1.1\"";
			state->os << " xmlns:MIR=\"http://www.phpcompiler.org/phc-1.1\"";
			state->os << " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"";
		}

		state->os << ">" << endl;
		state->indent++;

		if(state->print_attrs) print_attributes(in);
	}

	void post_node(Node* in)
	{
		state->indent--;
		state->print_indent();
		state->os << "</" << demangle_xml(in) << ">" << endl;
	}

protected:

	void maybe_encode (const char* tag_name, String* value)
	{
		state->os << "<" << tag_name;

		if(needs_encoding(value))
		{
			state->os << " encoding=\"base64\">";
			state->os << *base64_encode(value);
		}
		else
		{
			state->os << ">";
			state->os << *value;
		}

		state->os << "</" << tag_name << ">";
	}

	void print_attributes(Node* in)
	{
		if(in->attrs->size() == 0)
		{
			state->print_indent();
			state->os << "<attrs />" << endl;
		}
		else
		{
			state->print_indent();
			state->os << "<attrs>" << endl;
			state->indent++;

			AttrMap::const_iterator i;
			for(i = in->attrs->begin(); i != in->attrs->end(); i++)
			{
				print_attribute((*i).first, (*i).second);
			}

			state->indent--;
			state->print_indent();
			state->os << "</attrs>" << endl;
		}
	}

	void print_attribute(string name, Object* attr)
	{
		state->print_indent();

		if(String* str = dynamic_cast<String*>(attr))
		{
			state->os << "<attr key=\"" << name << "\">";
			maybe_encode ("string", str);
			state->os << "</attr>" << endl;
		}
		else if(Integer* i = dynamic_cast<Integer*>(attr))
		{
			state->os << "<attr key=\"" << name << "\"><integer>" << i->value () << "</integer></attr>" << endl;
		}
		else if(Boolean* b = dynamic_cast<Boolean*>(attr))
		{
			state->os << "<attr key=\"" << name << "\"><bool>" << (b->value() ? "true" : "false") << "</bool></attr>" << endl;
		}
		else if(List<String*>* ls = dynamic_cast<List<String*>*>(attr))
		{
			state->os << "<attr key=\"" << name << "\"><string_list>" << endl;
			state->indent++;

			List<String*>::const_iterator j;
			for(j = ls->begin(); j != ls->end(); j++)
			{
				state->print_indent();
				maybe_encode ("string", *j);
			}

			state->indent--;
			state->print_indent();
			state->os << "</string_list></attr>" << endl;
		}
		else if (attr == NULL)
		{
			state->os << "<!-- skipping NULL attribute " << name << " -->" << endl;
		}
		else if (IR::Node* node = dynamic_cast<IR::Node*> (attr))
		{
			xml_unparse (node, state);
		}
		else
			phc_warning ("Don't know how to deal with attribute '%s' of type '%s'", name.c_str(), demangle(attr, true));	
	}

	void pre_literal(Literal* in)
	{
		String* value = in->get_value_as_string();

		// NIL does not have a value
		if(!isa<NIL> (in))
		{
			state->print_indent();
			maybe_encode ("value", value);
			state->os << endl;
		}
	}

	void pre_identifier(Identifier* in)
	{
		String* value = in->get_value_as_string();

		state->print_indent();
		maybe_encode ("value", value);
		state->os << endl;
	}

	// Foreign nodes delegate to the appropriate XML_unparser.
	void pre_foreign (FOREIGN* in)
	{
		state->print_indent();
		state->os << "<value>" << endl;

		state->indent++;
		xml_unparse (in->value, state);
		state->indent--;

		state->print_indent();
		state->os << "</value>" << endl;
	}
};

#include "AST_visitor.h"
class AST_XML_unparser : public XML_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Visitor,
	AST::Identifier,
	AST::Literal,
	AST::NIL,
	AST::CAST,
	AST::FOREIGN
>
{
public:
	AST_XML_unparser(ostream& os = cout, bool print_attrs = true)
	: XML_unparser<
			AST::PHP_script,
			AST::Node,
			AST::Visitor,
			AST::Identifier,
			AST::Literal,
			AST::NIL,
			AST::CAST,
			AST::FOREIGN
		> ("AST", os, print_attrs)
	{
	}

	AST_XML_unparser(XML_unparser_state* state)
	: XML_unparser<
			AST::PHP_script,
			AST::Node,
			AST::Visitor,
			AST::Identifier,
			AST::Literal,
			AST::NIL,
			AST::CAST,
			AST::FOREIGN
		> ("AST", state)
	{
	}
	
};

#include "HIR_visitor.h"
class HIR_XML_unparser : public XML_unparser
<
	HIR::PHP_script,
	HIR::Node,
	HIR::Visitor,
	HIR::Identifier,
	HIR::Literal,
	HIR::NIL,
	HIR::CAST,
	HIR::FOREIGN
>
{
public:
	HIR_XML_unparser(ostream& os = cout, bool print_attrs = true)
	: XML_unparser<
			HIR::PHP_script,
			HIR::Node,
			HIR::Visitor,
			HIR::Identifier,
			HIR::Literal,
			HIR::NIL,
			HIR::CAST,
			HIR::FOREIGN
		> ("HIR", os, print_attrs)
	{
	}

	HIR_XML_unparser(XML_unparser_state* state)
	: XML_unparser<
			HIR::PHP_script,
			HIR::Node,
			HIR::Visitor,
			HIR::Identifier,
			HIR::Literal,
			HIR::NIL,
			HIR::CAST,
			HIR::FOREIGN
		> ("HIR", state)
	{
	}
};

#include "MIR_visitor.h"
class MIR_XML_unparser : public XML_unparser
<
	MIR::PHP_script, 
	MIR::Node, 
	MIR::Visitor,
	MIR::Identifier,
	MIR::Literal,
	MIR::NIL,
	MIR::CAST,
	MIR::FOREIGN
> 
{
public:
	MIR_XML_unparser(ostream& os = cout, bool print_attrs = true)
	: XML_unparser<
			MIR::PHP_script,
			MIR::Node,
			MIR::Visitor,
			MIR::Identifier,
			MIR::Literal,
			MIR::NIL,
			MIR::CAST,
			MIR::FOREIGN
		> ("MIR", os, print_attrs)
	{
	}

	MIR_XML_unparser(XML_unparser_state* state)
	: XML_unparser<
			MIR::PHP_script,
			MIR::Node,
			MIR::Visitor,
			MIR::Identifier,
			MIR::Literal,
			MIR::NIL,
			MIR::CAST,
			MIR::FOREIGN
		> ("MIR", state)
	{
	}

};


#endif // PHC_XML_UNPARSER
