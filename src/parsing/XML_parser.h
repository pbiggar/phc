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

#include <boost/lexical_cast.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/StdInInputSource.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/XMLString.hpp>

#include "lib/base64.h"
#include "lib/error.h"
#include "lib/AttrMap.h"
#include "lib/Stack.h"
#include "process_ir/General.h"
#include "AST.h"
#include "HIR.h"
#include "MIR.h"
#include "AST_factory.h"
#include "HIR_factory.h"
#include "MIR_factory.h"

#include "cmdline.h"
extern struct gengetopt_args_info args_info;

#define ERR_XML_PARSE "Could not parse the XML (%s)"

XERCES_CPP_NAMESPACE_USE
using namespace boost;

// The map wants a non-template class, so we put the code re-use in
// T_node_builder, and just put the definition here.
class Node_builder : public virtual GC_obj
{
public:
	virtual bool can_handle_token (string name) = 0;
	virtual Object* handle_token (string name, Object* param) = 0;

	virtual Object* create_node (char const* type, List<Object*>* args) = 0;
	virtual ~Node_builder () {}
};


template<
	class Factory,
	class STRING,
	class CAST,
	class INT,
	class REAL,
	class BOOL,
	class NIL,
	class FOREIGN
>
class T_Node_builder : public Node_builder
{
public:
	typedef T_Node_builder<Factory, STRING, CAST, INT, REAL, BOOL, NIL, FOREIGN> parent;

	virtual Object* handle_token (string name, Object* param)
	{
		String* value = dynamic_cast<String*> (param);

		// TODO CAST should be OK?
		// TODO all of these should be do-able, with minor changes to maketea.
		if (name == "STRING")
			return new STRING (value);

		else if (name == "CAST")
			return new CAST (value);

		else if (name == "INT")
			return new INT (lexical_cast <long> (*value));

		else if (name == "REAL")
			return new REAL (lexical_cast <double> (*value));

		else if (name == "BOOL")
		{
			// BOOL::get_value_as_string returns "True" or "False"
			if (*value == "True")
				return new BOOL(true);
			else
				return new BOOL(false);
		}

		else if (name == "NIL")
			return new NIL ();

		else
		{
			phc_internal_error ("Trying to parse token of unknown type: %s", name.c_str ());
			return NULL;
		}
	}

	virtual bool can_handle_token (string name)
	{
		return name == "STRING"
				|| name == "CAST"
				|| name == "INT"
				|| name == "REAL"
				|| name == "BOOL"
				|| name == "NIL";
	}

	Object* create_node (char const* type, List<Object*>* args)
	{
		// FOREIGN is special in that its a token with subnodes, which must be
		// processed first.
		if (type == *s("FOREIGN"))
		{
			assert (args->size () == 1);
			return new FOREIGN (dyc<IR::Node> (args->front ()));
		}
		else
			return Factory::create (type, args);
	}
};



class AST_node_builder : public T_Node_builder
<
	AST::Node_factory,
	AST::STRING,
	AST::CAST,
	AST::INT,
	AST::REAL,
	AST::BOOL,
	AST::NIL,
	AST::FOREIGN
>
{
};

class HIR_node_builder : public T_Node_builder
<
	HIR::Node_factory,
	HIR::STRING,
	HIR::CAST,
	HIR::INT,
	HIR::REAL,
	HIR::BOOL,
	HIR::NIL,
	HIR::FOREIGN
>
{
};

class MIR_node_builder : public T_Node_builder
<
	MIR::Node_factory,
	MIR::STRING,
	MIR::CAST,
	MIR::INT,
	MIR::REAL,
	MIR::BOOL,
	MIR::NIL,
	MIR::FOREIGN
>
{
	bool can_handle_token (string name)
	{
		return name == "PARAM_INDEX" || parent::can_handle_token (name);
	}


	Object* handle_token (string name, Object* param)
	{
		if (name == "PARAM_INDEX")
		{
			return new MIR::PARAM_INDEX (lexical_cast <int> (*dyc<String> (param)));
		}
		else
			return parent::handle_token (name, param);
	}
};

class PHC_SAX2Handler : public DefaultHandler, public virtual GC_obj
{
protected:
	Stack<Object*> node_stack;
private:
	Stack<int> num_children_stack;
	bool is_nil, is_base64_encoded;
	String buffer;
	Stack<string> key_stack;
	Stack<AttrMap*> attrs_stack;
	const Locator* locator;

public:
	IR::PHP_script* result;
	bool no_errors;
	Map<string, Node_builder*> builders;

public:
	PHC_SAX2Handler() 
	{
		builders["AST"] = new AST_node_builder;
		builders["HIR"] = new HIR_node_builder;
		builders["MIR"] = new MIR_node_builder;
	}

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
			result = dynamic_cast<IR::PHP_script*>(node_stack.top());
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
				key_stack.push (attr_value);
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

		String* ns = s (string (XMLString::transcode(qname)).substr (0, 3));
		if (*ns != "AST" && *ns != "HIR" && *ns != "MIR")
			ns = NULL;


		Object* node = NULL;
		bool accept_attrs = true;

		// Number of children of the node we are about to create
		int num_children = num_children_stack.top();

		// After we pop, num_children_stack.top() corresponds to the number
		// of children of the *parent* of the node we are about to create
		num_children_stack.pop();

