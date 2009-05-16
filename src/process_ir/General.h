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

//#define PUNT do { throw "punting"; } while (0)
//#define OPT_ASSERT(A) do { if (A) throw "punting"; } while (0)

// TODO: change these back later
#define PUNT assert (0);
#define OPT_ASSERT(A) assert (A);

using boost::lexical_cast;

bool is_builtin_function (String* name);

#endif // PHC_GENERAL
