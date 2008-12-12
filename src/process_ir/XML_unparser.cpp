/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */
#include <ostream>

#include "cmdline.h"

#include "lib/base64.h"
#include "lib/Boolean.h"
#include "lib/error.h"
#include "lib/demangle.h"
#include "lib/List.h"
#include "lib/Object.h"
#include "lib/String.h"

#include "XML_unparser.h"

using namespace std;

extern gengetopt_args_info args_info;

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
class XML_unparser : public Visitor, virtual public GC_obj
{
protected:
	string xmlns; // XML namespace
	XML_unparser_state* state;

public:
	XML_unparser(string xmlns, std::ostream& os = std::cout, bool print_attrs = true)
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
		else if (IR::Node* node = dynamic_cast<IR::Node*> (attr))
		{
			xml_unparse (node, state);
		}
		else if (attr == NULL)
		{
			state->os << "<!-- skipping NULL attribute " << name << " -->" << endl;
		}
		else if(String_list* ls = dynamic_cast<String_list*>(attr))
		{
			state->os << "<attr key=\"" << name << "\">" << endl;
			state->indent++;
			state->print_indent ();
			state->os << "<string_list>" << endl;
			state->indent++;

			foreach (String* s, *ls)
			{
				state->print_indent();
				maybe_encode ("string", s);
				state->os << endl;
			}

			state->indent--;
			state->print_indent();
			state->os << "</string_list>" << endl;
			state->indent--;
			state->print_indent();
			state->os << "</attr>" << endl;
		}
		else if(IR::Node_list* ls = dynamic_cast<IR::Node_list*>(attr))
		{
			// Allow lists of nodes, only if as List<IR::Node*>
			state->os << "<attr key=\"" << name << "\">" << endl;
			state->indent++;
			state->print_indent ();
			state->os << "<node_list>" << endl;
			state->indent++;

			foreach (IR::Node* node, *ls)
				xml_unparse (node, state);

			state->indent--;
			state->print_indent();
			state->os << "</node_list>" << endl;
			state->indent--;
			state->print_indent();
			state->os << "</attr>" << endl;
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
	AST_XML_unparser(ostream& os = std::cout, bool print_attrs = true)
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
	HIR_XML_unparser(ostream& os = std::cout, bool print_attrs = true)
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
	MIR_XML_unparser(ostream& os = std::cout, bool print_attrs = true)
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

	void pre_param_index (MIR::PARAM_INDEX* in)
	{
		String* value = in->get_value_as_string();

		state->print_indent();
		maybe_encode ("value", value);
		state->os << endl;
	}

};

#include "LIR_visitor.h"




XML_unparser_state::XML_unparser_state (ostream& os, bool print_attrs)
: os (os)
, print_attrs (print_attrs)
, indent (0)
{
}

void
XML_unparser_state::print_indent ()
{
	for(int i = 0; i < indent; i++)
		os << args_info.tab_arg;
}

void
xml_unparse (AST::Node* in, XML_unparser_state* state)
{
	in->visit (new AST_XML_unparser (state));
}

void xml_unparse (HIR::Node* in, XML_unparser_state* state)
{
	in->visit (new HIR_XML_unparser (state));
}

void xml_unparse (MIR::Node* in, XML_unparser_state* state)
{
	in->visit (new MIR_XML_unparser (state));
}

void xml_unparse (LIR::Node* in, XML_unparser_state* state)
{
//	in->visit (new LIR_XML_unparser (state));
	phc_TODO ();
//	TODO
}

void xml_unparse (IR::Node* in, XML_unparser_state* state)
{
	if (isa<AST::Node> (in))
		xml_unparse (dyc<AST::Node> (in), state);
	else if (isa<HIR::Node> (in))
		xml_unparse (dyc<HIR::Node> (in), state);
	else if (isa<MIR::Node> (in))
		xml_unparse (dyc<MIR::Node> (in), state);
	else
		xml_unparse (dyc<LIR::Node> (in), state);
}

void xml_unparse (AST::Node* in, std::ostream& os, bool print_attrs)
{
  in->visit (new AST_XML_unparser (os, print_attrs));
}

void xml_unparse (HIR::Node* in, std::ostream& os, bool print_attrs)
{
  in->visit (new HIR_XML_unparser (os, print_attrs));
}

void xml_unparse (MIR::Node* in, std::ostream& os, bool print_attrs)
{
  in->visit (new MIR_XML_unparser (os, print_attrs));
}

void xml_unparse (LIR::Node* in, std::ostream& os, bool print_attrs)
{
	phc_TODO ();
//  in->visit (new MIR_XML_unparser (os, print_attrs));
}






void xml_unparse (IR::PHP_script* in, std::ostream& os, bool print_attrs)
{
	if (isa<AST::PHP_script> (in))
		xml_unparse (dyc<AST::Node> (in), os, print_attrs);
	else if (isa<HIR::PHP_script> (in))
		xml_unparse (dyc<HIR::Node> (in), os, print_attrs);
	else
		xml_unparse (dyc<MIR::Node> (in), os, print_attrs);
}
