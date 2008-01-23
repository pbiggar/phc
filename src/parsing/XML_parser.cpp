/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the AST in XML format
 */

#include "XML_parser.h" 

#ifdef HAVE_XERCES

void init_xml ()
{
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) 
	{
		char* message = XMLString::transcode(toCatch.getMessage());
		phc_error(ERR_XML_PARSE, message);
	}
}

void shutdown_xml ()
{
	XMLPlatformUtils::Terminate();
}

#else

void init_xml () {};
void shutdown_xml () {};

#endif // HAVE_XERCES
