/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Error handling 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lib/error.h"

// printf format statements are supported

char*
phc_error_string (phc_error_code code)
{
	switch (code)
	{
		case ERR_BISON:
			return "%s";
			break;
		case ERR_EXPECT_VAR:
			return "Variable name expected";
			break;
		case ERR_FOREACH_KEY_REF:
			return "Key element cannot be a reference";
			break;
		case ERR_ABSTRACT_VARS:
			return "Cannot declare variables to be abstract";
			break;
		case ERR_FINAL_VARS:
			return "The final modifier is only allowed for methods";
			break;
		case ERR_XML_PARSE:
			return "Could not parse the XML (%s)";
			break;
		case ERR_NO_XML_SUPPORT:
			return "XML support not built-in; install Xerces C development library";
			break;
		case ERR_PLUGIN_NOT_FOUND:
			return "Could not find %s plugin with errors \"%s\", \"%s\" and \"%s\"";
			break;
		case ERR_PLUGIN_INVALID:
			return "Invalid plugin (%s): %s";
			break;
		case ERR_PLUGIN_UNKNOWN:
			return "Unknown error (%s) with plugin %s";
			break;
		case ERR_FILE_NOT_FOUND:
			return "File not found";
			break;
		case ERR_INVALID_INLINE_C:
			return "Invalid 'inline-c' directive";
			break;
		case ERR_INTERNAL:
			return "Internal error";
			break;
	}
	assert (false);
}

char*
phc_warning_string (phc_warning_code code)
{
	switch (code)
	{
		case WARNING_INCLUDE_FAILED:
			return "File %s could not be included";
			break;
		case WARNING_INCLUDE_RETURN:
			return "Returning values from included scripts is not supported in file %s";
			break;
		case WARNING_XML:
			return "XML error: %s";
			break;
		case WARNING_UNKNOWN_ATTRIBUTE:
			return "Unknown attribute '%s'";
			break;
	}
	assert (false);
}

void
phc_message (char* type, char* message_template, String* filename, int line, va_list argp)
{
	if(filename)
		fprintf(stderr, "%s:", filename->c_str());
	
	if(line > 0)
		fprintf(stderr, "%d:", line);

	if (filename or line > 0)
		fprintf(stderr, " ");
	
	fprintf(stderr, "%s: ", type);
	vfprintf(stderr, message_template, argp);
	fprintf(stderr, "\n");

	// A quick note to avoid complaints
	if(line > 0)
		fprintf(stderr, "Note that line numbers are inaccurate, and will be fixed"
		" in a later release\n");
}

// Print the error message and quit
void 
phc_error (phc_error_code code, String* filename, int line, ...)
{
	va_list argp;
	va_start(argp, line);
	phc_message ("Error", phc_error_string(code), filename, line, argp);
	va_end(argp);
	exit(int(code));
}

// Print the warning and continue 
void 
phc_warning (phc_warning_code code, String* filename, int line, ...)
{
	va_list argp;
	va_start(argp, line);
	phc_message ("Warning", phc_warning_string (code), filename, line, argp);
	va_end(argp);
}
