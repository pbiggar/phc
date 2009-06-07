/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience functions and headers
 */

#ifndef PHC_GENERAL
#define PHC_GENERAL

#include "lib/String.h"


#include "debug.h"
#include "stats.h"
#include "Foreach.h"
#include "fresh.h"
#include "parsing/Parse_buffer.h"

using boost::lexical_cast;

bool is_builtin_function (String* name);

#endif // PHC_GENERAL
