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

#include "cmdline.h"
extern struct gengetopt_args_info args_info;

XERCES_CPP_NAMESPACE_USE

AST_php_script* parse_ast_xml(InputSource& inputSource);

class PHC_SAX2Handler : public DefaultHandler {
private:
	stack<Object*> nodes;
	stack<int> num_children;
	bool is_nil, is_base64_encoded;
	String buffer;
	String* source_rep;
	string key;
	stack<AttrMap*> attrs_stack;
	const Locator* locator;

	bool is_ast_node(const XMLCh* const uri, const XMLCh* const name)
	{
		bool rv;

		char* elem_uri = XMLString::transcode(uri);
		char* elem_name = XMLString::transcode(name);

		if(strcmp(elem_uri, "http://www.phpcompiler.org/phc-1.0"))
			rv = false;
		else if(!strncmp(elem_name, "AST_", 4))
			rv = true;
		else if(!strncmp(elem_name, "Token_", 6))
			rv = true;
		else
			rv = false;
	
		XMLString::release(&elem_uri);
		XMLString::release(&elem_name);

		return rv;
	}

public:
	AST_php_script* result;
	bool no_errors;

public:
	PHC_SAX2Handler() {}

public:
	void startDocument()
	{
		num_children.push(0);
		no_errors = true;
	}

	void endDocument()
	{
		if(no_errors)
		{
			result = dynamic_cast<AST_php_script*>(nodes.top());
		}
	}

	void startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const Attributes& attrs
	)
	{
		if(no_errors)
		{
			is_nil = false;
			is_base64_encoded = false;
	
			// Clear the attribute map when seeing <attrs>
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
				
				if(!strcmp(attr_uri, "") &&
					!strcmp(attr_name, "key") &&
					!strcmp(name, "attr"))
				{
					key = attr_value;

					if(key == "phc.comments")
					{
						(*attrs_stack.top())["phc.comments"] = new List<String*>;
					}
				}
			
				XMLString::release(&attr_uri);
				XMLString::release(&attr_name);
				XMLString::release(&attr_value);
			}
	
			if(is_ast_node(uri, localname))
			{
				if(!is_nil)
					num_children.push(0);
			}
			else
			{
				buffer = "";
			}
		}
	}

	void endElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	)
	{
		if(no_errors)
		{
			char* name = XMLString::transcode(localname);
	
			if(!strcmp(name, "attrs"))
			{
				// ignore 
			}
			else if(!strcmp(name, "attr"))
			{
				if(key == "phc.line_number")
				{
					attrs_stack.top()->set("phc.line_number", new Integer(strtol(buffer.c_str(), 0, 0)));
				}
				else if(key == "phc.filename")
				{
					attrs_stack.top()->set("phc.filename", new String(buffer));
				}
				else if(key == "phc.comments")
				{
					// Dealt with in the start tag rather than the end tag
				}
				else if(key == "phc.unparser.needs_brackets")
				{
					if(buffer == "true")
						attrs_stack.top()->set("phc.unparser.needs_brackets", new Boolean(true));
					else
						attrs_stack.top()->set("phc.unparser.needs_brackets", new Boolean(false));
				}
				else if(key == "phc.unparser.needs_curlies")
				{
					if(buffer == "true")
						attrs_stack.top()->set("phc.unparser.needs_curlies", new Boolean(true));
					else
						attrs_stack.top()->set("phc.unparser.needs_curlies", new Boolean(false));
				}
				else if(key == "phc.unparser.is_elseif")
				{
					if(buffer == "true")
						attrs_stack.top()->set("phc.unparser.is_elseif", new Boolean(true));
					else
						attrs_stack.top()->set("phc.unparser.is_elseif", new Boolean(false));
				}
				else if(key == "phc.unparser.is_global_stmt")
				{
					if(buffer == "true")
						attrs_stack.top()->set("phc.unparser.is_global_stmt", new Boolean(true));
					else
						attrs_stack.top()->set("phc.unparser.is_global_stmt", new Boolean(false));
				}
				else if(key == "phc.unparser.is_opeq")
				{
					if(buffer == "true")
						attrs_stack.top()->set("phc.unparser.is_opeq", new Boolean(true));
					else
						attrs_stack.top()->set("phc.unparser.is_opeq", new Boolean(false));
				}
				else
				{
					::phc_warning(WARNING_UNKNOWN_ATTRIBUTE, NULL, locator->getLineNumber(), key.c_str()); 
				}
			}
			else if(!strcmp(name, "comment"))
			{
				Object* attr = (*attrs_stack.top())["phc.comments"];
				List<String*>* comments = dynamic_cast<List<String*>*>(attr);
				if(is_base64_encoded)
					comments->push_back(base64_decode(&buffer));
				else
					comments->push_back(new String(buffer));
					
			}
			else if(is_nil)
			{
				nodes.push(NULL);
				num_children.top()++;
				is_nil = false;
			}
			else if(is_ast_node(uri, localname))
			{
				List<Object*> args;
				AST_node* node;
	
				if(!strcmp(name, "Token_string"))
				{
					String* value = dynamic_cast<String*>(nodes.top());
					node = new Token_string(value, source_rep);
					node->attrs = attrs_stack.top();
					attrs_stack.pop();
					nodes.pop();
				}
				else if(!strcmp(name, "Token_int"))
				{
					String* value = dynamic_cast<String*>(nodes.top());
					node = new Token_int(strtol(value->c_str(), 0, 0), source_rep);
					node->attrs = attrs_stack.top();
					attrs_stack.pop();
					nodes.pop();
				}
				else if(!strcmp(name, "Token_real"))
				{
					String* value = dynamic_cast<String*>(nodes.top());
					node = new Token_real(atof(value->c_str()), source_rep);	
					node->attrs = attrs_stack.top();
					attrs_stack.pop();
					nodes.pop();
				}
				else if(!strcmp(name, "Token_bool"))
				{
					String* value = dynamic_cast<String*>(nodes.top());
					// Token_bool::get_value_as_string returns "True" or "False"
					if(*value == "True")
						node = new Token_bool(true, source_rep);
					else
						node = new Token_bool(false, source_rep);
					node->attrs = attrs_stack.top();
					attrs_stack.pop();
					nodes.pop();
				}
				else if(!strcmp(name, "Token_null"))
				{
					node = new Token_null(source_rep);
					node->attrs = attrs_stack.top();
					attrs_stack.pop();
				}
				else
				{
					for(int i = 0; i < num_children.top(); i++)
					{
						args.push_front(nodes.top());
						nodes.pop();
					}
					assert (0);
	
//					node = AST_node_factory::create(name, &args);
					node->attrs = attrs_stack.top();
					attrs_stack.pop();
				}
			
				num_children.pop();
				nodes.push(node);
				num_children.top()++;
			}
			else
			{
				if(!strcmp(name, "value"))
				{
					if(is_base64_encoded)
						nodes.push(base64_decode(&buffer));
					else
						nodes.push(new String(buffer));
	
					num_children.top()++;
				}
				else if(!strcmp(name, "bool"))
				{
					if(buffer == "true")
						nodes.push(new Boolean(true));
					else
						nodes.push(new Boolean(false));
					num_children.top()++;
				}
				else if(!strcmp(name, "source_rep"))
				{
					if(is_base64_encoded)
						source_rep = base64_decode(&buffer);
					else
						source_rep = new String(buffer);
				}
			}
	
			XMLString::release(&name);
		}
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
		::phc_warning(WARNING_XML, NULL, exception.getLineNumber(), message);
		XMLString::release(&message);
		no_errors = false;
	}

	void fatalError(const SAXParseException& exception)
	{	
		char* message = XMLString::transcode(exception.getMessage());
		::phc_warning(WARNING_XML, NULL, exception.getLineNumber(), message);
		XMLString::release(&message);
		no_errors = false;
	}

	void setDocumentLocator(const Locator* const locator)
	{
		// I love this one
		this->locator = &(*locator);
	}
};

