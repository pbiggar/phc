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

	if (print_attrs)
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
				if((*i).first == "phc.line_number")
				{
					print_indent();
					os << "<attr key=\"phc.line_number\">" << in->get_line_number() << "</attr>" << endl;
				}
				else if((*i).first == "phc.filename")
				{
					print_indent();
					os << "<attr key=\"phc.filename\">" << *in->get_filename() << "</attr>" << endl;
				}
				else if((*i).first == "phc.comments")
				{
					print_indent();
					os << "<attr key=\"phc.comments\">" << endl;
					indent++;

					List<String*>::const_iterator j;
					List<String*>* comments = dynamic_cast<List<String*>*>((*i).second);
					for(j = comments->begin(); j != comments->end(); j++)
					{
						print_indent();
						os << "<comment";

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

						os << "</comment>" << endl;
					}

					indent--;
					print_indent();
					os << "</attr>" << endl;
				}
#define HANDLE_BOOLEAN(A)																											\
				else if((*i).first == A)																							\
				{																															\
					print_indent();																									\
					bool attr_true = in->attrs->is_true (A);																	\
					os << "<attr key=\"" A "\">" << (attr_true ? "true" : "false") << "</attr>" << endl;		\
				}
#define HANDLE_STRING(A)																											\
				else if((*i).first == A)																							\
				{																															\
					print_indent();																									\
					String* string = in->attrs->get_string (A);																\
					os << "<attr key=\"" A "\">" << *string << "</attr>" << endl;										\
				}
#define HANDLE_INT(A)																												\
				else if((*i).first == A)																							\
				{																															\
					print_indent();																									\
					Integer* integer = in->attrs->get_integer (A);															\
					os << "<attr key=\"" A "\">" << integer->value () << "</attr>" << endl;							\
				}
				HANDLE_BOOLEAN ("phc.unparser.is_elseif")
				HANDLE_BOOLEAN ("phc.unparser.needs_brackets")
				HANDLE_BOOLEAN ("phc.unparser.needs_curlies")
				HANDLE_BOOLEAN ("phc.unparser.is_global_stmt")
				HANDLE_BOOLEAN ("phc.unparser.is_opeq")
				HANDLE_BOOLEAN ("phc.unparser.starts_line")
				HANDLE_STRING ("phc.generate_c.location")
				HANDLE_BOOLEAN ("phc.generate_c.is_addr")
				HANDLE_STRING ("phc.generate_c.hash")
				HANDLE_STRING ("phc.generate_c.stridx")
				HANDLE_INT ("phc.generate_c.strlen")
				HANDLE_STRING ("phc.generate_c.zvalidx")
				HANDLE_INT ("phc.codegen.temp")
				HANDLE_INT ("phc.codegen.num_temps")
				HANDLE_BOOLEAN ("phc.shredder.need_addr")
				HANDLE_BOOLEAN ("phc.lower_expr.no_temp")
				HANDLE_BOOLEAN ("phc.unparser.is_singly_quoted")
				HANDLE_BOOLEAN ("phc.unparser.index_curlies")
//				HANDLE_BOOLEAN ("phc.codegen.break_label")
//				HANDLE_BOOLEAN ("phc.codegen.continue_label")
#undef HANDLE_BOOLEAN
#undef HANDLE_STRING
#undef HANDLE_INT
				else
				{
					phc_warning("Unknown attribute '%s'", NULL, 0, (*i).first.c_str());	
				}
			}

			indent--;
			print_indent();
			os << "</attrs>" << endl;
		}
	}
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

void XML_unparser::visit_null(const char* type_id)
{
	print_indent();
	os << "<" << type_id << " xsi:nil=\"true\" />" << endl;
}

void XML_unparser::visit_marker(const char* name, bool value)
{
	print_indent();
	os << "<bool>" 
		<< "<!-- " << name << " -->"
		<< (value ? "true" : "false") << "</bool>" << endl;
}
