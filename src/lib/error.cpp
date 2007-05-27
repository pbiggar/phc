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

void phc_message (const char* type, const char* message_template, String* filename, int line, va_list argp)
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
void phc_error (const char* message, String* filename, int line, ...)
{
	va_list argp;
	va_start(argp, line);
	phc_message ("Error", message, filename, line, argp);
	va_end(argp);
	exit(-1);
}

// Print the error message and quit
void phc_error (const char* message, ...)
{
	va_list argp;
	va_start(argp, message);
	phc_message ("Error", message, NULL, 0, argp);
	va_end(argp);
	exit(-1);
}



// Print the warning and continue 
void phc_warning (const char* message, String* filename, int line, ...)
{
	va_list argp;
	va_start(argp, line);
	phc_message ("Warning", message, filename, line, argp);
	va_end(argp);
}
