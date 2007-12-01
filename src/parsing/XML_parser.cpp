/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the AST in XML format
 */

#include "XML_parser.h" 

#ifdef HAVE_XERCES

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

#include "cmdline.h"
extern struct gengetopt_args_info args_info;

using namespace AST;

#define ERR_XML_PARSE "Could not parse the XML (%s)"

XERCES_CPP_NAMESPACE_USE

PHP_script* parse_ast_xml(InputSource& inputSource);

class PHC_SAX2Handler : public DefaultHandler {
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
		Node* ast_node = NULL;
		String* value;
		String* source_rep;

		// Number of children of the node we are about to create
		int num_children = num_children_stack.top();

		// After we pop, num_children_stack.top() corresponds to the number
		// of children of the *parent* of the node we are about to create
		num_children_stack.pop();

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
			source_rep = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ast_node = new STRING(value, source_rep);
			ast_node->attrs = attrs_stack.top();
			attrs_stack.pop();
		}
		else if(!strcmp(name, "CAST"))
		{
			source_rep = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ast_node = new CAST(value, source_rep);
			ast_node->attrs = attrs_stack.top();
			attrs_stack.pop();
		}
		else if(!strcmp(name, "INT"))
		{
			source_rep = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ast_node = new INT(strtol(value->c_str(), 0, 0), source_rep);
			ast_node->attrs = attrs_stack.top();
			attrs_stack.pop();
		}
		else if(!strcmp(name, "REAL"))
		{
			source_rep = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ast_node = new REAL(atof(value->c_str()), source_rep);	
			ast_node->attrs = attrs_stack.top();
			attrs_stack.pop();
		}
		else if(!strcmp(name, "BOOL"))
		{
			source_rep = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			value = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			// BOOL::get_value_as_string returns "True" or "False"
			if(*value == "True")
				ast_node = new BOOL(true, source_rep);
			else
				ast_node = new BOOL(false, source_rep);
			ast_node->attrs = attrs_stack.top();
			attrs_stack.pop();
		}
		else if(!strcmp(name, "NIL"))
		{
			source_rep = dynamic_cast<String*>(node_stack.top()); node_stack.pop();
			
			ast_node = new NIL(source_rep);
			ast_node->attrs = attrs_stack.top();
			attrs_stack.pop();
		}
		else if(
 			 !strcmp(name, "value") 
		  || !strcmp(name, "source_rep")
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
			ast_node = dynamic_cast<Node*>(node);

			if(ast_node != NULL)
			{
				ast_node->attrs = attrs_stack.top();
				attrs_stack.pop();
			}
			else
			{
				// Must have been a list
			}
		}
	
		if(ast_node != NULL)
			node_stack.push(ast_node);
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

PHP_script* parse_ast_xml_file(String* filename)
{
	PHP_script* result;

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, message);
	}

	XMLCh* name = XMLString::transcode(filename->c_str());
	LocalFileInputSource* is = new LocalFileInputSource(name);
	result = parse_ast_xml(*is);
	XMLString::release(&name);

	delete is;
	XMLPlatformUtils::Terminate();

	return result;
}

PHP_script* parse_ast_xml_buffer(String* buffer)
{
	PHP_script* result;

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, message);
	}

	MemBufInputSource* is = new MemBufInputSource((XMLByte*) buffer->c_str(), buffer->length(), "parse_ast_xml_buffer", false);
	result = parse_ast_xml(*is);

	delete is;
	XMLPlatformUtils::Terminate();

	return result;
}

PHP_script* parse_ast_xml_stdin()
{
	PHP_script* result;

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, message);
	}

	StdInInputSource* is = new StdInInputSource();
	result = parse_ast_xml(*is);

	delete is;
	XMLPlatformUtils::Terminate();

	return result;
}

PHP_script* parse_ast_xml(InputSource& inputSource)
{
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
	
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

	PHC_SAX2Handler* phcHandler = new PHC_SAX2Handler();
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

#endif // HAVE_XERCES
