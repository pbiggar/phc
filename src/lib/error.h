/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Error handling 
 */

#ifndef PHC_ERROR
#define PHC_ERROR

#include <stdarg.h>
#include "lib/String.h"

// Messages for these errors are defined in error.cpp

enum _phc_error
{
	ERR_BISON = 1,
	ERR_EXPECT_VAR,
	ERR_FOREACH_KEY_REF,
	ERR_ABSTRACT_VARS,
	ERR_FINAL_VARS,
	ERR_XML_PARSE,
	ERR_NO_XML_SUPPORT,
	ERR_PLUGIN_NOT_FOUND,
	ERR_PLUGIN_INVALID,
	ERR_PLUGIN_UNKNOWN,
	ERR_FILE_NOT_FOUND,
	ERR_INVALID_INLINE_C,
	ERR_INTERNAL = 255,
};
typedef enum _phc_error phc_error_code;

enum _phc_warning
{
	WARNING_INCLUDE_FAILED = 1,
	WARNING_INCLUDE_RETURN,
	WARNING_XML,
	WARNING_UNKNOWN_ATTRIBUTE,
};
typedef enum _phc_warning phc_warning_code;

void phc_error (phc_error_code code, String* filename, int line, ...);
void phc_warning(phc_warning_code code, String* filename, int line, ...);


#endif
