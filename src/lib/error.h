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

void phc_error (const char*, String* filename, int line, ...);
void phc_error (const char*, ...);

void phc_warning (const char*, String* filename, int line, ...);
void phc_warning (const char*, ...);


#endif
