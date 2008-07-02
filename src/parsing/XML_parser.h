/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the AST in XML format
 */

#ifndef PHC_XML_PARSER_H
#define PHC_XML_PARSER_H

#include "config.h"

void init_xml ();
void shutdown_xml ();

#ifdef HAVE_XERCES

#include "AST.h"
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/StdInInputSource.hpp>
#include <stack>
#include "lib/base64.h"
#include "lib/error.h"
#include "lib/AttrMap.h"
#include "AST_factory.h"
#include "HIR_factory.h"
#include "MIR_factory.h"

#include "cmdline.h"
extern struct gengetopt_args_info args_info;

#define ERR_XML_PARSE "Could not parse the XML (%s)"

XERCES_CPP_NAMESPACE_USE


template<class PHP_script, class Node, class Node_factory, class STRING, class CAST, class INT, class REAL, class BOOL, class NIL>
class PHC_SAX2Handler : public DefaultHandler 
{
private:
	stack<Object*> node_stack;
	stack<int> num_children_stack;
	bool is_nil, is_base64_encoded;
	String buffer;
	string key;
	stack<AttrMap*> attrs_stack;
	const Locator* locator;

public:
	PHP_script* result;
	bool no_errors;

public:
	PHC_SAX2Handler() {}

public:
	void startDocument()
	{
		num_children_stack.push(0);
		no_errors = true;
	}

	void endDocument()
	{
		if(no_errors)
		{
			result = dynamic_cast<PHP_script*>(node_stack.top());
		}
	}

	void startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const Attributes& attrs
	)
	{
		if(!no_errors) return;

		is_nil = false;
		is_base64_encoded = false;
	
		// Push a new attribute map when seeing <attrs>
		char* name = XMLString::transcode(localname);
		if(!strcmp(name, "attrs"))
		{
			attrs_stack.push(new AttrMap);
		}
		
		// Check attributes
		for(unsigned i = 0; i < attrs.getLength(); i++)
		{
			char* attr_uri = XMLString::transcode(attrs.getURI(i));
			char* attr_name = XMLString::transcode(attrs.getLocalName(i));
			char* attr_value = XMLString::transcode(attrs.getValue(i));
	
			if(!strcmp(attr_uri, "http://www.w3.org/2001/XMLSchema-instance") &&
				!strcmp(attr_name, "nil") &&
				!strcmp(attr_value, "true"))
			{
				is_nil = true;
			}
	
			if(!strcmp(attr_uri, "") &&
				!strcmp(attr_name, "encoding") &&
				!strcmp(attr_value, "base64"))
			{
				is_base64_encoded = true;
			}
		
			// Store name of the attribute key 
			if(!strcmp(attr_uri, "") &&
				!strcmp(attr_name, "key") &&
				!strcmp(name, "attr"))
			{
				key = attr_value;
			}
		
			XMLString::release(&attr_uri);
			XMLString::release(&attr_name);
			XMLString::release(&attr_value);
		}

		buffer = "";

		num_children_stack.top()++;
		num_children_stack.push(0);
	}

	void endElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	)
	{
		if(!no_errors) return;
			
		char* name = XMLString::transcode(localname);
		Object* node = NULL;
		Node* ir_node = NULL;
		String* value;

		// Number of children of the node we are about to create
		int num_children = num_children_stack.top();

		// After we pop, num_children_stack.top() corresponds to the number
		// of children of the *parent* of the node we are about to create
		num_children_stack.pop();

#define copy_attrs()									\
do															\
{															\
	if (attrs_stack.size() > 0)					\
	{														\
		ir_node->attrs = attrs_stack.top();		\
		attrs_stack.pop();							\
	}														\
}															\
while (0)

		if(is_nil)
		{
			node_stack.push(NULL);
			is_nil = false;
		}
		else if(!strcmp(name, "attrs"))
		{
			// the <attrs> node isn't a proper child
			num_children_stack.top()--;
		}
		else if(!strcmp(name, "attr"))
		{
			// key is set when we see the open tag
			attrs_stack.top()->set(key, node_stack.top());
			node_stack.pop();
		}
		else if(!strcmp(name, "STRING"))
		{
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();

			ir_node = new STRING(value);
			copy_attrs ();
		}
		else if(!strcmp(name, "CAST"))
		{
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();

			ir_node = new CAST(value);
			copy_attrs ();
		}
		else if(!strcmp(name, "INT"))
		{
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ir_node = new INT(strtol(value->c_str(), 0, 0));
			copy_attrs ();
		}
		else if(!strcmp(name, "REAL"))
		{
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ir_node = new REAL(atof(value->c_str()));	
			copy_attrs ();
		}
		else if(!strcmp(name, "BOOL"))
		{
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			// BOOL::get_value_as_string returns "True" or "False"
			if(*value == "True")
				ir_node = new BOOL(true);
			else
				ir_node = new BOOL(false);
			copy_attrs ();
		}
		else if(!strcmp(name, "NIL"))
		{
			ir_node = new NIL();
			copy_attrs ();
		}
		else if(
 			 !strcmp(name, "value") 
		  || !strcmp(name, "string")
		  )
		{
			if(is_base64_encoded)
				node = base64_decode(&buffer);
			else
				node = new String(buffer);
		}
		else if(!strcmp(name, "bool"))
		{
			if(buffer == "true")
				node = new Boolean(true);
			else
				node = new Boolean(false);
		}
		else if(!strcmp(name, "integer"))
		{
			node = new Integer(strtol(buffer.c_str(), 0, 0));
		}
		else if(!strcmp(name, "string_list"))
		{
			List<String*>* string_list = new List<String*>;

			for(int i = 0; i < num_children; i++)
			{
				string_list->push_front(dynamic_cast<String*>(node_stack.top()));
				node_stack.pop();
			}

			node = string_list;
		}
		else 
		{
			List<Object*> args;

			for(int i = 0; i < num_children; i++)
			{
				args.push_front(node_stack.top());
				node_stack.pop();
			}
		
			node = Node_factory::create(name, &args);

			if(node == NULL)
			{
				phc_warning("XML parser: cannot deal with tag '%s'", name);
			}
			ir_node = dynamic_cast<Node*>(node);

			if(ir_node != NULL)
			{
				copy_attrs ();
			}
			else
			{
				// Must have been a list
			}
		}
	
		if(ir_node != NULL)
			node_stack.push(ir_node);
		else if(node != NULL)
			node_stack.push(node);

		XMLString::release(&name);
	}

	virtual void characters(const XMLCh* const chars, const unsigned int length)
	{
		if(no_errors)
		{
			char* content = XMLString::transcode(chars);
			buffer += content;
			XMLString::release(&content);
		}
	}

	void error(const SAXParseException& exception)
	{
		char* message = XMLString::transcode(exception.getMessage());
		::phc_warning("XML error: %s", NULL, exception.getLineNumber(), message);
		XMLString::release(&message);
		no_errors = false;
	}

	void fatalError(const SAXParseException& exception)
	{	
		char* message = XMLString::transcode(exception.getMessage());
		::phc_warning("XML error: %s", NULL, exception.getLineNumber(), message);
		XMLString::release(&message);
		no_errors = false;
	}

	void setDocumentLocator(const Locator* const locator)
	{
		// I love this one
		this->locator = &(*locator);
	}
};