		if (debugging_enabled)
		{
			cdebug 
				<< "Evaluating: " << name 
				<< ", and buffer: " << buffer 
				<< " with " << num_children << " children";

			if (num_children_stack.size() > 0)
				cdebug << ", and " << num_children_stack.top() << " parent's children";
			cdebug << ". With " << node_stack.size() << " nodes on the stack";
			if (node_stack.size() > 0)
			{
				cdebug << ", with the top one ";
				if (String* str = dynamic_cast<String*>(node_stack.top()))
					cdebug << "being a string with value: " << *str;
				else
					cdebug << "having type: " << typeid (node_stack.top()).name ();
			}
			cdebug << ", with " << attrs_stack.size() << " AttrMaps on the stack";
			cdebug << ", and " << key_stack.size() << " keys on the stack.";

			cdebug << std::endl;
		}

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
			string key = key_stack.top ();
			key_stack.pop();

			DEBUG ("Attr with key: " << key);
			// key is set when we see the open tag
			attrs_stack.top()->set(key, node_stack.top());
			node_stack.pop();
		}
		else if(num_children == 0 &&
				(!strcmp(name, "string")
				|| !strcmp(name, "value")))
		{
			if(is_base64_encoded)
				node = base64_decode(&buffer);
			else
				node = new String(buffer);
		}
		else if (!strcmp(name, "value")
			&& num_children == 1)
		{
			// Must be the child of a FOREIGN
			node = node_stack.top();
			node_stack.pop();

			// Don't let this take two attrs
			accept_attrs = false;
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
			node = new ::Integer(strtol(buffer.c_str(), 0, 0));
		}
		else if(!strcmp(name, "string_list"))
		{
			String_list* string_list = new String_list;

			for(int i = 0; i < num_children; i++)
			{
				string_list->push_front(dyc<String>(node_stack.top()));
				node_stack.pop();
			}

			node = string_list;
		}
		else if(!strcmp(name, "node_list"))
		{
			IR::Node_list* node_list = new IR::Node_list;

			for(int i = 0; i < num_children; i++)
			{
				node_list->push_front(dyc<IR::Node>(node_stack.top()));
				node_stack.pop();
			}

			node = node_list;
		}
		else if (ns 
			&& builders[*ns]->can_handle_token (name))
		{
			Object* arg = NULL;
			if (num_children == 1)
			{
				arg = node_stack.top();
				node_stack.pop ();
			}
				else assert (num_children == 0);

			node = builders[*ns]->handle_token (name, arg);
		}
		else 
		{
			List<Object*> args;

			for(int i = 0; i < num_children; i++)
			{
				args.push_front(node_stack.top());
				node_stack.pop();
			}

			assert (ns);
			node = builders[*ns]->create_node (name, &args);

			if(node == NULL)
			{
				phc_warning("XML parser: cannot deal with tag '%s' in namespace '%s'", name, ns ? ns->c_str() : "NONE");
			}
		}

		// Fetch attributes
		if(accept_attrs && isa <IR::Node> (node))
		{
			IR::Node* attr_node = dyc<IR::Node> (node);
			if (attrs_stack.size() > 0)
			{
				attr_node->attrs = attrs_stack.top();
				attrs_stack.pop();
			}
			else
			{
				// TODO: This is fine if there are no attributes, but if some nodes
				// are missing attributes it'll be a problem.

				// There might be no attributes in the XML file.
				attr_node->attrs = new AttrMap ();
			}
		}
	
		if(node != NULL)
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
		::phc_warning("XML error: %s", NULL, exception.getLineNumber(), exception.getColumnNumber(), message);
		XMLString::release(&message);
		no_errors = false;
	}

	void fatalError(const SAXParseException& exception)
	{	
		char* message = XMLString::transcode(exception.getMessage());
		::phc_warning("XML error: %s", NULL, exception.getLineNumber(), exception.getColumnNumber(), message);
		XMLString::release(&message);
		no_errors = false;
	}

	void setDocumentLocator(const Locator* const locator)
	{
		// I love this one
		this->locator = &(*locator);
	}
};

class XML_parser : public virtual GC_obj
{
public:
	IR::PHP_script* parse_xml_file (String* filename)
	{
		XMLCh* name = XMLString::transcode(filename->c_str());
		LocalFileInputSource is (name);
		IR::PHP_script* result = parse_xml(is);
		XMLString::release(&name);

		return result;
	}
	IR::PHP_script* parse_xml_buffer(String* buffer)
	{
		MemBufInputSource is((XMLByte*) buffer->c_str(), buffer->length(), "parse_ast_xml_buffer", false);
		return parse_xml (is);
	}

	IR::PHP_script* parse_xml_stdin()
	{
		StdInInputSource is;
		return parse_xml (is);
	}

	IR::PHP_script* parse_xml (InputSource& inputSource)
	{
		SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
		parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
		parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);

		// TODO this is the AST xsd. But validation doesnt work anyway
		if(!args_info.no_xml_validation_flag)
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

		PHC_SAX2Handler* phcHandler = new PHC_SAX2Handler;
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

		IR::PHP_script* result = phcHandler->result; 

		delete parser;
		delete phcHandler;

		return result;
	}
};

#endif // HAVE_XERCES

#endif // PHC_XML_PARSER_H
