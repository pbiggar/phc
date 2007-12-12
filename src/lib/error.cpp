/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Error handling 
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/error.h"
#include "AST.h"
#include "HIR.h"
#include "MIR.h"
#include "cmdline.h"

// Generally we pass this through the pass manager. However, this is
// very ugly for error messages, as then we would need access
// everywhere we want to cause an error.
struct gengetopt_args_info error_args_info;

enum Error_type { WARNING=0, ERROR=1, INTERNAL_ERROR=2 };
static char* error_messages[] = { "Warning", "Error", "Internal error" };

void phc_message (Error_type type, const char* message_template, String* filename, int line, va_list argp)
{
	if(filename)
		fprintf(stderr, "%s:", filename->c_str());
	
	if(line > 0)
		fprintf(stderr, "%d:", line);

	if (filename or line > 0)
		fprintf(stderr, " ");
	
	fprintf(stderr, "%s: ", error_messages[type]);
	vfprintf(stderr, message_template, argp);
	fprintf(stderr, "\n");

	// A quick note to avoid complaints
	if(line > 0)
		fprintf(stderr, "Note that line numbers are inaccurate, and will be fixed"
		" in a later release\n");

	if (type != WARNING && not error_args_info.dont_fail_flag)
		exit(-1);

}

// Explicit names and line numbers.
#define define_explicit_message_func(NAME, TYPE)				\
void phc_##NAME (const char* message,								\
						String* filename, int line, ...)				\
{																				\
	va_list argp;															\
	va_start(argp, line);												\
	phc_message(TYPE, message, filename, line, argp);			\
	va_end(argp);															\
}

define_explicit_message_func (internal_error, INTERNAL_ERROR);
define_explicit_message_func (error, ERROR);
define_explicit_message_func (warning, WARNING);

// No filename or line number
#define define_null_message_func(NAME, TYPE)						\
void phc_##NAME (const char* message, ... )						\
{																				\
	va_list argp;															\
	va_start(argp, message);											\
	phc_message(TYPE, message, NULL, 0, argp);					\
	va_end(argp);															\
}


define_null_message_func (internal_error, INTERNAL_ERROR);
define_null_message_func (error, ERROR);
define_null_message_func (warning, WARNING);


// Use the node to pass the name or line number
#define define_node_message_func(NAME, TYPE, NODE)				\
void phc_##NAME (const char* message, NODE* node, ...)		\
{																				\
	va_list argp;															\
	va_start(argp, node);												\
	phc_message(TYPE, message,											\
		node->get_filename (),											\
		node->get_line_number (),										\
		argp);																\
	va_end(argp);															\
}

/* Templates cant be used here because the compiler uses this version instead
 * of the previous version, leading to compiler errors for messages like "%s"
 * or "%d". */
define_node_message_func (warning, WARNING, AST::Node);
define_node_message_func (warning, WARNING, HIR::Node);
define_node_message_func (warning, WARNING, MIR::Node);

define_node_message_func (error, ERROR, AST::Node);
define_node_message_func (error, ERROR, HIR::Node);
define_node_message_func (error, ERROR, MIR::Node);

define_node_message_func (internal_error, INTERNAL_ERROR, AST::Node);
define_node_message_func (internal_error, INTERNAL_ERROR, HIR::Node);
define_node_message_func (internal_error, INTERNAL_ERROR, MIR::Node);