template <class PHP_script, class Node, class Node_factory, class STRING, class CAST, class INT, class REAL, class BOOL, class NIL>
class XML_parser
{
public:
	PHP_script* parse_xml_file (String* filename)
	{
		XMLCh* name = XMLString::transcode(filename->c_str());
		LocalFileInputSource is (name);
		PHP_script* result = parse_xml(is);
		XMLString::release(&name);

		return result;
	}
	PHP_script* parse_xml_buffer(String* buffer)
	{
		MemBufInputSource is((XMLByte*) buffer->c_str(), buffer->length(), "parse_ast_xml_buffer", false);
		return parse_xml (is);
	}

	PHP_script* parse_xml_stdin()
	{
		StdInInputSource is;
		return parse_xml (is);
	}

	PHP_script* parse_xml (InputSource& inputSource)
	{
		SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
		parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
		parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);

		// TODO this is the AST xsd. But validation doesnt work anyway
		if(!args_info.no_validation_flag)
		{
			XMLCh* propertyValue = XMLString::transcode(
					"http://www.phpcompiler.org/phc-1.1 ./phc-1.1.xsd "
					"http://www.phpcompiler.org/phc-1.1 " DATADIR "/" PACKAGE "/phc-1.1.xsd");
			ArrayJanitor<XMLCh> janValue(propertyValue);
			parser->setProperty(XMLUni::fgXercesSchemaExternalSchemaLocation, propertyValue);

			parser->setFeature(XMLUni::fgXercesSchema, true);
			parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
			parser->setFeature(XMLUni::fgXercesDynamic, false);
		}

		PHC_SAX2Handler<PHP_script, Node, Node_factory, STRING, CAST, INT, REAL, BOOL, NIL>* phcHandler =
			new PHC_SAX2Handler <PHP_script, Node, Node_factory, STRING, CAST, INT, REAL, BOOL, NIL>();
		parser->setContentHandler(phcHandler);
		parser->setErrorHandler(phcHandler);

		try {
			parser->parse(inputSource);
		}
		catch (const XMLException& toCatch) {
			char* message = XMLString::transcode(toCatch.getMessage());
			phc_error(ERR_XML_PARSE, message);
		}
		catch (const SAXParseException& toCatch) {
			char* message = XMLString::transcode(toCatch.getMessage());
			phc_error(ERR_XML_PARSE, message);
		}
		catch (...) {
			phc_error(ERR_XML_PARSE, "Unexpected exception");
		}

		if(!phcHandler->no_errors)
			phc_error(ERR_XML_PARSE, "There were XML errors");

		PHP_script* result = phcHandler->result; 

		delete parser;
		delete phcHandler;

		return result;
	}
};

class AST_XML_parser : public XML_parser 
<
	AST::PHP_script,
	AST::Node,
	AST::Node_factory,
	AST::STRING,
	AST::CAST,
	AST::INT,
	AST::REAL,
	AST::BOOL,
	AST::NIL
>
{
};

class HIR_XML_parser : public XML_parser
<
	HIR::PHP_script,
	HIR::Node,
	HIR::Node_factory,
	HIR::STRING,
	HIR::CAST,
	HIR::INT,
	HIR::REAL,
	HIR::BOOL,
	HIR::NIL
>
{
};

class MIR_XML_parser : public XML_parser
<
	MIR::PHP_script,
	MIR::Node,
	MIR::Node_factory,
	MIR::STRING,
	MIR::CAST,
	MIR::INT,
	MIR::REAL,
	MIR::BOOL,
	MIR::NIL
>
{
};

#endif // HAVE_XERCES

#endif // PHC_XML_PARSER_H