AST_php_script* parse_ast_xml_file(String* filename)
{
	AST_php_script* result;

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, NULL, 0, message);
	}

	XMLCh* name = XMLString::transcode(filename->c_str());
	LocalFileInputSource* is = new LocalFileInputSource(name);
	result = parse_ast_xml(*is);
	XMLString::release(&name);

	delete is;
	XMLPlatformUtils::Terminate();

	return result;
}

AST_php_script* parse_ast_xml_buffer(String* buffer)
{
	AST_php_script* result;

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, NULL, 0, message);
	}

	MemBufInputSource* is = new MemBufInputSource((XMLByte*) buffer->c_str(), buffer->length(), "parse_ast_xml_buffer", false);
	result = parse_ast_xml(*is);

	delete is;
	XMLPlatformUtils::Terminate();

	return result;
}

AST_php_script* parse_ast_xml_stdin()
{
	AST_php_script* result;

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, NULL, 0, message);
	}

	StdInInputSource* is = new StdInInputSource();
	result = parse_ast_xml(*is);

	delete is;
	XMLPlatformUtils::Terminate();

	return result;
}

AST_php_script* parse_ast_xml(InputSource& inputSource)
{
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
	
	if(!args_info.no_validation_flag)
	{
		XMLCh* propertyValue = XMLString::transcode(
			"http://www.phpcompiler.org/phc-1.0 ./phc-1.0.xsd "
			"http://www.phpcompiler.org/phc-1.0 " DATADIR "/" PACKAGE "/phc-1.0.xsd");
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
		phc_error(ERR_XML_PARSE, NULL, 0, message);
	}
	catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, NULL, 0, message);
	}
	catch (...) {
		phc_error(ERR_XML_PARSE, NULL, 0, "Unexpected exception");
	}

	if(!phcHandler->no_errors)
		phc_error(ERR_XML_PARSE, NULL, 0, "There were XML errors");
	
	AST_php_script* result = phcHandler->result; 

	delete parser;
	delete phcHandler;
	
	return result;
}

#endif // HAVE_XERCES
